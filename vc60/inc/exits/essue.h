#ifndef _essue_h_
#define _essue_h_

#include <stdlib.h>
#include "essrtypes.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define HIDE_FIELD_VALUE_ONLY   -1
 
/*
 *  Delimiter characters
 */

#ifndef DELIMITER_CHAR
#define DELIMITER_CHAR     '\n'
#endif
 
#ifndef SUB_DELIMITER_CHAR
#define SUB_DELIMITER_CHAR '\v'
#endif

typedef int AE_RSS_TYPE;

/*
** Funtion prototypes
*/
int    set_item_value( );
char * get_item_value( );
char * get_item_default_value( );
char * get_item_original_value( );
int    get_form_mode( );
int    ae_get_form_insert( );
int    set_item_state( );
int    get_item_state( );
int    ae_display_message( );
int    ae_form_refresh( );
int    ae_get_field_name_init( );
int    ae_get_field_name_next( );
int    ae_get_field_name_term( );
int    ae_set_item_visible( );
int    ae_get_item_visible( );
int    ae_set_current_field( );
int    ae_read_db_field( );
int    ae_read_db_field_from_array( );
int    ae_open_db_table( );
void   ae_close_db_table( );
int    ae_is_ess_admin( );
int    ae_is_demo( );
char * ae_get_user( );
int    ae_get_item_display_type ( );
void   add_user_exit( );
char * ae_get_fld_value( );
int    ae_get_fld_number( );
int    ae_get_external_id( );

/*
 *  Entity Types
 */
#define    AE_ENTITY_TYPE_RSS_USER       "rss_user"
#define    AE_ENTITY_TYPE_USER_GROUP     "user_group"
#define    AE_ENTITY_TYPE_RU_UG          "ru_ug"
#define    AE_ENTITY_TYPE_RESOURCE       "res"
#define    AE_ENTITY_TYPE_JOBCODE        "jobcode"
#define    AE_ENTITY_TYPE_PLATFORM       "platform"
#define    AE_ENTITY_TYPE_RSS            "rss"
#define    AE_ENTITY_TYPE_USER           "ent_user"
#define    AE_ENTITY_TYPE_UG_JC          "ug_jc"
#define    AE_ENTITY_TYPE_USER_JC        "user_jc"
#define    AE_ENTITY_TYPE_ACE            "ace"
#define    AE_ENTITY_TYPE_RSS_ADMIN      "rss_admin"
#define    AE_ENTITY_TYPE_OE             "oe"
 
/*
 * Form Types
 */
#define AE_FORM_TYPE_IS_STANDARD      0x00
#define AE_FORM_TYPE_IS_ACTION_DELETE 0x04
#define AE_FORM_TYPE_IS_PASSWORD      0x08
#define AE_FORM_TYPE_IS_ACTION_REVOKE 0x10
#define AE_FORM_TYPE_IS_ACTION_GET    0x20

/*
 * Various Defines
 */
#define USERIDLEN      20
#define USERNAMELEN    64

enum
{
   UE_FIELD_READ_FIELD=1234,
   UE_FIELD_READ_KEY
};
 
enum
{
   ESS_PROCESS_UNDEF,
   ESS_PROCESS_GUI,
   ESS_PROCESS_GTW,
   ESS_PROCESS_BATCH,
   ESS_PROCESS_PMP,
   ESS_PROCESS_DATASYNC,
   ESS_PROCESS_REFRESH,
   ESS_PROCESS_ROUTER,
   ESS_PROCESS_SERVER,
   ESS_PROCESS_CONFIG, 
   ESS_PROCESS_ACF2_KWD,
   ESS_PROCESS_BRL,
   ESS_PROCESS_UPDATE_RU_SUSPENDED,
   ESS_PROCESS_MAX
};


typedef enum
{
    AE_MODE_INIT = 0,
    AE_MODE_FIELD_CHANGE,
    AE_MODE_WRITE,
    AE_MODE_DELETE,
    AE_MODE_TERMINATE,
    AE_MODE_MAX_VALUE
} AE_MODE;
 
typedef enum
{
    AE_ITEM_TYPE_TEXT = 0,
    AE_ITEM_TYPE_CHECK_BUTTON,
    AE_ITEM_TYPE_CYCLE_BUTTON,
    AE_ITEM_TYPE_MTEXT
} AE_ITEM_TYPE;

