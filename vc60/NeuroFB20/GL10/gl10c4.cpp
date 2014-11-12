 // gl10c4.cpp: implementation of the CMeshGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c4.h"
#include "gl10c3.h"
#include "gl10c5.h"
#include "gl10c7.h"
#include "gl10c8.h"
#include "gl10c9.h"
#include "gl10c10.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeshGroup::CMeshGroup()
{
	InitMeshGroup();
}

CMeshGroup::~CMeshGroup()
{
	DeleteAllMeshGroup();
	DeleteAllMesh();
	DeleteAllVariables();
	delete m_MeshGroup;
}

int CMeshGroup::Paint()
{
	GLdouble pMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,pMatrix);

	POSITION	pPos;
	/*
	S_3DSPOINT	position=m_MeshGroup->info.position;
	S_3DSPOINT	rotation=m_MeshGroup->info.rotation;

	glTranslated(position.x,position.y,position.z);
	glRotatef(rotation.x,1,0,0);
	glRotatef(rotation.y,0,1,0);
	glRotatef(rotation.z,0,0,1);
	*/

	{	// revisar variables
		if (!m_MeshGroup->VarList.IsEmpty())
		{
			CVariableInstance*	pvar;
			pPos=m_MeshGroup->VarList.GetHeadPosition();
			do
			{
				pvar=(CVariableInstance*)m_MeshGroup->VarList.GetAt(pPos);
				pvar->ApplyModifier();
				m_MeshGroup->VarList.GetNext(pPos);
			} while (pPos !=NULL);
		}
			
	}

	//Painting all Mesh
	if (!m_MeshGroup->MeshList.IsEmpty()) 
	{
		CMeshInstance*	pMeshMat;
		pPos=m_MeshGroup->MeshList.GetHeadPosition();
		do
		{
			pMeshMat=(CMeshInstance*)m_MeshGroup->MeshList.GetAt(pPos);
			pMeshMat->GetMesh()->Paint();
			m_MeshGroup->MeshList.GetNext(pPos);
		} while (pPos != NULL);
	}
	// Painting All Mesgroup
	if (!m_MeshGroup->grouplist.IsEmpty())
	{
		CMeshGroup* pMG;
		pPos=m_MeshGroup->grouplist.GetHeadPosition();
		do
		{
			pMG=(CMeshGroup*)m_MeshGroup->grouplist.GetAt(pPos);
			pMG->Paint();
			m_MeshGroup->grouplist.GetNext(pPos);
		} while (pPos != NULL);
	}

	glLoadMatrixd(pMatrix);
	return true;
}

int CMeshGroup::SetParent(CMeshGroup *pMeshGroup)
{
	m_MeshGroup->parent=pMeshGroup;
	return true;
}

int CMeshGroup::SetPos(POSITION pPos)
{
	m_MeshGroup->pos=pPos;
	return true;
}

int CMeshGroup::AddMesh(CMeshMat *pMesh)
{
	CMeshInstance* pMeshInstance=new CMeshInstance();
	pMeshInstance->SetMesh(pMesh);
	AddMeshInstance(pMeshInstance);
	pMeshInstance->SetTree(m_MeshGroup->tree);
	// Esto se origina debido a un drag an drog
	pMeshInstance->AttachToTree();					
	return true;
}

LPARAM CMeshGroup::GetTreeLParam()
{
	return (DWORD)&m_MeshGroup->treelparam;
}

int CMeshGroup::SetEscena(CEscena *pEscena)
{
	m_MeshGroup->escena=pEscena;
	return true;
}

CEscena* CMeshGroup::GetEscena()
{
	return m_MeshGroup->escena;
}

HTREEITEM CMeshGroup::GetTreeHandle()
{
	return m_MeshGroup->htree;
}

int CMeshGroup::AddVariable(CVariable *pvariable)
{
	CVariableInstance* pnew= new CVariableInstance(pvariable);
	pnew->Propiedades();
	AddVariableInstance(pnew);
	pnew->SetTree(m_MeshGroup->tree);
	pnew->AttachToTree();
	return true;
}

