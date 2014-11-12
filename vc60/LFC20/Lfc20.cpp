// LFC20.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "LFC20.h"
#include "LFC20c01.h"

DWORD	LoadCount=0;		// Indica la cantidad de ventanas creadas
DWORD	OnRegister=false;	// Ya fue registrada la ventana LFCWnd
ATOM	classAtom;

LRESULT CALLBACK LFCWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CLFCWnd*	lpWnd;
	lpWnd=(CLFCWnd*)GetWindowLong(hWnd,GWL_USERDATA);
	
	return 0;
}

DWORD LFC20Init()
{
	WNDCLASSEX	classData;
	classData.cbSize=sizeof(classData);
	classData.cbClsExtra=0;
	classData.cbWndExtra=0;
	classData.hbrBackground=0;
	classData.hCursor=0;
	classData.hIcon=0;
	classData.hIconSm=0;
	classData.hInstance=(HINSTANCE)GetModuleHandle(NULL);
	classData.lpfnWndProc=LFCWndProc;
	classData.lpszClassName=LFC_CLASSNAME;
	classData.lpszMenuName=0;
	classData.style=CS_OWNDC;
	classAtom=RegisterClassEx(&classData);
	// Si no se puede registrar entonces no se carga la aplicacion
	if (!classAtom)
		return 1;
	return 0;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				break;
			}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}
