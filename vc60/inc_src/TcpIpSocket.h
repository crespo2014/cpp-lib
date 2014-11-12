// TcpIpSocket.h: interface for the CTcpIpSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPIPSOCKET_H__2BF733E2_1851_4579_9BD6_720CF1F25B23__INCLUDED_)
#define AFX_TCPIPSOCKET_H__2BF733E2_1851_4579_9BD6_720CF1F25B23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Winsock2.h"
#include "MessageEvent.h"
#include "ISocketEvents.h"

#define WB_SIZE	1024	// write buffer size

// Codigos de error
#define SE_DISCONNECT		10 // No hay coneccion establecida
#define SE_CONNECTING		11 // Estableciendo coneccion
#define SE_CONNECTFAILED	12 // Fallo estableciendo coneccion
#define SE_SNDMESSAGE		13 // Error enviando mensaje al hilo
#define SE_EVENTSEL			14 // Error asinando evento al socket
#define SE_SHUTDOWN			15 // Error en función shutdown

class CTcpIpSocket : protected CMessageEvent
{
protected:
	DWORD ThreadCheckEvents(WSANETWORKEVENTS* lpNetEvents);
	DWORD ThreadProcessMessage();
	DWORD ThreadGetMessage();
	DWORD ThreadConnectSocket();
	DWORD ThreadOnConnect(int iErrorCode);
	DWORD ThreadOnClose(int iErrorCode);
	DWORD ThreadCloseConnection();
	DWORD ThreadCloseSocket();
	DWORD ThreadOnRead(int iErrorCode);
	DWORD ThreadOnWrite(int iErrorCode);
	UINT Thread();
	static UINT ThreadProc(LPVOID pParam);
public:
	DWORD SetServer(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port);
	DWORD SetSocketEvents(LPTCPIPSOCKETEVENTS lpSocketEvents);
	DWORD Disconnect();
	DWORD ThreadSend(DWORD dwCant);
	DWORD ThreadGetSendBuffer(BYTE **lpbBuffer, DWORD *lpdwSize);

	DWORD Connect();
	DWORD GetThreadStatus(DWORD* lpdwstat);
	DWORD Release();
	DWORD Initialize();
	CTcpIpSocket();
	virtual ~CTcpIpSocket();
private:
	struct sockaddr_in m_SockAddr;
	BOOL		m_OnSockInit;
	WSAEVENT	m_hSockEvent;
	HANDLE		m_hSockThread;
	SOCKET		m_Socket;
	DWORD		m_ThreadStatus;
	int			m_ThreadError;	// Indica el codigo del ultimo error
	LPVOID		m_Param;
	DWORD		m_SockStat;		// Estado del socket utilizada por el hilo
	DWORD		m_BytesWritten;	// Cantidad de bytes que se han enviado
	DWORD		m_BytesToWrite;
	char		m_WriteBuffer[WB_SIZE];
	LPTCPIPSOCKETEVENTS	m_lpISocketEvents;

};

#endif // !defined(AFX_TCPIPSOCKET_H__2BF733E2_1851_4579_9BD6_720CF1F25B23__INCLUDED_)
