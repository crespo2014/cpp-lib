// class2.cpp: implementation of the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "class2.h"
#include "class6.h"
#include "Dlg2.h"
#include "gl10d3.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DObject::C3DObject()
{
	m_3DObject=new S_3DObject;
	Init();
}

C3DObject::~C3DObject()
{
	Destroy();
	RemoveFromTree();    
	// se pone aqui y no en destroy porque cuando se limpia la lista 
	// se pierde este elemento del tree
	delete m_3DObject;
}

int C3DObject::SaveToFile(FILE *pFile)
{
	S_3DVIEWINFO	pViewInfo;
	pViewInfo.m_ObjectsCant=m_3DObject->m_Disk.m_ChildsCant;
	fwrite(&pViewInfo,sizeof(S_3DVIEWINFO),1,pFile);
	SaveAllAssociatesObjects(pFile);
	SaveAllChildObject(pFile);
	return true;
}

int C3DObject::SetName(CString pName)
{
	m_3DObject->m_Name=pName;
	m_3DObject->m_Disk.m_NameLength=m_3DObject->m_Name.GetLength();
	return true;
}
/*
	Esto solo es aplicable a la escena
*/
int C3DObject::ReadFromFile(FILE *pFile)
{
	S_3DVIEWINFO	pViewInfo;
	fread(&pViewInfo,sizeof(S_3DVIEWINFO),1,pFile);
	AddChildsObjects(pViewInfo.m_ObjectsCant,pFile);
	return true;
}

int C3DObject::Paint()
{
	
	GLdouble pMatrix[16];
	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX,pMatrix);
	glPopMatrix();

	if (m_3DObject->m_Parent || m_3DObject->m_Partner)
	{
		// Aplicando transformaciones a la matrix si el objeto no es asociado
		glTranslated(m_3DObject->m_Disk.m_PosX,m_3DObject->m_Disk.m_PosY,m_3DObject->m_Disk.m_PosZ);
	}
	if (!m_3DObject->m_Partner)
	{
		glColor4fv(&m_3DObject->m_Disk.m_ColorR);
	}
		
	if (!IsPrimitive())
		VPaint();

	// recorriendo todas las primitivas
	if (!m_3DObject->m_Primitives.IsEmpty()) 
	{
		CGLPrimitiva*	pPrimitive;
		POSITION		pPos;
		pPos=m_3DObject->m_Primitives.GetHeadPosition();
		do
		{
			pPrimitive=(CGLPrimitiva*)m_3DObject->m_Primitives.GetAt(pPos);
			if (pPrimitive->IsSelected())
			{
				float pMax[3];
				float pMin[3];
				pPrimitive->GetMaxPoint(pMax);
				pPrimitive->GetMinPoint(pMin);
				PaintBox(pMax,pMin);
			}
			else 	
				pPrimitive->Paint();
			
			m_3DObject->m_Primitives.GetNext(pPos);
		} while (pPos != NULL);

	}
	// recorriendo todos los objetos
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Associates.GetAt(pPos);
			p3DObject->Paint();
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);

	}
	// recorriendo todos los objetos hijos
	if (!m_3DObject->m_Childs.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Childs.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Childs.GetAt(pPos);
			p3DObject->Paint();
			m_3DObject->m_Childs.GetNext(pPos);
		} while (pPos != NULL);

	}

	if (!m_MeshList.IsEmpty()) 
	{
		CMeshMat*		pMesh;
		POSITION		pPos;
		pPos=m_MeshList.GetHeadPosition();
		do
		{
			pMesh=(CMeshMat*)m_MeshList.GetAt(pPos);
			pMesh->Paint();
			m_MeshList.GetNext(pPos);
		} while (pPos != NULL);

	}
	
	glLoadMatrixd(pMatrix);
	return true;
}

int C3DObject::AddPrimitive(CGLPrimitiva *pPrimitiva)
{
	pPrimitiva->SetParent(this);
	m_3DObject->m_Primitives.AddTail(pPrimitiva);
	pPrimitiva->SetTree(m_3DObject->m_TreeCtrl);
	pPrimitiva->AddToTree();
	return true;
}

//
// SOPORTE PARA LAS CLASSES DE LIBRERIAS DE OBJETOS 
//
int C3DObject::EnabledFaces(DWORD pFaces)
{
	return true;
}

