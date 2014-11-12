// VirtualMemory.cpp: implementation of the CVirtualMemory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VirtualMemory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVirtualMemory::CVirtualMemory()
{
	m_CurrentBlock = NULL;
	m_CurrentBlockPos = 0;
	m_FirstBlock = NULL;
	m_FirstPos = 0;
	m_BlockSize = 0;
	m_Size = 0;
}

CVirtualMemory::~CVirtualMemory()
{

}

DWORD CVirtualMemory::GetNextValue(BYTE *lpbyte)
{
	if (WaitForSingleObject(m_SyncEvent,10) !=  WAIT_OBJECT_0)
		return 1;
	if (m_CurrentIndex < m_Size)
	{
		// Moverse al proximo byte
		if (m_CurrentBlockPos + 1 == m_BlockSize)
		{
			m_CurrentBlock = m_CurrentBlock->lpnext;
			m_CurrentBlockPos = 0;
		}
		else
			m_CurrentBlockPos++;

	}
	else
		return 2;	// No hay nada que recoger
	m_CurrentIndex++;
	*lpbyte = m_CurrentBlock->Data[m_CurrentBlockPos];
	SetEvent(m_SyncEvent);
	return 0;
}

DWORD CVirtualMemory::MoveTo(DWORD dwIndex)
{
	DWORD	result = 0;
	if (WaitForSingleObject(m_SyncEvent,10) !=  WAIT_OBJECT_0)
		return 1;
	result = IndexToBlock(dwIndex,&m_CurrentBlock,&m_CurrentBlockPos,FALSE);
	if (result == 0) m_CurrentIndex = dwIndex;
	SetEvent(m_SyncEvent);
	return result;
}

DWORD CVirtualMemory::Move(DWORD dwCant,BOOL bForward)
{
	if (m_CurrentBlock == NULL) return 1;
	if (bForward)
	{
		if (IndexToBlock(m_CurrentIndex+dwCant,&m_CurrentBlock,&m_CurrentBlockPos)==0)
			m_CurrentIndex += dwCant;
		else
			return 1;
	}
	else
	{
		if (IndexToBlock(m_CurrentIndex-dwCant,&m_CurrentBlock,&m_CurrentBlockPos) ==0)
			m_CurrentIndex -= dwCant;
		else
			return 1;
	}
	return 0;
}

DWORD CVirtualMemory::GetValue(DWORD dwIndex, BYTE *lpValue)
{
	return 0;
}
DWORD CVirtualMemory::AddBlock(MEMORY_BLOCK** lplpmemblock)
{
	*lplpmemblock = (MEMORY_BLOCK*)VirtualAlloc(NULL,1,MEM_COMMIT,PAGE_READWRITE);
	if (*lplpmemblock == NULL) 
		return 1;
	if (m_BlockSize == 0) 
	{
		MEMORY_BASIC_INFORMATION	mbi;
		::VirtualQuery(*lplpmemblock,&mbi,sizeof(mbi));
		m_BlockSize = mbi.RegionSize - sizeof(MEMORY_BLOCK);
	}
	(*lplpmemblock)->lpnext = NULL;
	return 0;
}

DWORD CVirtualMemory::AddData(BYTE *lpBuffer, DWORD dwCant)
{
	if (WaitForSingleObject(m_SyncEvent,SYNC_TIMEOUT) !=  WAIT_OBJECT_0)
		return 1;
	DWORD result = 0;
	DWORD Index = m_Size;	//Posicion en la cual se copiara el buffer
	// Adicionar bloque de memoria
	result = SetSize(m_Size+dwCant,FALSE);
	if (result != 0) goto add_buffer_exit; 
	result = CopyBuffer(Index,lpBuffer,dwCant,FALSE);
add_buffer_exit:
	SetEvent(m_SyncEvent);
	return result;
}

DWORD CVirtualMemory::InsertBuffer(DWORD dwIndex,BYTE *lpBuffer, DWORD dwCant)
{
	return 0;
}

