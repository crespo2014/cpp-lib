/**********************************************************************
*
*   H Source      : apires.h
*   Description   : USA_API REsource and ACE processing functions
*   %full_filespec: apires.h#2:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIRES_H_INCLUDED
#define APIRES_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API RESOURCE      == */
/* == and ACE functions.                                             == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: CTSGetRes                                        *
 * Description   : Get resource RSS info                            *
 * Input         : mode          - GET_FREE_HANDLE, otherwise ignore*
 *                 max_ress      - # of elements in res_params &    *
 *                                 addinfo_out arrays               *
 *                 admin_params  -                                  *
 * Output        : actual_num    - # of resources returned          *
 *                 have_more     - HAVE_MORE if more resources      *
 *                 res_params    - Returned resources               *
 *                 err           - error indication, message, etc.  *
 * Input/Output  : addinfo       - array of max_ress pointers:      *
 *                                 add.info per resource, caller    *
 *                                 puts requested keywords, callee  *
 *                                 returns actual add.info, per     *
 *                                 resource.                        *
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
 *                    resource, add.info, objs_exist                *
 ********************************************************************/

typedef ESA_RC GETRES_FUNC_TYP (GET_RESOURCE_MODE      mode,
                                OE_typ                 oe,
                                short                  max_ress,
                                short                * actual_num,
                                HAVE_MORE_typ        * have_more,
                                void                ** handle,
                                RES_PARAMS_rec_typ   * res_params_in,
                                ADDINFO_rec_typ      * addinfo_in,
                                RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ     ** addinfo_out,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  GETRES_FUNC_TYP   CTSGetRes;       /* actual function */

typedef GETRES_FUNC_TYP * GETRES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSGetResACL                                     *
 * Description   : Get one resource's ACL                           *
 * Input         : mode         - GET_FREE_HANDLE, otherwise ignore *
 *                 max_aces     - # of ACEs                         *
 *                 admin_params -                                   *
 * Output        : actual_num   - # of ACEs returned                *
 *                 have_more    - HAVE_MORE if more conns,          *
 *                                else NO_MORE                      *
 *                 ace_params   - contains: user, group, attributes *
 *                 err          - error indication, message, etc.   *
 * Input/Output  : addinfo      - array of max_aces pointers        *
 *                                add.info per ACE, caller puts     *
 *                                requested keywords,               *
 *                                callee returns actual add.info,   *
 *                                per ACE                           *
 *                 handle       - NULL on first call, filled by     *
 *                                callee,used to keep track.        *
 * Return Value  : ESA_RC                                           *
 * Side Effects  : The function may allocate memory for internal    *
 *                 usage and return pointer to it in *handle.       *
 *                 When function returns have_more==NO_MORE, it     *
 *                 will be called again in mode=GET_FREE_HANDLE.    *
 *                 the function should then free the memory. Such   *
 *                 a call will always be performed as the last call.*
 * Comments      : 1. Data is returned as pairs -                   *
 *                    ACE, addinfo (=permissions)                   *
 ********************************************************************/

typedef ESA_RC GTRSACL_FUNC_TYP (GET_ACL_MODE            mode,
                                 short                   max_aces,
                                 short                 * actual_num,
                                 HAVE_MORE_typ         * have_more,
                                 void                 ** handle,
                                 RES_PARAMS_rec_typ    * res_params,
                                 ACE_rec_typ           * ace_params,
                                 ADDINFO_rec_typ      ** addinfo,
                                 ADMIN_PARAMS_rec_typ  * admin_params,
                                 ERR_STRUCT_rec_typ    * err);

extern  GTRSACL_FUNC_TYP   CTSGetResACL;     /* actual function */

typedef GTRSACL_FUNC_TYP * GTRSACL_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddACE                                       *
 * Description    : Connect user/ug to a resource                   *
 * Input          : res_params      - Resource data                 *
 *                  new_ace         - New ACE data                  *
 *                  new ACE addinfo - RSS-specific keywords that    *
 *                                    define the permissions.       *
 *                  ace_pos         - position of new ACE. abs/rel  *
 *                  rel_ace         - position relative to existing *
 *                                    ACE                           *
 *                  rel_addinfo     - relative ACE addinfo          *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 * Comments       : rel_ace and rel_addinfo are meaningful only     *
 *                  if position is BEFORE/AFTER                     *
 ********************************************************************/

typedef ESA_RC ADDACE_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ACE_rec_typ          * new_ace,
                                ADDINFO_rec_typ      * new_addinfo,
                                ACE_POS_typ            ace_pos,
                                ACE_rec_typ          * rel_ace,
                                ADDINFO_rec_typ      * rel_addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  ADDACE_FUNC_TYP   CTSAddACE;       /* actual function */

typedef ADDACE_FUNC_TYP * ADDACE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSDelACE                                       *
 * Description    : Disconnect user/group from resource             *
 * Input          : res_params      - Resource data                 *
 *                  ace             - ACE data                      *
 *                  addinfo         - ACE RSS_specific keywords     *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 * Comments       : 1. addinfo contains the current permissions.    *
 ********************************************************************/

typedef ESA_RC DELACE_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ACE_rec_typ          * ace,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  DELACE_FUNC_TYP   CTSDelACE;       /* actual function */

typedef DELACE_FUNC_TYP * DELACE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdACE                                       *
 * Description    : Update user/group to resource connection        *
 * Input          : res_params      - Resource data                 *
 *                  new_ace         - new ace data                  *
 *                  new_addinfo     - RSS-specific keywords,        *
 *                                    includes the permissions      *
 *                  old_ace         - old ACE data                  *
 *                  old_addinfo     - old ACE RSS-specific keywords *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 * Comments       : 1. addinfo structs contain the permissions.     *
 ********************************************************************/

typedef ESA_RC UPDACE_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ACE_rec_typ          * new_ace,
                                ADDINFO_rec_typ      * new_addinfo,
                                ACE_rec_typ          * old_ace,
                                ADDINFO_rec_typ      * old_addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  UPDACE_FUNC_TYP   CTSUpdACE;       /* actual function */

typedef UPDACE_FUNC_TYP * UPDACE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSMoveRes                                      *
 * Description    : Change resource's parent container              * 
 * Input          : res_params    - Resource data                   *
 *                  new_parent_oe - parent container data           *
 *                  new_res       - Different from original name in *
 *                                  RSSs where the id contains the  *
 *                                  parent container.               *
 *                  addinfo       - RSS_specific keywords           *
 *                  admin_params                                    *
 * Output         : err           - Messages (Opt.)                 *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC MVRES_FUNC_TYP(RES_PARAMS_rec_typ   * res_params,
                              OE_typ                 new_parent_oe,
                              RESOURCE_typ           new_res,
                              ADDINFO_rec_typ      * addinfo,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  MVRES_FUNC_TYP   CTSMoveRes;       /* actual function */

typedef MVRES_FUNC_TYP * MVRES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSRenameRes                                    *
 * Description    : rename an existing resource                     *  
 * Input          : res_params      - Resource data                 *
 *                  new_resource    - new resource data             *
 *                  addinfo         - RSS_specific keywords         *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC RNRES_FUNC_TYP(RES_PARAMS_rec_typ   * res_params,
                              RESOURCE_typ           new_resource,
                              ADDINFO_rec_typ      * addinfo,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  RNRES_FUNC_TYP   CTSRenameRes;       /* actual function */

typedef RNRES_FUNC_TYP * RNRES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddRes                                       *
 * Description    : Creates a resource with no ACL info             *
 * Input          : res_params      - Resource data                 *
 *                  addinfo         - RSS_specific keywords         *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC ADDRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  ADDRES_FUNC_TYP   CTSAddRes;       /* actual function */

typedef ADDRES_FUNC_TYP * ADDRES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSDelRes                                       *
 * Description    : Deletes a resource with its ACL info            *
 * Input          : res_params      - Resource data                 *
 *                  addinfo         - RSS_specific keywords         *
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC DELRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  DELRES_FUNC_TYP   CTSDelRes;       /* actual function */

typedef DELRES_FUNC_TYP * DELRES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdRes                                       *
 * Description    : Update resource with non-ACL info               *
 * Input          : res_params      - Resource data                 *
 *                  addinfo         - RSS_specific keywords that    *
 *                                    contains the modifications    * 
 *                  admin_params                                    *
 * Output         : err             - Messages (Opt.)               *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  UPDRES_FUNC_TYP   CTSUpdRes;       /* actual function */

typedef UPDRES_FUNC_TYP * UPDRES_FUNC_PTR; /* pointer to func */

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIRES__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIRES__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIRES_H_INCLUDED */
