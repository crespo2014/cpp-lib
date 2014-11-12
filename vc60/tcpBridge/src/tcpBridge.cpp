// tcpBridge.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdarg.h>
#include "Winsock2.h"

// para poder compilar en visual estudio 6.0
#ifdef WIN32
	#define snprintf	_snprintf
	#define vsnprintf	_vsnprintf
	#define getpid		_getpid
	#define popen		_popen
	#define pclose		_pclose
	//#include "windows.h"
	#include <process.h>
#else
	
#endif

/*
	Definiciones de estructuras
*/

#define MAX_LISTEN_SOCK 10

// niveles de log disponibles
#define LOG_NONE	0
#define LOG_ERROR	1
#define LOG_WARNING	2
#define	LOG_DATA	3
#define LOG_TRACE	4
#define LOG_DEBUG	5

#define ERR_OK			0
#define ERR_FATAL		1
#define ERR_EOF			2
#define ERR_NOT_FOUND	3

#define CNF_TYP_NONE	0	// nada
#define CNF_TYP_MAIN	1	// se esta procesando la configuracion general
#define CNF_TYP_FPORT	2	// se esta procesando un puerto de forward

#define CNF_SEC_MAIN	"MAIN"
#define CNF_SEC_FPORT	"TCP_FORWARD_PORT"

// parametros disponibles
#define PRM_LOG_FILE			"LOG_FILE"
#define PRM_LOG_LEVEL			"LOG_LEVEL"
#define PRM_LOG_CONSOLE			"LOG_CONSOLE"
#define PRM_TCP_CMD_PORT		"TCP_CMD_PORT"	//si 1 indica que los ficheros de ejecucion de los batchrun deben eliminarse
#define PRM_CMD_ALLOWED_HOST	"ALLOWED_HOST"	// carpeta donde almacenar los ficheros de ejecucion de los batchrun


struct S_ERR_MSG
{
	union {	
		int		icode;
		DWORD	dwcode;
	};
	char	*msg;
};

struct S_ERR_MSG C_SOCK_ERR[] = {
	{ WSANOTINITIALISED	,"A successful WSAStartup call must occur before using this function."},
	{ WSAENETDOWN		,"The network subsystem or the associated service provider has failed."},
	{ WSAEAFNOSUPPORT	,"The specified address family is not supported."},
	{ WSAEINPROGRESS	,"A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. "},
	{ WSAEMFILE			,"No more socket descriptors are available. "},
	{ WSAENOBUFS		,"No buffer space is available. The socket cannot be created. "},
	{ WSAEPROTONOSUPPORT,"The specified protocol is not supported. "},
	{ WSAEPROTOTYPE		,"The specified protocol is the wrong type for this socket. "},
	{ WSAESOCKTNOSUPPORT,"The specified socket type is not supported in this address family."},
	{ WSAEACCES			,"The requested address is a broadcast address, but the appropriate flag was not set. Call setsockopt with the SO_BROADCAST parameter to allow the use of the broadcast address. "},
	{ WSAEADDRINUSE		,"A process on the machine is already bound to the same fully-qualified address and the socket has not been marked to allow address reuse with SO_REUSEADDR. For example, the IP address and port are bound in the af_inet case). (See the SO_REUSEADDR socket option under setsockopt.) "},
	{ WSAEADDRNOTAVAIL	,"The specified address is not a valid address for this machine. "},
	{ WSAEFAULT			,"The name or namelen parameter is not a valid part of the user address space, the namelen parameter is too small, the name parameter contains an incorrect address format for the associated address family, or the first two bytes of the memory block specified by name does not match the address family associated with the socket descriptor s. "},
	{ WSAEINPROGRESS	,"A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function. "},
	{ WSAEINVAL			,"The socket is already bound to an address. "},
	{ WSAENOBUFS		,"Not enough buffers available, too many connections. "},
	{ WSAENOTSOCK		,"The descriptor is not a socket. "},
	{ WSAENETRESET		,"The connection has been broken due to the keep-alive activity detecting a failure while the operation was in progress."},
	/*
WSAEINTR A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall. 
WSAENOTCONN The socket is not connected. 
WSAESHUTDOWN The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH. 
WSAEWOULDBLOCK The socket is marked as nonblocking and the requested operation would block. 
WSAEMSGSIZE The socket is message oriented, and the message is larger than the maximum supported by the underlying transport. 
WSAEHOSTUNREACH The remote host cannot be reached from this host at this time. 
WSAEINVAL The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled. 
WSAECONNABORTED The virtual circuit was terminated due to a time-out or other failure. The application should close the socket as it is no longer usable. 
WSAECONNRESET The virtual circuit was reset by the remote side executing a hard or abortive close. For UPD sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a "Port Unreachable" ICMP packet. The application should close the socket as it is no longer usable. 
WSAETIMEDOUT The connection has been dropped, because of a network failure or because the system on the other end went down without notice. 
*/
	{0,NULL}};

/*
	Estructura para el tratamiento de la memoria como un stack
*/
struct S_MEM_STACK
{
	int		binit;
	char	*wptr;
	DWORD	maxlen;
	char	data[1];
};

struct S_BRIDGE_CNF
{
	int	src_ip;
	int	src_port;
	int	dest_ip;
	int	dest_port;
	struct S_BRIDGE_CNF	*next;
};

struct	S_APP_CONF		// parametros de la aplicacion
{
	int		init;			// indica que la estructura esta incializada y todos los parametros cargados
	int		ilog_level;
	int		ilog_console;
	int		icmd_port;
	char	*log_file;
	char	*allowed_host;
	int		iallowed_host_count;
	struct S_BRIDGE_CNF	*first_bridge_cnf;
	union
	{
		struct S_MEM_STACK	stack;
		char	stack_data[2000];			// max 2Kbytes of configuration file
	};
};

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


struct S_SOCKET
{
	int	binit;								// indica que la estructura es valida
	int	handle;
	struct sockaddr_in lsn_sock_addr;	// datos de la conecion de escucha
	struct sockaddr_in sock_addr;		// datos de la conecion de salida
	//int	src_ip;
	//int	port;
	DWORD	flags;
	unsigned long	recv_bytes;				// datos recibidos en el socket
	unsigned long	send_bytes;				// datos enviados por el socket
	
	unsigned char	*wr_buffer;			// buffer de escritura  2-->1	aqui escribe el socket 2 o servidor
	unsigned char	*rd_buffer;			// buffer de lectura	1-->2	aqui escribe el socket 1 o cliente
	int		wr_size;					// tamaño del buffer de escritura
	int		rd_size;					// tamaño del buffer de lectura

	int		*pwr_start;					// posicion de inicio de los bytes a enviar
	int		*pwr_end;					// ultimo byte a enviar
	int		*prd_start;					// primer byte leido del buffer 
	int		*prd_end;					// byte precediendo la ultimo leido o posicion de la proxima lectura max = size

	struct S_SOCKET	*next;				// usado en listas
	struct S_SOCKET	*bridge;			// socket puente
};

