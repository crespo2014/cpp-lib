// g30c03.cpp: implementation of the CGameWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "g30def.h"
#include "g30c03.h"
#include "g30c04.h"	//CDXMesh

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameWind::CGameWind()
{
		
}

CGameWind::~CGameWind()
{
	Release();
}

LRESULT CGameWind::WindProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_PAINT:
		PAINTSTRUCT	ps;
		::BeginPaint(m_hWnd,&ps);
		::EndPaint(m_hWnd,&ps);
		return 0;
		/*
	case WM_ERASEBKGND:
		return 0;
		*/
	case WM_CLOSE:
		return 0;
	case WM_KEYDOWN:
		KeyDown(wParam,lParam);
		return 0;
	case WM_SETCURSOR:
		//SetCursor(NULL);
		return 0;
	case WM_ACTIVATEAPP:
		if (wParam)
		{
			m_dxescene.RestoreAll();
			m_OnRun=true;
		}
		else
		{
			m_OnRun=false;
		}

	}
	return CWind::WindProc(hWnd,Msg,wParam,lParam);
}

DWORD CGameWind::Initialize()
{
	if (CWind::Initialize() !=0)
		return 1;
	m_OnExit=FALSE;
	m_OnPlay=FALSE;
	m_OnRun=FALSE;
	m_dxescene.Initialize();

	m_angulo=0;
	return 0;
}

DWORD CGameWind::Release()
{
	return 0;
}

DWORD CGameWind::Run()
{
	// Crear la ventana
	if (CreateWindEx(WS_EX_APPWINDOW,"DirectX Game",WS_POPUP|WS_VISIBLE,0,0,100,100,GetDesktopWindow(),NULL,this)!=0)
		goto failed;
	m_dxescene.SetWind(m_hWnd);
	if (m_dxescene.CreateDirectX()!=0)
	{
		::DestroyWindow(m_hWnd);
		return 1;
	}
	GameInitialize();
	m_OnRun=true;
	// Ciclo indefinido
	MSG msg;
	while (!m_OnExit)
	{
		if (m_OnRun)
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
				ProcessMessage(&msg);
		}
		else
		{
			if (GetMessage(&msg,NULL,0,0))
				ProcessMessage(&msg);
		}
		if (m_OnRun)
		{
			DrawFrame();
		}
	}
	return 0;
failed:
	return 1;
}

/*
	Procesa mensajes de windows
*/	
DWORD CGameWind::ProcessMessage(MSG *lpmsg)
{
	if (lpmsg->message == WM_QUIT)
	{
		m_OnExit=TRUE;
		return 1;
	}
	TranslateMessage (lpmsg);
    DispatchMessage (lpmsg);
	return 0;
}

/*
	Dibuja la escena
*/
DWORD CGameWind::DrawFrame()
{
	if (m_OnPlay)
		UpDateFrame();

	m_angulo+=5;
	if (m_angulo > 360)
		m_angulo=0;
	D3DMATRIX	matworld=
	{
		cos(m_angulo*3.14/180),0,-sin(m_angulo*3.14/180),0
		,0,1,0,0
		,sin(m_angulo*3.14/180),0,cos(m_angulo*3.14/180),0
		,0,0,0,1
	};

	m_dxescene.SetTransform( D3DTRANSFORMSTATE_WORLD, &matworld ); 

	LPDIRECT3DDEVICE7 m_lpd3ddevice;
	m_dxescene.GetD3DDevice(&m_lpd3ddevice);

	m_lpd3ddevice->BeginScene();
	m_lpd3ddevice->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0x000000,1.0f,0);
	//m_lpd3ddevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,0x000000,1.0f,0);
	m_lpmesh->Paint();
	m_lpd3ddevice->EndScene();
		
	m_dxescene.FlipSurfaces();
	return 0;
}

DWORD CGameWind::UpDateFrame()
{
	return 0;
}

DWORD CGameWind::KeyDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_ESCAPE)
	{
		m_dxescene.Release();
		DestroyWindow(m_hWnd);
		m_OnExit=TRUE;
	}
	return 0;
}

typedef struct 
{
	float x,y,z;
}VERTEX_XYZ;

DWORD CGameWind::GameInitialize()
{
	if (m_dxescene.AddNewMesh(&m_lpmesh) !=0)
		return 1;

	#define VERTEX VERTEX_XYZ

	VERTEX g_pvTriangleVertices[12];

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
	m_lpmesh->SetVertex(3,D3DFVF_XYZ,g_pvTriangleVertices);
	m_lpmesh->SetPrimitiveType(D3DPT_TRIANGLELIST);

	D3DMATRIX matWorld =
	{
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
    m_dxescene.SetTransform( D3DTRANSFORMSTATE_WORLD, &matWorld );
	    
	D3DMATRIX matView = 
	{
		 1,0,0,0
		,0,1,0,0
		,0,0,1,0
		,0,0,-20,1
	};
	m_dxescene.SetTransform( D3DTRANSFORMSTATE_VIEW, &matView );

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
	 
	m_dxescene.SetTransform( D3DTRANSFORMSTATE_PROJECTION,&matproy );

	m_dxescene.ViewPort(0,0,640,480);

	LPDIRECT3DDEVICE7 m_D3DDevice;
	m_dxescene.GetD3DDevice(&m_D3DDevice);


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
	m_D3DDevice->SetRenderState( D3DRENDERSTATE_AMBIENT, 0xffffff);
	
	D3DLIGHT7	light;
	ZeroMemory(&light,sizeof(light));
	light.dltType =D3DLIGHT_POINT;
	light.dcvAmbient.r=0.0;
	light.dcvAmbient.g=0.0;
	light.dcvAmbient.b=0.0;
	light.dcvDiffuse.r=1.0;
	light.dcvDiffuse.g=1.0;
	light.dcvDiffuse.b=1.0;
	light.dcvDiffuse.a=1.0;
	light.dvDirection.x=0;
	light.dvDirection.y=0;
	light.dvDirection.z=-1;
	light.dvPosition.x=1;
	light.dvPosition.y=0;
	light.dvPosition.z=0;
	light.dvAttenuation0=1.0;
	light.dvAttenuation1=0.1;
	light.dvAttenuation2=0.0;
	light.dvRange=D3DLIGHT_RANGE_MAX;
	m_D3DDevice->SetLight(0,&light);
	m_D3DDevice->LightEnable(0,TRUE);

	m_D3DDevice->SetRenderState(D3DRENDERSTATE_LIGHTING,TRUE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_FILLMODE,D3DFILL_SOLID);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE,TRUE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE,FALSE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_CULLMODE,D3DCULL_NONE);
	m_D3DDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE );
	
	return 0;
}
