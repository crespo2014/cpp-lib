// TcpIpSocket.cpp: implementation of the CTcpIpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpIpSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Mensajes enviados al hilo que atiende el socket

#define SM_THCLOSE	3	// Cerrar el hilo
#define SM_CONNECT	4	// Indica al hilo que debe establecer coneccion
#define SM_CLOSE	5	// Indica al hilo que debe cerrar el socket

// Estados en los que puede encontrarse el socket
#define SS_NONE			0	// El socket no ha sido creado todavia
#define SS_CONECTING	2	// El socket esta tratando de establecer una coneccion
#define SS_CONECTED		3	// El socket esta conectado
#define SS_CONECTFAILED	4	// El socket no pudo conectarse

// Estados del hilo
#define THREAD_OK			0	// Todo bien
#define TH_WAIT_ERROR		1	// Error en una funcion WSAWaitForMultipleEvents
#define TH_ENUMEVENT_ERROR	2	// Error en funcion WSAEnumNetworkEvents
#define TH_EVENTSEL_ERROR	3	// Error en funcion WSAEventSelect
#define TH_CLOSE_ERROR		4	// Error en funcion closesocket
#define TH_SHUTDOWN_ERROR	5	// Error en funcion shutdown
#define TH_CREATE_ERROR		6	// Error creando el socket
#define TH_LISTEN_ERROR		7	// Error en funcion listen      

CTcpIpSocket::CTcpIpSocket()
{
	memset(&m_SockAddr,0,sizeof(m_SockAddr));
	m_SockAddr.sin_port = 0;
	m_SockAddr.sin_family = AF_INET;
	m_SockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_hSockEvent = WSA_INVALID_EVENT;
	m_OnSockInit = FALSE;
	m_Socket = INVALID_SOCKET;
	m_hSockThread = NULL;
	m_BytesToWrite = 0;		//Indica que no hay escritura en curso
	m_lpISocketEvents = NULL;
}

CTcpIpSocket::~CTcpIpSocket()
{
	Release();
}

DWORD CTcpIpSocket::Initialize()
{
	DWORD threadId;
	if (m_OnSockInit == TRUE)
		return 0;
	for (;;)
	{
		if (CMessageEvent::Initialize() != 0) break;
		// Creacion de todos los objetos utilizados
		m_hSockEvent = WSACreateEvent();
		if (m_hSockEvent == WSA_INVALID_EVENT)
			break;
		// Hilo
		m_hSockThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,&threadId);
		if (m_hSockThread == NULL) break;
		//if (!::SetThreadPriority(hThread,THREAD_PRIORITY_TIME_CRITICAL)) break;
		m_OnSockInit = TRUE;
		return 0;
	}
	Release();
	return 1;
}

DWORD CTcpIpSocket::Release()
{
	DWORD result = 0;
	// Terminar el hilo
	if (m_hSockThread != NULL)
	{
		Disconnect();
		S_MESSAGE Message;
		Message.Msg=SM_THCLOSE;
		if (SendMessage(&Message) != 0) result = 1;
		if (WaitForSingleObject(m_hSockThread,10000) != WAIT_OBJECT_0)
		{
			TerminateThread(m_hSockThread,1);
			result = 1;
		}
		CloseHandle(m_hSockThread);
		m_hSockThread = NULL;
	}
	// Destruir evento
	if (m_hSockEvent != WSA_INVALID_EVENT)
		if (!WSACloseEvent(m_hSockEvent)) result = 1;
	m_hSockEvent = WSA_INVALID_EVENT;
	if (CMessageEvent::Release() != 0) result = 1;
	return result;
}

UINT CTcpIpSocket::ThreadProc(LPVOID pParam)
{
	return ((CTcpIpSocket*)pParam)->Thread();
}

UINT CTcpIpSocket::Thread()
{
	HANDLE	Events[2];
	int result;
	WSANETWORKEVENTS eventos;
	Events[0] = m_hSockEvent;
	GetSendEventHandle(&Events[1]);
	m_SockStat = SS_NONE;
	m_ThreadStatus = THREAD_OK;
	m_ThreadError = 0;
	for (;;)
	{
		if (ThreadGetMessage() == 1)
			break;
		while ((m_Socket != INVALID_SOCKET) && (m_ThreadStatus == THREAD_OK))
		{
			switch(WSAWaitForMultipleEvents(2,Events,FALSE,INFINITE,FALSE))
			{
			case WSA_WAIT_EVENT_0:
				{
					result = WSAEnumNetworkEvents(m_Socket,m_hSockEvent,&eventos);
					if (result != 0) 
					{
						m_ThreadStatus = TH_ENUMEVENT_ERROR;
						m_ThreadError = WSAGetLastError();
						break;
					}
					ThreadCheckEvents(&eventos);
					break;					
				}
			case WAIT_IO_COMPLETION:
				{
					break;
				}
			case WSA_WAIT_TIMEOUT :
				{
					break;
				}
			case WSA_WAIT_EVENT_0+1 :
				{
					if (ThreadProcessMessage() == 1)
							return 0;
				}
			}
		}
	}
	return 0;
}

