// ConfigParser.h: interface for the CConfigParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGPARSER_H__D96E6E01_FC25_412D_9842_0A8980056728__INCLUDED_)
#define AFX_CONFIGPARSER_H__D96E6E01_FC25_412D_9842_0A8980056728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "itube.h"
#include "imem.h"
#include "iconfig.h"



class CConfigParser : public CbObject , public ITube
{
public:
	DWORD endData(WORD type);
	CConfigParser(IConfig *pConf, IMem* pMem);
	virtual ~CConfigParser();
private:
	WORD	mStatus;	// indica que estamos leyendo
	IMem	*mpMem;
	char	mlastChar;		// ultimo caracter recivido
	IConfig	*mpConfig;

	virtual DWORD	Start();
	virtual DWORD	End();
	virtual DWORD	Push(BYTE b);
};

#endif // !defined(AFX_CONFIGPARSER_H__D96E6E01_FC25_412D_9842_0A8980056728__INCLUDED_)
