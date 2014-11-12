// gl10c12.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "gl10c12.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemDCView

CMemDCView::CMemDCView()
{
	InitMemDCView();
}

CMemDCView::~CMemDCView()
{
	delete m_MemDCView;
}


BEGIN_MESSAGE_MAP(CMemDCView, CWnd)
	//{{AFX_MSG_MAP(CMemDCView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMemDCView message handlers

int CMemDCView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (SetupPixelFormat())
		if (CreateRC())
			if (wglMakeCurrent(m_MemDCView->memdc,m_MemDCView->hrc))
			{
				Init(false,0,0);
				wglMakeCurrent(NULL,NULL);
				return true;
			}
	return false;
}

int CMemDCView::SetupPixelFormat()
{
	CClientDC dc(this);
	m_MemDCView->memdc.Create(&dc);

	m_MemDCView->PFI = ChoosePixelFormat(m_MemDCView->memdc,&m_MemDCView->PFD);
	if (m_MemDCView->PFI==0) // Let's choose a default index.
	{
		m_MemDCView->PFI = 1;	
		if (DescribePixelFormat(m_MemDCView->memdc,m_MemDCView->PFI,
			sizeof(PIXELFORMATDESCRIPTOR), &m_MemDCView->PFD)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(m_MemDCView->memdc,m_MemDCView->PFI,&m_MemDCView->PFD)==FALSE)
	{
		AfxMessageBox("Failed SetupPixelFormat......");
		return FALSE;
	}
	return true;
}

int CMemDCView::InitMemDCView()
{
	m_MemDCView=new S_MEMDCVIEW;
	memset(&m_MemDCView->PFD,0,sizeof(PIXELFORMATDESCRIPTOR));

	m_MemDCView->PFD.nSize		=sizeof(PIXELFORMATDESCRIPTOR);
	m_MemDCView->PFD.nVersion	=1;
	m_MemDCView->PFD.dwFlags	=PFD_SUPPORT_OPENGL|PFD_SUPPORT_GDI|PFD_DRAW_TO_BITMAP;
	m_MemDCView->PFD.iPixelType	=PFD_TYPE_RGBA;
	m_MemDCView->PFD.cColorBits	=16;
	m_MemDCView->PFD.cDepthBits	=32;
	m_MemDCView->PFD.iLayerType	=PFD_MAIN_PLANE;

	m_MemDCView->hrc=NULL;
	m_MemDCView->autopaint=true;
	return true;
}

int CMemDCView::CreateRC()
{
	m_MemDCView->hrc=wglCreateContext(m_MemDCView->memdc);
	return (m_MemDCView->hrc != NULL);
}

int CMemDCView::RenderDC(CDC *dc)
{
	glClearColor(0,255,255,255);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glFinish();
	dc->TextOut(7,7,"GDI and OpenGL");
	return true;
}

void CMemDCView::OnPaint() 
{
	CPaintDC dc(this);
	if (!m_MemDCView->autopaint)
		return;

	if (wglMakeCurrent(m_MemDCView->memdc,m_MemDCView->hrc))
	{
		RenderDC(&m_MemDCView->memdc);
		wglMakeCurrent(NULL,NULL);
	}
	else
	{
		m_MemDCView->memdc.TextOut(0,0,"Error");
	}
	m_MemDCView->memdc.Swap(&dc);
}

void CMemDCView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	m_MemDCView->memdc.SetSize(cx,cy);
	if (wglMakeCurrent(m_MemDCView->memdc,m_MemDCView->hrc))
	{
		Init(true,cx,cy);
		wglMakeCurrent(NULL,NULL);
	}
}

int CMemDCView::Init(BOOL pOnSize, int pWidth, int pHeight)
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

	float ambient[]={0.5,0.5,0.5,1.0};
	float diffuse[]={0.3f,0.3f,0.3f,1};
	float pos[]={0,0,0,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,diffuse);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,true);

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

void CMemDCView::OnDestroy() 
{
	if (wglGetCurrentContext()!=NULL)
	{
		wglMakeCurrent(NULL,NULL);
	}
	if (m_MemDCView->hrc!=NULL)
	{
		wglDeleteContext(m_MemDCView->hrc);
		m_MemDCView->hrc=NULL;
	}
	CWnd::OnDestroy();
}

BOOL CMemDCView::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

BOOL CMemDCView::OnQueryNewPalette() 
{
	CClientDC dc(this);
	if (m_MemDCView->hrc && m_MemDCView->hPalette)
	{
		UnrealizeObject(m_MemDCView->hPalette);
		SelectPalette(dc,m_MemDCView->hPalette,FALSE);
		RealizePalette(dc);
		return true;
	}
	return CWnd::OnQueryNewPalette();
}

void CMemDCView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CClientDC dc(this);
	if (m_MemDCView->hrc && m_MemDCView->hPalette && this != pFocusWnd)
	{
		UnrealizeObject(m_MemDCView->hPalette);
		SelectPalette(dc,m_MemDCView->hPalette, FALSE);        
		RealizePalette(dc);
	}
	CWnd::OnPaletteChanged(pFocusWnd);
}

int CMemDCView::SetupPalette()
{
	LOGPALETTE* pPal;
	int paletteSize;
	int PixelFormat=GetPixelFormat(m_MemDCView->memdc);
	DescribePixelFormat(m_MemDCView->memdc,PixelFormat,sizeof(PIXELFORMATDESCRIPTOR),&m_MemDCView->PFD);
	if (m_MemDCView->PFD.dwFlags & PFD_NEED_PALETTE)
	{
		paletteSize=1<<m_MemDCView->PFD.cColorBits;
		pPal = (LOGPALETTE*)
		malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
		pPal->palVersion = 0x300;
		pPal->palNumEntries = paletteSize;
		
		int redMask = (1 << m_MemDCView->PFD.cRedBits) - 1;
        int greenMask = (1 << m_MemDCView->PFD.cGreenBits) - 1;
        int blueMask = (1 << m_MemDCView->PFD.cBlueBits) - 1;
        for (int i=0; i<paletteSize; ++i)
		{
            pPal->palPalEntry[i].peRed =
			(((i >> m_MemDCView->PFD.cRedShift) & redMask) * 255) / redMask;
			
			pPal->palPalEntry[i].peGreen =
				(((i >> m_MemDCView->PFD.cGreenShift) & greenMask) * 255) / greenMask;
			pPal->palPalEntry[i].peBlue =
				(((i >> m_MemDCView->PFD.cBlueShift) & blueMask) * 255) / blueMask;
			pPal->palPalEntry[i].peFlags = 0;
		}
		m_MemDCView->hPalette = CreatePalette(pPal);
		free(pPal);
		if (m_MemDCView->hPalette)
		{
			SelectPalette(m_MemDCView->memdc,m_MemDCView->hPalette, FALSE);
			RealizePalette(m_MemDCView->memdc);
		}
	}
	return TRUE;
}

//
// Cuando se pasa false ya la clase no pinta cuando recibe el mensage on paint
//
int CMemDCView::SetAutoPaint(BOOL state)
{
	m_MemDCView->autopaint=state;
	return true;
}

// Devuelve el RC asociado 
HGLRC CMemDCView::GetRC()
{
	return m_MemDCView->hrc;
}

CMemDC* CMemDCView::GetMemDC()
{
	return &m_MemDCView->memdc;
}
