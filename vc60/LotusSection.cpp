// LotusSection.cpp: implementation of the CLotusSection class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusSection.h"
#include "utils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct
{
	char*	name;
	WORD	type;
	
}EM_TABLE [] = {
	{"EM_NSFDBCLOSESESSION",1},
	{"EM_NSFDBCLOSE",2},
	{"EM_NSFDBCREATE",3},
	{"EM_NSFDBDELETE",4},
	{"EM_NSFNOTEOPEN",5},
	{"EM_NSFNOTECLOSE",6},
	{"EM_NSFNOTECREATE",7},
	{"EM_NSFNOTEDELETE",8},
	{"EM_NSFNOTEOPENBYUNID",10},
	{"EM_FTGETLASTINDEXTIME",11},
	{"EM_FTINDEX",12},
	{"EM_FTSEARCH",13},
	{"EM_NIFFINDBYKEY",14},
	{"EM_NIFFINDBYNAME",15},
	{"EM_NIFOPENNOTE",17},
	{"EM_NIFREADENTRIES",18},
	{"EM_NIFUPDATECOLLECTION",20},
	{"EM_NSFDBALLOCOBJECT",22},
	{"EM_NSFDBCOMPACT",23},
	{"EM_NSFDBDELETENOTES",24},
	{"EM_NSFDBFREEOBJECT",25},
	{"EM_NSFDBGETMODIFIEDNOTETABLE",26},
	{"EM_NSFDBGETNOTEINFO",29},
	{"EM_NSFDBGETNOTEINFOBYUNID",30},
	{"EM_NSFDBGETOBJECTSIZE",31},
	{"EM_NSFDBGETSPECIALNOTEID",32},
	{"EM_NSFDBINFOGET",33},
	{"EM_NSFDBINFOSET",34},
	{"EM_NSFDBLOCATEBYREPLICAID",35},
	{"EM_NSFDBMODIFIEDTIME",36},
	{"EM_NSFDBREADOBJECT",37},
	{"EM_NSFDBREALLOCOBJECT",39},
	{"EM_NSFDBREPLICAINFOGET",40},
	{"EM_NSFDBREPLICAINFOSET",41},
	{"EM_NSFDBSPACEUSAGE",42},
	{"EM_NSFDBSTAMPNOTES",43},
	{"EM_NSFDBWRITEOBJECT",45},
	{"EM_NSFNOTEUPDATE",47},
	{"EM_NIFOPENCOLLECTION",50},
	{"EM_NIFCLOSECOLLECTION",51},
	{"EM_NSFDBGETBUILDVERSION",52},
	{"EM_NSFDBITEMDEFTABLE",56},
	{"EM_NSFDBREOPEN",59},
	{"EM_NSFDBOPENEXTENDED",63},	
	{"EM_NSFNOTEOPENEXTENDED",64},
	{"EM_TERMINATENSF",69},
	{"EM_NSFNOTEDECRYPT",70},
	{"EM_GETPASSWORD",73},
	{"EM_SETPASSWORD",74},
	{"EM_NSFCONFLICTHANDLER",75},	
	{"EM_MAILSENDNOTE",83},
	{"EM_CLEARPASSWORD",90},
	{"EM_NSFNOTEUPDATEXTENDED",102},
	{"EM_SCHFREETIMESEARCH",105},
	{"EM_SCHRETRIEVE",106},
	{"EM_SCHSRVRETRIEVE",107},
	{"EM_ADMINPPROCESSREQUEST",124},
	{"EM_NIFGETCOLLECTIONDATA",126},
	{"EM_NSFDBCOPYNOTE",127},
	{"EM_NSFNOTECOPY",128},
	{"EM_NSFNOTEATTACHFILE",129},
	{"EM_NSFNOTEDETACHFILE",130},
	{"EM_NSFNOTEEXTRACTFILE",131},
	{"EM_NSFNOTEATTACHOLE2OBJECT",132},
	{"EM_NSFNOTEDELETEOLE2OBJECT",133},
	{"EM_NSFNOTEEXTRACTOLE2OBJECT",134},
	{"EM_NSGETSERVERLIST",135},
	{"EM_NSFDBCOPY",136},
	{"EM_NSFDBCREATEANDCOPY",137},
	{"EM_NSFDBCOPYACL",138},
	{"EM_NSFDBCOPYTEMPLATEACL",139},
	{"EM_NSFDBCREATEACLFROMTEMPLATE",140},
	{"EM_NSFDBREADACL",141},
	{"EM_NSFDBSTOREACL",142},
	{"EM_NSFDBFILTER",143},
	{"EM_FTDELETEINDEX",144},
	{"EM_NSFNOTEGETINFO",145},
	{"EM_NSFNOTESETINFO",146},
	{"EM_NSFNOTECOMPUTEWITHFORM",147},
	{"EM_NIFFINDDESIGNNOTE",148},
	{"EM_NIFFINDPRIVATEDESIGNNOTE",149},
	{"EM_NIFGETLASTMODIFIEDTIME",150},
	{"EM_FTSEARCHEXT",160},
	{"EM_NAMELOOKUP",161},
	{"EM_NSFNOTEUPDATEMAILBOX",164},
	{"EM_NIFFINDDESIGNNOTEEXT",167},
	{"EM_AGENTOPEN",170},
	{"EM_AGENTRUN",171},
	{"EM_AGENTCLOSE",172},
	{"EM_AGENTISENABLED",173},
	{"EM_AGENTCREATERUNCONTEXT",175},
	{"EM_AGENTDESTROYRUNCONTEXT ",176},
	{"EM_AGENTSETDOCUMENTCONTEXT",177},
	{"EM_AGENTSETTIMEEXECUTIONLIMIT",178},
	{"EM_AGENTQUERYSTDOUTBUFFER",179},
	{"EM_AGENTREDIRECTSTDOUT",180},
	{"EM_SECAUTHENTICATION",184},
	{"EM_NAMELOOKUP2",185},
	{"EM_NSFMARKREAD",208},
	{"EM_NSFADDTOFOLDER",209},
	{"EM_NSFDBSPACEUSAGESCALED",210},
	{"EM_NSFDBGETMAJMINVERSION",222},
	{"EM_ROUTERJOURNALMESSAGE",223},
	{"EM_SMTPCONNECT",224},
	{"EM_SMTPCOMMAND",225},
	{"EM_SMTPMESSAGEACCEPT",226},
	{"EM_SMTPDISCONNECT",227},
	{"EM_NSFARCHIVECOPYNOTES",228},
	{"EM_NSFARCHIVEDELETENOTES",229},
	{"EM_NSFNOTEEXTRACTWITHCALLBACK",235},
	{"Unknown",0}};

