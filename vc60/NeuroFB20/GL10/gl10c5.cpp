// gl10c5.cpp: implementation of the CEscena class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c5.h"
#include "gl10c3.h"
#include "gl10c7.h"
#include "gl10c6.h"
#include "gl10c9.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEscena::CEscena()
{
	InitEscena();
}

CEscena::~CEscena()
{
	DeleteAllMaterials();
	DeleteAllMeshes();
	DeleteAllVariables();
	delete m_Escena;
}

int CEscena::InitEscena()
{
	m_Escena=new S_ESCENA;
	m_Escena->info.m_version=sizeof(S_3DESCENE);
	m_Escena->info.m_mat_cant=0;
	m_Escena->info.m_mesh_cant=0;
	m_Escena->info.m_var_cant=0;
	m_Escena->htree=0;
	m_Escena->hmaterialfolder=0;
	m_Escena->hmeshfolder=0;
	m_Escena->treelparam.type=ID_ESCENA;
	m_Escena->treelparam.object=this;
	m_Escena->meshgroup.SetEscena(this);
	m_Escena->wireframe=false;
	m_Escena->tree=NULL;
	return true;
}

int CEscena::DeleteAllMaterials()
{
	if (!m_Escena->materials.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_Escena->materials.GetHeadPosition();
		do
		{
			delete m_Escena->materials.GetAt(pPos);
			m_Escena->materials.GetNext(pPos);
		} while (pPos != NULL);
		m_Escena->materials.RemoveAll();
	}
	return true;
}

int CEscena::DeleteAllMeshes()
{
	if (!m_Escena->meshes.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_Escena->meshes.GetHeadPosition();
		do
		{
			delete m_Escena->meshes.GetAt(pPos);
			m_Escena->meshes.GetNext(pPos);
		} while (pPos != NULL);
		m_Escena->meshes.RemoveAll();
	}
	return true;	
}

