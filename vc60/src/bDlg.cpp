// bDlg.cpp: implementation of the CbDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "bDlg.h"

#define _FILENAME_ "bdlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CHECK_HANDLE if (m_hwnd == NULL) return ERROR_LOG ERR_HANDLE,"Invalid Dlg handle");

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

	m_hwnd = CreateDialogParamA((HINSTANCE)hmod,resource_name,hmainwnd,(DLGPROC)DialogProc,(long)this);
	if (m_hwnd == NULL)  return log_w32error GetLastError(),ERR_API,"CreateDialogParam (%s) ",resource_name);
	return ERR_OK;
}

DWORD CbDlg::Dlg_CreateModal(char* resource_name,INT_PTR *exitCode)
{
	DWORD	dwr;

 	HMODULE	hmod = GetModuleHandle(NULL); //GetModuleHandle("notesdll");
 	HWND	hmainwnd = NULL; //GetActiveWindow();
 
 	*exitCode = DialogBoxParamA((HINSTANCE)hmod,resource_name,hmainwnd,(DLGPROC)DialogProc,(long)this);
	dwr = GetLastError();
 	if (m_hwnd == NULL)	return log_w32error dwr,ERR_API,"DialogBoxParam (%s) ",resource_name);
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
	::SetDlgItemTextA(m_hwnd,ctrlID,ptext);
	va_end(arg_ptr);
	return ERR_OK;
}

DWORD CbDlg::Item_GetText(WORD ctrlID, char *text, DWORD size)
{
	DWORD	dwr;
	UINT	ui;
	*text = 0;
	ui = GetDlgItemTextA(m_hwnd,ctrlID,text,size);
	dwr = GetLastError();
	if ((ui == 0) && (dwr != ERROR_SUCCESS)) return log_w32error dwr,ERR_API,"GetDlgItemTextA for CtrlID = %u ",ctrlID);
	return ERR_OK;
}

void CbDlg::Window_SetTitle(char *format, ... )
{
	char	ptext[1024];
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsprintf(ptext,format,arg_ptr);
	SetWindowTextA(m_hwnd,ptext);
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

DWORD CbDlg::End(INT_PTR nResult)
{
	if (m_hwnd == NULL) return log_error ERR_HANDLE,"Window handle not valid");
	if (EndDialog(m_hwnd,nResult)) return ERR_OK;
	return LOG_TW32_ERROR GetLastError(),ERR_API,"Calling EndDialog failed ");
}

DWORD CbDlg::CBW_AddStr(HWND hcb, char *format, ...)
{
	char	ptext[1024];
	LRESULT lr;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	_vsnprintf(ptext,sizeof(ptext),format,arg_ptr);
	va_end(arg_ptr);
	lr = SendMessage(hcb,CB_ADDSTRING,0,(LPARAM)ptext);
	if ((lr == CB_ERR) || (lr == CB_ERRSPACE)) {
		return LOG_TERROR ERR_FATAL,"CB_ADDSTRING failed with code = %d",lr);
	}
	return ERR_OK;
}

DWORD CbDlg::CBI_AddStr(int IDItem,  char *format, ...)
{
	char	ptext[1024];
	HWND	hcb;
	LRESULT lr;
	
	hcb = getItem(IDItem);if (hcb == NULL) return LOG_TERROR ERR_FATAL,"Item %d not found",IDItem);
	va_list arg_ptr;
	va_start(arg_ptr, format);
	_vsnprintf(ptext,sizeof(ptext),format,arg_ptr);
	va_end(arg_ptr);
	lr = SendMessage(hcb,CB_ADDSTRING,0,(LPARAM)ptext);
	if ((lr == CB_ERR) || (lr == CB_ERRSPACE)) {
		return LOG_TERROR ERR_FATAL,"CB_ADDSTRING failed with code = %d",lr);
	}
	return ERR_OK;

}

DWORD CbDlg::CreateModal(HMODULE hModule, HWND hMainWind, char *resource_name, INT_PTR *exitCode)
{
	if (hModule == NULL) hModule = GetModuleHandle(NULL);
 	*exitCode = DialogBoxParamA((HINSTANCE)hModule,resource_name,hMainWind,(DLGPROC)DialogProc,(long)this);
	if (*exitCode == -1) {
		return LOG_TW32_ERROR GetLastError(),ERR_API,"DialogBoxParamA failed for resource %s",resource_name);
	}
// 	if (m_hwnd == NULL)	return SetError_Add_W32_code_msg(ERR_API,dwr,"CbDlg::Show_Modal -> DialogBoxParam (\"%s\")... ",resource_name);
	return ERR_OK;
}

HWND CbDlg::getItem(int ctrlID)
{
	if (m_hwnd == NULL) 
	{
		LOG_TERROR ERR_HANDLE,"Invalid Dlg handle");
		return NULL;
	}
	return GetDlgItem(m_hwnd,ctrlID);
}

void CbDlg::Window_Center(HWND hwnd)
{

RECT	prect;
	RECT	wrect;
	int		Xo,Yo;
	HWND	phwnd;
	if (hwnd == NULL) return;
	phwnd = ::GetParent(hwnd); 
	if (phwnd == NULL) phwnd = GetDesktopWindow();
	if (phwnd == NULL) return;
	if (!::GetWindowRect(phwnd,&prect)) return;
	if (!::GetWindowRect(hwnd,&wrect)) return;
	Xo = ((prect.right - prect.left) - (wrect.right - wrect.left))/2;
	Yo = ((prect.bottom - prect.top) - (wrect.bottom - wrect.top))/2;
	::MoveWindow(hwnd,Xo,Yo,wrect.right - wrect.left,wrect.bottom - wrect.top,false);
}

DWORD CbDlg::getItemTextSize(DWORD id)
{
	HWND hwnd;
	DWORD	dwr;
	int i;
	if ((hwnd = getItem(id)) == NULL) return _LOG_AT;
	if ((i = GetWindowTextLength(hwnd)) == 0)
	{
		if ((dwr = GetLastError()) != ERROR_SUCCESS)  _LOG_W32ERROR dwr,ERR_API,"GetWindowTextLength");
	}
	return i;
}

void CbDlg::setText(char *cstr)
{
	SetWindowText(m_hwnd,cstr);
}
