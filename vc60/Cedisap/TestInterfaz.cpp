// TestInterfaz.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "..\interfaces\IServoDriver.h"
#include "..\interfaces\interfazdef.h"
#include "..\interfaces\iservo.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// TODO: Place code here.
	HMODULE HDll;
	LPDLLFUNC DllFunc;
	IServoDriver*	lpv;
	IServo*			Servo1;

	HDll = LoadLibrary("c:\\lib\\dllinterfaces.dll");
	DllFunc = (LPDLLFUNC)GetProcAddress(HDll,DllFuncName);
	if (DllFunc == NULL)
		return 0;
	
	DllFunc("IServoDriver",(LPVOID*)&lpv);
	if (lpv == NULL)
		return 0;
	/*
	lpv->SetCommunicationPort(2);
	lpv->StartCommunication();
	lpv->GetBedServo(1,&Servo1);
	DWORD ConectionStat;
	Servo1->IsConnect();
	*/
	Sleep(1000*60*30);
	return 0;

}



