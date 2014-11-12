#if !defined(AFX_T_G_DLG_H__E40325BB_0465_4C2C_B722_4C428B624077__INCLUDED_)
#define AFX_T_G_DLG_H__E40325BB_0465_4C2C_B722_4C428B624077__INCLUDED_

#include "Tgrafica.h"
#include "tcanal.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_G_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_G_DLG dialog

class T_G_DLG : public CDialog
{
// Construction
public:
	TCanal* lpCanal;
	BOOL Validar();
	T_G_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_G_DLG)
	enum { IDD = IDD_GRAFICO };
	TGrafica	m_grafico;
	float	m_x;
	float	m_y;
	float	m_z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_G_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_G_DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnAplicar();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_G_DLG_H__E40325BB_0465_4C2C_B722_4C428B624077__INCLUDED_)
