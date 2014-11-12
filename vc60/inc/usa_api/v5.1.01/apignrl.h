/**********************************************************************
*
*   H Source      : apignrl.h
*   Description   : USA-API general processing functions
*   %full_filespec: apignrl.h#5:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIGNRL_H_INCLUDED
#define APIGNRL_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API general       == */
/* == functions.                                                     == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name : CTSVersion                                      *
 * Description    : API version from API_VERSION                    *
 * Input          : None                                            *
 * Output         : version - API version - 4.0.0 etc.              *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC APIVERSION_X_FUNC_TYP (RSS_vers_typ      version,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  APIVERSION_X_FUNC_TYP   CTSVersionEX;    /* actual function */

typedef APIVERSION_X_FUNC_TYP * APIVERSION_X_FUNC_PTR;/*pointer to func */

/********************************************************************
 * Procedure Name : CTSAPIInit                                      *
 * Description    : API initialization                              *
 * Input          : admin_params                                    *
 * Output         : err - Messages (Opt.)                           *
 * Return Value   : ESA_RC                                          *
 * Comments       : API-dependent operations to be performed        *
 *                  prior to any API call.                          *
 *                  If the function need to pass information to     *
 *                  other USA-API functions, it can allocate storage*
 *                  and store its address in                        *
 *                         admin_params->apiinit_handle             *
 ********************************************************************/

