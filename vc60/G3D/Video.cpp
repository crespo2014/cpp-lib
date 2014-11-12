// Video.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Video.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideo

CVideo::CVideo()
{
	FillSin();
	m_RenderThread=NULL;
	m_hDC=NULL;
	m_hGLRC=NULL;
	m_hEvent=NULL;
	m_OnPlay=false;
	m_OnRC=false;
	m_hEvent=CreateEvent(NULL,false,false,NULL);
	if (!m_hEvent)
	{
		TRACE0("Creating Event Failed");
		return; 
	}

	m_RenderThread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_ABOVE_NORMAL);
	if (!m_RenderThread)
		return;
	PostThreadMessage(m_RenderThread->m_nThreadID,UM_THREADACK,0,0);
	if (WaitForSingleObject(m_hEvent,INFINITE)!=WAIT_OBJECT_0)
	{
		TRACE0("Wait Failed");
	}
}

CVideo::~CVideo()
{
	if (m_RenderThread)
	{
		PostThreadMessage(m_RenderThread->m_nThreadID,UM_CLOSE,0,0);
		WaitForSingleObject(m_hEvent,INFINITE);
		WaitForSingleObject(m_RenderThread->m_hThread,INFINITE);
	}
	CloseHandle(m_hEvent);
}


BEGIN_MESSAGE_MAP(CVideo, CWnd)
	//{{AFX_MSG_MAP(CVideo)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVideo message handlers

int CVideo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hDC = ::GetDC(m_hWnd);

	if (!SetupPF())
		return false;

	SetupPalette();

	if (!CreateRC())
		return false;

	// TODO: Add your specialized creation code here
	
	return 0;
}



int CVideo::CreateRC()
{
	m_hGLRC=wglCreateContext(m_hDC);
	if (m_hGLRC == NULL)
	{
		return FALSE;
	}
	if (m_RenderThread)
		PostThreadMessage(m_RenderThread->m_nThreadID,UM_ATTACHRC,(DWORD)m_hGLRC,(DWORD)m_hDC);
	else
	{
		if (wglMakeCurrent(m_hDC,m_hGLRC)==FALSE)
			return false;
	}
	return true;
}

LRESULT CVideo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_PAINT:
	case WM_SIZE:
	case WM_CHAR:
		{
			PostThreadMessage(m_RenderThread->m_nThreadID,message,wParam,lParam);
			break;
		}
	case WM_DESTROY:
		{
			PostThreadMessage(m_RenderThread->m_nThreadID,UM_RELEASERC,0,0);
			WaitForSingleObject(m_hEvent,INFINITE);
			wglMakeCurrent(m_hDC,m_hGLRC);
			break;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

BOOL CVideo::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_CHAR:
			{
				PostThreadMessage(m_RenderThread->m_nThreadID,pMsg->message,pMsg->wParam,pMsg->lParam);
				return true;
			}
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}

int CVideo::ProcessMessages()
{
	do 
	{
		if ((!m_OnPlay)|(!m_OnRC))
		{
			// Esperar por un mensaje
			if (!PeekMessage(&m_msg,NULL,NULL,NULL,PM_NOREMOVE))
				WaitMessage();
		}
		if (PeekMessage(&m_msg,NULL,NULL,NULL,PM_REMOVE))
		{
			switch(m_msg.message)
			{
			case UM_PLAY:
				{
					m_OnPlay=true;
					break;
				}
			case UM_PAUSE:
				{
					m_OnPlay=false;
					break;
				}
			case UM_THREADACK:
				{
					SetEvent(m_hEvent);
					break;
				}
			case UM_ATTACHRC:
				{
					m_OnRC=wglMakeCurrent((HDC)m_msg.lParam,(HGLRC)m_msg.wParam);
					InitView(false);
					break;
				}
			case UM_DESTROYRC:
				{
					wglMakeCurrent(NULL,NULL);
					wglDeleteContext(m_hGLRC);
					SetEvent(m_hEvent);
					m_OnRC=false;
					break;
				}
			case UM_RELEASERC:
				{
					wglMakeCurrent(NULL,NULL);
					m_OnRC=false;
					SetEvent(m_hEvent);
					break;
				}
			case UM_CLOSE:
				{
					return false;
				}
			case WM_PAINT:
				{
					m_OnPaint=true;
					break;
				}
			case WM_SIZE:
				{
					m_Width=LOWORD(m_msg.lParam);
					m_Height=HIWORD(m_msg.lParam);

					if (m_Height ==0)
						aspect=(GLdouble)m_Width;
					else
						aspect=(GLdouble)m_Width/(GLdouble)m_Height;
				
					if (m_OnRC)
					{
						glViewport(0,0,m_Width,m_Height);
						InitView(true);						
					}
					break;
				}
			case WM_CLOSE:
				{
					break;
				}
			default:
				{
					if (!ThreadProcessMessages())
						return false;
				}
			}
		}
	} while  (!(m_OnPlay | m_OnPaint)|(!m_OnRC));
	return true;
}

int CVideo::InitView(BOOL pOnSize)
{
	return true;
}

UINT CVideo::ThreadMain()
{
	while (true)
	{
		if (!ProcessMessages())
			break;
		if (!RenderScene())
			break;
		m_OnPaint=false;
	}
	SetEvent(m_hEvent);
	return 0;
}

int CVideo::RenderScene()
{
	return true;
}

UINT CVideo::ThreadProc(LPVOID pParam)
{
	return ((CVideo*)pParam)->ThreadMain();
}

int CVideo::ThreadProcessMessages()
{
	return true;
}

int CVideo::Play()
{
	if (m_RenderThread)
		PostThreadMessage(m_RenderThread->m_nThreadID,UM_PLAY,0,0);
	SetFocus();
	return true;
}

int CVideo::Pause()
{
	if (m_RenderThread)
		PostThreadMessage(m_RenderThread->m_nThreadID,UM_PAUSE,0,0);
	return true;
}

void CVideo::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CWnd::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	
}

BOOL CVideo::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_hGLRC && m_hPalette)
	{
		UnrealizeObject(m_hPalette);
		SelectPalette(m_hDC,m_hPalette,FALSE);
		RealizePalette(m_hDC);
		return true;
	}
	return CWnd::OnQueryNewPalette();
}

int CVideo::SetupPalette()
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

int CVideo::SetupPF()
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
