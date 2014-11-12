// Lisa2000.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "Lisa2000Client.h"
#include "Lisa2000def.h"
#include "Lisa200Wind.h"
#include "..\clases\common.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	if (InitializeWinSock() != 0) return 1;
	if (RegisterCWind() != 0) return 1;

	
	CLisa200Wind	Lisa200Wind;
	Lisa200Wind.Initialize();
	if (Lisa200Wind.Create_Window() != 0)
		MessageBox(NULL,"Aplication failed to initialize","Lisa 200 Monitor",MB_ICONSTOP|MB_TASKMODAL);
	
	MSG msg;
	// Main message loop:
	for (;;)
	{
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;

}