/*
struct S_BRIDGE_CONN
{
	int		binit;

	unsigned char	wr_buffer[200];			// buffer de escritura  2-->1	aqui escribe el socket 2 o servidor
	unsigned char	rd_buffer[200];			// buffer de lectura	1-->2	aqui escribe el socket 1 o cliente

	struct S_SOCKET		src_socket;
	struct S_SOCKET		dest_socket;
	struct S_BRIDGE_CONN		*next;
};

struct S_CMD_CONN			// cliente conectado por el puerto de comandos
{
	int		binit;			// indica que el cliente esta activo o inicializado
	struct S_SOCKET	socket;
	unsigned char	wr_buffer[200];			
	unsigned char	rd_buffer[200];	
};
*/

#define CONN_TYP_CMD	1
#define CONN_TYP_BRIDGE	2

struct S_CONNECTION						// estrutura de conecion que abarca todas las coneciones posibles
{
	int	binit;							// la estrutura esta activa e inicializada
	int	conn_type;						// tipo de conecion, puede ser conecion puente o de comando

	int	wr_start;						// posicion de inicio de los bytes a enviar
	int	wr_end;							// ultimo byte a enviar
	int	rd_start;						// primer byte leido del buffer 
	int	rd_end;							// byte precediendo la ultimo leido o posicion de la proxima lectura max = size

	struct S_SOCKET	src_socket;			// conecion establecida por listener o connect
	struct S_SOCKET	dest_socket;		// usado por el bridge
	unsigned char	wr_buffer[200];		// buffer de escritura  2-->1	aqui escribe el socket 2 o servidor
	unsigned char	rd_buffer[200];		// buffer de lectura	1-->2	aqui escribe el socket 1 o cliente

	struct S_CONNECTION	*next;			// lista de conexiones dinamica
};

struct S_LISTEN_SOCKET
{
	int	handle;
	struct sockaddr_in sock_addr;
};

struct	S_APP_DATA
{
	// Datos generales de la aplicacion 
	struct S_APP_CONF		conf;
	struct S_CONNECTION		*first_conn;		// primera conexion disponible
	struct S_LISTEN_SOCKET	listen_sock[MAX_LISTEN_SOCK];		// sockets de escucha para el comando y los sockets puente
	//struct sockaddr_in		bridge_srv;
	struct in_addr			srv_addr;
	char	srv_ip[20];

	int	listen_sock_count;
	union
	{
		struct S_MEM_STACK	app_stack;
		char	app_stack_data[4000];		// max 4000 of dinamy located data
	};
};

struct	S_APP_DATA	g_app_data;

static int			g_bcnf_load = 0;
static const char	*build = "Build: " __DATE__ "-" __TIME__;


DWORD _log(int nivel,const char * fmt, ...)
{
	FILE 	*file;
	char	*cptr;
	char	log_str[1024];	// se utiliza para el nombre del fichero al inicio y luego se escribe la cadena a tracear
	int		ppid;
	
	struct tm 	*newtime;
    time_t 		long_time;
	va_list 	arg_ptr;

	if ((g_app_data.conf.log_file == NULL) || (*g_app_data.conf.log_file == 0)) return 1;
	if (nivel > g_app_data.conf.ilog_level) return ERR_FATAL;
	
	file = fopen(g_app_data.conf.log_file,"a"); 
	if (file == NULL)
	{
		puts(build);
		puts(" failed to open log file\n");
		return ERR_FATAL;
	}
		
	time( &long_time );
    newtime = localtime( &long_time );
    ppid = getpid();		

	cptr = log_str;
	cptr += snprintf(cptr,sizeof(log_str) - (cptr-log_str)-1,"P%.8X\t",ppid);
	cptr += snprintf(cptr,sizeof(log_str) - (cptr-log_str)-1,"%04d/%02d/%02d %02d:%02d:%02d\t"
			,newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec);
	cptr += snprintf(cptr,sizeof(log_str) - (cptr-log_str)-1,"%u\t",nivel);
	va_start(arg_ptr, fmt);
    cptr += vsnprintf(cptr,sizeof(log_str) - (cptr-log_str)-1,fmt,arg_ptr);
    va_end(arg_ptr);
    cptr += sprintf(cptr,"\n");
    fputs(log_str,file);
    fclose(file); 
    if (g_app_data.conf.ilog_console == 1) 
	{
		cptr[-1] = 0;
		puts(log_str);		// salida por consola solo para depuracion
	}
    return ERR_FATAL;
}

DWORD	Socket_Error_Log(struct S_APP_DATA* data,int ecode,char* fmt, ...)
{
	char	err_str[500];
	char	*cptr;
	int		i;
	va_list arg_ptr;

	cptr = err_str;
	
	va_start(arg_ptr, fmt);
    cptr += vsnprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,fmt,arg_ptr);
    va_end(arg_ptr);
    
    cptr += snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1," failed with code = %d ",ecode); 
	for (i=0;C_SOCK_ERR[i].msg != NULL;i++)
	{
		if (C_SOCK_ERR[i].icode == ecode) 
		{
			cptr += snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,"%s",C_SOCK_ERR[i].msg);
			break;
		}
	}
	if (C_SOCK_ERR[i].msg == NULL) cptr += snprintf(cptr,sizeof(err_str) - (cptr-err_str)-1,"Unknown error ");
	return _log(LOG_ERROR,"%s",err_str);
	//return ERR_OK;
}

void string_upper(char* str)
{
	char	*cptr;
	cptr = str;
	while (*cptr != 0)
	{
		*cptr = toupper(*cptr);
		cptr++;
	}
}

void str_lower(char *str)
{
	for (;*str!= 0;str++) *str = tolower(*str);
}

void clr_ctrl_chars(char *str)
{
	for (;((*str != 0) && (*str >= ' '));str++);
	*str = 0;
};

DWORD	MemStack_Init(struct S_MEM_STACK* mstack,int size)
{
//	char	*fnc_name = "MemStack_Init";
	
	//_log(LOG_DEBUG,"%s Start size = %d",fnc_name,size);
	mstack->binit = 1;
	mstack->wptr = mstack->data;
	mstack->maxlen = size - sizeof(struct S_MEM_STACK);
	return ERR_OK;
}

DWORD	MemStack_Get(struct S_MEM_STACK* mstack,int size,void** ppBuffer,int align32,struct S_APP_DATA* data)
{
	// hay que alinear la memoria antes de devolverla, porque el uso de caracteres al final de una estructura 
	// genera desalineaciones y eso da problemas con algunas funciones numericas que no pueden escribir 
	// numeros de 32 bits desalineados
	int	align;
	char	*fnc_name = "MemStack_Get";
	
	_log(LOG_DEBUG,"%s Start size = %d, Remained = %d",fnc_name,size,(mstack->data + mstack->maxlen)-mstack->wptr);

	if (align32 != 0)
	{
		align = ((int)mstack->wptr) % 4;
		mstack->wptr += (4 - align);	
	}
	if (mstack->wptr + size > mstack->data + mstack->maxlen)  
		return _log(LOG_ERROR,"%s Buffer overflow, run time error ",fnc_name);
	*ppBuffer = mstack->wptr;
	memset(mstack->wptr,0,size);
	mstack->wptr += size;
	return ERR_OK;
}

