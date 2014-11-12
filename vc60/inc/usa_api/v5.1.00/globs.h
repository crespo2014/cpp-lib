/****************************************************
* Title           : SA-Agent Global Definitions
* File Name       : globs.h
* Author          : Amir
* Creation Date   : 15-Feb-94
* Description     : Global definitions
*****************************************************/

#ifndef GLOBS_H_INCLUDED
#define GLOBS_H_INCLUDED

#include "esaglobs.h"
#ifdef MVS
#define DATA_COMP_GLOBS__ glbs01
#endif
/* For SCRIPTS */

#define SCRIPT_DEL_KWD_1       "__DELETE__"
#define SCRIPT_DEL_KWD_2       "**DELETE**"


/*  All processes & utilities */

#define ESA_MAIN_CE            "MAIN_CE"
#define ESA_MAIN_CD            "MAIN_CD"
#define ESA_MAIN_CS            "MAIN_CS"
#define ESA_MAIN_PRIVATE_ONLI  "MAIN_ONLI"
#define ESA_MAIN_COMMON_ONLI   "MAIN_CMN_ONLI"
#define ESA_MAIN_PRIVATE_OFLI  "MAIN_PRV_OFLI"
#define ESA_MAIN_COMMON_OFLI   "MAIN_OFLI"
#define ESA_MAIN_COI           "MAIN_COI"
#define ESA_MAIN_ODU           "MAIN_ODU"
#define ESA_MAIN_PWI           "MAIN_PWI"
#define ESA_MAIN_OTHER_INTRCPT "MAIN_OTHER_INTRCPT"  
#define ESA_MAIN_ACSDIAG       "MAIN_ACSDIAG"
#define ESA_MAIN_ACSPRC        "MAIN_ACSPRC"
#define ESA_MAIN_ACSADM        "MAIN_ACSADM"
#define ESA_MAIN_KGEN          "MAIN_KGEN"
#define ESA_MAIN_QCR           "MAIN_QCR"
#define ESA_MAIN_QPR           "MAIN_QPR"
#define ESA_MAIN_CTSC100       "MAIN_CTSC100"
#define ESA_MAIN_ACSADAPT      "MAIN_ACSADAPT"
#define ESA_MAIN_ACSALERT      "MAIN_ACSALERT"
#define ESA_MAIN_CTSHTDWN      "MAIN_CTSHTDWN"
#define ESA_MAIN_CTSCTRL       "MAIN_CTSCTRL"
#define ESA_MAIN_APIVER        "MAIN_APIVER"
#define ESA_MAIN_TEST          "MAIN_TEST"
#define ESA_MAIN_MBX           "MAIN_MBX_LIB"
#define ESA_MAIN_MNGR          "MAIN_MNGR"
#define ESA_MAIN_OTHER         "MAIN_OTHER"
#define ESA_MAIN_EXTERNAL      "EXTERNAL"

#define ESA_CE             "CE Server"
#define ESA_CD             "CD Server"
#define ESA_CS             "CS Server"
#define ESA_PRIVATE_ONLI   "Private Online Interceptor"
#define ESA_COMMON_ONLI    "Standard Online Interceptor"
#define ESA_PRIVATE_OFLI   "Private Offline Interceptor"
#define ESA_COMMON_OFLI    "Standard Offline Interceptor"
#define ESA_COI            "Standard Offline Interceptor (SOFFI)"
#define ESA_COI_UPGRADE    "Standard Offline Interceptor Upgrade (UpgSoffi)"
#define ESA_ODU            "Offline Download Utility"
#define ESA_PWI            "Password Interceptor"
#define ESA_OTHER_INTRCPT  "Other Interceptor"
#define ESA_ACSDIAG        "CTSDIAG Utility"
#define ESA_ACSPRC         "CTSPRC Utility"
#define ESA_ACSADM         "Admin File Utility"
#define ESA_KGEN           "CTSKGEN Utility"
#define ESA_QCR            "Queue Format Utility"
#define ESA_QPR            "Queue Print Utility"
#define ESA_CTSC100        "CTSC100 Utility"
#define ESA_ACSADAPT       "CTSADAPT Utility"
#define ESA_ACSALERT       "Alert Utility"
#define ESA_CTSHTDWN       "Shutdown Utility"
#define ESA_CTSCTRL        "Service Control Utility"
#define ESA_APIVER         "Print Provisioning Module Version Utility"
#define ESA_TEST           "USAAPI Test Utility"
#define ESA_MNGR           "MANAGER Utility"

#ifdef _TANDEM_SOURCE
#define ESA_MBX            "Mailbox Server"
#else
#define ESA_MBX            "Mailbox Library"
#endif

#define ESA_OTHER          "*UNKNOWN*"

typedef enum ESA_MAIN_typ {ESA_ACE_PROC,
                           ESA_ACS_PROC,
                           ESA_ACD_PROC,
                           ESA_ONLI_PROC,
                           ESA_COMMON_ONLI_PROC,
                           ESA_PRIVATE_OFLI_PROC,
                           ESA_OFLI_PROC,
                           ESA_COI_PROC,
                           ESA_COI_UPGRADE_PROC,
                           ESA_ODU_PROC,
                           ESA_PWI_PROC,
                           ESA_OTHER_INTERCEPTOR_PROC,
                           ESA_ACSDIAG_PROC,
                           ESA_ACSPRC_PROC,
                           ESA_ACSADM_PROC,
                           ESA_KGEN_PROC,
                           ESA_QCR_PROC,
                           ESA_QPR_PROC,
                           ESA_CTSC100_PROC,
                           ESA_ACSADAPT_PROC,
                           ESA_ACSALERT_PROC,
                           ESA_CTSHTDWN_PROC,
                           ESA_CTSCTRL_PROC,
                           ESA_APIVER_PROC,
                           ESA_TEST_PROC,
                           ESA_MNGR_PROC,
                           ESA_MBX_PROC,
                           ESA_OTHER_PROC,
                           ESA_EXTERNAL,
                           ESA_ALL_PROC
} ESA_MAIN_NAME_typ;

