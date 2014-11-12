/*
 * error_base.h
 *
 *  Created on: 25 Apr 2014
 *      Author: lester
 */

#ifndef ERROR_BASE_H_1
#define ERROR_BASE_H_1

#include <stdint.h>
#include <exception>
#include <string.h>
#include <stdio.h>
#include "os.h"

/*
 *	Class holding extra info for exceptions throw point
 */
class _error_info
{

public:
	// function to handle exception type
	typedef void (*err_func)(const _error_info& e);

#ifdef _DEBUG
protected:
	void operator =(const _error_info& e)
	{
		/*
		 file_name = e.file_name;
		 file_line = e.file_line;
		 function_name = e.function_name;
		 */
	}
public:
	// Copy constructor
	_error_info(const _error_info& e) :
	file_name(e.file_name), file_line(e.file_line), function_name(
			e.function_name)
	{

	}
	// Constructor from data
	_error_info(const char* const file_name, uint32_t file_line,
			const char* const function_name) :
	file_name(file_name), file_line(file_line), function_name(
			function_name)
	{

	}
	// Getters
	const char* getFile() const
	{
		return file_name;
	}
	const char* getFucntion() const
	{
		return function_name;
	}
	uint32_t getLine() const
	{
		return file_line;
	}
	int print(char* msg, uint32_t max) const
	{
		return snprintf(msg, max, "%s %s(%d) ", file_name, function_name,
				file_line);
	}

protected:
	const char* const file_name;
	const uint32_t file_line;
	const char* const function_name;
#else

protected:
	// Use default constructor
	void operator =(const _error_info& e)
	{
	}
public:
	_error_info()
	{

	}
	_error_info(const _error_info& i)
	{
	}

	// empty getter
	const char* getFile() const
	{
		return "";
	}
	const char* getFunction() const
	{
		return "";
	}
	uint32_t getLine() const
	{
		return 0;
	}
	int print(char* msg, uint32_t max) const
	{
		return 0;
	}
#endif

};

namespace uexception {

class error_base: public std::exception, public _error_info
{

public:
	error_base(const _error_info& i) :
			_error_info(i)
	{

	}
	virtual ~error_base() throw ()
	{

	}
	virtual const char* what() const throw ()
	{
		return "no description";
	}
	/*
	 * Use to log all error info from a exception
	 */
	virtual unsigned print(char* str, uint32_t size) const
	{
		if (size == 0) return 0;
		*str = 0;
		return strlen(strncat(str, "general exception", size - 1));
	}
};
}

/*
 * Exceptions macro definition
 * Define a base exception type
 * Define a exception derived from a  previous declare base exception
 * Define a exception derive from base
 *
 * A function to throw a specific exception will be also define
 */

// ********************************************************************
#define DEFINE_BASE_EXCEPTION(type) \
namespace uexception { \
class type : public uexception::error_base  \
{ \
	public:  \
		type(const _error_info& i) : error_base(i) {} \
		virtual ~type() throw () 	{} \
} ;}

// *********************************************************************
#define DEFINE_DERIVED_EXCEPTION(type,base,desc)  \
namespace uexception { \
class type : public base  \
{ \
	public:  \
		type(const _error_info& i) : base(i) {} \
		virtual ~type() throw () 	{} \
		virtual const char* what() const throw () { return desc;}  \
};}

// **********************************************************************
#define DEFINE_EXCEPTION(type,desc)  \
namespace uexception { \
class type : public uexception::error_base  \
{ \
	public:  \
		type(const _error_info& i) : error_base(i) {} \
		virtual ~type() throw () 	{} \
		virtual const char* what() const throw () { return desc;}  \
};}

DEFINE_BASE_EXCEPTION(error_socket)

namespace uexception {
class error_api: public error_base, api_error
{
public:
	error_api(const _error_info& i) :
			error_base(i), api_error(os::getLastApiError())
	{

	}
	error_api(const _error_info& i, const api_error& api) :
			error_base(i), api_error(api)
	{

	}
	error_api(const _error_info& i, os::api_error_type code) :
			error_base(i), api_error(code)
	{

	}
	virtual ~error_api() throw ()
	{
	}
	virtual const char* what() const throw ()
	{
		return getDescription();
	}
	virtual unsigned print(char* str, uint32_t size) const override
	{
		return api_error::print(str,size);
	}
};

/*
 * Base class for exception on a socket that comes from a api call
 */

class error_sock_api: public error_socket
{
	virtual const char* what() const throw () override
	{
		if (desc == nullptr) desc = os::getSockApiErrorDescription(code);
		return desc;
	}
	virtual unsigned print(char* str, uint32_t size) const override
	{
		if (size)
		{
			if (desc == nullptr) desc = os::getSockApiErrorDescription(code);
			*str = 0;
			int ir = snprintf(str, size, "API %d : %s", code, desc);
			return (ir > 0 && (unsigned) ir > size) ? size : ir;
		}
		return 0;
	}
	os::sock_error_type code;
	mutable const char* desc = nullptr;

public:
	error_sock_api(const _error_info& i, const api_error e) :
			error_socket(i), code(e.getApi())
	{

	}
	error_sock_api(const _error_info& i, os::sock_error_type code) :
			error_socket(i), code(code)
	{

	}
	error_sock_api(const _error_info& i) :
			error_socket(i), code(os::getLastSocketError())
	{

	}
};

class error_maping: public error_api
{
public:
	error_maping(const _error_info& i, os::api_error_type code, uint32_t size) :
			error_api(i, code), size(size)
	{
	}
	virtual ~error_maping() throw ()
	{
	}
	virtual const char* what() const throw ()
	{
		return "Failed to get or map memory area";
	}
private:
	uint32_t size = 0;
};

// memory exceptions
class error_memory: public error_api
{
public:
	error_memory(const _error_info& i) :
			error_api(i)
	{
	}
};
}

/*
 * error code class holding user or api error codes
 * TODO all user exception must be a similar api exception and all must be join together
 *
 *
 */
using namespace uexception;

#endif /* ERROR_BASE_H_ */
