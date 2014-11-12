// TcpIpServer.cpp: implementation of the CTcpIpServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpIpServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Mensajes enviados al hilo 
#define TM_START	1	// Iniciar el servidor
#define TM_STOP		2	// Detener el servidor
#define TM_CLOSE	3	// Terminar el hilo


// Estados de error del hilo
#define TS_NONE				0	// Todo esta trabajando bien
#define TS_LISTEN			1	// El hilo se esncuentra trabajando bien
#define TS_INV				2	// El hilo no existe
#define TS_EVENTSEL_ERROR	3	// Error en funcion WSAEventSelect
#define TS_CLOSE_ERROR		4	// Error en funcion closesocket
#define TS_SHUTDOWN_ERROR	5	// Error en funcion shutdown
#define TS_CREATE_ERROR		6	// Error creando el socket
#define TS_BIND_ERROR		7	// Error en funcion bind
#define TS_LISTEN_ERROR		8	// Error en funcion listen
#define TS_ACCEPT_ERROR		9	// Error en funcion listen
#define TS_ENUMEVENT_ERROR	10	// Error en funcion WSAEnumNetworkEvents
#define TS_EVENT_ERROR		11	// Error creando evento
#define TS_WAIT_ERROR		12	// Error en una funcion WSAWaitForMultipleEvents

CTcpIpServer::CTcpIpServer()
{
	m_ListenSocket = INVALID_SOCKET;
	m_hSocketsEvent = NULL;
	m_Port = 0;
	m_ThreadError = 0;
	m_ThreadStatus = TS_INV;
	m_OnServerInit = FALSE;
	DWORD i;
	for (i=0;i<MAX_SOCKETS;i++)
	{
		m_Sockets[i].OnSocket = false;
	}
}

CTcpIpServer::~CTcpIpServer()
{
	Release();
}

UINT CTcpIpServer::ThreadProc(LPVOID pParam)
{
	return ((CTcpIpServer*)pParam)->Thread();	
}

UINT CTcpIpServer::Thread()
{
	HANDLE	Events[2];
	Events[0] = m_hSocketsEvent;
	GetSendEventHandle(&Events[1]);
	m_ThreadStatus = TS_NONE;
	m_ThreadError = 0;
	for (;;)
	{
		if (ThreadGetMessage() == 1) return 0;
		while ((m_ListenSocket != INVALID_SOCKET) && (m_ThreadStatus == TS_LISTEN))
		{
			switch(WSAWaitForMultipleEvents(2,Events,FALSE,INFINITE,FALSE))
			{
			case WSA_WAIT_EVENT_0: ThreadCheckSocketsEvents();break;
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
					if (ThreadProcessMessage() == 1) return 0;
				}
			}
		}
	}
	return 0;
}

DWORD CTcpIpServer::SetServerPort(unsigned short Port)
{
	m_Port = Port;
	return 0;
}

DWORD CTcpIpServer::ServerStart()
{
	if (m_ThreadStatus == TS_LISTEN) return 0;
	if (m_ThreadStatus != TS_NONE) return 1;
	S_MESSAGE Message;
	Message.Msg=TM_START;
	if (SendMessage(&Message) != 0)
		return 1;
	if (Message.Result != 0)
		return 1;
	return 0;
}

DWORD CTcpIpServer::ServerStop()
{
	S_MESSAGE Message;
	Message.Msg=TM_STOP;
	if (SendMessage(&Message) != 0)
		return 1;
	if (Message.Result != 0)
		return 1;
	return 0;
}

DWORD CTcpIpServer::Initialize()
{
	DWORD threadId;
	if (m_OnServerInit == TRUE)
		return 0;
	for (;;)
	{
		if (CMessageEvent::Initialize() != 0) break;
		m_hSocketsEvent = WSACreateEvent();
		if (m_hSocketsEvent == WSA_INVALID_EVENT) break;
		m_ListenSocket = ::socket(AF_INET,SOCK_STREAM,0);
		if (m_ListenSocket == INVALID_SOCKET) break;
		m_hServerThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,&threadId);
		if (m_hServerThread == NULL) break;
		m_ThreadStatus = TS_NONE;
		m_OnServerInit = TRUE;
		return 0;
	}
	Release();
	return 1;
}

DWORD CTcpIpServer::Release()
{
	DWORD result = 0;
	// Terminar el hilo
	if (m_hServerThread != NULL)
	{
		ServerStop();
		S_MESSAGE Message;
		Message.Msg=TM_CLOSE;
		if (SendMessage(&Message) != 0) result = 1;
		if (WaitForSingleObject(m_hServerThread,10000) != WAIT_OBJECT_0)
		{
			TerminateThread(m_hServerThread,1);
			result = 1;
		}
		CloseHandle(m_hServerThread);
		m_hServerThread = NULL;
	}
	if (CMessageEvent::Release() != 0) result = 1;
	return result;
}

