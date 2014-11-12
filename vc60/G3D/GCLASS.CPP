// GLGame.cpp : implementation file
//

#include "stdafx.h"
#include "gclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLGame

CGLGame::CGLGame()
{

}

CGLGame::~CGLGame()
{

}


BEGIN_MESSAGE_MAP(CGLGame,CGLView)
	//{{AFX_MSG_MAP(CGLGame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLGame message handlers

BOOL CGLGame::PreTranslateMessage(MSG* pMsg) 
{
	// Procesamiento del mensaje
	// Devolver true si no debe ser despachado
	return CWnd::PreTranslateMessage(pMsg);
}

int CGLGame::Init()
{

}

UINT CGLGame::ThreadMain()
{
	
	BOOL m_Dir=false;
	MSG m_msg;

	CGLFont m_font;
	SYSTEMTIME m_Time,m_TimeLast;
	char cadena1[50];
	char cadena2[50];
	
	m_GameParams.m_FireY=-1;
	m_GameParams.m_FireX=1;
	m_GameParams.m_FireFarZ=50;
	m_GameParams.m_FireVel=5;
	m_GameParams.m_FirePosX2;
	m_GameParams.m_FirePosY;


	m_ObjectParams[0].m_MaxZ=100;
	m_ObjectParams[0].m_PosZ=0;
	m_ObjectParams[0].m_Vel=0.5;
	m_ObjectParams[0].m_PosY=2;
	m_ObjectParams[0].m_PosX=0;
	m_ObjectParams[0].m_OnValid=true;

	ZeroMemory(m_GameParams.m_PointID,10*sizeof(DWORD));
	GetSystemTime(&m_TimeLast);
	BYTE m_FPS=0;
	BYTE m_FPSLast;
		
			
	int m_Key;
	DWORD i;
	int m_Width;
	int m_Height;
	GLdouble aspect;
	// Banderas
	BOOL m_OnSize=false;
	BOOL m_OnPlay=false;
	BOOL m_OnPaint=false;
	// Nave
	double m_angX=0;
	double m_dangX=5;

	
	// Colimador
	m_GameParams.m_PosX=0;
	m_GameParams.m_PosY=0;
	m_GameParams.m_PosZ=2;
	m_GameParams.m_dPos=1;
	
	// Movimiento del mouse
	
	double m_MouseX;
	double m_MouseY;
	

	// Caracteristicas del grafico
	double m_GrafMinZ=1;
	double m_GrafMaxZ=200;
	double m_GrafMinY;
	double m_GrafMaxY;
	double m_GrafMaxX;
	double m_GrafMinX;

	// otras banderas
	BOOL m_OnRC=false;
	

	// Piezas
	FillSin();
	SetResolution(20);
	CGLBmp m_GLBmp;

	for (i=0;i<10;i++)
	{
		m_FireData[i].m_OnValid=false;
		m_FireData[i].m_distz=100;
		m_ObjectParams[i].m_MaxZ=100;
		m_ObjectParams[i].m_PosZ=0;
		m_ObjectParams[i].m_Vel=0.5;
		m_ObjectParams[i].m_PosY=2;
		m_ObjectParams[i].m_PosX=0;
		m_ObjectParams[i].m_OnValid=true;
	}

	int r=1;
	// Inicializacion de las opengl

	while (true)
	{
	    if (!m_OnPlay)
			if (!PeekMessage(&m_msg,NULL,NULL,NULL,PM_NOREMOVE))
				WaitMessage();
	if (PeekMessage(&m_msg,NULL,NULL,NULL,PM_REMOVE))
	{
		switch(m_msg.message)
		{
		case UM_THREADACK:
			{
				SetEvent(m_GameParams.m_hEvent);
			}
		case UM_ATTACHRC:
			{
				m_OnRC=wglMakeCurrent((HDC)m_msg.lParam,(HGLRC)m_msg.wParam);
				InitView();
				GenGLList();
				break;
			}
		case UM_DESTROYRC:
			{
				wglMakeCurrent(NULL,NULL);
				wglDeleteContext(m_hGLRC);
				SetEvent(m_GameParams.m_hEvent);
				m_OnRC=false;
				m_OnSize=false;
				m_OnPlay=false;
				break;
			}
		case UM_RELEASERC:
			{
				wglMakeCurrent(NULL,NULL);
				m_OnRC=false;
				m_OnSize=false;
				m_OnPlay=false;
				SetEvent(m_GameParams.m_hEvent);
				break;
			}
		case UM_CLOSE:
			{
				SetEvent(m_GameParams.m_hEvent);
				return 0;
			}
		case WM_SIZE:
			{
				m_OnSize=true;
				m_Width=LOWORD(m_msg.lParam);
				m_Height=HIWORD(m_msg.lParam);
				
				if (m_Height ==0)
					aspect=(GLdouble)m_Width;
				else
					aspect=(GLdouble)m_Width/(GLdouble)m_Height;
				
				glViewport(0,0,m_Width,m_Height);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				

				gluPerspective(40,aspect,1,200);

				//glFrustum(-1,1,-1,1,1,200);
				m_GrafMaxY=m_GrafMinZ*Tangente(20);
				m_GrafMaxX=m_GrafMaxY*aspect;
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				
				glDrawBuffer(GL_BACK);
				break;
			}
		case WM_CLOSE:
			{
				wglMakeCurrent(NULL,NULL);
				wglDeleteContext(m_hGLRC);
				SetEvent(m_GameParams.m_hEvent);
				return 0;
			}
		case WM_PAINT:
			{
				m_OnPaint=true;
				SetEvent(m_GameParams.m_hEvent);
				break;
			}
		case MM_JOY1BUTTONDOWN:
		case MM_JOY2BUTTONDOWN:
			{
				if ((m_msg.wParam & JOY_BUTTON1CHG)|(m_msg.wParam & JOY_BUTTON2))
				{
					NewFire();
				}
				break;
			}
		case WM_KEYDOWN:
			{
				m_Key=(int)m_msg.wParam;
				switch(m_Key)
				{
				case 32:
					{
						NewFire();
						break;
					}
				case 0x28:
					{
						m_GameParams.m_MouseY+=10;
						break;
					}
				case 0x26:
					{
						m_GameParams.m_MouseY-=10;
						break;
					}
				case 0x27:
					{
						m_GameParams.m_MouseX+=10;
						break;
					}
				case 0x25:
					{
						m_GameParams.m_MouseX-=10;
						break;
					}
				}
				break;
			}
		case UM_COMMAND:
			{
				switch(m_msg.wParam)
				{
				case UC_BEGIN:
					{
						m_OnPlay=true;
						SetEvent(m_GameParams.m_hEvent);
						break;
					}
				case UC_PAUSE:
					{
						m_OnPlay=false;
						SetEvent(m_GameParams.m_hEvent);
						break;
					}
				case UC_END:
					{
						m_OnPlay=false;
						SetEvent(m_GameParams.m_hEvent);
						break;
					}

				}
				break;
			}
		}
	}
	if ((m_OnSize)&(m_OnPlay|m_OnPaint)&(m_OnRC))
	{
		
		m_OnPaint=false;
	
		if (m_GameParams.m_IsJoystick)
		{
			// Ajuste del colimador
			m_MouseX=m_GameParams.m_JoystickX;
			m_MouseY=m_GameParams.m_JoystickY;
		} else
		{
			m_MouseX=(double)m_GameParams.m_MouseX;
			m_MouseY=(double)m_GameParams.m_MouseY;
			
			if (m_MouseX<0)
				m_MouseX=0;
			if (m_MouseY<0)
				m_MouseY=0;
			if (m_MouseX > m_Width)
				m_MouseX=m_Width;
			if (m_MouseY>m_Height)
				m_MouseY=m_Height;
			m_MouseX=(double)m_MouseX/m_Width;
			m_MouseY=(double)m_MouseY/m_Height;
		}
				
		// Corregir posicion
		m_MouseY=1-m_MouseY*2;
		m_MouseX=m_MouseX*2-1;
		
		// Desnormalizar
		m_MouseY=m_MouseY*m_GrafMaxY;
		m_MouseX=m_MouseX*m_GrafMaxX;
		// calcular posicion del lente
		
		m_GameParams.m_PosY=m_MouseY*m_GameParams.m_PosZ/m_GrafMinZ;
		m_GameParams.m_PosX=m_MouseX*m_GameParams.m_PosZ/m_GrafMinZ;
		

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glPushMatrix();

		// Colimador
		glTranslated(m_GameParams.m_PosX,m_GameParams.m_PosY,-m_GameParams.m_PosZ);
		glCallList(m_GameParams.m_ListBase+2);
		glTranslated(-m_GameParams.m_PosX,-m_GameParams.m_PosY,m_GameParams.m_PosZ);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0,m_Width,0,m_Height,1,2);

		glRasterPos3d(0,m_Height-12,-1);
		GetSystemTime(&m_Time);

		if ((m_Time.wMinute-m_GameParams.m_STime.wMinute)>m_GameParams.m_CondMin)
			m_OnPlay=false;
		_itoa(m_Time.wHour,cadena1,10);
		m_font.PrintString(cadena1);
		m_font.PrintString(":");
		_itoa(m_Time.wMinute,cadena1,10);
	    m_font.PrintString(cadena1);
		m_font.PrintString(":");
		_itoa(m_Time.wSecond,cadena1,10);
		m_font.PrintString(cadena1);

		/*
		if(m_Time.wSecond>m_TimeLast.wSecond)
		{
			m_FPS=m_FPSLast/(double)1000/(m_Time.wMilliseconds+1000-m_TimeLast.wMilliseconds);
			m_FPSLast=0;
			m_TimeLast=m_Time;
		} else 
			m_FPSLast++;
			*/
		/*
		m_font.PrintString("FperS");
		_itoa(m_FPS,cadena1,10);
		m_font.PrintString(cadena1);
		*/

		glRasterPos3d(0,0,-1);
		_itoa(m_GameParams.m_JX,cadena1,10);
		m_font.PrintString("X : ");
		m_font.PrintString(cadena1);
		_itoa(m_GameParams.m_JY,cadena1,10);
		m_font.PrintString(" Y : ");
		m_font.PrintString(cadena1);




		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		
	
		CheckColision();
		MoveObjects();

		glPopMatrix();
		glFlush();
		SwapBuffers(m_hDC);
	}
	}
	
	return true;
}

