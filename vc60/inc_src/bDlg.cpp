// bDlg.cpp: implementation of the CbDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbDlg::CbDlg()
{
	m_hwnd = NULL;
	m_rcode = 0;
	m_bExit = false;
}

CbDlg::~CbDlg()
{
	Release();	
}

DWORD CbDlg::Dlg_Create(char *resource_name)
{
	HMODULE	hmod = GetModuleHandle(NULL);
	HWND	hmainwnd = GetActiveWindow();

	m_hwnd = CreateDialogParam((HINSTANCE)hmod,resource_name,hmainwnd,(DLGPROC)DialogProc,(long)this);
	if (m_hwnd == NULL) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbDlg::Create -> CreateDialogParam (%s) ",resource_name);
	return ERR_OK;
}

DWORD CbDlg::Dlg_CreateModal(char* resource_name,INT_PTR *exitCode)
{
	DWORD	dwr;

 	HMODULE	hmod = GetModuleHandle(NULL); //GetModuleHandle("notesdll");
 	HWND	hmainwnd = NULL; //GetActiveWindow();
 
 	*exitCode = DialogBoxParam((HINSTANCE)hmod,resource_name,hmainwnd,(DLGPROC)DialogProc,(long)this);
	dwr = GetLastError();
 	if (m_hwnd == NULL)	return SetError_Add_W32_code_msg(true,ERR_API,dwr,"CbDlg::Show_Modal -> DialogBoxParam (\"%s\")... ",resource_name);
	return ERR_OK;

}

INT_PTR CbDlg::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CbDlg*	pDlg;
	if (uMsg == WM_INITDIALOG)
	{
		pDlg = (CbDlg*)lParam;
		::SetWindowLong(hwndDlg,GWL_USERDATA,(LONG)pDlg);
		pDlg->m_hwnd = hwndDlg;
	}
	// tomar ptr a la clase
	pDlg = (CbDlg*)::GetWindowLong(hwndDlg,GWL_USERDATA);
	// llamar al metodo de la clase
	if (pDlg != NULL) return pDlg->Dlg_Proc(hwndDlg,uMsg,wParam,lParam);
	return false;
	// Procesamiento por defecto o devolver false a ver que
//	return DefWindowProc(hwndDlg,uMsg,wParam,lParam);
}

INT_PTR CbDlg::Dlg_Proc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return false;
}

DWORD CbDlg::Item_SetText(WORD ctrlID, char *format, ... )
{
	char	ptext[1024];
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(ptext,format,arg_ptr);
	::SetDlgItemText(m_hwnd,ctrlID,ptext);
	va_end(arg_ptr);
	return ERR_OK;
}

DWORD CbDlg::Item_GetText(WORD ctrlID, char *text, DWORD size)
{
	DWORD	dwr;
	UINT	ui;
	*text = 0;
	ui = GetDlgItemText(m_hwnd,ctrlID,text,size);
	dwr = GetLastError();
	if ((ui == 0) && (dwr != ERROR_SUCCESS)) return SetError_Add_W32_code_msg(true,ERR_API,dwr,"CProgressDlg::Item_GetText for CtrlID = %u ",ctrlID);
	return ERR_OK;
}

void CbDlg::Window_SetTitle(char *format, ... )
{
	char	ptext[1024];
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(ptext,format,arg_ptr);
	SetWindowText(m_hwnd,ptext);
	va_end(arg_ptr);
}

DWORD CbDlg::Dlg_ModalShow(INT_PTR* exitCode)
{
	MSG	msg;
	*exitCode = 0;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!IsDialogMessage(m_hwnd,&msg)) DispatchMessage(&msg);
		if (m_bExit)
		{
			*exitCode = m_rcode;
			return ERR_OK;
		}
	}
	return ERR_OK;
}

void CbDlg::Dlg_ModalEnd(INT_PTR rc)
{
//	Window_Destroy();
	m_bExit = true;
	m_rcode = rc;
}

void CbDlg::Release()
{
	if (m_hwnd != NULL) DestroyWindow(m_hwnd);
}

DWORD CbDlg::Dlg_ModalLoop(INT_PTR *exitCode)
{
	MSG	msg;
	*exitCode = 0;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!IsDialogMessage(m_hwnd,&msg)) DispatchMessage(&msg);
		if (m_bExit)
		{
			*exitCode = m_rcode;
			return ERR_OK;
		}
	}
	return ERR_OK;

}

void CbDlg::Dlg_ModalLoopExit(INT_PTR exitCode)
{
	m_rcode = exitCode;
	m_bExit = true;
}
