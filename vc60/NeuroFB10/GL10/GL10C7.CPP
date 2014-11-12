 // gl10c7.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "resource.h"
#include "gl10c7.h"
#include "gl10c4.h"
#include "gl10c8.h"
#include "gl10c5.h"
#include "gl10c3.h"
#include "gl10c9.h"
#include "gl10c10.h"
#include "gl10c6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEscenaTree

CEscenaTree::CEscenaTree()
{
	InitEscenaTree();
}

CEscenaTree::~CEscenaTree()
{
	delete m_EscenaTree;
}


BEGIN_MESSAGE_MAP(CEscenaTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CEscenaTree)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_ESCENA_READ3DS, OnEscenaRead3ds)
	ON_COMMAND(ID_VARIABLE_PROPIEDADES, OnVariablePropiedades)
	ON_COMMAND(ID_MESHINSTANCE_DELETE, OnMeshinstanceDelete)
	ON_COMMAND(ID_MESGROUP_NEW, OnMesgroupNew)
	ON_COMMAND(ID_MESGROUP_DELETE, OnMesgroupDelete)
	ON_COMMAND(ID_VARIABLEINSTANCE_DELETE, OnVariableinstanceDelete)
	ON_COMMAND(ID_ESCENA_NEWVARIABLE, OnEscenaNewvariable)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(ID_ESCENA_SAVE, OnEscenaSave)
	ON_COMMAND(ID_ESCENA_READ, OnEscenaRead)
	ON_COMMAND(ID_VARIABLEINSTANCE_PROPIEDADES, OnVariableinstancePropiedades)
	ON_UPDATE_COMMAND_UI(ID_ESCENA_WIREFRAME, OnUpdateEscenaWireframe)
	ON_COMMAND(ID_ESCENA_WIREFRAME, OnEscenaWireframe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEscenaTree message handlers

void CEscenaTree::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	CTreeCtrl::PreSubclassWindow();
	Inicializar();
}

int CEscenaTree::Inicializar()
{
	SetImageList(&m_EscenaTree->imglist,LVSIL_NORMAL);	
	return true;
}

int CEscenaTree::InitEscenaTree()
{
	HINSTANCE hInst=GetModuleHandle("GL10.dll");
	m_EscenaTree=new S_ESCENATREE;	
	m_EscenaTree->ondrag=false;
	CWinApp* pApp=AfxGetApp();
	m_EscenaTree->imglist.Create(16,16,TRUE,4,4);
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_VISTA)));
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_FOLDER)));
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_MATERIAL)));
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_MESH)));
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_MESHGROUP)));
	m_EscenaTree->imglist.Add(LoadIcon(hInst,MAKEINTRESOURCE(IDI_VARIABLE)));
	m_EscenaTree->nodragcursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_NODROP));
	m_EscenaTree->dragcursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_DRAG));
	m_EscenaTree->menu.LoadMenu(IDR_TREE_MENU);
	m_EscenaTree->OnLabelEdit=false;
	return true;
}

void CEscenaTree::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW*	pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	S_TREELPARAM*	lparam=(S_TREELPARAM*)pNMTreeView->itemNew.lParam;
	
	CPoint	point;
	GetCursorPos(&point);
	if (lparam)
	{
		if (lparam->type == ID_ESCENA)
			return;
		if (lparam->type == ID_MESHGROUP)
		{
			if (!((CMeshGroup*)lparam->object)->GetParent())
				return;
		}
		m_EscenaTree->itemdrag=(S_TREELPARAM*)pNMTreeView->itemNew.lParam;
		SetCapture();
		m_EscenaTree->ondrag=true;
	};
	*pResult = 0;
}

