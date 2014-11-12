#if !defined(AFX_VIEWCONFIGURARSESION_H__A6527B87_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWCONFIGURARSESION_H__A6527B87_BFBB_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewConfigurarSesion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewConfigurarSesion dialog
#include "resource.h"
#include "msflexgrid.h"
#define ADICIONAR 0
#define ACTUALIZAR 1

class CViewConfigurarSesion : public CDialog
{
// Construction
public:
	bool RefrescarParametros();
	bool PonerNombres(CMSFlexGrid* pGrid);
	bool Mostrar(void *pApp);
	CViewConfigurarSesion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewConfigurarSesion)
//	enum { IDD = IDD_CONFIGURARSESION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewConfigurarSesion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewConfigurarSesion)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnUpdate();
	afx_msg void OnClickRejilla();
	afx_msg void OnDblClickRejilla();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCONFIGURARSESION_H__A6527B87_BFBB_11D4_9126_0000E83D722B__INCLUDED_)
