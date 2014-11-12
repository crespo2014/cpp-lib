// TestDLLsDlg.h : header file
//

#if !defined(AFX_TESTDLLSDLG_H__7964E0AE_1F3D_4B99_BE92_5610A01F60D8__INCLUDED_)
#define AFX_TESTDLLSDLG_H__7964E0AE_1F3D_4B99_BE92_5610A01F60D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "servo\svdef.h"
#include "iserialport.h"


/////////////////////////////////////////////////////////////////////////////
// CTestDLLsDlg dialog

class CTestDLLsDlg : public CDialog
{
// Construction
public:
	CTestDLLsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDLLsDlg)
	enum { IDD = IDD_TESTDLLS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDLLsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDLLsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSerialport();
	afx_msg void OnDestroy();
	afx_msg void OnSv300();
	afx_msg void OnAttach();
	afx_msg void OnRc();
	afx_msg void OnButton1();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ISerialPort*	m_ISerialPort;
	IServo*			m_IServo;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLSDLG_H__7964E0AE_1F3D_4B99_BE92_5610A01F60D8__INCLUDED_)
