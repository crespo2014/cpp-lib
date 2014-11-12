/*
 * Modbus.cpp
 *
 *  Created on: 17 Oct 2013
 *      Author: lester
 */

#include "Modbus.h"
#include "math.h"
#include "os.h"

/* Table of CRC values for high-order byte */
static const unsigned char table_crc_hi[] = { 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
		0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
		0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
		0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
		0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80,
		0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
		0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
		0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
		0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80,
		0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40 };

/* Table of CRC values for low-order byte */
static const unsigned char table_crc_lo[] = { 0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC,
		0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
		0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0,
		0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F,
		0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D,
		0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
		0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B,
		0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74,
		0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96,
		0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
		0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46,
		0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40 };

void Modbus::get8Hex(unsigned char* &str, unsigned char &val)
{
	val = 0;
	for (unsigned char i = 0; i < 2; i++)
	{
		if ((*str < '0') || (*str > 'F') || ((*str > '9') && (*str < 'A')))
			throw error_api(ERROR_INFO(),api_error::get_invalid_char());
		val = (val * 16) + ((*str >= 'A') ? (*str - 'A' + 10) : (*str - '0'));
		str++;
	}
}
void Modbus::get16Hex(unsigned char* &str, unsigned short &val)
{
	val = 0;
	for (unsigned char i = 0; i < 4; i++)
	{
		if ((*str < '0') || (*str > 'F') || ((*str > '9') && (*str < 'A'))) throw error_api(ERROR_INFO(),api_error::get_invalid_char());
		val = (val * 16) + ((*str >= 'A') ? (*str - 'A' + 10) : (*str - '0'));
		str++;
	}
}

void Modbus::readHex(unsigned char* &str, unsigned char maxchar, unsigned int &val)
{
	val = 0;
	while (maxchar && *str)
	{
		if ((*str < '0') || (*str > 'F')) throw error_api(ERROR_INFO(),api_error::get_wrong_param());
		if ((*str > '9') && (*str < 'A'))  throw error_api(ERROR_INFO(),api_error::get_wrong_param());
		val = (val * 16) + ((*str >= 'A') ? (*str - 'A' + 10) : (*str - '0'));
		maxchar--;
		str++;
	}
	if (maxchar != 0)  throw error_api(ERROR_INFO(),api_error::get_wrong_param());

}

void Modbus::writeHex(unsigned short val, unsigned char maxchar, unsigned char* str)
{
	while (maxchar)
	{
		unsigned char d = (val % 16);
		val /= 16;
		if (d > 9)
			d += ('A' - 10);
		else
			d += '0';
		maxchar--;
		str[maxchar] = d;
	}
}
/*
 * use byte count to known howm any data need to be read
 */
void Modbus::UnPackRegisters(unsigned short* data, unsigned char byte_count, unsigned char *in, unsigned char size_bits)
{
	unsigned short data_pos = 0;
	if (size_bits == 1)
	{
		for (unsigned i = 0; i < byte_count; i++)
		{
			for (unsigned char bit = 1; bit != 0; bit <<= 1)
			{
				data[data_pos] = (in[i] & bit) ? 1 : 0;
				++data_pos;
			}
		}
	} else
	{
		for (unsigned i = 0; i < byte_count; i += 2)
		{
			data[data_pos] = in[i] * 0x100 + in[i + 1];
			++data_pos;
		}
	}
}

void Modbus::ASCIIUnPackRegisters(unsigned short* data, unsigned char byte_count, unsigned char* &in, unsigned char size_bits,
		unsigned char &lrc)
{
	if (size_bits == 1)
	{
		unsigned char bit_pos = 1;
		for (unsigned i = 0; i < byte_count; i++)
		{
			unsigned char val;
			if (bit_pos == 1)
			{
				get8Hex(in, val);
				lrc -= val;
			}
			data[i] = (val & bit_pos) ? 1 : 0;
			if (bit_pos == 128)
			{
				bit_pos = 1;
			} else
				bit_pos *= 2;
		}
	} else
	{
		for (unsigned i = 0; i < byte_count; i++)
		{
			unsigned short val;
			get16Hex(in, val);
			data[i] = val;
			lrc -= (val / 256);
			lrc -= (val & 0xFF);
		}
	}
}

float floatfromu16(unsigned short hi, unsigned short low)
{
	float fp, f;
	unsigned int val = (hi << 16) + low;
	unsigned int s = 0;
	int e;
	s = val >> 31;/*sign bit*/
	e = (val >> 23 & 0xff);/*exponent*/
	f = val & 0x7FFFFF;/*fraction*/
	e -= 127;
	fp = 1;

	for (int i = 23; i; i--)
	{
		f /= 2.0f;
	}

	f += 1;

	for (; e;)
	{
		if (e < 0)
		{
			f /= 2;
			e++;
		} else
		{
			f *= 2;
			e--;
		}
	}
	fp = (s ? -1 : 1) * f;
	return fp;
}

