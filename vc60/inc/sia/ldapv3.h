/*******************************************************************************
i500 History Detail for /fennel4/jean/work-ldap/v3api/includes/ldapv3.h

Extraction: Tue Jun  1 10:03:49 BST 1999

 Version 8.1.7.1 Dated 99/01/12
********************************************************************************

  @(#)ldapv3.h	8.1.7.1

  Copyright (c) 1999 by PeerLogic, Inc.  All Rights Reserved.

  Copyright in this software remains vested in PeerLogic and no copies may be
  made of it or any part of it except for the purpose of evaluation in
  confidence.
  The contents of this software may not be disclosed in whole or in part to
  any other party without the prior written consent of PeerLogic.

*******************************************************************************/

/* 
 *  This header file is based on the draft proposal 
 *  draft-ietf-ldapext-ldap-c-api-00.txt March 1998 which makes the 
 *  following acknowledgements and copyright statements: 
 *
 *  
 *  Acknowledgements 
 *
 *  Many members of the IETF ASID working group as well as members of the 
 *  Internet at large have provided useful comments and suggestions that 
 *  have been incorporated into this revision.  
 *
 *  This original material upon which this revision is based was based upon 
 *  work supported by the National Science Foundation under Grant No.  NCR- 
 *  9416667.  
 *
 *  
 *  Copyright 
 *
 *  Copyright (C) The Internet Society (1998).  All Rights Reserved.  
 *
 *  This document and translations of it may be copied and furnished to 
 *  others, and derivative works that comment on or otherwise explain it or 
 *  assist in its implementation may be prepared, copied, published and 
 *  distributed, in whole or in part, without restriction of any kind, 
 *  provided that the above copyright notice and this paragraph are included 
 *  on all such copies and derivative works.  However, this document itself 
 *  may not be modified in any way, such as by removing the copyright notice 
 *  or references to the Internet Society or other Internet organizations, 
 *  except as needed for the purpose of developing Internet standards in 
 *  which case the procedures for copyrights defined in the Internet 
 *  Standards process must be followed, or as required to translate it into 
 *  languages other than English.  
 */

#ifndef _LDAPV3_H
#define _LDAPV3_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Define platform specific macros.
 */
#ifdef _WIN32
/*
 *  Windows specific methods of importing/exporting external functions of the 
 *  DLL.
 */
#ifndef BASETYPES
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

/*
 *  Macros for exporting/importing functions from the library.
 */
#ifdef _DLLEXPORT_
/*
 *  Creating a DLL - exporting functions from the library.
 */
#define ICLLDAPAPI __declspec(dllexport)
#else
/*
 *  Not creating a DLL - importing functions from the library.
 */
#define ICLLDAPAPI DECLSPEC_IMPORT
#endif /* _DLLEXPORT_  */

#ifndef LDAPAPI
#define LDAPAPI
#endif

#endif /* _WIN32 */

#if defined(sunos5) || defined(hpux)
#define ICLLDAPAPI
#define LDAPAPI
#include <sys/time.h>
#endif

/* 
 *  An application generally uses the C LDAP API in four simple steps.  
 *
 *  - Initialize an LDAP session with a default LDAP server.  
 *
 *  The ldap_init() function returns a handle to the session, allowing 
 *  multiple connections to be open at once.  
 *
 *  - Authenticate to the LDAP server.  
 *
 *  The ldap_bind() function and friends support a variety of authentication 
 *  methods.  
 *
 *  - Perform some LDAP operations and obtain some results.  
 *
 *  ldap_search() and friends return results which can be parsed by 
 *  ldap_parse_result(), ldap_first_entry(), ldap_next_entry(), etc.  
 *
 *  - Close the session.  
 *
 *  The ldap_unbind() function closes the connection.  
 *
 *  Operations can be performed either synchronously or asynchronously.  The 
 *  names of the synchronous functions end in _s.  For example, a 
 *  synchronous search can be completed by calling ldap_search_s().  An 
 *  asynchronous search can be initiated by calling ldap_search().  All 
 *  synchronous routines return an indication of the outcome of the 
 *  operation (e.g, the constant LDAP_SUCCESS or some other error code).  
 *  The asynchronous routines return the message id of the operation 
 *  initiated.  This id can be used in subsequent calls to ldap_result() to 
 *  obtain the result(s) of the operation.  An asynchronous operation can be 
 *  abandoned by calling ldap_abandon() or ldap_abandon_ext().  
 *
 *  Results and errors are returned in an opaque structure called 
 *  LDAPMessage.  Routines are provided to parse this structure, step 
 *  through entries and attributes returned, etc.  Routines are also 
 *  provided to interpret errors.  Later sections of this document describe 
 *  these routines in more detail.  
 */

/* 
 *  LDAP version 3 servers may return referrals to other servers.  By 
 *  default, implementations of this API will attempt to follow referrals 
 *  automatically for the application.  This behavior can be disabled glo- 
 *  bally (using the ldap_set_option() call) or on a per-request basis 
 *  through the use of a client control.  
 *
 *  zzz: by default this implementation currently will not follow referrals.  
 *
 *  As in the LDAPv3 protocol itself, all DNs and string values that are 
 *  passed into or produced by the C LDAP API are represented as UTF-8[10] 
 *  characters.  
 *
 *  For compatibility with existing applications, implementations of this 
 *  API will by default use version 2 of the LDAP protocol.  Applications 
 *  that intend to take advantage of LDAP version 3 features will need to 
 *  use the ldap_set_option() call with a LDAP_OPT_PROTOCOL_VERSION to 
 *  switch to version 3.  
 */

/*
 *  Common data Structures:
 */
 
/* 
 *  The LDAP structure is an opaque data type that represents an LDAP 
 *  session.  Typically this corresponds to a connection to a single server, 
 *  but it may encompass several server connections in the face of LDAPv3 
 *  referrals.  
 */
#ifndef _DLLEXPORT_
#ifndef _LDAPV3_INT_H
/*ICL_LAPI_ldapv3-int.h  provides this*/
typedef struct ldap LDAP;
#endif /* _LDAPV3_INT_H */
#endif /* _DLLEXPORT_ */

/* 
 *  The LDAPMessage structure is an opaque data type that is used to return 
 *  results and error information.  
 */
#ifndef _DLLEXPORT_
#ifndef _LDAPV3_INT_H
/*ICL_LAPI_ldapv3-int.h  provides this*/
typedef struct ldapmsg LDAPMessage;
#endif /* _LDAPV3_INT_H */
#endif /* _DLLEXPORT_ */

/* 
 *  The berval structure is used to represent arbitrary binary data and its 
 *  fields have the following meanings: 
 *
 *  A struct berval contains a sequence of bytes and an indication of its 
 *  length.  The bv_val is not null terminated.  bv_len must always be a 
 *  nonnegative number.  Applications may allocate their own berval 
 *  structures.  
 *
 *  bv_len: Length of data in bytes.  
 *
 *  bv_val: A pointer to the data itself.  
 *
 *  (Note that the interface (draft-ietf-ldapext-ldap-c-api-00.txt March 
 *  1998) does not allow for the definition of BERVAL.  It is included for 
 *  ease of use.) 
 */
typedef struct berval
{
  unsigned long  bv_len;
  char          *bv_val;
} BERVAL;

/* 
 *  The timeval structure is used to represent an interval of time and its 
 *  fields have the following meanings: 
 *
 *  tv_sec: Seconds component of time interval.  
 *
 *  tv_usec: Microseconds component of time interval.  
 *
 *  (Note that the interface (draft-ietf-ldapext-ldap-c-api-00.txt March 
 *  1998) does not allow for the definition of TIMEVAL.  It is included for 
 *  ease of use.) 
 *  
 *  [CHANGE: Note that this definition has been removed as it is already  
 *  defined.]
 */

/*
  struct timeval
  {
    long           tv_sec;
    long           tv_usec;
  } 
 */
  
/*
 *  Retrieving Information About the API Implementation
 */
 
/* 
 *  The LDAPVersion structure is used in retrieving basic information about 
 *  the API implementation.  
 *
 *  Parameters are: 
 *
 *  ver The address of an LDAPVersion structure which is filled in by this 
 *  call.  If ver is NULL, 
 *
 *  The ldap_version() call returns an implementation-specific version 
 *  number multiplied by 100 (this is the same as the sdk_version field of 
 *  the LDAPVersion structure; see below).  
 *
 *  The members of the LDAPVersion structure are: 
 *
 *  sdk_version: An implementation-specific version number multiplied by 
 *  100.  For example, if the API version is 4.0 then this field will be set 
 *  to 400.  
 *
 *  protocol_version: The highest LDAP protocol version supported by the 
 *  implementation multiplied by 100.  For example, if LDAPv3 is the highest 
 *  version support then this field will be set to 300.  
 *
 *  SSL_version: Reserved for implementations that support SSL and TLS (to 
 *  be specified).  
 *
 *  security_level: Reserved for implementations that support SSL and TLS 
 *  (to be specified).  
 *
 *  sdk_vendor: Pointer to a zero-terminated string that contains the name 
 *  of the party that produced this implementation of the LDAP API.  The 
 *  name may be NULL if no name is available.  The data is assumed to be 
 *  static and so the caller of ldap_version() does not need to worry about 
 *  disposing of the memory occupied by the vendor string.  
 *
 *  reserved: Reserved for future expansion (not currently used).  
 *
 */
typedef struct _LDAPVersion
{
  int  sdk_version;       /* Version of the SDK * 100 */
  int  protocol_version;  /* Highest protocol version supported * 100 */
  int  SSL_version;       /* reserved for SSL/TLS */
  int  security_level;    /* reserved for SSL/TLS */
  char *sdk_vendor;       /* Name of the supplier of the SDK */
  int  reserved[3];       /* reserved for future expansion */
} LDAPVersion;

/* 
 *  The ldap_version() call can be used to retrieve some basic information 
 *  about the API implementation.  
 */
ICLLDAPAPI int LDAPAPI
ldap_version(LDAPVersion *ver);

/*
 *  LDAP Error Codes
 */

/* 
 *  Many of the LDAP API routines return LDAP error codes, some of which 
 *  indicate local errors and some of which may be returned by servers.  All 
 *  of the LDAP error codes returned will be positive integers.  All of the 
 *  LDAP error codes returned will be positive integers.  Supported error 
 *  codes are:
 */
#define LDAP_SUCCESS                         0x00
#define LDAP_OPERATIONS_ERROR                0x01
#define LDAP_PROTOCOL_ERROR                  0x02
#define LDAP_TIMELIMIT_EXCEEDED              0x03
#define LDAP_SIZELIMIT_EXCEEDED              0x04
#define LDAP_COMPARE_FALSE                   0x05
#define LDAP_COMPARE_TRUE                    0x06
#define LDAP_STRONG_AUTH_NOT_SUPPORTED       0x07
#define LDAP_STRONG_AUTH_REQUIRED            0x08
#define LDAP_REFERRAL                        0x0a     /* new in LDAPv3        */
#define LDAP_ADMINLIMIT_EXCEEDED             0x0b     /* new in LDAPv3        */
#define LDAP_UNAVAILABLE_CRITICAL_EXTENSION  0x0c     /* new in LDAPv3        */
#define LDAP_CONFIDENTIALITY_REQUIRED        0x0d     /* new in LDAPv3        */
#define LDAP_SASL_BIND_IN_PROGRESS           0x0e     /* new in LDAPv3        */
#define LDAP_NO_SUCH_ATTRIBUTE               0x10
#define LDAP_UNDEFINED_TYPE                  0x11
#define LDAP_INAPPROPRIATE_MATCHING          0x12
#define LDAP_CONSTRAINT_VIOLATION            0x13
#define LDAP_ATTRIBUTE_OR_VALUE_EXISTS       0x14
#define LDAP_INVALID_SYNTAX                  0x15
#define LDAP_NO_SUCH_OBJECT                  0x20
#define LDAP_ALIAS_PROBLEM                   0x21
#define LDAP_INVALID_DN_SYNTAX               0x22
#define LDAP_IS_LEAF                         0x23     /* not used in LDAPv3   */
#define LDAP_ALIAS_DEREF_PROBLEM             0x24
#define LDAP_INAPPROPRIATE_AUTH              0x30
#define LDAP_INVALID_CREDENTIALS             0x31
#define LDAP_INSUFFICIENT_ACCESS             0x32
#define LDAP_BUSY                            0x33
#define LDAP_UNAVAILABLE                     0x34
#define LDAP_UNWILLING_TO_PERFORM            0x35
#define LDAP_LOOP_DETECT                     0x36
#define LDAP_NAMING_VIOLATION                0x40
#define LDAP_OBJECT_CLASS_VIOLATION          0x41
#define LDAP_NOT_ALLOWED_ON_NONLEAF          0x42
#define LDAP_NOT_ALLOWED_ON_RDN              0x43
#define LDAP_ALREADY_EXISTS                  0x44
#define LDAP_NO_OBJECT_CLASS_MODS            0x45
#define LDAP_RESULTS_TOO_LARGE               0x46     /* reserved for CLDAP   */
#define LDAP_AFFECTS_MULTIPLE_DSAS           0x47     /* new in LDAPv3        */
#define LDAP_OTHER                           0x50
#define LDAP_SERVER_DOWN                     0x51
#define LDAP_LOCAL_ERROR                     0x52
#define LDAP_ENCODING_ERROR                  0x53
#define LDAP_DECODING_ERROR                  0x54
#define LDAP_TIMEOUT                         0x55
#define LDAP_AUTH_UNKNOWN                    0x56
#define LDAP_FILTER_ERROR                    0x57
#define LDAP_USER_CANCELLED                  0x58
#define LDAP_PARAM_ERROR                     0x59
#define LDAP_NO_MEMORY                       0x5a
#define LDAP_CONNECT_ERROR                   0x5b
#define LDAP_NOT_SUPPORTED                   0x5c
#define LDAP_CONTROL_NOT_FOUND               0x5d
#define LDAP_NO_RESULTS_RETURNED             0x5e
#define LDAP_MORE_RESULTS_TO_RETURN          0x5f
#define LDAP_CLIENT_LOOP                     0x60
#define LDAP_REFERRAL_LIMIT_EXCEEDED         0x61

