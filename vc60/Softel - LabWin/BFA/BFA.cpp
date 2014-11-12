// BFA.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "bfa_.h"
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
		CBFA	bfa;
		dr = DLLCreateInstance((void**)lpInstance,&bfa,sizeof(CBFA));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ILabDevice",(void**)lpInstance);
	}
	return ERR_NONE;
}