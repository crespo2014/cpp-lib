/**********************************************************************
*
*   H Source      : apidefs.h
*   Description   : Definitions for Agent interfaces to USA-API and
*                   interceptors
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APIDEFS_H_INCLUDED
#define APIDEFS_H_INCLUDED

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains definitions for the use of USA-API   == */
/* == and user-written interceptors.                                 == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************/
/*  Define time and date formats            */
/********************************************/

#define DATE_LEN             8
#define TIME_LEN             6
#define TIMESTR_LEN         10     

typedef char TIME_typ [ TIME_LEN + 1 ];  /* HHMMSS   */
typedef char DATE_typ [ DATE_LEN + 1 ];  /* YYYYMMDD */

/********************************************/
/*  Length values for entity names          */
/********************************************/

#define RSS_NAME_LEN         32
#define LOGENT_LEN         2560
#define RSS_VERS_LEN         50
#define MAX_RSS_EUID_LEN          64 
#define MAX_RSS_KEY_LEN           RSS_NAME_LEN + HOST_NAME_LENGTH + 3

#define  MAX_RSS_RESTYPE_NAME_LEN  64*3
#define  MAX_RSS_OE_NAME_LEN       256*3 
#define  MAX_RSS_ACE_OE_NAME_LEN   MAX_RSS_OE_NAME_LEN + HOST_NAME_LENGTH + 3
#define  MAX_RSS_USER_NAME_LEN     256*3
#define  MAX_RSS_USER_NAME_ANSI_LEN  256
#define  MAX_ADMIN_NAME_ANSI_LEN   256
#define  MAX_ADMIN_GROUP_ANSI_LEN  256 
#define  MAX_ADMIN_NAME_LEN        256*3
#define  MAX_ADMIN_GROUP_LEN       256*3 
#define  MAX_RSS_ACE_USER_NAME_LEN MAX_RSS_USER_NAME_LEN + HOST_NAME_LENGTH + 3
#define  MAX_RSS_UG_NAME_LEN       256*3
#define  MAX_RSS_ACE_UG_NAME_LEN   MAX_RSS_UG_NAME_LEN + HOST_NAME_LENGTH + 3
#define  MAX_RSS_RESOURCE_NAME_LEN 256*3
#define  MAX_RSS_CNN_LEN           256*3
#define  MAX_RSS_PASSWD_LEN        32*3 
#define  MAX_RSS_PASSWD_ANSI_LEN   32 

/********************************************/
/*  typedefs for entity names               */
/********************************************/

typedef char OE_typ           [ MAX_RSS_OE_NAME_LEN + 1       ];
typedef char ACE_OE_typ       [ MAX_RSS_ACE_OE_NAME_LEN + 1   ]; 
typedef char RSS_typ          [ RSS_NAME_LEN + 1              ];
typedef char ADMIN_typ        [ MAX_ADMIN_NAME_LEN + 1        ];
typedef char USER_typ         [ MAX_RSS_USER_NAME_LEN + 1     ];
typedef char EUID_typ         [ MAX_RSS_EUID_LEN + 1          ];
typedef char ACE_USER_typ     [ MAX_RSS_ACE_USER_NAME_LEN + 1 ];
typedef char UG_typ           [ MAX_RSS_UG_NAME_LEN + 1       ];
typedef char ADMIN_UG_typ     [ MAX_ADMIN_GROUP_LEN + 1       ];
typedef char ACE_UG_typ       [ MAX_RSS_ACE_UG_NAME_LEN + 1   ]; 
typedef char RESOURCE_typ     [ MAX_RSS_RESOURCE_NAME_LEN + 1 ];
typedef char RESTYPE_typ      [ MAX_RSS_RESTYPE_NAME_LEN + 1  ];
typedef char LOGENT_typ       [ LOGENT_LEN + 1                ];
typedef char RSS_vers_typ     [ RSS_VERS_LEN + 1              ];
typedef char PASSWD_typ       [ MAX_RSS_PASSWD_LEN + 1        ];
typedef char TIMESTAMP_typ    [ TIMESTR_LEN + 1               ];
typedef char CNN_OBJ_typ      [ MAX_RSS_CNN_LEN + 1           ];
typedef char RSS_KEY_typ      [ MAX_RSS_KEY_LEN + 1           ];

