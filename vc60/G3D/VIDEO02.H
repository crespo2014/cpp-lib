#if !defined(AFX_VIDEO02_H__1CB0FFE5_B851_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_VIDEO02_H__1CB0FFE5_B851_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "video.h"
#include "GlClass.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Video02.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideo02 window


class CVideo02 : public CVideo
{
// Construction
public:
	CVideo02();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideo02)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:

	int Wait( DWORD pTime);
	
	virtual int RenderScene();
	virtual int InitView(BOOL pOnSize);
 	virtual int ThreadProcessMessages();
	CGLNumber m_Number01;
	LARGE_INTEGER m_Frec,m_LastCount,m_CurrentCount;
	DWORD m_Count;
	BOOL m_OnObject;
	virtual ~CVideo02();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideo02)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEO02_H__1CB0FFE5_B851_11D3_A036_0000E8DE4B3B__INCLUDED_)
