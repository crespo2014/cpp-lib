// Video01.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Video01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideo01

CVideo01::CVideo01()
{
 	m_angulo=0;
}

CVideo01::~CVideo01()
{
}


BEGIN_MESSAGE_MAP(CVideo01, CVideo)
	//{{AFX_MSG_MAP(CVideo01)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVideo01 message handlers

int CVideo01::InitView(BOOL pOnSize)
{
	if (pOnSize)
	{
		GLdouble aspect;
		if (m_Height ==0)
			aspect=(GLdouble)m_Width;
		else
			aspect=(GLdouble)m_Width/(GLdouble)m_Height;
		//glPushAttrib(GL_MATRIX_MODE);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40,aspect,1,500);
		glMatrixMode(GL_MODELVIEW);
		// glPopAttrib();

		return true;
	}

	glClearColor(0,0,0.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_BACK);
		
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);
	glDisable(GL_LIGHTING);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);

	// creacion del Font
	m_Font1.CreateFont(GetDC(),"Arial Black");
	return true;
}

int CVideo01::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(-4.0,0,-10);
	glColor3ub(255,0,0);
	glTranslated(4,0,0);
	glRotated(m_angulo,0,1,0);
	glTranslated(-4,0,0);
	m_Font1.PrintString("Neuro");
	glColor3ub(0,255,0);
	m_Font1.PrintString("Games");
	m_Font1.PrintString(" Ver 1.0");
	if (m_OnPlay)
	{
		m_angulo+=5;
		if (m_angulo > 360 ) 
			m_angulo=0;
	}
	glPopMatrix();
	SwapBuffers(m_hDC);
	return true;
}

