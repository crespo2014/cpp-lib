// VideoLevel1.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Level_1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoLevel1

CVideoLevel1::CVideoLevel1()
{
	m_hCursor=NULL;
	m_OnDevice=false;
	m_GrafMinZ=1;
	m_GrafMaxZ=200;
}

CVideoLevel1::~CVideoLevel1()
{

}


BEGIN_MESSAGE_MAP(CVideoLevel1, CVideo)
	//{{AFX_MSG_MAP(CVideoLevel1)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVideoLevel1 message handlers

int CVideoLevel1::RenderScene()
{
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
	
	/*
	if ((m_Time.wMinute-m_GameParams.m_STime.wMinute)>m_GameParams.m_CondMin)
		m_OnPlay=false;
		*/
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
	return true;
}

int CVideoLevel1::InitView(BOOL pOnSize)
{
	if (pOnSize)
	{
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40,aspect,1,200);
		//glFrustum(-1,1,-1,1,1,200);
		m_GrafMaxY=m_GrafMinZ*Tangente(20);
		m_GrafMaxX=m_GrafMaxY*aspect;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		return true;
	}
	glClearColor(0,0,0.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

	glPixelStorei(GL_UNPACK_SKIP_PIXELS,0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS,0); 
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	GenGLList();

	m_Dir=false;
	
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
	// Nave
	m_angX=0;
	m_dangX=5;
	
	// Colimador
	m_GameParams.m_PosX=0;
	m_GameParams.m_PosY=0;
	m_GameParams.m_PosZ=2;
	m_GameParams.m_dPos=1;
	
	// Piezas
	FillSin();
	SetResolution(20);
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

	m_Joystick.SetWnd(m_hWnd);
	m_GameParams.m_IsJoystick=m_Joystick.Init();
	return true;
}

int CVideoLevel1::ThreadProcessMessages()
{
	switch(m_msg.message)
	{
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
	}
	return true;
}

int CVideoLevel1::NewFire()
{
	// Adiciona un nuevo disparo 
	for (i=0;i<10;i++)
	{
		if(m_FireData[i].m_OnValid & (m_FireData[i].m_distz < 10))
			break;
		if (!m_FireData[i].m_OnValid)
		{
			//sndPlaySound("",SND_ASYNC | SND_MEMORY);
			m_FireData[i].m_distz=0;
			m_FireData[i].m_OnValid=true;
			m_FireData[i].m_LastY=m_GameParams.m_FireFarZ*m_GameParams.m_PosY/2;
			m_FireData[i].m_LastX=m_GameParams.m_FireFarZ*m_GameParams.m_PosX/2;
			m_FireData[i].m_angXZ=atan2(m_GameParams.m_FireFarZ*m_GameParams.m_PosY/2-m_GameParams.m_FireY,m_GameParams.m_FireFarZ-1)*180/3.14;
			m_FireData[i].m_angYZ1=atan2(m_GameParams.m_PosX*m_GameParams.m_FireFarZ/2-m_GameParams.m_FireX,m_GameParams.m_FireFarZ-1)*180/3.14;
			m_FireData[i].m_angYZ2=atan2(m_GameParams.m_PosX*m_GameParams.m_FireFarZ/2+m_GameParams.m_FireX,m_GameParams.m_FireFarZ-1)*180/3.14;
			break;
		}
		
	}
	return true;

}

int CVideoLevel1::CheckColision()
{
	double dx,dy,dz;
	for (i=0;i<MAX_FIRE;i++)
	{
		if (m_FireData[i].m_OnValid)
		{
			// Chequeo de colision				
			m_GameParams.m_FirePosY=(m_FireData[i].m_LastY-m_GameParams.m_FireY)*(m_FireData[i].m_distz-1)/(m_GameParams.m_FireFarZ-1)+m_GameParams.m_FireY;
			m_GameParams.m_FirePosX1=(m_FireData[i].m_LastX-m_GameParams.m_FireX)*(m_FireData[i].m_distz-1)/(m_GameParams.m_FireFarZ-1)+m_GameParams.m_FireX;
			m_GameParams.m_FirePosX2=(m_FireData[i].m_LastX+m_GameParams.m_FireX)*(m_FireData[i].m_distz-1)/(m_GameParams.m_FireFarZ-1)-m_GameParams.m_FireX;

			for (j=0;j<MAX_OBJECT;j++)
			{
				dx=m_GameParams.m_FirePosX2-m_ObjectParams[j].m_PosX;
				dy=m_GameParams.m_FirePosY-m_ObjectParams[j].m_PosY;
				dz=m_ObjectParams[j].m_PosZ-m_FireData[i].m_distz;
				m_GameParams.m_ImpactDist=sqrt(pow(dx,2)+pow(dy,2)+pow(dz,2));
				if (m_GameParams.m_ImpactDist<1.5)
				{
					m_GameParams.m_PointID[0]++;
					m_FireData[i].m_OnValid=false;
					m_ObjectParams[j].m_OnValid=false;
					m_GameParams.m_Points++;
				}
			}
			
			glPushMatrix();
			
			glPushMatrix();
			glTranslated(m_GameParams.m_FirePosX1,m_GameParams.m_FirePosY,-m_FireData[i].m_distz);
			glRotated(m_FireData[i].m_angXZ,1,0,0);
			glRotated(m_FireData[i].m_angYZ1,0,-1,0);
			glCallList(m_GameParams.m_ListBase+1);
			glPopMatrix();
			
			glTranslated(m_GameParams.m_FirePosX2,m_GameParams.m_FirePosY,-m_FireData[i].m_distz);
			glRotated(m_FireData[i].m_angXZ,1,0,0);
			glRotated(m_FireData[i].m_angYZ2,0,-1,0);
			glCallList(m_GameParams.m_ListBase+1);
			
			m_FireData[i].m_distz+=m_GameParams.m_FireVel;
			if (m_FireData[i].m_distz > m_GameParams.m_FireFarZ)
				m_FireData[i].m_OnValid=false;
			glPopMatrix();
		}
	}
	return true;

}

