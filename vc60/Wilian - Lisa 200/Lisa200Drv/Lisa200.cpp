// Lisa200.cpp: implementation of the CLisa200 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa200.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLisa200::CLisa200()
{

}

CLisa200::~CLisa200()
{

}

DWORD _stdcall CLisa200::CheckCap(DWORD dwCapability)
{
	switch (dwCapability)
	{
	case CAP_LOCALCONNECTION : return ERR_UNSUPORTED;
	case CAP_REMOTECONNECTION : return 0;
	}
	return 0;
}
DWORD _stdcall CLisa200::SetRemoteConfiguration(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port)
{
	return SetServer(b1,b2,b3,b4,port);
}
DWORD _stdcall CLisa200::SetLocalConfiguration(BYTE bPort,DWORD dwBaudRate,BYTE bParity,BYTE bStopBits)
{
	return 1;
}
DWORD _stdcall CLisa200::Connect()
{
	switch (CTcpIpSocket::Connect())
	{
	case SE_CONNECTING: return ERR_CONNECTING;
	case SE_CONNECTFAILED: return ERR_CONNECT_FAILED;
	case 0: return 0;
	}
	return ERR_UNKNOWN;
}
DWORD _stdcall CLisa200::Disconnect()
{
	return 0;
}
DWORD _stdcall CLisa200::Initialize()
{
	CLisa2000Client::Initialize();
	return 0;
}
DWORD _stdcall CLisa200::Release()
{
	CLisa2000Client::Release();
	return 0;
}
DWORD _stdcall CLisa200::GetResults()
{
	switch (RequestResults())
	{
	case CE_DISCONNECT : return ERR_CONNECT_FAILED;
	case CE_GETINGDATA : return ERR_GETING_RESULT;
	case 0 :	 return 0;
	case CE_INVDATA : return ERR_INVALIDDATA;
	}
	return ERR_UNKNOWN;
}

DWORD _stdcall CLisa200::GetResultByName(char* PatName,char* AnaName,float* lpResult)
{

	return 0;
}

DWORD _stdcall CLisa200::GetAnalisysByName(char* AnaName,char* unit,DWORD* dwMaxCount)
{

	return 0;
}

DWORD _stdcall CLisa200::GetResultByPos(DWORD PatPos,DWORD AnaPos,float* lpResult)
{
	return CLisa2000Client::GetResultByPos(PatPos,AnaPos,lpResult);
}
