// bApp.cpp: implementation of the CbApp class.
//
//////////////////////////////////////////////////////////////////////

#include "bApp.h"
#include "tube.h"
#include "configparser.h"

#define _FILENAME_ "bapp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Modo de lectura del conf
#define CNF_MODE		0
#define STR_MODE		1

CbApp::CbApp()
{
	m_cnf_data = NULL;
	m_str_data = NULL;
}

CbApp::~CbApp()
{
	
}

DWORD	CbApp::OnParam(char* pname,bool *pbRelease)
{
	if (mReadMode == CNF_MODE) return OnConfParam(pname,pbRelease);
	if (mReadMode == STR_MODE) return OnStrParam(pname,pbRelease);
	return _LOG_ERROR ERR_FATAL,"Invalid conf read mode");
}

DWORD	CbApp::OnValue(char* pval,bool *pbRelease)
{
	if (mReadMode == CNF_MODE) return OnConfValue(pval,pbRelease);
	if (mReadMode == STR_MODE) return OnStrValue(pval,pbRelease);
	return _LOG_ERROR ERR_FATAL,"Invalid conf read mode");
}

char* CbApp::getcStr(DWORD strId)
{
	char	*str;
	if (strId < m_str_count) 
	{
		str = m_str_data[strId];
		if (str != NULL) return str;
		_LOG_ERROR ERR_FATAL,"string id %d not found",strId);
	}
	else
		_LOG_ERROR ERR_FATAL,"Invalid string id %d",strId);
	
	return NO_STRING;
}

DWORD CbApp::OnStrParam(char *pname, bool *pbRelease)
{
	// Buscar el parametro en la lista
	const struct _ini_key	*pkey;
	pkey = m_str_key;
	
	while(pkey->key)
	{
		if (strcmpi(pname,pkey->key) == 0) 
		{
			mCurrentKey = pkey;
			break;
		}
		pkey++;
	}
	if (pkey->key == NULL)
	{
		mCurrentKey = NULL;
		_LOG_WARNING "Unknown string %s in languaje file",pname);
	}
	return ERR_OK;	
}

DWORD CbApp::OnStrValue(char *pval, bool *pbRelease)
{
	if (mCurrentKey != NULL)
	{
		m_str_data[mCurrentKey->id] = pval;
		*pbRelease = false;
	}
	mCurrentKey = NULL;
	return ERR_OK;
}

DWORD CbApp::OnConfValue(char *pval, bool *pbRelease)
{
	if (mCurrentKey != NULL)
	{
		m_cnf_data[mCurrentKey->id] = pval;
		*pbRelease = false;
	}
	mCurrentKey = NULL;
	return ERR_OK;
	
}

DWORD CbApp::OnConfParam(char *pname, bool *pbRelease)
{
	// Buscar el parametro en la lista
	const struct _ini_key	*pkey;
	pkey = m_cnf_key;
	
	while(pkey->key)
	{
		if (strcmpi(pname,pkey->key) == 0) 
		{
			mCurrentKey = pkey;
			break;
		}
		pkey++;
	}
	if (pkey->key == NULL)
	{
		mCurrentKey = NULL;
		_LOG_WARNING "Unknown parameter %s in config file",pname);
	}
	return ERR_OK;
}

char* CbApp::getcConf(WORD id)
{
	char	*str;
	if (id < m_cnf_count) 
	{
		str = m_cnf_data[id];
		if (str == NULL)
		{
			_LOG_ERROR ERR_FATAL,"configuration param %d not loaded",id);
			str = "";
		}
	}
	else
	{
		str = "";
		_LOG_ERROR ERR_FATAL,"Invalid configuration id %d",id);
	}
	
	return str;
}

DWORD CbApp::LoadConfiguration(char *fname)
{
	mReadMode = CNF_MODE;
	CTube	tube;
	CConfigParser	cnfParse(this,&mdata);
	return tube.ReadFile(fname,&cnfParse);
}

DWORD CbApp::LoadStringResource(char *type, char *name)
{
	mReadMode = STR_MODE;
	CTube	tube;
	CConfigParser	confParser(this,&mdata);
	return tube.ReadResource(type,name,GetModuleHandle(NULL),&confParser);
}

DWORD CbApp::OnCmdLineValue_c(char *cval, BOOL *pbRelease)
{
	_LOG_DATA "onCmdLine %s",cval);
	return ERR_OK;
}


DWORD CbApp::ParseCmdLine_c(char *cmdline)
{
	CbAppCmdLineEvent	evt(this);	
	CcmdLineParser		parser(&evt,&mdata);
	return CTube::Push_cs(cmdline,&parser);
}
