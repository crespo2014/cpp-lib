// Carta.h: interface for the CCarta class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARTA_H__FE8B09F6_D476_41E6_A2AD_04F041FF6899__INCLUDED_)
#define AFX_CARTA_H__FE8B09F6_D476_41E6_A2AD_04F041FF6899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBCommon.h"
#include "memarray.h"
#include "Wind.h"
#include "CorrespoDef.h"


class CCarta  : public CdbClass,
				private IinfProcess
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

private:
	// IinfProcess
	virtual DWORD _stdcall OnStart();
	virtual DWORD _stdcall OnNewSection(char* name);	
	virtual DWORD _stdcall OnNewValue(char* name,char* value);
	virtual DWORD _stdcall OnFinish();

//	char		m_str[360];
	// Campos de la carta
	BOOL	m_OnModified;	// Indica que los valores an sido alterados
	char	m_Expediente[7];
	char	m_Nombre[31];
	char	m_Direccion[41];
	char	m_Sintesis1[71];
	char	m_Sintesis2[71];
	char	m_Sintesis3[71];
	char	m_Sintesis4[71];
	char	m_Sintesis5[71];
	char	m_SindicatoAbrev[4];
	char	m_Tema[6];
	DBDATE	m_FechaEntrada;
	DBDATE	m_FechaEnvio;
	DBDATE	m_FechaRespuesta;
	char	m_Provincia[16];
	char	m_Respuesta[4];
	char	m_Muni[5];
	char	m_Clasificacion;
	char	m_Codigo[4];
	char	m_ProvinciaAbrev[4];
	char	m_Codigo1[4];
	char	m_Codigo2[4];
	char	m_Codigo3[4];
	char	m_Sindicato[21];
	char	m_Municipio[25];
	char	m_NoMes[3];
	DWORD	m_ProvinciaID;


	// Base de datos
	CMemArray*	m_lpMemArray;
	DBDATAINFO	m_DataInfo[CARTA_DBCOUNT];
	//
	BYTE		m_provinciaCount;
	BYTE		m_InfStatus;

public:
	
	DWORD SaveToDB();
	DWORD _stdcall Initialize();
	CCarta();
	virtual ~CCarta();
	DWORD LoadExpte();
	DWORD InitializeControl(DWORD dwdbIndex,HWND hControl);

};

#endif // !defined(AFX_CARTA_H__FE8B09F6_D476_41E6_A2AD_04F041FF6899__INCLUDED_)