typedef char ADMIN_ANSI_typ     [ MAX_ADMIN_NAME_ANSI_LEN + 1];
typedef char ADMIN_UG_ANSI_typ  [ MAX_ADMIN_GROUP_ANSI_LEN + 1];
typedef char PASSWD_ANSI_typ    [ MAX_RSS_PASSWD_ANSI_LEN + 1];
typedef char USER_ANSI_typ       [ MAX_RSS_USER_NAME_ANSI_LEN + 1 ];

typedef union /* Defines a general object that can contain ANY CTSA object */
{
   OE_typ              OE;
   ACE_OE_typ          ACE_OE;
   RSS_typ             RSS;
   USER_typ            USER;
   ACE_USER_typ        ACE_USER;
   UG_typ              UG;
   ACE_UG_typ          ACE_UG;
   RESOURCE_typ        RESOURCE;
   RESTYPE_typ         RESTYPE;
   CNN_OBJ_typ         CNN;
   RSS_KEY_typ         RSS_KEY;
   char                unknown[1];
} SEC_OBJ_typ;


/********************************************/
/*  Typedefs for Admin Params rec typ       */
/********************************************/

typedef enum {
   SERVICE_UNDEFINED,               
   SERVICE_GET_OBJECT,       /* Get object details - for single sync (F) */
   SERVICE_SET_OBJECT,       /* Update object details                (T) */
   SERVICE_GLOBAL_SYNC,      /* Performing global sync               (P) */
   SERVICE_DOWNLOAD,         /* Performing download                  (D) */
   SERVICE_ADMIN,            /* Administrator update                 (A) */
   SERVICE_INTERCEPT_GET,    /* Get object performed for interception(U) 
	                                 (called from notification server)*/
   SERVICE_OFFLINE_INTERCEPTOR,  /* Performing Offline interceptor   (-) */
   SERVICE_ONLINE_INTERCEPTOR,   /* Performing Online interceptor    (-) */
   SERVICE_PASSWORD_INTERCEPTOR, /* Performing Password interceptor  (-) */
   SERVICE_AGENT_INIT,       /* USA-API functions called when agent  (S)
   								     is initialized                   */
   SERVICE_KEYWORDS,         /* Keyword service                      (K) */                  
   SERVICE_INTECEPT_CONFIRM,  /* Performing Interception Confirmations(V) */
   SERVICE_SPECIAL_SET_OBJECT       /* Update object details                (M) */

} SERVICE_typ;

