// BlockMem.cpp: implementation of the CBlockMem class.
//
//////////////////////////////////////////////////////////////////////

#include "BlockMem.h"

#define _FILENAME_	"blockmen.cpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define _CHECK_LOCK_ if (m_first_lock == NULL) return _LOG_ERROR ERR_NOMEMORY,"no lock memory");


DWORD	CBlockMem::Start()
{
	return lock();
}

DWORD	CBlockMem::End()
{
	return ERR_OK;
}

DWORD	CBlockMem::Push(BYTE b)
{
	// esto hay que modificarlo y hacerlo directamente para ganar tiempo
	// o mejor no
	return lockAdd(&b,1);
}


CBlockMem::CBlockMem()
{
	m_first_block = NULL;
	m_first_lock = NULL;
	mMinSize = 0x1000;		// 4KB tamaño de los bloques
}

CBlockMem::~CBlockMem()
{
	_release();	
}

/*
	Crea un nuevo bloque de memoria con un tamaño igual o mayor al especificado
*/

DWORD CBlockMem::createBlock(DWORD minsize)
{
	// ir al ultimo bloque disponible
	struct _mblock *nblock,*tblock;			// nuevo bloque creado
	DWORD size = minsize + sizeof(struct _mblock);		// se asume que despues de la estructura hay alineacion
	if (size < mMinSize) size = mMinSize;

	MEMORY_BASIC_INFORMATION	mbi;

	nblock = (struct _mblock*)VirtualAlloc(NULL,size,MEM_COMMIT,PAGE_READWRITE);
	if (nblock == NULL) return _LOG_W32ERROR GetLastError(),ERR_API,"VirtualAlloc with %d bytes ",size);

	::VirtualQuery(nblock,&mbi,sizeof(mbi));
	nblock->free_index = sizeof(struct _mblock);
	nblock->max_index = (DWORD)mbi.RegionSize;
	nblock->next = NULL;

	if (m_first_block == NULL) m_first_block = nblock;
	else
	{
		tblock = m_first_block;
		while (tblock->next != NULL) tblock = tblock->next;
		tblock->next = nblock;
	}

	return ERR_OK;
}


DWORD CBlockMem::_get(DWORD size, void **ppvoid,bool align)
{
	// buscar un bloque con el tamaño disponible
	struct _mblock* pblock;
	DWORD	offset;
	
	// encontar un bloque con suficiente espacio que no este bloqueado
	pblock = m_first_block;
	for(;;)
	{
		// validar si cabe en este bloque que existe
		if ((pblock) && (pblock->look_index == 0))
		{
			offset = pblock->free_index;
			if (align)
			{
				if (offset & (sizeof(void*)-1)) offset = (offset + sizeof(void*)) & ~(sizeof(void*)-1);
			}
			if (pblock->max_index - offset >= size) break;
		}
		// si no hay bloque o es el ultimo se crea un nuevo bloque
		if ((!pblock) || (!pblock->next))
		{
			if (createBlock(size) != ERR_OK) return _LOG_AT;
			if (!pblock) 
				pblock = m_first_block;
			else
				pblock=pblock->next;
			if (!pblock) return _LOG_ERROR ERR_UNEXPECTED,"unexpected missing block");
			// 	if (cblock->max_index-offset < size) return _LOG_ERROR ERR_UNEXPECTED,"unexpected fulled block");
			offset = pblock->free_index;
			break;
		}
		pblock=pblock->next;
	}
	// Alinear la memoria
	*ppvoid = ((BYTE*)(pblock))+offset;
	pblock->free_index = offset + size;
	return ERR_OK;
}

DWORD CBlockMem::_add(void *pdata, DWORD size, void **ppvoid,bool align)
{
	void*	pvoid;
	if (_get(size,&pvoid,align) != ERR_OK) return _LOG_AT;
	memcpy(pvoid,pdata,size);
	*ppvoid=pvoid;
	return ERR_OK;
}

DWORD CBlockMem::addS(char *str, DWORD size, char **pstr)
{
	void*	pvoid;
	if (size == 0)
	{
		char	*cptr=str;
		while (*cptr++ != 0);
		size = (DWORD)(cptr-str+1);
	}
	if (_get(size,&pvoid,false) != ERR_OK) return _LOG_AT;
	memcpy(pvoid,str,size);
	((BYTE*)pvoid)[size] = 0;
	*pstr = (char*)pvoid;
	return ERR_OK;
}

DWORD CBlockMem::lock()
{
	struct _mblock	*pblock;

	if (m_first_lock != NULL) return _LOG_ERROR ERR_IS_LOCK,"");
	
	// solicitamos memoria alineada para poder hacer un compact en condiciones
	pblock = _look(2*sizeof(void*),true); if (pblock == NULL) return  _LOG_AT;

	// bloquear el bloque
	m_first_lock = pblock;
	pblock->look_index = pblock->free_index;
	return ERR_OK;
}