//
// aqui convierte todos los objetos a primitivas
//
int C3DObject::GeneratePrimitive()
{
	if (!IsPrimitive())
		if (!VGeneratePrimitive())
			return false;
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Associates.GetAt(pPos);
			p3DObject->GeneratePrimitive();
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);
	}
	m_3DObject->m_OnPrimitive=true;
	return true;
}
// Indica que las primitivas fueron generadas para este objeto
int C3DObject::IsPrimitive()
{
	return m_3DObject->m_OnPrimitive;
}



int C3DObject::Configure()
{
	CDlg3DObject  Dlg;
	Dlg.m_Objeto=this;
	Dlg.m_PosX=m_3DObject->m_Disk.m_PosX;
	Dlg.m_PosY=m_3DObject->m_Disk.m_PosY;
	Dlg.m_PosZ=m_3DObject->m_Disk.m_PosZ;
	Dlg.m_Asociar=true;
	if (Dlg.DoModal()== IDOK)
	{
		m_3DObject->m_Disk.m_PosX=Dlg.m_PosX;
		m_3DObject->m_Disk.m_PosY=Dlg.m_PosY;
		m_3DObject->m_Disk.m_PosZ=Dlg.m_PosZ;
		m_3DObject->m_OnAsociar=Dlg.m_Asociar;
		return true;
	}
	return false;
}

// Aqui se limpian todos los valores de todas las variables
int C3DObject::Init()
{
	m_3DObject->m_Disk.m_AmbientR=0;
	m_3DObject->m_Disk.m_AmbientG=0;
	m_3DObject->m_Disk.m_AmbientB=0;
	m_3DObject->m_Disk.m_AmbientA=0;
	m_3DObject->m_Disk.m_DiffuseR=0;
	m_3DObject->m_Disk.m_DiffuseG=0;
	m_3DObject->m_Disk.m_DiffuseB=0;
	m_3DObject->m_Disk.m_DiffuseA=0;

	m_3DObject->m_Disk.m_SpecularR=0;
	m_3DObject->m_Disk.m_SpecularG=0;
	m_3DObject->m_Disk.m_SpecularB=0;
	m_3DObject->m_Disk.m_SpecularA=0;
	m_3DObject->m_Disk.m_EmissionR=0;
	m_3DObject->m_Disk.m_EmissionG=0;
	m_3DObject->m_Disk.m_EmissionB=0;
	m_3DObject->m_Disk.m_EmissionA=0;
	m_3DObject->m_Disk.m_ShininessR=0;
	m_3DObject->m_Disk.m_ShininessG=0;
	m_3DObject->m_Disk.m_ShininessB=0;
	m_3DObject->m_Disk.m_ShininessA=0;
	m_3DObject->m_Disk.m_ColorR=0;
	m_3DObject->m_Disk.m_ColorG=0;
	m_3DObject->m_Disk.m_ColorB=1.0;
	m_3DObject->m_Disk.m_ColorA=1.0;
	m_3DObject->m_Disk.m_PosX=0;
	m_3DObject->m_Disk.m_PosY=0;
	m_3DObject->m_Disk.m_PosZ=0;

	m_3DObject->m_Disk.m_RotateX=0;
	m_3DObject->m_Disk.m_RotateY=0;
	m_3DObject->m_Disk.m_RotateZ=0;

	m_3DObject->m_Disk.m_AssociatesCant=0;
	m_3DObject->m_Disk.m_ChildsCant=0;
	m_3DObject->m_Disk.m_NameLength=0;
	m_3DObject->m_Disk.m_PrimitivesCant=0;
	m_3DObject->m_Disk.m_Version=sizeof(m_3DObject->m_Disk);

	m_3DObject->m_Header.m_Type=0;
	m_3DObject->m_Header.m_Version=sizeof(S_3D0BJECTHEADER);

	m_3DObject->m_OnList=false;
	m_3DObject->m_Parent=NULL;
	m_3DObject->m_Partner=NULL;
	m_3DObject->m_OnPrimitive=false;
	m_3DObject->m_hTreeItem=NULL;
	m_3DObject->m_TreeCtrl=NULL;
	m_3DObject->m_TreeObject.m_Type=1;
	m_3DObject->m_TreeObject.m_This=this;

	return true;
}