typedef enum {
   TRANSACTION_UNDEFINED= 0,               

   TRANSACTION_INTERCEPT_USER,       /* User Interception                   (U-BA)*/
   TRANSACTION_INTERCEPT_GROUP,      /* User Group Interception             (U-BB)*/
   TRANSACTION_INTERCEPT_CONNECTION, /* Connection Interception             (U-BC)*/
   TRANSACTION_INTERCEPT_RESOURCE,   /* Resource Interception               (U-BD)*/
   TRANSACTION_INTERCEPT_CONTAINER,  /* Container Interception              (U-BH)*/
   TRANSACTION_INTERCEPT_PASSWORD,   /* User Password Interception          (U-PA)*/
   TRANSACTION_INTERCEPT_USER_REVOKE,/* User Revoke Interception            (U-VA)*/
   TRANSACTION_INTERCEPT_RSS,        /* RSS keywords Interception           (U-BA)*/
   TRANSACTION_INTERCEPT_RSS_STATUS, /* Rss StatusInterception              (U-UQ)*/
   TRANSACTION_INTERCEPT_EVENT,      /* LOG Event Interception              (U-AL)*/

   TRANSACTION_GET_USER,             /* Get user Transaction                (F-IA)*/
   TRANSACTION_GET_GROUP,            /* Get user group Transaction          (F-IB)*/
   TRANSACTION_GET_CONTAINER,        /* Get container Transaction           (F-IH)*/
   TRANSACTION_GET_CONNECTION,       /* Get connection Transaction          (F-IC)*/
   TRANSACTION_GET_RESOURCE,         /* Get resource Transaction            (F-ID)*/
   TRANSACTION_GET_RSS_PARAMETERS,   /* Get RSS parameters Transaction      (F-IK)*/
   TRANSACTION_GET_ACL,              /* Get acl Transaction                 (F-IG)*/
   TRANSACTION_GET_RESOURCE_ACL,     /* Get resource and Transaction        (F-IJ)*/

   TRANSACTION_UPDATE_RSS_PARAMETERS,/* Update RSS parameters Transaction   (T-UK)*/
   TRANSACTION_ADD_ADMIN,            /* Add administrator Transaction       (T-AT)*/
   TRANSACTION_DELETE_ADMIN,         /* Delete administrator Transaction    (T-DT)*/
   TRANSACTION_UPDATE_ADMIN,         /* Update administrator Transaction    (T-UT)*/

   TRANSACTION_MOVE_USER,            /* Move user Transaction               (T-MA)*/
   TRANSACTION_RENAME_USER,          /* Rename user Transaction             (T-NA)*/
   TRANSACTION_ADD_USER,             /* Add user Transaction                (T-AA)*/
   TRANSACTION_DELETE_USER,          /* Delete user Transaction             (T-DA)*/
   TRANSACTION_UPDATE_USER,          /* Update user Transaction             (T-UA)*/
   TRANSACTION_UPDATE_PASSWORD,      /* Update user password Transaction    (T-PA)*/
   TRANSACTION_REVOKE_USER,          /* Revoke / Restore user Transaction   (T-VA)*/

   TRANSACTION_MOVE_GROUP,           /* Move user group Transaction         (T-MB)*/
   TRANSACTION_RENAME_GROUP,         /* Rename user group Transaction       (T-NB)*/
   TRANSACTION_ADD_GROUP,            /* Add user group Transaction          (T-AB)*/
   TRANSACTION_DELETE_GROUP,         /* Delete user group Transaction       (T-DB)*/
   TRANSACTION_UPDATE_GROUP,         /* Update user group Transaction       (T-UB)*/

   TRANSACTION_MOVE_CONTAINER,       /* Move container Transaction          (T-MH)*/
   TRANSACTION_RENAME_CONTAINER,     /* Rename container Transaction        (T-NH)*/
   TRANSACTION_ADD_CONTAINER,        /* Add container Transaction           (T-AH)*/
   TRANSACTION_DELETE_CONTAINER,     /* Delete container Transaction        (T-DH)*/
   TRANSACTION_UPDATE_CONTAINER,     /* Update container Transaction        (T-UH)*/

   TRANSACTION_ADD_CONNECTION,       /* Add connection Transaction          (T-AC)*/
   TRANSACTION_DELETE_CONNECTION,    /* Delete connection Transaction       (T-DC)*/
   TRANSACTION_UPDATE_CONNECTION,    /* Update connection Transaction       (T-UC)*/

   TRANSACTION_MOVE_RESOURCE,        /* Move resource Transaction           (T-MD)*/
   TRANSACTION_RENAME_RESOURCE,      /* Rename resource Transaction         (T-ND)*/
   TRANSACTION_ADD_RESOURCE,         /* Add resource Transaction            (T-AD)*/
   TRANSACTION_DELETE_RESOURCE,      /* Delete resource Transaction         (T-DD)*/
   TRANSACTION_UPDATE_RESOURCE,      /* Update resource Transaction         (T-UD)*/

   TRANSACTION_ADD_ACE,              /* Add ace Transaction                 (T-AG)*/
   TRANSACTION_DELETE_ACE,           /* Delete ace Transaction              (T-DG)*/
   TRANSACTION_UPDATE_ACE            /* Update ace Transaction              (T-UG)*/

} TRANSACTION_typ;