DWORD	MemStack_Add(struct S_MEM_STACK* mstack,void* obj,int len,void** ppBuffer,struct S_APP_DATA* data)
{
	if (MemStack_Get(mstack,len,(void**)ppBuffer,1,data) != ERR_OK) return ERR_FATAL;
	memcpy(*ppBuffer,obj,len);
	return ERR_OK;
}


DWORD	MemStack_AddString(struct S_MEM_STACK* mstack,char* str,int len,char** ppBuffer,struct S_APP_DATA* data)
{
	char	*cptr;
	if (len == 0) len = strlen(str);
	if (MemStack_Get(mstack,len+1,(void**)ppBuffer,0,data) != ERR_OK) return ERR_FATAL;
	cptr = *ppBuffer;
	if (str != NULL) 
	{
		memcpy(cptr,str,len);
		cptr[len] = 0;
	}
	return ERR_OK;
}

int conf_add_forward_port(char* cnf_line,struct S_APP_DATA* app)
{
	struct S_BRIDGE_CNF	bridge_conf;
	struct S_BRIDGE_CNF	**ppbridge_conf;
	struct S_BRIDGE_CNF	*pbridge_conf;

	char	*fnc_name = "conf_add_forward_port";
	char	*cptr;
	char	*src_ip,*src_port;
	char	*dest_ip,*dest_port;

	src_ip = cnf_line;
	cptr = strchr(cnf_line,':'); if (cptr == NULL) return _log(LOG_ERROR,"%s invalid line (%s)",fnc_name,cnf_line);
	*cptr++ = 0;
	src_port = cptr;
	cptr = strchr(cptr,';'); if (cptr == NULL) return _log(LOG_ERROR,"%s invalid line (%s)",fnc_name,cnf_line);
	*cptr++ = 0;
	dest_ip = cptr;
	cptr = strchr(cptr,':'); if (cptr == NULL) return _log(LOG_ERROR,"%s invalid line (%s)",fnc_name,cnf_line);
	*cptr++ = 0;
	dest_port = cptr;
	
	memset(&bridge_conf,0,sizeof(bridge_conf));
	/*
	bridge_conf.next = NULL;
	bridge_conf.dest_ip = 0;
	bridge_conf.src_ip = 0;
	*/
	if (sscanf(src_port,"%d" ,&bridge_conf.src_port ) != 1) return _log(LOG_ERROR,"%s invalid port (%s)",fnc_name,src_port);
	if (sscanf(dest_port,"%d",&bridge_conf.dest_port) != 1) return _log(LOG_ERROR,"%s invalid port (%s)",fnc_name,dest_port);
	
	if (MemStack_Add(&app->conf.stack,&bridge_conf,sizeof(bridge_conf),(void**)&pbridge_conf,app) != ERR_OK) return _log(LOG_ERROR,"%s ERR: No memory",fnc_name);

	ppbridge_conf = &app->conf.first_bridge_cnf;
	while (*ppbridge_conf != NULL) ppbridge_conf = &(*ppbridge_conf)->next;
	*ppbridge_conf = pbridge_conf;
	return ERR_OK;
}

