// TrafficFile.h: interface for the CTrafficFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAFFICFILE_H__E7081907_12F0_4CF8_BEB2_7B50E257713D__INCLUDED_)
#define AFX_TRAFFICFILE_H__E7081907_12F0_4CF8_BEB2_7B50E257713D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TF_NONE	0
#define TF_SEND	1
#define TF_RECV	2

class CTrafficFile  
{
public:
	DWORD Write(BYTE bOp, BYTE *pBuffer, DWORD dwSize);
	DWORD ProcessBuffer(BYTE bOp,BYTE* pBuffer,DWORD dwSize);
	DWORD AddSendBuffer(BYTE* pBuffer,DWORD dwSize);
	DWORD AddRecvBuffer(BYTE* pBuffer,DWORD dwSize);
	DWORD Close();
	DWORD Create(char* pFileName);
	CTrafficFile();
	virtual ~CTrafficFile();
private:
	HANDLE	m_File;
	BYTE	m_LastOp;	// Ultima operacion realizada snd rcv
	BYTE	m_Buffer[16];
	int		m_BufferCount;

};

#endif // !defined(AFX_TRAFFICFILE_H__E7081907_12F0_4CF8_BEB2_7B50E257713D__INCLUDED_)
