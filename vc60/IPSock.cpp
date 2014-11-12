// IPSock.cpp: implementation of the CIPSock class.
//
//////////////////////////////////////////////////////////////////////

#include "IPSock.h"

#define _FILENAME_ "ipsock.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void iptodw(BYTE x1,BYTE x2,BYTE x3, BYTE x4,BYTE* pb)
{
	*pb++ = x1;
	*pb++ = x2;
	*pb++ = x3;
	*pb = x4;
}

CIPSock::CIPSock()
{
	
}

CIPSock::~CIPSock()
{
	
}

/*
Obtener una tuberia para enviar los datos, 
se utilizara algun tipo de buffer 
*/

ITube* CIPSock::getSendTube()
{
	return this;
}

/*
Enviar datos cacheados. Es invocado a travez del End del tubo de salida
*/

DWORD CIPSock::flush()
{
	return ERR_OK;
}

/*
Se define la tuberia que procesara los datos de entrada del socket
*/
void CIPSock::setRecvTube(ITube *ptube)
{
	
}

/*
Leer los datos disponibles en el canal de entrada y pasarlos a la tuberia
*/
DWORD CIPSock::readInput()
{
	return ERR_OK;
}

/*
conectar el socket segun los parametros especificados
ip byte array [0].[1].[2].[3]
*/
DWORD CIPSock::connect(BYTE* ip,WORD port)
{
	if (create() != ERR_OK) return ERR_FATAL;
	
	m_ip = *((DWORD*)ip);
	
	int ir;
	iptodw(ip[0],ip[1],ip[2],ip[3],(BYTE*)&m_sock_addr.sin_addr.s_addr);
	m_sock_addr.sin_port = htons(80);
	m_sock_addr.sin_family = AF_INET;
	
	ir = ::connect(m_handle,(sockaddr*)&m_sock_addr,sizeof(m_sock_addr));
	
	return ERR_OK;
}

DWORD CIPSock::create()
{
	m_handle = socket(AF_INET,SOCK_STREAM,0);
	if (m_handle == -1) return ERR_FATAL;
	return ERR_OK;
}

DWORD CIPSock::system_init()
{
	static BOOL	binit = false;
	int	ir;
	if (binit) return ERR_OK;		// already initialize
	
#ifdef WIN32
	WORD	wVersionRequested;
	WSADATA wsaData;
	
	wVersionRequested = MAKEWORD( 2, 2 );
	ir = WSAStartup( wVersionRequested, &wsaData ); //if (ir != 0) return log_socket(&g_app_data,WSAGetLastError(),"%s WSAStartup ",fnc_name);
	if (ir != 0) return log_exit(ERR_FATAL);
#else
	
#endif
	binit = true;			// initialization is OK
	return ERR_OK;
}

 DWORD	CIPSock::Start()
{
	return ERR_OK;
}

 DWORD	CIPSock::End()
{
	return ERR_OK;
}

DWORD	CIPSock::Push(BYTE b)
{
	DWORD dwr;
	mOutBuffer[mOutBufferCount++] = b;
	// utilizar un buffer temporal y esperar un flush
	if (mOutBufferCount == 255)
	{
		dwr = Flush(); if (dwr != ERR_OK) return log_exit(dwr);
	}
	return ERR_OK;
}

DWORD CIPSock::Flush()
{
	int	ir;
	ir = send(m_handle,(const char*)mOutBuffer,mOutBufferCount,0);
	if (ir == SOCKET_ERROR) return log_exit(ERR_FATAL);
	mOutBufferCount = 0;
	return ERR_OK;
}
