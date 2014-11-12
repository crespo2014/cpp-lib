// dbProvincia.cpp: implementation of the CdbProvincia class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbProvincia.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


#define INFS_NONE		0
#define INFS_CATALOG	1	//leyendo catalogo


CdbProvincia::CdbProvincia()
{
	m_pdbTableInfo = &ProvinciaTableInfo;
}

CdbProvincia::~CdbProvincia()
{

}

DWORD _stdcall CdbProvincia::SetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return 0;
}

DWORD _stdcall CdbProvincia::GetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	DWORD		dr;
	DBDATAINFO*	dbdatainfo;
	dr = db_GetdbDataInfo(MAKELONG(wdbIndex,PROVINCIA_TINDEX),this,&dbdatainfo);
	if (dr != ERR_NONE) return dr;
	switch(wdbIndex)
	{
	case DB_ID_CINDEX:		lpVariant->ulVal = m_ID;break;
	case PROV_NAME_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Nombre,dbdatainfo->size);break;
	case PROV_ABREV_CINDEX:	lstrcpyn(lpVariant->pzsVal,m_Abrev,dbdatainfo->size);break;
	case PROV_DBNAME_CINDEX:lstrcpyn(lpVariant->pzsVal,m_OldName,dbdatainfo->size);break;
	case PROV_CODIGO_CINDEX:lpVariant->bVal = m_Codigo;break;
	default:
		return ERR_NOTFOUND;
		
	}
	return 0;
}

DWORD _stdcall CdbProvincia::SetValue(WORD wdbIndex,HWND hControl)
{
	return 0;
}

DWORD _stdcall CdbProvincia::GetValue(WORD wdbIndex, HWND hControl)
{
	return 0;
}

DWORD _stdcall CdbProvincia::Clear()
{
	return 0;
}

DWORD CdbProvincia::LoadCatalogo(IDBArray *pIdbArray)
{
	DWORD dr;
	if (ProvinciaCount == 0)
	{
		m_InfStatus = INFS_CATALOG;
		dr = ProcessInfResource("provincias",this);
	}
	WORD	i;	
	dr = pIdbArray->ResetContent();
	dr = pIdbArray->SetMaxParams(PROVINCIA_DBCOUNT,ProvinciaCount,sizeof(_PROVINCIA));
	for (i = 0;i<ProvinciaTableInfo.dataCount;i++)
	{
		dr = pIdbArray->AddColumn(&ProvinciaTableInfo.lpDataInfo[i],NULL);
	}
	for (i=0;i<ProvinciaCount;i++)
	{
		Set(&Provincia[i]);
		pIdbArray->AddRow();
		dr = pIdbArray->SetData(i);
	}
	return 0;
}

DWORD _stdcall CdbProvincia::OnStart()
{
	/*
	switch(m_InfStatus)
	{
//	case INFS_CATALOG: m_provinciaCount = 0;break; 
	}
	*/
	return 0;
}

DWORD _stdcall CdbProvincia::OnNewSection(char* name)
{
	return 0;
}

DWORD _stdcall CdbProvincia::OnNewValue(char* name,char* value)
{
	int val;
	switch(m_InfStatus)
	{
	case INFS_CATALOG: 
		{
			sscanf(value,"%d",&val);
			if (strcmp(name,"id")==0) 
			{
				Provincia[ProvinciaCount].id = val;
				(ProvinciaCount)++;
				break;
			}
			if (ProvinciaCount == 0) return 0;
			if (strcmp(name,"cod")==0) {Provincia[ProvinciaCount-1].cod = val;break;}
			if (strcmp(name,"name")==0) {lstrcpyn(Provincia[ProvinciaCount-1].name,value,25);break;}
			if (strcmp(name,"dbname")==0) {lstrcpyn(Provincia[ProvinciaCount-1].dbname,value,16);break;}
			if (strcmp(name,"abrev")==0) {lstrcpyn(Provincia[ProvinciaCount-1].abrev,value,4);break;}
			if (strcmp(name,"abrev")==0) {lstrcpyn(Provincia[ProvinciaCount-1].abrev,value,4);break;}
			break;
		}
	}
	return 0;
}

DWORD _stdcall CdbProvincia::OnFinish()
{
	return 0;
}

DWORD CdbProvincia::GetdbTableInfo(DBTABLEINFO **lpdbTableInfo)
{
	*lpdbTableInfo = &ProvinciaTableInfo;
	return 0;
}

DWORD CdbProvincia::Set(_PROVINCIA *pProvincia)
{
	strcpy(m_Abrev,pProvincia->abrev);
	strcpy(m_Nombre,pProvincia->name);
	strcpy(m_OldName,pProvincia->dbname);
	m_Codigo = pProvincia->cod;
	m_ID = pProvincia->id;
	return 0;
}

//DEL DWORD CdbProvincia::LoadCatalogo()
//DEL {
//DEL 	m_InfStatus = INFS_CATALOG;
//DEL 	return ProcessInfResource("provincias",this);
//DEL }
