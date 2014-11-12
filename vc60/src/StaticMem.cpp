// StaticMem.cpp: implementation of the CStaticMem class.
//
//////////////////////////////////////////////////////////////////////

#include "StaticMem.h"

#define _FILENAME_ "staticmem.c"

#define _CHECK_BLOCK_	if ((!m_pblock)||(!m_block_max))	return _LOG_ERROR ERR_HANDLE,"Memory is undefined");
#define _CHECK_NO_LOCK_	if (m_locked)						return _LOG_ERROR ERR_IS_LOCK,"Memory is locked");
#define _CHECK_IS_LOCK_	if (!m_locked)						return _LOG_ERROR ERR_IS_LOCK,"Memory is not locked");
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStaticMem::CStaticMem()
{
	
}

CStaticMem::~CStaticMem()
{
	
}

CStaticMem::CStaticMem(void *pblock, DWORD blockSize)
{
	m_pblock = (BYTE*)pblock;
	m_block_max = blockSize;
	m_block_free = 0;
	m_locked = 0;
}

void CStaticMem::SetBlock(void *pblock, DWORD blockSize)
{
	m_pblock = (BYTE*)pblock;
	m_block_max = blockSize;
	m_block_free = 0;
	m_locked = 0;
}


DWORD CStaticMem::addS(char* str,DWORD size,char **pstr)
{
	void*	pvoid;
	if (size == 0)
	{
		char	*cptr=str;
		while (*cptr++ != 0);
		size = (DWORD)(cptr-str+1);
	}
	if (_get(size,&pvoid,false) != ERR_OK) return _LOG_AT;
	memcpy(pvoid,str,size-1);
	((BYTE*)pvoid)[size] = 0;
	*pstr = (char*)pvoid;
	return ERR_OK;	
}

DWORD CStaticMem::lock()
{
	_CHECK_BLOCK_;
	_CHECK_NO_LOCK_;

	m_locked = true;

	m_look_index = m_block_free;		// anotamos la posicion libre
	// comenzamos con memoria alineada para pode devolver un compact
	if (m_block_free & (sizeof(void*)-1)) 
	{
		m_block_free = (m_block_free + sizeof(void*)) & ~(sizeof(void*)-1);
	}
	return ERR_OK;
}

DWORD CStaticMem::lockAdd(void* dt,DWORD size)
{
	_CHECK_IS_LOCK_;
	if (m_block_free + size > m_block_max) return _LOG_ERROR ERR_OVERFLOW,"No memory for %d bytes remain is %d ",size,m_block_max-m_block_free);	
	memcpy(&m_pblock[m_block_free],dt,size);
	m_block_free += size;
	return ERR_OK;
}

DWORD CStaticMem::lockAvaliable(void** ppvoid,DWORD* ppsize)
{
	_CHECK_IS_LOCK_;
	*ppsize = m_block_max - m_block_free;
	*ppvoid = &m_pblock[m_block_free];
	return ERR_OK;
}

DWORD CStaticMem::lockCommit(DWORD size)
{
	_CHECK_IS_LOCK_;
	if (m_block_free + size > m_block_max) return _LOG_ERROR ERR_OVERFLOW,"overflow");
	m_block_free += size;
	return ERR_OK;
}

DWORD CStaticMem::lockCompact(void** ppvoid,DWORD* ppsize)
{
	// vamos a comprobar la alineacion
	_CHECK_IS_LOCK_;
	DWORD pos;

	if (m_look_index & (sizeof(void*)-1)) 
	{
		pos = (m_look_index + sizeof(void*)) & ~(sizeof(void*)-1);
	}
	else
		pos = m_look_index;

	*ppvoid = &m_pblock[pos];
	if (ppsize) *ppsize = m_block_free - pos;
	return ERR_OK;
}

DWORD CStaticMem::lockClose()
{
	_CHECK_IS_LOCK_;
	m_locked = false;
	return ERR_OK;
}

DWORD CStaticMem::lockFree()
{
	_CHECK_IS_LOCK_;
	m_locked = false;
	m_block_free = m_look_index;
	return ERR_OK;
}

DWORD CStaticMem::lockSize()
{
	if (!m_locked) return 0;
	DWORD pos;

	if (m_look_index & (sizeof(void*)-1)) 
	{
		pos = (m_look_index + sizeof(void*)) & ~(sizeof(void*)-1);
	}
	else
		pos = m_look_index;
	return m_block_free - pos;
}

DWORD CStaticMem::_get(DWORD size, void **ppvoid, bool align)
{
	DWORD	offset;
	_CHECK_BLOCK_;
	_CHECK_NO_LOCK_;
	
	offset = m_block_free;
	if (align)
	{
		if (m_block_free & (sizeof(void*)-1)) offset = (m_block_free + sizeof(void*)) & ~(sizeof(void*)-1);
	}
	if (offset + size > m_block_max) return _LOG_ERROR ERR_OVERFLOW,"No memory for %d bytes remain is %d ",size,m_block_max-m_block_free);	
	*ppvoid = &m_pblock[offset];
	m_block_free = offset + size;
	return ERR_OK;
}

DWORD CStaticMem::_add(void *pdata, DWORD size, void **ppvoid, bool align)
{
	void*	pvoid;
	if (_get(size,&pvoid,align) != ERR_OK) return _LOG_AT;
	memcpy(pvoid,pdata,size);
	*ppvoid=pvoid;
	return ERR_OK;
}

// Implementar ITube
DWORD	CStaticMem::Start()
{
	return lock();
}
DWORD	CStaticMem::End()
{
	return ERR_OK;
}
DWORD	CStaticMem::Push(BYTE b)
{
	_CHECK_IS_LOCK_;
	if (m_block_free + 1 > m_block_max) return _LOG_ERROR ERR_NOMEMORY,"Memory is full");	
	m_pblock[m_block_free] = b;
	m_block_free ++;
	return ERR_OK;
}
