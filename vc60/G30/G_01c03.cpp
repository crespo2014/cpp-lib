// G_01C023cpp.cpp: implementation of the C3DCohete class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G_01C03.h"
#include "G_01C08.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DCohete::C3DCohete()
{

}

C3DCohete::~C3DCohete()
{

}

DWORD C3DCohete::Fly(DWORD pTime)
{
	m_currentz-=400;
	m_currenty=m_starty+((m_lasty-m_starty)*(m_currentz-m_startz)/(m_lastz-m_startz));
	m_currentx=m_startx+((m_lastx-m_startx)*(m_currentz-m_startz)/(m_lastz-m_startz));
	if (m_currentz < -10000)
		m_delete=true;
	return 0;
}

DWORD C3DCohete::Paint()
{
	glPushMatrix();
	/*
	GLdouble pMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,pMatrix);
	*/
	glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex3d(m_startx,m_starty,m_startz);
		glVertex3d(m_lastx,m_lasty,m_lastz);
	glEnd();
	glTranslated(m_currentx,m_currenty,m_currentz);
	glRotated(m_angxz,1,0,0);
	glRotated(m_angyz,0,1,0);
	C3DObject::Paint();
	glPopMatrix();
	//glLoadMatrixd(pMatrix);
	return true;
}
