/**********************************************************************
*
*   H Source      : apiuser.h
*   Description   : USA_API User processing functions
*   %full_filespec: apiuser.h#3:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIUSER_H_INCLUDED
#define APIUSER_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API USER          == */
/* == functions.                                                     == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: CTSGetUsers                                      *
 * Description   : Get users                                        *
 * Input         : mode          - GET_ALL,                         *
 *                                 GET_MANY - exact IDs specified   *
 *                                            for one or more       *
 *                                 GET_WILD (wildcards)             *
 *                                 GET_SUBTREE (containers)         *
 *                                 GET_FREE_HANDLE (see below)      *
 *                 oe            - container (if mode - GET_SUBTREE)*
 *                 max_users     - Number of users to be retrieved  *
 *                                 in each call. The same as # of   *
 *                                 elements in user_params,         *
 *                                 objs_exist and addinfo arrays    *
 *                 num_users_in  - # of elements in user_params_in  *
 *                 user_params_in- array of num_users_in, filled    *
 *                                 with IDs/masks requested.        *
 *                 admin_params                                     *
 * Output        : actual_num   - # of users returned in this call  *
 *                 have_more    - HAVE_MORE if more users           *
 *                                else NO_MORE                      *
 *                 objs_exist   - array of max_users:               *
 *                                OBJ_EXIST if user exists, else    *
 *                                OBJ_NOT_EXIST.                    *
 *                 user_params  - array of max_users:               *
 *                                callee fills with users returned  *
 *                 err          - Messages (Opt.)                   *
 * Input/Output  : addinfo      - array of max_users pointers:      *
 *                                add.info per user, Caller puts    *
 *                                requested keywords, callee returns*
 *                                actual add.info.                  *
 *                 handle       - NULL on first call, filled by     *
 *                                callee,used to keep track.        *
 * Return Value  : ESA_RC                                           *
 * Side Effects  : The function may allocate memory for internal    *
 *                 usage and return pointer to it in *handle.       *
 *                 When function returns have_more==NO_MORE, it     *
 *                 will be called again in mode=GET_FREE_HANDLE.    *
 *                 the function should then free the memory. Such   *
 *                 a call will always be performed as the last call.*
 ********************************************************************/

typedef ESA_RC GTUSERS_FUNC_TYP (GET_USER_MODE       mode,
                              OE_typ                 oe,
                              short                  max_users,
                              short                * actual_num,
                              HAVE_MORE_typ        * have_more,
                              void                ** handle,
                              short                  num_users_in,
                              USER_PARAMS_rec_typ  * user_params_in,
                              USER_PARAMS_rec_typ  * user_params,
                              ADDINFO_rec_typ     ** addinfo,
                              OBJ_EXISTS_typ       * objs_exist,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  GTUSERS_FUNC_TYP   CTSGetUsers;      /* actual function */

typedef GTUSERS_FUNC_TYP * GTUSERS_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddUser                                      *
 * Description    : Add a new user                                  *
 * Input          : user_params  - User data                        *
 *                  addinfo      - RSS-specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC ADDUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  ADDUSER_FUNC_TYP   CTSAddUser;       /* actual function */

typedef ADDUSER_FUNC_TYP * ADDUSER_FUNC_PTR; /* pointer to func */

/*******************************************************************
 * Procedure Name : CTSDelUser                                     *
 * Description    : Delete a user                                  *
 * Input          : user_params - user data                        *
 *                  addinfo     - RSS-specific keywords            *
 *                  admin_params                                   *
 * Output         : err         - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                         *
 *******************************************************************/

typedef ESA_RC DELUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  DELUSER_FUNC_TYP   CTSDelUser;       /* actual function */

typedef DELUSER_FUNC_TYP * DELUSER_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdUser                                      *
 * Description    : Update user details                             *
 * Input          : user_params - user data                         *
 *                  addinfo     - RSS_specific keywords, containing *
 *                                changed keywords only.            *
 *                  admin_params                                    *
 * Output         : err         - Messages (Opt.)                   *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDUSER_FUNC_TYP   CTSUpdUser;    /* actual function */

typedef UPDUSER_FUNC_TYP * UPDUSER_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRevokeUser                                   *
 * Description    : Revoke or restore a user                        *
 * Input          : user_params  - user data                        *
 *                  addinfo      - RSS-specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 * Comments       : Action (REVOKE or RESTORE) is in the            *
 *                  user_params structure                           *
 ********************************************************************/

typedef ESA_RC REVUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  REVUSER_FUNC_TYP   CTSRevokeUser;    /* actual function */

typedef REVUSER_FUNC_TYP * REVUSER_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdPassword                                  *
 * Description    : Update password and its parameters              *
 * Input          : user_params - user data                         *
 *                  addinfo     - RSS-specific keywords             *
 *                  admin_params                                    *
 * Output         : err         - Messages (Opt.)                   *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDPASS_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDPASS_FUNC_TYP   CTSUpdPassword;   /* actual function */

typedef UPDPASS_FUNC_TYP * UPDPASS_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSMoveUser                                     *
 * Description    : Move user to different parent container         *
 * Input          : user_params   - User data                       *
 *                  new_parent_oe - New parent container            *
 *                  new_user      - Different from original name in *
 *                                  RSSs where the id contains the  *
 *                                  parent container.               *
 *                  addinfo       - RSS specific keywords           *
 *                  admin_params                                    *
 * Output         : err           - Messages (Opt.)                 *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC MVUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                OE_typ                 new_parent_oe,
                                USER_typ               new_user,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  MVUSER_FUNC_TYP   CTSMoveUser;       /* actual function */

typedef MVUSER_FUNC_TYP * MVUSER_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRenameUser                                   *
 * Description    : Rename an existing user                         *
 * Input          : user_params - old user identification           *
 *                  new_user    - new id                            *
 *                  addinfo     - RSS-specific keywords             *
 *                  admin_params                                    *
 * Output         : err         - Messages (Opt.)                   *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RNUSER_FUNC_TYP(USER_PARAMS_rec_typ  * user_params,
                               USER_typ               new_user,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  RNUSER_FUNC_TYP   CTSRenameUser;   /* actual function*/

typedef RNUSER_FUNC_TYP * RNUSER_FUNC_PTR; /* pointer to func*/

/********************************************************************
 * Procedure Name: CTSRSSVerifyPassword                             *
 * Description   : Verify password                                  *
 * Input         : admin        - administrator name                *
 *                 admin_passwd - administrator's password          *
 *                 admin_params                                     *
 * Output        : None                                             *
 * Return Value  : ESA_OK     upon success                          *
 *                 ESA_ERR  on any fail situation                   *
 ********************************************************************/

typedef ESA_RC VERIFY_PWD_FUNC_TYP (
								  USER_typ               admin,
                                  PASSWD_typ             admin_passwd,
                                  ADMIN_PARAMS_rec_typ * admin_params);

extern  VERIFY_PWD_FUNC_TYP   CTSVerifyPassword;

typedef VERIFY_PWD_FUNC_TYP * VERIFY_PWD_FUNC_PTR; 

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIUSER__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIUSER__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIUSER_H_INCLUDED */
