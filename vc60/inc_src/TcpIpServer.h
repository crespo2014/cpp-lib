// TcpIpServer.h: interface for the CTcpIpServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPIPSERVER_H__B0506F75_9B2D_44A6_B564_9C1C4B8124FD__INCLUDED_)
#define AFX_TCPIPSERVER_H__B0506F75_9B2D_44A6_B564_9C1C4B8124FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winsock2.h"
#include "MessageEvent.h"
#include "itcpipserverevents.h"


#define SOCKET_BUFFERLEN 255
#define MAX_SOCKETS 10

// Informacion de los sockets
typedef struct 
{
	BOOL	OnSocket;	// Indica que este socket esta activo.
	//BYTE	Status;		// Estado del socket
	SOCKET	Socket;		// Handle del socket
	LPVOID	lParam;		// Parametro extra puntero
	struct sockaddr_in sockaddr;	// Conneccion
	char	buffer[SOCKET_BUFFERLEN];
	DWORD	BytesToWrite;
	DWORD	BytesWritten;
} S_SOCKET_DATA;

#define SRV_STOPED	1	// El servidor esta detenido
#define SRV_STARTED	2	// El servidor esta funcionando
#define SRV_ERROR	3	// Ocurrio un error



class CTcpIpServer : private CMessageEvent 
{
public:
	DWORD GetServerStatus(DWORD* dwStatus,int* iError);
	DWORD GetServerPort(unsigned short* lpPort);
	DWORD ThreadOnSocketWrite(DWORD SockID);
	DWORD SetServerEvents(LPTCPIPSERVEREVENTS lpServerEvents);
	DWORD ThreadSend(DWORD SockID,DWORD dwCant);
	DWORD ThreadGetSendBuffer(DWORD SockID,BYTE **lpbBuffer, DWORD *lpdwSize);
	CTcpIpServer();
	virtual ~CTcpIpServer();
	DWORD Release();
	DWORD Initialize();
	DWORD ServerStop();
	DWORD ServerStart();
	DWORD SetServerPort(unsigned short Port);
	DWORD ThreadSetSocketParam(DWORD SocketID,LPVOID lpParam);
private:
	DWORD ThreadAcceptConnection();
	DWORD ThreadCheckListenSocketEvents();
	DWORD ThreadCheckSocketsEvents();
	DWORD ThreadGetMessage();
	DWORD ThreadProcessMessage();
	DWORD ThreadStop();
	DWORD ThreadStart();
	UINT Thread();
	static UINT ThreadProc(LPVOID pParam);
protected:
	unsigned short	m_Port;
	SOCKET			m_ListenSocket;
//	BYTE			m_Status;			//Estado del servidor
	BYTE			m_ThreadStatus;		// Estado del hilo
	int				m_ThreadError;
	HANDLE			m_hServerThread;
	LPTCPIPSERVEREVENTS m_Events;
	HANDLE			m_hSocketsEvent;
	S_SOCKET_DATA	m_Sockets[MAX_SOCKETS];
	BOOL			m_OnServerInit;

};

#endif // !defined(AFX_TCPIPSERVER_H__B0506F75_9B2D_44A6_B564_9C1C4B8124FD__INCLUDED_)
