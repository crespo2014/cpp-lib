/*
 * ModbusSlave.cpp
 *
 *  Created on: 13 Mar 2014
 *      Author: lester
 */

#include "ModbusSlave.h"

void ModbusSlaveProtocol::getData(const Buffer& blck, ModbusCmd& cmd,
		api_error& e)
{
	switch (cmd.protocol)
	{
	case ModbusCmd::MODBUS_PROTO_ASCII:
		return ASCII_getData(blck, cmd, e);
	case ModbusCmd::MODBUS_PROTO_RTU:
	case ModbusCmd::MODBUS_PROTO_RTU_OVER_TCP:
		return RTU_getData(blck, cmd, e);
	case ModbusCmd::MODBUS_PROTO_TCP:
		return TCP_getData(blck, cmd, e);
	case ModbusCmd::MODBUS_PROTO_ELAN:
		return ELAM_getData(blck, cmd, e);
	default:
		break;
	}
	throw error_api(ERROR_INFO(), api_error::get_no_implement());
}

void ModbusSlaveProtocol::ASCII_getData(const Buffer& blck, ModbusCmd& cmd,
		api_error& e)
{
	throw error_api(ERROR_INFO(), api_error::get_protocol());
}

/*
 * EOF return is not a exception
 */
void ModbusSlaveProtocol::RTU_getData(const Buffer& blck, ModbusCmd& cmd,
		api_error& e)
{
	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
	if (blck.getRSize() < 5)
		return e.seteof();
	cmd.slave = msg[0];
	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(msg[1]);

	getFunctionParameters(cmd);

	if ((cmd.function == ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS))
	{
		if (blck.getRSize() < 9)
			return e.seteof();
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
		cmd.byte_count = msg[6];
		cmd.vdata = &msg[7];
		cmd.desire_size = 9 + cmd.byte_count;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		cmd.count = 1;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.vdata = &msg[4];
	}
	CheckCRC16(msg, cmd.desire_size);
}

void ModbusSlaveProtocol::TCP_getData(const Buffer& blck, ModbusCmd& cmd,
		api_error& e)
{
	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
	// check message size at less 6 bytes
	if (blck.getRSize() < MODBUS_TCP_PRESET_REQ_LENGTH)
		return e.seteof();;

	// check transation id
	cmd.transation_id = msg[0] * 0x100 + msg[1];
	if (msg[2] != 0 || msg[3] != 0)
		throw error_api(ERROR_INFO(), api_error::get_protocol());
	cmd.desire_size = msg[4] * 0x100 + msg[5] + MODBUS_TCP_PRESET_REQ_LENGTH;
	if (blck.getRSize() < cmd.desire_size)
		return e.seteof();

	//blck.update
	// adjust message begin to make similar to rtu
	msg += MODBUS_TCP_PRESET_REQ_LENGTH;
	cmd.slave = msg[0];
	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(msg[1]);

	getFunctionParameters(cmd);

	if ((cmd.function == ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS))
	{
		if (blck.getRSize() < 9)
			return e.seteof();;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
		cmd.byte_count = msg[6];
		cmd.vdata = &msg[7];
		cmd.desire_size = 9 + cmd.byte_count;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();;
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();;
		cmd.count = 1;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.vdata = &msg[4];
	}
}

void ModbusSlaveProtocol::ELAM_getData(const Buffer& blck, ModbusCmd& cmd,
		api_error& e)
{
	unsigned char* msg = reinterpret_cast<unsigned char*>(blck.getR());
	if (blck.getRSize() < 5)
		return e.seteof();;
	cmd.slave = msg[0];
	if ((cmd.slave & 0xF8) == 0xF8)	// slave address > 248 are elam extended address
	{
		cmd.slave = msg[0] * 0x100 + msg[1];
		msg++;
	}
	cmd.function = static_cast<ModbusCmd::ModBusFunctions>(msg[1]);

	getFunctionParameters(cmd);

	if ((cmd.function == ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS))
	{
		if (blck.getRSize() < 9)
			return e.seteof();;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.count = msg[4] * 0x100 + msg[5];
		cmd.byte_count = msg[6];
		cmd.vdata = &msg[7];
		cmd.desire_size = 9 + cmd.byte_count;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();;
	}
	else if ((cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER)
			|| (cmd.function == ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL))
	{
		cmd.desire_size = 8;
		if (blck.getRSize() < cmd.desire_size)
			return e.seteof();;
		cmd.count = 1;
		cmd.start_address = msg[2] * 0x100 + msg[3];
		cmd.vdata = &msg[4];
	}
	CheckCRC16(msg, cmd.desire_size);
}

void ModbusSlaveProtocol::getReply(const ModbusCmd& cmd, Buffer& blck)
{
	switch (cmd.protocol)
	{
	case ModbusCmd::MODBUS_PROTO_ASCII:
		//return ASCII_getData(blck, cmd);
	case ModbusCmd::MODBUS_PROTO_RTU:
	case ModbusCmd::MODBUS_PROTO_RTU_OVER_TCP:
		return RTU_ReplyData(cmd, blck);
	case ModbusCmd::MODBUS_PROTO_TCP:
		return TCP_ReplyData(cmd, blck);
	case ModbusCmd::MODBUS_PROTO_ELAN:
		//return ELAM_getData(blck, cmd);
	default:
		break;
	}
	throw error_api(ERROR_INFO(), api_error::get_no_implement());
}