/********************************************/
/*  Typedefs for RSS status check           */
/********************************************/

typedef enum {                   
    RSS_DOWN,
    RSS_UP
} RSS_STATUS_typ;

/* For rsslist_get  */
typedef struct S_RSS_rec_typ {
    RSS_typ                rss_name;
    RSS_typ                rss_type;
    RSS_STATUS_typ         rss_status;
} RSS_rec_typ, * RSS_rec_ptr;

/********************************************/
/*  Typedefs for any object                 */
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

/********************************************/
/*  Typedefs for user data                  */
/********************************************/

typedef enum {
    USER_STAT_IGNORED,
    USER_STAT_REVOKED,
    USER_STAT_ACTIVE
} USER_STATUS_typ;

typedef enum {
    INTRUDER_STAT_IGNORED,
    INTRUDER_STAT_LOCKED,
    INTRUDER_STAT_UNLOCKED
} LOCK_STATUS_typ;

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

/* Processing previous default connection indication - 
   Input to USA-API, do not change                      */
typedef enum {
    OLD_DEF_UG_ACT_IGNORED, /* Field value is N/A in this function*/
    OLD_DEF_UG_ACT_DROP,    /* delete old connection              */
    OLD_DEF_UG_ACT_KEEP     /* keep old connection as non-default */
} OLD_DEF_UG_ACTION_typ;

typedef  struct  S_USER_PARAMS {
    USER_typ              user;
    OE_typ                parent_oe;
    UG_typ                def_group;
    PASSWD_typ            passwd;
    PASSWD_LIFE_typ       passwd_life;
    USER_STATUS_typ       rev_status;
    LOCK_STATUS_typ       lock_status;
    USER_ADMIN_typ        user_admin;
    OLD_DEF_UG_ACTION_typ def_ug_action;
    EUID_typ              euid;   
    TIMESTAMP_typ         timestamp;     
}  USER_PARAMS_rec_typ, * USER_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for UG data                    */
/********************************************/

typedef  struct  S_UG_PARAMS {
    UG_typ          group;
    OE_typ          parent_oe;
    UG_typ          parent_group;
    EUID_typ        euid;   
    TIMESTAMP_typ   timestamp;     
} UG_PARAMS_rec_typ, * UG_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for connections                */
/********************************************/

typedef  enum {CNN_U2UG,
               CNN_G2G
} CNN_CLASS_typ;

typedef enum {CNN_ATTR_IGNORED,
              CNN_ATTR_REGULAR,
              CNN_ATTR_DEFAULT_GROUP
} CNN_ATTR_typ;


typedef enum {CNN_BOTH_LOCAL,
              CNN_REMOTE_CONTAINED,   /* The contained object is remote  */
              CNN_REMOTE_CONTAINING   /* The containing object is remote */
} CNN_REMOTE_typ;

typedef enum {CNN_ADM_IGNORED,
              CNN_ADM_NONE,
              CNN_ADM_AUDIT,
              CNN_ADM_ADMIN,
              CNN_ADM_ALL
} CNN_ADMIN_typ;

typedef struct S_CNN_PARAMS {
    CNN_OBJ_typ       containing_object;
    CNN_OBJ_typ       contained_object;
    CNN_ADMIN_typ     cnn_admin_data;
    CNN_ATTR_typ      cnn_attr_data;
    UG_typ            def_group;
    CNN_REMOTE_typ    cnn_remote;
    RSS_KEY_typ       remote_rss_key;
    RSS_typ           remote_rss_type;
    CNN_CLASS_typ     cnn_class ;
    TIMESTAMP_typ     timestamp;     
} CNN_PARAMS_rec_typ;

/********************************************/
/*  Typedefs for OE (container) objects     */
/********************************************/

