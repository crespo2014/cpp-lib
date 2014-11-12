//{{AFX_INCLUDES()
#include "msflexgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_T_S_DLG_H__3BC47350_FC1E_4FCD_BCB2_E17F4F925C96__INCLUDED_)
#define AFX_T_S_DLG_H__3BC47350_FC1E_4FCD_BCB2_E17F4F925C96__INCLUDED_

#include "tcanal.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_S_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_S_DLG dialog

class T_S_DLG : public CDialog
{
// Construction
public:
	TCanal* lpCanal;
	T_S_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_S_DLG)
	enum { IDD = IDD_SIMULACION };
	CMSFlexGrid	m_fg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_S_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_S_DLG)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_S_DLG_H__3BC47350_FC1E_4FCD_BCB2_E17F4F925C96__INCLUDED_)
