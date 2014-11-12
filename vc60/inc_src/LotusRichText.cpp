// LotusRichText.cpp: implementation of the CLotusRichText class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusRichText.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
	sr = CompoundTextClose(m_hRichText,NULL,NULL,NULL,0);if (sr != NOERROR) ErrorApiFail(sr,"CompoundTextClose ... failed");
	m_hRichText = NULL;	
	return ERR_OK;
}

DWORD CLotusRichText::Create(char *name)
{
	DWORD	dwr;
	Close();
	dwr = m_note->Create_CompoundText(name,&m_hRichText);
	if (dwr != ERR_OK) return SetError(true,ERR_FATAL,"CLotusRichText::Create failed because %s",m_note->GetErrorMsg());
	return ERR_OK;
}

DWORD CLotusRichText::ErrorApiFail(STATUS sr, char *msg)
{
	char	str[256];
	OSLoadString(NULLHANDLE,ERR(sr),str,sizeof(str));
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,str,sizeof(str),str,sizeof(str));

	if (msg != NULL) strcpy(m_err_msg,msg); else m_err_msg[0] = 0;
	strcat(m_err_msg," ERROR : ");
	strcat(m_err_msg,str);
	glog.log_strings(LOG_ERROR,m_err_msg);
	return ERR_API;
}

DWORD CLotusRichText::AttachFile(char *file_path)
{
	STATUS	sr;
	if (m_hRichText == NULL) return Error_Handle("CLotusRichText::AttachFile");
	sr = CompoundTextAssimilateFile(m_hRichText,file_path,0);if (sr != NOERROR) return ErrorApiFail(sr,"CompoundTextAssimilateFile ... failed");
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
