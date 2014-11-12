// cmdLineParser.h: interface for the CcmdLineParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDLINEPARSER_H__6BCE36DE_248E_48E0_A5F4_6883629CA33C__INCLUDED_)
#define AFX_CMDLINEPARSER_H__6BCE36DE_248E_48E0_A5F4_6883629CA33C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITube.h"
#include "bObject.h"
#include "imem.h"

//TODO. implementar tuberia para escapar carateres < 32 y > 128 y para resolver esos escapes como
// si se estuviera utiliznado un string en lenguaje c

class ICmdLineEvent  
{
public:
	virtual DWORD	OnStart() = 0;
	virtual DWORD	OnValue_c(char*	val,BOOL* pbRelease) = 0;
	//virtual DWORD	OnValue_b(BYTE*	val,WORD size,BOOL* pbRelease) = 0;	
	// En un futuro se pueden introducir datos o caracteres no legibles utilizando secuencias de escape \n \r
	virtual DWORD	OnEnd() = 0;
};


class CcmdLineParser : 
	public CbObject, 
	public ITube  
{
public:
	CcmdLineParser(ICmdLineEvent* plistener,IMem* pMem);
	virtual ~CcmdLineParser();
private:
	DWORD endValue();
	ICmdLineEvent	*mListener;
	WORD	mStatus;
	IMem	*mpMem;

	virtual DWORD	Start();
	virtual DWORD	End();
	virtual DWORD	Push(BYTE b);

};

#endif // !defined(AFX_CMDLINEPARSER_H__6BCE36DE_248E_48E0_A5F4_6883629CA33C__INCLUDED_)
