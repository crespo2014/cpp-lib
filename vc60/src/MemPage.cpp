// MemPage.cpp: implementation of the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#include "MemPage.h"

#define _FILENAME_ "MemPage.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemPage::CMemPage()
{
	m_ver = "Class CMemPage " CLASS_VER;
	m_page = NULL;
	m_page_size = 0;
	m_page_ptr = NULL;
	m_data_size = 0;
	m_max_reserved = 0;
	m_max_size = 0;
}

CMemPage::~CMemPage()
{
	Release();
}

void* CMemPage::CreatePage(DWORD maxsize)
{
	MEMORY_BASIC_INFORMATION	mbi;

	if (m_page != NULL) Release();
	if (maxsize == 0) return NULL;

	m_page = (BYTE*)VirtualAlloc(NULL,maxsize,MEM_COMMIT,PAGE_READWRITE);
	if (m_page == NULL) 
	{
		LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualAlloc with %d bytes ",maxsize);
		return NULL;
	}

	m_data_size = maxsize;
	::VirtualQuery(m_page,&mbi,sizeof(mbi));

	m_page_size = mbi.RegionSize;
	m_page_ptr = m_page;
	return m_page;
}

void CMemPage::Release()
{
	if (m_page == NULL) return;
	VirtualFree(m_page,0,MEM_RELEASE);
	m_page = NULL;
	m_page_size = 0;
	m_page_ptr =  NULL;
	m_data_size = 0;
	m_max_reserved = 0;
}


DWORD CMemPage::LoadFile(const char *file_path)
{
	HANDLE	hFile;
	BOOL	br;
	DWORD	fsize;
	DWORD	bread;
	DWORD	maxsize;

	hFile = CreateFileA(file_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"CreateFile (%s)",file_path);
	}
	fsize = GetFileSize(hFile,NULL);
	maxsize = fsize + 1;
	if (CreatePage(maxsize) == NULL) return ERR_FATAL;
	//if (fsize == 0) return ERR_OK;
	br = ReadFile(hFile,m_page,fsize,&bread,NULL);
	CloseHandle(hFile);
	if (!br)
	{
		Release();
		return LOG_TW32_ERROR GetLastError(),ERR_API,"ReadFile %d bytes",fsize); 
	}
	m_page_ptr = m_page + bread + 1;
	m_page_ptr[-1] = 0;
	m_data_size = fsize;	
	return ERR_OK;
}

DWORD CMemPage::CommitPages(DWORD size)
{
	MEMORY_BASIC_INFORMATION	mbi;
		
	if (m_page == NULL)	return LOG_TERROR ERR_FATAL,"Call ReservePage before "); 
	if (size > m_max_reserved) return LOG_TERROR ERR_FATAL,"not enough memory for %X bytes max %X bytes",size,m_max_reserved); 
	if (size > m_page_size)
	{
		if (VirtualAlloc(m_page,size,MEM_COMMIT,PAGE_READWRITE) == NULL) 
		{
			return LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualAlloc for MEM_COMMIT with %X bytes",size);
		}
		::VirtualQuery(m_page,&mbi,sizeof(mbi));
		m_page_size = mbi.RegionSize;
	}
	//if (*psize == 0) 
	m_data_size = size;
	return ERR_OK;
}

void CMemPage::Clone(CMemPage *pMemPage)
{
	CbObject::Clone(pMemPage,sizeof(CMemPage));
	Init();
	if (pMemPage->m_max_reserved != 0)
	{
		m_max_size = pMemPage->m_max_reserved;
		if (ReserveMemory()						!= ERR_OK) return;
		if (CommitPages(pMemPage->m_page_size)	!= ERR_OK) return;
	}
	else
	{
		if (pMemPage->m_page_size != 0)
		{
			if (CreatePage(pMemPage->m_page_size-1) == NULL) return;
		}
	}
	m_data_size = pMemPage->m_data_size;
	m_page_ptr  = m_page + (pMemPage->m_page_ptr - pMemPage->m_page);
	memcpy(m_page,pMemPage->m_page,m_data_size);
}

DWORD CMemPage::SetMaxSize(DWORD max_size)
{
	// liberar la memoria y tomar este valor como el maximo
	Release();
	m_max_size = max_size;
	return ERR_OK;
}

DWORD CMemPage::ReserveMemory()
{
	MEMORY_BASIC_INFORMATION	mbi;

	if (m_page != NULL) return ERR_OK;
	if (m_max_size == 0) return LOG_TERROR ERR_FATAL,"Undefined Max memory size",__LINE__);
	m_page = (BYTE*)VirtualAlloc(NULL,m_max_size,MEM_RESERVE,PAGE_READWRITE);
	if (m_page == NULL) 
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualAlloc Failed with %X bytes",m_max_size);
	}
	::VirtualQuery(m_page,&mbi,sizeof(mbi));
	m_max_reserved = mbi.RegionSize;
	m_page_size = 0;
	m_page_ptr = m_page;
	return ERR_OK;

}

void CMemPage::Reset()
{
	m_data_size = 0;
	m_page_ptr = m_page;
}

DWORD CMemPage::addBlock(void *pblock, DWORD len, void **ppos, BOOL align)
{
	void	*block;
	if (getBlock(&block,len,align) != ERR_OK) return _LOG_EXIT(ERR_FATAL);
	memcpy(block,pblock,len);
	if (ppos != NULL) *ppos = block;
	return ERR_OK;

}

DWORD CMemPage::decAddString(char *str, DWORD size, char **pos)
{
	if (m_page_ptr != NULL) m_page_ptr--;
	if (addString(str,pos,size) != ERR_OK) return _LOG_EXIT(ERR_FATAL);
	return ERR_OK;
}

DWORD CMemPage::addString(char *str, char **pos, DWORD size)
{
	char	*cptr;
	
	if (str == NULL) return LOG_TERROR ERR_FATAL,"Null pointer");
	if (size == 0) size = strlen(str);
	size++;
	if (getStr(&cptr,size) != ERR_OK) return _LOG_EXIT(ERR_FATAL);;
	memcpy(cptr,str,size-1);
	cptr[size-1] = 0;
	if (pos != NULL) *pos = cptr;
	return ERR_OK;

}

DWORD CMemPage::getBlock(void **pos, DWORD len, BOOL align)
{
	BYTE	*top;

	if (len == 0)					return LOG_TERROR ERR_PARAM,"Invalid Param len most be > 0");
	if (ReserveMemory() != ERR_OK)	return _LOG_EXIT(ERR_FATAL);
	
	*pos = NULL;
	if (align)
	{
		int align32 = ((int)m_page_ptr) % sizeof(int);
		if (align32 != 0) m_page_ptr += (sizeof(int) - align32);	
	}

	if (m_max_reserved == 0)
		top = m_page + m_page_size;
	else 
		top = m_page + m_max_reserved;
	if (m_page_ptr + len > top) return LOG_TERROR ERR_FATAL,"Failed to get %d bytes from buffer, %d bytes remined",len,top-m_page_ptr);
	if ((m_max_reserved != 0) && (m_page_ptr + len > m_page + m_page_size))
	{
		if (CommitPages(m_page_ptr + len - m_page) != ERR_OK) return _LOG_EXIT(ERR_FATAL);;
	}
	*pos = m_page_ptr;
	m_page_ptr += len;
	// quedarnos con la ultima posicion en la que se adiciono un dato 
	if (m_data_size + m_page  < m_page_ptr) m_data_size = m_page_ptr - m_page;
	return ERR_OK;

}
