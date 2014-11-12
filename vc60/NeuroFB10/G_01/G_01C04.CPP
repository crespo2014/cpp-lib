// G_01C04cpp.cpp: implementation of the C3DNave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G_01C04.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DNave::C3DNave()
{
	Initialize();
}

C3DNave::~C3DNave()
{

}

DWORD C3DNave::Fly(DWORD pTime)
{
	m_currentz+=150;
	if (m_currentz > -1 )
		Initialize();
	return 0;
}

DWORD C3DNave::Paint()
{
	glPushMatrix();
	/*
	GLdouble pMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,pMatrix);
	*/
	glTranslated(m_currentx,m_currenty,m_currentz);
	if (m_vuelta)
	{
		glRotated(m_ang,1,1,0);
		m_ang+=20;
		if (m_ang > 360)
			m_ang=0;
	}
	C3DObject::Paint();
	//glLoadMatrixd(pMatrix);
	glPopMatrix();
	return 0;
}

DWORD C3DNave::Initialize()
{
	m_vuelta=false;
	m_ang=0;
	m_currentx=((double)rand()/RAND_MAX)*2000-1000;
	m_currenty=((double)rand()/RAND_MAX)*2000-1000;
	m_currentz=((double)rand()/RAND_MAX)*10000-15000;	
	return 0;
}
