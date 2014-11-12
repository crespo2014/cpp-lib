/********************************************************************** 
* 
* H Source: platform.h 
* Description: Platform Definitions
* %created_by: leonid_s % 
* %date_created: Tue Jan 13 10:42:38 2004 % 
* %full_filespec: platform.h#2:incl:2 % 
* 
**********************************************************************/ 

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#ifndef   WNTNOINC
#define   WNTINC
#endif 

/*
#ifndef   UNICODE
#define   UNICODE
#endif // UNICODE
*/

#define   SCCSID(A)	   //For the sake of unix

#include  <windows.h>
#include  <lm.h>

/****************************************************
 *
 ****************************************************/

#ifdef  THIS_IS_MAIN
#define EXT
#else
#define EXT extern
#endif

#define WINNT          1
#ifdef THIS_IS_MAIN
  char   NATIVE_RSS [32] = "WinNT";
#else
  extern char NATIVE_RSS [32];
#endif /* THIS_IS_MAIN */

#define LOWBYTEFIRST   1
//#define HIGHBYTEFIRST 1
#define BLANK         ' '

#define CTSA_NAME      "SA-Agent"

#define WCHARSZ		   sizeof(WCHAR)

/****************************************************
 * Windows NT System Include Files
 ****************************************************/

#define   WINDOWS       <windows.h>

#define   CTYPE         <ctype.h>
#define   ERRNO         "errno.h"
#define   MALLOC        <malloc.h>
#define   MATH          <math.h>
#define   MEMORY        <memory.h>
#define   STDARG        <stdarg.h>
#define   STDIO         <stdio.h>
#define   CONIO         <conio.h>
#define   STDLIB        <stdlib.h>
#define   SYSLOG        <syslog.h>
#define   TIME_H        <time.h>
#define   SIGNAL        <signal.h>
#define   UNISTD        <unistd.h>
#define   VFORK         <vfork.h>
#define   FCNTL         <fcntl.h>
#define   IO            <io.h>
#define   DIRECT        <direct.h>

#define   TYPES     	<SYS\types.h>


/********************************************
 * ESAAPI stuff
 *******************************************/

/*All MAX_RSS_xxx have been moved to esaapi.h. You can define maximum lengths you need in rssdefs.h*/

#define DIAG_INFO_LEVEL        3
#define DIAG_PRINT_LEVEL       4

#define DOMAIN_NAME_LEN               256
#define HOST_NAME_LENGTH              LM20_UNCLEN 
#define PID_MAX_LEN                   50

#define ERR_MSG_TEXT_LEN    1024   /* length of text in ERR_STRUCT_rec_typ */
#define PROGRAM_NAME_LEN     255
#define OS_LOCK_INTERVAL       2   /* Time to wait between successive calls to lockf */
#define MAX_FILENAME_LEN      255
#define TTY_DEVICE           "TT:"
#define NULL_DEVICE          "NUL"

 /********************************************
 * CS stuff                                 *
 *******************************************/

/* Maximum values used to allocate memory */

#define MAX_GET               5   /* Aviw - 6/5/01 */

#define FILE_OPEN_FOR_UPDATE "r+"
#define FILE_OPEN_FOR_READ   "r"
#define FILE_CREAT           "w+"
#define FILE_APPEND          "a"

#define Q_PUT_INTERVAL        3000
#define Q_GET_INTERVAL        3000

#define IGNORE_NUMBER         -1
#define EMPTY_NUMBER          -2

/********************************************
 * CTSPARM file                             *
 ********************************************/

#define CTSROOT_ENV         "%CTSROOT%"
#define CTSROOT             "CTSROOT"
#define CTSRSSTYP           "CTSRSSTYP"
#define REG_ENV_PATH        "Software\\%s\\%s\\AgentParameters"
#define INIT_FILE_NAME      "%CTSROOT%\\DATA\\CTSPARM.PRM"

#define SA_HOSTNAME         "CmnHostName"


/********************************************
 * DLL file names                           *
 *******************************************/

#define   WNT_DLL_FILE        "%CTSROOT%\\EXE\\CTS_API_%s.DLL"
#define   EXE_DIR_NAME        "EXE"
#define   SA_AGENT_ID         "CTSA0_AGENTID"
#define   EXECUTABLE_DIR_PATH "EXECUTABLE_DIR_PATH"

/****************************************************
 * Process & Utilities exit statuses.
 ****************************************************/

