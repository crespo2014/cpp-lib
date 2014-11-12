// TReceptor.h: interface for the TReceptor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRECEPTOR_H__CB0BBCD1_B214_47C6_B694_257203EA6184__INCLUDED_)
#define AFX_TRECEPTOR_H__CB0BBCD1_B214_47C6_B694_257203EA6184__INCLUDED_

#include "TVector.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TReceptor  
{
public:
	void GetVectorP(float *px, float *py, float *pz);
	void GetVectorO(float* px,float* py,float* pz);
	float GetAreaCol();
	float GetAreaSup();
	float GetCampVista();
	void SetAreaCol(float pac);
	void SetAreaSup(float pac);
	void SetCampVista(float pac);
	void SetVectorO(float px,float py,float pz);
	void SetVectorP(float px,float py,float pz);
	TVector VectorP,VectorO;
	float	AreaCol,CampVista,AreaSup;
	TReceptor();
	~TReceptor();

};

#endif // !defined(AFX_TRECEPTOR_H__CB0BBCD1_B214_47C6_B694_257203EA6184__INCLUDED_)
