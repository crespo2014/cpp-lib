// OpenGl10.h: interface for the COpenGl10 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL10_H__A004A190_9457_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_OPENGL10_H__A004A190_9457_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COpenGl10 : public CWnd  
{
public:
	COpenGl10();
	virtual ~COpenGl10();

protected:
	HGLRC m_hGLContext;
	HDC   m_hDC;
	int m_GLPixelIndex;
	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
protected:
	PIXELFORMATDESCRIPTOR pixelDesc;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); 
	afx_msg void OnDestroy();
public:
	void SetupPalette();
	// uso de un hilo para trabajar el RC
	//int m_IsThread;
	HPALETTE hPalette;
	virtual int GlInit();
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_OPENGL10_H__A004A190_9457_11D3_A036_0000E8DE4B3B__INCLUDED_)
