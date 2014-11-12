// BlockMem.h: interface for the CBlockMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOCKMEM_H__4C5F235E_AFC1_4972_BBE7_28839ADECCEA__INCLUDED_)
#define AFX_BLOCKMEM_H__4C5F235E_AFC1_4972_BBE7_28839ADECCEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"
#include "imem.h"


/* 
 TODO:	
	Crear un avriable last_lock para agilizar el recorrido por los bloques
 */

struct _mblock {
	struct _mblock* next;
	DWORD	max_index;			// posicion maxima no se puede escribir en este indice
	DWORD	free_index;			// cantidad ocupada, siempres es mayor que el tamao de la estructura
	// indica que este bloque esta bloqueado a partir de este indice y no puede ser utilizado 
	// 0 indica no bloqueado
	DWORD	look_index;			
};

// SnapShot de la memoria
struct _mshot {
	struct _mblock*	block;			// bloque actual
	struct _mshot* next;
};

class CBlockMem  : public IMem, CbObject, private ITube
{
public:
	ITube* getTube() { return this; };
	DWORD lockSize();
	struct _mblock* _lastLock();
	DWORD lockFree();
	DWORD lockClose();
	DWORD lockCompact(void** ppvoid,DWORD* ppsize);
	DWORD lockAdd(void* dt,DWORD size);
	DWORD lockCommit(DWORD size);
	DWORD lockAvaliable(void** ppvoid,DWORD* ppsize);
	DWORD lock();
	DWORD addS(char* str,DWORD size,char **pstr);
	DWORD getU(DWORD size,void **ppvoid) { return _get(size,ppvoid,false); };	
	DWORD get(DWORD size,void** ppvoid)  { return _get(size,ppvoid,true);  };
	DWORD add(void* pdata,DWORD size,void** ppvoid) { return _add(pdata,size,ppvoid,true);  };
	DWORD addU(void* pdata,DWORD size,void** ppvoid) { return _add(pdata,size,ppvoid,false); };

	DWORD	Start();
	DWORD	End();
	DWORD	Push(BYTE b);
	
	DWORD createBlock(DWORD minsize);
	CBlockMem();
	virtual ~CBlockMem();
private:
	void _release();
	DWORD _newBlock(struct _mblock* plast,DWORD size);
	struct _mblock* _look(DWORD size,bool align);
	struct _mblock* _createLock(struct _mblock* plast);
	struct _mblock*	m_first_block,*m_first_lock;
	DWORD _get(DWORD size, void **ppvoid,bool align);
	DWORD _add(void *pdata, DWORD size, void **ppvoid,bool align);

	DWORD			mMinSize;	// el menor tamaño de bloque que se puede reservar
};

#endif // !defined(AFX_BLOCKMEM_H__4C5F235E_AFC1_4972_BBE7_28839ADECCEA__INCLUDED_)
