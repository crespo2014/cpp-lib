// LockEvent.h: interface for the CLockEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOCKEVENT_H__324936B2_7C98_48E0_8E80_077C77B0DC7A__INCLUDED_)
#define AFX_LOCKEVENT_H__324936B2_7C98_48E0_8E80_077C77B0DC7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LOCK_TIMEOUT INFINITE 

class CLockEvent  
{
public:
	DWORD UnLock();
	DWORD Lock();
	DWORD UnInitialize();
	DWORD Initialize();
	CLockEvent();
	~CLockEvent();
private:
	HANDLE	m_hMutex;

};

#endif // !defined(AFX_LOCKEVENT_H__324936B2_7C98_48E0_8E80_077C77B0DC7A__INCLUDED_)
