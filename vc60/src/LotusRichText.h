// LotusRichText.h: interface for the CLotusRichText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSRICHTEXT_H__4C97ADA8_C064_4AD2_B23D_98CDC51F5205__INCLUDED_)
#define AFX_LOTUSRICHTEXT_H__4C97ADA8_C064_4AD2_B23D_98CDC51F5205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lotusnote.h"
#include "memarray.h"

class CLotusRichText : public CbObject 
{
public:
	DWORD DumpItem_Start();
	DWORD NewItem_Save(char* name,WORD flags = 0);
	DWORD NewItem_Initialize(DWORD max_size = 0);
	DWORD AttachFile(char* file_path);
	DWORD ErrorApiFail(STATUS sr,char* msg);
	DWORD Create(char* name);
	DWORD Close();
	CLotusRichText(CLotusNote*	pnote);
	virtual ~CLotusRichText();
private:
	HANDLE	m_hRichText;
	//char	m_errmsg[300];
	CLotusNote	*m_note;
	CMemArray	m_newitem_mem;
	DWORD		m_newitem_size;
	DWORD		m_dumpItem_pos;
};

#endif // !defined(AFX_LOTUSRICHTEXT_H__4C97ADA8_C064_4AD2_B23D_98CDC51F5205__INCLUDED_)