typedef enum {
    OE_ATTR_IGNORED,
    OE_ATTR_ACL,         /* OE allowed in ACL */
    OE_ATTR_NO_ACL       /* OE not allowed in ACL */
} OE_ATTR_typ;

typedef struct S_OE_PARAMS {
    OE_typ        oe;
    OE_typ        parent;
    OE_ATTR_typ   attr;
    EUID_typ      euid;   
    TIMESTAMP_typ timestamp;     
} OE_PARAMS_rec_typ, * OE_PARAMS_rec_ptr;

/********************************************/
/*  Typedefs for RSS_PARAMS data            */
/********************************************/

typedef short MPL_typ;   /* Minimum Password Length              */
typedef short MPE_typ;   /* Maximum days for Password Expiration */
typedef short MLA_typ;   /* Maximum # of bad Login Allowed       */

typedef struct S_RSS_PARAMS_rec_typ {
    MPL_typ          min_pass_len;
    MPE_typ          max_expire;
    MLA_typ          max_logins;
    RSS_KEY_typ      remote_rss_key;         
    TIMESTAMP_typ    timestamp;     
} RSS_PARAMS_rec_typ, * RSS_PARAMS_rec_ptr;

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

/*********************************************************
 *  typedef for action:                                  *
 *  unknown, add, update, delete, revoke, passwd_updated *
 ********************************************************/

typedef enum {
    ACT_UNKNOWN,
    ACT_ADD,
    ACT_UPDATE,
    ACT_DELETE,
    ACT_REVOKE,   
    ACT_PWD_UPD,  
    ACT_CONN_UPD,
    ACT_RENAME,   
    ACT_MOVE
} ACTION_typ;

typedef enum {
    ACT_RESOURCE_UNKNOWN,
    ACT_RESOURCE_ONLY,
    ACT_RESOURCE_AND_ACL
} RES_ACTION_typ;

typedef enum {
    OPT_FALSE,
    OPT_TRUE,
    OPT_UNDEFINED
} OPTION_typ;

/********************************************/
/*  Typedefs for INTERCEPTION data          */
/********************************************/
#define MAX_INITIATOR_LEN 1024
typedef char INITIATOR_typ [MAX_INITIATOR_LEN+ 1];

typedef enum {
    UNKNOWN_INTERCEPTOR           = 0,
    INTERCEPT_OFFLINE             = 1,
    STANDARD_OFFLINE_INTERCEPTOR  = 1,     
    INTERCEPT_ONLINE              = 2,
    CUSTOM_ONLINE_INTERCEPTOR     = 2, 
/*	INTERCEPT_SOI                 = 3,*/
    STANDARD_ONLINE_INTERCEPTOR   = 3,
    STANDARD_PASSWORD_INTERCEPTOR = 4,
    CUSTOM_OFFLINE_INTERCEPTOR    = 5,
    CUSTOM_PASSWORD_INTERCEPTOR   = 6,
	AUTOMATIC_PASSWORD_CHANGE     = 7,
    OTHER_INTERCEPTOR             = 8
} INTERCEPTOR_typ;


/* ENUM values also used for CTSA3_INTERCEPT_TYPE_nn */
typedef enum {
    INTERCEPT_NONE,             /* 0  ----Backward compatability----      */
    INTERCEPT_SPECIFIC,         /* 1 Intercept specific object            */
    INTERCEPT_FULL,      /* Intercept object and its connections */
    INTERCEPT_SUBTREE    /* Intercept subtree of container       */
} INTERCEPT_typ;

/* ENUM values also used for CTSA3_OBJECT_TYPE_nn */
typedef enum {
    INTERCEPT_CONTAINER = 0,    /* 0 Container (OE) activity               */
    INTERCEPT_USER      = 1,    /* 1 User Add/Up/Del/Move/Ren etc.         */
    INTERCEPT_GROUP     = 2,    /* 2 Group Add/Upd/Del/Move/Ren etc.       */
    INTERCEPT_CONNECTION= 3,    /* 3 Connection Add/Upd/Del                */
    INTERCEPT_RSSPRM    = 4,    /* 4 RSS parameters update                 */
    INTERCEPT_RESOURCE  = 5,    /* 5 Resource Add/Upd/Del/Move             */
    INTERCEPT_ALL       = 6     /* Valid for NONE and SUBTREE type         */
} INTERCEPT_obj_typ;