int	conf_load(char* file_path,struct S_APP_DATA* app)		// se carga todo el fichero de parametros en la memoria
{   
	/*
		formato del fichero
		[xxx]		- inicio de secion **** el ] no es obligatorio
		key=val		- key : debe comenzar con un caracter alfanumerico, puede haer espacios o TAB antes de y depues del =
					-		no puede contener espacios no caracteres <32 en el nombre
					- val : solo puede contener caracteres validos ascii >32
					- No usar " para delimitar nada, pues seran tratadas como parte del valor 
	*/
    
	struct	
	{
		char	*key;
		char	**value;		
	}keys[] = {		
		{PRM_LOG_FILE  				,&app->conf.log_file	},
		{PRM_LOG_LEVEL				,NULL				},
		{PRM_LOG_CONSOLE			,NULL				},
		{PRM_TCP_CMD_PORT			,NULL				},
		{PRM_CMD_ALLOWED_HOST		,&app->conf.allowed_host },
		{NULL,NULL}
		};
		
	FILE	*hfile;
	char	*fnc_name = "conf_load";
	static char	line[400];
	int		cnf_type;
	char	*cptr;			// posicion que se esta tratando
	char	key[50];		// parametro que se esta tratando
	char	*val;
	int		i;
	char	*sptr1,*sptr2;
		
	if (app->conf.init == 1) return ERR_OK;
	_log(LOG_DEBUG,"%s Start",fnc_name);

	memset(&app->conf,0,sizeof(app->conf));		//todos los punteros a null y los parametros a cero
	if (MemStack_Init(&app->conf.stack,sizeof(app->conf.stack_data)) != ERR_OK) return ERR_FATAL;
	
	hfile = fopen(file_path,"r"); 
	if (hfile == NULL)  return _log(LOG_ERROR,"%s failed to open %s",fnc_name,file_path);

  	//for (i=0;keys[i].key != NULL;i++) *(keys[i].value) = NULL;		// NULL para todos los parametros

    g_bcnf_load = 1;
	cnf_type = CNF_TYP_NONE;

  	while(fgets(line,sizeof(line),hfile) != NULL)
  	{
		cptr = line;
		for(;(*cptr != 0)&& (*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
		if (cptr[0] == '[')
		{
			// inicio de seccion
			cptr++;
			sptr1 = strchr(cptr,']');
			if (sptr1 == NULL) 
				for (sptr1=cptr;*sptr1 >= ' ';sptr1++);
			*sptr1 = 0;
			if (strcmp(cptr,CNF_SEC_MAIN) == 0)
			{
				cnf_type = CNF_TYP_MAIN;
				continue;
			}
			if (strcmp(cptr,CNF_SEC_FPORT) == 0)
			{
				cnf_type = CNF_TYP_FPORT;
				continue;
			}
				
			cnf_type = CNF_TYP_NONE;
			_log(LOG_ERROR,"%s invalid section name '%s'",fnc_name,cptr);
			continue;
		}
		if (cnf_type == CNF_TYP_FPORT)
		{
			clr_ctrl_chars(line);
			if (*line != 0) conf_add_forward_port(line,app);
		}
		if (!isalpha((int)line[0]) ) continue;	// comentario
		if (cnf_type == CNF_TYP_NONE) _log(LOG_ERROR,"%s - this line is out of section, line = %s ",fnc_name,line);
		
		sptr2 = cptr;
		cptr = strchr(cptr,'=');if (cptr == NULL) continue;	// si no hay = esta mal
		*cptr = 0;cptr++;
		for (sptr1 = sptr2;*sptr1 != 0;sptr1++)
			if (*sptr1<=32) *sptr1=0;			// ignorar espacios y caracteres no validos en key
		*key = 0;
		strncat(key,sptr2,sizeof(key)-1);
		string_upper(key);

		for(;((*cptr <= ' ') &&(*cptr != 0));cptr++);						//ignorar espacios y caracteres no validos antes del valor
		if (*cptr == '\"') cptr++;
		val = cptr;
		for (;*cptr >= ' ';cptr++);*cptr = 0;	// solo caracteres >=32 para el valor
		for (i=0;keys[i].key != NULL;i++)
		{
			if (strcmp(keys[i].key,key) == 0) break;
		}
		if (keys[i].key == NULL)	
		{
			_log(LOG_ERROR,"%s %s = %s .... ignored",fnc_name,key,val);
			continue;
		}
		//else						_log(LOG_ERROR,fnc_name,"%s = %s .... accepted",key,*(keys[i].value));
		if (keys[i].value != NULL)	//almacenar el valor de la keyword
		{
			if (MemStack_AddString(&app->conf.stack,val,0,&(*keys[i].value),app) != ERR_OK)	return _log(LOG_ERROR,"%s constant value es too long",fnc_name);
			//*(keys[i].value) = (char*)pvoid;
			continue;
		}
		// llegado a este punto se obtiene un valor de keyword que debe ser procesado y no almacenarse
		// es el caso de los parametros numericos o listas
		if (strcmp(key,PRM_LOG_CONSOLE) == 0)
		{
			if (*val == '1') app->conf.ilog_console = 1;
			continue;		
		}
		if (strcmp(key,PRM_LOG_LEVEL) == 0)
		{
			sscanf(val,"%d",&app->conf.ilog_level);
			continue;
		}
		if (strcmp(key,PRM_TCP_CMD_PORT) == 0)
		{
			sscanf(val,"%d",&app->conf.icmd_port);
			continue;
		}
		_log(LOG_ERROR,"%s %s = %s .... ignored",fnc_name,key,val);
		
	}
	fclose(hfile);

	//_log(LOG_ERROR,fnc_name,"All file has process");
	_log(LOG_DATA,"KEY %s  = %d",PRM_LOG_CONSOLE,app->conf.ilog_console);
	_log(LOG_DATA,"KEY %s  = %d",PRM_LOG_LEVEL,app->conf.ilog_level);
	_log(LOG_DATA,"KEY %s  = %d",PRM_TCP_CMD_PORT,app->conf.icmd_port);

	for (i=0;keys[i].key != NULL;i++)
	{ 
		if (keys[i].value == NULL) continue;	//esta keyword no se puede tratar
		if (*(keys[i].value) == NULL) 
		{
			_log(LOG_ERROR,"KEY %s .... not found",keys[i].key);
			*(keys[i].value) = "";
		}
		else 
			_log(LOG_DATA,"KEY %s  = %s",keys[i].key,*(keys[i].value));
	}
    
	return ERR_OK;
}

/*
	Realiza la lectura de datos de un socket,
	la lectura no es obligatoria, y se debe realizar simpre que el socket tenga datos,
	porque el buffer lo controla desde el exterior, y no hay control del estado del mismo
	por eso siempre se debe leer, para actualizar el estado del buffer
*/
DWORD	socket_rd_data(struct S_APP_DATA* app,S_SOCKET	*sock)
{
	char	*fnc_name = "socket_read_data";
	int		ir;
	char	*ip;
	int		port;

	// no se puede leer si se cumple esta condicion
	if ((sock->flags & F_SOCKET_RD_CLOSE)  || 
		(sock->flags & F_SOCKET_RD_FAILED) || 
		(sock->rd_buffer == NULL)) return ERR_OK;

	// si no se puede leer en el socket hay que solicitarlo
	if ((sock->flags & F_SOCKET_CAN_READ) == 0)
	{
		sock->flags |= F_SOCKET_NEED_READ;
		return ERR_OK;
	}

	// esto lo debe hacer el que modifica el buffer de datos o el que los lee
	if (*sock->prd_end == *sock->prd_start)
	{
		*sock->prd_start = 0;
		*sock->prd_end = 0;
	}
	if (*sock->prd_end == sock->rd_size)
	{
		sock->flags &= ~F_SOCKET_NEED_READ;
		return ERR_OK;
	}

	ir = recv(sock->handle,(char*)&sock->rd_buffer[*sock->prd_end],sock->rd_size - *sock->prd_end,0);
	sock->flags &= ~F_SOCKET_CAN_READ;
	sock->flags |= F_SOCKET_NEED_READ;

	if (ir > 0)
	{
		// Lectura satisfactoria hay que espera otro evento de lectura
		(*sock->prd_end) += ir;
		return ERR_OK;
	}

	// error o cierre del canal de lectura EOF
	if (sock->flags & F_SOCKET_SRV_CONN)
	{
		ip = inet_ntoa(sock->lsn_sock_addr.sin_addr);
		port = ntohl(sock->lsn_sock_addr.sin_port);
	}
	else
	{
		ip = inet_ntoa(sock->sock_addr.sin_addr);
		port = ntohl(sock->sock_addr.sin_port);
	}

	sock->flags |= F_SOCKET_RD_CLOSE;
	sock->flags &= ~F_SOCKET_NEED_READ;
	if (ir == 0)		// se esta cerrando la conexion
	{
		_log(LOG_WARNING,"%s Connection %s:%d read channel is closed by EOF",fnc_name,ip,port); 
	}
	if (ir == SOCKET_ERROR) 
	{
		_log(LOG_ERROR,"%s Connection %s:%d read channel is closed by failed operation ",fnc_name,ip,port);
		sock->flags |= (F_SOCKET_RD_FAILED|F_SOCKET_OP_FAILED);
		socket_wr_close(app,sock);
		return Socket_Error_Log(app,WSAGetLastError(),"%s recv",fnc_name);
	}
	return ERR_OK;
}

DWORD	socket_wr_data(struct S_APP_DATA* app,S_SOCKET	*sock)
{
	char	*fnc_name = "socket_wr_data";
	int		ir;
	char	*ip;
	int		port;

	// no se acepta escritura si
	if ((sock->flags & F_SOCKET_WR_CLOSE) ||
		(sock->flags & F_SOCKET_WR_FAILED) ||
		(sock->wr_buffer == NULL)) return ERR_OK;

	// si no se puede escribir en el socket hay que solicitarlo
	if ((sock->flags & F_SOCKET_CAN_WRITE) == 0)
	{
		sock->flags |= F_SOCKET_NEED_WRITE;
		return ERR_OK;
	}
	// se puede escribir en el socket, pero si no hay nada pues no se solicita escritura
	if (*sock->pwr_end == *sock->pwr_start)
	{
		*sock->pwr_start = 0;
		*sock->pwr_end = 0;
		sock->flags &= ~F_SOCKET_NEED_WRITE;
		if (sock->flags & F_SOCKET_WR_CLOSING)
		{
			shutdown(sock->handle,SD_SEND);
			//sock->flags |= F_SOCKET_WR_CLOSE;
		}
		return ERR_OK;
	}

	ir = send(sock->handle,(char*)&sock->wr_buffer[*sock->pwr_start],*sock->pwr_end - *sock->pwr_start,0);
	sock->flags &= ~F_SOCKET_CAN_WRITE;
	sock->flags |= F_SOCKET_NEED_WRITE;

	if (ir > 0)
	{
		(*sock->pwr_start) += ir;
		return ERR_OK;
	}

	// error o cierre del canal de lectura EOF
	if (sock->flags & F_SOCKET_SRV_CONN)
	{
		ip = inet_ntoa(sock->lsn_sock_addr.sin_addr);
		port = ntohl(sock->lsn_sock_addr.sin_port);
	}
	else
	{
		ip = inet_ntoa(sock->sock_addr.sin_addr);
		port = ntohl(sock->sock_addr.sin_port);
	}

	sock->flags &= ~F_SOCKET_NEED_WRITE;
	sock->flags |= F_SOCKET_WR_CLOSE;

	if (ir == 0)
	{
		_log(LOG_WARNING,"%s Connection %s:%d write channel is closed by EOF",fnc_name,ip,port); 
	}
	if (ir == SOCKET_ERROR) 
	{
		_log(LOG_ERROR,"%s Connection %s:%d write channel is closed by failed operation ",fnc_name,ip,port);
		sock->flags |= (F_SOCKET_WR_FAILED|F_SOCKET_OP_FAILED);
		socket_rd_close(app,sock);
		return Socket_Error_Log(app,WSAGetLastError(),"%s send",fnc_name);
	}
	return ERR_OK;
}

// se solicita el cierre del socket despues de enviar los ultimos bytes
DWORD	socket_wr_close(struct S_APP_DATA* app,S_SOCKET	*sock)
{
	if (sock->flags & F_SOCKET_WR_CLOSE) return ERR_OK;
	if (*sock->pwr_end == *sock->pwr_start)
	{
		shutdown(sock->handle,SD_SEND);
		//sock->flags |= F_SOCKET_WR_CLOSE;
		sock->flags &= ~F_SOCKET_NEED_WRITE;
	}
	else
		sock->flags &= F_SOCKET_WR_CLOSING;
		
	return ERR_OK;
}

// si se invoca este metodo es porque no se quieren recibir mas datos de forma inmediata
DWORD	socket_rd_close(struct S_APP_DATA* app,S_SOCKET	*sock)
{
	if (sock->flags & F_SOCKET_RD_CLOSE) return ERR_OK;
	shutdown(sock->handle,SD_RECEIVE);
	sock->flags |= F_SOCKET_RD_CLOSE;
	sock->flags &= ~F_SOCKET_NEED_READ;
	return ERR_OK;
}

DWORD socket_send(struct S_APP_DATA* app,S_SOCKET	*psock,void* buff,int len)
{
	char	*fnc_name;
	int		send;

	fnc_name = "socket_send";
	// Liberar el buffer
	if (*psock->pwr_end == *psock->pwr_start)
	{
		*psock->pwr_start = 0;
		*psock->pwr_end = 0;
	}
	if (*psock->pwr_end + len > psock->wr_size) 
	{
		send = psock->wr_size - *psock->pwr_end;
		_log(LOG_ERROR,"%s Data has been trunc by %d bytes in sock ???",fnc_name,len-send);
	}
	else
		send = len;

	memcpy(&psock->wr_buffer[*psock->pwr_end],buff,send);
	(*psock->pwr_end) += send;
	socket_wr_data(app,psock);
	return ERR_OK;
}

DWORD	cmd_send_prompt(struct S_APP_DATA* app,S_CONNECTION	*pconn)
{
	char	*fnc_name;
	int		ir;

	struct S_SOCKET	*psock;
	
	fnc_name = "cmd_send_prompt";
	psock = &pconn->src_socket;

	ir = _snprintf((char*)&psock->wr_buffer[*psock->pwr_end],psock->wr_size-*psock->pwr_end,"\n\r>");
	if (ir > 0) 
		(*psock->pwr_end) += ir;
	else
	{
		*psock->pwr_end = psock->wr_size;
	}
	socket_wr_data(app,psock);

	return ERR_OK;
}
// cuando se reciven datos de un socket tipo comando se invoca este metodo para procesarlo si se ha recivido el <enter>
DWORD	cmd_socket_read_data(struct S_APP_DATA* app,S_CONNECTION	*pconn)
{
	char	*fnc_name;
	char	*cptr;
	char	*cmd;
	int		ir;
	char	cmd_result[155];

	unsigned long	ip;
	struct S_SOCKET	*psock;
	
	fnc_name = "cmd_socket_read_data";
	if (pconn->conn_type != CONN_TYP_CMD) return ERR_OK;
	psock = &pconn->src_socket;

	cmd = (char*)&psock->rd_buffer[*psock->prd_start];
	cptr = (char*)memchr(cmd,'\r',*psock->prd_end-*psock->prd_start);
	if (cptr == NULL) return ERR_OK;
	
	// procesar el comando obtenido
	*cptr = 0;
	// clear rd buffer
	*psock->prd_end = 0;
	*psock->prd_start = 0;
	ip = inet_addr(cmd);
	if ((ip == INADDR_NONE) || (*cmd == 0) || (ip == 0))
	{
		app->srv_addr.s_addr = INADDR_NONE;
		ir = _snprintf(cmd_result,sizeof(cmd_result),"ERR001 - Invalid IP Address. Use X.X.X.X where X=[0..255]\r\n>");
		if (ir < 0) 
		{
			ir = sizeof(cmd_result);
			cmd_result[ir-1] = 0;
			//_log(LOG_ERROR,"%s out of buffer to send cmd result msg ",fnc_name,&psock->wr_buffer[psock->wr_end]);
		}
		socket_send(app,psock,cmd_result,ir);
		return _log(LOG_DATA,"%s %s",fnc_name,cmd_result);
	}

	// Validar si existe alguna conecion puente pendiente antes de aceptar la nueva IP o servidor
	app->srv_addr.s_addr = ip;
	strcpy(app->srv_ip,inet_ntoa(app->srv_addr));
	ir = _snprintf(cmd_result,sizeof(cmd_result),"OK - Changed to server %s\r\n>",cmd);
	if (ir < 0) 
	{
		ir = sizeof(cmd_result);
		cmd_result[ir-1] = 0;
	}
	socket_send(app,psock,cmd_result,ir);
	_log(LOG_DATA,"%s %s",fnc_name,cmd_result);

	/*
	ir = sscanf("%d.%d.%d.%d",cptr,&srv_ip[0],&srv_ip[1],&srv_ip[2],&srv_ip[3]);
	if (ir != 4)
	{
		_snprintf((char*)&psock->wr_buffer[psock->wr_end],psock->wr_size-psock->wr_end,"ERR001 - Invalid IP Address. Use X.X.X.X");
		socket_wr_data(app,psock);
		return _log(LOG_ERROR,"%s %s",fnc_name,&psock->wr_buffer[psock->wr_end]);
	}
	for (i=0;i<4;i++)
	{
		if ((srv_ip[i]<0) || (srv_ip[i]>255)) 
		{
			_snprintf((char*)&psock->wr_buffer[psock->wr_end],psock->wr_size-psock->wr_end,"ERR002 - IP Address out of range. Use X.X.X X where X=[0..255]");
			socket_wr_data(app,psock);
			return _log(LOG_ERROR,"%s %s",fnc_name,&psock->wr_buffer[psock->wr_end]);
		}
	}
	
	// INADDR_NONE inet_addr 
	app->srv_addr.s S_un_b[0] = srv_ip[0];
	app->srv_addr.s_un_b.s_b2 = srv_ip[1];
	app->srv_addr.s_un_b.s_b3 = srv_ip[2];
	app->srv_addr.s_un_b.s_b4 = srv_ip[3];
	*/

	return ERR_OK;
}
DWORD	bridge_close(struct S_APP_DATA* app,S_CONNECTION *pconn)
{
	if (pconn->dest_socket.binit) closesocket(pconn->dest_socket.handle);
	if (pconn->src_socket.binit) closesocket(pconn->src_socket.handle);
	
	pconn->binit = 0;
	pconn->dest_socket.binit = 0;
	pconn->src_socket.binit = 0;
	return ERR_OK;
}
/*
	Determina el estado de los socket
	El posible estado de cierre y si estan cerrado los dos se cierra el puente
	El posible estado de fallo
	Genera los eventos de shutdown en el socket
*/
DWORD	bridge_check(struct S_APP_DATA* app,S_CONNECTION *pconn)
{
	char	*fnc_name;

	fnc_name = "bridge_check";
	if (pconn->conn_type != CONN_TYP_BRIDGE) return ERR_OK;
	// esperar a que se establesca la conecion con el servidor
	if (pconn->dest_socket.flags & F_SOCKET_CONNECTING) return ERR_OK;
	// validar el cierre de sockets.
	if ((pconn->src_socket.flags & F_SOCKET_RD_CLOSE) &&
		(pconn->dest_socket.flags & F_SOCKET_WR_CLOSE) == 0)) socket_wr_close(app,&pconn->dest_socket);
	
	if ((pconn->src_socket.flags & F_SOCKET_WR_CLOSE) &&
		(pconn->dest_socket.flags & F_SOCKET_RD_CLOSE) == 0)) socket_rd_close(app,&pconn->dest_socket);
	
	if ((pconn->dest_socket.flags & F_SOCKET_RD_CLOSE) &&
		(pconn->src_socket.flags & F_SOCKET_WR_CLOSE) == 0)) socket_wr_close(app,&pconn->src_socket);
	
	if ((pconn->dest_socket.flags & F_SOCKET_WR_CLOSE) &&	
		(pconn->src_socket.flags & F_SOCKET_RD_CLOSE) == 0) socket_rd_close(app,&pconn->src_socket);
	
	// validar si el puente esta cerrado completamente
	if ((pconn->src_socket.flags & F_SOCKET_RD_CLOSE) &&
		(pconn->src_socket.flags & F_SOCKET_WR_CLOSE) &&
		(pconn->dest_socket.flags & F_SOCKET_RD_CLOSE) &&
		(pconn->dest_socket.flags & F_SOCKET_WD_CLOSE)) return bridge_close(app,pconn);
	
	// Reiniciar la comunicacion en sockets que se han quedado detenidos
	if (((pconn->src_socket.flags & F_SOCKET_NEED_READ) == 0) &&
		(*pconn->src_socket.prd_end != pconn->src_socket.rd_size))
	{
		socket_rd_data(app,&pconn->src_socket);
	}
	if (((pconn->src_socket.flags & F_SOCKET_NEED_WRITE) == 0) &&
		(*pconn->src_socket.pwr_start != *pconn->src_socket.pwr_end))
	{
		socket_wr_data(app,&pconn->src_socket);
	}
	if (((pconn->dest_socket.flags & F_SOCKET_NEED_READ) == 0) &&
		(*pconn->dest_socket.prd_end != pconn->dest_socket.rd_size))
	{
		socket_rd_data(app,&pconn->dest_socket);
	}
	if (((pconn->dest_socket.flags & F_SOCKET_NEED_WRITE) == 0) &&
		(*pconn->dest_socket.pwr_start != *pconn->dest_socket.pwr_end))
	{
		socket_wr_data(app,&pconn->dest_socket);
	}

	return ERR_OK;
}

