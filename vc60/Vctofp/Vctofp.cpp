// Vctofp.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "ILabDevice.h"
#include "interfazdef.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

// Funciones a exportar para utilizar en el foxpro

ILabDevice* LabDevice = NULL;
HMODULE		hDll = NULL;

extern "C" __declspec(dllexport) DWORD __cdecl LoadDriver(char* chName)
{
	LPDLLFUNC DllFunc;
	hDll = LoadLibrary(chName);
	if (hDll == NULL) return ERR_NODRIVE;
	DllFunc = (LPDLLFUNC)GetProcAddress(hDll,DllFuncGetInterfaz);
	if (DllFunc == NULL) return ERR_NODRIVE;
	DllFunc("ILabDevice",(LPVOID*)&LabDevice);
	if (LabDevice == NULL) return ERR_NODRIVE;
	return 0;
}

extern "C" __declspec(dllexport) DWORD __cdecl UnLoadDriver()
{
	::FreeLibrary(hDll);
	return 0;
}

extern "C" __declspec(dllexport) DWORD __cdecl GetResults()
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->GetResults();
}

extern "C" __declspec(dllexport) DWORD __cdecl Initialize()
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->Initialize();
}

extern "C" __declspec(dllexport) DWORD __cdecl SetLocalConfiguration(short sPort,DWORD dwBaudRate,short sParity,short sStopBits)
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->SetLocalConfiguration((BYTE)sPort,dwBaudRate,(BYTE)sParity,(BYTE)sStopBits);
}

extern "C" __declspec(dllexport) DWORD __cdecl SetRemoteConfiguration(short b1,short b2,short b3,short b4,short port)
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->SetRemoteConfiguration((BYTE)b1,(BYTE)b2,(BYTE)b3,(BYTE)b4,port);
}

extern "C" __declspec(dllexport) DWORD __cdecl CheckCap(DWORD dwCapability)
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->CheckCap(dwCapability);
}

extern "C" __declspec(dllexport) DWORD __cdecl OpenConnection()
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->Connect();
}

extern "C" __declspec(dllexport) DWORD __cdecl CloseConnection()
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->Disconnect();
}

extern "C" __declspec(dllexport) DWORD __cdecl GetResultByPos(DWORD PatPos,DWORD AnaPos,float* lpResult)
{
	if (LabDevice == NULL) return ERR_NODRIVE;
	return LabDevice->GetResultByPos(PatPos,AnaPos,lpResult);
}
