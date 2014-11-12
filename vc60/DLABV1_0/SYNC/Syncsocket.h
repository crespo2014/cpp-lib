// SyncSocket.h: interface for the CSyncSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCSOCKET_H__5AAD584C_3154_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_SYNCSOCKET_H__5AAD584C_3154_11D3_A264_0000E856599A__INCLUDED_
#include <WinSock.h>
#include "SockAddr.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CSyncSocket 
{
public:
	USHORT GetBigIndianOrder(USHORT port);
	int SendDatagram(char *pch, const int nSize, LPSOCKADDR psa, const int nSecs,int& fromlen);
	int ReceiveDatagram(char* pch, const int nSize, LPSOCKADDR psa, const int nSecs,int& fromlen);
	void Close();
	int Receive(char* pch, const int nSize, const int nSecs);
	int Send(const char* pch,const int nSize,const int nSecs);
	void Connect(LPSOCKADDR psa);
	static CSockAddr GetHostByName(const char* pchName,const USHORT ushPort=0);
	BOOL Accept(CSyncSocket& s, LPSOCKADDR psa);
	void Listen();
	void Bind(LPSOCKADDR psa);
	SOCKET m_hSocket;
	CString msg_error;
	void Create(int nType=SOCK_STREAM);
	CSyncSocket();
	virtual ~CSyncSocket();

private:
	
};

#endif // !defined(AFX_SYNCSOCKET_H__5AAD584C_3154_11D3_A264_0000E856599A__INCLUDED_)
