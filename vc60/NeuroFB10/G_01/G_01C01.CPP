// G_01C01.cpp : implementation file
//
 
#include "stdafx.h"
#include "stdafx.h"
#include "G_01C01.h"
#include "..\include\define.h"
#include "G_01C02.h"
#include "G_01C04.h"
#include "math.h"
#include "G_01C03.h"
#include "..\gl10\gl10c3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Errores que pueden devolver las funciones
// de esta clase
#define G_OK				0	//No hay error
#define GERR_FIRST			1
#define GERR_BACKDC			GERR_FIRST+1	//No se pudo crear el DC trasero
#define GERR_BACKBMP		GERR_FIRST+2	//No se pudo crear el bitmap del buffer trasero
#define GERR_BACKDCBMP		GERR_FIRST+3	//No se pudo seleccionar el bitmap en el dc trasero
#define GERR_BACKDCPF		GERR_FIRST+4	//No se pudo poner el formato de pixel en el back DC 
#define GERR_BACKRC			GERR_FIRST+5	//No se pudo crear el Render Context
#define GERR_BACKRCCURRENT	GERR_FIRST+6	//RC is not current to the DC
#define GERR_WND			GERR_FIRST+7	//No se pudo crear la ventana de juego
#define GERR_DD				GERR_FIRST+8	//No se pudo crear el Objeto DirectDraw
#define GERR_DDS			GERR_FIRST+9	//No se pudo crear la superficie DirectDraw
#define GERR_DDCL			GERR_FIRST+10	//No se pudo poner el nivel de cooperacion
#define GERR_DDDM			GERR_FIRST+11	//No se pudo poner el modo de display
#define GERR_DDFDC			GERR_FIRST+12	//No se pudo obtener un DC frontal
#define GERR_DDFS			GERR_FIRST+13	//No se pudo crear la superficie DD

/////////////////////////////////////////////////////////////////////////////
// CViewGame


CViewGame::CViewGame()
{
	Initialize();
}

CViewGame::~CViewGame()
{
	Destroy();
}


BEGIN_MESSAGE_MAP(CViewGame, CWnd)
	//{{AFX_MSG_MAP(CViewGame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CViewGame message handlers

LRESULT CViewGame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	BOOL	Send=false;
	S_MESSAGE	Msg;
	Msg.Msg=message;
	Msg.lParam=lParam;
	Msg.wParam=wParam;
	Message.SendMessage(&Msg);
	switch (message)
	{
	case WM_DESTROY:
		{
			Send=true;
			Msg.Msg=UM_GAME_STOP;
			Message.SendMessage(&Msg);
			DestroyFullScreen();
			break;
		}
	case WM_SETFOCUS:
		{
			return 0;
		}
	case WM_ERASEBKGND:
		{
			return 1;
		}
	case WM_PAINT:
		{
			ThreadRenderScene();
			//CPaintDC dc(this);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			DestroyWindow();
			break;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}


DWORD CViewGame::Start()
{
	if (!CreateEx(WS_EX_TOPMOST,"STATIC",NULL,WS_POPUP|WS_VISIBLE,0,0,500,500,NULL,NULL,NULL))
		return GERR_WND;
	SetCapture();
	SetFocus();
	//SetCursor(NULL);

	QueryPerformanceFrequency(&TimerFrec);
	
	BackDC=::GetDC(m_hWnd);
	CreateRC();
		
	
	/*
	SetFullScreen();
	S_MESSAGE	Msg;
	Msg.Msg=UM_INIT_OPENGL;
	Message.SendMessage(&Msg);
	
		
	/*
	CreateBackBuffer();
	CreateFrontDC();
	*/
	return 0;
}

/*
	Se crea un bitmap en memoria usado como
	segundo buffer
*/
DWORD CViewGame::CreateBackBuffer()
{
	FrontDC=::GetDC(NULL);
	// Crear bitmap compatible con el DC del DDraw
	BackDC=::CreateCompatibleDC(FrontDC);
	if (!BackDC)
	{
		::ReleaseDC(NULL,FrontDC);
		return GERR_BACKDC;
	}

	BackBmp=::CreateCompatibleBitmap(FrontDC,640,480);
	if (!BackBmp)
	{
		::ReleaseDC(NULL,FrontDC);
		return GERR_BACKBMP;
	}
	::ReleaseDC(NULL,FrontDC);

	BackOldBmp=(HBITMAP)::SelectObject(BackDC,BackBmp);
	if (!BackOldBmp)
		return GERR_BACKDCBMP;

	return CreateRC();
	

}

DWORD CViewGame::Initialize()
{
	GameInitialize();
	memset(&BackDCPFD,0,sizeof(BackDCPFD));
	BackDCPFD.nSize			=sizeof(BackDCPFD);
	BackDCPFD.nVersion		=1;
	BackDCPFD.dwFlags		=PFD_SUPPORT_OPENGL|PFD_SUPPORT_GDI|PFD_DRAW_TO_BITMAP|PFD_GENERIC_FORMAT;
	BackDCPFD.iPixelType	=PFD_TYPE_RGBA;
	BackDCPFD.cColorBits	=16;
	BackDCPFD.cDepthBits	=32;
	BackDCPFD.iLayerType	=PFD_MAIN_PLANE;
	BackDC=NULL;
	BackBmp=NULL;
	BackDCPFI=0;
	BackOldBmp=NULL;
	BackRC=NULL;
	FrontDC=NULL;
	FrontDD=NULL;
	FrontDDS=NULL;
	OnPlay=false;
	WTime=INFINITE;
	Game_ColX=0;
	Game_ColY=0;
	Game_ColZ=-30;
	Game_Misil_SX=0;
	Game_Misil_SZ=0;
	Game_Misil_SY=-1;
	angulo=0;

	BackThread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	return 0;
}

DWORD CViewGame::Destroy()
{
	S_MESSAGE Msg;
	Msg.Msg=UM_THREAD_CLOSE;
	Message.SendMessage(&Msg);
	WaitForSingleObject(BackThread->m_hThread,INFINITE);
	return 0;
}

DWORD CViewGame::DestroyBackBuffer()
{
	wglMakeCurrent(NULL,NULL);
	if (BackRC)
		wglDeleteContext(BackRC);
	if (BackOldBmp)
		SelectObject(BackDC,BackOldBmp);
	if (BackBmp)
		DeleteObject(BackBmp);
	if (BackDC)
		DeleteObject(BackDC);
	return 0;
}

/*
	Transfiere el contenido del buffer
	trasero al delantero
*/
DWORD CViewGame::SwapBuffer()
{
	if (!(FrontDC && BackDC && BackDDS))
		return 1;
	BackDDS->GetDC(&FrontDC);
		::BitBlt(FrontDC,0,0,640,480,BackDC,0,0,SRCCOPY);
	BackDDS->ReleaseDC(FrontDC);
	FrontDDS->Flip(NULL,0);
	return 0;
}

DWORD CViewGame::SetFullScreen()
{
    HRESULT             ddrval;
    ddrval = DirectDrawCreate( NULL, &FrontDD, NULL );
	if (ddrval)
		return GERR_DD;
    ddrval = FrontDD->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);
	if (ddrval)
		return GERR_DDCL;
	ddrval = FrontDD->SetDisplayMode( 640, 480, 16 );
	if (ddrval)
		return GERR_DDDM;
	return 0;
}

