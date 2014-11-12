// dbProvincia.h: interface for the CdbProvincia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBPROVINCIA_H__17BA702D_A646_4C1D_BDB7_B1E0EECA0AC2__INCLUDED_)
#define AFX_DBPROVINCIA_H__17BA702D_A646_4C1D_BDB7_B1E0EECA0AC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBCommon.h"
#include "CorrespoDef.h"

class CdbProvincia : public CdbClass,
					 public IinfProcess
{
	// IDBClass  Interfaz
	DWORD _stdcall GetdbTableInfo(DBTABLEINFO** lpdbTableInfo);
	DWORD _stdcall SetValue(WORD wdbIndex,_VARIANT* lpVariant);
	DWORD _stdcall GetValue(WORD wdbIndex,_VARIANT* lpVariant);
	DWORD _stdcall SetValue(WORD wdbIndex,HWND hControl);
	DWORD _stdcall GetValue(WORD wdbIndex, HWND hControl);
	DWORD _stdcall Clear();

	// IinfProcess
	DWORD _stdcall OnStart();
	DWORD _stdcall OnNewSection(char* name);	
	DWORD _stdcall OnNewValue(char* name,char* value);
	DWORD _stdcall OnFinish();
	
	BYTE			m_InfStatus;
	// Datos
	char	m_Abrev[4];
	char	m_Nombre[26];
	BYTE	m_Codigo;
	char	m_OldName[17];

public:
	
	DWORD LoadCatalogo(IDBArray* pIdbArray);
	CdbProvincia();
	virtual ~CdbProvincia();

private:
	DWORD Set(_PROVINCIA* pProvincia);
};

#endif // !defined(AFX_DBPROVINCIA_H__17BA702D_A646_4C1D_BDB7_B1E0EECA0AC2__INCLUDED_)
