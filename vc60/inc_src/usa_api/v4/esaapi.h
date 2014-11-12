/**********************************************************************
*
*	H Source:		esaapi.h
*	Description:	ESA-API interface
*	%date_created:	Fri May 09 18:17:41 2003 %
*   %full_filespec: esaapi.h#19:incl:1 %
*	%created_by:	leonid_s %
*
**********************************************************************/

#ifndef ESAAPI_H_INCLUDED
#define ESAAPI_H_INCLUDED

#include "esaglobs.h"

/*#ifdef  WINNT*/

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*#endif*/ /* WINNT */

#ifdef WNTINC
#include "esadiag.h"
#include "ctsamsg.h"
#elif defined AS400_NT
#include "h.esadiag"
#include "h.ctsamsg"
#else
#include ESA_DIAG
#include ESA_CTSAMSG
#endif

/****************************************************
 * Define short function names for MVS compiler
 ***************************************************/

#ifdef MVS

#define rsslist_get          rsslist
#define rssprm_get           rsspget
#define rsskwd_typ           rssktyp
#define rssprm_get_opt       rsspgop
#define MSG_printf           msgprnt
#define DIAG_printf          diagprt
#define DIAG_enter           diagent
#define DIAG_exit            diagext
#define LOG_event            logevnt
#define DIAG_get_debug_level diadbgl
#define DIAG_refresh         diafrsh
#define RssTblGet            rsstblg  
#define RssTblSet            rsstbls  
#define CTSApiProcTerm       Apiptrm
#define CTSApiProcInit       Apipini
#define DATA_COMP_ESAAPI__   Api0001

#endif /* MVS */

/********************************************/
/*  Typedefs for RSS status check           */
/********************************************/

typedef enum {
    RSS_UP,
    RSS_DOWN
} RSS_STATUS_typ;

/********************************************/
/*  Define time and date formats            */
/********************************************/

#define DATE_LEN             8
#define TIME_LEN             6

typedef char TIME_typ [ TIME_LEN + 1 ];  /* HHMMSS   */
typedef char DATE_typ [ DATE_LEN + 1 ];  /* YYYYMMDD */

/********************************************/
/*  Length values for entity names          */
/********************************************/

#define RSS_NAME_LEN         32
#define LOGENT_LEN         2560
#define RSS_VERS_LEN         12

/********************************************/
/* ESAAPI Limits                 		    */
/********************************************/

#define MAX_RSS_OE_NAME_LEN			256
#define MAX_RSS_ACE_OE_NAME_LEN		256
#define MAX_RSS_USER_NAME_LEN		256
#define MAX_RSS_ACE_USER_NAME_LEN	MAX_RSS_USER_NAME_LEN + HOST_NAME_LENGTH + 3
#define MAX_RSS_UG_NAME_LEN			256
#define MAX_RSS_ACE_UG_NAME_LEN		256 + HOST_NAME_LENGTH + 3
#define MAX_RSS_RESOURCE_NAME_LEN	256 + 4
#define MAX_RSS_RESTYPE_NAME_LEN	20
#define MAX_RSS_PASSWD_LEN			256

#define MAX_RSS_ADDINFO_KWD_LEN		64


#define MAX_RSS_ADDINFO_VAL_LEN       4096   /* Aviw - 6/5/01 */

/********************************************/
/*  typedefs for entity names               */
/********************************************/

typedef char OE_typ           [ MAX_RSS_OE_NAME_LEN + 1       ];
typedef char ACE_OE_typ       [ MAX_RSS_ACE_OE_NAME_LEN + 1   ];
typedef char RSS_typ          [ RSS_NAME_LEN + 1              ];
typedef char USER_typ         [ MAX_RSS_USER_NAME_LEN + 1     ];
typedef char ACE_USER_typ     [ MAX_RSS_ACE_USER_NAME_LEN + 1 ];
typedef char UG_typ           [ MAX_RSS_UG_NAME_LEN + 1       ];
typedef char ACE_UG_typ       [ MAX_RSS_ACE_UG_NAME_LEN + 1   ];
typedef char RESOURCE_typ     [ MAX_RSS_RESOURCE_NAME_LEN + 1 ];
typedef char RESTYPE_typ      [ MAX_RSS_RESTYPE_NAME_LEN + 1  ];
typedef char LOGENT_typ       [ LOGENT_LEN + 1                ];
typedef char RSS_vers_typ     [ RSS_VERS_LEN + 1              ];
typedef char PASSWD_typ       [ MAX_RSS_PASSWD_LEN + 1        ];

/********************************************/
/*  Typedefs for OE objects                 */
/********************************************/

typedef enum {
    TYPE_IGNORE = 1,
    TYPE_USER,
    TYPE_GROUP,
    TYPE_CONTAINER,
    TYPE_CONNECTION,
    TYPE_RESOURCE,
    TYPE_ACL,
    TYPE_RSS,
    TYPE_END
} OBJECT_TYPE_typ;

typedef enum {
    MASK_REGULAR = 0,
    MASK_WILD
} MASK_TYPE_typ;

typedef enum {
    OE_ATTR_IGNORED,
    OE_ATTR_ACL,         /* OE allowed in ACL */
    OE_ATTR_NO_ACL       /* OE not allowed in ACL */
} OE_ATTR_typ;

typedef struct S_OE_PARAMS {
    OE_typ      oe;
    OE_typ      parent;
    OE_ATTR_typ attr;
} OE_PARAMS_rec_typ, * OE_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for RSS_PARAMS data            */
/********************************************/

typedef short MPL_typ;   /* Minimum Password Length              */
typedef short MPE_typ;   /* Maximum days for Password Expiration */
typedef short MLA_typ;   /* Maximum # of bad Login Allowed       */

typedef struct S_RSS_PARAMS_rec_typ {
    MPL_typ   min_pass_len;
    MPE_typ   max_expire;
    MLA_typ   max_logins;
} RSS_PARAMS_rec_typ, * RSS_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for Additional Info data       */
/********************************************/

typedef enum {TYPE_AI_IGNORED= 0,
              TYPE_1A,
              TYPE_1B,
              TYPE_2A,
              TYPE_2B
} ADDINFO_typ;

typedef struct S_ONE_FIELD_rec_typ {
   ADDINFO_typ add_typ;
   short       keylen;                      /* field len w/o null*/
   char        keyword [MAX_RSS_ADDINFO_KWD_LEN+1];/* Null-term.str.*/
   short       vallen;                      /* field len w/o null*/
   char        value   [MAX_RSS_ADDINFO_VAL_LEN+1];/* Null-term.str.*/
} ONE_FIELD_rec_typ, * ONE_FIELD_rec_ptr;

typedef  struct  S_ADDINFO {
   short              num_pairs;
   short              max_pairs;
   ONE_FIELD_rec_typ  pair [1];   /* actually pair [num_pairs] */
} ADDINFO_rec_typ, * ADDINFO_rec_ptr;

/********************************************/
/*  Typedef for common error structure      */
/********************************************/

typedef  struct S_ERR_STRUCT {
  short    length;
  char     err_msg_text [ERR_MSG_TEXT_LEN]; /* LEN in platform.h */
} ERR_STRUCT_rec_typ, * ERR_STRUCT_rec_ptr;

/********************************************/
/*  Typedefs for RSS-related data           */
/********************************************/

typedef enum {ADMIN_MODE_IGNORED,
              ADMIN_MODE_NORMAL,
              ADMIN_MODE_SIMULATION
} ADMIN_MODE_typ;

/********************************************/
/*  Typedefs for INTERCEPTION data          */
/********************************************/

typedef enum {
    INTERCEPT_NONE,      /* Not interception required            */
    INTERCEPT_SPECIFIC,  /* Intercept specific object            */
    INTERCEPT_FULL,      /* Intercept object and its connections */
    INTERCEPT_SUBTREE    /* Intercept subtree of container       */
} INTERCEPT_typ;

typedef enum {
    INTERCEPT_CONTAINER,    /* Valid only for SPECIFIC & SUBTREE type*/
    INTERCEPT_USER,         /* Valid for any type but SUBTREE        */
    INTERCEPT_GROUP,        /* Valid for any type but SUBTREE        */
    INTERCEPT_CONNECTION ,  /* Valid for SPECIFIC type               */
    INTERCEPT_RSSPRM,       /* Valid for NONE type                   */
    INTERCEPT_ALL           /* Valid for NONE and SUBTREE type       */
} INTERCEPT_obj_typ;

