// ProyectoView.h : interface of the CProyectoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROYECTOVIEW_H__DB3E40E8_9558_4B95_AD77_D6C736D6DC48__INCLUDED_)
#define AFX_PROYECTOVIEW_H__DB3E40E8_9558_4B95_AD77_D6C736D6DC48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProyectoView : public CView
{
protected: // create from serialization only
	CProyectoView();
	DECLARE_DYNCREATE(CProyectoView)

// Attributes
public:
	CProyectoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProyectoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Save();
	BOOL CheckChanges();
	virtual ~CProyectoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProyectoView)
	afx_msg void OnConfigurarDimensiones();
	afx_msg void OnConfigurarReceptor();
	afx_msg void OnUpdateConfigurarReceptor(CCmdUI* pCmdUI);
	afx_msg void OnConfigurarSuperficie();
	afx_msg void OnUpdateConfigurarSuperficie(CCmdUI* pCmdUI);
	afx_msg void OnConfigurarTransmisor();
	afx_msg void OnUpdateConfigurarTransmisor(CCmdUI* pCmdUI);
	afx_msg void OnCerrar();
	afx_msg void OnUpdateCerrar(CCmdUI* pCmdUI);
	afx_msg void OnGuardar();
	afx_msg void OnUpdateGuardar(CCmdUI* pCmdUI);
	afx_msg void OnNuevo();
	afx_msg void OnUpdateNuevo(CCmdUI* pCmdUI);
	afx_msg void OnSimulacion();
	afx_msg void OnUpdateSimulacion(CCmdUI* pCmdUI);
	afx_msg void OnAbrir();
	afx_msg void OnUpdateAbrir(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConfigurarDimensiones(CCmdUI* pCmdUI);
	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProyectoView.cpp
inline CProyectoDoc* CProyectoView::GetDocument()
   { return (CProyectoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROYECTOVIEW_H__DB3E40E8_9558_4B95_AD77_D6C736D6DC48__INCLUDED_)
