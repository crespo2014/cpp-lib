#if !defined(AFX_PAGE_H__C8890161_BB65_11D4_8635_00D0093D4380__INCLUDED_)
#define AFX_PAGE_H__C8890161_BB65_11D4_8635_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Page.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage window

typedef struct
{
	WORD	DCMX;  // Area cliente dimensiones
	WORD	DCMY;  //

}S_DRAWINFO;
class CPage : public CWnd
{
// Construction
public:
	CPage();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPage();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE_H__C8890161_BB65_11D4_8635_00D0093D4380__INCLUDED_)
