// Cliente.h: interface for the CCliente class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTE_H__6C459332_03B4_40DF_859C_DA3D7CB1E5BF__INCLUDED_)
#define AFX_CLIENTE_H__6C459332_03B4_40DF_859C_DA3D7CB1E5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBCommon.h"
#include "memarray.h"
#include "Wind.h"

class CCliente :	public CdbClass
					//private IinfProcess 
{
public:
	// IDBClass  Interfaz
	DWORD _stdcall GetdbTableInfo(DBTABLEINFO** lpdbTableInfo);
	DWORD _stdcall GetItemText(ITEM_DATA *lpItemData);
	DWORD _stdcall SetValue(WORD wdbIndex,_VARIANT* lpVariant);
	DWORD _stdcall GetValue(WORD wdbIndex,_VARIANT* lpVariant);
	DWORD _stdcall SetValue(WORD wdbIndex,HWND hControl);
	DWORD _stdcall Clear();
	DWORD _stdcall GetValue(WORD wdbIndex, HWND hControl);

	CCliente();
	virtual ~CCliente();
private:
	DWORD	m_id;
	char	m_empresa[255];
	char	m_nombre[100];
	char	m_cargo[100];
	char	m_direccion[210];
	char	m_telefono[50];
	char	m_fax[50];
	char	m_email[50];
	char	m_bancoUSD[50];
	char	m_bancoMN[50];
	char	m_cuentaUSD[50];
	char	m_cuentaMN[50];
	char	m_observ[210];		//observaciones



};

#endif // !defined(AFX_CLIENTE_H__6C459332_03B4_40DF_859C_DA3D7CB1E5BF__INCLUDED_)
