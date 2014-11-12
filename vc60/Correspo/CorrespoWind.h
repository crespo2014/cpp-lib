// CorrespoWind.h: interface for the CCorrespoWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRESPOWIND_H__E5F801A4_C883_410E_A3DD_4331B12D5CDC__INCLUDED_)
#define AFX_CORRESPOWIND_H__E5F801A4_C883_410E_A3DD_4331B12D5CDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wind.h"
#include "workwind.h"
#include "Correspondencia.h"
#include "StartViewWind.h"

class CCorrespoWind  : public CWind
{
	LRESULT OnSetFocus(HWND hOldWnd);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

	CStartViewWind m_StartView;
	CWorkWind	m_WorkWind;

public:
	DWORD _stdcall PreTranslateMessage(MSG *pMsg);
	DWORD Initialize();
	
	DWORD Create_Window();
	CCorrespoWind();
	virtual ~CCorrespoWind();
	
};

#endif // !defined(AFX_CORRESPOWIND_H__E5F801A4_C883_410E_A3DD_4331B12D5CDC__INCLUDED_)
