// g30c06.cpp: implementation of the CDXEscene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#define INITGUID
#include "g30def.h"
#include "g30c06.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef struct
{
	BOOL			on_valid;
	DDPIXELFORMAT	ddpf;
}S_ZBUFFER;

CDXEscene::CDXEscene()
{
	m_on_init=false;
}

CDXEscene::~CDXEscene()
{
	Release();
}

DWORD CDXEscene::Initialize()
{
	m_on_init=TRUE;
	m_bpp=16;
	m_cooperativeflags=DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT;
	m_height=480;
	m_hwnd=NULL;
	m_lpd3d7=NULL;
	m_lpd3ddevice7=NULL;
	m_lpddbacksurface7=NULL;
	m_lpddfrontsurface7=NULL;
	m_lpddraw7=NULL;
	m_lpddzbuffer=NULL;
	m_on_fullscreen=TRUE;
	m_on_zbuffer=TRUE;
	m_refresh_rate=0;
	m_width=640;
	m_first_mesh=NULL;
	return 0;
}

DWORD CDXEscene::Release()
{
	if (!m_on_init)
		return 0;
	DestroyDirectX();
	DeleteAllMesh();
	return 0;
}

DWORD CDXEscene::SetWind(HWND phwnd)
{
	m_hwnd=phwnd;
	return 0;
}

DWORD CDXEscene::CreateDirectDraw()
{
	HRESULT			hr;
	DDSURFACEDESC2	ddsd;
	DDSCAPS2		ddscaps;
	hr=::DirectDrawCreateEx(NULL,(void**)&m_lpddraw7,IID_IDirectDraw7,NULL);
	if (hr!=DD_OK)
		goto failed;
	hr = m_lpddraw7->SetCooperativeLevel(m_hwnd,m_cooperativeflags);
	if (hr!=DD_OK)
		goto failed;
	hr = m_lpddraw7->SetDisplayMode(m_width,m_height,m_bpp,m_refresh_rate,0);
	if (hr!=DD_OK)
		goto failed;

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
	hr = m_lpddraw7->CreateSurface( &ddsd, &m_lpddfrontsurface7, NULL );
	if (hr!=DD_OK)
		goto failed;
	ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    hr = m_lpddfrontsurface7->GetAttachedSurface(&ddscaps, &m_lpddbacksurface7);
	if (hr!=DD_OK)
		goto failed;
	return 0;
failed:
	if (m_lpddfrontsurface7 != NULL)	m_lpddfrontsurface7->Release();
	if (m_lpddraw7 != NULL )			m_lpddraw7->Release();
	m_lpddbacksurface7=NULL;
	m_lpddfrontsurface7=NULL;
	m_lpddraw7=NULL;
	return 1;
}

DWORD CDXEscene::CreateDirectX()
{
	if (!m_on_init)
		return 1;
	if (m_hwnd == NULL)
		return 1;
	if (CreateDirectDraw()!=0)
		return 1;
	if (CreateD3D(IID_IDirect3DHALDevice)==0)
		return 0;
	if (CreateD3D(IID_IDirect3DRGBDevice)==0)
		return 0;
	DestroyDDraw();
	return 1;
}
HRESULT CALLBACK CDXEscene::D3DEnumZBufferCallback(  LPDDPIXELFORMAT lpDDPixFmt,LPVOID lpContext)
{
	S_ZBUFFER*	param= (S_ZBUFFER*)lpContext;
	if( lpDDPixFmt->dwFlags == DDPF_ZBUFFER ) 
	{
        memcpy(&param->ddpf, lpDDPixFmt, sizeof(param->ddpf)); 
		if (lpDDPixFmt->dwZBufferBitDepth==16)
		{
			param->on_valid=TRUE;
			return D3DENUMRET_CANCEL;
		}
		if (lpDDPixFmt->dwZBufferBitDepth==32)
		{
			param->on_valid=TRUE;
			return D3DENUMRET_CANCEL;
		}
    }
	return D3DENUMRET_OK;
}

DWORD CDXEscene::CreateD3D(REFCLSID pd3dclsid)
{
	HRESULT	hr;
	if (m_lpddraw7 == NULL)
		return 1;
	// D3D 
	hr=m_lpddraw7->QueryInterface(IID_IDirect3D7,(void**)&m_lpd3d7);
	if (hr)
		return 2;
	// Crear z-buffer
	if (CreateZBuffer(pd3dclsid)!=0)
		goto failed;
	hr=m_lpd3d7->CreateDevice(pd3dclsid,m_lpddbacksurface7,&m_lpd3ddevice7);
	if (hr != 0)
		goto failed;
	return 0;
failed:
	if (m_lpddzbuffer) m_lpddzbuffer->Release();
	if (m_lpd3d7) m_lpd3d7->Release();
	m_lpddzbuffer=NULL;
	m_lpd3d7=NULL;
	return 2;
}

