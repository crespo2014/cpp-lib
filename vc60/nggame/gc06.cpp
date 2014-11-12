// gc06.cpp : implementation file
//

#include "gc06.h"
#include "gc02.h"
#include "gc03.h"
#include "gc04.h"
//#include "..\include\define.h"
#include "gc08.h"
//#include "..\neurofbdll\app.h"

#define NO_DD

// Dimesiones de la ventana
const double WWIDTH		=640;
const double WHEIGHT	=480;
const double VIEWANG	=40;

// Dimensiones del area de la opengl
const double OGLWIDTH	=640;
const double OGLHEIGHT	=420;

// coordenada z del colimador
const double COLIMADORZ =-1500;

// planos de corte
const double NEARZ	=-100;	
const double FARZ	=-200000;

//salida del misil
const double MISILSX	=0;
const double MISILSY	=0;
const double MISILSZ	=0;


const double OGLMAXY=(-tan((VIEWANG/2)*3.14/180)*NEARZ);
const double OGLMAXX=OGLMAXY*OGLWIDTH/OGLHEIGHT;

/*
const double PIXELxCMX=WWIDTH/2/OGLMAXX;
const double PIXELxCMY=WHEIGHT/2/OGLMAXY;
*/


/////////////////////////////////////////////////////////////////////////////
// C3DViewGame

C3DViewGame::C3DViewGame()
{
	Initialize();
}

C3DViewGame::~C3DViewGame()
{
	Destroy();
}

DWORD C3DViewGame::Initialize()
{
	m_tierra=NULL;
	m_end_time=false;
	m_hrc=NULL;
	m_hdc=NULL;
	m_first_cohete=NULL;
	m_first_nave=NULL;
	m_message_time=INFINITE;
	m_font=NULL;
	m_font2=NULL;
	m_hbitmap=NULL;
	m_hdc=NULL;
	m_holdbitmap=NULL;
	m_hrc=NULL;
	m_play=false;
	
	m_start_time=0;

	memset(&m_pfd,0,sizeof(m_pfd));
	m_pfd.nSize			=sizeof(m_pfd);
	m_pfd.nVersion		=1;
	m_pfd.dwFlags		=PFD_SUPPORT_OPENGL|PFD_SUPPORT_GDI|PFD_DRAW_TO_BITMAP|PFD_GENERIC_FORMAT;
	m_pfd.iPixelType	=PFD_TYPE_RGBA;
	m_pfd.cColorBits	=16;
	m_pfd.cDepthBits	=32;
	m_pfd.iLayerType	=PFD_MAIN_PLANE;
	return 0;
}

DWORD C3DViewGame::Destroy()
{
	return 0;
}

DWORD C3DViewGame::OglCreateRC()
{
	// Tomar el DC
	HDC FrontDC=::GetDC(m_hWnd);
	// crear un DC en memoria

	// Crear bitmap compatible con el DC del DDraw
	HDC BackDC=::CreateCompatibleDC(FrontDC);
	if (!BackDC)
	{
		::ReleaseDC(m_hWnd,FrontDC);
		return GERR_BACKDC;
	}

	m_hbitmap=::CreateCompatibleBitmap(FrontDC,640,480);
	if (!m_hbitmap)
	{
		::ReleaseDC(NULL,FrontDC);
		return GERR_BACKBMP;
	}
	::ReleaseDC(NULL,FrontDC);

	m_holdbitmap=(HBITMAP)::SelectObject(BackDC,m_hbitmap);
	if (!m_holdbitmap)
		return GERR_BACKDCBMP;

	m_hdc= BackDC;
	// SetPixelFormat
	int	m_pfi;
	m_pfi = ChoosePixelFormat(m_hdc,&m_pfd);
	if (m_pfi==0)
	{
		m_pfi = 1;	
		DescribePixelFormat(m_hdc,m_pfi,sizeof(m_pfd),&m_pfd);
	}
	if (!SetPixelFormat(m_hdc,m_pfi,&m_pfd))
	{
		return ERR_NOPF;
	}
	//	Crear el rendering Context
	m_hrc=wglCreateContext(m_hdc);
	if (!m_hrc)
		return ERR_NORC;
	if (!wglMakeCurrent(m_hdc,m_hrc))
		return ERR_NOCRC;
	return OglInitialize();
}

