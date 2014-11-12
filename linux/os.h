/*
 * os.h
 *
 *  Created on: 22 Jun 2014
 *      Author: lester
 */

#ifndef OS_H_
#define OS_H_

#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "errno.h"
#include "ualgorithm.h"

#ifdef _DEBUG
#define ERROR_INFO() _error_info(__FILE__,__LINE__,__func__)
#else
#define ERROR_INFO() _error_info()
#endif

class os
{
public:
	using sock_fd_type = int;
	using fd_type = int;
	using api_error_type = int;
	using sock_error_type = int;

	typedef struct
	{
		int code;
		const char* msg;
		bool operator ==(int code)
		{
			return this->code == code;
		}
		bool operator >(int code)
		{
			return this->code > code;
		}
		bool operator <(int code)
		{
			return this->code < code;
		}
	} _error_tbl;

	static _error_tbl api_tbl[];
	static _error_tbl* api_tbl_last;

	static const char* getApiErrorDescription(api_error_type code)
	{
		//_error_tbl* t = find(api_tbl,api_tbl_last,code);
		const _error_tbl* it = api_tbl;
		while (it->code != code && it != api_tbl_last)
			++it;
		return it->msg;
	}
	static const char* getSockApiErrorDescription(sock_error_type code)
	{
		return getApiErrorDescription(code);
	}
	static api_error_type getLastApiError()
	{
		return errno;
	}
	static sock_error_type getLastSocketError()
	{
		return errno;
	}
	static constexpr const char *getBuildVersion()
	{
		return "Build: " __DATE__ " " __TIME__;
	}
};

#define ERROR_BASE64_LEN		200		// len of base 64 is not valid
#define ERROR_BASE64_CHAR		201		// invalid base 64 char
#define ERROR_WRONG_PROTOCOL 	202
#define ERROR_CRC			 	203
#define ERROR_OVERWRITTEN		204		// data has been overwritten. (share memory consumer design)
#define ERROR_EOF				205		// data has been overwritten. (share memory consumer design)
#define ERROR_INVALID_CHAR		206
#define ERROR_WRONG_PARAM		207
#define ERROR_LOCKED			208
#define ERROR_CALL_NOT_IMPLEMENTED 209

#define API_ERROR(name,val) \
	bool name() const { return code == val; }  \
	void set ## name() { code = val; }  \
	static os::api_error_type get_ ## name() { return val; }

class api_error
{
	os::api_error_type code;
public:
	api_error(os::api_error_type code) :
			code(code)
	{

	}
	api_error() :
			code(0)
	{

	}
	void setApi(os::api_error_type code)
	{
		this->code = code;
	}
	os::api_error_type getApi() const
	{
		return code;
	}
	const char* getDescription() const
	{
		return os::getApiErrorDescription(code);
	}
	unsigned print(char* str, uint32_t size) const
	{
		if (size)
		{
			int ir = snprintf(str, size, "%d : %s", code, os::getApiErrorDescription(code));
			return (ir > 0 && (unsigned) ir > size) ? size : ir;
		}
		return 0;
	}

	API_ERROR(ok,0)
	API_ERROR(not_permitive,EPERM)
	API_ERROR(input_output,EIO)
	API_ERROR(overwritten,ERROR_OVERWRITTEN)
	API_ERROR(crc,ERROR_CRC)
	API_ERROR(protocol,ERROR_WRONG_PROTOCOL)
	API_ERROR(not_enough_memory,ENOMEM)
	API_ERROR(base64_len,ERROR_BASE64_LEN)
	API_ERROR(base64_character,ERROR_BASE64_CHAR)
	API_ERROR(not_found,ENOENT)
	API_ERROR(close,EBADF)
	API_ERROR(eof,ERROR_EOF)
	API_ERROR(invalid_char,ERROR_INVALID_CHAR)
	API_ERROR(wrong_param,ERROR_WRONG_PARAM)
	API_ERROR(no_implement,ERROR_CALL_NOT_IMPLEMENTED)
	API_ERROR(locked,ERROR_LOCKED)

};

#endif /* OS_H_ */
