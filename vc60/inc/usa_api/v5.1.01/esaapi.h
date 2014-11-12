/** @file esaapi.h
 * Agent interface to USA-API and interceptors
 */
/**********************************************************************
*
*   H Source      : esaapi.h
*   Description   : Agent interface to USA-API and interceptors
*   %full_filespec: esaapi.h#18:incl:3 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef ESAAPI_H_INCLUDED
#define ESAAPI_H_INCLUDED

#include "esaglobs.h"

#if defined (MVS)
#define DATA_COMP_ESAAPI__  esaap01
#define DATA_COMP_APICODE__ esaap02
#define DATA_COMP_APICONN__ esaap03
#define DATA_COMP_APIDEFS__ esaap04
#define DATA_COMP_APIEVNT__ esaap05
#define DATA_COMP_APIGNRL__ esaap06
#define DATA_COMP_APIGRP__  esaap07
#define DATA_COMP_APIOE__   esaap08
#define DATA_COMP_APIOLDV__ esaap09
#define DATA_COMP_APIRES__  esaap10
#define DATA_COMP_APISRVC__ esaap11
#define DATA_COMP_APIUSER__ esaap12
#endif

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*  */

struct  S_ADMIN_PARAMS;
typedef  struct  S_ADMIN_PARAMS  ADMIN_PARAMS_rec_typ;
typedef  struct  S_ADMIN_PARAMS  * ADMIN_PARAMS_rec_ptr;


#ifdef WNTINC
#include "addinfo.h"
#else
#include ESA_ADDINFO
#endif

/********************************************/

static char API_VERSION[]="5.1.01";

/********************************************/

#include  "apidefs.h"    /* General definitions          */
#include  "apisrvc.h"    /* Agent callable services      */
#include  "apioldv.h"    /* obsolete functions           */

#include  "apignrl.h"    /* USA-API general functions    */
#include  "apiuser.h"    /* USA-API user functions       */
#include  "apigrp.h"     /* USA-API group functions      */
#include  "apiconn.h"    /* USA-API connection functions */
#include  "apires.h"     /* USA-API resource functions   */
#include  "apioe.h"      /* USA-API container functions  */

#include  "apievnt.h"    /* Agent interceptors services  */

/*******************************************************************/
/*                Agent Callable Services                          */
/*  Agent function pointers passed to USA-API for their code to    */
/*  be used.                                                       */
/*******************************************************************/

