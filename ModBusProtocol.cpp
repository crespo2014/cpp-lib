/*
 * ModBusProtocol.cpp
 *
 *  Created on: 20 Feb 2014
 *      Author: lester
 */

#include "ModBusProtocol.h"

void ModBusProtocol::ASCII_msg_WriteSingleRegister(const ModbusCmd& cmd,
		Buffer &blck, unsigned char data_size_bits)
{
	if (blck.getWSize() < 1 + 2 * (1 + 1 + 1) + 4 * (1 + 1) + 2)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory()); // (:) (slave fnc lrc) (start,value) (CR LF)
	unsigned char* cptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(1 + 2 * (1 + 1 + 1) + 4 * (1 + 1) + 2);

	unsigned char lrc = 0 - cmd.slave - cmd.function
			- ((cmd.start_address >> 8) & 0xFF) - (cmd.start_address & 0xFF);

	cptr += sprintf((char*) cptr, ":%.2X%.2X%.4X", cmd.slave, cmd.function,
			cmd.start_address);

	if (data_size_bits == 1)
	{
		if (cmd.u16data[0])
		{
			writeHex(0xFF, 4, cptr);
			lrc -= 0xFF;
		}
		else
			writeHex(0x00, 4, cptr);
	}
	else
	{
		lrc -= (cmd.u16data[0] / 256);
		lrc -= (cmd.u16data[0] & 0xFF);
		writeHex(cmd.u16data[0], 4, cptr);
	}
	cptr += 4;
	sprintf((char*) cptr, "%.2X\r\n", lrc);
}

void ModBusProtocol::ASCII_msg_WriteMultipleRegisters(const ModbusCmd& cmd,
		Buffer &blck, unsigned char data_size_bits)
{
	unsigned char byte_count = (cmd.count * data_size_bits + 7) / 8;
	if (blck.getWSize()
			< 1 + 2 * (1 + 1 + 1 + 1) + 4 * (1 + 1) + 2 * byte_count + 2) // (:) (slave fnc byte_count lrc) (start,count) (data) (CR LF)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());

	unsigned char* cptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(1 + 2 * (1 + 1 + 1 + 1) + 4 * (1 + 1) + 2 * byte_count + 2);

	// byte count = count
	unsigned char lrc = 0 - cmd.slave - cmd.function
			- ((cmd.start_address >> 8) & 0xFF) - (cmd.start_address & 0xFF)
			- ((cmd.count >> 8) & 0xFF) - (cmd.count & 0xFF) - byte_count;

	cptr += sprintf((char*) cptr, ":%.2X%.2X%.4X%.4X%.2X", cmd.slave,
			cmd.function, cmd.start_address, cmd.count, byte_count);

	ASCIIPackRegisters(cmd.u16data, cmd.count, data_size_bits, cptr, lrc);

	cptr += byte_count * 2;

	cptr += sprintf((char*) cptr, "%.2X\r\n", lrc);
}