/*
	Inicializa todos los parametros del juego
	Inicializa toda la opengl y el DirectX
*/
DWORD C3DViewGame::GameInitialize()
{
	OglCreateRC();
	// Leer la informacion del recurso
	if (m_3descene.ReadFromResource("misil.ogl","File")!=0)
		return 1;
	m_tierra=m_3descene.Get3DMesh("Tierra");
	for (DWORD i=0;i< 5;i++)
	{
		// Poner a volar naves
		C3DNave*	m_nave= new C3DNave();
		m_nave->Set3DMesh(m_3descene.Get3DMesh("Nave"));
		GameAdd3DNave(m_nave);
	}
	GamePlay();
	// Inicializacion de los parametros del juego
	m_score=0;
	m_start_time=GetTickCount();
	
	return 0;
}

DWORD C3DViewGame::OglSwapBuffer()
{
#ifdef NO_DD
	HDC m_dc=::GetDC(m_hWnd);
	::BitBlt(m_dc,0,0,(int)WWIDTH,(int)WHEIGHT,m_hdc,0,0,SRCCOPY);
	::ReleaseDC(m_hWnd,m_dc);
#else
	
	HDC	m_dc;
	m_backdds->GetDC(&m_dc);
	::BitBlt(m_dc,0,0,(int)WWIDTH,(int)WHEIGHT,m_hdc,0,0,SRCCOPY);
	m_backdds->ReleaseDC(m_dc);
	m_dds->Flip(NULL,0);
#endif
	

	return 0;
}

/*
	Inicializacion de todos los parametros
	del RenderContext
*/
DWORD C3DViewGame::OglInitialize()
{
	float ambient[]={0.5,0.5,0.5,1.0};
	float diffuse[]={0.3f,0.3f,0.3f,1};
	float pos[]={-100,100,0,1};

	float luz1_ambient[]={0.0,0.0,0.0,1.0};
	float luz1_diffuse[]={0.4f,0.4f,0.4f,1};
	float luz1_pos[]={100,-100,0,1};

	glDisable(GL_NORMALIZE); 
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_DITHER);
	glDisable(GL_FOG);
	glDisable(GL_LIGHTING);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_LINE_STIPPLE);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_NORMALIZE);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_POLYGON_STIPPLE);
	glDisable(GL_SCISSOR_TEST);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glCullFace(GL_BACK);
#ifdef NO_DD
	glDrawBuffer(GL_BACK);
#else
	glDrawBuffer(GL_FRONT);
#endif
	glColor3ub(255,0,0);
	glClearColor(0,0,0,0);
	glViewport(0,60,(int)OGLWIDTH,(int)OGLHEIGHT);
	GLdouble aspect;
	aspect=OGLWIDTH/OGLHEIGHT;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(VIEWANG,aspect,-NEARZ,-FARZ);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,diffuse);

	glLightfv(GL_LIGHT1,GL_AMBIENT,luz1_ambient);
	glLightfv(GL_LIGHT1,GL_POSITION,luz1_pos);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,luz1_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,luz1_diffuse);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glFrontFace(GL_CCW);

	// Inicializacion de todos los objetos de la GDI
	m_linecolor=::CreatePen(PS_SOLID,0,0xFFFFFF);
	
	LOGFONT	logfont;
	memset(&logfont,0,sizeof(LOGFONT));
	strcpy(logfont.lfFaceName,"Arial");
	logfont.lfHeight=-24;
	logfont.lfWidth=0;
	logfont.lfWeight=FW_NORMAL;
	logfont.lfOutPrecision=3;
	logfont.lfClipPrecision=2;
	logfont.lfQuality=1;
	logfont.lfPitchAndFamily=34;
	logfont.lfCharSet=ANSI_CHARSET;
	logfont.lfItalic = false;
	
	m_font=::CreateFontIndirect(&logfont);

	strcpy(logfont.lfFaceName,"Arial");
	logfont.lfHeight=-10;
	logfont.lfWidth=0;
	logfont.lfWeight=FW_NORMAL;
	logfont.lfOutPrecision=3;
	logfont.lfClipPrecision=2;
	logfont.lfQuality=1;
	logfont.lfPitchAndFamily=34;
	logfont.lfCharSet=ANSI_CHARSET;
	logfont.lfItalic = false;
	m_font2=::CreateFontIndirect(&logfont);


