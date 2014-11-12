// Correspondencia.h: interface for the CCorrespondencia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRESPONDENCIA_H__87C8BBEA_4DB5_4201_AD96_69EE77705949__INCLUDED_)
#define AFX_CORRESPONDENCIA_H__87C8BBEA_4DB5_4201_AD96_69EE77705949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "carta.h"
#include "StartViewWind.h"

// Tablas de la correspondencia

class CCorrespondencia  
{
public:
	DWORD GetApiError();
	DWORD CloseDB();
	DWORD Show(HWND hWndParent);
	DWORD OpenDB();
	DWORD InitDB();
	CCorrespondencia();
	virtual ~CCorrespondencia();
private:
	ICommand*	m_lpICommand;
	//CCarta	m_cartas;
	DWORD	m_ApiError;
//	CStartViewWind m_StartView;
//	CdbCartasStartView m_StartView;
};

#endif // !defined(AFX_CORRESPONDENCIA_H__87C8BBEA_4DB5_4201_AD96_69EE77705949__INCLUDED_)
