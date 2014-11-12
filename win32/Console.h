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
#include "iobase.h"
#include "Windows.h"
#include <io.h>
#include <fcntl.h>

class _console: public io::io_base
{
	FILE* streamf = nullptr;
	HANDLE fh = INVALID_HANDLE_VALUE;
public:
	void open()
	{
		if (fh == INVALID_HANDLE_VALUE)
		{
			fh = GetStdHandle(STD_OUTPUT_HANDLE);
			if (fh == INVALID_HANDLE_VALUE)
			{
				GetLastError();
			}
			int hCrt = _open_osfhandle((long) fh, _O_TEXT);
			streamf = _fdopen(hCrt, "w");
		}
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
		if (streamf)
			fclose(streamf);
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
			// DWORD written; 	::WriteConsole(fh,buffer,len, &written, nullptr);
		}
	}

	void flush()
	{
		fflush(streamf);
	}

};

#endif /* CONSOLE_H_ */
