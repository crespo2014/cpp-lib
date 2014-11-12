// puertoDlg.h : header file
//

#if !defined(AFX_PUERTODLG_H__B615690C_7363_11D4_8CE5_00D0093847B4__INCLUDED_)
#define AFX_PUERTODLG_H__B615690C_7363_11D4_8CE5_00D0093847B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\interfaces\IServoDriver.h"
#include "..\interfaces\interfazdef.h"
#include "..\interfaces\iservo.h"
#include "..\interfaces\IServoSV900CDriver.h"

/////////////////////////////////////////////////////////////////////////////
// CPuertoDlg dialog

class CPuertoDlg : public CDialog
{
// Construction
public:
	IServoSV900CDriver Driver;
	IServo* lpServo;

	//CDeviceRed Puerto;
	CPuertoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPuertoDlg)
	enum { IDD = IDD_PUERTO_DIALOG };
	CString	m_estado;
	CString	m_curvas;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPuertoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	DWORD CantRead;
	BYTE Read[100];

	// Generated message map functions
	//{{AFX_MSG(CPuertoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUERTODLG_H__B615690C_7363_11D4_8CE5_00D0093847B4__INCLUDED_)