typedef struct S_INTERCEPT_rec_typ {
    INTERCEPT_typ          type;
    INTERCEPT_obj_typ      obj_type;
    OE_typ                 oe;
    USER_typ               user;
    UG_typ                 ug;
} INTERCEPT_rec_typ, * INTERCEPT_rec_ptr;

typedef enum {
    UPDCONN_NO,
    UPDCONN_YES
} TRNSEVNT_UPCON_FLAG_typ;

typedef enum {
    OPT_FALSE,
    OPT_TRUE,
    OPT_UNDEFINED
} OPTION_typ;

typedef struct S_RSS_rec_typ {
    RSS_typ                rss_name;
    RSS_typ                rss_type;
    RSS_STATUS_typ         rss_status;
} RSS_rec_typ, * RSS_rec_ptr;

/****************************************************
 * Procedure Name: rsstbl_get
 * Description   : Get data from RSSOFLI for specific rss
 * Return Value  : ESA_OK             upon success
 *                 ESA_KEY_NOT_FOUND  on any other situation
 ****************************************************/

typedef ESA_RC RSSTBL_GET_DATA_FUNC_TYP (DATE_typ        TblDate,
                                         TIME_typ        TblTime,
                                         unsigned long * RecNum); 

extern  RSSTBL_GET_DATA_FUNC_TYP   RssTblGet;

typedef RSSTBL_GET_DATA_FUNC_TYP * RSSTBL_GET_DATA_FUNC_PTR; 


/****************************************************
 * Procedure Name: rsstbl_set
 * Description   : Set data from RSSOFLI for specific rss
 * Return Value  : ESA_OK             upon success
 *                 ESA_KEY_NOT_FOUND  on any other situation
 ****************************************************/

typedef ESA_RC RSSTBL_SET_DATA_FUNC_TYP (DATE_typ        TblDate,
                                         TIME_typ        TblTime,
                                         unsigned long   RecNum); 

extern  RSSTBL_SET_DATA_FUNC_TYP   RssTblSet;

typedef RSSTBL_SET_DATA_FUNC_TYP * RSSTBL_SET_DATA_FUNC_PTR; 


/****************************************************
 * Procedure Name: DIAG_refresh
 * Description   : Read levels from file, set debug level for
 *                 all components
 * Return Value  : ESA_RC
 * Side Effects  : Static array is modified
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

typedef ESA_RC DIAG_REFRESH_FUNC_TYP (void);

extern  DIAG_REFRESH_FUNC_TYP DIAG_refresh;            

typedef DIAG_REFRESH_FUNC_TYP * DIAG_REFRESH_FUNC_PTR;

/**************************************************************
* Procedure Name   : MSG_print                            *
* Description      : Issue a message to the requested         *
*                    destinations                             *
* Input            : 1) msgid   - msgid to be printed         *
*                    2) ...     - arguments for message       *
* Return Value     : ESA_RC                                   *
* Comments         : The function process the arg list and    *
*                    calls CTSAMSG_print                      *
**************************************************************/

typedef ESA_RC MSG_PRINT_FUNC_TYP (const char * msgid , ... );

extern  MSG_PRINT_FUNC_TYP MSG_printf;             

typedef MSG_PRINT_FUNC_TYP * MSG_PRINT_FUNC_PTR ; 

/****************************************************
 * Procedure Name: DIAG_printf
 * Description   : printf-like diagnostics
 * Input         : Component, level, format, arguments
 * Output        :
 * Return Value  :
 * Side Effects  : VARARGS is used
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

typedef void DIAG_PRINTF_FUNC_TYP (ESA_DIAG_COMP_typ    comp,
                                   ESA_DIAG_LEVEL_typ   level,
                                   const char         * format, ... );

extern  DIAG_PRINTF_FUNC_TYP DIAG_printf;            

typedef DIAG_PRINTF_FUNC_TYP * DIAG_PRINTF_FUNC_PTR;

/****************************************************
 * Procedure Name: DIAG_get_debug_level
 * Description   : return diag level of a component
 * Input         : Component
 * Output        : None
 * Return Value  : Level
 * Re-entrant    : No
 ****************************************************/

typedef ESA_DIAG_LEVEL_typ DIAG_GET_DEBUG_LEVEL_FUNC_TYP (
                                          ESA_DIAG_COMP_typ  comp);

extern DIAG_GET_DEBUG_LEVEL_FUNC_TYP DIAG_get_debug_level;            

typedef DIAG_GET_DEBUG_LEVEL_FUNC_TYP * DIAG_GET_DEBUG_LEVEL_FUNC_PTR;

/****************************************************
 * Procedure Name: DIAG_enter
 * Description   : Push calling func name on stack, print message
 * Input         : component, level, func name
 * Output        :
 * Return Value  :
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

typedef void DIAG_ENTER_FUNC_TYP (ESA_DIAG_COMP_typ    comp,
                                  ESA_DIAG_LEVEL_typ   level,
                                  const char         * funcname);

extern  DIAG_ENTER_FUNC_TYP DIAG_enter;           /* act function */

typedef DIAG_ENTER_FUNC_TYP * DIAG_ENTER_FUNC_PTR;/* pntr to func */

/****************************************************
 * Procedure Name: DIAG_exit
 * Description   : Pop function stack, print message
 * Input         : Component, level, function name, RC
 * Output        :
 * Return Value  :
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

typedef void DIAG_EXIT_FUNC_TYP (ESA_DIAG_COMP_typ   comp,
                                 ESA_DIAG_LEVEL_typ  level,
                                 const char        * funcname,
                                 ESA_RC              rc_ret);

extern  DIAG_EXIT_FUNC_TYP DIAG_exit;            /* act function */

typedef DIAG_EXIT_FUNC_TYP * DIAG_EXIT_FUNC_PTR; /* pntr to func */

/****************************************************
 * Procedure Name: rsslist_get
 * Description   : Get list of rsses from CONTROL-SA global parameter
 *                 file for a specific RSS.
 * Output        : rss_num 
 *                 rss_rec
 * Return Value  : ESA_OK             upon success
 *                 ESA_KEY_NOT_FOUND  on any other situation
 ****************************************************/

typedef ESA_RC RSSLIST_GET_FUNC_TYP (unsigned int  * rss_num,
                                     RSS_rec_typ  ** rss_rec);

extern  RSSLIST_GET_FUNC_TYP    rsslist_get;    /* actual function */

typedef RSSLIST_GET_FUNC_TYP * RSSLIST_GET_FUNC_PTR;/*pointer to func*/

/****************************************************
 * Procedure Name: rssprm_get
 * Description   : Get a parameter from CONTROL-SA global parameter
 *                 file for a specific RSS.
 * Input         : RSS name
 *                 parameter name
 *                 maximum value length
 * Output        : parameter value
 * Return Value  : ESA_OK             upon success
 *                 ESA_KEY_NOT_FOUND  on any other situation
 ****************************************************/

typedef ESA_RC RSSPRM_GET_FUNC_TYP (RSS_typ const   rss,
                                    char const    * param_name,
                                    unsigned int    max_value_len,
                                    char          * param_value);

extern  RSSPRM_GET_FUNC_TYP    rssprm_get;         /* actual function */

typedef RSSPRM_GET_FUNC_TYP * RSSPRM_GET_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: rssprm_get_opt
 * Description   : Get a parameter from CONTROL-SA global parameter
 *                 file for a specific RSS.
 * Input         : RSS name
 *                 parameter name
 *                 maximum value length
 *                 optional_prm    TRUE  - The parameter is optional
 *                                 FALSE - The parameter must exist
 *                 optional_value  TRUE  - The parameter value may
 *                                         empty.
 *                                 FALSE - The parameter value may
 *                                         not be empty
 * Output        : parameter value
 * Return Value  : ESA_OK             upon success
 *                 ESA_KEY_NOT_FOUND  on any other situation
 ****************************************************/

typedef ESA_RC RSSPRM_GET_OPT_FUNC_TYP (RSS_typ const  rss,
                                        char const   * param_name,
                                        unsigned int   max_value_len,
                                        char         * param_value,
                                        OPTION_typ     optional_prm,
                                        OPTION_typ     optional_value);

