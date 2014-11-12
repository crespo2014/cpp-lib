#if !defined(AFX_VIDEO_H__1CB0FFE1_B851_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_VIDEO_H__1CB0FFE1_B851_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Video.h : header file
//
#include "glclass.h"
/////////////////////////////////////////////////////////////////////////////
// CVideo window

class CVideo : public CWnd
{
// Construction
public:
	CVideo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

    // Implementation
public:
	int SetupPF();
	int SetupPalette();
	int Pause();
	int Play();
	
	static UINT ThreadProc(LPVOID pParam);
	virtual int RenderScene();
	UINT ThreadMain();
	virtual int InitView(BOOL pOnSize);
	MSG m_msg;
	BOOL m_OnRC;
	BOOL m_OnPlay;
	int ProcessMessages();
	BOOL m_OnPaint;
	int m_Height;
	int m_PFI;
	int m_Width;
	HPALETTE m_hPalette;
	PIXELFORMATDESCRIPTOR m_PFD;
	GLdouble aspect;
	HANDLE m_hEvent;
	int CreateRC();
	HGLRC m_hGLRC;
	HDC m_hDC;
	CWinThread* m_RenderThread;
	virtual int ThreadProcessMessages();
	virtual ~CVideo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideo)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEO_H__1CB0FFE1_B851_11D3_A036_0000E8DE4B3B__INCLUDED_)
