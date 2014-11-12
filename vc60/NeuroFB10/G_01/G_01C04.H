// G_01C04.h: interface for the C3DNave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C04_H__56304443_C74D_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C04_H__56304443_C74D_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "G_01C02.h"

class C3DNave : public C3DObject  
{
public:
	DWORD Initialize();
	virtual DWORD Paint();
	virtual DWORD Fly(DWORD pTime);
	BOOL	m_vuelta;
	DWORD	m_ang;
	double	m_dist;
	C3DNave();
	virtual ~C3DNave();

};

#endif // !defined(AFX_G_01C04_H__56304443_C74D_11D4_9126_0000E83D722B__INCLUDED_)