#ifdef NO_DD
#else
	HRESULT	ddrval;
	// Creacion de la superficie para el direct Draw
	DDSURFACEDESC       ddsd;
	DDSCAPS				ddscaps;
	memset(&ddsd,0,sizeof(ddsd));
	ddsd.dwSize = sizeof( ddsd );
	
	ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE |
			  DDSCAPS_FLIP |
			  DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval = m_dd->CreateSurface( &ddsd, &m_dds, NULL );
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    ddrval = m_dds->GetAttachedSurface(&ddscaps, &m_backdds);
#endif

	return 0;
}

DWORD C3DViewGame::OglRenderContext()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();

	glDisable(GL_LIGHTING);

	// Dibujar unos triangulitos cerca del colimador
	double radio = 2;
	double ancho = 1;
	/*
	if (m_online && !m_app->m_device.m_disparar)
		glColor3ub(255,0,0);
		*/
//	else
		glColor3ub(0,255,0);

	

	glBegin(GL_TRIANGLES);
		
		glVertex3d(m_mirax,m_miray+radio,NEARZ);
		glVertex3d(m_mirax+ancho,m_miray+ancho+radio,NEARZ);
		glVertex3d(m_mirax-ancho,m_miray+ancho+radio,NEARZ);

		glVertex3d(m_mirax+ancho,m_miray-ancho-radio,NEARZ);
		glVertex3d(m_mirax,m_miray-radio,NEARZ);
		glVertex3d(m_mirax-ancho,m_miray-ancho-radio,NEARZ);

		glVertex3d(m_mirax+ancho+radio,m_miray+ancho,NEARZ);
		glVertex3d(m_mirax+radio,m_miray,NEARZ);
		glVertex3d(m_mirax+ancho+radio,m_miray-ancho,NEARZ);


		glVertex3d(m_mirax-radio,m_miray,NEARZ);
		glVertex3d(m_mirax-ancho-radio,m_miray+ancho,NEARZ);
		glVertex3d(m_mirax-ancho-radio,m_miray-ancho,NEARZ);

	glEnd();
	glEnable(GL_LIGHTING);

	// Recorrer la lista de 3DObjects 
	C3DObject*	m_3dobject=m_first_cohete;
	C3DObject*	m_temp3dobject;
	DWORD		m_current_time=GetTickCount();
	while (true)
	{
		if (!m_3dobject)
			break;
		m_3dobject->Fly(m_current_time);
		m_3dobject->Paint();
		GameCheckColision((C3DCohete*)m_3dobject);
		// Borrar el objeto
		if (m_3dobject->m_delete)
		{
			if (m_3dobject->m_prev)
				m_3dobject->m_prev->m_next=m_3dobject->m_next;
			else
				m_first_cohete=m_3dobject->m_next;
			m_temp3dobject=m_3dobject;
			if (m_3dobject->m_next)
				m_3dobject->m_next->m_prev=m_3dobject->m_prev;
			m_3dobject=m_3dobject->GetNext();
			delete m_temp3dobject;
		}
		else
			m_3dobject=m_3dobject->GetNext();
	}

	m_3dobject=m_first_nave;
	while (true)
	{
		if (!m_3dobject)
			break;
		m_3dobject->Fly(m_current_time);
		m_3dobject->Paint();
		// Borrar el objeto
		if (m_3dobject->m_delete)
		{
			if (m_3dobject->m_prev)
				m_3dobject->m_prev->m_next=m_3dobject->m_next;
			else
				m_first_nave=m_3dobject->m_next;
			m_temp3dobject=m_3dobject;
			if (m_3dobject->m_next)
				m_3dobject->m_next->m_prev=m_3dobject->m_prev;
			m_3dobject=m_3dobject->GetNext();
			delete m_temp3dobject;
		}
		else
			m_3dobject=m_3dobject->GetNext();
	}
	glFinish();
	// Zona que no pertenece al juego
	HPEN oldpen=(HPEN)::SelectObject(m_hdc,m_linecolor);
	::MoveToEx(m_hdc,0,421,NULL);
	::LineTo(m_hdc,641,421);
	::SelectObject(m_hdc,oldpen);
	HFONT	oldfont =(HFONT)::SelectObject(m_hdc,m_font);
	RECT rect;
	rect.left=500;
	rect.top=420;
	rect.bottom=480;
	rect.right=640;
	char	record[255];
	sprintf(record,"SCORE %d",m_score);
	::SetBkMode(m_hdc,TRANSPARENT);
	::SetTextColor(m_hdc,0xFFFFFF);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	if (m_online)
	{
	::SelectObject(m_hdc,m_font2);
	rect.left=10;
	rect.top=430;
	/*
	sprintf(record,"IEEG Set Point %.2f  \nIEEG Value %.2f ",m_app->pParam->m_Nivel_I_Eeg,m_app->m_device.m_prom_ieeg_sec);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT);

	rect.left=120;
	sprintf(record,"REEG Set Point %.2f  \nREEG Value %.2f ",m_app->pParam->m_Nivel_R_Eeg,m_app->m_device.m_prom_reeg_sec);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT);

	rect.left=230;
	sprintf(record,"IEMG Set Point %.2f  \nIEMG Value %.2f ",m_app->pParam->m_Nivel_I_Musculo,m_app->m_device.m_prom_iemg_sec);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT);
	
	/*
	rect.left+=100;
	sprintf(record,"Burst/s Set Point  %d \nBurst/s Value %d ",m_app->pParam->m_Crit_Comp_Burst,m_app->m_device.m_burst_sec);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT);
	*/
	/*
	rect.left=340;
	sprintf(record,"Codition Time %d:00\nCurrent Time %d:%d",m_app->pParam->m_Duracion_Cond,m_app->m_device.m_minuto,m_app->m_device.m_cant_seconds);
	DrawText(m_hdc,record,-1,&rect,DT_LEFT);
	*/

	/*
	if (m_app->m_device.m_minuto == m_app->pParam->m_Duracion_Cond)
	{
		GameEndTime();
	}
	*/

	}

	::SelectObject(m_hdc,oldfont);
	OglSwapBuffer();
	glPopMatrix();
	return 0;
}

