// GlString.cpp: implementation of the CGlString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlString::CGlString()
{
	
}

CGlString::~CGlString()
{
	
}

int m_BmpR[10]=
{ 195,198,198,198,252,198,198,198,252,0 };
int m_Bmpa[10]=
{ 124,204,204,108,60,204,56,0,0,0 };
int m_Bmpw[10]=
{ 102,102,255,219,219,219,195,0,0,0 };
int m_BmpE[10]=
{ 254,192,192,192,192,252,192,192,192,254 };
int m_BmpG[10]=
{ 61,99,195,195,207,192,192,193,99,62 };
int m_Bmpe[10]=
{ 120,204,192,192,252,204,120,0,0,0};
int m_BmpT[10]=
{ 24,24,24,24,24,24,24,24,24,255};
int m_Bmpm[10]=
{ 219,219,219,219,219,219,126,0,0,0 };
int m_Bmpp[10]=
{ 192,192,192,248,204,204,204,204,204,248 };
int m_Bmph[10]=
{ 204,204,204,204,204,204,248,192,192,192};
int m_Bmpt[10]=
{ 96,96,96,96,96,96,240,96,96,0};
int m_BmpA[10]=
{ 195,195,126,102,102,36,60,60,24,24};
int m_Bmpl[10]=
{ 192,192,192,192,192,192,192,192,192,192};
int m_BmpB[10]=
{ 254,195,195,195,195,254,195,195,195,254};
int m_BmpM[10]=
{ 153,153,189,165,231,195,195,129,0,0};
int m_Bmp[10]=
{ 0,0,0,0,0,0,0,0,0,0};


void CGlString::Paint()
{
	for (int i=0;;i++)
	{
		if (m_Buffer[i]==0)
			break;
		switch (m_Buffer[i])
		{
		case ' ':
			{
				glBitmap(8,10,0,0,8,0,(const BYTE*)m_Bmp);
				break;
			}
		case 'R':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpR);
				break;
			}
		case 'a':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpa);
				break;
			}
		case 'w':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpw);
				break;
			}
		case 'E':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpE);
				break;
			}
		case 'G':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpG);
				break;
			}
		case 'e':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpe);
				break;
			}
		case 'T':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpT);
				break;
			}
		case 'm':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpm);
				break;
			}
		case 'p':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpp);
				break;
			}
		case 'h':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmph);
				break;
			}
		case 't':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpt);
				break;
			}
		case 'A':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpA);
				break;
			}
		case 'l':
			{
				glBitmap(8,10,0,0,9,0,(const BYTE*)m_Bmpl);
				break;
			}
		case 'B':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpB);
				break;
			}
		case 'M':
			{
				glBitmap(8,10,0,0,10,0,(const BYTE*)m_BmpM);
				break;
			}
		}
	}

}
