// ClienteCatWin.h: interface for the CClienteCatWin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTECATWIN_H__1111709B_F147_4942_B490_8EEE054977EB__INCLUDED_)
#define AFX_CLIENTECATWIN_H__1111709B_F147_4942_B490_8EEE054977EB__INCLUDED_

#include "dbcommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	Ventana de catalogo del cliente
*/

class CClienteCatWin : private IdbView   
{
public:
	CClienteCatWin();
	virtual ~CClienteCatWin();

};

#endif // !defined(AFX_CLIENTECATWIN_H__1111709B_F147_4942_B490_8EEE054977EB__INCLUDED_)
