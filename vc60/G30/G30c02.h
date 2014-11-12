// G30c02.h: interface for the CBitmapWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G30C02_H__4FA91FB4_078F_11D5_94DA_00D0093D4380__INCLUDED_)
#define AFX_G30C02_H__4FA91FB4_078F_11D5_94DA_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lfc30\wind.h"

/*
	Esta es la ventana que contiene a la ventana de juego.
*/
class CBitmapWind : public CWind  
{
public:
	DWORD Initialize();
	DWORD StartGame();
	CBitmapWind();
	virtual ~CBitmapWind();

};

#endif // !defined(AFX_G30C02_H__4FA91FB4_078F_11D5_94DA_00D0093D4380__INCLUDED_)