// Inicializar una conecion por el puerto de comandos
DWORD	cmd_connection_accept(struct S_APP_DATA* app,S_CONNECTION	*pconn)
{
	char	*fnc_name;
	fnc_name = "accept_cmd_connection";
	char	prompt[155];
	int		ir;

	pconn->conn_type = CONN_TYP_CMD;
	pconn->rd_start = 0;
	pconn->rd_end = 0;
	pconn->wr_start = 0;
	pconn->wr_end = 0;

	pconn->src_socket.wr_buffer = pconn->wr_buffer;
	pconn->src_socket.wr_size = sizeof(pconn->wr_buffer);
	pconn->src_socket.pwr_start = &pconn->wr_start;
	pconn->src_socket.pwr_end	= &pconn->wr_end;

	pconn->src_socket.rd_buffer = pconn->rd_buffer;
	pconn->src_socket.rd_size = sizeof(pconn->rd_buffer);
	pconn->src_socket.prd_start = &pconn->rd_start;
	pconn->src_socket.prd_end	= &pconn->rd_end;
	
	pconn->src_socket.flags |= (F_SOCKET_NEED_READ | F_SOCKET_NEED_WRITE);
	// enviar el prompt
	ir = snprintf(prompt,sizeof(prompt),"OK>");
	if (ir < 0) ir = sizeof(prompt);
	socket_send(app,&pconn->src_socket,prompt,ir);
	return ERR_OK;
}

