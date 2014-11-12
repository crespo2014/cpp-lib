// TSuperficie.cpp: implementation of the TSuperficie class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSuperficie.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TSuperficie::TSuperficie()
{
	CoefRef=0;
}

TSuperficie::~TSuperficie()
{

}

void TSuperficie::SetVectorO(float px,float py,float pz)
{
	VectorO.SetX(px);
	VectorO.SetY(py);
	VectorO.SetZ(pz);
}

void TSuperficie::SetVectorP(float px,float py,float pz)
{
	VectorP.SetX(px);
	VectorP.SetY(py);
	VectorP.SetZ(pz);
}

void TSuperficie::SetCoefRef(float pcr)
{
	CoefRef=pcr;
}

float TSuperficie::GetCoefRef()
{
	return CoefRef;
}

void TSuperficie::GetVectorO(float *px, float *py, float *pz)
{
	*px=VectorO.GetX();
	*py=VectorO.GetY();
	*pz=VectorO.GetZ();	
}

void TSuperficie::GetVectorP(float *px, float *py, float *pz)
{
	*px=VectorP.GetX();
	*py=VectorP.GetY();
	*pz=VectorP.GetZ();
}
