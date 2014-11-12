// Lisa2000Server.h: interface for the CLisa2000Server class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA2000SERVER_H__A9AE9489_B94A_4CC1_9E5A_B5B610583EC0__INCLUDED_)
#define AFX_LISA2000SERVER_H__A9AE9489_B94A_4CC1_9E5A_B5B610583EC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Clases\SerialPortBridge.h"
#include "..\Clases\TcpIpServer.h"
#include "lisa2000resultFilter.h"

typedef struct
{
	BOOL OnActive;	// Indica que esta coneccion esta activa
	BYTE cmd;		// Comando enviado
	BYTE tmp01;		// Variables temporales
	BYTE tmp02;
} CONNECTION_INFO;	// Informacion acerca de la coneccion establecida

#define MAX_CONECCTIONS 10

class CLisa2000Server :	public	CSerialPortBridge,
						public	CTcpIpServer,
						private	ITcpIpServerEvents,
						private	ICommunicationBridgeEvents,
						public CLisa2000ResultFilter
{
public:
	DWORD ThreadSendResults(CONNECTION_INFO* lpconinf,DWORD SockID);
	DWORD Release();
	DWORD Initialize();
	CLisa2000Server();
	virtual ~CLisa2000Server();
	
	//CLisa2000ResultFilter	m_ResultsFilter;

private:
	virtual DWORD _stdcall OnBridgeSndBuffer(BYTE *buffer, DWORD dwsize);
	virtual DWORD _stdcall OnBridgeRcvBuffer(BYTE *buffer, DWORD dwsize);
	virtual DWORD _stdcall OnBridgeSndPortEvent(DWORD pEventMask);
	virtual DWORD _stdcall OnBridgeRcvPortEvent(DWORD pEventMask);

	virtual DWORD _stdcall OnSocketClose(LPVOID lpParam,DWORD SockID,int iErrorCode);
	virtual DWORD _stdcall OnSocketConnect(DWORD SockID);
	virtual DWORD _stdcall OnServerProcessMessage(LP_MESSAGE lpMessage);
	virtual DWORD _stdcall OnSocketWrite(LPVOID lpParam,DWORD SockID);
	virtual DWORD _stdcall OnSocketWriteFailed(LPVOID lpParam,DWORD SockIDint,int iErrorCode);
	virtual DWORD _stdcall OnSocketRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam,DWORD SockID);
	virtual DWORD _stdcall OnSocketReadFailed(LPVOID lpParam,DWORD SockID,int iErrorCode);

	DWORD SendAnalysisInfo(CONNECTION_INFO*	lpconinf,DWORD SockID);

	
	BOOL					m_OnLisa2000Init;
	CONNECTION_INFO			m_Conecctions[MAX_CONECCTIONS];
		
};

#endif // !defined(AFX_LISA2000SERVER_H__A9AE9489_B94A_4CC1_9E5A_B5B610583EC0__INCLUDED_)