// cuando se recive una coneccion en un socket tipo bridge hay que inicializar la conecion con el servidor
DWORD	bridge_connection_accept(struct S_APP_DATA* app, S_CONNECTION	*pconn)
{
	char	*fnc_name;
	int		ir;
	char	client_ip[20];

	struct	S_BRIDGE_CNF	*pconf;
	u_short	port;

	fnc_name = "accept_bridge_connection";
	pconn->conn_type = CONN_TYP_BRIDGE;
	pconn->rd_start = 0;
	pconn->rd_end = 0;
	pconn->wr_start = 0;
	pconn->wr_end = 0;

	for (;;)
	{
		if (app->srv_addr.s_addr == INADDR_NONE)
		{
			_log(LOG_ERROR,"%s Undefined server, use the command port to set a valid server addres",fnc_name);
			break;
		}
		pconn->dest_socket.handle = socket(AF_INET,SOCK_STREAM,0);
		if (pconn->dest_socket.handle == INVALID_SOCKET) 
		{
			Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s socket function ",fnc_name);
			break;
		}
		pconn->dest_socket.binit = 1;
#ifndef WIN32
		fcntl(pconn->dest_socket.handle,F_SETFL,fcntl(pconn->dest_socket.handle,F_GETFL,0)|O_NONBLOCK));
#endif
		// determinar el servidor y puerto de destino
		port = ntohs(pconn->src_socket.lsn_sock_addr.sin_port);

		for (pconf=g_app_data.conf.first_bridge_cnf;pconf != NULL;pconf=pconf->next)
		{
			if (port == pconf->src_port) break;
		}
		pconn->dest_socket.sock_addr.sin_addr = app->srv_addr;
		pconn->dest_socket.sock_addr.sin_port = htons(pconf->dest_port);
		pconn->dest_socket.sock_addr.sin_family = AF_INET;

		strcpy(client_ip,inet_ntoa(pconn->src_socket.sock_addr.sin_addr));
//		if (bridge_get_server(pconn->src_socket.sock_addr,&pconn->dest_socket.sock_addr) != ERR_OK) break;
		ir = connect(pconn->dest_socket.handle,(SOCKADDR*)&pconn->dest_socket.sock_addr,sizeof(pconn->dest_socket.sock_addr));
		if (ir == SOCKET_ERROR) 
		{
			Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s connect to %s:%d ",fnc_name,inet_ntoa(pconn->dest_socket.sock_addr.sin_addr),ntohs(pconn->dest_socket.sock_addr.sin_port));
			break;
		}
		if (ir != 0) break;
		
		_log(LOG_DEBUG,"%s Start Bridge from %s:%d to %s:%d",fnc_name,client_ip,ntohs(pconn->src_socket.lsn_sock_addr.sin_port),app->srv_ip,ntohs(pconn->dest_socket.sock_addr.sin_port));

		pconn->src_socket.wr_buffer = pconn->wr_buffer;
		pconn->src_socket.wr_size = sizeof(pconn->wr_buffer);
		pconn->src_socket.pwr_start = &pconn->wr_start;
		pconn->src_socket.pwr_end	= &pconn->wr_end;
		pconn->src_socket.rd_buffer = pconn->rd_buffer;
		pconn->src_socket.rd_size = sizeof(pconn->rd_buffer);
		pconn->src_socket.prd_start = &pconn->rd_start;
		pconn->src_socket.prd_end	= &pconn->rd_end;
		pconn->src_socket.flags |= (F_SOCKET_NEED_READ|F_SOCKET_NEED_WRITE);

		pconn->dest_socket.wr_buffer = pconn->rd_buffer;
		pconn->dest_socket.wr_size	 = sizeof(pconn->rd_buffer);
		pconn->dest_socket.pwr_start  = &pconn->rd_start;
		pconn->dest_socket.pwr_end	 = &pconn->rd_end;
		pconn->dest_socket.rd_buffer = pconn->wr_buffer;
		pconn->dest_socket.rd_size	 = sizeof(pconn->wr_buffer);
		pconn->dest_socket.prd_start  = &pconn->wr_start;
		pconn->dest_socket.prd_end	 = &pconn->wr_end;
		pconn->dest_socket.flags |= (F_SOCKET_NEED_READ|F_SOCKET_NEED_WRITE);
		return ERR_OK;
	}
	if (pconn->dest_socket.binit) closesocket(pconn->dest_socket.handle);
	closesocket(pconn->src_socket.handle);
	
	pconn->binit = 0;
	pconn->dest_socket.binit = 0;
	pconn->src_socket.binit = 0;
	_log(LOG_ERROR,"%s Connection from %s in %d closed because server failed",fnc_name,client_ip,ntohs(pconn->src_socket.lsn_sock_addr.sin_port));
	return ERR_FATAL;
}

