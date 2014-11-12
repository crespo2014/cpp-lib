// Servo900C.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ServoSV900CDriver.h"
#include "Interfazdef.h"
#include "ServoSV900C.h"

CServoSV900CDriver Servo900CDriver;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

DLL_API DWORD _stdcall GetInterfaz(char* InterfazName,LPVOID* lpInterfaz)
{
	if (Servo900CDriver.GetInterfaz(InterfazName,lpInterfaz)==0)
		return 0;
	return 1;
}

DLL_API DWORD _stdcall CreateInterfaz(char* InterfazName,LPVOID* lpInterfaz)
{
	return 1;
}

DWORD test(float* p)
{
	float (*p2)[10];
	p2 = new float[5][10];
	return 0;
}
