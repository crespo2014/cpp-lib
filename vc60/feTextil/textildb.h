// textildb.h: interface for the Ctextildb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTILDB_H__DBFFCAB2_4D47_43A9_AF2D_9769523C9E8E__INCLUDED_)
#define AFX_TEXTILDB_H__DBFFCAB2_4D47_43A9_AF2D_9769523C9E8E__INCLUDED_

#include "DBCommon.h"
#include "MemArray.h"	// Added by ClassView
#include "windgrid.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTextildb	: public IdbDatabase   
{
	ICommand* _stdcall _ICommand();
	ICommand*		m_lpICommand;
public:
	DWORD LoadCatalogo(WORD wTableIndex);
	DWORD Initialize();
	DWORD LoadCatalogo(WORD wTableIndex,IDBArray** ppIdbArray);
	DWORD Close();
	DWORD Open();
public:
	CTextildb();
	virtual ~CTextildb();

};


extern CTextildb	Textildb;
extern char			TextilSQL[];

extern DBTABLEINFO	ClienteTI;

#endif // !defined(AFX_TEXTILDB_H__DBFFCAB2_4D47_43A9_AF2D_9769523C9E8E__INCLUDED_)
