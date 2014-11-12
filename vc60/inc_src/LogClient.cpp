// LogClient.cpp: implementation of the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#include "LogClient.h"
#include "stdio.h"
#include "utils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogClient	glog;

extern "C" 
{
	DWORD glog_log(char* str1,char* str2)
	{
		return glog.log_strings(LOG_LAST,str1,str2);
	}
	DWORD	glog_int(char* str1,int val)
	{
		return glog.log_uint(LOG_LAST,str1,val);
	}
}

#define LOGCONSEVENT	"Global\\logconsoleevent"	// Usado para activar la pantalla de consola
#define LOGFILEEVENT	"Global\\logfileevent"	// Usado para activar la pantalla de consola

CLogClient::CLogClient()
{
	//	Crear evento de disparo de la consola
	m_hFile			= INVALID_HANDLE_VALUE;
	m_hStdOut		= INVALID_HANDLE_VALUE;
	m_bDeleteStd	= FALSE;
	m_dwlasttime	= GetTickCount();
	m_bShowThread	= false;
	m_bAddEndFile	= false;
	m_bShowTime		= true;
	m_bShowPID		= false;
	m_log_level		= LOG_LAST;
	m_bCloseFile	= true;			// siempres se puede cerrar a menos que se cree sin el evento
	m_bconsole_ouput = false;
	m_logfnc = NULL;
	m_logfnc_prm = NULL;

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

DWORD CLogClient::CreateLogFile(char *lpName,BOOL bOpen)
{
	DWORD	dwr;
	DWORD	pid;
	DWORD	flags;
	DWORD	share;
	char name[256];
	char	pname[20];
	char	*cptr;
	name[0] = 0;
	pid = ::GetCurrentProcessId();

	/*
	sprintf(edata->batchrun_file,"/tmp/e9_%X_%04d%02d%02d_%02d%02d%02d",
    		_pid,newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec);

  SYSTEMTIME date;
		GetLocalTime(&date);
		//GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&date,"dd/MM/yyyy",SSIZE(fecha));
		GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&date,"yyyy/MM/dd",SSIZE(fecha));
		GetTimeFormat(NULL,TIME_FORCE24HOURFORMAT,&date," hh:mm:ss ",SSIZE(hora));
		cptr += sprintf(cptr,"%s%s\t",fecha,hora);
	*/

	if (lpName == NULL)
	{
		if (m_hFile != INVALID_HANDLE_VALUE) return 0;	// Ya esta creado el fichero
		GetModuleFileName(NULL,name,sizeof(name));
		cptr = gutils.File_GetName(name);
		*pname = 0;
		if (cptr != NULL) strncat(pname,cptr,sizeof(name));
		SYSTEMTIME date;
		GetLocalTime(&date);

		_snprintf(SSIZE(name),"c:\\log\\%s_%02d%02d_%X.log",pname,date.wMonth,date.wDay,GetTickCount());
		//_snprintf(SSIZE(name),"c:\\log\\P%X_%02d%02d_%02d%02d%02d.log",pid,date.wMonth,date.wDay,date.wHour,date.wMinute,date.wSecond)
		//_snprintf(SSIZE(name),"c:\\LOG\\PID_%X_%X.log",pid,m_file_sec);
	}
	else
		strncat(name,lpName,sizeof(name)-1);

	CloseFile();
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
	m_hFile = CreateFile(name,GENERIC_WRITE,share,NULL,flags,FILE_ATTRIBUTE_NORMAL,NULL);
	dwr = GetLastError();
	if (m_hFile == INVALID_HANDLE_VALUE) return ERR_FATAL;// {TRACE1("E: CreateFile Failed... Error %d",GetLastError());return 1;}
	m_bCloseFile = false;
	GetModuleFileName(NULL,name,sizeof(name));
	_log(LOG_ERROR,"%s::%X",name,pid);

	static const char * const version = "Build: " __DATE__ "-" __TIME__;
	_log(LOG_ERROR,"%s",version);

	// redireccionar al fichero el errio
	//if (SetStdHandle(STD_ERROR_HANDLE,m_hFile) == 0) _log(LOG_ERROR,"Failed to set STD_ERROR_HANDLE");

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

//DEL DWORD CLogClient::AddWin32ErrorMsg(DWORD dwerror)
//DEL {
//DEL 	char	msg[250];
//DEL 
//DEL 	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,dwerror,
//DEL 					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),msg,sizeof(msg),NULL);
//DEL 	return log_strings(LOG_ERROR,"Win32 Error Msg : ",msg);
//DEL }

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
			m_log_level = LOG_LAST;
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
			CreateLogFile();
			m_bCloseFile = true;
			m_log_level = LOG_LAST;
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
	m_hconsoleevent = CreateEvent(NULL,true,false,LOGCONSEVENT);
	m_hfileevent	= CreateEvent(NULL,true,false,LOGFILEEVENT);
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

DWORD CLogClient::ElapsedTime_Show(DWORD starttime)
{
	DWORD	time;
	WORD	day;
	WORD	hour;
	WORD	min;
	WORD	sec;
	WORD	msec;
	char	elapse[150];

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
	for(;;)
	{
		sprintf(elapse," %d days %d hours %d minutes %d seconds %d ms ",day,hour,min,sec,msec);
		if (day != 0) break;
		sprintf(elapse," %d hours %d minutes %d seconds %d ms ",hour,min,sec,msec);
		if (hour != 0) break;
		sprintf(elapse," %d minutes %d seconds %d ms ",min,sec,msec);
		if (min != 0) break;
		sprintf(elapse," %d seconds %d ms ",sec,msec);
		if (sec != 0) break;
		sprintf(elapse," %d ms ",msec);
		break;
	} 
	log_strings(LOG_ERROR,"Elapse : ",elapse);
	return ERR_OK;

}

DWORD CLogClient::ElapsedTime_Reset(DWORD *time)
{
	if (time == NULL)
		m_dwlasttime = GetTickCount();
	else
		*time = GetTickCount();
	log_strings(LOG_ERROR,"Start Time Count......0s");
	return ERR_OK;
}

DWORD CLogClient::EventsClose()
{
	if (m_hconsoleevent != NULL) CloseHandle(m_hconsoleevent);
	if (m_hfileevent != NULL) CloseHandle(m_hfileevent);
	m_hconsoleevent = NULL;
	m_hfileevent	= NULL;
	return ERR_OK;
}

//DEL char* CLogClient::GetFileName(char *file_path)
//DEL {
//DEL 	char*	file_name;
//DEL 	char*	cptr;
//DEL 	cptr = file_path;
//DEL 	for (;;)
//DEL 	{
//DEL 		file_name = cptr;
//DEL 		cptr = strstr(cptr,"\\");
//DEL 		if (cptr == NULL) break;
//DEL 		cptr++;
//DEL 	}
//DEL 	return file_name;	
//DEL }

//DEL DWORD CLogClient::Execute(char *exec_path, char *cm_line)
//DEL {
//DEL 	/*
//DEL 	DWORD				dr;
//DEL 	STARTUPINFO			si;
//DEL 	PROCESS_INFORMATION pi;
//DEL 
//DEL 	ZeroMemory( &si, sizeof(si));
//DEL 	si.cb = sizeof(si);
//DEL 	si.dwFlags  =STARTF_USESTDHANDLES;
//DEL 	si.hStdInput=NULL;
//DEL 	si.hStdOutput=NULL;
//DEL 	si.hStdError=NULL;
//DEL 	ZeroMemory( &pi, sizeof(pi));
//DEL 
//DEL 	char	cmd_line[300];
//DEL 	char	aux_path[MAX_PATH];
//DEL 	DWORD	pid = GetCurrentProcessId();
//DEL 	char	fileAct[MAX_PATH];
//DEL 
//DEL 	memset (cmd_line, 0, 300);
//DEL 	memset (aux_path, 0, 300);
//DEL 	
//DEL 	OSGetExecutableDirectory(fileAct);
//DEL 
//DEL 	// Busca el notes.ini y, en función del resultado se llama a ActualizaID con la ruta del ini o no
//DEL 	OSGetExecutableDirectory(m_iniPath);
//DEL 	strcat(m_iniPath,"\\notes.ini");
//DEL 	glog.log_strings(LOG_TRACE,"GetIniPath (m_iniPath) -> ", m_iniPath);
//DEL 	dr = ::GetFileAttributes(m_iniPath);
//DEL 	if (dr == -1) 
//DEL 	{ 
//DEL 		OSGetDataDirectory(m_iniPath);
//DEL 		strcat(m_iniPath,"\\notes.ini");
//DEL 		glog.log_strings(LOG_TRACE,"GetIniPath (m_iniPath) -> ", m_iniPath);
//DEL 		dr = ::GetFileAttributes(m_iniPath);
//DEL 		if (dr == -1)
//DEL 		{
//DEL 			// No se ha encontrado el Ini
//DEL 			glog.log_strings(LOG_TRACE,"GetIniPath -> notes.ini File not found : ",m_iniPath);
//DEL 		} else {
//DEL 			// El ini está en el directorio de datos--> se llama al actualizaID con este path
//DEL 			aux_path[0] = '=';
//DEL 			strcat(aux_path, m_iniPath);
//DEL 			glog.log_strings(LOG_TRACE,"GetIniPath (m_iniPath) -> ", aux_path);
//DEL 			sprintf(cmd_line,"\"%sActualizaID.exe\" -a %s -cid %d -pid %d -u %s -f \"%s\" -s \"%s\" -i \"%s\"",fileAct,action,m_user_conf.delete_id,pid,m_userid,m_idFilePath,m_server,aux_path);
//DEL 			
//DEL 		}
//DEL 	} else {
//DEL 		sprintf(cmd_line,"\"%sActualizaID.exe\" -a %s -cid %d -pid %d -u %s -f \"%s\" -s \"%s\"",fileAct,action,m_user_conf.delete_id,pid,m_userid,m_idFilePath,m_server);
//DEL 	}
//DEL 	
//DEL 	glog.log_strings(LOG_TRACE,"Launch -> ",cmd_line);
//DEL 	if (cmd_line[0] != NULL) {
//DEL 		dr = CreateProcess(NULL,cmd_line,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,fileAct,&si,&pi);
//DEL 		if (dr) glog.log_strings(LOG_TRACE,"ActualizarID -> Actualizar ID running ...");
//DEL 		else
//DEL 		{
//DEL 			glog.log_strings(LOG_ERROR,"ActualizarID -> Failed.. to Launch ActualizarID");
//DEL 			glog.AddWin32ErrorMsg(GetLastError());
//DEL 		}
//DEL 	}
//DEL 	m_iniPath[0] = 0;
//DEL 	return ERR_OK;
//DEL 	*/
//DEL 	return ERR_OK;
//DEL }

//DEL DWORD CLogClient::AddSystemError(DWORD error, char *msg)
//DEL {
//DEL 	char	sys_msg[250];
//DEL 
//DEL 	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,error,
//DEL 					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),sys_msg,sizeof(sys_msg),NULL);
//DEL 	return log_strings(LOG_ERROR,msg," System Error Msg : ",sys_msg);
//DEL }

//DEL void CLogClient::Big_Div_8(BYTE *dividend, BYTE dsize, BYTE divisor, BYTE *quotient, BYTE *remainder)
//DEL {
//DEL 	BYTE	num_size;
//DEL 	BYTE	reminder;
//DEL 	memset(quotient,0,dsize);
//DEL 
//DEL 	_asm
//DEL 	{
//DEL 		mov dh,0;
//DEL 		xor ecx,ecx;
//DEL 		mov cl,dsize;
//DEL 		mov eax,dividend;
//DEL 		mov dl,0;
//DEL loop_0:
//DEL 		cmp [eax],byte ptr 0;
//DEL 		je nxt_0;
//DEL 		mov dh,dl;
//DEL nxt_0:
//DEL 		inc eax;
//DEL 		inc dl;
//DEL 		loop loop_0;
//DEL 		inc dh;
//DEL 		mov num_size,dh	//cantidad de bytes validos * 8 cantidad de bits
//DEL 		mov al,8;
//DEL 		mul dh;
//DEL 		mov cx,ax		// tamaño en bits del numero	
//DEL 		mov bl,divisor	//divisor
//DEL 		mov bh,0	// reminder
//DEL loop_1:
//DEL 		// rotar el dividendo y pasar el bit al reminder
//DEL 		clc;
//DEL 		mov eax,dividend;
//DEL 		call rot_19;
//DEL 		rcl bh,1;
//DEL 		// comparar los numeros
//DEL 		cmp bh,bl;
//DEL 		jb menor;
//DEL 		sub bh,bl;
//DEL 		stc;
//DEL 		jmp rotar
//DEL menor:
//DEL 		clc;
//DEL rotar:		
//DEL 		mov eax,quotient;
//DEL 		call rot_19;
//DEL 		loop loop_1;
//DEL 		jmp end_;
//DEL 
//DEL rot_19:	//rotar los dl numeros apuntados por eax a traves del CF
//DEL 		push cx;
//DEL 		mov ecx,0
//DEL 		mov cl,num_size;
//DEL l_1:
//DEL 		rcl byte ptr [eax],1;
//DEL 		inc eax;
//DEL 		loop l_1;
//DEL 		pop cx;
//DEL 		ret;
//DEL end_:
//DEL 		mov reminder,bh;
//DEL 	}
//DEL 	*remainder = reminder;	
//DEL 
//DEL }

//DEL void CLogClient::Big_GetDecimal(BYTE *number, BYTE dsize, char *decimal, BYTE max)
//DEL {
//DEL 	BYTE is0;
//DEL 	BYTE res[20];
//DEL 	BYTE resto;
//DEL 	char str[40];
//DEL 	int	i,k;
//DEL 	k = 0;
//DEL 	if (dsize > sizeof(res)) dsize = sizeof(res);
//DEL 	do
//DEL 	{
//DEL 		Big_Div_8(number,dsize,10,res,&resto);
//DEL 		str[k] = resto+0x30;
//DEL 		k++;
//DEL 		if (k == sizeof(str)) break;
//DEL 	_asm{
//DEL 		lea eax,[res];
//DEL 		mov ecx,0
//DEL 		mov cl,dsize;
//DEL 		mov bh,0;
//DEL lp_1:
//DEL 		or bh,[eax];
//DEL 		inc eax;
//DEL 		loop lp_1;
//DEL 		mov is0,bh;		
//DEL 	}
//DEL 		memcpy(number,res,dsize);
//DEL 	} while (is0 != 0);
//DEL 	i = 0;
//DEL 	
//DEL 	while (k>0)
//DEL 	{
//DEL 		k--;
//DEL 		decimal[i] = str[k];
//DEL 		i++;
//DEL 		if (i == max-1) break;
//DEL 		
//DEL 	}
//DEL 	decimal[i] = 0;
//DEL }

//DEL void CLogClient::Big_HEX_to_Number(char* hex_num,BYTE* number, BYTE max)
//DEL {
//DEL 	char	*cptr;
//DEL 	BYTE	val;
//DEL 	int		i,j;
//DEL 
//DEL 	memset(number,0,max);
//DEL 	i = strlen(hex_num);
//DEL 	i--;
//DEL 	j = 0;
//DEL 	cptr = hex_num;
//DEL 	while (i >= 0)
//DEL 	{
//DEL 		val = hex_num[i] - 0x30;
//DEL 		if (val > 9) val = hex_num[i] - 'A'+10;
//DEL 		if (val > 15) return;	// error en el caracter recivido se aborta
//DEL 		number[j] = val;
//DEL 		i--; 
//DEL 		if (i < 0) break;
//DEL 		val = hex_num[i] - 0x30;
//DEL 		if (val > 9) val = hex_num[i] - 'A'+10;
//DEL 		if (val > 15) return;	// error en el caracter recivido se aborta
//DEL 		number[j] = number[j] + val*16;
//DEL 		i--;
//DEL 		j++;
//DEL 	}
//DEL }

DWORD CLogClient::_log(int level,char *format,...)
{
	va_list arg_ptr;
	if (level > m_log_level) return ERR_OK;
	
	CheckEvents();
	if ((m_hFile == INVALID_HANDLE_VALUE) && 
		(m_hStdOut == INVALID_HANDLE_VALUE) && 
		(!m_bconsole_ouput) &&
		(m_logfnc == NULL)) return ERR_OK;

	char	fecha[50];
	char	hora[50];
	char	msg[2048];
	char	*cptr;

	fecha[0] = 0;
	hora[0] = 0;
	
	DWORD	len;
	DWORD	BytesWritten;
	BOOL	br;

	cptr = msg;

	// sample T0000246A 01/03/2007 02:56:45 Error opening file "c:\pepe"
	if (m_bShowPID) cptr += sprintf(cptr,"P%08X\t",GetCurrentProcessId());
	if (m_bShowTime)
	{
		SYSTEMTIME date;
		GetLocalTime(&date);
		GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&date,"yyyy/MM/dd",SSIZE(fecha));
		GetTimeFormat(NULL,TIME_FORCE24HOURFORMAT,&date," hh:mm:ss ",SSIZE(hora));
		cptr += sprintf(cptr,"%s%s\t",fecha,hora);
	}
	if (m_bShowThread) cptr+= sprintf(cptr,"T%08X\t",::GetCurrentThreadId());
	cptr+= sprintf(cptr,"%u\t",level);

	va_start(arg_ptr, format);
	cptr+= _vsnprintf(cptr,sizeof(msg)- (cptr-msg-2),format,arg_ptr);
	va_end(arg_ptr);
	cptr += sprintf(cptr,"\r\n");

	len = strlen(msg);
	if (m_hFile != INVALID_HANDLE_VALUE)	
	{
		if (m_bAddEndFile) SetFilePointer(m_hFile,0,NULL,FILE_END);
		br = WriteFile(m_hFile,msg,len,&BytesWritten,NULL);
		FlushFileBuffers(m_hFile);
	}
	if (m_hStdOut != INVALID_HANDLE_VALUE)	
		br = WriteFile(m_hStdOut,msg,len,&BytesWritten,NULL);
	//if (m_logfnc != NULL);

	/*
	else
		if (m_bconsole_ouput) fputs(msg,stdout);
	*/
	return ERR_FATAL;
};

BSTR CLogClient::GetBSTR(char* str)
{
	BSTR	bstr;
	if (str[0] == 0) return NULL;
	int	i;
	int	len = strlen(str);
	bstr = SysAllocStringByteLen(NULL,(len)*2);
	if (bstr == NULL) return NULL;
	i = MultiByteToWideChar(CP_ACP,0,str,len,bstr,len);
	if (i == len) return bstr;
	glog.log_strings(LOG_ERROR,"FATAL ERROR :: MultiByteToWideChar Failed");
	SysFreeString(bstr);
	return NULL;
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

//DEL void CLogClient::GetChar(unsigned short *u_str,char* str,int maxsize,int u_size)
//DEL {
//DEL 	int	i;
//DEL 	str[0] = 0;
//DEL 	if (u_str == NULL) return;
//DEL 	i = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)u_str,u_size,str,maxsize,NULL,NULL);
//DEL 	if ((i == 0) || (i ==  maxsize))
//DEL 	{
//DEL 		_snprintf(str,maxsize,"##TRUNCATE##");
//DEL 		glog.log_strings(LOG_ERROR,"FATAL ERROR :: WideCharToMultiByte string has been trunqued");
//DEL 		return;
//DEL 	}
//DEL 	if (u_size != -1) str[i] = 0;	// si se especifica el tamaño del string entonces hay que poner el cero
//DEL }

//DEL void CLogClient::GetChar_FreeBSTR(BSTR bstr,char* str,int maxsize)
//DEL {
//DEL 	GetChar((unsigned short *)bstr,str,maxsize,SysStringLen(bstr));
//DEL 	SysFreeString(bstr);
//DEL }

void CLogClient::SetConsoleOutput(BOOL status)
{
	m_bconsole_ouput = status; 
	if (status) 
		OpenConsole(); 
	else 
		CloseConsole();
};

//DEL DWORD CLogClient::log_Add_W32_code_msg(int level, DWORD w32_ecode, char *format, ...)
//DEL {
//DEL 	char	*cptr;
//DEL 	char	tmp_msg[1024];
//DEL 
//DEL 	va_list arg_ptr;
//DEL 
//DEL 	va_start(arg_ptr, format);
//DEL 	cptr = tmp_msg;
//DEL 	cptr += _vsnprintf(cptr,sizeof(tmp_msg)-(tmp_msg-cptr),format,arg_ptr);
//DEL 	va_end(arg_ptr);
//DEL 
//DEL 	cptr += sprintf(cptr," 0x%X - ",w32_ecode);
//DEL 
//DEL 	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,NULL,w32_ecode,
//DEL 					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),cptr,sizeof(tmp_msg)-(cptr-tmp_msg),NULL);
//DEL 	_log(level,"%s",tmp_msg);
//DEL 	return ERR_OK;
//DEL }


	

DWORD CLogClient::log_buffer(int level, byte *buffer, WORD size, byte width, byte base, char separator, bool browpos)
{
	int		i;
	int		col;
	int		row;
	char	msg[2048];
	char	*cptr;

	DWORD	len;
	DWORD	BytesWritten;
	BOOL	br;

	if (level > m_log_level) return ERR_FATAL;

	CheckEvents();
	if ((m_hFile == INVALID_HANDLE_VALUE) && 
		(m_hStdOut == INVALID_HANDLE_VALUE) && 
		(!m_bconsole_ouput) &&
		(m_logfnc == NULL)) return ERR_FATAL;

	_log(level,"Showing %d bytes of data",size); 
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
			if (m_hFile != INVALID_HANDLE_VALUE)	
			{
				if (m_bAddEndFile) SetFilePointer(m_hFile,0,NULL,FILE_END);
				br = WriteFile(m_hFile,msg,len,&BytesWritten,NULL);
				FlushFileBuffers(m_hFile);
			}
			if (m_hStdOut != INVALID_HANDLE_VALUE)	
				br = WriteFile(m_hStdOut,msg,len,&BytesWritten,NULL);
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
