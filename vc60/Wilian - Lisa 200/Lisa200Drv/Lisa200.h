// Lisa200.h: interface for the CLisa200 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA200_H__E8CC344A_47D3_4F22_9BBF_02CA9D662C25__INCLUDED_)
#define AFX_LISA200_H__E8CC344A_47D3_4F22_9BBF_02CA9D662C25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lisa200\Lisa2000Client.h"
#include "..\interfaces\ILabDevice.h"

class CLisa200 : public CLisa2000Client,
				 public ILabDevice
{
public:
	CLisa200();
	virtual ~CLisa200();

	// ILabDevice
	virtual DWORD _stdcall CheckCap(DWORD dwCapability);
	virtual DWORD _stdcall SetRemoteConfiguration(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port);
	virtual DWORD _stdcall SetLocalConfiguration(BYTE bPort,DWORD dwBaudRate,BYTE bParity,BYTE bStopBits);
	virtual DWORD _stdcall Connect();
	virtual DWORD _stdcall Disconnect();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall GetResults();
	virtual DWORD _stdcall GetResultByName(char* PatName,char* AnaName,float* lpResult);
	virtual DWORD _stdcall GetAnalisysByName(char* AnaName,char* unit,DWORD* dwMaxCount);
	virtual DWORD _stdcall GetResultByPos(DWORD PatPos,DWORD AnaPos,float* lpResult);

};

#endif // !defined(AFX_LISA200_H__E8CC344A_47D3_4F22_9BBF_02CA9D662C25__INCLUDED_)
