// dbQueryDlg.h : header file
//

#if !defined(AFX_DBQUERYDLG_H__A81D58EC_2AFC_4A9C_98F6_816853A966BF__INCLUDED_)
#define AFX_DBQUERYDLG_H__A81D58EC_2AFC_4A9C_98F6_816853A966BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "memarray.h"
#include "grid.h"

/////////////////////////////////////////////////////////////////////////////
// CDbQueryDlg dialog

class CDbQueryDlg : public CDialog
{
// Construction
public:
	CDbQueryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDbQueryDlg)
	enum { IDD = IDD_DBQUERY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbQueryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDbQueryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConectar();
	afx_msg void OnEjecutar();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ICommand*	m_lpICommand;
	CMemArray	m_MemArray;
	CGrid		m_Grid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBQUERYDLG_H__A81D58EC_2AFC_4A9C_98F6_816853A966BF__INCLUDED_)