DWORD app_get_new_connection(struct S_APP_DATA* app,struct S_CONNECTION	**ppconn)
{
	char	*fnc_name;

	struct S_CONNECTION	**conn;

	fnc_name = "app_get_new_connection";

	// buscar una conecion no inicializada
	for (conn = &app->first_conn;*conn != NULL;conn = &(*conn)->next)
	{
		if ((*conn)->binit == 0)
		{
			*ppconn = *conn;
			return ERR_OK;
		}
	}
	// no hay coneciones disponibles sin usar
	if (MemStack_Get(&app->conf.stack,sizeof(**conn),(void**)conn,1,app) != ERR_OK) return _log(LOG_ERROR,"%s ERR: No memory",fnc_name);
	(*conn)->next = NULL;
	*ppconn = *conn;
	return ERR_OK;
}

DWORD app_accept_connection(struct S_APP_DATA* app,int index)
{
	char	*fnc_name;
	int		size;
	int		hsocket;
//	int		i;
//	DWORD	dwr;

	struct sockaddr_in		sock_addr;
	struct S_CONNECTION		*pconn;
	struct S_LISTEN_SOCKET	*plsn_sock;

	fnc_name = "app_accept_cmd_connection";

	plsn_sock = &g_app_data.listen_sock[index];
	size = sizeof(sock_addr);
	
	hsocket = accept(plsn_sock->handle,(struct sockaddr*)&sock_addr,&size);
	if (hsocket == INVALID_SOCKET) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s accept ",fnc_name);

	// buscar si hay coneciones disponibles
	//_log(LOG_DEBUG,"Accepted Connection from %d.%d.%d.%d",sock_addr.sin_addr.S_un.S_un_b.s_b1,sock_addr.sin_addr.S_un.S_un_b.s_b2,sock_addr.sin_addr.S_un.S_un_b.s_b3,sock_addr.sin_addr.S_un.S_un_b.s_b4);
	_log(LOG_DEBUG,"Accepted Connection from %s in %d",inet_ntoa(sock_addr.sin_addr),ntohs(plsn_sock->sock_addr.sin_port));

	if (app_get_new_connection(app,&pconn) != ERR_OK)
	{
		_log(LOG_ERROR,"%s Connection from %s in %d closed because Failed to process",fnc_name,inet_ntoa(sock_addr.sin_addr),sock_addr.sin_port);
		closesocket(hsocket);
		return ERR_FATAL;
	}
	memset(pconn,sizeof(*pconn),0);
	pconn->binit = 1;
	pconn->src_socket.binit = 1;
	pconn->src_socket.handle = hsocket;
	pconn->src_socket.sock_addr = sock_addr;
	pconn->src_socket.lsn_sock_addr = plsn_sock->sock_addr;
	pconn->src_socket.flags = F_SOCKET_NEED_READ|F_SOCKET_NEED_WRITE|F_SOCKET_SRV_CONN;
	if (index == 0) 
		return cmd_connection_accept(app,pconn);
	else
		return bridge_connection_accept(app,pconn);
	
	return ERR_OK;
}

void _FD_ADD(int fd,fd_set* fd_list,int* maxfd)
{
	FD_SET(fd,fd_list);
	if (fd > *maxfd) *maxfd = fd;
}

