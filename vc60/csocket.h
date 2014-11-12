// csocket.h: interface for the csocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSOCKET_H__512CA647_A61A_4C18_85B0_6CB3F1BADBD2__INCLUDED_)
#define AFX_CSOCKET_H__512CA647_A61A_4C18_85B0_6CB3F1BADBD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// el objeto base depende del sistema operativo y debe implementar todas las funciones 
// comunes

#ifdef WIN32

#include "w32\sysocket.h"

#else

#include "linux\csocket.h"

#endif

#include "bObject.h"


class csocket : public csysocket  
{
public:
	DWORD close();
	csocket();
	virtual ~csocket();
	const char* get_dw_error_text(const DWORD dwcode); 
	DWORD ip4_connect(BYTE* ip,DWORD port);
};

#endif // !defined(AFX_CSOCKET_H__512CA647_A61A_4C18_85B0_6CB3F1BADBD2__INCLUDED_)
