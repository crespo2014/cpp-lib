// Socket.h: interface for the CSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKET_H__6EFEDEF2_45B9_41CA_A0AA_5F902C6BD360__INCLUDED_)
#define AFX_SOCKET_H__6EFEDEF2_45B9_41CA_A0AA_5F902C6BD360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

#ifdef WIN32
	#define snprintf	_snprintf
	#define vsnprintf	_vsnprintf
	#define getpid		_getpid
	#define popen		_popen
	#define pclose		_pclose
	#define socklen_t	int
	#include <process.h>
	#include "Winsock.h"

	//#define WSAGetLastError()		errno
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <time.h>
	#include <ctype.h>
	#include <netinet/in.h>
    #include <arpa/inet.h>
	#include <errno.h>
    
	#define DWORD			unsigned long
	#define WORD			unsigned short
	#define BYTE			unsigned char       
	#define INADDR_NONE		0xffffffff
	#define SD_SEND			SHUT_WR
	#define SD_RECEIVE		SHUT_RD
	#define SD_BOTH			SHUT_RDWR
	#define SOCKET_ERROR        -1
	#define INVALID_SOCKET		-1
	#define WSAGetLastError()		errno
	#define closesocket				close
#endif


#define F_SOCKET_CAN_READ	1
#define F_SOCKET_CAN_WRITE	2
#define F_SOCKET_RD_CLOSE	4		// se ha cerrado el socket no se pueden leer mas bytes
#define F_SOCKET_WR_CLOSE	8		// se ha cerrado el socket no se pueden leer mas bytes
#define F_SOCKET_RD_FAILED	16		// fallo una operacion de lectura el socket esta en un estado fallido
#define F_SOCKET_WR_FAILED	32		// fallo una operacion de lectura el socket esta en un estado fallido
#define F_SOCKET_NEED_READ	64		// Indica que se necesita esperar el evento de lectura es una redundancia
#define F_SOCKET_NEED_WRITE	128		// Indica que se necesita esperar el evento de escritura	
#define F_SOCKET_OP_FAILED	256		// fallo una operacion en el socket esta en un estado fallido
#define F_SOCKET_CONNECTING	512		// fallo una operacion en el socket esta en un estado fallido
#define F_SOCKET_SRV_CONN	1024	// indica que la conecion se establecido por un socket de escucha y la estructura lsn_sock_addr es valida
#define F_SOCKET_WR_CLOSING	2048	// el canal de escritura debe ser cerrado despues de enviar el ultimo byte del buffer
#define F_SOCKET_RD_CLOSING	4096	// el canal de lectura es cerrado inmediatamente


class CSocket : public CbObject  
{
public:
	DWORD Close();
	void Release();
	DWORD Connect(BYTE b1, BYTE b2, BYTE b3, BYTE b4, WORD wPort);
	DWORD Write(void* pBuffer,DWORD dwSize);
	DWORD Create();
	DWORD SocketError_log(DWORD retval,int ierr_code, const char *format,...);
	CSocket();
	virtual ~CSocket();
private:
	SOCKET	m_socket;
	BOOL	m_bCantWrite;
	BOOL	m_bCantRead;
	WORD	m_port;
	DWORD	m_flags;
	struct sockaddr_in m_sockaddr;
};

#endif // !defined(AFX_SOCKET_H__6EFEDEF2_45B9_41CA_A0AA_5F902C6BD360__INCLUDED_)
