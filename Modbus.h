/*
 * Modbus.h
 *
 *  Created on: 17 Oct 2013
 *      Author: lester
 */

#ifndef MODBUS_CLASS_
#define MODBUS_CLASS_

#include "ModbusCmd.h"
#include "string.h"

/**
 * UTILS FUNCTIONS
 **/

#define MODBUS_GET_HIGH_BYTE(data) (((data) >> 8) & 0xFF)
#define MODBUS_GET_LOW_BYTE(data) ((data) & 0xFF)
#define MODBUS_GET_INT32_FROM_INT16(tab_int16, index) ((tab_int16[(index)] << 16) + tab_int16[(index) + 1])
#define MODBUS_GET_INT16_FROM_INT8(tab_int8, index) ((tab_int8[(index)] << 8) + tab_int8[(index) + 1])
#define MODBUS_SET_INT16_TO_INT8(tab_int8, index, value) \
    do { \
        tab_int8[(index)] = (value) >> 8;  \
        tab_int8[(index) + 1] = (value) & 0xFF; \
    } while (0)

struct _modbus_msg
{
	_modbus_msg() :
			msg(0), max_size(0), size(0)
	{
	}
	_modbus_msg(void* dt, unsigned short max_size) :
			msg((unsigned char*) dt), max_size(max_size), size(0)
	{
	}

	unsigned char* msg;
	unsigned short max_size;
	unsigned short size;
};

#define MODBUS_MAX_READ_REGISTERS          125
#define MODBUS_MAX_WRITE_REGISTERS         123
#define MODBUS_MAX_RW_WRITE_REGISTERS      121

#define MODBUS_MAX_MESSAGE_SIZE     		260
#define MODBUS_TCP_PRESET_REQ_LENGTH		6

class Modbus
{

public:
	static void get8Hex(unsigned char* &str, unsigned char &val);
	static void get8Hex(unsigned char* &str, unsigned short &val)
	{
		unsigned char uc;
		get8Hex(str, uc);
		val = uc;
	}
	//
	static void get16Hex(unsigned char* &str, unsigned short &val);
	//
	static void readHex(unsigned char* &str, unsigned char maxchar, unsigned int &val);
	//
	static void ASCIIUnPackRegisters(unsigned char* &in, unsigned char size_bits, struct _modbus_cmd &cmd, unsigned char &lrc);
	//
	static void writeHex(unsigned short val, unsigned char maxchar, unsigned char* str);
	//
	static void PackRegisters(unsigned short* data, unsigned char count, unsigned char size_bits, unsigned char* out);
	static void ASCIIPackRegisters(unsigned short* data, unsigned char count, unsigned char size_bits, unsigned char* out, unsigned char &lrc);
	//
	static void UnPackRegisters(unsigned short* data, unsigned char byte_count, unsigned char *in, unsigned char size_bits);
	static void ASCIIUnPackRegisters(unsigned short* data, unsigned char byte_count, unsigned char* &in, unsigned char size_bits,
			unsigned char &lrc);

	/*
	 * Check crc, pass message size including crc data
	 * last two bytes of message will be validate again calculate crc
	 */
	static void CheckCRC16(unsigned char* msg, unsigned short len);
	/*
	 * pass full length of the message to this function
	 * last two bytes will be use to store CRC
	 */
	static void SetCRC16(unsigned char* msg, unsigned short len);

	/*
	 * Fill fields, data size bits and base address using function number
	 */
	static void getFunctionParameters(ModbusCmd & cmd);

	/*
	 * Unpack data store as 8 bits per bit and convert to a bit per byte with values 0xFF or 0x00
	 */
	static void unpack_1Bit_toByte(uint8_t* src, uint16_t count, uint8_t *dest)
	{
		uint16_t bit = 1;
		for (uint16_t i = 0; i < count; ++i)
		{
			if (bit == 256)
			{
				++src;
				bit = 1;
			}
			*dest = (*src & bit) ? 0xFF : 0x00;
			++dest;
			bit <<= 1;
		}
	}
	/*
	 * Unpack data from modbus command
	 * to 8bits if size is 1bit
	 * to 16Bits if size is 16bits
	 */
	static void unpack(const ModbusCmd & cmd, uint8_t *dest)
	{
		uint8_t* src = cmd.u8data;
		if (cmd.data_size_bits == 1)
		{
			uint16_t bit = 1;
			for (uint16_t i = 0; i < cmd.count; ++i)
			{
				if (bit == 256)
				{
					++src;
					bit = 1;
				}
				*dest = (*src & bit) ? 0xFF : 0x00;
				++dest;
				bit <<= 1;
			}
		} else if (cmd.data_size_bits == 16)
		{
			memcpy(dest, cmd.u8data, cmd.count * 2);
		}

	}

};

#endif /* MODBUS_CLASS_ */
