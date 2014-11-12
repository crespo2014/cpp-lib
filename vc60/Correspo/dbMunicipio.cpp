// dbMunicipio.cpp: implementation of the CdbMunicipio class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbMunicipio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define INFS_NONE		0
#define INFS_CATALOG	1	//leyendo catalogo

CdbMunicipio::CdbMunicipio()
{
	m_pdbTableInfo = &MunicipioTableInfo;
}

CdbMunicipio::~CdbMunicipio()
{

}

DWORD _stdcall CdbMunicipio::SetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return 0;
}

DWORD _stdcall CdbMunicipio::GetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return 0;
}

DWORD _stdcall CdbMunicipio::SetValue(WORD wdbIndex,HWND hControl)
{
	return 0;
}

DWORD _stdcall CdbMunicipio::GetValue(WORD wdbIndex, HWND hControl)
{
	return 0;
}

DWORD _stdcall CdbMunicipio::Clear()
{
	return 0;
}

DWORD CdbMunicipio::LoadCatalogo(IDBArray *pIdbArray)
{
	DWORD dr;
	if (MunicipioCount == 0)
	{
		m_InfStatus = INFS_CATALOG;
		dr = ProcessInfResource("municipios",this);
	}
	WORD	i;	
	dr = pIdbArray->ResetContent();
	dr = pIdbArray->SetMaxParams(MUNICIPIO_DBCOUNT,MunicipioCount,sizeof(_MUNICIPIO));
	for (i = 0;i<MunicipioTableInfo.dataCount;i++)
	{
		dr = pIdbArray->AddColumn(&MunicipioTableInfo.lpDataInfo[i],NULL);
	}
	for (i=0;i<MunicipioCount;i++)
	{
		Set(&Municipio[i]);
		pIdbArray->AddRow();
		dr = pIdbArray->SetData(i);
	}
	return 0;
}

DWORD CdbMunicipio::GetdbTableInfo(DBTABLEINFO **lpdbTableInfo)
{
	*lpdbTableInfo = &MunicipioTableInfo;
	return 0;
}

DWORD _stdcall CdbMunicipio::OnStart()
{
	return 0;
}

DWORD _stdcall CdbMunicipio::OnNewSection(char* name)
{
	return 0;
}

DWORD _stdcall CdbMunicipio::OnNewValue(char* name,char* value)
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

DWORD _stdcall CdbMunicipio::OnFinish()
{
	return 0;
}

DWORD CdbMunicipio::Set(_MUNICIPIO *pMunicipio)
{
	m_ID = pMunicipio->id;
	strcpy(m_Codigo,pMunicipio->codigo);
	strcpy(m_Nombre,pMunicipio->name);
	m_ProvID = pMunicipio->provincia;
	return 0;
}