typedef  struct  S_CS_FUNC_PTR {
  SM_VERSION_FUNC_PTR            SMVersionEX_ptr; 
  RSSLIST_GET_FUNC_PTR               rsslist_get_ptr;
  RSSPRM_GET_FUNC_PTR                rssprm_get_ptr;
  RSSPRM_GET_OPT_FUNC_PTR            rssprm_get_opt_ptr;
  RSSKWD_TYP_FUNC_PTR                rsskwd_typ_ptr;
  INTERCEPT_SET_FUNC_PTR             intercept_set_ptr;
  INTERCEPT_SEND_FUNC_PTR          intercept_setEX_ptr;  
  LOGEVT_FUNC_PTR                    LOG_event_ptr;
  MSG_PRINT_FUNC_PTR                 MSG_printf_ptr;
  MSG_VPRINT_FUNC_PTR            MSG_vprintfEX_ptr;
  DIAG_PRINTF_FUNC_PTR               DIAG_printf_ptr;
  DIAG_GET_DEBUG_LEVEL_FUNC_PTR      DIAG_get_debug_level_ptr;
  DIAG_ENTER_FUNC_PTR                DIAG_enter_ptr;
  DIAG_EXIT_FUNC_PTR                 DIAG_exit_ptr;
  DIAG_REFRESH_FUNC_PTR              DIAG_refresh_ptr;
  DIAG_GET_INFO_FUNC_PTR         DIAG_get_infoEX_ptr; 
  DIAG_INITIALIZE_FUNC_PTR       DIAG_initializeEX_ptr; 
  DIAG_TERMINATE_FUNC_PTR        DIAG_terminateEX_ptr; 
  GET_TIMESTAMP_FUNC_PTR         GLB_get_timestrEX_ptr;
  DIAGR_VPRINTF_FUNC_PTR           DIAG_vprintfEX_ptr;
  DIAGR_PRINTF_FUNC_PTR            DIAG_printfEX_ptr;
  DIAGR_ENTER_FUNC_PTR             DIAG_enterEX_ptr;
  DIAGR_EXIT_FUNC_PTR              DIAG_exitEX_ptr;
  RSSLIST_GET_EX_FUNC_PTR          rsslist_getEX_ptr;
  RSSPRM_GET_EX_FUNC_PTR           rssprm_getEX_ptr;
  RSSPRM_GET_OPT_EX_FUNC_PTR       rssprm_get_optEX_ptr;
  RSSKWD_TYP_EX_FUNC_PTR           rsskwd_typEX_ptr;
  LOGEVT_EX_FUNC_PTR               LOG_eventEX_ptr;
  MSG_PRINT_EX_FUNC_PTR            MSG_printfEX_ptr;
  ENCRYPT_INT_FUNC_PTR           Encrypt_intEX_ptr;
  DECRYPT_INT_FUNC_PTR           Decrypt_intEX_ptr;
  /* ADDINFO processing functions */
   ADI_kwd_find_PTR                 ADI_kwd_find_ptr;
   ADI_kwd_get_next_PTR             ADI_kwd_get_next_ptr;
   ADI_kwd_find_by_prefix_PTR       ADI_kwd_find_by_prefix_ptr;
   ADI_kwd_and_value_add_PTR        ADI_kwd_and_value_add_ptr;
   ADI_kwd_delete_PTR               ADI_kwd_delete_ptr;
   ADI_kwd_dup_check_PTR            ADI_kwd_dup_check_ptr;
   ADI_value_get_PTR                ADI_value_get_ptr;
   ADI_value_set_PTR                ADI_value_set_ptr;
   ADI_kwd_find_value_get_PTR       ADI_kwd_find_value_get_ptr;
   ADI_kwd_find_value_set_PTR       ADI_kwd_find_value_set_ptr;
   ADI_kwd_find_and_delete_PTR      ADI_kwd_find_and_delete_ptr;
   ADI_value_reset_PTR              ADI_value_reset_ptr;
   ADI_value_concat_PTR             ADI_value_concat_ptr;
   ADI_table_reset_PTR              ADI_table_reset_ptr;
   ADI_table_alloc_PTR              ADI_table_alloc_ptr;
   ADI_table_free_PTR               ADI_table_free_ptr;
   ADI_table_realloc_PTR            ADI_table_realloc_ptr;
   ADI_table_copy_PTR               ADI_table_copy_ptr;
   ADI_table_diag_PTR               ADI_table_diag_ptr;
   ADI_table_to_buffer_PTR          ADI_table_to_buffer_ptr;
   ADI_table_from_buffer_PTR        ADI_table_from_buffer_ptr;
   ADI_list_search_PTR              ADI_list_search_ptr;
   ADI_list_diff_PTR                ADI_list_diff_ptr;
   ADI_list_convert_sep_PTR         ADI_list_convert_sep_ptr;
   ADI_list_to_string_PTR           ADI_list_to_string_ptr;
   ADI_list_from_string_PTR         ADI_list_from_string_ptr;
   ADI_list_entry_append_start_PTR  ADI_list_entry_append_start_ptr;
   ADI_list_subfield_get_next_PTR   ADI_list_subfield_get_next_ptr;
   ADI_list_subfield_append_PTR     ADI_list_subfield_append_ptr;

   RSINIT_X_FUNC_PTR                CTSInterceptorInitEX_ptr;
   RSTERM_X_FUNC_PTR                CTSInterceptorTermEX_ptr;
   RS_PWDMOD_X_FUNC_PTR             CTSPassModEventEX_ptr;
   RS_USDIS_X_FUNC_PTR              CTSUserRevokedEventEX_ptr; 
   RS_USER_X_FUNC_PTR               CTSUserEventEX_ptr;    
   RS_RNUSER_FUNC_PTR               CTSRenameUserEventEX_ptr;
   RS_MVUSER_FUNC_PTR               CTSMoveUserEventEX_ptr;
   RS_UG_X_FUNC_PTR                 CTSUGEventEX_ptr;    
   RS_RNUG_FUNC_PTR                 CTSRenameUGEventEX_ptr; 
   RS_MVUG_FUNC_PTR                 CTSMoveUGEventEX_ptr;
   RS_CONN_X_FUNC_PTR               CTSConnectionEventEX_ptr;
   RS_OE_X_FUNC_PTR                 CTSOEEventEX_ptr;    
   RS_MVOE_FUNC_PTR                 CTSMoveOEEventEX_ptr; 
   RS_RNOE_FUNC_PTR                 CTSRenameOEEventEX_ptr; 
   RSSSTATUS_X_FUNC_PTR             CTSRssStatusEventEX_ptr;  
   RS_RES_FUNC_PTR                  CTSResEventEX_ptr;    
   RS_RNRES_FUNC_PTR                CTSRenameResEventEX_ptr;
   RS_MVRES_FUNC_PTR                CTSMoveResEventEX_ptr;  
   RS_PRMMOD_X_FUNC_PTR             CTSParamsModEventEX_ptr; 

   PMPRM_GET_FUNC_PTR             pmprm_getEX_ptr;
} CS_FUNC_PTR_rec_typ,  * CS_FUNC_PTR_rec_ptr;

