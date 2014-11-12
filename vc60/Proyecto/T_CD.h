#if !defined(AFX_T_CD_H__618D12C5_5D81_446D_86B2_B68DBCFD39DA__INCLUDED_)
#define AFX_T_CD_H__618D12C5_5D81_446D_86B2_B68DBCFD39DA__INCLUDED_

#include "tgrafica.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_CD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_CD dialog

class T_CD : public CDialog
{
// Construction
public:
	T_CD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_CD)
	enum { IDD = IDD_CD };
	float	m_altura;
	float	m_ancho;
	float	m_largo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_CD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_CD)
	afx_msg void OnAceptar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_CD_H__618D12C5_5D81_446D_86B2_B68DBCFD39DA__INCLUDED_)