/*
 *  Performing LDAP Operations
 */
 
/* 
 *  This section describes each LDAP operation API call in detail.  All 
 *  functions take a "session handle," a pointer to an LDAP structure 
 *  containing per-connection information.  Many routines return results in 
 *  an LDAPMessage structure.  These structures and others are described as 
 *  needed below.  
 */

/* 
 *  Initializing an LDAP Session 
 */
 
/* 
 *  ldap_init() initializes a session with an LDAP server.  The server is 
 *  not actually contacted until an operation is performed that requires it, 
 *  allowing various options to be set after initialization.  
 *
 *  ldap_init() returns a "session handle," a pointer to an opaque structure 
 *  that should be passed to subsequent calls pertaining to the session.  
 *  These routines return NULL if the session cannot be initialized in which 
 *  case the operating system error reporting mechanism can be checked to 
 *  see why the call failed.  
 *
 *  Note that if you connect to an LDAPv2 server, one of the ldap_bind() 
 *  calls described below must be completed before other operations can be 
 *  performed on the session.  LDAPv3 does not require that a bind operation 
 *  be completed before other operations can be performed.  
 *
 *  Parameters are: 
 *
 *  hostname: Contains a space-separated list of hostnames or dotted strings 
 *  representing the IP address of hosts running an LDAP server to connect 
 *  to.  Each hostname in the list can include an optional port number which 
 *  is separated from the host itself with a colon (:) character.  The hosts 
 *  are tried in the order listed, stopping with the first one to which a 
 *  successful connection is made.  Note that only ldap_open() attempts to 
 *  make the connection before returning to the caller.  ldap_init() does 
 *  not connect to the LDAP server.  
 *
 *  portno: Contains the TCP port number to connect to.  The default LDAP 
 *  port of 389 can be obtained by supplying the constant LDAP_PORT.  If a 
 *  host includes a port number then this parameter is ignored.  
 */
ICLLDAPAPI LDAP* LDAPAPI
ldap_init(char *hostname,
          int   portno);

#define LDAP_PORT    389

/* 
 *  Note that use of the following routine is deprecated: 
 *
 *  ICLLDAPAPI LDAP* LDAPAPI
 *  ldap_open(char *hostname,
 *            int   portno);
 */

/* 
 *  LDAP Session Handle Options 
 */

/* 
 *  The calling program can set various attributes of the session by calling 
 *  the LDAP Session Handle Options routines.  
 *
 *  The LDAP session handle returned by ldap_init() is a pointer to an 
 *  opaque data type representing an LDAP session.  Formerly, this data type 
 *  was a structure exposed to the caller, and various fields in the 
 *  structure could be set to control aspects of the session, such as size 
 *  and time limits on searches.  
 *
 *  In the interest of insulating callers from inevitable changes to this 
 *  structure, these aspects of the session are now accessed through a pair 
 *  of accessor functions, described below.  
 */
 
/* 
 *  ldap_get_option() is used to access the current value of various 
 *  session-wide parameters.  
 *
 *  ldap_set_option() is used to set the value of these parameters.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  If this is NULL, a set of global defaults is 
 *  accessed.  New LDAP session handles created with ldap_init() or 
 *  ldap_open() inherit their characteristics from these global defaults.  
 *
 *  option: The name of the option being accessed or set.  This parameter 
 *  should be one of the following constants, which have the indicated 
 *  meanings.  After the constant the actual value of the constant is listed 
 *  in hexadecimal in parentheses followed by the type of the corresponding 
 *  outvalue or invalue parameter.  
 *
 *  LDAP_OPT_DESC (0x01) int *: The underlying socket descriptor corresponding 
 *  to the default LDAP connection.  
 *
 *  LDAP_OPT_DEREF (0x02) int *: Controls how aliases are handled during 
 *  search.  It can have one of the following constants: 
 *
 *  LDAP_DEREF_NEVER (0x00) 
 *
 *  LDAP_DEREF_SEARCHING (0x01) 
 *
 *  LDAP_DEREF_FINDING (0x02) 
 *
 *  LDAP_DEREF_ALWAYS (0x03) 
 *
 *  The LDAP_DEREF_SEARCHING value means aliases should be dereferenced during 
 *  the search but not when locating the base object of the search.  
 *
 *  The LDAP_DEREF_FINDING value means aliases should be dereferenced when 
 *  locating the base object but not during the search.  
 *
 *  LDAP_OPT_SIZELIMIT (0x03) int *: A limit on the number of entries to 
 *  return from a search.  A value of LDAP_NO_LIMIT (0) means no limit.  
 *
 *  LDAP_OPT_TIMELIMIT (0x04) int *: A limit on the number of seconds to spend 
 *  on a search.  A value of LDAP_NO_LIMIT (0) means no limit 
 *
 *  LDAP_OPT_REBIND_FN (0x06) function pointer: See the "Handling 
 *  Re-Authentication (re-bind)" section below.  
 *
 *  LDAP_OPT_REBIND_ARG (0x07) void *: See the "Handling Re-Authentication 
 *  (re-bind)" section below.  
 *
 *  LDAP_OPT_REFERRALS (0x08) void *: This option controls whether the LDAP 
 *  library automatically follows referrals returned by LDAP servers or not.  
 *  It can be set to one of the following constants: 
 *
 *  LDAP_OPT_ON (0x01) 
 *
 *  LDAP_OPT_OFF (0x00).  
 *
 *  LDAP_OPT_RESTART (0x09) void *: This option controls whether LDAP I/O 
 *  operations should automatically be restarted if they abort prematurely.  
 *  It should be set to one of the following constants: 
 *
 *  LDAP_OPT_ON (0x01) 
 *
 *  LDAP_OPT_OFF (0x00).  
 *
 *  This option is useful if an LDAP I/O operation may be interrupted 
 *  prematurely, for example by a timer going off, or other interrrupt.  
 *
 *  LDAP_OPT_PROTOCOL_VERSION (0x11) int *: This option indicates the version 
 *  of the default LDAP server.  It can be one of the following constants: 
 *
 *  LDAP_VERSION2 (0x02) 
 *
 *  LDAP_VERSION3 (0x03).  
 *
 *  If no version is set the default is LDAP_VERSION2 (2).  
 *
 *  LDAP_OPT_SERVER_CONTROLS (0x12) LDAPControl ***: A default list of LDAP 
 *  server controls to be sent with each request.  See the Using Controls 
 *  section below.  
 *
 *  [CHANGE: previously the parameter had type LDAPControl **] 
 *
 *  LDAP_OPT_CLIENT_CONTROLS (0x13) LDAPControl ***: A default list of client 
 *  controls that affect the LDAP session.  See the Using Controls section 
 *  below.  
 *
 *  [CHANGE: previously the parameter had type LDAPControl **] 
 *
 *  LDAP_OPT_HOST_NAME (0x30) char **: The host name of the default LDAP 
 *  server.  
 *
 *  LDAP_OPT_ERROR_NUMBER (0x31) int *: The code of the most recent LDAP error 
 *  that occurred for this session.  
 *
 *  LDAP_OPT_ERROR_STRING (0x32) char **: The message returned with the most 
 *  recent LDAP error that occurred for this session.  
 *
 *  LDAP_OPT_EXT_CONFIG_FILE (0x99) char * Used to supply the full pathname of
 *  the clientconfig.cfg file
 *
 *  outvalue: The address of a place to put the value of the option.  The 
 *  actual type of this parameter depends on the setting of the option 
 *  parameter.  
 *
 *  invalue: A pointer to the value the option is to be given.  The actual 
 *  type of this parameter depends on the setting of the option parameter.  
 *  The constants LDAP_OPT_ON and LDAP_OPT_OFF can be given for options that 
 *  have on or off settings.  
 *
 *  Both ldap_get_option() and ldap_set_option() return 0 if successful and -1 
 *  if an error occurs.  
 */
ICLLDAPAPI int LDAPAPI
ldap_get_option(LDAP *ld,
                int   option,
                void *outvalue);

ICLLDAPAPI int LDAPAPI
ldap_set_option(LDAP *ld,
                int   option,
                void *invalue);

#define LDAP_OPT_DESC              0x01
#define LDAP_OPT_DEREF             0x02
#define LDAP_OPT_SIZELIMIT         0x03
#define LDAP_OPT_TIMELIMIT         0x04
#define LDAP_OPT_REBIND_FN         0x06
#define LDAP_OPT_REBIND_ARG        0x07
#define LDAP_OPT_REFERRALS         0x08
#define LDAP_OPT_RESTART           0x09
#define LDAP_OPT_PROTOCOL_VERSION  0x11
#define LDAP_OPT_SERVER_CONTROLS   0x12
#define LDAP_OPT_CLIENT_CONTROLS   0x13
#define LDAP_OPT_HOST_NAME         0x30
#define LDAP_OPT_ERROR_NUMBER      0x31
#define LDAP_OPT_ERROR_STRING      0x32

#define LDAP_OPT_EXT_CONFIG_FILE   0x99

#define LDAP_OPT_ON                0x01
#define LDAP_OPT_OFF               0x00

#define LDAP_VERSION2              0x02
#define LDAP_VERSION3              0x03

/*
 *  Working with controls. 
 */

/* 
 *  LDAPv3 operations can be extended through the use of controls.  Controls 
 *  may be sent to a server or returned to the client with any LDAP message.  
 *  These controls are referred to as server controls.  
 */
 
/* 
 *  The LDAP API also supports a client-side extension mechanism through the 
 *  use of client controls.  These controls affect the behavior of the LDAP 
 *  API only and are never sent to a server.  A common data structure is 
 *  used to represent both types of controls: 
 *
 *  The fields in the ldapcontrol structure have the following meanings: 
 *
 *  ldctl_oid: The control type, represented as a string.  
 *
 *  ldctl_value: The data associated with the control (if any).  To specify 
 *  a zero-length value, set ldctl_value.bv_len to zero and 
 *  ldctl_value.bv_val to a zero-length string.  To indicate that no data is 
 *  associated with the control, set ldctl_value.bv_val to NULL.  
 *
 *  ldctl_iscritical: Indicates whether the control is critical of not.  If 
 *  this field is non-zero, the operation will only be carried out if the 
 *  control is recognized by the server and/or client.  
 */
typedef struct ldapcontrol
{
  char          *ldctl_oid;
  struct berval  ldctl_value;
  char           ldctl_iscritical;
} LDAPControl, *PLDAPControl;

/* 
 *  Some LDAP API calls allocate an ldapcontrol structure or a NULL- 
 *  terminated array of ldapcontrol structures.  The following routines can 
 *  be used to dispose of a single control or an array of controls.  
 *
 *  A set of controls that affect the entire session can be set using the 
 *  ldap_set_option() function (see above).  A list of controls can also be 
 *  passed directly to some LDAP API calls such as ldap_search_ext(), in 
 *  which case any controls set for the session through the use of 
 *  ldap_set_option() are ignored.  Control lists are represented as a NULL- 
 *  terminated array of pointers to ldapcontrol structures.  
 *
 *  Server controls are defined by LDAPv3 protocol extension documents; for 
 *  example, a control has been proposed to support server-side sorting of 
 *  search results [7].  
 *
 *  No client controls are defined by this API but they may be defined in 
 *  future revisions or in any document that extends this API.  
 */
ICLLDAPAPI void LDAPAPI
ldap_control_free(LDAPControl *ctrl);

ICLLDAPAPI void LDAPAPI
ldap_controls_free(LDAPControl **ctrls);


/*
 *  Authenticating to the directory.
 */
 
/* 
 *  The following functions are used to authenticate an LDAP client to an 
 *  LDAP directory server.  
 */
 
