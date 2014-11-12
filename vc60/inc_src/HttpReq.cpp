// HttpReq.cpp: implementation of the CHttpReq class.
//
//////////////////////////////////////////////////////////////////////


#include "HttpReq.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHttpReq::CHttpReq()
{
	mAgent = L"Mozilla/4.0";
	mProtocol = L"HTTP/1.1";
	mProxy = NULL;
	mLanguage = L"es";

}

CHttpReq::~CHttpReq()
{

}

DWORD CHttpReq::Connect(WCHAR *agent, WCHAR *proxy, WCHAR *server, WORD port)
{
	return ERR_OK;
}
