// Sock.h: interface for the CSock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCK_H__9E7CB77E_3378_4680_849A_AC61018E6F55__INCLUDED_)
#define AFX_SOCK_H__9E7CB77E_3378_4680_849A_AC61018E6F55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winsock.h"
#include "logclient.h"

// Estados del socket
#define SS_NONE			0	// No se ha creado el socket hilo cerrado
#define SS_LISTEN		1	// El socket esta en estado de escucha por una coneccion
#define SS_CONNECTING	2	// El socket esta procesando una coneccion (connect)
#define SS_CONNECT		3	// El socket esta conectado
#define SS_DISCONNECT	4	// Se esta desconectando recivio un shutdown
#define SS_CLOSING		5	// Cerrando se envio un Shutdown SEND
#define SS_CLOSED		6	// socket creado pero desconectado se cayo la coneccion o no se pudo conecctar

#define SCK_SNDSIZE	500		// Tamaño del buffer de escritura

// mensajes enviados

class ISockEvents;

typedef struct {
  u_int    fd_count;                  
  SOCKET   fd_array[1];
  operator fd_set*() {return (fd_set*)this;};
} fd_set1;

class CSock  
{
public:
	DWORD Send(void *buffer,DWORD size);
	DWORD TRecv(char *pBuffer, WORD size, WORD *pReceived);
	DWORD TSend(char* pBuffer,WORD size,WORD* pWritten);
	DWORD TSend(WORD wSize);
	DWORD TGetSendBuffer(char **ppBuffer, WORD *pSize);
	DWORD TOnExcept();
	DWORD TOnRead();
	DWORD TOnWrite();
	DWORD TProcessMessage();
	DWORD TGetMessage();
	DWORD	SetEvents(ISockEvents* pISockEvents);
	DWORD	GetError(int* pierror);
	DWORD	Listen(WORD wport,int ibacklog = 5);
	DWORD	ShutDownSend();
	DWORD	Bind(WORD wPort);
	DWORD	Accept(CSock * pSock);
	DWORD	Close();
	DWORD	SetNonBlockingMode(BOOL bmode);
	DWORD	Connect(BYTE b1,BYTE b2,BYTE b3,BYTE b4,WORD wPort);
	DWORD	Create();
	BOOL	OnCheckRead() {return ((m_status == SS_CONNECT)||(m_status == SS_LISTEN)||(m_status == SS_CLOSING))&&(!m_OnCantWrite);};
	BOOL	OnCheckWrite() {return ((m_status == SS_CONNECT)||(m_status == SS_CONNECTING)||(m_status == SS_DISCONNECT))&&(!m_OnCantRead);};
	BOOL	OnCheckError() {return (m_status == SS_CONNECTING);};
	BOOL	OnSocket() {return m_socket != INVALID_SOCKET;};
	BOOL	OnCantRead() {return ((m_status == SS_CONNECT)&&(m_OnCantRead));};
	BOOL	OnCantWrite() {return ((m_status == SS_CONNECT)&&(m_OnCantWrite));};
	operator SOCKET()  const {return m_socket;};
	CSock();
	virtual ~CSock();
private:
	DWORD Thread();
	SOCKET	m_socket;
	BOOL	m_OnCantWrite;
	BOOL	m_OnCantRead;
	DWORD	m_status;
	WORD	m_port;
	int		m_error;
	struct sockaddr_in m_sockaddr;
	DWORD	m_nonblockingmode;
	char	m_sndbuff[SCK_SNDSIZE];
	WORD	m_bufffirst;	// Primer byte a enviar (0...n)
	WORD	m_buffsize;		// cantida de bytes por enviar
	ISockEvents*	m_events;
	BOOL	m_trunning;
	HANDLE	m_hThread;
	
protected:
	static UINT ThreadProc(LPVOID pParam);
};

class ISockEvents
{
public:
	virtual DWORD _stdcall OnProcessRead(CSock* pSock) = 0;
	virtual DWORD _stdcall OnProcessWrite(CSock* pSock) = 0;
	virtual DWORD _stdcall OnClose(CSock* pSock) = 0;
	virtual DWORD _stdcall OnConnect(CSock* pSock) = 0;
	virtual DWORD _stdcall OnDisconnect(CSock* pSock) = 0;
};

#endif // !defined(AFX_SOCK_H__9E7CB77E_3378_4680_849A_AC61018E6F55__INCLUDED_)
