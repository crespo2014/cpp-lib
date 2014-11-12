
//#define VERTEX D3DLVERTEX
#define VERTEX VERTEX_XYZ

typedef struct 
{
	float x,y,z;
}VERTEX_XYZ;

#include "gdef.h"
#include "gc01.h"

/*
 *	Constantes utilizadas
 */
    VERTEX g_pvTriangleVertices[12];

	float fTimeKey=0;

/*
	Constantes
*/
#define CLASS_NAME "DirectXWindow"
/*
	Variables globales
*/
BOOL		m_OnRegister=false;		//Indica si la ventana ya fue registrada
ATOM		m_ClassAtom=0;			//Clase registrada
HINSTANCE	m_hInstance=0;		

/*
	Posibles respuestas de error
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LRESULT CALLBACK DirectXGameWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CDirectXGame*	lpWnd;
	if ((Msg == WM_CREATE) || (Msg == WM_NCCREATE))
	{
		CREATESTRUCT*	lpcs;
		lpcs = (CREATESTRUCT*)lParam;
		lpWnd = (CDirectXGame*) lpcs->lpCreateParams;
		::SetWindowLong(hWnd,GWL_USERDATA,(long)lpWnd);
	}
	else
		lpWnd = (CDirectXGame*)::GetWindowLong(hWnd,GWL_USERDATA);
	if (lpWnd)
		return lpWnd->VFWindProc(hWnd,Msg,wParam,lParam);
	else
		return DefWindowProc(hWnd,Msg,wParam,lParam);
}
/*
	CallBack Funtion
*/
HRESULT CALLBACK D3DEnumZBufferCallback(  LPDDPIXELFORMAT lpDDPixFmt,LPVOID lpContext)
{
	CDirectXGame* pThis=(CDirectXGame*)lpContext;

	if( lpDDPixFmt->dwFlags == DDPF_ZBUFFER ) 
	{
        memcpy(&pThis->m_ZBPF, lpDDPixFmt, sizeof(pThis->m_ZBPF)); 
		if (lpDDPixFmt->dwZBufferBitDepth==16)
		{
			pThis->m_OnZBuffer=true;
		}
		if (lpDDPixFmt->dwZBufferBitDepth==32)
		{
			pThis->m_OnZBuffer=true;
			return D3DENUMRET_CANCEL;
		}
    }
	return D3DENUMRET_OK;		// Continuar enumerando
}


CDirectXGame::CDirectXGame()
{
	m_hInstance=(HINSTANCE)GetModuleHandle(NULL);
	m_DDraw=NULL;
	m_DDSurface=NULL;
	m_DDBackSurface=NULL;
	m_D3D=NULL;
	m_D3DDevice=NULL;
	m_DDZBuffer=NULL;
	m_hWnd=0;
	m_OnPause=false;
	m_OnDirectX=false;
	m_OnActive=false;

	radio=200;
	ang=0;

	
	VERTEX v11={ 0.0f , 0.0f ,0.0f};// ,0 ,0xff0000};
	VERTEX v21={ 10.0f, 0.0f ,0.0f};// ,0 ,0xff0000};
	VERTEX v31={ 0.0f , 10.0f,0.0f };//,0 ,0xff0000};

	VERTEX v12={ 0.0f , 0.0f ,0.0f};// ,0  ,0x00ff00};
	VERTEX v22={ -10.0f, 0.0f ,0.0f};// ,0 ,0x00ff00};
	VERTEX v32={ 0.0f , 10.0f,0.0f};// ,0  ,0x00ff00};

	VERTEX v13={ 0.0f , 0.0f ,0.0f};// ,0 ,0x0000ff};
	VERTEX v23={ 0.0f, 0.0f ,10.0f};// ,0 ,0x0000ff};
	VERTEX v33={ 0.0f , 10.0f,0.0f};// ,0 ,0x0000ff};

	VERTEX v14={ 0.0f , 0.0f ,0.0f };//,0  ,0xffffff};
	VERTEX v24={ 0.0f, 0.0f ,-10.0f};// ,0 ,0xffffff};
	VERTEX v34={ 0.0f , 10.0f,0.0f};// ,0  ,0xffffff};
	

	g_pvTriangleVertices[0]=v11;
	g_pvTriangleVertices[1]=v31;
	g_pvTriangleVertices[2]=v21;
	g_pvTriangleVertices[3]=v12;
	g_pvTriangleVertices[4]=v32;
	g_pvTriangleVertices[5]=v22;
	g_pvTriangleVertices[6]=v13;
	g_pvTriangleVertices[7]=v33;
	g_pvTriangleVertices[8]=v23;
	g_pvTriangleVertices[9]=v14;
	g_pvTriangleVertices[10]=v34;
	g_pvTriangleVertices[11]=v24;
}