DWORD CBlockMem::lockAvaliable(void **ppvoid, DWORD *psize)
{
	// buscar el utlimo bloque bloqueado
	struct _mblock*	plock;
	
	_CHECK_LOCK_
	plock = _lastLock();	
	// si en este bloque no queda espacio, hay que crear otro ya que es el utlimo bloque 
	if (plock->free_index == plock->max_index)
	{
		plock = _createLock(plock); if (plock == NULL) return _LOG_AT;
	}
	*psize = plock->max_index - plock->free_index;
	*ppvoid = ((BYTE*)plock) + plock->free_index;
	return ERR_OK;
}


DWORD CBlockMem::lockCommit(DWORD size)
{
	// Buscar el ultimo bloque bloqueado y actualizar el free index
	struct _mblock*	plock;

	_CHECK_LOCK_
	plock = _lastLock();
	if (plock->free_index + size > plock->max_index) return _LOG_ERROR ERR_OVERFLOW,"overflow");
	plock->free_index = plock->free_index + size;
	return ERR_OK;
}

DWORD CBlockMem::lockAdd(void *dt, DWORD size)
{
	_CHECK_LOCK_
	struct _mblock* plock;
	BYTE *psrc = (BYTE*)dt;
	DWORD count;
	plock = _lastLock();
	// poner datos mientras quepan
	for (;size > 0;)
	{
		count = plock->max_index - plock->free_index;
		if (count == 0) 
		{
			plock = _createLock(plock);if (plock == NULL) return _LOG_AT;
			continue;
		}
		if (count > size) count = size;
		memcpy((BYTE*)plock + plock->free_index,psrc,count);
		plock->free_index += count;
		size -= count;
		psrc += count;
	}
	return ERR_OK;
}

DWORD CBlockMem::lockCompact(void **ppvoid, DWORD *ppsize)
{
	// este metodo requiere optimizacion para poder utilizar el ultimo bloque bloqueado si es posible
	// recorrer todo los bloques con bloqueo y contar la cantidad de datos y de bloques bloqueados
	DWORD size = 0;
	DWORD free;
	DWORD look_index;
	WORD  count = 0;
	struct _mblock* pblock = m_first_lock;
	struct _mblock* tblock;

	if (m_first_lock == NULL) return _LOG_ERROR ERR_NOMEMORY,"no lock memory");
	for (;pblock;)
	{
		size += pblock->free_index - pblock->look_index;
		count ++;
		do
		{
			pblock = pblock->next;
		} while ((pblock) && (pblock->look_index == 0));

	}
	tblock = m_first_lock;
	// Si solo hay un bloque bloqueado es mas facil
	if (count == 1)
	{
		*ppvoid = (BYTE*)tblock+tblock->look_index;
		if (ppsize) *ppsize = tblock->free_index - tblock->look_index;
		return ERR_OK;
	}
	// buscar espacio entre los bloques para ubicar todo el lock
	pblock = _look(size,true);if (pblock == NULL) return _LOG_AT;
	look_index = pblock->free_index;

	*ppvoid = (BYTE*)pblock + pblock->free_index;
	if (ppsize) *ppsize = size;

	for (;tblock;)
	{
		free = tblock->free_index-tblock->look_index;
		memcpy((BYTE*)pblock+pblock->free_index,(BYTE*)tblock + tblock->look_index,free);
		size -= free;
		pblock->free_index += free;
		// liberar el bloqueo de este bloque
		tblock->free_index = tblock->look_index;
		tblock->look_index = 0;
		// buscar el proximo bloque bloqueado
		if (!size) break;
		do 
		{
			tblock = tblock->next;
		}while (tblock && (tblock->look_index == 0));
	}
	// dejar bloqueado solo el bloque donde se han copiado los datos
	m_first_lock = pblock;
	pblock->look_index = look_index;
	return ERR_OK;
	
}

DWORD CBlockMem::lockClose()
{
	// cierra todos los bloques bloqueados
	_CHECK_LOCK_
	struct _mblock* pblock = m_first_lock;
	for (;pblock;)
	{
		pblock->look_index = 0;
		/*
		if (pblock->look_index != 0) 
		{
			pblock->look_index == 0;
		}
		*/
		pblock = pblock->next;
	}
	m_first_lock = NULL;
	return ERR_OK;
}

