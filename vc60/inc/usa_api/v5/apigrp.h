/**********************************************************************
*
*   H Source      : apigrp.h
*   Description   : ESA-API interface
*   %full_filespec: apigrp.h#2:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIGRP_H_INCLUDED
#define APIGRP_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API USER-GROUP    == */
/* == functions.                                                     == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: CTSGetUGs                                        *
 * Description   : Get user groups                                  *
 * Input         : mode         - GET_ALL,                          *
 *                                GET_MANY,                         *
 *                                GET_WILD (not implemented)        *
 *                                GET_SUBTREE (containers)          *
 *                                GET_FREE_HANDLE (see below)       *
 *                 oe             container (if mode - GET_SUBTREE) *
 *                 max_ugs      - Number of groups to retrieve in   *
 *                                each call. The same as the # of   *
 *                                elements in ug_params & addinfo   *
 *                                arrays.                           *
 *                 num_ugs_in   - # of elements in ug_params_in.    *
 *                 ug_params_in - array of num_ugs_in, filled with  *
 *                                ugs requested.                    *
 *                 admin_params -                                   *
 * Output        : actual_num   - # of ugs returned.                *
 *                 have_more    - HAVE_MORE if more ugs,            *
 *                                else NO_MORE.                     *
 *                 err          - error indication, message, etc.   *
 *                 objs_exist   - array of max_ugs:                 *
 *                                OBJ_EXIST if ug exists, else      *
 *                                OBJ_NOT_EXIST.                    *
 *                 ug_params    - array of max_ugs:                 *
 *                                callee fills with groups returned.*
 * Input/Output  : addinfo      - array of max_users pointers:      *
 *                                add.info per group, Caller puts   *
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

typedef ESA_RC GETUGS_FUNC_TYP (GET_GROUP_MODE         mode,
                                OE_typ                 oe,
                                short                  max_ugs,
                                short                * actual_num,
                                HAVE_MORE_typ        * have_more,
                                void                ** handle,
                                short                  num_ugs_in,
                                UG_PARAMS_rec_typ    * ug_params_in,
                                UG_PARAMS_rec_typ    * ug_params,
                                ADDINFO_rec_typ     ** addinfo,
                                OBJ_EXISTS_typ       * objs_exist,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  GETUGS_FUNC_TYP   CTSGetUGs;       /* actual function */

typedef GETUGS_FUNC_TYP * GETUGS_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddUG                                        *
 * Description    : Add a user group                                *
 * Input          : ug_params  - user group data                    *
 *                  addinfo    - RSS_specific keywords              *
 *                  admin_params                                    *
 * Output         : err        - Messages (Opt.)                    *
 * Return Value   : ESA_RC                                          *
 * Comments       : No users are initally connected to the group.   *
 ********************************************************************/

typedef ESA_RC ADDUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  ADDUG_FUNC_TYP   CTSAddUG; /* actual function */

typedef ADDUG_FUNC_TYP * ADDUG_FUNC_PTR;  /* pointer to func */

/********************************************************************
 * Procedure Name : CTSDelUG                                        *
 * Description    : Delete a user group                             *
 * Input          : ug_params - user group data                     *
 *                  addinfo   - RSS_specific keywords               *
 *                  admin_params                                    *
 * Output         : err       - Messages (Opt.)                     *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC DELUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  DELUG_FUNC_TYP   CTSDelUG; /* actual function */

typedef DELUG_FUNC_TYP * DELUG_FUNC_PTR;  /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdUG                                        *
 * Description    : Update user group details                       *
 * Input          : ug_params - user group data                     *
 *                  addinfo   - RSS_specific keywords               *
 *                  admin_params                                    *
 * Output         : err       - Messages (Opt.)                     *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  UPDUG_FUNC_TYP   CTSUpdUG; /* actual function */

typedef UPDUG_FUNC_TYP * UPDUG_FUNC_PTR;     /* pointer to func */

/********************************************************************
 * Procedure Name : CTSMoveUG                                       *
 * Description    : Move a user group                               *
 * Input          : ug_params     - user group data                 * 
 *                  new_parent_oe - moved to                        *
 *                  new_group     - Different from original name in *
 *                                  RSSs where the id contains the  *
 *                                  parent container.               *
 *                  addinfo       - RSS_specific keywords           *
 *                  admin_params                                    *
 * Output         : err - Messages (Opt.)                           *
 * Return Value   : ESA_RC                                          *
 * Comments       : No users are initally connected to the group.   *
 ********************************************************************/

typedef ESA_RC MVUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                              OE_typ                 new_parent_oe,
                              UG_typ                 new_group,
                              ADDINFO_rec_typ      * addinfo,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  MVUG_FUNC_TYP   CTSMoveUG; /* actual function */

typedef MVUG_FUNC_TYP * MVUG_FUNC_PTR;  /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRenameUG                                     *
 * Description    : Rename a user group                             *
 * Input          : ug_params   - user group data                   *
 *                  new_group   - new group id                      *
 *                  addinfo     - RSS_specific keywords             *
 *                  admin_params                                    *
 * Output         : err         - Messages (Opt.)                   *
 * Return Value   : ESA_RC                                          *
 * Comments       : No users are initally connected to the group.   *
 ********************************************************************/

typedef ESA_RC RNUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                              UG_typ                 new_group,
                              ADDINFO_rec_typ      * addinfo,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  RNUG_FUNC_TYP   CTSRenameUG; /* actual function */

typedef RNUG_FUNC_TYP * RNUG_FUNC_PTR;  /* pointer to func */


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIGRP__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIGRP__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIGRP_H_INCLUDED */
