// CircularBuffer.cpp: implementation of the CCircularBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CircularBuffer.h"
#include "errorcodes.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCircularBuffer::CCircularBuffer()
{
	m_dwEnd = 0;
	m_dwStart = 0;
	m_pBuffer = NULL;
	m_dwSize = 0;
}

CCircularBuffer::~CCircularBuffer()
{
	if (m_pBuffer) VirtualFree(m_pBuffer,0,MEM_RELEASE);
}

DWORD CCircularBuffer::AddBuffer(BYTE *pBuffer, DWORD dwSize, DWORD *pdwPos)
{
	DWORD dwend;
	DWORD cant;		// tamaño disponible pa escribir
	DWORD dwmax;	// maxima cantidad disponible

	// Verificar disponibilidad de espacio
	if (m_dwStart <= m_dwEnd) 
	{
		dwmax = m_dwSize - m_dwEnd + m_dwStart-1; // no se puede llegar a Size
	}
	else
	{
		dwmax = m_dwStart-1-m_dwEnd;	
	}
	if (dwSize > dwmax) return ERR_OUT_RANGE;

	if (pdwPos != NULL) 
		dwend = *pdwPos;
	else
		dwend = m_dwEnd;

	// Ajuste de punteros
	if ((dwend == m_dwSize) && (m_dwStart >0)) dwend = 0;

	// Determinar hasta cuanto se puede escribir
	if (m_dwStart <= m_dwEnd) 
		cant = m_dwSize - m_dwEnd;
	else
		cant = m_dwStart-1 - m_dwEnd;

	// Ajustar 
	if (dwSize < cant) cant = dwSize;

	// Copiar un poco
	if (pBuffer != NULL) memcpy(pBuffer,&m_pBuffer[dwend],cant);
	// Desplazar
	dwend += cant;
	if ((dwend == m_dwSize) && (m_dwStart >0)) dwend = 0;
	dwSize -= cant;
	pBuffer += cant;
	// copiar el resto
	if ((dwSize != 0) && (pBuffer != NULL))	memcpy(pBuffer,&m_pBuffer[dwend],dwSize);						
	dwend += dwSize;
	// Asentar desplazamiento
	if (pdwPos != NULL) 
		*pdwPos = dwend;
	else
		m_dwEnd = dwend;
	return 0;

}

DWORD CCircularBuffer::GetWritePos(DWORD *pdwPos)
{
	*pdwPos = m_dwEnd;
	return 0;

}

/*
	Solicitar buffer en el cual escribir datos, 
	pero usar la posicion indicada.
*/
DWORD CCircularBuffer::GetWriteBuffer(BYTE **ppbBuffer, DWORD *dwSize, DWORD dwPos)
{
	DWORD dwend;
	DWORD cant;		// tamaño disponible pa escribir

	if (dwPos != NULL) 
		dwend = dwPos;
	else
		dwend = m_dwEnd;

	// Ajuste de punteros
	if ((dwend == m_dwSize) && (m_dwStart >0)) dwend = 0;

	// Determinar hasta cuanto se puede escribir
	if (m_dwStart <= m_dwEnd) 
		cant = m_dwSize - m_dwEnd;
	else
		cant = m_dwStart-1 - m_dwEnd;
	
	*dwSize = cant;
	*ppbBuffer = &m_pBuffer[dwend];
	return 0;

}

DWORD CCircularBuffer::SetSize(DWORD dwSize)
{
	if (m_pBuffer) VirtualFree(m_pBuffer,0,MEM_RELEASE);
	MEMORY_BASIC_INFORMATION	mbi;
	m_pBuffer = (BYTE*)VirtualAlloc(NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);
	if (m_pBuffer == NULL) 
	{
		//m_LastError = GetLastError();
		return ERR_NOMEMORY;
	}
	::VirtualQuery(m_pBuffer,&mbi,sizeof(mbi));
	m_dwSize= mbi.RegionSize;
	return ERR_NONE;
}

// Obtener buffer de lectura
DWORD CCircularBuffer::GetReadBuffer(BYTE **ppbBuffer, DWORD *dwSize)
{
	if (m_dwStart <= m_dwEnd) 
	{
		*dwSize = m_dwEnd - m_dwStart;
	}
	else
	{
		*dwSize = m_dwSize - m_dwStart;	
	}
	*ppbBuffer = &m_pBuffer[m_dwStart];
	return ERR_NONE;
}

// Copiar buffer aqui
DWORD CCircularBuffer::GetBuffer(BYTE *pBuffer, DWORD dwSize,DWORD *dwRead)
{
	if (dwSize == NULL) return ERR_INV_ARG;
	DWORD	max;
	if (m_dwStart <= m_dwEnd) 
	{
		max = m_dwEnd - m_dwStart;
	}
	else
	{
		max = m_dwSize - m_dwStart;	
	}
	max = min(dwSize,max);
	if (pBuffer != NULL) memcpy(pBuffer,&m_pBuffer[m_dwStart],max);
	m_dwStart += max;
	dwSize -= max;
	if (m_dwStart == m_dwSize) m_dwStart = 0;
	if (dwSize != 0);
	
	return ERR_NONE;
}

DWORD CCircularBuffer::GetWriteBuffer(BYTE **ppbBuffer, DWORD *dwSize)
{
	DWORD dwend;
	DWORD cant;		// tamaño disponible pa escribir
	DWORD dwmax;	// maxima cantidad disponible

	// Verificar disponibilidad de espacio
	if (m_dwStart <= m_dwEnd) 
	{
		dwmax = m_dwSize - m_dwEnd + m_dwStart-1; // no se puede llegar a Size
	}
	else
	{
		dwmax = m_dwStart-1-m_dwEnd;	
	}
	if (*dwSize > dwmax) return ERR_OUT_RANGE;

	dwend = m_dwEnd;

	// Ajuste de punteros
	if ((dwend == m_dwSize) && (m_dwStart >0)) dwend = 0;

	// Determinar hasta cuanto se puede escribir
	if (m_dwStart <= m_dwEnd) 
		cant = m_dwSize - m_dwEnd;
	else
		cant = m_dwStart-1 - m_dwEnd;

	// Ajustar 
	if (*dwSize < cant) cant = *dwSize;

	// Copiar un poco
//	if (pBuffer != NULL) memcpy(pBuffer,&m_pBuffer[dwend],cant);
	// Desplazar
	dwend += cant;
	if ((dwend == m_dwSize) && (m_dwStart >0)) dwend = 0;
	dwSize -= cant;
//	pBuffer += cant;
	// copiar el resto
//	if ((dwSize != 0) && (pBuffer != NULL))	memcpy(pBuffer,&m_pBuffer[dwend],dwSize);						
	dwend += *dwSize;
	// Asentar desplazamiento
	m_dwEnd = dwend;
	return ERR_NONE;	
}

/*
	Desplazar el puntero de escritura en el buffer
*/
DWORD CCircularBuffer::UpdateWritePtr(DWORD dwCant)
{
	return 0;
}

/*
	Desplazar puntero de lectura en el buffer
*/
DWORD CCircularBuffer::UpdateReadPtr(DWORD dwCant)
{
	return 0;
}
