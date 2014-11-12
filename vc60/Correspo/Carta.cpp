// Carta.cpp: implementation of the CCarta class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Carta.h"
#include "resource.h"
#include "correspodb.h"
#include "errorcodes.h" 
#include "common.h"
#include "WindComboBox.h" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define INFS_NONE	1

char	CartaStr[400];

CCarta::CCarta()
{
	// Inicializacion de variables
	m_pdbTableInfo = &CartaTableInfo;
	m_InfStatus = INFS_NONE;
	SetDatabase(&Correspodb);
}

CCarta::~CCarta()
{

}

DWORD _stdcall CCarta::Initialize()
{
	

	m_InfStatus = INFS_NONE;
	return 0;
}

DWORD _stdcall CCarta::SetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	DWORD		dr;
	WORD		dbIndex;
	DBDATAINFO*	dbdatainfo;
	dr = db_GetdbDataInfo(MAKEDBINDEX(CARTAS_TINDEX,wdbIndex),this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	dbIndex = LOWORD(wdbIndex);
	switch(dbIndex)
	{
	case EXPTE_CINDEX:		lstrcpyn(m_Expediente,lpVariant->pzsVal,dbdatainfo->size);break;
	case NOMBRE_CINDEX:		lstrcpyn(m_Nombre,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINDICATO_CINDEX:	lstrcpyn(m_Sindicato,lpVariant->pzsVal,dbdatainfo->size);break;
	case TEMA_CINDEX:		lstrcpyn(m_Tema,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS1_CINDEX:	lstrcpyn(m_Sintesis1,lpVariant->pzsVal,dbdatainfo->size);break;
	case DIRECCION_CINDEX:	lstrcpyn(m_Direccion,lpVariant->pzsVal,dbdatainfo->size);break;
	case FECHAE_CINDEX:		m_FechaEntrada = lpVariant->dbdate;break;
	case PROVINCIA_ID_CINDEX:	lstrcpyn(m_Provincia,lpVariant->pzsVal,dbdatainfo->size);break;
	case RESPUESTA_CINDEX:	lstrcpyn(m_Respuesta,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS2_CINDEX:	lstrcpyn(m_Sintesis2,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS3_CINDEX:	lstrcpyn(m_Sintesis3,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS4_CINDEX:	lstrcpyn(m_Sintesis4,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS5_CINDEX:	lstrcpyn(m_Sintesis5,lpVariant->pzsVal,dbdatainfo->size);break;
	case CARTA_MUNI_CINDEX:	lstrcpyn(m_Muni,lpVariant->pzsVal,dbdatainfo->size);break;
	case SINTESIS_CINDEX:	
		{
			lstrcpyn(m_Sintesis1,lpVariant->pzsVal,71);
			if (strlen(m_Sintesis1) < 70) break;
			lstrcpyn(m_Sintesis2,&lpVariant->pzsVal[70],71);
			if (strlen(m_Sintesis2) < 70) break;
			lstrcpyn(m_Sintesis3,&lpVariant->pzsVal[140],71);
			if (strlen(m_Sintesis3) < 70) break;
			lstrcpyn(m_Sintesis4,&lpVariant->pzsVal[210],71);
			if (strlen(m_Sintesis4) < 70) break;
			lstrcpyn(m_Sintesis5,&lpVariant->pzsVal[70],71);
			break;
		}
	default:
		return ERR_NOTFOUND;
		
	}
	return 0;
}

DWORD _stdcall CCarta::GetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	DWORD		dr;
	DBDATAINFO*	dbdatainfo;
	dr = db_GetdbDataInfo(MAKELONG(wdbIndex,CARTAS_TINDEX),this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	switch(wdbIndex)
	{
	case EXPTE_CINDEX:		lstrcpyn(lpVariant->pzsVal,m_Expediente,dbdatainfo->size);break;
	case NOMBRE_CINDEX:		lstrcpyn(lpVariant->pzsVal,m_Nombre,dbdatainfo->size);break;
	case SINDICATO_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sindicato,dbdatainfo->size);break;
	case TEMA_CINDEX:		lstrcpyn(lpVariant->pzsVal,m_Tema,dbdatainfo->size);break;
	case SINTESIS1_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sintesis1,dbdatainfo->size);break;
	case DIRECCION_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Direccion,dbdatainfo->size);break;
	case FECHAE_CINDEX:		lpVariant->dbdate = m_FechaEntrada;break;
	case PROVINCIA_ID_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Provincia,dbdatainfo->size);break;
	case RESPUESTA_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Respuesta,dbdatainfo->size);break;
	case SINTESIS2_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sintesis2,dbdatainfo->size);break;
	case SINTESIS3_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sintesis3,dbdatainfo->size);break;
	case SINTESIS4_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sintesis4,dbdatainfo->size);break;
	case SINTESIS5_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Sintesis5,dbdatainfo->size);break;
	case CARTA_MUNI_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Muni,dbdatainfo->size);break;
	case SINTESIS_CINDEX:	
		{
			strcpy(lpVariant->pzsVal,m_Sintesis1);
			strcat(lpVariant->pzsVal,m_Sintesis2);
			strcat(lpVariant->pzsVal,m_Sintesis3);
			strcat(lpVariant->pzsVal,m_Sintesis4);
			strcat(lpVariant->pzsVal,m_Sintesis5);
			break;
		}
	default:
		return ERR_NOTFOUND;
		
	}
	return 0;
}

