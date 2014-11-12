// OpenGl10.cpp: implementation of the COpenGl10 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGl10.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COpenGl10::COpenGl10()
{
	// Llenado por defecto de esta estructura
	pixelDesc.nSize =sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion=1;
	pixelDesc.dwFlags= PFD_DRAW_TO_WINDOW|
						PFD_SUPPORT_OPENGL|
						PFD_DOUBLEBUFFER;
	pixelDesc.iPixelType =PFD_TYPE_RGBA;
	pixelDesc.cColorBits=32;
	pixelDesc.cRedBits=8;
	pixelDesc.cRedShift=16;
	pixelDesc.cGreenBits=8;
	pixelDesc.cGreenShift=8;
	pixelDesc.cBlueBits=8;
	pixelDesc.cBlueShift=0;
	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits		= 32;	
	pixelDesc.cAccumRedBits		= 8;
	pixelDesc.cAccumGreenBits	= 8;
	pixelDesc.cAccumBlueBits	= 8;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved		= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;


}

COpenGl10::~COpenGl10()
{

}

BEGIN_MESSAGE_MAP(COpenGl10, CWnd)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

int COpenGl10::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Seleccion del formato del pixel
	HWND hWnd = GetSafeHwnd();
	m_hDC = ::GetDC(hWnd);

	if (SetWindowPixelFormat(m_hDC)==FALSE)
		return 0;
	if (CreateViewGLContext(m_hDC)==FALSE)
		return 0;

	GlInit();
	return 0;
};

void COpenGl10::OnDestroy()
{
	// Destrucion del RC
	
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (m_hGLContext!=NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext=NULL;
	}
	
	CWnd::OnDestroy();
};

BOOL COpenGl10::SetWindowPixelFormat(HDC hDC)
{
	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat( hDC, m_GLPixelIndex, &pixelDesc)==FALSE)
	{
		return FALSE;
	}
	// Configurar la palette
	LOGPALETTE* pPal;
	int paletteSize;
	int PixelFormat=GetPixelFormat(hDC);
	DescribePixelFormat(hDC,PixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc);
	if (pixelDesc.dwFlags & PFD_NEED_PALETTE)
	{
		paletteSize=1<<pixelDesc.cColorBits;
		pPal = (LOGPALETTE*)
		malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
		pPal->palVersion = 0x300;
		pPal->palNumEntries = paletteSize;
		
		int redMask = (1 << pixelDesc.cRedBits) - 1;
        int greenMask = (1 << pixelDesc.cGreenBits) - 1;
        int blueMask = (1 << pixelDesc.cBlueBits) - 1;
        for (int i=0; i<paletteSize; ++i)
		{
            pPal->palPalEntry[i].peRed =
			(((i >> pixelDesc.cRedShift) & redMask) * 255) / redMask;
			
			pPal->palPalEntry[i].peGreen =
				(((i >> pixelDesc.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> pixelDesc.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
		hPalette = CreatePalette(pPal);
		free(pPal);
		if (hPalette)
		{
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
		}
	}
	return TRUE;
};

BOOL COpenGl10::CreateViewGLContext(HDC hDC)
{
	m_hGLContext=wglCreateContext(hDC);
	if (m_hGLContext == NULL)
	{
		return FALSE;
	}
	/*
	if (wglMakeCurrent(hDC,m_hGLContext) ==FALSE)
	{
		return FALSE;
	}
	*/
		
	return TRUE;
};

void COpenGl10::OnSize(UINT nType, int cx, int cy) 
{

	CWnd::OnSize(nType, cx, cy);
	{
		// TODO: Add your message handler code here
		GLdouble aspect;
		if (cy ==0)
			aspect=(GLdouble)cx;
		else
			aspect=(GLdouble)cx/(GLdouble)cy;
		
		glViewport(0,0,cx,cy);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(45,aspect,1,200);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDrawBuffer(GL_BACK);
	}
};

BOOL COpenGl10::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	cs.style|=(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	return CWnd::PreCreateWindow(cs);

};	

// Cuando este miembro es llamado ya todo esta hecho menos el size
int COpenGl10::GlInit()
{
	return false;	
}



void COpenGl10::SetupPalette()
{
	
}
