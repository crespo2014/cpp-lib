/*
 * ModbusCmd.h
 *
 *  Created on: 20 Feb 2014
 *      Author: lester
 */

#ifndef MODBUSCMD_H_
#define MODBUSCMD_H_

#include "stdint.h"
#include "log.h"

/* Protocol exceptions */
enum
{
	MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,
	MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,
	MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,
	MODBUS_EXCEPTION_ACKNOWLEDGE,
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,
	MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,
	MODBUS_EXCEPTION_MEMORY_PARITY,
	MODBUS_EXCEPTION_NOT_DEFINED,
	MODBUS_EXCEPTION_GATEWAY_PATH,
	MODBUS_EXCEPTION_GATEWAY_TARGET,
	MODBUS_EXCEPTION_MAX
};

class ModbusCmd
{
public:
	typedef enum
	{
		MODBUS_PROTO_NONE,    //
		MODBUS_PROTO_ASCII,    //
		MODBUS_PROTO_RTU,
		MODBUS_PROTO_TCP,
		MODBUS_PROTO_RTU_OVER_TCP,
		MODBUS_PROTO_ELAN
	} ModbusProtocol;

	typedef enum
	{
		MODBUS_FC_NONE = 0x00,
		MODBUS_FC_READ_COILS = 0x01,
		MODBUS_FC_READ_DISCRETE_INPUTS = 0x02,
		MODBUS_FC_READ_HOLDING_REGISTERS = 0x03,
		MODBUS_FC_READ_INPUT_REGISTERS = 0x04,
		MODBUS_FC_WRITE_SINGLE_COIL = 0x05,
		MODBUS_FC_WRITE_SINGLE_REGISTER = 0x06,
		MODBUS_FC_READ_EXCEPTION_STATUS = 0x07,
		MODBUS_FC_WRITE_MULTIPLE_COILS = 0x0F,
		MODBUS_FC_WRITE_MULTIPLE_REGISTERS = 0x10,
		MODBUS_FC_REPORT_SLAVE_ID = 0x11,
		MODBUS_FC_WRITE_AND_READ_REGISTERS = 0x17,
	} ModBusFunctions;

	ModbusCmd(ModbusProtocol protocol, unsigned short *data, unsigned short max) :
			protocol(protocol), desire_size(0), slave(0), function(MODBUS_FC_NONE), exception(0), byte_count(0), start_address(0), count(0), vdata(
					data),  data_max(data_max), transation_id(0), base(0),data_size_bits(0)
	{

	}
	ModbusCmd() :
			protocol(MODBUS_PROTO_NONE), desire_size(0), slave(0), function(MODBUS_FC_NONE), exception(0), byte_count(0), start_address(0), count(0), vdata(
					0),  data_max(0), transation_id(0), base(0),data_size_bits(0)
	{
	}

	ModbusProtocol protocol;
	unsigned char desire_size;		// desire or expected size of this command
	unsigned short slave;			// 0 .. 127 or extended for ELAM
	ModBusFunctions function;		// function ...
	unsigned char exception;		// if there is any error
	unsigned char byte_count;		// response byte count or exception code
	unsigned short start_address;   // start address without base
	unsigned short count;			// count of data contained in vdata, on slave mode it is obtained from byte count
	union
	{
		/*
		 	 read or write data here, in slave mode point to started of data in input buffer
		 	 master mode data_max will be use in write mode, count will be use in read mode
		 */
		//void *data;			// TODO Deprecate data to send or space to receive data
		void *vdata;		// data void pointer
		uint8_t	*u8data;
		uint16_t * u16data;
	};
	//unsigned short data_count;		// how many data is on data buffer read from modbus response
	unsigned short data_max;		// max space for store data on data pointer
	mutable unsigned short transation_id;    // transation_id use by modbus tcp
	unsigned short base;			// base address can be 0 1 3 or 4
	unsigned char data_size_bits;

	/*
	 * get absolute address
	 * modbus protocol use range address starting from 0 -
	 * devices starting from 1
	 * this function return absolute address of device
	 */
	uint16_t absoluteAddress()
	{
		return (base * 10000 + start_address + 1);
	}
	void trace()
	{
		// TODO use stream operator agains buffer
#ifdef _DEBUG
		log_d("Protocol %d",protocol);
		log_d("Slave %d",slave);
		log_d("Function %d",function);
		log_d("Byte Count %d",byte_count);
		log_d("Base %d",base);
		log_d("Address %d",start_address);
		log_d("Bits %d",data_size_bits);
		log_d("Count %d",count);
#endif
	}
};

#endif /* MODBUSCMD_H_ */
