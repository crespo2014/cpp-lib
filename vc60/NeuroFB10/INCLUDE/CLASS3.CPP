// class3.cpp: implementation of the CGLPrimitiva class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "class3.h"
#include "class2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLPrimitiva::CGLPrimitiva()
{
	Init();
}

CGLPrimitiva::~CGLPrimitiva()
{
	Destroy();
	delete m_Texture;
	delete m_Vertices;
	delete m_Colors;
	delete m_Normales;
}

int CGLPrimitiva::SaveToFile(FILE *pFile)
{
	return true;
}

int CGLPrimitiva::ReadFromFile(FILE *pFile)
{
	CalcDim();
	return true;
}

int CGLPrimitiva::Paint()
{
	if (!m_Vertices)
		return false;

	glDisableClientState(GL_EDGE_FLAG_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	/*
	
	(m_OnColor)		? (glEnableClientState(GL_COLOR_ARRAY))			:(glDisableClientState (GL_COLOR_ARRAY));
	(m_OnNormals)	? (glEnableClientState(GL_NORMAL_ARRAY))		:(glDisableClientState (GL_NORMAL_ARRAY));
	(m_OnTexture)	? (glEnableClientState(GL_TEXTURE_COORD_ARRAY))	:(glDisableClientState (GL_TEXTURE_COORD_ARRAY));

	if (m_OnColor)
	{
		glColorPointer(3,GL_FLOAT,sizeof(S_Color),m_Colors);
	}
	if (m_OneColor)
	{
		glColor4fv(m_Color);
	}
	if (m_OnNormals)
	{
		glNormalPointer(GL_FLOAT,sizeof(S_Normal),m_Normales);
	}
	if (m_OneNormal)
		glNormal3fv(m_Normal);
	if (m_OnTexture)
	{
		glTexCoordPointer(2,GL_FLOAT,sizeof(S_Texture),m_Texture);
	}
	glVertexPointer(3,GL_FLOAT,sizeof(point3ds),m_Vertices);
	*/

	glDrawArrays(m_Disk.m_Type,0,m_Disk.m_CantVert);
	return true;
}

int CGLPrimitiva::SetCantVert(DWORD pCant)
{
	m_Disk.m_CantVert=pCant;
	delete m_Texture;
	delete m_Vertices;
	delete m_Colors;
	delete m_Normales;
	m_Texture=NULL;
	m_Vertices=NULL;
	m_Colors=NULL;
	m_Normales=NULL;
	m_Vertices=new point3ds[m_Disk.m_CantVert];
	return true;
}

DWORD CGLPrimitiva::GetCantVert()
{
	return m_Disk.m_CantVert;
}

int CGLPrimitiva::SetPrimitiva(UINT pType)
{
	m_Type=pType;
	return true;
}

int CGLPrimitiva::SetVertex(point3ds *pVertex)
{
	if (!m_Vertices)
	{
		m_Vertices=new point3ds[m_Disk.m_CantVert];
	}
	memcpy(m_Vertices,pVertex,m_Disk.m_CantVert*sizeof(point3ds));
	CalcDim();
	return true;
}

int CGLPrimitiva::SetNormal(S_Normal *pNormals)
{
	/*
	if (!m_Normales)
	{
		m_Normales=new S_Normal[m_CantVert];
	}
	memcpy(m_Normales,pNormals,m_CantVert*sizeof(S_Normal));
	m_OneNormal=false;
	*/
	return true;
}

void CGLPrimitiva::Init()
{
	/*
	m_OnColor=false;
	m_OneColor=false;
	m_OnTexture=false;
	m_OnNormals=false;
	m_OneNormal=false;
	*/
	m_OnList=false;
	m_Texture=NULL;
	m_Vertices=NULL;
	m_Colors=NULL;
	m_Normales=NULL;
	m_Disk.m_CantVert=0;
	m_List=0;
	m_MaxX=0;
	m_MaxY=0;
	m_MaxZ=0;
	m_MinX=0;
	m_MinY=0;
	m_MinZ=0;
	m_TreeObject.m_This=this;
	m_TreeObject.m_Type=0;
	m_TreeCtrl=NULL;
	m_hTreeItem=NULL;
	m_OnTreeSelect=false;
}

int CGLPrimitiva::Trasladar(float px, float py, float pz)
{
	UINT i;
	if (m_Vertices)
	{
		for (i=0;i<m_Disk.m_CantVert;i++)
		{
			m_Vertices[i].x+=px;
			m_Vertices[i].y+=py;
			m_Vertices[i].z+=pz;
		}
	}
	return true;
}

int CGLPrimitiva::CalcDim()
{
	float px,py,pz;
	float mx,my,mz;
	DWORD i;
	mx=m_Vertices[0].x;
	my=m_Vertices[0].y;
	mz=m_Vertices[0].z;
	px=mx;py=my;pz=mz;

	for (i=0;i<m_Disk.m_CantVert;i++)
	{
		if (m_Vertices[i].x > px)
			px=m_Vertices[i].x;
		if (m_Vertices[i].y > py)
			py=m_Vertices[i].y;
		if (m_Vertices[i].z > pz)
			pz=m_Vertices[i].z;
		if (m_Vertices[i].x < mx)
			mx=m_Vertices[i].x;
		if (m_Vertices[i].y < my)
			my=m_Vertices[i].y;
		if (m_Vertices[i].z < mz)
			mz=m_Vertices[i].z;
	}
	
	m_MaxX=px;
	m_MaxY=py;
	m_MaxZ=pz;
	m_MinX=mx;
	m_MinY=my;
	m_MinZ=mz;
	return true;
}

int CGLPrimitiva::GetMaxPoint(float *pPoint)
{
	pPoint[0]=m_MaxX;
	pPoint[1]=m_MaxY;
	pPoint[2]=m_MaxZ;
	return true;
}

int CGLPrimitiva::GetMinPoint(float *pPoint)
{
	pPoint[0]=m_MinX;
	pPoint[1]=m_MinY;
	pPoint[2]=m_MinZ;
	return true;
}

int CGLPrimitiva::SetParent(C3DObject* pParent)
{
	m_ParentObject=pParent;
 	return true;
}

int CGLPrimitiva::SetTree(CTree3DObject *pTree)
{
	m_TreeCtrl=pTree;
	return true;
}

int CGLPrimitiva::AddToTree()
{
	if (!m_TreeCtrl)
		return false;
	if (!m_hTreeItem)
	{
		TV_INSERTSTRUCT tvi;
		tvi.hParent=m_ParentObject->GetTreeItemHandle();
		tvi.hInsertAfter=TVI_LAST;
		tvi.item.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
		tvi.item.hItem=NULL;
		tvi.item.state=0;
		tvi.item.stateMask=0;
		tvi.item.cchTextMax=10;
		tvi.item.iSelectedImage=TYPE_PRIMITIVA;
		tvi.item.cChildren=0;
		tvi.item.lParam=0;
		tvi.item.pszText="Primitiva";
		tvi.item.iImage=TYPE_PRIMITIVA;
		tvi.item.lParam=(LPARAM)&m_TreeObject;
		m_hTreeItem=m_TreeCtrl->InsertItem(&tvi);
	}
	return true;
}

int CGLPrimitiva::Destroy()
{
	RemoveFromTree();
	return true;
}

int CGLPrimitiva::RemoveFromTree()
{
	if (!m_hTreeItem)
		return false;
	if (!m_TreeCtrl)
		return false;
	m_TreeCtrl->DeleteItem(m_hTreeItem);
	m_hTreeItem=NULL;
	return true;
}

int CGLPrimitiva::SetColor(float pR, float pG, float pB, float pA)
{
	/*
	delete m_Colors;
	m_Colors=NULL;
	m_OnColor=false;
	m_OneColor=true;
	m_Color[0]=pR;
	m_Color[1]=pG;
	m_Color[2]=pB;
	m_Color[3]=pA;
	*/
	return true;
}

int CGLPrimitiva::SetNormal(float px, float py, float pz)
{
	/*
	delete m_Normales;
	m_Normales=NULL;
	m_OnNormals=false;
	m_OneNormal=true;
	m_Normal[0]=px;
	m_Normal[1]=py;
	m_Normal[2]=pz;
	*/
	return true;
}

int CGLPrimitiva::SetSelect(BOOL pState)
{
	m_OnTreeSelect=pState;
	return true;
}

BOOL CGLPrimitiva::IsSelected()
{
	return m_OnTreeSelect;
}
