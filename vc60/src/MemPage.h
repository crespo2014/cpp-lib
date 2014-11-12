// MemPage.h: interface for the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_)
#define AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"

/*
	Hay que ampliar la funcionalidad de estas clases, 
	Crear una interfaz comun para todas las manejadoras de memoria
	IMem
	disponer de los sigueintes metodos
	get (size)		//alineada siempre
	add (size)		// agregar datos alineados
	addStr ()		// con tamaño definido o no
	getStr( size)	// sin alinear
	PreAlloc(size)	// prelocalizar un bloque continuo	se necesita un buffer que aumenta de tamaño
						continuamente hasta conseguir un dato no se permite pedir mas memoria mientras 
						hay un bloqueo
	lock(size)
	unlock(size)    // se desbloquea la zona de memoria y hacemos efectivo solo el tamaño indicado
	lockAdd()		// adicionar datos continuos o no a la zona de bloqueo
	lockRemove()	// hechar atras datos adicionados

*/

class CMemPage  : public CbObject
{
public:
	DWORD getBlock(void** pos,DWORD len, BOOL align = true);
	DWORD getStr(char **pos,DWORD len)				{ return getBlock((void**)pos,len,false); };

	DWORD addBlock(void* pblock,DWORD len, void **pppos, BOOL align = true);
	DWORD addString(char *str, char **pos, DWORD size = 0);
	DWORD decAddString(char *str,DWORD size,char** pos);
	//DWORD addStringDec(char *str,DWORD size,char** pos); // adiciona un string pero deja decrementada la posicion
	
	void Reset();
	DWORD ReserveMemory();
	DWORD SetMaxSize(DWORD max_size);
	void Clone(CMemPage* pMemPage);
	DWORD CommitPages(DWORD size);
	DWORD LoadFile(const char *file_path);
	void Release();
	void* CreatePage(DWORD maxsize);
	
	BOOL	IsFreeToAdd(DWORD size) { return (m_page + m_max_reserved > m_page_ptr + size); };
	DWORD	GetFreeSize()		{ return m_max_reserved - m_data_size; };
	DWORD	GetReservedSize()	{ return m_max_reserved;};
	DWORD	GetDataSize()		{ return m_data_size;	};	// es el tamaño maximo de los datos, puede estar defasado con pageptr si este 
	DWORD	GetSize()			{ return m_page_size;	};	// tamaño de la pagina disponible
	BYTE*	GetPage()			{ return m_page;		};
	BYTE*	GetPtr()			{ return m_page_ptr;	};	//indica el puntero donde se estan adicionando datos a la pagina y es el tamaño de los datos
	char*	getStrPage()		{ return m_cpage;		};
	void SetPtr(BYTE* bptr)		{ m_page_ptr = bptr;	};
	CMemPage();
	virtual ~CMemPage();
	
private:
	union {
		BYTE*	m_page;
		char*	m_cpage;
		BYTE*	m_bpage;
		void*	m_vpage;
	};
	DWORD	m_page_size;	// tamaño maximo de la pagina
	DWORD	m_data_size;	// tamaño de los datos, tamaño actual o tamaño solicitado
	BYTE*	m_page_ptr;		// puntero que indica donde se estan adicionando datos
	DWORD	m_max_reserved;	// maxima memoria reservada
	DWORD	m_max_size;
	DWORD	m_obj_size;		// cuando se usa como un arreglo para almacenar objetos o estructuras
	DWORD	m_obj_count;	// Se indica la cantidad de objetos que hay actualmente

};

#endif // !defined(AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_)