extern  RSSPRM_GET_OPT_FUNC_TYP    rssprm_get_opt; /* actual function */

typedef RSSPRM_GET_OPT_FUNC_TYP * RSSPRM_GET_OPT_FUNC_PTR;/*ptr to fnc*/

/****************************************************
 * Procedure Name: rsskwd_typ
 * Description   : Get a keyword type from CONTROL-SA global keywords
 *                 file for a specific RSS.
 * Input         : RSS name
 *                 func_code
 *                 keyword
 * Output        : keyword type
 * Return Value  : ESA_OK             upon success
 ****************************************************/

typedef ESA_RC RSSKWD_TYP_FUNC_TYP (RSS_typ           rss,
                                    int               func_code,
                                    char            * keyword,
                                    ADDINFO_typ     * keyword_type);

extern  RSSKWD_TYP_FUNC_TYP  rsskwd_typ;   /* actual function */

typedef RSSKWD_TYP_FUNC_TYP * RSSKWD_TYP_FUNC_PTR;

/*****************************************************************
* Procedure Name: intercept_set
* Description   : Accept request for interception
* Input         : interc. type, obj_type, OE, user, ug
* Output        : intercept_record
* Input/Output  : num_intercept_rec
* Return Value  : ESA_RC
*****************************************************************/

typedef ESA_RC INTERCEPT_SET_FUNC_TYP (
        INTERCEPT_typ        type,
        INTERCEPT_obj_typ    obj_type,
        OE_typ               oe,
        USER_typ             user,
        UG_typ               ug);

extern  INTERCEPT_SET_FUNC_TYP intercept_set;   /* actual function */

typedef INTERCEPT_SET_FUNC_TYP * INTERCEPT_SET_FUNC_PTR;
                                                /* pointer to func */
/****************************************************
 * Procedure Name: CTSLogEvent
 * Description   : RSS log event has occured
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 msgid    - Message code from message code file.
 *                 ...      - Message parameters list.
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSLOGEVT_FUNC_TYP (RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  const char             * msgid,
                                  ...);

extern  RSLOGEVT_FUNC_TYP   CTSLogEvent;       /* actual function */

typedef RSLOGEVT_FUNC_TYP * RSLOGEVT_FUNC_PTR; /* pointer to func */


/****************************************************
 * Procedure Name: LOG_event
 * Description   : RSS log event has occured
 * Input           msgid    - Message code from message code file.
 *                 ...      - Message parameters list.
 * Output        :
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC LOGEVT_FUNC_TYP (const char * msgid,
                                ...);

extern  LOGEVT_FUNC_TYP   LOG_event;       /* actual function */

typedef LOGEVT_FUNC_TYP * LOGEVT_FUNC_PTR; /* pointer to func */


/********************************************/
/*  CSA function pointers structure         */
/********************************************/

typedef  struct  S_CS_FUNC_PTR {

  RSSLIST_GET_FUNC_PTR          rsslist_get_ptr;
  RSSPRM_GET_FUNC_PTR           rssprm_get_ptr;
  RSSKWD_TYP_FUNC_PTR           rsskwd_typ_ptr;
  INTERCEPT_SET_FUNC_PTR        intercept_set_ptr;
  RSSPRM_GET_OPT_FUNC_PTR       rssprm_get_opt_ptr;
  LOGEVT_FUNC_PTR               LOG_event_ptr;
  MSG_PRINT_FUNC_PTR            MSG_printf_ptr;
  DIAG_PRINTF_FUNC_PTR          DIAG_printf_ptr;
  DIAG_GET_DEBUG_LEVEL_FUNC_PTR DIAG_get_debug_level_ptr;
  DIAG_ENTER_FUNC_PTR           DIAG_enter_ptr;
  DIAG_EXIT_FUNC_PTR            DIAG_exit_ptr;
  DIAG_REFRESH_FUNC_PTR         DIAG_refresh_ptr;
  RSSTBL_GET_DATA_FUNC_PTR      RssTblGet_ptr;
  RSSTBL_SET_DATA_FUNC_PTR      RssTblSet_ptr;
} CS_FUNC_PTR_rec_typ,  * CS_FUNC_PTR_rec_ptr;

typedef  struct  S_ADMIN_PARAMS {
    RSS_typ                      rss_name;
    RSS_typ                      rss_type;
    USER_typ                     admin_uname;
    UG_typ                       admin_gname;
    RSS_vers_typ                 rss_version;
    ADMIN_MODE_typ               mode;
    void                       * os_proc_handle;
    void                       * login_handle;
    void                       * esadiag_handle;
    void                       * apiinit_handle;
    CTSAMSG_HANDLE_rec_typ     * ctsamsg_handle;
    CTSAMSG_DEST_TABLE_rec_typ * ctsamsg_dest;
    CS_FUNC_PTR_rec_typ          cs_func;
    PASSWD_typ                   admin_passwd;
    USER_typ                     def_admin;
    PASSWD_typ                   def_admin_passwd;
    const char                 * program_name;                 
}  ADMIN_PARAMS_rec_typ, * ADMIN_PARAMS_rec_ptr;


/********************************************/
/*  Typedefs for user data                  */
/********************************************/

typedef enum {
    USER_STAT_IGNORED,
    USER_STAT_REVOKED,
    USER_STAT_ACTIVE
} USER_STATUS_typ;

typedef enum {
    USER_ADM_IGNORED,
    USER_ADM_NONE,
    USER_ADM_AUDIT,
    USER_ADM_ADMIN,
    USER_ADM_ALL
} USER_ADMIN_typ;

typedef enum {
    PASS_LIFE_IGNORED,
    PASS_LIFE_PERMANENT,
    PASS_LIFE_RESET
} PASSWD_LIFE_typ;

typedef enum {
    OLD_DEF_UG_ACT_IGNORED,
    OLD_DEF_UG_ACT_DROP,    /* delete old connection */
    OLD_DEF_UG_ACT_KEEP     /* keep old connection as non-default */
} OLD_DEF_UG_ACTION_typ;

typedef  struct  S_USER_PARAMS {
    USER_typ              user;
    OE_typ                parent_oe;
    UG_typ                def_group;
    PASSWD_typ            passwd;
    PASSWD_LIFE_typ       passwd_life;
    USER_STATUS_typ       rev_status;
    USER_ADMIN_typ        user_admin;
    OLD_DEF_UG_ACTION_typ def_ug_action;
}  USER_PARAMS_rec_typ, * USER_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for UG data                    */
/********************************************/

typedef  struct  S_UG_PARAMS {
    UG_typ          group;
    OE_typ          parent_oe;
    UG_typ          parent_group;
} UG_PARAMS_rec_typ, * UG_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for USER-to-UG connection      */
/********************************************/

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
} U2UG_PARAMS_rec_typ;

/********************************************/
/*  Typedefs for RESOURCE data              */
/********************************************/

typedef  struct  S_RES_PARAMS {
  RESOURCE_typ    resource;
  RESTYPE_typ     restype;
  OE_typ          parent_oe;
} RES_PARAMS_rec_typ, * RES_PARAMS_rec_ptr;


/********************************************/
/*  Typedef for exist/not exist array       */
/********************************************/

typedef enum {OBJ_IGNORED,
              OBJ_EXIST,
              OBJ_NOT_EXIST,
              OBJ_ERR
} OBJ_EXISTS_typ;

/********************************************/
/*  Typedefs for time range                 */
/********************************************/

typedef  struct  S_TIME_RANGE {
    DATE_typ      from_date;
    TIME_typ      from_time;
    DATE_typ      end_date;
    TIME_typ      end_time;
} TIME_RANGE_rec_typ, * TIME_RANGE_rec_ptr;

/********************************************/
/*  Typedef for intercept type              */
/********************************************/

typedef enum {INTERCEPT_OFFLINE,
              INTERCEPT_ONLINE,
              INTERCEPT_SOI
} INTERCEPTOR_typ;

/********************************************/
/*  Typedef for logi/logout mode            */
/********************************************/

typedef enum {LOGIN_MODE_FIRST = 1,
              LOGIN_MODE,
              LOGOUT_MODE,
              LOGOUT_MODE_LAST
} LOGIN_MODE_typ;

/**********************************************/
/*  Typedefs for ACE operations (add/del/upd) */
/**********************************************/

