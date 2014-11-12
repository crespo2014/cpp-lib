#if !defined(AFX_T_CR_DLG_H__07481FB9_E781_4D10_94FB_ECB919B8614D__INCLUDED_)
#define AFX_T_CR_DLG_H__07481FB9_E781_4D10_94FB_ECB919B8614D__INCLUDED_

#include "tcanal.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_CR_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_CR_DLG dialog

class T_CR_DLG : public CDialog
{
// Construction
public:
	BOOL Validar();
	void FromCanal();
	void ToCanal();
	TCanal* lpCanal;
	int Cantidad;
	int Activo;
	T_CR_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_CR_DLG)
	enum { IDD = IDD_CONFIG_CR };
	CButton	m_siguiente;
	CButton	m_anterior;
	float	m_ac;
	float	m_as;
	float	m_cv;
	float	m_vox;
	float	m_voy;
	float	m_voz;
	float	m_vpx;
	float	m_vpy;
	float	m_vpz;
	CString	m_pos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_CR_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_CR_DLG)
	virtual BOOL OnInitDialog();
	afx_msg void OnGraficar();
	afx_msg void OnAnterior();
	afx_msg void OnAdicionar();
	afx_msg void OnSiguiente();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_CR_DLG_H__07481FB9_E781_4D10_94FB_ECB919B8614D__INCLUDED_)
