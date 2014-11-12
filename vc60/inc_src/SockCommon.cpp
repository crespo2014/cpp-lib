// Sock.cpp: implementation of the CSock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sock.h"
#include "winsock2.h"

DWORD InitializeWinSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2,2);
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) return 1;
	return 0;
}