typedef enum {
    ACE_TYPE_IGNORED,
    ACE_TYPE_UNDEFINED,
    ACE_TYPE_USER,
    ACE_TYPE_GROUP,
    ACE_TYPE_USER_AND_GROUP,
    ACE_TYPE_WORLD,
    ACE_TYPE_MASK,
    ACE_TYPE_OE
} ACE_TYPE_typ;

typedef enum {ACE_POS_IGNORED,
              ACE_POS_FIRST,
              ACE_POS_LAST,
              ACE_POS_BEFORE,
              ACE_POS_AFTER
} ACE_POS_typ;

typedef enum {ACE_ATTR_IGNORED,
              ACE_ATTR_REGULAR,
              ACE_ATTR_PERMANENT
} ACE_ATTR_typ;

typedef struct S_ACE_STRUCT {
    ACE_TYPE_typ         ace_type;
    ACE_USER_typ         user_name;
    ACE_UG_typ           ug_name;
    ACE_OE_typ           oe_name;
    ACE_ATTR_typ         ace_attrs;
} ACE_rec_typ, * ACE_rec_ptr;

/*****************************************************
 *
 * Typedefs for Get functions
 *
 ****************************************************/

typedef enum {
    NO_MORE,
    HAVE_MORE
} HAVE_MORE_typ;

typedef enum {
    GET_ALL_USERS,
    GET_MANY_USERS,
    GET_WILD_USERS,         /* Let's all get wild */
    GET_SUBTREE_USERS,      /* For OE objects     */
    GET_FREE_HANDLE_USERS   /* free *handle       */
} GET_USER_MODE;

typedef enum {
    GET_ALL_GROUPS,
    GET_MANY_GROUPS,
    GET_SUBTREE_GROUPS,      /* For OE objects  */
    GET_FREE_HANDLE_GROUPS   /* free *handle    */
} GET_GROUP_MODE;

typedef enum {
    GET_ALL_OES,
    GET_MANY_OES,
    GET_SUBTREE_OES,      /* For OE objects  */
    GET_FREE_HANDLE_OES   /* free *handle    */
} GET_OE_MODE;

typedef enum {
    GET_MANY_RESOURCES,
    GET_FREE_HANDLE_RESOURCES   /* free *handle */
} GET_RESOURCE_MODE;

typedef enum {
    GET_RESOURCE_ACL,     /* Get all ACLs of specified resource */
    GET_FREE_HANDLE_ACL   /* free *handle                       */
} GET_ACL_MODE;

typedef enum {
    GET_ALL_CONNS,
    GET_GROUPS_CONNS,     /* Get all connections for spec. groups*/
    GET_USERS_CONNS,      /* Get all connections for spec. users */
    GET_MANY_CONNS,       /* Get specified connections           */
    GET_FREE_HANDLE_CONNS /* free *handle                        */
} GET_CONN_MODE;

typedef enum {
    GET_ALL_GRP_RES,          /* resource groups */
    GET_FREE_HANDLE_GRP_RES   /* free *handle    */
} GET_GRP_RES_MODE;

/*********************************************************
 *  typedef for action:                                  *
 *  unknown, add, update, delete, revoke, passwd_updated *
 ********************************************************/

typedef enum {
    ACT_UNKNOWN,
    ACT_ADD,
    ACT_UPDATE,
    ACT_DELETE,
    ACT_REVOKE,    /* DXC001 */
    ACT_PWD_UPD,   /* DXC001 */
    ACT_CONN_UPD   /* AJKxxx */
} ACTION_typ;

/*****************************************************
 *
 * Non-RSS functions
 *
 ****************************************************/

/****************************************************
 * Procedure Name : CTSVersion
 * Description    : API version from API_VERSION
 * Input          :
 * Output         : api_version
 * Return Value   : ESA_RC
 * Comments       : Platform-dependent operations to be performed
 *                  prior to any API call.
 ***************************************************/

typedef ESA_RC APIVERSION_FUNC_TYP (RSS_vers_typ  version);

extern  APIVERSION_FUNC_TYP   CTSVersion;    /* actual function */

typedef APIVERSION_FUNC_TYP * APIVERSION_FUNC_PTR;/*pointer to func */


/****************************************************
 * Procedure Name : CTSAPIInit
 * Description    : API initialization
 * Input          :
 * Output         :
 * Input/Output   : admin, err
 * Return Value   : ESA_RC
 * Comments       : Platform-dependent operations to be performed
 *                  prior to any API call.
 ***************************************************/

