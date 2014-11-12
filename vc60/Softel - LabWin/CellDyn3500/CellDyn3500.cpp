// CellDyn3500.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "CellDyn3500_.h"
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
		CCellDyn3500	cellDyn3500;
		dr = DLLCreateInstance((void**)lpInstance,&cellDyn3500,sizeof(CCellDyn3500));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ILabDevice",(void**)lpInstance);
	}
	return ERR_NONE;
}