void ModBusProtocol::ASCII_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck)
{
	unsigned char lrc = 0 - cmd.slave - cmd.function
			- ((cmd.start_address >> 8) & 0xFF) - (cmd.start_address & 0xFF)
			- ((cmd.count >> 8) & 0xFF) - (cmd.count & 0xFF);
	int ir;
	ir = snprintf(reinterpret_cast<char*>(blck.getW()), blck.getWSize(),
			":%.2X%.2X%.4X%.4X%.2X\r\n", cmd.slave, cmd.function,
			cmd.start_address, cmd.count, lrc);
	if ((ir < 0) || (ir >= blck.getWSize()))
	{
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	}
	blck.updateW(ir);
}
void ModBusProtocol::ASCII_getData(io::Buffer &blck, ModbusCmd& cmd,
		api_error& e)
{
	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
	unsigned char uc;
	unsigned char lrc = 0;
	unsigned char *buffer = msg;
	if (blck.getRSize() < 9)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	if (*buffer++ != ':')
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	get8Hex(buffer, cmd.slave);
	get8Hex(buffer, uc);

	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(uc);

	lrc = lrc - cmd.slave - cmd.function;
	if (cmd.function >= 0x80)
	{
		get8Hex(buffer, cmd.exception);
		lrc = lrc - cmd.exception;
	}
	else
	{
		// read byte count for function returning it
		if ((cmd.function == ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS)
				|| (cmd.function == ModbusCmd::MODBUS_FC_READ_COILS)
				|| (cmd.function == ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS)
				|| (cmd.function == ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS))
		{
			get8Hex(buffer, cmd.byte_count);
			lrc = lrc - cmd.byte_count;
			// validate message size
			cmd.desire_size = 9 + cmd.byte_count;
			if (blck.getRSize() < cmd.desire_size)
				return e.seteof();
		}
	}
	getFunctionParameters(cmd);
	switch (cmd.function)
	{
	case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
	case ModbusCmd::MODBUS_FC_READ_COILS:
	case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
	case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		ASCIIUnPackRegisters(cmd.u16data, cmd.count, buffer, cmd.data_size_bits,
				lrc);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		cmd.desire_size = 15;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		get16Hex(buffer, cmd.start_address);
		lrc = lrc - cmd.start_address / 256 - cmd.start_address % 0xFF;
		get16Hex(buffer, cmd.count);
		lrc = lrc - cmd.count / 256 - cmd.count % 0xFF;
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
		cmd.desire_size = 15;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		get16Hex(buffer, cmd.start_address);
		lrc = lrc - cmd.start_address / 256 - cmd.start_address % 0xFF;
		get16Hex(buffer, cmd.count);
		lrc = lrc - cmd.count / 256 - cmd.count % 0xFF;
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		cmd.desire_size = 15;
		cmd.count = 1;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		get16Hex(buffer, cmd.start_address);
		lrc = lrc - cmd.start_address / 256 - cmd.start_address % 0xFF;
		ASCIIUnPackRegisters(cmd.u16data, cmd.count, buffer, 1, lrc);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
		cmd.desire_size = 15;
		cmd.count = 1;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		get16Hex(buffer, cmd.start_address);
		lrc = lrc - cmd.start_address / 256 - cmd.start_address % 0xFF;
		ASCIIUnPackRegisters(cmd.u16data, cmd.count, buffer, 16, lrc);
		break;
	case ModbusCmd::MODBUS_FC_NONE:
	case ModbusCmd::MODBUS_FC_READ_EXCEPTION_STATUS:
	case ModbusCmd::MODBUS_FC_REPORT_SLAVE_ID:
	case ModbusCmd::MODBUS_FC_WRITE_AND_READ_REGISTERS:
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	}
	get8Hex(buffer, uc);
	if (lrc != uc)
		throw error_api(ERROR_INFO(), api_error::get_protocol());
}

/* create a ReadRegisters message */
void ModBusProtocol::RTU_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck)
{
	if (blck.getWSize() < 8)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(8);
	if (cmd.slave > 247)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	ptr[0] = cmd.slave;
	ptr[1] = cmd.function;
	ptr[2] = cmd.start_address / 256;
	ptr[3] = cmd.start_address & 0xFF;
	ptr[4] = cmd.count / 256;
	ptr[5] = cmd.count & 0xFF;
	SetCRC16(ptr, 8);
}

void ModBusProtocol::RTU_msg_WriteSingleRegister(const ModbusCmd& cmd,
		Buffer &blck)
{
	if (cmd.slave > 247)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	if (blck.getWSize() < 8)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(8);

	ptr[0] = cmd.slave;
	ptr[1] = cmd.function;
	ptr[2] = cmd.start_address / 256;
	ptr[3] = cmd.start_address & 0xFF;

	if (cmd.data_size_bits == 1)
	{
		if (*cmd.u16data)
		{
			ptr[4] = 0xFF;
		}
		else
		{
			ptr[4] = 0;
		}
		ptr[5] = 0;

	}
	else
	{
		ptr[4] = (*cmd.u16data) / 256;
		ptr[5] = (*cmd.u16data) & 0xFF;
	}
	SetCRC16(ptr, 8);
}

