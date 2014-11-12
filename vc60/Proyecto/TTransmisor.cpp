// TTransmisor.cpp: implementation of the TTransmisor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TTransmisor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TTransmisor::TTransmisor()
{
	PerfRad=0;
	PotRad=0;
}

TTransmisor::~TTransmisor()
{

}

float TTransmisor::GetPerfilRadiacion()
{
	return PerfRad;
}

void TTransmisor::SetPerfilRadiacion(float ppr)
{
	PerfRad=ppr;
}

void TTransmisor::SetVectorO(float px,float py,float pz)
{
	VectorO.SetX(px);
	VectorO.SetY(py);
	VectorO.SetZ(pz);
}

float TTransmisor::GetPotenciaRadiacion()
{
	return PotRad;
}
void TTransmisor::SetPotenciaRadiacion(float ppr)
{
	PotRad=ppr;
}

void TTransmisor::GetVectorO(float *px, float *py, float *pz)
{
	*px=VectorO.GetX();
	*py=VectorO.GetY();
	*pz=VectorO.GetZ();
	
}

void TTransmisor::GetVectorP(float *px, float *py, float *pz)
{
	*px=VectorP.GetX();
	*py=VectorP.GetY();
	*pz=VectorP.GetZ();
}

void TTransmisor::SetVectorP(float px, float py, float pz)
{
	VectorP.SetX(px);
	VectorP.SetY(py);
	VectorP.SetZ(pz);
}
