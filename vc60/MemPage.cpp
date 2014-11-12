// MemPage.cpp: implementation of the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#include "MemPage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemPage::CMemPage()
{
	m_ver = "Class CMemPage " CLASS_VER;
	m_page = NULL;
	m_page_size = 0;
	m_page_ptr = NULL;	
}

CMemPage::~CMemPage()
{
	Release();
}

void* CMemPage::CreatePage(DWORD* maxsize)
{
	char	*fnc_name = "CMemPage::CreatePage";
	MEMORY_BASIC_INFORMATION	mbi;

	if (m_page != NULL) Release();
	if (*maxsize == 0) return NULL;

	m_page = (BYTE*)VirtualAlloc(NULL,*maxsize,MEM_COMMIT,PAGE_READWRITE);
	if (m_page == NULL) 
	{
		SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->VirtualAlloc for %d bytes ",fnc_name,maxsize);
		return NULL;
	}

	::VirtualQuery(m_page,&mbi,sizeof(mbi));
	*maxsize = mbi.RegionSize;

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
}

DWORD CMemPage::AddStr(char *str, char **pos, DWORD len)
{
	char	*fnc_name = "CMemPage::Data_AddStr";

	if (m_page == NULL) return SetError(true,ERR_FATAL,"%s invalid memory pointer",fnc_name);
	if ((str == NULL) && (len == 0))
	{
		*pos = NULL;
		return SetError(true,ERR_FATAL,"%s Invalid params",fnc_name);
	}

	DWORD remained = m_page_size - (m_page_ptr - m_page);
	if (len == 0) len = strlen(str);
	if (remained < len+1) return SetError(true,ERR_FATAL,"%s failed to get %d bytes from buffer, %d bytes remined",fnc_name,len,remained);
	*pos = (char*)m_page_ptr;
	if (str != NULL) memcpy(m_page_ptr,str,len);
	m_page_ptr += (len+1);
	m_page_ptr[-1] = 0;
	return ERR_OK;
}


DWORD CMemPage::LoadFile(const char *file_path)
{
	char	*fnc_name = "CMemPage::LoadFile";

	HANDLE	hFile;
	BOOL	br;
	DWORD	fsize;
	DWORD	bread;
	DWORD	maxsize;

	hFile = CreateFile(file_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->CreateFile (%s)",fnc_name,file_path);
	fsize = GetFileSize(hFile,NULL);
	maxsize = fsize;
	if (CreatePage(&maxsize) != ERR_OK) return ERR_FATAL;
	if (fsize == 0) return ERR_OK;

	br = ReadFile(hFile,m_page,fsize,&bread,NULL);
	m_page_ptr = m_page + bread + 1;
	m_page_ptr[-1] = 0;
	if (!br) SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->ReadFile",fnc_name); 
	CloseHandle(hFile);
	if (br) return ERR_OK;
	Release();
	return ERR_FATAL;
}
