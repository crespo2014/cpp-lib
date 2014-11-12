// LFC30.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "LFC30def.h"
#include "wind.h"

/*
	
*/
ATOM		m_Atom=0;	// Valor que devuelve RegisterClass
HANDLE		hDll=0;		//Handle de la dll
HINSTANCE	hProg=0;	//Handle del programa


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				hDll=hModule;
				break;
			}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
LFC30_API int nLFC30=0;

LRESULT CALLBACK WindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CWind*	lpWnd;
	if ((Msg == WM_CREATE) || (Msg == WM_NCCREATE))
	{
		CREATESTRUCT*	lpcs;
		lpcs = (CREATESTRUCT*)lParam;
		lpWnd = (CWind*) lpcs->lpCreateParams;
		::SetWindowLong(hWnd,GWL_USERDATA,(long)lpWnd);
	}
	else
		lpWnd = (CWind*)::GetWindowLong(hWnd,GWL_USERDATA);
	if (lpWnd)
		//return lpWnd->VFWindProc(lpWnd,hWnd,Msg,wParam,lParam);
		return lpWnd->WindProc(hWnd,Msg,wParam,lParam);
	else
		return DefWindowProc(hWnd,Msg,wParam,lParam);
}

DWORD RegisterCWindClass()
{
	if (m_Atom !=0)
		return 0;
	WNDCLASSEX	classData;
	classData.cbSize=sizeof(classData);
	classData.cbClsExtra=0;
	classData.cbWndExtra=0;
	classData.hbrBackground=0;
	classData.hCursor=0;
	classData.hIcon=0;
	classData.hIconSm=0;
	classData.hInstance=hProg;
	classData.lpfnWndProc=WindProc;
	classData.lpszClassName=CLASS_NAME;
	classData.lpszMenuName=0;
	classData.style=CS_DBLCLKS;
	m_Atom=RegisterClassEx(&classData);
	if (m_Atom)
		return 0;
	return 1;
}

DWORD LFC30Initialize(HINSTANCE hInst)
{
	hProg=hInst;
	return RegisterCWindClass();
}

DWORD LFC30GetString(char* lpString,DWORD index)
{
	char str[SHARE_MAXLEN];
	str[0]=0;
	SYSTEMTIME	stime;
	GetSystemTime(&stime);
	sprintf(str,"%d%d%d%d%d%d%d%d_%d",
		stime.wYear,
		stime.wMonth,
		stime.wDay,
		stime.wDayOfWeek,
		stime.wHour,
		stime.wMinute,
		stime.wSecond,
		stime.wMilliseconds,
		index);
	strcpy(lpString,str);
	return 0;
}
