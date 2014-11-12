// LFC10C06.cpp: implementation of the CSignalFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sigC06.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSignalFilter::CSignalFilter()
{
	Init();
}

CSignalFilter::~CSignalFilter()
{
	delete CoefA;
	delete CoefB;
	delete TempIn;
	delete TempOut;
}

double CSignalFilter::GetOutput(double pInput)
{
	double OutValue=0.0;
	if (Order==0)
		return 0.0;
	OutValue=CoefB[0]*pInput;
	for (DWORD i=1;i<Order;i++)
	{
		OutValue+=CoefB[i]*TempIn[Order-i]-
			CoefA[i]*TempOut[Order-i];
	}
	memmove(&TempIn[0],&TempIn[1],(Order-1)*sizeof(double));
	memmove(&TempOut[0],&TempOut[1],(Order-1)*sizeof(double));
	TempIn[Order-1]=pInput;
	TempOut[Order-1]=OutValue;
	return OutValue;
}

int CSignalFilter::SetCoeficient(double *pCoefA, double *pCoefB, DWORD pOrder)
{
	if (Order != pOrder)
	{
		delete CoefA;
		delete CoefB;
		delete TempIn;
		delete TempOut;
		Order=pOrder;
		CoefA=new double[pOrder];
		CoefB=new double[pOrder];
		TempIn=new double[pOrder];
		TempOut=new double[pOrder];
	}
	memcpy(CoefA,pCoefA,pOrder*sizeof(double));
	memcpy(CoefB,pCoefB,pOrder*sizeof(double));
	memset(TempIn,0,sizeof(double)*pOrder);
	memset(TempOut,0,sizeof(double)*pOrder);
	return true;
}

int CSignalFilter::Init()
{
	CoefA=NULL;
	CoefB=NULL;
	Order=0;
	TempIn=NULL;
	TempOut=NULL;
	return true;
}
