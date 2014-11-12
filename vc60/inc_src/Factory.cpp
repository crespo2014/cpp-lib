// Factory.cpp: implementation of the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Factory.h"
#include "_IUnknown.h"
#include "errorcodes.h"

// Definiciones ocultas

#define MAX_INSTANCE	20

struct INSTANCE
{
	HMODULE		hdll;
	_IUnknown*	lpInstance;
};

typedef DWORD _stdcall CreateInstanceFunc(char*,_IUnknown**);
typedef CreateInstanceFunc* LPCreateInstanceFunc;

// Codigo

INSTANCE Instances[MAX_INSTANCE];

DWORD CreateInstance(char* lpDllName,char* lpInstanceName,_IUnknown** lpInstance)
{
	DWORD	Index;
	DWORD	dr;
	LPCreateInstanceFunc CreateInstance;
 
	// Buscar una casilla vacia;
	for (Index=0;Index<MAX_INSTANCE;Index++)
	{
		if (Instances[Index].hdll == NULL) break;
	}
	if (Index == MAX_INSTANCE) return ERR_NOMEMORY;
	for (;;)
	{
		dr = ERR_APIFAIL;
		Instances[Index].hdll = LoadLibrary(lpDllName);
		if (Instances[Index].hdll == NULL) break;
		dr = ERR_NOINTERFACE;
		CreateInstance = (LPCreateInstanceFunc)GetProcAddress(Instances[Index].hdll,"_CreateInstance@8");
		if (CreateInstance == NULL) break;
		dr = CreateInstance(lpInstanceName,&Instances[Index].lpInstance);
		if (dr != ERR_NONE) break;
		*lpInstance = Instances[Index].lpInstance;
		return ERR_NONE;
	}
	if (Instances[Index].hdll)	
	{
		FreeLibrary(Instances[Index].hdll);
		Instances[Index].hdll = NULL;
	}
	lpInstance = NULL;
	return dr;
}

DWORD DeleteInstance(_IUnknown* lpInstance)
{
	WORD	Index;
	// buscar el index
	for (Index=0;Index<MAX_INSTANCE;Index++)
	{
		if (Instances[Index].lpInstance == lpInstance) break;
	}
	if (Index == MAX_INSTANCE) return ERR_NOINTERFACE;
	if (Instances[Index].lpInstance->Release() == 0)
	{
		FreeLibrary(Instances[Index].hdll);
		Instances[Index].hdll = NULL;
		return ERR_NONE;
	}
	return ERR_FAIL;
}
