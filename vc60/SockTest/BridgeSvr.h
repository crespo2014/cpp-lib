// BridgeSvr.h: interface for the CBridgeSvr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRIDGESVR_H__C9E40903_4F19_444E_B16B_26790D4B1929__INCLUDED_)
#define AFX_BRIDGESVR_H__C9E40903_4F19_444E_B16B_26790D4B1929__INCLUDED_

#include "SockSvr.h"	// Added by ClassView
#include "sock.h"
#include "SockBridge.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_BSOCKS	250

class CBridgeSvr : public CISockSrvEvents   
{
public:
	CSockBridge* GetFreeSock();
	DWORD Start(WORD wListenPort);
	DWORD SetListenPort(WORD wPort);
	DWORD SetDestAddress(BYTE b1, BYTE b2,BYTE b3, BYTE b4, WORD wPort);
	CBridgeSvr();
	virtual ~CBridgeSvr();
private:
	DWORD _stdcall OnConnect(CSock* pSock);
	
	// Direccion destino del puente
	BYTE		m_b1,m_b2,m_b3,m_b4;
	WORD		m_Port;
	CSockSvr	m_SockSvr;
	CSockBridge m_Socks[MAX_BSOCKS];
	WORD		m_ListenPort;


};

#endif // !defined(AFX_BRIDGESVR_H__C9E40903_4F19_444E_B16B_26790D4B1929__INCLUDED_)
