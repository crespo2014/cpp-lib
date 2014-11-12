#if !defined(AFX_DB11D2_H__4CA87C24_0E80_11D4_BC42_0000E8DE4B3B__INCLUDED_)
#define AFX_DB11D2_H__4CA87C24_0E80_11D4_BC42_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// db11d2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSQLDlg dialog

#include "resource.h"

class CSQLDlg : public CDialog
{
// Construction
public:
	CSQLDlg(CWnd* pParent = NULL);   // standard constructor
	char	sqlstring[1024];

// Dialog Data
	//{{AFX_DATA(CSQLDlg)
	enum { IDD = IDD_SQL_DLG };
	CComboBox	m_TSindicato;
	CComboBox	m_TProvincia;
	CComboBox	m_TDepartamento;
	CComboBox	m_tema;
	CComboBox	m_Sindicato;
	CComboBox	m_Organismo;
	CComboBox	m_Ordenar;
	CEdit	m_Numero;
	CEdit	m_Nombre;
	CComboBox	m_Municipio;
	CDateTimeCtrl	m_Hasta;
	CDateTimeCtrl	m_Desde;
	CComboBox	m_clasificacion;
	CEdit	m_2apellido;
	CEdit	m_1apellido;
	BOOL	m_On1apellido;
	BOOL	m_On2apellido;
	BOOL	m_OnClasificacion;
	BOOL	m_OnDesde;
	BOOL	m_OnHasta;
	BOOL	m_OnMunicipio;
	BOOL	m_OnNombre;
	BOOL	m_OnNumero;
	BOOL	m_OnOrdenar;
	BOOL	m_OnOrganismo;
	BOOL	m_OnRespuesta;
	BOOL	m_OnSindicato;
	BOOL	m_OnTDepartamento;
	BOOL	m_OnTema;
	BOOL	m_OnTProvincia;
	BOOL	m_OnTSindicato;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSQLDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DB11D2_H__4CA87C24_0E80_11D4_BC42_0000E8DE4B3B__INCLUDED_)
