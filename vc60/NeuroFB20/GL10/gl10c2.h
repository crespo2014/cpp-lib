#if !defined(AFX_GL10C2_H__223B4DE9_E5F0_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_GL10C2_H__223B4DE9_E5F0_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10c2.h : header file
//

typedef struct
{
	CImageList	m_ImageListSmall;
	CMenu		escenamenu;
	CMenu		meshmenu;
	CMenu		mesgroupmenu;
	CMenu		materialmenu;
	CMenu		meshinstancemenu;
} S_Tree3DObject;
/////////////////////////////////////////////////////////////////////////////
// CTree3DObject window

class CTree3DObject : public CTreeCtrl
{
// Construction
public:
	CTree3DObject();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTree3DObject)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	int Init();
	S_Tree3DObject* m_Members;
	int Inicializar();
	virtual ~CTree3DObject();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTree3DObject)
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnConfigure();
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddobject();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnImport3ds();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10C2_H__223B4DE9_E5F0_11D3_A036_0000E83D722B__INCLUDED_)