LRESULT C3DViewGame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		{
			m_mousex=LOWORD(lParam);  
			m_mousey=HIWORD(lParam);
			
			// Normalizar a 0,-1
			m_colimadory=(float)m_mousey/OGLHEIGHT;
			m_colimadorx=(float)m_mousex/OGLWIDTH;
			// Normalizar a 1,-1 
			m_colimadory=1-m_colimadory*2;
			m_colimadorx=m_colimadorx*2-1;
			// coordenadas en OpenGL
			m_mirax=m_colimadorx*OGLMAXX;
			m_miray=m_colimadory*OGLMAXY;
			// coordenadas reales en OpenGL
			m_colimadory=m_miray*COLIMADORZ/NEARZ;
			m_colimadorx=m_mirax*COLIMADORZ/NEARZ;
			return 0;
		}
	case WM_PAINT:
		{
			PAINTSTRUCT	m_ps;
			HDC hdc=::BeginPaint(m_hWnd,&m_ps);
			::EndPaint(m_hWnd,&m_ps);
			break;
		}
	case WM_KEYDOWN:
		{
			int m_Key;
 			m_Key=wParam;
			switch(m_Key)
			{
			case 32:
				{
					GameNewFire();
					break;
				}
			case 27:
				{
					m_end_time=false;
					GameEnd();
					break;
				}
			case 13:
				{
					if (m_end_time)
						GameEnd();
					break;
				}
			}
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			GameNewFire();
			return 0;
		}
	case WM_DESTROY:
		{
			GameExitFullScreen();
			break;			
		}
	}
	return DefWindowProc(m_hWnd,message, wParam, lParam);
}

