// CamBuff.h: interface for the CCamBuff class.
//
//////////////////////////////////////////////////////////////////////


#include <VisImSrc.h>
#include <VisCore.h>
#include <VisDisplay.h>

#if !defined(AFX_CAMBUFF_H__114A1E01_389C_11D3_9261_E22F7FAD314A__INCLUDED_)
#define AFX_CAMBUFF_H__114A1E01_389C_11D3_9261_E22F7FAD314A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CCamBuff  
{
public:
	CVisPane* m_pane;
	CWnd* m_handle;
	CVisShape *shape;
	CVisByteImage *image;
	bool nuevo;

	void GetHandle(CWnd* handle);
	void Display(CPoint org);
	void GetBuffer(char* buf);
	CCamBuff();
	virtual ~CCamBuff();
	

};

#endif // !defined(AFX_CAMBUFF_H__114A1E01_389C_11D3_9261_E22F7FAD314A__INCLUDED_)
