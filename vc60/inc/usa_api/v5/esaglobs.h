/**********************************************************************
*
*   H Source      : esaglobs.h
*   Description   : USA-API Global Definitions
*   %full_filespec: esaglobs.h#6:incl:3 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef ESAGLOBS_H_INCLUDED
#define ESAGLOBS_H_INCLUDED

/*I18n: Japanese strings can take up to 3 times more place */
#define UTF8_MODIFIER 3 

#include  "string.h"
#include  "platform.h"

#define   EQ   ==
#define   NE   !=
#define   GT   >
#define   GE   >=
#define   LT   <
#define   LE   <=

#define   AND  &&
#define   OR   ||
#define   NOT  !

#define   ADDINFO_LIST_ENTRY        0x01
#define   ADDINFO_LIST_SUBFIELD     0x02


#define   NULL_CHAR      '\0'
#define   NEWLINE        '\n'
#define   BACKSLASH      '\\'
#define   BACKSLASH_STR  "\\"
#define   QUOTE_CHAR     '\''
#define   NULL_STRING    ""

#define  ESS_YES_FLAG          "Y"
#define  ESS_NOT_FLAG          "N"
#define  ESS_YES_SIGN          'Y'
#define  ESS_NOT_SIGN          'N'

#define   ESA_OK                 0
#define   ESA_SKIP               1
#define   ESA_WARN               2
#define   ESA_ERR                3
#define   ESA_FATAL              4
#define   ESA_LOCKED             5  /* File/record already locked */
#define   ESA_KEY_NOT_FOUND      6  /* key not found in DB        */
#define   ESA_DUP_KEY            7  /* duplicate key found in DB  */
#define   ESA_EOF                8  /* End of file encountered    */
#define   ESA_NOT_SUPP           9  /* Unsupported API function   */
#define   ESA_RC_UNDEFINED      10  /* for Post, when actual not run */
#define   ESA_MBX_FULL          11
#define   ESA_MBX_NOT_EXIST     12
#define   ESA_MBX_BUFFEROVF     13
#define   ESA_MBX_EMPTY         14
#define   ESA_MBX_ALREADY_EXIST 15
#define   ESA_TERM_CTSA         16
#define   ESA_CANCEL_SERVICE    17
#define   ESA_FATAL_IO          18  /* A fatal I/O that should cause
                                       process rundown - reserved for
                                       COMMON CODE only!!         */
#define   ESA_ABORT_REQ         19
#define   ESA_RSS_INACTIVE      20
#define	  ESA_UNKNWNERR          21
#define   ESA_DB_DUPLIC          22
#define	  ESA_PROC_NOTEXIST      23
#define	  ESA_PROC_EXIST         24
/* This RC is a special value used in ESA_DIAG_exit by functions that
 * do not return a value.
 */
#define       ESA_LENGTH_ERR       25
#define       ESA_SOS              26
#define       ESA_VOID             27 
#define       CE_STAT_TERMINATE      28
#define       CE_STAT_WAIT_TERMINATE 29
#define       CE_STAT_SESS_CLOSED    30 
#define       CE_STAT_OK             31
#define       CE_STAT_WAIT_AJF_REF   32
#define       CE_STAT_AJF_REF        33
#define       CE_STAT_AFTER_AJF_REF  34
#define       CE_STAT_DOWNLOAD_REQ   35
#define       CE_STAT_DOWNLOAD       36
#define       CE_SRVC_BAD_MSG        37
#define       CE_SRVC_CNTL_MSG       38
#define       CE_SRVC_NO_MORE        39
#define       CE_SRVC_WAIT_SERVER    40
#define       CE_SRVC_SESS_CLOSED    41
#define       CE_DSPT_MSG_NOT_ALWD   42
#define       CE_SRVR_P_MAX_REACHED  43
#define       ESA_MAX_RC             44 

#define       ESA_RC_VOID            666 

typedef long int ESA_RC;


#define   CLEAR(X)         memset ((char *)(X),  '\0', sizeof ((X)))
#define   CLEAR_STRUCT(X)  memset ((char *)&(X), '\0', sizeof ((X)))

#define  ESA_API         "esaapi.h"
#define  ESA_API_CODES   "apicode.h"
#define  ESA_ESAADI      "esaadi.h" 
#define  ESA_CTSAMSG     "ctsamsg.h"  
#define  ESA_ADDINFO     "addinfo.h"
#define  ESA_HLPUTILS    "hlputils.h"
#define  ESA_DIAG        "esadiag.h"
#define  ESA_VER         "esaver.h"

/* Unicode stuff */
#define UTFCONV		"utfconv.h"
#define ESA_CONV	"gt_conv.h"

/* define BOOL, TRUE and FALSE */

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
#ifdef ESAINIT_C
void DATA_COMP_ESAGLOBS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_ESAGLOBS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif /* ESAGLOBS_H_INCLUDED */
