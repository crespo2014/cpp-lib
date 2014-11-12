// LFC10C06.h: interface for the CSignalFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC10C06_H__8D2EE1E1_7C43_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_LFC10C06_H__8D2EE1E1_7C43_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSignalFilter  
{
public:
	int Init();
	int SetCoeficient(double* pCoefA,double* pCoefB,DWORD pOrder);
	double GetOutput(double pInput);
	CSignalFilter();
	virtual ~CSignalFilter();
	DWORD	Order;
	double* CoefA;
	double* CoefB;
	double* TempIn;
	double* TempOut;

};

#endif // !defined(AFX_LFC10C06_H__8D2EE1E1_7C43_11D4_8632_00D0093D4380__INCLUDED_)
