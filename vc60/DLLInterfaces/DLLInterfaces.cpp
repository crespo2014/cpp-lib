// DLLInterfaces.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "DLLInterfaces.h"
#include "IServoSV900CDriver.h"
#include "Interfazdef.h"

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

IServoSV900CDriver Servo900CDriver;

DLL_API DWORD _stdcall GetInterfaz(char* InterfazName,LPVOID* lpInterfaz)
{
	if (Servo900CDriver.GetInterfaz(InterfazName,lpInterfaz)==0)
		return 0;
	return 0;
}