// Socket.cpp: implementation of the CSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "Socket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct S_ERR_MSG
{
	union {	
		int		icode;
		DWORD	dwcode;
	};
	char	*msg;
};

struct S_ERR_MSG C_SOCK_ERR[] = {

#ifdef WIN32
	{ WSAEACCES			,"The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST parameter to allow the use of the broadcast address. "},
	{ WSAEADDRINUSE		,"A process on the machine is already bound to the same fully-qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP address and port are bound in the af_inet case). (See the SO_REUSEADDR socket option under setsockopt.) "},
	{ WSAEADDRNOTAVAIL	,"The specified address is not a valid address for this machine (such as ADDR_ANY)."},
	{ WSAEAFNOSUPPORT	,"Addresses in the specified family cannot be used with this socket. The specified address family is not supported. "},
	{ WSAEALREADY		,"A nonblocking connect call is in progress on the specified socket. Note In order to preserve backward compatibility, this error is reported as WSAEINVAL to Windows Sockets 1.1 applications that link to either Winsock.dll or Wsock32.dll."},
	{ WSAECONNABORTED 	,"The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable. "},
	{ WSAECONNREFUSED	,"The attempt to connect was forcefully rejected. "},
	{ WSAECONNRESET 	,"The virtual circuit was reset by the remote side executing a hard or abortive close. For UPD sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a Port Unreachable ICMP packet. The application should close the socket as it is no longer usable. "},
	{ WSAEFAULT			,"The name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s. "},
	{ WSAEFAULT			,"The name or the namelen parameter is not a valid part of the user address space, the namelen parameter is too small, or the name parameter contains incorrect address format for the associated address family. "},
	{ WSAEHOSTUNREACH 	,"The remote host cannot be reached from this host at this time. "},
	{ WSAEINPROGRESS	,"A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. "},
	{ WSAEINTR			,"A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall. "},
	{ WSAEINVAL			,"The socket is already bound to an address. or has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled. "},
	{ WSAEISCONN		,"The socket is already connected (connection-oriented sockets only). "},
	{ WSAEMFILE			,"No more socket descriptors are available. "},
	{ WSAEMSGSIZE 		,"The socket is message oriented, and the message is larger than the maximum supported by the underlying transport. "},
	{ WSAENETDOWN		,"The network subsystem or the associated service provider has failed."},
	{ WSAENETRESET		,"The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress."},
	{ WSAENETUNREACH	,"The network cannot be reached from this host at this time. "},
	{ WSAENOBUFS		,"Not enough buffers available. "},
	{ WSAENOTCONN		,"The socket is not connected. "},
	{ WSAENOTSOCK		,"The descriptor is not a socket. "},
	{ WSAEPROTONOSUPPORT,"The specified protocol is not supported. "},
	{ WSAEPROTOTYPE		,"The specified protocol is the wrong type for this socket. "},
	{ WSAESHUTDOWN		,"The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH. "},
	{ WSAESOCKTNOSUPPORT,"The specified socket type is not supported in this address family."},
	{ WSAETIMEDOUT 		,"The connection has been dropped, because of a network failure or because the system on the other end went down without notice. "},
	{ WSAEWOULDBLOCK	,"The socket is marked as nonblocking and the requested operation would block. "},
	{ WSANOTINITIALISED	,"A successful WSAStartup call must occur before using this function."},
#else
	{ EACCES			,"Permission to create a socket of  the  specified  type and/or protocol is denied."},
	{ EACCES			,"Search permission is denied for  a  component  of  the path prefix of the pathname in name."},
	{ EACCES			,"The requested address is  protected  and  the  current user has inadequate permission to access it."},
	{ EADDRINUSE		,"The specified address is already in use."},
	{ EADDRNOTAVAIL		,"The specified address is not available  on  the  local machine."},
	{ EBADF				,"s is not a valid descriptor."},
	{ EINVAL			,"The socket is already bound to an address."},
	{ EINVAL			,"namelen is not the size of a  valid  address  for  the specified address family."},
	{ EIO				,"An I/O error occurred while making the directory entry or allocating the inode."},
	{ EISDIR			,"A null pathname was specified."},
	{ ELOOP				,"Too many symbolic links were encountered in  translat- ing the pathname in name."},
	{ EMFILE			,"The per-process descriptor table is full."},
	{ ENOENT			,"A component of the path prefix of the pathname in name does not exist."},
	{ ENOMEM			,"Insufficient user memory is available."},
	{ ENOSR				,"There were  insufficient  STREAMS  resources  for  the operation to complete."},
	{ ENOSR				,"There were insufficient STREAMS resources available to  complete the operation."},
	{ ENOTDIR			,"A component of the path prefix of the pathname in name is not a directory."},
	{ ENOTSOCK			,"s is a descriptor for a file, not a socket."},
	{ EPROTONOSUPPORT   ,"The protocol type or the  specified  protocol  is  not  supported within this domain."},
	{ EROFS				,"The inode would reside on a read-only file system."},
#endif
	{0,NULL}};


