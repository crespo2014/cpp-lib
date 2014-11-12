#if !defined(AFX_VIEWTRAINING_H__ECA8EB61_CB81_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWTRAINING_H__ECA8EB61_CB81_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTraining.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CViewTraining dialog

class CApp;

class CViewTraining : public CDialog
{
// Construction
public:
	CApp* m_pApp;
	bool SetApp(CApp* pAppt);
	CViewTraining(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewTraining)
//	enum { IDD = IDD_TRAINING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTraining)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewTraining)
	afx_msg void OnCliniciandisplay();
    afx_msg void OnSaveandExit();
	afx_msg void OnChangeparameters();
	afx_msg void OnStarttraining();
	afx_msg void OnCancelsession();
	afx_msg void OnDestroy();
	afx_msg void OnTrainingoffline();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTRAINING_H__ECA8EB61_CB81_11D4_9126_0000E83D722B__INCLUDED_)
