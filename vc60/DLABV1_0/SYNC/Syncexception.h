// SyncException.h: interface for the CSyncException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCEXCEPTION_H__046D18C1_5DEC_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_SYNCEXCEPTION_H__046D18C1_5DEC_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CSyncException : public CException  
{
	DECLARE_DYNAMIC(CSyncException)
public:
	CString GetErrorMsg();
	CString msg_error;
	CSyncException(CString error);
	virtual ~CSyncException();

};

#endif // !defined(AFX_SYNCEXCEPTION_H__046D18C1_5DEC_11D3_8023_0000E8DE4B3B__INCLUDED_)
