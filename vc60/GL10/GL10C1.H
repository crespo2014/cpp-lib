// gl10c1.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C1_H__223B4DE1_E5F0_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_GL10C1_H__223B4DE1_E5F0_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatrix : public CObject  
{
public:
	int Destroy();
	int Init();
	int SetSize(int pFilas,int pColumnas);
	float*  m_pData;
	int		m_Filas;
	int		m_Columnas;
	CMatrix();
	virtual ~CMatrix();

};

#endif // !defined(AFX_GL10C1_H__223B4DE1_E5F0_11D3_A036_0000E83D722B__INCLUDED_)