int CGLGame::GenGLList()
{
	int i;
	CCilindroXY Cohete_01;
	CConoXY Cohete_02;

	m_GameParams.m_ListBase=glGenLists(5);
	if (m_GameParams.m_ListBase==0)
		return false;

	float scale=1;
	glNewList(m_GameParams.m_ListBase,GL_COMPILE);
	glBegin(GL_POLYGON);
	  glVertex3d(0,0,0);
	  glVertex3d(0,0,-5);
	  glVertex3d(1,1,-5);
	  glVertex3d(1,1,0);
    glEnd();

	glBegin(GL_POLYGON);
	  glVertex3d(0,0,0);
	  glVertex3d(0,0,-5);
	  glVertex3d(-1,1,-5);
	  glVertex3d(-1,1,0);
    glEnd();

	glColor3ub(255,0,0);
	glBegin(GL_POLYGON);
	  glVertex3d(1.5,0.5,0);
	  glVertex3d(1.5,0.5,-5);
	  glVertex3d(0.5,1.5,-5);
	  glVertex3d(0.5,1.5,0);
	 glEnd();

	 glBegin(GL_POLYGON);
	  glVertex3d(-1.5,0.5,0);
	  glVertex3d(-1.5,0.5,-5);
	  glVertex3d(-0.5,1.5,-5);
	  glVertex3d(-0.5,1.5,0);
	 glEnd();

	glEndList();

	
	float scale1=0.3f;

	glNewList(m_GameParams.m_ListBase+1,GL_COMPILE);
	glPushMatrix();

	glColor3ub(0,0,255);
	Cohete_01.Set(0.5*scale1,-5*scale1);
	Cohete_01.Paint();
	glTranslated(0,0,-5*scale1);
	Cohete_02.Set(0.5*scale1,-1.5);
	glColor3ub(255,0,0);
	Cohete_02.Paint();

	glPopMatrix();
	glEndList();

	glNewList(m_GameParams.m_ListBase+2,GL_COMPILE);
	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
	for (i=0;i<360;i+=45)
	{
		glVertex3d(0.05*Coseno(i),0.05*Seno(i),0);
	}
	glEnd();
	glEndList();

	glNewList(m_GameParams.m_ListBase+3,GL_COMPILE);
	
	glBegin(GL_TRIANGLES);
	  glColor3ub(255,0,0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(1.0*scale,0.0,0.0);
	  glVertex3d(0.0,0.0,-1.0*scale);
	  
	  glColor3ub(0,255,0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(0.5*scale,1.0,-0.5*scale);
	  glVertex3d(0.0,0.0,-1.0*scale);
		  
	  glColor3ub(200,200,200);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(1.0*scale,0.0,0.0);
	  glVertex3d(0.5*scale,1.0*scale,-0.5*scale);
		  
	  glColor3ub(0,0,255);
	  glVertex3d(0.0,0.0,-1.0);
	  glVertex3d(1.0*scale,0.0,0.0);
	  glVertex3d(0.5*scale,1.0*scale,-0.5*scale);
	glEnd();
	glEndList();

	m_ObjectParams[0].m_List=m_GameParams.m_ListBase+3+3;
	m_ObjectParams[0].m_ID=0;
	m_ObjectParams[1].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[0].m_ID=1;
	m_ObjectParams[2].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[0].m_ID=0;
	m_ObjectParams[3].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[4].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[5].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[6].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[7].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[8].m_List=m_GameParams.m_ListBase+3;
	m_ObjectParams[9].m_List=m_GameParams.m_ListBase+3;


	return true;
}

int CGLGame::Close()
{
	if (!m_OnInit)
		return true;
	PostThreadMessage(m_Thread->m_nThreadID,WM_CLOSE,0,0);
	WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	WaitForSingleObject(m_Thread->m_hThread,INFINITE);
	CloseHandle(m_GameParams.m_hEvent);
	
	UnlockResource(m_hSound1);
    UnlockResource(m_hSound2);
    FreeResource(m_hSound1);
    FreeResource(m_hSound2);

	sndPlaySound(NULL,0);
	
	m_OnInit=false;
	return true;
}

int CGLGame::PauseGame()
{

}

int CGLGame::BeginGame()
{
	return true;
}

int CGLGame::SetDevice(CDevice *pDevice)
{
}

BOOL  CGLGame::OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message )
{
	SetCursor(m_hCursor);
	return true;
}

int CGLGame::NewFire()
{
	return true;
}

int CGLGame::CheckColision()
{
	return true;
}

int CGLGame::MoveObjects()
{
	return true;
}

int CGLGame::GameInit()
{
}
int CGLGame::InitView()
{
	return true;
}



