// LogServer.h: interface for the CLogServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGSERVER_H__08FE513D_2FE7_4C71_B277_B9F4929CE652__INCLUDED_)
#define AFX_LOGSERVER_H__08FE513D_2FE7_4C71_B277_B9F4929CE652__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"

#define LOGFILE "log.txt"
#define LOGSERVER "logsrv"


typedef struct {
	BOOL	init;			// Indica que todos los campos de la estructura estan inicializados
	HANDLE	hServer;		// Handle del proceso que crea los objetos de sincronismo 
	HANDLE	hSendEvent;
	HANDLE	hReplyEvent;
	HANDLE	hMutex;			// Mutex usado para controlar el acceso a la estructura

	DWORD	clientID;		// handle del proceso que envia los datos
	DWORD	logtyp;			// Tipo de log
	DWORD	SrvCmd;			// Comando enviado por el servidor
	char	data[1];		// datos extras de la estructura

} S_DSERVER;

class CLogServer  
{
private:
	HANDLE		m_hFileMap;		// Handle del fichero mapeado o zona de memoria
	S_DSERVER*	m_pDebug;
	HANDLE		m_hThread;

	static UINT ThreadProc(LPVOID pParam);
	UINT Thread();

public:
	DWORD Initialize();
	DWORD StartServer(char* lpName = LOGSERVER);
	CLogServer();
	virtual ~CLogServer();

};

#endif // !defined(AFX_LOGSERVER_H__08FE513D_2FE7_4C71_B277_B9F4929CE652__INCLUDED_)
