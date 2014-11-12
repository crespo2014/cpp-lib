// LogClient.cpp: implementation of the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#include "LogClient.h"
#include "stdio.h"
#include "utils.h"
#define _FILENAME_ "log.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
extern "C" 
{
	DWORD glog_log(char* str1,char* str2)
	{
		return CLogClient::get()->Write(LOG_LLAST,"","",0,ERR_FATAL,"%s %s",str1,str2);
	}
	DWORD	glog_int(char* str1,int val)
	{
		return  CLogClient::get()->Write(LOG_LLAST,"","",0,ERR_FATAL,"%s %d",str1,val);
	}
}
*/

#define _CHECK_NULL_	if (this == NULL) return retval;

#define LOGCONSEVENT	"Global\\logconsoleevent"	// Usado para activar la pantalla de consola
#define LOGFILEEVENT	"Global\\logfileevent"	// Usado para activar la pantalla de consola

static struct 
{
	union {	
		int		icode;
		DWORD	dwcode;
	};
	char	*msg;
} C_SOCK_ERR[] = {

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


CLogClient::CLogClient()
{
	//	Crear evento de disparo de la consola
	m_hFile			= INVALID_HANDLE_VALUE;
	m_hStdOut		= INVALID_HANDLE_VALUE;
	m_bDeleteStd	= FALSE;
	m_dwlasttime	= GetTickCount();
	m_bAddEndFile	= false;
	m_log_level		= LOG_LERROR;
	m_bCloseFile	= true;			// siempres se puede cerrar a menos que se cree sin el evento
	m_bconsole_ouput = false;
	m_ilog	= NULL;

	m_show_flag = LOG_SHOW_DATETIME|LOG_SHOW_LEVEL|LOG_SHOW_FILE_NAME|LOG_SHOW_FILE_LINE;

	CreateEvents();
}

CLogClient::~CLogClient()
{
	EventsClose();
	CloseFile();
	CloseConsole();	
}

DWORD CLogClient::CloseFile()
{
	if (m_hFile == INVALID_HANDLE_VALUE) return 0;
	CloseHandle(m_hFile);
	m_hFile = INVALID_HANDLE_VALUE;
	return 0;
}

DWORD CLogClient::CloseConsole()
{
	if ((m_hStdOut == INVALID_HANDLE_VALUE) ||
		(m_bconsole_ouput)) return 0;

	m_hStdOut = INVALID_HANDLE_VALUE;
	if (m_bDeleteStd)	FreeConsole();
	return ERR_OK;
}

BOOL CLogClient::HasLogFile()
{
	return (m_hFile != INVALID_HANDLE_VALUE);
}

// Revisar los eventos para permitir el envio de logs a consola y fichero
DWORD CLogClient::CheckEvents()
{
	DWORD	dwr;
	if ((m_hconsoleevent != NULL) && (!m_bconsole_ouput)) 
	{
		dwr = WaitForSingleObject(m_hconsoleevent,0);
		if (dwr == WAIT_OBJECT_0) 
		{
			m_log_level = LOG_LLAST;
			OpenConsole();
		}
		else 
			CloseConsole();
	}

	if (m_bCloseFile)
	{
		dwr = WaitForSingleObject(m_hfileevent,0);
		switch (dwr)
		{
		case WAIT_OBJECT_0: 
			if (m_hFile != INVALID_HANDLE_VALUE) break;
			CreateFile();
			m_bCloseFile = true;
			m_log_level = LOG_LLAST;
			break;
		default:
			if (m_hFile == INVALID_HANDLE_VALUE) break;
			CloseFile();
			break;
		}
	}
	return ERR_OK;
}

DWORD CLogClient::CreateEvents()
{
	m_hconsoleevent = CreateEventA(NULL,true,false,LOGCONSEVENT);
	m_hfileevent	= CreateEventA(NULL,true,false,LOGFILEEVENT);
	return ERR_OK;
}

DWORD CLogClient::OpenConsole()
{
	// abrir la consola y verificar que fue creada por nosotros
	if (m_hStdOut != INVALID_HANDLE_VALUE) return 0;
	BOOL	br;
	br = AllocConsole();
	m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (br) m_bDeleteStd = TRUE;	// fue creada por nosotros se debe borrar
	return ERR_OK;
	
}

DWORD CLogClient::SetEvent(HANDLE m_hevent, BOOL bstate)
{
	if (m_hevent == NULL)	return ERR_HANDLE;
	if (bstate)
		::SetEvent(m_hevent);
	else
		::ResetEvent(m_hevent);
	return ERR_OK;
}

DWORD CLogClient::ElapsedTime_Show(char* fnc_name,int line,WORD level,DWORD starttime)
{
	DWORD	time;
	WORD	day;
	WORD	hour;
	WORD	min;
	WORD	sec;
	WORD	msec;
	char	elapse[150];
	int		size = sizeof(elapse) - 1;
	int		i;
	char	*cptr = elapse;

	if (this == NULL)			return ERR_OK;
	if (level > m_log_level)	return ERR_OK;

	if (starttime == 0)
		time = GetTickCount() - m_dwlasttime;
	else
		time = GetTickCount() - starttime;

	msec =  (WORD)(time % 1000);
	time =  time / 1000;
	sec =	(WORD)(time % 60);
	time =  time / 60;
	min =	(WORD)(time % 60);
	time =  time / 60;
	hour = 	(WORD)(time % 24);
	time =	time / 24;
	day =	(WORD)time;
	if (day != 0)		i = _snprintf(cptr,size," %d days %d hours %d minutes %d seconds %d ms ",day,hour,min,sec,msec);
	else if (hour != 0) i = _snprintf(cptr,size," %d hours %d minutes %d seconds %d ms ",hour,min,sec,msec);
	else if (min != 0)	i = _snprintf(cptr,size," %d minutes %d seconds %d ms ",min,sec,msec);
	else if (sec != 0)	i = _snprintf(cptr,size," %d seconds %d ms ",sec,msec);
	else i = _snprintf(cptr,size," %d ms ",msec);
	return Write (level,fnc_name,line,ERR_OK,"Elapse : %s",elapse);
}

DWORD CLogClient::ElapsedTime_Reset(char* fnc_name,int line,WORD level,DWORD *time)
{
	if (this == NULL)			return ERR_OK;
	if (level > m_log_level)	return ERR_OK;

	if (time == NULL)
		m_dwlasttime = GetTickCount();
	else
		*time = GetTickCount();
	
	return Write (level,fnc_name,line,ERR_OK,"Start Time Count......0s");
}

DWORD CLogClient::EventsClose()
{
	if (m_hconsoleevent != NULL) CloseHandle(m_hconsoleevent);
	if (m_hfileevent != NULL)	 CloseHandle(m_hfileevent);
	m_hconsoleevent = NULL;
	m_hfileevent	= NULL;
	return ERR_OK;
}

void CLogClient::_rtrim(char* str)
{
	if (str[0] == 0) return;
	int i = strlen(str)-1;
	for(;i>0;i--)
	{
		if (str[i] != ' ') break;
		str[i] = 0;
	}
}

void CLogClient::SetConsoleOutput(BOOL status)
{
	m_bconsole_ouput = status; 
	if (status) 
		OpenConsole(); 
	else 
		CloseConsole();
};

DWORD CLogClient::log_buffer(WORD level, byte *buffer, WORD size, byte width, byte base, char separator, bool browpos)
{
	int		i;
	int		col;
	int		row;
	char	msg[2048];
	char	*cptr;

	DWORD	len;

	if (!IsActiveLogOutput())	return ERR_FATAL;
	if (level > m_log_level)	return ERR_FATAL;
	Write(level,"",0,ERR_OK,"Showing %d bytes of data",size); 
	cptr = msg;
	col = 0;
	row = 0;
	for (i = 0;i<(size + 1);i++,col++)
	{
		if (i == size) cptr += sprintf(cptr,"\r\n");
		if ((cptr - msg > (sizeof(msg) - 10)) ||
			(i == size))
		{
			len = strlen(msg);
			Write(level,"",0,ERR_OK,"%s",msg); 
			cptr = msg;
		}
		if (i == size) break;

		if (col == width) 
		{
			cptr += sprintf(cptr,"\r\n");
			col = 0;
			row++;
		}
		if ((col == 0) && (browpos)) cptr += sprintf(cptr,"%04X ",i);
		// imprimir el numero en i
		switch (base)
		{
		case 10: cptr += sprintf(cptr,"%03d",buffer[i]);break;
		//case 10: cptr += sprintf(cptr,"%03d",buffer[i]);break;
		case 255: 
			{
				if (buffer[i] < ' ') *cptr = '.'; else *cptr = buffer[i];
				cptr++; *cptr=0;
				break;
			}
		default:
		case 16: cptr += sprintf(cptr,"%02X",buffer[i]);break;
		}
		
		if (separator != 0) { *cptr = separator; cptr++; *cptr = 0;}
	}
	return ERR_FATAL;
}

DWORD CLogClient::CreateFile(char *file_name, char *end_str, char *file_ext,BOOL bOpen)
{
	char	fname[MAX_PATH];
	_snprintf(fname,sizeof(fname),"%s%s%s",file_name,end_str,file_ext);
	return CreateFile(fname,bOpen);
}

//DEL void CLogClient::SetStack(void *pmempage, WORD level)
//DEL {
//DEL 	if (pmempage == NULL)
//DEL 	{
//DEL 		m_bStack_Output = false;
//DEL 	}
//DEL 	else
//DEL 		m_bStack_Output = true;
//DEL 	m_pstack = pmempage;
//DEL 	m_stack_level = level;
//DEL }

//DEL void CLogClient::Push(char *log_str,DWORD str_len)
//DEL {
//DEL 	CMemPage	*mempage;
//DEL 
//DEL 	if (m_pstack == NULL) return;
//DEL 	if (str_len == 0) str_len = strlen(log_str);
//DEL 	if (str_len == 0) return;
//DEL 	mempage = (CMemPage*)m_pstack;
//DEL 	if (!mempage->IsFreeToAdd(str_len))
//DEL 	{
//DEL 		mempage->SetPtr(mempage->GetPage());
//DEL 		// reseteo del puntero, el datasize no va a disminuir y marcara el ultimo cartel, ponerlo a cero para el edit
//DEL 	}
//DEL 	mempage->addBlock(log_str,str_len,NULL,false);
//DEL }

DWORD CLogClient::CreateFile(char *file_name,BOOL bOpen)
{
	DWORD	dwr;
	DWORD	flags;
	DWORD	share;
	char	fname[MAX_PATH];
	char	pname[MAX_PATH];
	char	*cptr;
	CLogClient*	m_plog = this;

	if ((file_name == NULL) || (*file_name == 0))
	{
		if (m_hFile != INVALID_HANDLE_VALUE) return ERR_OK;	// Ya esta creado el fichero
		GetModuleFileNameA(NULL,pname,sizeof(pname));
		cptr = CUtils::File_GetName(pname);
		SYSTEMTIME date;
		GetLocalTime(&date);
		_snprintf(SSIZE(fname),"c:\\log\\%s_%02d%02d_%08X",cptr,date.wMonth,date.wDay,GetTickCount());
	}
	else
	{
		*fname = 0;
		strncat(fname,file_name,sizeof(fname));
	}
	if (bOpen) 
	{
		flags = OPEN_ALWAYS;
		share = FILE_SHARE_WRITE;
	}
	else 
	{
		flags = CREATE_ALWAYS;
		share = 0;
	}
	share = share | FILE_SHARE_READ;
	m_bAddEndFile = bOpen;
	CloseFile();
	m_hFile = ::CreateFileA(fname,GENERIC_WRITE,share,NULL,flags,FILE_ATTRIBUTE_NORMAL,NULL);
	dwr = GetLastError();
	if (m_hFile == INVALID_HANDLE_VALUE) 
	{
		cptr = pname;
		_snprintf(cptr,sizeof(pname)-(cptr-pname)-1,"CreateFile <%s> Failed because ",fname);
		cptr += sprintf(cptr," 0x%X - ",dwr);
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,dwr,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(pname)-(cptr-pname)-1,NULL);
		// {TRACE1("E: CreateFile Failed... Error %d",GetLastError());return 1;}
		return ERR_FATAL;
	}
	m_bCloseFile = false;
	GetModuleFileNameA(NULL,fname,sizeof(fname));
	_LOG_ERROR ERR_OK,"Proccess %s, PID 0x%X",fname,GetCurrentProcessId());
	return ERR_OK;

}