int CVideoLevel1::GenGLList()
{
	int i;
	SetResolution(10);
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

int CVideoLevel1::MoveObjects()
{
	for (i=0;i<MAX_OBJECT;i++)
	{
		glPushMatrix();
		if (m_ObjectParams[i].m_Dir)
		{
			m_ObjectParams[i].m_PosZ+=m_ObjectParams[i].m_Vel;
		}else
			m_ObjectParams[i].m_PosZ-=m_ObjectParams[i].m_Vel;

		if ((m_ObjectParams[i].m_PosZ > m_ObjectParams[i].m_MaxZ)|
			(m_ObjectParams[i].m_PosZ < 0))
		{
			m_ObjectParams[i].m_PosZ=100;
			m_ObjectParams[i].m_OnValid=true;
			m_ObjectParams[i].m_Dir=false;
			m_ObjectParams[i].m_PosY=(((double)rand())/RAND_MAX*2-1)*4;
			m_ObjectParams[i].m_PosX=(((double)rand())/RAND_MAX*2-1)*4;
			m_ObjectParams[i].m_PosZ=(((double)rand())/RAND_MAX)*100+50;
		}
		glTranslated(m_ObjectParams[i].m_PosX,m_ObjectParams[i].m_PosY,-m_ObjectParams[i].m_PosZ);
		if (m_ObjectParams[i].m_OnValid)
		{
			glColor3ub(255,0,255);
			glCallList(m_ObjectParams[i].m_List);
		}
		else
		{
			glColor3ub(0,255,0);
			glRotated(m_ObjectParams[i].m_PosZ*100,35,20,25);							
			glCallList(m_ObjectParams[i].m_List);
		}
		glPopMatrix();
	}

	return true;

}

int CVideoLevel1::InitGame()
{
	m_GameParams.m_CondMin=1;
	GetSystemTime(&m_GameParams.m_STime);
	return true;
}

BOOL CVideoLevel1::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (pMsg->message)
	{
	case MM_JOY1MOVE:
		{
			m_GameParams.m_JX=LOWORD(pMsg->lParam);
			m_GameParams.m_JY=HIWORD(pMsg->lParam);
			m_Joystick.Normalize(LOWORD(pMsg->lParam),HIWORD(pMsg->lParam),0,
				&m_GameParams.m_JoystickX,
				&m_GameParams.m_JoystickY,
				&m_GameParams.m_JoystickZ);
			return true;
		}
	case MM_JOY1BUTTONDOWN:
	case MM_JOY2BUTTONDOWN:
		{
			PostThreadMessage(m_RenderThread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);						
			return true;
		}
	case WM_MOUSEMOVE:
		{
			m_GameParams.m_MouseX=LOWORD(pMsg->lParam);
			m_GameParams.m_MouseY=HIWORD(pMsg->lParam);  
			break;
		} 
	case WM_SETCURSOR:
		{
			SetCursor(NULL);
			return true;
		}
	case WM_LBUTTONDOWN:
		{
			PostThreadMessage(m_RenderThread->m_nThreadID,WM_KEYDOWN,32,0);
			break;
		}
	case UM_COMMAND:
		{
			switch(pMsg->wParam)
			{
			case UC_FIRE:
				{
					
					break;
				}
			}

			return true;
		}
	}


	if ((pMsg->message>=WM_KEYFIRST)&(pMsg->message<=WM_KEYLAST+1))
	{
		PostThreadMessage(m_RenderThread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
		return true;
	}
	/*
	if((pMsg->message>=WM_MOUSEFIRST)&(pMsg->message<=WM_MOUSELAST))
	{
		PostThreadMessage(m_RenderThread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
		return true;
	}
	*/
	
	return CVideo::PreTranslateMessage(pMsg);
}

BOOL CVideoLevel1::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(NULL);	
	return true;
	//return CVideo::OnSetCursor(pWnd, nHitTest, message);
}

int CVideoLevel1::SetDevice(CSignalDevice *pDevice)
{
	m_OnDevice=true;
 	m_LPDevice=pDevice;
 	return true;
}
