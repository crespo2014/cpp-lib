// ISocketEvents.h: interface for the ISocketEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISOCKETEVENTS_H__11CDD91D_7203_4A04_87AF_45C9ECB72379__INCLUDED_)
#define AFX_ISOCKETEVENTS_H__11CDD91D_7203_4A04_87AF_45C9ECB72379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ITcpIpSocketEvents  
{
public:
	virtual DWORD _stdcall OnClose(LPVOID lpParam,int iErrorCode)=0;
	virtual DWORD _stdcall OnConnect(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnConnectFailed(LPVOID lpParam,int iErrorCode)=0;
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnWrite(LPVOID lpParam)=0;	// Ya se proceso la ultima escritura
	virtual DWORD _stdcall OnWriteFailed(LPVOID lpParam,int iErrorCode)=0;
	virtual DWORD _stdcall OnRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnReadFailed(LPVOID lpParam,int iErrorCode)=0;
};

typedef ITcpIpSocketEvents* LPTCPIPSOCKETEVENTS;

#endif // !defined(AFX_ISOCKETEVENTS_H__11CDD91D_7203_4A04_87AF_45C9ECB72379__INCLUDED_)