DWORD CLogClient::Write(WORD level,char	*file,int line,DWORD retval,char *format, ...)
{
	char	msg[2048];
	char	*cptr;
	int		i;
	va_list arg_ptr;
	DWORD	len;
	_CHECK_NULL_
	if (level > m_log_level) return retval;		// esta funcion puede ser invocada directamente
	if (!IsActiveLogOutput())	return retval;

	*msg = 0;
	cptr = GetHeader(msg,sizeof(msg),level,file,line);
	for (;;) {
		va_start(arg_ptr, format);
		i = _vsnprintf(cptr,sizeof(msg)- (cptr-msg)-2,format,arg_ptr);
		va_end(arg_ptr);
		if (i<0) break; cptr += i;

		i = _snprintf(cptr,msg + sizeof(msg) - cptr-1,"\r\n");
		if (i<0) break; cptr += i;
		break;
	} 
	len = strlen(msg);
	if (m_ilog != NULL) m_ilog->Log(level,file,line,msg);
	return Log_Write(retval,msg,len);
}

DWORD CLogClient::Write_W32Error(char *file,int line,DWORD w32_ecode, DWORD retval, char *format, ...)
{
	char	msg[2048];
	char	*cptr;
	int		i;
	va_list arg_ptr;
	DWORD	len;

	if (this == NULL) return retval;
	if (!IsActiveLogOutput())	return retval;

	*msg = 0;
	cptr = GetHeader(msg,sizeof(msg),LOG_LERROR,file,line);
	for (;;) {
		va_start(arg_ptr, format);
		i = _vsnprintf(cptr,sizeof(msg)- (cptr-msg)-2,format,arg_ptr);
		va_end(arg_ptr);
		if (i<0) break; cptr += i;

		i = sprintf(cptr," 0x%X - ",w32_ecode);
		if (i<0) break; cptr += i;

		i = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,w32_ecode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(msg)-(cptr-msg)-1,NULL);
		if (i<0) break; cptr += i;

		i = _snprintf(cptr,msg + sizeof(msg) - cptr-1,"\r\n");
		if (i<0) break; cptr += i;

		break;
	} 
	len = strlen(msg);
	if (m_ilog != NULL) m_ilog->Log(LOG_LERROR,file,line,msg);
	return Log_Write(retval,msg,len);
}

