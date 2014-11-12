// bDlg.h: interface for the CbDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BDLG_H__4EB00CD1_7CCA_46C7_BBBE_D640438AC37F__INCLUDED_)
#define AFX_BDLG_H__4EB00CD1_7CCA_46C7_BBBE_D640438AC37F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

// TODO:		setcStr	setcfStr	para especificar si tiene o no formato la cadena
// setcText  setfcText

class CbDlg : public CbObject  
{
public:
	void setText(char* cstr);
	DWORD getItemTextSize(DWORD id);
	void Window_Center(HWND hwnd);
	DWORD CreateModal(HMODULE hModule,HWND hMainWind,char* resource_name,INT_PTR *exitCode);
	DWORD CBI_AddStr(int IDItem,  char *format, ...);
	DWORD CBW_AddStr(HWND hcb,char* format,...);
	DWORD End(INT_PTR nResult);
	void	Release();
	void	Window_SetTitle(char *format, ... );
	DWORD	Item_GetText(WORD ctrlID, char *text, DWORD size);
	DWORD	Item_SetText(WORD ctrlID, char *format, ...);
	DWORD	Dlg_CreateModal(char* resource_name, INT_PTR *exitCode);
	DWORD	Dlg_Create(char* resource_name);
	void	SetDlgItemText(int itemID,char* text) { ::SetDlgItemTextA(m_hwnd,itemID,text); };
	
	BOOL	IsWindow()					{ return m_hwnd != NULL; };
	void	Window_Destroy()			{ DestroyWindow(m_hwnd); };
	void	Window_Update()				{ UpdateWindow(m_hwnd); };
	void	Window_Hide()				{ ShowWindow(m_hwnd,SW_HIDE); };
	void	Window_Show()				{ ShowWindow(m_hwnd,SW_SHOW); };
	HWND	Window_GetH()				{ return m_hwnd; };
	void	Timer_Stop()				{ KillTimer(m_hwnd,1000); };
	void	Timer_Start(DWORD milisec)	{ SetTimer(m_hwnd,1000,milisec,NULL); };

	HWND	getItem(int ctrlID);
	HWND	getHandle()					{ return m_hwnd; };
	
	CbDlg();
	virtual ~CbDlg();

protected:
	HWND	m_hwnd;
	BOOL	m_bExit;		// inidica que se debe cerrar el dialogo
	INT_PTR	m_rcode;		// result code 

	INT_PTR virtual Dlg_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	INT_PTR static CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void	Dlg_ModalEnd(INT_PTR rc);
	DWORD	Dlg_ModalShow(INT_PTR* exitCode);
	void	Dlg_ModalLoopExit(INT_PTR exitCode);
	DWORD	Dlg_ModalLoop(INT_PTR* exitCode);
};

#endif // !defined(AFX_BDLG_H__4EB00CD1_7CCA_46C7_BBBE_D640438AC37F__INCLUDED_)
