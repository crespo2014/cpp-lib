#if !defined(AFX_TREEPACIENTE_H__D7CD45C2_C05E_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_TREEPACIENTE_H__D7CD45C2_C05E_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreePaciente.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreePaciente window

class CTreePaciente : public CTreeCtrl
{
// Construction
public:
	CTreePaciente();

// Attributes
public:

	HTREEITEM Paciente;
	TV_INSERTSTRUCT tvstruct;
	
	CImageList* pImageList;
	CBitmap bitmap;
    CBitmap bitmap1;
	CBitmap bitmap2;
	CBitmap bitmap3;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreePaciente)
	//}}AFX_VIRTUAL

// Implementation
public:
	bool PonerDatos();
	bool GetSeleccion();
	long m_condicion_sel;
	long m_sesion_sel;
	bool InitTree();
	bool PintarTree(long sesiones, long* condiciones, void *pApp, void *pMostrar);
	virtual ~CTreePaciente();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreePaciente)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEPACIENTE_H__D7CD45C2_C05E_11D4_9126_0000E83D722B__INCLUDED_)
