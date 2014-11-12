// TVector.cpp: implementation of the TVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TVector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TVector::TVector()
{
	x=0;
	y=0;
	z=0;
}

TVector::~TVector()
{

}

float TVector::GetX()
{
	return x;
}
float TVector::GetY()
{
	return y;
}
float TVector::GetZ()
{
	return z;
}

void TVector::SetX(float pX)
{
	x=pX;
}

void TVector::SetY(float pY)
{
	y=pY;
}

void TVector::SetZ(float pZ)
{
	z=pZ;
}