#if !defined(AFX_VIEWBUSCARPACIENTE_H__12510BA9_6469_11D1_BC4C_0000E8DE4B3B__INCLUDED_)
#define AFX_VIEWBUSCARPACIENTE_H__12510BA9_6469_11D1_BC4C_0000E8DE4B3B__INCLUDED_
#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewBuscarPaciente.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewBuscarPaciente dialog

typedef struct data
{
	long valor;
	CString name;
}DATA;

class CViewBuscarPaciente : public CDialog
{
// Construction
public:
		void RefrescarPacientes();
	CDaoRecordset* pRs;
	CDaoRecordset* pRsbackup;
	DATA paciente_data;
	void* pAppt;
	bool Mostrar(void* pApp);
	CViewBuscarPaciente(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewBuscarPaciente)
//	enum { IDD = IDD_BUSCARPACIENTE };
	int		m_opcion;
	long	m_id;
	CString	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewBuscarPaciente)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewBuscarPaciente)
	afx_msg void OnBuscarPaciente();
	afx_msg void OnBorraPaciente();
	afx_msg void OnClickMsflexgrid1();
	afx_msg void OnDestroy();
	afx_msg void OnCargaPaciente();
	afx_msg void OnActualizarPaciente();
	afx_msg void OnExportaPaciente();
	afx_msg void OnImportaPaciente();
	virtual BOOL OnInitDialog();
	afx_msg void OnTodos();
	afx_msg void OnNombre();
	afx_msg void OnBuscaTodos();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWBUSCARPACIENTE_H__12510BA9_6469_11D1_BC4C_0000E8DE4B3B__INCLUDED_)
