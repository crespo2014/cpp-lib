// ct10c1.cpp: implementation of the CPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CT10.h"
#include "ct10c1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPort::CPort()
{

}

CPort::~CPort()
{

}

int CPort::OnReceiveData(BYTE* pBuffer, DWORD pCant)
{
	Dlg->SendMessage(RECEIVED_DATA,(DWORD)pBuffer,(DWORD)pCant);
	return true;
}


