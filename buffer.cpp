/*
 * buffer.cpp
 *
 *  Created on: 28 May 2014
 *      Author: lester
 */

#include "Buffer.h"

namespace io
{
Buffer& Buffer::operator <<(const char* s)
{
	uint32_t l = strlen(s);
	if (l > getWSize())
	{

		if (throw_overflow) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		l = getWSize();
	}
	memcpy(getW(), s, l);
	updateW(l);
	return *this;
}

Buffer& Buffer::operator<<(const fstring& s)
{
	uint32_t l = s.size();
	if (s.size() > getWSize())
	{
		if (throw_overflow) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		l = getWSize();
	}
	memcpy(getW(), s.c_str(), l);
	updateW(l);
	return *this;
}

Buffer& Buffer::operator<<(const Buffer& b)
{
	uint32_t l = b.getRSize();
	if (l > getWSize())
	{
		if (throw_overflow) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		l = getWSize();
	}
	memcpy(getW(), b.getR(), l);
	updateW(l);
	return *this;
}

template<int N>
Buffer& Buffer::operator<<(const Block<N> &b)
{
	uint32_t l = b.size();
	if (l > getWSize())
	{
		if (throw_overflow) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		l = getWSize();
	}
	memcpy(getW(), b.data(), l);
	updateW(l);
	return *this;
}

Buffer& Buffer::operator<<(const cBlock& b)
{
	uint32_t l = b.size();
	if (l > getWSize())
	{
		if (throw_overflow) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		l = getWSize();
	}
	memcpy(getW(), b.data(), l);
	updateW (l);
	return *this;

}

}