typedef ESA_RC APIINIT_FUNC_TYP (ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  APIINIT_FUNC_TYP   CTSAPIInit;       /* actual function */

typedef APIINIT_FUNC_TYP * APIINIT_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSAPITerm
 * Description    : API termination & cleanup
 * Input          :
 * Output         :
 * Input/Output   : admin, err
 * Return Value   : ESA_RC
 * Comments       : Platform-dependent operations to be performed
 *                  when API is no longer needed.
 ***************************************************/

typedef ESA_RC APITERM_FUNC_TYP (ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  APITERM_FUNC_TYP   CTSAPITerm;       /* actual function */

typedef APITERM_FUNC_TYP * APITERM_FUNC_PTR; /* pointer to func */

/***************************************************************
 *
 * Services that enable ESA to administer security on the RSS
 *
 **************************************************************/

/****************************************************
 * Procedure Name : CTSSetRSSParams
 * Description    : Set RSS parameters
 * Input          : rss_params, admin
 * Output         : err
 * Input/Output   : addinfo
 * Return Value   : ESA_RC
 * Comments       : RSS-dependent operations to modify
 *                  global RSS parameters.
 ***************************************************/

typedef ESA_RC STRSPRM_FUNC_TYP (RSS_PARAMS_rec_typ   * rss_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  STRSPRM_FUNC_TYP   CTSSetRSSParams;  /* actual function */

typedef STRSPRM_FUNC_TYP * STRSPRM_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSAddUser
 * Description    : Add a new user
 * Input          : User data, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC ADDUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  ADDUSER_FUNC_TYP   CTSAddUser;       /* actual function */

typedef ADDUSER_FUNC_TYP * ADDUSER_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSDelUser
 * Description    : Delete a user
 * Input          : user data, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC DELUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  DELUSER_FUNC_TYP   CTSDelUser;       /* actual function */

typedef DELUSER_FUNC_TYP * DELUSER_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSUpdUser
 * Description    : Update user details
 * Input          : user data, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC UPDUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDUSER_FUNC_TYP   CTSUpdUser;    /* actual function */

typedef UPDUSER_FUNC_TYP * UPDUSER_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSRevokeUser
 * Description    : Revoke or restore a user
 * Input          : user data, addinfo, admin
 * Output         : err
 * Input/Output   : addinfo
 * Return Value   : ESA_RC
 * Comments       : opcode (Revoke or RESTORE) is in the
 *                  user_params structure
 ***************************************************/

typedef ESA_RC REVUSER_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  REVUSER_FUNC_TYP   CTSRevokeUser;    /* actual function */

typedef REVUSER_FUNC_TYP * REVUSER_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSUpdPassword
 * Description    : Update password and its parameters
 * Input          : user struct, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC UPDPASS_FUNC_TYP (USER_PARAMS_rec_typ  * user_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDPASS_FUNC_TYP   CTSUpdPassword;/* actual function */

typedef UPDPASS_FUNC_TYP * UPDPASS_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSAddUG
 * Description    : Add a user group
 * Input          : ug, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 * Comments       : No users are initally connected to the group.
 ***************************************************/

typedef ESA_RC ADDUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  ADDUG_FUNC_TYP   CTSAddUG; /* actual function */

typedef ADDUG_FUNC_TYP * ADDUG_FUNC_PTR;  /* pointer to func */

/****************************************************
 * Procedure Name : CTSDelUG
 * Description    : Delete a user group
 * Input          : ug, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC DELUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  DELUG_FUNC_TYP   CTSDelUG; /* actual function */

typedef DELUG_FUNC_TYP * DELUG_FUNC_PTR;  /* pointer to func */

/****************************************************
 * Procedure Name : CTSUpdUG
 * Description    : Update user group details
 * Input          : ug, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC UPDUG_FUNC_TYP (UG_PARAMS_rec_typ    * ug_params,
                               ADDINFO_rec_typ      * addinfo,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  UPDUG_FUNC_TYP   CTSUpdUG; /* actual function */

typedef UPDUG_FUNC_TYP * UPDUG_FUNC_PTR;     /* pointer to func */

/****************************************************
 * Procedure Name : CTSAddUserToUG
 * Description    : Connect user to user group
 * Input          : u2ug_params, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC ADDU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  ADDU2UG_FUNC_TYP   CTSAddUserToUG;/* actual function */

typedef ADDU2UG_FUNC_TYP * ADDU2UG_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSDelUserFromUG
 * Description    : Disconnect user from user group
 * Input          : u2ug_params, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC DELU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  DELU2UG_FUNC_TYP   CTSDelUserFromUG;  /* actual */

typedef DELU2UG_FUNC_TYP * DELU2UG_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSUpdUserToUG
 * Description    : Update user to user group connection details
 * Input          : u2ug_params, addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC UPDU2UG_FUNC_TYP (U2UG_PARAMS_rec_typ  * u2ug_data,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  UPDU2UG_FUNC_TYP   CTSUpdUserToUG;   /* actual function */

typedef UPDU2UG_FUNC_TYP * UPDU2UG_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSAddACE
 * Description    : Connect user/ug to a resource
 * Input          : Resource, New ACE,
 *                  new ACE addinfo,
 *                  place of new ace, relative ACE,
 *                  relative ACE addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 * Comments       : 1. rel_ace and rel_addinfo are meaningful only
 *                     if ace_place is used.
 *                  2. addinfo contains the permissions.
 ***************************************************/

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

/****************************************************
 * Procedure Name : CTSDelACE
 * Description    : Disconnect user/group from resource
 * Input          : resource, ACE, ACE addinfo, admin
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 * Comments       : 1. addinfo contains the current permissions.
 ***************************************************/

typedef ESA_RC DELACE_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ACE_rec_typ          * ace,
                                ADDINFO_rec_typ      * addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  DELACE_FUNC_TYP   CTSDelACE;       /* actual function */

typedef DELACE_FUNC_TYP * DELACE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name : CTSUpdACE
 * Description    : Update user/group to resource connection
 * Input          : resource, new ace, new ACE addinfo,
 *                  old ace, old ACE addinfo
 * Output         : err
 * Input/Output   :
 * Return Value   : ESA_RC
 * Comments       : 1. addinfo structs contain the permissions.
 ***************************************************/

typedef ESA_RC UPDACE_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ACE_rec_typ          * new_ace,
                                ADDINFO_rec_typ      * new_addinfo,
                                ACE_rec_typ          * old_ace,
                                ADDINFO_rec_typ      * old_addinfo,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  UPDACE_FUNC_TYP   CTSUpdACE;       /* actual function */

typedef UPDACE_FUNC_TYP * UPDACE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSAddRes
 * Description   : Creadts a resource with non-ACL info
 * Input         : resource, addinfo_data
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC ADDRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo_data,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  ADDRES_FUNC_TYP   CTSAddRes;       /* actual function */

typedef ADDRES_FUNC_TYP * ADDRES_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSDelRes
 * Description   : Deletes a resource with it's ACL info
 * Input         : resource, addinfo_data.
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC DELRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo_data,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  DELRES_FUNC_TYP   CTSDelRes;       /* actual function */

typedef DELRES_FUNC_TYP * DELRES_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSUpdRes
 * Description   : Update resource with non-ACL info
 * Input         : resource
 *                 addinfo_data (data to update)
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC UPDRES_FUNC_TYP (RES_PARAMS_rec_typ   * res_params,
                                ADDINFO_rec_typ      * addinfo_data,
                                ADMIN_PARAMS_rec_typ * admin_params,
                                ERR_STRUCT_rec_typ   * err);

extern  UPDRES_FUNC_TYP   CTSUpdRes;       /* actual function */

typedef UPDRES_FUNC_TYP * UPDRES_FUNC_PTR; /* pointer to func */

/***************************************************************
 *
 * Services that enable ESA to notify the USAAPI about
 * transaction (initiated by the ESS) completion for the sake of
 * synchronising the offline database or any other reason.
 *
 **************************************************************/

/****************************************************
 * Procedure Name: CTSTransactionEvent
 * Description   : Notify USAAPI of ESS transaction completion
 * Input         : Object type , container , user , group
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC TRNSEVNT_FUNC_TYP (INTERCEPT_obj_typ       object_type ,
                                  OE_typ                  oe ,
                                  USER_typ                user,
                                  UG_typ                  ug ,
                                  TRNSEVNT_UPCON_FLAG_typ connflag ,
                                  ADMIN_PARAMS_rec_typ  * admin_params,
                                  ERR_STRUCT_rec_typ    * err);

extern  TRNSEVNT_FUNC_TYP   CTSTransactionEvent;/* actual function */

typedef TRNSEVNT_FUNC_TYP * TRNSEVNT_FUNC_PTR; /* pointer to func */

/***************************************************************
 *
 * Services that enable ESA to request information from the RSS
 *
 **************************************************************/

/****************************************************
 * Procedure Name : CTSGetRSSParams
 * Description    : Get RSS parameters
 * Input          : addinfo, admin
 * Output         : rss_params, err
 * Input/Output   :
 * Return Value   : ESA_RC
 ***************************************************/

typedef ESA_RC GTRSPRM_FUNC_TYP (RSS_PARAMS_rec_typ   * rss_params,
                                 ADDINFO_rec_typ      * addinfo,
                                 ADMIN_PARAMS_rec_typ * admin_params,
                                 ERR_STRUCT_rec_typ   * err);

extern  GTRSPRM_FUNC_TYP   CTSGetRSSParams;  /* actual function */

typedef GTRSPRM_FUNC_TYP * GTRSPRM_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSGetUsers
 * Description   : Get users
 * Input         : mode          - GET_ALL,
 *                                 GET_MANY (one or many),
 *                                 GET_WILD (wildcards)
 *                                 GET_SUBTREE (containers)
 *                                 GET_FREE_HANDLE (see below)
 *                 oe              container (if mode - GET_SUBTREE)
 *                 max_users     - # of elements in user_params,
 *                                 objs_exist and addinfo arrays
 *                 num_users_in  - # of elements in user_params_in
 *                 user_params_in- array of num_users_in, filled with
 *                                 users requested.
 *                 admin_params   -
 * Output        : actual_num   - # of users returned
 *                 have_more    - HAVE_MORE if more users, else NO_MORE
 *                 err          - error indication, message, etc.
 *                 objs_exist   - array of max_users:
 *                                OBJ_EXIST if user exists, else
 *                                OBJ_NOT_EXIST.
 *                 user_params  - array of max_users:
 *                                callee fills with users returned
 *  Input/Output : addinfo      - array of max_users pointers:
 *                                add.info per user, Caller puts
 *                                requested keywords, callee returns
 *                                actual add.info.
 *                 handle       - NULL on first call, filled by callee,
 *                                used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 * Comments      : Caller must reset I/O params to their initial values
 *                 when using subsequent calls (if HAVE_MORE).
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSGetUGs
 * Description   : Get user groups
 * Input         : mode         - GET_ALL,
 *                                GET_MANY,
 *                                GET_WILD (wildcard - not implemented),
 *                                GET_SUBTREE (containers)
                                  GET_FREE_HANDLE (see below)
 *                 oe             container (if mode - GET_SUBTREE)
 *                 max_ugs      - # of elements in ug_params & addinfo
 *                                arrays.
 *                 num_ugs_in   - # of elements in ug_params_in.
 *                 ug_params_in - array of num_ugs_in, filled with
 *                                ugs requested.
 *                 admin_params -
 * Output        : actual_num   - # of ugs returned.
 *                 have_more    - HAVE_MORE if more ugs, else NO_MORE.
 *                 err          - error indication, message, etc.
 *                 objs_exist   - array of max_ugs:
 *                                OBJ_EXIST if ug exists, else
 *                                OBJ_NOT_EXIST.
 *                 ug_params    - array of max_ugs:
 *                                callee fills with groups returned.
 * Input/Output  : addinfo      - array of max_users pointers:
 *                                add.info per group, Caller puts
 *                                requested keywords, callee returns
 *                                actual add.info.
 *                 handle       - NULL on first call, filled by callee,
 *                                used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSGetConns
 * Description   : Get user-group to user connections
 * Input         : mode         - GET_ALL    - get all connections
 *                                     (all users of all groups)
 *                                GET_MANY_UGS - get connections of
 *                                               supplied ugs
 *                                GET_MANY_USERS - get connections of
 *                                                 supplied users
 *                                GET_MANY_CONNS - get connections for
 *                                                 supplied pairs.
 *                                GET_FREE_HANDLE (see below)
 *                 max_conns    - # of elements in ugs,
 *                                users, obj_exist & addinfo
 *                                arrays
 *                 admin_params -
 *                 num_ugs_in   - # of input ugs
 *                 num_users_in - # of input users
 *                 ugs_in       - array of num_ugs_in.
 *                                Caller fills with ugs requested
 *                                (if not GET_ALL);
 *                 users_in     - array of num_users_in.
 *                                Caller fills with users requested.
 * Output        : actual_num   - # of connections returned
 *                 have_more    - HAVE_MORE if more conns, else NO_MORE
 *                 u2ug_params  - details of each connection
 *                 objs_exist   - array of max_conns:
 *                                OBJ_EXIST if connection exists, else
 *                                OBJ_NOT_EXIST.
 *                 addinfo      - array of max_conns pointers,
 *                                one add.info per connection
 *                 err          - error indication, message, etc.
 * Input/Output  : handle       - NULL on first call, filled by callee,
 *                                used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 * Comments      : 1. Data is returned as triplets -
 *                    u2ug_params, add.info, obj_exist
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSGetRes
 * Description   : Get resource RSS info
 * Input         : mode          - GET_FREE_HANDLE, otherwise ignored
 *                 max_ress      - # of elements in res_params &
 *                                 addinfo_out arrays
 *                 admin_params  -
 * Output        : actual_num    - # of resources returned
 *                 have_more     - HAVE_MORE if more resources
 *                 res_params    - Returned resources
 *                 err           - error indication, message, etc.
 * Input/Output  : addinfo       - array of max_ress pointers:
 *                                 add.info per resource, caller puts
 *                                 requested keywords, callee returns
 *                                 actual add.info, per resource.
 *                 handle        - NULL on first call, filled by callee,
 *                                 used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 * Comments      : 1. Data is returned as triplets -
 *                    resource, add.info, objs_exist
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSGetResACL
 * Description   : Get one resource's ACL
 * Input         : mode         - GET_FREE_HANDLE, other values ignored
 *                 max_aces     - # of ACEs
 *                 admin_params -
 * Output        : actual_num   - # of ACEs returned
 *                 have_more    - HAVE_MORE if more conns, else NO_MORE
 *                 ace_params   - contains: user, group, attributes
 *                 err          - error indication, message, etc.
 * Input/Output  : addinfo      - array of max_aces pointers
 *                                add.info per ACE, caller puts
 *                                requested keywords,
 *                                callee returns actual add.info, per
 *                                ACE.
 *                 handle       - NULL on first call, filled by callee,
 *                                used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 * Comments      : 1. Data is returned as pairs -
 *                    ACE, addinfo (=permissions)
 ****************************************************/

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

/***************************************************************
 *
 * Services that enable the RSS to send information to ESA
 *
 **************************************************************/

/****************************************************
 * Procedure Name : CTSInterceptorInit
 * Description    : RSS functions initialization for the offline
 *                  interceptor.
 * Input          : rss_name - RSS name when available.
 *                             NULL if not available
 *                  rss_type - Mandatory information.
 *                  handle   - NULL on first call, filled by callee,
 *                             used by callee to store all the
 *                             initialization information.
 *                  intercept_typ - OFLI / ONLI
 * Output        : Time Range:
 *                  start_date
 *                  start_time The date and time of the
 *                             first entry that the interceptor
 *                             should start with.
 *                  end_date
 *                  end_time   The date and time of the last entry.
 *                             If fields are empty, then the last entry
 *                             is the last in the log or file.
 *
 *                 CTSAMSG stuff
 * Return Value  : ESA_RC / ESA_FATAL
 * Comments      : RSS dependent operations to be performed
 *                 prior to RSS function call:
 *                 Open the queue.
 *                 ESA_DIAG initialization.
 *                 CTSAMSG initialization.
 *                 Get the start date and time
 *                     off line interceptor should start
 *                     with.
 *                 rslogevnt Off Line Intercept started.
 *                 OS_CS_lock on the handled rss
 **********************************************************/

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

typedef RSINIT_FUNC_TYP * RSINIT_FUNC_PTR;    /* pointer to func */


/****************************************************
 * Procedure Name:CTSApiProcInit
 * Description   :PROC functions initialization for the Api utility
 * Input         
 *                 CTSAMSG stuff
 * Return Value  : ESA_RC / ESA_FATAL
 *                 ESA_DIAG initialization.
 *                 CTSAMSG initialization.
 **********************************************************/
typedef ESA_RC PROCINIT_FUNC_TYP (char                  * ProgramName,
                                  char                  * ProgramMain, 
                                  int                     argc_prm,    
                                  char                 ** argv_prm,  
                                  void                 ** EncrHndl,   
                                  void                 ** ProcHndl,  
                                  ADMIN_PARAMS_rec_typ  * admin_prm);

extern  PROCINIT_FUNC_TYP CTSApiProcInit; /* actual function */

typedef PROCINIT_FUNC_TYP * PROCINIT_FUNC_PTR;    /* pointer to func */

/****************************************************
 * Procedure Name : CTSInterceptorTerm
 * Description    : RSS functions termination for the offline
 *                  interceptor.
 *
 * Input          : handle   - Free by callee,
 *                  intercept- OFLI / ONLI
 *                  exit_status - The interceptor's exit status.
 *                  Time Range:
 *                    start_date
 *                    start_time The date and time of the
 *                               first entry that the interceptor
 *                               should start with.
 *                    end_date
 *                    end_time   The date and time of the last entry.
 *                               If fields are empty, then the last
 *                               entry is the last in the log or file.
 * Output         :
 * Return Value   : ESA_RC / ESA_FATAL
 * Comments       : RSS function cleanup operations.
 *                  Close the Queue.
 *                  CTSAMSG termination.
 *                  rslogevnt Off Line Intercept end
 *                  OS_CS_unlock
 ***************************************************/

typedef ESA_RC RSTERM_FUNC_TYP (void                  ** handle,
                                INTERCEPTOR_typ          intercept_typ,
                                ESA_RC                   exit_status,
                                TIME_RANGE_rec_typ     * time_range,
                                ADMIN_PARAMS_rec_typ   * admin_params);

extern  RSTERM_FUNC_TYP   CTSInterceptorTerm; /* actual function */

typedef RSTERM_FUNC_TYP * RSTERM_FUNC_PTR;    /* pointer to func */

/****************************************************
 * Procedure Name : CTSApiProcTerm
 * Description    : RSS functions termination for the Api utility
 *                  exit_status - The process's exit status.
 * Output         :
 * Return Value   : ESA_RC / ESA_FATAL
 * Comments       : RSS function cleanup operations.
 *                  CTSAMSG termination.
 ***************************************************/

typedef ESA_RC PROCTERM_FUNC_TYP (ESA_RC    exit_status,
                                  void   ** EncrHndl,   
                                  void   ** ProcHndl);  

extern  PROCTERM_FUNC_TYP CTSApiProcTerm; /* actual function */

typedef PROCTERM_FUNC_TYP * PROCTERM_FUNC_PTR;    /* pointer to func */

/****************************************************
 * Procedure Name: CTSParamsModEvent
 * Description   : Notify that RSS parameters have changed
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSPRMMOD_FUNC_TYP (RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSPRMMOD_FUNC_TYP   CTSParamsModEvent;   /* actual function */

typedef RSPRMMOD_FUNC_TYP * RSPRMMOD_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSUserRevokedEvent
 * Description   : User was disabled (revoked)
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 user name -
 * Input/Output  : CTSAMSG_params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSUSDIS_FUNC_TYP (RSS_typ                  rss_type,
                                 RSS_typ                  rss_name,
                                 void                   * handle,
                                 USER_typ                 user,
                                 ADMIN_PARAMS_rec_typ * admin_prm);

extern  RSUSDIS_FUNC_TYP   CTSUserRevokedEvent; /* actual function */

typedef RSUSDIS_FUNC_TYP * RSUSDIS_FUNC_PTR;    /* pointer to func */

/****************************************************
 * Procedure Name: CTSPassModEvent
 * Description   : User's password was modified
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 user     - user name
 *                 password - new password
 *                 additional info
 * Input/Output  : CTSAMSG params
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSPWDMOD_FUNC_TYP (RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  USER_typ                 user,
                                  PASSWD_typ               passwd,
                                  ADDINFO_rec_typ        * addinfo,
                                  ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSPWDMOD_FUNC_TYP   CTSPassModEvent;   /* actual function */

typedef RSPWDMOD_FUNC_TYP * RSPWDMOD_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSUserEvent
 * Description   : User state changed - user was added, deleted
 *                 or updated.
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 user name   -
 *                 action type - add/del/update
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSUSER_FUNC_TYP (RSS_typ                  rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                USER_typ                 user,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSUSER_FUNC_TYP   CTSUserEvent;    /* actual function */

typedef RSUSER_FUNC_TYP * RSUSER_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSUGEvent
 * Description   : User group state changed - user group was added,
 *                 deleted or updated.
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 user group -
 *                 action type - add/del/update
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSUG_FUNC_TYP (RSS_typ                  rss_type,
                              RSS_typ                  rss_name,
                              void                   * handle,
                              UG_typ                   ug,
                              ACTION_typ               action,
                              ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSUG_FUNC_TYP   CTSUGEvent;    /* actual function */

typedef RSUG_FUNC_TYP * RSUG_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSConnEvent
 * Description   : User to User-Group connection state changed -
 *                 connection was added, deleted or updated.
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 user group  -
 *                 user name   -
 *                 action type - (connect/disconnect/update)
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSU2UG_FUNC_TYP (RSS_typ                  rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                UG_typ                   ug,
                                USER_typ                 user,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSU2UG_FUNC_TYP   CTSConnEvent;    /* actual function */

typedef RSU2UG_FUNC_TYP * RSU2UG_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSOEEvent
 * Description   : OE was added, deleted
 *                 or updated.
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 OE name   -
 *                 action type - add/del/update
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC RSOE_FUNC_TYP   (RSS_typ                  rss_type,
                                RSS_typ                  rss_name,
                                void                   * handle,
                                OE_typ                   oe,
                                ACTION_typ               action,
                                ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSOE_FUNC_TYP   CTSOEEvent;    /* actual function */

typedef RSOE_FUNC_TYP * RSOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSRssStatusEvent
 * Description   : RSS status was changed.
 * Input         : rss_type - Mandatory information.
 *                 rss_name - RSS name when available.
 *                            NULL if not available
 *                 handle   - initialization information
 *                            (e.g. queue file handle)
 *                 rss_status RSS status
 * Output        :
 * Input/Output  : CTSAMSG params
 * Return Value  : ESA_RC
 * Side Effects  :
 ***************************************************/

typedef ESA_RC RSSSTATUS_FUNC_TYP(RSS_typ                  rss_type,
                                  RSS_typ                  rss_name,
                                  void                   * handle,
                                  RSS_STATUS_typ         * rss_status,
                                  ADMIN_PARAMS_rec_typ   * admin_prm);

extern  RSSSTATUS_FUNC_TYP CTSRssStatusEvent;    /* actual function */

typedef RSSSTATUS_FUNC_TYP * RSSSTATUS_FUNC__PTR;/* pointer to func */

/****************************************************
 * Procedure Name: CTSRSSLogin
 * Description   : log in under the permissions and
 *                 limitations of the requsted administrator.
 * Input         : RSS name
 *                 administrator name, group AND password
 * Output        : CTSAMSG error structure
 * Input/Output  : admin, err
 *                 handle - NULL on first call, filled by callee.
 * Return Value  : ESA_OK     upon success
 *                 ESA_FATAL  on any fail situation
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSRSSLogout
 * Description   : logout from the last OS_CS_login
 * Input         : RSS name
 *                 administrator name and group
 *                 CTSAMSG stuff
 * Output        : CTSAMSG error structure
 * Input/Output  : handle.
 * Return Value  : ESA_OK     upon success
 *                 ESA_FATAL  on any fail situation
 * Comments      :
 ****************************************************/

typedef ESA_RC RSS_LOGOUT_FUNC_TYP (RSS_typ                rss_name,
                                    USER_typ               admin,
                                    UG_typ                 admin_group,
                                    LOGIN_MODE_typ         login_mode,
                                    void                ** handle,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  RSS_LOGOUT_FUNC_TYP   CTSRSSLogout;        /* actual function */

typedef RSS_LOGOUT_FUNC_TYP * RSS_LOGOUT_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSRSSCheck
 * Description   : checks if RSS is alive
 * Input         : RSS name
 *                 CTSAMSG stuff
 * Output        : status RSS_UP if rss is alive
 *                        RSS_DOWN if rss is down
 *                 CTSAMSG error structure
 * Return Value  : ESA_OK     upon success
 *                 ESA_FATAL  on any fail situation
 ****************************************************/

typedef ESA_RC RSS_CHECK_FUNC_TYP (RSS_typ                rss_name,
                                   RSS_STATUS_typ       * status,
                                   ADMIN_PARAMS_rec_typ * admin_params,
                                   ERR_STRUCT_rec_typ   * err);

extern  RSS_CHECK_FUNC_TYP   CTSRSSCheck;        /* actual function */

typedef RSS_CHECK_FUNC_TYP * RSS_CHECK_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSInterceptorStart
 * Description   : Start the offline interceptor.
 * Input         : RSS name, host name
 * Output        : None
 * Input/Output  : admin, err
 * Return Value  : ESA_OK     upon success
 *                 ESA_FATAL  on any fail situation
 ****************************************************/

typedef ESA_RC RSS_START_INTERCEPT_FUNC_TYP (
        RSS_typ                rss_name,
        char                 * host_name,
        ADMIN_PARAMS_rec_typ * admin_params,
        ERR_STRUCT_rec_typ   * err);

extern  RSS_START_INTERCEPT_FUNC_TYP   CTSInterceptorStart;

typedef RSS_START_INTERCEPT_FUNC_TYP * RSS_START_INTERCEPT_FUNC_PTR;

/********************************************/
/*  Container-related functions             */
/********************************************/

/****************************************************
 * Procedure Name: CTSAddOE
 * Description   : Create new container
 * Input         : container, addinfo_data, admin_params.
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC ADDOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo_data,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  ADDOE_FUNC_TYP   CTSAddOE;       /* actual function */

typedef ADDOE_FUNC_TYP * ADDOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSDelOE
 * Description   : Delete container
 * Input         : container, addinfo_data, admin_params.
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC DELOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo_data,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  DELOE_FUNC_TYP   CTSDelOE;       /* actual function */

typedef DELOE_FUNC_TYP * DELOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSUpdOE
 * Description   : Update container
 * Input         : container, addinfo_data, admin_params.
 * Output        : None
 * Input/Output  : None
 * Return Value  : ESA_RC
 ***************************************************/

typedef ESA_RC UPDOE_FUNC_TYP (OE_PARAMS_rec_typ    * oe_params,
                               ADDINFO_rec_typ      * addinfo_data,
                               ADMIN_PARAMS_rec_typ * admin_params,
                               ERR_STRUCT_rec_typ   * err);

extern  UPDOE_FUNC_TYP   CTSUpdOE;       /* actual function */

typedef UPDOE_FUNC_TYP * UPDOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSGetOEs
 * Description   : Get containers
 * Input         : mode          - GET_ALL,
 *                                 GET_MANY (one or many),
 *                                 GET_WILD (wildcards)
 *                                 GET_FREE_HANDLE (see below)
 *                 max_oe        - # of elements in oe_params,
 *                                 objs_exist and addinfo arrays
 *                 num_oe_in     - # of elements in oe_params_in
 *                 oe_params_in  - array of num_oe_in, filled with
 *                                 OEs requested.
 *                 admin_params   -
 * Output        : actual_num   - # of OEs returned
 *                 have_more    - HAVE_MORE if more OEs, else NO_MORE
 *                 err          - error indication, message, etc.
 *                 objs_exist   - array of max_oe:
 *                                OBJ_EXIST if OE exists, else
 *                                OBJ_NOT_EXIST.
 *                 oe_params    - array of max_oe:
 *                                callee fills with OES returned
 *  Input/Output : addinfo      - array of max_OE pointers:
 *                                add.info per OE, Caller puts
 *                                requested keywords, callee returns
 *                                actual add.info.
 *                 handle       - NULL on first call, filled by callee,
 *                                used by callee to keep track.
 * Return Value  : ESA_RC
 * Side Effects  : The function may allocate memory for internal usage
 *                 and return pointer to it in *handle.
 *                 Memory will be freed when function returns
 *                 have_more==NO_MORE.
 *                 If caller stop calling the function before NO_MORE,
 *                 he MUST call the function with mode=GET_FREE_HANDLE
 *                 to free the memory.
 * Comments      : Caller must reset I/O params to their initial values
 *                 when using subsequent calls (if HAVE_MORE).
 ****************************************************/

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

/****************************************************
 * Procedure Name: CTSIsUserInOE
 * Description   : User belong to the OE
 * Input         : user_type    - User name.
 *                 oe_mask      - OE mask.
 *                 admin_params -
 * Output        :
 * Return Value  : ESA_OK     User in OE
 *                 ESA_EOF    User not in OE
 *                 ESA_ERR    on any other situation
 ***************************************************/

typedef ESA_RC ISUSERINOE_FUNC_TYP (USER_typ               user,
                                    OE_typ                 oe_mask,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISUSERINOE_FUNC_TYP   CTSIsUserInOE;       /* actual function */

typedef ISUSERINOE_FUNC_TYP * ISUSERINOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSIsUGInOE
 * Description   : Group belong to the OE
 * Input         : ug_type      - Group name.
 *                 oe_mask      - OE mask.
 *                 admin_params -
 * Output        :
 * Return Value  : ESA_OK     Group in OE
 *                 ESA_EOF    Group not in OE
 *                 ESA_ERR    on any other situation
 ***************************************************/

typedef ESA_RC ISUGINOE_FUNC_TYP   (UG_typ                 ug,
                                    OE_typ                 oe_mask,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISUGINOE_FUNC_TYP   CTSIsUGInOE;       /* actual function */

typedef ISUGINOE_FUNC_TYP * ISUGINOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSIsOEInOE
 * Description   : OE belong to the OE
 * Input         : oe_name      - OE name.
 *                 oe_mask      - OE mask.
 *                 admin_params -
 * Output        :
 * Return Value  : ESA_OK     OE in OE
 *                 ESA_EOF    OE not in OE
 *                 ESA_ERR    on any other situation
 ***************************************************/

typedef ESA_RC ISOEINOE_FUNC_TYP   (OE_typ                 oe_name,
                                    OE_typ                 oe,
                                    ADMIN_PARAMS_rec_typ * admin_params,
                                    ERR_STRUCT_rec_typ   * err);

extern  ISOEINOE_FUNC_TYP   CTSIsOEInOE;       /* actual function */

typedef ISOEINOE_FUNC_TYP * ISOEINOE_FUNC_PTR; /* pointer to func */

/****************************************************
 * Procedure Name: CTSIsMaskMatch
 * Description   : Object is matches a Mask
 * Input         : object.
 *                 .
 *                 admin_params -
 * Output        :
 * Return Value  : ESA_OK     Mask is Match
 *                 ESA_EOF    Mask is not Match
 *                 ESA_ERR    on any other situation
 ***************************************************/

typedef ESA_RC ISMASKMATCH_FUNC_TYP (
        char                 * object,
        char                 * mask,
        OBJECT_TYPE_typ        object_type,
        MASK_TYPE_typ          mask_type,
        ADMIN_PARAMS_rec_typ * admin_params,
        ERR_STRUCT_rec_typ   * err);

extern  ISMASKMATCH_FUNC_TYP   CTSIsMaskMatch;      /* actual function*/

typedef ISMASKMATCH_FUNC_TYP * ISMASKMATCH_FUNC_PTR;/*pointer to func*/

/********************************************/
/*  API function pointers structure         */
/********************************************/

typedef  struct  S_FUNC_PTR {

  APIINIT_FUNC_PTR              apiinit_ptr;
  APITERM_FUNC_PTR              apiterm_ptr;
  STRSPRM_FUNC_PTR              strsprm_ptr;
  ADDUSER_FUNC_PTR              adduser_ptr;
  UPDUSER_FUNC_PTR              upduser_ptr;
  DELUSER_FUNC_PTR              deluser_ptr;
  REVUSER_FUNC_PTR              revuser_ptr;
  UPDPASS_FUNC_PTR              updpass_ptr;
  ADDUG_FUNC_PTR                addug_ptr;
  UPDUG_FUNC_PTR                updug_ptr;
  DELUG_FUNC_PTR                delug_ptr;
  ADDU2UG_FUNC_PTR              addu2ug_ptr;
  UPDU2UG_FUNC_PTR              updu2ug_ptr;
  DELU2UG_FUNC_PTR              delu2ug_ptr;
  ADDACE_FUNC_PTR               addace_ptr;
  DELACE_FUNC_PTR               delace_ptr;
  UPDACE_FUNC_PTR               updace_ptr;
  ADDRES_FUNC_PTR               addres_ptr;
  DELRES_FUNC_PTR               delres_ptr;
  UPDRES_FUNC_PTR               updres_ptr;
  GTRSPRM_FUNC_PTR              gtrsprm_ptr;
  GTUSERS_FUNC_PTR              gtusers_ptr;
  GETUGS_FUNC_PTR               getugs_ptr;
  GTUG2UC_FUNC_PTR              gtug2uc_ptr;
  GETRES_FUNC_PTR               getres_ptr;
  GTRSACL_FUNC_PTR              gtrsacl_ptr;
  RSS_LOGIN_FUNC_PTR            rss_login_ptr;
  RSS_LOGOUT_FUNC_PTR           rss_logout_ptr;
  RSS_CHECK_FUNC_PTR            rss_check_ptr;
  RSS_START_INTERCEPT_FUNC_PTR  rss_start_intercept_ptr;
  ADDOE_FUNC_PTR                addoe_ptr;
  UPDOE_FUNC_PTR                updoe_ptr;
  DELOE_FUNC_PTR                deloe_ptr;
  GETOES_FUNC_PTR               getoes_ptr;
  ISUSERINOE_FUNC_PTR           isuserinoe_ptr;
  ISUGINOE_FUNC_PTR             isuginoe_ptr;
  ISOEINOE_FUNC_PTR             isoeinoe_ptr;
  ISMASKMATCH_FUNC_PTR          ismaskmatch_ptr;
  TRNSEVNT_FUNC_PTR             trnsevnt_ptr ;
  APIVERSION_FUNC_PTR           apiversion_ptr;

  void                         *Reserved10 ;
  void                         *Reserved9 ;
  void                         *Reserved8 ;
  void                         *Reserved7 ;
  void                         *Reserved6 ;
  void                         *Reserved5 ;
  void                         *Reserved4 ;
  void                         *Reserved3 ;
  void                         *Reserved2 ;
  void                         *Reserved1 ;

} FUNC_PTR_rec_typ,  * FUNC_PTR_rec_ptr;

#define FUNC_PTR_ARRAY_SIZE \
    (sizeof (FUNC_PTR_rec_typ) / sizeof (APIINIT_FUNC_PTR))

/* RSS Limits */
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

} RSS_LIMITS_rec_typ, * RSS_LIMITS_rec_ptr;

/****************************************************
 * Procedure Name: CTSAPILoad
 * Description   : Load api functions
 * Input         : RSS name and type
 *                 CTSAMSG stuff
 * Output        : func ptr structure
 *                 CTSAMSG error structure
 * Return Value  : ESA_OK     upon success
 *                 ESA_FATAL  on any fail situation
 ****************************************************/

typedef ESA_RC API_LOAD_FUNC_TYP (
        RSS_typ                rss_name,
        FUNC_PTR_rec_typ     * func_ptr,
        RSS_LIMITS_rec_typ   * rss_limits_ptr,
        ADMIN_PARAMS_rec_typ * admin_params,
        ERR_STRUCT_rec_typ   * err);

extern  API_LOAD_FUNC_TYP   CTSAPILoad;        /* actual function */

typedef API_LOAD_FUNC_TYP * API_LOAD_FUNC_PTR; /* pointer to func */


/*#ifdef  WINNT*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

/*#endif*/ /* WINNT */

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
