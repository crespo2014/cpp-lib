// cconsole.h: interface for the cconsole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCONSOLE_H__F402FA80_ABCE_4D0F_9C92_0E6540707CD3__INCLUDED_)
#define AFX_CCONSOLE_H__F402FA80_ABCE_4D0F_9C92_0E6540707CD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32

#include "w32\sysconsole.h"

#else

#include "linux\sysconsole.h"

#endif

#include "bobject.h"

// Definir el objeto con las estructuras propias del SO.
// y los metodo comunes.

class cconsole  : public csysconsole , CbObject
{
public:
	cconsole();
	virtual ~cconsole();
	void close();
	DWORD open();
	DWORD	write(const void* buffer, const DWORD size);
	BOOL	isOpen();

};

#endif // !defined(AFX_CCONSOLE_H__F402FA80_ABCE_4D0F_9C92_0E6540707CD3__INCLUDED_)
