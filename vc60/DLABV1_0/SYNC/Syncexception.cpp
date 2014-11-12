// SyncException.cpp: implementation of the CSyncException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SyncException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSyncException,CException)

CSyncException::CSyncException(CString error)
{
	msg_error=error;
}

CSyncException::~CSyncException()
{

}

CString CSyncException::GetErrorMsg()
{
	return msg_error;

}
