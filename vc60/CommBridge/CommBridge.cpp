// CommBridge.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "commbridgewind.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if (RegisterCWind() != 0)
		return 1;
	CCommBridgeWind MainWind;
	if (MainWind.Initialize() != 0)
		return 1;
	if (MainWind.Create_Window() !=0)
		return 1;
	MSG msg;
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	MainWind.Release();
	return 0;
}



