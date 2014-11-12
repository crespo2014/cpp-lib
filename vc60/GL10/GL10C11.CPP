 // gl10c11.cpp: implementation of the CMemDC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c11.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemDC::CMemDC()
{
	InitMemDC();
}

CMemDC::~CMemDC()
{
	SelectObject(m_MemDC->oldbitmap);
	delete m_MemDC->bitmap;
	delete m_MemDC;
}

int CMemDC::InitMemDC()
{
	m_MemDC=new S_MEMDC;
	m_MemDC->oldbitmap=NULL;
	m_MemDC->bitmap=new CBitmap();
	return true;
}

int CMemDC::Create(CDC *dc)
{
	CreateCompatibleDC(dc);
	m_MemDC->bitmap->CreateCompatibleBitmap(dc,100,100);
	m_MemDC->currentsize.cx=100;
	m_MemDC->currentsize.cy=100;
	m_MemDC->realsize.cx=100;
	m_MemDC->realsize.cy=100;
	m_MemDC->oldbitmap=SelectObject(m_MemDC->bitmap);
	return true;
}

int CMemDC::SetSize(int cx, int cy)
{
	if((m_MemDC->realsize.cx < cx)|(m_MemDC->realsize.cy < cy))
	{
		CBitmap* tempbmp=new CBitmap();
		tempbmp->CreateCompatibleBitmap(this,cx,cy);
		BITMAP bmpinfo;
		tempbmp->GetBitmap(&bmpinfo);
		SelectObject(tempbmp);
		delete m_MemDC->bitmap;
		m_MemDC->bitmap=tempbmp;
		m_MemDC->realsize.cx=cx;
		m_MemDC->realsize.cy=cy;
	}
	m_MemDC->currentsize.cx=cx;
	m_MemDC->currentsize.cy=cy;
	return true;
}

int CMemDC::Swap(CDC *dc)
{
	dc->BitBlt(0,0,m_MemDC->currentsize.cx,m_MemDC->currentsize.cy,this,0,0,SRCCOPY);
	return true;
}


