#if !defined(AFX_VIEWREGISTRO_H__A6527B83_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWREGISTRO_H__A6527B83_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRegistro.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewRegistro dialog
#include "resource.h"


class CViewRegistro : public CDialog
{
// Construction
public:
	
	bool ChekData();
	bool Mostrar();
	CViewRegistro(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewRegistro)
//	enum { IDD = IDD_REGISTRO };
	CString	m_Apellido_Paciente;
	CString	m_Diagnostico;
	CString	m_Direccion;
	COleDateTime	m_Fecha_Nacimiento;
	CString	m_Medicacion_Actual;
	long	m_No_Paciente;
	CString	m_Nombre_Paciente;
	CString	m_Telefono;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRegistro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewRegistro)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWREGISTRO_H__A6527B83_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
