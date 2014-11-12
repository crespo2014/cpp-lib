// SerialPort32.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "errorcodes.h"
#include "serialport.h"
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
	if (strcmp(pName,"ISerialPort") == 0)
	{
		CSerialPort	sp;
		dr = DLLCreateInstance((void**)lpInstance,&sp,sizeof(CSerialPort));
		if (dr != ERR_NONE) return dr;
		dr = (*lpInstance)->QueryInterface("ISerialPort",(void**)lpInstance);
	}
	return ERR_NONE;
}

