// gl10c11.h: interface for the CMemDC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C11_H__73553F22_F8D7_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C11_H__73553F22_F8D7_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	CBitmap*	bitmap;
	CBitmap*	oldbitmap;
	CSize		currentsize;
	CSize		realsize;
	BOOL		OnCreate;
} S_MEMDC;

class CMemDC : public CDC  
{
public:
	DWORD Erase(COLORREF color);
	int SetHeight(long Height);
	int Swap(long x,long y,CDC* dc);
	int Swap(CDC* dc);
	int SetSize(int cx, int cy);
	int Create(CDC* dc);
	int InitMemDC();
	S_MEMDC* m_MemDC;
	CMemDC();
	virtual ~CMemDC();

};

#endif // !defined(AFX_GL10C11_H__73553F22_F8D7_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
