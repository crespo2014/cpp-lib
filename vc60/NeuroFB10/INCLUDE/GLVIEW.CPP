// glview.cpp : implementation file
//

#include "stdafx.h"
#include "glview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

CGLView::CGLView()
{
	m_PFD.nSize =sizeof(PIXELFORMATDESCRIPTOR);
	m_PFD.nVersion=1;
	m_PFD.dwFlags= PFD_DRAW_TO_WINDOW|
						PFD_SUPPORT_OPENGL|
						PFD_DOUBLEBUFFER;
	m_PFD.iPixelType =PFD_TYPE_RGBA;
	m_PFD.cColorBits=32;
	m_PFD.cRedBits=8;
	m_PFD.cRedShift=16;
	m_PFD.cGreenBits=8;
	m_PFD.cGreenShift=8;
	m_PFD.cBlueBits=8;
	m_PFD.cBlueShift=0;
	m_PFD.cAlphaBits		= 0;
	m_PFD.cAlphaShift		= 0;
	m_PFD.cAccumBits		= 32;	
	m_PFD.cAccumRedBits		= 0;
	m_PFD.cAccumGreenBits	= 0;
	m_PFD.cAccumBlueBits	= 0;
	m_PFD.cAccumAlphaBits	= 0;
	m_PFD.cDepthBits		= 32;
	m_PFD.cStencilBits		= 8;
	m_PFD.cAuxBuffers		= 0;
	m_PFD.iLayerType		= PFD_MAIN_PLANE;
	m_PFD.bReserved		= 0;
	m_PFD.dwLayerMask		= 0;
	m_PFD.dwVisibleMask		= 0;
	m_PFD.dwDamageMask		= 0;
}

CGLView::~CGLView()
{
}


BEGIN_MESSAGE_MAP(CGLView, CWnd)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hDC = ::GetDC(m_hWnd);
	if (!SetupPF())
		return false;

	if (!CreateRC())
		return false;

	return Init();
}

void CGLView::OnDestroy() 
{
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (m_hGLRC!=NULL)
	{
		wglDeleteContext(m_hGLRC);
		m_hGLRC=NULL;
	}
	CWnd::OnDestroy();
}

int CGLView::SetupPF()
{
	m_PFI = ChoosePixelFormat(m_hDC, &m_PFD);
	if (m_PFI==0) // Let's choose a default index.
	{
		m_PFI = 1;	
		if (DescribePixelFormat(m_hDC, m_PFI,
			sizeof(PIXELFORMATDESCRIPTOR), &m_PFD)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(m_hDC,m_PFI,&m_PFD)==FALSE)
	{
		return FALSE;
	}
	return true;
}

int CGLView::SetupPalette()
{
	// Configurar la palette
	LOGPALETTE* pPal;
	int paletteSize;
	int PixelFormat=GetPixelFormat(m_hDC);
	DescribePixelFormat(m_hDC,PixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&m_PFD);
	if (m_PFD.dwFlags & PFD_NEED_PALETTE)
	{
		paletteSize=1<<m_PFD.cColorBits;
		pPal = (LOGPALETTE*)
		malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
		pPal->palVersion = 0x300;
		pPal->palNumEntries = paletteSize;
		
		int redMask = (1 << m_PFD.cRedBits) - 1;
        int greenMask = (1 << m_PFD.cGreenBits) - 1;
        int blueMask = (1 << m_PFD.cBlueBits) - 1;
        for (int i=0; i<paletteSize; ++i)
		{
            pPal->palPalEntry[i].peRed =
			(((i >> m_PFD.cRedShift) & redMask) * 255) / redMask;
			
			pPal->palPalEntry[i].peGreen =
				(((i >> m_PFD.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> m_PFD.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
		m_hPalette = CreatePalette(pPal);
		free(pPal);
		if (m_hPalette)
		{
			SelectPalette(m_hDC,m_hPalette, FALSE);
			RealizePalette(m_hDC);
		}
	}
	return TRUE;
}

void CGLView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (m_hGLRC && m_hPalette && this != pFocusWnd)
	{
		UnrealizeObject(m_hPalette);
		SelectPalette(m_hDC,m_hPalette, FALSE);        
		RealizePalette(m_hDC);
	}
	CWnd::OnPaletteChanged(pFocusWnd);
}

BOOL CGLView::OnQueryNewPalette() 
{
	if (m_hGLRC && m_hPalette)
	{
		UnrealizeObject(m_hPalette);
		SelectPalette(m_hDC,m_hPalette,FALSE);
		RealizePalette(m_hDC);
		return true;
	}
	return CWnd::OnQueryNewPalette();
}

int CGLView::CreateRC()
{
	m_hGLRC=wglCreateContext(m_hDC);
	if (m_hGLRC == NULL)
	{
		return FALSE;
	}
	if (wglMakeCurrent(m_hDC,m_hGLRC) ==FALSE)
	{
		return FALSE;
	}
	return true;	
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style|=(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	return CWnd::PreCreateWindow(cs);
}

int CGLView::Init()
{
	return true;
}
