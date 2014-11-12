// bApp.h: interface for the CbApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BAPP_H__A473F8B3_AE5F_487D_8569_650CDA83F192__INCLUDED_)
#define AFX_BAPP_H__A473F8B3_AE5F_487D_8569_650CDA83F192__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cmdlineparser.h"
#include "bObject.h"
#include "iconfig.h"
#include "blockmem.h"


#define NO_STRING	"***UNKNOWN STRING***"

/*
	es posible indicar el nombre de la seccion para los parametros de configuración
	mientras que string se mantiene igual
*/
struct	_ini_key
{
	WORD	id;		//identificador numero de la configuracion
	char	*key;	// nombre del parametro
};

class CbApp : 
	public CbObject, 
	private IConfig
{
public:
	CbApp();
	virtual ~CbApp();

public:
	DWORD ParseCmdLine_c(char* cmdline);
	virtual DWORD OnCmdLineEnd()	{ return ERR_OK; };
	virtual DWORD OnCmdLineStart()  { return ERR_OK; };
	virtual DWORD OnCmdLineValue_c(char* cval,BOOL* pbRelease);

	DWORD LoadConfiguration(char *fname);
	DWORD LoadStringResource(char* type,char* name);
	char* getcConf(WORD id);
	char* getcStr(DWORD strId);
	virtual DWORD OnConfParam(char* pname,bool *pbRelease);
	virtual DWORD OnConfValue(char* pval,bool *pbRelease);
	DWORD OnStrValue(char* pval,bool *pbRelease);
	DWORD OnStrParam(char* pname,bool *pbRelease);
	virtual	DWORD	OnSection(char* psection,bool *pbRelease) { return ERR_OK; };
	virtual	DWORD	OnParam(char* pname,bool *pbRelease);
	virtual	DWORD	OnValue(char* pval,bool *pbRelease);
	IMem*	getMem() { return &mdata; };

private:
	WORD	mReadMode;				// Indica si se esta procesando un fichero INI o un Strtable

protected :
	const struct _ini_key	*m_cnf_key;		// tabla de parametros de confiuracion de la aplicacion
	const struct _ini_key	*m_str_key;		// tabla de cadenas de la aplicacion
	const struct _ini_key	*mCurrentKey;	// key recivida por onParam
	
	char**	m_cnf_data;		// array de cadenas con todos los parametros de configuracion
	char**	m_str_data;		// array de string con todas las cadenas de la aplicación
	WORD	m_str_count;	// cantidad maxima de cadenas
	WORD	m_cnf_count;

	//bloque de memoria de la aplicacion. con datos duraderos
	CBlockMem	mdata;
};


class CbAppCmdLineEvent:
public 	ICmdLineEvent
{
public:
	CbAppCmdLineEvent(CbApp	*pApp) { mpApp = pApp; };
	~CbAppCmdLineEvent() {};
	virtual DWORD	OnStart()	{ return mpApp->OnCmdLineStart();	};
	virtual DWORD	OnEnd()		{ return mpApp->OnCmdLineEnd();		};
	virtual DWORD	OnValue_c(char*	val,BOOL* pbRelease) {  return mpApp->OnCmdLineValue_c(val,pbRelease); };
private:
	CbApp	*mpApp;
};

#endif // !defined(AFX_BAPP_H__A473F8B3_AE5F_487D_8569_650CDA83F192__INCLUDED_)
