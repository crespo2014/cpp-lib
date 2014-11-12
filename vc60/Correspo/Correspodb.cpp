// Correspodb.cpp: implementation of the CCorrespodb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Correspodb.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCorrespodb Correspodb;
char		CorrespoSQL[2000];

// Provincias
_PROVINCIA	Provincia[15];
DWORD		ProvinciaCount;
DBDATAINFO  ProvinciaDataInfo[PROVINCIA_DBCOUNT];
DBTABLEINFO	ProvinciaTableInfo;

//Municipios
_MUNICIPIO	Municipio[200];
DWORD		MunicipioCount;
DBDATAINFO  MunicipioDataInfo[MUNICIPIO_DBCOUNT];
DBTABLEINFO	MunicipioTableInfo;


// Cartas
DBDATAINFO  CartaDataInfo[CARTA_DBCOUNT];
DBTABLEINFO	CartaTableInfo;


CCorrespodb::CCorrespodb()
{
	m_lpICommand = NULL;
	//
	m_dbAProvincia.SetDBInterfaz(&m_dbProvincia);
	m_dbAProvincia.SetExtraDataSize(MA_GRID_ROW_DATA,sizeof(GROWINFO));
	m_dbAProvincia.SetExtraDataSize(MA_GRID_COLUMN_DATA,sizeof(GCOLUMNINFO));
	ProvinciaTableInfo.lpDataInfo = ProvinciaDataInfo; 
	//
	m_dbAMunicipio.SetDBInterfaz(&m_dbCMunicipio);
	m_dbAMunicipio.SetExtraDataSize(MA_GRID_ROW_DATA,sizeof(GROWINFO));
	m_dbAMunicipio.SetExtraDataSize(MA_GRID_COLUMN_DATA,sizeof(GCOLUMNINFO));
	MunicipioTableInfo.lpDataInfo = MunicipioDataInfo;
	//
	CartaTableInfo.lpDataInfo = CartaDataInfo;
	MunicipioTableInfo.lpDataInfo = MunicipioDataInfo;
}

CCorrespodb::~CCorrespodb()
{
	Close();
}

DWORD CCorrespodb::Open()
{
	SetCursor(LoadCursor(NULL,IDC_WAIT));
	DWORD					dr;
	DWORD					rc;
	HRESULT					hr;
	IDataInitialize *		pIDataInitialize    = NULL;
	IDBInitialize *			pIDBInitialize      = NULL;
	IDBCreateSession*		pIDBCreateSession	= NULL;
	IUnknown *				pUnkSession			= NULL;
	ICommandText*			pICommandText		= NULL;
	IDBCreateCommand*		pICreateCommand		= NULL;
	char					cConnectionStr[500];
	strcpy(cConnectionStr,"Driver={Microsoft dBase Driver (*.dbf)};FIL=dBase 5;DBQ=C:\\CORRESPO OK;DriverId=533;");
	db_CharToWChar(cConnectionStr);
	for(;;)
	{
		dr = ERR_OLEDBFAIL;
		hr = CoCreateInstance(CLSID_MSDAINITIALIZE,NULL,CLSCTX_INPROC_SERVER,IID_IDataInitialize,(VOID **)&pIDataInitialize);
		if (hr != S_OK) break;
		hr = pIDataInitialize->GetDataSource(NULL,CLSCTX_INPROC_SERVER,(LPCOLESTR)cConnectionStr,IID_IDBInitialize,(IUnknown **)&pIDBInitialize);
		if (hr != S_OK) break;
		hr = pIDBInitialize->Initialize();
		if (hr != S_OK) break;
		hr = pIDBInitialize->QueryInterface(IID_IDBCreateSession, (void**)&pIDBCreateSession);
		if (hr != S_OK) break;
		hr = pIDBCreateSession->CreateSession(NULL,IID_IOpenRowset,&pUnkSession );
		if (hr != S_OK) break;
		hr = pUnkSession->QueryInterface(IID_IDBCreateCommand,(void**)&pICreateCommand);
		if (hr != S_OK) break;
		hr = pICreateCommand->CreateCommand(NULL,IID_ICommand,(IUnknown**)&m_lpICommand);
		if (hr != S_OK) break;
		dr = ERR_NONE;
		break;
	};
	if (pIDataInitialize)	rc = pIDataInitialize->Release();
	if (pIDBInitialize)		rc = pIDBInitialize->Release();
	if (pIDBCreateSession)	rc = pIDBCreateSession->Release();
	if (pUnkSession)		rc = pUnkSession->Release();
	if (pICreateCommand)	rc = pICreateCommand->Release();
	if (hr != S_OK) 
	{
		if (m_lpICommand)		rc = m_lpICommand->Release();
		m_lpICommand = NULL;
	}
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	return ERR_OLEDBFAIL;
}

ICommand* _stdcall CCorrespodb::_ICommand()
{
	if (m_lpICommand == NULL) 
	{
		Open();
	}
	return m_lpICommand;
}

DWORD CCorrespodb::Close()
{
	HRESULT	hr;
	if (m_lpICommand) hr = m_lpICommand->Release();
	m_lpICommand = NULL;
	return ERR_NONE;
}

DWORD CCorrespodb::LoadCatalogo(WORD wTableIndex, IDBArray **ppIdbArray)
{
	DWORD	dr;
	dr = LoadCatalogo(wTableIndex);
	if (dr != ERR_NONE) return dr;
	switch(wTableIndex)
	{
	case PROVINCIA_TINDEX:*ppIdbArray = &m_dbAProvincia;break;
		
	}
	return 0;
}

DWORD CCorrespodb::Initialize()
{
	DWORD	dr;
	dr = db_GetdbTableInfoFromResource("Provincia_dbTableInfo",&ProvinciaTableInfo);
	dr = db_GetdbTableInfoFromResource("Cartas_dbTableInfo",&CartaTableInfo);
	ProvinciaCount = 0;
	return dr;
}

//DEL DWORD CCorrespodb::QueryCatalogo(WORD wTableIndex, IDBClass **ppIdbClass)
//DEL {
//DEL 	return 0;
//DEL }

/*
	Carga el catalogo correspondiente en el memarray destinado para el.
*/

DWORD CCorrespodb::LoadCatalogo(WORD wTableIndex)
{
	DWORD	rowcount;
	switch(wTableIndex)
	{
	case PROVINCIA_TINDEX:
		{
			rowcount  = m_dbAProvincia.GetRowCount();
			if (rowcount == 0)
			{
				m_dbProvincia.LoadCatalogo(&m_dbAProvincia);
			}
			break;
		}
	}
	return 0;
}