DWORD CVirtualMemory::GetBuffer(DWORD dwIndex,DWORD dwCant,BYTE *lpBuffer)
{
	MEMORY_BLOCK *mb;
	DWORD		 pos;
	DWORD		 cant,writepos;
	writepos=0;
	if (IndexToBlock(dwIndex,&mb,&pos) != 0) return 1;
	do
	{
		if (pos+dwCant < m_BlockSize)
			cant = dwCant;
		else
			cant = m_BlockSize-pos-1;
		dwCant-=cant;
		memmove(&lpBuffer[writepos],&mb->Data[pos],cant);
		writepos+=cant;
		MovePos(cant,&mb,&pos);
	} while (dwCant >0);
	
	return 0;
}

DWORD CVirtualMemory::MoveBlock( DWORD dwDestIndex,DWORD dwSrcIndex, DWORD dwCant)
{
	MEMORY_BLOCK *srcB,*destB;
	DWORD		 destPos,srcPos;
	DWORD		 movCant;
	if ((dwSrcIndex + dwCant > m_Size ) || (dwDestIndex + dwCant > m_Size) ||
		(dwSrcIndex >= m_Size) || (dwDestIndex >= m_Size))
		return 2;
	if (dwDestIndex < dwSrcIndex)
	{
		if ((IndexToBlock(dwDestIndex,&destB,&destPos) != 0) || (IndexToBlock(dwSrcIndex,&srcB,&srcPos) != 0))
			return 1;
		do 
		{
			// Bloque fuente
			if (srcPos+dwCant < m_BlockSize)
				movCant = dwCant;
			else
				movCant = m_BlockSize - srcPos-1;
			// Bloque destino
			if (destPos+movCant >= m_BlockSize)
				movCant = m_BlockSize - srcPos-1;
			// Copiar la cantidad que se puede
			memmove(&destB->Data[destPos],&srcB->Data[srcPos],movCant);
			dwCant -= movCant;
			MovePos(movCant,&destB,&destPos);
			MovePos(movCant,&srcB,&srcPos);
		} while (dwCant > 0);
	}
	else
	{
		dwDestIndex += dwCant;
		dwSrcIndex += dwCant;
		if ((IndexToBlock(dwDestIndex,&destB,&destPos) != 0) || (IndexToBlock(dwSrcIndex,&srcB,&srcPos) != 0))
			return 1;
		do
		{
			if (srcPos >= dwCant)
				movCant = srcPos;
			else
				movCant = srcPos+1;
			if (destPos+1 < movCant) 
				movCant = destPos+1;
			memmove(&destB->Data[destPos+1-movCant],&srcB->Data[srcPos+1-movCant],movCant);
			dwCant -= movCant;
			MovePos(movCant,&destB,&destPos,false);
			MovePos(movCant,&srcB,&srcPos,false);
		}
		while (dwCant > 0);
	}
	return 0;
}

DWORD CVirtualMemory::DeleteBlock(DWORD dwIndex, DWORD dwCant)
{
	return 0;
}

DWORD CVirtualMemory::GetSize(DWORD *lpdwSize)
{
	*lpdwSize = m_Size;
	return 0;
}

DWORD CVirtualMemory::CopyBlock(DWORD dwDestIndex,DWORD dwSrcIndex,DWORD dwCant)
{
	return 0;
}

DWORD CVirtualMemory::DeleteFromBeginNoMove(DWORD dwCant)
{
	return 0;
}

