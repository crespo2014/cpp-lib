// g30c06.h: interface for the CDXEscene class.
//
//////////////////////////////////////////////////////////////////////

/*
	Esta clase encapsula los metodos necesarios para trabajar con el
	DirectDraw 
*/

#if !defined(AFX_G30C06_H__78E99100_16F1_11D5_8D01_00D0093D4380__INCLUDED_)
#define AFX_G30C06_H__78E99100_16F1_11D5_8D01_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "g30def.h"
#include "g30c04.h"		// CDXMesh

class CDXEscene  
{
public:
	DWORD ViewPort(DWORD x,DWORD y, DWORD width,DWORD height);
	DWORD SetTransform(D3DTRANSFORMSTATETYPE tstype, D3DMATRIX* matrix);
	DWORD DrawPrimitive(D3DPRIMITIVETYPE ptype,DWORD  vtype,LPVOID lpvertices,DWORD  cant,DWORD  flags);
	DWORD AddMaterial(CDXMaterial *lpmaterial);
	DWORD AddNewMaterial(CDXMaterial** lplpmaterial);
	DWORD DrawIndexedPrimitive(D3DPRIMITIVETYPE ptype,DWORD vtype,LPVOID lpvertex,DWORD vcant,LPWORD vindex,DWORD icant,DWORD flags);
	DWORD DeleteAllMesh();
	DWORD AddMesh(CDXMesh* lpmesh);
	DWORD AddNewMesh(CDXMesh** lplpmesh);
	DWORD DeleteMesh(CDXMesh* lpmesh);
	DWORD Translate(float x,float y,float z);
	DWORD RotateZ(float ang);
	DWORD RotateY(float ang);
	DWORD RotateX(float ang);
	DWORD Perspective(float fovy,float aspect,float znear,float zfar);
	DWORD Frustum(float left,float right,float bottom,float top,float znear,float zfar);
	DWORD LoadIdentity(D3DTRANSFORMSTATETYPE ptst);
	DWORD DestroyDirectX();
	DWORD FlipSurfaces();
	DWORD GetD3DDevice(LPDIRECT3DDEVICE7 *plpd3ddevice);
	DWORD DestroyDDraw();
	DWORD DestroyD3D();
	DWORD RestoreAll();
	DWORD CreateZBuffer(REFCLSID m_d3dclsid);
	DWORD CreateD3D(REFCLSID pd3dclsid);
	static HRESULT CALLBACK D3DEnumZBufferCallback(  LPDDPIXELFORMAT lpDDPixFmt,LPVOID lpContext);
	DWORD CreateDirectX();
	DWORD CreateDirectDraw();
	DWORD SetWind(HWND phwnd);
	DWORD Release();
	DWORD Initialize();
	CDXEscene();
	virtual ~CDXEscene();

private:
	LPDIRECTDRAW7			m_lpddraw7;
	LPDIRECTDRAWSURFACE7	m_lpddfrontsurface7;
	LPDIRECTDRAWSURFACE7	m_lpddbacksurface7;
	LPDIRECTDRAWSURFACE7	m_lpddzbuffer;
	LPDIRECT3D7				m_lpd3d7;
	LPDIRECT3DDEVICE7		m_lpd3ddevice7;
	BOOL	m_on_init;
	HWND	m_hwnd;
	BOOL	m_on_fullscreen;
	DWORD	m_cooperativeflags;
	DWORD	m_width,m_height,m_bpp,m_refresh_rate;
	BOOL	m_on_zbuffer;
	CDXMesh*	m_first_mesh;
	CDXMaterial* m_first_material;
};

#endif // !defined(AFX_G30C06_H__78E99100_16F1_11D5_8D01_00D0093D4380__INCLUDED_)
