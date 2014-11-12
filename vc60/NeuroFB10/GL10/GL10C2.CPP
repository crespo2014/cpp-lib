// gl10c2.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "gl10c2.h"
#include "class3.h"
#include "class2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CTree3DObject

CTree3DObject::CTree3DObject()
{
	m_Members=new S_Tree3DObject;
	Init();
}

CTree3DObject::~CTree3DObject()
{
	delete m_Members;
}


BEGIN_MESSAGE_MAP(CTree3DObject, CTreeCtrl)
	//{{AFX_MSG_MAP(CTree3DObject)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_COMMAND(ID_CONFIGURE, OnConfigure)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_ADDOBJECT, OnAddobject)
	ON_WM_RBUTTONDOWN()
	ON_WM_CLOSE()
	ON_COMMAND(ID_IMPORT3DS, OnImport3ds)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTree3DObject message handlers

int CTree3DObject::Inicializar()
{
	SetImageList(&m_Members->m_ImageListSmall,LVSIL_NORMAL);
	m_Members->m_Menu.LoadMenu(IDR_TREE_MENU);
	return true;
}

int CTree3DObject::Init()
{
	CWinApp* pApp=AfxGetApp();
	m_Members->m_ImageListSmall.Create(16,16,TRUE,4,4);
	m_Members->m_ImageListSmall.Add(pApp->LoadIcon(IDI_VISTA));
	m_Members->m_ImageListSmall.Add(pApp->LoadIcon(IDI_3DOBJECT));
	m_Members->m_ImageListSmall.Add(pApp->LoadIcon(IDI_PRIMITIVA));
	m_Members->m_ImageListSmall.Add(pApp->LoadIcon(IDI_CILINDRO));
	return true;
}



void CTree3DObject::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CTreeCtrl::PreSubclassWindow();
	Inicializar();
}

void CTree3DObject::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
		
	*pResult = 0;
}

void CTree3DObject::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW*	pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	S_TreeObject*	p3DObject;
	// TODO: Add your control notification handler code here
	if (pNMTreeView->itemNew.hItem)
	{
		p3DObject=(S_TreeObject*)pNMTreeView->itemNew.lParam;
		if (p3DObject->m_Type==0)
		{
			CGLPrimitiva* pPrim= (CGLPrimitiva*)p3DObject->m_This;
			pPrim->SetSelect(true);
		}
	}
	if (pNMTreeView->itemOld.hItem)
	{
		p3DObject=(S_TreeObject*)pNMTreeView->itemOld.lParam;
		if (p3DObject->m_Type==0)
		{
			CGLPrimitiva* pPrim= (CGLPrimitiva*)p3DObject->m_This;
			pPrim->SetSelect(false);
		}
	}
	/*

	HTREEITEM phItem=pNMTreeView->itemNew.hItem;
	TRACE1("Nuevo item Selecionado Item %d \n",phItem);
	*/

	*pResult = 0;
}

void CTree3DObject::OnConfigure() 
{
	// TODO: Add your command handler code here
	HTREEITEM phItem=GetSelectedItem();
	if (!phItem)
		return;
	S_TreeObject* p3DObject=(S_TreeObject*)GetItemData(phItem);
	if (p3DObject->m_Type==1)
	{
		C3DObject* pObject1= (C3DObject*)p3DObject->m_This;
		pObject1->Configure();
	}
}

void CTree3DObject::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM phItem=GetSelectedItem();
	if (!phItem)
		return;
	CPoint point;
	GetCursorPos(&point);
	CMenu* pPopup = m_Members->m_Menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this,NULL);
    *pResult = 0;
}

void CTree3DObject::OnAddobject() 
{
	HTREEITEM phItem=GetSelectedItem();
	if (!phItem)
		return;
	S_TreeObject* p3DObject=(S_TreeObject*)GetItemData(phItem);
	if (p3DObject->m_Type==1)
	{
		C3DObject* pObject1= (C3DObject*)p3DObject->m_This;
		pObject1->AddNewObject();
	}		
}

void CTree3DObject::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UINT pint;
	HTREEITEM phItem=HitTest(point,&pint);
	SelectItem(phItem);
	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CTree3DObject::OnClose() 
{
	DeleteAllItems();
	CTreeCtrl::OnClose();
}

void CTree3DObject::OnImport3ds() 
{
	// TODO: Add your command handler code here
	HTREEITEM phItem=GetSelectedItem();
	if (!phItem)
		return;
	S_TreeObject* p3DObject=(S_TreeObject*)GetItemData(phItem);
	if (p3DObject->m_Type==1)
	{
		C3DObject* pObject1= (C3DObject*)p3DObject->m_This;
		pObject1->Import3ds();
	}

}
