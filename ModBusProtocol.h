/*
 * ModBusProtocol.h
 *
 *  Created on: 19 Feb 2014
 *      Author: lester
 */

#ifndef MODBUSPROTOCOL_H_
#define MODBUSPROTOCOL_H_

#include "Modbus.h"
#include "ModbusCmd.h"
#include "iobase.h"
#include "Buffer.h"
#include "MonotonicTime.h"

using namespace io;

typedef void (*fncMsg)(const ModbusCmd& cmd, Buffer &blck);
typedef void (*fncData)(const io::Buffer &blck, ModbusCmd& cmd);

class ModBusProtocol: public Modbus
{
	// ASCII Protocol
	static void ASCII_msg_WriteSingleRegister(const ModbusCmd& cmd, Buffer &blck, unsigned char data_size_bits);
	static void ASCII_msg_WriteMultipleRegisters(const ModbusCmd& cmd, Buffer &blck, unsigned char data_size_bits);
	static void ASCII_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck);
	//static unsigned short ASCII_respReadDiscreteInput(Buffer &blck, ModbusCmd& cmd);
	static void ASCII_getData(Buffer &blck, ModbusCmd& cmd,api_error& e);
	static void ASCII_msgWriteSingleCoil(const ModbusCmd& cmd, Buffer &blck)
	{
		return ASCII_msg_WriteSingleRegister(cmd, blck, 1);
	}
	static void ASCII_msgWriteSingleRegister(const ModbusCmd& cmd, Buffer &blck)
	{
		return ASCII_msg_WriteSingleRegister(cmd, blck, 16);
	}
	static void ASCII_msgWriteMultipleRegister(const ModbusCmd& cmd, Buffer &blck)
	{
		return ASCII_msg_WriteMultipleRegisters(cmd, blck, 16);
	}
	static void ASCII_msgWriteMultipleCoil(const ModbusCmd& cmd, Buffer &blck)
	{
		return ASCII_msg_WriteMultipleRegisters(cmd, blck, 16);
	}
	// RTU Protocol
	static void RTU_getData(Buffer &blck, ModbusCmd& cmd,api_error& e);
	static void RTU_msg_WriteMultipleRegisters(const ModbusCmd& cmd, Buffer &blck);
	static void RTU_msg_WriteSingleRegister(const ModbusCmd& cmd, Buffer &blck);
	static void RTU_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck);

	// TCP Protocol
	static void TCP_getData(Buffer &blck, ModbusCmd& cmd,api_error& e);
	static void TCP_msg_WriteSingleRegister(const ModbusCmd& cmd, Buffer &blck);
	static void TCP_msg_WriteMultipleRegisters(const ModbusCmd& cmd, Buffer &blck);
	static void TCP_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck);
public:

	static void getData(Buffer &blck, ModbusCmd& cmd,api_error& e)
	{
		if (cmd.protocol == ModbusCmd::MODBUS_PROTO_ASCII)
			return ASCII_getData(blck, cmd,e);
		else if ((cmd.protocol == ModbusCmd::MODBUS_PROTO_RTU) || (cmd.protocol == ModbusCmd::MODBUS_PROTO_RTU_OVER_TCP))
			return RTU_getData(blck, cmd,e);
		else if (cmd.protocol == ModbusCmd::MODBUS_PROTO_TCP)
			return TCP_getData(blck, cmd,e);
	}
	static void getMessage(const ModbusCmd& cmd, Buffer &blck)
	{
		static unsigned char proto_idx[] = {    //
				ModbusCmd::MODBUS_PROTO_ASCII, ModbusCmd::MODBUS_PROTO_RTU, ModbusCmd::MODBUS_PROTO_TCP, ModbusCmd::MODBUS_PROTO_RTU_OVER_TCP };
		static unsigned char fnc_idx[] = {    //
				ModbusCmd::MODBUS_FC_READ_COILS, ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS, ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS,
						ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS, ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL, ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER, /*MODBUS_FC_READ_EXCEPTION_STATUS,*/
						ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS, ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS /*, MODBUS_FC_REPORT_SLAVE_ID, MODBUS_FC_WRITE_AND_READ_REGISTERS*/};

		static fncMsg fnc_table[sizeof(proto_idx)][sizeof(fnc_idx)] = { {    //
				ASCII_msgReadRegisters, ASCII_msgReadRegisters, ASCII_msgReadRegisters, ASCII_msgReadRegisters, ASCII_msgWriteSingleCoil,
						ASCII_msgWriteSingleRegister, ASCII_msgWriteMultipleCoil, ASCII_msgWriteMultipleRegister }, {    //
				RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msg_WriteSingleRegister,
				RTU_msg_WriteSingleRegister, RTU_msg_WriteMultipleRegisters, RTU_msg_WriteMultipleRegisters }, {    //
				TCP_msgReadRegisters, TCP_msgReadRegisters, TCP_msgReadRegisters, TCP_msgReadRegisters, TCP_msg_WriteSingleRegister,
				TCP_msg_WriteSingleRegister, TCP_msg_WriteMultipleRegisters, TCP_msg_WriteMultipleRegisters }, {    //
				RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msgReadRegisters, RTU_msg_WriteSingleRegister,
				RTU_msg_WriteSingleRegister, RTU_msg_WriteMultipleRegisters, RTU_msg_WriteMultipleRegisters } };

		for (unsigned char i = 0; i < sizeof(proto_idx); ++i)
		{
			if (proto_idx[i] == cmd.protocol)
			{
				for (unsigned char j = 0; j < sizeof(fnc_idx); ++j)
				{
					if (cmd.function == fnc_idx[j])
						return fnc_table[i][j](cmd, blck);
				}
			}
		}
		throw error_api(ERROR_INFO(),api_error::get_no_implement());
	}
	// protocol must be specified inside cmd structure
	static void MessageToCommand(const Buffer &blck, ModbusCmd& cmd);

	/*
	 * Base on modbus function set the next parameters to the correct value
	 * data_size_bits
	 * base
	 * count only if byte_count !=0 avoiding modification when creating a modbus message
	 */
	static void getFunctionParameters(ModbusCmd& cmd)
	{
		struct
		{
			ModbusCmd::ModBusFunctions fnc;
			unsigned short base;
			unsigned char data_size_bits;
		} info[] = { { ModbusCmd::MODBUS_FC_READ_COILS, 0, 1 }, { ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS, 1, 1 }, {
				ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS, 4, 16 }, { ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS, 3, 16 }, {
				ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL, 0, 1 }, { ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER, 3, 16 }, {
				ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS, 0, 1 }, { ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS, 3, 16 } };
		for (uint8_t i = 0; i < sizeof(info) / sizeof(*info); ++i)
		{
			if (info[i].fnc == cmd.function)
			{
				cmd.base = info[i].base;
				cmd.data_size_bits = info[i].data_size_bits;
				if (cmd.byte_count)
				{
					if (cmd.data_size_bits == 1)
						cmd.count = cmd.byte_count * 8;
					else if (cmd.data_size_bits == 16)
						cmd.count = cmd.byte_count / 2;
				}
				return;
			}
		}
		cmd.base = 0;
		cmd.data_size_bits = 0;
		cmd.count = 0;
	}

};

#endif /* MODBUSPROTOCOL_H_ */