DWORD CTcpIpSocket::ThreadGetMessage()
{
	WaitMessage();
	return ThreadProcessMessage();
}

DWORD CTcpIpSocket::ThreadProcessMessage()
{
	S_MESSAGE*	message;
	DWORD	result=0;
	if (PeekMessage(&message) != 0)
		return 0;
	switch (message->Msg)
	{
	case SM_CONNECT: message->Result = ThreadConnectSocket();break;
	case SM_CLOSE:	 message->Result = ThreadCloseConnection();break;
	case SM_THCLOSE:
		{
			result=1;
			break;
		}
	default:
		{
			if (m_lpISocketEvents)
				message->Result = m_lpISocketEvents->OnProcessMessage(message,m_Param);
			break;
		}
	}
	message->ErrorCode = m_ThreadError;
	ReplyMessage();
	return result;
}

DWORD CTcpIpSocket::GetThreadStatus(DWORD *lpdwstat)
{
	*lpdwstat = m_ThreadStatus;
	return 0;
}

DWORD CTcpIpSocket::ThreadCheckEvents(WSANETWORKEVENTS *lpNetEvents)
{
	int result;
	if (lpNetEvents->lNetworkEvents & FD_READ)
	{
		ThreadOnRead(lpNetEvents->iErrorCode[FD_READ_BIT]);
	}
	if (lpNetEvents->lNetworkEvents & FD_WRITE)
	{
		ThreadOnWrite(lpNetEvents->iErrorCode[FD_WRITE_BIT]);
	}
	if (lpNetEvents->lNetworkEvents & FD_ACCEPT)
	{
		result = 1;
	}
	if (lpNetEvents->lNetworkEvents & FD_CONNECT)
	{
		ThreadOnConnect(lpNetEvents->iErrorCode[FD_CONNECT_BIT]);
	}
	if (lpNetEvents->lNetworkEvents & FD_CLOSE)
	{
		ThreadOnClose(lpNetEvents->iErrorCode[FD_CLOSE_BIT]);
	}
	return 0;
}

DWORD CTcpIpSocket::ThreadConnectSocket()
{
	// Crear el socket y conectarse
	m_Socket = ::socket(AF_INET,SOCK_STREAM,0);
	if (m_Socket == INVALID_SOCKET)
	{
		m_ThreadStatus = TH_CREATE_ERROR;
		m_ThreadError = WSAGetLastError();
		return 1;
	}
	// datos del socket
	int val;
	int size = sizeof(int);
	int rs = getsockopt(m_Socket,SOL_SOCKET,SO_RCVBUF,(char*)&val,&size);
	rs = getsockopt(m_Socket,SOL_SOCKET,SO_SNDBUF,(char*)&val,&size);
	int result = WSAEventSelect(m_Socket,m_hSockEvent,FD_READ|FD_WRITE|FD_ACCEPT|FD_CONNECT|FD_CLOSE);
	if (result != 0)
	{
		m_ThreadStatus = TH_EVENTSEL_ERROR;
		m_ThreadError = WSAGetLastError();
		ThreadCloseSocket();
		return 1;
	}
	result = connect(m_Socket,(SOCKADDR*)&m_SockAddr,sizeof(m_SockAddr));
	if (result == 0)
	{
		ThreadOnConnect(0);
		m_SockStat = SS_CONECTED;
		return 0;
	}
	result = WSAGetLastError();
	if (result == WSAEWOULDBLOCK)
	{
		m_SockStat = SS_CONECTING;
		return SE_CONNECTING;
	}
	ThreadCloseSocket();
	m_ThreadError = result;
	return 1;
}

DWORD CTcpIpSocket::Connect()
{
	// ver el estatus del hilo
	switch (m_SockStat)
	{
	case SS_CONECTED  : return 0;
	case SS_CONECTING : return SE_CONNECTING;
	case SS_CONECTFAILED : 
		{
			m_SockStat = SS_NONE;
			return SE_CONNECTFAILED;
		}
	}
	DWORD result;
	S_MESSAGE Message;
	Message.Msg=SM_CONNECT;
	result = SendMessage(&Message);
	if (result != 0) return SE_SNDMESSAGE;
	result = Message.Result;
	return result;
}

DWORD CTcpIpSocket::ThreadOnConnect(int iErrorCode)
{
	if (iErrorCode ==0)
	{
		if (m_lpISocketEvents)
			m_lpISocketEvents->OnConnect(m_Param);
		m_SockStat = SS_CONECTED;
	}
	else
	{
		if (m_lpISocketEvents)
			m_lpISocketEvents->OnConnectFailed(m_Param,iErrorCode);
		m_ThreadError = iErrorCode;
		m_SockStat = SS_CONECTFAILED;
		ThreadCloseSocket();
	}
	return 0;
}


