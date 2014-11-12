// LotusDB.cpp: implementation of the CLotusDB class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusDB.h"
#include "logclient.h"
#include "stdio.h"

#define _FILENAME_ "lotusdb.c"

#define _CHECK_HANDLE_		if (m_dbHandle == NULL) return _LOG_ERROR ERR_HANDLE,"Invalid Handle value (no database open)");
#define _CHECK_ACL_HANDLE_	if (m_hACL == NULL)	return _LOG_ERROR ERR_HANDLE,"acl is not open");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LOTUSDB_HANDLE	if (m_dbHandle == NULL) return Error_InvalidHandle(fnc_name);

class CLotusAgent 
{
public:
	CLotusAgent() 
	{
		mHandle = NULL;
		mContext = NULL;
	};
	~CLotusAgent() 
	{
		if (mContext != NULL) AgentDestroyRunContext(mContext);
		if (mHandle != NULL)  AgentClose(mHandle);
	};
	HAGENT		mHandle;
	HAGENTCTX	mContext;
	
};

CLotusDB::CLotusDB()
{
	m_ver = "Class CLotusDB " CLASS_VER;
	Clean();
}

CLotusDB::~CLotusDB()
{
	Release();
}

DWORD CLotusDB::Open(char *dbName)
{
	//char	dbpath[DBNAME_SIZE];
	STATUS		sr;	
	if (m_dbHandle != NULL)
	{
		if (strcmp(dbName,m_dbName) == 0) 
		{
			_LOG_WARNING "DB <%s> is already open",dbName);
			return ERR_OK;
		}
		DBClose();
	}
	*m_dbName = 0;

	m_hACL = NULL;
	sr = NSFDbOpen(dbName,&m_dbHandle);		if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbOpen of %s failed : %s",dbName,CLNotesError().getErrorString(sr));
	strncat(m_dbName,dbName,sizeof(m_dbName));
	_LOG_INFO "OpenDB -> DB = <%s>",m_dbName);
	return ERR_OK;
}

DWORD CLotusDB::CallAgent(char *agentName,NOTEHANDLE pnote)
{
	CLotusAgent	agent;
	STATUS		sr;	
	
	NOTEID		agentID = NULL;
	
	_CHECK_HANDLE_
		
	sr = NIFFindDesignNote(m_dbHandle,agentName,NOTE_CLASS_FILTER,&agentID);
	if (sr != NOERROR) 
	{
		_LOG_ERROR ERR_API,"NIFFindDesignNote for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
		sr = NIFFindPrivateDesignNote(m_dbHandle,agentName,NOTE_CLASS_FILTER,&agentID); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NIFFindPrivateDesignNote for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
	}
	sr = ::AgentOpen(m_dbHandle,agentID,&agent.mHandle);					if (sr != NOERROR) return _LOG_ERROR ERR_API,"AgentOpen for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
	sr = AgentCreateRunContext(agent.mHandle,NULL,(DWORD)0,&agent.mContext);if (sr != NOERROR) return _LOG_ERROR ERR_API,"AgentCreateRunContext for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
	
	if (pnote != NULL)
	{
		sr = ::AgentSetDocumentContext(agent.mContext,pnote);		if (sr != NOERROR) return _LOG_ERROR ERR_API,"AgentSetDocumentContext for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
	}
	sr = AgentRun(agent.mHandle,agent.mContext,(HANDLE)0,(DWORD)0);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"AgentRun for %s failed : %s",agentName,CLNotesError().getErrorString(sr));
	
	return ERR_OK;
}


