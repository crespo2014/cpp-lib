/**********************************************************************
*
*   H Source      : apievnt.h
*   Description   : Agent services for interceptors
*   %full_filespec: apievnt.h#3:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIEVNT_H_INCLUDED
#define APIEVNT_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains SA-Agent interceptor services.       == */
/* ==                                                                == */
/* == The functions enable an interceptor to  notify the agent that  == */
/* == a change in a security object occured. The agent will then send== */
/* == the new details of the object to the ESS.                      == */
/* ==                                                                == */
/* == Function addresses are not supplied, use LINK or DLL.          == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name : CTSInterceptorInitEx                            * 
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

typedef ESA_RC RSINIT_X_FUNC_TYP(char                  * ProgName,
                                 char                  * ProgMain, 
                                 RSS_typ                 rss_typ,
                                 RSS_typ                 rss_name,
                                 void                 ** handle,
                                 void                 ** EncrHndl,
                                 INTERCEPTOR_typ         intercept_typ,
                                 TIME_RANGE_rec_typ    * time_range,
                                 ADMIN_PARAMS_rec_typ  * admin_params,
                                 int                      argc_prm,
                                 char                 ** argv_prm);

extern  RSINIT_X_FUNC_TYP   CTSInterceptorInit_CS; /* actual function */

typedef RSINIT_X_FUNC_TYP * RSINIT_X_FUNC_PTR;    /* pointer to func */

/********************************************************************
 * Procedure Name : CTSInterceptorTermEx                            *
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

typedef ESA_RC RSTERM_X_FUNC_TYP (char                 * ProgName,
                                 char                  * ProgMain, 
                                 void                 ** handle,
                                 INTERCEPTOR_typ         intercept_typ,
                                 ESA_RC                  exit_status,
                                 TIME_RANGE_rec_typ   * time_range,
                                 ADMIN_PARAMS_rec_typ * admin_params);

extern  RSTERM_X_FUNC_TYP   CTSInterceptorTerm_CS; /* actual function */

typedef RSTERM_X_FUNC_TYP * RSTERM_X_FUNC_PTR;    /* pointer to func */

/********************************************************************
 * Procedure Name: CTSForceIntercept                                *
 * Description   : This function tells an interceptor to send       *
 *                 interception notification to the agent.          *
 *                 A USA-API should contain such a function if an   *
 *                 interceptor other than the standard offline      *
 *                 interceptor is used.                             *
 *                 Function is called by the agent when the object  *
 *                 is unreachable when its details should be sent   *
 *                 to the ESS.                                      *
 * Input         : intercept_rec    - interception details          *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 *                                                                  *
 *  This routine will write a checksum of zero to the OFLI          *
 *  transactions file. And that will cause the next run of the      *
 *                                                                  *
 *  Function created for Unreachables for V400                      *
 *                                                                  *
 ********************************************************************/

 typedef ESA_RC FORCEINTRCPT_FUNC_TYP  
                             (INTERCEPT_rec_ptr      intercept_rec, 
                              ADMIN_PARAMS_rec_typ  * admin_params);


 extern  FORCEINTRCPT_FUNC_TYP   CTSForceIntercept_CS;     /* actual function */

 typedef FORCEINTRCPT_FUNC_TYP * FORCEINTRCPT_FUNC_PTR; /* pointer to func */

 
