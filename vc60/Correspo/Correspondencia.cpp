// Correspondencia.cpp: implementation of the CCorrespondencia class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Correspondencia.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const OLECHAR* InitStr	= L"Driver={Microsoft dBase Driver (*.dbf)};FIL=dBase 5;DBQ=C:\\CORRESPO OK;DriverId=533;";


CCorrespondencia::CCorrespondencia()
{
	m_lpICommand = NULL;
}

CCorrespondencia::~CCorrespondencia()
{

}

DWORD CCorrespondencia::InitDB()
{
	// Inicializar OLEDB
	return ERR_NONE;
}

DWORD CCorrespondencia::OpenDB()
{
	return Correspodb.Open();
	DWORD					rc;
	HRESULT					hr;
	IDataInitialize *		pIDataInitialize    = NULL;
	IDBInitialize *			pIDBInitialize      = NULL;
	IDBCreateSession*		pIDBCreateSession	= NULL;
	IUnknown *				pUnkSession			= NULL;
	ICommandText*			pICommandText		= NULL;
	IDBCreateCommand*		pICreateCommand		= NULL;
//	m_cartas.Initialize();
	for(;;)
	{
		hr = CoCreateInstance(CLSID_MSDAINITIALIZE,NULL,CLSCTX_INPROC_SERVER,IID_IDataInitialize,(VOID **)&pIDataInitialize);
		if (hr != S_OK) break;
		hr = pIDataInitialize->GetDataSource(NULL,CLSCTX_INPROC_SERVER,InitStr,IID_IDBInitialize,(IUnknown **)&pIDBInitialize);
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
//		m_cartas.SetICommand(m_lpICommand);
		break;
	};
	if (pIDataInitialize)
		rc = pIDataInitialize->Release();
	if (pIDBInitialize)
		rc = pIDBInitialize->Release();
	if (pIDBCreateSession)
		rc = pIDBCreateSession->Release();
	if (pUnkSession)
		rc = pUnkSession->Release();
	if (pICreateCommand)
		rc = pICreateCommand->Release();
	if (hr == S_OK) return ERR_NONE;
	if (m_lpICommand)
		rc = m_lpICommand->Release();
	m_lpICommand = NULL;
	m_ApiError = hr;
	return ERR_OLEDBFAIL;
}

DWORD CCorrespondencia::Show(HWND hWndParent)
{
	OpenDB();
	m_StartView.Initialize();
	m_StartView.Show(hWndParent);
	return 0;
}

DWORD CCorrespondencia::CloseDB()
{
	HRESULT	hr;
	if (m_lpICommand) 
		hr = m_lpICommand->Release();
	return ERR_NONE;
}

DWORD CCorrespondencia::GetApiError()
{
	return m_ApiError;
}
