// bLDAP.cpp: implementation of the CbLDAP class.
//
//////////////////////////////////////////////////////////////////////

#include "bLDAP.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct
{
	HRESULT	code;
	char*	msg;
}_LDAP_etable[] = {
	{ LDAP_ADMIN_LIMIT_EXCEEDED,	"Administration limit on the server was exceeded"},
	{ LDAP_AFFECTS_MULTIPLE_DSAS,	"Multiple directory service agents are affected."},
	{ LDAP_ALIAS_DEREF_PROBLEM,		"Cannot dereference the alias."},
	{ LDAP_ALIAS_PROBLEM,			"The alias is invalid."},
	{ LDAP_ALREADY_EXISTS,			"The object already exists."},
	{ LDAP_ATTRIBUTE_OR_VALUE_EXISTS,"The attribute exists or the value has been assigned."},
	{ LDAP_AUTH_METHOD_NOT_SUPPORTED,"The authentication method is not supported. To determine the authentication methods supported by an Active Directory server, retrieve the SupportedSASLMechanisms property of rootDSE. See Serverless Binding and RootDSE."},
	{ LDAP_AUTH_UNKNOWN,			"Unknown authentication error occurred."},
	{ LDAP_BUSY,					"The server is busy."},
	{ LDAP_CLIENT_LOOP,				"Client loop was detected."},
	{ LDAP_COMPARE_FALSE,			"For ldap_compare_ext_s and ldap_compare_s, this message is returned if the function succeeds, and the attribute and known values do not match."},
	{ LDAP_COMPARE_TRUE,			"For ldap_compare_ext_s and ldap_compare_s, this message is returned if the function succeeds, and the attribute and known values match."},
	{ LDAP_CONFIDENTIALITY_REQUIRED,"Confidentiality is required."},
	{ LDAP_CONNECT_ERROR,			"Cannot establish the connection."},
	{ LDAP_CONSTRAINT_VIOLATION,	"There was a constraint violation."},
	{ LDAP_CONTROL_NOT_FOUND,		"The ldap function ( ldap_parse_page_control, ldap_parse_sort_control, or ldap_parse_vlv_control) did not find the specified control."},
	{ LDAP_DECODING_ERROR,			"Decoding error occurred."},
	{ LDAP_ENCODING_ERROR,			"Encoding error occurred."},
	{ LDAP_FILTER_ERROR,			"The search filter is bad."},
	{ LDAP_INAPPROPRIATE_AUTH,		"Authentication is inappropriate."},
	{ LDAP_INAPPROPRIATE_MATCHING,	"There was an inappropriate matching."},
	{ LDAP_INSUFFICIENT_RIGHTS,		"The user has insufficient access rights."},
	{ LDAP_INVALID_CREDENTIALS,		"The supplied credential is invalid."},
	{ LDAP_INVALID_DN_SYNTAX,		"The distinguished name has an invalid syntax."},
	{ LDAP_INVALID_SYNTAX,			"The syntax is invalid."},
	{ LDAP_IS_LEAF,					"The object is a leaf."},
	{ LDAP_LOCAL_ERROR,				"Local error occurred."},
	{ LDAP_LOOP_DETECT,				"The chain of referrals has looped back to a referring server."},
	{ LDAP_MORE_RESULTS_TO_RETURN,	"More results are to be returned."},
	{ LDAP_NAMING_VIOLATION,		"There was a naming violation."},
	{ LDAP_NO_MEMORY,				"The system is out of memory."},
	{ LDAP_NO_OBJECT_CLASS_MODS,	"Cannot modify object class."},
	{ LDAP_NO_RESULTS_RETURNED,		"Results are not returned."},
	{ LDAP_NO_SUCH_ATTRIBUTE,		"Requested attribute does not exist."},
	{ LDAP_NO_SUCH_OBJECT,			"Object does not exist."},
	{ LDAP_NOT_ALLOWED_ON_NONLEAF,	"Operation is not allowed on a non leaf object."},
	{ LDAP_NOT_ALLOWED_ON_RDN,		"Operation is not allowed on RDN."},
	{ LDAP_NOT_SUPPORTED,			"The feature is not supported."},
	{ LDAP_OBJECT_CLASS_VIOLATION,	"There was an object class violation."},
	{ LDAP_OPERATIONS_ERROR,		"Operations error occurred."},
	{ LDAP_OTHER,					"Unknown error occurred."},
	{ LDAP_PARAM_ERROR,				"A bad parameter was passed to a routine."},
	{ LDAP_PARTIAL_RESULTS,			"Partial results and referrals received."}, 
	{ LDAP_PROTOCOL_ERROR,			"Protocol error occurred."},
	{ LDAP_REFERRAL,				"A referral was returned from the server."},
	{ LDAP_REFERRAL_LIMIT_EXCEEDED,	"The referral limit has been exceeded."},
	{ LDAP_REFERRAL_V2,				"A referral was returned from the server."},
	{ LDAP_RESULTS_TOO_LARGE,		"Results returned are too large."},
	{ LDAP_SERVER_DOWN,				"Cannot contact the LDAP server."},
	{ LDAP_SIZELIMIT_EXCEEDED,		"Size limit was exceeded"},
	{ LDAP_STRONG_AUTH_REQUIRED,	"Strong authentication is required."},
	{ LDAP_SUCCESS,					"The call completed successfully."},
	{ LDAP_TIMELIMIT_EXCEEDED,		"Time limit, set by the server side time limit parameter, was exceeded."},
	{ LDAP_TIMEOUT,					"The search was aborted due to exceeding the limit of the client side timeout parameter."},
	{ LDAP_UNAVAILABLE,				"The server is unavailable."},
	{ LDAP_UNAVAILABLE_CRIT_EXTENSION,"The control is critical and the server does not support the control."},
	{ LDAP_UNDEFINED_TYPE,			"Type is not defined."},
	{ LDAP_UNWILLING_TO_PERFORM,	"The server is not willing to handle directory requests."},
	{ LDAP_USER_CANCELLED,			"The user has cancelled the operation."},
	{ 0x00000000L,					"Unknown error"},
};

