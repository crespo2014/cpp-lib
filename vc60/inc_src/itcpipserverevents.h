// itcpipserverevents.h: interface for the ITcpIpServerEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITCPIPSERVEREVENTS_H__865E8495_BB19_48E8_8DD4_4FDFE0886359__INCLUDED_)
#define AFX_ITCPIPSERVEREVENTS_H__865E8495_BB19_48E8_8DD4_4FDFE0886359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ITcpIpServerEvents  
{
public:
	virtual DWORD _stdcall OnSocketClose(LPVOID lpParam,DWORD SockID,int iErrorCode)=0;
	virtual DWORD _stdcall OnSocketConnect(DWORD SockID)=0;
	virtual DWORD _stdcall OnServerProcessMessage(LP_MESSAGE lpMessage)=0;
	virtual DWORD _stdcall OnSocketWrite(LPVOID lpParam,DWORD SockID)=0;
	virtual DWORD _stdcall OnSocketWriteFailed(LPVOID lpParam,DWORD SockID,int iErrorCode)=0;
	virtual DWORD _stdcall OnSocketRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam,DWORD SockID)=0;
	virtual DWORD _stdcall OnSocketReadFailed(LPVOID lpParam,DWORD SockID,int iErrorCode)=0;
};

typedef ITcpIpServerEvents* LPTCPIPSERVEREVENTS;

#endif // !defined(AFX_ITCPIPSERVEREVENTS_H__865E8495_BB19_48E8_8DD4_4FDFE0886359__INCLUDED_)
