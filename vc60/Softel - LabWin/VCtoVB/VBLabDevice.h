// VBLabDevice.h: interface for the CVBLabDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VBLABDEVICE_H__F76E49B9_BA5C_4953_973D_F1DF90B97899__INCLUDED_)
#define AFX_VBLABDEVICE_H__F76E49B9_BA5C_4953_973D_F1DF90B97899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\interfaces\Ilabdevice.h"

struct LABDEVICE
{
	HMODULE		hdll;
	ILabDevice*	lpInstance;
};

#define MAX_LABDEVICE	10	// Cantidad maxima de dispositivos

#endif // !defined(AFX_VBLABDEVICE_H__F76E49B9_BA5C_4953_973D_F1DF90B97899__INCLUDED_)