CbLDAP::CbLDAP()
{
	m_hldap = NULL;
	m_blogged = false;
	m_ldapmessage = NULL;
	m_ldap_entry = NULL;
	m_attr_name = NULL;
	m_attr_ber = NULL;
}

CbLDAP::~CbLDAP()
{
	Release();
}

DWORD CbLDAP::Init(char *hostName, ULONG port)
{
	m_hldap = ldap_init(hostName,port);
	if (m_hldap == NULL) return SetError_Add_ldap_code_msg(LdapGetLastError(),"CbLDAP::Init (%s:%u) ... ",hostName,port);
	return ERR_OK;
}

DWORD CbLDAP::SetError_Add_ldap_code_msg(ULONG ulr, char *format, ... )
{
//	WORD	i;
	char	*cptr;
	va_list arg_ptr;

	m_err_msg[sizeof(m_err_msg)-1] = 0;

	va_start(arg_ptr, format);
	cptr = m_err_msg;
	cptr += _vsnprintf(m_err_msg,sizeof(m_err_msg)-1,format,arg_ptr);
	va_end(arg_ptr);

	cptr += sprintf(cptr," failed with code 0x%X - %s",ulr,ldap_err2string(ulr));
	
	/*
	if (HRESULT_FACILITY(hr)==FACILITY_WIN32)
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,hr&0xFFFF,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(m_err_msg)-(cptr-m_err_msg),NULL);
		if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
		return ERR_API;
	}
	*/
	/*
    {
    	for (i=0;;i++)
		{
			if ((_LDAP_etable[i].code == lr) || (_LDAP_etable[i].code == 0)) break;
		}
		cptr += _snprintf(cptr,sizeof(m_err_msg)-(cptr-m_err_msg)-1," %s",_ADSI_etable[i].msg);
		if (m_btrace_all) glog._log(LOG_ERROR,"%s",m_err_msg);
		return ERR_API;
    }
	*/
	glog._log(LOG_ERROR,"%s",m_err_msg);
	return ERR_API;
}

void CbLDAP::Release()
{
	// validar si hay atributos
	Attribute_Free();
	EntryFree();
	if (m_blogged) 
	{
		ldap_unbind_s(m_hldap);
	}
	m_hldap = NULL;
}

DWORD CbLDAP::Login(char *host, ULONG port, char *user, char *pass)
{
	ULONG	ulr;
	if (m_hldap == NULL) 
	{
		m_hldap = ldap_init(host,port);
		//m_hldap = ldap_sslinit(host,port,1);
		
		if (m_hldap == NULL) return SetError_Add_ldap_code_msg(LdapGetLastError(),"CbLDAP::Init (%s:%u) ... ",host,port);
	}
	
	ulr = ldap_connect(m_hldap,NULL);
	ULONG version = LDAP_VERSION3;
	//ulr = ldap_set_option(m_hldap, LDAP_OPT_VERSION, &version );
	//ulr = ldap_simple_bind_s(m_hldap,user,pass);
	
	ulr = ldap_bind_s(m_hldap,user,pass,LDAP_AUTH_SIMPLE);
	if (ulr != LDAP_SUCCESS)
	{
		return SetError_Add_ldap_code_msg(ulr,"CbLDAP::Login (%s:%u,%s) ... ",host,port,user);
	}
	m_blogged = true;
	return ERR_OK;

}
//ldap_search_ext_s 

// ULONG ldap_search_ext_s(PCHAR base,ULONG scope,PCHAR filter,PCHAR attrs[], ULONG attrsonly, PLDAPControl* ServerControls, PLDAPControl* ClientControls, struct l_timeval* timeout, ULONG SizeLimit);
//, LDAPMessage** res);