void ModBusProtocol::RTU_msg_WriteMultipleRegisters(const ModbusCmd& cmd,
		Buffer &blck)
{
	if (cmd.slave > 246)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());

	unsigned char byte_count = (cmd.count * cmd.data_size_bits + 7) / 8;

	if (blck.getWSize() < 9 + byte_count)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());

	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(9 + byte_count);

	ptr[0] = cmd.slave;
	ptr[1] = cmd.function;
	ptr[2] = cmd.start_address / 256;
	ptr[3] = cmd.start_address & 0xFF;
	ptr[4] = cmd.count / 256;
	ptr[5] = cmd.count & 0xFF;
	ptr[6] = byte_count;
	PackRegisters(cmd.u16data, cmd.count, cmd.data_size_bits,
			(unsigned char*) &ptr[7]);

	SetCRC16(ptr, 9 + byte_count);
}

void ModBusProtocol::RTU_getData(Buffer &blck, ModbusCmd& cmd, api_error& e)
{

	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
	if (blck.getRSize() < 5)
		return e.seteof();
	cmd.slave = msg[0];
	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(msg[1]);
	if (cmd.function >= 0x80)
		cmd.exception = msg[2];
	cmd.byte_count = msg[2];

	getFunctionParameters(cmd);
	switch (cmd.function)
	{
	case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
	case ModbusCmd::MODBUS_FC_READ_COILS:
	case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
	case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		cmd.desire_size = 3 + cmd.byte_count + 2;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[3],
				cmd.data_size_bits);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		cmd.count = msg[4] * 0x100 + msg[5];
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
		cmd.count = msg[4] * 0x100 + msg[5];
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
		cmd.count = 1;
		cmd.byte_count = 2;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();

		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[4],
				cmd.data_size_bits);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		cmd.count = 1;
		cmd.byte_count = 1;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();

		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[4],
				cmd.data_size_bits);
		break;
	default:
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	}
	CheckCRC16(msg, cmd.desire_size);
}

void ModBusProtocol::TCP_getData(Buffer &blck, ModbusCmd& cmd, api_error& e)
{
	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
// check message size at less 6 bytes
	if (blck.getRSize() < MODBUS_TCP_PRESET_REQ_LENGTH)
		return e.seteof();

// check transation id
	cmd.transation_id = msg[0] * 0x100 + msg[1];
	if (msg[2] != 0 || msg[3] != 0)
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	cmd.desire_size = msg[4] * 0x100 + msg[5] + MODBUS_TCP_PRESET_REQ_LENGTH;
	if (blck.getRSize() < cmd.desire_size)
		return e.seteof();

	/*
	 CRC on rtu does not allow to do this
	 Buffer Buffer(blck);
	 Buffer.updateR(MODBUS_TCP_PRESET_REQ_LENGTH);
	 return RTU_getData(Buffer,cmd);
	 */
//blck.update
// adjust message begin to make similar to rtu
	msg += MODBUS_TCP_PRESET_REQ_LENGTH;
	cmd.slave = msg[0];
	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(msg[1]);
	if (cmd.function >= 0x80)
		cmd.exception = msg[2];

	cmd.byte_count = msg[2];
	getFunctionParameters(cmd);
	switch (cmd.function)
	{
	case ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS:
	case ModbusCmd::MODBUS_FC_READ_COILS:
	case ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS:
	case ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS:
		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[3],
				cmd.data_size_bits);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS:
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
		break;
	case ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS:
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER:
		cmd.count = 1;
		cmd.byte_count = 2;
		cmd.start_address = msg[2] * 0x100 + msg[3];

		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[4],
				cmd.data_size_bits);
		break;
	case ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL:
		cmd.count = 1;
		cmd.byte_count = 1;
		cmd.start_address = msg[2] * 0x100 + msg[3];

		UnPackRegisters(cmd.u16data, cmd.byte_count, &msg[4],
				cmd.data_size_bits);
		break;
	default:
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	}
}

