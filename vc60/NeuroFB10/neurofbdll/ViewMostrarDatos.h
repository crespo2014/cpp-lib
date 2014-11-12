#if !defined(AFX_VIEWMOSTRARDATOS_H__A6527B85_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWMOSTRARDATOS_H__A6527B85_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewMostrarDatos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewMostrarDatos dialog
#include "resource.h"
#include "treepaciente.h"

class CViewMostrarDatos : public CDialog
{
// Construction
public:
	void* pAppt;
	bool RefrescarDatos(long sesion, long condicion);
	long* cantidad_condiciones_por_sesion;
	long cantidad_sesiones;
	CDaoRecordset* pRs;
	CDaoRecordset* pRc;
	CDaoRecordset* pRm;

	bool Mostrar(void *pApp);
	CViewMostrarDatos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewMostrarDatos)
//	enum { IDD = IDD_MOSTRARDATOS };
	CTreePaciente	m_tree_paciente;
	long	m_Af_I_Eeg;
	long	m_Af_R_Eeg;
	long	m_Bf_I_Eeg;
	long	m_Bf_R_Eeg;
	long	m_Crit_Comp_Burst;
	long	m_Duracion_Cond;
	double	m_Nivel_I_Eeg;
	double	m_Nivel_I_Musculo;
	double	m_Nivel_R_Eeg;
	COleDateTime	m_Fecha_Sesion;
	CString	m_Reporte_Sesion;
	long	m_Temperatura;
	long	m_Tiempo_Conteo_Burst;
	long	m_Af_Muscle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewMostrarDatos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewMostrarDatos)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWMOSTRARDATOS_H__A6527B85_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
