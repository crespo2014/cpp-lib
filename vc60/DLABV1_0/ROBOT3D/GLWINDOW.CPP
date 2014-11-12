// GLWindow.cpp: implementation of the CGLWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLWindow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLWindow::~CGLWindow()
{

}

CGLWindow::CGLWindow()
{
	m_hGLContext=NULL;
	m_GLPixelIndex=0;
	m_lpx = 0.0f;
	m_lpy = 0.0f;
	m_lpz = 1.0f;
	FillSin();
	OnBegin=TRUE;
	TimerOn=FALSE;
	OnCapture=false;
	Camara_angx=0.0f;
	Camara_angy=0.0f;
	//Camara_dz=100;
	Camara_tox=0.0;
	Camara_toy=1.4;
	Camara_toz=100.0;
	Left_Button=false;
	OnCursor=true;
	m_On_RButton=false;
	m_On_LButton=false;
};

BEGIN_MESSAGE_MAP(CGLWindow, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()
	


BOOL CGLWindow::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style|=(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	return CWnd::PreCreateWindow(cs);
};

BOOL CGLWindow::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	pixelDesc.nSize =sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion=1;
	pixelDesc.dwFlags= PFD_DRAW_TO_WINDOW|
						PFD_SUPPORT_OPENGL|
						PFD_DOUBLEBUFFER|
						PFD_STEREO_DONTCARE;
	pixelDesc.iPixelType =PFD_TYPE_RGBA;
	pixelDesc.cColorBits=32;
	pixelDesc.cRedBits=8;
	pixelDesc.cRedShift=16;
	pixelDesc.cGreenBits=8;
	pixelDesc.cGreenShift=8;
	pixelDesc.cBlueBits=8;
	pixelDesc.cBlueShift=0;
	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits		= 64;	
	pixelDesc.cAccumRedBits		= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved		= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;

	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}

	return TRUE;

};

int CGLWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	if (CreateViewGLContext(hDC)==FALSE)
		return 0;

	return 0;
};

BOOL CGLWindow::CreateViewGLContext(HDC hDC)
{
	m_hGLContext=wglCreateContext(hDC);
	if (m_hGLContext == NULL)
	{
		return FALSE;
	}
	if (wglMakeCurrent(hDC,m_hGLContext) ==FALSE)
	{
		return FALSE;
	}
	return TRUE;
};

void CGLWindow::OnDestroy()
{
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (m_hGLContext!=NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext=NULL;
	}
	CWnd::OnDestroy();
};
 
void CGLWindow::SizeSetup()
{
	GLdouble aspect;
	if (Height ==0)
		aspect=(GLdouble)Width;
	else
		aspect=(GLdouble)Width/(GLdouble)Height;

	glViewport(0,0,Width,Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45,aspect,0.001,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDrawBuffer(GL_BACK);
	


}

void CGLWindow::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	Width=cx;
	Height=cy;
	SizeSetup();
	
};

void CGLWindow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RenderScene();
	SwapBuffers(dc.m_ps.hdc);
};

void CGLWindow::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	  /*
	  glTranslated(0.0,0.0,-Camara_dz);
	  // la traslacion es negativa porque hay que alejar el eje
	  glRotated(Camara_angx,1.0,0.0,0.0);
	  glRotated(Camara_angy,0.0,1.0,0.0);
	  glTranslated(-Camara_tox,-Camara_toy,-Camara_toz);
	  */
	  // El siguiente codigo es usado para un especifico
	  // movimiento de camara

	  glRotated(Camara_angx,1.0,0.0,0.0);
	  glRotated(Camara_angy,0.0,1.0,0.0);
	  glTranslated(-Camara_tox,-Camara_toy,-Camara_toz);
	  PaintNow();

    glPopMatrix();

}



void CGLWindow::OnLButtonDown( UINT nFlags, CPoint point )
{
	m_On_LButton=true;
	Left_Button=true;
	Left_Point=point;
	SetCapture();
	BeginTimer();

}