DWORD _stdcall CCarta::Clear()
{
	m_Expediente[0] = 0;
	m_Nombre[0] = 0;
	m_Direccion[0] = 0;
	m_Sintesis1[0] = 0;
	m_Sintesis2[0] = 0;
	m_Sintesis3[0] = 0;
	m_Sintesis4[0] = 0;
	m_Sintesis5[0] = 0;
	m_Sindicato[0] = 0;
	m_Tema[0] = 0;
	ZeroMemory(&m_FechaEntrada,sizeof(DBDATE));
	m_Provincia[0] = 0;
	m_Respuesta[0] = 0;
	m_Muni[0]=0;
	return 0;
}

DWORD CCarta::SaveToDB()
{
	char	SqlStr[300];
	char*			sqlinsert = "insert into correspo (Nombre,direccion,fecha_e,tema,sintesis,sintesis2,sintesis3,sintesis4,sintesis5,sindicato,respuesta,provincia,expte) values ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')";
	char*			sqlupdate = "update correspo set Nombre='%s',direccion='%s',fecha_e='%s',tema='%s',sintesis='%s',sintesis2='%s',sintesis3='%s',sintesis4='%s',sintesis5='%s',sindicato='%s',respuesta='%s',provincia='%s' where expte ='%s'";
	char*			sql;
	char			fecha[10];
	SYSTEMTIME		stime;
	HRESULT			hr;
	ICommandText*	pICommandText	= NULL;
	IRowset*		pIRowset		= NULL;
	long			pRowsCant;
	if (!m_pIdbDatabase) return 0;
	stime.wDay = m_FechaEntrada.day;
	stime.wMonth = m_FechaEntrada.month;
	stime.wYear = m_FechaEntrada.year;
	::GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&stime,NULL,fecha,300);
	if (m_ID != 0) 
		sql = sqlupdate;
	else
		sql = sqlinsert;
	for(;;)
	{
		sprintf(SqlStr,sql,m_Nombre,m_Direccion,fecha,m_Tema,m_Sintesis1,m_Sintesis2,m_Sintesis3,m_Sintesis4,m_Sintesis5,m_Sindicato,m_Respuesta,m_Provincia,m_Expediente);
		db_CharToWChar(SqlStr);
		hr = m_pIdbDatabase->_ICommand()->QueryInterface(IID_ICommandText,(void**)&pICommandText);
		hr = pICommandText->SetCommandText(DBGUID_DEFAULT,(OLECHAR*)SqlStr);
		hr = pICommandText->Release();
		hr = m_pIdbDatabase->_ICommand()->Execute(NULL,IID_IRowset,NULL,&pRowsCant,(IUnknown **)&pIRowset);
		break;
	}
	return ERR_NONE;
}

