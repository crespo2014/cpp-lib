// FileFilterDlg.h : header file
//

#if !defined(AFX_FILEFILTERDLG_H__4CB9D67C_2AA5_40DD_98CA_30B343747332__INCLUDED_)
#define AFX_FILEFILTERDLG_H__4CB9D67C_2AA5_40DD_98CA_30B343747332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lisa200\Lisa2000Filter.h"

/////////////////////////////////////////////////////////////////////////////
// CFileFilterDlg dialog

class CFileFilterDlg : public CDialog
{
// Construction
public:
	DWORD ProcessFilter();
	DWORD PrintHexValue(BYTE value,char* str);
	DWORD CloseInFile();
	DWORD Initialize();
	DWORD CloseOutFile();
	CFileFilterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileFilterDlg)
	enum { IDD = IDD_FILEFILTER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CLisa2000Filter LisaFilter;
	// Generated message map functions
	//{{AFX_MSG(CFileFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDoit();
	afx_msg void OnInfile();
	afx_msg void OnOutfile();
	afx_msg void OnEnableCommand();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HANDLE m_hOutFile;
	HANDLE m_hInFile;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFILTERDLG_H__4CB9D67C_2AA5_40DD_98CA_30B343747332__INCLUDED_)
