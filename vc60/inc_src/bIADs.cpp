// bIADs.cpp: implementation of the CbIADs class.
//
//////////////////////////////////////////////////////////////////////

#include "bIADs.h"
#include "utils.h"
#include "bstr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// tabla de errores del ADSI
struct
{
	HRESULT	code;
	char*	msg;
}_ADSI_etable[] = {
	{ 0x00005011L, "During a query, one or more errors occurred. Verify that the search preference can be legally set and, if so, is properly set"}, 
	{ 0x00005012L, "The search operation has reached the last row. Move on to the rest of the program."}, 
	{ 0x00005013L, "The search operation has reached the last column for the current row. Move on to next row."}, 
	{ 0x80005000L, "An invalid ADSI pathname was passed. Verify that the object exists on the directory server and check for typos of the path."}, 
	{ 0x80005001L, "An unknown ADSI domain object was requested. Verify the path of the domain object."}, 
	{ 0x80005002L, "An unknown ADSI user object was requested. Verify the existence of the user object, check for typos of the path name and the user's access rights."}, 
	{ 0x80005003L, "An unknown ADSI computer object was requested. Verify the existence of the computer object, check for typos of the path name and the computer's access rights."}, 
	{ 0x80005004L, "An unknown ADSI object was requested. Verify the name of and the access rights to the object."}, 
	{ 0x80005005L, "The specified ADSI property was not set."}, 
	{ 0x80005006L, "The specified ADSI property is not supported. Verify that the correct property is being set."}, 
	{ 0x80005007L, "The specified ADSI property is invalid Verify the parameters passed to the method call."}, 
	{ 0x80005008L, "One or more input parameters are invalid."}, 
	{ 0x80005009L, "The specified ADSI object is not bound to a remote resource. Make sure to call GetInfo on a newly created object after SetInfo has been called."}, 
	{ 0x8000500AL, "The specified ADSI object has not been modified."}, 
	{ 0x8000500BL, "The specified ADSI object has been modified."}, 
	{ 0x8000500CL, "The data type cannot be converted to/from a native DS data type. Make sure that the correct data type is used and/or that there is sufficient schema information available to perform data type conversion."}, 
	{ 0x8000500DL, "The property cannot be found in the cache. Make sure that GetInfo has been called (implicitly or explicitly). If the attribute is an operational attribute, it must be explicitly retrieved with GetInfoEx instead of GetInfo. If the problem persists, the property has not been set on the server."}, 
	{ 0x8000500EL, "The ADSI object exists. Use a different name to create the object."}, 
	{ 0x8000500FL, "The attempted action violates the directory service schema rules."}, 
	{ 0x80005010L, "The specified column in the ADSI was not set."}, 
	{ 0x80005014L, "The specified search filter is invalid. Make sure to use the correct format of the filter that is acceptable to the directory server."}, 
	{ 0x80004004L, "Operation aborted."},
	{ 0x80004005L, "Unspecified error."},
	{ 0x80004002L, "Interface not supported."},
	{ 0x80004001L, "Not implemented."}, 
	{ 0x80004003L, "Invalid pointer."}, 
	{ 0x8000FFFFL, "Catastrophic failure."},
	{ 0x00000000L, "Unknown error"},
};

CbIADs::CbIADs()
{
	m_iads = NULL;
}

CbIADs::~CbIADs()
{
	Release();
}

void CbIADs::Release()
{
	if (m_iads != NULL) m_iads->Release();
	m_iads = NULL;
}

DWORD CbIADs::OpenObject(LPWSTR lpszPathName, LPWSTR lpszUserName, LPWSTR lpszPassword, DWORD dwReserved, REFIID riid, VOID **ppObject)
{
	HRESULT	hr;
	char	emsg[255];
	Release();
	hr = ADsOpenObject(lpszPathName,lpszUserName,lpszPassword,dwReserved,riid,ppObject);
	if (hr != S_OK) 
	{
		gutils.Char_Get(lpszPathName,emsg,sizeof(emsg));
		return 	SetError_Add_iads_code_msg(hr,"CbIADs::OpenObject (%s)",emsg);
	}
	m_iads = (IADs*)(*ppObject);
	return ERR_OK;
}

DWORD CbIADs::SetError_Add_iads_code_msg(HRESULT hr, char *format, ...)
{
	WORD	i;
	char	*cptr;
	va_list arg_ptr;

	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	cptr = m_err_msg;
	cptr += _vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);

	cptr += sprintf(cptr," failed with code 0x%X - ",hr);
	
	if (HRESULT_FACILITY(hr)==FACILITY_WIN32)
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,hr&0xFFFF,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(m_err_msg)-(cptr-m_err_msg),NULL);
		if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
		return ERR_API;
	}

	if ( hr & 0x00005000) // standard ADSI Errors 
    {
        // recorrer la tabla de errores s = GetADSIError(hr);
		for (i=0;;i++)
		{
			if ((_ADSI_etable[i].code == hr) || (_ADSI_etable[i].code == 0)) break;
		}
		cptr += _snprintf(cptr,sizeof(m_err_msg)-(cptr-m_err_msg)-1," %s",_ADSI_etable[i].msg);
		if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
		return ERR_API;
    }


	WCHAR	sError[255];
    WCHAR	sProvider[255];
	DWORD	code;
	HRESULT	hr1;
	char	err_msg[255];
	char	err_prov[255];

	hr1 = ADsGetLastError(&code,sError,sizeof(sError)/2,sProvider,sizeof(sProvider)/2);
	if (hr1 != S_OK)
	{
		cptr += _snprintf(cptr,sizeof(m_err_msg)-(cptr-m_err_msg),"... ADsGetLastError failed with code %u",hr1);
		if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
		return ERR_FATAL;
	}
	gutils.Char_Get(sError,SSIZE(err_msg));
	gutils.Char_Get(sProvider,SSIZE(err_prov));
	cptr += _snprintf(cptr,sizeof(m_err_msg)-(cptr-m_err_msg),"Provider = %s Msg = %s",err_prov,err_msg);
	if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
	return ERR_API;
}

DWORD CbIADs::GetObject(LPWSTR PathName, REFIID riid, VOID **ppObject)
{
	HRESULT	hr;
	char	emsg[255];
	Release();
	hr = ADsGetObject(PathName,riid,ppObject);
	if (hr != S_OK) 
	{
		gutils.Char_Get(PathName,emsg,sizeof(emsg));
		return 	SetError_Add_iads_code_msg(hr,"CbIADs::GetObject (%s)",emsg);
	}
	m_iads = (IADs*)(*ppObject);
	return ERR_OK;

}

DWORD CbIADs::QueryInterfaz(IADs *piads, REFIID riid, VOID **ppObject)
{
	HRESULT	hr;
	Release();
	hr = piads->QueryInterface(riid,ppObject);
	if (hr != S_OK) return 	SetError_Add_iads_code_msg(hr,"CbIADs::QueryInterfaz ");
	m_iads = (IADs*)(*ppObject);
	return ERR_OK;
}

void CbIADs::Attach(IADs *piads)
{
	Release();
	m_iads = piads;
}

DWORD CbIADs::Get(BSTR prop, VARIANT *pvProp)
{
	HRESULT	hr;
	char	tmp_str[255];
	hr = m_iads->Get(prop,pvProp);
	if (hr != S_OK) 
	{
		gutils.Char_Get(prop,tmp_str,sizeof(tmp_str));
		return 	SetError_Add_iads_code_msg(hr,"CbIADs::Get (%s)",tmp_str);
	}
	return ERR_OK;	
}