char* CLogClient::GetHeader(char *cstr, WORD size, WORD level, char *file, int line)
{
	SYSTEMTIME date;
	
	int		i;
	char	*cptr = cstr;
	char	*pchr;

	for (;;){
		//**********************************************************
		if (m_show_flag & LOG_SHOW_DATETIME) GetLocalTime(&date);

		if (m_show_flag & LOG_SHOW_DATE)
		{
			i = GetDateFormatA(LOCALE_SYSTEM_DEFAULT,0,&date,"yyyy/MM/dd",cptr,cstr + size - cptr-1);
			if (i==0) break;
			cptr += (i-1);
		}
		if (m_show_flag & LOG_SHOW_TIME)
		{
			i = GetTimeFormatA(NULL,TIME_FORCE24HOURFORMAT,&date," hh:mm:ss ",cptr,cstr + size - cptr-1);
			if (i==0) break; cptr += (i-1);
		}
		if (m_show_flag & LOG_SHOW_DATETIME) 
		{
			i = _snprintf(cptr,cstr + size - cptr-1,"\t"); 
			if (i<0) break; cptr += i;
		}
		//**********************************************************
		if (m_show_flag & LOG_SHOW_LEVEL)	
		{
			i = _snprintf(cptr,cstr + size - cptr-1,"%u\t",level);
			if (i<0) break; cptr += i;
		}
		//**********************************************************
		if (m_show_flag & LOG_SHOW_PID)
		{
			i = _snprintf(cptr,cstr + size - cptr-1,"P%08X\t",GetCurrentProcessId()); 
			if (i<0) break; cptr += i;
		}
		//**********************************************************
		if (m_show_flag & LOG_SHOW_THREAD)	 
		{
			i = _snprintf(cptr,cstr + size - cptr-1,"T%08X\t",::GetCurrentThreadId()); 
			if (i<0) break; cptr += i;
		}
		//**********************************************************
		if (m_show_flag & LOG_SHOW_FILE_NAME)	
		{
			// Se puede cojer solo el nombre del fichero
			pchr = strrchr(file,'\\');
			if (pchr != NULL) file = pchr + 1;
			i = _snprintf(cptr,cstr + size - cptr-1,"%s",file);
			if (i<0) break; cptr += i;
		}

		if (m_show_flag & LOG_SHOW_FILE_LINE)	
		{
			i = _snprintf(cptr,cstr + size - cptr-1,":%d",line);
			if (i<0) break; cptr += i;
		}

		/*
		if (m_show_flag & LOG_SHOW_FNC_NAME)	
		{
			i = _snprintf(cptr,cstr + size - cptr-1," %s",fnc);
			if (i<0) break; cptr += i;
		}
		*/
		
		if (m_show_flag & (LOG_SHOW_FILE_LINE|LOG_SHOW_FILE_NAME))
		{
			i = _snprintf(cptr,cstr + size - cptr-1,"\t"); 
			if (i<0) break; cptr += i;
		}
		//**********************************************************
		break;
	}
	return cptr;
}