/*
	Destruye el RC y libera el DC 
*/
DWORD C3DViewGame::OglDestroyRC()
{
	wglMakeCurrent(NULL,NULL);
	if (m_hrc)
		wglDeleteContext(m_hrc);
	if (m_holdbitmap)
		SelectObject(m_hdc,m_holdbitmap);
	if (m_hbitmap)
		DeleteObject(m_hbitmap);
	if (m_hdc)
		DeleteObject(m_hdc);

#ifdef	NO_DD
#else
	// Destruir superficies de Direct Draw
	if (m_dds)
	{
		m_dds->Release();
		m_dds=NULL;
		m_backdds=NULL;
	}
#endif

	return 0;
}

DWORD C3DViewGame::GameDestroy()
{
	// Borrar la lista de objetos
	C3DObject* m_3dobject=m_first_cohete;
	C3DObject* m_temp3doject;
	while (true)
	{
		if (!m_3dobject)
			break;
		m_temp3doject=m_3dobject;
		m_3dobject=m_3dobject->GetNext();
		delete m_temp3doject;
	}
	m_first_cohete=NULL;
	
	m_3dobject=m_first_nave;
	while (true)
	{
		if (!m_3dobject)
			break;
		m_temp3doject=m_3dobject;
		m_3dobject=m_3dobject->GetNext();
		delete m_temp3doject;
	}
	m_first_nave=NULL;
	return 0;
}

DWORD C3DViewGame::GameAdd3dObject(C3DObject *p3dobject)
{
	/*
	if (m_first_3dobject)
		m_first_3dobject->SetPrev(p3dobject);
	p3dobject->SetNext(m_first_3dobject);
	m_first_3dobject=p3dobject;
	*/
	return 0;
}

DWORD C3DViewGame::GameNewFire()
{
	/*
	if (m_online && !m_app->m_device.m_disparar)
		return 0;
		*/
	C3DCohete* m_misil=new C3DCohete();
	// Calculo del punto de llegada del misil

	m_misil->m_lastx=m_colimadorx;
	m_misil->m_lasty=m_colimadory;
	m_misil->m_lastz=COLIMADORZ;
	m_misil->m_startx=MISILSX;
	m_misil->m_starty=MISILSY;
	m_misil->m_startz=MISILSZ;
	m_misil->m_currentz=MISILSZ;
	m_misil->m_angxz=-atan2(m_colimadory-MISILSY,COLIMADORZ-MISILSZ)*180/3.14;
	m_misil->m_angyz=-atan2(m_colimadorx-MISILSX,COLIMADORZ-MISILSZ)*180/3.14;
	
	m_misil->Set3DMesh(m_3descene.Get3DMesh("Misil"));
	GameAdd3DCohete(m_misil);
	return 0;
}

DWORD C3DViewGame::GameAdd3DCohete(C3DObject *pcohete)
{
	if (m_first_cohete)
		m_first_cohete->SetPrev(pcohete);
	pcohete->SetNext(m_first_cohete);
	m_first_cohete=pcohete;
	return 0;
}

