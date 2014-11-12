// SqlConnection.h: interface for the CSqlConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLCONNECTION_H__7E79F1FA_141E_494A_8BE5_9278112CB298__INCLUDED_)
#define AFX_SQLCONNECTION_H__7E79F1FA_141E_494A_8BE5_9278112CB298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqldriver.h"

class CSqlConnection  : public CbObject
{
public:
	void Init();
	DWORD SetAttribute(SQLINTEGER Attribute,SQLPOINTER ValuePtr,SQLINTEGER StringLength);
	DWORD BrowseConnect(char* InConnectionString,char* OutConnectionString,SQLSMALLINT BufferLength,SQLSMALLINT* StringLength2Ptr);
	DWORD Disconnect();
	DWORD Transation(SQLSMALLINT operation);
	DWORD TransationEnable(BOOL bstate);
	DWORD Release();
	DWORD Make_ErrorSTR(char *msg,SQLRETURN	sr);
	DWORD ConnectTo(char* datasource,char* user,char* password);
	DWORD CreateCommand(SQLHENV *psqlenv);
	DWORD Initialize();

	DWORD Transation_Commit()	{ return Transation(SQL_COMMIT);	};
	DWORD Transation_RollBack() { return Transation(SQL_ROLLBACK);	};
	BOOL IsConnected()			{ return m_connect;					};

	void SetDriver(CSqlDriver* pSqlDriver);
	CSqlConnection(CSqlDriver* pSqlDriver);
	CSqlConnection();

	virtual ~CSqlConnection();

private:
	CSqlDriver*	m_sqldriver;
	SQLHENV		m_henv;
	BOOL		m_connect;
	BOOL	m_ontransation;			// indica que esta habilitada una trnsacion si se destruye la clase hay que hacer roolback

};

#endif // !defined(AFX_SQLCONNECTION_H__7E79F1FA_141E_494A_8BE5_9278112CB298__INCLUDED_)
