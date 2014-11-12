#if !defined(AFX_DIALOG01_H__C3B643C1_6FED_11D2_8635_00D0093D4380__INCLUDED_)
#define AFX_DIALOG01_H__C3B643C1_6FED_11D2_8635_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dialog01.h : header file
//
#include "ReGrid.h"
/////////////////////////////////////////////////////////////////////////////
// CDialog01 dialog

class CDialog01 : public CDialog
{
// Construction
public:
	CReGrid	m_Grid;
	CDaoDatabase	Database;
	CDaoRecordset*	Recordset;
	CFont	Font;
	LOGFONT lf;
	CDialog01(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialog01)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialog01)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialog01)
	afx_msg void OnPrint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG01_H__C3B643C1_6FED_11D2_8635_00D0093D4380__INCLUDED_)
