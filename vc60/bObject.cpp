// bObject.cpp: implementation of the CbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "bObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbObject::CbObject()
{
	m_plog = &glog;
	m_err_msg[0] = 0;
	m_btrace_all = false;
	m_ver = "Class CbObject " CLASS_VER;
}

CbObject::~CbObject()
{

}

DWORD CbObject::ErrorMsg_code(DWORD ret_val, DWORD err_code, char *str1, char *str2, char *str3, char *str4, char *str5, char *str6)
{
	m_err_msg[sizeof(m_err_msg)-1] = 0;
	_snprintf(m_err_msg,sizeof(m_err_msg)-1,"%s %s %s %s %s %s failed with Code = 0x%X",str1,str2,str3,str4,str5,str6,err_code);
	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	return ret_val;
}

DWORD CbObject::Error(DWORD retval, const char *format, ...)
{
	va_list arg_ptr;
	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	_vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);
	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	return retval;
}

DWORD	CbObject::Error_Add_W32_msg(DWORD retval,DWORD w32_ecode,const char *format, ...)
{
	char	*cptr;
	va_list arg_ptr;
	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	cptr = m_err_msg;
	cptr += _vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,w32_ecode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(m_err_msg)-(cptr-m_err_msg)-1,NULL);
	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	return retval;
}


DWORD CbObject::SetError(BOOL trace, DWORD retval, const char *format,...)
{
	va_list arg_ptr;
	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	_vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);
	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	else
		if (trace) m_plog->log_strings(LOG_ERROR,m_err_msg);
	m_err_code = retval;
	return retval;
}

DWORD CbObject::SetError_Add_W32_code_msg(BOOL trace, DWORD retval,DWORD w32_ecode, const char *format,...)
{
	char	*cptr;
	va_list arg_ptr;
	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	cptr = m_err_msg;
	cptr += _vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);

	cptr += sprintf(cptr," 0x%X - ",w32_ecode);

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,w32_ecode,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(m_err_msg)-(cptr-m_err_msg)-1,NULL);

	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	else
		if (trace) m_plog->log_strings(LOG_ERROR,m_err_msg);
	m_err_code = retval;
	return retval;
}

DWORD CbObject::Error_Add(BOOL trace, DWORD retval, const char *format,...)
{
	DWORD	size;
	DWORD	pos;
	char	*cptr;
	va_list arg_ptr;
	m_err_msg[sizeof(m_err_msg)-1] = 0;

	pos = strlen(m_err_msg);
	cptr = m_err_msg + pos;
	size = sizeof(m_err_msg) - pos-1;

	va_start(arg_ptr, format);
	_vsnprintf(m_err_msg,size,format,arg_ptr);
	va_end(arg_ptr);
	if (m_btrace_all) m_plog->_log(LOG_ERROR,"%s",m_err_msg);
	else
		if (trace) m_plog->_log(LOG_ERROR,m_err_msg);
	m_err_code = retval;
	return retval;
}


