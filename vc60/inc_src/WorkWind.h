// WorkWind.h: interface for the CWorkWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKWIND_H__339A3CE6_36F3_4D85_B40B_D4D669B006A9__INCLUDED_)
#define AFX_WORKWIND_H__339A3CE6_36F3_4D85_B40B_D4D669B006A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "DBCommon.h"

class CWorkWind : public CWind  
{
	LRESULT OnSize(WORD wWidth,WORD wHeight,UINT uType);
	LRESULT OnEraseBkgnd(HDC hdc);
	LRESULT OnSetContent(IdbView *lpIdbView);
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	DWORD OnCloseContent(DWORD dwCode,void* pParam);
	DWORD Create(int x, int y, int nWidth, int nHeight, HWND hWndParent);
	CWorkWind();
	virtual ~CWorkWind();
	IdbView* m_IdbView;
};

#endif // !defined(AFX_WORKWIND_H__339A3CE6_36F3_4D85_B40B_D4D669B006A9__INCLUDED_)