//DEL DWORD CLotusDB::CheckIDFile()
//DEL {
//DEL 	DWORD dr;
//DEL 	if (m_idFilePath[0] == 0) 
//DEL 	{
//DEL 		sprintf(m_err_msg,"CLotusDB::CheckIDFile failed because id file is blank");
//DEL 		glog.log_strings(LOG_ERROR,m_err_msg);
//DEL 		return ERR_PARAM;
//DEL 	}
//DEL 
//DEL 	dr = ::GetFileAttributes(m_idFilePath);
//DEL 	if ((dr & FILE_ATTRIBUTE_DIRECTORY) || (dr == -1)) 
//DEL 	{
//DEL 		sprintf(m_err_msg,"CLotusDB::CheckIDFile failed because Id File Not found : %s",m_idFilePath);
//DEL 		glog.log_strings(LOG_ERROR,m_err_msg);
//DEL 		return ERR_PARAM;
//DEL 	}
//DEL 	glog.log_strings(LOG_ERROR,"CheckIDFile -> Id File OK = ",m_idFilePath);
//DEL 	return ERR_OK;
//DEL }


DWORD CLotusDB::Release()
{
	DBClose();	
	return ERR_OK;
}

//DEL DWORD CLotusDB::GetVar(char *name, char *value, WORD size,WORD logtype)
//DEL {
//DEL 	WORD i;
//DEL 	DWORD len;
//DEL 
//DEL 	value[0] = 0;
//DEL 	if (!OSGetEnvironmentString(name,value,size))
//DEL 	{
//DEL 		sprintf(m_err_msg,"GetVar -> Not Found : %s",name);
//DEL 		return ErrorLog(ERR_API);
//DEL 	}
//DEL 	//limpiar los espacios vacios al comienzo de la cadena
//DEL 	len = strlen(value);
//DEL 	for (i = 0;i < len ;i++)
//DEL 		if (value[i] != ' ') break;
//DEL 	if (i != 0)
//DEL 	{
//DEL 		memmove(value,&value[i],len-i);
//DEL 	}
//DEL 
//DEL 	switch(logtype)
//DEL 	{
//DEL 	case LOG_NONE:	m_err_msg[0] = 0;break;
//DEL 	case LOG_VAR:	sprintf(m_err_msg,"GetVar -> %s ",name);
//DEL 	default:		sprintf(m_err_msg,"GetVar -> %s = %s ",name,value);break;
//DEL 	}
//DEL 	_LOG_INFO m_err_msg);
//DEL 	return ERR_OK;
//DEL }

//DEL DWORD CLotusDB::SetVar(char *name, char *value)
//DEL {
//DEL 	if (value == NULL) 
//DEL 	{
//DEL 		sprintf(m_err_msg,"SetVar -> %s .... Cleared",name);
//DEL 		value = "";
//DEL 	}
//DEL 	else
//DEL 		sprintf(m_err_msg,"SetVar -> %s = %s ",name,value);
//DEL 	
//DEL 	OSSetEnvironmentVariable(name,value);
//DEL 	_LOG_INFO m_err_msg);
//DEL 	return ERR_OK;
//DEL }

/*
DWORD CLotusDB::InitNotes(char *init_filepath)
{
char*	arg[3];

  arg[0] = "";
  arg[1] = init_filepath;
  
	do
	{
	//sr = NotesInitExtended(2,arg);
	sr = NotesInitExtended(0,NULL);
	if (sr != NOERROR)
	{
	sprintf(m_err_msg,"Init -> NotesInitExtended...Failed Result : %d ",sr);
	glog.log_strings(LOG_ERROR,m_err_msg);
	return ERR_API;
	}
	OSGetDataDirectory(m_datadir);
	OSGetExecutableDirectory(m_execdir);
	} while (false);
	
	  return ERR_OK;
	  }
*/

//DEL DWORD CLotusDB::SetIdFile(char *idfilepath)
//DEL {
//DEL 	// validar que el fichero existe valido despues de asignarlo
//DEL 	m_idFilePath[0] = 0;
//DEL 	strncat(m_idFilePath,idfilepath,sizeof(m_idFilePath)-1);
//DEL 	return CheckIDFile();
//DEL }

DWORD CLotusDB::ReOpenDB()
{
	DBClose();
	return Open(m_dbName);
}

DWORD CLotusDB::OpenDBServer(char *server, char *dbname)
{
	char	dbpath[DBNAME_SIZE];
	OSPathNetConstruct("TCPIP",server,dbname,dbpath);
	return Open(dbpath);
}

