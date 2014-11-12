// IServo.h: interface for the IServo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERVO_H__3A90AD36_CE5F_44EA_97DD_368D2B9B4FB0__INCLUDED_)
#define AFX_ISERVO_H__3A90AD36_CE5F_44EA_97DD_368D2B9B4FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IServo   
{
public:
	virtual DWORD _stdcall IsConnect() = 0;
	virtual DWORD _stdcall GetGraphs(float* pPressBuff,float* pFlowBuff,float* pVolBuff) = 0;
	virtual DWORD _stdcall GetGraphsLength(DWORD* plength) = 0;
	virtual DWORD _stdcall RequestGraph() = 0;
};

#endif // !defined(AFX_ISERVO_H__3A90AD36_CE5F_44EA_97DD_368D2B9B4FB0__INCLUDED_)