typedef struct
{
    char *keyword;
    char *value;
    int   changed;
    int   fldnum;
} ADDINFO_PAIR;

typedef struct
{
  char   *rss_type;
  char   *rss_name;
  int     rss_users_num;
  char  **rss_users_array;
} JC_CONFLICT_RSS_USER_DATA;

typedef enum
{
    AD_OP_VIEW,
    AD_OP_ADD,
    AD_OP_UPDATE,
    AD_OP_DELETE,
    AD_OP_SYNC,
    AD_OP_PLATFORM_DATA,
    AD_OP_SET_PASSWORD,
    AD_OP_REVOKE,
    AD_OP_RESTORE,
    AD_OP_LOAD,
    AD_OP_OFLI,
    AD_OP_LOG,
    AD_OP_REVOKE_AND_PASSWORD,
    AD_OP_RESTORE_AND_PASSWORD,
    AD_OP_CONNECT,
    AD_OP_START
} ADMIN_OPERATION;
 
typedef struct
{
    char *ad_usr_rss_user_name;
    char *ad_usr_rss_name;
    char *ad_usr_rss_type;
} ADMIN_USER_DATA;

typedef struct
{
    char *ad_grp_user_group_name;
    char *ad_grp_rss_name;
    char *ad_grp_rss_type;
} ADMIN_GROUP_DATA;
 
typedef struct
{
    char *rss_name;
    char *rss_type;
    char *rss_user_name;
    char *def_ug_name;
    char *user_id;
} ADMIN_ADMIN_DATA;

typedef enum
{
   UE_INSERT,
   UE_UPDATE,
   UE_DELETE
} UE_ACTION;
 
typedef enum
{
   UE_UNDEF,
   UE_GUI,
   UE_GATEWAY,
   UE_BATCHRUN,
   UE_SERVER,
   UE_REFRESH
} UE_PROCESS;

typedef enum
{
   UE_BEFORE_WRITE
} UE_CALLTYPE;

typedef enum
{
   UE10_ACTION_INIT,
   UE10_ACTION_TERM
} UE10_ACTION;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_is_demo)();
    int    (*ae_display_message)();
} UE11_API;
 
typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_is_demo)();
    int    (*ae_display_message)();
} UE12_API;

typedef struct
{
    int    (*set_item_value)();
    char * (*get_item_value)();
    char * (*get_item_default_value)();
    char * (*get_item_original_value)();
    int    (*get_form_mode)();
    int    (*get_form_insert)();
    int    (*set_item_state)();
    int    (*get_item_state)();
    int    (*ae_display_message)();
    int    (*ae_get_field_name_init)();
    int    (*ae_get_field_name_next)();
    int    (*ae_get_field_name_term)();
    int    (*ae_set_item_visible)();
    int    (*ae_get_item_visible)();
    int    (*ae_form_refresh)();
    int    (*ae_set_current_field)();
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_is_ess_admin)();
    char * (*ae_get_user)();
    int    (*ae_is_demo)();
    int    (*ae_get_item_display_type)();
} UE1_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_display_message)();
    int    (*ae_is_demo)();
} UE2_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_display_message)();
} UE3_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    char*  (*get_fld_lbl)();
    int    dmlv;
    int    (*ae_is_demo)();
} UE6_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_is_ess_admin)();
    char*  (*ae_get_fld_value)();
    int    (*ae_get_fld_number)();
    int    (*ae_is_demo)();
} UE7_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    char*  (*get_fld_lbl)();
    int    dmlv;
    int    (*ae_is_demo)();
    int    (*ae_display_message)();
} UE8_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    char*  (*get_fld_lbl)();
    int    dmlv;
    int    (*ae_is_demo)();
    int    (*ae_display_message)();
    int    (*ae_is_ess_admin)();
    char*  (*ae_get_fld_value)();
    int    (*ae_get_fld_number)();
    char*  orig_rec;
} UE9_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_is_demo)();
    int    (*ae_display_message)();
    int    (*ae_is_ess_admin)();
    int    (*ae_get_external_id)();
} UE10_API;

typedef struct
{
    int    (*ae_read_db_field)();
    int    (*ae_read_db_field_from_array)();
    int    (*ae_open_db_table)();
    void   (*ae_close_db_table)();
    int    (*ae_display_message)();
} UE13_API;

