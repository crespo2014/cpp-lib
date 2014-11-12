 #if !defined(AFX_GL10C7_H__5567D3A1_F374_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C7_H__5567D3A1_F374_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10c7.h : header file
//

#include "gl10s.h"
/////////////////////////////////////////////////////////////////////////////
// CEscenaTree window
typedef struct
{
	BOOL			ondrag;
	S_TREELPARAM*	itemdrag;
	S_TREELPARAM*	itemdrog;
	S_TREELPARAM*	itemselect;
	CImageList		imglist;
	HCURSOR			nodragcursor;
	HCURSOR			dragcursor;
	CMenu			menu;
	BOOL			OnLabelEdit;
}S_ESCENATREE;

class AFX_EXT_CLASS CEscenaTree : public CTreeCtrl
{
// Construction
public:
	CEscenaTree();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEscenaTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int MouseButtonDown(CPoint* point);
	int MouseButtonUp();
	S_ESCENATREE* m_EscenaTree;
	int InitEscenaTree();
	int Inicializar();
	virtual ~CEscenaTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEscenaTree)
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEscenaRead3ds();
	afx_msg void OnVariablePropiedades();
	afx_msg void OnMeshinstanceDelete();
	afx_msg void OnMesgroupNew();
	afx_msg void OnMesgroupDelete();
	afx_msg void OnVariableinstanceDelete();
	afx_msg void OnEscenaNewvariable();
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEscenaSave();
	afx_msg void OnEscenaRead();
	afx_msg void OnVariableinstancePropiedades();
	afx_msg void OnUpdateEscenaWireframe(CCmdUI* pCmdUI);
	afx_msg void OnEscenaWireframe();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10C7_H__5567D3A1_F374_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