ULONG CbLDAP::Search_ext_s(PCHAR base, ULONG scope, PCHAR filter, PCHAR attrs[], ULONG attrsonly, PLDAPControl *ServerControls, PLDAPControl *ClientControls, l_timeval *timeout, ULONG SizeLimit)
{
	ULONG	ulr;
	ulr = ldap_search_ext_s(m_hldap,base,scope,filter,attrs,attrsonly,ServerControls,ClientControls,timeout,SizeLimit,&m_ldapmessage);
	if (ulr != LDAP_SUCCESS) return SetError_Add_ldap_code_msg(ulr,"CbLDAP::Search_ext_s (%s,%s) ... ",base,filter);
	// tomar el primer attributo 

	return ERR_OK;

}

void CbLDAP::EntryFree()
{
	if (m_ldapmessage != NULL) ldap_msgfree(m_ldapmessage);
	m_ldapmessage = NULL;
	m_ldap_entry = NULL;
}

DWORD CbLDAP::Entry_Next()
{
	//ir a la proxima entrada o a la primera, las entradas no se liberan
	ULONG	ulr;
	LDAPMessage*	ldap_entry;
	if (m_ldap_entry == NULL)
	{
		m_ldap_entry = ldap_first_entry(m_hldap,m_ldapmessage);
		if (m_ldap_entry == NULL) return SetError_Add_ldap_code_msg(LdapGetLastError(),"CbLDAP::Entry_Next ... ");
		return ERR_OK;
	}
	Attribute_Free();
	ldap_entry = m_ldap_entry;
	m_ldap_entry = ldap_next_entry(m_hldap,ldap_entry);
	if (m_ldap_entry == NULL) return SetError_Add_ldap_code_msg(LdapGetLastError(),"CbLDAP::Entry_Next ... ");
	return ERR_OK;
}

void CbLDAP::Attribute_Free()
{
	if (m_attr_name != NULL)  ldap_memfree(m_attr_name);
//	if (m_attr_ber != NULL) ber_vbfree( m_attr_ber, 0 );
	m_attr_name = NULL;
	m_attr_ber = NULL;
}

DWORD CbLDAP::Attribute_Next()
{
	ULONG			ulr;
	BerElement*		attr_ber1;
	if (m_attr_ber == NULL)
	{
		m_attr_name = ldap_first_attribute(m_hldap,m_ldap_entry,&m_attr_ber);
		ulr = LdapGetLastError();
		if (m_attr_name == NULL)  
		{
			if (ulr != LDAP_SUCCESS) return SetError_Add_ldap_code_msg(ulr,"CbLDAP::Attribute_Next ... ");
			else
				return SetError(true,ERR_EOF,"CbLDAP::Attribute_Next ... EOF");
		}
		
		return ERR_OK;			
	}
	//attr_ber1 = m_attr_ber;
	m_attr_name = ldap_next_attribute(m_hldap,m_ldap_entry,m_attr_ber);
	ulr = LdapGetLastError();
	if (m_attr_name == NULL) 
	{
		if (ulr != LDAP_SUCCESS) return SetError_Add_ldap_code_msg(ulr,"CbLDAP::Attribute_Next ... ");
		else
			return SetError(true,ERR_EOF,"CbLDAP::Attribute_Next ... EOF");
	}
	return ERR_OK;
}

DWORD CbLDAP::Attribute_GetName(char *str, WORD max_size)
{
	*str = 0;
	if (m_attr_name == NULL) return SetError(true,ERR_EOF,"CbLDAP::Attribute_GetName ... NULL");
	strncat(str,m_attr_name,max_size);
	return ERR_OK;
}

DWORD CbLDAP::Attribute_GetValue(char* attribute,char *str, WORD max_size)
{
	// Aqui se obtiene un array de valores, y hay que analizar esto
	ULONG	ulr;
	PCHAR*	attr;
	*str = 0;
	attr = ldap_get_values(m_hldap,m_ldap_entry,attribute);
	ulr = LdapGetLastError();
	if (attr == NULL) return SetError_Add_ldap_code_msg(ulr,"CbLDAP::AttributeGetValue (%s) ... ",attribute);
	strncat(str,*attr,max_size);
	ldap_value_free(attr);
	return ERR_OK;
}


DWORD CbLDAP::LoginSSL(char *host, ULONG port, char *user, char *pass)
{
	ULONG	ulr;
	if (m_hldap == NULL) 
	{
		//m_hldap = ldap_init(host,port);
		m_hldap = ldap_sslinit(host,port,1);
		if (m_hldap == NULL) return SetError_Add_ldap_code_msg(LdapGetLastError(),"CbLDAP::Init (%s:%u) ... ",host,port);
	}
	
	ulr = ldap_connect(m_hldap,NULL);
	ULONG version = LDAP_VERSION3;
	//ulr = ldap_set_option(m_hldap, LDAP_OPT_VERSION, &version );
	//ulr = ldap_simple_bind_s(m_hldap,user,pass);
	
	ulr = ldap_bind_s(m_hldap,NULL,NULL,LDAP_AUTH_NEGOTIATE);
	if (ulr != LDAP_SUCCESS)
	{
		return SetError_Add_ldap_code_msg(ulr,"CbLDAP::Login (%s:%u,%s) ... ",host,port,user);
	}
	m_blogged = true;
	return ERR_OK;

}