/* 
 *  The ldap_sasl_bind() and ldap_sasl_bind_s() functions can be used to do 
 *  general and extensible authentication over LDAP through the use of the 
 *  Simple Authentication Security Layer [8].  The routines both take the dn 
 *  to bind as, the method to use, as a dotted-string representation of an 
 *  OID identifying the method, and a struct berval holding the credentials.  
 *  The special constant value LDAP_SASL_SIMPLE (NULL) can be passed to 
 *  request simple authentication, or the simplified routines 
 *  ldap_simple_bind() or ldap_simple_bind_s() can be used.  
 *
 *  The ldap_sasl_bind() function initiates an asynchronous bind operation 
 *  and returns the constant LDAP_SUCCESS if the request was successfully 
 *  sent, or another LDAP error code if not.  See the section below on error 
 *  handling for more information about possible errors and how to interpret 
 *  them.  If successful, ldap_sasl_bind() places the message id of the 
 *  request in *msgidp.  A subsequent call to ldap_result(), described 
 *  below, can be used to obtain the result of the bind.  
 *
 *  The ldap_simple_bind() function initiates a simple asynchronous bind 
 *  operation and returns the message id of the operation initiated.  A 
 *  subsequent call to ldap_result(), described below, can be used to obtain 
 *  the result of the bind.  In case of error, ldap_simple_bind() will 
 *  return -1, setting the session error parameters in the LDAP structure 
 *  appropriately.  
 *
 *  The synchronous ldap_sasl_bind_s() and ldap_simple_bind_s() functions 
 *  both return the result of the operation, either the constant 
 *  LDAP_SUCCESS if the operation was successful, or another LDAP error code 
 *  if it was not.  See the section below on error handling for more 
 *  information about possible errors and how to interpret them.  
 *
 *  Note that if an LDAPv2 server is contacted, no other operations over the 
 *  connection should be attempted before a bind call has successfully 
 *  completed.  
 *
 *  Subsequent bind calls can be used to re-authenticate over the same 
 *  connection, and multistep SASL sequences can be accomplished through a 
 *  sequence of calls to ldap_sasl_bind() or ldap_sasl_bind_s().  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry to bind as.  
 *
 *  mechanism: Either LDAP_SASL_SIMPLE (NULL) to get simple authentication, 
 *  or a dotted text string representing an OID identifying the SASL method.  
 *
 *  cred: The credentials with which to authenticate.  Arbitrary credentials 
 *  can be passed using this parameter.  The format and content of the 
 *  credentials depends on the setting of the mechanism parameter.  
 *
 *  passwd: For ldap_simple_bind(), the password to compare to the entry's 
 *  userPassword attribute.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_sasl_bind() call succeeds.  
 *
 *  servercredp: This result parameter will be filled in with the 
 *  credentials passed back by the server for mutual authentication, if 
 *  given.  An allocated berval structure is returned that should be 
 *  disposed of by calling ber_bvfree().  NULL may be passed to ignore this 
 *  field.  
 */
