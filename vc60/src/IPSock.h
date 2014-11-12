// IPSock.h: interface for the CIPSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPSOCK_H__318C778C_BF02_4D81_9F3E_EDB9B214BD9B__INCLUDED_)
#define AFX_IPSOCK_H__318C778C_BF02_4D81_9F3E_EDB9B214BD9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITube.h"
#include "bobject.h"

/*
	Dispone de una tuberia para escribir datos y se le asigan uan tuberia de recepcion de datos 
	que puede ser sincronica  o asincronica.
*/ 

class CIPSock : 
	public CbObject, 
	public ITube  
{
public:
	DWORD Flush();
	DWORD system_init();
	DWORD create();
	DWORD connect(BYTE* ip,WORD port);
	DWORD readInput();
	void setRecvTube(ITube* ptube);
	DWORD flush();
	ITube* getSendTube();
	CIPSock();
	virtual ~CIPSock();

	virtual DWORD	Start();
	virtual DWORD	End();
	virtual DWORD	Push(BYTE b);

private:
	DWORD	m_ip;
	WORD	m_port;
	struct  in_addr m_dest_ip;		// Direccion destino
	DWORD	m_read_timeout;			// tiempo de esperad de datos
	DWORD	m_interval_timout;		// tiempo maximo entre un byte y otro

	int		m_handle;
	struct sockaddr_in m_sock_addr;	// datos de la conecion 

	BYTE	mOutBuffer[255];
	BYTE	mOutBufferCount;


};

#endif // !defined(AFX_IPSOCK_H__318C778C_BF02_4D81_9F3E_EDB9B214BD9B__INCLUDED_)
