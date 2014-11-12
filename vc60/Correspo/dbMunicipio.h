// dbMunicipio.h: interface for the CdbMunicipio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMUNICIPIO_H__9DC44373_D3EE_4306_AFA7_2ADC2AF4126D__INCLUDED_)
#define AFX_DBMUNICIPIO_H__9DC44373_D3EE_4306_AFA7_2ADC2AF4126D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBCommon.h"
#include "CorrespoDef.h"

class CdbMunicipio	:public CdbClass,
					 private IinfProcess
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
	
	BYTE	m_InfStatus;

	// Campos del municipio
	DWORD	m_ID;
	char	m_Nombre[26];
	DWORD	m_ProvID;
	char	m_Codigo[5];

public:
	DWORD Set(_MUNICIPIO* pMunicipio);
	DWORD LoadCatalogo(IDBArray *pIdbArray);
	CdbMunicipio();
	virtual ~CdbMunicipio();

};

#endif // !defined(AFX_DBMUNICIPIO_H__9DC44373_D3EE_4306_AFA7_2ADC2AF4126D__INCLUDED_)
