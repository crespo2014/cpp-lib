// AsmFilterDlg.h : header file
//

#if !defined(AFX_ASMFILTERDLG_H__F9E7A5E3_5A4B_42E9_A5B7_4707484D387F__INCLUDED_)
#define AFX_ASMFILTERDLG_H__F9E7A5E3_5A4B_42E9_A5B7_4707484D387F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAsmFilterDlg dialog

class CAsmFilterDlg : public CDialog
{
// Construction
public:
	CAsmFilterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAsmFilterDlg)
	enum { IDD = IDD_ASMFILTER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsmFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAsmFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDoIt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASMFILTERDLG_H__F9E7A5E3_5A4B_42E9_A5B7_4707484D387F__INCLUDED_)
