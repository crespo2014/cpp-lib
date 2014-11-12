// SV300.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "errorcodes.h"
#include "servo300.h"
#include "_IUnknown.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" __declspec(dllexport)
DWORD _stdcall CreateInstance(char* pName,_IUnknown** lpInstance)
{
	DWORD dr;
	if (strcmp(pName,"IServo") == 0)
	{
		CServo300	sv;
		dr = DLLCreateInstance(lpInstance,(IServo*)&sv,sizeof(CServo300));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("IServo",lpInstance);
	}
	return ERR_NONE;
}