DWORD CTcpIpServer::ThreadStart()
{
	int result;
	for (;;)
	{
		// Asociar el socket con un evento
		result = WSAEventSelect(m_ListenSocket,m_hSocketsEvent,FD_READ|FD_WRITE|FD_ACCEPT|FD_CONNECT|FD_CLOSE);
		if (result != 0)
		{
			m_ThreadError = WSAGetLastError();
			m_ThreadStatus = TS_EVENTSEL_ERROR;
			break;
		}
		// Asociar el socket a un puerto determinado
		struct sockaddr_in sockaddr;
		sockaddr.sin_port = htons(m_Port);
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		result = ::bind(m_ListenSocket,(SOCKADDR*)&sockaddr,sizeof(sockaddr));
		if (result != 0)
		{
			m_ThreadStatus = TS_BIND_ERROR;break;
		}
		result = listen(m_ListenSocket,5);
		if (result != 0)
		{
			m_ThreadError = WSAGetLastError();
			m_ThreadStatus = TS_LISTEN_ERROR;break;
		}
		m_ThreadStatus = TS_LISTEN; 
		return 0;
	}
	m_ThreadError = WSAGetLastError();
	return 1;
}

DWORD CTcpIpServer::ThreadStop()
{
	// Terminar todas las conecciones establecidas
	// Poner el listen en 0
	return 0;
}

DWORD CTcpIpServer::ThreadProcessMessage()
{
	S_MESSAGE*	message;
	DWORD	result=0;
	if (PeekMessage(&message) != 0)
		return 0;
	switch (message->Msg)
	{
	case TM_START:	message->Result = ThreadStart();break;
	case TM_STOP:	message->Result = ThreadStop();break;
	case TM_CLOSE:
		{
			result=1;
			break;
		}
	default:
		{
			if (m_Events)
				message->Result = m_Events->OnServerProcessMessage(message);
			break;
		}
	}
	message->ErrorCode = m_ThreadError;
	ReplyMessage();
	return result;
}	

DWORD CTcpIpServer::ThreadGetMessage()
{
	WaitMessage();
	return ThreadProcessMessage();
}

DWORD CTcpIpServer::ThreadCheckSocketsEvents()
{
	// Determinar el socket y el evento que este provoco.
	// Empezar por el socket de escucha
	ThreadCheckListenSocketEvents();
	// Chequear el resto de los sockets
	for (DWORD i=0; i<MAX_SOCKETS;i++)
	{
		if (m_Sockets[i].OnSocket)
		{
			WSANETWORKEVENTS eventos;
			int result = WSAEnumNetworkEvents(m_Sockets[i].Socket,m_hSocketsEvent,&eventos);
			if (result != 0) 
			{
				m_ThreadStatus = TS_ENUMEVENT_ERROR;
				m_ThreadError = WSAGetLastError();
				return 1;
			}
			if (eventos.lNetworkEvents & FD_CLOSE) 
			{
				m_Events->OnSocketClose(m_Sockets[i].lParam,i,eventos.iErrorCode[FD_CLOSE_BIT]);
				closesocket(m_Sockets[i].Socket);
				m_Sockets[i].OnSocket = false;				
			}
			if (eventos.lNetworkEvents & FD_READ)
			{
				char	readbuffer[1024];
				int		readcant;
				for (;;)
				{
					readcant = recv(m_Sockets[i].Socket,readbuffer,1024,0);
					if (readcant == SOCKET_ERROR)
					{
						result = WSAGetLastError();
						if (result != WSAEWOULDBLOCK)
							m_Events->OnSocketReadFailed(m_Sockets[i].lParam,i,eventos.iErrorCode[FD_READ_BIT]);
						break;
					}
					m_Events->OnSocketRead((BYTE*)readbuffer,readcant,m_Sockets[i].lParam,i);
				}
			}
			// Hay que cambiar el procesamiento de la escritura.
			if (eventos.lNetworkEvents & FD_WRITE)
			{
				if (eventos.iErrorCode[FD_WRITE_BIT] == 0)
					ThreadOnSocketWrite(i);
				else
					m_Events->OnSocketWriteFailed(m_Sockets[i].lParam,i,eventos.iErrorCode[FD_WRITE_BIT]);
			}
			// Estos eventos no deberian ocurrir
			if (eventos.lNetworkEvents & FD_CONNECT) return 1;
			if (eventos.lNetworkEvents & FD_ACCEPT) return 1;
		}
	}
	return 0;
}

