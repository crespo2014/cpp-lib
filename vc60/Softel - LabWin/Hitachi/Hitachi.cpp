// Hitachi.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "dllCommon.h"
#include "errorcodes.h"
#include "hitachi00a.h"

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
	if (strcmp(pName,"ILabDevice") == 0)
	{
		CHitachi00A	hitachi;
		dr = DLLCreateInstance(lpInstance,&hitachi,sizeof(CHitachi00A));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ILabDevice",lpInstance);
	}
	return ERR_NONE;
}