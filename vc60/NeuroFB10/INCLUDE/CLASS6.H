// class6.h: interface for the CGLCilinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASS6_H__6D6CC641_E05A_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASS6_H__6D6CC641_E05A_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "class2.h"
#include "class6.h"
#include "Dlg1.h"

/*

*/

typedef struct
{
	DWORD	m_Version;
	double radio;
	double altura;
	double begin_ang;
	double end_ang;
	double resolucion;
	BOOL Tapa1;
	BOOL Tapa0;
} S_CILINDERINFO;

typedef struct
{
	S_CILINDERINFO m_Disk;
} S_GLCilinder;

class AFX_EXT_CLASS CGLCilinder : public C3DObject  
{
public:
	int Init();
	virtual int VReadData(FILE *pFile);
	virtual int VSaveData(FILE *pFile);
	virtual int VGeneratePrimitive();
	virtual int VConfigure();
	int SaveDataToFile(FILE *pFile);
	int SetAng(double pBegin, double pEnd);
	int Set(double pradio,double paltura);
	virtual int EnabledFaces(DWORD pFaces);
	virtual int VPaint();
	S_GLCilinder* m_GLCilinder;
	CGLCilinder();
	virtual ~CGLCilinder();

};

#endif // !defined(AFX_CLASS6_H__6D6CC641_E05A_11D3_A036_0000E83D722B__INCLUDED_)
