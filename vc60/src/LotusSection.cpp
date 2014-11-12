// LotusSection.cpp: implementation of the CLotusSection class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusSection.h"
#include "utils.h"

#define _FILENAME_ "lotussection.c"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLotusSection::CLotusSection()
{
	m_notes_init = false;
	m_notes_thread_init = false;
	m_sr = NOERROR;
}

CLotusSection::~CLotusSection()
{
	NotesRelease();
}

DWORD CLotusSection::NotesInit(int argc, char **argv)
{
	if (NotesInitExtended(argc,argv) != NOERROR) return _LOG_AT;
	m_notes_init = true;
	return ERR_OK;
}

DWORD CLotusSection::NotesThreadInit()
{
	STATUS	sr;
	sr = NotesInitThread();
	if (sr != NOERROR)	return _LOG_ERROR ERR_API,"CLotusSection -> NotesInitThread ... Failed Result : %d",sr);
	m_notes_thread_init = true;
	return ERR_OK;
}

DWORD CLotusSection::Login(char *idfile_path, char *pass)
{
	DWORD	dr;
	STATUS	sr;
	if ((idfile_path[0] == 0) || (pass[0] == 0))	return _LOG_ERROR ERR_PARAM,"Missing id file or password");

	dr = ::GetFileAttributes(idfile_path);
	if ((dr & FILE_ATTRIBUTE_DIRECTORY) || (dr == -1)) 
	{
		return _LOG_ERROR ERR_PARAM,"CLotusSection::Login ... ID File (%s) not found",idfile_path);
	}
	sr = SECKFMSwitchToIDFile(idfile_path,pass,NULL,0,0,NULL); if (sr != NOERROR) return _LOG_ERROR ERR_API,"SECKFMSwitchToIDFile for %s failed : %s",idfile_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusSection::SetVar(char *name, char *value)
{
	// convertir la variable primero
	To_LMBCS(value);
	OSSetEnvironmentVariable(name,value);
	return ERR_OK;
}

DWORD CLotusSection::GetVar(char *name, char *value, WORD size)
{
	WORD i;
	DWORD len;
	value[0] = 0;
	if (!OSGetEnvironmentString(name,value,size))
	{
		return _LOG_ERROR ERR_API,"CLotusSection::GetVar (%s) -> Not Found",name);
	}
	//limpiar los espacios vacios al comienzo de la cadena
	len = strlen(value);
	for (i = 0;i < len ;i++)
		if (value[i] != ' ') break;
	if (i != 0)
	{
		memmove(value,&value[i],len-i);
	}
	To_Native(value);
	return ERR_OK;
}

DWORD CLotusSection::NotesRelease()
{
	if (m_notes_init)			::NotesTerm();
	if (m_notes_thread_init)	::NotesTermThread();
	m_notes_init = false;
	m_notes_thread_init = false;
	return ERR_OK;
}

DWORD CLotusSection::NotesInit(char *ini_file)
{
	STATUS	sr;
	char	*argv[2];
	char	arg[MAX_PATH];

	argv[0] = NULL;
	argv[1] = arg;
	sprintf(arg,"=%s",ini_file);

	sr = NotesInitExtended(2,argv);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"CLotusSection::NotesInit -> NotesInitExtended(%s)... failed with code %u",ini_file,sr);
	m_notes_init = true;
	return ERR_OK;
}

DWORD CLotusSection::ChangePassword(char * idfile_path, char * old_password, char * new_password)
{
		STATUS	sr;
	DWORD	dr;
	dr = ::GetFileAttributes(idfile_path);
	if ((dr & FILE_ATTRIBUTE_DIRECTORY) || (dr == -1)) 
	{
		return _LOG_ERROR ERR_PARAM,"CLotusSection::Login ... ID File (%s) not found",idfile_path);
	}
	sr = SECKFMChangePassword(idfile_path,old_password,new_password);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"SECKFMChangePassword for %s failed : %s",idfile_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

void CLotusSection::To_Native(char* text, WORD size)
{
	if (size == 0) size = strlen(text) + 1;
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,text,size,text,size);
}

void CLotusSection::To_LMBCS(char* text, WORD size)
{
	if (size == 0) size = strlen(text) + 1;
	OSTranslate(OS_TRANSLATE_NATIVE_TO_LMBCS,text,size,text,size);
}

DWORD CLotusSection::To_Abbreviate(char *text, WORD max_size)
{
	char tmp_str[MAXUSERNAME];
	STATUS	sr;
	sr = DNAbbreviate(0,NULL,text,tmp_str,sizeof(tmp_str),NULL);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"DNAbbreviate for %s failed : %s",text,CLNotesError().getErrorString(sr));
	if (strlen(tmp_str) >= max_size) return _LOG_ERROR ERR_FATAL,"overflow");
	strcpy(text,tmp_str);
	return ERR_OK;
}

DWORD CLotusSection::To_Canonical(char *text, WORD max_size)
{
	char tmp_str[MAXUSERNAME];
	STATUS	sr;
	sr =  DNCanonicalize(0,NULL,text,tmp_str,sizeof(tmp_str),NULL);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"DNCanonicalize for %s failed : %s",text,CLNotesError().getErrorString(sr));
	if (strlen(tmp_str) >= max_size) return _LOG_ERROR ERR_FATAL,"overflow");
	strcpy(text,tmp_str);
	return ERR_OK;

}

DWORD CLotusSection::Password_Check(char *idfile_path, char *password)
{
	STATUS	sr;
	if ((idfile_path == NULL) || (GetFileAttributes(idfile_path) == INVALID_FILE_ATTRIBUTES)) return ERR_NOT_FOUND;
	sr = SECKFMChangePassword(idfile_path,password,password);
	if (sr != NOERROR) return _LOG_ERROR ERR_FALSE,"SECKFMChangePassword for %s failed : %s",idfile_path,CLNotesError().getErrorString(sr));
	return ERR_OK;	
}

DWORD CLotusSection::SetLNotesVersion(WORD wVersion)
{
	if (wVersion <= 166) desktop_file = "desktop5.dsk";
	else
		if (wVersion <= 254) desktop_file = "desktop6.ndk";
		else
			desktop_file = "desktop8.ndk";

	return ERR_OK;
}
