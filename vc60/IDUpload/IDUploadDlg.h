// IDUploadDlg.h : header file
//

#if !defined(AFX_IDUPLOADDLG_H__5A0DBE0F_2170_4FE8_BE4F_2383CFCB58CB__INCLUDED_)
#define AFX_IDUPLOADDLG_H__5A0DBE0F_2170_4FE8_BE4F_2383CFCB58CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIDUploadDlg dialog

class CIDUploadDlg : public CDialog
{
// Construction
public:
	CIDUploadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIDUploadDlg)
	enum { IDD = IDD_IDUPLOAD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDUploadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIDUploadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdminLook();
	afx_msg void OnUpload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDUPLOADDLG_H__5A0DBE0F_2170_4FE8_BE4F_2383CFCB58CB__INCLUDED_)
