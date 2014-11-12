#if !defined(AFX_DLG03_H__2CFDA622_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_DLG03_H__2CFDA622_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "resource.h"
#include "level_1.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg03.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg03 dialog

class CDlg03 : public CDialog
{
// Construction
public:
	CVideoLevel1 m_GLGame;
	CDlg03(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg03)
	enum { IDD = IDD_G3D_DIALOG3 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg03)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg03)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG03_H__2CFDA622_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
