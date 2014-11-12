// g30c04.cpp: implementation of the CDXMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "g30c04.h"
#include "g30c06.h"		//CDXEscene

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXMesh::CDXMesh()
{
	Initialize();
}

CDXMesh::~CDXMesh()
{
	Release();
}

DWORD CDXMesh::SetEscene(CDXEscene *lpdxescene)
{
	m_lpescene=lpdxescene;
	return 0;	
}

DWORD CDXMesh::Release()
{
	if (!m_on_init)
		return 1;
	m_info.m_material_cant=0;
	m_info.m_vertex_cant=0;
	m_info.m_faces_cant=0;
	m_lpescene=NULL;
	m_lpmaterial=NULL;
	delete m_lpmaterials;
	m_lpmaterials=NULL;
	delete m_lpvertex;
	m_lpvertex=NULL;
	delete m_lpfaces;
	m_lpfaces=NULL;
	m_memory_size=0;
	m_next=NULL;
	m_prev=NULL;
	return 0;
}

DWORD CDXMesh::Read(C3DMesh *lp3dmesh)
{
	DWORD i,j;
	DWORD faceindex=0;
	D3DVECTOR *lpvertex;

	Release();
	m_info.m_vertex_cant=lp3dmesh->m_lpdata->m_nvertex;
	m_lpvertex = new D3DVECTOR[m_info.m_vertex_cant];
	if (!m_lpvertex)
		goto failed;
	lpvertex=(D3DVECTOR*)m_lpvertex;
	for (i=0;i<m_info.m_vertex_cant;i++)
	{
		
		lpvertex[i].x=lp3dmesh->m_vertex[i].x;
		lpvertex[i].y=lp3dmesh->m_vertex[i].y;
		lpvertex[i].z=lp3dmesh->m_vertex[i].z;
	}
	m_info.m_material_cant=lp3dmesh->m_lpdata->m_nmat;
	m_info.m_faces_cant=lp3dmesh->m_lpdata->m_nfaces;
	m_lpmaterials = new S_MATS[m_info.m_material_cant];
	m_lpfaces=		new S_DXFACE[m_info.m_faces_cant];
	if ((m_lpmaterials != NULL )|| (m_lpfaces !=NULL))
		goto failed;

	// Recorrer todos los materiales
	
	for (i=0;i<m_info.m_material_cant;i++)
	{
		m_lpmaterials[i].first_face=faceindex;
		m_lpmaterials[i].face_cant=lp3dmesh->m_materials[i].m_data.m_faces_cant;
		for (j=0;j<lp3dmesh->m_materials[i].m_data.m_faces_cant;j++)
		{
			m_lpfaces[faceindex].v1=lp3dmesh->m_faces[lp3dmesh->m_materials[i].m_faces[j]].v1;			
			m_lpfaces[faceindex].v2=lp3dmesh->m_faces[lp3dmesh->m_materials[i].m_faces[j]].v2;			
			m_lpfaces[faceindex].v3=lp3dmesh->m_faces[lp3dmesh->m_materials[i].m_faces[j]].v3;			
			faceindex++;
		}
	}
	return 0;
failed:
	Release();
	return 0;
}

DWORD CDXMesh::Initialize()
{
	m_on_init=true;
	m_info.m_material_cant=0;
	m_info.m_vertex_cant=0;
	m_info.m_vertex_type=0;
	m_info.m_faces_cant=0;
	m_lpescene=NULL;
	m_lpmaterials=NULL;
	m_lpmaterial=NULL;
	m_lpfaces=NULL;
	m_lpvertex=NULL;
	m_memory_size=0;
	m_next=NULL;
	m_prev=NULL;
	m_ptype=D3DPT_TRIANGLELIST;
	return 0;
}

DWORD CDXMesh::SetVertex(DWORD cant, DWORD vtype, LPVOID lpvertex)
{
	DWORD	vertexsize=0;
	if (vtype & D3DFVF_DIFFUSE)
		vertexsize+=sizeof(DWORD);
	if (vtype & D3DFVF_NORMAL)
		vertexsize+=3*sizeof(float);
	if (vtype & D3DFVF_SPECULAR)
		vertexsize+=sizeof(DWORD);
	if (vtype & D3DFVF_XYZ)
		vertexsize+=3*sizeof(float);
	if (vtype & D3DFVF_RESERVED1)
		vertexsize+=sizeof(DWORD);
	if (vtype & D3DFVF_XYZRHW)
		vertexsize+=4*sizeof(float);
	BYTE*	lpvertex01;
	lpvertex01 = new BYTE [vertexsize*cant];
	if (lpvertex01 == NULL)
		return 1;
	// Borra la configuracion antigua
	DeleteAll();
	m_lpvertex=lpvertex01;
	m_info.m_vertex_cant=cant;
	m_info.m_vertex_type=vtype;
	memcpy(m_lpvertex,lpvertex,vertexsize*cant);
	return 0;
}

DWORD CDXMesh::Paint()
{
	if (m_lpescene == NULL)
		return 0;
	if (m_lpvertex == NULL)
		return 0;
	if (m_info.m_faces_cant == 0)
	{
		// Dibujar todos los vertices
		m_lpescene->DrawPrimitive(m_ptype,m_info.m_vertex_type,m_lpvertex,m_info.m_vertex_cant,0);
		return 0;
	}
	if (m_info.m_material_cant == 1)
	{
		//m_lpmaterial->MakeCurrent();
	}

	return 0;
}

DWORD CDXMesh::SetPrimitiveType(D3DPRIMITIVETYPE ptype)
{
	m_ptype=ptype;
	return 0;
}


DWORD CDXMesh::DeleteAll()
{
	m_info.m_material_cant=0;
	m_info.m_vertex_cant=0;
	m_info.m_faces_cant=0;
	delete m_lpmaterials;
	delete m_lpvertex;
	delete m_lpfaces;
	m_lpmaterials=NULL;
	m_lpvertex=NULL;
	m_lpfaces=NULL;
	m_memory_size=0;
	return 0;
}
