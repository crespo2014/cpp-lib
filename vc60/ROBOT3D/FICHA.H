// Ficha.h: interface for the CFicha class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHA_H__8E1FFAE2_6A1E_11D3_A767_0000E856599A__INCLUDED_)
#define AFX_FICHA_H__8E1FFAE2_6A1E_11D3_A767_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Trayectoria.h"
#include "Pos.h"
#include "Formas.h"

class AFX_EXT_CLASS CFicha : 
	public CPos
{
public:
	void SetValue(DWORD pValue);
	virtual LPCSTR GetMov();
	virtual void Paint();
	CFicha();
	virtual ~CFicha();

private:
	CString m_Move;
	DWORD m_Value;
};

#endif // !defined(AFX_FICHA_H__8E1FFAE2_6A1E_11D3_A767_0000E856599A__INCLUDED_)