DWORD CDXEscene::CreateZBuffer(REFCLSID pd3dclsid)
{
	S_ZBUFFER		param;
	HRESULT			hr;
	DDSURFACEDESC2	ddsd;
	DDSCAPS2		ddscaps;
	if (!m_lpd3d7)
		return 1;
	param.on_valid=FALSE;
	hr=m_lpd3d7->EnumZBufferFormats(pd3dclsid,D3DEnumZBufferCallback,&param);
	if (hr != DD_OK)
		return 2;
	if (!param.on_valid)
		return 1;
	// crear z-buffer
	memset(&ddsd,0,sizeof(ddsd));
	memset(&ddscaps,0,sizeof(ddscaps));	
	ddsd.dwSize = sizeof( ddsd );
	ddsd.dwFlags        = DDSD_CAPS|DDSD_WIDTH|DDSD_HEIGHT|DDSD_PIXELFORMAT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_ZBUFFER;
    ddsd.dwWidth        = m_width;
    ddsd.dwHeight       = m_height;
	if (pd3dclsid==IID_IDirect3DHALDevice)
		ddsd.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	else
		ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	memcpy( &ddsd.ddpfPixelFormat, &param.ddpf,sizeof(ddsd.ddpfPixelFormat));
	hr=m_lpddraw7->CreateSurface(&ddsd,&m_lpddzbuffer,NULL);
	if (hr)
		return 2;
	hr=m_lpddbacksurface7->AddAttachedSurface(m_lpddzbuffer);
	if (hr==DD_OK)
		return 0;
	m_lpddzbuffer->Release();
	m_lpddzbuffer=NULL;
	return 2;
}

DWORD CDXEscene::RestoreAll()
{
	if (!m_lpddraw7)
		return 1;
	if (m_lpddraw7->RestoreAllSurfaces() != DD_OK)
		return 2;
	return 0;
}

DWORD CDXEscene::DestroyD3D()
{
	if (m_lpd3ddevice7	!= NULL)	m_lpd3ddevice7->Release();
	if (m_lpddzbuffer	!= NULL)	m_lpddzbuffer->Release();
	if (m_lpd3d7		!= NULL)	m_lpd3d7->Release();
	m_lpd3ddevice7=NULL;
	m_lpddzbuffer=NULL;
	m_lpd3d7=NULL;
	return 0;
}

DWORD CDXEscene::DestroyDDraw()
{
	if (m_lpddfrontsurface7	!= NULL)	m_lpddfrontsurface7->Release();
	if (m_lpddraw7			!= NULL)	m_lpddraw7->Release();
	m_lpddfrontsurface7=NULL;
	m_lpddraw7=NULL;
	m_lpddbacksurface7=NULL;
	return 0;
}

DWORD CDXEscene::GetD3DDevice(LPDIRECT3DDEVICE7 *plpd3ddevice)
{
	*plpd3ddevice=m_lpd3ddevice7;
	return 0;
}

DWORD CDXEscene::FlipSurfaces()
{
	m_lpddfrontsurface7->Flip(NULL,0);
	return 0;
}

DWORD CDXEscene::DestroyDirectX()
{
	DestroyD3D();
	DestroyDDraw();
	return 0;
}

DWORD CDXEscene::LoadIdentity(D3DTRANSFORMSTATETYPE ptst)
{
	if (!m_lpd3ddevice7)
		return 1;
	D3DMATRIX	mat={
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		0.0,0.0,0.0,1.0};
	m_lpd3ddevice7->SetTransform(ptst,&mat);
	return 0;
}


DWORD CDXEscene::Frustum(float left, float right, float bottom, float top, float znear, float zfar)
{
	if (!m_lpd3ddevice7)
		return 1;
	float A11=2*znear/(right-left);
	float A22=2*znear/(top-bottom);
	float A=(right+left)/(right-left);
	float B=(top+bottom)/(top-bottom);
	float C=-(zfar+znear)/(zfar-znear);
	float D=-2*zfar*znear/(zfar-znear);
	D3DMATRIX	mat={
		A11  ,0.0  ,A  ,0.0,
		0.0  ,A22  ,B  ,0.0,
		0.0  ,0.0  ,C  ,D,
		0.0  ,0.0  ,-1 ,0.0,
		};
	m_lpd3ddevice7->SetTransform(D3DTRANSFORMSTATE_PROJECTION,&mat);
	return 0;	
}

DWORD CDXEscene::Perspective(float fovy, float aspect, float znear, float zfar)
{
	fovy*=3.14f/180.0f;
	float top=(float)tan(fovy/2);
	float bottom=-top;
	float left=-top*aspect;
	float right=-left;
	return Frustum(left,right,bottom,top,znear,zfar);
}

DWORD CDXEscene::RotateX(float ang)
{
	if (!m_lpd3ddevice7)
		return 1;
	ang*=3.14f/180.0f;
	D3DMATRIX	mat={
		1.0	,0.0		,0.0	,0.0,
		0.0	,cos(ang)	,sin(ang)	,0.0,
		0.0	,-sin(ang)	,-cos(ang)	,0.0,
		0.0	,0.0		,0.0		,1.0};
	m_lpd3ddevice7->MultiplyTransform(D3DTRANSFORMSTATE_WORLD,&mat);
	return 0;
}

