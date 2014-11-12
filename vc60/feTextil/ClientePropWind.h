// ClientePropWind.h: interface for the CClientePropWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTEPROPWIND_H__BDF011D3_F8F7_4BA5_88BB_090BE2AA46D2__INCLUDED_)
#define AFX_CLIENTEPROPWIND_H__BDF011D3_F8F7_4BA5_88BB_090BE2AA46D2__INCLUDED_

#include "WindComboBox.h"	// Added by ClassView
#include "dbCommon.h"
#include "Wind.h"
#include "textildb.h"
#include "cliente.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClientePropWind : private IdbView   
{
public:
	CClientePropWind();
	virtual ~CClientePropWind();

};

#endif // !defined(AFX_CLIENTEPROPWIND_H__BDF011D3_F8F7_4BA5_88BB_090BE2AA46D2__INCLUDED_)
