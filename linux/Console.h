/*
 * Console.h
 *
 *  Created on: 29 May 2014
 *      Author: lester
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "stdio.h"
#include "Buffer.h"
#include <unistd.h>
#include "iobase.h"

class _console: public io::io_base
{
	FILE* streamf = nullptr;
public:
	bool open()
	{
		if (streamf) return true;
		streamf = fdopen(STDOUT_FILENO, "a");
		return streamf != nullptr;
	}
	void close()
	{
		if (streamf)
		{
			fclose(streamf);
			streamf = nullptr;
		}
	}
	~_console()
	{
		if (streamf) fclose(streamf);
	}
	operator bool()
	{
		return streamf != nullptr;
	}
	void read(void* buffer, uint32_t& maxSize, api_error * e = nullptr) override
	{

	}
	void write(void* buffer, uint32_t& len, api_error* e = nullptr) override
	{
		if (streamf)
		{
			fwrite(buffer, 1, len, streamf);
		}
	}
	void flush()
	{
		fflush(streamf);
	}

};

#endif /* CONSOLE_H_ */
