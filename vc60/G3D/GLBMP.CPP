// GLBmp.cpp: implementation of the CGLBmp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLBmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLBmp::CGLBmp()
{
	m_OnOpen=false;
	m_Data=NULL;
}

CGLBmp::~CGLBmp()
{
	delete m_Data;

}

void CGLBmp::SetFile(LPCTSTR pFileName)
{
	m_FileName=pFileName;
}

int CGLBmp::OpenFile()
{
	Open(m_FileName,CFile::modeRead);
	Read(&m_BFH,sizeof(BITMAPFILEHEADER));
	
	WORD ID=('M'<<8)|'B';
	if (m_BFH.bfType != ID)
	{
		Close();
		return false;
	}
	
	Read(&m_BIH,sizeof(BITMAPINFOHEADER));
	if( m_BIH.biPlanes != 1||
		m_BIH.biBitCount != 24)
		return false;
	
	m_Data= new BYTE[m_BIH.biSizeImage];
	if (m_Data==NULL)
	{
		Close();
		return false;
	}
	Read(m_Data,m_BIH.biSizeImage);
	Close();

	// Ajuste a 4 bytes por linea de imagen
	int rest=(m_BIH.biWidth*m_BIH.biBitCount/8)%4;

	if(rest != 0)
		m_BytesWidth=(m_BIH.biWidth*m_BIH.biBitCount/8 + 4-rest);
	else
		m_BytesWidth=(m_BIH.biWidth*m_BIH.biBitCount/8);

	m_Width=m_BIH.biWidth;
	m_Height=m_BIH.biHeight;
	m_BytePerPixel = m_BIH.biBitCount/8;

	return true;
}

void CGLBmp::BGRtoRGB()
{
	unsigned char pixel;
	for(unsigned int j=0;j<m_Height;j++)
		for(unsigned int i=0;i<m_Width;i++)
		{
			pixel = m_Data[m_BytesWidth*j+i*m_BytePerPixel+2];
			m_Data[m_BytesWidth*j+i*m_BytePerPixel+2] = m_Data[m_BytesWidth*j+i*m_BytePerPixel];
			m_Data[m_BytesWidth*j+i*m_BytePerPixel] = pixel;
		}
}

