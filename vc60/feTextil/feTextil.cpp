// feTextil.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Textilwind.h"
#include "dbCommon.h"
#include "errorcodes.h"

CTextilWind	MainWind;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	INITCOMMONCONTROLSEX icex;
	DWORD dr;
	MSG msg;
	
	if (CoInitialize(NULL) != S_OK) return -1;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_DATE_CLASSES;
    if (!InitCommonControlsEx(&icex)) return -1;
	dr = RegisterCWind();
	if (dr != ERR_NONE) return -1;
	dr = MainWind.Initialize();
	if (dr != ERR_NONE) return dr;
	dr = MainWind.Create_Window();
	if (dr != ERR_NONE) return dr;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!MainWind.PreTranslateMessage(&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
 	return 0;
}