void floatToShort(float f, unsigned short &hi, unsigned short &low)
{
	int i;
	unsigned char s = 0, e = 0;
	unsigned char find = 0, bit_value = 0;
	unsigned long m = 0;
	double value, temp;
	if (f < 0)
	{
		s = 1;
		f *= -1;
	}
	i = -127;
	while ((f / pow(2, i)) > 1)
	{
		i++;
		if (i > 128) return;
	}
	if (i <= -127) return;
	e = (unsigned char) (i - 1 + 127);
	value = f / pow(2, (i - 1));
	value -= 1;
	for (i = -1; i > -24; i--)
	{
		bit_value = 0;
		if (find == 0)
		{
			temp = pow(2, i);
			if (value == temp)
			{
				find = 1;
				bit_value = 1;
			} else if (value > temp)
			{
				value -= temp;
				bit_value = 1;
			} else
				bit_value = 0;
		}
		m |= bit_value;
		if (i > -23) m = m << 1;
	}
	//process data

	unsigned int val = (s << 31) + (e << 23) + m;
	hi = val >> 16;
	low = val & 0xFFFF;
	/*
	 (unsigned char) ((s << 7) + (e >> 1));
	 *data1 = (unsigned char) (((e & 0x01) << 7) + ((m & 0xFF0000) >> 16));
	 *data2 = (unsigned char) ((m & 0xFF00) >> 8);
	 *data3 = (unsigned char) (m & 0xFF);
	 *data3 */

}

void Modbus::PackRegisters(unsigned short* data, unsigned char count, unsigned char size_bits, unsigned char* out)
{
	if (size_bits == 16)
	{
		for (int i = 0; i < count; ++i)
		{
			out[i * 2] = data[i] / 256;
			out[i * 2 + 1] = data[i] & 0xFF;
		}
	} else if (size_bits == 1)
	{
		unsigned char bit_pos = 1;
		unsigned char data_pos = 0;
		for (int i = 0; i < count; i++)
		{
			if (bit_pos == 1) out[data_pos] = 0;
			if (data[i]) out[data_pos] |= bit_pos;
			if (bit_pos == 128)
			{
				bit_pos = 1;
				data_pos++;
			} else
				bit_pos *= 2;
		}
	}
}
void Modbus::ASCIIPackRegisters(unsigned short* data, unsigned char count, unsigned char size_bits, unsigned char* out, unsigned char &lrc)
{
	if (size_bits == 16)
	{
		for (int i = 0; i < count; i++)
		{
			writeHex(data[i], 4, out);
			out += 4;
			lrc -= (data[i] / 256);
			lrc -= (data[i] & 0xFF);
		}
	} else if (size_bits == 1)
	{
		unsigned char bit_pos = 1;
		unsigned char val;
		for (int i = 0; i < count; i++)
		{
			if (bit_pos == 1) val = 0;
			if (data[i]) val |= bit_pos;
			if (bit_pos == 128)
			{
				bit_pos = 1;
				writeHex(val, 2, out);
				lrc -= val;
				out += 2;
			} else
				bit_pos *= 2;
		}
		if (bit_pos != 1)
		{
			writeHex(val, 2, out);
			lrc -= val;
			out += 2;
		}
	}
}

void Modbus::CheckCRC16(unsigned char* msg, unsigned short len)
{
	unsigned short pos = 0; /* frame position index */
	unsigned char crc_hi = 0xFF; /* high CRC byte initialized */
	unsigned char crc_lo = 0xFF; /* low CRC byte initialized */
	unsigned int i; /* will index into CRC lookup */

	/* pass through message buffer */
	while (pos < len - 2)
	{
		i = crc_hi ^ msg[pos++]; /* calculate the CRC  */
		crc_hi = crc_lo ^ table_crc_hi[i]; /* ^ XOR */
		crc_lo = table_crc_lo[i];
	}
	if ((msg[pos] != crc_hi) || (msg[pos+1] != crc_lo))
		throw error_api(ERROR_INFO(), api_error::get_crc());
}



void Modbus::SetCRC16(unsigned char* msg, unsigned short len)
{
	unsigned short pos = 0; /* frame position index */
	unsigned char crc_hi = 0xFF; /* high CRC byte initialized */
	unsigned char crc_lo = 0xFF; /* low CRC byte initialized */
	unsigned int i; /* will index into CRC lookup */

	/* pass through message buffer */
	while (pos < len - 2)
	{
		i = crc_hi ^ msg[pos++]; /* calculate the CRC  */
		crc_hi = crc_lo ^ table_crc_hi[i]; /* ^ XOR */
		crc_lo = table_crc_lo[i];
	}
	msg[pos++] = crc_hi;
	msg[pos++] = crc_lo;
}

void Modbus::getFunctionParameters(ModbusCmd& cmd)
{
	struct s_cmd_data
	{
		char func;
		char base;
		char size;
	} cmd_data[] = { { ModbusCmd::MODBUS_FC_READ_COILS, 0, 1 }, { ModbusCmd::MODBUS_FC_READ_DISCRETE_INPUTS, 1, 1 }, {
			ModbusCmd::MODBUS_FC_READ_HOLDING_REGISTERS, 4, 16 }, { ModbusCmd::MODBUS_FC_READ_INPUT_REGISTERS, 3, 16 }, {
			ModbusCmd::MODBUS_FC_WRITE_SINGLE_COIL, 0, 1 }, { ModbusCmd::MODBUS_FC_WRITE_SINGLE_REGISTER, 4, 16 }, {
			ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_COILS, 0, 1 }, { ModbusCmd::MODBUS_FC_WRITE_MULTIPLE_REGISTERS, 4, 16 }, { 0, 0 } };
	for (struct s_cmd_data* it = cmd_data; it != (cmd_data + sizeof(cmd_data) / sizeof(*cmd_data)); ++it)
	{
		if ((*it).func == cmd.function)
		{
			cmd.base = (*it).base;
			cmd.data_size_bits = (*it).size;
			break;
		}
	}
}