CLotusSection::CLotusSection()
{
	m_datadir[0] = 0;
	m_err_msg[0] = 0;
	m_execdir[0] = 0;
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
	STATUS	sr;

	sr = NotesInitExtended(argc,argv);
	if (sr != NOERROR)
	{
		sprintf(m_err_msg,"CLotusSection -> NotesInitExtended ... Failed Result : %d",sr);
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_API;
	}
	ReadEnvironment();
	m_notes_init = true;

	return ERR_OK;
}

void CLotusSection::ReadEnvironment()
{
	int	len;
	OSGetDataDirectory(m_datadir);
	OSGetExecutableDirectory(m_execdir);	
	len = strlen(m_datadir);
	if ((len > 1) && (m_datadir[len-1] == '\\') ) m_datadir[len-1] = 0;
	len = strlen(m_execdir);
	if ((len > 1) && (m_execdir[len-1] == '\\') ) m_execdir[len-1] = 0;
}

DWORD CLotusSection::NotesThreadInit()
{
	STATUS	sr;
	sr = NotesInitThread();
	if (sr != NOERROR)
	{
		sprintf(m_err_msg,"CLotusSection -> NotesInitThread ... Failed Result : %d",sr);
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_API;
	}
	ReadEnvironment();
	m_notes_thread_init = true;
	return ERR_OK;
}

DWORD CLotusSection::Login(char *idfile_path, char *pass)
{
	DWORD	dr;
	if (idfile_path[0] == 0)	return SetError(false,ERR_PARAM,"Login -> Missing id file");
	if (pass[0] == 0)			return SetError(false,ERR_PARAM,"Login -> Missing password ");

	dr = ::GetFileAttributes(idfile_path);
	if ((dr & FILE_ATTRIBUTE_DIRECTORY) || (dr == -1)) 
	{
		return SetError(false,ERR_PARAM,"CLotusSection::Login ... ID File (%s) not found",idfile_path);
	}
	m_plog->_log(LOG_TRACE,"CLotusSection::Login ...");
	return SetError_Add_NApi_code_msg(SECKFMSwitchToIDFile(idfile_path,pass,NULL,0,0,NULL),"CLotusSection::Login -> SECKFMSwitchToIDFile (%s) ",idfile_path);
}
/*
DWORD CLotusSection::ErrorLog(DWORD code, char *msg)
{
	if (msg != NULL) strcpy(m_err_msg,msg);
	glog.log_strings(LOG_ERROR,m_err_msg);
	return code;
}
*/

DWORD CLotusSection::SetVar(char *name, char *value)
{
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
		return SetError(true,ERR_API,"CLotusSection::GetVar (%s) -> Not Found",name);
	}
	//limpiar los espacios vacios al comienzo de la cadena
	len = strlen(value);
	for (i = 0;i < len ;i++)
		if (value[i] != ' ') break;
	if (i != 0)
	{
		memmove(value,&value[i],len-i);
	}
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