DWORD CLogClient::Log_Write(DWORD retval, void *pBuffer, DWORD size)
{
	BOOL	br;
	DWORD	BytesWritten;

	// File Write
	if (m_hFile != INVALID_HANDLE_VALUE) {
		if (m_bAddEndFile) SetFilePointer(m_hFile,0,NULL,FILE_END);
		br = WriteFile(m_hFile,pBuffer,size,&BytesWritten,NULL);
		FlushFileBuffers(m_hFile);
	}
	// Console Write
	if (m_hStdOut != INVALID_HANDLE_VALUE) {	
		br = WriteFile(m_hStdOut,pBuffer,size,&BytesWritten,NULL);
	}
	/*
	// Memstack Write
	if ((m_bStack_Output))
	{
		Push((char*)pBuffer,size);		// se necesita el \r\n para que funcione el edit multiline
	}
	*/
	return retval;
}

BOOL CLogClient::IsActiveLogOutput()
{
	CheckEvents();
	if ((m_hFile == INVALID_HANDLE_VALUE) && 
		(m_hStdOut == INVALID_HANDLE_VALUE) && 
		(!m_bconsole_ouput) &&
		(m_ilog == NULL)) return false;
	return true;
}


CLogClient* CLogClient::get()
{
	static CLogClient	log;
	return &log;
}

BOOL CLogClient::getConsoleOutput()
{
	if (this) return m_bconsole_ouput;
	return false;
}
