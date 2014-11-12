// SockAddr.cpp: implementation of the CSockAddr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SockAddr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSockAddr::CSockAddr()
{
	sin_family=AF_INET;
	sin_port=0;
	sin_addr.s_addr=0;

}

CSockAddr::~CSockAddr()
{

}

CSockAddr::CSockAddr(const ULONG ulAddr, const USHORT ushPort)
{
	sin_family=AF_INET;
	sin_port=htons(ushPort);
	sin_addr.s_addr=htonl(ulAddr);

}


