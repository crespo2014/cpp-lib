// BridgeSvr.cpp: implementation of the CBridgeSvr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BridgeSvr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBridgeSvr::CBridgeSvr()
{
	m_b1 = 0;
	m_b2 = 0;
	m_b3 = 0;
	m_b4 = 0;
	m_Port = 0;
	m_SockSvr.SetEvents(this);
}

CBridgeSvr::~CBridgeSvr()
{

}

DWORD _stdcall CBridgeSvr::OnConnect(CSock* pSock)
{
	CSock*			dest;
	CSockBridge*	sock;

	sock = GetFreeSock();
	dest = m_SockSvr.GetFreeSock();
	if ((sock == NULL)||(dest == NULL))
	{
		pSock->Close();	// No hay sockets disponibles
		return 0;
	}
	sock->ConnectSock(pSock,dest,m_b1,m_b2,m_b3,m_b4,m_Port);
	return 0;
}

DWORD CBridgeSvr::SetDestAddress(BYTE b1, BYTE b2, BYTE b3, BYTE b4, WORD wPort)
{
	m_b1 = b1;
	m_b2 = b2;
	m_b3 = b3;
	m_b4 = b4;
	m_Port = wPort;
	return 0;
}

DWORD CBridgeSvr::SetListenPort(WORD wPort)
{
	m_ListenPort = wPort;
	return 0;
}

DWORD CBridgeSvr::Start(WORD wListenPort)
{
	m_ListenPort = wListenPort;
	return m_SockSvr.Start(wListenPort);	
}

CSockBridge* CBridgeSvr::GetFreeSock()
{
	DWORD i;
	for (i = 0;i<MAX_BSOCKS;i++)
	{
		if (!m_Socks[i].OnConnect()) return &m_Socks[i];
	}
	return NULL;
}
