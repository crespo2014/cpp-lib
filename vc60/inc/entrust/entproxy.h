/*******************************************************************************
 * entproxy.h - Header file for Proxy Callback functions
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.          
 ******************************************************************************/
/* 
 * Proxy callback access functions
 */

#ifndef etproxy_h
#define etproxy_h

/*Entrust toolkits are compiled using a structure member alignment of 8*/
#if _MSC_VER >= 1100
#pragma pack(push, 8)
#endif


#ifdef ENTAPI
// HI-Haider June 30th, 99
#ifndef	MACOS
#include <base/winsock/winsock.h>
#endif
#include <base/comm/callback.h>
#else
/* These are defined in headers/callback.h, but that's not shipped with the toolkit */
/*** Begin mirrored section ***/

/** <datatype>CallbackParams</datatype> */
/* destination of a callback request */
typedef enum {
	CALLBACK_DEST_LDAP,
	CALLBACK_DEST_SEP
} CALLBACK_DEST;

/* callback request type */
typedef enum {
	CALLBACK_REQUEST_CONNECT,
	CALLBACK_REQUEST_SEND,
	CALLBACK_REQUEST_RECEIVE,
	CALLBACK_REQUEST_DISCONNECT
} CALLBACK_REQUEST;

typedef union {
	/* For a CONNECT request, an entrust.ini entry of the form "hostname+port" 
       gets split into "hostname" and "port".  The dest callback parameter is actually
	   a CALLBACK_DEST type enum. */
	struct {
		const char	*host;
		UINT16		port;
		UINT16		*id;
	} connect;
	/* For a SEND request, the data and its length are specified */
	struct {
		const BYTE	*data;
		UINT32		len;
	} send;
	/* For a RECEIVE request, the buffer is allocated by the caller.
       The len field has two uses: it specifies the length of the buffer
	   passed to the callback, and after the call, the callback should set
	   it to the length of data actually read */
	struct {
		BYTE		*data;
		UINT32		*len;
	} receive;
	/* For a DISCONNECT request, no parameters are used */
} CallbackParams;

/** <datatype>TransportCallback</datatype> */
/*
 * Application defined callback for socket communication.
 *
 *		request: What needs to be done during this call
 *		dest: The integer "connection ID" returned by callback after a
 *			  CONNECT call.  If this is a CONNECT call, then dest is
 *            CALLBACK_DEST_LDAP or CALLBACK_DEST_SEP.
 *		params: request dependent information
 *		context: application supplied context
 *
 */
typedef INT16 (*TransportCallback)(CALLBACK_REQUEST request,
									UINT16 dest,
									CallbackParams params,
									void * context);

/*** End mirrored section ***/
#endif /* !defined(ENTAPI) */


#ifdef __cplusplus
extern "C" {
#endif

/* HI-Haider May 19th, 98:*/
#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

/* 
 * Sets the callback to be used for all communications
 */
EXPT32 extern void EXPT		ETSetCallback(TransportCallback callback, void * context);

/** <function>ETEnableCallback</function> */
/*
 * Used to enable/disable callback use for some destinations
 */
EXPT32 extern void EXPT		ETEnableCallback(CALLBACK_DEST dest, BOOL enable);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}; /* extern C close brace */
#endif

/*Entrust toolkits are compiled using a structure member alignment of 8*/
#if _MSC_VER >= 1100
#pragma pack(pop)
#endif


#endif /* !defined(entproxy_h) */

