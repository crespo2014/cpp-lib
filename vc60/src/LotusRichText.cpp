// LotusRichText.cpp: implementation of the CLotusRichText class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusRichText.h"

#define _FILENAME_ "lotusrichtext.c"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define _CHECK_HANDLE_ 	if (m_hRichText == NULL) return _LOG_ERROR ERR_HANDLE,"Invalid handle (not open richtext)");

CLotusRichText::CLotusRichText(CLotusNote*	pnote)
{
	m_note = pnote;
	m_hRichText = NULL;
	m_newitem_mem.SetElementSize(1);
	m_newitem_size = 0;
}

CLotusRichText::~CLotusRichText()
{

}

DWORD CLotusRichText::Close()
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = CompoundTextClose(m_hRichText,NULL,NULL,NULL,0);if (sr != NOERROR) return _LOG_ERROR ERR_API,"CompoundTextClose failed : %s",CLNotesError().getErrorString(sr));
	m_hRichText = NULL;	
	return ERR_OK;
}

DWORD CLotusRichText::Create(char *name)
{
	Close();
	if (m_note->Create_CompoundText(name,&m_hRichText) != ERR_OK) return _LOG_AT;
	return ERR_OK;
}

DWORD CLotusRichText::AttachFile(char *file_path)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = CompoundTextAssimilateFile(m_hRichText,file_path,0);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"CompoundTextAssimilateFile for %s failed : %s",file_path,CLNotesError().getErrorString(sr));
	return ERR_OK;		
}

DWORD CLotusRichText::NewItem_Initialize(DWORD max_size)
{
	if (max_size == 0) max_size = 1*1024*1024;	//1MB
	m_newitem_mem.SetMaxMemorySize(max_size);
	m_newitem_mem.SetSize(100);
	return ERR_OK;
}

DWORD CLotusRichText::NewItem_Save(char *name, WORD flags)
{
	return ERR_OK;
}

DWORD CLotusRichText::DumpItem_Start()
{

	return ERR_OK;
}