CSocket::CSocket()
{
	m_socket = INVALID_SOCKET;
	m_bCantWrite = 0;
	m_bCantRead = 0;
	m_flags = 0;
	m_port = 0;
	ZERO(m_sockaddr);
}

CSocket::~CSocket()
{

}

DWORD CSocket::SocketError_log(DWORD retval, int ierr_code, const char *format, ... )
{
	char	*fnc_name = "CSocket::SocketError_log";
	char	err_str[500];
	char	*cptr;
	int		i,j;
	va_list arg_ptr;

	cptr = err_str; 
	for (;;) {
		va_start(arg_ptr, format);
		i = vsnprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,format,arg_ptr);
		va_end(arg_ptr);
		if (i<0) break;
		cptr += i;
    
		i = snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1," failed with code = %d ",ierr_code);
		if (i<0) break;
		cptr += i;

		i = 0;
		for (j=0;C_SOCK_ERR[j].msg != NULL;j++)
		{
			if (C_SOCK_ERR[j].icode == ierr_code) 
			{
				i = snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,"%s",C_SOCK_ERR[j].msg);
				break;
			}
		}
		if (i<0) break;
		cptr += i;

	#ifdef WIN32
	#else
		i = snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,"%s : ",strerror(ecode));
		if (i<0) break;
		cptr += i;
	#endif
		if (C_SOCK_ERR[j].msg == NULL) {
			i = snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,"Unknown error ");
			if (i<0) break;
			cptr += i;
		}
		break;
	}
	
	return LOG_TERROR retval,"%s",err_str);
}

DWORD CSocket::Create()
{
	char	*fnc_name = "CSocket::Create";
	
	if (m_socket != INVALID_SOCKET) Release();

	m_socket = ::socket(AF_INET,SOCK_STREAM,0);  if (m_socket == INVALID_SOCKET) return SocketError_log(ERR_API,WSAGetLastError(),"%s Socket",fnc_name);
	m_bCantRead = true;
	m_bCantWrite = true;
	/*
	m_error = ioctlsocket(m_socket,FIONBIO,&m_nonblockingmode);
	if (m_error != 0) return ERR_API;
	*/
	return ERR_OK;	
}

DWORD CSocket::Write(void *pBuffer, DWORD dwSize)
{
	char	*fnc_name = "CSocket::Write";
	int	ir;
	
	if (m_socket == INVALID_SOCKET) return LOG_TERROR ERR_HANDLE,"Socket not open");

	ir = send(m_socket,(char*)pBuffer,dwSize,0);
	if (ir>0)
	{
		if (ir < dwSize) return LOG_TERROR ERR_HANDLE,"%d bytes of data has been trunc",dwSize - ir);
		return ERR_OK;
	}
	if (ir == 0) return LOG_TERROR ERR_EOF,"Write channel is closed");
	return SocketError_log(ERR_API,WSAGetLastError(),"%s Send",fnc_name);
}

DWORD CSocket::Connect(BYTE b1, BYTE b2, BYTE b3, BYTE b4, WORD wPort)
{
	char	*fnc_name = "CSocket::Connect";
	DWORD dwr;
	int	ir;
	dwr = Create(); if (dwr != ERR_OK) return LOG_TSTACK;

	m_sockaddr.sin_family = AF_INET;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b1 = b1;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b2 = b2;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b3 = b3;
	m_sockaddr.sin_addr.S_un.S_un_b.s_b4 = b4;
	m_sockaddr.sin_port = htons(wPort);

	ir = connect(m_socket,(SOCKADDR*)&m_sockaddr,sizeof(m_sockaddr));
	if (ir == 0) return ERR_OK;

	return SocketError_log(ERR_API,WSAGetLastError(),"%s Connect",fnc_name);
}

void CSocket::Release()
{
	Close();
}

DWORD CSocket::Close()
{
	if (m_socket == INVALID_SOCKET) return ERR_OK;
	::closesocket(m_socket);
	m_socket = INVALID_SOCKET;
	m_bCantWrite = 0;
	m_bCantRead = 0;
	m_flags = 0;
	m_port = 0;
	ZERO(m_sockaddr);
	return ERR_OK;
}
