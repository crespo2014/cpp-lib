// FileFilterDlg.h : header file
//

#if !defined(AFX_FILEFILTERDLG_H__69D2F3C4_B30C_47E4_BA6C_550DE65B6340__INCLUDED_)
#define AFX_FILEFILTERDLG_H__69D2F3C4_B30C_47E4_BA6C_550DE65B6340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileFilterDlg dialog

class CFileFilterDlg : public CDialog
{
private:
	HANDLE	m_hFile;
	FILE*	m_File;	
// Construction
public:
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

	// Generated message map functions
	//{{AFX_MSG(CFileFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenFile();
	afx_msg void OnPortMonFilter();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFILTERDLG_H__69D2F3C4_B30C_47E4_BA6C_550DE65B6340__INCLUDED_)
