/*
 * os.h
 *
 *  Created on: 23 Jun 2014
 *      Author: lester.crespo
 */

#ifndef OS_H_
#define OS_H_

// compiler will warning when a function is declared to throw a exception
#pragma warning( disable : 4290 )
// compiler warning about snprintf
#pragma warning( disable : 4996 )

#include <WinSock2.h>	// Never ever include this before windows.h Microsoft sheet (ee =i)
#include <Windows.h>
#include <process.h>
#include <stdint.h>
#include <exception>
#include <stdio.h>

//c:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\process.h

// para poder compilar en visual estudio 6.0

#define snprintf	_snprintf
#define vsnprintf	_vsnprintf
#define getpid		_getpid
#define popen		_popen
#define pclose		_pclose
#define socklen_t	int

#ifdef _DEBUG
#define ERROR_INFO() _error_info(__FILE__,__LINE__,"")
#else
#define ERROR_INFO() _error_info()
#endif

class os
{
public:
	using sock_fd_type = SOCKET;
	using fd_type = HANDLE;
	using api_error_type = HRESULT;
	using sock_error_type = int;

	typedef struct _error_tbl_
	{
		os::api_error_type code;
		const char* msg;
		bool operator ==(const struct _error_tbl_& e)
		{
			return code == e.code;
		}
	} _error_tbl;

	static struct _error_tbl api_tbl[];
	static struct _error_tbl* api_tbl_last;

	static const char* getApiErrorDescription(api_error_type code)
	{
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
		return GetLastError();
	}
	static sock_error_type getLastSocketError()
	{
		return WSAGetLastError();
	}
	static const char *getBuildVersion()
	{
		return "Build: " __DATE__ "-" __TIME__;
	}
};

/*
 * Header file for error handling.
 * exception and so
 */

/*
 #ifndef _WIN32
 constexpr
 #endif
 const char* _file(const char* next, const char* name)
 {
 return *next == 0 ?
 name :
 (*next == '/' ? _file(next + 1, next + 1) : _file(next + 1, name));
 }

 const char* _file_name(const char* str)
 {
 return _file(str + 1, str);
 //return *str ? str + 2 : str + 1;
 }
 */

#define ERROR_BASE64_LEN		0x4000		// len of base 64 is not valid
#define ERROR_BASE64_CHAR		0x4001		// invalid base 64 char
#define ERROR_WRONG_PROTOCOL 	0x4002
#define ERROR_OVERWRITTEN		0x4004		// data has been overwritten. (share memory consumer design)
#define ERROR_INVALID_CHAR		0x4005
#define ERROR_WRONG_PARAM		0x4006		// invalid param, value or argument passed to the function
/*
 * An API error codes holding and allow some operations to test error type
 */
#define API_ERROR(name,val) \
	bool name() const { return code == val; }  \
	void set ## name() { code = val; } \
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
			code(ERROR_SUCCESS)
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

	API_ERROR(ok,ERROR_SUCCESS)
	API_ERROR(eof,ERROR_HANDLE_EOF)
	API_ERROR(access_denied,ERROR_ACCESS_DENIED)
	API_ERROR(not_enough_memory,ERROR_NOT_ENOUGH_MEMORY)
	API_ERROR(close,ERROR_INVALID_HANDLE)
	API_ERROR(open,ERROR_ALREADY_EXISTS)
	API_ERROR(would_block,WSAEWOULDBLOCK)
	API_ERROR(not_found,ERROR_FILE_NOT_FOUND)
	API_ERROR(io,ERROR_DEV_NOT_EXIST)
	API_ERROR(overwritten,ERROR_OVERWRITTEN)
	API_ERROR(crc,ERROR_CRC)
	API_ERROR(protocol,ERROR_WRONG_PROTOCOL)
	API_ERROR(base64_len,ERROR_BASE64_LEN)
	API_ERROR(base64_character,ERROR_BASE64_CHAR)
	API_ERROR(invalid_char,ERROR_INVALID_CHAR)
	API_ERROR(wrong_param,ERROR_WRONG_PARAM)
	API_ERROR(no_implement,ERROR_CALL_NOT_IMPLEMENTED)
	API_ERROR(locked,ERROR_LOCKED)


};
#endif /* OS_H_ */
