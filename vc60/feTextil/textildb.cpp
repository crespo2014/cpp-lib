// textildb.cpp: implementation of the Ctextildb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "textildb.h"
#include "fetextildef.h"

/*
	Aqui se declaran todas las variables globales del proyecto
	las estructuras de datos.
*/

// Clientes
DBDATAINFO  ClienteDI[CLIENTE_DBCOUNT];
DBTABLEINFO	ClienteTI;

CTextildb	Textildb;
char		TextilSQL[2000];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextildb::CTextildb()
{
	ClienteTI.lpDataInfo = ClienteDI;
}

CTextildb::~CTextildb()
{

}

DWORD CTextildb::Open()
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
	strcpy(cConnectionStr,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=bd1.mdb;Persist Security Info=False");
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

ICommand* _stdcall CTextildb::_ICommand()
{
	if (m_lpICommand == NULL) 
	{
		Open();
	}
	return m_lpICommand;
}

DWORD CTextildb::Close()
{
	HRESULT	hr;
	if (m_lpICommand) hr = m_lpICommand->Release();
	m_lpICommand = NULL;
	return ERR_NONE;
}

DWORD CTextildb::LoadCatalogo(WORD wTableIndex, IDBArray **ppIdbArray)
{
	DWORD	dr;
	dr = LoadCatalogo(wTableIndex);
	if (dr != ERR_NONE) return dr;
	switch(wTableIndex)
	{
//	case PROVINCIA_TINDEX:*ppIdbArray = &m_dbAProvincia;break;
		
	}
	return 0;
}

DWORD CTextildb::Initialize()
{
	DWORD	dr;
	dr = db_GetdbTableInfoFromResource("CLIENTE_TI",&ClienteTI);
	
	return dr;
}

/*
	Carga el catalogo correspondiente en el memarray destinado para el.
*/

DWORD CTextildb::LoadCatalogo(WORD wTableIndex)
{
	DWORD	rowcount;
	switch(wTableIndex)
	{
		/*
	case PROVINCIA_TINDEX:
		{
			rowcount  = m_dbAProvincia.GetRowCount();
			if (rowcount == 0)
			{
				m_dbProvincia.LoadCatalogo(&m_dbAProvincia);
			}
			break;
		}
		*/
	}
	return 0;
}