DWORD CCarta::InitializeControl(DWORD dwdbIndex, HWND hControl)
{
	DWORD	dr;
	WORD	dbIndex;
	DBDATAINFO*	dbdatainfo;
	dwdbIndex = MAKELONG(dwdbIndex,CARTAS_TINDEX);
	dr = db_GetdbDataInfo(dwdbIndex,this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	dbIndex = LOWORD(dwdbIndex);
	switch(dbIndex)
	{
	case EXPTE_CINDEX:
	case NOMBRE_CINDEX:
	case SINDICATO_CINDEX:
	case TEMA_CINDEX:
		{
			::SendMessage(hControl,EM_LIMITTEXT,dbdatainfo->size-1,0);
			break;
		}
	case SINTESIS_CINDEX:
		{
			::SendMessage(hControl,EM_LIMITTEXT,350,0);
			break;
		}
	}
	return 0;
}

DWORD _stdcall CCarta::SetValue(WORD wdbIndex, HWND hControl)
{
	DWORD		dr;
	DBDATAINFO*	dbdatainfo;
	IDBArray*	dbArray = NULL;
	_VARIANT*	variant;
	dr = db_GetdbDataInfo(MAKELONG(wdbIndex,CARTAS_TINDEX),this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	variant = (_VARIANT*)CartaStr;
	switch(wdbIndex)
	{
	case EXPTE_CINDEX:
	case NOMBRE_CINDEX:
	case SINDICATO_CINDEX:
	case TEMA_CINDEX:
	case SINTESIS_CINDEX:
	case DIRECCION_CINDEX:
	case RESPUESTA_CINDEX:
		{
			::GetWindowText(hControl,variant->pzsVal,dbdatainfo->size);
			SetValue(wdbIndex,variant);
			break;
		}
	case PROVINCIA_ID_CINDEX:
		{
			DWORD provincia_id;
			dr = ::SendMessage(hControl,CB_GETIDSEL,(WPARAM)&provincia_id,0);
			if (provincia_id == DB_INVALID_ID) return ERR_INVALID_ID;
			variant->ulVal = provincia_id;
			SetValue(wdbIndex,variant);
			break;
		}
	}
	return ERR_NONE;
}

DWORD CCarta::LoadExpte()
{
	// preparar consulta
	DWORD			dr;
	DWORD			rc;	// Reference count
	long			pRowsCant;
	HRESULT			hr;
	IRowset*		pIRowset		= NULL;
	ICommandText*	pICommandText	= NULL;
	CMemArray		memarray;
	DBDATAINFO*	dbdatainfo;
	dr = db_GetdbDataInfo(MAKELONG(EXPTE_CINDEX,CARTAS_TINDEX),this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	dr = memarray.SetMaxSize(1000);
	if (dr != ERR_NONE) return dr;
	sprintf(CorrespoSQL,"select top 1 * from correspo where ucase(%s) = ucase('%s')",dbdatainfo->name,m_Expediente);
	db_CharToWChar(CorrespoSQL);
	Clear();
	for(;;)
	{
		hr = m_pIdbDatabase->_ICommand()->QueryInterface(IID_ICommandText,(void**)&pICommandText);
		if (hr != S_OK) break;
		hr = pICommandText->SetCommandText(DBGUID_DEFAULT,(OLECHAR*)CorrespoSQL);
		if (hr != S_OK) break;
		hr = m_pIdbDatabase->_ICommand()->Execute(NULL,IID_IRowset,NULL,&pRowsCant,(IUnknown **)&pIRowset);
		if (hr != S_OK) break;
		if (pRowsCant == 0) 
		{
			dr = ERR_NOTFOUND;
			break;
		}
		dr = memarray.SetDBInterfaz(this);
		dr = memarray.SetData(pIRowset,0);
		if (memarray.GetRowCount() != 0) memarray.GetData(0);
		break;
	};
	if (pICommandText) rc = pICommandText->Release();
	if (pIRowset) rc = pIRowset->Release();
	if ((hr == S_OK) && (dr == ERR_NONE)) return ERR_NONE;
	if (hr != S_OK) dr = ERR_OLEDBFAIL;
	return dr;
}

DWORD _stdcall CCarta::GetValue(WORD wdbIndex, HWND hControl)
{
	DWORD		dr;
	_VARIANT*	pvariant;
	_VARIANT	muni;
	pvariant = (_VARIANT*)CartaStr;
	GetValue(wdbIndex,pvariant);
	switch(wdbIndex)
	{
	case EXPTE_CINDEX:
	case NOMBRE_CINDEX:
	case SINDICATO_CINDEX:
	case TEMA_CINDEX:
	case SINTESIS_CINDEX:
	case DIRECCION_CINDEX:
	case RESPUESTA_CINDEX:
		{
			::SetWindowText(hControl,CartaStr);
			break;
		}
	case PROVINCIA_ID_CINDEX:
		{
			if (m_Muni[0]==0)
			{
				SendMessage(hControl,CB_SETIDSEL,DB_INVALID_ID,0);
				break;
			}
			// Obtener el memarray
			IDBArray*	pdbArray;
			DWORD		RowIndex;
			SendMessage(hControl,UM_GET_INTERFAZ,(WPARAM)IDBARRAY_NAME,(LPARAM)&pdbArray);
			if (pdbArray == NULL) return ERR_NOINTERFACE;
			muni.iVal = (m_Muni[0]-0x30)*10+ (m_Muni[1]-0x30);
			dr = pdbArray->Find(0,PROV_CODIGO_CINDEX,&muni,&RowIndex);
			if (dr != ERR_NONE) return dr;
			SendMessage(hControl,CB_SETROWSEL,RowIndex,0);
			break;
		}
	}
	return 0;	
}

DWORD _stdcall CCarta::OnStart()
{
	/*
	switch(m_InfStatus)
	{
	}
	*/
	return 0;
}

DWORD _stdcall CCarta::OnNewSection(char* name)
{
	return 0;
}

DWORD _stdcall CCarta::OnNewValue(char* name,char* value)
{
	/*
	int val;
	switch(m_InfStatus)
	{
	}
	*/
	return 0;
}

DWORD _stdcall CCarta::OnFinish()
{
	return 0;
}

DWORD _stdcall CCarta::GetItemText(ITEM_DATA *lpItemData)
{
	DWORD	dr;
	WORD	ColumnIndex;
	char*	str;
	DWORD	Index = LOWORD(lpItemData->dwdbIndex);
	DWORD	RowIndex = lpItemData->dwRowIndex;
	lpItemData->pzsText = CartaStr;
	lpItemData->pzsText[0]=0;
	switch (Index)
	{
	case SINTESIS_CINDEX:
		{
			if (RowIndex == INVALID_INDEX) break;
			dr = m_lpMemArray->GetColumn(MAKEDBINDEX(CARTAS_TINDEX,SINTESIS1_CINDEX),&ColumnIndex);
			dr = m_lpMemArray->GetDataPrtAt(RowIndex,ColumnIndex,(void**)&str);
			strcpy(lpItemData->pzsText,str);	
			dr = m_lpMemArray->GetColumn(MAKELONG(SINTESIS2_CINDEX,CARTAS_TINDEX),&ColumnIndex);
			dr = m_lpMemArray->GetDataPrtAt(RowIndex,ColumnIndex,(void**)&str);
			if (dr == ERR_NONE)	strcat(lpItemData->pzsText,str);
			dr = m_lpMemArray->GetColumn(MAKELONG(SINTESIS3_CINDEX,CARTAS_TINDEX),&ColumnIndex);
			dr = m_lpMemArray->GetDataPrtAt(RowIndex,ColumnIndex,(void**)&str);
			if (dr == ERR_NONE)	strcat(lpItemData->pzsText,str);
			dr = m_lpMemArray->GetColumn(MAKELONG(SINTESIS4_CINDEX,CARTAS_TINDEX),&ColumnIndex);
			dr = m_lpMemArray->GetDataPrtAt(RowIndex,ColumnIndex,(void**)&str);
			if (dr == ERR_NONE) strcat(lpItemData->pzsText,str);
			dr = m_lpMemArray->GetColumn(MAKELONG(SINTESIS5_CINDEX,CARTAS_TINDEX),&ColumnIndex);
			dr = m_lpMemArray->GetDataPrtAt(RowIndex,ColumnIndex,(void**)&str);
			if (dr == ERR_NONE) strcat(lpItemData->pzsText,str);
			break;
		}
	}
	return 0;
}

DWORD CCarta::GetdbTableInfo(DBTABLEINFO **lpdbTableInfo)
{
	*lpdbTableInfo = &CartaTableInfo;
	return 0;
}
