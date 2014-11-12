// B64Encode.h: interface for the CB64Encode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_B64ENCODE_H__13221F40_94D3_41A3_8102_06532122C49A__INCLUDED_)
#define AFX_B64ENCODE_H__13221F40_94D3_41A3_8102_06532122C49A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "itube.h"

class Cb64 : public CbObject , public ITube 
{
public:
	DWORD decode();
	void encode();
	Cb64(ITube	*pOutTube,bool encode);
	virtual ~Cb64();

	DWORD	Start();
	DWORD	End();
	DWORD	Push(BYTE b);

	void setEncode(BOOL bencode) { mbEncode = bencode; }

private:
	ITube	*mOutTube;		// salida de datos
	BYTE	mcache[4];
	BYTE	mindex;
	BOOL	mbEncode;
};

#endif // !defined(AFX_B64ENCODE_H__13221F40_94D3_41A3_8102_06532122C49A__INCLUDED_)
