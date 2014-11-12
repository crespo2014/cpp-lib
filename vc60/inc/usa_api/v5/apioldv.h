/**********************************************************************
*
*   H Source      : apioldv.h
*   Description   : API Obsolete functions
*   %full_filespec: apioldv.h#5:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIOLDV_H_INCLUDED
#define APIOLDV_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains obsolete definitions.                == */
/* ==                                                                == */
/* == Functions defined in this file are still available for backward== */
/* == compatibility, but should not be used in new code.             == */
/* ==                                                                == */
/* ==================================================================== */
/* Old values, used by INTERCEPTOR_typ enum */
/*  INTERCEPT_OFFLINE  1
/*  INTERCEPT_ONLINE   2
*/
typedef enum {               
    GET_ALL_GRP_RES,          /* resource groups */
    GET_FREE_HANDLE_GRP_RES   /* free *handle    */
} GET_GRP_RES_MODE;           /* Old definition. Not in use by CC !!! */   


typedef enum {U2UG_ADM_IGNORED,
              U2UG_ADM_NONE,
              U2UG_ADM_AUDIT,
              U2UG_ADM_ADMIN,
              U2UG_ADM_ALL
} U2UG_ADMIN_typ;

typedef enum {U2UG_ATTR_IGNORED,
              U2UG_ATTR_REGULAR,
              U2UG_ATTR_DEFAULT_GROUP
} U2UG_ATTR_typ;

typedef  struct  S_U2UG_PARAMS {
    USER_typ        user;
    UG_typ          group;
    U2UG_ADMIN_typ  u2ug_admin_data;
    U2UG_ATTR_typ   u2ug_attr_data;
    UG_typ          def_group;
    TIMESTAMP_typ   timestamp;     
} U2UG_PARAMS_rec_typ;

/********************************************************************
* Procedure Name: INIT_intercept_set                                *
* Description   : Accept request for interception                   *
* Input         : interc. type, obj_type, OE, user, ug              *
* Output        : Interception passed to agent                      *
* Input/Output  : num_intercept_rec                                 *
* Return Value  : ESA_RC                                            *
* Note - Function remains for backward compatibility.               *
*        Replaced by function intercept_send.                       *
*********************************************************************/
#ifdef MVS
#define INIT_intercept_set_CS   intset
#endif 

typedef ESA_RC INTERCEPT_SET_FUNC_TYP (
        INTERCEPT_typ        type,
        INTERCEPT_obj_typ    obj_type,
        OE_typ               oe,
        USER_typ             user,
        UG_typ               ug);

extern  INTERCEPT_SET_FUNC_TYP INIT_intercept_set_CS;/* actual function */

typedef INTERCEPT_SET_FUNC_TYP * INTERCEPT_SET_FUNC_PTR;
                                                /* pointer to func */

/********************************************************************
 * Procedure Name: CTSTransactionEvent                              *
 * Description   : Notify interceptor of ESS transaction            *
 * Input         : Object type , container , user , group           *
 * Output         : err                   - Messages (Opt.)         *
 * Return Value  : ESA_RC                                           * 
 ********************************************************************/

typedef ESA_RC TRNSEVNT_FUNC_TYP (INTERCEPT_obj_typ       object_type ,
                                  OE_typ                  oe ,
                                  USER_typ                user,
                                  UG_typ                  ug ,
                                  TRNSEVNT_UPCON_FLAG_typ connflag ,
                                  ADMIN_PARAMS_rec_typ  * admin_params,
                                  ERR_STRUCT_rec_typ    * err);

extern  TRNSEVNT_FUNC_TYP   CTSTransactionEvent;/* actual function */

typedef TRNSEVNT_FUNC_TYP * TRNSEVNT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSLogEvent                                      *
 * Description   : RSS log event has occured                        *
 * Input         : rss_type - RSS type                              *
 *                 rss_name - RSS name, if available                *
 *                 handle   - To interception queue                 *
 *                 msgid    - Message code from message code file.  *
 *                 ...      - Message parameters list.              *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
/*
#ifdef MVS
#define CTSLogEvent     cloge
#endif
*/
typedef ESA_RC RSLOGEVT_FUNC_TYP (RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  const char             * msgid,
                                  ...);

extern  RSLOGEVT_FUNC_TYP   CTSLogEvent;       /* actual function */

