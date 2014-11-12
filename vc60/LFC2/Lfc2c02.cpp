// lfc2c02.cpp: implementation of the CShareSignalDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lfc2c02.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareSignalDevice::CShareSignalDevice()
{
	Initialize();
}

CShareSignalDevice::~CShareSignalDevice()
{

}

CSignalDevice* CShareSignalDevice::GetSignalDevice()
{
	return lpSignalDevice;
}

DWORD CShareSignalDevice::Initialize()
{
	ZeroMemory(this,sizeof(CShareSignalDevice));
	return 0;
}

DWORD CShareSignalDevice::Release()
{
	if (lpSignalDevice)
		if (OnCreate)
		{
			lpSignalDevice->Release();
			::UnmapViewOfFile(lpSignalDevice);
		}
	if (hMapObject)
		::CloseHandle(hMapObject);
	lpSignalDevice=NULL;
	hMapObject=NULL;
	OnCreate=false;
	return 0;
}

/*
	Busca un CSignalDevice que ya fue creado	
*/
DWORD CShareSignalDevice::Open()
{
	if (lpSignalDevice!=NULL)
		return 1;
	hMapObject=::OpenFileMapping(FILE_MAP_ALL_ACCESS,
		TRUE,
		"CSignalDevice");
	if(hMapObject==NULL)
		goto failed;
	lpSignalDevice=(CSignalDevice*)::MapViewOfFile(hMapObject,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0);
	if (lpSignalDevice==NULL)
		goto failed;
	/*
		Aqui hay que asegurarse que ya esta 
		inicializada la clase CSignalDevice
	*/
	return 0;
failed:
	Release();
	return 1;
}
/*
	Crea una nueva clase CSignalDevice
*/
DWORD CShareSignalDevice::Create()
{
	if (lpSignalDevice!=NULL)
		return 1;
	hMapObject=::CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		sizeof(CSignalDevice),
		"CSignalDevice");
	if (hMapObject == NULL)
		goto failed;
	if (GetLastError()==ERROR_ALREADY_EXISTS)
		goto failed;
	
	lpSignalDevice=(CSignalDevice*)::MapViewOfFile(hMapObject,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);
	if (lpSignalDevice==NULL)
		goto failed;
	ZeroMemory(lpSignalDevice,sizeof(CSignalDevice));
	if (lpSignalDevice->Initialize()!=0)
		goto failed;
	OnCreate=true;
	return 0;
failed:
	CloseHandle(hMapObject);
	lpSignalDevice=NULL;
	hMapObject=NULL;
	return 1;
}
