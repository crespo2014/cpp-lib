// LogServer.cpp: implementation of the CLogServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogServer::CLogServer()
{
	m_hThread = NULL;
	m_hFileMap = NULL;
	m_pDebug = NULL;
}

CLogServer::~CLogServer()
{

}

DWORD CLogServer::StartServer(char *lpName)
{
	if (m_hFileMap != NULL) return 0;
	do {
		// Crear zona de memoria compartida
		m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,2048,lpName);if (m_hFileMap == NULL) break;TRACE1("Create File Mapping     Handle : %d",m_hFileMap); 
		m_pDebug =(S_DSERVER*)MapViewOfFile(m_hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);if (m_pDebug == NULL) break; TRACE1("Create map of File		PTR : %d",m_pDebug);
				
		// Llenar estructura y crear objetos de sincronismo
		m_pDebug->init = FALSE;
		m_pDebug->hServer = GetModuleHandle(NULL);
		m_pDebug->hMutex = ::CreateMutex(NULL,FALSE,NULL);				TRACE("Creating ... Mutex");if (m_pDebug->hMutex == NULL) break;
		m_pDebug->hSendEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);	TRACE("Creating ... Event");if (m_pDebug->hSendEvent == NULL) break;
		m_pDebug->hReplyEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);	if (m_pDebug->hReplyEvent == NULL) break;
		
		m_pDebug->init = TRUE;
		return 0;
	} while (false);

	// No se pudieron completar todas las operaciones
	TRACE("Failed ");
	m_pDebug->init = FALSE;
	if (m_pDebug->hReplyEvent != NULL)	CloseHandle(m_pDebug->hReplyEvent);
	if (m_pDebug->hSendEvent != NULL) CloseHandle(m_pDebug->hSendEvent);
	if (m_pDebug->hMutex != NULL) CloseHandle(m_pDebug->hMutex);
	m_pDebug->hServer = NULL;
	m_pDebug->hMutex = NULL;
	m_pDebug->hSendEvent = NULL;
	m_pDebug->hReplyEvent = NULL;
	if (m_pDebug != NULL) UnmapViewOfFile(m_pDebug);
	if (m_hFileMap != NULL) CloseHandle(m_hFileMap);
	m_pDebug = NULL;
	
	return 0;
}

DWORD CLogServer::Initialize()
{
	//StartServer();
	return 0;
}

UINT CLogServer::ThreadProc(LPVOID pParam)
{
	return ((CLogServer*)pParam)->Thread();
}

UINT CLogServer::Thread()
{
	DWORD	dwr;
	dwr = StartServer();
	return 0;
}
