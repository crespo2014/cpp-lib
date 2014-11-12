// VCtoVB.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "interfazdef.h"
#include "vblabdevice.h"
#include "errorcodes.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

LABDEVICE LabDevice[MAX_LABDEVICE];

BOOL Check_Handle(DWORD Handle)
{
	if (Handle >= MAX_LABDEVICE) return false;
	if (LabDevice[Handle].hdll == NULL) return false;
	return true;
}
DWORD _stdcall Init()
{
	return 0;
}

//extern "C" __declspec(dllexport)
DWORD _stdcall LabDevice_Load(char* lpdllName,LPDWORD lpHandle)
{
	DWORD	Index;
	DWORD	dr;
	LPCreateInstanceFunc CreateInstance;
 
	// Buscar una casilla vacia;
	for (Index=0;Index<MAX_LABDEVICE;Index++)
	{
		if (LabDevice[Index].hdll == NULL) break;
	}
	if (Index == MAX_LABDEVICE) return ERR_NOMEMORY;
	for (;;)
	{
		dr = ERR_APIFAIL;
		LabDevice[Index].hdll = LoadLibrary(lpdllName);
		if (LabDevice[Index].hdll == NULL) break;
		dr = ERR_NOINTERFACE;
		CreateInstance = (LPCreateInstanceFunc)GetProcAddress(LabDevice[Index].hdll,"_CreateInstance@8");
		if (CreateInstance == NULL) break;
		dr = CreateInstance("ILabDevice",(_IUnknown**)&LabDevice[Index].lpInstance);
		if (dr != ERR_NONE) break;
		*lpHandle = Index;
		return ERR_NONE;
	}
	if (LabDevice[Index].hdll)	
	{
		FreeLibrary(LabDevice[Index].hdll);
		LabDevice[Index].hdll = NULL;
	}
	*lpHandle = MAX_LABDEVICE; 
	return dr;
}

//extern "C" __declspec(dllexport)
DWORD _stdcall LabDevice_UnLoad(DWORD Handle)
{
	if (Handle >= MAX_LABDEVICE) return ERR_OUT_RANGE;
	if (LabDevice[Handle].hdll == NULL) return ERR_OUT_RANGE;

	LabDevice[Handle].lpInstance->Release();
	FreeLibrary(LabDevice[Handle].hdll);
	LabDevice[Handle].hdll = NULL;
	return ERR_NONE;
}

DWORD _stdcall LabDevice_Initialize(DWORD Handle)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->Initialize();
}

DWORD _stdcall LabDevice_SetPort(DWORD Handle,BYTE port)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->SetPort(port);
}

DWORD _stdcall LabDevice_GetName(DWORD Handle,char* lpBuffer,DWORD* bufferSize)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->GetName(lpBuffer,bufferSize);
}

DWORD _stdcall LabDevice_SetPortConfiguration(DWORD Handle,DWORD dwBaudRate,BYTE bParity,BYTE bStopBits)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->SetPortConfiguration(dwBaudRate,bParity,bStopBits);
}

DWORD _stdcall LabDevice_GetPortConfiguration(DWORD Handle,DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->GetPortConfiguration(dwBaudRate,bParity,bStopBits);
}

DWORD _stdcall LabDevice_Connect(DWORD Handle)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->Connect();
}

DWORD _stdcall LabDevice_Disconnect(DWORD Handle)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->Disconnect();
}

DWORD _stdcall LabDevice_GetResults(DWORD Handle,ANALYSIS* lpResults,DWORD* lpCount)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->GetResults(lpResults,lpCount);
}

DWORD _stdcall LabDevice_ClearResults(DWORD Handle)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->ClearResults();

}

DWORD _stdcall LabDevice_ProcessFile(DWORD Handle,char* lpFileName)
{
	if (!Check_Handle(Handle)) return ERR_INV_HANDLE;
	return LabDevice[Handle].lpInstance->ProcessFile(lpFileName);
}