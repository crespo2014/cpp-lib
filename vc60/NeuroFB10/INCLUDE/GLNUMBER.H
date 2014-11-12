// GlNumber.h: interface for the CGlNumber class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLNUMBER_H__186A1764_9F37_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GLNUMBER_H__186A1764_9F37_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGlNumber  
{
public:
	void Paint();
	void IntToStr();
	int m_Number;
	char m_Buffer[20];
	CGlNumber();
	virtual ~CGlNumber();

};

#endif // !defined(AFX_GLNUMBER_H__186A1764_9F37_11D3_A036_0000E8DE4B3B__INCLUDED_)