DWORD CVirtualMemory::IndexToBlock(DWORD dwIndex,MEMORY_BLOCK** lplpMB,DWORD* lpdwPos,BOOL bLock)
{
	DWORD result = 0;
	if (bLock)
		if (WaitForSingleObject(m_SyncEvent,SYNC_TIMEOUT) !=  WAIT_OBJECT_0)
			return 1;
	// Inicio del recorrido
	DWORD cant;
	DWORD Pos = m_FirstPos;
	DWORD Index = 0;
	MEMORY_BLOCK**	memblock = &m_FirstBlock;
	if (dwIndex >= m_Size)
	{
		result = 1;
		*lplpMB = NULL;
	} 
	else
	{
		do
		{
			cant = m_BlockSize-1-Pos;
			if (cant > dwIndex - Index) cant = dwIndex - Index;
			Pos += cant;
			Index += cant;
			if (Index < dwIndex) 
			{
				Pos = 0;
				memblock = &(*memblock)->lpnext;
				Index++;
			}

		} while (Index < dwIndex);
		*lplpMB = *memblock;
		*lpdwPos = Pos;
	}
	if (bLock)
		SetEvent(m_SyncEvent);
	return result;
}

DWORD CVirtualMemory::SetSize(DWORD dwSize,BOOL	bLock)
{
	DWORD result = 0;
	if (bLock)
		if (WaitForSingleObject(m_SyncEvent,SYNC_TIMEOUT) !=  WAIT_OBJECT_0)
			return 1;
	if (dwSize > m_Size)
	{
		MEMORY_BLOCK**	memblock = &m_FirstBlock;
		DWORD			canttoinc;
		if (*memblock == NULL) 
		{
			result = AddBlock(memblock);
			if ( result != 0) goto set_size_exit;
			m_LastPos = 0;
		}
		else
		{
			// Buscar el ultimo bloque de memoria
			for (;(*memblock)->lpnext != NULL;memblock = &(*memblock)->lpnext);
		}
		while (true)
		{
			canttoinc = m_BlockSize - m_LastPos;
			if (canttoinc > dwSize - m_Size) canttoinc = dwSize - m_Size;
			m_LastPos += canttoinc;
			m_Size += canttoinc;
			if (m_Size == dwSize) goto set_size_exit;
			result = AddBlock(&(*memblock)->lpnext);
			if ( result != 0) goto set_size_exit; 
			m_LastPos = 0;
			memblock = &(*memblock)->lpnext;
		}
	} else
	{
		MEMORY_BLOCK* mb1,*mb2;
		DWORD Pos;
		if (dwSize != 0)
			IndexToBlock(dwSize-1,&mb1,&Pos,FALSE);
		else
			IndexToBlock(dwSize,&mb1,&Pos,FALSE);
		m_LastPos = Pos;
		mb2 = mb1->lpnext;
		mb1->lpnext = NULL;
		//Borrar todos los bloques de aqui en adelante
		while (mb2 != NULL)
		{
			mb1 = mb2->lpnext;
			VirtualFree(mb2,0,MEM_RELEASE);
			mb2 = mb1; 
		}
	}
	m_Size = dwSize;
	if (m_CurrentIndex >= dwSize)
		m_CurrentBlock = NULL;
set_size_exit:
	if (bLock)
		SetEvent(m_SyncEvent);
	return result;
}

DWORD CVirtualMemory::Initialize()
{
	m_SyncEvent = ::CreateEvent(NULL,FALSE,TRUE,NULL);
	if (m_SyncEvent == NULL) return 1;
	return 0;
}

DWORD CVirtualMemory::SetValue(BYTE bValue)
{
	if ((m_CurrentIndex >= m_Size) || (m_CurrentBlock == NULL)) return 2;
	m_CurrentBlock->Data[m_CurrentBlockPos] = bValue;
	return 0;
}

DWORD CVirtualMemory::GetValueMoveNext(BYTE *lpValue)
{
	if ((m_CurrentIndex >= m_Size) || (m_CurrentBlock == NULL)) return 2;
	*lpValue = m_CurrentBlock->Data[m_CurrentBlockPos];
	m_CurrentIndex++;
	m_CurrentBlockPos++;
	if (m_CurrentBlockPos == m_BlockSize)
	{
		m_CurrentBlock = m_CurrentBlock->lpnext;
		m_CurrentBlockPos = 0;
	}
	return 0; 
}