DWORD CBlockMem::lockFree()
{
	// liberar todos los bloques bloqueados
	_CHECK_LOCK_
	struct _mblock* pblock = m_first_lock;
	for (;pblock;)
	{
		if (pblock->look_index != 0) 
		{
			pblock->free_index = pblock->look_index;
			pblock->look_index = 0;
		}
		pblock = pblock->next;
	}
	m_first_lock = NULL;
	return ERR_OK;
}

/*
	encuentra y bloquea el proximo bloque disponible, 
	si no se indica un bloque de entrada se aplica desde el primer bloque
*/
struct _mblock* CBlockMem::_createLock(struct _mblock* plast)
{
	DWORD size = 2*sizeof(void*);
	// buscar un bloque activo y bloquearlo
	for(;;)
	{
		if ((plast == NULL) || (plast->next == NULL))
		{
			// no hay mas bloques hay que crear uno
			if (_newBlock(plast,size) != ERR_OK) { _LOG_AT; return NULL; }
			if (plast) plast = plast->next;
			else
				plast = m_first_block;
			break;
		}
		plast = plast->next;
		// comprobar si cabe aqui 
		if (plast->max_index - plast->free_index >= size) break;
	}
	// ya tenemos un bloque disponible que se puede bloquear
	if (m_first_lock == NULL) m_first_lock = plast;
	plast->look_index = plast->free_index;
	return plast;

}

/*
	crear un bloque de memoria a conitnuacion de este
	si es null se crea el primer bloque de memoria
*/
DWORD CBlockMem::_newBlock(struct _mblock *plast, DWORD size)
{
	struct _mblock *nblock;					// nuevo bloque creado
	size += sizeof(struct _mblock);		// se asume que despues de la estructura hay alineacion
	if (size < mMinSize) size = mMinSize;

	MEMORY_BASIC_INFORMATION	mbi;

	nblock = (struct _mblock*)VirtualAlloc(NULL,size,MEM_COMMIT,PAGE_READWRITE);
	if (nblock == NULL) return _LOG_W32ERROR GetLastError(),ERR_API,"VirtualAlloc with %d bytes ",size);

	::VirtualQuery(nblock,&mbi,sizeof(mbi));
	nblock->free_index = sizeof(struct _mblock);
	nblock->max_index = (DWORD)mbi.RegionSize;
	nblock->next = NULL;

	if (plast) 
		plast->next = nblock;
	else
		m_first_block = nblock;

	return ERR_OK;
}

/*
	Buscar o crear un bloque que disponga del tamaño indicado de forma alineada
	alinear automaticamente 
*/
struct _mblock* CBlockMem::_look(DWORD size,bool align)
{
	// buscar un bloque con el tamaño disponible
	size += sizeof(struct _mblock);	

	struct _mblock* pblock = m_first_block;
	DWORD	offset;
	
	// encontar un bloque con suficiente espacio que no este bloqueado
	for(;;)
	{
		// validar si cabe en este bloque que existe
		if ((pblock) && (pblock->look_index == 0))
		{
			offset = pblock->free_index;
			if (align)
			{
				if (offset & (sizeof(void*)-1)) offset = (offset + sizeof(void*)) & ~(sizeof(void*)-1);
			}
			if (pblock->max_index - offset >= size) 
			{
				if (align) pblock->free_index = offset;
				return pblock;
			}
		}
		// si no hay bloque o es el ultimo se crea un nuevo bloque
		if ((!pblock) || (!pblock->next))
		{
			if (createBlock(size) != ERR_OK) { _LOG_AT; return NULL; }
			if (!pblock) 
				return m_first_block;
			else
				return pblock=pblock->next;
		}
		pblock=pblock->next;
	}
	return NULL;	
}

// buscar el ultimo bloque bloqueado
struct _mblock* CBlockMem::_lastLock()
{
	// buscar el utlimo bloque bloqueado
	struct _mblock*	plock = NULL;
	struct _mblock*	pblock;
	
	for (pblock = m_first_lock;pblock;)
	{
		if (pblock->look_index != 0) plock = pblock;
		pblock=pblock->next;
	}
	return plock;
}

void CBlockMem::_release()
{
	struct _mblock*	pblock,*cblock;
	
	for (pblock = m_first_lock;pblock;)
	{
		cblock = pblock;
		pblock = pblock->next;
		VirtualFree(cblock,0,MEM_RELEASE);	
	}
	m_first_block = NULL;
	m_first_lock = NULL;
}

DWORD CBlockMem::lockSize()
{
	// recorrer todo los bloques con bloqueo y contar la cantidad de datos y de bloques bloqueados
	DWORD size = 0;

	struct _mblock* pblock = m_first_lock;
	for (;pblock;)
	{
		size += pblock->free_index - pblock->look_index;
		do
		{
			pblock = pblock->next;
		} while ((pblock) && (pblock->look_index == 0));

	}
	return size;
}