CDirectXGame::~CDirectXGame()
{
	ReleaseDirectX();
}

/*
	Registrar la ventana
*/
DWORD CDirectXGame::RegisterClass()
{
	if (m_OnRegister)
		return 0;
	WNDCLASSEX	classData;
	classData.cbSize=sizeof(classData);
	classData.cbClsExtra=0;
	classData.cbWndExtra=0;
	classData.hbrBackground=0;
	classData.hCursor=0;
	classData.hIcon=0;
	classData.hIconSm=0;
	classData.hInstance=m_hInstance;
	classData.lpfnWndProc=DirectXGameWndProc;
	classData.lpszClassName=CLASS_NAME;
	classData.lpszMenuName=0;
	classData.style=CS_DBLCLKS;
	m_ClassAtom=RegisterClassEx(&classData);
	if (!m_ClassAtom)
		return 1;
	m_OnRegister=true;
	return 0;
}

LRESULT CDirectXGame::WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_DESTROY:
		{
			ReleaseDirectX();
			::PostQuitMessage(0);
			return 0;
		}
	case WM_CHAR:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(m_hWnd);
					break;
			}
			return 0;
		}
		
		/*
	case WM_SETCURSOR:
        SetCursor(NULL);
		return TRUE;
		*/
	case WM_ACTIVATEAPP:
		{
			m_OnActive	= (BOOL) wParam;
			if (m_OnActive)
			{
				if (m_OnDirectX)
				{
					m_DDSurface->Restore();
					m_DDZBuffer->Restore();
				}
			}
			else
			{
				
			}
			break;
		}
	}
	return DefWindowProc(hWnd,Msg,wParam,lParam);
	
}

/*
	Creacion de la ventana de render
*/
DWORD CDirectXGame::CreateDirectXWindow()
{
	if (!m_OnRegister)
		return 1;
	m_hWnd=CreateWindowEx(WS_EX_APPWINDOW,CLASS_NAME,"DirectX Game",WS_POPUP|WS_VISIBLE,0,0,100,100,GetDesktopWindow(),NULL,m_hInstance,this);
	if (!m_hWnd)
		return 2;
	return 0;
}

DWORD CDirectXGame::MainLoop()
{
	MSG msg;
	BOOL m_OnM;
	while (true)
	{
		if (m_OnActive && !m_OnPause)
			m_OnM=::PeekMessage(&msg,NULL,0,0,PM_REMOVE);
		else
		{
			::GetMessage(&msg,NULL,0,0);
			m_OnM=true;
		}
		if (m_OnM)
		{
			if (msg.message == WM_QUIT)
				return 0;
			TranslateMessage (&msg);
            DispatchMessage (&msg);
		}
		RenderScene();
	}
	return 0;
}