DWORD app_main_loop(struct S_APP_DATA* app)
{
	char	*fnc_name;
	int		ir;
	int		i;
	int		fdmax;
	struct S_CONNECTION	*pconn;

	fd_set rd_socks;
	fd_set wr_socks;

	fnc_name = "app_main_loop";

	for (;;)
	{
		FD_ZERO(&rd_socks);
		FD_ZERO(&wr_socks);
		fdmax = 0;

		// socket de listen que acepta conexiones
		for (i=0;i<app->listen_sock_count;i++)
		{
			_FD_ADD(app->listen_sock[i].handle,&rd_socks,&fdmax);	
		}
		
		for (pconn = app->first_conn;pconn != NULL;pconn = pconn->next)
		{
			if (!pconn->binit) continue;
			// el socket src es comun sea cual sea el tipo de estructura
			if (pconn->src_socket.binit)
			{
				if (pconn->src_socket.flags & F_SOCKET_NEED_READ) _FD_ADD(pconn->src_socket.handle,&rd_socks,&fdmax);
				if (pconn->src_socket.flags & F_SOCKET_NEED_WRITE) _FD_ADD(pconn->src_socket.handle,&wr_socks,&fdmax);
			}

			// si la conecion es tipo puente entonces el socket destino tambien se utiliza
			if ((pconn->conn_type == CONN_TYP_BRIDGE) && (pconn->dest_socket.binit))
			{
				if (pconn->dest_socket.flags & F_SOCKET_NEED_READ) _FD_ADD(pconn->dest_socket.handle,&rd_socks,&fdmax);
				if (pconn->dest_socket.flags & F_SOCKET_NEED_WRITE) _FD_ADD(pconn->dest_socket.handle,&wr_socks,&fdmax);
			}
		}
		ir = select(fdmax+1,&rd_socks,&wr_socks,NULL,NULL);
		if (ir == SOCKET_ERROR) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s select ",fnc_name);
		if (ir == 0) _log(LOG_DEBUG,"%s select timeout",fnc_name);

		// Validar coneciones entrantes
		for (i=0;i<app->listen_sock_count;i++)
		{
			if (FD_ISSET(app->listen_sock[i].handle,&rd_socks) != 0) app_accept_connection(app,i);
		} 
		// Validar eventos en las coneciones establecidas
		for (pconn = app->first_conn;pconn != NULL;pconn = pconn->next)
		{
			if (!pconn->binit) continue;
			if (pconn->src_socket.binit)
			{
				if ((pconn->src_socket.flags & F_SOCKET_NEED_READ) && (FD_ISSET(pconn->src_socket.handle,&rd_socks) != 0))
				{
					pconn->src_socket.flags |= F_SOCKET_CAN_READ;
					socket_rd_data(app,&pconn->src_socket);
					if (pconn->conn_type == CONN_TYP_CMD) cmd_socket_read_data(app,pconn);
				}
				if ((pconn->src_socket.flags & F_SOCKET_NEED_WRITE) && (FD_ISSET(pconn->src_socket.handle,&wr_socks) != 0))
				{
					pconn->src_socket.flags |= F_SOCKET_CAN_WRITE;
					socket_wr_data(app,&pconn->src_socket);
				}
			}
			if (pconn->dest_socket.binit)
			{
				if ((pconn->dest_socket.flags & F_SOCKET_NEED_READ) && (FD_ISSET(pconn->dest_socket.handle,&rd_socks) != 0))
				{
					pconn->dest_socket.flags |= F_SOCKET_CAN_READ;
					socket_rd_data(app,&pconn->dest_socket);
				}
				if ((pconn->dest_socket.flags & F_SOCKET_NEED_WRITE) && (FD_ISSET(pconn->dest_socket.handle,&wr_socks) != 0))
				{
					pconn->dest_socket.flags |= F_SOCKET_CAN_WRITE;
					socket_wr_data(app,&pconn->dest_socket);
				}
			}
			if (pconn->conn_type == CONN_TYP_BRIDGE) bridge_check(app,pconn);
		}
	}

	return ERR_OK;
}

/*
		Leer fichero de configuracion
		-	Abrir puerto de comando 
		-	Abrir puertos de salto
		-	esperar eventos en todos los sockets
		-	no se puede procesar ninguna conexion de entrada si no esta configurada una primera pc de destino
		-	ciclo para procesar los eventos en los sockets
*/

int main(int argc, char* argv[])
{
	/*
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
*/
	
	char	*fnc_name;
	WORD	wVersionRequested;
	WSADATA wsaData;
	int		ir;
	int		i;

	struct S_BRIDGE_CNF	*pconf;
	struct S_LISTEN_SOCKET	*plsn_sock;

	fnc_name = "main";
	memset(&g_app_data,0,sizeof(g_app_data));
	g_app_data.srv_addr.s_addr = INADDR_NONE;
	*g_app_data.srv_ip = 0;

	conf_load("..\\bin\\tcpbridge.ini",&g_app_data);

	// Inicializacion de los sockets

	wVersionRequested = MAKEWORD( 2, 2 );
	ir = WSAStartup( wVersionRequested, &wsaData ); if (ir != 0) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s WSAStartup ",fnc_name);

	g_app_data.listen_sock[0].handle = socket(AF_INET,SOCK_STREAM,0);
	if (g_app_data.listen_sock[0].handle == INVALID_SOCKET) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s socket function ",fnc_name);

	 /* fill address struct */
	g_app_data.listen_sock[0].sock_addr.sin_addr.s_addr	= INADDR_ANY;
    g_app_data.listen_sock[0].sock_addr.sin_port		= htons(g_app_data.conf.icmd_port);
    g_app_data.listen_sock[0].sock_addr.sin_family		= AF_INET;
	g_app_data.listen_sock_count = 1;
	
	// crear todos los sockets de escucha del puente, dada la configuracion obtenida
	for (pconf=g_app_data.conf.first_bridge_cnf;pconf != NULL;pconf=pconf->next)
	{
		if (g_app_data.listen_sock_count >= MAX_LISTEN_SOCK)
		{
			return _log(LOG_ERROR,"%s listen socket overflow max = %d",fnc_name,MAX_LISTEN_SOCK);
			break;
		}
		plsn_sock = &g_app_data.listen_sock[g_app_data.listen_sock_count];

		plsn_sock->sock_addr.sin_addr.s_addr = INADDR_ANY;
		plsn_sock->sock_addr.sin_family = AF_INET;
		plsn_sock->sock_addr.sin_port = htons(pconf->src_port);
		
		plsn_sock->handle = socket(AF_INET,SOCK_STREAM,0);
		if (plsn_sock->handle == INVALID_SOCKET) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s socket function ",fnc_name);
		g_app_data.listen_sock_count++;

	}
	// iniciar todos los sockets de escucha
	for (i=0;i<g_app_data.listen_sock_count;i++)
	{
		plsn_sock = &g_app_data.listen_sock[i];

		if (bind(plsn_sock->handle,(struct sockaddr*)&plsn_sock->sock_addr,sizeof(plsn_sock->sock_addr)) == SOCKET_ERROR) return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s bind with port %d ",fnc_name,ntohs(plsn_sock->sock_addr.sin_port));
		if (listen(plsn_sock->handle,5) == SOCKET_ERROR)	return Socket_Error_Log(&g_app_data,WSAGetLastError(),"%s listen with 5 ",fnc_name);
		_log(LOG_DEBUG,"%s Listener Socket started in port %d",fnc_name,ntohs(plsn_sock->sock_addr.sin_port));
	}

	app_main_loop(&g_app_data);
	return 0;
}



