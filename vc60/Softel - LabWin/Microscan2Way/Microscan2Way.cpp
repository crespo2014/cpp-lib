// Microscan2Way.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Microscan2Way_.h"
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
		CMicroscan2Way	microscan2Way;
		dr = DLLCreateInstance((void**)lpInstance,&microscan2Way,sizeof(CMicroscan2Way));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ILabDevice",(void**)lpInstance);
	}
	return ERR_NONE;
}