DWORD C3DViewGame::GameCheckColision(C3DCohete *p3dcohete)
{
	S_3DSIZE	size1,size2;
	C3DNave*	m_nave;
	if (!p3dcohete)
		return false;
	if (!p3dcohete->m_lp3dmesh)
		return false;
	p3dcohete->m_lp3dmesh->GetSize(&size1);

	// ajuste por posicion
	size1.x1+=p3dcohete->m_currentx;
	size1.y1+=p3dcohete->m_currenty;
	size1.z1+=p3dcohete->m_currentz;
	size1.x2+=p3dcohete->m_currentx;
	size1.y2+=p3dcohete->m_currenty;
	size1.z2+=p3dcohete->m_currentz;

	m_nave=(C3DNave*)m_first_nave;
	while (true)
	{
		if (!m_nave)
			break;
		if (!m_nave->m_vuelta)
		{
		m_nave->m_lp3dmesh->GetSize(&size2);
		size2.x1+=m_nave->m_currentx;
		size2.y1+=m_nave->m_currenty;
		size2.z1+=m_nave->m_currentz;
		size2.x2+=m_nave->m_currentx;
		size2.y2+=m_nave->m_currenty;
		size2.z2+=m_nave->m_currentz;

		if (!((size1.x1 < size2.x1 && size1.x2 < size2.x1)||
			(size1.x1 > size2.x1 && size2.x2 < size1.x1)||
			// Y
			(size1.y1 < size2.y1 && size1.y2 < size2.y1)||
			(size1.y1 > size2.y1 && size2.y2 < size1.y1)||
			// z
			(size1.z1 < size2.z1 && size1.z2 < size2.z1)||
			(size1.z1 > size2.z1 && size2.z2 < size1.z1)
			))
		{
			m_score+=10;
			m_nave->m_vuelta=true;
			p3dcohete->m_delete=true;
			return false;
		}
		}
		m_nave=(C3DNave*)m_nave->GetNext();
	}
	return true;
}

DWORD C3DViewGame::GameAdd3DNave(C3DNave *lp3dnave)
{
	if (m_first_nave)
		m_first_nave->SetPrev(lp3dnave);
	lp3dnave->SetNext(m_first_nave);
	lp3dnave->SetPrev(NULL);
	m_first_nave=lp3dnave;
	return 0;
}

/*
	Detiene el juego
*/
DWORD C3DViewGame::GameStop()
{
	return 0;
}

DWORD C3DViewGame::GamePause()
{
	m_play=false;
	m_message_time=INFINITE;
	return 0;
}

DWORD C3DViewGame::GamePlay()
{
	m_play=true;
	m_message_time=0;
	return 0;
}

DWORD C3DViewGame::GameEnd()
{
	OglDestroyRC();
	GameDestroy();
	return 0;
}

DWORD C3DViewGame::GameEndTime()
{
	GamePause();
	m_end_time=true;
	
	HFONT	oldfont =(HFONT)::SelectObject(m_hdc,m_font);
	RECT rect;
	rect.left=0;
	rect.top=200;
	rect.bottom=420;
	rect.right=(long)WWIDTH;
	::SetBkMode(m_hdc,TRANSPARENT);
	::SetTextColor(m_hdc,0xFFFFFF);
	DrawText(m_hdc,"GAME  OVER \n Press ESC to Abort \n or RETURN to save the condition ",-1,&rect,DT_LEFT|DT_VCENTER|DT_CENTER);
	::SelectObject(m_hdc,oldfont);
	return 0;
}

DWORD C3DViewGame::GameFullScreen()
{
	HRESULT             ddrval;
    ddrval = DirectDrawCreate( NULL, &m_dd, NULL );
	if (ddrval)
		return GERR_DD;
    ddrval = m_dd->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN	);
	if (ddrval)
		return GERR_DDCL;
	ddrval = m_dd->SetDisplayMode( 640, 480, 16 );
	if (ddrval)
		return GERR_DDDM;

	return 0;
}

DWORD C3DViewGame::GameExitFullScreen()
{
#ifdef NO_DD
#else
	if (m_dd)
	{
		m_dd->Release();
		m_dd=NULL;
	}
#endif
	return 0;
}

DWORD C3DViewGame::SetGameMode(BOOL ponline)
{
	m_online=ponline;
	return 0;
}

DWORD C3DViewGame::Run()
{
	RegisterClass();
	CreateDirectXWindow();
	/*
	if (CreateDirectX())
	{
		ReleaseDirectX();
		return 0;
	}
	*/
#ifdef NO_DD
#else
	GameFullScreen();
#endif
	GameInitialize();
	m_OnDirectX=true;
	m_OnPause=false;
	return	MainLoop();
}

HRESULT C3DViewGame::VFWindProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return WindowProc(Msg,wParam,lParam);
}

DWORD C3DViewGame::VFDrawFrame()
{
	return OglRenderContext();
}
