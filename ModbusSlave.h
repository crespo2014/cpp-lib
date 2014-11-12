/*
 * ModbusSlave.h
 *
 *  Created on: 13 Mar 2014
 *      Author: lester
 */

#ifndef MODBUSSLAVE_H_
#define MODBUSSLAVE_H_

#include "ModbusCmd.h"
#include "iobase.h"
#include "Modbus.h"
#include "log.h"

using namespace io;

typedef unsigned short (*fncGetMsg)(const ModbusCmd& cmd, Buffer &blck);
typedef unsigned short (*fncGetData)(const Buffer &blck, ModbusCmd& cmd);

class ModbusSlaveProtocol: public Modbus
{

	/*
	 * Fill a rtu main frame response CRC16 is optional
	 * Not check of length
	 * return
	 * 	ptr will be on last position
	 */
	static void RTU_ReplyData(const ModbusCmd& cmd, uint8_t* &ptr, bool crc16)
	{
		uint8_t* start = ptr;
		// set values and got o next position
		*ptr++ = cmd.slave & 0xFF;
		*ptr++ = cmd.function;
		switch (cmd.function)
		{
		case ModbusCmd::MODBUS_FC_READ_COILS:
		case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
			*ptr++ = (cmd.count * cmd.data_size_bits + 7) / 8;	//set byte count
			if (cmd.data_size_bits == 1)
			{
				--ptr;	//  pointer will be increment on first loop interaction
				for (uint16_t data_pos = 0, bit_pos = 256; data_pos < cmd.count; ++data_pos)
				{
					// go to next position if bit is in 9,
					if (bit_pos == 256)
					{
						*(++ptr) = 0;    // clear data on first bit
						bit_pos = 1;
					}
					// set bit if values is not zero
					if (cmd.u8data[data_pos]) (*ptr) |= bit_pos;
					bit_pos <<= 1;
				}
				// go to next position if
				++ptr;
			} else if (cmd.data_size_bits == 16)
			{
				for (uint16_t data_pos = 0; data_pos < cmd.count; ++data_pos)
				{
					*ptr++ = cmd.u16data[data_pos] / 256;
					*ptr++ = cmd.u16data[data_pos] & 0xFF;
				}
			} else
				throw error_api(ERROR_INFO(),api_error::get_protocol());
			break;
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
			*ptr = cmd.start_address / 256;
			++ptr;
			*ptr = cmd.start_address & 0xFF;
			++ptr;
			if (cmd.data_size_bits == 1)
			{
				if (*cmd.u8data)
					*ptr++ = 0xff;
				else
					*ptr++ = 0;
				*ptr++ = 0;
			} else if (cmd.data_size_bits == 16)
			{
				*ptr++ = (*cmd.u16data) / 256;
				*ptr++ = (*cmd.u16data) & 0xFF;
			} else
				throw error_api(ERROR_INFO(),api_error::get_protocol());
			break;
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
			*ptr++ = cmd.start_address / 256;
			*ptr++ = cmd.start_address & 0xFF;
			*ptr++ = cmd.count / 256;
			*ptr++ = cmd.count & 0xFF;
			break;
		default:
			throw error_api(ERROR_INFO(),api_error::get_protocol());
		}
		if (crc16)
		{
			ptr += 2;
			SetCRC16(start, ptr - start);
		}
	}

	/*
	 * Create a reply data command for RTU
	 * simple register reply is allowed
	 * 1 Bit data is ready as byte from u8data
	 * 16 bits data is read as short from u16data pointer must be alignment
	 */
	static void RTU_ReplyData(const ModbusCmd& cmd, Buffer &blck)
	{
		uint8_t* ptr = reinterpret_cast<uint8_t*>(blck.getW());
		uint16_t len = 0;

		/*
		 * Check if there is a exception
		 */
		if (cmd.exception)
		{
			len = 5;
		} else
		// check if there is enough room to store reply message
		switch (cmd.function)
		{
		case ModbusCmd::MODBUS_FC_READ_COILS:
		case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
			len = 5 + (cmd.count * cmd.data_size_bits + 7) / 8;
			break;
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
			len = 8;
			break;
		default:
			throw error_api(ERROR_INFO(),api_error::get_protocol());
		}
		if (len >= blck.getWSize()) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		blck.updateW(len);
		if (cmd.exception)
		{
			*ptr++ = (cmd.slave &0xFF);
			*ptr++ = (cmd.function | 0x80);
		}
		return RTU_ReplyData(cmd, ptr, true);
	}
	/*
	 * Fill a response with data for a modbus tcp protocol
	 */
	static void TCP_ReplyData(const ModbusCmd& cmd, Buffer &blck)
	{
		uint8_t* ptr = reinterpret_cast<uint8_t*>(blck.getW());
		uint16_t len = 0;

		// check if there is enough room to store reply message
		switch (cmd.function)
		{
		case ModbusCmd::MODBUS_FC_READ_COILS:
		case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
		case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
			len = MODBUS_TCP_PRESET_REQ_LENGTH + 3 + (cmd.count * cmd.data_size_bits + 7) / 8;
			break;
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
			len = MODBUS_TCP_PRESET_REQ_LENGTH + 1 + 1 +2 + 2;
			break;
		default:
			throw error_api(ERROR_INFO(),api_error::get_protocol());
		}
		*ptr++ = cmd.transation_id / 256;
		*ptr++ = cmd.transation_id & 0xFF;
		*ptr++ = 0;
		*ptr++ = 0;
		*ptr++ = (len - MODBUS_TCP_PRESET_REQ_LENGTH) / 256;
		*ptr++ = (len - MODBUS_TCP_PRESET_REQ_LENGTH) & 0xFF;
		blck.updateW(len);
		return RTU_ReplyData(cmd, ptr, false);
	}

public:
	static void getData(const Buffer &blck, ModbusCmd& cmd,api_error& e);
	static void ASCII_getData(const Buffer& blck, ModbusCmd& cmd,api_error& e);
	static void RTU_getData(const Buffer& blck, ModbusCmd& cmd,api_error& e);
	static void TCP_getData(const Buffer& blck, ModbusCmd& cmd,api_error& e);
	static void ELAM_getData(const Buffer& blck, ModbusCmd& cmd,api_error& e);
	/*
	 create a reply command
	 data will be get from dat pointer
	 data of size bit will be read as u8 and packet
	 */
	static void getReply(const ModbusCmd& cmd, Buffer &blck);

};

#endif /* MODBUSSLAVE_H_ */
