// LotusDB.cpp: implementation of the CLotusDB class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusDB.h"
#include "logclient.h"
#include "stdio.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LOTUSDB_HANDLE	if (m_dbHandle == NULL) return Error_InvalidHandle(fnc_name);

CLotusDB::CLotusDB()
{
	Clean();
}

CLotusDB::~CLotusDB()
{
	Release();
}

DWORD CLotusDB::Open(char *dbName)
{
	char	msg[200];
	if (m_dbHandle != NULL)
	{
		if (strcmp(dbName,m_dbName) == 0) 
		{
			glog.log_strings(LOG_WARNING,"DB <",dbName,"> is already open");
			return ERR_OK;
		}
		DBClose();
	}
	if (dbName != m_dbName)	strcpy(m_dbName,dbName);
	m_hACL = NULL;
	sr = NSFDbOpen(m_dbName,&m_dbHandle);
	if (sr == NOERROR)	
	{
		glog.log_strings(LOG_TRACE,"OpenDB -> DB = <",m_dbName,">");
		return ERR_OK;
	}
	sprintf(msg,"NSFDbOpen : Failed  Database path = %s ",dbName);
	m_dbName[0] = 0;
	return ErrorApiFail(msg);
}

DWORD CLotusDB::CallAgent(char *agentName,NOTEHANDLE pnote)
{
	NOTEID		agentID = NULL;
	HAGENT		agentHandle = NULL;
	HAGENTCTX	agentContext = NULL;
	char		msg[300];
	
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::CallAgent");

	//result = -1;
	do
	{
		sr = NIFFindDesignNote(m_dbHandle,agentName,NOTE_CLASS_FILTER,&agentID);
		if (sr != NOERROR)
		{
			sprintf(msg,"AgentOpen -> NIFFindDesignNote : Failed  Agent : %s  Result : %d ",agentName,sr);
			glog.log_strings(LOG_ERROR,msg);
			sr = NIFFindPrivateDesignNote(m_dbHandle,agentName,NOTE_CLASS_FILTER,&agentID);
			if (sr != NOERROR)
			{
				sprintf(msg,"AgentOpen -> NIFFindPrivateDesignNote : Failed  Agent : %s ",agentName);
				return ErrorApiFail(msg);
			}
		}
		glog.log_strings(LOG_TRACE,"NIFFindDesignNote or NIFFindPrivateDesignNote is OK");

		sr = ::AgentOpen(m_dbHandle,agentID,&agentHandle);
		if (sr != NOERROR)
		{
			sprintf(msg,"AgentOpen -> AgentOpen : Failed  Agent : %s ",agentName);
			break;
		}
		glog.log_strings(LOG_TRACE,"AgentOpen is OK");
		sr = AgentCreateRunContext(agentHandle,NULL,(DWORD)0,&agentContext);
		if (sr != NOERROR)
		{
			sprintf(msg,"AgentOpen -> AgentCreateRunContext : Failed  Agent : %s ",agentName);
			break;
		}
		glog.log_strings(LOG_TRACE,"AgentCreateRunContext is OK");
		if (pnote != NULL)
		{
			sr = ::AgentSetDocumentContext(agentContext,pnote);
			if (sr != NOERROR) 
			{
				sprintf(msg,"AgentOpen -> AgentSetDocumentContext : Failed  Agent : %s ",agentName);
				sr = ERR_NULL_NOTEHANDLE;
				break;
			}
			glog.log_strings(LOG_TRACE,"AgentSetDocumentContext is OK");
		}
		
		sr = AgentRun(agentHandle,agentContext,(HANDLE)0,(DWORD)0);
		if (sr != NOERROR)
		{
			sprintf(msg," AgentOpen -> AgentRun : Failed  Agent : %s ",agentName);
			break;
		}
		glog.log_strings(LOG_TRACE,"AgentRun is OK");
		break;

	} while (false);

	if (agentContext != NULL) AgentDestroyRunContext(agentContext);
	if (agentHandle != NULL)  AgentClose(agentHandle);
	return m_section->Error_Api(SSIZE(m_err_msg),sr,msg);
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
//DEL 	glog.log_strings(LOG_TRACE,m_err_msg);
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
//DEL 	glog.log_strings(LOG_TRACE,m_err_msg);
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
	if (m_dbHandle == NULL) return InvalidHandle();
	sr = NSFDbInfoGet(m_dbHandle,pinfo);
	if (sr == NOERROR)	return ERR_OK;
	return ErrorApiFail("DBGetInfo ...Failed ");
}

