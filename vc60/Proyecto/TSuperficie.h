// TSuperficie.h: interface for the TSuperficie class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSUPERFICIE_H__5C5A9159_379B_41FD_9B2D_B220C0FDD1EA__INCLUDED_)
#define AFX_TSUPERFICIE_H__5C5A9159_379B_41FD_9B2D_B220C0FDD1EA__INCLUDED_

#include "TVector.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TSuperficie  
{
public:
	void GetVectorP(float *px, float *py, float *pz);
	void GetVectorO(float *px, float *py, float *pz);
	void SetVectorO(float px,float py,float pz);
	void SetVectorP(float px,float py,float pz);
	void SetCoefRef(float pcr);
	float GetCoefRef();
	TVector VectorP,VectorO;
	float CoefRef;
	TSuperficie();
	~TSuperficie();

};

#endif // !defined(AFX_TSUPERFICIE_H__5C5A9159_379B_41FD_9B2D_B220C0FDD1EA__INCLUDED_)
