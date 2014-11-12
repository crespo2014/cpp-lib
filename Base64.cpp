/*
 * Base64.cpp
 *
 *  Created on: 3 Sep 2013
 *      Author: lester
 */

#include "Base64.h"
#include "log.h"

//#define log_e()

Base64::Base64(void* out, unsigned short max_size)
{
	wr = reinterpret_cast<unsigned char*>(out);
	wr_size = max_size;
	wr_pos = 0;
}

Base64::~Base64()
{
}

void Base64::encode(const unsigned char* data, unsigned short size)
{
	wr_pos = 0;
	unsigned short rd_pos = 0;
	unsigned short count;
	unsigned char cache[4];
	const static char *tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	while (rd_pos < size)
	{
		if (wr_pos + 4 > wr_size)
		{
			throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		}
		count = 0;
		for (; count < 3 && rd_pos < size; count++, rd_pos++)
		{
			cache[count] = reinterpret_cast<const unsigned char*>(data)[rd_pos];
		}
		if (count < 3)
		{
			if (count < 2)
			{
				cache[1] = 0;
				wr[wr_pos + 2] = '=';
			}
			cache[2] = 0;
			wr[wr_pos + 3] = '=';
		}
		wr[wr_pos] = tbl[cache[0] >> 2];
		wr[wr_pos + 1] = tbl[(unsigned char)(((cache[0] & 0x03) << 4) | (cache[1] >> 4))];
		if (count > 1)
		{
			wr[wr_pos + 2] = tbl[(unsigned char)(((cache[1] & 0xF) << 2) | (cache[2] >> 6))];

			if (count > 2)
			{
				wr[wr_pos + 3] = tbl[(unsigned char)(cache[2] & 0x3F)];
			}
		}
		wr_pos += 4;

	}
}

void Base64::decode(const unsigned char* data, unsigned short size)
{
	if (size & 3)
	{
		throw error_api(ERROR_INFO(),api_error::get_base64_len());
	}
#define NS	0xFF		// no base 64 symbol
	const static unsigned char decode_tbl[] =
		/*			0	1	2	3	4	5	6	7	8	9	0	11	12	13	14	15	16	17	18	19	*/

		/*   0 */{ NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/*  20   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/*  40   */NS, NS, NS, 62, NS, NS, NS, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, NS, NS,

		/*  60   */NS, NS, NS, NS, NS, 00, 01, 02, 03, 04, 05, 06, 07, 8, 9, 10, 11, 12, 13, 14,

		/*  80   */15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, NS, NS, NS, NS, NS, NS, 26, 27, 28,

		/* 100   */29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,

		/* 120   */49, 50, 51, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 140   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 160   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 180   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 200   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 220   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,

		/* 240   */NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS, NS };

	unsigned char cache[4];
	unsigned char i;
	unsigned short rd_pos;
	wr_pos = 0;
	rd_pos = 0;
	while (rd_pos < size)
	{
		// check for space
		if (wr_pos + 3 > wr_size)
			throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		// read first byte or 0
		cache[0] = data[rd_pos++];
		// read 3 more bytes
		while (rd_pos & 3)		// stop on next multiple of 4
		{
			cache[(rd_pos & 3)] = data[rd_pos];
			rd_pos++;
		}
		i = 4;
		if (cache[3] == '=')
		{
			i = 3;
			cache[3] = 0xFF;
		}
		if (cache[2] == '=')
		{
			i = 2;
			cache[2] = 0xFF;
		}
		while (i--)
		{
			cache[i] = decode_tbl[cache[i]];
			if (cache[i] == NS)
			{
				// todo create a base64 exception to holding the symbol
				throw error_api(ERROR_INFO(),api_error::get_invalid_char());
				//log_e("Invalid b64 symbol x%0x", cache[i]);

			}
		}
		wr[wr_pos++] = (unsigned char) ((cache[0] << 2) | (cache[1] >> 4));
		if (cache[2] != 0xFF)
			wr[wr_pos++] = (unsigned char) ((cache[1] << 4) | (cache[2] >> 2));
		if (cache[3] != 0xFF)
			wr[wr_pos++] = (unsigned char) ((cache[2] << 6) | cache[3]);

	}
}
