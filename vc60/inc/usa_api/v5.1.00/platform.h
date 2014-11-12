/********************************************************************** 
* 
* H Source: platform.h 
* Description: Platform Definitions
* %created_by: leonid_s % 
* %date_created: Tue Mar 22 11:22:57 2005 % 
* %full_filespec: platform.h#24:incl:18 % 
* 
**********************************************************************/ 

#ifndef PLATFORM_H_INCLUDED
#define PLATFORM_H_INCLUDED

#ifndef   WNTNOINC
#define   WNTINC
#endif 

#ifndef   UNICODE
#define   UNICODE
#endif // UNICODE

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

#define AGENT_SUPPORTS_I18N
#define CTSA_NAME      "Services Manager"
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
/*#define   STRING        <string.h>*/
#define   SYSLOG1        <syslog.h>
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

#define DIAG_INFO_LEVEL        3              
#define DIAG_PRINT_LEVEL       4              

#define DOMAIN_NAME_LEN               256     
#define HOST_NAME_LENGTH              256 
#define PID_MAX_LEN                   50
/*
#define MAX_RSS_PASSWD_LEN            PWLEN 
#define MAX_RSS_RESTYPE_NAME_LEN      20
#define MAX_RSS_USER_NAME_LEN         UNLEN 
#define MAX_RSS_ACE_USER_NAME_LEN     MAX_RSS_USER_NAME_LEN + HOST_NAME_LENGTH + 3
#define MAX_RSS_OE_NAME_LEN           UNLEN
#define MAX_RSS_ACE_OE_NAME_LEN       MAX_RSS_OE_NAME_LEN + HOST_NAME_LENGTH + 3
#define MAX_RSS_UG_NAME_LEN           GNLEN
#define MAX_RSS_ACE_UG_NAME_LEN       MAX_RSS_UG_NAME_LEN + HOST_NAME_LENGTH + 3
#define MAX_RSS_RESOURCE_NAME_LEN     PATHLEN   
*/
#define MAX_RSS_ADDINFO_KWD_LEN       64     
#define MAX_RSS_ADDINFO_VAL_LEN       4096   

#define ERR_MSG_TEXT_LEN    2048   /* length of text in ERR_STRUCT_rec_typ */
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
#define FILE_OPEN_FOR_WRITE  "w"
#define FILE_CREAT           "w+"
#define FILE_APPEND          "a"

#define Q_PUT_INTERVAL        3000
#define Q_GET_INTERVAL        3000

#define IGNORE_NUMBER         -1
#define EMPTY_NUMBER          -2
#define DIR_SEP               '\\'

/********************************************
 * For initialize                           *
 ********************************************/

#define CTSROOT_ENV         "%CTSROOT%"
#define CTSROOT             "CTSROOT"                            
#define CTSRSSTYP           "CTSRSSTYP"                          
#define REG_ENV_PATH        "Software\\%s\\%s\\AgentParameters"  /* Not Used in CC */
#define INIT_FILE_NAME      "%CTSROOT%\\DATA\\CTSPARM.PRM"       /* Not Used in CC */ 

#define SA_HOSTNAME         "CmnHostName"                        

#define ANCHOR_FILE_NAME    "Anchor.txt"
#define SM_INSTANCE_ID      "SM_INSTANCE_ID"
#define SM_SERVICE_NAME     "SM_SERVICE_NAME"
#define SM_INSTANCE_ROOT    "SM_INSTANCE_ROOT"
#define SM_SMPARM_LOCATION  "SM_SMPARM_LOCATION"


/********************************************
 * Executables                        *
 ********************************************/

/*#define  WNT_DLL_FILE        "%s\\CTS_API_%s.DLL"*/
#define  EXE_DIR_NAME        "bin"
#define  SA_AGENT_ID         "CTSA0_AGENTID" /*Created Env.Var, but not Used */
#define  EXECUTABLE_DIR_PATH "EXECUTABLE_DIR_PATH"

#define  CE_EXE_NAME         "p_ctsce.exe"
#define  CS_EXE_NAME         "p_ctscs.exe"
#define  CD_EXE_NAME         "p_ctscd.exe"
#define  CTSMANAGER_EXE      "ctsmanager.exe"
#define  OFFLINE_EXE_NAME    "ctssoffi.exe"
#define  ONLINE_EXE_NAME     "ctssoni.exe"
#define  CTSADM_EXE          "ctsadm.exe"
#define  CTSPRC_EXE          "ctsprc.exe"
#define  CTSKGSD_EXE         "ctskgsd.exe"
#define  CTSDIAG_EXE         "ctsdiag.exe"
#define  CTSADAPT_EXE        "ctsadapt.exe"
#define  CTSHTDWN_EXE        "ctshtdwn.exe"
#define  CTSQCR_EXE          "ctsqcr.exe"
#define  CTSQPR_EXE          "ctsqpr.exe"

/****************************************************
 * Process & Utilities exit statuses.
 ****************************************************/

#define PLAT_OK_STAT     0     /* Process terminated OK */
#define PLAT_FAIL_STAT   1     /* Process terminated due to error */

#define HELP_PRM         "/H,-H"

/****************************************************
 * CE stuff
 ****************************************************/

/* #define  COM_MAX_MSG_SZ        (2*10240) AVIW-19/11/00*/

#define  CO_ESA_MBX_RETRY_INT  100 
#define  CO_LOOP_SLEEP_TIME    100
#define  CO_SLEEP_TIME         100

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

#define OFFLINE_RSS_VERB_KWD           "OFLI_VERBOSE"
#define MS_WORK_DIR                    "MS_WORK_DIR"
#define OFLI_WORK_PATH_PARAM           "MS_WORK_DIR"
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

#define COI_USR_IMG_FILE_NAME "usrimg.dat"
#define COI_GRP_IMG_FILE_NAME "grpimg.dat"
#define COI_CNN_IMG_FILE_NAME "cnnimg.dat"
#define COI_RPM_IMG_FILE_NAME "rpmimg.dat"
#define COI_CNT_IMG_FILE_NAME "cntimg.dat"
#define COI_USR_OMG_FILE_NAME "usromg.dat"
#define COI_GRP_OMG_FILE_NAME "grpomg.dat"
#define COI_CNN_OMG_FILE_NAME "cnnomg.dat"
#define COI_RPM_OMG_FILE_NAME "rpmomg.dat"
#define COI_CNT_OMG_FILE_NAME "cntomg.dat"
#define COI_OSF_FILE_NAME     "osf.dat"
#define COI_MSF_FILE_NAME     "msf.dat"
#define COI_TSF_FILE_NAME     "tsf.dat"
#define COI_STATUS_FILE_NAME  "status.dat"
#define COI_PSF_FILE_NAME     "psf.dat"

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
