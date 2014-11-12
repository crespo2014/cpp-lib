// ngsig.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE NgsigDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
    
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("NGSIG.DLL Initializing!\n");
		
		if (!AfxInitExtensionModule(NgsigDLL, hInstance))
			return 0;

		new CDynLinkLibrary(NgsigDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("NGSIG.DLL Terminating!\n");
		AfxTermExtensionModule(NgsigDLL);
	}
	return 1;
}