/* The following structure is used to keep object synchronization details 
   in the envir. 
   Except for connection, fill fields type, obj_type and object only.
   For changed connection, fill the first 6 fields. If one end of the 
   connection is remote, indicate so in cnn_remote, then fill the 
   remote_rss_key and remote_rss_type fields                             */
typedef struct S_INTERCEPT_rec_typ {
    INTERCEPT_typ        type;             /* Also Defined in old definition.*/ 
    ACTION_typ           action;
    INTERCEPT_obj_typ    obj_type;         /* Also Defined in old definition.*/
    CNN_CLASS_typ        cnn_class;        /* U2UG or G2G               */
    CNN_REMOTE_typ       cnn_remote;       /* Both objects are local 
                                              or one is remote          */
    SEC_OBJ_typ          object;           /* OE, User, Group, resource */
    SEC_OBJ_typ          contained_object; /* For connection - put user 
										      here and group in object  */
    RESTYPE_typ          resource_type;    /* Type, for resource only   */
    SEC_OBJ_typ          new_object_id;    /* For rename/move           */
    OE_typ               old_parent_oe_id;
    OE_typ               new_parent_oe_id; /* For move                  */
    UG_typ               def_group;        /* For user records          */
    EUID_typ             euid;             /* For user, group and oe    */
    RSS_KEY_typ          remote_rss_key;   /* RSS key of remote object  */
    RSS_typ              remote_rss_type;  /* RSS type of remote object */
    OE_typ                 oe;             /* Defined in old definition. Not in use by CC !!!*/
    USER_typ               user;           /* Defined in old definition. Not in use by CC !!!*/
    UG_typ                 ug;             /* Defined in old definition. Not in use by CC !!!*/ 
} INTERCEPT_rec_typ, * INTERCEPT_rec_ptr;

/* For CTSTransactionEvent */
typedef enum {
    UPDCONN_NO,
    UPDCONN_YES
} TRNSEVNT_UPCON_FLAG_typ;

/********************************************/
/*  Typedefs for RESOURCE data              */
/********************************************/

typedef  struct  S_RES_PARAMS {
  RESOURCE_typ    resource;
  RESTYPE_typ     restype;
  OE_typ          parent_oe;
  RESOURCE_typ    parent_resource;
  RESTYPE_typ     parent_restype;
  TIMESTAMP_typ   timestamp;     
} RES_PARAMS_rec_typ, * RES_PARAMS_rec_ptr;


/********************************************/
/*  Typedef for exist/not exist array       */
/********************************************/

