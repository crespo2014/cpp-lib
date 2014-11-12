// Crypter.h: interface for the CCrypter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTER_H__D6ABD961_63DB_4389_AAFA_BDFE83EF8453__INCLUDED_)
#define AFX_CRYPTER_H__D6ABD961_63DB_4389_AAFA_BDFE83EF8453__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "itube.h"

/*
Objeto de cifrado RC4
*/

class CCrypter : public CbObject , public ITube 
{
public:
	DWORD End();
	DWORD Start();
	DWORD Push(BYTE b);
	void KeyDec(BYTE cant = 1);
	void SetKey(char* key);
	CCrypter(ITube	*pOutTube);
	void SetOut(ITube *pOutTube) { mOutTube = pOutTube; }
	CCrypter() {};
	virtual ~CCrypter();

	ITube* getTube(ITube *pOutTube) 
	{
		mOutTube = pOutTube;
		return this;
	}

private:
	struct 
	{
		BYTE s[256];
		BYTE k[256];
		BYTE i,j;
	} m_rc4;

	ITube	*mOutTube;		// salida de datos
	
};

#endif // !defined(AFX_CRYPTER_H__D6ABD961_63DB_4389_AAFA_BDFE83EF8453__INCLUDED_)
