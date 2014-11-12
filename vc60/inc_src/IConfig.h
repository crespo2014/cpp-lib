// IConfig.h: interface for the IConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICONFIG_H__C4B1EDBC_76C6_401C_B3DD_F8AF6CC37370__INCLUDED_)
#define AFX_ICONFIG_H__C4B1EDBC_76C6_401C_B3DD_F8AF6CC37370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

// tiene que haber una forma de decidir si la memoria se mantendra inalterada al volver del metodo

class IConfig  
{
public:
	virtual	DWORD	OnSection(char* psection,bool *pbRelease) = 0;
	virtual	DWORD	OnParam(char* pname,bool *pbRelease) = 0;
	virtual	DWORD	OnValue(char* pval,bool *pbRelease) = 0;
};

#endif // !defined(AFX_ICONFIG_H__C4B1EDBC_76C6_401C_B3DD_F8AF6CC37370__INCLUDED_)
