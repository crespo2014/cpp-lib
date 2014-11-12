// SyncCommPort.h: interface for the CSyncCommPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCCOMMPORT_H__D53B92E4_7B48_11D4_8CE6_00D0093847B4__INCLUDED_)
#define AFX_SYNCCOMMPORT_H__D53B92E4_7B48_11D4_8CE6_00D0093847B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncCommPort : public CObject  
{
public:
	DCB				dcb;
	COMMTIMEOUTS	CommTimeOuts;
	char			PortName[10];
	HANDLE			PortHandle;
	BOOL			OnOpen;
	DWORD			EventMask;

	int ReadBuffer(BYTE *pBuffer, DWORD pBufferLen,DWORD* pCantRead);
	int SendBuffer(BYTE *pBuffer, DWORD pCant);
	int SetPort(char *pPortName);
	int SetStopBits(BYTE pStopBits);
	int SetParity(DWORD pParity);
	int SetBaudRate(DWORD pBaudRate);
	int ApplyConfiguration();
	int ClosePort();
	int OpenPort();
	CSyncCommPort();
	virtual ~CSyncCommPort();

};

#endif // !defined(AFX_SYNCCOMMPORT_H__D53B92E4_7B48_11D4_8CE6_00D0093847B4__INCLUDED_)
