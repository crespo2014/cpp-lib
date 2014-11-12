// VLClient1View.h : interface of the CVLClient1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VLCLIENT1VIEW_H__B1D8C12E_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_VLCLIENT1VIEW_H__B1D8C12E_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_
#define WM_SHOW_USERS WM_USER+5
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVLClient1CntrItem;

class CVLClient1View : public CFormView
{
protected: // create from serialization only
	CVLClient1View();
	DECLARE_DYNCREATE(CVLClient1View)

public:
	//{{AFX_DATA(CVLClient1View)
	enum { IDD = IDD_VLCLIENT1_FORM };
	CButton	m_GLButton;
	int		m_cant;
	int		m_lines;
	CString	m_msg;
	CString	m_nick;
	CString	m_public;
	double	m_XPos;
	double	m_ZPos;
	BYTE	m_Value;
	//PVOID m_Tablero[100];
    //BYTE m_Tablero_Count;
	//}}AFX_DATA

// Attributes
public:
	CVLClient1Doc* GetDocument();
	// m_pSelection holds the selection to the current CVLClient1CntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CVLClient1CntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CVLClient1CntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLClient1View)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	//PVOID m_Tablero[100];
	//BYTE m_Tablero_Count;
			
	CRect* rect;
	bool visualiza;
	virtual ~CVLClient1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVLClient1View)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnConect();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRequestChat();
	afx_msg void OnDblclkUsersList();
	afx_msg void OnSendPublic();
	afx_msg void OnFinishChat();
	afx_msg void OnFinishVideo();
	afx_msg void OnGetFicha();
	afx_msg void OnSimulation();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT OnShowUsers(WPARAM wParam,LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VLClient1View.cpp
inline CVLClient1Doc* CVLClient1View::GetDocument()
   { return (CVLClient1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLCLIENT1VIEW_H__B1D8C12E_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
