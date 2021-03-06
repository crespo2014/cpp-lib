#if !defined(AFX_INTERFAZDEF_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_)
#define AFX_INTERFAZDEF_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_

#include "_IUnknown.h"

typedef struct {} INTERFAZ_DEFINICIONES;

#ifdef DLL_EXPORTS	// se define en la linea de comandos de la dll
	#define DLL_API extern "C" __declspec(dllexport)
#else
	#define DLL_API extern "C" __declspec(dllimport)
#endif

// Prototipo de la funcion
typedef DWORD _stdcall DllFunc(char*,LPVOID*);
typedef DllFunc* LPDLLFUNC;
typedef DWORD _stdcall CreateInstanceFunc(char*,_IUnknown**);
typedef CreateInstanceFunc* LPCreateInstanceFunc;

// Declaracion de la funcion 
DLL_API DWORD _stdcall GetInterfaz(char* InterfazName,LPVOID* lpInterfaz);
DLL_API DWORD _stdcall CreateInterfaz(char* InterfazName,LPVOID* lpInterfaz);
DLL_API DWORD _stdcall CreateInstance(char* pName,_IUnknown** lpInstance);

const char* DllFuncGetInterfaz = "_GetInterfaz@8";
const char* DllFuncCreateInterfaz = "_CreateInterfaz@8";
const char* DllFuncCreateInstance = "_CreateInstance@8";

#endif