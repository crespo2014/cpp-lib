// g_01c08.cpp: implementation of the C3DMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "g_01c08.h"
#include "g_01c07.h"
#include "g_01c09.h"

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DMesh::C3DMesh()
{
	m_lpdata=&m_data;
	m_faces=NULL;
	m_onstatic=false;
	m_vertex=NULL;
	m_materials=NULL;
}

C3DMesh::~C3DMesh()
{
	Destroy();
}

/*
	Usado para leer Meshes de un recurso
*/
DWORD C3DMesh::ReadFromMemory(void *lpPointer)
{
	BYTE*	m_lppos;
	DWORD	i;
	m_onstatic=true;
	m_lpdata = (S_3DMESH*)lpPointer;
	m_lppos = (BYTE*)m_lpdata+sizeof(S_3DMESH);
	if (m_lpdata ->m_version != sizeof (m_data))
		return 1;
	// Leer toda la informacion de la malla

	// Leer todos los vertices
	m_vertex = (S_3DSPOINT*)m_lppos;
	m_lppos+= sizeof(S_3DSPOINT)*m_lpdata->m_nvertex;

	// Leer todas las caras
	m_faces = (S_3DSFACE*)m_lppos;
	m_lppos+= sizeof(S_3DSFACE)*m_lpdata->m_nfaces;

	// Reservar espacio para los materiales
	m_materials=new S_3DMESHMAT[m_lpdata->m_nmat];
	S_3DMESHMATDAT*	m_mat_dat;

	// Leer todos los materiales
	for (i=0;i<m_lpdata->m_nmat;i++)
	{
		m_mat_dat = (S_3DMESHMATDAT*)m_lppos;		
		m_lppos+=sizeof(S_3DMESHMATDAT);
		m_materials[i].m_data=*m_mat_dat;
		m_materials[i].m_faces=(DWORD*)m_lppos;
		if (m_3descene)
			m_materials[i].m_material=m_3descene->GetMaterial(m_materials[i].m_data.m_mat_index);
		else
			m_materials[i].m_material=NULL;
		m_lppos+=sizeof(DWORD)*m_mat_dat->m_faces_cant;
	}
	CalcSize();
	return 0;
}

DWORD C3DMesh::Set3DEscene(C3DEscene *p3descene)
{
	m_3descene=p3descene;
	return 0;
}

DWORD C3DMesh::Paint()
{
	/*
	glBegin(GL_TRIANGLES);
		glVertex3d(0,0,0);
		glVertex3d(20,20,0);
		glVertex3d(0,0,-283);
	glEnd();
	*/
	DWORD	mats,faces;
	DWORD	face;
	float	max;
	float	pto1[3];
	float	pto2[3];
	float	pto3[3];
	float	vector1[3];
	float	vector2[3];
	float	normal[3];
	
	glBegin(GL_TRIANGLES);
	for (mats=0;mats<m_lpdata->m_nmat;mats++)
	{
		if (m_materials[mats].m_material)
			m_materials[mats].m_material->MakeCurrent();
		for (faces=0;faces<m_materials[mats].m_data.m_faces_cant;faces++)
		{
			face=m_materials[mats].m_faces[faces];
			memcpy(pto1,&m_vertex[m_faces[face].v1],sizeof(S_3DSPOINT));
			memcpy(pto2,&m_vertex[m_faces[face].v2],sizeof(S_3DSPOINT));
			memcpy(pto3,&m_vertex[m_faces[face].v3],sizeof(S_3DSPOINT));
			
			
			vector1[0]=pto2[0]-pto1[0];vector1[1]=pto2[1]-pto1[1];vector1[2]=pto2[2]-pto1[2];
			vector2[0]=pto3[0]-pto1[0];vector2[1]=pto3[1]-pto1[1];vector2[2]=pto3[2]-pto1[2];
			normal[0]=vector2[1]*vector1[2]-vector2[2]*vector1[1];
			normal[1]=vector2[2]*vector1[0]-vector2[0]*vector1[2];
			normal[2]=vector2[0]*vector1[1]-vector2[1]*vector1[0];
			max=(float)sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
			
			normal[0]/=-max;
			normal[1]/=-max;
			normal[2]/=-max;
			
			glNormal3fv(normal);
			glVertex3fv(pto1);
			glVertex3fv(pto2);
			glVertex3fv(pto3);
		}
	}
	glEnd();

	return 0;
}

DWORD C3DMesh::Destroy()
{
	delete m_materials;
	return 0;
}

DWORD C3DMesh::GetSize(S_3DSIZE *p3dsize)
{
	*p3dsize=m_size;
	return 0;
}

DWORD C3DMesh::CalcSize()
{
	DWORD i;
	if (!m_lpdata->m_nvertex)
		return 0;
	m_size.x1=m_size.x2=m_vertex[0].x;
	m_size.y1=m_size.y2=m_vertex[0].y;
	m_size.z1=m_size.z2=m_vertex[0].z;
	for (i=0;i<m_lpdata->m_nvertex;i++)
	{
		if (m_vertex[i].x < m_size.x1)
			m_size.x1=m_vertex[i].x;
		if (m_vertex[i].x > m_size.x2)
			m_size.x2=m_vertex[i].x;
		if (m_vertex[i].y < m_size.y1)
			m_size.y1=m_vertex[i].y;
		if (m_vertex[i].y > m_size.y2)
			m_size.y2=m_vertex[i].y;
		if (m_vertex[i].z < m_size.z1)
			m_size.z1=m_vertex[i].z;
		if (m_vertex[i].z > m_size.z2)
			m_size.z2=m_vertex[i].z;

	}
	return 0;
}

DWORD C3DMesh::SetD3DDevice(LPDIRECT3DDEVICE7 lpd3ddevice)
{
	m_lpd3ddevice=lpd3ddevice;
	return 0;
}
