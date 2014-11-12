// GLBmp.h: interface for the CGLBmp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLBMP_H__7C338949_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GLBMP_H__7C338949_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGLBmp  : public CFile
{
public:
	DWORD m_BytePerPixel;
	void BGRtoRGB();
	DWORD m_Height;
	DWORD m_Width;
	BOOL m_OnOpen;
	DWORD m_BytesWidth;
	BYTE* m_Data;
	BITMAPFILEHEADER m_BFH;
	BITMAPINFOHEADER m_BIH;
	int OpenFile();
	void SetFile(LPCTSTR pFileName);
	CString m_FileName;
	CGLBmp();
	virtual ~CGLBmp();

};

#endif // !defined(AFX_GLBMP_H__7C338949_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_)
