/*
 * utf8_it.h
 *
 *  Created on: 7 May 2014
 *      Author: lester
 */

#ifndef UTF8_IT_H_
#define UTF8_IT_H_

#include "os.h"
#include <functional>

/*
 * this is a utf8 decoder
 * it will be use to read data from a buffer.
 * the read pointer is moved until the last valid character for utf8 sequence
 */

/*
 * V2.0
 * UTF8 iterator from input buffer
 * set Origin as option.
 * end iterator is virtual, depends on input buffer read.
 * put end iterator 2 step pass input buffer until last block is read then update.
 * ++it will read more data if necessary
 *
 * utf8 iterator will throw exception when value is not valid
 * how avoid iterator read pass end of the buffer
 */

DEFINE_BASE_EXCEPTION(utf8_base);

DEFINE_DERIVED_EXCEPTION(continuation_byte, utf8_base, "A continuation byte is not 10x");
DEFINE_DERIVED_EXCEPTION(overlong, utf8_base, "The encoded byte is more long than needed");
DEFINE_DERIVED_EXCEPTION(end, utf8_base, "Missing a continuation byte");
DEFINE_DERIVED_EXCEPTION(leading, utf8_base, "Too long utf8 character with more than 4 bytes");
DEFINE_DERIVED_EXCEPTION(unexpected_continuation, utf8_base, "Unexpected continuation byte read");
DEFINE_DERIVED_EXCEPTION(invalid_leading, utf8_base, "Leading byte is invalid");

/*
class utf8_dec
{
public:
	template<class F>
	static uint32_t read(uint8_t c, F f)
	{
		static unsigned char unused_tbl[] =
		{ 0, 0x4, 0x08, 0x10, 0x20, 0xFF, 0xFF, 0xFF }; // when 1 bits is unused then next value can not have more than 3 bits 0 on MSB

		// read byte and go next
		uint8_t len = 0;
		while (c & 0x80)
		{
			++len;
			c <<= 1;
		}
		if (!len)
			return c;
		if ((len == 1) || (len > 4) || ((len == 4) && (!c)) || ((len == 2) && (c < 0x40)))
			throw_error(invalid_leading);
		uint8_t unused_bits = 7 - len;
		uint32_t utf8c = c;
		utf8c >>= (len + 1);
		--len;
		while (len)
		{
			--len;
			c = f();
			if ((c & 0xC0) != 0x80)
				throw_error(continuation_byte);
			if (unused_bits)
			{
				// go here only at second byte of sequence
				if ((c & 0x3F) < unused_tbl[unused_bits])
					throw_error(overlong);
				unused_bits = 0;
			}
			utf8c <<= 6;
			utf8c |= (c & 0x3F);
		}
		return utf8c;
	}
};
*/

/*
 *
 * UTF-8  is a variable-width encoding
 * can store numbers up to 31bits
 * a value between 0-127 is store on a single byte
 * values over 127 are stored using 1 leading byte and one or more continuation bytes.
 *
 * encoding failures
 * - byte without information or Overlong encodings
 * - unexpected leading byte
 * - unexpected single byte
 * - an unexpected continuation byte
 * - a start byte not followed by enough continuation bytes
 * - sequence more than 6 bytes
 *
 *  this specification are not coded at all
 *  UTF-8 was restricted by RFC 3629 to end at U+10FFFF
 *  - A 4-byte sequence (starting with 0xF4) that decodes to a value greater than U+10FFFF
 *
 *  modified utf8 encode 00 as  11000000 10000000 to allow use byte 0 as string terminator
 */

class decode_utf8
{
	uint32_t c;
	uint8_t len;
	uint8_t unused_bits;
public:
	decode_utf8() :
			c(0), len(0), unused_bits(0)
	{

	}
	/*
	 * No throw exception function
	 */
	bool push(uint8_t v,uint32_t& ecode)
	{
		return false;
	}
	/*
	 * Push byte to decode while false
	 */
	bool push(uint8_t v)
	{
		static unsigned char unused_tbl[] =
				{ 0, 0x4, 0x08, 0x10, 0x20, 0xFF, 0xFF, 0xFF }; // when 1 bits is unused then next value can not have more than 3 bits 0 on MSB

		if (!len)
		{
			while (v & 0x80)
			{
				++len;
				v <<= 1;
			}
			c = v >> len;
			if (len)
			{
				if ((len == 1) || (len > 4) || ((len == 4) && (!c)) || ((len == 2) && (c < 0x2)))
					return_exception(invalid_leading);
				if (!c)
					unused_bits = 7 - len;
				--len;
			}
		}
		else
		{
			--len;
			if ((v & 0xC0) != 0x80)
				return_exception(continuation_byte);
			if (unused_bits)
			{
				// go here only at second byte of sequence
				if ((c & 0x3F) < unused_tbl[unused_bits])
					return_exception(overlong);
				unused_bits = 0;
			}
			c <<= 6;
			c |= (v & 0x3F);
		}
		return (!len);	// return true if len equal zero
	}
	/*
	 * Get char from decode and clear status machine
	 */
	uint32_t get() const
	{
		return c;
	}
};

#endif /* UTF8_IT_H_ */
