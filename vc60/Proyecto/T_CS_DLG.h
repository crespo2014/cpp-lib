#if !defined(AFX_T_CS_DLG_H__2F5AB95D_B5AC_4392_9A40_BF040A3BA1F4__INCLUDED_)
#define AFX_T_CS_DLG_H__2F5AB95D_B5AC_4392_9A40_BF040A3BA1F4__INCLUDED_

#include "tcanal.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_CS_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_CS_DLG dialog

class T_CS_DLG : public CDialog
{
// Construction
public:
	BYTE Cantidad;
	BYTE Activo;
	TCanal* lpCanal;
	BOOL Validar();
	void FromCanal();
	void ToCanal();
	T_CS_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_CS_DLG)
	enum { IDD = IDD_CONFIG_SUP };
	CButton	m_siguiente;
	CButton	m_anterior;
	CString	m_pos;
	float	m_vox;
	float	m_voy;
	float	m_voz;
	float	m_vpx;
	float	m_vpy;
	float	m_vpz;
	float	m_cr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_CS_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_CS_DLG)
	virtual void OnOK();
	afx_msg void OnSGraficar();
	afx_msg void OnSAnterior();
	afx_msg void OnSAdiconar();
	virtual void OnCancel();
	afx_msg void OnSSiguiente();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_CS_DLG_H__2F5AB95D_B5AC_4392_9A40_BF040A3BA1F4__INCLUDED_)
