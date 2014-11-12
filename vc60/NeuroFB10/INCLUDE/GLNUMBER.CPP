// GlNumber.cpp: implementation of the CGlNumber class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlNumber.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlNumber::CGlNumber()
{

}

CGlNumber::~CGlNumber()
{

}

int m_Bmp0[10]=
{ 120,204,204,204,204,204,204,204,204,120 };
int m_Bmp1[10]=
{ 48,48,48,48,48,48,48,48,240,48 };
int m_Bmp2[10]=
{ 252,192,192,96,48,24,12,204,204,120 };
int m_Bmp3[10]=
{ 120,204,12,12,12,56,12,12,204,120 };
int m_Bmp4[10]=
{ 12,12,252,204,108,108,60,60,28,12 };
int m_Bmp5[10]=
{ 120,204,12,12,204,248,192,192,192,252 };
int m_Bmp6[10]=
{ 120,204,204,204,204,248,192,192,204,120 };
int m_Bmp7[10]=
{ 96,96,96,48,48,48,24,24,12,252};
int m_Bmp8[10]=
{ 120,204,204,204,204,120,204,204,204,120 };
int m_Bmp9[10]=
{ 120,204,12,12,124,204,204,204,204,120 };




int* m_Numbers[10]=
{
	m_Bmp0,m_Bmp1,m_Bmp2,m_Bmp3,m_Bmp4,m_Bmp5,m_Bmp6,m_Bmp7,m_Bmp8,m_Bmp9
};

void CGlNumber::IntToStr()
{
	_itoa(m_Number,(char*)m_Buffer,10);   
}

void CGlNumber::Paint()
{
	IntToStr();
	if (m_Buffer[0]==0)
	{
		 glBitmap(8,10,0,0,0,0,(const BYTE*)m_Numbers[0]);
	}
	for (int i=0;;i++)
	{
		if (m_Buffer[i]==0)
			break;
		glBitmap(8,10,0,0,8,0,(const BYTE*)m_Numbers[m_Buffer[i]-'0']);
	}
}

