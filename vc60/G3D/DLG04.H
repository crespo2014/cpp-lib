#if !defined(AFX_DLG04_H__2CFDA623_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_DLG04_H__2CFDA623_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "Video02.h"	// Added by ClassView
#include "TovaParams.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg04.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg04 dialog

class CDlg04 : public CDialog
{
// Construction
public:
	UINT m_TimerID;
	TovaParams m_TovaParams;
	CTovaParams m_TovaDlg;
	CVideo02 m_Video;
	CDlg04(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg04)
	enum { IDD = IDD_G3D_DIALOG4 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg04)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg04)
	virtual BOOL OnInitDialog();
	afx_msg void OnG3dButton5();
	afx_msg void OnG3dButton6();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG04_H__2CFDA623_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
