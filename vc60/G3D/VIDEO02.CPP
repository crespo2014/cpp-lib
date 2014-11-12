// Video02.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Video02.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

    GLfloat RedSurface[]={1.0f,0.0f,0.0f,1.0f};
	GLfloat GreenSurface[]={0.0f,1.0f,0.0f,1.0f};
	GLfloat BlueSurface[]={0.0f,0.0f,1.0f,1.0f};
	GLfloat WhiteSurface[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat GraySurface[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat Gray2Surface[]={1.0f,0.2f,0.2f,1.0f};
	GLfloat YellowSurface[]={1.0f,1.0f,0.0,1.0f};
	GLfloat BlackSurface[]={0.0f,0.0f,0.0,1.0f};
	GLfloat CarmelitaSurface[]={0.2f,0.2f,0.2f,1.0f};
	GLfloat OrangeSurface[]={1.0f,0.541176f,0.0823529f,1.0f};

	/*
		COLORREF color = ::GetSysColor(COLOR_3DFACE);
		glClearColor((float)GetRValue(color)/255.0f,
					 (float)GetGValue(color)/255.0f,
					 (float)GetBValue(color)/255.0f,
					 1.0);
					 */


/////////////////////////////////////////////////////////////////////////////
// CVideo02

CVideo02::CVideo02()
{
	m_Count=0;
	m_OnObject=false;
}

CVideo02::~CVideo02()
{
}


BEGIN_MESSAGE_MAP(CVideo02, CVideo)
	//{{AFX_MSG_MAP(CVideo02)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVideo02 message handlers

// procesador de mensajes del hilo de dibujo

int CVideo02::ThreadProcessMessages()
{
	switch(m_msg.message)
	{
	case WM_CHAR:
		{
			if (m_OnObject)
			{
				m_Count++;
			}
			break;
		}
	}
	return true;
}

int CVideo02::InitView(BOOL pOnSize)
{
	if (pOnSize)
	{
		GLdouble aspect;
		if (m_Height ==0)
			aspect=(GLdouble)m_Width;
		else
			aspect=(GLdouble)m_Width/(GLdouble)m_Height;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40,aspect,1,500);
		glMatrixMode(GL_MODELVIEW);
		return true;
	}
	SetResolution(10);
	if (!QueryPerformanceFrequency(&m_Frec))
		return false;
	glClearColor(0,0,0.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glDrawBuffer(GL_FRONT);
	glDrawBuffer(GL_BACK);
		
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);
	glDisable(GL_LIGHTING);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS,0); 
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	
	GLfloat LightAmbient0[] ={0.5f,0.5f,0.5f,1.0f};
	GLfloat LightDiffuse0[] ={0.2f,0.2f,0.2f,1.0f};
	GLfloat LightSpecular0[] ={1.0f,0.0f,0.0f,1.0f};
	GLfloat LightPosition0[] ={100.0,100.0,100.0,1.0};
	GLfloat LightDirection0[] ={0.0f,0.0f,-1.0f,1.0f};
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular0);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,LightDirection0);
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosition0);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,WhiteSurface);

	return true;
}

int CVideo02::RenderScene()
{
	CEsfera m_Esf;
	m_Esf.radio=5;
	if (!m_OnPlay)
		return true;
	if ((m_OnRC) &(m_OnPaint|m_OnPlay))
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		glPushMatrix();
		glTranslated(0,0,-40);
		
		m_Esf.Paint();
		glPopMatrix();
		glColor3ub(255,255,255);
		glRasterPos3d(1,0,-5);
		m_Number01.SetValue(m_Count);
		m_Number01.Paint();
		SwapBuffers(m_hDC);
		m_OnObject=true;
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		if (!Wait(2000))
			return false;
		m_OnObject=false;
		glColor3ub(255,255,255);

		glRasterPos3d(1,0,-5);
		m_Number01.SetValue(m_Count);
		m_Number01.Paint();
		SwapBuffers(m_hDC);
		if (!Wait(1000))
			return false;
	
	}
	return true;
}

// Esperar un tiempo determinado
int CVideo02::Wait(DWORD pTime)
{
	QueryPerformanceCounter(&m_LastCount);
	while (true)
	{
		if (!ProcessMessages())
			return false;
		Sleep(1);
		QueryPerformanceCounter(&m_CurrentCount);
		if (pTime < 1000*(m_CurrentCount.QuadPart-m_LastCount.QuadPart)/m_Frec.QuadPart)
		{
			return true;
		}
	}
		
}




