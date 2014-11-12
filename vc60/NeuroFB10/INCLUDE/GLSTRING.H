// GlString.h: interface for the CGlString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLSTRING_H__2ED438A4_9F4B_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GLSTRING_H__2ED438A4_9F4B_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGlString  
{
public:
	void Paint();
	char* m_Buffer;
	CGlString();
	virtual ~CGlString();

};

#endif // !defined(AFX_GLSTRING_H__2ED438A4_9F4B_11D3_A036_0000E8DE4B3B__INCLUDED_)