#define PLAT_OK_STAT     0     /* Process terminated OK */
#define PLAT_FAIL_STAT   1     /* Process terminated due to error */

/****************************************************
 * CE stuff
 ****************************************************/

/* #define  COM_MAX_MSG_SZ        (2*10240) AVIW-19/11/00*/

#define  CO_ESA_MBX_RETRY_INT  (5*1000) 
#define  CO_LOOP_SLEEP_TIME    (5*1000)
#define  CO_SLEEP_TIME         (1*1000)

/****************************************************
 * General macros.
 ****************************************************/

#define is_null_dev(X) ((strcmp((X) , NULL_DEVICE) EQ 0) ? 1 : 0)
#define MAX(X,Y)   ((X)>(Y)?(X):(Y))
#define MIN(X,Y)   ((X)>(Y)?(Y):(X))

#define OPENER(X)  fopen((X),"a")

/********************************************
 * OS_MBX stuff                             *
********************************************/

#define  MBX_QUE_NAME_D_size     255

typedef void           *MBX_QUE_HDL_D_typ;
typedef char            MBX_QUE_NAME_D_typ [MBX_QUE_NAME_D_size +1];
typedef long unsigned   MBX_QUE_SIZE_D_typ;   
typedef int             MBX_QUE_CONF_D_typ;
typedef long            MBX_QUE_KEY_D_typ; 

/**********************
*   Miscellanouse 	  *
**********************/

#define   WNT_EVENT_DLL      "%CTSROOT%\\EXE\\CTSAEVNT.dll"

#define   WSIZE(X)           (sizeof((X)) / WCHARSZ)

#define   SYSTEM_USER        "SYSTEM"

/* AviW 15/11/99 */

#define  INTERCEPTOR_SRVC_NAME      "SA-Interceptor"

#define  STRLIST_ENTRY_SEPARATOR       ","
#define  STRLIST_SUBFIELD_SEPARATOR    ";"

/*******************************************
 * Offline Interceptor stuff
 *******************************************/

#define OFFLINE_EXE_NAME               "CTSOFLI.EXE"

#define OFFLINE_RSS_VERB_KWD           "OFLI_VERBOSE"
#define OFLI_WORK_PATH_PARAM           "RSS_WORK_DIR"
#define OFLI_CAREOE_FILE_NAME          "CAREOEF.IMG"

#define USER_INIT_FILE_NAME            "oflusr.img"
#define GROUP_INIT_FILE_NAME           "oflgrp.img"
#define CONNECTION_INIT_FILE_NAME      "oflcnn.img"
#define RSS_INIT_FILE_NAME             "oflrss.img"
#define OE_INIT_FILE_NAME              "ofloe.img"

#define USER_REGULAR_FILE_NAME         "oflusr.tmp"
#define GROUP_REGULAR_FILE_NAME        "oflgrp.tmp"
#define CONNECTION_REGULAR_FILE_NAME   "oflcnn.tmp"
#define RSS_REGULAR_FILE_NAME          "oflrss.tmp"
#define OE_REGULAR_FILE_NAME           "ofloe.tmp"

#define USER_COMPARE_FILE_NAME         "oflusr.cmp"
#define GROUP_COMPARE_FILE_NAME        "oflgrp.cmp"
#define CONNECTION_COMPARE_FILE_NAME   "oflcnn.cmp"
#define RSS_COMPARE_FILE_NAME          "oflrss.cmp"
#define OE_COMPARE_FILE_NAME           "ofloe.cmp"

#define OSOFLI_USER_FILE_NAME          "oflusr.osf"
#define OSOFLI_GROUP_FILE_NAME         "oflgrp.osf"
#define OSOFLI_CONNECTION_FILE_NAME    "oflcnn.osf"
#define OSOFLI_RSS_FILE_NAME           "oflrss.osf"
#define OSOFLI_OE_FILE_NAME            "ofloe.osf"

#define MAX_EXPECTED_FIELDS            100
#define MAX_EXPECTED_CNN_CHANGES       100
#define MAX_EXPECTED_RECORDS           500

#define DB_FIELDS_SEPARATOR_CHAR       '\x11'
#define DB_FIELDS_SEPARATOR_STR        "\x11"
#define DB_REMOVE_MASS_CHAR            '*'      /* '\x12' */
#define DB_REMOVE_MASS_STR             "*"      /* "\x12" */

#ifdef ESAINIT_C 
void DATA_COMP_PLATFORM__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_PLATFORM__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif /* PLATFORM_H_INCLUDED */
