// LotusDB.h: interface for the CLotusDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSDB_H__8D45AD7E_E3FB_454C_9C7F_24E2122F9B2B__INCLUDED_)
#define AFX_LOTUSDB_H__8D45AD7E_E3FB_454C_9C7F_24E2122F9B2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LotusSection.h"

#define DBNAME_SIZE	256

class CLotusDB  : public CbObject
{
private:
	DWORD ProfileGetField(char* name, char *uname,char *field, WORD* pwtype,BLOCKID* pvalue, DWORD* pdwlen);
	void Clean();

	CLotusSection	*m_section;
	DBHANDLE	m_dbHandle;					// handle de la base de datos Notes abierta
	char		m_agentmsg[300];
	char		m_dbName[DBNAME_SIZE];
	char		m_idFilePath[MAX_PATH];		// Fichero id ruta completa no es igual al useridfile del notes.ini 
	HANDLE		m_hACL;						// Lista de control de acceso

public:
	CLotusSection *getSection() { return m_section; };
	DWORD GetBuildVersion(WORD* pwVersion);
	DWORD AttachIDFile(char* profile_name,char* user_name,char *idfile_path,char* idfile_pass);
	DWORD ProfileEnum(char *name,NSFPROFILEENUMPROC pfunc,void* pctx = NULL, DWORD flags = 0);
	DWORD ProfileOpen( NOTEHANDLE* hprofile,char *name, char *uname, BOOL bcopy);
	DWORD Delete(char* db_path);
	DWORD QuotaInfo_Set(char* db_path,DBQUOTAINFO *pQuotaInfo,DWORD flags = 0);
	DWORD QuotaInfo_Get(char* db_path,DBQUOTAINFO* pQuota);
	DWORD Error_InvalidHandle(char* function);
	DWORD NoteOpen_UNID(NOTEHANDLE *phandle,UNID* pnote_uid,WORD flags = 0);
	DWORD NoteOpen(NOTEHANDLE *pnote,NOTEID note_id,WORD flags = 0);
	DWORD NoteLook(char *view, char *key, NOTEID *pnote_id);
	DWORD NoteDelete(NOTEID note_id,WORD flag = 0);
	DWORD NoteCreate(NOTEHANDLE* pnote);
	DWORD NoteFind(char* view,char* key,NOTEID* pnote);
	DWORD NoteRefresh(NOTEHANDLE pnote);
	BOOL IsValid()	{return m_dbHandle != NULL;};
	DWORD DBCreateAndCopy(char* source,char* dest,WORD note_class,WORD limit,DWORD flags);
	DWORD DBClose();
	DWORD ACLDelete(char* name);
	DWORD ACLFree();
	DWORD ACLStore();
	DWORD ACLAdd(char* name,WORD level,ACL_PRIVILEGES* privileges, WORD flags);
	DWORD ACLRead();
	DWORD InfoSet(char* pinfo);
	DWORD InfoGet(char* pinfo);
	DWORD OpenDBServer(char* server, char* dbname);
	DWORD ReOpenDB();
	DWORD LogLotusErrorMsg(STATUS sr);
	DWORD Release();
	DWORD CallAgent(char* agentName,NOTEHANDLE pnote = NULL);
	DWORD Open(char* dbName);
	CLotusDB();
	CLotusDB(CLotusSection* pSection);
	void SetSection(CLotusSection* pSection) { m_section = pSection; };
	virtual ~CLotusDB();
};

#endif // !defined(AFX_LOTUSDB_H__8D45AD7E_E3FB_454C_9C7F_24E2122F9B2B__INCLUDED_)
