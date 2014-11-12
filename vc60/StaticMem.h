// StaticMem.h: interface for the CStaticMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATICMEM_H__7ACE85FA_EC6B_456F_8C09_46CFAB65CF62__INCLUDED_)
#define AFX_STATICMEM_H__7ACE85FA_EC6B_456F_8C09_46CFAB65CF62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "imem.h"
#include "itube.h"

class CStaticMem : 
public CbObject ,
public IMem,
private ITube
{
public:
	DWORD _add(void *pdata, DWORD size, void **ppvoid,bool align);
	void SetBlock(void *pblock, DWORD blockSize);
	CStaticMem(void* pblock,DWORD blockSize);
	CStaticMem();
	virtual ~CStaticMem();
	void Reset() { m_block_free = 0; };

	// Implementar ITube
	DWORD	Start();
	DWORD	End();
	DWORD	Push(BYTE b);
	// *******************************

	// Implementacion del IMem
	DWORD getU(DWORD size,void **ppvoid) { return _get(size,ppvoid,false); };	
	DWORD get(DWORD size,void** ppvoid)  { return _get(size,ppvoid,true);  };
	DWORD add(void* pdata,DWORD size,void** ppvoid) { return _add(pdata,size,ppvoid,true);  };
	DWORD addU(void* pdata,DWORD size,void** ppvoid) { return _add(pdata,size,ppvoid,false); };

	DWORD addS(char* str,DWORD size,char **pstr);
	DWORD lock();
	DWORD lockAdd(void* dt,DWORD size);
	DWORD lockAvaliable(void** ppvoid,DWORD* ppsize);
	DWORD lockCommit(DWORD size);
	DWORD lockCompact(void** ppvoid,DWORD* ppsize);
	DWORD lockClose();
	DWORD lockFree();
	DWORD lockSize();
	ITube* getTube() { return this; };
	// *************************
private:
	DWORD _get(DWORD size, void **ppvoid,bool align);
	BYTE	*m_pblock;
	DWORD	m_block_max;		// tamaño maximo del bloque posicion que nose puede utilizar
	DWORD	m_block_free;		//tamaño ocupado o posicion que se puede utilizar
	DWORD	m_look_index;		// a partir de donde esta ocupado el bloque por un lock
	BOOLEAN	m_locked;			// ya que se permite el look_index == 0
};

#endif // !defined(AFX_STATICMEM_H__7ACE85FA_EC6B_456F_8C09_46CFAB65CF62__INCLUDED_)
