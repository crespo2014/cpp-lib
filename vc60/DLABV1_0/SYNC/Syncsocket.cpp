// SyncSocket.cpp: implementation of the CSyncSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SyncSocket.h"
#include "SyncException.h"
#include <WinSock.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSyncSocket::CSyncSocket()
{
	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
	//	return FALSE;
	//}
	WSADATA wsd;
	WSAStartup(0x0101,&wsd);
	m_hSocket=NULL;
	
}

CSyncSocket::~CSyncSocket()
{

}
void CSyncSocket::Create(int nType)
{
	CSyncException* pSE;
	m_hSocket=socket(AF_INET,nType,0);
	if(m_hSocket==INVALID_SOCKET)
	{
		msg_error="error in function that Create a Socket";
		throw (pSE=new CSyncException(msg_error));
	}
}

void CSyncSocket::Bind(LPSOCKADDR psa)
{
	CSyncException* pSE;
	if(bind(m_hSocket,psa,sizeof(*psa))==SOCKET_ERROR)
	{
		msg_error="error in function bind";
		throw (pSE=new CSyncException(msg_error));
	}

}

void CSyncSocket::Listen()
{
	CSyncException* pSE;
	if(listen(m_hSocket,5)==SOCKET_ERROR)
	{
		msg_error="error in function Listen";
		throw (pSE=new CSyncException(msg_error));
	}
}

BOOL CSyncSocket::Accept(CSyncSocket &s, LPSOCKADDR psa)
{
	CSyncException* pSE;
	int fromlen=sizeof(*psa);
	s.m_hSocket=accept(m_hSocket,psa,&fromlen);
	if(s.m_hSocket==INVALID_SOCKET)
	{
		msg_error="error in function Accept";
		throw (pSE=new CSyncException(msg_error));
		return false;
	}
	return true;
}

CSockAddr CSyncSocket::GetHostByName(const char *pchName, const USHORT ushPort)
{
	CSockAddr saServer;
	struct hostent *hp;
	hp=gethostbyname(pchName);
	memset(&saServer,0,sizeof(saServer));
	memcpy(&(saServer.sin_addr),hp->h_addr,hp->h_length);
	saServer.sin_family=hp->h_addrtype;
	saServer.sin_port=htons(ushPort);
	return saServer;

}

void CSyncSocket::Connect(LPSOCKADDR psa)
{
	CSyncException* pSE;
	if(connect(m_hSocket,psa,sizeof(*psa))==SOCKET_ERROR)
	{
		msg_error="error in function Connect";
		throw (pSE=new CSyncException(msg_error));
	}
}

int CSyncSocket::Send(const char *pch, const int nSize, const int nSecs)
{
	CSyncException* pSE;
	int retval;
	retval=send(m_hSocket,pch,nSize,0);
	if(retval==SOCKET_ERROR)
	{
		msg_error="error in function Send";
		throw (pSE=new CSyncException(msg_error));
	}
	return retval;
}

int CSyncSocket::Receive(char *pch, const int nSize, const int nSecs)
{
	int next,retval;

	timeval* time_value=new timeval;
	time_value->tv_sec=nSecs;
	time_value->tv_usec=0;

	fd_set* timeout=new fd_set;
	timeout->fd_count=1;
	timeout->fd_array[0]=m_hSocket;
	
	CSyncException* pSE; 
		
	next=select(1,timeout,NULL,NULL,time_value);
	
	if (next)
	{
		retval=recv(m_hSocket,pch,nSize,0);
	}

	else return 0;
	
	if(retval==SOCKET_ERROR)
	{
		msg_error="error in function Receive";
		throw (pSE=new CSyncException(msg_error));
	}
	return retval;
	
}

void CSyncSocket::Close()
{
	closesocket(m_hSocket);
	WSACleanup();

}


int CSyncSocket::ReceiveDatagram(char *pch, const int nSize, LPSOCKADDR psa, const int nSecs,int& fromlen)
{
	CSyncException* pSE; 
	int retval;
	retval=recvfrom(m_hSocket,pch,nSize,0,psa,&fromlen);
	if(retval==SOCKET_ERROR)
	{
		msg_error="error in function ReceiveDatagram";
		throw (pSE=new CSyncException(msg_error));
	}
	return retval;

}

int CSyncSocket::SendDatagram(char *pch, const int nSize, LPSOCKADDR psa, const int nSecs,int& fromlen)
{
	CSyncException* pSE;
	int retval;
	retval=sendto(m_hSocket,pch,nSize,0,psa,fromlen);
	if(retval==SOCKET_ERROR)
	{
		msg_error="error in function SendDatagram";
		throw (pSE=new CSyncException(msg_error));
	}
	return retval;
}

USHORT CSyncSocket::GetBigIndianOrder(USHORT port)
{
	return htons(port);
}