/** 
 * General Admin parameters.
 *
 * The admin_params structure is used as input to API functions, and at 
 * the same time includes pointers to these functions. Therefore the structure
 * must be declared (but cannot be detailed) before the API functions.
 * The exact definition is last, following the definitions of all functions.
 *
 */
typedef  struct  S_ADMIN_PARAMS {
    RSS_typ                      rss_name;
    RSS_typ                      rss_type;
    ADMIN_ANSI_typ               admin_uname_ansi;		/* for backward compatibility */
    ADMIN_UG_ANSI_typ            admin_gname_ansi;		/* for backward compatibility */
    RSS_vers_typ                 rss_version;
    ADMIN_MODE_typ               mode;
    void                       * os_proc_handle;
    void                       * login_handle;
    void                       * esadiag_handle;
    void                       * apiinit_handle;
    void                       * rssinit_handle;
    CTSAMSG_HANDLE_rec_typ     * ctsamsg_handle;
    CTSAMSG_DEST_TABLE_rec_typ * ctsamsg_dest;
    CS_FUNC_PTR_rec_typ          cs_func;
    PASSWD_ANSI_typ              admin_passwd_ansi; 	/* for backward compatibility */
    USER_ANSI_typ                def_admin_ansi;		/* for backward compatibility */
    PASSWD_ANSI_typ              def_admin_passwd_ansi; /* for backward compatibility */
	const char                 * program_name;   
    SERVICE_typ                  service_type;
    TRANSACTION_typ              transaction_type;
    void                       * transaction_handle;
	INTERCEPTOR_typ              InterceptorType;
	RESOURCE_typ                 MSCSWorkDir;
/* Fields changed in 5.1 start here */
	ADMIN_typ				     admin_uname;
	ADMIN_UG_typ		         admin_gname;
	PASSWD_typ                   admin_passwd;
    USER_typ                     def_admin;
    PASSWD_typ                   def_admin_passwd;
} S_ADMIN_PARAMS;


/********************************************************************
 * Procedure Name: CTSApiProcInit                                   * 
 * Description   : PROC functions initialization for the Api utility*
 * Input         : ProgramName   -                                  *
 *                 ProgramMain   -                                  *
 *                 argc_prm      -                                  *
 *                 argv_prm      -                                  *
 *                 EncrHndl      - Encryption handle                *
 *                 ProcHndl      - PROC handle                      *
 *                 admin_params                                     *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC PROCINIT_FUNC_TYP (char                  * ProgramName,
                                  char                  * ProgramMain, 
                                  int                     argc_prm,    
                                  char                 ** argv_prm,  
                                  void                 ** EncrHndl,   
                                  void                 ** ProcHndl,  
                                  ADMIN_PARAMS_rec_typ  * admin_params);

extern  PROCINIT_FUNC_TYP CTSApiProcInit; /* actual function */