DWORD CVirtualMemory::GetValue(BYTE *lpValue)
{
	if ((m_CurrentIndex >= m_Size) || (m_CurrentBlock == NULL)) return 2;
	*lpValue = m_CurrentBlock->Data[m_CurrentBlockPos];
	return 0;
}

DWORD CVirtualMemory::CopyBuffer(DWORD dwIndex, BYTE *lpBuffer, DWORD dwSize,BOOL bLock)
{
	DWORD result = 0;
	MEMORY_BLOCK* mb;
	DWORD	Pos;
	DWORD	canttocopy;
	DWORD	copyfrom=0;
	if (bLock)
		if (WaitForSingleObject(m_SyncEvent,SYNC_TIMEOUT) !=  WAIT_OBJECT_0)
			return 1;
	if (dwIndex + dwSize > m_Size) {result = 1;goto copy_buffer_exit;}
	result = IndexToBlock(dwIndex,&mb,&Pos,FALSE);
	if (result != 0) goto copy_buffer_exit;
	// Comenzar la copia
	for (;dwSize>0;mb = mb->lpnext)
	{
		canttocopy = m_BlockSize - Pos;
		if (canttocopy > dwSize) canttocopy = dwSize;
		memcpy(&mb->Data[Pos],&lpBuffer[copyfrom],canttocopy);
		dwSize -= canttocopy;
		copyfrom+= canttocopy;
		Pos = 0;
		/*
			La posicion es diferente de cero solo en el primer bloque, en los demas es 
			a comienzo de bloque obligado
		*/
	}
	

copy_buffer_exit:
	if (bLock)
		SetEvent(m_SyncEvent);
	return result;
}

DWORD CVirtualMemory::Size()
{
	return m_Size;
}

DWORD CVirtualMemory::MovePos(DWORD dwCant, MEMORY_BLOCK **lplpMB, DWORD *lpdwPos, BOOL bForward)
{
	if (bForward)
	{
		while (dwCant != 0) 
		{
			if (*lplpMB == NULL) return 1;
			if (*lpdwPos + dwCant >= m_BlockSize)
			{
				*lplpMB = (*lplpMB)->lpnext;
				dwCant -= m_BlockSize-*lpdwPos;
				*lpdwPos = 0;
			}
			else
			{
				*lpdwPos += dwCant;
				return 0;
			}
		}
	}
	else
	{
		while (dwCant != 0) 
		{
			if (*lpdwPos < dwCant) 
			{
				// Buscar el bloque anterior
				if (m_FirstBlock == *lplpMB) return 1;
				dwCant -= *lpdwPos;
				*lpdwPos= m_BlockSize-1;
				MEMORY_BLOCK* tmpMB;
				tmpMB = m_FirstBlock;
				while (tmpMB->lpnext != *lplpMB)
					tmpMB = tmpMB->lpnext;
				*lplpMB = tmpMB;
			}
			else
			{
				*lpdwPos -= dwCant;
				return 0;
			}
		}
	}
	return 0;
}

DWORD CVirtualMemory::MemMove(DWORD dwDestIndex, DWORD dwSrcIndex)
{
	DWORD Cant;
	if (dwDestIndex > dwSrcIndex)
	{
		Cant = m_Size - dwDestIndex;
		SetSize(m_Size+dwDestIndex-dwSrcIndex);
	}
	else
		Cant = m_Size - dwSrcIndex;
	return MoveBlock(dwDestIndex,dwSrcIndex,Cant);
}

DWORD CVirtualMemory::GetAbsolutePos(DWORD dwIndex, BYTE **lpbData)
{
	DWORD result;
	MEMORY_BLOCK* mb;
	DWORD		 pos;	
	result = IndexToBlock(dwIndex,&mb,&pos);
	if (result != 0) return result;
	*lpbData = &mb->Data[pos];
	return 0;
}
