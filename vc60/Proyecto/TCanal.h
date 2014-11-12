// TCanal.h: interface for the TCanal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCANAL_H__2FA5D557_4700_40BC_913A_30AB35FBC0BC__INCLUDED_)
#define AFX_TCANAL_H__2FA5D557_4700_40BC_913A_30AB35FBC0BC__INCLUDED_

#include "treceptor.h"
#include "tsuperficie.h"
#include "ttransmisor.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TCanal  
{
public:
	void SetAltura(float paltura);
	void SetAncho(float pancho);
	void SetLargo(float plargo);
	TReceptor Receptores[50];
	TTransmisor Transmisores[50];
	TSuperficie Superficies[50];
	int	CantSup,CantTrans,CantRecep;
	float	largo,ancho,altura;
	TCanal();
	~TCanal();

};

#endif // !defined(AFX_TCANAL_H__2FA5D557_4700_40BC_913A_30AB35FBC0BC__INCLUDED_)