typedef RSLOGEVT_FUNC_TYP * RSLOGEVT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSParamsModEvent                                *
 * Description   : Notify that RSS parameters have changed          *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                  admin_params                                    *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_PRMMOD_FUNC_TYP (RSS_typ           rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_PRMMOD_FUNC_TYP   CTSParamsModEvent;  

typedef RS_PRMMOD_FUNC_TYP * RS_PRMMOD_FUNC_PTR; 

/********************************************************************
 * Procedure Name : CTSUserRevokedEvent                             *
 * Description    : User was disabled (revoked)                     *
 * Input          : rss_type - Mandatory information.               *
 *                  rss_name - RSS name when available.             *
 *                             NULL if not available                *
 *                  handle   - initialization information           *
 *                             (e.g. queue file handle)             *
 *                  user name -                                     *
 *                  admin_params                                    *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RS_USDIS_FUNC_TYP (RSS_typ                 rss_type,
                                 RSS_typ                  rss_name,
                                 void                   * handle,
                                 USER_typ                 user,
                                 ADMIN_PARAMS_rec_typ   * admin_params);

extern  RS_USDIS_FUNC_TYP   CTSUserRevokedEvent; 

typedef RS_USDIS_FUNC_TYP * RS_USDIS_FUNC_PTR;    

/********************************************************************
 * Procedure Name : CTSPassModEvent                                 *
 * Description    : User's password was modified                    *
 * Input          : rss_type - Mandatory information.               *
 *                  rss_name - RSS name when available.             *
 *                             NULL if not available                *
 *                  user     - user name                            *
 *                  password - new password                         *
 *                  addinfo - RS-specific keywords                  *
 *                  admin_params                                    *
 * Input/Output   : CTSAMSG params                                  *
 *                  handle   - initialization information           *
 *                             (e.g. queue file handle)             *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RS_PWDMOD_FUNC_TYP (RSS_typ                 rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  USER_typ                 user,
                                  PASSWD_typ               passwd,
                                  ADDINFO_rec_typ        * addinfo,
                                  ADMIN_PARAMS_rec_typ   * admin_params);

extern  RS_PWDMOD_FUNC_TYP   CTSPassModEvent;   

typedef RS_PWDMOD_FUNC_TYP * RS_PWDMOD_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSUserEvent                                     *
 * Description   : User state changed - user was added, deleted     *
 *                 or updated.                                      *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 user name   -                                    *
 *                 action type - add/del/update                     *
 *                  admin_params                                    *
 * Output        :                                                  *
 * Input/Output  : CTSAMSG params                                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
typedef ESA_RC RS_USER_FUNC_TYP (RSS_typ                 rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                USER_typ                 user,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_params);

extern  RS_USER_FUNC_TYP   CTSUserEvent;    

typedef RS_USER_FUNC_TYP * RS_USER_FUNC_PTR; 

/********************************************************************
 * Procedure Name: CTSUGEvent                                       *
 * Description   : User group state changed - user group was added, *
 *                 deleted or updated.                              *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 user group -                                     *
 *                 action type - add/del/update                     *
 *                  admin_params                                    *
 * Output        :                                                  *
 * Input/Output  : CTSAMSG params                                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_UG_FUNC_TYP (RSS_typ                 rss_type,
                              RSS_typ                  rss_name,
                              void                   * handle,
                              UG_typ                   ug,
                              ACTION_typ               action,
                              ADMIN_PARAMS_rec_typ   * admin_params);

extern  RS_UG_FUNC_TYP   CTSUGEvent;    

typedef RS_UG_FUNC_TYP * RS_UG_FUNC_PTR; 


/********************************************************************
 * Procedure Name: CTSOEEvent                                       *
 * Description   : OE was added, deleted                            *
 *                 or updated.                                      *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 OE name   -                                      *
 *                 action type - add/del/update                     *
 *                  admin_params                                    *
 * Output        :                                                  *
 * Input/Output  : CTSAMSG params                                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_OE_FUNC_TYP   (RSS_typ                 rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                OE_typ                   oe,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_params);

extern  RS_OE_FUNC_TYP   CTSOEEvent;    

typedef RS_OE_FUNC_TYP * RS_OE_FUNC_PTR; 

/********************************************************************
 * Procedure Name: CTSRssStatusEvent                                *
 * Description   : RSS status was changed.                          *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 rss_status RSS status                            *
 *                  admin_params                                    *
 * Output        :                                                  *
 * Input/Output  : CTSAMSG params                                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RSSSTATUS_FUNC_TYP(RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  RSS_STATUS_typ         * rss_status,
                                  ADMIN_PARAMS_rec_typ   * admin_params);

extern  RSSSTATUS_FUNC_TYP CTSRssStatusEvent;    /* actual function */

typedef RSSSTATUS_FUNC_TYP * RSSSTATUS_FUNC__PTR;/* pointer to func */

/********************************************************************
 * Procedure Name: CTSConnEvent                                     *
 * Description   : User to User-Group connection state changed -    *
 *                 connection was added, deleted or updated.        *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 user group  -                                    *
 *                 user name   -                                    *
 *                 action type - (connect/disconnect/update)        *
 * Input/Output  : CTSAMSG params                                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RSU2UG_FUNC_TYP (RSS_typ                  rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                UG_typ                   ug,
                                USER_typ                 user,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSU2UG_FUNC_TYP   CTSConnEvent;    /* actual function */

typedef RSU2UG_FUNC_TYP * RSU2UG_FUNC_PTR; /* pointer to func */

/* ================================================================= */
/* ==                Obsolete USA-API functions                   == */
/* ================================================================= */
												 
/********************************************************************
 * Procedure Name: CTSGetConns                                      *
 * Description   : Get user-group to user connections               *
 * Input         : mode         - GET_ALL    - get all connections  *
 *                                     (all users of all groups)    *
 *                                GET_MANY_UGS - get connections of *
 *                                               supplied ugs       *
 *                                GET_MANY_USERS - get connections  *
 *                                                 of supplied users*
 *                                GET_MANY_CONNS - get connections  * 
 *                                                 of supplied pairs*
 *                                GET_FREE_HANDLE (see below)       *
 *                 max_conns    - # of elements in ugs,             *
 *                                users, obj_exist & addinfo        *
 *                                arrays                            *
 *                 admin_params -                                   *
 *                 num_ugs_in   - # of input ugs                    *
 *                 num_users_in - # of input users                  *
 *                 ugs_in       - array of num_ugs_in.              *
 *                                Caller fills with ugs requested   *
 *                                (if not GET_ALL);                 *
 *                 users_in     - array of num_users_in.            *
 *                                Caller fills with users requested.*
 * Output        : actual_num   - # of connections returned         *
 *                 have_more    - HAVE_MORE if more conns,          *
 *                                else NO_MORE                      *
 *                 u2ug_params  - details of each connection        *
 *                 objs_exist   - array of max_conns:               *
 *                                OBJ_EXIST if connection exists,   *
 *                                else OBJ_NOT_EXIST.               *
 *                 addinfo      - array of max_conns pointers,      *
 *                                one add.info per connection       *
 *                 err          - error indication, message, etc.   *
 *                 handle       - NULL on first call, filled by     *
 *                                callee,used to keep track.        *
 * Return Value  : ESA_RC                                           *
 * Side Effects  : The function may allocate memory for internal    *
 *                 usage and return pointer to it in *handle.       *
 *                 When function returns have_more==NO_MORE, it     *
 *                 will be called again in mode=GET_FREE_HANDLE.    *
 *                 the function should then free the memory. Such   *
 *                 a call will always be performed as the last call.*
 * Comments      : 1. Data is returned as triplets -                *
 *                    u2ug_params, add.info, obj_exist              *
 ********************************************************************/

typedef ESA_RC GTUG2UC_FUNC_TYP (GET_CONN_MODE       mode,
                              short                  max_conns,
                              short                * actual_num,
                              HAVE_MORE_typ        * have_more,
                              void                ** handle,
                              short                  num_ugs_in,
                              short                  num_users_in,
                              UG_typ               * ugs_in,
                              USER_typ             * users_in,
                              U2UG_PARAMS_rec_typ  * u2ug_params,
                              ADDINFO_rec_typ     ** addinfo,
                              OBJ_EXISTS_typ       * objs_exist,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  GTUG2UC_FUNC_TYP   CTSGetConns;      /* actual function */

typedef GTUG2UC_FUNC_TYP * GTUG2UC_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddUserToUG                                  *
 * Description    : Connect user to user group                      *
 * Input          : u2ug_data    - user and group data              *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC ADDU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  ADDU2UG_FUNC_TYP   CTSAddUserToUG;/* actual function */

typedef ADDU2UG_FUNC_TYP * ADDU2UG_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSDelUserFromUG                                *
 * Description    : Disconnect user from user group                 *
 * Input          : u2ug_data    - user and group data              *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC DELU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  DELU2UG_FUNC_TYP   CTSDelUserFromUG;  /* actual */

typedef DELU2UG_FUNC_TYP * DELU2UG_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdUserToUG                                  *
 * Description    : Update user to user group connection details    *
 * Input          : u2ug_data    - user and group data              *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDU2UG_FUNC_TYP   CTSUpdUserToUG;   /* actual function */

typedef UPDU2UG_FUNC_TYP * UPDU2UG_FUNC_PTR; /* pointer to func */



/********************************************************************
 * Procedure Name : CTSInterceptorInit                              * 
 * Description    : RSS functions initialization for interceptors.  *  
 * Input          :                                                 *
 *                  rss_typ  - Mandatory information.               *
 *                  rss_name - RSS name when available.             *
 *                             NULL if not available                *
 *                  handle   - NULL on first call, filled by callee,*
 *                             used by callee to store all the      *
 *                             initialization information.          *
 *                  intercept_typ - OFLI / ONLI                     *
 *                  admin_params                                    *
 * Output        : Time Range:                                      *
 *                  start_date                                      *
 *                  start_time The date and time of the             *
 *                             first entry that the interceptor     *
 *                             should start with.                   *
 *                  end_date                                        *
 *                  end_time   The date and time of the last entry. *
 *                             If fields are empty, then the last   *
 *                             entry is the last in the log or file.*
 *                                                                  *
 *                 EncHndl    - handle to encryption scheme         *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RSINIT_FUNC_TYP (RSS_typ                  rss_typ,
                                RSS_typ                  rss_name,
                                void                  ** handle,
                                void                  ** EncrHndl,
                                INTERCEPTOR_typ          intercept_typ,
                                TIME_RANGE_rec_typ     * time_range,
                                ADMIN_PARAMS_rec_typ   * admin_params,
                                int                      argc_prm,
                                char                  ** argv_prm);

extern  RSINIT_FUNC_TYP   CTSInterceptorInit; /* actual function */


/********************************************************************
 * Procedure Name : CTSInterceptorTerm                              *
 * Description    : RSS functions termination for the offline       *
 *                  interceptor.                                    *
 *                                                                  *
 * Input          : handle        - Free by callee,                 *
 *                  intercept_typ - OFLI / ONLI                     *
 *                  exit_status   - The interceptor's return code   *
 *                  Time Range:                                     *
 *                    start_date                                    *
 *                    start_time The date and time of the           *
 *                               first entry that the interceptor   *
 *                               should start with.                 *
 *                    end_date                                      *
 *                    end_time   The date and time of the last entry*
 *                               If fields are empty, then the last *
 *                              entry is the last in the log or file*
 *                  admin_params                                    *
 * Output         : None                                            *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RSTERM_FUNC_TYP (void                  ** handle,
                                INTERCEPTOR_typ          intercept_typ,
                                ESA_RC                   exit_status,
                                TIME_RANGE_rec_typ     * time_range,
                                ADMIN_PARAMS_rec_typ   * admin_params);

extern  RSTERM_FUNC_TYP   CTSInterceptorTerm; /* actual function */

typedef RSTERM_FUNC_TYP * RSTERM_FUNC_PTR;    /* pointer to func */

/********************************************************************
 * Procedure Name : CTSVersion                                      *
 * Description    : API version from API_VERSION                    *
 * Input          : None                                            *
 * Output         : version - API version - 4.0.0 etc.              *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC APIVERSION_FUNC_TYP (RSS_vers_typ  version);

extern  APIVERSION_FUNC_TYP   CTSVersion;    /* actual function */

typedef APIVERSION_FUNC_TYP * APIVERSION_FUNC_PTR;/*pointer to func */


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIOLDV__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIOLDV__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIOLDV_H_INCLUDED */