typedef enum {OBJ_IGNORED,
              OBJ_EXIST,
              OBJ_NOT_EXIST,
              OBJ_UNREACHABLE,
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
/*  Typedef for login/logout mode           */
/********************************************/

typedef enum {LOGIN_MODE_FIRST = 1,
              LOGIN_MODE,
              LOGOUT_MODE,
              LOGOUT_MODE_LAST
} LOGIN_MODE_typ;

typedef enum {DO_LOGIN,
              NO_LOGIN
} DO_LOGIN_typ;


typedef struct S_FUNC_LOGIN_MODE_STRUCT {

  DO_LOGIN_typ  gtusers;
  DO_LOGIN_typ  adduser;
  DO_LOGIN_typ  upduser;
  DO_LOGIN_typ  deluser;
  DO_LOGIN_typ  revuser;
  DO_LOGIN_typ  updpass;
  DO_LOGIN_typ  mvuser;
  DO_LOGIN_typ  rnuser;

  DO_LOGIN_typ  getugs;
  DO_LOGIN_typ  addug;
  DO_LOGIN_typ  updug;
  DO_LOGIN_typ  delug;
  DO_LOGIN_typ  mvug;
  DO_LOGIN_typ  rnug;

  DO_LOGIN_typ  gtug2uc;
  DO_LOGIN_typ  addu2ug;
  DO_LOGIN_typ  updu2ug;
  DO_LOGIN_typ  delu2ug;

  DO_LOGIN_typ  getconnection;
  DO_LOGIN_typ  addcnn;
  DO_LOGIN_typ  updcnn;
  DO_LOGIN_typ  delcnn;

  DO_LOGIN_typ  getres;
  DO_LOGIN_typ  addres;
  DO_LOGIN_typ  delres;
  DO_LOGIN_typ  updres;
  DO_LOGIN_typ  mvres;
  DO_LOGIN_typ  rnres;

  DO_LOGIN_typ  gtrsacl;
  DO_LOGIN_typ  addace;
  DO_LOGIN_typ  delace;
  DO_LOGIN_typ  updace;

  DO_LOGIN_typ  addoe;
  DO_LOGIN_typ  updoe;
  DO_LOGIN_typ  deloe;
  DO_LOGIN_typ  getoes;
  DO_LOGIN_typ  isuserinoe;
  DO_LOGIN_typ  isuginoe;
  DO_LOGIN_typ  isoeinoe;
  DO_LOGIN_typ  mvoe;
  DO_LOGIN_typ  rnoe;

  DO_LOGIN_typ  ismaskmatch;

  DO_LOGIN_typ  gtrsprm;
  DO_LOGIN_typ  strsprm;

  /* The following are USA-API functions that do not require
     login - therefore do not need the login indication. They 
	 are listed here for documentation purposes.              */ 

/*DO_LOGIN_typ  apiinit;*/
/*DO_LOGIN_typ  apiterm;*/

/*DO_LOGIN_typ  rss_login;          */
/*DO_LOGIN_typ  rss_logout;         */
/*DO_LOGIN_typ  rss_check;          */
/*DO_LOGIN_typ  rss_start_intercept;*/
/*DO_LOGIN_typ  trnsevnt;           */
/*DO_LOGIN_typ  apiversion;         */
/*DO_LOGIN_typ  intercept_retry;    */
/*DO_LOGIN_typ  RSSVerifyPassword;  */
/*DO_LOGIN_typ  APILoginModes;      */

} FUNC_LOGIN_MODE_rec_typ, * FUNC_LOGIN_MODE_rec_ptr;

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
    RSS_KEY_typ          remote_rss_key;   
    RSS_typ              remote_rss_type;  
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
    GET_WILD_USERS,            /* Let's all get wild */
    GET_SUBTREE_USERS,         /* For OE objects     */
    GET_FREE_HANDLE_USERS      /* free *handle       */
} GET_USER_MODE;

typedef enum {
    GET_ALL_GROUPS,
    GET_MANY_GROUPS,
    GET_SUBTREE_GROUPS,        /* For OE objects  */
    GET_FREE_HANDLE_GROUPS     /* free *handle    */
} GET_GROUP_MODE;

typedef enum {
    GET_ALL_OES,
    GET_MANY_OES,
    GET_SUBTREE_OES,           /* For OE objects  */
    GET_FREE_HANDLE_OES        /* free *handle    */
} GET_OE_MODE;

typedef enum {
    GET_MANY_RESOURCES,
    GET_FREE_HANDLE_RESOURCES  /* free *handle */
} GET_RESOURCE_MODE;

typedef enum {
    GET_RESOURCE_ACL,          /* Get all ACLs of specified resource */
    GET_FREE_HANDLE_ACL        /* free *handle                       */
} GET_ACL_MODE;

typedef enum {
    GET_ALL_CONNS,
    GET_GROUPS_CONNS,          /* Get all connections for spec. groups*/
    GET_USERS_CONNS,           /* Get all connections for spec. users */
    GET_MANY_CONNS,            /* Get specified connections           */
    GET_FREE_HANDLE_CONNS      /* free *handle                        */
} GET_CONN_MODE;