/********************************************************************
 * Procedure Name: CTSLogEventEx                                    *
 * Description   : Send message to ESS, to be displayed immediately.*
 *                 Messages from msg_print will be displayed only   *
 *                 after the transaction finishes, but this function*
 *                 causes messages to be shown immediately in the   *
 *                 ESS log                                          *
 * Input         : rss_type     - Mandatory information.            * 
 *                 rss_name     - RSS name when available.          * 
 *                                NULL if not available             *
 *                 handle       - initialization information        *
 *                                (e.g. queue file handle)          * 
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator    - interceptor identification        *
 *                 msgid        - Message code from codes file.     *
 *                 ...          - Message parameters list.          *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
#ifdef MVS
#define CTSLogEventEx   clogex
#endif 


typedef ESA_RC RSLOGEVT_X_FUNC_TYP (RSS_typ           rss_type,
                             RSS_typ                  rss_name,
                             void                   * handle,
                             INTERCEPTOR_typ          interceptor_type,
                             INITIATOR_typ            initiator,
                             const char             * msgid,
                                    ...);

extern  RSLOGEVT_X_FUNC_TYP   CTSLogEvent_CS;   

typedef RSLOGEVT_X_FUNC_TYP * RSLOGEVT_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSParamsModEventEx                              *
 * Description   : Notify that RSS parameters have changed          *
 * Input         : rss_type     - Mandatory information.            *
 *                 rss_name     - RSS name when available.          *
 *                                NULL if not available             *
 *                 handle       - initialization information        *
 *                                (e.g. queue file handle)          *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_PRMMOD_X_FUNC_TYP (void          * DiagHndl,
									 RSS_typ         rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_PRMMOD_X_FUNC_TYP   CTSParamsModEvent_CS; 

typedef RS_PRMMOD_X_FUNC_TYP * RS_PRMMOD_X_FUNC_PTR;

/********************************************************************
 * Procedure Name : CTSUserRevokedEventEx                           *
 * Description    : User was disabled (revoked)                     *
 * Input          : rss_type     - Mandatory information.           *
 *                  rss_name     - RSS name when available.         *
 *                                 NULL if not available            *
 *                  handle       - initialization information       *
 *                                 (e.g. queue file handle)         *
 *                  user         - user id                          *
 *                  interceptor_type - indicates standard/custom,   *
 *                                     online/offline               *
 *                  initiator        - interceptor identification   *
 *                  admin_params                                    *
 * Output         : None                                            *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RS_USDIS_X_FUNC_TYP (void           * DiagHndl,
									RSS_typ          rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             USER_typ                user,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_USDIS_X_FUNC_TYP   CTSUserRevokedEvent_CS; 

typedef RS_USDIS_X_FUNC_TYP * RS_USDIS_X_FUNC_PTR;    

/********************************************************************
 * Procedure Name : CTSPassModEventEx                               *
 * Description    : User's password was modified                    *
 * Input          : rss_type         - Mandatory information.       *
 *                  rss_name         - RSS name when available.     *
 *                                     NULL if not available        *
 *                  handle           - initialization information   *
 *                                     (e.g. queue file handle)     *
 *                  user             - user name                    *
 *                  password         - new password                 *
 *                  passwd_life      -                              *
 *                  interceptor_type - indicates standard/custom,   *
 *                                     online/offline               *
 *                  initiator        - interceptor identification   *
 *                  addinfo          - RSS-specific keywords        *
 *                  admin_params                                    *
 * Output         : None                                            *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RS_PWDMOD_X_FUNC_TYP (void          * DiagHndl,
									 RSS_typ         rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             USER_typ                user,
                             PASSWD_typ              passwd,
                             PASSWD_LIFE_typ         passwd_life,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADDINFO_rec_typ       * addinfo,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_PWDMOD_X_FUNC_TYP   CTSPassModEvent_CS;   

typedef RS_PWDMOD_X_FUNC_TYP * RS_PWDMOD_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSUserEventEx                                   *
 * Description   : User state changed - user was added, deleted     *
 *                 or updated.                                      *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 user name   -                                    *
 *                 action type - add/del/update                     *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
typedef ESA_RC RS_USER_X_FUNC_TYP (void            * DiagHndl,
								   RSS_typ           rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             USER_typ                user,
                             ACTION_typ              action,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_USER_X_FUNC_TYP   CTSUserEvent_CS;    

typedef RS_USER_X_FUNC_TYP * RS_USER_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSRenameUserEventEx                             *
 * Description   : User renamed                                     *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 old user name   -                                *
 *                 new user name   -                                *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_RNUSER_FUNC_TYP(void            * DiagHndl,
								  RSS_typ           rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             USER_typ               old_user,
                             USER_typ               new_user,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_RNUSER_FUNC_TYP   CTSRenameUserEvent_CS; /* actual function */