void ModBusProtocol::TCP_msg_WriteSingleRegister(const ModbusCmd& cmd,
		Buffer &blck)
{
	if (cmd.slave > 246)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	if (blck.getWSize() < 13)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(12);

	cmd.transation_id = MonotonicTime().getMs();
	ptr[0] = cmd.transation_id >> 8;
	ptr[1] = cmd.transation_id & 0xFF;
	ptr[2] = 0x00;
	ptr[3] = 0x00;
	ptr[4] = (12 - MODBUS_TCP_PRESET_REQ_LENGTH) >> 8;
	ptr[5] = (12 - MODBUS_TCP_PRESET_REQ_LENGTH) & 0xFF; // header length is substrate from total
	ptr[6] = cmd.slave;
	ptr[7] = cmd.function;
	ptr[8] = cmd.start_address / 256;
	ptr[9] = cmd.start_address & 0xFF;

	if (cmd.data_size_bits == 1)
	{
		if (*cmd.u16data)
		{
			ptr[10] = 0xFF;
		}
		else
		{
			ptr[10] = 0;
		}
		ptr[11] = 0;

	}
	else
	{
		ptr[10] = (*cmd.u16data) / 256;
		ptr[11] = (*cmd.u16data) & 0xFF;
	}
}

void ModBusProtocol::TCP_msg_WriteMultipleRegisters(const ModbusCmd& cmd,
		Buffer &blck)
{
	unsigned char byte_count = (cmd.count * cmd.data_size_bits + 7) / 8;

	if (cmd.slave > 246)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	if (blck.getWSize() < (MODBUS_TCP_PRESET_REQ_LENGTH + 7 + byte_count))
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());

	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(MODBUS_TCP_PRESET_REQ_LENGTH + 7 + byte_count);

	cmd.transation_id = MonotonicTime().getMs();
	ptr[0] = cmd.transation_id >> 8;
	ptr[1] = cmd.transation_id & 0xFF;
	ptr[2] = 0x00;
	ptr[3] = 0x00;
	ptr[4] = (7 + byte_count) >> 8;
	ptr[5] = (7 + byte_count) & 0xFF;	// header length is substrate from total
	ptr[6] = cmd.slave;
	ptr[7] = cmd.function;
	ptr[8] = cmd.start_address / 256;
	ptr[9] = cmd.start_address & 0xFF;
	ptr[10] = cmd.count / 256;
	ptr[11] = cmd.count & 0xFF;
	ptr[12] = byte_count;		// byte count

	PackRegisters(cmd.u16data, cmd.count, cmd.data_size_bits, ptr + 13);
}

void ModBusProtocol::TCP_msgReadRegisters(const ModbusCmd& cmd, Buffer &blck)
{
	if (cmd.slave > 246)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	if (blck.getWSize() < 12)
		throw error_api(ERROR_INFO(), api_error::get_not_enough_memory());
	unsigned char* ptr = reinterpret_cast<unsigned char*>(blck.getW());
	blck.updateW(12);

	cmd.transation_id = MonotonicTime().getMs();
	ptr[0] = cmd.transation_id >> 8;
	ptr[1] = cmd.transation_id & 0xFF;
	ptr[2] = 0x00;
	ptr[3] = 0x00;
	ptr[4] = (12 - MODBUS_TCP_PRESET_REQ_LENGTH) >> 8;
	ptr[5] = (12 - MODBUS_TCP_PRESET_REQ_LENGTH) & 0xFF;// header length is substrate from total
	ptr[6] = cmd.slave;
	ptr[7] = cmd.function;
	ptr[8] = cmd.start_address / 256;
	ptr[9] = cmd.start_address & 0xFF;
	ptr[10] = cmd.count / 256;
	ptr[11] = cmd.count & 0xFF;
}

/*
 * Interpret message and obtain command information
 */
void ModBusProtocol::MessageToCommand(const Buffer& blck, ModbusCmd& cmd)
{
	throw error_api(ERROR_INFO(), api_error::get_no_implement());
}