ICLLDAPAPI int LDAPAPI
ldap_sasl_bind(LDAP           *ld,
               char           *dn,
               char           *mechanism,
               struct berval  *cred,
               LDAPControl   **serverctrls,
               LDAPControl   **clientctrls,
               int            *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_sasl_bind_s(LDAP          *ld,
                 char          *dn,
                 char          *mechanism,
                 struct berval *cred,
                 LDAPControl   **serverctrls,
                 LDAPControl   **clientctrls,
                 struct berval **servercredp);

ICLLDAPAPI int LDAPAPI
ldap_simple_bind(LDAP *ld,
                 char *dn,
                 char *passwd);

ICLLDAPAPI int LDAPAPI
ldap_simple_bind_s(LDAP *ld,
                   char *dn,
                   char *passwd);
   
/* 
 *  Note that use of the following routine is deprecated: 
 *
 *  
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_bind(LDAP *ld,
 *            char *dn,
 *            char *cred,
 *            int   method);
 *
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_bind_s(LDAP *ld,
 *              char *dn,
 *              char *cred,
 *              int   method);
 *
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_kerberos_bind(LDAP *ld,
 *                     char *dn);
 *
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_kerberos_bind_s(LDAP *ld,
 *                       char *dn);
 */

/*
 *  Closing the session
 */

/* 
 *  The following functions are used to unbind from the directory, close the 
 *  connection, and dispose of the session handle.  
 *
 *  ldap_unbind() and ldap_unbind_s() both work synchronously, unbinding 
 *  from the directory, closing the connection, and freeing up the ld 
 *  structure before returning.  There is no server response to an unbind 
 *  operation.  ldap_unbind() returns LDAP_SUCCESS (or another LDAP error 
 *  code if the request cannot be sent to the LDAP server).  After a call to 
 *  ldap_unbind() or ldap_unbind_s(), the session handle ld is invalid.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 */
ICLLDAPAPI int LDAPAPI
ldap_unbind(LDAP *ld);

ICLLDAPAPI int LDAPAPI
ldap_unbind_s(LDAP *ld);

/*
 *  Handling re-authentication (re-bind)
 */
 
/* 
 *  The ldap_set_rebind_proc() can be used to install an application- 
 *  provided function which is called by the LDAP library when credentials 
 *  are needed.  Normally this happens when automatic referral chasing is 
 *  enabled when the LDAP library connects to another server and needs to 
 *  re-authenticate.  Calling ldap_set_rebind_proc() is equivalent to making 
 *  two calls to ldap_set_option(), one to set the LDAP_OPT_REBIND_FN option 
 *  and one to set the LDAP_OPT_REBIND_ARG option.  
 *
 *  When the rebindproc is called back by the LDAP library, it will always 
 *  be called twice: one with the freeit argument set to zero and a second 
 *  time with it set to a non-zero number.  On the first call, the 
 *  rebindproc should set the dnp, passwdp, and authmethodp parameters to 
 *  point to the DN, password, and LDAP bind method respectively.  When 
 *  called a second time, the rebindproc will be passed the dnp and passwdp 
 *  parameters so it can clean up any allocated memory.  The LDAP library 
 *  uses the values for DN, password, and bind method between the first call 
 *  to rebindproc and the second one.  
 *
 *  The parameters to ldap_set_rebind_proc() are: 
 *
 *  ld: The session handle.  
 *
 *  rebindproc: A pointer to a function of type LDAP_REBINDPROC_CALLBACK.  
 *
 *  arg: An application-specific argument that is passed intact to the 
 *  rebindproc.  
 */
typedef int(LDAP_REBINDPROC_CALLBACK)(LDAP  *ld,
                                      char **dnp,
                                      char **passwdp,
                                      int   *authmethodp,
                                      int    freeit,
                                      void  *arg);

ICLLDAPAPI void LDAPAPI
ldap_set_rebind_proc(LDAP                     *ld,
                     LDAP_REBINDPROC_CALLBACK *rebindproc,
                     void                     *arg);

/*
 *  Searching
 */
 
/* 
 *  The following functions are used to search the LDAP directory, returning 
 *  a requested set of attributes for each entry matched.  There are five 
 *  variations.  
 *
 *  The ldap_search_ext() function initiates an asynchronous search 
 *  operation and returns the constant LDAP_SUCCESS if the request was 
 *  successfully sent, or another LDAP error code if not.  See the section 
 *  below on error handling for more information about possible errors and 
 *  how to interpret them.  If successful, ldap_search_ext() places the 
 *  message id of the request in *msgidp.  A subsequent call to 
 *  ldap_result(), described below, can be used to obtain the results from 
 *  the search.  These results can be parsed using the result parsing 
 *  routines described in detail later.  
 *
 *  Similar to ldap_search_ext(), the ldap_search() function initiates an 
 *  asynchronous search operation and returns the message id of the 
 *  operation initiated.  As for ldap_search_ext(), a subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  search. [CHANGE: draft says bind]  In case of error, ldap_search() will  
 *  return -1, setting the session error parameters in the LDAP structure  
 *  appropriately.
 *
 *  The synchronous ldap_search_ext_s(), ldap_search_s(), and 
 *  ldap_search_st() functions all return the result of the operation, 
 *  either the constant LDAP_SUCCESS if the operation was successful, or 
 *  another LDAP error code if it was not.  See the section below on error 
 *  handling for more information about possible errors and how to interpret 
 *  them.  Entries returned from the search (if any) are contained in the 
 *  res parameter.  This parameter is opaque to the caller.  Entries, 
 *  attributes, values, etc., should be extracted by calling the parsing 
 *  routines described below.  The results contained in res should be freed 
 *  when no longer in use by calling ldap_msgfree(), described later.  
 *
 *  The ldap_search_ext() and ldap_search_ext_s() functions support LDAPv3 
 *  server controls, client controls, and allow varying size and time limits 
 *  to be easily specified for each search operation.  The ldap_search_st() 
 *  function is identical to ldap_search_s() except that it takes an 
 *  additional parameter specifying a local timeout for the search.  The 
 *  local search timeout is used to limit the amount of time the API 
 *  implementation will wait for a search to complete.  After the local 
 *  search timeout expires, the API implementation will send an abandon 
 *  operation to abort the search operation.  
 *
 *  There are three options in the session handle ld which potentially 
 *  affect how the search is performed.  They are: 
 *
 *  LDAP_OPT_SIZELIMIT A limit on the number of entries to return from the 
 *  search.  A value of LDAP_NO_LIMIT (0) means no limit.  Note that the 
 *  value from the session handle is ignored when using the 
 *  ldap_search_ext() or ldap_search_ext_s() functions.  
 *
 *  LDAP_OPT_TIMELIMIT A limit on the number of seconds to spend on the 
 *  search.  A value of LDAP_NO_LIMIT (0) means no limit.  Note that the 
 *  value from the session handle is ignored when using the 
 *  ldap_search_ext() or ldap_search_ext_s() functions.  
 *
 *  LDAP_OPT_DEREF One of LDAP_DEREF_NEVER (0x00), LDAP_DEREF_SEARCHING 
 *  (0x01), LDAP_DEREF_FINDING (0x02), or LDAP_DEREF_ALWAYS (0x03), 
 *  specifying how aliases should be handled during the search.  The 
 *  LDAP_DEREF_SEARCHING value means aliases should be dereferenced during 
 *  the search but not when locating the base object of the search.  The 
 *  LDAP_DEREF_FINDING value means aliases should be dereferenced when 
 *  locating the base object but not during the search.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  base: The dn of the entry at which to start the search.  
 *
 *  scope: One of the following constant values: 
 *
 *  LDAP_SCOPE_BASE (0x00) 
 *
 *  LDAP_SCOPE_ONELEVEL (0x01) 
 *
 *  LDAP_SCOPE_SUBTREE (0x02) 
 *
 *  indicating the scope of the search.  
 *
 *  filter: A character string as described in [3], representing the search 
 *  filter.  
 *
 *  attrs: A NULL-terminated array of strings indicating which attributes to 
 *  return for each matching entry.  Passing NULL for this parameter causes 
 *  all available user attributes to be retrieved.  The special constant 
 *  string LDAP_NO_ATTRS ("1.1") can be used as the only in the array to 
 *  indicate that no attribute types should be returned by the server.  The 
 *  special constant string LDAP_ALL_USER_ATTRS ("*") can be used in the 
 *  attrs array along with the names of some operational attributes to 
 *  indicate that all user attributes plus the listed operational attributes 
 *  should be returned.  
 *
 *  attrsonly: A boolean value that should be zero if both attribute types 
 *  and values are to be returned, non-zero if only types are wanted.  
 *
 *  timeout: For the ldap_search_st() function, this specifies the local 
 *  search timeout value (if it is NULL, the timeout is infinite).  For the 
 *  ldap_search_ext() and ldap_search_ext_s() functions, this specifies both 
 *  the local search timeout value and the operation time limit that is sent 
 *  to the server within the search request.  For the ldap_search_ext() and 
 *  ldap_search_ext_s() functions, passing a NULL value for timeout causes 
 *  the global default timeout stored in the LDAP session handle to be used 
 *  (set by using ldap_set_option() with the LDAP_OPT_TIMELIMIT parameter).  
 *
 *  sizelimit: For the ldap_search_ext() and ldap_search_ext_s() calls, this 
 *  is a limit on the number of entries to return from the search.  A value 
 *  of LDAP_NO_LIMIT (0) means no limit.  
 *
 *  res: For the synchronous calls, this is a result parameter which will 
 *  contain the results of the search upon completion of the call.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_search_ext() call succeeds.  
 */
ICLLDAPAPI int LDAPAPI
ldap_search_ext(LDAP            *ld,
                char            *base,
                int              scope,
                char            *filter,
                char           **attrs,
                int              attrsonly,
                LDAPControl    **serverctrls,
                LDAPControl    **clientctrls,
                struct timeval  *timeoutp,
                int              sizelimit,
                int             *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_search_ext_s(LDAP            *ld,
                  char            *base,
                  int              scope,
                  char            *filter,
                  char           **attrs,
                  int              attrsonly,
                  LDAPControl    **serverctrls,
                  LDAPControl    **clientctrls,
                  struct timeval  *timeoutp,
                  int              sizelimit,
                  LDAPMessage    **res);

ICLLDAPAPI int LDAPAPI
ldap_search(LDAP  *ld,
            char  *base,
            int    scope,
            char  *filter,
            char **attrs,
            int    attrsonly);

ICLLDAPAPI int LDAPAPI
ldap_search_s(LDAP         *ld,
              char         *base,
              int           scope,
              char         *filter,
              char        **attrs,
              int           attrsonly,
              LDAPMessage **res);

ICLLDAPAPI int LDAPAPI
ldap_search_st(LDAP            *ld,
               char            *base,
               int              scope,
               char            *filter,
               char           **attrs,
               int              attrsonly,
               struct timeval  *timeout,
               LDAPMessage    **res);


#define  LDAP_SCOPE_BASE       0x00
#define  LDAP_SCOPE_ONELEVEL   0x01
#define  LDAP_SCOPE_SUBTREE    0x02

#define  LDAP_NO_LIMIT         0

#define LDAP_DEREF_NEVER       0x00
#define LDAP_DEREF_SEARCHING   0x01
#define LDAP_DEREF_FINDING     0x02
#define LDAP_DEREF_ALWAYS      0x03

/* 
 *  Note that LDAP does not support a read operation directly.  Instead, 
 *  this operation is emulated by a search with base set to the DN of the 
 *  entry to read, scope set to LDAP_SCOPE_BASE, and filter set to 
 *  "(objectclass=*)".  attrs contains the list of attributes to return.  
 *
 *  Note also that LDAP does not support a list operation directly.  
 *  Instead, this operation is emulated by a search with base set to the DN 
 *  of the entry to list, scope set to LDAP_SCOPE_ONELEVEL, and filter set 
 *  to "(objectclass=*)".  attrs contains the list of attributes to return 
 *  for each child entry.  
 */
 
/*
 *  Comparing a Value Against an Entry
 */

/* 
 *  The following routines are used to compare a given attribute value 
 *  assertion against an LDAP entry.  There are four variations: 
 *
 *  The ldap_compare_ext() function initiates an asynchronous compare 
 *  operation and returns the constant LDAP_SUCCESS if the request was 
 *  successfully sent, or another LDAP error code if not.  See the section 
 *  below on error handling for more information about possible errors and 
 *  how to interpret them.  If successful, ldap_compare_ext() places the 
 *  message id of the request in *msgidp.  A subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  compare.  
 *
 *  Similar to ldap_compare_ext(), the ldap_compare() function initiates an 
 *  asynchronous compare operation and returns the message id of the 
 *  operation initiated.  As for ldap_compare_ext(), a subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  bind.  In case of error, ldap_compare() will return -1, setting the 
 *  session error parameters in the LDAP structure appropriately.  
 *
 *  The synchronous ldap_compare_ext_s() and ldap_compare_s() functions both 
 *  return the result of the operation, either the constant LDAP_SUCCESS if 
 *  the operation was successful, or another LDAP error code if it was not.  
 *  See the section below on error handling for more information about 
 *  possible errors and how to interpret them.  
 *
 *  The ldap_compare_ext() and ldap_compare_ext_s() functions support LDAPv3 
 *  server controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry to compare against.  
 *
 *  attr: The attribute to compare against.  
 *
 *  bvalue: The attribute value to compare against those found in the given 
 *  entry.  This parameter is used in the extended routines and is a pointer 
 *  to a struct berval so it is possible to compare binary values.  
 *
 *  value: A string attribute value to compare against, used by the 
 *  ldap_compare() and ldap_compare_s() functions.  Use ldap_compare_ext() 
 *  or ldap_compare_ext_s() if you need to compare binary values.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_compare_ext() call succeeds.  
 */
ICLLDAPAPI int LDAPAPI
ldap_compare_ext(LDAP           *ld,
                 char           *dn,
                 char           *attr,
                 struct berval  *bvalue,
                 LDAPControl   **serverctrls,
                 LDAPControl   **clientctrls,
                 int            *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_compare_ext_s(LDAP           *ld,
                   char           *dn,
                   char           *attr,
                   struct berval  *bvalue,
                   LDAPControl   **serverctrls,
                   LDAPControl   **clientctrls);

ICLLDAPAPI int LDAPAPI
ldap_compare(LDAP *ld,
             char *dn,
             char *attr,
             char *value);

ICLLDAPAPI int LDAPAPI
ldap_compare_s(LDAP *ld,
               char *dn,
               char *attr,
               char *value);

/*
 *  Modifying an entry
 */

/* 
 *  The following routines are used to modify an existing LDAP entry.  There 
 *  are four variations: 
 *
 *  The ldap_modify_ext() function initiates an asynchronous modify 
 *  operation and returns the constant LDAP_SUCCESS if the request was 
 *  successfully sent, or another LDAP error code if not.  See the section 
 *  below on error handling for more information about possible errors and 
 *  how to interpret them.  If successful, ldap_modify_ext() places the 
 *  message id of the request in *msgidp.  A subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  modify.  
 *
 *  Similar to ldap_modify_ext(), the ldap_modify() function initiates an 
 *  asynchronous modify operation and returns the message id of the 
 *  operation initiated.  As for ldap_modify_ext(), a subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  modify.  In case of error, ldap_modify() will return -1, setting the 
 *  session error parameters in the LDAP structure appropriately.  
 *
 *  The synchronous ldap_modify_ext_s() and ldap_modify_s() functions both 
 *  return the result of the operation, either the constant LDAP_SUCCESS if 
 *  the operation was successful, or another LDAP error code if it was not.  
 *  See the section below on error handling for more information about 
 *  possible errors and how to interpret them.  
 *
 *  The ldap_modify_ext() and ldap_modify_ext_s() functions support LDAPv3 
 *  server controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry to modify.  
 *
 *  mods: A NULL-terminated array of modifications to make to the entry.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_modify_ext() call succeeds.  
 *
 *  The fields in the LDAPMod structure have the following meanings: 
 *
 *  mod_op: The modification operation to perform.  It should be one of the 
 *  following constants: 
 *
 *  LDAP_MOD_ADD (0x00) 
 *
 *  LDAP_MOD_DELETE (0x01) 
 *
 *  LDAP_MOD_REPLACE (0x02).  
 *
 *  This field also indicates the type of values included in the mod_vals 
 *  union.  It is logically ORed with the constant LDAP_MOD_BVALUES (0x80) 
 *  to select the mod_bvalues form.  Otherwise, the mod_values form is used.  
 *
 *  mod_type: The type of the attribute to modify.  
 *
 *  mod_vals: The values (if any) to add, delete, or replace.  Only one of 
 *  the mod_values or mod_bvalues variants should be used, selected by ORing 
 *  the mod_op field with the constant LDAP_MOD_BVALUES.  mod_values is a 
 *  NULL-terminated array of zero-terminated strings and mod_bvalues is a 
 *  NULL-terminated array of berval structures that can be used to pass 
 *  binary values such as images.  
 *
 *  For LDAP_MOD_ADD modifications, the given values are added to the entry, 
 *  creating the attribute if necessary.  
 *
 *  For LDAP_MOD_DELETE modifications, the given values are deleted from the 
 *  entry, removing the attribute if no values remain.  If the entire 
 *  attribute is to be deleted, the mod_vals field should be set to NULL.  
 *
 *  For LDAP_MOD_REPLACE modifications, the attribute will have the listed 
 *  values after the modification, having been created if necessary, or 
 *  removed if the mod_vals field is NULL.  All modifications are performed 
 *  in the order in which they are listed.  
 */
typedef struct ldapmod
{
  int   mod_op;
  char *mod_type;
  union
  {
    char          **modv_strvals;
    struct berval **modv_bvals;
  } mod_vals;
} LDAPMod;

#define mod_values         mod_vals.modv_strvals
#define mod_bvalues        mod_vals.modv_bvals
#define LDAP_MOD_BVALUES   0x80
           
ICLLDAPAPI int LDAPAPI
ldap_modify_ext(LDAP         *ld,
                char         *dn,
                LDAPMod     **mods,
                LDAPControl **serverctrls,
                LDAPControl **clientctrls,
                int          *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_modify_ext_s(LDAP         *ld,
                  char         *dn,
                  LDAPMod     **mods,
                  LDAPControl **serverctrls,
                  LDAPControl **clientctrls);

ICLLDAPAPI int LDAPAPI
ldap_modify(LDAP     *ld,
            char     *dn,
            LDAPMod **mods);

ICLLDAPAPI int LDAPAPI
ldap_modify_s(LDAP     *ld,
              char     *dn,
              LDAPMod **mods);

#define  LDAP_MOD_ADD        0x00
#define  LDAP_MOD_DELETE     0x01
#define  LDAP_MOD_REPLACE    0x02


/*
 *  Modifying the Name of an Entry
 */
 
/* 
 *  In LDAPv2, the ldap_modrdn() and ldap_modrdn_s() routines were used to 
 *  change the name of an LDAP entry.  They could only be used to change the 
 *  least significant component of a name (the RDN or relative distinguished 
 *  name).  LDAPv3 provides the Modify DN protocol operation that allows 
 *  more general name change access.  The ldap_rename() and ldap_rename_s() 
 *  routines are used to change the name of an entry, and the use of the 
 *  ldap_modrdn() and ldap_modrdn_s() routines is deprecated.  
 *
 *  The ldap_rename() function initiates an asynchronous modify DN operation 
 *  and returns the constant LDAP_SUCCESS if the request was successfully 
 *  sent, or another LDAP error code if not.  See the section below on error 
 *  handling for more information about possible errors and how to interpret 
 *  them.  If successful, ldap_rename() places the DN message id of the 
 *  request in *msgidp.  A subsequent call to ldap_result(), described 
 *  below, can be used to obtain the result of the rename.  
 *
 *  The synchronous ldap_rename_s() returns the result of the operation, 
 *  either the constant LDAP_SUCCESS if the operation was successful, or 
 *  another LDAP error code if it was not.  See the section below on error 
 *  handling for more information about possible errors and how to interpret 
 *  them.  
 *
 *  The ldap_rename() and ldap_rename_s() functions both support LDAPv3 
 *  server controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry whose DN is to be changed.  
 *
 *  newrdn: The new RDN to give the entry.  
 *
 *  newparent: The new parent, or superior entry.  If this parameter is 
 *  NULL, only the RDN of the entry is changed.  The root DN may be 
 *  specified by passing a zero length string, "".  The newparent parameter 
 *  should always be NULL when using version 2 of the LDAP protocol; 
 *  otherwise the server's behavior is undefined.  
 *
 *  deleteoldrdn: This parameter only has meaning on the rename routines if 
 *  newrdn is different than the old RDN.  It is a boolean value, if 
 *  non-zero indicating that the old RDN value(s) should be removed, if zero 
 *  indicating that the old RDN value(s) should be retained as 
 *  non-distinguished values of the entry.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_rename() call succeeds.  
 */
ICLLDAPAPI int LDAPAPI
ldap_rename(LDAP         *ld,
            char         *dn,
            char         *newrdn,
            char         *newparent,
            int           deleteoldrdn,
            LDAPControl **serverctrls,
            LDAPControl **clientctrls,
            int          *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_rename_s(LDAP         *ld,
              char         *dn,
              char         *newrdn,
              char         *newparent,
              int           deleteoldrdn,
              LDAPControl **serverctrls,
              LDAPControl **clientctrls);

/*
 *  Note that use of the following routines is deprecated.
 *            
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_modrdn(LDAP *ld,
 *              char *dn,
 *              char *newrdn,
 *              int   deleteoldrdn);
 *
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_modrdn_s(LDAP *ld,
 *                char *dn,
 *                char *newrdn,
 *                int   deleteoldrdn);
 */

/*
 *  Adding an entry.
 */
 
/* 
 *  The following functions are used to add entries to the LDAP directory.  
 *  There are four variations.  
 *
 *  Note that the parent of the entry being added must already exist or the 
 *  parent must be empty (i.e., equal to the root DN) for an add to succeed.  
 *
 *  The ldap_add_ext() function initiates an asynchronous add operation and 
 *  returns the constant LDAP_SUCCESS if the request was successfully sent, 
 *  or another LDAP error code if not.  See the section below on error 
 *  handling for more information about possible errors and how to interpret 
 *  them.  If successful, ldap_add_ext() places the message id of the 
 *  request in *msgidp.  A subsequent call to ldap_result(), described 
 *  below, can be used to obtain the result of the add.  
 *
 *  Similar to ldap_add_ext(), the ldap_add() function initiates an 
 *  asynchronous add operation and returns the message id of the operation 
 *  initiated.  As for ldap_add_ext(), a subsequent call to ldap_result(), 
 *  described below, can be used to obtain the result of the add.  In case 
 *  of error, ldap_add() will return -1, setting the session error 
 *  parameters in the LDAP structure appropriately.  
 *
 *  The synchronous ldap_add_ext_s() and ldap_add_s() functions both return 
 *  the result of the operation, either the constant LDAP_SUCCESS if the 
 *  operation was successful, or another LDAP error code if it was not.  See 
 *  the section below on error handling for more information about possible 
 *  errors and how to interpret them.  
 *
 *  The ldap_add_ext() and ldap_add_ext_s() functions support LDAPv3 server 
 *  controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry to add.  
 *
 *  attrs: The entry's attributes, specified using the LDAPMod structure 
 *  defined for ldap_modify().  The mod_type and mod_vals fields should be 
 *  filled in.  The mod_op field is ignored unless ORed with the constant 
 *  LDAP_MOD_BVALUES, used to select the mod_bvalues case of the mod_vals 
 *  union.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_add_ext() call succeeds.  
 */
ICLLDAPAPI int LDAPAPI
ldap_add_ext(LDAP         *ld,
             char         *dn,
             LDAPMod     **attrs,
             LDAPControl **serverctrls,
             LDAPControl **clientctrls,
             int          *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_add_ext_s(LDAP         *ld,
               char         *dn,
               LDAPMod     **attrs,
               LDAPControl **serverctrls,
               LDAPControl **clientctrls);

ICLLDAPAPI int LDAPAPI
ldap_add(LDAP     *ld,
         char     *dn,
         LDAPMod **attrs);

ICLLDAPAPI int LDAPAPI
ldap_add_s(LDAP     *ld,
           char     *dn,
           LDAPMod **attrs);

/*
 *  Deleting an entry.
 */

/* 
 *  The following functions are used to delete a leaf entry from the LDAP 
 *  directory.  There are four variations.  
 *
 *  Note that the entry to delete must be a leaf entry (i.e., it must have 
 *  no children).  Deletion of entire subtrees in a single operation is not 
 *  supported by LDAP.  
 *
 *  The ldap_delete_ext() function initiates an asynchronous delete 
 *  operation and returns the constant LDAP_SUCCESS if the request was 
 *  successfully sent, or another LDAP error code if not.  See the section 
 *  below on error handling for more information about possible errors and 
 *  how to interpret them.  If successful, ldap_delete_ext() places the 
 *  message id of the request in *msgidp.  A subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  delete.  
 *
 *  Similar to ldap_delete_ext(), the ldap_delete() function initiates an 
 *  asynchronous delete operation and returns the message id of the 
 *  operation initiated.  As for ldap_delete_ext(), a subsequent call to 
 *  ldap_result(), described below, can be used to obtain the result of the 
 *  delete.  In case of error, ldap_delete() will return -1, setting the 
 *  session error parameters in the LDAP structure appropriately.  
 *
 *  The synchronous ldap_delete_ext_s() and ldap_delete_s() functions both 
 *  return the result of the operation, either the constant LDAP_SUCCESS if 
 *  the operation was successful, or another LDAP error code if it was not.  
 *  See the section below on error handling for more information about 
 *  possible errors and how to interpret them.  
 *
 *  The ldap_delete_ext() and ldap_delete_ext_s() functions support LDAPv3 
 *  server controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  dn: The name of the entry to delete.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_delete_ext() call succeeds.  
 */
ICLLDAPAPI int LDAPAPI
ldap_delete_ext(LDAP         *ld,
                char         *dn,
                LDAPControl **serverctrls,
                LDAPControl **clientctrls,
                int          *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_delete_ext_s(LDAP         *ld,
                  char         *dn,
                  LDAPControl **serverctrls,
                  LDAPControl **clientctrls);

ICLLDAPAPI int LDAPAPI
ldap_delete(LDAP *ld,
            char *dn);

ICLLDAPAPI int LDAPAPI
ldap_delete_s(LDAP *ld,
              char *dn);

/*
 *  Extended Operations.
 */

/* 
 *  The ldap_extended_operation() and ldap_extended_operation_s() routines 
 *  allow extended LDAP operations to be passed to the server, providing a 
 *  general protocol extensibility mechanism.  
 *
 *  The ldap_extended_operation() function initiates an asynchronous 
 *  extended operation and returns the constant LDAP_SUCCESS if the request 
 *  was successfully sent, or another LDAP error code if not.  See the 
 *  section below on error handling for more information about possible 
 *  errors and how to interpret them.  If successful, 
 *  ldap_extended_operation() places the message id of the request in 
 *  *msgidp.  A subsequent call to ldap_result(), described below, can be 
 *  used to obtain the result of the extended operation which can be passed 
 *  to ldap_parse_extended_result() to obtain the OID and data contained in 
 *  the response.  
 *
 *  The synchronous ldap_extended_operation_s() function returns the result 
 *  of the operation, either the constant LDAP_SUCCESS if the operation was 
 *  successful, or another LDAP error code if it was not.  See the section 
 *  below on error handling for more information about possible errors and 
 *  how to interpret them.  The retoid and retdata parameters are filled in 
 *  with the OID and data from the response.  If no OID or data was 
 *  returned, these parameters are set to NULL.  
 *
 *  The ldap_extended_operation() and ldap_extended_operation_s() functions 
 *  both support LDAPv3 server controls and client controls.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  exoid: The dotted-OID text string naming the request.  
 *  [CHANGE: Draft says requestoid]
 *
 *  exdata: The arbitrary data required by the operation (if NULL, no data 
 *  is sent to the server).  
 *  [CHANGE: Draft says requestdata]
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 *
 *  msgidp: This result parameter will be set to the message id of the 
 *  request if the ldap_extended_operation() call succeeds.  
 *
 *  retoidp: Pointer to a character string that will be set to an allocated, 
 *  dotted-OID text string returned by the server.  This string should be 
 *  disposed of using the ldap_memfree() function.  If no OID was returned, 
 *  *retoidp is set to NULL.  
 *
 *  retdatap: Pointer to a berval structure pointer that will be set an 
 *  allocated copy of the data returned by the server.  This struct berval 
 *  should be disposed of using ber_bvfree().  If no data is returned, 
 *  *retdatap is set to NULL.  
 */
ICLLDAPAPI int LDAPAPI
ldap_extended_operation(LDAP           *ld,
                        char           *exoid,
                        struct berval  *exdata,
                        LDAPControl   **serverctrls,
                        LDAPControl   **clientctrls,
                        int            *msgidp);

ICLLDAPAPI int LDAPAPI
ldap_extended_operation_s(LDAP           *ld,
                          char           *exoid,
                          struct berval  *exdata,
                          LDAPControl   **serverctrls,
                          LDAPControl   **clientctrls,
                          char          **retoidp,
                          struct berval **retdatap);

/*
 * The following calls are specifically for use with TLS.
 * 
 * ldap_api_tls_connect() is used to initiaite a TLS secure connection
 * between the calling LDAP client and the directory server. It can be
 * used in two distinct ways. Firstly it can be used to invoke a secure
 * connection before any LDAP operations are initiated so that all
 * subsequent LDAP operations on the connection are secured. Secondly
 * it can be used to convert an existing unsecure LDAP V3 connection
 * to a secure one following a successful 'Start TLS' LDAP V3 extended
 * operation. The client_data parameter can be used to pass client specific
 * data, the client_data_len parameter is also user defined. Both the
 * client_data parameters are passed through transparently.
 *
 * ldap_api_tls_close() is used to close a secure connection. It can
 * be invoked by the client on an existing LDAP V3 secure connection
 * such that the connection is left active but unsecure.
 */

ICLLDAPAPI int LDAPAPI
ldap_api_tls_close(LDAP *ld);

ICLLDAPAPI int LDAPAPI
ldap_api_tls_connect(LDAP *ld,
					 void *client_data,
					 int client_data_len);


/*
 *  Abandoning An Operation.
 */
 
/* 
 *  The following calls are used to abandon an operation in progress.  
 *
 *  ldap_abandon_ext() abandons the operation with message id msgid and 
 *  returns the constant LDAP_SUCCESS if the abandon was successful or 
 *  another LDAP error code if not.  See the section below on error handling 
 *  for more information about possible errors and how to interpret them.  
 *
 *  ldap_abandon() is identical to ldap_abandon_ext() except that it does 
 *  not accept client or server controls and it returns zero if the abandon 
 *  was successful, -1 otherwise and does not support LDAPv3 server controls 
 *  or client controls.  
 *
 *  After a successful call to ldap_abandon() or ldap_abandon_ext(), results 
 *  with the given message id are never returned from a subsequent call to 
 *  ldap_result().  There is no server response to LDAP abandon operations.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  msgid: The message id of the request to be abandoned.  
 *
 *  serverctrls: List of LDAP server controls.  
 *
 *  clientctrls: List of client controls.  
 */
ICLLDAPAPI int LDAPAPI
ldap_abandon_ext(LDAP         *ld,
                 int           msgid,
                 LDAPControl **serverctrls,
                 LDAPControl **clientctrls);

ICLLDAPAPI int LDAPAPI
ldap_abandon(LDAP *ld,
             int   msgid);

/*
 *  Obtaining Results and Peeking Inside LDAP Messages.
 */

/* 
 *  ldap_result() is used to obtain the result of a previous asynchronously 
 *  initiated operation.  Note that depending on how it is called, 
 *  ldap_result() may actually return a list or "chain" of messages.  
 *
 *  ldap_msgfree() frees the results obtained from a previous call to 
 *  ldap_result(), or a synchronous search routine.  
 *
 *  ldap_msgtype() returns the type of an LDAP message.  ldap_msgid() 
 *  returns the message ID of an LDAP message.  
 *
 *  Upon successful completion, ldap_result() returns the type of the first 
 *  result returned in the res parameter.  This will be one of the following 
 *  constants.  
 *
 *  LDAP_RES_BIND (0x61)
 *  
 *  LDAP_RES_SEARCH_ENTRY (0x64)
 *  
 *  LDAP_RES_SEARCH_REFERENCE (0x73) -- new in LDAPv3
 *  
 *  LDAP_RES_SEARCH_RESULT (0x65)
 *  
 *  LDAP_RES_MODIFY (0x67)
 *  
 *  LDAP_RES_ADD (0x69)
 *  
 *  LDAP_RES_DELETE (0x6B)
 *  
 *  LDAP_RES_MODDN (0x6D)
 *  
 *  LDAP_RES_COMPARE (0x6F)
 *  
 *  LDAP_RES_EXTENDED (0x78) -- new in LDAPv3 
 *
 *  ldap_result() returns 0 if the timeout expired and -1 if an error 
 *  occurs, in which case the error parameters of the LDAP session handle 
 *  will be set accordingly.  
 *
 *  ldap_msgfree() frees the result structure pointed to by res and returns 
 *  the type of the message it freed.  
 *
 *  ldap_msgtype() returns the type of the LDAP message it is passed as a 
 *  parameter.  The type will be one of the types listed above, or -1 on 
 *  error.  
 *
 *  ldap_msgid() returns the message ID associated with the LDAP message 
 *  passed as a parameter.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  msgid: The message id of the operation whose results are to be returned, 
 *  or the constant LDAP_RES_ANY (-1) if any result is desired.  
 *
 *  all: Specifies how many messages will be retrieved in a single call to 
 *  ldap_result().  This parameter only has meaning for search results.  
 *  Pass the constant LDAP_MSG_ONE (0x00) to retrieve one message at a time.  
 *  Pass LDAP_MSG_ALL (0x01) to request that all results of a search be 
 *  received before returning all results in a single chain.  Pass 
 *  LDAP_MSG_RECEIVED (0x02) to indicate that all results retrieved so far 
 *  should be returned in the result chain.  
 *
 *  timeout: A timeout specifying how long to wait for results to be 
 *  returned.  A NULL value causes ldap_result() to block until results are 
 *  available.  A timeout value of zero seconds specifies a polling 
 *  behavior.  
 *
 *  res: For ldap_result(), a result parameter that will contain the 
 *  result(s) of the operation.  For ldap_msgfree(), the result chain to be 
 *  freed, obtained from a previous call to ldap_result(), ldap_search_s(), 
 *  or ldap_search_st().  
 */
ICLLDAPAPI int LDAPAPI
ldap_result(LDAP            *ld,
            int              msgid,
            int              all,
            struct timeval  *timeout,
            LDAPMessage    **res);

ICLLDAPAPI int LDAPAPI
ldap_msgfree(LDAPMessage *res);

ICLLDAPAPI int LDAPAPI
ldap_msgtype(LDAPMessage *res);

ICLLDAPAPI int LDAPAPI
ldap_msgid(LDAPMessage *res);

#define  LDAP_RES_BIND              0x61
#define  LDAP_RES_SEARCH_ENTRY      0x64
#define  LDAP_RES_SEARCH_REFERENCE  0x73  /* new in LDAPv3                    */
#define  LDAP_RES_SEARCH_RESULT     0x65
#define  LDAP_RES_MODIFY            0x67
#define  LDAP_RES_ADD               0x69
#define  LDAP_RES_DELETE            0x6B
#define  LDAP_RES_MODDN             0x6D
#define  LDAP_RES_COMPARE           0x6F
#define  LDAP_RES_EXTENDED          0x78  /* new in LDAPv3                    */

#define  LDAP_MSG_ONE               0
#define  LDAP_MSG_ALL               1
#define  LDAP_MSG_RECEIVED          2

#define  LDAP_RES_ANY               -1

/*
 *  Handling Errors and Parsing Results
 */

/* 
 *  The following calls are used to extract information from results and 
 *  handle errors returned by other LDAP API routines.  
 *
 *  All three of the ldap_parse_*_result() routines skip over messages of 
 *  type LDAP_RES_SEARCH_ENTRY and LDAP_RES_SEARCH_REFERENCE when looking 
 *  for a result message to parse.  They return the constant LDAP_SUCCESS if 
 *  the result was successfully parsed and another LDAP error code if not.  
 *  Note that the LDAP error code that indicates the outcome of the 
 *  operation performed by the server is placed in the errcodep 
 *  ldap_parse_result() parameter. [CHANGE: This parameter is undefined if  
 *  the result did not parse correctly].  
 *
 *  ldap_err2string() is used to convert a numeric LDAP error code, as 
 *  returned by one of the three ldap_parse_*_result() routines, or one of 
 *  the synchronous API operation calls, into an informative zero-terminated 
 *  character string message describing the error.  It returns a pointer to 
 *  static data.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  res: The result of an LDAP operation as returned by ldap_result() or one 
 *  of the synchronous API operation calls.  
 *
 *  errcodep: This result parameter will be filled in with the LDAP error 
 *  code field from the LDAPResult message.  This is the indication from the 
 *  server of the outcome of the operation.  NULL may be passed to ignore 
 *  this field.  
 *
 *  matcheddnp: In the case of a return of LDAP_NO_SUCH_OBJECT, this result 
 *  parameter will be filled in with a DN indicating how much of the name in 
 *  the request was recognized.  NULL may be passed to ignore this field.  
 *  The matched DN string should be freed by calling ldap_memfree() which is 
 *  described later in this document.  
 *
 *  errmsgp: This result parameter will be filled in with the contents of 
 *  the error message field from the LDAPResult message.  The error message 
 *  string should be freed by calling ldap_memfree() which is described 
 *  later in this document.  NULL may be passed to ignore this field.  
 *
 *  referralsp: This result parameter will be filled in with the contents of 
 *  the referrals field from the LDAPResult message, indicating zero or more 
 *  alternate LDAP servers where the request should be retried.  The 
 *  referrals array should be freed by calling ldap_value_free() which is 
 *  described later in this document.  NULL may be passed to ignore this 
 *  field.  
 *
 *  serverctrlsp: This result parameter will be filled in with an allocated 
 *  array of controls copied out of the LDAPResult message.  The control 
 *  array should be freed by calling ldap_controls_free() which was 
 *  described earlier.  
 *
 *  freeit: A boolean that determines whether the res parameter is disposed 
 *  of or not.  Pass any non-zero value to have these routines free res 
 *  after extracting the requested information.  This is provided as a 
 *  convenience; you can also use ldap_msgfree() to free the result later.  
 *
 *  servercredp: For SASL bind results, this result parameter will be filled 
 *  in with the credentials passed back by the server for mutual 
 *  authentication, if given.  An allocated berval structure is returned 
 *  that should be disposed of by calling ber_bvfree().  NULL may be passed 
 *  to ignore this field.  
 *
 *  resultoidp: For extended results, this result parameter will be filled 
 *  in with the dotted-OID text representation of the name of the extended 
 *  operation response.  This string should be disposed of by calling 
 *  ldap_memfree().  NULL may be passed to ignore this field.  
 *
 *  resultdatap: For extended results, this result parameter will be filled 
 *  in with a pointer to a struct berval containing the data in the extended 
 *  operation response.  It should be disposed of by calling ber_bvfree().  
 *  NULL may be passed to ignore this field.  
 *
 *  err: For ldap_err2string(), an LDAP error code, as returned by 
 *  ldap_parse_result() or another LDAP API call.  
 */
ICLLDAPAPI int LDAPAPI
ldap_parse_result(LDAP          *ld,
                  LDAPMessage   *res,
                  int           *errcodep,
                  char         **matcheddnp,
                  char         **errmsgp,
                  char        ***referralsp,
                  LDAPControl ***serverctrlsp,
                  int            freeit);

ICLLDAPAPI int LDAPAPI
ldap_parse_sasl_bind_result(LDAP           *ld,
                            LDAPMessage    *res,
                            struct berval **servercredp,
                            int             freeit);

ICLLDAPAPI int LDAPAPI
ldap_parse_extended_result(LDAP           *ld,
                           LDAPMessage    *res,
                           char          **resultoidp,
                           struct berval **resultdatap,
                           int             freeit);


ICLLDAPAPI char* LDAPAPI
ldap_err2string(int err);

/*
 *  Note that the use of the following routines is deprecated.
 *
 *  ICLLDAPAPI int LDAPAPI
 *  ldap_result2error(LDAP        *ld,
 *                    LDAPMessage *res,
 *                    int          freeit);
 *
 *
 *  ICLLDAPAPI void LDAPAPI
 *  ldap_perror(LDAP *ld,
 *              char *msg);
 */

/* 
 *  Stepping Through a List of Results.  
 */

/* 
 *  The ldap_first_message() and ldap_next_message() routines are used to 
 *  step through the list of messages in a result chain returned by 
 *  ldap_result().  For search operations, the result chain may actually 
 *  include referral messages, entry messages, and result messages.  
 *  ldap_count_messages() is used to count the number of messages returned.  
 *  The ldap_msgtype() function, described above, can be used to distinguish 
 *  between the different message types.  
 *
 *  ldap_first_message() and ldap_next_message() will return NULL when no 
 *  more messages exist in the result set to be returned.  NULL is also 
 *  returned if an error occurs while stepping through the entries, in which 
 *  case the error parameters in the session handle ld will be set to 
 *  indicate the error.  
 *
 *  ldap_count_messages() returns the number of messages contained in a 
 *  chain of results.  It can also be used to count the number of messages 
 *  that remain in a chain if called with a message, entry, or reference 
 *  returned by ldap_first_message(), ldap_next_message(), 
 *  ldap_first_entry(), ldap_next_entry(), ldap_first_reference(), 
 *  ldap_next_reference().  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  res: The result chain, as obtained by a call to one of the synchronous 
 *  search routines or ldap_result().  
 *
 *  msg: The message returned by a previous call to ldap_first_message() or 
 *  ldap_next_message().  
 */
ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_first_message(LDAP        *ld,
                   LDAPMessage *res);

ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_next_message(LDAP        *ld,
                  LDAPMessage *msg);

ICLLDAPAPI int LDAPAPI
ldap_count_messages(LDAP        *ld,
                    LDAPMessage *res);

/*
 *  Parsing Search Results.
 */

/* 
 *  The following calls are used to parse the entries and references 
 *  returned by ldap_search() and friends.  These results are returned in an 
 *  opaque structure that should only be accessed by calling the routines 
 *  described below.  Routines are provided to step through the entries and 
 *  references returned, step through the attributes of an entry, retrieve 
 *  the name of an entry, and retrieve the values associated with a given 
 *  attribute in an entry.  
 */

/*
 *  Stepping Through a List of Entries.
 */

/* 
 *  The ldap_first_entry() and ldap_next_entry() routines are used to step 
 *  through and retrieve the list of entries from a search result chain.  
 *  The ldap_first_reference() and ldap_next_reference() routines are used 
 *  to step through and retrieve the list of continuation references from a 
 *  search result chain.  ldap_count_entries() is used to count the number 
 *  of entries returned.  ldap_count_references() is used to count the 
 *  number of references returned.  
 *
 *  [CHANGE: Definition stated below has changed.  The previous definition 
 *  stated "ldap_first_entry() and ldap_next_entry() will return NULL when 
 *  no more entries or references exist in the result set to be returned." 
 *  This is changed to "no more entries exist" and an extra paragraph 
 *  detailing the definition of ldap_first_reference() and 
 *  ldap_next_reference().] 
 *
 *  ldap_first_entry() and ldap_next_entry() will return NULL when no more 
 *  entries exist in the result set to be returned.  NULL is also returned 
 *  if an error occurs while stepping through the entries, in which case the 
 *  error parameters in the session handle ld will be set to indicate the 
 *  error.  
 *
 *  ldap_first_reference() and ldap_next_reference() will return NULL when 
 *  no more references exist in the result set to be returned.  NULL is also 
 *  returned if an error occurs while stepping through the entries, in which 
 *  case the error parameters in the session handle ld will be set to 
 *  indicate the error.  
 *
 *  ldap_count_entries() returns the number of entries contained in a chain 
 *  of entries.  It can also be used to count the number of entries that 
 *  remain in a chain if called with a message, entry or reference returned 
 *  by ldap_first_message(), ldap_next_message(), ldap_first_entry(), 
 *  ldap_next_entry(), ldap_first_reference(), ldap_next_reference().  
 *
 *  ldap_count_references() returns the number of references contained in a 
 *  chain of search results.  It can also be used to count the number of 
 *  references that remain in a chain.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  res: The search result, as obtained by a call to one of the synchronous 
 *  search routines or ldap_result().  
 *
 *  entry: The entry returned by a previous call to ldap_first_entry() or 
 *  ldap_next_entry().  
 */
ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_first_entry(LDAP        *ld,
                 LDAPMessage *res);

ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_next_entry(LDAP        *ld,
                LDAPMessage *entry);

ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_first_reference(LDAP        *ld,
                     LDAPMessage *res);

ICLLDAPAPI LDAPMessage* LDAPAPI
ldap_next_reference(LDAP        *ld,
                    LDAPMessage *ref);

ICLLDAPAPI int LDAPAPI
ldap_count_entries(LDAP        *ld,
                   LDAPMessage *res);

ICLLDAPAPI int LDAPAPI
ldap_count_references(LDAP        *ld,
                      LDAPMessage *res);

/*
 *  Stepping Through the Attributes of an Entry.
 */
 
/* 
 *  The BerElement structure contains not only a copy of the encoded value, 
 *  but also state information used in encoding or decoding.  Applications 
 *  cannot allocate their own BerElement structures.  The internal state is 
 *  neither thread-specific nor locked, so two threads should not manipulate 
 *  the same BerElement value simultaneously.  
 *
 *  A single BerElement value cannot be used for both encoding and decoding.  
 */
#ifndef _DLLEXPORT_
typedef struct berelement BerElement;
#endif /* _DLLEXPORT_ */

/* 
 *  The ldap_first_attribute() and ldap_next_attribute() calls are used to 
 *  step through the list of attribute types returned with an entry.  
 *
 *  ldap_first_attribute() and ldap_next_attribute() will return NULL when 
 *  the end of the attributes is reached, or if there is an error, in which 
 *  case the error parameters in the session handle ld will be set to 
 *  indicate the error.  
 *
 *  Both routines return a pointer to an allocated buffer containing the 
 *  current attribute name.  This should be freed when no longer in use by 
 *  calling ldap_memfree().  
 *
 *  ldap_first_attribute() will allocate and return in ptr a pointer to a 
 *  BerElement used to keep track of the current position.  This pointer 
 *  should be passed in subsequent calls to ldap_next_attribute() to step 
 *  through the entry's attributes.  After a set of calls to 
 *  ldap_first_attribute() and ldap_next_attribute(), if ptr is non-NULL, it 
 *  should be freed by calling ldap_ber_free( ptr, 0 ).  Note that it is 
 *  very important to pass the second parameter as 0 (zero) in this call, 
 *  since the buffer associated with the BerElement does not point to 
 *  separately allocated memory.  
 *
 *  The attribute type names returned are suitable for passing in a call to 
 *  ldap_get_values() and friends to retrieve the associated values.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  entry: The entry whose attributes are to be stepped through, as returned 
 *  by ldap_first_entry() or ldap_next_entry().  
 *
 *  ptr: In ldap_first_attribute(), the address of a pointer used internally 
 *  to keep track of the current position in the entry.  In 
 *  ldap_next_attribute(), the pointer returned by a previous call to 
 *  ldap_first_attribute().  
 *
 *  mem: A pointer to memory allocated by the LDAP library, such as the 
 *  attribute type names returned by ldap_first_attribute() and 
 *  ldap_next_attribute, or the DN returned by ldap_get_dn().  
 */
ICLLDAPAPI char* LDAPAPI
ldap_first_attribute(LDAP         *ld,
                     LDAPMessage  *entry,
                     BerElement  **ptr);

ICLLDAPAPI char* LDAPAPI
ldap_next_attribute(LDAP        *ld,
                    LDAPMessage *entry,
                    BerElement  *ptr);

ICLLDAPAPI void LDAPAPI
ldap_ber_free(BerElement *ber,
              int         freebuf);

ICLLDAPAPI void LDAPAPI
ldap_memfree(char *mem);

/*
 *  Retrieving the Values of an Attribute.
 */

/* 
 *  ldap_get_values() and ldap_get_values_len() are used to retrieve the 
 *  values of a given attribute from an entry.  ldap_count_values() and 
 *  ldap_count_values_len() are used to count the returned values.  
 *  
 *  ldap_value_free() and ldap_value_free_len() are used to free the values.  
 *
 *  Two forms of the various calls are provided.  The first form is only 
 *  suitable for use with non-binary character string data.  The second _len 
 *  form is used with any kind of data.  
 *
 *  ldap_get_values() and ldap_get_values_len() return NULL if no values are 
 *  found for attr or if an error occurs.  
 *
 *  ldap_count_values() and ldap_count_values_len() return -1 if an error 
 *  occurs such as the vals parameter being invalid.  
 *
 *  Note that the values returned are dynamically allocated and should be 
 *  freed by calling either ldap_value_free() or ldap_value_free_len() when 
 *  no longer in use.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  entry: The entry from which to retrieve values, as returned by 
 *  ldap_first_entry() or ldap_next_entry().  
 *
 *  attr: The attribute whose values are to be retrieved, as returned by 
 *  ldap_first_attribute() or ldap_next_attribute(), or a caller-supplied 
 *  string (e.g., "mail").  
 *
 *  vals: The values returned by a previous call to ldap_get_values() or 
 *  ldap_get_values_len().  
 */
ICLLDAPAPI char** LDAPAPI
ldap_get_values(LDAP         *ld,
                LDAPMessage  *entry,
                char         *attr);

ICLLDAPAPI struct berval** LDAPAPI
ldap_get_values_len(LDAP           *ld,
                    LDAPMessage    *entry,
                    char           *attr);

ICLLDAPAPI int LDAPAPI
ldap_count_values(char **vals);

ICLLDAPAPI int LDAPAPI
ldap_count_values_len(struct berval **vals);

ICLLDAPAPI void LDAPAPI
ldap_value_free(char **vals);

ICLLDAPAPI void LDAPAPI
ldap_value_free_len(struct berval **vals);

/*
 *  Retrieving the name of an entry.
 */
 
/* 
 *  ldap_get_dn() is used to retrieve the name of an entry.  
 *  ldap_explode_dn() and ldap_explode_rdn() are used to break up a name 
 *  into its component parts.  ldap_dn2ufn() is used to convert the name 
 *  into a more "user friendly" format.  
 *
 *  ldap_get_dn() will return NULL if there is some error parsing the dn, 
 *  setting error parameters in the session handle ld to indicate the error.  
 *  It returns a pointer to newly allocated space that the caller should 
 *  free by calling ldap_memfree() when it is no longer in use.  Note the 
 *  format of the DNs returned is given by [4].  
 *
 *  ldap_explode_dn() returns a NULL-terminated char * array containing the 
 *  RDN components of the DN supplied, with or without types as indicated by 
 *  the notypes parameter.  The components are returned in the order they 
 *  appear in the dn.  The array returned should be freed when it is no 
 *  longer in use by calling ldap_value_free().  
 *
 *  ldap_explode_rdn() returns a NULL-terminated char * array containing the 
 *  components of the RDN supplied, with or without types as indicated by 
 *  the notypes parameter.  The components are returned in the order they 
 *  appear in the rdn.  The array returned should be freed when it is no 
 *  longer in use by calling ldap_value_free().  
 *
 *  ldap_dn2ufn() converts the DN into the user friendly format described in 
 *  [5].  The UFN returned is newly allocated space that should be freed by 
 *  a call to ldap_memfree() when no longer in use.  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  entry: The entry whose name is to be retrieved, as returned by 
 *  ldap_first_entry() or ldap_next_entry().  
 *
 *  dn: The dn to explode, such as returned by ldap_get_dn().  
 *
 *  rdn: The rdn to explode, such as returned in the components of the array 
 *  returned by ldap_explode_dn().  
 *
 *  notypes: A boolean parameter, if non-zero indicating that the dn or rdn 
 *  components should have their type information stripped off (i.e., 
 *  "cn=Babs" would become "Babs").  
 */
ICLLDAPAPI char* LDAPAPI
ldap_get_dn(LDAP        *ld,
            LDAPMessage *entry);

ICLLDAPAPI char** LDAPAPI
ldap_explode_dn(char  *dn,
                int    notypes);

ICLLDAPAPI char** LDAPAPI
ldap_explode_rdn(char  *rdn,
                 int    notypes);

ICLLDAPAPI char* LDAPAPI
ldap_dn2ufn(char *dn);

/*
 *  Retrieving controls from an entry.
 */

/* 
 *  ldap_get_entry_controls() is used to extract LDAP controls from an 
 *  entry.  
 *
 *  ldap_get_entry_controls() returns an LDAP error code that indicates 
 *  whether the reference could be successfully parsed (LDAP_SUCCESS if all 
 *  goes well).  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  entry: The entry to extract controls from, as returned by 
 *  ldap_first_entry() or ldap_next_entry().  
 *
 *  serverctrlsp: This result parameter will be filled in with an allocated 
 *  array of controls copied out of entry.  The control array should be 
 *  freed by calling ldap_controls_free().  If serverctrlsp is NULL, no 
 *  controls are returned.  
 *
 */
ICLLDAPAPI int LDAPAPI
ldap_get_entry_controls(LDAP          *ld,
                        LDAPMessage   *entry,
                        LDAPControl ***serverctrlsp);

/*
 *  Parsing References.
 */

/* 
 *  ldap_parse_reference() is used to extract referrals and controls from a 
 *  SearchResultReference message.  
 *
 *  ldap_parse_reference() returns an LDAP error code that indicates whether 
 *  the reference could be successfully parsed (LDAP_SUCCESS if all goes 
 *  well).  
 *
 *  Parameters are: 
 *
 *  ld: The session handle.  
 *
 *  ref: The reference to parse, as returned by ldap_result(), 
 *  ldap_first_reference(), or ldap_next_reference().  
 *
 *  [CHANGE: referralsp was of type char**, to be able to implement the 
 *  definition it is required to be of type char***.]
 *  
 *  referralsp: This result parameter will be filled in with an allocated 
 *  array of character strings.  The elements of the array are the referrals 
 *  (typically LDAP URLs) contained in ref.  The array should be freed when 
 *  no longer in used by calling ldap_value_free().  If referralsp is NULL, 
 *  the referral URLs are not returned.  
 *
 *  serverctrlsp: This result parameter will be filled in with an allocated 
 *  array of controls copied out of ref.  The control array should be freed 
 *  by calling ldap_controls_free().  If serverctrlsp is NULL, no controls 
 *  are returned.  
 *
 *  freeit: A boolean that determines whether the ref parameter is disposed 
 *  of or not.  Pass any non-zero value to have these routines free res 
 *  after extracting the requested information.  This is provided as a 
 *  convenience; you can also use ldap_msgfree() to free the result later.  
 */
ICLLDAPAPI int LDAPAPI
ldap_parse_reference(LDAP          *ld,
                     LDAPMessage   *ref,
                     char        ***referralsp,
                     LDAPControl ***serverctrlsp,
                     int            freeit);

/*
 *  Encoded ASN.1 Value Manipulation.
 */
 
/* 
 *  This section describes routines which may be used to encode and decode 
 *  BER-encoded ASN.1 values, which are often used inside of control and 
 *  extension values.  
 *
 *  [CHANGE: ber_init in the API does not match that in umich ber_init;
 *  agreed to go to ldap_api_ber_init for the API function to avoid name
 *  clashes.]
 *  
 *  With the exceptions of two new functions ber_flatten() and  
 *  ldap_api_ber_init() [CHANGE:], these functions are compatible with the  
 *  University of Michigan LDAP 3.3 implementation of BER. 
 */

/*
 *  General.
 *  
 *  [berval was also redefined here zzz]
 */


/* 
 *  ber_bvfree() frees a berval returned from this API.  Both the bv->bv_val 
 *  string and the berval itself are freed.  Applications should not use 
 *  ber_bvfree() with bervals which the application has allocated.  
 */
ICLLDAPAPI void LDAPAPI
ber_bvfree(struct berval *bv);

/* 
 *  ber_bvecfree() frees an array of bervals returned from this API.  Each 
 *  of the bervals in the array are freed using ber_bvfree(), then the array 
 *  itself is freed.  
 */
ICLLDAPAPI void LDAPAPI
ber_bvecfree(struct berval **bv);

/* 
 *  ber_bvdup() returns a copy of a berval.  The bv_val field in the 
 *  returned berval points to a different area of memory as the bv_val field 
 *  in the argument berval.  The null pointer is returned on error (e.g.  
 *  out of memory).  
 */
ICLLDAPAPI struct berval* LDAPAPI
ber_bvdup(struct berval *bv);

/* 
 *  ber_free() frees a BerElement which is returned from the API calls 
 *  ber_alloc_t() or ldap_api_ber_init() [CHANGE:].  Each BerElement must 
 *  be freed by the caller.  The second argument fbuf should always be set to 
 *  1 to ensure that the internal buffer used by the BER functions is freed 
 *  as well as the BerElement container itself.  
 */
ICLLDAPAPI void LDAPAPI
ber_free(BerElement *ber,
         int         fbuf);

/*
 *  Encoding.
 */

/* 
 *  ber_alloc_t() constructs and returns BerElement.  The null pointer is 
 *  returned on error.  The options field contains a bitwise-or of options 
 *  which are to be used when generating the encoding of this BerElement.  
 *  One option is defined and must always be supplied: 
 *
 *  LBER_USE_DER (0x01)
 *
 *  When this option is present, lengths will always be encoded in the 
 *  minimum number of octets.  Note that this option does not cause values 
 *  of sets and sequences to be rearranged in tag and byte order, so these 
 *  functions are not suitable for generating DER output as defined in X.509 
 *  and X.680.  
 *
 *  Unrecognized option bits are ignored.  
 *
 *  The BerElement returned by ber_alloc_t() is initially empty.  Calls to 
 *  ber_printf() will append bytes to the end of the ber_alloc_t().  
 */
ICLLDAPAPI BerElement* LDAPAPI
ber_alloc_t(int options);

#define LBER_USE_DER 0x01

/* 
 *  The ber_printf() routine is used to encode a BER element in much the 
 *  same way that sprintf() works.  One important difference, though, is 
 *  that state information is kept in the ber argument so that multiple 
 *  calls can be made to ber_printf() to append to the end of the BER 
 *  element.  ber must be a pointer to a BerElement returned by 
 *  ber_alloc_t().  ber_printf() interprets and formats its arguments 
 *  according to the format string fmt.  ber_printf() returns -1 if there is 
 *  an error during encoding and a positive number if successful.  As with 
 *  sprintf(), each character in fmt refers to an argument to ber_printf().  
 *
 *  The format string can contain the following format characters: 
 *
 *  't' - Tag: 
 *
 *  The next argument is an int specifying the tag to override the next 
 *  element to be written to the ber.  This works across calls.  The int 
 *  value must contain the tag class, constructed bit, and tag value.  The 
 *  tag value must fit in a single octet (tag value is less than 32).  For 
 *  example, a tag of "[3]" for a constructed type is 0xA3.  
 *
 *  'b' - Boolean: 
 *
 *  The next argument is an int, containing either 0 for FALSE or 0xff for 
 *  TRUE.  A boolean element is output.  If this format character is not 
 *  preceded by the 't' format modifier, the tag 0x01 is used for the 
 *  element.  
 *
 *  'i' - Integer: 
 *
 *  The next argument is an int, containing the integer in the host's byte 
 *  order.  An integer element is output.  If this format character is not 
 *  preceded by the 't' format modifier, the tag 0x02 is used for the 
 *  element.  
 *
 *  'X' - Bitstring: 
 *
 *  The next two arguments are a char * pointer to the start of the 
 *  bitstring, followed by an int containing the number of bits in the 
 *  bitstring.  A bitstring element is output, in primitive form.  If this 
 *  format character is not preceded by the 't' format modifier, the tag 
 *  0x03 is used for the element.  
 *
 *  'n' - Null: 
 *
 *  No argument is required.  An ASN.1 NULL element is output.  If this 
 *  format character is not preceded by the 't' format modifier, the tag 
 *  0x05 is used for the element.  
 *
 *  'o' - Octet string: 
 *
 *  The next two arguments are a char *, followed by an int with the length 
 *  of the string.  The string may contain null bytes and need not by 
 *  zero-terminated.  An octet string element is output, in primitive form.  
 *  If this format character is not preceded by the 't' format modifier, the 
 *  tag 0x04 is used for the element.  
 *
 *  's' - Octet string: 
 *
 *  The next argument is a char * pointing to a zero-terminated string.  An 
 *  octet string element in primitive form is output, which does not include 
 *  the trailing ' ' byte.  If this format character is not preceded by the 
 *  't' format modifier, the tag 0x04 is used for the element.  
 *
 *  'v' - Several octet strings: 
 *
 *  The next argument is a char **, an array of char * pointers to 
 *  zero-terminated strings.  The last element in the array must be a null 
 *  pointer.  The octet strings do not include the trailing SEQUENCE OF 
 *  octet strings.  The 't' format modifier cannot be used with this format 
 *  character.  
 *
 *  'V' - Several octet strings: 
 *
 *  A NULL-terminated array of berval *'s is supplied.  Note that a 
 *  construct like '{V}' is required to get an actual SEQUENCE OF octet 
 *  strings.  The 't' format modifier cannot be used with this format 
 *  character.  
 *
 *  '{' - Begin sequence: 
 *
 *  No argument is required.  If this format character is not preceded by 
 *  the 't' format modifier, the tag 0x30 is used.  
 *
 *  '}' - End sequence: 
 *
 *  No argument is required.  The 't' format modifier cannot be used with 
 *  this format character.  
 *
 *  '[' - Begin set: 
 *
 *  No argument is required.  If this format character is not preceded by 
 *  the 't' format modifier, the tag 0x31 is used.  
 *
 *  ']' - End set.  
 *
 *  No argument is required.  The 't' format modifier cannot be used with 
 *  this format character.  
 *
 *  Each use of a '{' format character must be matched by a '}' character, 
 *  either later in the format string, or in the format string of a 
 *  subsequent call to ber_printf() for that BerElement.  The same applies 
 *  to the '[' and 
 *
 *  Sequences and sets nest, and implementations of this API must maintain 
 *  internal state to be able to properly calculate the lengths.  
 */
ICLLDAPAPI int LDAPAPI
ber_printf(BerElement *ber,
           char *fmt,
           ...);

/* 
 *  The ber_flatten routine allocates a struct berval whose contents are a 
 *  BER encoding taken from the ber argument.  The bvPtr pointer points to 
 *  the returned berval, which must be freed using ber_bvfree().  This 
 *  routine returns 0 on success and -1 on error.  
 *
 *  The ber_flatten API call is not present in U-M LDAP 3.3.  
 *
 *  The use of ber_flatten on a BerElement in which all '{' and '}' format 
 *  modifiers have not been properly matched can result in a berval whose 
 *  contents are not a valid BER encoding.  
 */
ICLLDAPAPI int LDAPAPI
ber_flatten(BerElement     *ber,
            struct berval **bvPtr);

/*
 *  Encoding Example.
 */
 
/*
 *  The following is an example of encoding the following ASN.1 data type:
 *
 *        Example1Request ::= SEQUENCE {
 *             s     OCTET STRING, -- must be printable
 *             val1  INTEGER,
 *             val2  [0] INTEGER DEFAULT 0
 *        }
 *
 *
 *        int encode_example1(char *s,int val1,int val2,struct berval **bvPtr)
 *        {
 *             BerElement *ber;
 *             int rc;
 *
 *             ber = ber_alloc_t(LBER_USE_DER);
 *
 *
 *             if (ber == NULL) return -1;
 *
 *             if (ber_printf(ber,"{si",s,val1) == -1) {
 *                     ber_free(ber,1);
 *                     return -1;
 *             }
 *
 *             if (val2 != 0) {
 *                     if (ber_printf(ber,"ti",0x80,val2) == -1) {
 *                             ber_free(ber,1);
 *                             return -1;
 *                     }
 *             }
 *
 *             if (ber_printf(ber,"}") == -1) {
 *                     ber_free(ber,1);
 *                     return -1;
 *             }
 *
 *             rc = ber_flatten(ber,bvPtr);
 *             ber_free(ber,1);
 *             return -1;
 *        }
 */

/*
 *  Decoding.
 */

/* 
 *  The following two symbols are available to applications.  
 *
 *  #define LBER_ERROR 0xffffffffL 
 *
 *  #define LBER_DEFAULT 0xffffffffL 
 *
 *  The ldap_api_ber_init [CHANGE:] function constructs a BerElement and  
 *  returns a new BerElement containing a copy of the data in the bv argument.  
 *  ldap_api_ber_init [CHANGE:] returns the null pointer on error.  
 *
 */
ICLLDAPAPI BerElement* LDAPAPI
ldap_api_ber_init(struct berval *bv);

#define LBER_ERROR     0xffffffffL 
#define LBER_DEFAULT   0xffffffffL 

/* 
 *  The ber_scanf() routine is used to decode a BER element in much the same 
 *  way that sscanf() works.  One important difference, though, is that some 
 *  state information is kept with the ber argument so that multiple calls 
 *  can be made to ber_scanf() to sequentially read from the BER element.  
 *  The ber argument must be a pointer to a BerElement returned by 
 *  ldap_api_ber_init() [CHANGE:].  ber_scanf interprets the bytes according 
 *  to the format string fmt, and stores the results in its additional   
 *  arguments.  ber_scanf() returns LBER_ERROR on error, and a different value  
 *  on success.  
 *
 *  The format string contains conversion specifications which are used to 
 *  direct the interpretation of the BER element.  The format string can 
 *  contain the following characters: 
 *
 *  'a' - Octet string: 
 *
 *  A char ** argument should be supplied.  Memory is allocated, filled with 
 *  the contents of the octet string, null-terminated, and the pointer to 
 *  the string is stored in the argument.  The returned value must be 
 *  freed using ldap_memfree.  The tag of the element must indicate the 
 *  primitive form (constructed strings are not supported) but is otherwise 
 *  ignored and discarded during the decoding.  This format cannot be used 
 *  with octet strings which could contain null bytes.  
 *
 *  'O' - Octet string: 
 *
 *  A struct berval ** argument should be supplied, which upon return points 
 *  to a allocated struct berval containing the octet string and its length.  
 *  ber_bvfree() must be called to free the allocated memory.  The tag of 
 *  the element must indicate the primitive form (constructed strings are 
 *  not supported) but is otherwise ignored during the decoding.  
 *
 *  'b' - Boolean: 
 *
 *  A pointer to an int should be supplied.  The int value stored will be 0 
 *  for FALSE or nonzero for TRUE.  The tag of the element must indicate the 
 *  primitive form but is otherwise ignored during the decoding.  
 *
 *  'i' - Integer: 
 *
 *  A pointer to an int should be supplied.  The int value stored will be in 
 *  host byte order.  The tag of the element must indicate the primitive 
 *  form but is otherwise ignored during the decoding.  ber_scanf() will 
 *  return an error if the integer cannot be stored in an int.  
 *
 *  'B' - Bitstring: 
 *
 *  A char ** argument should be supplied which will point to the allocated 
 *  bits, followed by an unsigned long * argument, which will point to the 
 *  length (in bits) of the bitstring returned.  ldap_memfree must be 
 *  called to free the bitstring.  The tag of the element must indicate 
 *  the primitive form (constructed bitstrings are not supported) but is 
 *  otherwise ignored during the decoding.  
 *
 *  'n' - Null: 
 *
 *  No argument is required.  The element is simply skipped if it is 
 *  recognized as a zero-length element.  The tag is ignored.  
 *
 *  'v' - Several octet strings: 
 *
 *  A char *** argument should be supplied, which upon return points to a 
 *  allocated null-terminated array of char *'s containing the octet 
 *  strings.  NULL is stored if the sequence is empty.  ldap_memfree must be 
 *  called to free each element of the array and the array itself.  The tag 
 *  of the sequence and of the octet strings are ignored.  
 *
 *  'V' - Several octet strings (which could contain null bytes): 
 *
 *  A struct berval *** should be supplied, which upon return points to a 
 *  allocated null-terminated array of struct berval *'s containing the 
 *  octet strings and their lengths.  NULL is stored if the sequence is 
 *  empty.  ber_bvecfree() can be called to free the allocated memory.  The 
 *  tag of the sequence and of the octet strings are ignored.  
 *
 *  'x' - Skip element: 
 *
 *  The next element is skipped.  No argument is required.  
 *
 *  '{' - Begin sequence: 
 *
 *  No argument is required.  The initial sequence tag and length are 
 *  skipped.  
 *
 *  '}' - End sequence: 
 *
 *  No argument is required.  
 *
 *  '[' - Begin set: 
 *
 *  No argument is required.  The initial set tag and length are skipped.  
 *
 *  ']'- End set: 
 *
 *  No argument is required.  
 */
ICLLDAPAPI unsigned long LDAPAPI
ber_scanf(BerElement *ber,
          char       *fmt,
          ...);

/* 
 *  ber_peek_tag() returns the tag of the next element to be parsed in the 
 *  BerElement argument.  The length of this element is stored in the lenPtr 
 *  argument.  LBER_DEFAULT is returned if there is no further data to be 
 *  read.  The ber argument is not modified.  
 */
ICLLDAPAPI unsigned long LDAPAPI
ber_peek_tag(BerElement    *ber,
             unsigned long *lenPtr);

/* 
 *  ber_skip_tag() is similar to ber_peek_tag(), except that the state 
 *  pointer in the BerElement argument is advanced past the first tag and 
 *  length, and is pointed to the value part of the next element.  This 
 *  routine should only be used with constructed types and situations when a 
 *  BER encoding is used as the value of an OCTET STRING.  The length of the 
 *  value is stored in *lenPtr.  
 */
ICLLDAPAPI unsigned long LDAPAPI
ber_skip_tag(BerElement *ber, unsigned long *lenPtr);

/* 
 *  ber_first_element() and ber_next_element() are used to traverse a SET, 
 *  SET OF, SEQUENCE or SEQUENCE OF data value.  ber_first_element() calls 
 *  ber_skip_tag(), stores internal information in *lenPtr and *opaquePtr, 
 *  and calls ber_peek_tag() for the first element inside the constructed 
 *  value.  LBER_DEFAULT is returned if the constructed value is empty.  
 *  ber_next_element() positions the state at the start of the next element 
 *  in the constructed type.  LBER_DEFAULT is returned if there are no 
 *  further values.  
 *
 *  The len and opaque values should not be used by applications other than 
 *  as arguments to ber_next_element(), as shown in the example below.  
 */
ICLLDAPAPI unsigned long LDAPAPI
ber_first_element(BerElement     *ber,
                  unsigned long  *lenPtr,
                  char          **opaquePtr);

ICLLDAPAPI unsigned long LDAPAPI
ber_next_element(BerElement    *ber,
                 unsigned long *lenPtr,
                 char          *opaque);

/*
 *  Decoding Example.
 */

/*
 *  The following is an example of decoding an ASN.1 data type:
 *
 *       Example2Request ::= SEQUENCE {
 *            dn    OCTET STRING, -- must be printable
 *            scope ENUMERATED { b (0), s (1), w (2) },
 *            ali   ENUMERATED { n (0), s (1), f (2), a (3) },
 *            size  INTEGER,
 *            time  INTEGER,
 *            tonly BOOLEAN,
 *            attrs SEQUENCE OF OCTET STRING, -- must be printable
 *            [0] SEQUENCE OF SEQUENCE {
 *               type  OCTET STRING -- must be printable,
 *               crit  BOOLEAN DEFAULT FALSE,
 *               value OCTET STRING
 *            } OPTIONAL }
 *
 *       #define LDAP_TAG_CONTROL_LIST 0xA0L // context specific cons 0
 *
 *       int decode_example2(struct berval *bv)
 *       {
 *            BerElement *ber;
 *            unsigned long len;
 *            int scope, ali, size, time, tonly;
 *            char *dn = NULL, **attrs = NULL;
 *            int res,i,rc = 0;
 *
 *            ber = ldap_api_ber_init(bv);   // [CHANGE:] 
 *            if (ber == NULL) {
 *                    printf("ERROR ldap_api_ber_init failed0); // [CHANGE:]
 *                    return -1;
 *            }
 *
 *            res = ber_scanf(ber,"{aiiiiib{v}",&dn,&scope,&ali,
 *                            &size,&time,&tonly,&attrs);
 *
 *            if (res == -1) {
 *                    printf("ERROR ber_scanf failed0);
 *                    ber_free(ber,1);
 *                    return -1;
 *            }
 *
 *            // *** use dn 
 *            ldap_memfree(dn);
 *
 *            for (i = 0; attrs != NULL && attrs[i] != NULL; i++) {
 *                    // *** use attrs[i]
 *                    ldap_memfree(attrs[i]);
 *            }
 *            ldap_memfree(attrs);
 *
 *            if (ber_peek_tag(ber,&len) == LDAP_TAG_CONTROL_LIST) {
 *                    char *opaque;
 *                    unsigned long tag;
 *
 *                    for (tag = ber_first_element(ber,&len,&opaque);
 *                         tag != LBER_DEFAULT;
 *                         tag = ber_next_element (ber,&len,opaque)) {
 *
 *                            unsigned long ttag, tlen;
 *                            char *type;
 *                            int crit;
 *                            struct berval *value;
 *
 *                            if (ber_scanf(ber,"{a",&type) == LBER_ERROR) {
 *                                    printf("ERROR cannot parse type0);
 *                                    break;
 *                            }
 *                            /// *** use type
 *                            ldap_memfree(type);
 *
 *                            ttag = ber_peek_tag(ber,&tlen);
 *                            if (ttag == 0x01) {  // boolean
 *                                    if (ber_scanf(ber,"b",
 *                                                  &crit) == LBER_ERROR) {
 *                                            printf("ERROR cannot parse crit0);
 *                                            rc = -1;
 *                                            break;
 *                                    }
 *                            } else if (ttag == 0x04) { // octet string
 *                                    crit = 0;
 *                            } else {
 *                                    printf("ERROR extra field in controls0);
 *                                    break;
 *                            }
 *
 *                            if (ber_scanf(ber,"O}",&value) == LBER_ERROR) {
 *                                    printf("ERROR cannot parse value0);
 *                                    rc = -1;
 *                                    break;
 *                            }
 *                            // *** use value
 *                            ber_bvfree(value);
 *                    }
 *            }
 *
 *            ber_scanf(ber,"}");
 *
 *            ber_free(ber,1);
 *
 *            return rc;
 *        }
 */

/* 
 *  Bibliography 
 */

/* 
 *  References used in this header file 
 *
 *  [1] The Directory: Selected Attribute Syntaxes.  CCITT, Recommendation 
 *  X.520.  
 *
 *  [2] M.  Wahl, A.  Coulbeck, T.  Howes, S.  Kille, W.  Yeong, C.  
 *  Robbins, "Lightweight Directory Access Protocol (v3): Attribute Syntax 
 *  Definitions", RFC 2252, December 1997.  
 *
 *  [3] T.  Howes, "The String Representation of LDAP Search Filters," RFC 
 *  2254, December 1997.  
 *
 *  [4] M.  Wahl, S.  Kille, T.  Howes, "Lightweight Directory Access 
 *  Protocol (v3): A UTF-8 String Representation of Distinguished Names", 
 *  RFC 2253, December 1997.  
 *
 *  [5] S.  Kille, "Using the OSI Directory to Achieve User Friendly Nam- 
 *  ing," RFC 1781, March 1995.  
 *
 *  [6] M.  Wahl, T.  Howes, S.  Kille, "Lightweight Directory Access 
 *  Protocol (v3)", RFC 2251, December 1997.  
 *
 *  [7] A.  Herron, T.  Howes, M.  Wahl, C.  Weider, A.  Anantha, "LDAP 
 *  Control Extension for Server Side Sorting of Search Results", INTERNET- 
 *  DRAFT <draft-ietf-ldapext-sorting-01.txt>, 10 March 1998.  
 *
 *  [8] J.  Meyers, "Simple Authentication and Security Layer (SASL)", RFC 
 *  2222, October 1997.  
 *
 *  [9] "Lightweight Directory Access Protocol (v3) Extension for Transport 
 *  Layer Security", INTERNET-DRAFT <draft-ietf-asid-ldapv3-tls- 01.txt>, 
 *  June 1997.  
 *
 *  [10] "UTF-8, a transformation format of Unicode and ISO 10646", RFC 
 *  2044, October 1996.  
 *
 *  [11] "IP Version 6 Addressing Architecture,", RFC 1884, December 1995.  
 */
 
#ifdef __cplusplus
}
#endif

#endif /* _LDAPV3_H */