DWORD CDXEscene::RotateY(float ang)
{
	if (!m_lpd3ddevice7)
		return 1;
	ang*=3.14f/180.0f;
	D3DMATRIX	mat={
		cos(ang),0.0	,-sin(ang)	,0.0,
		0.0		,1.0	,0.0		,0.0,
		sin(ang),0.0	,cos(ang)	,0.0,
		0.0		,0.0	,0.0		,1.0};
	m_lpd3ddevice7->MultiplyTransform(D3DTRANSFORMSTATE_WORLD,&mat);
	return 0;
}

DWORD CDXEscene::RotateZ(float ang)
{
	if (!m_lpd3ddevice7)
		return 1;
	ang*=3.14f/180.0f;
	D3DMATRIX	mat={
		cos(ang),sin(ang)	,0.0		,0.0,
		0.0		,-sin(ang)	,cos(ang)	,0.0,
		0.0		,0.0		,1.0		,0.0,
		0.0		,0.0		,0.0		,1.0};
	m_lpd3ddevice7->MultiplyTransform(D3DTRANSFORMSTATE_WORLD,&mat);
	return 0;
}

DWORD CDXEscene::Translate(float x, float y, float z)
{
	if (!m_lpd3ddevice7)
		return 1;
		D3DMATRIX	mat={
		1.0,0.0,0.0,x,
		0.0,1.0,0.0,y,
		0.0,0.0,1.0,z,
		0.0,0.0,0.0,1.0};
	m_lpd3ddevice7->MultiplyTransform(D3DTRANSFORMSTATE_WORLD,&mat);
	return 0;
}



DWORD CDXEscene::DeleteMesh(CDXMesh *lpmesh)
{
	if (lpmesh->m_prev != NULL)
		lpmesh->m_prev->m_next=lpmesh->m_next;
	else
		m_first_mesh = lpmesh->m_next;
	if (lpmesh->m_next !=NULL)
		lpmesh->m_next->m_prev=lpmesh->m_prev;
	delete lpmesh;	
	return 0;
}

DWORD CDXEscene::AddNewMesh(CDXMesh **lplpmesh)
{
	CDXMesh* lpmesh= new CDXMesh();
	if (lpmesh == NULL)
		return 1;
	lpmesh->Initialize();
	*lplpmesh = lpmesh;
	return AddMesh(lpmesh);
}

DWORD CDXEscene::AddMesh(CDXMesh *lpmesh)
{
	if (m_first_mesh !=NULL)
		m_first_mesh->m_prev=lpmesh;
	lpmesh->m_next=m_first_mesh;
	lpmesh->m_prev=NULL;
	m_first_mesh=lpmesh;
	lpmesh->m_lpescene=this;
	return 0;
}

DWORD CDXEscene::DeleteAllMesh()
{
	CDXMesh*	lpmesh;
	while (m_first_mesh != NULL)
	{
		lpmesh = m_first_mesh->m_next;
		delete m_first_mesh;
		m_first_mesh = lpmesh;
	}
	return 0;
}

DWORD CDXEscene::DrawIndexedPrimitive(D3DPRIMITIVETYPE ptype, DWORD vtype, LPVOID lpvertex, DWORD vcant, LPWORD vindex, DWORD icant, DWORD flags)
{
	if (m_lpd3ddevice7 == NULL)
		return 1;
	m_lpd3ddevice7->DrawIndexedPrimitive(ptype,vtype,lpvertex,vcant,vindex,icant,flags);
	return 0;
}

DWORD CDXEscene::AddNewMaterial(CDXMaterial **lplpmaterial)
{
	CDXMaterial* lpmaterial= new CDXMaterial();
	if (lpmaterial == NULL)
		return 1;
	lpmaterial->Initialize();
	*lplpmaterial = lpmaterial;
	return AddMaterial(lpmaterial);
}

DWORD CDXEscene::AddMaterial(CDXMaterial *lpmaterial)
{
	if (m_first_material !=NULL)
		m_first_material->m_prev=lpmaterial;
	lpmaterial->m_next=m_first_material;
	lpmaterial->m_prev=NULL;
	m_first_material=lpmaterial;
	return 0;
}

DWORD CDXEscene::DrawPrimitive(D3DPRIMITIVETYPE ptype, DWORD vtype, LPVOID lpvertices, DWORD cant, DWORD flags)
{
	if (m_lpd3ddevice7 == NULL)
		return 1;
	m_lpd3ddevice7->DrawPrimitive(ptype,vtype,lpvertices,cant,flags);
	return 0;
}

DWORD CDXEscene::SetTransform(D3DTRANSFORMSTATETYPE tstype, D3DMATRIX* matrix)
{
	if (m_lpd3ddevice7 == NULL)
		return 1;
	m_lpd3ddevice7->SetTransform(tstype,matrix);
	return 0;
}

DWORD CDXEscene::ViewPort(DWORD x, DWORD y, DWORD width, DWORD height)
{
	D3DVIEWPORT7 vp = { x, y, width, height, 0.0f, 1.0f };
	if (m_lpd3ddevice7 == NULL)
		return 1;
	m_lpd3ddevice7->SetViewport(&vp);
	return 0;
}
