// Correspodb.h: interface for the CCorrespodb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRESPODB_H__E783A6CD_715C_49B5_A77A_53697B8710F3__INCLUDED_)
#define AFX_CORRESPODB_H__E783A6CD_715C_49B5_A77A_53697B8710F3__INCLUDED_

#include "dbProvincia.h"	// Added by ClassView
#include "dbMunicipio.h"	// Added by ClassView
#include "DBCommon.h"
#include "carta.h"
#include "MemArray.h"	// Added by ClassView
#include "windgrid.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCorrespodb : public IdbDatabase 
{
	ICommand* _stdcall _ICommand();
	ICommand*		m_lpICommand;
	CdbProvincia	m_dbProvincia;
	CdbMunicipio	m_dbCMunicipio;
	CMemArray		m_dbAProvincia;
	CMemArray		m_dbAMunicipio;
//	BOOL			m_bOnCatProvincias;	// Indica si el catalogo de provincias ya se leyo
public:
	DWORD LoadCatalogo(WORD wTableIndex);
	DWORD Initialize();
	DWORD LoadCatalogo(WORD wTableIndex,IDBArray** ppIdbArray);
	DWORD Close();
	DWORD Open();
	CCorrespodb();
	virtual ~CCorrespodb();
	CCarta	m_carta;
};

extern CCorrespodb	Correspodb;
extern char			CorrespoSQL[];

#endif // !defined(AFX_CORRESPODB_H__E783A6CD_715C_49B5_A77A_53697B8710F3__INCLUDED_)
