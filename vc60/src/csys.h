// csys.h: interface for the csys class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSYS_H__9D434836_C231_4793_A348_C2EB9B8C05EA__INCLUDED_)
#define AFX_CSYS_H__9D434836_C231_4793_A348_C2EB9B8C05EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "cstr.h"

class csys : public CbObject  
{
public:

	static void* getrootFolder(char* buff,WORD size);
	static char getFileSeparator();
	static void* gettmpFolder(char* buff,WORD size);
	static void* getUserFolder(char* buff,WORD size);

	csys();
	virtual ~csys();
	static DWORD	getPID();
	static DWORD	getTID();

};

#endif // !defined(AFX_CSYS_H__9D434836_C231_4793_A348_C2EB9B8C05EA__INCLUDED_)
