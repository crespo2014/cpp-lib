#if !defined(AFX_VIDEO01_H__524C78A1_B554_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_VIDEO01_H__524C78A1_B554_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "Glfont.h"	// Added by ClassView
#include "Video.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Video01.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideo01 window

class CVideo01 : public CVideo
{
// Construction
public:
	CVideo01();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideo01)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CGLFont m_Font1;
	virtual int RenderScene();
	virtual int InitView(BOOL pOnSize);
	int m_angulo;
	virtual ~CVideo01();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideo01)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEO01_H__524C78A1_B554_11D3_A036_0000E8DE4B3B__INCLUDED_)
