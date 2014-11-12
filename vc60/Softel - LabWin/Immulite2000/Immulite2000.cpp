// Immulite2000.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Immulite2000_.h"
#include "dllcommon.h"
#include "errorcodes.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" __declspec(dllexport) DWORD _stdcall CreateInstance(char* pName,_IUnknown** lpInstance)
{
	DWORD dr;
	if (strcmp(pName,"ILabDevice") == 0)
	{
		CImmulite2000	immulite2000;
		dr = DLLCreateInstance((void**)lpInstance,&immulite2000,sizeof(CImmulite2000));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ILabDevice",(void**)lpInstance);
	}
	return ERR_NONE;
}