DWORD CLotusDB::InfoGet(char *pinfo)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFDbInfoGet(m_dbHandle,pinfo); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbInfoGet failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}


DWORD CLotusDB::InfoSet(char *pinfo)
{
	_CHECK_HANDLE_
		STATUS		sr;	
		sr = NSFDbInfoSet(m_dbHandle,pinfo);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbInfoSet failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::ACLRead()
{
	_CHECK_HANDLE_
		STATUS		sr;	
	sr = NSFDbReadACL(m_dbHandle,&m_hACL);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbReadACL failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::ACLAdd(char *name, WORD level, ACL_PRIVILEGES *privileges, WORD flags)
{
	_CHECK_HANDLE_
	_CHECK_ACL_HANDLE_
	STATUS		sr;	
	sr = ::ACLAddEntry(m_hACL,name,level,privileges,flags);  if (sr != NOERROR) return _LOG_ERROR ERR_API,"ACLAddEntry %s failed : %s",name,CLNotesError().getErrorString(sr));

	return ERR_OK;
}

DWORD CLotusDB::ACLStore()
{
	_CHECK_HANDLE_
	_CHECK_ACL_HANDLE_
	STATUS		sr;	
	sr = NSFDbStoreACL(m_dbHandle,m_hACL,0L,0); if (sr != NOERROR) return _LOG_ERROR ERR_API,"ACLStore failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::ACLFree()
{
	_CHECK_HANDLE_
		if (m_hACL != NULL)	
		{
			OSMemFree(m_hACL);
			m_hACL = NULL;
		}
		return ERR_OK;	
}

DWORD CLotusDB::ACLDelete(char *name)
{
	_CHECK_HANDLE_
		_CHECK_ACL_HANDLE_
	STATUS		sr;	
	sr = ACLDeleteEntry(m_hACL,name);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"ACLDelete %s failed : %s",name,CLNotesError().getErrorString(sr));
	return ERR_OK;
	
}

DWORD CLotusDB::DBClose()
{
	if (m_dbHandle != NULL)
	{
		_LOG_INFO "CloseDB -> DB : ",m_dbName);
		ACLFree();
		::NSFDbClose(m_dbHandle);	
		m_dbHandle = NULL;
	}
	return ERR_OK;
}

DWORD CLotusDB::DBCreateAndCopy(char *source, char *dest, WORD note_class, WORD limit, DWORD flags)
{
	DBClose();
	STATUS		sr;	
	sr = NSFDbCreateAndCopy(source,dest,NOTE_CLASS_ALL,limit,flags,&m_dbHandle);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbCreateAndCopy from %s to %s failed : %s",source,dest,CLNotesError().getErrorString(sr));
	strcpy(m_dbName,dest);
	return ERR_OK;
}

DWORD CLotusDB::NoteFind(char *view, char *key, NOTEID* pnote)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = REGFindAddressBookEntry(m_dbHandle,view,key,pnote);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"REGFindAddressBookEntry view,key %s,%s failed : %s",view,key,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::NoteCreate(NOTEHANDLE *pnote)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFNoteCreate(m_dbHandle,pnote); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteCreate failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

void CLotusDB::Clean()
{
	// inicializar todas las variables
	m_dbHandle = NULL;
	m_hACL = NULL;
	m_idFilePath[0] = 0;
	m_dbName[0] = 0;
	m_section	= NULL;
	
}

CLotusDB::CLotusDB(CLotusSection *pSection)
{
	Clean();
	m_section = pSection;
}

DWORD CLotusDB::NoteDelete(NOTEID note_id, WORD flags)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFNoteDelete(m_dbHandle,note_id,flags); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteDelete failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::NoteLook(char *view, char *key, NOTEID *pnote_id)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = REGFindAddressBookEntry(m_dbHandle,view,key,pnote_id);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"REGFindAddressBookEntry view,key %s,%s failed : %s",view,key,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::NoteOpen(NOTEHANDLE *pnote,NOTEID note_id,WORD flags)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFNoteOpen(m_dbHandle,note_id,flags,pnote); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteOpen failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::NoteRefresh(NOTEHANDLE pnote)
{
	return ERR_OK;
}