/*
 * Form Specific API Functions
 */
#define AE_GET_DEFAULT( api, form, entity, rss_type, rss, item ) \
                          (api->get_item_default_value)( form, entity, rss_type, item, rss )
 
#define AE_GET_ORIGINAL( api, form, item, rsstype ) \
                          (api->get_item_original_value)(form, item, rsstype )
 
#define AE_SET_VALUE( api, form, item, value, rsstype ) \
                              (api -> set_item_value) (form, item, value, rsstype )
 
#define AE_GET_VALUE( api, form, item, rsstype ) \
                          (api->get_item_value)(form, item, rsstype )
 
#define AE_GET_FORM_TYPE( api, form ) \
                          (api->get_form_mode)(form)
 
#define AE_GET_INSERT( api, form ) \
                      (api->get_form_insert)(form)
 
#define AE_SET_ITEM_ENABLED( api, form, item, state, rsstype ) \
                          (api->set_item_state)(form, item, state, rsstype)
 
#define AE_GET_ITEM_ENABLED( api, form, item, rsstype ) \
                          (api->get_item_state)(form, item, rsstype)
 
#define AE_DISPLAY_MESSAGE( api, form, title, message ) \
                          (api->ae_display_message)(form, title, message)
 
 
#define AE_GET_FIELD_NAME_INIT( api, form ) \
                          (api->ae_get_field_name_init)(form)
#define AE_GET_FIELD_NAME_NEXT( api, form, iter, rsstype, fldbuf, fldlen ) \
                          (api->ae_get_field_name_next)(iter, form, rsstype, fldbuf, fldlen)
#define AE_GET_FIELD_NAME_TERM( api, iter ) \
                          (api->ae_get_field_name_term)(iter)
#define AE_SET_ITEM_VISIBLE( api, form, item, state, rsstype ) \
                          (api->ae_set_item_visible)(form, item, state, rsstype)
#define AE_GET_ITEM_VISIBLE( api, form, item, rsstype ) \
                          (api->ae_get_item_visible)(form, item, rsstype)
 
#define AE_SET_CURRENT_FIELD( api, form, item, rsstype ) \
                          (api->ae_set_current_field)(form, item, rsstype)
 
#define AE_FORM_REFRESH( api, form ) \
                          (api->ae_form_refresh)(form)
#define AE_GET_ITEM_DISPLAY_TYPE( api, form, item, rsstype ) \
                          (api->ae_get_item_display_type)(form, item, rsstype)
/*
 * General API Functions
 */
#define UE_DISPLAY_MESSAGE( api, title, message ) \
                          (api->ae_display_message)(NULL, title, message)
#define UE_OPEN_DB_TABLE( api, table ) \
                          (api->ae_open_db_table)(table)
#define UE_CLOSE_DB_TABLE( api, tblhdl ) \
                          (api->ae_close_db_table)(tblhdl)
#define UE_READ_DB_FIELD( api, arg_list ) \
                          ((api->ae_read_db_field) arg_list )
#define UE_READ_DB_FIELD_FROM_ARRAY( api, tblhd, table, rsstype, numentries, entries ) \
                          (api->ae_read_db_field_from_array) (tblhd, table, rsstype, numentries, entries )
 
#define UE_GET_USER( api ) \
                      (api->ae_get_user)()
#define UE_IS_SUPER_USER( api ) \
                      (api->ae_is_ess_admin)()
#define UE_GET_FLD_VALUE( api, tbl, rec, fld ) \
                          (api->ae_get_fld_value) (tbl, rec, fld )
#define UE_GET_FLD_LABEL( api, fld ) \
                          (api->get_fld_lbl)(api->dmlv, fld, -1)
#define UE_GET_FLD_NUMBER( api, tbl, fld ) \
                          (api->ae_get_fld_number)(tbl, fld )
#define UE_IS_DEMO( api ) \
                 (api->ae_is_demo)()
#define UE_DISPLAY_MESSAGE( api, title, message ) \
                 (api->ae_display_message)(NULL, title, message)
#define UE_GET_EXTERNAL_ID( api ) \
                      (api->ae_get_external_id)()

#endif    /* #ifndef _essue_h_ */
