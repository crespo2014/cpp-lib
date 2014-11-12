#if !defined(AFX_TOVAPARAMS_H__E9D24685_B876_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_TOVAPARAMS_H__E9D24685_B876_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TovaParams.h : header file
//

////////////////////////////////////////////////////////////////////////////
// CTovaParams dialog

typedef struct S_TovaParams
{
	DWORD m_PresTime;
	DWORD m_InterTime;
	DWORD m_Cant;
} TovaParams;



class CTovaParams : public CDialog
{
// Construction
public:
	TovaParams m_TovaParams;
	CTovaParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTovaParams)
	enum { IDD = IDD_G3D_DIALOG6 };
	DWORD	m_TBO;
	DWORD	m_TP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTovaParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTovaParams)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOVAPARAMS_H__E9D24685_B876_11D3_A036_0000E8DE4B3B__INCLUDED_)
