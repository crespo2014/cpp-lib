/**********************************************************************
*
*   H Source      : apiconn.h
*   Description   : USA-API Connection processing functions
*   %full_filespec: apiconn.h#2:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APICONN_H_INCLUDED
#define APICONN_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains prototypes for USA-API CONNECTION    == */
/* == functions.                                                     == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: CTSGetConnections                                *
 * Description   : Get group to user / group to group connections   *
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
 *                 num_contained_                                   *
 *                   objects_in  - # of input contained objects     *
 *                 num_containing_                                  *
 *                    objects_in - # of input containing objects    *
 *                 contained_objects_in                             *
 *                              - array of num_contained_objects_in.*
 *                                Caller fills with contained       *
 *                                objects requested (if not GET_ALL)*
 *                 containing_objects_in                            *
 *                              - array of num_containing_objects_in*
 *                                Caller fills with containing      *
 *                                objects requested.                *
 * Output        : actual_num   - # of connections returned         *
 *                 have_more    - HAVE_MORE if more conns,          *
 *                                else NO_MORE                      *
 *                 cnn_params  - details of each connection         *
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
 *                    cnn_params, add.info, obj_exist               *
 ********************************************************************/

typedef ESA_RC GETCONNECTION_FUNC_TYP
                             (GET_CONN_MODE          mode,
                              short                  max_conns,
                              short                * actual_num,
                              HAVE_MORE_typ        * have_more,
                              void                ** handle,
                              short                  num_containing_objects_in,
                              short                  num_contained_objects_in,
                              CNN_OBJ_typ          * containing_objects_in,
                              CNN_OBJ_typ          * contained_objects_in,
                              CNN_PARAMS_rec_typ   * cnn_params,
                              ADDINFO_rec_typ     ** addinfo,
                              OBJ_EXISTS_typ       * objs_exist,
                              ADMIN_PARAMS_rec_typ * admin_params,
                              ERR_STRUCT_rec_typ   * err);

extern  GETCONNECTION_FUNC_TYP   CTSGetConnections;      /* actual function */

typedef GETCONNECTION_FUNC_TYP * GETCONNECTION_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSAddConnection                                *
 * Description    : Connect two objects                             *
 * Input          : cnn_data     - connection data                  *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC ADDCNN_FUNC_TYP (CNN_PARAMS_rec_typ   * cnn_data,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  ADDCNN_FUNC_TYP   CTSAddConnection; /* actual function */

typedef ADDCNN_FUNC_TYP * ADDCNN_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name : CTSDelConnection                                *
 * Description    : Disconnect two objects                          *
 * Input          : cnn_data     - connection data                  *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC DELCNN_FUNC_TYP (CNN_PARAMS_rec_typ   * cnn_data,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  DELCNN_FUNC_TYP   CTSDelConnection; /* actual function */

typedef DELCNN_FUNC_TYP * DELCNN_FUNC_PTR;  /* pointer to func */

/********************************************************************
 * Procedure Name : CTSUpdConnection                                *
 * Description    : Update connection details                       *
 * Input          : cnn_data     - connection data                  *
 *                  addinfo      - RSS_specific keywords            *
 *                  admin_params                                    *
 * Output         : err          - Messages (Opt.)                  *
 * Return Value   : ESA_RC                                          *
 ********************************************************************/

typedef ESA_RC UPDCNN_FUNC_TYP (CNN_PARAMS_rec_typ   * cnn_data,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  UPDCNN_FUNC_TYP   CTSUpdConnection; /* actual function */

typedef UPDCNN_FUNC_TYP * UPDCNN_FUNC_PTR;  /* pointer to func */


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APICONN__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APICONN__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APICONN_H_INCLUDED */
