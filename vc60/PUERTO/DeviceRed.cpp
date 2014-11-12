// DeviceRed.cpp: implementation of the CDeviceRed class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "puerto.h" 
#include "DeviceRed.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceRed::CDeviceRed()
{

}

CDeviceRed::~CDeviceRed()
{

}

int CDeviceRed::SendFrame(BYTE *pBuffer, DWORD pCant)
{
	DWORD	Event;
	SetParity(MARKPARITY);
	if (SendBuffer(pBuffer,1)!=0)
		AfxMessageBox("Error enviando datos");
	if (WaitCommEvent(PortHandle,&Event,NULL)==0)
		AfxMessageBox("Huye que la cosa esta fea");
	SetParity(SPACEPARITY);
	if (SendBuffer(pBuffer+1,pCant-1)!=0)
		AfxMessageBox("Error enviando datos");
	if (WaitCommEvent(PortHandle,&Event,NULL)==0)
		AfxMessageBox("Huye que la cosa esta fea");
	return true;
}
