// ptr.cpp: implementation of the Cptr class.
//
//////////////////////////////////////////////////////////////////////

#include "ptr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cptr::Cptr()
{
	m_ptr = NULL;
}

Cptr::~Cptr()
{
	if (m_ptr != NULL) delete m_ptr;
	m_ptr = NULL;
}

Cptr::Cptr(CbObject *ptr)
{
	m_ptr = ptr;
}

CbObject* Cptr::Attach(CbObject *ptr)
{
	CbObject*	ptr1 = m_ptr;
	m_ptr = ptr;
	return ptr1;
}

void Cptr::Set(CbObject *ptr)
{
	if (m_ptr != NULL) delete m_ptr;
	m_ptr = ptr;
}
