/**********************************************************************
*
*   H Source      : apioe.h
*   Description   : USA-API Container processing functions
*   %full_filespec: apioe.h#3:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIOE_H_INCLUDED
#define APIOE_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API CONTAINER     == */
/* == functions.                                                     == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: CTSMoveOE                                        *
 * Description   : Move container                                   *
 * Input         : oe_params    - container data                    *
 *                 new_parent   - move to                           *
 *                 addinfo      - RSS-specific keywords             *
 *                 admin_params                                     *
 * Output        : resulted_oe  - new OE id, if affected by move    *
 *                 err - Messages (Opt.)                            *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC MVOE_FUNC_TYP(OE_PARAMS_rec_typ    * oe_params,
                             OE_typ                 new_parent,
                             OE_typ                 resulted_oe,
                             ADDINFO_rec_typ      * addinfo,
                             ADMIN_PARAMS_rec_typ * admin_params,
                             ERR_STRUCT_rec_typ   * err);

extern  MVOE_FUNC_TYP   CTSMoveOE;       /* actual function */

typedef MVOE_FUNC_TYP * MVOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSRenameOE                                      *
 * Description   : Move container                                   *
 * Input         : oe_params    - container data                    *
 *                 new_oe       - new container                     *
 *                 addinfo      - RSS-specific keywords             *
 *                 admin_params                                     *
 *                 err - Messages (Opt.)                            *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC RNOE_FUNC_TYP(OE_PARAMS_rec_typ    * oe_params,
                             OE_typ                 new_oe,
                             ADDINFO_rec_typ      * addinfo,
                             ADMIN_PARAMS_rec_typ * admin_params,
                             ERR_STRUCT_rec_typ   * err);

extern  RNOE_FUNC_TYP   CTSRenameOE;       /* actual function */

typedef RNOE_FUNC_TYP * RNOE_FUNC_PTR; /* pointer to func */


/********************************************************************
 * Procedure Name: CTSAddOE                                         *
 * Description   : Create new container                             *
 * Input         : oe_params    - container data                    *
 *                 addinfo - RSS-specific keywords                  *
 *                 admin_params                                     *
 * Output        : err - Messages (Opt.)                            *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC ADDOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  ADDOE_FUNC_TYP   CTSAddOE;       /* actual function */

typedef ADDOE_FUNC_TYP * ADDOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSDelOE                                         *
 * Description   : Delete container                                 *
 * Input         : oe_params    - container data                    *
 *                 addinfo      - RSS-specific keywords             *
 *                 admin_params                                     *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC DELOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  DELOE_FUNC_TYP   CTSDelOE;       /* actual function */

typedef DELOE_FUNC_TYP * DELOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSUpdOE                                         *
 * Description   : Update container                                 *
 * Input         : oe_params    - container data                    *
 *                 addinfo      - RSS-specific keywords             *
 *                 admin_params                                     *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/

typedef ESA_RC UPDOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  UPDOE_FUNC_TYP   CTSUpdOE;       /* actual function */

typedef UPDOE_FUNC_TYP * UPDOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSGetOEs                                        *
 * Description   : Get containers                                   *
 * Input         : mode          - GET_ALL,                         *
 *                                 GET_MANY (one or many),          *
 *                                 GET_WILD (wildcards)             *
 *                                 GET_FREE_HANDLE (see below)      *
 *                 max_oe        - # of elements in oe_params,      *
 *                                 objs_exist and addinfo arrays    *
 *                 num_oe_in     - # of elements in oe_params_in    *
 *                 oe_params_in  - array of num_oe_in, filled with  *
 *                                 OEs requested.                   *
 *                 admin_params   -                                 *
 * Output        : actual_num   - # of OEs returned                 *
 *                 have_more    - HAVE_MORE if more OEs,            *
 *                                else NO_MORE                      *
 *                 err          - error indication, message, etc.   *
 *                 objs_exist   - array of max_oe:                  *
 *                                OBJ_EXIST if OE exists, else      *
 *                                OBJ_NOT_EXIST.                    *
 *                 oe_params    - array of max_oe:                  *
 *                                callee fills with OES returned    *
 *  Input/Output : addinfo      - array of max_OE pointers:         *
 *                                add.info per OE, Caller puts      *
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

typedef ESA_RC GETOES_FUNC_TYP (GET_OE_MODE            mode,
                                OE_typ                 oe,
                                short                  max_oe,
                                short                * actual_num,
                                HAVE_MORE_typ        * have_more,
                                void                ** handle,
                                short                  num_oe_in,
                                OE_PARAMS_rec_typ    * oe_params_in,
                                OE_PARAMS_rec_typ    * oe_params,
                                ADDINFO_rec_typ     ** addinfo,
                                OBJ_EXISTS_typ       * objs_exist,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  GETOES_FUNC_TYP   CTSGetOEs;       /* actual function */

typedef GETOES_FUNC_TYP * GETOES_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSIsUserInOE                                    *
 * Description   : User belong to the OE                            *
 * Input         : user_type    - User name.                        *
 *                 oe_mask      - OE mask.                          *
 *                 admin_params -                                   *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_OK     User in OE                            *
 *                 ESA_EOF    User not in OE                        *
 *                 ESA_ERR    on any other situation                *
 ********************************************************************/

typedef ESA_RC ISUSERINOE_FUNC_TYP (USER_typ               user,
                                    OE_typ                 oe_mask,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISUSERINOE_FUNC_TYP   CTSIsUserInOE;       /* actual function */

typedef ISUSERINOE_FUNC_TYP * ISUSERINOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSIsUGInOE                                      *
 * Description   : Group belong to the OE                           *
 * Input         : ug_type      - Group name.                       *
 *                 oe_mask      - OE mask.                          *
 *                 admin_params -                                   *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_OK     Group in OE                           *
 *                 ESA_EOF    Group not in OE                       *
 *                 ESA_ERR    on any other situation                *
 ********************************************************************/

typedef ESA_RC ISUGINOE_FUNC_TYP   (UG_typ                 ug,
                                    OE_typ                 oe_mask,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISUGINOE_FUNC_TYP   CTSIsUGInOE;       /* actual function */

typedef ISUGINOE_FUNC_TYP * ISUGINOE_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: CTSIsOEInOE                                      *
 * Description   : OE belong to the OE                              *
 * Input         : oe_name      - OE name.                          *
 *                 oe_mask      - OE mask.                          *
 *                 admin_params -                                   *
 * Output        : err          - Messages (Opt.)                   *
 * Return Value  : ESA_OK     OE in OE                              *
 *                 ESA_EOF    OE not in OE                          *
 *                 ESA_ERR    on any other situation                *
 ********************************************************************/

typedef ESA_RC ISOEINOE_FUNC_TYP   (OE_typ                 oe_name,
                                    OE_typ                 oe,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISOEINOE_FUNC_TYP   CTSIsOEInOE;       /* actual function */

typedef ISOEINOE_FUNC_TYP * ISOEINOE_FUNC_PTR; /* pointer to func */


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIOE__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIOE__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIOE_H_INCLUDED */