DWORD CTcpIpServer::ThreadCheckListenSocketEvents()
{
	WSANETWORKEVENTS eventos;
	int result = WSAEnumNetworkEvents(m_ListenSocket,m_hSocketsEvent,&eventos);
	if (result != 0) 
	{
		m_ThreadError = WSAGetLastError();
		m_ThreadStatus = TS_ENUMEVENT_ERROR;
		return 1;
	}
	if (eventos.lNetworkEvents & FD_ACCEPT)
	{
		// Aceptar una coneccion
		ThreadAcceptConnection();
	}
	if (eventos.lNetworkEvents & FD_CLOSE) return 1;
	// Estos eventos no deberian ocurrir
	if (eventos.lNetworkEvents & FD_READ) return 1;
	if (eventos.lNetworkEvents & FD_WRITE) return 1;
	if (eventos.lNetworkEvents & FD_CONNECT) return 1;
	return 0;
}

DWORD CTcpIpServer::ThreadAcceptConnection()
{
	int	sockaddrlen = sizeof(SOCKADDR);
	struct sockaddr_in sockaddr;
	int result;
	SOCKET socket = accept(m_ListenSocket,(SOCKADDR*)&sockaddr,&sockaddrlen);
	if (socket == INVALID_SOCKET)
	{
		result = WSAGetLastError();
		if (result == WSAEWOULDBLOCK) return 0;
		m_ThreadError = result;
		m_ThreadStatus = TS_ACCEPT_ERROR;
		return 1;
	}
	// La conección fue realizada con exito
	if (m_Events)
	{
		// Buscar una estructura para almacenar los datos del socket
		for (DWORD i=0; i<MAX_SOCKETS;i++)
		{
			if (m_Sockets[i].OnSocket == FALSE) break;
		}
		if (i<MAX_SOCKETS)
		{
			m_Sockets[i].OnSocket = true;
			m_Sockets[i].sockaddr = sockaddr;
			m_Sockets[i].Socket = socket;
			m_Sockets[i].BytesToWrite = 0;
			//m_Sockets[i].
			if (m_Events->OnSocketConnect(i) == 0) return 0;
			m_Sockets[i].OnSocket = false;
			return 0;
		}
	}
	result = closesocket(socket);
	return 0;					
}

DWORD CTcpIpServer::ThreadSetSocketParam(DWORD SocketID, LPVOID lpParam)
{
	m_Sockets[SocketID].lParam = lpParam;
	return 0;
}

DWORD CTcpIpServer::ThreadGetSendBuffer(DWORD SockID, BYTE **lpbBuffer, DWORD *lpdwSize)
{
	if (m_Sockets[SockID].BytesToWrite != 0)
	{
		//Escritura en curso
		*lpbBuffer = NULL;
		*lpdwSize = 0;
		return 2;	
	}
	*lpbBuffer = (BYTE*)m_Sockets[SockID].buffer;
	*lpdwSize = SOCKET_BUFFERLEN;
	return 0;
}

DWORD CTcpIpServer::ThreadSend(DWORD SockID, DWORD dwCant)
{
	if (m_Sockets[SockID].BytesToWrite != 0)
	{
		//Escritura en curso
		return 2;
	}
	m_Sockets[SockID].BytesToWrite = dwCant;
	m_Sockets[SockID].BytesWritten = 0;
	ThreadOnSocketWrite(SockID);
	return 0;
}


DWORD CTcpIpServer::SetServerEvents(LPTCPIPSERVEREVENTS lpServerEvents)
{
	m_Events = lpServerEvents;
	return 0;
}

DWORD CTcpIpServer::ThreadOnSocketWrite(DWORD SockID)
{
	S_SOCKET_DATA*	socket;
	socket = &m_Sockets[SockID];
	if (socket->BytesToWrite == 0)
	{
		// Primera confirmacion de escritura
		return 0;
	}
	for (;;)
	{
		if (socket->BytesWritten == socket->BytesToWrite) 
		{
			// Esto indica que no hay escritura pendiente
			socket->BytesToWrite = 0;	
			if (m_Events)
				m_Events->OnSocketWrite(socket->lParam,SockID);
			return 0;
		}
		int result = send(socket->Socket,&socket->buffer[socket->BytesWritten],socket->BytesToWrite-socket->BytesWritten,0);
		if (result == SOCKET_ERROR)
		{
			result = WSAGetLastError();
			switch (result)
			{
			case WSAEWOULDBLOCK: return 0;	// Hay que espera a que se vacie el buffer
			default: 
				{
					if (m_Events)
						m_Events->OnSocketWriteFailed(socket->lParam,SockID,result);
					return 1;
				}

			}
		}	
		socket->BytesWritten+= result;
	}

}

DWORD CTcpIpServer::GetServerPort(unsigned short *lpPort)
{
	*lpPort = m_Port;
	return 0;
}

DWORD CTcpIpServer::GetServerStatus(DWORD *dwStatus, int *iError)
{
	switch (m_ThreadStatus)
	{
	case TS_NONE:
	case TS_INV:
		*dwStatus = SRV_STOPED; break;
	case TS_LISTEN:
		*dwStatus = SRV_STARTED;break;
	default:
		*dwStatus = SRV_ERROR;break;
	}
	*iError = m_ThreadError;
	return 0;
}
