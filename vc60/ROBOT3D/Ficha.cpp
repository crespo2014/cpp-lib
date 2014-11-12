// Ficha.cpp: implementation of the CFicha class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Ficha.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PROF  " 25 "   //altura para soltar la ficha
#define ATACK " 10 "   // altura de cogida

/*
	Posicion de las cajas
*/
#define CAJA3X  -34
#define CAJA3Z	18
#define CAJA2X	-34
#define CAJA2Z	4
#define CAJA1X	-34
#define CAJA1Z	-12
#define CIERRAPINZA 150

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFicha::CFicha()
{

}

CFicha::~CFicha()
{

}

void CFicha::Paint()
{
	CCilindroXZ cilindro;
	cilindro.Set(1.0,2.0);
	cilindro.Paint();
}

LPCSTR CFicha::GetMov()
{
	char	c1x[3],c1z[3],c2x[3],c2z[3],c3x[3],c3z[3];	
	char	cierrapinza[5],abrepinza[5];
	_itoa(CAJA1X,c1x,10);
	_itoa(CAJA1Z,c1z,10);
	_itoa(CAJA2X,c2x,10);
	_itoa(CAJA2Z,c2z,10);
	_itoa(CAJA3X,c3x,10);
	_itoa(CAJA3Z,c3z,10);
	_itoa(CIERRAPINZA,cierrapinza,10);
	_itoa(-CIERRAPINZA,abrepinza,10);

	m_Move.Empty();
	int c;
	char b[10];
	char d[10];
	c=(int)m_Position[0];
	_itoa(c,b,10);
	c=(int)m_Position[2];
	_itoa(c,d,10);
	
	m_Move=m_Move+"G "+b+PROF+d+" W ";
	m_Move=m_Move+"G "+b+ATACK+d+" W M3 "+cierrapinza+" W G "+b+PROF+d+" W ";
	switch (m_Value)
	{
	case 3:
		{
			m_Move=m_Move+"G "+c3x+PROF+c3z+" W M3 "+abrepinza+" W";
			break;
		}
	case 2:
		{
			m_Move=m_Move+"G "+c2x+PROF+c2z+" W M3 "+abrepinza+" W";
			break;
		}
	default:
		{
			m_Move=m_Move+"G "+c1x+PROF+c1z+" W M3 "+abrepinza+" W";
			break;
		}
	}
	return m_Move;
}

void CFicha::SetValue(DWORD pValue)
{
	m_Value=pValue;

}
