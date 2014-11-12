// TVector.h: interface for the TVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVECTOR_H__F81F86D9_FD30_44B6_B421_1A082EFDCABF__INCLUDED_)
#define AFX_TVECTOR_H__F81F86D9_FD30_44B6_B421_1A082EFDCABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TVector  
{
public:
	void SetX(float pX);
	void SetY(float pY);
	void SetZ(float pZ);
	float GetX();
	float GetY();
	float GetZ();
	float x,y,z;
	TVector();
	~TVector();

};

#endif // !defined(AFX_TVECTOR_H__F81F86D9_FD30_44B6_B421_1A082EFDCABF__INCLUDED_)
