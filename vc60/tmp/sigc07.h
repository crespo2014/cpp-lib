#if !defined(AFX_SIGC07_H__522A7463_0102_11D5_902D_0000E83D722B__INCLUDED_)
#define AFX_SIGC07_H__522A7463_0102_11D5_902D_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sigc07.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSignalFrame frame

#include "sigc04.h"

class AFX_EXT_CLASS CSignalFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CSignalFrame)
protected:
	

// Attributes
public:
	CSignalFrame();           // protected constructor used by dynamic creation

// Operations
public:
	void LoadClinician(CApp* pApp);
	DWORD SetAppPtr(CApp* lpApp);
	virtual ~CSignalFrame();
	CApp*		m_lpApp;
    CToolBar m_wndToolBar;
	bool m_All_Graphics_State;
	bool m_RAW_State;
	bool m_Temp_State;
    bool m_REEG_State;
	bool m_IEEG_State;
	bool m_IEMG_State;
	bool m_Frec_State;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CSignalFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTbshowallgraphics();
	afx_msg void OnConfigurationGraphicssettings();
	afx_msg void OnUpdateTbShowAllGraphics(CCmdUI* pCmdUI);
	afx_msg void OnTbShowIeeg();
	afx_msg void OnUpdateTbShowIeeg(CCmdUI* pCmdUI);
	afx_msg void OnTbShowIemg();
	afx_msg void OnUpdateTbShowIemg(CCmdUI* pCmdUI);
	afx_msg void OnTbShowRaw();
	afx_msg void OnUpdateTbShowRaw(CCmdUI* pCmdUI);
	afx_msg void OnTbShowReeg();
	afx_msg void OnUpdateTbShowReeg(CCmdUI* pCmdUI);
	afx_msg void OnTbshowTemp();
	afx_msg void OnUpdateTbshowTemp(CCmdUI* pCmdUI);
	afx_msg void OnViewFrec();
	afx_msg void OnUpdateViewFrec(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGC07_H__522A7463_0102_11D5_902D_0000E83D722B__INCLUDED_)
