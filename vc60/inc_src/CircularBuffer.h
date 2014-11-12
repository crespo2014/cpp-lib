// CircularBuffer.h: interface for the CCircularBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCULARBUFFER_H__545679AF_EC84_4C59_8735_218F5FBD904E__INCLUDED_)
#define AFX_CIRCULARBUFFER_H__545679AF_EC84_4C59_8735_218F5FBD904E__INCLUDED_

#include "errorcodes.h" 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCircularBuffer  
{
public:
	DWORD GetWriteBuffer(BYTE **ppbBuffer, DWORD *dwSize);
	DWORD SetBuffer(BYTE* pBuffer,DWORD Size);
	DWORD GetReadBuffer(BYTE **ppbBuffer, DWORD *dwSize);
	DWORD GetUsed();
	DWORD GetAvailable();
	DWORD ReleaseBuffer();
	DWORD UpdateReadPtr(DWORD dwCant);
	DWORD UpdateWritePtr(DWORD dwCant);
	DWORD GetBuffer(BYTE *pBuffer, DWORD dwSize,DWORD *dwRead);
	DWORD SetSize(DWORD dwSize);
	DWORD GetWriteBuffer(BYTE** ppbBuffer,DWORD* dwSize,DWORD dwPos);
	DWORD GetWritePos(DWORD* pdwPos);
	DWORD AddBuffer(BYTE* pBuffer,DWORD dwSize,DWORD* pdwPos = NULL);
	BOOL  OnBuffer() {return m_pBuffer != NULL;};
	CCircularBuffer();
	virtual ~CCircularBuffer();
private:
	BYTE*	m_pBuffer;
	DWORD	m_dwSize;
	DWORD	m_dwStart;
	DWORD	m_dwEnd;
	BOOL	m_OnExtBuffer;	// Se esta usando un buffer externo

};

#endif // !defined(AFX_CIRCULARBUFFER_H__545679AF_EC84_4C59_8735_218F5FBD904E__INCLUDED_)