typedef PROCINIT_FUNC_TYP * PROCINIT_FUNC_PTR;    /* pointer to func */

/********************************************************************
 * Procedure Name : CTSApiProcTerm                                  *  
 * Description    : PROC functions termination for the Api utility  *
 * Input          : exit_status - The process's return code         *
 *                  EncrHndl      - Encryption handle to be released*
 *                  ProcHndl      - PROC handle to be released      *
 * Output         : None                                            *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC PROCTERM_FUNC_TYP (ESA_RC    exit_status,
                                  void   ** EncrHndl,   
                                  void   ** ProcHndl);  

extern  PROCTERM_FUNC_TYP CTSApiProcTerm; /* actual function */

typedef PROCTERM_FUNC_TYP * PROCTERM_FUNC_PTR;    /* pointer to func */

/*******************************************************************/
/*  API function pointers structure - Structure must be filled by  */
/*  CTSApiLoad function, so the agent can call these functions.    */
/*  Any pointer that is not filled, the action will be treated as  */
/*  unsupported                                                    */
/*******************************************************************/

typedef  struct  S_FUNC_PTR {

  APIINIT_FUNC_PTR              apiinit_ptr;
  APITERM_FUNC_PTR              apiterm_ptr;
  APIVERSION_FUNC_PTR           apiversion_ptr;
  APIVERSION_X_FUNC_PTR         apiversion_x_ptr;

  RSSINIT_FUNC_PTR              rssinit_ptr;
  RSSTERM_FUNC_PTR              rssterm_ptr;

  GTRSPRM_FUNC_PTR              gtrsprm_ptr;
  STRSPRM_FUNC_PTR              strsprm_ptr;

  RSS_LOGIN_FUNC_PTR            rss_login_ptr;
  RSS_LOGOUT_FUNC_PTR           rss_logout_ptr;
  RSS_CHECK_FUNC_PTR            rss_check_ptr;

  GTUSERS_FUNC_PTR              gtusers_ptr;
  ADDUSER_FUNC_PTR              adduser_ptr;
  UPDUSER_FUNC_PTR              upduser_ptr;
  DELUSER_FUNC_PTR              deluser_ptr;
  REVUSER_FUNC_PTR              revuser_ptr;
  UPDPASS_FUNC_PTR              updpass_ptr;
  VERIFY_PWD_FUNC_PTR           VerifyPassword_ptr;
  MVUSER_FUNC_PTR               mvuser_ptr;
  RNUSER_FUNC_PTR               rnuser_ptr;

  GETUGS_FUNC_PTR               getugs_ptr;
  ADDUG_FUNC_PTR                addug_ptr;
  UPDUG_FUNC_PTR                updug_ptr;
  DELUG_FUNC_PTR                delug_ptr;
  MVUG_FUNC_PTR                 mvug_ptr;
  RNUG_FUNC_PTR                 rnug_ptr;

  GTUG2UC_FUNC_PTR              gtug2uc_ptr;
  ADDU2UG_FUNC_PTR              addu2ug_ptr;
  UPDU2UG_FUNC_PTR              updu2ug_ptr;
  DELU2UG_FUNC_PTR              delu2ug_ptr;
  GETCONNECTION_FUNC_PTR        getconnection_ptr; 
  ADDCNN_FUNC_PTR               addcnn_ptr;
  UPDCNN_FUNC_PTR               updcnn_ptr;
  DELCNN_FUNC_PTR               delcnn_ptr;
  
  GETRES_FUNC_PTR               getres_ptr;
  ADDRES_FUNC_PTR               addres_ptr;
  UPDRES_FUNC_PTR               updres_ptr;
  DELRES_FUNC_PTR               delres_ptr;
  MVRES_FUNC_PTR                mvres_ptr;
  RNRES_FUNC_PTR                rnres_ptr;
  
  GTRSACL_FUNC_PTR              gtrsacl_ptr;
  ADDACE_FUNC_PTR               addace_ptr;
  UPDACE_FUNC_PTR               updace_ptr;
  DELACE_FUNC_PTR               delace_ptr;

  GETOES_FUNC_PTR               getoes_ptr;
  ADDOE_FUNC_PTR                addoe_ptr;
  UPDOE_FUNC_PTR                updoe_ptr;
  DELOE_FUNC_PTR                deloe_ptr;
  ISUSERINOE_FUNC_PTR           isuserinoe_ptr;
  ISUGINOE_FUNC_PTR             isuginoe_ptr;
  ISOEINOE_FUNC_PTR             isoeinoe_ptr;
  MVOE_FUNC_PTR                 mvoe_ptr;
  RNOE_FUNC_PTR                 rnoe_ptr;

  ISMASKMATCH_FUNC_PTR          ismaskmatch_ptr;

  RSS_START_INTERCEPT_FUNC_PTR  rss_start_intercept_ptr;
  TRNSEVNT_FUNC_PTR             trnsevnt_ptr ;
  TRNSEVNT_X_FUNC_PTR           trnsevnt_x_ptr ;
  FORCEINTRCPT_FUNC_PTR         force_intercept_ptr;

  API_LOGIN_MODE_FUNC_PTR       APILoginModes_ptr;

  TRANS_START_FUNC_PTR          transaction_start_ptr;
  TRANS_END_FUNC_PTR            transaction_end_ptr;
  void                         *Reserved6 ;
  void                         *Reserved5 ;
  void                         *Reserved4 ;
  void                         *Reserved3 ;
  void                         *Reserved2 ;
  void                         *Reserved1 ;

  /* PM 5.1.00 Functions */
	PMAPIVERSION_FUNC_PTR       pmapiversion_ptr;

} FUNC_PTR_rec_typ,  * FUNC_PTR_rec_ptr;

