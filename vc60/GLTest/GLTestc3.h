// GLwind.h: interface for the CGLwind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLWIND_H__3C2EF641_DFBD_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_GLWIND_H__3C2EF641_DFBD_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10c5.h"
#include "gl10c11.h"
#include "gl10c12.h"

// dimensiones de la mesa en la que estaran las fichas
#define MESA_DX  40
#define	MESA_DY	40
#define MESA_MINX -20
#define MESA_MINY -20

class CGLwind : public CMemDCView  
{

public:
	int RenderDC(CDC *dc);
	double ang;
	CEscena	m_Escena;
	CDC		memdc;
	CBitmap	bitmap;
	float CurX,CurY;
	CGLwind();
	virtual ~CGLwind();

protected:
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_GLWIND_H__3C2EF641_DFBD_11D3_A036_0000E83D722B__INCLUDED_)
