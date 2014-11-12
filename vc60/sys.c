/*
 * sys.c
 *
 *  Created on: Nov 17, 2011
 *      Author: main
 *  La finalidad de este fichero es dar soporte para poder compilar tanto multiples plataformas
 *  se van a definir los tipos de datos que no estan presentes en determinados sistemas.
 *
 */

#include <stdio.h>

// para poder compilar en visual estudio 6.0
#ifdef WIN32
	#define snprintf	_snprintf
	#define vsnprintf	_vsnprintf
	#define getpid		_getpid
	#define popen		_popen
	#define pclose		_pclose
	#define socklen_t	int
	#include <process.h>
	#include "Winsock2.h"
	//#define WSAGetLastError()		errno
#else
	#include <pthread.h>
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

	#define BOOL			unsigned char
	#define DWORD			unsigned long
	#define WORD			unsigned short
	#define BYTE			unsigned char
	// #define INADDR_NONE		0xffffffff		// ya definida en el include #include <netinet/in.h>
	#define SD_SEND			SHUT_WR
	#define SD_RECEIVE		SHUT_RD
	#define SD_BOTH			SHUT_RDWR
	#define SOCKET_ERROR        -1
	#define INVALID_SOCKET		-1
	#define WSAGetLastError()		errno
	#define closesocket				close
#endif

#ifdef _cplusplus
#else
	#define true	1
	#define false	0
	#define bool	unsigned char
#endif

void string_upper(char* str)
{
	int c = *str;
	while (c != 0)
	{
		*str++ = toupper(c);
		c = *str;
	}
};
