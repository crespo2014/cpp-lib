// ILabDevice.h: interface for the ILabDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILABDEVICE_H__1C4DBD62_61AD_4261_9EA9_FC50ED28F772__INCLUDED_)
#define AFX_ILABDEVICE_H__1C4DBD62_61AD_4261_9EA9_FC50ED28F772__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lisa200\lisa2000def.h"

#define CAP_LOCALCONNECTION	 1
#define CAP_REMOTECONNECTION 2

class ILabDevice  
{
public:
	virtual DWORD _stdcall CheckCap(DWORD dwCapability)=0;
	virtual DWORD _stdcall SetRemoteConfiguration(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port)=0;
	virtual DWORD _stdcall SetLocalConfiguration(BYTE bPort,DWORD dwBaudRate,BYTE bParity,BYTE bStopBits)=0;
	virtual DWORD _stdcall Connect()=0;
	virtual DWORD _stdcall Disconnect()=0;
	virtual DWORD _stdcall Initialize()=0;
	virtual DWORD _stdcall GetResults()=0;
	virtual DWORD _stdcall GetResultByName(char* PatName,char* AnaName,float* lpResult)=0;
	virtual DWORD _stdcall GetAnalisysByName(char* AnaName,char* unit,DWORD* dwMaxCount)=0;
	virtual DWORD _stdcall GetResultByPos(DWORD PatPos,DWORD AnaPos,float* lpResult)=0;
};

#endif // !defined(AFX_ILABDEVICE_H__1C4DBD62_61AD_4261_9EA9_FC50ED28F772__INCLUDED_)
