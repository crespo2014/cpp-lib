#if !defined(AFX_TGRAFICA_H__C7DF2674_2583_453D_8A10_54226856FA48__INCLUDED_)
#define AFX_TGRAFICA_H__C7DF2674_2583_453D_8A10_54226856FA48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TGrafica.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TGrafica window

class TGrafica : public CStatic
{
// Construction
public:
	TGrafica();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TGrafica)
	//}}AFX_VIRTUAL

// Implementation
public:
	float x,y,z,escala;

	virtual ~TGrafica();

	// Generated message map functions
protected:
	//{{AFX_MSG(TGrafica)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TGRAFICA_H__C7DF2674_2583_453D_8A10_54226856FA48__INCLUDED_)