int CMeshGroup::InitMeshGroup()
{
	char	name[]="MeshGroup";
	m_MeshGroup=new S_MESHGROUP;
	memcpy(m_MeshGroup->info.name,name,sizeof(name));
	m_MeshGroup->pos=NULL;
	m_MeshGroup->info.nmesh=0;
	m_MeshGroup->info.nvar=0;
	m_MeshGroup->info.nmeshgroup=0;
	m_MeshGroup->info.version=sizeof(S_MESHGROUPINFO);
	/*
	m_MeshGroup->info.position.x=0;
	m_MeshGroup->info.position.y=0;
	m_MeshGroup->info.position.z=0;
	m_MeshGroup->info.rotation.x=0;
	m_MeshGroup->info.rotation.y=0;
	m_MeshGroup->info.rotation.z=0;
	*/
	m_MeshGroup->tree=NULL;
	m_MeshGroup->parent=NULL;
	m_MeshGroup->escena=NULL;
	m_MeshGroup->htree=NULL;
	m_MeshGroup->treelparam.object=this;
	m_MeshGroup->treelparam.type=ID_MESHGROUP;
	return true;
}

int CMeshGroup::AddMeshGroup(CMeshGroup* pmeshgroup)
{
	if (!pmeshgroup)
	{
		CMeshGroup*	pnew=new CMeshGroup();
		AddMeshGroup(pnew);
		pnew->AttachToTree();
	} else
	{
		pmeshgroup->SetParent(this);
		pmeshgroup->SetEscena(m_MeshGroup->escena);
		pmeshgroup->SetPos(m_MeshGroup->grouplist.AddTail(pmeshgroup));
		pmeshgroup->SetTree(m_MeshGroup->tree);
		m_MeshGroup->info.nmeshgroup++;
	}
	return true;
}

int CMeshGroup::DeleteAllMeshGroup()
{
	POSITION	pos;
	if (!m_MeshGroup->grouplist.IsEmpty()) 
	{
		pos=m_MeshGroup->grouplist.GetHeadPosition();
		do
		{
			delete m_MeshGroup->grouplist.GetAt(pos);
			m_MeshGroup->grouplist.GetNext(pos);
		} while (pos != NULL);
		m_MeshGroup->grouplist.RemoveAll();
	}
	return true;
}

int CMeshGroup::DeleteAllMesh()
{
	POSITION	pos;
	if (!m_MeshGroup->MeshList.IsEmpty()) 
	{
		pos=m_MeshGroup->MeshList.GetHeadPosition();
		do
		{
			delete m_MeshGroup->MeshList.GetAt(pos);
			m_MeshGroup->MeshList.GetNext(pos);
		} while (pos != NULL);
		m_MeshGroup->MeshList.RemoveAll();
	}
	return true;
}

int CMeshGroup::DeleteAllVariables()
{
	POSITION	pos;
	if (!m_MeshGroup->VarList.IsEmpty()) 
	{
		pos=m_MeshGroup->VarList.GetHeadPosition();
		do
		{
			delete m_MeshGroup->VarList.GetAt(pos);
			m_MeshGroup->VarList.GetNext(pos);
		} while (pos != NULL);
		m_MeshGroup->VarList.RemoveAll();
	}
	return true;
}

CMeshGroup* CMeshGroup::GetParent()
{
	return m_MeshGroup->parent;
}

int CMeshGroup::DeleteMeshInstance(POSITION pos)
{
	CMeshInstance* pMI;
	pMI=(CMeshInstance*)m_MeshGroup->MeshList.GetAt(pos);
	pMI->DetachFromTree();
	m_MeshGroup->MeshList.RemoveAt(pos);
	delete pMI;
	m_MeshGroup->info.nmesh--;
	return true;
}

int CMeshGroup::DeleteMeshGroup(POSITION pos)
{
	CMeshGroup* pMG;
	pMG=(CMeshGroup*)m_MeshGroup->grouplist.GetAt(pos);
	pMG->DetachFromTree();
	m_MeshGroup->grouplist.RemoveAt(pos);
	delete pMG;
	m_MeshGroup->info.nmeshgroup--;
	return true;
}