DWORD CLotusDB::InvalidHandle()
{
	sprintf(m_err_msg,"Invalid Handle, not database open");
	return ERR_HANDLE;
}

DWORD CLotusDB::InfoSet(char *pinfo)
{
	if (m_dbHandle == NULL) return InvalidHandle();
	sr = NSFDbInfoSet(m_dbHandle,pinfo);
	if (sr == NOERROR)	return ERR_OK;
	return ErrorApiFail("DBSetInfo ...Failed ");
}

DWORD CLotusDB::ACLRead()
{
	char msg[300];
	if (m_dbHandle == NULL) return InvalidHandle();
	sr = NSFDbReadACL(m_dbHandle,&m_hACL);
	if (sr == NOERROR)	return ERR_OK;
	sprintf(msg,"NSFDbReadACL ...Failed DB = \"%s\" ",m_dbName,sr);
	return ErrorApiFail(msg);
	
}

DWORD CLotusDB::ACLAdd(char *name, WORD level, ACL_PRIVILEGES *privileges, WORD flags)
{
	char	msg[300];
	if ((m_dbHandle == NULL)||(m_hACL == NULL)) return InvalidHandle();
	sr = ::ACLAddEntry(m_hACL,name,level,privileges,flags);
	if (sr == NOERROR)	return ERR_OK;
	sprintf(msg,"ACLAddEntry ...Failed DB = \"%s\" user =\"%s\" ",m_dbName,name);
	return ErrorApiFail(msg);	
}

DWORD CLotusDB::ACLStore()
{
	char	msg[300];
	if ((m_dbHandle == NULL)||(m_hACL == NULL)) return InvalidHandle();
	sr = NSFDbStoreACL(m_dbHandle,m_hACL,0L,0);
	if (sr == NOERROR)	return ERR_OK;
	sprintf(msg,"NSFDBStoreACL ...Failed DB = \"%s\" ",m_dbName);
	return ErrorApiFail(msg);
}

DWORD CLotusDB::ACLFree()
{
	if ((m_dbHandle == NULL)||(m_hACL == NULL)) return InvalidHandle();
	OSMemFree(m_hACL);
	m_hACL = NULL;
	return ERR_OK;	
}

DWORD CLotusDB::ACLDelete(char *name)
{
	char	msg[300];
	if ((m_dbHandle == NULL)||(m_hACL == NULL)) return InvalidHandle();
	sr = ACLDeleteEntry(m_hACL,name);
	if (sr == NOERROR)	return ERR_OK;
	sprintf(msg,"ACLDeleteEntry ...Failed DB = \"%s\" user =\"%s\" ",m_dbName,name);
	return ErrorApiFail(msg);
}

//DEL DWORD CLotusDB::NotesInit()
//DEL {
//DEL 	sr = NotesInitExtended(0,NULL);
//DEL 	if (sr != NOERROR)
//DEL 	{
//DEL 		glog.log_sint(LOG_ERROR,"Init -> NotesInitExtended...Failed Result : ",sr);
//DEL 		return ERR_API;
//DEL 	}
//DEL 	OSGetDataDirectory(m_datadir);
//DEL 	OSGetExecutableDirectory(m_execdir);
//DEL 	m_notes_init = true;
//DEL 
//DEL 	return ERR_OK;
//DEL }

