// class4.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "class4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

CGLView::CGLView()
{
	m_Params=new S_GLView;

	m_Params->m_PFD.nSize =sizeof(PIXELFORMATDESCRIPTOR);
	m_Params->m_PFD.nVersion=1;
	m_Params->m_PFD.dwFlags= PFD_DRAW_TO_WINDOW|
						PFD_SUPPORT_OPENGL|
						PFD_DOUBLEBUFFER|
						//PFD_SUPPORT_GDI|
						PFD_DRAW_TO_BITMAP|
						0;
	m_Params->m_PFD.iPixelType =PFD_TYPE_RGBA;
	m_Params->m_PFD.cColorBits=32;
	m_Params->m_PFD.cRedBits=8;
	m_Params->m_PFD.cRedShift=16;
	m_Params->m_PFD.cGreenBits=8;
	m_Params->m_PFD.cGreenShift=8;
	m_Params->m_PFD.cBlueBits=8;
	m_Params->m_PFD.cBlueShift=0;
	m_Params->m_PFD.cAlphaBits		= 0;
	m_Params->m_PFD.cAlphaShift		= 0;
	m_Params->m_PFD.cAccumBits		= 0;	
	m_Params->m_PFD.cAccumRedBits	= 0;
	m_Params->m_PFD.cAccumGreenBits	= 0;
	m_Params->m_PFD.cAccumBlueBits	= 0;
	m_Params->m_PFD.cAccumAlphaBits	= 0;
	m_Params->m_PFD.cDepthBits		= 32;
	m_Params->m_PFD.cStencilBits	= 0;
	m_Params->m_PFD.cAuxBuffers		= 0;
	m_Params->m_PFD.iLayerType		= PFD_MAIN_PLANE;
	m_Params->m_PFD.bReserved		= 0;
	m_Params->m_PFD.dwLayerMask		= 0;
	m_Params->m_PFD.dwVisibleMask	= 0;
	m_Params->m_PFD.dwDamageMask	= 0;
	
	Init();
}

CGLView::~CGLView()
{
	if (m_Params)
		delete m_Params;
}


BEGIN_MESSAGE_MAP(CGLView, CWnd)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CDC* dc=GetDC();
	m_Params->m_hDC=*dc;

	if (!SetupPF())
		return false;

	SetupPalette();

	if (!CreateRC())
		return false;
	InitView(false,0,0);	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CGLView::OnDestroy() 
{
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (m_Params->m_hGLRC!=NULL)
	{
		wglDeleteContext(m_Params->m_hGLRC);
		m_Params->m_hGLRC=NULL;
	}
	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CGLView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (m_Params->m_hGLRC && m_Params->m_hPalette && this != pFocusWnd)
	{
		UnrealizeObject(m_Params->m_hPalette);
		SelectPalette(m_Params->m_hDC,m_Params->m_hPalette, FALSE);        
		RealizePalette(m_Params->m_hDC);
	}
	CWnd::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	
}

BOOL CGLView::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Params->m_hGLRC && m_Params->m_hPalette)
	{
		UnrealizeObject(m_Params->m_hPalette);
		SelectPalette(m_Params->m_hDC,m_Params->m_hPalette,FALSE);
		RealizePalette(m_Params->m_hDC);
		return true;
	}
	return CWnd::OnQueryNewPalette();
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style|=(WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
	return CWnd::PreCreateWindow(cs);
}

int CGLView::CreateRC()
{
	m_Params->m_hGLRC=wglCreateContext(m_Params->m_hDC);
	if (m_Params->m_hGLRC == NULL)
	{
		return FALSE;
	}
	if (wglMakeCurrent(m_Params->m_hDC,m_Params->m_hGLRC) ==FALSE)
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
	int PixelFormat=GetPixelFormat(m_Params->m_hDC);
	DescribePixelFormat(m_Params->m_hDC,PixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&m_Params->m_PFD);
	if (m_Params->m_PFD.dwFlags & PFD_NEED_PALETTE)
	{
		paletteSize=1<<m_Params->m_PFD.cColorBits;
		pPal = (LOGPALETTE*)
		malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
		pPal->palVersion = 0x300;
		pPal->palNumEntries = paletteSize;
		
		int redMask = (1 << m_Params->m_PFD.cRedBits) - 1;
        int greenMask = (1 << m_Params->m_PFD.cGreenBits) - 1;
        int blueMask = (1 << m_Params->m_PFD.cBlueBits) - 1;
        for (int i=0; i<paletteSize; ++i)
		{
            pPal->palPalEntry[i].peRed =
			(((i >> m_Params->m_PFD.cRedShift) & redMask) * 255) / redMask;
			
			pPal->palPalEntry[i].peGreen =
				(((i >> m_Params->m_PFD.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> m_Params->m_PFD.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
		m_Params->m_hPalette = CreatePalette(pPal);
		free(pPal);
		if (m_Params->m_hPalette)
		{
			SelectPalette(m_Params->m_hDC,m_Params->m_hPalette, FALSE);
			RealizePalette(m_Params->m_hDC);
		}
	}
	return TRUE;

}

int CGLView::SetupPF()
{
	m_Params->m_PFI = ChoosePixelFormat(m_Params->m_hDC, &m_Params->m_PFD);
	if (m_Params->m_PFI==0) // Let's choose a default index.
	{
		m_Params->m_PFI = 1;	
		if (DescribePixelFormat(m_Params->m_hDC,m_Params->m_PFI,
			sizeof(PIXELFORMATDESCRIPTOR), &m_Params->m_PFD)==0)
		{
			AfxMessageBox("DescribePixelFormat Failed ...");
			return FALSE;
		}
	}

	if (SetPixelFormat(m_Params->m_hDC,m_Params->m_PFI,&m_Params->m_PFD)==FALSE)
	{
		AfxMessageBox("SetPixelFormat Failed ...");
		return FALSE;
	}
	return true;
}

void CGLView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	RenderScene();
	// Do not call CWnd::OnPaint() for painting messages
}

int CGLView::RenderScene()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(m_Params->m_hDC);	
	return true;
}

int CGLView::InitView(BOOL pOnSize, int pWidth, int pHeight)
{
	if (pOnSize)
	{
		glViewport(0,0,pWidth,pHeight);

		GLdouble aspect;
		if (pHeight ==0)
			aspect=(GLdouble)pWidth;
		else
			aspect=(GLdouble)pWidth/(GLdouble)pHeight;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40,aspect,1,2000);
		glMatrixMode(GL_MODELVIEW);
		return true;
	}

	glClearColor(0,0,0.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float ambient[]={1,1,1,1};
	float diffuse[]={0.3f,0.3f,0.3f,1};
	float pos[]={0,0,0,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,diffuse);

	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	glDisable(GL_AUTO_NORMAL);
	glDisable(GL_NORMALIZE); 
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_DITHER);
	glDisable(GL_FOG);
	glDisable(GL_LOGIC_OP); 
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_TEXTURE_1D); 
	glDisable(GL_TEXTURE_2D);
	return true;
}

void CGLView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	InitView(true,cx,cy);
}

HDC CGLView::GetViewDC()
{
	return m_Params->m_hDC;
}

int CGLView::Init()
{
	return true;
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC) 
{
	return true;		
}
