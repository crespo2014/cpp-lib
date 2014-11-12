// SockSvr.cpp: implementation of the CSockSvr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SockSvr.h"
#include "errorcodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSockSvr::CSockSvr()
{
	m_ISockSrvEvents = NULL;
	m_Port = 0;
	DWORD i;
	for (i = 0;i<MAX_SOCKS;i++)
	{
//		m_Socks[i].SetIndex(i);
	}
}

CSockSvr::~CSockSvr()
{

}

DWORD CSockSvr::Start(WORD wPort)
{
	WORD	i;
	DWORD	dr;
	int		ir;
	CSock*	pSock;
	do
	{
		dr = m_Socks[0].Listen(wPort);
		if (dr != ERR_NONE) break;
		for (;;)
		{
			dr = FillReadWriteSocks();
			if (dr == ERR_EOT) break;	// No se puede monitorear ningun socket
			ir = select(0,&m_ReadSet,&m_WriteSet,&m_ErrorSet,NULL);
			if (ir == SOCKET_ERROR) break;	//Fin del monitoreo por error
			// revisar coneccion
			if (FD_ISSET(m_Socks[0],&m_ReadSet) != 0)
			{
				pSock = GetFreeSock();
				if (pSock != NULL)
				{
					dr = pSock->Accept(&m_Socks[0]);
					if ((dr == ERR_NONE) && (m_ISockSrvEvents != NULL))
					{
						m_ISockSrvEvents->OnConnect(pSock);
					}
				}
			}
			// revisar resto de los sockets
			for (i=1;i<MAX_SOCKS;i++)
			{
				if (m_Socks[i].OnCheckRead())
				{
					if (FD_ISSET(m_Socks[i],&m_ReadSet) != 0) m_Socks[i].ProcessRead();
				}
				if (m_Socks[i].OnCheckWrite()) 
				{
					if (FD_ISSET(m_Socks[i],&m_WriteSet) != 0) m_Socks[i].ProcessWrite(); 				
				}
				if (FD_ISSET(m_Socks[i],&m_ErrorSet) != 0) m_Socks[i].ProcessError(); 				
			}
		}
	} while (false);
	return dr;
}

DWORD CSockSvr::FillReadWriteSocks()
{
	DWORD i;
	FD_ZERO(&m_WriteSet);
	FD_ZERO(&m_ReadSet);
	FD_ZERO(&m_ErrorSet);
	for (i = 0;i<MAX_SOCKS;i++)
	{
		if (!m_Socks[i].OnSocket()) continue;
		if (m_Socks[i].OnCheckRead())	FD_SET(m_Socks[i],&m_ReadSet);
		if (m_Socks[i].OnCheckWrite())	FD_SET(m_Socks[i],&m_WriteSet);
		if (m_Socks[i].OnCheckError())	FD_SET(m_Socks[i],&m_ErrorSet);
	}
	if ((m_WriteSet.fd_count == 0)&&
		(m_ReadSet.fd_count == 0)&&
		(m_ErrorSet.fd_count == 0))	return ERR_EOT;
	return 0;
}

/*
	Se monitorean lso sockets pero no se aceptan conecciones
*/
DWORD CSockSvr::Start()
{
	return ERR_NONE;
}

CSock* CSockSvr::GetFreeSock()
{
	DWORD i;
	for (i = 1;i<MAX_SOCKS;i++)
	{
		if (!m_Socks[i].OnSocket()) return &m_Socks[i];
	}
	return NULL;
}

DWORD CSockSvr::SetEvents(ISockSrvEvents *pISockSrvEvents)
{
	m_ISockSrvEvents = pISockSrvEvents;
	return 0;
}
