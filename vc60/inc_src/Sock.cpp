// Sock.cpp: implementation of the CSock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSock::CSock()
{
	m_OnCantRead = TRUE;
	m_OnCantWrite = TRUE;
	m_socket = INVALID_SOCKET;
	m_nonblockingmode = false;		// el socket se bloquea
	m_events = NULL;
}

CSock::~CSock()
{

}


DWORD CSock::Create()
{
	m_socket = ::socket(AF_INET,SOCK_STREAM,0);
	m_error = WSAGetLastError();
	if (m_socket == INVALID_SOCKET) return ERR_APIFAIL;
	m_OnCantRead = true;
	m_OnCantWrite = true;
	m_error = ioctlsocket(m_socket,FIONBIO,&m_nonblockingmode);
	if (m_error != 0) return ERR_APIFAIL;
	return ERR_NONE;	
}

DWORD CSock::Connect(BYTE b1, BYTE b2, BYTE b3, BYTE b4, WORD wPort)
{
	DWORD dwr;
	if (m_socket == INVALID_SOCKET) 
	{
		dwr = Create();
		if (dwr != ERR_NONE) return dwr;
	}
	m_sockaddr.sin_addr.S_un.S_un_b.s_b1 = b1;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b2 = b2;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b3 = b3;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b4 = b4;
	m_sockaddr.sin_port = htons(wPort);
	m_error = connect(m_socket,(SOCKADDR*)&m_sockaddr,sizeof(m_sockaddr));
	if (m_error == SOCKET_ERROR) 
	{
		m_error = WSAGetLastError();
		if ((m_error == WSAEWOULDBLOCK) && m_nonblockingmode) return ERR_NONE;
	}
	if (m_error != 0) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD CSock::SetNonBlockingMode(BOOL bmode)
{
	m_nonblockingmode = bmode;
	if (m_socket == INVALID_SOCKET)	return ERR_NONE;
	m_error = ioctlsocket(m_socket,FIONBIO,&m_nonblockingmode);
	if (m_error != 0) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD CSock::Close()
{
	if (m_socket == INVALID_SOCKET) return ERR_INV_HANDLE;
	::closesocket(m_socket);
	m_socket = INVALID_SOCKET;
	return ERR_NONE;

}

DWORD CSock::Accept(CSock *pSock)
{
	int	sockaddrlen = sizeof(m_sockaddr);
	m_socket = accept(*pSock,(SOCKADDR*)&m_sockaddr,&sockaddrlen);
	m_error = WSAGetLastError();
	if (m_socket == INVALID_SOCKET) return ERR_APIFAIL;
	return ERR_NONE;
	
}

DWORD CSock::Bind(WORD wPort)
{
	if (m_socket == INVALID_SOCKET) return ERR_INV_HANDLE;
	m_port = wPort;
	m_sockaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(wPort);
	m_error = ::bind(m_socket,(SOCKADDR*)&m_sockaddr,sizeof(m_sockaddr));
	if (m_error != 0) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD CSock::ShutDownSend()
{
	if (m_socket == INVALID_SOCKET) return ERR_INV_HANDLE;
	return ERR_NONE;
}

DWORD CSock::Listen(WORD wport, int ibacklog)
{
	if (m_socket == INVALID_SOCKET)
	{
		DWORD dwr = Create();
		if (dwr != ERR_NONE) return dwr;
	}
	m_port = wport;
	m_sockaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_port = htons(wport);
	m_error = ::bind(m_socket,(SOCKADDR*)&m_sockaddr,sizeof(m_sockaddr));
	if (m_error != 0) return ERR_APIFAIL;
	m_error = listen(m_socket,ibacklog);
	if (m_error != 0) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD CSock::GetError(int *pierror)
{
	*pierror = m_error;
	m_error = 0;
	return ERR_NONE;
}

DWORD CSock::GetWriteBuffer(BYTE **ppBuffer, WORD *pSize)
{
	if (m_bufflast >= SCK_SNDSIZE-10) return ERR_NOMEMORY;
	*ppBuffer = &m_sndbuff[m_bufflast];
	*pSize = SCK_SNDSIZE - m_bufflast;
	return ERR_NONE;
	
}

DWORD CSock::ProcessRead()
{
	m_OnCantRead = true;
	return 0;
}

DWORD CSock::ProcessWrite()
{
	return 0;
}

DWORD CSock::ProcessError()
{
	return 0;
}

DWORD CSock::SetEvents(ISockEvents *pISockEvents)
{
	m_events = pISockEvents;
	return ERR_NONE;
}
