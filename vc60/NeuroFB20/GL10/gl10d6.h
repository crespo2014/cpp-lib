 #if !defined(AFX_GL10D6_H__1529AB02_FD11_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10D6_H__1529AB02_FD11_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10d6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVariableInstanceDlg dialog

#include "resource.h"
#include "gl10s.h"

class CVariableInstanceDlg : public CDialog
{
// Construction
public:
	void UpdateButton();
	BOOL m_OnRotar;
	CVariableInstance* m_Object;
	CVariableInstanceDlg(CWnd* pParent=NULL);

// Dialog Data
	//{{AFX_DATA(CVariableInstanceDlg)
	enum { IDD = IDD_VAR_INST_DLG };
	float	m_minimo;
	float	m_pendiente;
	float	m_posx;
	float	m_posy;
	float	m_posz;
	float	m_rotcenx;
	float	m_rotceny;
	float	m_rotcenz;
	float	m_rotvecx;
	float	m_rotvecy;
	float	m_rotvecz;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVariableInstanceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVariableInstanceDlg)
	afx_msg void OnModificar();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10D6_H__1529AB02_FD11_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
