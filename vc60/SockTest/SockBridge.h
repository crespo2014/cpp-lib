// SockBridge.h: interface for the CSockBridge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKBRIDGE_H__6B85E609_28CE_4225_A879_6DE31432D641__INCLUDED_)
#define AFX_SOCKBRIDGE_H__6B85E609_28CE_4225_A879_6DE31432D641__INCLUDED_

#include "sock.h"
#include "TrafficFile.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SCKB_NONE		0
#define SCKB_CONNECTING	1	// Conectando socket destino
#define SCKB_CONNECT	2	// Socket destino conectado inicializandose
#define SCKB_BICONNECT	3	// Flujo de coneccion establecido

class CSockBridge : private ISockEvents 
{
public:
	CTrafficFile TrafficFile;
	BOOL  OnConnect(){return m_Status != SCKB_NONE;};
	DWORD RecvAndSend(CSock* pRcvSock,CSock* pSndSock);
	DWORD Close();
	DWORD ConnectSock(CSock* src, CSock* dest,BYTE b1,BYTE b2,BYTE b3,BYTE b4,WORD wPort);
	CSockBridge();
	virtual ~CSockBridge();
private:
	DWORD _stdcall OnProcessRead(CSock* pSock);
	DWORD _stdcall OnProcessWrite(CSock* pSock);
	DWORD _stdcall OnClose(CSock* pSock);
	DWORD _stdcall OnConnect(CSock* pSock);
	CSock* m_destSock;
	CSock* m_srcSock;
	DWORD	m_Status;

};

#endif // !defined(AFX_SOCKBRIDGE_H__6B85E609_28CE_4225_A879_6DE31432D641__INCLUDED_)