int C3DObject::Destroy()
{
	if (!m_3DObject->m_Primitives.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_3DObject->m_Primitives.GetHeadPosition();
		do
		{
			 delete (CGLPrimitiva*)m_3DObject->m_Primitives.GetAt(pPos);
			 m_3DObject->m_Primitives.GetNext(pPos);
		} while (pPos != NULL);
		m_3DObject->m_Primitives.RemoveAll();

	}
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			delete (CGLPrimitiva*)m_3DObject->m_Associates.GetAt(pPos);
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);
		m_3DObject->m_Associates.RemoveAll();
	}
		// recorriendo todos los objetos hijos
	if (!m_3DObject->m_Childs.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=m_3DObject->m_Childs.GetHeadPosition();
		do
		{
			delete (C3DObject*)m_3DObject->m_Childs.GetAt(pPos);
			m_3DObject->m_Childs.GetNext(pPos);
		} while (pPos != NULL);
		m_3DObject->m_Childs.RemoveAll();
	}
	return true;
}

int C3DObject::VGeneratePrimitive()
{
	return true;
}

int C3DObject::VPaint()
{
	return false;
}

int C3DObject::PaintBox(float *pUp, float *pDown)
{
	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
	  glVertex3d(pDown[0],pUp[1],pDown[2]);
	  glVertex3d(pUp[0],pUp[1],pDown[2]);
	  glVertex3d(pUp[0],pUp[1],pUp[2]);
	  glVertex3d(pDown[0],pUp[1],pUp[2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	  glVertex3d(pDown[0],pDown[1],pDown[2]);
	  glVertex3d(pUp[0],pDown[1],pDown[2]);
	  glVertex3d(pUp[0],pDown[1],pUp[2]);
	  glVertex3d(pDown[0],pDown[1],pUp[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	  glVertex3d(pDown[0],pUp[1],pDown[2]);
	  glVertex3d(pUp[0],pUp[1],pDown[2]);
	  glVertex3d(pUp[0],pDown[1],pDown[2]);
	  glVertex3d(pDown[0],pDown[1],pDown[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	  glVertex3d(pDown[0],pUp[1],pUp[2]);
	  glVertex3d(pUp[0],pUp[1],pUp[2]);
	  glVertex3d(pUp[0],pDown[1],pUp[2]);
	  glVertex3d(pDown[0],pDown[1],pUp[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	  glVertex3d(pDown[0],pUp[1],pUp[2]);
	  glVertex3d(pDown[0],pDown[1],pUp[2]);
	  glVertex3d(pDown[0],pDown[1],pDown[2]);
	  glVertex3d(pDown[0],pUp[1],pDown[2]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	  glVertex3d(pUp[0],pUp[1],pUp[2]);
	  glVertex3d(pUp[0],pDown[1],pUp[2]);
	  glVertex3d(pUp[0],pDown[1],pDown[2]);
	  glVertex3d(pUp[0],pUp[1],pDown[2]);
	glEnd();


	return true;
}

int C3DObject::AddNewObject()
{
	CDlgSelectObject Dlg;
	if (Dlg.DoModal()==IDOK)
	{
		C3DObject* pNew=Dlg.m_3DObject;
		if (pNew->Configure()==IDOK)
		{
			if (pNew->m_3DObject->m_OnAsociar)
				AddAssociateObject(pNew);
			else
				AddChildObject(pNew);
			pNew->AddToTree();
		}
		else
			delete pNew;
	}
	return true;
}

int C3DObject::AddToTree()
{
	if (!m_3DObject->m_TreeCtrl)
		return false;
	if (!m_3DObject->m_hTreeItem)
	{
		// evitar reinsercion en el tree
		TV_INSERTSTRUCT tvi;
		if (m_3DObject->m_Parent)
		{
			tvi.hParent=m_3DObject->m_Parent->GetTreeItemHandle();
		} else
			if (m_3DObject->m_Partner)
				tvi.hParent=m_3DObject->m_Partner->GetTreeItemHandle();
			else
				tvi.hParent=NULL;
		
		tvi.hInsertAfter=TVI_LAST;
		tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
		tvi.itemex.hItem=NULL;
		tvi.itemex.state=0;
		tvi.itemex.stateMask=0;
		tvi.itemex.cchTextMax=10;
		tvi.itemex.iSelectedImage=m_3DObject->m_Header.m_Type;
		tvi.itemex.cChildren=0;
		tvi.itemex.lParam=1;
		tvi.itemex.pszText=(char*)(LPCSTR)m_3DObject->m_Name;
		tvi.itemex.iImage=m_3DObject->m_Header.m_Type;
		tvi.itemex.lParam=(LPARAM)&m_3DObject->m_TreeObject;
		m_3DObject->m_hTreeItem=m_3DObject->m_TreeCtrl->InsertItem(&tvi);
	}

	// despues que me adiciono entonces adiciono a los demas
	if (!m_3DObject->m_Primitives.IsEmpty()) 
	{
		CGLPrimitiva*	pPrimitive;
		POSITION		pPos;
		pPos=m_3DObject->m_Primitives.GetHeadPosition();
		do
		{
			pPrimitive=(CGLPrimitiva*)m_3DObject->m_Primitives.GetAt(pPos);
			pPrimitive->AddToTree();
			m_3DObject->m_Primitives.GetNext(pPos);
		} while (pPos != NULL);
		
	}
	// recorriendo todos los objetos asociados
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Associates.GetAt(pPos);
			p3DObject->AddToTree();
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);
		
	}
	// recorriendo todos los objetos hijos
	if (!m_3DObject->m_Childs.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Childs.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Childs.GetAt(pPos);
			p3DObject->AddToTree();
			m_3DObject->m_Childs.GetNext(pPos);
		} while (pPos != NULL);
		
	}
	return true;
}

int C3DObject::AddChildObject(C3DObject *pObject)
{
	m_3DObject->m_Childs.AddTail(pObject);
	pObject->SetParent(this);
	pObject->SetTree(m_3DObject->m_TreeCtrl);

	m_3DObject->m_Disk.m_ChildsCant++;
	return true;
}

int C3DObject::AddAssociateObject(C3DObject *pObject)
{
	if (!(m_3DObject->m_Parent || m_3DObject->m_Partner))
	{	
		return AddChildObject(pObject);	// No adicionar objetos asociados a la escena
	}

	m_3DObject->m_Associates.AddTail(pObject);
	pObject->SetPartner(this);
	pObject->SetTree(m_3DObject->m_TreeCtrl);
	m_3DObject->m_Disk.m_AssociatesCant++;
	return true;
}

int C3DObject::SetParent(C3DObject *pParent)
{
	m_3DObject->m_Parent=pParent;
	m_3DObject->m_Partner=NULL;
	return true;
}

int C3DObject::SetPartner(C3DObject *p3DObject)
{
	m_3DObject->m_Partner=p3DObject;
	m_3DObject->m_Parent=NULL;
	return true;
}

int C3DObject::RemoveFromTree()
{
	if (!m_3DObject->m_hTreeItem)
		return false;
	if (!m_3DObject->m_TreeCtrl)
		return false;
	m_3DObject->m_TreeCtrl->DeleteItem(m_3DObject->m_hTreeItem);
	m_3DObject->m_hTreeItem=NULL;
	return true;
}

int C3DObject::SetTree(CTree3DObject *pTree)
{
	m_3DObject->m_TreeCtrl=pTree;
	// Poner el tree a todos los objetos contenidos en este
	if (!m_3DObject->m_Primitives.IsEmpty()) 
	{
		CGLPrimitiva*	pPrimitive;
		POSITION		pPos;
		pPos=m_3DObject->m_Primitives.GetHeadPosition();
		do
		{
			pPrimitive=(CGLPrimitiva*)m_3DObject->m_Primitives.GetAt(pPos);
			pPrimitive->SetTree(pTree);
			m_3DObject->m_Primitives.GetNext(pPos);
		} while (pPos != NULL);

	}
	// recorriendo todos los objetos
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Associates.GetAt(pPos);
			p3DObject->SetTree(pTree);
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);

	}
	// recorriendo todos los objetos hijos
	if (!m_3DObject->m_Childs.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Childs.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Childs.GetAt(pPos);
			p3DObject->SetTree(pTree);
			m_3DObject->m_Childs.GetNext(pPos);
		} while (pPos != NULL);

	}
	return true;
}

HTREEITEM C3DObject::GetTreeItemHandle()
{
	return m_3DObject->m_hTreeItem;
}

int C3DObject::VConfigure()
{
	return true;
}

/*
	Comienza la lectura de los datos desde S_3DOBJECTINFO
*/
int C3DObject::ReadData(FILE *pFile)
{
	fread(&m_3DObject->m_Disk,sizeof(S_3DOBJECTINFO),1,pFile);
	DWORD pLength=m_3DObject->m_Disk.m_NameLength;
	fread(m_3DObject->m_Name.GetBuffer(pLength),pLength,1,pFile);
	m_3DObject->m_Name.ReleaseBuffer();
	VReadData(pFile);
	// leer asociados,primitivas,acoplados,variables
	return true;
}
/*
	Permite la lectura de los datos del objetos 
*/
int C3DObject::VReadData(FILE *pFile)
{
	return true;
}
/*
	Permite salvar los parametros del objeto
*/
int C3DObject::VSaveData(FILE *pFile)
{
	return true;
}

/*
	Lee un nuevo objeto
	Comenzando por S_3D0BJECTHEADER
*/
C3DObject* C3DObject::ReadObject(FILE *pFile)
{
	S_3D0BJECTHEADER	pHeader;
	C3DObject*			pNew;
	fread(&pHeader,sizeof(S_3D0BJECTHEADER),1,pFile);
	switch (pHeader.m_Type)
	{
	case TYPE_3DOBJECT:
		{
			pNew=new C3DObject();
			break;
		}
	case TYPE_CILINDER:
		{
			pNew=new CGLCilinder();
			break;
		}
	default:
		{
			pNew=NULL;
		}
	}
	if (pNew)
		pNew->ReadData(pFile);
	return pNew;	
}
/*
	Usada cuando se esta leyendo de un fichero
*/
int C3DObject::AddChildsObjects(DWORD pCant, FILE *pFile)
{
	DWORD		i;
	C3DObject*	pNew;
	for (i=0;i<pCant;i++)
	{
		pNew=ReadObject(pFile);
		if (pNew)
			AddChildObject(pNew);
	}
	return true;
}
/*
	Usada cuando se esta leyendo de un fichero
*/
int C3DObject::AddAssociatesObjects(DWORD pCant, FILE *pFile)
{
	DWORD		i;
	C3DObject*	pNew;
	for (i=0;i<pCant;i++)
	{
		pNew=ReadObject(pFile);
		if (pNew)
			AddAssociateObject(pNew);
	}
	return true;
}

int C3DObject::SaveAllAssociatesObjects(FILE *pFile)
{
	if (!m_3DObject->m_Associates.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Associates.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Associates.GetAt(pPos);
			p3DObject->SaveData(pFile);
			m_3DObject->m_Associates.GetNext(pPos);
		} while (pPos != NULL);

	}
	return true;
}

/*
	Salvar desde S_3D0BJECTHEADER
*/
int C3DObject::SaveData(FILE *pFile)
{
	fwrite(&m_3DObject->m_Header,sizeof(S_3D0BJECTHEADER),1,pFile);
	fwrite(&m_3DObject->m_Disk,sizeof(S_3DOBJECTINFO),1,pFile);
	fwrite(m_3DObject->m_Name,m_3DObject->m_Disk.m_NameLength,1,pFile);
	if (m_3DObject->m_Header.m_Type != TYPE_3DOBJECT)
	{
		VSaveData(pFile);
	}
	return true;	
}

int C3DObject::SaveAllChildObject(FILE *pFile)
{
	if (!m_3DObject->m_Childs.IsEmpty()) 
	{
		C3DObject*		p3DObject;
		POSITION		pPos;
		pPos=m_3DObject->m_Childs.GetHeadPosition();
		do
		{
			p3DObject=(C3DObject*)m_3DObject->m_Childs.GetAt(pPos);
			p3DObject->SaveData(pFile);
			m_3DObject->m_Childs.GetNext(pPos);
		} while (pPos != NULL);

	}
	return true;
}
int C3DObject::Import3ds()
{
	return true;
	CEscena pEscena;
	pEscena.Read3DS();
	return true;
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
		ulong3ds		Count;

		m_FileName=Dlg.GetFileName();
		InitDatabase3ds(&db);
		file=OpenFile3ds(m_FileName,"rb");
		CreateDatabase3ds(file,db);
		Count=GetMeshCount3ds(db);

		GetMeshNameList3ds(db, &meshlist);
		GetMaterialNameList3ds(db,&matlist);
		PRINT_ERRORS_EXIT(stderr);
		for (i=0; i < meshlist->count; i++)
		{
			GetMeshByName3ds(db, meshlist->list[i].name, &mesh);
			
			if (mesh->matarray)
				GetMaterialByName3ds(db,mesh->matarray[0].name,&mat);
			
			PRINT_ERRORS_EXIT(stderr);
			CMeshMat* pMesh=new CMeshMat(mesh);
			AddMesh(pMesh);			
			RelMeshObj3ds (&mesh);
			PRINT_ERRORS_EXIT(stderr);
		}
		ReleaseNameList3ds(&meshlist);
		PRINT_ERRORS_EXIT(stderr);
	}
	return true;
}

int C3DObject::AddMesh(CMeshMat *pMesh)
{
	m_MeshList.AddHead(pMesh);
	return true;
}
