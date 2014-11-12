// TCanal.cpp: implementation of the TCanal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCanal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TCanal::TCanal()
{
	CantSup=0;
	CantTrans=0;
	CantRecep=0;
	altura=0;
	ancho=0;
	largo=0;
}

TCanal::~TCanal()
{

}

void TCanal::SetAltura(float paltura)
{
	altura =paltura;
}

void TCanal::SetAncho(float pancho)
{
	ancho =pancho;
}

void TCanal::SetLargo(float plargo)
{
	largo =plargo;
}