DWORD CLotusDB::QuotaInfo_Get(char *db_path, DBQUOTAINFO *pQuota)
{
	STATUS		sr;	
	sr = NSFDbQuotaGet(db_path,pQuota);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbQuotaGet failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::QuotaInfo_Set(char *db_path,DBQUOTAINFO *pQuotaInfo,DWORD flags)
{
	STATUS		sr;	
	sr = NSFDbQuotaSetExt(db_path,flags,pQuotaInfo); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbQuotaSetExt failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::Delete(char *db_path)
{
	STATUS		sr;	
	sr = NSFDbDelete(db_path); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbDelete for %s failed : %s",db_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::NoteOpen_UNID(NOTEHANDLE *phandle, UNID* pnote_uid, WORD flags)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFNoteOpenByUNID(m_dbHandle,pnote_uid,flags,phandle); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteOpenByUNID failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::ProfileOpen(NOTEHANDLE *hprofile, char *name, char *uname, BOOL bcopy)
{
	WORD	nlen;
	WORD	unlen;
	_CHECK_HANDLE_
	STATUS		sr;	
		
	if (name == NULL) nlen = 0; else nlen = (WORD)clen(name);
	if (uname == NULL) unlen = 0; else unlen = (WORD)clen(uname);
	sr = NSFProfileOpen(m_dbHandle,name,nlen,uname,unlen,bcopy,hprofile); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFProfileOpen profile,user %s,%s failed : %s",name,uname,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusDB::ProfileGetField(char *name, char *uname, char *field, WORD *pwtype, BLOCKID *pvalue, DWORD *pdwlen)
{
	WORD	nlen;
	WORD	unlen;
	STATUS		sr;	
	
	_CHECK_HANDLE_
	if (name == NULL) nlen = 0; else nlen = (WORD)clen(name);
	if (uname == NULL) nlen = 0; else unlen = (WORD)clen(uname);
	if (field == NULL) return _LOG_ERROR ERR_PARAM,"Field Name is NULL");
	sr = NSFProfileGetField(m_dbHandle,name,nlen,uname,unlen,field,strlen(field),pwtype,pvalue,pdwlen); if (sr != NOERROR) return _LOG_ERROR ERR_API,"ProfileGetField profile,user,field %s,%s failed : %s",name,uname,field,CLNotesError().getErrorString(sr));
	return ERR_OK;	
}

DWORD CLotusDB::ProfileEnum(char *name, NSFPROFILEENUMPROC pfunc, void *pctx, DWORD flags)
{
	WORD	nlen;
	STATUS		sr;	
	_CHECK_HANDLE_
	if (name == NULL) nlen = 0; else nlen = strlen(name);
	sr = NSFProfileEnum(m_dbHandle,name,nlen,pfunc,pctx,flags);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"ProfileEnum %s failed :: %s",name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

#ifdef LOTUS8

DWORD CLotusDB::AttachIDFile(char *profile_name, char *user_name, char *idfile_path, char *idfile_pass)
{
	STATUS		sr;	
	_CHECK_HANDLE_
	sr = SECAttachIdFileToDB(m_dbHandle,profile_name,strlen(profile_name),user_name,strlen(user_name),idfile_path,idfile_pass,0,NULL); if (sr != NOERROR) return _LOG_ERROR ERR_API,"SECAttachIdFileToDB profile,user,idfile %s,%s,%s failed :: %s",profile_name,user_name,idfile_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

#endif

DWORD CLotusDB::GetBuildVersion(WORD *pwVersion)
{
	_CHECK_HANDLE_
	STATUS		sr;	
	sr = NSFDbGetBuildVersion(m_dbHandle,pwVersion); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFDbGetBuildVersion failed :: %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}
