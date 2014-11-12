// ptr.h: interface for the Cptr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTR_H__4BB59D52_C27D_4CD7_8DA3_CBF66141A2C7__INCLUDED_)
#define AFX_PTR_H__4BB59D52_C27D_4CD7_8DA3_CBF66141A2C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class Cptr : public CbObject  
{
public:
	void Set(CbObject *ptr);
	CbObject* Attach(CbObject* ptr);
	Cptr(CbObject* ptr);
	Cptr();
	virtual ~Cptr();

	CbObject*	m_ptr;

};

#endif // !defined(AFX_PTR_H__4BB59D52_C27D_4CD7_8DA3_CBF66141A2C7__INCLUDED_)
