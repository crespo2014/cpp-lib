// memarray.h: interface for the Cpep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMARRAY_H__C344E8E8_A030_4B6E_8E2B_4CA5B47F4E78__INCLUDED_)
#define AFX_MEMARRAY_H__C344E8E8_A030_4B6E_8E2B_4CA5B47F4E78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"
#include "bobject.h"

class CMemArray  : public CbObject
{
public:
	DWORD SizeInc(DWORD cant)			{ return SetSize(m_mem_size+cant); };
	DWORD LoadFile(const char* file_path);
	void SetElementSize(WORD size)		{ m_element_size = size;};
	void* GetMemBuffer()				{ return m_mem;};
	DWORD	GetSize()					{ return m_mem_size; };
	DWORD AddElements(WORD cant)		{ return SetElementCount(cant+m_element_count);};	
	DWORD SetElementCount(WORD count)	{ return SetSize(count*m_element_size);};
	void ClearData();
	DWORD Release();
	void* GetElementAt(WORD index);
	DWORD SetMaxMemorySize(DWORD max_size);
	
	
	DWORD SetSize(DWORD new_size);
	CMemArray();
	virtual ~CMemArray();

private:
	WORD	m_element_size;		// tamaño de los elementos del arreglo
	WORD	m_element_count;	// maxima cantidad de elementos
	DWORD	m_mem_size;			// cantidad de memoria solicitada
	DWORD	m_max_commit;		// maxima cantidad de memoria disponible
	DWORD	m_max_reserved;		// maxima cantidad de memoria reservada
	BYTE*	m_mem;				// memoria reservada
	

};

#endif // !defined(AFX_MEMARRAY_H__C344E8E8_A030_4B6E_8E2B_4CA5B47F4E78__INCLUDED_)
