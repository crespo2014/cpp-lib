#if !defined(AFX_T_MSG_DLG_H__74E9E6E1_FEE7_445C_9D4B_43C6D16E676C__INCLUDED_)
#define AFX_T_MSG_DLG_H__74E9E6E1_FEE7_445C_9D4B_43C6D16E676C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_MSG_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_MSG_DLG dialog

class T_MSG_DLG : public CDialog
{
// Construction
public:
	T_MSG_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_MSG_DLG)
	enum { IDD = IDD_MSG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_MSG_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_MSG_DLG)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_MSG_DLG_H__74E9E6E1_FEE7_445C_9D4B_43C6D16E676C__INCLUDED_)
