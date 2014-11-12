// MemStack.cpp: implementation of the CMemStack class.
//
//////////////////////////////////////////////////////////////////////

#include "MemStack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemStack::CMemStack()
{
	Init();
}

CMemStack::~CMemStack()
{

}

DWORD CMemStack::Initialize(void* stack,DWORD size)
{
	m_binit = 1;
	m_data_ptr = (char*)stack;
	m_maxlen = size;
	m_wptr = m_data_ptr;
	return ERR_OK;
}

void CMemStack::Init()
{
	m_binit = 0;
	m_data_ptr = NULL;
	m_maxlen = 0;
	m_wptr = NULL;
}

DWORD CMemStack::AddString(char *str, int len, char **ppBuffer)
{
	char	*cptr;
	if (len == 0) len = strlen(str);
	if (Get(len+1,(void**)ppBuffer,0) != ERR_OK) return ERR_FATAL;
	cptr = *ppBuffer;
	if (str != NULL) 
	{
		memcpy(cptr,str,len);
		cptr[len] = 0;
	}
	return ERR_OK;
}

DWORD CMemStack::Get(int size, void **ppBuffer, int align32)
{
	// hay que alinear la memoria antes de devolverla, porque el uso de caracteres al final de una estructura 
	// genera desalineaciones y eso da problemas con algunas funciones numericas que no pueden escribir 
	// numeros de 32 bits desalineados
	int	align;
	char	*fnc_name = "CMemStack::Get";

	LOG_TLAST	" size = %d, Remained = %d",size,(m_data_ptr + m_maxlen)-m_wptr);

	if (align32 != 0)
	{
		align = ((int)m_wptr) % 4;
		m_wptr += (4 - align);	
	}
	if (m_wptr + size > m_data_ptr + m_maxlen)  return LOG_TERROR ERR_FATAL,"Buffer overflow, Remained = %d  ",(m_data_ptr + m_maxlen)-m_wptr);
	*ppBuffer = m_wptr;
	memset(m_wptr,0,size);
	m_wptr += size;
	return ERR_OK;
}
