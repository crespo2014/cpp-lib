// LotusSection.h: interface for the CLotusSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_)
#define AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"
#include "bobject.h"

#ifdef LOTUS8
#include "lotus8\global.h"
#include "lotus8\extmgr.h"
#include "lotus8\nsferr.h"
#include "lotus8\bsafeerr.h"
#include "lotus8\dname.h"
#include "lotus8\osmisc.h"
#include "lotus8\osenv.h"
#include "lotus8\ostime.h"
#include "lotus8\ns.h"
#include "lotus8\osmem.h"
#include "lotus8\nsfdb.h"
#include "lotus8\osfile.h"
#include "lotus8\acl.h"
#include "lotus8\kfm.h"
#include "lotus8\nsfsearc.h"
#include "lotus8\textlist.h"
#include "lotus8\agents.h"
#include "lotus8\oserr.h"
#include "lotus8\lookup.h"
#include "lotus8\reg.h"
#include "lotus8\nsfdata.h"
#include "lotus8\pool.h"
#include "lotus8\nsfnote.h"
#include "lotus8\mailserv.h"
#include "lotus8\easycd.h"
#include "lotus8\colorid.h"
#include "lotus8\bsafe.h"
#include "lotus8\editods.h"
#else
#include "lotus\global.h"
#include "lotus\extmgr.h"
#include "lotus\nsferr.h"
#include "lotus\bsafeerr.h"
#include "lotus\dname.h"
#include "lotus\osmisc.h"
#include "lotus\osenv.h"
#include "lotus\ostime.h"
#include "lotus\ns.h"
#include "lotus\osmem.h"
#include "lotus\nsfdb.h"
#include "lotus\osfile.h"
#include "lotus\acl.h"
#include "lotus\kfm.h"
#include "lotus\nsfsearc.h"
#include "lotus\textlist.h"
#include "lotus\agents.h"
#include "lotus\oserr.h"
#include "lotus\lookup.h"
#include "lotus\reg.h"
#include "lotus\nsfdata.h"
#include "lotus\pool.h"
#include "lotus\nsfnote.h"
#include "lotus\mailserv.h"
#include "lotus\easycd.h"
#include "lotus\colorid.h"
#include "lotus\bsafe.h"
#include "lotus\editods.h"

#endif

class CLotusSection  : public CbObject
{

private:
	char	m_datadir[MAX_PATH];
	char	m_execdir[MAX_PATH];
	BOOL	m_notes_thread_init;		// Inidica que se hizo una inicializacion del tipo threadInit 
	BOOL	m_notes_init;				// inidica que se hizo una inicializacion general de notes

public:
	DWORD ChangePassword(char * idfile_path, char * old_password, char * new_password);
	
	DWORD NotesInit(char* ini_file);
	DWORD Error_Handle(char *err_str, int max_len,char *function);
	DWORD Error_Api(char* err_str,int max_len,STATUS sr,char* function);
	DWORD NotesRelease();
	DWORD GetVar(char *name, char *value, WORD size);
	DWORD SetVar(char *name, char *value);
	//DWORD ErrorLog(DWORD code,char* msg = NULL);
	DWORD Login(char* idfile_path,char* pass);
	DWORD NotesThreadInit();
	DWORD NotesInit(int argc = 0,char** argv = NULL);
	void	ReadEnvironment();

	CLotusSection();
	virtual ~CLotusSection();

	char*	GetExecDir()	{return m_execdir;};
	char*	GetDataDir()	{return m_datadir;};
	char*	GetErrorMsg()	{return m_err_msg;};

	STATUS	m_sr;				// Codigo de error de la operacion

	DWORD SetError_Add_NApi_code_msg(STATUS ecode,char* format,...);
	static DWORD Add_NApi_code_msg(STATUS ecode,char* err_buff,WORD buff_size,char* format,...);

public:
	char* EM_GetName(WORD em_xxx);
	DWORD Password_Check(char * idfile_path, char * password);
	DWORD To_Canonical(char* text, WORD max_size);
	DWORD To_Abbreviate(char* text, WORD max_size);
	void To_Native(char* text, WORD size = 0);
	void To_LMBCS(char* text, WORD size = 0);
};

#endif // !defined(AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_)
