// VirtualMemory.h: interface for the CVirtualMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALMEMORY_H__5F3BB279_94F8_449A_9128_7536009239EE__INCLUDED_)
#define AFX_VIRTUALMEMORY_H__5F3BB279_94F8_449A_9128_7536009239EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

typedef struct _MEMORY_BLOCK
{
	struct _MEMORY_BLOCK*	lpnext;
	BYTE   Data[0];			// [0..m_blockSize-1]	
} MEMORY_BLOCK;

typedef struct
{
	MEMORY_BLOCK*	mb;
	DWORD			pos;
} MEMORY_PTR;

#define SYNC_TIMEOUT 10 

class CVirtualMemory  
{
public:
	DWORD GetAbsolutePos(DWORD dwIndex,BYTE **lpbData);
	DWORD MemMove(DWORD dwDestIndex,DWORD dwSrcIndex);
	DWORD MovePos(DWORD dwCant,MEMORY_BLOCK** lplpMB,DWORD* lpdwPos,BOOL bForward = TRUE);
	DWORD Size();
	DWORD CopyBuffer(DWORD dwIndex,BYTE* lpBuffer,DWORD dwSize,BOOL bLock = TRUE);
	DWORD GetValue(BYTE* lpValue);
	DWORD GetValueMoveNext(BYTE* lpValue);
	DWORD SetValue(BYTE bValue);
	DWORD Initialize();
	DWORD IndexToBlock(DWORD dwIndex,MEMORY_BLOCK** lplpMB,DWORD* lpdwPos,BOOL bLock = TRUE);
	DWORD SetSize(DWORD dwSize,BOOL	bLock = TRUE);
	DWORD DeleteFromBeginNoMove(DWORD dwCant);
	DWORD CopyBlock(DWORD dwDestIndex,DWORD dwSrcIndex,DWORD dwCant);
	DWORD GetSize(DWORD* lpdwSize);
	DWORD DeleteBlock(DWORD dwIndex,DWORD dwCant);
	DWORD MoveBlock(DWORD dwDestIndex,DWORD dwSrcIndex, DWORD dwCant);
	DWORD GetBuffer(DWORD dwIndex,DWORD dwCant,BYTE *lpBuffer);
	DWORD InsertBuffer(DWORD dwIndex,BYTE *lpBuffer, DWORD dwCant);
	DWORD AddData(BYTE* lpBuffer,DWORD dwCant);
	DWORD GetValue(DWORD dwIndex,BYTE* lpValue);
	DWORD Move(DWORD dwCant,BOOL bForward = TRUE);
	DWORD MoveTo(DWORD dwIndex);
	DWORD GetNextValue(BYTE* lpbyte);
	DWORD AddBlock(MEMORY_BLOCK** lplpmemblock);
	CVirtualMemory();
	virtual ~CVirtualMemory();
private:
	DWORD	m_Size;				// Cantidad de bytes utilizados
	DWORD	m_CurrentBlockPos;	// Posicion dentro del bloque
	DWORD	m_LastPos;			// Ultimo bloque maxima posicion
	DWORD	m_FirstPos;			// Posicion de inicio del primer bloque
	DWORD	m_BlockSize;		// Tamaño de bloque o pagina
	HANDLE	m_SyncEvent;		// Evento utilizado para sincronizacion
	DWORD	m_CurrentIndex;		// Posicion absoluta actual
	MEMORY_BLOCK* m_FirstBlock;
	MEMORY_BLOCK* m_CurrentBlock;	//
	
	
};

#endif // !defined(AFX_VIRTUALMEMORY_H__5F3BB279_94F8_449A_9128_7536009239EE__INCLUDED_)
