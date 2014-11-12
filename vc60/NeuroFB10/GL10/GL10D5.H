 #if !defined(AFX_GL10D5_H__9FE5EC07_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10D5_H__9FE5EC07_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10d5.h : header file
//

#include "resource.h"
#include "gl10s.h"
/////////////////////////////////////////////////////////////////////////////
// CVariableDlg dialog

class CVariableDlg : public CDialog
{
// Construction
public:
	float m_factor;
	CVariable* m_var;
	CVariableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVariableDlg)
	enum { IDD = IDD_VARIABLE };
	float	m_max;
	int		m_pos;
	float	m_valor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVariableDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKillfocusMax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10D5_H__9FE5EC07_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