DWORD CTcpIpSocket::ThreadOnClose(int iErrorCode)
{
	if (m_lpISocketEvents)
			m_lpISocketEvents->OnClose(m_Param,iErrorCode);
	return ThreadCloseSocket();
}

DWORD CTcpIpSocket::ThreadCloseSocket()
{
	int result = closesocket(m_Socket);
	if (result != 0)
	{
		m_ThreadStatus = TH_CLOSE_ERROR;
		m_ThreadError = WSAGetLastError();
		return 1;
	}
	m_Socket = INVALID_SOCKET;
	return 0;
}

DWORD CTcpIpSocket::ThreadGetSendBuffer(BYTE **lpbBuffer, DWORD *lpdwSize)
{
	if (m_BytesToWrite != 0)
	{
		//Escritura en curso
		*lpbBuffer = NULL;
		*lpdwSize = 0;
		return 2;
	}
	*lpbBuffer = (BYTE*)m_WriteBuffer;
	*lpdwSize = WB_SIZE;
	return 0;
}

DWORD CTcpIpSocket::ThreadSend(DWORD dwCant)
{
	if (m_BytesToWrite != 0)
	{
		//Escritura en curso
		return 2;
	}
	m_BytesToWrite = dwCant;
	m_BytesWritten = 0;
	ThreadOnWrite(0);
	return 0;
}

DWORD CTcpIpSocket::ThreadOnWrite(int iErrorCode)
{
	// Enviar los bytes que faltan por enviar
	if (iErrorCode != 0)
	{
		if (m_lpISocketEvents)
				m_lpISocketEvents->OnWriteFailed(m_Param,iErrorCode);
		return 1;
	}
	for (;;)
	{
		if (m_BytesWritten == m_BytesToWrite) 
		{
			m_BytesToWrite = 0;
			if (m_lpISocketEvents)
				m_lpISocketEvents->OnWrite(m_Param);
			return 0;

		}
		int result = send(m_Socket,&m_WriteBuffer[m_BytesWritten],m_BytesToWrite-m_BytesWritten,0);
		if (result == SOCKET_ERROR)
		{
			result = WSAGetLastError();
			switch (result)
			{
			case WSAEWOULDBLOCK: return 0;	// Hay que espera a que se vacie el buffer
			default: 
				{
					if (m_lpISocketEvents)
						m_lpISocketEvents->OnWriteFailed(m_Param,result);
					return 1;
				}

			}
		}	
		m_BytesWritten+= result;
	}
}

DWORD CTcpIpSocket::ThreadOnRead(int iErrorCode)
{
	char	readbuffer[1024];
	int		readcant;
	int		result;
	if ((m_lpISocketEvents) && (iErrorCode != 0))
		m_lpISocketEvents->OnReadFailed(m_Param,iErrorCode);
	for (;;)
	{
		readcant = recv(m_Socket,readbuffer,1024,0);
		if (readcant == SOCKET_ERROR)
		{
			result = WSAGetLastError();
			switch (result)
			{
			case WSAEWOULDBLOCK: return 0;	// Hay que espera a que arriven mas bytes
			default: 
				{
					if (m_lpISocketEvents)
						m_lpISocketEvents->OnReadFailed(m_Param,iErrorCode);
					return 1;
				}
			}
		}
		if (m_lpISocketEvents)
				m_lpISocketEvents->OnRead((BYTE*)readbuffer,readcant,m_Param);

	}
}

DWORD CTcpIpSocket::ThreadCloseConnection()
{
	int result = ::shutdown(m_Socket,SD_BOTH);
	if (result != 0)
	{
		m_ThreadStatus = TH_SHUTDOWN_ERROR;
		m_ThreadError = WSAGetLastError();
		return SE_SHUTDOWN;
	}
	return 0;
}

DWORD CTcpIpSocket::Disconnect()
{
	return 0;
}

DWORD CTcpIpSocket::SetSocketEvents(LPTCPIPSOCKETEVENTS lpSocketEvents)
{
	m_lpISocketEvents = lpSocketEvents;
	return 0;
}

DWORD CTcpIpSocket::SetServer(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port)
{
	m_SockAddr.sin_addr.S_un.S_un_b.s_b1 = b1;
	m_SockAddr.sin_addr.S_un.S_un_b.s_b2 = b2;
	m_SockAddr.sin_addr.S_un.S_un_b.s_b3 = b3;
	m_SockAddr.sin_addr.S_un.S_un_b.s_b4 = b4;
	m_SockAddr.sin_port = htons(port);
	return 0;
}
