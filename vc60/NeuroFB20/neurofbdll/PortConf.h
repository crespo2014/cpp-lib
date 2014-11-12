#if !defined(AFX_PORTCONFIGURATION_H__BD3139C3_0198_11D5_9031_0000E83D722B__INCLUDED_)
#define AFX_PORTCONFIGURATION_H__BD3139C3_0198_11D5_9031_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortConfiguration.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPortConf dialog



class CPortConf : public CDialog
{
// Construction
public:
	void SetPointer(void* p);
	CPortConf(CWnd* pParent = NULL);   // standard constructor
    void *pApp;
	
// Dialog Data
	//{{AFX_DATA(CPortConf)
	enum { IDD = PORT_CONFIGURATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortConf)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPortConf)
	afx_msg void OnSelchangeBaudrate();
	afx_msg void OnSelchangeBytesize();
	afx_msg void OnSelchangeParity();
	afx_msg void OnSelchangePort();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeStopbits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTCONFIGURATION_H__BD3139C3_0198_11D5_9031_0000E83D722B__INCLUDED_)