typedef RS_RNUSER_FUNC_TYP * RS_RNUSER_FUNC_PTR; /* pointer to func */
                                           
/********************************************************************
 * Procedure Name: CTSMoveUserEventEx                               *
 * Description   : User moved                                       *
 * Input         : rss_type      - Mandatory information.           *
 *                 rss_name      - RSS name when available.         *
 *                                 NULL if not available            *
 *                 handle        - initialization information       *
 *                                 (e.g. queue file handle)         *
 *                 user          - user id                          *
 *                 resulted_user - new id, if changed by move       *
 *                 old_parent_oe - old container id                 *
 *                 new parent oe - new container id                 *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_MVUSER_FUNC_TYP(void            * DiagHndl,
								  RSS_typ           rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             USER_typ               user,
                             USER_typ               resulted_user,
                             OE_typ                 old_parent_oe,
                             OE_typ                 new_parent_oe,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_MVUSER_FUNC_TYP   CTSMoveUserEvent_CS;    /* actual function */

typedef RS_MVUSER_FUNC_TYP * RS_MVUSER_FUNC_PTR; /* pointer to func */
                                           
/********************************************************************
 * Procedure Name: CTSUGEventEx                                     *
 * Description   : User group state changed - user group was added, *
 *                 deleted or updated.                              *
 * Input         : rss_type    - Mandatory information.             *
 *                 rss_name    - RSS name when available.           *
 *                               NULL if not available              *
 *                 handle      - initialization information         *
 *                               (e.g. queue file handle)           *
 *                 ug          - group id                           *
 *                 action type - add/del/update                     *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_UG_X_FUNC_TYP (void               * DiagHndl,
								 RSS_typ              rss_type,
                              RSS_typ                 rss_name,
                              void                  * handle,
                              UG_typ                  ug,
                              ACTION_typ              action,
                              INTERCEPTOR_typ         interceptor_type,
                              INITIATOR_typ           initiator,
                              ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_UG_X_FUNC_TYP   CTSUGEvent_CS;    

typedef RS_UG_X_FUNC_TYP * RS_UG_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSRenameUGEventEx                               *
 * Description   : User group renamed                               *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 old_ug   - old user-group id                     *
 *                 new_ug   - new id                                *
 *                 interceptor_type - indicates standard/custom,    *
 *                                     online/offline               *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_RNUG_FUNC_TYP (void             * DiagHndl,
								 RSS_typ            rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             UG_typ                 old_ug,
                             UG_typ                 new_ug,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_RNUG_FUNC_TYP   CTSRenameUGEvent_CS; 

typedef RS_RNUG_FUNC_TYP * RS_RNUG_FUNC_PTR; 

/********************************************************************
 * Procedure Name: CTSMoveUGEventEx                                 *
 * Description   : User group moved                                 *
 * Input         : rss_type      - Mandatory information.           *
 *                 rss_name      - RSS name when available.         *
 *                                 NULL if not available            *
 *                 handle        - initialization information       *
 *                                (e.g. queue file handle)          *
 *                 ug            - old group id                     *
 *                 resulted_ug   - new id, if changed by move       *
 *                 old_parent_oe - old container id                 *
 *                 new_parent_oe - new container id                 *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_MVUG_FUNC_TYP (void             * DiagHndl,
								 RSS_typ            rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             UG_typ                 ug,
                             UG_typ                 resulted_ug,
                             OE_typ                 old_parent_oe,
                             OE_typ                 new_parent_oe,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_MVUG_FUNC_TYP   CTSMoveUGEvent_CS;    /* actual function */

typedef RS_MVUG_FUNC_TYP * RS_MVUG_FUNC_PTR;    /* pointer to func */

