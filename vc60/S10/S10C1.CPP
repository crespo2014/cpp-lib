// s10c1.cpp: implementation of the CSock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "s10c1.h"

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
	InitCSock();
}

CSock::~CSock()
{

}

int CSock::InitCSock()
{
	m_CSock = new S_CSOCK;
	m_CSock->handle=NULL;
	return true;
}

int CSock::SetTCPIP()
{
	m_CSock->protocol=0;
	m_CSock->af=AF_INET;
	m_CSock->type=SOCK_STREAM;
	return true;
}

int CSock::Create()
{
	m_CSock->handle=socket(m_CSock->af,m_CSock->type,m_CSock->protocol);
	if (m_CSock->handle == INVALID_SOCKET)
		return false;
	return true;
}

int CSock::Bind()
{
	int  result;
	result=bind(m_CSock->handle,(sockaddr*)&m_CSock->IPaddress,sizeof(m_CSock->IPaddress));
	if (result!=0)
	{
		result=WSAGetLastError();
		return false;
	}
	return true;
}

int CSock::SetIPandPort(char *ip, u_short port)
{
	m_CSock->IPaddress.sin_addr.S_un.S_addr=inet_addr(ip);
	m_CSock->IPaddress.sin_family=AF_INET;
	m_CSock->IPaddress.sin_port=port;//htons(port);
	memset(m_CSock->IPaddress.sin_zero,0,sizeof(m_CSock->IPaddress.sin_zero));
	return true;
}

int CSock::Accept()
{
	struct sockaddr_in	IPaddress;
	int		len=sizeof(IPaddress);
	accept(m_CSock->handle,(sockaddr*)&IPaddress,&len);
	return true;
}

int CSock::SetAddress(sockaddr_in address)
{
	m_CSock->IPaddress=address;
	return true;
}

int CSock::Listen()
{
	if (listen(m_CSock->handle,5)==SOCKET_ERROR)
		return false;
	return true;
}

int CSock::EnableMultiIP()
{
	BOOL p=true;
	int result;
	result=setsockopt(m_CSock->handle,SOL_SOCKET,SO_REUSEADDR,(char*)&p,sizeof(p));
	if (result==SOCKET_ERROR)
	{
		result=WSAGetLastError();
		return false;
	}
	return true;
}