UINT CViewGame::ThreadProc(LPVOID pParam)
{
	return ((CViewGame*)pParam)->ThreadMain();
}

UINT CViewGame::ThreadMain()
{
	angulo=0;
	while (true)
	{
		if (Message.WaitMessage(WTime))
				if (!TProcessMessage())
					return 0;
		if (OnPlay)
			ThreadRenderScene();
	}
	return 0;
}

DWORD CViewGame::ThreadRenderScene()
{
	float factor=4;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glColor3ub(255,0,0);

	/*
	glColor3ub(255,0,0);
	glBegin(GL_LINE_LOOP);
	for (int i=0;i<360;i+=45)
	{
		glVertex3d(Game_ColX+0.05*cos(i),Game_ColY+0.05*sin(i),Game_ColZ);
	}
	glEnd();
	*/

	Fly();
	glFinish();
	SwapBuffer();
	glPopMatrix();
	return 0;
}

// Procesar todos los mensajes que han llegado al hilo
DWORD CViewGame::TProcessMessage()
{
	S_MESSAGE	Msg;
	if (!Message.PeekMessage(&Msg))
		return true;
	switch (Msg.Msg)
	{
	case WM_MOUSEMOVE:
		{
			float m_MouseX=LOWORD(Msg.lParam);
			float m_MouseY=HIWORD(Msg.lParam);
			float m_GrafMaxY=480;
			float m_GrafMaxX=640;
			// Corregir posicion
			m_MouseY=1-m_MouseY*2;
			m_MouseX=m_MouseX*2-1;
			
			// Desnormalizar
			m_MouseY=m_MouseY*m_GrafMaxY;
			m_MouseX=m_MouseX*m_GrafMaxX;
			// calcular posicion del lente
			
			Game_ColY=m_MouseY*Game_ColZ/1;
			Game_ColX=m_MouseX*Game_ColZ/1;
			break;
		}
	case WM_DESTROY:
		{
			DestroyFrontDC();
			break;
		}
	case UM_INIT_OPENGL:
		{
			if (CreateBackBuffer()!=0)
				break;
			if (CreateFrontDC()!=0)
				break;
			QueryPerformanceCounter(&TimerStart);
			
			OnPlay=true;
			WTime=0;
			break;
		}
	case UM_GAME_START:
		{
			OnPlay=true;
			WTime=0;
			break;
		}
	case UM_GAME_STOP:
		{
			OnPlay=false;
			WTime=INFINITE;
			break;
		}
	case UM_THREAD_CLOSE:
		{
			OnPlay=false;
			WTime=INFINITE;
			DestroyBackBuffer();
			Message.ReplyMessage(0);
			return false;
		}
	case WM_KEYDOWN:
		{
			MessageBeep(-1);
			GameNewFire();
			break;
		}

	}
	Message.ReplyMessage(0);
	return true;
}

