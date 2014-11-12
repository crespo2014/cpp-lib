// gl10c13.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "gl10c13.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphWnd

 CGraphWnd::CGraphWnd()
{
	InitGraphWnd();
}

CGraphWnd::~CGraphWnd()
{
	delete m_GraphWnd;
}


BEGIN_MESSAGE_MAP(CGraphWnd, CWnd)
	//{{AFX_MSG_MAP(CGraphWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGraphWnd message handlers

int CGraphWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CClientDC dc(this);
	m_GraphWnd->memdc.Create(&dc);
	return 0;
}

int CGraphWnd::InitGraphWnd()
{
	m_GraphWnd=new S_GRAPHWND;
	return true;
}

void CGraphWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	m_GraphWnd->memdc.SetSize(cx,cy);
}