CMaterial* CEscena::GetMaterial(DWORD pIndex)
{
	if (!m_Escena->materials.IsEmpty()) 
	{
		POSITION		pPos;
		CMaterial*		pMaterial;
		pPos=m_Escena->materials.GetHeadPosition();
		do
		{
			pMaterial=(CMaterial*) m_Escena->materials.GetAt(pPos);
			if (pMaterial->GetIndex()==pIndex)
				return pMaterial;
			m_Escena->materials.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;	
}


CMaterial* CEscena::GetMaterial(POSITION pPos)
{
	return (CMaterial*) m_Escena->materials.GetAt(pPos);
}

int CEscena::Read3DS()
{
	CString	m_FileName;
	static char ExtFilter[] = "3DS Files (*.3DS) |*.3ds||"; 
	CFileDialog Dlg(true,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,ExtFilter);
	if (Dlg.DoModal() == IDOK)
	{
		database3ds*	db		= NULL;
		file3ds*		file	= NULL;
		namelist3ds*	meshlist= NULL;
		namelist3ds*	matlist	= NULL;
		mesh3ds*		mesh	= NULL;
		material3ds*	mat		= NULL; 
		ulong3ds		i;

		m_FileName=Dlg.GetFileName();
		InitDatabase3ds(&db);
		file=OpenFile3ds(m_FileName,"rb");
		CreateDatabase3ds(file,db);
		GetMeshNameList3ds(db, &meshlist);
		GetMaterialNameList3ds(db,&matlist);
		PRINT_ERRORS_EXIT(stderr);
		for (i=0; i<matlist->count; i++)
		{
			GetMaterialByName3ds(db,matlist->list[i].name,&mat);
			CMaterial* pMaterial=new CMaterial(mat);
			AddMaterial(pMaterial);
			ReleaseMaterial3ds(&mat);
		}
		for (i=0; i < meshlist->count; i++)
		{
			GetMeshByName3ds(db, meshlist->list[i].name, &mesh);
			PRINT_ERRORS_EXIT(stderr);
			CMeshMat* pMesh=new CMeshMat();
			pMesh->SetEscena(this);
			pMesh->ReadMesh3DS(mesh);
			AddMesh(pMesh);
			RelMeshObj3ds (&mesh);
		}
		ReleaseNameList3ds(&meshlist);
		ReleaseNameList3ds(&matlist);
		DisconnectDatabase3ds(db);
		ReleaseDatabase3ds(&db);
		CloseAllFiles3ds();
	}
	return true;
}

 int CEscena::AddMaterial(CMaterial *pMaterial)
{
	POSITION	pPos=m_Escena->materials.AddTail(pMaterial);
	m_Escena->info.m_mat_cant++;
	pMaterial->SetPos(pPos);
	if (!m_Escena->tree)
		return false;
	TV_INSERTSTRUCT tvi;
	tvi.hParent=m_Escena->hmaterialfolder;
	tvi.hInsertAfter=TVI_LAST;
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=17;
	tvi.itemex.iSelectedImage=MATERIAL_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=pMaterial->GetName();
	tvi.itemex.iImage=MATERIAL_ICON;
	tvi.itemex.lParam=pMaterial->GetTreeLParam();
	pMaterial->SetTreeHandle(m_Escena->tree->InsertItem(&tvi));
	return true;
}

int CEscena::AddMesh(CMeshMat *pMesh)
{
	pMesh->SetEscena(this);
	m_Escena->meshes.AddTail(pMesh);
	m_Escena->info.m_mesh_cant++;
	if (!m_Escena->tree)
		return true;
	TV_INSERTSTRUCT tvi;
	tvi.hParent=m_Escena->hmeshfolder;
	tvi.hInsertAfter=TVI_LAST;
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=17;
	tvi.itemex.iSelectedImage=MESH_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=pMesh->GetName();
	tvi.itemex.iImage=MESH_ICON;
	tvi.itemex.lParam=pMesh->GetTreeLParam();
	pMesh->SetTreeHandle(m_Escena->tree->InsertItem(&tvi));	
	return true;
}

int CEscena::Paint()
{
	if (IsWireFrame())
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	}
	m_Escena->meshgroup.Paint();
	return true;
}

CMaterial* CEscena::GetMaterial(char *pname)
{
	if (!m_Escena->materials.IsEmpty()) 
	{
		POSITION		pPos;
		CMaterial*		pMaterial;
		pPos=m_Escena->materials.GetHeadPosition();
		do
		{
			pMaterial=(CMaterial*) m_Escena->materials.GetAt(pPos);
			if (!strcmp(pMaterial->GetName(),pname))
				return pMaterial;
			m_Escena->materials.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;
}

int CEscena::AttachTree(CEscenaTree *pTree)
{
	m_Escena->tree=pTree;
	UpDateTree();
	return true;
}

int CEscena::UpDateTree()
{
	if (!m_Escena->htree)
	{
		TV_INSERTSTRUCT tvi;
		tvi.hParent=NULL;
		tvi.hInsertAfter=TVI_LAST;
		tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
		tvi.itemex.hItem=NULL;
		tvi.itemex.state=0;
		tvi.itemex.stateMask=0;
		tvi.itemex.cchTextMax=10;
		tvi.itemex.iSelectedImage=VISTA_ICON;
		tvi.itemex.cChildren=0;
		tvi.itemex.pszText="Escena";
		tvi.itemex.iImage=VISTA_ICON;
		tvi.itemex.lParam=GetTreeLParam();
		m_Escena->htree=m_Escena->tree->InsertItem(&tvi);
		tvi.itemex.lParam=0;
		tvi.hParent=m_Escena->htree;
		tvi.itemex.iSelectedImage=FOLDER_ICON;
		tvi.itemex.iImage=FOLDER_ICON;
		tvi.itemex.pszText="Materials";
		m_Escena->hmaterialfolder=m_Escena->tree->InsertItem(&tvi);
		tvi.itemex.pszText="Meshes";
		m_Escena->hmeshfolder=m_Escena->tree->InsertItem(&tvi);
		tvi.itemex.pszText="Variables";
		m_Escena->hvarfolder=m_Escena->tree->InsertItem(&tvi);
	}
	m_Escena->meshgroup.SetTree(m_Escena->tree);
	m_Escena->meshgroup.AttachToTree();
	return true;
}

LPARAM CEscena::GetTreeLParam()
{
	return (DWORD)&m_Escena->treelparam;
}

CMeshMat* CEscena::GetMesh(DWORD index)
{
	if (!m_Escena->meshes.IsEmpty()) 
	{
		POSITION		pPos;
		CMeshMat*		pMesh;
		pPos=m_Escena->meshes.GetHeadPosition();
		do
		{
			pMesh=(CMeshMat*) m_Escena->meshes.GetAt(pPos);
			if (pMesh->GetIndex()==index)
				return pMesh;
			m_Escena->meshes.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;
}

CMeshMat* CEscena::GetMesh(POSITION pPos)
{
	return (CMeshMat*)m_Escena->meshes.GetAt(pPos);	
}

HTREEITEM CEscena::GetTreeHandle()
{
	return m_Escena->htree;
}

int CEscena::AddVar(CVariable *pvar)
{
	pvar->SetPos(m_Escena->vars.AddTail(pvar));
	pvar->SetEscena(this);
	pvar->AttachToTree(m_Escena->tree);
	m_Escena->info.m_var_cant++;
	return true;
}

HTREEITEM CEscena::GetVarTreeHandle()
{
	return m_Escena->hvarfolder;
}

int CEscena::DeleteAllVariables()
{
	if (!m_Escena->vars.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_Escena->vars.GetHeadPosition();
		do
		{
			delete m_Escena->vars.GetAt(pPos);
			m_Escena->vars.GetNext(pPos);
		} while (pPos != NULL);
		m_Escena->vars.RemoveAll();
	}
	return true;

}

int CEscena::NewVar()
{
	CVariable* pnew=new CVariable();
	AddVar(pnew);
	return true;
}

int CEscena::SaveToFile(FILE *pFile)
{
	UpdateIndex();
	fwrite(&m_Escena->info,sizeof(S_3DESCENE),1,pFile);

	if (!m_Escena->vars.IsEmpty()) 
	{
		POSITION		pPos;
		CVariable*		pVariable;
		pPos=m_Escena->vars.GetHeadPosition();
		do
		{
			pVariable=(CVariable*) m_Escena->vars.GetAt(pPos);
			pVariable->SaveToFile(pFile);
			m_Escena->vars.GetNext(pPos);
		} while (pPos != NULL);
	}

	if (!m_Escena->materials.IsEmpty()) 
	{
		POSITION		pPos;
		CMaterial*		pMaterial;
		pPos=m_Escena->materials.GetHeadPosition();
		do
		{
			pMaterial=(CMaterial*) m_Escena->materials.GetAt(pPos);
			pMaterial->SaveToFile(pFile);
			m_Escena->materials.GetNext(pPos);
		} while (pPos != NULL);
	}

	if (!m_Escena->meshes.IsEmpty()) 
	{
		POSITION		pPos;
		CMeshMat*		pMeshMat;
		pPos=m_Escena->meshes.GetHeadPosition();
		do
		{
			pMeshMat=(CMeshMat*) m_Escena->meshes.GetAt(pPos);
			pMeshMat->SaveToFile(pFile);
			m_Escena->meshes.GetNext(pPos);
		} while (pPos != NULL);
	}
	m_Escena->meshgroup.SaveToFile(pFile);
	return true;
}

//
// Actualiza el indice de los maeriales,las mallas y las variables
//
int CEscena::UpdateIndex()
{
	DWORD pIndex;
	pIndex=0;
	if (!m_Escena->materials.IsEmpty()) 
	{
		POSITION		pPos;
		CMaterial*		pMaterial;
		pPos=m_Escena->materials.GetHeadPosition();
		do
		{
			pMaterial=(CMaterial*) m_Escena->materials.GetAt(pPos);
			pMaterial->SetIndex(pIndex);
			pIndex++;
			m_Escena->materials.GetNext(pPos);
		} while (pPos != NULL);
	}

	pIndex=0;
	if (!m_Escena->vars.IsEmpty()) 
	{
		POSITION		pPos;
		CVariable*		pVariable;
		pPos=m_Escena->vars.GetHeadPosition();
		do
		{
			pVariable=(CVariable*) m_Escena->vars.GetAt(pPos);
			pVariable->SetIndex(pIndex);
			pIndex++;
			m_Escena->vars.GetNext(pPos);
		} while (pPos != NULL);
	}

	pIndex=0;
	if (!m_Escena->meshes.IsEmpty()) 
	{
		POSITION		pPos;
		CMeshMat*		pMeshMat;
		pPos=m_Escena->meshes.GetHeadPosition();
		do
		{
			pMeshMat=(CMeshMat*) m_Escena->meshes.GetAt(pPos);
			pMeshMat->SetIndex(pIndex);
			pIndex++;
			m_Escena->meshes.GetNext(pPos);
		} while (pPos != NULL);
	}
	return true;	
}

int CEscena::Save()
{
	CString	m_FileName;
	static char ExtFilter[] = "OpenGL Files (*.OGL) |*.ogl||"; 
	CFileDialog Dlg(false,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,ExtFilter);
	if (Dlg.DoModal() == IDOK)	
	{
		m_FileName=Dlg.GetPathName();
		FILE*	file=fopen(m_FileName,"wb");
		if (file)
		{
			SaveToFile(file);
			fclose(file);
			return true;
		}
	}
	return false;
}

int CEscena::ReadFromFile(FILE *pFile)
{
	fread(&m_Escena->info.m_version,sizeof(S_3DESCENE),1,pFile);
	if (m_Escena->info.m_version != sizeof (S_3DESCENE))
		return false;
	// lectura de todas las variables
	DWORD i;
	DWORD cant;
	cant=m_Escena->info.m_var_cant;
	m_Escena->info.m_var_cant=0;
	for (i=0;i<cant;i++)
	{
		CVariable* pVar= new CVariable();
		if (pVar->ReadFromFile(pFile))
			AddVar(pVar);
		else
		{
			delete pVar;
			return false;
		}
	}
	// Lectura de todos los materiales
	cant=m_Escena->info.m_mat_cant;
	m_Escena->info.m_mat_cant=0;
	for (i=0;i<cant;i++)
	{
		CMaterial* pMat = new CMaterial();
		if (pMat->ReadFromFile(pFile))
			AddMaterial(pMat);
		else
		{
			delete pMat;
			return false;
		}
	}
	// Lectura de las mallas
	cant=m_Escena->info.m_mesh_cant;
	m_Escena->info.m_mesh_cant=0;
	for (i=0;i<cant;i++)
	{
		CMeshMat* pMesh = new CMeshMat();
		pMesh->SetEscena(this);
		if (pMesh->ReadFromFile(pFile))
			AddMesh(pMesh);
		else
		{
			delete pMesh;
			return false;
		}
	}
	// lectura de todos los grupos de mallas
	m_Escena->meshgroup.DetachFromTree();
	m_Escena->meshgroup.ReadFromFile(pFile);
	m_Escena->meshgroup.AttachToTree();
	return true;
}

int CEscena::Read()
{
	CString	m_FileName;
	static char ExtFilter[] = "OpenGL Files (*.OGL) |*.ogl||"; 
	CFileDialog Dlg(true,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,ExtFilter);
	if (Dlg.DoModal() == IDOK)	
	{
		m_FileName=Dlg.GetPathName();
		FILE*	file=fopen(m_FileName,"rb");
		if (file)
		{
			ReadFromFile(file);
			fclose(file);
			return true;
		}
	}
	return false;	
}

CVariable* CEscena::GetVariable(DWORD pIndex)
{
	if (!m_Escena->vars.IsEmpty()) 
	{
		POSITION		pPos;
		CVariable*		pV;
		pPos=m_Escena->vars.GetHeadPosition();
		do
		{
			pV=(CVariable*) m_Escena->vars.GetAt(pPos);
			if (pV->GetIndex()==pIndex)
				return pV;
			m_Escena->vars.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;	
}

BOOL CEscena::IsWireFrame()
{
	return m_Escena->wireframe;
}



int CEscena::SetWireFrame(BOOL state)
{
	m_Escena->wireframe=state;
	return true;
}

CVariable* CEscena::GetVariable(char *name)
{
	if (!m_Escena->vars.IsEmpty()) 
	{
		POSITION		pPos;
		CVariable*		pVar;
		pPos=m_Escena->vars.GetHeadPosition();
		do
		{
			pVar=(CVariable*) m_Escena->vars.GetAt(pPos);
			if (!strcmp(pVar->GetName(),name))
				return pVar;
			m_Escena->vars.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;

}

int CEscena::SetVarValue(char *name, float value)
{
	CVariable*	pVar=GetVariable(name);
	if (!pVar)
		return false;
	pVar->SetValue(value);
	return true;
}

CMeshMat* CEscena::GetMesh(char *name)
{
	if (!m_Escena->meshes.IsEmpty()) 
	{
		POSITION		pPos;
		CMeshMat*		pMesh;
		pPos=m_Escena->meshes.GetHeadPosition();
		do
		{
			pMesh=(CMeshMat*) m_Escena->meshes.GetAt(pPos);
			if (!strcmp(pMesh->GetName(),name))
				return pMesh;
			m_Escena->meshes.GetNext(pPos);
		} while (pPos != NULL);
	}
	return NULL;
}
