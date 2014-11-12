// SockBridge.cpp: implementation of the CSockBridge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SockBridge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSockBridge::CSockBridge()
{
	m_Status = SCKB_NONE;
	m_srcSock = NULL;
	m_destSock = NULL;
}

CSockBridge::~CSockBridge()
{

}

DWORD CSockBridge::ConnectSock(CSock *src, CSock *dest, BYTE b1, BYTE b2,BYTE b3, BYTE b4, WORD wPort)
{
	DWORD	dr;
//	CCircularBuffer* pBuffer;
	do
	{
		m_srcSock = src;
		m_destSock = dest;
		m_srcSock->SetEvents(this);
		m_destSock->SetEvents(this);
//		pBuffer = m_srcSock->GetSndBuffer();
//		if (pBuffer != NULL) pBuffer->SetSize(500);
		m_Status = SCKB_CONNECTING;
		dr = m_destSock->Connect(b1,b2,b3,b4,wPort);
		if ((dr != ERR_NONE) && (dr != ERR_PENDING)) break;
		return ERR_NONE;
	}while(false);
	Close();
	return dr;
}

DWORD _stdcall CSockBridge::OnProcessRead(CSock* pSock)
{
	if (m_Status == SCKB_CONNECT)
	{
		// Procesamiento extra antes de biconnected
	}
	
	// si no hay biconeccion no se puede proceder
	if (m_Status != SCKB_BICONNECT) return 0; 
	
	CSock* readsck = pSock;
	CSock* writesck;
	if (readsck == m_srcSock) 
		writesck = m_destSock;
	else
		writesck = m_srcSock;

	return RecvAndSend(readsck,writesck);
}

DWORD _stdcall CSockBridge::OnProcessWrite(CSock* pSock)
{
	if (m_Status == SCKB_CONNECT)
	{
		// Procesamiento extra antes de biconnected
	}

	// si no hay biconeccion no se puede proceder
	if (m_Status != SCKB_BICONNECT) return 0;

	CSock*				writesck = pSock;
	CSock*				readsck;
	// Ajuste de sock
	if (writesck == m_srcSock) 
		readsck = m_destSock;
	else
		readsck = m_srcSock;
	
	return RecvAndSend(readsck,writesck);
}

DWORD _stdcall CSockBridge::OnClose(CSock* pSock)
{
	// Si se cae un socket se cae el otro 
	CSock* destSock;
	if (pSock == m_srcSock)
	{
		m_srcSock = NULL;
		destSock = m_destSock;
	}
	else
	{
		m_destSock = NULL;
		destSock = m_srcSock;
	}
	return Close();
}

DWORD _stdcall CSockBridge::OnConnect(CSock* pSock)
{
//	CCircularBuffer* pBuffer;

	// Socket destino conectado
	m_Status = SCKB_CONNECT;
	//pBuffer = pSock->GetSndBuffer();
	//if (pBuffer != NULL) pBuffer->SetSize(500);

	// Pasos iniciales
	m_Status = SCKB_BICONNECT;
	// esperar por los eventos del socket que se acaba de conectar
	char name[30];
//	sprintf(name,"S%d-%d.hex",pSock->GetIndex(),GetTickCount());
	TrafficFile.Create(name);
	return 0;
}

DWORD CSockBridge::Close()
{
	if (m_Status == SCKB_NONE) return ERR_NONE;
	DWORD dr;
	m_Status = SCKB_NONE;
	if (m_srcSock != NULL) dr = m_srcSock->Close();
	if (m_destSock != NULL) dr = m_destSock->Close();
	m_srcSock = NULL;
	m_destSock = NULL;
	TrafficFile.Close();
	return ERR_NONE;
}

DWORD CSockBridge::RecvAndSend(CSock *pRcvSock, CSock *pSndSock)
{
	DWORD				dr;
	DWORD				size;
//	CCircularBuffer*	pBuffer;
	BYTE*				Buffer;
	DWORD				BytesRead;

	// Preguntar si el otro socket soporta escritura
	if (pRcvSock->OnCantRead()) 
	{
		pSndSock->ShutDownSend();
		return 0;
	}
	if (pSndSock->OnCantWrite())
	{
		pRcvSock->ShutDownSend();
		return 0;
	}

	// Revisar disponibilidad de buffer
	//pBuffer = pSndSock->GetSndBuffer();					
	//if (!pBuffer->OnBuffer()) return Close();			// No hay buffer no se puede proceder
	
	BOOL loop = true;
	BOOL onread = false;
	do
	{
		//dr = pBuffer->GetWriteBuffer(&Buffer,&size,NULL);
		if (size == 0) break;							// No hay espacio, hay que esperar
		// Leer datos del socket
//		dr = pRcvSock->Recv(Buffer,size,&BytesRead);
		switch (dr)
		{
		case ERR_NODATA:
			{
				loop = false;
				break;
			}
		case ERR_EOT:
			{
				// Graceful shutdown
				//pRcvSock->Close();
				pRcvSock->ShutDownSend();
				pSndSock->ShutDownSend();
				onread = true;
				loop = false;
				break;
			}
		case ERR_NONE:
			{
//				pBuffer->UpdateWritePtr(BytesRead);
				if (pRcvSock == m_srcSock) 
					TrafficFile.AddSendBuffer(Buffer,BytesRead);
				else
					TrafficFile.AddRecvBuffer(Buffer,BytesRead);
				// Se puede indicar un process write para que lo datos leidos se transmitan al momento
				onread = true;
				break;
			}
		case ERR_CLOSE:
		default:
			{
				loop = false;
				break;
			}
		}
	}while (loop);
//	if (onread) pSndSock->DispatchSendData();
	return 0;
}
