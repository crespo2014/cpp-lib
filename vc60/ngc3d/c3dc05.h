// c3dc05.h: interface for the CDXMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_C3DC05_H__FE0EBFE0_0201_11D5_8D3A_00D0093D4380__INCLUDED_)
#define AFX_C3DC05_H__FE0EBFE0_0201_11D5_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "c3ddef.h"

class CDXEscene;
class CDXMaterial;

typedef struct
{
	DWORD	matcant;
	DWORD	facescant;
	DWORD	vertexcant;
	DWORD	id;
	char	name[30];
	D3DVERTEXTYPE	vertextype;
} S_DXMESH;

typedef struct
{
	DWORD	id;
	DWORD	facescant;
}S_DXMATDAT;

typedef struct
{
	S_DXMATDAT		data;
	CDXMaterial*	lpdxmat;
	DWORD*			lpfaces;
}S_DXMATS;


class CDXMesh  
{
public:
	DWORD ReadFromStaticMemory(void* lpvoid);
	DWORD Paint();
	DWORD Release();
	DWORD Initialize();
	CDXEscene* GetEscene();
	DWORD SetEscene(CDXEscene* lpdxescene);
	CDXEscene*	m_lpdxescene;
	S_DXMESH	m_data,*m_lpdata;
	void*		m_lpvertex;
	S_DXFACE*	m_lpface;
	S_DXMATS*	m_lpmat;
	CDXMesh();
	virtual ~CDXMesh();

};

#endif // !defined(AFX_C3DC05_H__FE0EBFE0_0201_11D5_8D3A_00D0093D4380__INCLUDED_)
