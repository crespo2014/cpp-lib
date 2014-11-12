#if !defined(AFX_GAMDLG_H__2CFDA621_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GAMDLG_H__2CFDA621_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "Dlg03.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GamDlg.h : header file
//

#include "resource.h"
#include "Dlg04.h"	// Added by ClassView
#include "Dlg05.h"	// Added by ClassView
#include "Video01.h"	// Added by ClassView
#include "Level1Dlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CGamDlg dialog

class AFX_EXT_CLASS CGamDlg : public CDialog
{
// Construction
public:
	CLevel1Dlg m_Level1Dlg;
	CVideo01 m_Video;
	CDlg05 m_Dlg05;
	CDlg04 m_Dlg04;
	CDlg03 m_Dlg03;
	CGamDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGamDlg)
	enum { IDD = IDD_G3D_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGamDlg)
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton2();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMDLG_H__2CFDA621_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
