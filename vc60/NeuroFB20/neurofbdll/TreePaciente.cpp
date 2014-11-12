// TreePaciente.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "TreePaciente.h"
#include "viewmostrardatos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "app.h"
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CTreePaciente

void* pAppt;
void* pMostrart; 

CTreePaciente::CTreePaciente()
{
		pImageList = new CImageList();
	    pImageList->Create(15,15, TRUE, 5, 2);

	    bitmap.LoadBitmap(IDB_NOPACIENT);
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();
	
		bitmap.LoadBitmap(IDB_PACIENT);
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_SESSION);
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_CONDITION);
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();

		bitmap.LoadBitmap(IDB_MINUTE);
		pImageList->Add(&bitmap, (COLORREF)0xFFFFFF);
		bitmap.DeleteObject();

		m_condicion_sel = 0;
		m_sesion_sel = 0;

}

CTreePaciente::~CTreePaciente()
{
	delete pImageList;
}


BEGIN_MESSAGE_MAP(CTreePaciente, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreePaciente)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreePaciente message handlers

bool CTreePaciente::PintarTree(long sesiones, long *condiciones, void *pApp, void *pMostrar)
{
    
	pMostrart = (CViewMostrarDatos*) pMostrar;
	pAppt = (CApp*) pApp;
	InitTree();
	HTREEITEM Sesion, Condicion;
	CString str_sesion, str_condicion, temp;
    char *put_sesion;
	char *put_condicion;

	put_sesion = new char[12];
	put_condicion = new char[15];

	//aqui se dibuja en el tree las sesiones y las condiciones
	for (long j=0; j<sesiones; j++)
	{
	    	
	    tvstruct.hParent = Paciente;
		tvstruct.item.iImage = 2;
		tvstruct.item.iSelectedImage = 2;
		temp.Format("%d", (sesiones-j));
		str_sesion = "Session " +temp;
		strcpy(put_sesion, (LPCSTR) str_sesion);
		tvstruct.item.pszText = put_sesion;
        Sesion = InsertItem(&tvstruct);

		   for (int i=0; i<condiciones[sesiones-j]; i++)
		   {
		     tvstruct.hParent = Sesion;
		     tvstruct.item.iImage = 3;
		     tvstruct.item.iSelectedImage = 3;
			 temp.Format("%d", (condiciones[sesiones-j]-i));
		     str_condicion = "Condition " + temp;
		     strcpy(put_condicion, (LPCSTR) str_condicion);
		     tvstruct.item.pszText = put_condicion; 
             Condicion = InsertItem(&tvstruct);
		   }
	}
	
	//aqui si existe al menos una sesion se selecciona la primera 
	//y la primera condicion

	Expand(Paciente,TVE_EXPAND);
	Expand(Sesion,TVE_EXPAND);
	SelectItem(Condicion);

    GetSeleccion();
	PonerDatos();

	delete put_sesion;
	delete put_condicion;

    return true;
}

	
bool CTreePaciente::InitTree()
{

	char *nombre;
	nombre = new char[((CApp*)pAppt)->paciente.nombre.GetLength() +1];
	strcpy(nombre, (LPCSTR) ((CApp*)pAppt)->paciente.nombre);
	
	SetImageList(pImageList, TVSIL_NORMAL);
	DeleteAllItems();
	ModifyStyle(NULL,TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT , 0);
	tvstruct.hParent = NULL;
	tvstruct.hInsertAfter = TVI_FIRST;
	tvstruct.item.iImage = 1;
	tvstruct.item.iSelectedImage = 1;
	tvstruct.item.pszText = nombre;
	tvstruct.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	
	Paciente = InsertItem(&tvstruct);
    delete nombre;
	return true;
}

void CTreePaciente::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	GetSeleccion();
	PonerDatos();
	
    *pResult = 0;
}

bool CTreePaciente::GetSeleccion()
{

    HTREEITEM selected;
    HTREEITEM parent;
	CString str_sel, str_parent, temp;

	selected = GetSelectedItem();
    str_sel = GetItemText(selected);

    if (str_sel.Find("Condition",0) != -1)
	{
	  temp = str_sel.Right(str_sel.GetLength()-10);
	  m_condicion_sel = atoi(temp);

	  parent = GetParentItem(selected);
	  str_parent = GetItemText(parent);
      temp = str_parent.Right(str_parent.GetLength()-8);
	  m_sesion_sel = atoi(temp);
	}
 
	if (str_sel.Find("Session",0) != -1)
	{
	  temp = str_sel.Right(str_sel.GetLength()-8);
	  m_sesion_sel = atoi(temp);
      m_condicion_sel = 1;
	}
	
	return true;
}

bool CTreePaciente::PonerDatos()
{
    ((CViewMostrarDatos*)pMostrart)->RefrescarDatos(m_sesion_sel, m_condicion_sel);
	return true;
}
