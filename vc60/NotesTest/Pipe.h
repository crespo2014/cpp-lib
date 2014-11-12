// Pipe.h: interface for the CPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIPE_H__C1195C93_81F3_43F8_BFC4_76932F688D13__INCLUDED_)
#define AFX_PIPE_H__C1195C93_81F3_43F8_BFC4_76932F688D13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"

class CPipe  : public CbObject
{
public:
	DWORD Create(char* pipe_name);
	CPipe();
	virtual ~CPipe();
private:
	HANDLE	m_hpipe;
	char	m_pipe_name[255];
};

#endif // !defined(AFX_PIPE_H__C1195C93_81F3_43F8_BFC4_76932F688D13__INCLUDED_)
