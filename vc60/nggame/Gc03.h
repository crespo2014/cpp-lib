// G_01C03.h: interface for the C3DCohete class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C03_H__56304442_C74D_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C03_H__56304442_C74D_11D4_9126_0000E83D722B__INCLUDED_

#include "gdef.h"
#include "GC02.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C3DCohete : public C3DObject  
{
public:
	virtual DWORD Paint();
	virtual DWORD Fly(DWORD pTime);
	C3DCohete();
	virtual ~C3DCohete();
	// Datos de los disparos
	double m_angxz,m_angyz;
	double relacionxz,relacionyz;
};

#endif // !defined(AFX_G_01C03_H__56304442_C74D_11D4_9126_0000E83D722B__INCLUDED_)