/********************************************************************
 * Procedure Name: CTSConnectionEventEx                             *
 * Description   : User to User-Group / Group to Group              *
 *                 connection state changed -                       *
 *                 connection was added, deleted or updated.        *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                  cnn_class             - U2UG or G2G             *
 *                  cnn_remote            - flag local or remote    *
 *                                          if remote - which       *
 *                  containing_object     - top-level object id     *
 *                  contained_object      - second-level id         *
 *                  new_object_name       - for move/rename         *
 *                  old_parent_oe         - container id            *
 *                  new_parent_oe         - for move                *
 *                  remote_rss_key        - for remote              *
 *                  remote_rss_type       - for remote              *
 *                  action type - (connect/disconnect/update)       *
 *                  interceptor_type - indicates standard/custom,   *
 *                                     online/offline               *
 *                  initiator        - interceptor identification   *
 *                  admin_params                                    *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_CONN_X_FUNC_TYP (void            * DiagHndl,
								   RSS_typ           rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             CNN_CLASS_typ           cnn_class,
                             CNN_REMOTE_typ          cnn_remote,
                             CNN_OBJ_typ             containing_object,
                             CNN_OBJ_typ             contained_object,
                             RSS_KEY_typ             remote_rss_key,
                             RSS_typ                 remote_rss_type,
                             ACTION_typ              action,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_CONN_X_FUNC_TYP   CTSConnectionEvent_CS;

typedef RS_CONN_X_FUNC_TYP * RS_CONN_X_FUNC_PTR;  

/********************************************************************
 * Procedure Name: CTSOEEventEx                                     *
 * Description   : OE was added, deleted                            *
 *                 or updated.                                      *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 OE       - container id                          *
 *                 action type - add/del/update                     *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_OE_X_FUNC_TYP (void               * DiagHndl,
								 RSS_typ              rss_type,
                              RSS_typ                 rss_name,
                              void                  * handle,
                              OE_typ                  oe,
                              ACTION_typ              action,
                              INTERCEPTOR_typ         interceptor_type,
                              INITIATOR_typ           initiator,
                              ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_OE_X_FUNC_TYP   CTSOEEvent_CS;    

typedef RS_OE_X_FUNC_TYP * RS_OE_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSMoveOEEventEx                                 *
 * Description   : OE moved                                         *
 * Input         : rss_type    - Mandatory information.             *
 *                 rss_name    - RSS name when available.           *
 *                               NULL if not available              *
 *                 handle      - initialization information         *
 *                               (e.g. queue file handle)           *
 *                 oe          - container                          *
 *                 resulted_oe - new id, if changed by move         *
 *                 old_parent_oe - old container id                 *
 *                 new_parent_oe - new container id                 *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_MVOE_FUNC_TYP (void             * DiagHndl,
								 RSS_typ            rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             OE_typ                 oe,
                             OE_typ                 resulted_oe,
                             OE_typ                 old_parent_oe,
                             OE_typ                 new_parent_oe,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_MVOE_FUNC_TYP   CTSMoveOEEvent_CS; 

typedef RS_MVOE_FUNC_TYP * RS_MVOE_FUNC_PTR; 

/********************************************************************
 * Procedure Name: CTSRenameOEEventEx                               *
 * Description   : OE moved                                         *
 * Input         : rss_type    - Mandatory information.             *
 *                 rss_name    - RSS name when available.           *
 *                               NULL if not available              *
 *                 handle      - initialization information         *
 *                               (e.g. queue file handle)           *
 *                 oe          - container                          *
 *                 new_oe      - new oe                             *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_RNOE_FUNC_TYP (void             * DiagHndl,
								 RSS_typ            rss_type,
                             RSS_typ                rss_name,
                             void                 * handle,
                             OE_typ                 oe,
                             OE_typ                 new_oe,
                             INTERCEPTOR_typ        interceptor_type,
                             INITIATOR_typ          initiator,
                             ADMIN_PARAMS_rec_typ * admin_params);

extern  RS_RNOE_FUNC_TYP   CTSRenameOEEventEx; 

typedef RS_RNOE_FUNC_TYP * RS_RNOE_FUNC_PTR; 


/********************************************************************
 * Procedure Name: CTSRssStatusEventEx                              *
 * Description   : RSS status was changed.                          *
 * Input         : rss_type     - Mandatory information.            *
 *                 rss_name     - RSS name when available.          *
 *                                NULL if not available             *
 *                 handle       - initialization information        *
 *                                (e.g. queue file handle)          *
 *                 rss_status   - RSS status                        *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RSSSTATUS_X_FUNC_TYP (void          * DiagHndl,
									 RSS_typ         rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             RSS_STATUS_typ        * rss_status,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RSSSTATUS_X_FUNC_TYP CTSRssStatusEvent_CS;  

typedef RSSSTATUS_X_FUNC_TYP * RSSSTATUS_X_FUNC_PTR;

/********************************************************************
 * Procedure Name: CTSResEventEx                                    *
 * Description   : Resource state changed - was added, deleted      *
 *                 or updated.                                      *
 * Input         : rss_type    - Mandatory information.             *
 *                 rss_name    - RSS name when available.           *
 *                              NULL if not available               *
 *                 handle      - initialization information         *
 *                               (e.g. queue file handle)           *
 *                 res_name    - resource name                      *
 *                 res_type    - resource type                      *
 *                 full_res    - flag with/without ACL              *
 *                 parent_oe   - container id                       *
 *                 action type - add/del/update                     *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_RES_FUNC_TYP (void               * DiagHndl,
								RSS_typ              rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             RESOURCE_typ            res_name,
                             RESTYPE_typ             res_type,
                             RES_ACTION_typ          full_res,
                             OE_typ                  parent_oe,
                             ACTION_typ              action,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_RES_FUNC_TYP   CTSResEvent_CS;    

typedef RS_RES_FUNC_TYP * RS_RES_FUNC_PTR; 

/********************************************************************
 * Procedure Name: CTSRenameResEventEx                              *
 * Description   : Resourse renamed                                 *
 * Input         : rss_type - Mandatory information.                *
 *                 rss_name - RSS name when available.              *
 *                            NULL if not available                 *
 *                 handle   - initialization information            *
 *                            (e.g. queue file handle)              *
 *                 old_res_name   -  old resource id                *
 *                 new_res_name   -  new resource id                *
 *                 res_type       - resource type                   *
 *                 full_res       - flag with/without ACL           *
 *                 parent_oe      - container id                    *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_RNRES_FUNC_TYP (void             * DiagHndl,
								  RSS_typ            rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             RESOURCE_typ            old_res_name,
                             RESOURCE_typ            new_res_name,
                             RESTYPE_typ             res_type,
                             RES_ACTION_typ          full_res,
                             OE_typ                  parent_oe,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_RNRES_FUNC_TYP   CTSRenameResEvent_CS;

typedef RS_RNRES_FUNC_TYP * RS_RNRES_FUNC_PTR; 
                                           
/********************************************************************
 * Procedure Name: CTSMoveResEventEx                                *
 * Description   : Resource moved                                   *
 * Input         : rss_type      - Mandatory information.           *
 *                 rss_name      - RSS name when available.         *
 *                                 NULL if not available            *
 *                 handle        - initialization information       *
 *                                 (e.g. queue file handle)         *
 *                 res_name      - resource name                    *
 *                 resulted_res  - new id, if changed by move       *
 *                 res_type      - resource type                    *
 *                 old parent_oe - old container id                 *
 *                 new_parent_oe - new container id                 *
 *                 full_res      - flag with/without ACL            *
 *                 interceptor_type - indicates standard/custom,    *
 *                                    online/offline                *
 *                 initiator        - interceptor identification    *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RS_MVRES_FUNC_TYP (void             * DiagHndl,
								  RSS_typ            rss_type,
                             RSS_typ                 rss_name,
                             void                  * handle,
                             RESOURCE_typ            res_name,
                             RESOURCE_typ            resulted_res,
                             RESTYPE_typ             res_type,
                             OE_typ                  old_parent_oe,
                             OE_typ                  new_parent_oe,
                             RES_ACTION_typ          full_res,
                             INTERCEPTOR_typ         interceptor_type,
                             INITIATOR_typ           initiator,
                             ADMIN_PARAMS_rec_typ  * admin_params);

extern  RS_MVRES_FUNC_TYP   CTSMoveResEvent_CS;  

typedef RS_MVRES_FUNC_TYP * RS_MVRES_FUNC_PTR; 


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIEVNT__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIEVNT__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIEVNT_H_INCLUDED */
