// SqlDriver.h: interface for the CSqlDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLDRIVER_H__501B629E_473E_49CC_B31A_5A8E4FFC909E__INCLUDED_)
#define AFX_SQLDRIVER_H__501B629E_473E_49CC_B31A_5A8E4FFC909E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <windows.h>
#include <Sql.h>
#include <Sqlext.h>
#include "bobject.h"
#include "logclient.h"

class CSqlDriver : public CbObject
{
public:
	void Init();
	DWORD Make_ErrorSTR(char *msg);
	BOOL  IsValid()			{ return (m_henv != NULL);};
	DWORD SetVersion(DWORD version);
	DWORD CreateConnection(SQLHENV* psqlenv);
	DWORD Release();
	DWORD Initialize();
	CSqlDriver();
	virtual ~CSqlDriver();
private:
	SQLHENV m_henv;
};

#endif // !defined(AFX_SQLDRIVER_H__501B629E_473E_49CC_B31A_5A8E4FFC909E__INCLUDED_)
