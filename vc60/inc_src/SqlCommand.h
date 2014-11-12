// SqlCommand.h: interface for the CSqlCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_)
#define AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqlconnection.h"

class CSqlCommand : public CbObject
{
public:
	BOOL  IsValid()	{ return (m_henv != NULL);};
	BOOL  IsEOF()	{ return m_beof;};
	DWORD Make_ErrorSTR(char* msg,SQLRETURN	sr);
	DWORD NextRow();
	DWORD GetData(SQLUSMALLINT colindex,SQLSMALLINT datatype,SQLPOINTER dataptr,SQLINTEGER datasize,SQLINTEGER* curr_size = NULL);
	DWORD GetColumnNameType(SQLUSMALLINT index,char* name, SQLSMALLINT*  name_size,SQLSMALLINT* datatype,SQLUINTEGER* datasize);
	DWORD Execute(char* sql_cmd);
	DWORD Release();
	DWORD Initialize();
	void SetConnection(CSqlConnection* pSqlConnection);
	CSqlCommand(CSqlConnection*	pSqlConnection);
	CSqlCommand();
	virtual ~CSqlCommand();

private:
	CSqlConnection*	m_sqlconnection;
	SQLHENV	m_henv;
	BOOL	m_beof;
	
public:
	DWORD InvalidHandle(char* fnc_name) { return SetError(true,ERR_HANDLE,"%s failed with invalid sql handle call Initialize Before",fnc_name); };
	DWORD ResetAll();
	void Init();
	DWORD RowCount(SQLINTEGER * pRowCount);
	DWORD log_Row();
	DWORD ResetCursor();
	DWORD SetAttribute(SQLINTEGER Attribute,SQLPOINTER ValuePtr,SQLINTEGER StringLength);
	DWORD BindParameter(SQLUSMALLINT index,SQLSMALLINT  inout_type,SQLSMALLINT c_type,SQLSMALLINT sql_type,SQLUINTEGER col_size,SQLSMALLINT dec_digits,SQLPOINTER var_ptr,SQLINTEGER var_size,SQLINTEGER *val_len = NULL);
	DWORD Execute();
	DWORD Prepared(char* sql);
	char* GetErrorStr(){return m_err_msg;};
	DWORD BindColumn(SQLUSMALLINT col,SQLSMALLINT type,SQLPOINTER varptr,SQLINTEGER varsize,SQLINTEGER * vallen);
	
};

#endif // !defined(AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_)
