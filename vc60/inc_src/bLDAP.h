// bLDAP.h: interface for the CbLDAP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLDAP_H__3BE3F9F8_ECB8_4411_B8DC_EA5C3AA9B5CC__INCLUDED_)
#define AFX_BLDAP_H__3BE3F9F8_ECB8_4411_B8DC_EA5C3AA9B5CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"

//#include <ntldap.h>
#include <winldap.h>
//#include <winber.h>


// incluir Wldap32.lib

class CbLDAP : public CbObject  
{
public:
	DWORD LoginSSL(char *host, ULONG port, char *user, char *pass);
	DWORD Attribute_GetValue(char* attribute,char* str, WORD max_size);
	DWORD Attribute_GetName(char* str, WORD max_size);
	DWORD Attribute_Next();
	void Attribute_Free();
	DWORD Entry_Next();
	void EntryFree();
	ULONG Search_ext_s(PCHAR base,ULONG scope,PCHAR filter,PCHAR attrs[], ULONG attrsonly, PLDAPControl* ServerControls, PLDAPControl* ClientControls, struct l_timeval* timeout, ULONG SizeLimit);
	DWORD Login(char* host,ULONG port, char* user, char* pass);
	void Release();
	DWORD SetError_Add_ldap_code_msg(ULONG lr, char *format, ...);
	DWORD Init(char* hostName, ULONG port);
	CbLDAP();
	virtual ~CbLDAP();

private:
	LDAP*	m_hldap;
	BOOL	m_blogged;
	LDAPMessage*	m_ldapmessage;
	LDAPMessage*	m_ldap_entry;
	PCHAR			m_attr_name;
	BerElement*		m_attr_ber;
	//berval*		m_attr_ber;

};

#endif // !defined(AFX_BLDAP_H__3BE3F9F8_ECB8_4411_B8DC_EA5C3AA9B5CC__INCLUDED_)



