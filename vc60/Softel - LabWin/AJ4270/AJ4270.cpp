// AJ4270.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "AJ_4270.h"
#include "dllcommon.h"
#include "errorcodes.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

extern "C" __declspec(dllexport)
DWORD _stdcall CreateInstance(char* pName,void** lpInstance)
{
	DWORD dr;
	if (strcmp(pName,"ILabDevice") == 0)
	{
		CAJ_4270	AJ4270;
		dr = DLLCreateInstance(lpInstance,&AJ4270,sizeof(CAJ_4270));
		if (dr != ERR_NONE) return dr;
		dr = ((_IUnknown*)(*lpInstance))->QueryInterface("ILabDevice",(void**)lpInstance);
	}
	return ERR_NONE;
}

