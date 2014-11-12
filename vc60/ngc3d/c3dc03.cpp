// c3dc03.cpp: implementation of the CDXEscene class.
//
//////////////////////////////////////////////////////////////////////

#include "c3dc03.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXEscene::CDXEscene()
{

}

CDXEscene::~CDXEscene()
{

}

DWORD CDXEscene::ReadFromResource(char *lpname, char *lptype)
{
	return 0;
}

DWORD CDXEscene::SetD3DDevice(LPDIRECT3DDEVICE7 lpd3ddevice)
{
	m_lpd3ddevice=lpd3ddevice;
	return 0;
}
