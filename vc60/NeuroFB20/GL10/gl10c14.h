 // gl10c14.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C14_H__B5A2FF41_2AC1_11D4_BC45_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C14_H__B5A2FF41_2AC1_11D4_BC45_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct 
{
	DWORD	nc,nf;
	float*	datos;
}S_MATRIX;

class CMatrix : public CObject  
{
public:
	S_MATRIX* m_Matrix;
	int InitMatrix();
	CMatrix();
	virtual ~CMatrix();
};

#endif // !defined(AFX_GL10C14_H__B5A2FF41_2AC1_11D4_BC45_0000E8DE4B3B__INCLUDED_)
