// LotusSection.h: interface for the CLotusSection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_)
#define AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"
#include "lnoteserror.h"


class CLotusSection  : public CbObject
{

private:
	BOOL	m_notes_thread_init;		// Inidica que se hizo una inicializacion del tipo threadInit 
	BOOL	m_notes_init;				// inidica que se hizo una inicializacion general de notes
public:
	DWORD ChangePassword(char * idfile_path, char * old_password, char * new_password);
	
	DWORD NotesInit(char* ini_file);
	DWORD NotesRelease();
	DWORD GetVar(char *name, char *value, WORD size);
	DWORD SetVar(char *name, char *value);
	DWORD Login(char* idfile_path,char* pass);
	DWORD NotesThreadInit();
	DWORD NotesInit(int argc = 0,char** argv = NULL);

	CLotusSection();
	virtual ~CLotusSection();

	STATUS	m_sr;				// Codigo de error de la operacion

public:
	DWORD SetLNotesVersion(WORD wVersion);
	DWORD Password_Check(char * idfile_path, char * password);
	DWORD To_Canonical(char* text, WORD max_size);
	DWORD To_Abbreviate(char* text, WORD max_size);
	void To_Native(char* text, WORD size = 0);
	void To_LMBCS(char* text, WORD size = 0);

	char	*desktop_file;
};

#endif // !defined(AFX_LOTUSSECTION_H__E0139C16_0C18_49EB_97D3_7C85ABF695C1__INCLUDED_)
