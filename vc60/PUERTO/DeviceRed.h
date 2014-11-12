// DeviceRed.h: interface for the CDeviceRed class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICERED_H__D53B92E5_7B48_11D4_8CE6_00D0093847B4__INCLUDED_)
#define AFX_DEVICERED_H__D53B92E5_7B48_11D4_8CE6_00D0093847B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyncCommPort.h"

 class CDeviceRed : public CSyncCommPort  
{
public:
	int SendFrame(BYTE* pBuffer,DWORD pCant);
	CDeviceRed();
	virtual ~CDeviceRed();

};

#endif // !defined(AFX_DEVICERED_H__D53B92E5_7B48_11D4_8CE6_00D0093847B4__INCLUDED_)
