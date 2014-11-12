/*
 * File.h
 *
 *  Created on: 18 Apr 2014
 *      Author: lester
 */

#ifndef FILE_H_
#define FILE_H_

#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <cstdio>
#include <stdarg.h>
//#include <libio.h>

#include "stdio.h"
#include "iobase.h"
#include "OneRelease.h"
#include "os.h"

//using namespace uexception;

class File: public io::io_base
{
	FILE *f;
	bool close()
	{
		if (fclose(f) == EOF) return false;    // do not throw use a file
		f = 0;
		return true;
	}
protected:
public:
	File() :
			f(0)
	{

	}
	virtual ~File()
	{
		if (f) close();
	}
	File(const char* file_name, const char* mode = "r")
	{
		if (!open(file_name, mode)) throw error_api(ERROR_INFO(),api_error::get_not_found());
	}
	void Close()
	{
		if (f)
		{
			close();
		}
	}
	void read(void* buffer, uint32_t& maxSize, api_error * e = nullptr) override
	{
		size_t t = read1(buffer,maxSize);
	}
	void write(void* buffer, uint32_t& len, api_error* e = nullptr) override
	{
		write(buffer,len);
	}
	size_t read1(void *data, size_t size)
	{
		if (!f) throw error_api(ERROR_INFO(),api_error::get_close());
		size_t st = fread(data, 1, size, f);
		if (!st)
		{
			if (feof(f)) st = 1;
			close();
			if (st)
				throw error_api(ERROR_INFO(),api_error::get_eof());
			else
				throw error_api(ERROR_INFO());
			//if (ferror(f))
		}
		return st;
	}
	size_t write(const void *data, size_t size) {
		if (!f)
			throw error_api(ERROR_INFO(),api_error::get_close());
		size_t st = fwrite(data, 1, size, f);
		if (!st)
		{
			if (feof(f)) st = 1;
			close();
			if (st)
				throw error_api(ERROR_INFO(),api_error::get_eof());
			else
				throw error_api(ERROR_INFO());
		}
		return st;
	}

	bool open(const char* name, const char* mode = "r")
	{
		//struct stat fstatus;
		f = fopen(name, mode);
		if (!f) return false;
		/*
		 CHECK_API_RET(lstat(fname, &fstatus) == 0);
		 dt = alloc.alloc(fstatus.st_size);
		 CHECK_RET_CODE(dt != 0, ERR_MEMORY);
		 size = fread(dt, 1, fstatus.st_size, f);
		 close();
		 return NO_ERR;

		 */
		return true;
	}

	operator bool()
	{
		return (f != 0);
	}
	void writef(const char* fmt, ...)
	{
		if (!f)
			throw error_api(ERROR_INFO(),api_error::get_close());
		va_list arg_ptr;
		va_start(arg_ptr, fmt);
		vfprintf(f, fmt, arg_ptr);
		va_end(arg_ptr);
	}
	void vwritef(const char* fmt, va_list args)
	{
		if (!f)
			throw error_api(ERROR_INFO(),api_error::get_close());
		vfprintf(f, fmt, args);
	}

	void flush()
	{
		if (!f)
			throw error_api(ERROR_INFO(),api_error::get_close());
		fflush(f);
	}
	/*
	 * Store and object or data as raw
	 * push(n) if n is a number a integer type will be use
	 * push(' ') the function is call with a char
	 */
	template<typename T>
	void push(const T& d)
	{
		write(&d, sizeof(d));
	}

	void LoadToMemory(const char* fname, void* &dt, unsigned int &size, OneRelease &alloc);

};

#endif /* FILE_H_ */