//DEL DWORD CLotusDB::NotesRelease()
//DEL {
//DEL 	NotesTerm();
//DEL 	return ERR_OK;
//DEL }

DWORD CLotusDB::DBClose()
{
	if (m_dbHandle == NULL) return ERR_OK;
	glog.log_strings(LOG_TRACE,"CloseDB -> DB : ",m_dbName);
	if (m_hACL != NULL)  { glog.log_strings(LOG_TRACE,"Free .... ACL");OSMemFree(m_hACL);}
	::NSFDbClose(m_dbHandle);	
	m_dbHandle = NULL;
	m_hACL = NULL;
	return ERR_OK;
}

DWORD CLotusDB::DBCreateAndCopy(char *source, char *dest, WORD note_class, WORD limit, DWORD flags)
{
	char	msg[300];
	DBClose();
	sr = NSFDbCreateAndCopy(source,dest,NOTE_CLASS_ALL,limit,flags,&m_dbHandle);
	if (sr == NOERROR)	
	{
		strcpy(m_dbName,dest);
		return ERR_OK;
	}
	sprintf(msg,"NSFDbCreateAndCopy ...Failed source = \"%s\" dest = \"%s\" ",source,dest);
	return ErrorApiFail(msg);
}

DWORD CLotusDB::NoteFind(char *view, char *key, NOTEID* pnote)
{
	if (m_dbHandle == NULL) return InvalidHandle();
	return m_section->Error_Api(SSIZE(m_err_msg),REGFindAddressBookEntry(m_dbHandle,view,key,pnote),"CLotusDB::NoteFind->REGFindAddressBookEntry");
}

DWORD CLotusDB::NoteCreate(NOTEHANDLE *pnote)
{
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::NoteCreate");
	return m_section->Error_Api(SSIZE(m_err_msg),NSFNoteCreate(m_dbHandle,pnote),"CLotusDB::NoteCreate->NSFNoteCreate");
}

/*
	Toma un mensaje o m_err y le incorpora el codigo de error de la api, 
	lo pasa el log y devuelve ERR_API
*/
DWORD CLotusDB::ErrorApiFail(char* msg)
{
	char	str[255];
	OSLoadString(NULLHANDLE,ERR(sr),SSIZE(str));
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,SSIZE(str),SSIZE(str));
	sprintf(m_err_msg,"%s Code : %d Message : %s ",msg,sr,str);
	glog.log_strings(LOG_ERROR,m_err_msg);
	return ERR_API;
}

void CLotusDB::Clean()
{
	// inicializar todas las variables
	m_dbHandle = NULL;
	m_hACL = NULL;
	m_idFilePath[0] = 0;
	m_err_msg[0] = 0;
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
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::NoteDelete");
	return m_section->Error_Api(SSIZE(m_err_msg),NSFNoteDelete(m_dbHandle,note_id,flags),"CLotusDB::NoteDelete->NSFNoteDelete");
}

DWORD CLotusDB::NoteLook(char *view, char *key, NOTEID *pnote_id)
{
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::NoteLook");
	return m_section->Error_Api(SSIZE(m_err_msg),REGFindAddressBookEntry(m_dbHandle,view,key,pnote_id),"CLotusDB::NoteLook->REGFindAddressBookEntry");
	
}

DWORD CLotusDB::NoteOpen(NOTEHANDLE *pnote,NOTEID note_id,WORD flags)
{
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::NoteOpen");
	return m_section->Error_Api(SSIZE(m_err_msg),NSFNoteOpen(m_dbHandle,note_id,flags,pnote),"CLotusDB::NoteOpen->NSFNoteOpen");
}

DWORD CLotusDB::NoteRefresh(NOTEHANDLE pnote)
{
	return ERR_OK;
}

DWORD CLotusDB::Error_InvalidHandle(char *function)
{
	_snprintf(SSIZE(m_err_msg),"%s failed with Invalid Handle value (no database open)",function);
	glog.log_strings(LOG_ERROR,m_err_msg);
	return ERR_HANDLE;
}