/****************************************************
 * ESA Platform-independent Include Files
 ****************************************************/

#define  ESA_DB         "esadb.h"
#define  ESA_SYNC       "acssync.h"
#define  ESA_PUMP       "acspump.h"
#define  ESA_ACSPUMP    "cspump.h"
#define  ESA_MSG        "esamsg.h"    /* CS Masseges             */
#define  ESA_MSG_GPF    "esamgpf.h"   /* CS Masseges global      */
#define  ESA_MSG_SETF   "esamset.h"   /* CS Masseges set func    */
#define  ESA_MSG_GETF   "esamget.h"   /* CS Masseges get func    */

#define  ESA_KWD        "acskwd.h"    /* CS Kewords              */
#define  ESA_SCRAPI     "acsapi.h"    /* CS Script-API table     */
#define  ESA_CS_SINFO   "acsinfo.h"   /* CS Struct to addinfo    */

#define  ESA_CS_OS      "esaoscs.h"   /* CS OS functions         */
#define  ESA_OS_PROC    "osproc.h"    /* OS_PROC stuff           */
#define  ESA_OS_MBX     "esambx.h"    /* Mailbox crapola         */
#define  ESA_OS_EVENT   "osevent.h"   /* OS events               */
#define  ESA_OS_CONSOLE "osconso.h"   /* Messages to console     */
#define  ESA_OS_SCRIPT  "osscrip.h"   /* OS Script     */
#define  ESA_UTFCONV    "utfconv.h"   /* Multi Lang.Support      */

#define  ESA_OS_SOCKOPS "sockops.h"   /* TCP/IP sockets ops      */

#define  ESA_CAREUSR    "acscarf.h"   /* care control entity         */
#define  ESA_ADMIN      "acsadm.h"    /* administrators maintanance  */
#define  ESA_INIT       "esainit.h"   /* for main and init. routines */
#define  ESA_PROC       "acsproc.h"   /* for start/end interceptor   */
#define  ESA_RSSF       "esarssf.h"   /* for RSS _ api functions     */
#define  ESA_RSS        "acsrss.h"    /* for RSS params              */
#define  ESA_PM         "acspm.h"     /* for PM params              */
#define  ESA_ACSU       "acsu.h"
/*#define  ESA_CI         "acsci.h"      Confirmation Interception */
#define  ESA_ALOCK      "acsalock.h"  /* SA-Agent Memory Allocation */
#define  ESA_LOCK       "acslock.h"  /*SA-Agent Lock/Unlock Name/File*/
#define  ESA_CMN        "acscmn.h"   /*SA-Agent Common functions*/
#define  ESA_DMP        "esadmp.h"
#define  ESA_QUEUE      "esaque.h"
#define  ESA_QUEUE_OS   "esaqos.h"
#define  ESA_PREPOST    "prepost.h"
#ifndef  ESA_ADDINFO
#define  ESA_ADDINFO    "addinfo.h"
#endif /* Sachin - ESA_ADDINFO*/

#define  ESA_API_PM     "pm.h"

#define  ESA_ADAPT      "adapt.h"
#define  ESA_MANAGER    "ctsmanager.h"
 
/********************************************
 * Grand Unified Offline Interceptor stuff
 *******************************************/

#define  ESA_OS_OFLI    "osofli.h"
#define  ESA_ESALIST    "esalist.h"
#define  ESA_WRITEOSF   "writeosf.h"

/********************************************
 * AR DES stuff
 *******************************************/

#define  AR_DES         "ardes.h"
#define  AR_TBL         "artbl.h"
#define  ENC_API        "encapi.h"

#define  ESA_CHKSUM     "chksum.h"

/* Include ESA_DIAG component defines */

#include  "esacomp.h"

/********************************************
 * CE (suco)
 *******************************************/

#define CE_COMM           "cecommsg.h"
#define CE_COMM_          "cecomsts.h"
#define CE_DB_IN          "ceprocnm.h"
#define CE_CONTA          "cecomcon.h"
#define CE_DISPA          "cedispat.h"
#define CE_ERR            "ceerrmsg.h"
#define CE_ERR_D          "ceerrdta.h"
#define CE_HDR_D          "cemsghdr.h"
#define CE_IPC            "cecomipc.h"
#define CE_MSG_B          "cemsgbod.h"
#define CE_PRIO           "cepriort.h"
#define CE_S_CO           "cesessds.h"
#define CE_S_CO_          "cesocket.h"
#define CE_S_IPR          "cecsmsgt.h"
#define CE_SESS           "cesessmn.h"
#define CE_SRVC           "cecssrvc.h"
#define CE_SRVC_          "cecspool.h"
#define CE_SRVR           "cecdsrvc.h"
#define CE_SRVR_          "cecdpool.h"
#define CE_STATU          "ceprcsts.h"

#define CE_OSMBX          "ce_osmbx.h"
#define CE_OSTCP		  "ostcp.h"
#define CE_OSSSL		  "osssl.h"


/* Define default level for ESA_DIAG_enter/exit */

#ifndef  DIAG_ENTER_LEVEL
#define  DIAG_ENTER_LEVEL   5
#endif


#ifdef ESAINIT_C
void DATA_COMP_GLOBS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_GLOBS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif

#endif /* GLOBS_H_INCLUDED */

