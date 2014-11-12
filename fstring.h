/*
 * fstring.h
 *
 *  Created on: 17 Apr 2014
 *      Author: lester
 */

#ifndef FSTRING_H_
#define FSTRING_H_

#include <string>
#include <string.h>


template<unsigned N>
class stackstring
{
	char c[N];
	unsigned size = 0;
public:
	bool set(unsigned v)
	{
		if (N < 20)
			return false;
		return true;
	}
	unsigned len() const
	{
		return this->size;
	}
	char* begin()
	{
		return c;
	}
};

/*
 * Fast string holder and comparator
 * invariant object use to handle string in temporal memory base on start end position
 *
 */
class fstring
{
	const char* const start;	// string first character
	const unsigned len;
public:
	fstring(const fstring &str) :
			start(str.start), len(str.len)
	{

	}
	// end is one character pass the end of string
	fstring(const char* start, const char* end) :
			start(start), len(end - start)
	{

	}
	// end is one character pass the end of string
	fstring(const char* start) :
			start(start), len(strlen(start))
	{

	}
	fstring(const char* start, unsigned len) :
			start(start), len(len)
	{

	}
	std::string getString() const
	{
		return
		{	start,static_cast<size_t>(len)};
	}
	~fstring()
	{
	}
	// Comparation operators
	bool operator ==(const char* str) const
	{
		return str && (strncmp(str, start, len) == 0) && str[len] == 0;
	}
	bool operator ==(const fstring & str) const
	{
		return len == str.len && strncmp(str.start, start, len) == 0;
	}
	bool operator !=(const char* str) const
	{
		return !(operator ==(str));
	}
	bool operator !=(const fstring & str) const
	{
		return !(operator ==(str));
	}
	operator bool() const
	{
		return len != 0;
	}
	unsigned size() const
	{
		return len;
	}
	// convert string to unsigned
	bool get(unsigned &v)
	{
		return false;
	}
	/*
	 * Be carefully using this function,
	 * if fstring does not come from a zero-end string do not use it
	 */
	const char* c_str() const
	{
		return start;
	}
	const char* begin() const
	{
		return start;
	}
	const char* end() const
	{
		return start + len;
	}
};

#endif /* FSTRING_H_ */
