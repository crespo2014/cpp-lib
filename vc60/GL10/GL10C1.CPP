// gl10c1.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c1.h"

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
	Init();
}

CMatrix::~CMatrix()
{

}

int CMatrix::SetSize(int pFilas, int pColumnas)
{
	Destroy();
	m_pData= new float[pFilas*pColumnas];
	if (m_pData == NULL)
		return false;
	m_Filas=pFilas;
	m_Columnas=pColumnas;
	return true;
}

int CMatrix::Init()
{
	m_pData=NULL;
	m_Filas=0;
	m_Columnas=0;
	return true;
}

int CMatrix::Destroy()
{
	delete m_pData;
	Init();
	return true;
}
