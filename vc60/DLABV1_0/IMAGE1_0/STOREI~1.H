// StoreImage.h: interface for the CStoreImage class.
//
//////////////////////////////////////////////////////////////////////
#include <VisImSrc.h>
#include <VisCore.h>
#include <VisDisplay.h>

#if !defined(AFX_STOREIMAGE_H__3CD67AE1_2402_11D3_9A2B_000021B01127__INCLUDED_)
#define AFX_STOREIMAGE_H__3CD67AE1_2402_11D3_9A2B_000021B01127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CStoreImage  
{
public:
	int y_size;
	int x_size;
	char* in;

	CVisByteImage* DevImage(int x,int y);
	int GetInt(FILE *fd);
	void GetImage(CString filename);
	CVisByteImage* LoadImage(CString filename);
	void SaveImage(CString filename, CVisByteImage *m_gray);
	void PutImage(CString filename);
	void SaveSubImage(CString filename, CPoint Store[255], int contfind, CVisByteImage *m_gray);
	CStoreImage();
	virtual ~CStoreImage();

};

#endif // !defined(AFX_STOREIMAGE_H__3CD67AE1_2402_11D3_9A2B_000021B01127__INCLUDED_)
