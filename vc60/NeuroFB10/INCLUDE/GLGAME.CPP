// GLGame.cpp : implementation file
//

#include "stdafx.h"
#include "GLGame.h"

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


BEGIN_MESSAGE_MAP(CGLGame, CGLView)
	//{{AFX_MSG_MAP(CGLGame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_SIZE()
		ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLGame message handlers

UINT CGLGame::Thread(LPVOID pParam)
{
	return ((CGLGame*)pParam)->ThreadMain();
}

BOOL CGLGame::PreTranslateMessage(MSG* pMsg) 
{
	// Procesamiento del mensaje
	// Devolver true si no debe ser despachado

	switch (pMsg->message)
	{
	case MM_JOY1MOVE:
		{
			m_GameParams.m_MouseX=LOWORD(pMsg->lParam)*m_Joystick.m_SmaxX/m_Joystick.m_JmaxX;
			m_GameParams.m_MouseY=HIWORD(pMsg->lParam)*m_Joystick.m_SmaxY/m_Joystick.m_JmaxY;
			return true;
		}
	case MM_JOY1BUTTONDOWN:
	case MM_JOY1BUTTONUP:
		{
			/*
			if (pMsg->wParam & JOY_BUTTON1)
				sndPlaySound((char*)m_lpSound1,SND_ASYNC | SND_MEMORY);
				*/
			PostThreadMessage(m_Thread->m_nThreadID,MM_JOY1BUTTONDOWN,pMsg->wParam,pMsg->lParam);						
			return true;
		}
	case WM_CLOSE:
		{
			PostThreadMessage(m_Thread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
		}
	}


	if ((pMsg->message>=WM_KEYFIRST)&(pMsg->message<=WM_KEYLAST+1))
	{
		PostThreadMessage(m_Thread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
		return false;
	}
	if((pMsg->message>=WM_MOUSEFIRST)&(pMsg->message<=WM_MOUSELAST))
	{
		PostThreadMessage(m_Thread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
		return true;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

int CGLGame::Init()
{
	m_Joystick.SetWnd(GetSafeHwnd());
	m_Joystick.Init();

	m_GameParams.m_hEvent=CreateEvent(NULL,false,false,NULL);
	if (!m_GameParams.m_hEvent)
		TRACE0("Creating Event Failed");

	wglMakeCurrent(NULL,NULL);

	m_Thread=AfxBeginThread(Thread,this,THREAD_PRIORITY_ABOVE_NORMAL);
	PostThreadMessage(m_Thread->m_nThreadID,UM_ACK,0,0);
	WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	return true;
}

UINT CGLGame::ThreadMain()
{
	BOOL m_Dir=false;
	MSG m_msg;

	FireData m_FireData[10];
	double   m_FireY=-1;
	double   m_FireX=1;
	double   m_FireFarZ=50;
	double   m_FireVel=5;
	double   m_FirePosX1;
	double   m_FirePosX2;
	double   m_FirePosY;

	ObjectData m_ObjectData[10];
	m_ObjectData[0].m_MaxZ=100;
	m_ObjectData[0].m_PosZ=0;
	m_ObjectData[0].m_Vel=0.5;
	m_ObjectData[0].m_PosY=2;
	m_ObjectData[0].m_PosX=0;
	m_ObjectData[0].m_OnValid=true;
	
	double m_ImpactDist;
	int m_Points=0;
	
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
	double m_PosX=0;
	double m_PosY=0;
	double m_PosZ=2;
	double m_dPos=0.06;
	// Movimiento del mouse
	
	double m_MouseX;
	double m_MouseY;
	

	// Caracteristicas del grafico
	int m_GrafMinZ=1;
	int m_GrafMaxZ=200;
	double m_MaxY;
	double m_MaxX;




	// Piezas
	FillSin();
	SetResolution(20);
	CGLBmp m_GLBmp;
	CGlNumber m_Score;
	m_Score.m_Number=0;

	for (i=0;i<10;i++)
	{
		m_FireData[i].m_OnValid=false;
		m_FireData[i].m_distz=100;
	}

	int r=1;
	// Inicializacion de las opengl

	if (!wglMakeCurrent(m_hDC,m_hGLRC))
		return 56;

	COLORREF color = GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
		(float)GetGValue(color)/255.0f,
		(float)GetBValue(color)/255.0f,
		1.0);

	glClearColor(0,0,0,1);
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

	// definicion de los parametros de la textura
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	/*
	m_GLBmp.SetFile("space.bmp");
	m_GLBmp.OpenFile();
	m_GLBmp.BGRtoRGB();
    glTexImage2D(GL_TEXTURE_2D,0,3,m_GLBmp.m_Width,m_GLBmp.m_Height,0,GL_RGB,GL_UNSIGNED_BYTE,m_GLBmp.m_Data);
	
	glReadBuffer(GL_BACK);
	*/

	GenGLList();
	while (true)
	{
	    if (!m_OnPlay)
			WaitMessage();

	if (PeekMessage(&m_msg,NULL,NULL,NULL,PM_REMOVE))
	{
		switch(m_msg.message)
		{
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
				

				//gluPerspective(40,aspect,1,200);
				glFrustum(-1,1,-1,1,1,200);
				m_MaxY=1;
				m_MaxX=1;
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
			{
				if (m_msg.wParam & JOY_BUTTON1CHG)
				{
					//NewFire();
					for (i=0;i<10;i++)
					{
						if (m_FireData[i].m_distz < 10)
							break;
						if (!m_FireData[i].m_OnValid)
						{
							m_FireData[i].m_distz=0;
							m_FireData[i].m_OnValid=true;
							m_FireData[i].m_LastY=m_FireFarZ*m_PosY/2;
							m_FireData[i].m_LastX=m_FireFarZ*m_PosX/2;
							m_FireData[i].m_angXZ=atan2(m_FireFarZ*m_PosY/2-m_FireY,m_FireFarZ-1)*180/3.14;
							m_FireData[i].m_angYZ1=atan2(m_PosX*m_FireFarZ/2-m_FireX,m_FireFarZ-1)*180/3.14;
							m_FireData[i].m_angYZ2=atan2(m_PosX*m_FireFarZ/2+m_FireX,m_FireFarZ-1)*180/3.14;
							break;
						}
						
					}
					break;
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
						for (i=0;i<10;i++)
						{
							if (m_FireData[i].m_distz < 10)
								break;
							if (!m_FireData[i].m_OnValid)
							{
								m_FireData[i].m_distz=0;
								m_FireData[i].m_OnValid=true;
								m_FireData[i].m_LastY=m_FireFarZ*m_PosY/2;
								m_FireData[i].m_LastX=m_FireFarZ*m_PosX/2;
								m_FireData[i].m_angXZ=atan2(m_FireFarZ*m_PosY/2-m_FireY,m_FireFarZ-1)*180/3.14;
								m_FireData[i].m_angYZ1=atan2(m_PosX*m_FireFarZ/2-m_FireX,m_FireFarZ-1)*180/3.14;
								m_FireData[i].m_angYZ2=atan2(m_PosX*m_FireFarZ/2+m_FireX,m_FireFarZ-1)*180/3.14;
								break;
							}
							
						}
						break;
					}
				case 0x28:
					{
						m_PosY-=m_dPos;
						break;
					}
				case 0x26:
					{
						m_PosY+=m_dPos;
						break;
					}
				case 0x27:
					{
						m_PosX+=m_dPos;
						break;
					}
				case 0x25:
					{
						m_PosX-=m_dPos;
						break;
					}
				}
				break;
			}
		case UM_ACK:
			{
				SetEvent(m_GameParams.m_hEvent);
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
	if ((m_OnSize)&(m_OnPlay|m_OnPaint))
	{
		
		m_OnPaint=false;

		// Ajuste del colimador
		m_MouseX=m_GameParams.m_MouseX;
		m_MouseY=m_GameParams.m_MouseY;

		if (m_MouseX<0)
			m_MouseX=0;
		if (m_MouseY<0)
			m_MouseY=0;
		if (m_MouseX > m_Width)
			m_MouseX=m_Width;
		if (m_MouseY>m_Height)
			m_MouseY=m_Height;
		
		// Normalizar coordenadas
		m_MouseY=m_MouseY/m_Height*2;
		m_MouseX=m_MouseX/m_Width*2;
		
		// Corregir posicion
		m_MouseY=1-m_MouseY;
		m_MouseX=m_MouseX-1;
		
		// Desnormalizar
		m_MouseY=m_MouseY*m_MaxY;
		m_MouseX=m_MouseX*m_MaxX;
		// calcular posicion del lente
		
		m_PosY=m_MouseY*m_PosZ/m_GrafMinZ;
		m_PosX=m_MouseX*m_PosZ/m_GrafMinZ;
		

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glPushMatrix();

		/*7
		glDisable(GL_DEPTH_TEST);
		glColor3ub(255,255,255);
		glRasterPos3d(-1,-1,-1);
		glDrawPixels(512,512,GL_BGR_EXT,GL_UNSIGNED_BYTE,m_GLBmp.m_Data);
		*/
		
		//glAccum(GL_RETURN,1);
		glEnable(GL_DEPTH_TEST);
		
		// Colimador
		glTranslated(m_PosX,m_PosY,-2.0);
		glCallList(m_GameParams.m_ListBase+2);
		glTranslated(-m_PosX,-m_PosY,2.0);

		glRasterPos3d(-1,-1,-1);
		m_Score.Paint();
		/*
		glPushMatrix();
		glTranslated(1,-1,-1);
		glCallList(m_List_Base+1);
		glTranslated(-2.0,0,0);
		glCallList(m_List_Base+1);
		glPopMatrix();
		*/
	
		// Cohetes
		for (i=0;i<10;i++)
		{
			if (m_FireData[i].m_OnValid)
			{
				// Chequeo de colision				
				m_FirePosY=(m_FireData[i].m_LastY-m_FireY)*(m_FireData[i].m_distz-1)/(m_FireFarZ-1)+m_FireY;
				m_FirePosX1=(m_FireData[i].m_LastX-m_FireX)*(m_FireData[i].m_distz-1)/(m_FireFarZ-1)+m_FireX;
				m_FirePosX2=(m_FireData[i].m_LastX+m_FireX)*(m_FireData[i].m_distz-1)/(m_FireFarZ-1)-m_FireX;
				
				m_ImpactDist=sqrt(pow((m_FirePosY-2),2)+pow((m_FirePosX2),2)+pow((m_ObjectData[0].m_PosZ-m_FireData[i].m_distz),2));
				
				if (m_ImpactDist<1.5)
				{
					m_FireData[i].m_OnValid=false;
					m_ObjectData[0].m_OnValid=false;
					m_Score.m_Number++;
				}

				glPushMatrix();

				glPushMatrix();
				glTranslated(m_FirePosX1,m_FirePosY,-m_FireData[i].m_distz);
				glRotated(m_FireData[i].m_angXZ,1,0,0);
				glRotated(m_FireData[i].m_angYZ1,0,-1,0);
				glCallList(m_GameParams.m_ListBase+1);
				glPopMatrix();

				glTranslated(m_FirePosX2,m_FirePosY,-m_FireData[i].m_distz);
				glRotated(m_FireData[i].m_angXZ,1,0,0);
				glRotated(m_FireData[i].m_angYZ2,0,-1,0);
				glCallList(m_GameParams.m_ListBase+1);

				m_FireData[i].m_distz+=m_FireVel;
				if (m_FireData[i].m_distz > m_FireFarZ)
					m_FireData[i].m_OnValid=false;
				glPopMatrix();
			}
		}

		
		m_ObjectData[0].m_PosZ+=m_ObjectData[0].m_Vel;
		if (m_ObjectData[0].m_PosZ > m_ObjectData[0].m_MaxZ)
		{
			m_ObjectData[0].m_PosZ=1;
			m_ObjectData[0].m_OnValid=true;
		}
		glTranslated(0.0,2.0,-m_ObjectData[0].m_PosZ);
		if (m_ObjectData[0].m_OnValid)
		{
			glCallList(m_GameParams.m_ListBase);
		}
		else
		{
			glRotated(m_ObjectData[0].m_PosZ*100,35,20,25);							
			glCallList(m_GameParams.m_ListBase);
		}
	
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

	m_GameParams.m_ListBase=glGenLists(3);
	if (m_GameParams.m_ListBase==0)
		return false;

	float scale=1;
	glNewList(m_GameParams.m_ListBase,GL_COMPILE);
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

	return true;
}

int CGLGame::Close()
{
	PostThreadMessage(m_Thread->m_nThreadID,WM_CLOSE,0,0);
	WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	WaitForSingleObject(m_Thread->m_hThread,INFINITE);
	CloseHandle(m_GameParams.m_hEvent);
	return true;
}

int CGLGame::PauseGame()
{
	PostThreadMessage(m_Thread->m_nThreadID,UM_COMMAND,UC_PAUSE,0);
	WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	return true;
}

int CGLGame::BeginGame()
{
	PostThreadMessage(m_Thread->m_nThreadID,UM_COMMAND,UC_BEGIN,0);
	WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	SetCapture();
	return true;
}

int CGLGame::SetDevice(CDevice *pDevice)
{
	m_LPDevice=pDevice;
	return true;
}

void CGLGame::OnSize(UINT nType, int cx, int cy) 
{
	PostThreadMessage(m_Thread->m_nThreadID,WM_SIZE,nType,MAKELPARAM(cx,cy));
	//WaitForSingleObject(m_GameParams.m_hEvent,INFINITE);
	CWnd::OnSize(nType, cx, cy);
}

void CGLGame::OnDestroy()
{
	Close();
	CWnd::OnDestroy();
}