#define FUNC_PTR_ARRAY_SIZE \
    (sizeof (FUNC_PTR_rec_typ) / sizeof (APIINIT_FUNC_PTR))

/***************************************************************/
/* RSS Limits - to be filled by USA-API function CTSApiLoad    */
/***************************************************************/

/* Format of data sent between USA-API and agent */
typedef enum {SUPPORT_I18N_NO,       /* Data in ASCII/EBCDIC    */
              SUPPORT_I18N_UTF8      /* Data in UTF8/UTFE       */
} SUPPORT_I18N_typ;      

typedef  struct  S_RSS_LIMITS {
  unsigned int           max_pwd_len;
  unsigned int           max_restype_len;
  unsigned int           max_user_len;
  unsigned int           max_ace_user_len;
  unsigned int           max_oe_len;
  unsigned int           max_ace_oe_len;
  unsigned int           max_ug_len;
  unsigned int           max_ace_ug_len;
  unsigned int           max_resource_len;
  unsigned int           max_addinfo_kwd_len;
  unsigned int           max_addinfo_val_len;
  unsigned int           max_euid_len;
  SUPPORT_I18N_typ       support_I18N;
  char                   pm_ver[RSS_VERS_LEN + 1]; /* Version of Provisioning */
                                                   /* Module for checking the */
                                                   /* compatability with the  */
                                                   /* SA-Agent Services Mgr.  */

} RSS_LIMITS_rec_typ, * RSS_LIMITS_rec_ptr;

/********************************************************************
 * Procedure Name: CTSAPILoad                                       *
 * Description   : Load api functions                               *
 * Input         : RSS name and type                                *
 *                 CTSAMSG stuff                                    *
 *                  admin_params                                    *
 * Output        : func ptr structure                               *
 *                 CTSAMSG error structure                          *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 ********************************************************************/

typedef ESA_RC API_LOAD_FUNC_TYP (
                                  RSS_typ                rss_name,
                                  FUNC_PTR_rec_typ     * func_ptr,
                                  RSS_LIMITS_rec_typ   * rss_limits_ptr,
                                  ADMIN_PARAMS_rec_typ * admin_params,
                                  ERR_STRUCT_rec_typ   * err);

extern  API_LOAD_FUNC_TYP   CTSAPILoad;        /* actual function */

typedef API_LOAD_FUNC_TYP * API_LOAD_FUNC_PTR; /* pointer to func */

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_ESAAPI__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_ESAAPI__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef ESAAPI_H_INCLUDED */