int CMeshGroup::DetachFromTree()
{
	if (m_MeshGroup->htree)
	{
		m_MeshGroup->tree->DeleteItem(m_MeshGroup->htree);
	}
	return true;
}

int CMeshGroup::Delete()
{
	if (!m_MeshGroup->parent)
		return false;
	m_MeshGroup->parent->DeleteMeshGroup(m_MeshGroup->pos);
	return true;
}

int CMeshGroup::DeleteVariableInstance(POSITION pos)
{
	CVariableInstance* pVI;
	pVI=(CVariableInstance*)m_MeshGroup->VarList.GetAt(pos);
	pVI->DetachFromTree();
	m_MeshGroup->VarList.RemoveAt(pos);
	delete pVI;
	m_MeshGroup->info.nvar--;
	return true;
}

int CMeshGroup::SetName(char *name)
{
	memcpy(m_MeshGroup->info.name,name,20);
	return true;
}

int CMeshGroup::SaveToFile(FILE *pFile)
{
	fwrite(&m_MeshGroup->info,sizeof(S_MESHGROUPINFO),1,pFile);

	POSITION	pos;
	CVariableInstance*	pVariable;
	CMeshInstance*		pMesh;
	CMeshGroup*			pMeshGroup;

	if (!m_MeshGroup->VarList.IsEmpty()) 
	{
		pos=m_MeshGroup->VarList.GetHeadPosition();
		do
		{
			pVariable=(CVariableInstance*)m_MeshGroup->VarList.GetAt(pos);
			pVariable->SaveToFile(pFile);
			m_MeshGroup->VarList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->MeshList.IsEmpty()) 
	{
		pos=m_MeshGroup->MeshList.GetHeadPosition();
		do
		{
			pMesh=(CMeshInstance*)m_MeshGroup->MeshList.GetAt(pos);
			pMesh->SaveToFile(pFile);
			m_MeshGroup->MeshList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->grouplist.IsEmpty()) 
	{
		pos=m_MeshGroup->grouplist.GetHeadPosition();
		do
		{
			pMeshGroup=(CMeshGroup*)m_MeshGroup->grouplist.GetAt(pos);
			pMeshGroup->SaveToFile(pFile);
			m_MeshGroup->grouplist.GetNext(pos);
		} while (pos != NULL);
	}
	return true;
}

int CMeshGroup::ReadFromFile(FILE *pFile)
{
	DWORD	cant;
	DWORD	i;
	fread(&m_MeshGroup->info,sizeof(S_MESHGROUPINFO),1,pFile);

	// leer todas las variables
	cant=m_MeshGroup->info.nvar;
	m_MeshGroup->info.nvar=0;
	for (i=0;i<cant;i++)
	{
		CVariableInstance* pVI = new CVariableInstance();
		AddVariableInstance(pVI);
		pVI->ReadFromFile(pFile);
	}
	// leer todas las mallas
	cant=m_MeshGroup->info.nmesh;
	m_MeshGroup->info.nmesh=0;
	for (i=0;i<cant;i++)
	{
		CMeshInstance* pMI= new CMeshInstance();
		AddMeshInstance(pMI);
		pMI->ReadFromFile(pFile);
	}
	// leer todos los grupos de mallas
	cant=m_MeshGroup->info.nmeshgroup;
	m_MeshGroup->info.nmeshgroup=0;
	for (i=0;i<cant;i++)
	{
		CMeshGroup* pMG = new CMeshGroup();
		AddMeshGroup(pMG);
		pMG->ReadFromFile(pFile);
	}
	return true;
}

int CMeshGroup::AddVariableInstance(CVariableInstance *pVariableInstance)
{
	pVariableInstance->SetPos(m_MeshGroup->VarList.AddTail(pVariableInstance));
	pVariableInstance->SetParent(this);
	pVariableInstance->SetTree(m_MeshGroup->tree);
	m_MeshGroup->info.nvar++;
	return true;
}

int CMeshGroup::AddMeshInstance(CMeshInstance *pMI)
{
	POSITION	pos;
	pos=m_MeshGroup->MeshList.AddHead(pMI);
	pMI->SetParent(this);
	pMI->SetPos(pos);
	pMI->SetTree(m_MeshGroup->tree);
	m_MeshGroup->info.nmesh++;
	return true;
}

int CMeshGroup::SetTree(CEscenaTree *pTree)
{
	m_MeshGroup->tree=pTree;

	// Poner el tree a todos los elementos del meshgroup 
	POSITION pos;
	CVariableInstance*	pVariable;
	CMeshInstance*		pMesh;
	CMeshGroup*			pMeshGroup;

	if (!m_MeshGroup->VarList.IsEmpty()) 
	{
		pos=m_MeshGroup->VarList.GetHeadPosition();
		do
		{
			pVariable=(CVariableInstance*)m_MeshGroup->VarList.GetAt(pos);
			pVariable->SetTree(pTree);
			m_MeshGroup->VarList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->MeshList.IsEmpty()) 
	{
		pos=m_MeshGroup->MeshList.GetHeadPosition();
		do
		{
			pMesh=(CMeshInstance*)m_MeshGroup->MeshList.GetAt(pos);
			pMesh->SetTree(pTree);
			m_MeshGroup->MeshList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->grouplist.IsEmpty()) 
	{
		pos=m_MeshGroup->grouplist.GetHeadPosition();
		do
		{
			pMeshGroup=(CMeshGroup*)m_MeshGroup->grouplist.GetAt(pos);
			pMeshGroup->SetTree(pTree);
			m_MeshGroup->grouplist.GetNext(pos);
		} while (pos != NULL);
	}
	return true;
}

int CMeshGroup::AttachToTree()
{
	if (!m_MeshGroup->tree)
		return false;
	TV_INSERTSTRUCT tvi;
	if (m_MeshGroup->parent)
	{
		tvi.hParent=m_MeshGroup->parent->GetTreeHandle();
		tvi.hInsertAfter=TVI_LAST;
	}
	else
	{
		tvi.hParent=m_MeshGroup->escena->GetTreeHandle();
		tvi.hInsertAfter=TVI_FIRST;
	}
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=10;
	tvi.itemex.iSelectedImage=MESHGROUP_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=m_MeshGroup->info.name;
	tvi.itemex.iImage=MESHGROUP_ICON;
	tvi.itemex.lParam=(DWORD)&m_MeshGroup->treelparam;
	m_MeshGroup->htree=m_MeshGroup->tree->InsertItem(&tvi);

	// Adicionar todos los elementos del meshgroup al tree
	POSITION pos;
	CVariableInstance*	pVariable;
	CMeshInstance*		pMesh;
	CMeshGroup*			pMeshGroup;

	if (!m_MeshGroup->VarList.IsEmpty()) 
	{
		pos=m_MeshGroup->VarList.GetHeadPosition();
		do
		{
			pVariable=(CVariableInstance*)m_MeshGroup->VarList.GetAt(pos);
			pVariable->AttachToTree();
			m_MeshGroup->VarList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->MeshList.IsEmpty()) 
	{
		pos=m_MeshGroup->MeshList.GetHeadPosition();
		do
		{
			pMesh=(CMeshInstance*)m_MeshGroup->MeshList.GetAt(pos);
			pMesh->AttachToTree();
			m_MeshGroup->MeshList.GetNext(pos);
		} while (pos != NULL);
	}

	if (!m_MeshGroup->grouplist.IsEmpty()) 
	{
		pos=m_MeshGroup->grouplist.GetHeadPosition();
		do
		{
			pMeshGroup=(CMeshGroup*)m_MeshGroup->grouplist.GetAt(pos);
			pMeshGroup->AttachToTree();
			m_MeshGroup->grouplist.GetNext(pos);
		} while (pos != NULL);
	}
	return true;
}
