// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__FEC7B9AB_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_CHILDVIEW_H__FEC7B9AB_BFA8_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

#include "..\neurofbdll\app.h"

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
    CApp App; 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool entrada;
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnOptionsGraphics();
	afx_msg void OnUpdateOptionsGraphics(CCmdUI* pCmdUI);
	afx_msg void OnOptionsPrintsession();
	afx_msg void OnUpdateOptionsPrintsession(CCmdUI* pCmdUI);
	afx_msg void OnPatientNewpatient();
	afx_msg void OnUpdatePatientNewpatient(CCmdUI* pCmdUI);
	afx_msg void OnPatientPatientoptions();
	afx_msg void OnUpdatePatientPatientoptions(CCmdUI* pCmdUI);
	afx_msg void OnPatientShowpatientdata();
	afx_msg void OnUpdatePatientShowpatientdata(CCmdUI* pCmdUI);
	afx_msg void OnSessionNewsesion();
	afx_msg void OnUpdateSessionNewsesion(CCmdUI* pCmdUI);
	afx_msg void OnSessionSessionsettings();
	afx_msg void OnUpdateSessionSessionsettings(CCmdUI* pCmdUI);
	afx_msg void OnSessionShowallsessionsreports();
	afx_msg void OnUpdateSessionShowallsessionsreports(CCmdUI* pCmdUI);
	afx_msg void OnSessionStartsession();
	afx_msg void OnUpdateSessionStartsession(CCmdUI* pCmdUI);
	afx_msg void OnCHANGEPASSWORD();
	afx_msg void OnUpdateCHANGEPASSWORD(CCmdUI* pCmdUI);
	afx_msg void OnOptionsSerialportconfiguration();
	afx_msg void OnUpdateOptionsSerialportconfiguration(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__FEC7B9AB_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
