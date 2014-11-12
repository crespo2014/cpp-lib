// LNotesError.cpp: implementation of the CLNotesError class.
//
//////////////////////////////////////////////////////////////////////

#include "LNotesError.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct _name_type 
{
	char*	name;
	WORD	type;
};

CLNotesError::CLNotesError()
{
	
	
}

CLNotesError::~CLNotesError()
{
	
}

char* CLNotesError::getErrorString(STATUS ecode)
{
	if (ecode != NOERROR)
	{
		int		len;
		
		OSLoadString(NULLHANDLE,ERR(ecode),m_err_str,sizeof(m_err_str)-1);
		len = strlen(m_err_str);
		OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,m_err_str,len,m_err_str,len);
	}
	else
		*m_err_str = 0;
	return m_err_str;
	
}

char* CLNotesError::getEMName(WORD id)
{
	const static struct _name_type tbl[] = {
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
		
		const struct _name_type *key = tbl;
		while ((key->type !=0) && (key->type != id)) { key++; }
		return key->name;
		
}
