// SqlConnection.h: interface for the CSqlConnection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLCONNECTION_H__7E79F1FA_141E_494A_8BE5_9278112CB298__INCLUDED_)
#define AFX_SQLCONNECTION_H__7E79F1FA_141E_494A_8BE5_9278112CB298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqldriver.h"

#define SQL_CON_LOG_ERROR		LogError(fnc_name,__LINE__,
#define SQL_CON_INVALID_HANDLE	LOG_TERROR	ERR_HANDLE,"Invalid Handle valued call Initialize Before");


class CSqlConnection  : public CbObject
{
public:
	DWORD LogError(char *fnc_name, DWORD line, SQLRETURN sr, char *format, ...);
	void Init();
	DWORD SetAttribute(SQLINTEGER Attribute,SQLPOINTER ValuePtr,SQLINTEGER StringLength);
	DWORD BrowseConnect(char* InConnectionString,char* OutConnectionString,SQLSMALLINT BufferLength,SQLSMALLINT* StringLength2Ptr);
	DWORD Disconnect();
	DWORD Transation(SQLSMALLINT operation);
	DWORD TransationEnable(BOOL bstate);
	DWORD Release();
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