/*
	Si no se crea la superficie en memoria de video
	entonces se crea una en memoria del sistema
	si nose crea un HAL entonces creo un HEL
	crear viewport y adicionar viewport
*/
DWORD CDirectXGame::CreateDirectX()
{
	HRESULT	hResult,hr;
	DDSURFACEDESC2	ddsd;
	DDSCAPS2		ddscaps;
	hResult = ::DirectDrawCreateEx(NULL,(void**)&m_DDraw,IID_IDirectDraw7,NULL);
	if (hResult)
		return ERR_NO_DD;
	
    hr = m_DDraw->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT);
	if (hr)
		return ERR_NO_CL;
	
	hResult = m_DDraw->SetDisplayMode(640,480,16,0,0);
	if (hResult)
		return ERR_NO_DM;


	memset(&ddsd,0,sizeof(ddsd));
	memset(&ddscaps,0,sizeof(ddscaps));
	ddsd.dwSize = sizeof( ddsd );
	
	ddsd.dwFlags = DDSD_CAPS | 
				   DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE
						  | DDSCAPS_FLIP 
						  | DDSCAPS_COMPLEX
						  | DDSCAPS_3DDEVICE
						  | DDSCAPS_VIDEOMEMORY
						 ;
    ddsd.dwBackBufferCount = 1;

    hResult = m_DDraw->CreateSurface( &ddsd, &m_DDSurface, NULL );
	if (hResult)
		return ERR_NO_DDS;
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    hResult = m_DDSurface->GetAttachedSurface(&ddscaps, &m_DDBackSurface);

	// D3D 
	hResult=m_DDraw->QueryInterface(IID_IDirect3D7,(void**)&m_D3D);
	if (hResult)
		return ERR_NO_D3DI;

    
	// crear un z-buffer para HAL
	if (D3DCreateZBuffer(IID_IDirect3DHALDevice)==0)
	{
		hr=m_D3D->CreateDevice(IID_IDirect3DHALDevice,m_DDBackSurface,&m_D3DDevice);
		if (hr != 0)
		{
			m_DDBackSurface->DeleteAttachedSurface(0,NULL);
			m_DDZBuffer->Release();
		}
		else
		{
			m_OnDirectX=true;
			return 0;
		}
	}

	if (D3DCreateZBuffer(IID_IDirect3DRGBDevice)==0)
	{
		hr=m_D3D->CreateDevice(IID_IDirect3DRGBDevice,m_DDBackSurface,&m_D3DDevice);
		if (hr != 0)
		{
			m_DDBackSurface->DeleteAttachedSurface(0,NULL);
			m_DDZBuffer->Release();
			return 1;
		}
	}
	m_OnDirectX=true;
	return 0;
}

DWORD CDirectXGame::ReleaseDirectX()
{
	if (m_D3DDevice)	m_D3DDevice->Release();
	if (m_D3D)			m_D3D->Release();
	if (m_DDBackSurface) m_DDBackSurface->DeleteAttachedSurface(0,NULL);
	if (m_DDZBuffer)	m_DDZBuffer->Release();
	if (m_DDSurface)	m_DDSurface->Release();
	if (m_DDraw)		m_DDraw->Release();
	m_DDSurface=NULL;
	m_DDBackSurface=NULL;
	m_DDraw=NULL;
	m_D3DDevice=NULL;
	m_D3D=NULL;
	m_DDZBuffer=NULL;
	m_OnDirectX=false;
	m_OnPause=true;
	return 0;
}

DWORD CDirectXGame::RenderScene()
{
	if (!(m_OnActive && m_OnDirectX))
		return 0;
	
	fTimeKey+=2;
	if (fTimeKey > 360)
		fTimeKey=0;
	D3DMATRIX	matworld=
	{
		cos(fTimeKey*3.14/180),0,-sin(fTimeKey*3.14/180),0
		,0,1,0,0
		,sin(fTimeKey*3.14/180),0,cos(fTimeKey*3.14/180),0
		,0,0,0,1
	};

	m_D3DDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matworld ); 
	m_D3DDevice->Clear(0,NULL,D3DCLEAR_TARGET,0x0000ff,1.0f,0);
	m_D3DDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,0x000000,1.0f,0);
	
	if(m_D3DDevice->BeginScene()) 
		return 0;
	m_D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,D3DFVF_XYZ,
                               g_pvTriangleVertices, 12, 0  ); 
	m_D3DDevice->EndScene();
	m_DDSurface->Flip(NULL,0);
 	return 0;
}

