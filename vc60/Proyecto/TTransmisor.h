// TTransmisor.h: interface for the TTransmisor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTRANSMISOR_H__F369B23A_2EB1_474D_BD27_245002FFEB7E__INCLUDED_)
#define AFX_TTRANSMISOR_H__F369B23A_2EB1_474D_BD27_245002FFEB7E__INCLUDED_

#include "TVector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TTransmisor  
{
public:
	void SetVectorP(float px,float py,float pz);
	void GetVectorP(float *px, float *py, float *pz);
	void GetVectorO(float *px, float *py, float *pz);
	float GetPotenciaRadiacion();
	void SetPotenciaRadiacion(float ppr);
	float GetPerfilRadiacion();
	void SetPerfilRadiacion(float ppr);
	void SetVectorO(float px,float py,float pz);
	TVector VectorP,VectorO;
	float	PerfRad;
	float	PotRad;
	TTransmisor();
	~TTransmisor();

};

#endif // !defined(AFX_TTRANSMISOR_H__F369B23A_2EB1_474D_BD27_245002FFEB7E__INCLUDED_)
