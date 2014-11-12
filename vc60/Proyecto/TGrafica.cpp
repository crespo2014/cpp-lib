// TGrafica.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "TGrafica.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TGrafica

TGrafica::TGrafica()
{
	x=50;
	y=50;
	z=50;
	escala=0;
}

TGrafica::~TGrafica()
{
}


BEGIN_MESSAGE_MAP(TGrafica, CStatic)
	//{{AFX_MSG_MAP(TGrafica)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TGrafica message handlers

void TGrafica::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.MoveTo(rect.Width()/2,rect.Height()/2);
	dc.LineTo(rect.Width(),rect.Height()/2);
	dc.LineTo(rect.Width()-5,rect.Height()/2-5);
	dc.MoveTo(rect.Width(),rect.Height()/2);
	dc.LineTo(rect.Width()-5,rect.Height()/2+5);


	dc.MoveTo(rect.Width()/2,rect.Height()/2);
	dc.LineTo(rect.Width()/2,0);
	dc.LineTo(rect.Width()/2+5,0+5);
	dc.MoveTo(rect.Width()/2,0);
	dc.LineTo(rect.Width()/2-5,0+5);
	
	dc.MoveTo(rect.Width()/2,rect.Height()/2);
	dc.LineTo(rect.Width()/4,(float)(rect.Height())*3.0f/4.0f);
	dc.LineTo(rect.Width()/4,(float)(rect.Height())*3.0f/4.0f-5);
	dc.MoveTo(rect.Width()/4,(float)(rect.Height())*3.0f/4.0f);
	dc.LineTo(rect.Width()/4+5,(float)(rect.Height())*3.0f/4.0f);

	dc.MoveTo(rect.Width()/2,rect.Height()/2);

	float px=(float)(rect.Width())/2;
	px=px+y*escala;
	px=px-x*escala/2;
	float py=(float)(rect.Height())/2;
	py=py-z*escala;
	py=py+x*escala/2;
	dc.FillSolidRect(px-1,py-1,3,3,0);
}
