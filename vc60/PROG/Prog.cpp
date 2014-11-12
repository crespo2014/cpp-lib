// Prog.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "..\g30\g30c03.h"   //CGameWind

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	if (LFC30Initialize(hInstance)!=0)
		return 1;
	CGameWind	Wind;
	Wind.Initialize();
	Wind.Run();
	return 0;
}



