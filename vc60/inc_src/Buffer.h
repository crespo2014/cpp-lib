// Buffer.h: interface for the CBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFER_H__6FEB52A3_DEF9_416A_9600_61A4FBA030E8__INCLUDED_)
#define AFX_BUFFER_H__6FEB52A3_DEF9_416A_9600_61A4FBA030E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBuffer  
{
public:
	DWORD SetSize(DWORD dwSize);
	DWORD GetWriteBuffer(BYTE** ppbBuffer,DWORD* dwSize);
	DWORD GetWritePos(DWORD* pdwPos);
	DWORD AddBuffer(BYTE* pBuffer,DWORD dwSize,DWORD* pdwPos = NULL);
	CBuffer();
	virtual ~CBuffer();
private:
	BYTE*	m_pBuffer;
	DWORD	m_dwSize;
	DWORD	m_dwStart;
	DWORD	m_dwEnd;

};

#endif // !defined(AFX_BUFFER_H__6FEB52A3_DEF9_416A_9600_61A4FBA030E8__INCLUDED_)