DWORD CLotusSection::Error_Api(char *err_str, int max_len, STATUS sr, char *function)
{
	char	*cptr;
	int		len;
	cptr	= err_str;
	cptr[0] = 0;
	if (sr == NOERROR)	return ERR_OK;
	cptr+= _snprintf(err_str,max_len,"%s API failed with Code = %d, Message = ",function,sr);
	OSLoadString(NULLHANDLE,ERR(sr),cptr,err_str+max_len - cptr);
	len = strlen(cptr);
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,cptr,len,cptr,len);
	glog.log_strings(LOG_ERROR,err_str);
	return ERR_API;	

}

DWORD CLotusSection::Error_Handle(char *err_str, int max_len,char *function)
{
	_snprintf(err_str,max_len,"%s failed because not valid handle value ",function);
	glog.log_strings(LOG_ERROR,err_str);
	return ERR_HANDLE;
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
	if (sr != NOERROR) return SetError(true,ERR_API,"CLotusSection::NotesInit -> NotesInitExtended(%s)... failed with code %u",ini_file,sr);
	ReadEnvironment();
	m_notes_init = true;
	return ERR_OK;
}

DWORD CLotusSection::SetError_Add_NApi_code_msg(STATUS ecode,char *format,...)
{
	if (ecode == NOERROR)	{m_err_msg[0] = 0;return ERR_OK;}
	char	*cptr;
	int		len;
	va_list arg_ptr;

	va_start(arg_ptr, format);
	cptr = m_err_msg;
	cptr += _vsnprintf(m_err_msg,sizeof(m_err_msg),format,arg_ptr);
	va_end(arg_ptr);

	cptr += _snprintf(cptr,sizeof(m_err_msg)-(cptr-m_err_msg)," Notes Api failed 0x%X - ",ecode);
	OSLoadString(NULLHANDLE,ERR(ecode),cptr,sizeof(m_err_msg)-(cptr-m_err_msg));
	len = strlen(cptr);
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,cptr,len,cptr,len);
	return ERR_API;
}

DWORD CLotusSection::ChangePassword(char * idfile_path, char * old_password, char * new_password)
{
	DWORD	dr;
	dr = ::GetFileAttributes(idfile_path);
	if ((dr & FILE_ATTRIBUTE_DIRECTORY) || (dr == -1)) 
	{
		return SetError(false,ERR_PARAM,"CLotusSection::Login ... ID File (%s) not found",idfile_path);
	}
	return SetError_Add_NApi_code_msg(SECKFMChangePassword(idfile_path,old_password,new_password),"CLotusSection::ChangePassword -> IDFile (%s) ",idfile_path);
	return 0;
}

DWORD CLotusSection::Add_NApi_code_msg(STATUS ecode,char* err_buff,WORD buff_size,char* format,...)
{
	if (ecode == NOERROR)	{err_buff[0] = 0;return ERR_OK;}
	char	*cptr;
	int		len;
	va_list arg_ptr;

	va_start(arg_ptr, format);
	cptr = err_buff;
	cptr += _vsnprintf(err_buff,buff_size,format,arg_ptr);
	va_end(arg_ptr);

	cptr += _snprintf(cptr,buff_size-(cptr-err_buff)," Notes Api failed 0x%X - ",ecode);
	OSLoadString(NULLHANDLE,ERR(ecode),cptr,buff_size-(cptr-err_buff));
	len = strlen(cptr);
	OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,cptr,len,cptr,len);
	return ERR_API;
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
	if (sr != NOERROR) return SetError_Add_NApi_code_msg(sr,"CLotusSection::To_Abbreviate ... failed");
	if (strlen(tmp_str) >= max_size) return SetError(true,ERR_FATAL,"CLotusSection::To_Abbreviate ... failed result overflow");
	strcpy(text,tmp_str);
	return ERR_OK;
}

DWORD CLotusSection::To_Canonical(char *text, WORD max_size)
{
	char tmp_str[MAXUSERNAME];
	STATUS	sr;
	sr =  DNCanonicalize(0,NULL,text,tmp_str,sizeof(tmp_str),NULL);
	if (sr != NOERROR) return SetError_Add_NApi_code_msg(sr,"CLotusSection::To_Canonical ... failed");
	if (strlen(tmp_str) >= max_size) return SetError(true,ERR_FATAL,"CLotusSection::To_Canonical ... failed result overflow");
	strcpy(text,tmp_str);
	return ERR_OK;

}

DWORD CLotusSection::Password_Check(char *idfile_path, char *password)
{
	if (gutils.File_IsValid(idfile_path) != ERR_OK)
		return SetError(true,ERR_FATAL,"CLotusSection::Password_Check (%s) ... ID file is missing",idfile_path);
	if (SECKFMChangePassword(idfile_path,password,password) == NOERROR) return ERR_OK;
	return SetError(false,ERR_FATAL,"CLotusSection::Password_Check ... not valid");
}

char* CLotusSection::EM_GetName(WORD em_xxx)
{
	WORD	i;
	for (i=0;((EM_TABLE[i].type != 0) && (EM_TABLE[i].type != em_xxx));i++);
	return EM_TABLE[i].name;
}
