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
	m_Move.Empty();
	int c;
	char b[10];
	char d[10];
	c=(int)m_Position[0];
	_itoa(c,b,10);
	c=(int)m_Position[2];
	_itoa(c,d,10);
	
	m_Move=m_Move+"G "+b+" 20 "+d+" W ";
	m_Move=m_Move+"G "+b+" 12 "+d+" W M3 140 W G "+b+" 20 "+d+" W ";
	/*
	strcpy(m_Move,"G ");strcpy(m_Move,b);strcpy(m_Move," 20 ");strcpy(m_Move,d);strcpy(m_Move," W ");
	strcpy(m_Move,"G ");strcpy(m_Move,b);strcpy(m_Move," 12 ");
	strcpy(m_Move,d);strcpy(m_Move," W M3 140 W G ");strcpy(m_Move,b);strcpy(m_Move," 20 ");
	strcpy(m_Move,d);strcpy(m_Move," W ");
	*/
	switch (m_Value)
	{
	case 0:
		{
			m_Move=m_Move+"G 0 18 10 W M3 -140 W";
//			strcpy(m_Move,"G 0 18 10 W M3 -140 W");
			break;
		}
	case 1:
		{
			m_Move=m_Move+"G -10 18 10 W M3 -140 W";
//			strcpy(m_Move,"G -10 18 10 W M3 -140 W");
			break;
		}
	case 2:
		{
			m_Move=m_Move+"G -20 18 10 W M3 -140 W";
//			strcpy(m_Move,"G -20 18 10 W M3 -140 W");
			break;
		}
	default:
		{
			m_Move=m_Move+"G -25 18 10 W M3 -140 W";
//			strcpy(m_Move,"G -25 18 10 W M3 -140 W");
			break;
		}
	}
	return m_Move;
}

void CFicha::SetValue(DWORD pValue)
{
	m_Value=pValue;

}
