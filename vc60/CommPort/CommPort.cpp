// CommPort.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Wind.h"
#include "commportwind.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	int a = CBS_DROPDOWNLIST|WS_CHILDWINDOW|ES_LEFT|WS_TILED|WS_VISIBLE|WS_TABSTOP;
	if (RegisterCWind() != 0)
		return 1;
	CCommPortWind MainWind;
	MainWind.Initialize();
	if (MainWind.Create_Window() !=0)
		return 1;
	MSG msg;
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