DWORD CDirectXGame::InitScene()
{
	D3DVIEWPORT7 vp = { 0, 0, 640, 480, 0.0f, 1.0f };
	m_D3DDevice->SetViewport(&vp);

	D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.diffuse.r = mtrl.diffuse.g = mtrl.diffuse.b = 1.0f;
    mtrl.ambient.r = mtrl.ambient.g = mtrl.ambient.b = 1.0f;
    m_D3DDevice->SetMaterial( &mtrl );

	//D3DMATERIAL7 mtrl;
    ZeroMemory( &mtrl, sizeof(mtrl) );
    mtrl.ambient.r = 1.0f;
    mtrl.ambient.g = 1.0f;
    mtrl.ambient.b = 0.0f;
    m_D3DDevice->SetMaterial( &mtrl );
//	m_D3DDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffff );
	
	D3DLIGHT7	light;
	ZeroMemory(&light,sizeof(light));
	light.dltType =D3DLIGHT_POINT;
	light.dcvAmbient.r=1.0;
	light.dcvAmbient.g=1.0;
	light.dcvAmbient.b=1.0;
	light.dcvDiffuse.r=1.0;
	light.dcvDiffuse.g=1.0;
	light.dcvDiffuse.b=1.0;
	light.dcvDiffuse.a=1.0;
	light.dvDirection.x=0;
	light.dvDirection.y=0;
	light.dvDirection.z=1;
	light.dvPosition.x=1;
	light.dvPosition.y=-1;
	light.dvPosition.z=-1;
	light.dvAttenuation0=1.0;
	light.dvAttenuation1=0.1;
	light.dvAttenuation2=0.0;
	m_D3DDevice->SetLight(0,&light);
	m_D3DDevice->LightEnable(0,TRUE);

	m_D3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,FALSE                                                                                                                                                                                                                                                          );
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_SOLID);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE,FALSE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_NONE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
	
    D3DMATRIX matWorld =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
    m_D3DDevice->SetTransform( D3DTRANSFORMSTATE_WORLD, &matWorld );
	    
	D3DMATRIX matView = 
	{
		 1,0,0,0
		,0,1,0,0
		,0,0,1,0
		,0,0,-20,1
	};
	m_D3DDevice->SetTransform( D3DTRANSFORMSTATE_VIEW, &matView );

	float ang =40.0f;
	float znear=1.0f;
	float zfar =100.0f;
	float top =(float)tan(ang*3.14/180)*znear;
	float bottom=-top;
	float right=top*640/480;
	float left=-right;
	
	D3DMATRIX matproy=
	{
	 2*znear/(right-left),0					  ,(right+left)/(right-left) ,0
	,0				 	 ,2*znear/(top-bottom),(top+bottom)/(top-bottom) ,0
	,0					 ,0				 	  ,-(zfar+znear)/(zfar-znear),-2*zfar*znear/(zfar-znear)
	,0					 ,0					  ,-1						 ,0
	};
	 
	m_D3DDevice->SetTransform( D3DTRANSFORMSTATE_PROJECTION,&matproy );
	return 0;
}

/*
	Enumera y crea un z-buffer para el dispositivo especificado
*/
DWORD CDirectXGame::CreateZBuffer(REFCLSID rclsid)
{
	HRESULT	hr;
	hr=m_D3D->EnumZBufferFormats(rclsid,D3DEnumZBufferCallback,this);
	if ((hr==0)&&(m_OnZBuffer))	
		return 0;			
	return 1;
}

DWORD CDirectXGame::D3DReleaseZBuffer()
{
	if (m_DDZBuffer)
		m_DDZBuffer->Release();
	return 0;
}

DWORD CDirectXGame::D3DCreateZBuffer(REFCLSID rclsid)
{
	HRESULT	hr;
	DDSURFACEDESC2	ddsd;
	DDSCAPS2		ddscaps;

	hr=m_D3D->EnumZBufferFormats(rclsid,D3DEnumZBufferCallback,this);
	if ((hr!=0)&&(!m_OnZBuffer))
		return 1;

	// crear z-buffer
	memset(&ddsd,0,sizeof(ddsd));
	memset(&ddscaps,0,sizeof(ddscaps));	
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags        = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
    ddsd.dwWidth        = 640;
    ddsd.dwHeight       = 480;
	if (rclsid==IID_IDirect3DHALDevice)
		ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	memcpy( &ddsd.ddpfPixelFormat, &m_ZBPF,sizeof(ddsd.ddpfPixelFormat)); 
	hr=m_DDraw->CreateSurface(&ddsd,&m_DDZBuffer,NULL);
	if (hr)
		return 1;
	hr=m_DDBackSurface->AddAttachedSurface(m_DDZBuffer);
	if (hr)
		return 1;
	return 0;
}

DWORD CDirectXGame::Run()
{
	RegisterClass();
	CreateDirectXWindow();
	if (CreateDirectX())
	{
		ReleaseDirectX();
		return 0;
	}
	InitScene();
	return	MainLoop();
}

LRESULT CDirectXGame::VFWindProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return WindowProc(hWnd,Msg,wParam,lParam);
}

DWORD CDirectXGame::VFDrawFrame()
{
	RenderScene();
	return 0;
}