DWORD CLotusDB::QuotaInfo_Get(char *db_path, DBQUOTAINFO *pQuota)
{
	return m_section->Error_Api(SSIZE(m_err_msg),NSFDbQuotaGet(db_path,pQuota),"CLotusDB::GetQuota->NSFDbQuotaGet");	
}

DWORD CLotusDB::QuotaInfo_Set(char *db_path,DBQUOTAINFO *pQuotaInfo,DWORD flags)
{
	//if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::QuotaInfo_Set");
	return m_section->Error_Api(SSIZE(m_err_msg),NSFDbQuotaSetExt(db_path,flags,pQuotaInfo),"CLotusDB::GetQuota->NSFDbQuotaGet");	
}

DWORD CLotusDB::Delete(char *db_path)
{
	return m_section->Error_Api(SSIZE(m_err_msg),NSFDbDelete(db_path),"CLotusDB::Delete->NSFDbDelete");	
}

DWORD CLotusDB::NoteOpen_UNID(NOTEHANDLE *phandle, UNID* pnote_uid, WORD flags)
{
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::NoteOpen");
	return m_section->Error_Api(SSIZE(m_err_msg),NSFNoteOpenByUNID(m_dbHandle,pnote_uid,flags,phandle),"CLotusDB::NoteOpen->NSFNoteOpenByUNID");
}

DWORD CLotusDB::ProfileOpen(NOTEHANDLE *hprofile, char *name, char *uname, BOOL bcopy)
{
	WORD	nlen;
	WORD	unlen;
	if (m_dbHandle == NULL) return Error_InvalidHandle("CLotusDB::ProfileOpen");

	if (name == NULL) nlen = 0; else nlen = strlen(name);
	if (uname == NULL) unlen = 0; else unlen = strlen(uname);
	sr = NSFProfileOpen(m_dbHandle,name,nlen,uname,unlen,bcopy,hprofile);
	return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),"CLotusDB::ProfileOpen %s,%s",name,uname);
}

DWORD CLotusDB::ProfileGetField(char *name, char *uname, char *field, WORD *pwtype, BLOCKID *pvalue, DWORD *pdwlen)
{
	WORD	nlen;
	WORD	unlen;
//	WORD	flen;
	char	*fnc_name = "CLotusDB::ProfileGetField";

	if (m_dbHandle == NULL) return Error_InvalidHandle(fnc_name);
	if (name == NULL) nlen = 0; else nlen = strlen(name);
	if (uname == NULL) nlen = 0; else unlen = strlen(name);
	if (field == NULL) return SetError(true,ERR_PARAM,"%s->Field Name is NULL",fnc_name);
	sr = NSFProfileGetField(m_dbHandle,name,nlen,uname,unlen,field,strlen(field),pwtype,pvalue,pdwlen);
	return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),"%s %s,%s,%s",fnc_name,name,uname,field);
}

DWORD CLotusDB::ProfileEnum(char *name, NSFPROFILEENUMPROC pfunc, void *pctx, DWORD flags)
{
	WORD	nlen;
	char	*fnc_name = "CLotusDB::ProfileEnum";
	if (m_dbHandle == NULL) return Error_InvalidHandle(fnc_name);
	if (name == NULL) nlen = 0; else nlen = strlen(name);
	sr = NSFProfileEnum(m_dbHandle,name,nlen,pfunc,pctx,flags);
	return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),fnc_name);
}

#ifdef LOTUS8

DWORD CLotusDB::AttachIDFile(char *profile_name, char *user_name, char *idfile_path, char *idfile_pass)
{
	WORD	nlen;
	char	*fnc_name = "CLotusDB::AttachIDFile";
	if (m_dbHandle == NULL) return Error_InvalidHandle(fnc_name);
	sr = SECAttachIdFileToDB(m_dbHandle,profile_name,strlen(profile_name),user_name,strlen(user_name),idfile_path,idfile_pass,0,NULL);
	return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),fnc_name);
}

#endif