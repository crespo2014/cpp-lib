// CodePage.h: interface for the CCodePage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODEPAGE_H__28EF9F6D_44C3_4E34_832A_D3EED5345D95__INCLUDED_)
#define AFX_CODEPAGE_H__28EF9F6D_44C3_4E34_832A_D3EED5345D95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITube.h"
#include "bObject.h"

/*
	Para la codificación hay que saber el codigo origen, llevarlo a un codigo intermedio ASCII
	y despues codificar al codigo que se necesita.
*/

#define CP_NONE		0
#define CP_1250		1
#define CP_1251		2
#define CP_1252		3
#define CP_1253		4


class CCodePage : 
	public CbObject, 
	public ITube  
{
public:
	WORD getCode(BYTE src);
	BYTE* getTable(WORD codePage);
	CCodePage();
	virtual ~CCodePage();
private:
	WORD	mSrcCode;
	WORD	mOutCode;
	WORD*	mSrcTbl;
	WORD*	mDestTbl;
};

#endif // !defined(AFX_CODEPAGE_H__28EF9F6D_44C3_4E34_832A_D3EED5345D95__INCLUDED_)
