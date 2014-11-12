#if !defined(AFX_T_CT_DLG_H__89B60F20_A678_45BE_94B1_2C08799745B8__INCLUDED_)
#define AFX_T_CT_DLG_H__89B60F20_A678_45BE_94B1_2C08799745B8__INCLUDED_

#include "tcanal.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// T_CT_DLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// T_CT_DLG dialog

class T_CT_DLG : public CDialog
{
// Construction
public:
	void ToCanal();
	void FromCanal();
	BOOL Validar();
	BYTE Cantidad;
	BYTE Activo;
	TCanal* lpCanal;
	T_CT_DLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(T_CT_DLG)
	enum { IDD = IDD_CONFIG_CT };
	CButton	m_siguiente;
	CButton	m_anterior;
	float	m_voz;
	float	m_vox;
	float	m_voy;
	float	m_vpx;
	float	m_vpy;
	float	m_vpz;
	float	m_perrad;
	float	m_potrad;
	CString	m_pos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(T_CT_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(T_CT_DLG)
	afx_msg void OnTGraficar();
	afx_msg void OnTAnterior();
	virtual void OnOK();
	afx_msg void OnTAdicionar();
	virtual void OnCancel();
	afx_msg void OnTSiguiente();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T_CT_DLG_H__89B60F20_A678_45BE_94B1_2C08799745B8__INCLUDED_)