void CEscenaTree::OnMouseMove(UINT nFlags, CPoint point) 
{
	TVITEM		pItem;
	HTREEITEM	hItem;
	
	if (m_EscenaTree->ondrag)
	{
		// Esto es usado para el scroll
		POINT	pt;
		GetCursorPos(&pt);
		RECT	rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);
		if (pt.y < rect.top +10)
			SendMessage(WM_VSCROLL,SB_LINEUP);
		if (pt.y > rect.bottom-10)
			SendMessage(WM_VSCROLL,SB_LINEDOWN);

		UINT pint;
		hItem=HitTest(point,&pint);
		pItem.hItem=hItem;
		pItem.mask=TVIF_HANDLE|TVIF_PARAM;
		if (pItem.hItem)
		{
			GetItem(&pItem);
			Expand(hItem,TVE_EXPAND);
			if (pItem.lParam)
			{
				m_EscenaTree->itemdrog=(S_TREELPARAM*)pItem.lParam;
				// comprobar la validez del Drag Drog
				switch (m_EscenaTree->itemdrag->type)
				{
				case ID_VARIABLE:
				case ID_MESH:
				case ID_MESHGROUP:
				case ID_MESHINSTANCE:
					{
						if (m_EscenaTree->itemdrog->type != ID_MESHGROUP)
							hItem=NULL;
						break;
					}
				case ID_MATERIAL:
					{
						if (m_EscenaTree->itemdrog->type != ID_MESH)
							hItem=NULL;
						break;
					}
				}
			}
			else 
				hItem=NULL;

		}
		if (hItem)
			SetCursor(m_EscenaTree->dragcursor);
		else
		{
			SetCursor(m_EscenaTree->nodragcursor);
			m_EscenaTree->itemdrog=NULL;
		}
		SelectDropTarget(hItem);
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void CEscenaTree::OnMButtonUp(UINT nFlags, CPoint point) 
{
	MouseButtonUp();
	CTreeCtrl::OnMButtonUp(nFlags, point);
}

int CEscenaTree::MouseButtonUp()
{
	if (m_EscenaTree->ondrag)
	{
		m_EscenaTree->ondrag=false;
		SelectDropTarget(NULL);
		ReleaseCapture();
		if (!m_EscenaTree->itemdrog)
			return false;
		switch(m_EscenaTree->itemdrog->type)
		{
		case ID_MESHGROUP:
			{
				CMeshGroup* pMG=(CMeshGroup*)m_EscenaTree->itemdrog->object;
				switch(m_EscenaTree->itemdrag->type)
				{
				case ID_MESH:
					{
						pMG->AddMesh((CMeshMat*)m_EscenaTree->itemdrag->object);
						break;
					}
				case ID_VARIABLE:
					{
						pMG->AddVariable((CVariable*)m_EscenaTree->itemdrag->object);
						break;
					}
				}
				break;
			}
		}
	}
	return true;
}

void CEscenaTree::OnLButtonUp(UINT nFlags, CPoint point) 
{
	MouseButtonUp();	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CEscenaTree::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	MouseButtonDown(&point);
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CEscenaTree::OnMButtonDown(UINT nFlags, CPoint point) 
{
	MouseButtonDown(&point);	
	CTreeCtrl::OnMButtonDown(nFlags, point);
}

int CEscenaTree::MouseButtonDown(CPoint *point)
{
	UINT			pint;
	TVITEM			pItem;
	HTREEITEM		hItem=HitTest(*point,&pint);
	SelectItem(hItem);	
	if (!hItem)	
		return true;
	pItem.hItem=hItem;
	pItem.mask=TVIF_HANDLE|TVIF_PARAM;
	GetItem(&pItem);
	m_EscenaTree->itemselect=(S_TREELPARAM*)pItem.lParam;
	return true;
}

void CEscenaTree::OnRButtonDown(UINT nFlags, CPoint point) 
{
	MouseButtonDown(&point);
	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CEscenaTree::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TVITEM			pItem;
	HTREEITEM		hItem=GetSelectedItem();
	S_TREELPARAM*	lparam;

	if (!hItem)	return;
	pItem.hItem=hItem;
	pItem.mask=TVIF_HANDLE|TVIF_PARAM;
	GetItem(&pItem);
	if (!pItem.lParam) return;
	lparam=(S_TREELPARAM*)pItem.lParam;
	CMenu* pPopup = m_EscenaTree->menu.GetSubMenu(lparam->type);
	CPoint point;
	GetCursorPos(&point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this,NULL);
	*pResult = 0;
}

void CEscenaTree::OnEscenaRead3ds() 
{
	TVITEM			pItem;
	HTREEITEM		hItem=GetSelectedItem();
	S_TREELPARAM*	lparam;
	if (!hItem)	return;
	pItem.hItem=hItem;
	pItem.mask=TVIF_HANDLE|TVIF_PARAM;
	GetItem(&pItem);
	if (!pItem.lParam) return;
	lparam=(S_TREELPARAM*)pItem.lParam;
	CEscena* pEscena=(CEscena*)lparam->object;
	pEscena->Read3DS();	
}

void CEscenaTree::OnVariablePropiedades() 
{
	if (!m_EscenaTree->itemselect)
		return;
	CVariable* pVar=(CVariable*)m_EscenaTree->itemselect->object;
	pVar->Change();
}

void CEscenaTree::OnMeshinstanceDelete() 
{
	if (!m_EscenaTree->itemselect)
		return;
	CMeshInstance* pMeshInstance =(CMeshInstance*)m_EscenaTree->itemselect->object;
	pMeshInstance->Delete();
}

void CEscenaTree::OnMesgroupNew() 
{
	if (!m_EscenaTree->itemselect)
		return;
	CMeshGroup* pMG= (CMeshGroup*)m_EscenaTree->itemselect->object;
	pMG->AddMeshGroup();
}

void CEscenaTree::OnMesgroupDelete() 
{
	if (!m_EscenaTree->itemselect)
		return;
	CMeshGroup* pMG= (CMeshGroup*)m_EscenaTree->itemselect->object;
	pMG->Delete();	
}

void CEscenaTree::OnVariableinstanceDelete() 
{
	if(!m_EscenaTree->itemselect)
		return;
	CVariableInstance* pVI =(CVariableInstance*)m_EscenaTree->itemselect->object;
	pVI->Delete();
}

void CEscenaTree::OnEscenaNewvariable() 
{
	CEscena* pE =(CEscena*)m_EscenaTree->itemselect->object;
	pE->NewVar();
}

void CEscenaTree::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CEdit* pedit=GetEditControl();
	pedit->SetLimitText(20);
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = true;
	S_TREELPARAM*	pLParam = (S_TREELPARAM*)pTVDispInfo->item.lParam;
	if (pLParam)
	{
		*pResult = false;
		switch (pLParam->type)
		{
		case ID_ESCENA:
		case ID_MESHINSTANCE:
		case ID_VARIABLEINSTANCE:
			{
				*pResult=true;
				break;
			}
		}
	}
	m_EscenaTree->OnLabelEdit=!(*pResult);
}

void CEscenaTree::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	*pResult = false;
	char* name=pTVDispInfo->item.pszText;
	if (!name)	return;

	if (m_EscenaTree->OnLabelEdit)
	{
		S_TREELPARAM*	pLParam = (S_TREELPARAM*)pTVDispInfo->item.lParam;

		LPVOID ptr=pLParam->object;

		switch (pLParam->type)
		{
		case ID_MATERIAL:
			{
				CMaterial* p=(CMaterial*)ptr;
				p->SetName(name);
				break;
			}
		case ID_MESH:
			{
				CMeshMat* p=(CMeshMat*)ptr;
				p->SetName(name);
				break;
			}
		case ID_VARIABLE:
			{
				CVariable* p=(CVariable*)ptr;
				p->SetName(name);
				break;
			}
		case ID_MESHGROUP:
			{
				CMeshGroup* p=(CMeshGroup*)ptr;
				p->SetName(name);
				break;
			}
			
		}
		*pResult = true;
	}
	m_EscenaTree->OnLabelEdit=false;
}