typedef ESA_RC APIINIT_FUNC_TYP (ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  APIINIT_FUNC_TYP   CTSAPIInit;       /* actual function */

typedef APIINIT_FUNC_TYP * APIINIT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAPITerm                                      *
 * Description    : API termination & cleanup                       *
 * Input          : admin_params                                    *
 * Output         : err - Messages (Opt.)                           *
 * Return Value   : ESA_RC                                          *
 * Comments       : API-dependent operations to be performed        *
 *                  when API is no longer needed.                   *
 *                  Remember to release the storage pointed by      *
 *                  admin_params->apiinit_handle if used by         *
 *                  CTSAPIInit                                      *
 ********************************************************************/

typedef ESA_RC APITERM_FUNC_TYP (ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  APITERM_FUNC_TYP   CTSAPITerm;       /* actual function */

typedef APITERM_FUNC_TYP * APITERM_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRSSInit                                      *
 * Description    : RSS initialization - called when RSS is changed *
 * Input          : rss_name - RSS name                             *
 *                  rss_type - RSS type                             *
 *                  admin_params                                    *
 * Output         : handle   - to pass information, may contain     *
 *                             pointer to area allocated by this    *
 *                             function, in which data can be stored*
 *                  err      - Messages (Opt.)                      *
 * Return Value   : ESA_RC                                          *
 * Comments       : The handle is stored in the admin_params        *
 *                  structure (rssinit_handle), for the use         *
 *                  of other USA-API functions. If used, the area   *
 *                  must be freed by CTSRSSTerm.                    *
 ********************************************************************/

typedef ESA_RC RSSINIT_FUNC_TYP (
                                 RSS_typ                rss_name,
                                 RSS_typ                rss_type,
                                 void                ** handle,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  RSSINIT_FUNC_TYP   CTSRSSInit;       /* actual function */

typedef RSSINIT_FUNC_TYP * RSSINIT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRSSTerm                                      *
 * Description    : RSS termination & cleanup                       *
 * Input          : rss_name - RSS name                             *
 *                  rss_type - RSS type                             *
 *                  admin_params                                    *
 *                  handle   - addr of area allocate by CTSRSSInit  *
 *                             area should be released by this      *
 *                             function and pointer cleared.        *
 * Output         : err      - Messages (Opt.)                      *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RSSTERM_FUNC_TYP (
                                 RSS_typ                rss_name,
                                 RSS_typ                rss_type,
                                 void                ** handle,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  RSSTERM_FUNC_TYP   CTSRSSTerm;       /* actual function */

typedef RSSTERM_FUNC_TYP * RSSTERM_FUNC_PTR; /* pointer to func */


/********************************************************************
 * Procedure Name : CTSTransactionStart                             *
 * Description    : Transaction initialization - called when start  *
 *                      new transaction.                            *
 * Input          : admin_params                                    *
 * Output         : handle   - to pass information, may contain     *
 *                             pointer to area allocated by this    *
 *                             function, in which data can be stored*
 *                  err      - Messages (Opt.)                      *
 * Return Value   : ESA_RC                                          *
 * Comments       : The handle is stored in the admin_params        *
 *                  structure (transaction_handle), for the use     *
 *                  of other USA-API functions. If used, the area   *
 *                  must be freed by CTSTransactionEnd.             *
 ********************************************************************/

typedef ESA_RC TRANS_START_FUNC_TYP (void                ** handle,
                                     ADMIN_PARAMS_rec_typ * admin_params,
                                     ERR_STRUCT_rec_typ   * err);

extern  TRANS_START_FUNC_TYP   CTSTransactionStart;  /* actual function */

typedef TRANS_START_FUNC_TYP * TRANS_START_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSTransactionEnd                               *
 * Description    : Transaction termination & cleanup               *
 * Input          : admin_params                                    *
 *                  handle   - addr of area allocate by             *
 *                      CTSTransactionStart area should be released *
 *                      by this function and pointer cleared.       *
 * Output         : err      - Messages (Opt.)                      *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC TRANS_END_FUNC_TYP (void                ** handle,
                                   ADMIN_PARAMS_rec_typ * admin_params,
                                   ERR_STRUCT_rec_typ   * err);

extern  TRANS_END_FUNC_TYP   CTSTransactionEnd;   /* actual function */

typedef TRANS_END_FUNC_TYP * TRANS_END_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSGetRSSParams                                 *
 * Description    : Get RSS parameters                              *
 * Input          : admin_params                                    *
 * Output         : rss_params - RSS data                           *
 *                  addinfo    - RSS_specific keywords              *
 *                  err        - Messages (Opt.)                    *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC GTRSPRM_FUNC_TYP (RSS_PARAMS_rec_typ   * rss_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  GTRSPRM_FUNC_TYP   CTSGetRSSParams;  /* actual function */

typedef GTRSPRM_FUNC_TYP * GTRSPRM_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSSetRSSParams                                 *
 * Description    : Modify RSS global parameters                    *
 * Input          : rss_params  - RSS data                          *
 *                  addinfo     - RSS keywords to be updated in RSS *
 *                  admin_params                                    *
 * Output         : err         - messages (Opt.)                   *
 *                  Note : addinfo may be changed for the benefit of*
 *                  post-script.                                    *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC STRSPRM_FUNC_TYP (RSS_PARAMS_rec_typ   * rss_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  STRSPRM_FUNC_TYP   CTSSetRSSParams;  /* actual function */

typedef STRSPRM_FUNC_TYP * STRSPRM_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSRSSLogin                                      *
 * Description   : log in under the permissions and                 *
 *                 limitations of the requsted administrator.       *
 * Input         : rss_name     - RSS name                          *
 *                 admin        - administrator name                *
 *                 admin_group  - administrator's group             *
 *                 admin_passwd - administrator's password          *
 *                 login_mode   -  prepare (first) or do login      *
 *                 admin_params -                                   *
 * Output        : err          - Messages (Opt.)                   *
 *                 handle       - NULL on 1st call, filled by callee*
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 ********************************************************************/

typedef ESA_RC RSS_LOGIN_FUNC_TYP (RSS_typ                rss_name,
                                   USER_typ               admin,
                                   UG_typ                 admin_group,
                                   PASSWD_typ             admin_passwd,
                                   LOGIN_MODE_typ         login_mode,
                                   void                ** handle,
                                   ADMIN_PARAMS_rec_typ * admin_params,
                                   ERR_STRUCT_rec_typ   * err);

extern  RSS_LOGIN_FUNC_TYP   CTSRSSLogin;        /* actual function */

typedef RSS_LOGIN_FUNC_TYP * RSS_LOGIN_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSRSSLogout                                     *
 * Description   : logout from the last OS_CS_login                 *
 * Input         : rss_name     - RSS name                          *
 *                 admin        - administrator name                *
 *                 admin_group  - administrator's group             *
 *                 admin_passwd - administrator's password          *
 *                 login_mode   - do logout or clean (last)         *
 *                 admin_params -                                   *
 * Output        : err          - Messages (Opt.)                   *
 *                 handle       - Value passed from login.          *
 *                                If mode is last, free the area.   *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 ********************************************************************/

typedef ESA_RC RSS_LOGOUT_FUNC_TYP (RSS_typ                rss_name,
                                    USER_typ               admin,
                                    UG_typ                 admin_group,
                                    LOGIN_MODE_typ         login_mode,
                                    void                ** handle,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  RSS_LOGOUT_FUNC_TYP   CTSRSSLogout;        /* actual function */

typedef RSS_LOGOUT_FUNC_TYP * RSS_LOGOUT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSRSSCheck                                      *
 * Description   : checks if RSS is alive                           *
 * Input         : rss_name     -  RSS name                         *
 *                 admin_params -                                   *
 * Output        : status       -  RSS_UP if rss is alive           *
 *                                 RSS_DOWN if rss is down          *
 *                 err          - Messages (Opt.)                   *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 ********************************************************************/

typedef ESA_RC RSS_CHECK_FUNC_TYP (RSS_typ                rss_name,
                                   RSS_STATUS_typ       * status,
                                   ADMIN_PARAMS_rec_typ * admin_params,
                                   ERR_STRUCT_rec_typ   * err);

extern  RSS_CHECK_FUNC_TYP   CTSRSSCheck;        /* actual function */

typedef RSS_CHECK_FUNC_TYP * RSS_CHECK_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSAPILoginModes                                 *
 * Description   : Returns a flag for each USA-API functions,       * 
 *                 indicating if a LOGIN and LOGOUT should be       *
 *                 performed for this function.                     *
 * Input         : FuncLoginModes - array of flags                  *
 *                 admin_params   -                                 *
 * Output        : err            - Messages (Opt.)                 *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 * Note - If function is not implemented in the USA-API, a LOGIN and*
 *        LOGOUT will be performed for every USA-API function.      *    
 ********************************************************************/

typedef ESA_RC API_LOGIN_MODE_FUNC_TYP (
                         FUNC_LOGIN_MODE_rec_typ * FuncLoginModes,
                         ADMIN_PARAMS_rec_typ    * admin_params,
                         ERR_STRUCT_rec_typ      * Err);

extern  API_LOGIN_MODE_FUNC_TYP   CTSAPILoginModes;/* actual function*/

typedef API_LOGIN_MODE_FUNC_TYP * API_LOGIN_MODE_FUNC_PTR;

/********************************************************************
 * Procedure Name : CTSIsMaskMatch                                  *
 * Description    : Object matches a mask                           *
 * Input          : object       - exact ID                         *
 *                  mask         - as typed in the ESS GUI          *
 *                  object type  - user/group etc.                  *
 *                  mask type    - regular/wild                     * 
 *                  admin_params -                                  *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_OK     Object matches the mask              *
 *                  ESA_EOF    Object does not match the mask       *
 *                  ESA_ERR    on any other situation               *
 ********************************************************************/

typedef ESA_RC ISMASKMATCH_FUNC_TYP (
                                     char                 * object,
                                     char                 * mask,
                                     OBJECT_TYPE_typ        object_type,
                                     MASK_TYPE_typ          mask_type,
                                     ADMIN_PARAMS_rec_typ * admin_params,
                                     ERR_STRUCT_rec_typ   * err);

extern  ISMASKMATCH_FUNC_TYP   CTSIsMaskMatch;      /* actual function*/

typedef ISMASKMATCH_FUNC_TYP * ISMASKMATCH_FUNC_PTR;/*pointer to func*/

/* ------------------------------------------------------- */
/* -- The following are interceptor-related functions  --- */
/* -- to be implemented in a USA-API.                  --- */
/* ------------------------------------------------------- */

/********************************************************************
 * Procedure Name : CTSTransactionEventEx                           *
 * Description    : Notify interceptor of ESS transaction.          *
 *                  This function should be implemented if an       *
 *                  interceptor other than the standard offline int.*
 *                  is used. In which case, the function should     *
 *                  notify the custom interceptor that this change  *
 *                  was made from the ESS, so there is not need to  *
 *                  create an interception for it.                  *
 * Input          : intercept_rec         - interception details    *
 *                  connflag              - update connection flag  *
 *                  admin_params                                    *
 * Output         : err                   - Messages (Opt.)         *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC TRNSEVNT_X_FUNC_TYP (
                            INTERCEPT_rec_ptr         intercept_rec, 
                            TRNSEVNT_UPCON_FLAG_typ   connflag,
                            ADMIN_PARAMS_rec_typ    * admin_params,
                            ERR_STRUCT_rec_typ      * err);

extern  TRNSEVNT_X_FUNC_TYP   CTSTransactionEventEx;/*actual function*/

typedef TRNSEVNT_X_FUNC_TYP * TRNSEVNT_X_FUNC_PTR; /*pointer to func*/

/********************************************************************
 * Procedure Name: CTSInterceptorStart                              *
 * Description   : Start an offline interceptor.                    *
 * Input         : rss_name     - RSS name                          *
 *                 host name    -                                   *
 *                 admin_params                                     *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_FATAL  on any fail situation                 *
 ********************************************************************/

typedef ESA_RC RSS_START_INTERCEPT_FUNC_TYP (
                                      RSS_typ                rss_name,
                                      char                 * host_name,
                                      ADMIN_PARAMS_rec_typ * admin_params,
                                      ERR_STRUCT_rec_typ   * err);

extern  RSS_START_INTERCEPT_FUNC_TYP   CTSInterceptorStart;

typedef RSS_START_INTERCEPT_FUNC_TYP * RSS_START_INTERCEPT_FUNC_PTR;


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIGNRL__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIGNRL__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIGNRL_H_INCLUDED */
