// TReceptor.cpp: implementation of the TReceptor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TReceptor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TReceptor::TReceptor()
{
	AreaCol=0;
	AreaSup=0;
	CampVista=0;
}

TReceptor::~TReceptor()
{

}

void TReceptor::SetVectorO(float px,float py,float pz)
{
	VectorO.SetX(px);
	VectorO.SetY(py);
	VectorO.SetZ(pz);
}

void TReceptor::SetVectorP(float px,float py,float pz)
{
	VectorP.SetX(px);
	VectorP.SetY(py);
	VectorP.SetZ(pz);
}

void TReceptor::SetAreaCol(float pac)
{
	AreaCol=pac;
}

void TReceptor::SetAreaSup(float pas)
{
	AreaSup=pas;
}

void TReceptor::SetCampVista(float pcv)
{
	CampVista=pcv;
}

float TReceptor::GetAreaCol()
{
	return AreaCol;
}

float TReceptor::GetAreaSup()
{
	return AreaSup;
}

float TReceptor::GetCampVista()
{
	return CampVista;
}

void TReceptor::GetVectorO(float *px, float *py, float *pz)
{
	*px=VectorO.GetX();
	*py=VectorO.GetY();
	*pz=VectorO.GetZ();
}

void TReceptor::GetVectorP(float *px, float *py, float *pz)
{
	*px=VectorP.GetX();
	*py=VectorP.GetY();
	*pz=VectorP.GetZ();
}
