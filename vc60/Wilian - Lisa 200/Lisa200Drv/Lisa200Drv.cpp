// Lisa200Drv.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Lisa200Drv.h"
#include "Lisa200.h"
#include "..\interfaces\Interfazdef.h"
#include "..\interfaces\ILabDevice.h"
#include "..\clases\common.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			if (InitializeWinSock() != 0) return FALSE;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

CLisa200 Lisa200;

DLL_API DWORD _stdcall GetInterfaz(char* InterfazName,LPVOID* lpInterfaz)
{
	if (strcmp(InterfazName,"ILabDevice")==0)
	{
		ILabDevice* Ilab = &Lisa200;
		*lpInterfaz = Ilab;
		return 0;
	}
	*lpInterfaz = NULL;
	return 1;
}
