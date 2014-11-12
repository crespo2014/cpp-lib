/*
 * platform.h
 *
 *  Created on: 10/07/2012
 *      Author: lester

  Define comun functions and constants
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "stdio.h"
#include "stdarg.h"

#ifdef WIN32
	#define snprintf	_snprintf
	#define vsnprintf	_vsnprintf
	#define getpid		_getpid
	#define popen		_popen
	#define pclose		_pclose
	#include <process.h>
	#include "windows.h"

// para que compilen los proyectos con includes de la sdk 8
/*
typedef ULONG ULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;
 */
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

typedef void *HANDLE;
typedef wchar_t WCHAR;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#define SOCKET_ERROR	-1
#define MAX_PATH 		255
#define NULL			0x0000
#define	TRUE			1
#define FALSE			0
#define INVALID_HANDLE_VALUE  -1

#endif

#ifdef LINUX

#endif

#ifdef _cplusplus
#else
	#define true	1
	#define false	0
	#define bool	unsigned char
#endif


// Codigos de error comunes
#define ERR_OK			0	// Operacion satisfactoria o es TRUE
#define ERR_API			1	// Una funcion externa o API no pudo completar la operacion 
#define ERR_PARAM		2	// No se procedio porque faltaron parametros o eran invalidos
#define ERR_HANDLE		3	// No se tiene un handle valido para la operacion, dispositivo cerrado
#define ERR_CLOSE		3	// dispositivo cerrado o no abierto
#define ERR_FATAL		4	// no se pudo completar la operacion
#define ERR_FALSE		6	// La funcion bool devolvio false no se cumple la condicion pero no hay error
#define ERR_EOF			7	// Fin del fichero o no hay mas elementos a enumerar
#define ERR_NULL		8	// No hay resultados por devolver
#define ERR_TRUNCD		9	// Los datos han sido truncados
#define ERR_OP			10	// la operacion no se puede realizar
#define ERR_PENDING		11	// operacion pendiente, revisar el estado del evento
#define ERR_TIMEOUT		12	// sobrepasado el tiempo permitido para realizar la operacion
#define ERR_NOT_FOUND	13	// el elemento no se encontro
#define ERR_PASSWORD	14	// la contraseña o las crdenciales no son validas
#define ERR_NOMEMORY	15	// Error de memoria
#define ERR_ABORT		16	// La operacion ha sido cancelada o abortada
#define ERR_UNSUPPORTED	17	// Funcion u operacion no soportada o no implementada
#define ERR_UNEXPECTED	18	// situacion no esperada o codigo corrupto, es una situacion no esperada
#define ERR_IS_LOCK		19	// el recurso esta bloqueado
#define ERR_OVERFLOW	20	// la operacion no se puede aplicar porque hay desbordamiento de memoria
#define ERR_LAST		100	// permite definir a partir de aqui los errores propios de la aplicación

#endif /* PLATFORM_H_ */
