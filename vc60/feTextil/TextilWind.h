// TextilWind.h: interface for the CTextilWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTILWIND_H__DA8B0C83_4BB5_4E3B_808B_190C52ABD7D6__INCLUDED_)
#define AFX_TEXTILWIND_H__DA8B0C83_4BB5_4E3B_808B_190C52ABD7D6__INCLUDED_

#include "wind.h"
#include "workwind.h"
#include "textildb.h"
#include "clientecatwin.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTextilWind  : public CWind
{
	LRESULT OnSetFocus(HWND hOldWnd);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	CWorkWind	m_WorkWind;	// ventana contenedora de dialogos
public:
	LRESULT OnCommand(WORD wCode, WORD wId, HWND hWind);
	DWORD _stdcall PreTranslateMessage(MSG *pMsg);
	DWORD Initialize();
	DWORD Create_Window();

	CTextilWind();
	virtual ~CTextilWind();
private:
//	CClienteCatWin	ClienteCat;	// Catalogo de clientes
		

};

#endif // !defined(AFX_TEXTILWIND_H__DA8B0C83_4BB5_4E3B_808B_190C52ABD7D6__INCLUDED_)
