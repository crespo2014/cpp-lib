// Tube.h: interface for the CTube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TUBE_H__8C58F1A9_6C66_43B9_80EE_AE108FC31983__INCLUDED_)
#define AFX_TUBE_H__8C58F1A9_6C66_43B9_80EE_AE108FC31983__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "itube.h"

class CTube : public CbObject  
{
public:
	static DWORD Push_cs(char* cs,ITube* pTube);
	DWORD ReadResource(char *res_type, char* res_name, HMODULE hModule,ITube* pITube);
	DWORD ReadFile(char* pcFileName,ITube* pITube);
	CTube(){};
	~CTube(){};
};

#endif // !defined(AFX_TUBE_H__8C58F1A9_6C66_43B9_80EE_AE108FC31983__INCLUDED_)