typedef int  ESA_DIAG_LEVEL_typ;
typedef int  ESA_DIAG_COMP_typ;

/* Loaded Messages entry   */
#define CTSAMSG_MSGID_LEN             12
#define CTSAMSG_FORMAT_LEN           133

typedef char CTSAMSG_MSGID_typ  [ CTSAMSG_MSGID_LEN  + 1 ];
typedef char CTSAMSG_FORMAT_typ [ CTSAMSG_FORMAT_LEN + 1 ];

typedef struct S_MSG_STRUCT {
    CTSAMSG_MSGID_typ   id;
    CTSAMSG_FORMAT_typ  format;
} CTSAMSG_MSG_rec_typ, *CTSAMSG_MSG_rec_ptr;

/* Loaded Messages array handle  */

typedef struct S_HANDLE_STRUCT {
    CTSAMSG_MSG_rec_typ    * buffer;
    unsigned int             size;      /* # of allocated slots */
    unsigned int             used;      /* # of used slots      */
    void                   * diag_handle; /* for ESA_DIAGR      */
} CTSAMSG_HANDLE_rec_typ, *CTSAMSG_HANDLE_rec_ptr;


/* CTSAMSG entities type definitions */
#define CTSAMSG_MSG_LEN             2048

typedef char CTSAMSG_MSG_typ    [ CTSAMSG_MSG_LEN    + 1 ];

/* Flag type */
typedef enum {
    FLAG_NO, FLAG_YES
} CTSAMSG_FLAG_typ;

/* Timestamp flag */
typedef enum {
    TIMES_NONE, TIMES_SHORT, TIMES_FULL
}   CTSAMSG_TIMESTAMP_typ;

/* Destination Type type */

typedef enum {
	DEST_FILE, 
	DEST_FILE_APPEND, 
	DEST_ERR, 
	DEST_USER, 
	DEST_CONSOLE,
	DEST_CONSOLE2,
	DEST_STDOUT,
	DEST_STDERR
} CTSAMSG_DEST_TYPE_typ;


/* Destination Handling Functions */

typedef ESA_RC CTSAMSG_INITFUNC (void              *dest_name,
                                 void             **handle);

typedef ESA_RC CTSAMSG_PRTFUNC (/*void                    *DiagHndl, */
								void                    *dest_name,
 	                            CTSAMSG_HANDLE_rec_typ  *msg_handle,
                                CTSAMSG_MSG_typ          msg,
                                void                   **handle,
                                int                      max_gen,
                                int                      max_lines,
                                int                      max_interval);

typedef ESA_RC CTSAMSG_TERMFUNC (void             *dest_name,
                                 void            **handle);

/* Destination Description Entry */

typedef struct S_DEST_STRUCT {
    CTSAMSG_DEST_TYPE_typ   type;
    void                  * name;
    void                  * handle;
    CTSAMSG_INITFUNC      * init_func;
    CTSAMSG_PRTFUNC       * prt_func;
    CTSAMSG_TERMFUNC      * term_func;
    CTSAMSG_FLAG_typ        active;    /* Active flag    */
    CTSAMSG_TIMESTAMP_typ   timestamp; /* Timestamp flag */
} CTSAMSG_DEST_rec_typ, *CTSAMSG_DEST_rec_ptr;

/* Destination Description Table */

typedef struct S_DEST_TABLE_STRUCT {
    short   num;
    int     max_gen;      /* Max Number of genrations */
    int     max_lines;    /* Max number of messages in a generation */
    int     max_interval; /* Max time between generations */
    CTSAMSG_DEST_rec_typ  dests[1];
} CTSAMSG_DEST_TABLE_rec_typ, *CTSAMSG_DEST_TABLE_rec_ptr;


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APIDEFS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APIDEFS__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APIDEFS_H_INCLUDED */
