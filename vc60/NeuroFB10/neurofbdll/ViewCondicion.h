#if !defined(AFX_VIEWCONDICION_H__A6527B88_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWCONDICION_H__A6527B88_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewCondicion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewCondicion dialog
#include "resource.h"

class CViewCondicion : public CDialog
{
// Construction
public:
	int m_task;
	long m_Af_I_Eeg;
    long m_Af_R_Eeg;
	long m_Bf_I_Eeg;
	long m_Bf_R_Eeg;
	long m_Af_Musculo;

	bool GetAppPointer(void *pApp, int task);
	CViewCondicion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewCondicion)
//	enum { IDD = IDD_CONDICION };
	long	m_Crit_Comp_Burst;
	long	m_Duracion_Cond;
	double	m_Nivel_I_Eeg;
	double	m_Nivel_I_Musculo;
	double	m_Nivel_R_Eeg;
	long	m_Temperatura;
	long	m_Tiempo_Conteo_Burst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewCondicion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewCondicion)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCONDICION_H__A6527B88_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
