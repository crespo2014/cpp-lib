#if !defined(AFX_GRAPHICSSETTINGS_H__5E674896_0292_11D5_9039_0000E83D722B__INCLUDED_)
#define AFX_GRAPHICSSETTINGS_H__5E674896_0292_11D5_9039_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphicsSettings.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphicsSettings dialog

class CApp;

class CGraphicsSettings : public CDialog
{
// Construction
public:
	CApp *m_pApp;
	void SetAppPointer(void *pApp);
	CGraphicsSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphicsSettings)
//	enum { IDD = IDD_SETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphicsSettings)
	afx_msg void OnSelchangeVoltPorDiv();
	afx_msg void OnSignalColor();
	afx_msg void OnSelchangeSamplesCant();
	afx_msg void OnGridColor();
	afx_msg void OnBackColor();
	afx_msg void OnSelchangeAxisPosition();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICSSETTINGS_H__5E674896_0292_11D5_9039_0000E83D722B__INCLUDED_)
