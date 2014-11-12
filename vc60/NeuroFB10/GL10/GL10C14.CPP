 // gl10c14.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c14.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix()
{
	InitMatrix();
}

CMatrix::~CMatrix()
{

}

int CMatrix::InitMatrix()
{
	m_Matrix = new S_MATRIX;
	m_Matrix->datos=NULL;
	m_Matrix->nc=0;
	m_Matrix->nf=0;
	return true;
}
