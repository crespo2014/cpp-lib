// GLwind.cpp: implementation of the CGLwind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLTest.h"
#include "GLwind.h"
#include "gl10c3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGLwind, CMemDCView)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

CGLwind::CGLwind()
{
	ang=0;
	CurX=0;
	CurY=0;
}

CGLwind::~CGLwind()
{
	
}

void CGLwind::OnTimer(UINT nIDEvent) 
{
	Invalidate(false);		
}

int CGLwind::RenderDC(CDC *dc)
{
	static BOOL first=true;
	if (first)
	{
		CClientDC dc(this);
		memdc.CreateCompatibleDC(&dc);
		bitmap.LoadBitmap(IDB_BITMAP1);
		memdc.SelectObject(&bitmap);
	} 
	first =false;
	CRect rect;
	GetClientRect(&rect);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glFinish();
	static BYTE posx=0;
	static int posy=0;
	posx++;
	char number[20];
	sprintf(number,"%d",posx);
	for (DWORD i=0; i< strlen(number);i++)
	{
		dc->BitBlt(i*20,0,20,44,&memdc,(number[i]-48)*20,0,SRCPAINT);
	}
	glPushMatrix();
	glLoadIdentity();
	glNormal3f(0,1,1);

	ang+=5;
	if (ang> 360) 
		ang=0;

	//gluLookAt(100*cos(ang*3.14/180),50,100*sin(ang*3.14/180),0,0,0,0,1,0);
	gluLookAt(10,50,100,10,10,0,0,1,0);
	glRotated(-90,1,0,0);
	int factor=10;

	glDisable(GL_LIGHTING);
	
	glColor3ub(255,255,255);
	glBegin(GL_LINES);
	  glColor3ub(255,0,0);
	  glVertex3d(0,0,0);
	  glVertex3d(factor,0,0);

	  glColor3ub(0,0,255);
	  glVertex3d(0,0,0);
	  glVertex3d(0,factor,0);

	  glColor3ub(0,255,0);
	  glVertex3d(0,0,0);
	  glVertex3d(0,0,factor);
	  // X
	  glColor3ub(255,0,0);
	  glVertex3d(1.1*factor,0.1*factor,0);
	  glVertex3d(1.3*factor,-0.1*factor,0);
	  glVertex3d(1.1*factor,-0.1*factor,0);
	  glVertex3d(1.3*factor,0.1*factor,0);
	  // Y
	  glColor3ub(0,0,255);
	  glVertex3d(-0.1*factor,1.1*factor,0);
	  glVertex3d(0.1*factor,1.3*factor,0);
	  glVertex3d(-0.1*factor,1.3*factor,0);
	  glVertex3d(0.0,1.2*factor,0);
	  // Z
	  glColor3ub(0,255,0);
	  glVertex3d(0,0.1*factor,1.3*factor);
	  glVertex3d(0,0.1*factor,1.1*factor);
	  glVertex3d(0,0.1*factor,1.1*factor);
	  glVertex3d(0,-0.1*factor,1.3*factor);
	  glVertex3d(0,-0.1*factor,1.3*factor);
	  glVertex3d(0,-0.1*factor,1.1*factor);
	glEnd();
	glFinish();

	/*
	m_Escena.SetVarValue("Ang_Hombro",ang);
	m_Escena.SetVarValue("Ang_Base",45);
	*/

	m_Escena.Paint();

	glEnable(GL_LIGHTING);
	glTranslated(CurX-20,-(CurY),0.0);
	CMeshMat* pMesh;
	pMesh=m_Escena.GetMesh("Ficha");
	if (pMesh)
		pMesh->Paint();

	glFlush();
	glPopMatrix();

	return true;	
}
void CGLwind::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect(&rect);
	CurX=MESA_MINX+MESA_DX*point.x/rect.Width();
	CurY=MESA_MINY+MESA_DY*point.y/rect.Height();
}

