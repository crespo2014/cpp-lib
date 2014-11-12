// LockEvent.cpp: implementation of the CLockEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LockEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLockEvent::CLockEvent()
{
	m_hMutex = NULL;
}

CLockEvent::~CLockEvent()
{
	UnInitialize();
}

DWORD CLockEvent::Initialize()
{
	m_hMutex = ::CreateMutex(NULL,FALSE,NULL);
	if (m_hMutex == NULL) return 1;
	return 0;
}

DWORD CLockEvent::UnInitialize()
{
	if (m_hMutex != NULL)
		CloseHandle(m_hMutex);
	m_hMutex = NULL;
	return 0;
}

DWORD CLockEvent::Lock()
{
	switch (WaitForSingleObject(m_hMutex,LOCK_TIMEOUT))
	{
	case WAIT_TIMEOUT:
	case WAIT_ABANDONED:
	case WAIT_FAILED : return 1;
	case WAIT_OBJECT_0 : return 0;
	}
	return 1;
}

DWORD CLockEvent::UnLock()
{
	if (ReleaseMutex(m_hMutex))
		return 0;
	return 1;
}
