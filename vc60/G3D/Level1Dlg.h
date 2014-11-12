#if !defined(AFX_LEVEL1DLG_H__3F01E801_B88F_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_LEVEL1DLG_H__3F01E801_B88F_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "level_1.h"	// Added by ClassView
#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Level1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLevel1Dlg dialog

class CLevel1Dlg : public CDialog
{
// Construction
public:
	UINT m_TimerID;
	CVideoLevel1 m_Video;
	CLevel1Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLevel1Dlg)
	enum { IDD = IDD_G3D_LEVEL1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevel1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLevel1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnG3dStart();
	afx_msg void OnG3dPause();
	afx_msg void OnG3dFinish();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVEL1DLG_H__3F01E801_B88F_11D3_A036_0000E8DE4B3B__INCLUDED_)
