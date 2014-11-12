// ICommunicationBridgeEvents.h: interface for the ICommunicationBridgeEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMUNICATIONBRIDGEEVENTS_H__2F64EAB9_0FD8_4908_BC7D_2A1A18BBC7CD__INCLUDED_)
#define AFX_ICOMMUNICATIONBRIDGEEVENTS_H__2F64EAB9_0FD8_4908_BC7D_2A1A18BBC7CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ICommunicationBridgeEvents  
{
public:
	virtual DWORD _stdcall OnBridgeSndBuffer(BYTE *buffer, DWORD dwsize)=0;
	virtual DWORD _stdcall OnBridgeRcvBuffer(BYTE *buffer, DWORD dwsize)=0;
	virtual DWORD _stdcall OnBridgeSndPortEvent(DWORD pEventMask)=0;
	virtual DWORD _stdcall OnBridgeRcvPortEvent(DWORD pEventMask)=0;
	virtual DWORD _stdcall OnBridgePortOpen(LPVOID lpParam)=0;
};

typedef ICommunicationBridgeEvents* LPCOMMUNICATIONBRIDGEEVENTS;

#endif // !defined(AFX_ICOMMUNICATIONBRIDGEEVENTS_H__2F64EAB9_0FD8_4908_BC7D_2A1A18BBC7CD__INCLUDED_)