void CGLWindow::OnMouseMove( UINT nFlags, CPoint point )
{
	CSize rotate=point;
	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);
	ActiveCursor=LoadCursor(NULL,IDC_ARROW);

	// antes que nada para cambiar el cursor deben estar activo
	// los botones del mouse
	if (Left_Button)
	{
		rotate=Left_Point-point;
		if (rotate.cy >20)
			OnAcercar=true;
		else
			OnAcercar=false;
		if (rotate.cy <-20)
			OnAlejar=true;
		else
			OnAlejar=false;
		if (rotate.cx<-20)
			OnDerecha=true;
		else
			OnDerecha=false;
		if (rotate.cx>20)
			OnIzquierda=true;
		else
			OnIzquierda=false;
		int temp;
		temp=OnDerecha+OnAcercar*2+OnAlejar*4+OnIzquierda*8;
		switch (temp)
		{
		case 0: 
			{
				ActiveCursor=HCursor[0];
				break;
			}
		case 1:
			{
				ActiveCursor=HCursor[8];
				break;
			}
		case 2: 
			{
				ActiveCursor=HCursor[5];
				break;
			}
		case 3:
			{
				ActiveCursor=HCursor[7];
				break;
			}
		case 4:
			{
				ActiveCursor=HCursor[6];
				break;
			}
		case 5:
			{
				ActiveCursor=HCursor[9];
				break;
			}
		case 8:
			{
				ActiveCursor=HCursor[10];
				break;
			}
		case 10:
			{
				ActiveCursor=HCursor[12];
				break;
			}
		case 12:
			{
				ActiveCursor=HCursor[11];
				break;
			}

		}
		SetCursor(ActiveCursor);
		Cursor_dy=abs(rotate.cy)-10;
		Cursor_dx=abs(rotate.cx)-10;
	}
	if (m_On_RButton)
	{
		if (m_OnRel)
		{  
			// Diferencia entre los puntos
			m_dCursor=point-m_RPoint;
			// Para que la clase derivada procese el mensaje
			MouseMoving();
		}
	}

}

void CGLWindow::OnLButtonUp( UINT nFlags, CPoint point )
{
	Left_Button=false;
	EndTimer();
	m_On_LButton=false;
	if (!m_On_RButton) ReleaseCapture();
}

void CGLWindow::OnRButtonUp( UINT nFlags, CPoint point )
{
	m_On_RButton=false;
	if (!m_OnRel)
	{
		EndTimer();
	}
	if (!m_On_LButton) ReleaseCapture();
}

void CGLWindow::OnRButtonDown( UINT nFlags, CPoint point )
{
	m_On_RButton=true;
	m_RPoint=point;
	MouseClick();
	if (!m_OnRel)
	{
		BeginTimer();
	}
	SetCapture();
}

void CGLWindow::OnTimer( UINT nIDEvent )
{
	if (nIDEvent==1)
	{
		CheckAng();
		/*
		// Este Codigo es una forma de mover la imagen
		if (OnAcercar)
		Camara_toz-=(float)Cursor_dy*0.5;
		if (OnAlejar)
		Camara_toz+=(float)Cursor_dy*0.5;
		*/
		
		// Este codigo es otra dorma de mover la imagen
		
		if (OnAcercar)
		{
			// alejar pto de mira
			Camara_tox+=0.01*Cursor_dy*Seno((int)Camara_angy);
			Camara_toz-=0.01*Cursor_dy*Coseno((int)Camara_angy);
		}
		if (OnAlejar)
		{
			// alejar pto de mira
			Camara_tox-=0.01*Cursor_dy*Seno((int)Camara_angy);
			Camara_toz+=0.01*Cursor_dy*Coseno((int)Camara_angy);
		}
		
		// Otro tipo de movimiento de camara es utilizando el mismo
		// codigo anterior pero con otra transformacion de matrices
		
		// Este codigo es comun a cualquier movimiento
		if (OnDerecha)
			Camara_angy+=(float)Cursor_dx*0.01;
		if (OnIzquierda)
			Camara_angy-=(float)Cursor_dx*0.01;
		if (OnAcercar|OnAlejar|OnDerecha|OnIzquierda)
			Invalidate(TRUE);
	} else Timer();

}

void CGLWindow::BeginTimer()
{
	if (!TimerOn & OnCursor)
	{
		TimerID=SetTimer(1,25,NULL);
		TimerOn=TRUE;
		OnAcercar=false;
		OnAlejar=false;
		OnDerecha=false;
		OnIzquierda=false;
		SetCursor(HCursor[0]);
	}

}

void CGLWindow::EndTimer()
{
	if (TimerOn)
	{
		KillTimer(TimerID);
		TimerOn=false;
	}

}

void CGLWindow::CheckAng()
{
	// actualizacion de los angulos en el rango 0,360
	while (Camara_angx > 360)
		Camara_angx=Camara_angx-360;
	while (Camara_angx < 0)
		Camara_angx=Camara_angx+360;
	while (Camara_angy > 360)
		Camara_angy=Camara_angy-360;
	while (Camara_angx < 0)
		Camara_angy=Camara_angy+360;
}

void CGLWindow::SetMouse(BOOL estado)
{
	// Esta funcion permite que la camara sea sensible al mouse
	OnCursor=estado;
}

void CGLWindow::PaintNow()
{

}

void CGLWindow::MouseMoving()
{

}

void CGLWindow::MouseClick()
{

}

void CGLWindow::Timer()
{

}
