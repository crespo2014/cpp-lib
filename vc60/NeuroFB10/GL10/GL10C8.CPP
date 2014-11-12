 // gl10c8.cpp: implementation of the CMeshInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c8.h"
#include "gl10c4.h"
#include "gl10c5.h"
#include "gl10c3.h"
#include "gl10c7.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeshInstance::CMeshInstance()
{
	InitMeshInstance();
}

CMeshInstance::~CMeshInstance()
{
	delete m_MeshInstance;
}

int CMeshInstance::UpDateMeshByIndex()
{
	m_MeshInstance->parent->GetEscena()->GetMesh(m_MeshInstance->info.index);
	return true;
}

int CMeshInstance::SetMesh(CMeshMat *pmesh)
{
	m_MeshInstance->info.index=pmesh->GetIndex();
	m_MeshInstance->mesh=pmesh;
	return true;
}

int CMeshInstance::InitMeshInstance()
{
	m_MeshInstance=new S_MESHINSTANCE;
	m_MeshInstance->htree=NULL;
	m_MeshInstance->info.index=0;
	m_MeshInstance->info.version=sizeof(S_MESHINSTANCEINFO);
	m_MeshInstance->parent=NULL;
	m_MeshInstance->pos=NULL;
	m_MeshInstance->treelparam.object=this;
	m_MeshInstance->treelparam.type=ID_MESHINSTANCE;
	m_MeshInstance->tree=NULL;
	m_MeshInstance->mesh=NULL;
	return true;
}

int CMeshInstance::SetParent(CMeshGroup *parent)
{
	m_MeshInstance->parent=parent;
	return true;
}

CMeshMat* CMeshInstance::GetMesh()
{
	return m_MeshInstance->mesh;
}

int CMeshInstance::Delete()
{
	m_MeshInstance->parent->DeleteMeshInstance(m_MeshInstance->pos);
	return true;
}

int CMeshInstance::DetachFromTree()
{
	if (m_MeshInstance->htree)
	{
		m_MeshInstance->tree->DeleteItem(m_MeshInstance->htree);
	}
	return true;
}

int CMeshInstance::SetPos(POSITION pos)
{
	m_MeshInstance->pos=pos;
	return true;
}

int CMeshInstance::SaveToFile(FILE *pFile)
{
	UpdateIndex();
	fwrite(&m_MeshInstance->info,sizeof(S_MESHINSTANCEINFO),1,pFile);
	return true;
}

int CMeshInstance::UpdateIndex()
{
	m_MeshInstance->info.index=m_MeshInstance->mesh->GetIndex();
	return true;
}

int CMeshInstance::ReadFromFile(FILE *pFile)
{
	fread(&m_MeshInstance->info,sizeof(S_MESHINSTANCEINFO),1,pFile);
	if (m_MeshInstance->info.version != sizeof(S_MESHINSTANCEINFO))
		return false;
	m_MeshInstance->mesh=m_MeshInstance->parent->GetEscena()->GetMesh(m_MeshInstance->info.index);
	return true;
}

int CMeshInstance::SetTree(CEscenaTree *pTree)
{
	m_MeshInstance->tree=pTree;
	return true;
}

int CMeshInstance::AttachToTree()
{
	if (!m_MeshInstance->tree)
		return false;
	TV_INSERTSTRUCT tvi;
	tvi.hParent=m_MeshInstance->parent->GetTreeHandle();
	tvi.hInsertAfter=TVI_FIRST;
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=10;
	tvi.itemex.iSelectedImage=MESH_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=m_MeshInstance->mesh->GetName();
	tvi.itemex.iImage=MESH_ICON;
	tvi.itemex.lParam=(DWORD)&m_MeshInstance->treelparam;
	m_MeshInstance->htree=m_MeshInstance->tree->InsertItem(&tvi);
	return true;
}
