// gl10c3.cpp: implementation of the CMeshMat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c3.h"
#include "gl10c5.h"
#include "gl10c6.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeshMat::CMeshMat()
{
	InitMeshMat();	
}

CMeshMat::~CMeshMat()
{
	delete m_MeshMat->facearray;
	delete m_MeshMat->vertexarray;
	WORD mats;
	for (mats=0;mats<m_MeshMat->info.m_nmat;mats++)
	{
		delete m_MeshMat->matarray[mats].facesindex;
	}
	delete m_MeshMat->matarray;
	delete m_MeshMat;
}

int CMeshMat::Paint()
{
	DWORD	mats,faces;
	DWORD	face;
	float	max;
	float	pto1[3];
	float	pto2[3];
	float	pto3[3];
	float	vector1[3];
	float	vector2[3];
	float	normal[3];

	if (!m_MeshMat->view)
		return false;
	if (m_MeshMat->view->IsWireFrame())
	{
		glBegin(GL_LINE_LOOP);
		for (int i=0;i<m_MeshMat->info.m_nvertex;i++)
		{
			glVertex3fv((float*)&m_MeshMat->vertexarray[i]);
		}
		glEnd();
	}
	else
	{
		
		glBegin(GL_TRIANGLES);
		for (mats=0;mats<m_MeshMat->info.m_nmat;mats++)
		{
			m_MeshMat->matarray[mats].pMaterial->MakeCurrent();
			for (faces=0;faces<m_MeshMat->matarray[mats].info.nfaces;faces++)
			{
				face=m_MeshMat->matarray[mats].facesindex[faces];
				memcpy(pto1,&m_MeshMat->vertexarray[m_MeshMat->facearray[face].v1],3*sizeof(float));
				memcpy(pto2,&m_MeshMat->vertexarray[m_MeshMat->facearray[face].v2],3*sizeof(float));
				memcpy(pto3,&m_MeshMat->vertexarray[m_MeshMat->facearray[face].v3],3*sizeof(float));
				
				
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
	}
	return true;
}

CMeshMat::CMeshMat(WORD pnvertex, WORD pnfaces)
{
	InitMeshMat();
	SetCantVertex(pnvertex);
	SetCantFaces(pnfaces);
}

int CMeshMat::SetCantVertex(WORD pCant)
{
	if (m_MeshMat->info.m_nvertex==pCant)
		return true;
	delete m_MeshMat->vertexarray;
	m_MeshMat->vertexarray=new S_3DSPOINT[pCant];
	m_MeshMat->info.m_nvertex=pCant;
	return true;	
}

int CMeshMat::SetCantFaces(WORD pCant)
{
	if (m_MeshMat->info.m_nfaces==pCant)
		return true;
	delete m_MeshMat->facearray;
	m_MeshMat->facearray=new S_3DSFACE[pCant];
	m_MeshMat->info.m_nfaces=pCant;
	return true;
}

int CMeshMat::SetVertex(DWORD pPos, S_3DSPOINT pPoint)
{
	if (pPos >= m_MeshMat->info.m_nvertex)
		return false;
	m_MeshMat->vertexarray[pPos]=pPoint;
	return true;
}

int CMeshMat::SetFace(DWORD pPos, S_3DSFACE pFace)
{
	if (pPos >= m_MeshMat->info.m_nfaces)
		return false;
	m_MeshMat->facearray[pPos]=pFace;
	return true;
}

int CMeshMat::SetEscena(CEscena *pEscena)
{
	m_MeshMat->view=pEscena;
	return true;
}

int CMeshMat::SetTreeHandle(HTREEITEM pHandle)
{
	m_MeshMat->htree=pHandle;
	return true;
}


char* CMeshMat::GetName()
{
	return m_MeshMat->info.m_name;
}

LPARAM CMeshMat::GetTreeLParam()
{
	return (DWORD)&m_MeshMat->treelparam;
}

DWORD CMeshMat::GetIndex()
{
	return m_MeshMat->info.m_index;
}

POSITION CMeshMat::GetPos()
{
	return m_MeshMat->pos;
}

int CMeshMat::SetName(char *name)
{
	memcpy(m_MeshMat->info.m_name,name,20);
	return true;
}

int CMeshMat::InitMeshMat()
{
	m_MeshMat=new S_MESHMAT;
	m_MeshMat->facearray=NULL;
	m_MeshMat->vertexarray=NULL;
	m_MeshMat->matarray=NULL;
	m_MeshMat->info.m_version=sizeof(S_3DMESH);
	m_MeshMat->info.m_size=sizeof(S_3DMESH);
	m_MeshMat->info.m_index=0;
	m_MeshMat->info.m_name[20]=0;
	m_MeshMat->info.m_nfaces=0;
	m_MeshMat->info.m_nvertex=0;
	m_MeshMat->info.m_nmat=0;
	m_MeshMat->treelparam.type=ID_MESH;
	m_MeshMat->treelparam.object=this;
	return true;	
}

int CMeshMat::SetIndex(DWORD pIndex)
{
	m_MeshMat->info.m_index=pIndex;
	return true;
}

int CMeshMat::SaveToFile(FILE *pFile)
{
	DWORD i;
	UpdateIndex();
	// Calcular tamano que ocupa toda la informacion de la malla
	m_MeshMat->info.m_size = sizeof(S_3DMESH)+sizeof(S_3DSPOINT)*m_MeshMat->info.m_nvertex+
		sizeof(S_3DSFACE)*m_MeshMat->info.m_nfaces+sizeof(S_MATDATINFO)*m_MeshMat->info.m_nmat;
	for (i=0;i<m_MeshMat->info.m_nmat;i++)
	{
		m_MeshMat->info.m_size+=sizeof(DWORD)*m_MeshMat->matarray[i].info.nfaces;
	}

	fwrite(&m_MeshMat->info,sizeof(S_3DMESH),1,pFile);
	fwrite(m_MeshMat->vertexarray,sizeof(S_3DSPOINT),m_MeshMat->info.m_nvertex,pFile);
	fwrite(m_MeshMat->facearray,sizeof(S_3DSFACE),m_MeshMat->info.m_nfaces,pFile);
	
	for (i=0;i<m_MeshMat->info.m_nmat;i++)
	{
		fwrite(&m_MeshMat->matarray[i].info,sizeof(S_MATDATINFO),1,pFile);
		fwrite(m_MeshMat->matarray[i].facesindex,sizeof(DWORD),m_MeshMat->matarray[i].info.nfaces,pFile);	
	}
	return true;
}

int CMeshMat::ReadMesh3DS(mesh3ds *pmesh)
{
	DWORD i;
	S_3DSPOINT	pPoint;
	S_3DSFACE	pFace;
	memcpy(m_MeshMat->info.m_name,pmesh->name,11);
	SetCantVertex(pmesh->nvertices);
	SetCantFaces(pmesh->nfaces);
	for (i=0;i<pmesh->nvertices;i++)
	{
		pPoint.x=pmesh->vertexarray[i].x;
		pPoint.y=pmesh->vertexarray[i].y;
		pPoint.z=pmesh->vertexarray[i].z;
		SetVertex(i,pPoint);
	}
	for (i=0;i<pmesh->nfaces;i++)
	{
		pFace.v1=pmesh->facearray[i].v1;
		pFace.v2=pmesh->facearray[i].v2;
		pFace.v3=pmesh->facearray[i].v3;
		SetFace(i,pFace);
	}
	// Tomar los materiales
	DWORD	mats;
	char	name[21];
	m_MeshMat->info.m_nmat=pmesh->nmats;
	m_MeshMat->matarray= new S_MATDAT[pmesh->nmats];
	for (mats=0;mats<pmesh->nmats;mats++)
	{
		memcpy(name,pmesh->matarray[mats].name,17);
		m_MeshMat->matarray[mats].info.nfaces=pmesh->matarray[mats].nfaces;
		m_MeshMat->matarray[mats].facesindex=new DWORD[pmesh->matarray[mats].nfaces];
		m_MeshMat->matarray[mats].pMaterial=m_MeshMat->view->GetMaterial(name);
		for (i=0;i<pmesh->matarray[mats].nfaces;i++)
			m_MeshMat->matarray[mats].facesindex[i]=pmesh->matarray[mats].faceindex[i];

	}
	return true;
}

int CMeshMat::UpdateIndex()
{
	int i;
	for (i=0;i<m_MeshMat->info.m_nmat;i++)
	{
		m_MeshMat->matarray[i].info.index=m_MeshMat->matarray[i].pMaterial->GetIndex();
	}
	return true;
}

int CMeshMat::ReadFromFile(FILE *pFile)
{
	DWORD i;
	fread(&m_MeshMat->info,sizeof(S_3DMESH),1,pFile);
	if (m_MeshMat->info.m_version != sizeof(S_3DMESH))
		return false;

	// Lectura de toda la composicion de la malla

	// Lectura de los vertices
	m_MeshMat->vertexarray=new S_3DSPOINT[m_MeshMat->info.m_nvertex];
	fread(m_MeshMat->vertexarray,sizeof(S_3DSPOINT),m_MeshMat->info.m_nvertex,pFile);
	// Lectura de las caras
	m_MeshMat->facearray= new S_3DSFACE[m_MeshMat->info.m_nfaces];
	fread(m_MeshMat->facearray,sizeof(S_3DSFACE),m_MeshMat->info.m_nfaces,pFile);
	// Lectura de los materiales
	m_MeshMat->matarray= new S_MATDAT[m_MeshMat->info.m_nmat];
	for (i=0;i<m_MeshMat->info.m_nmat;i++)
	{
		fread(&m_MeshMat->matarray[i].info,sizeof(S_MATDATINFO),1,pFile);
		m_MeshMat->matarray[i].facesindex = new DWORD[m_MeshMat->matarray[i].info.nfaces];
		fread(m_MeshMat->matarray[i].facesindex,sizeof(DWORD),m_MeshMat->matarray[i].info.nfaces,pFile);	
		m_MeshMat->matarray[i].pMaterial=m_MeshMat->view->GetMaterial(m_MeshMat->matarray[i].info.index);
	}
	return true;
}