DWORD CViewGame::DestroyFullScreen()
{
	if (FrontDD)
	{
		FrontDD->Release();
		FrontDD=NULL;
	}
	return 0;
}

// Crear la superficie en DD para el bitblt
DWORD CViewGame::CreateFrontDC()
{
	HRESULT ddrval;
	DDSURFACEDESC       ddsd;
	DDSCAPS				ddscaps;
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof( ddsd );
	/*
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddrval = FrontDD->CreateSurface( &ddsd, &FrontDDS, NULL );
	if(ddrval)
		return GERR_DDFS;
	ddrval = FrontDDS->GetDC(&FrontDC);
	if(ddrval)
		return GERR_DDFDC;
	*/
	
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			  DDSCAPS_FLIP |
			  DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = FrontDD->CreateSurface( &ddsd, &FrontDDS, NULL );

	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = FrontDDS->GetAttachedSurface(&ddscaps, &BackDDS);
	return 0;
}

DWORD CViewGame::Fly()
{
	POSITION	Pos;

	QueryPerformanceCounter(&TimerCurrent);
	DWORD	TimeMs=(TimerCurrent.QuadPart-TimerStart.QuadPart)/TimerFrec.QuadPart;
	POSITION	pPos;
	if (!Objetos3DList.IsEmpty())
	{
		C3DObject*	pvar;
		pPos=Objetos3DList.GetHeadPosition();
		do
		{
			pvar=(C3DObject*)Objetos3DList.GetAt(pPos);
			pvar->Fly(TimeMs);
			if (!pvar->Paint())
			{
				delete pvar;
				Pos=pPos;
			}
			else Pos=NULL;
			Objetos3DList.GetNext(pPos);
			if (Pos)
				Objetos3DList.RemoveAt(Pos);
		} while (pPos !=NULL);
	}
	return true;
}



DWORD CViewGame::GameInitialize()
{
//	Escena.Read();	
	return 0;
}

DWORD CViewGame::DestroyFrontDC()
{
	if (FrontDDS)
	{
		FrontDDS->ReleaseDC(FrontDC);
		FrontDDS->Release();
		FrontDDS=NULL;
		BackDDS=NULL;
	}
	return 0;
}

DWORD CViewGame::GameAdd3DObject(void *p3DObject)
{
	Objetos3DList.AddTail((CObject*) p3DObject);
	return 0;
}

// Actualiza  el formato de pixels de un DC 
// y crea un RC para este
// el HDC esta en BACKDC
DWORD CViewGame::CreateRC()
{
	// Seleccionar el formato de pixels
	BackDCPFI= ChoosePixelFormat(BackDC,&BackDCPFD);

	if (BackDCPFI==0) 
		BackDCPFI = 1;
	DescribePixelFormat(BackDC,BackDCPFI,sizeof(BackDCPFI),&BackDCPFD);
	if (!SetPixelFormat(BackDC,BackDCPFI,&BackDCPFD))
		return GERR_BACKDCPF;

	//	Crear el rendering Context
	BackRC=wglCreateContext(BackDC);
	if (!BackRC)
		return GERR_BACKRC;
	if (!wglMakeCurrent(BackDC,BackRC))
		return GERR_BACKRCCURRENT;
	return RCInitialize();
}

/*
	Inicializacion del RC
*/
DWORD CViewGame::RCInitialize()
{
	float ambient[]={0.5,0.5,0.5,1.0};
	float diffuse[]={0.3f,0.3f,0.3f,1};
	float pos[]={0,0,0,1};
	
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);

	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE); 
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_DITHER);
	glDisable(GL_FOG);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);


	glViewport(0,0,640,480);
	GLdouble aspect;
	aspect=640/480;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40,aspect,1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glColor3ub(255,0,0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,diffuse);
	glDrawBuffer(GL_FRONT);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,true);
	glClearColor(0.0f,0.0f,0.0f,1.0f);

	return G_OK;
}

DWORD CViewGame::GameNewFire()
{
	/*
	C3DCohete* Misil= new C3DCohete();
	Misil->AttachMesh(Escena.GetMesh("Misil"));
	Misil->ang_xz=atan2(Game_ColX-Game_Misil_SX,Game_ColZ-Game_Misil_SZ)*180/3.14;
	Misil->ang_yz=atan2(Game_ColY-Game_Misil_SY,Game_ColZ-Game_Misil_SZ)*180/3.14;
	Misil->relacionxz=(Game_ColX-Game_Misil_SX)/(Game_ColZ-Game_Misil_SZ);
	Misil->relacionyz=(Game_ColY-Game_Misil_SY)/(Game_ColZ-Game_Misil_SZ);
	Misil->start_x=Game_Misil_SX;
	Misil->start_y=Game_Misil_SY;
	Misil->start_z=Game_Misil_SZ;
	Misil->currentz=Game_Misil_SZ;
	Misil->lastz=Game_ColZ;
	Misil->AttachMesh(Escena.GetMesh("Misil"));
	GameAdd3DObject(Misil);
	*/

	return true;
}
