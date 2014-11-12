// SockSvr.h: interface for the CSockSvr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKSVR_H__E290CFD6_E615_46C0_BCEC_B62DB0F0B34E__INCLUDED_)
#define AFX_SOCKSVR_H__E290CFD6_E615_46C0_BCEC_B62DB0F0B34E__INCLUDED_

#include "Sock.h"	// Added by ClassView
#include "_IUnknown.h"
#include "Unknown.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_SOCKS	100

class ISockSrvEvents : public _IUnknown   
{
public:
	virtual DWORD _stdcall OnConnect(CSock* pSock) = 0;
};

class CISockSrvEvents : public ISockSrvEvents,
						protected CUnknown
{
protected:
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz)	{return CUnknown::QueryInterface(lpName,lpInterfaz);}
	virtual DWORD _stdcall AddRef()											{return CUnknown::AddRef();}
	virtual DWORD _stdcall Release()										{return CUnknown::Release();}
	virtual DWORD _stdcall Initialize()										{return CUnknown::Initialize();}
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz)		{return CUnknown::GetInterfaz(lpName,lpInterfaz);}
	virtual DWORD _stdcall DeleteObject()									{return CUnknown::DeleteObject();}
	virtual DWORD _stdcall UnInitialize()									{return CUnknown::UnInitialize();}
	//
	virtual DWORD _stdcall OnConnect(CSock* pSock)							{return ERR_INV_FUNC;};
};

class CSockSvr  
{
public:
	DWORD	SetEvents(ISockSrvEvents* pISockSrvEvents);
	DWORD	Start();
	DWORD	FillReadWriteSocks();
	DWORD	Start(WORD wPort);
	CSock*	GetFreeSock();
	CSockSvr();
	virtual ~CSockSvr();
private:
	CSock	m_Socks[MAX_SOCKS];
	fd_set	m_ReadSet;
	fd_set	m_WriteSet;
	fd_set	m_ErrorSet;
	WORD	m_Port;
	ISockSrvEvents*	m_ISockSrvEvents;
};

#endif // !defined(AFX_SOCKSVR_H__E290CFD6_E615_46C0_BCEC_B62DB0F0B34E__INCLUDED_)
