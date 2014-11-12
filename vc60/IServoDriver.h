// IServoDriver.h: interface for the IServoDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERVODRIVER_H__BCE4F56D_1A03_4008_99BE_230386E268AA__INCLUDED_)
#define AFX_ISERVODRIVER_H__BCE4F56D_1A03_4008_99BE_230386E268AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IServo.h" 

class IServoDriver
{
public:
	virtual DWORD _stdcall GetParamsCant(DWORD* pcant) = 0;
	virtual DWORD _stdcall GetParamData(DWORD pIndex,char** pName,char** pMeasureUnit) = 0;
	virtual DWORD _stdcall GetName(char** pName) = 0;
	virtual DWORD _stdcall GetServoForBed(DWORD pBedNo,IServo** pServo) = 0;
	virtual DWORD _stdcall SetCommunicationPort(DWORD pPortNo) = 0; 
	virtual DWORD _stdcall StartCommunication() = 0;
	virtual DWORD _stdcall Initialize() = 0;
};

#endif // !defined(AFX_ISERVODRIVER_H__BCE4F56D_1A03_4008_99BE_230386E268AA__INCLUDED_)