BOOL CEscenaTree::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			if (m_EscenaTree->OnLabelEdit)
			{
				if (pMsg->wParam ==VK_ESCAPE)
					m_EscenaTree->OnLabelEdit=false;
				switch(pMsg->wParam)
				{
				case VK_RETURN:
				case VK_ESCAPE:
					{
						SetFocus();
						return true;
					}
				}
			}
			if (m_EscenaTree->ondrag)
			{
				switch(pMsg->wParam)
				{
				case VK_ESCAPE:
				case VK_RETURN:
					{
						m_EscenaTree->ondrag=false;
						SelectDropTarget(NULL);
						ReleaseCapture();
						return true;
					}
				}
			}
			break;
		}
	}
	return CTreeCtrl::PreTranslateMessage(pMsg);
}


void CEscenaTree::OnEscenaSave() 
{
	CEscena* pE =(CEscena*)m_EscenaTree->itemselect->object;
	pE->Save();		
}

void CEscenaTree::OnEscenaRead() 
{
	CEscena* pE =(CEscena*)m_EscenaTree->itemselect->object;
	pE->Read();
}

void CEscenaTree::OnVariableinstancePropiedades() 
{
	if(!m_EscenaTree->itemselect)
		return;
	CVariableInstance* pVI =(CVariableInstance*)m_EscenaTree->itemselect->object;
	pVI->Propiedades();		
}

void CEscenaTree::OnUpdateEscenaWireframe(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CEscenaTree::OnEscenaWireframe() 
{
	CEscena* pE =(CEscena*)m_EscenaTree->itemselect->object;
	pE->SetWireFrame(!pE->IsWireFrame());
}
