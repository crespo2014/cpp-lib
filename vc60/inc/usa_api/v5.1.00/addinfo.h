/********************************************************************** 
* 
* H Source: addinfo.h 
* Description: Additional Info Manipulation - including long values
* %created_by: leonid_s % 
* %date_created: Wed Sep 01 11:06:14 2004 % 
* %full_filespec: addinfo.h#5:incl:2 % 
* 
* Note - ALL definitions must start with ADI, for uniqueness.
*
**********************************************************************/ 

#ifndef ADI_H_included
#define ADI_H_included

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifdef MVS
#define ADI_kwd_find                  adilv01
#define ADI_kwd_find_CS               adils01
#define ADI_kwd_get_next              adilv02
#define ADI_kwd_get_next_CS           adils02
#define ADI_kwd_find_by_prefix        adilv03
#define ADI_kwd_find_by_prefix_CS     adils03
#define ADI_kwd_and_value_add         adilv04
#define ADI_kwd_and_value_add_CS      adils04
#define ADI_kwd_delete                adilv05
#define ADI_kwd_delete_CS             adils05
#define ADI_kwd_dup_check             adilv06
#define ADI_kwd_dup_check_CS          adils06
#define ADI_value_get                 adilv07
#define ADI_value_get_CS              adils07
#define ADI_value_set                 adilv08
#define ADI_value_set_CS              adils08
#define ADI_kwd_find_value_get        adilv28
#define ADI_kwd_find_value_get_CS     adils28
#define ADI_kwd_find_value_set        adilv29
#define ADI_kwd_find_value_set_CS     adils29
#define ADI_kwd_find_and_delete       adilv30
#define ADI_kwd_find_and_delete_CS    adils30
#define ADI_value_reset               adilv09
#define ADI_value_reset_CS            adils09
#define ADI_value_concat              adilv10
#define ADI_value_concat_CS           adils10
#define ADI_table_reset               adilv11
#define ADI_table_reset_CS            adils11
#define ADI_table_alloc               adilv12
#define ADI_table_alloc_EX            adile12
#define ADI_table_alloc_CS            adils12
#define ADI_table_free                adilv13
#define ADI_table_realloc             adilv14
#define ADI_table_realloc_CS          adils14
#define ADI_table_copy                adilv15
#define ADI_table_copy_CS             adils15
#define ADI_table_diag                adilv16
#define ADI_table_diag_CS             adils16
#define ADI_table_to_buffer           adilv17
#define ADI_table_to_buffer_CS        adils17
#define ADI_table_from_buffer         adilv18
#define ADI_table_from_buffer_CS      adils18
#define ADI_list_search               adilv19
#define ADI_list_search_CS            adils19
#define ADI_list_diff                 adilv20
#define ADI_list_diff_CS              adils20
#define ADI_list_convert_sep          adilv21
#define ADI_list_convert_sep_CS       adils21
#define ADI_list_to_string            adilv22
#define ADI_list_to_string_CS         adils22
#define ADI_list_from_string          adilv23
#define ADI_list_from_string_CS       adils23
#define ADI_list_entry_append_start   adilv24
#define ADI_list_entry_append_start_CS adils24
#define ADI_list_subfield_get_next    adilv25
#define ADI_list_subfield_get_next_CS adils25
#define ADI_list_subfield_append      adilv26
#define ADI_list_subfield_append_CS   adils26
#define DATA_COMP_ADDINFO_C           adilv27
#define DATA_COMP_ADDINFO__           adilv28
#define ADI_table_free_EX             adilv29
#define ADI_table_free_CS             adils29
#endif

#include STDIO
#define M_LOCKED            "1"
#define M_UNLOCKED          "2"
#define M_IGNOR_INTRUDER    "3"

#define M_REVOKE            "1"
#define M_RESTORE           "2"
#define M_OP_IS_IGNOR       "/"

#define M_USER_IS_USER      "1"
#define M_USER_IS_AUDITOR   "2"
#define M_USER_IS_ADMIN     "3"
#define M_USER_IS_BOTH      "4"
#define M_USER_IS_IGNORED   "5"

/* ACE stuff */

#define M_ACE_IS_USER       "1"
#define M_ACE_IS_GROUP      "2"
#define M_ACE_IS_BOTH       "3"
#define M_ACE_IS_OE         "4"
#define M_ACE_IS_MASK       "5"
#define M_ACE_IS_OTHER      "6"
#define M_ACE_IS_UNDEFINED  "7"
#define M_ACE_IS_IGNORE     "/"

#define M_ACE_LOC_FIRST     "1"
#define M_ACE_LOC_LAST      "2"
#define M_ACE_LOC_BEFORE    "3"
#define M_ACE_LOC_AFTER     "4"
#define M_ACE_LOC_IGNORED   "5"

#define M_ACE_ATTR_IS_PERMANENT   "1"
#define M_ACE_ATTR_IS_REGULAR     "2"
#define M_ACE_ATTR_IGNORED        "/"

#define M_LOGEVENT          "0"
#define M_REGULARALERT      "1"
#define M_URGENTALERT       "2"
#define M_VERYURGENTALERT   "3"

/* OE stuff */
#define M_OE_ATTR_ACL        "1"
#define M_OE_ATTR_NO_ACL     "2"
#define M_OE_ATTR_IGNORED    "3"

/* User password life enums */

#define M_PASS_LIFE_PERMANENT "1"
#define M_PASS_LIFE_RESET     "2"
#define M_PASS_LIFE_IGNORED   "3"

#define M_NORMAL_MODE         "1"
#define M_SIMULATION_MODE     "2"
#define M_ADMIN_MODE_IGNORED  "3"


#define M_OLD_DEF_UG_ACT_IGNORED "3"
#define M_OLD_DEF_UG_ACT_DROP    "2"
#define M_OLD_DEF_UG_ACT_KEEP    "1"

#define M_U2UG_CONN_NONE      "1"
#define M_U2UG_CONN_IS_ADMIN  "2"
#define M_U2UG_CONN_IS_AUDIT  "3"
#define M_U2UG_CONN_IS_BOTH   "4"
#define M_U2UG_CONN_IGNORE    "5"

#define M_U2UG_ATTR_UNDEFINED     "1"
#define M_U2UG_ATTR_DEFAULT_GROUP "2"
#define M_U2UG_ATTR_IGNORED       "3"

/* WSAN100653 start */
#define M_CNN_ADM_NONE      "1"
#define M_CNN_ADM_IS_ADMIN  "2"
#define M_CNN_ADM_IS_AUDIT  "3"
#define M_CNN_ADM_IS_BOTH   "4"
#define M_CNN_ADM_IGNORE    "5"

#define M_CNN_ATTR_UNDEFINED     "1"
#define M_CNN_ATTR_DEFAULT_GROUP "2"
#define M_CNN_ATTR_IGNORED       "3"

#define M_CNN_REM_BOTH_LOCAL         "0"
#define M_CNN_REM_REMOTE_CONTAINED   "1"
#define M_CNN_REM_REMOTE_CONTAINING  "2"

#define M_CNN_CLASS_U2UG  "1"
#define M_CNN_CLASS_G2G   "2"
/* WSAN100653 end */

#define ORIGINATOR_77 "77Originator"

/* ------------------------------------------------------------- */    
/* -- ADDINFO table definitions                               -- */    
/* --                                                         -- */    
/* -- (Moved from ESAAPI.H)                                   -- */    
/* ------------------------------------------------------------- */    

/* keywoword type definition */

typedef enum {
    TYPE_AI_IGNORED= 0,
    TYPE_1A,                /* pre-defined, single value           */
    TYPE_1B,                /* pre-defined, multiple value (list)  */
    TYPE_2A,                /* user-defined, single value          */
    TYPE_2B                 /* user-defined, multiple value (list) */
} ADDINFO_typ;


/* Definition of single keyword entry in addinfo table */

typedef struct S_ONE_FIELD_rec_typ {
    ADDINFO_typ add_typ;
    short       keylen;                              /* field len w/o null*/
    char        keyword [MAX_RSS_ADDINFO_KWD_LEN+1]; /* Null-term.str.    */
    short       vallen;                              /* field len w/o null*/
    char        value   [MAX_RSS_ADDINFO_VAL_LEN+1]; /* Null-term.str.    */
                           /* value is in use only if following field = 0 */
    size_t      value_offset;     /* long value offset into values buffer */

}  ONE_FIELD_rec_typ, 	* ONE_FIELD_rec_ptr;
                                  
/* Definition on addinfo table */

typedef  struct S_ADDINFO {
    short               num_pairs;        /* entries (pairs) in use      */  
    short               max_pairs;        /* entries allocated           */       

    char              * values_buff_addr; /* values buffer address       */
    size_t              values_buff_len;  /* Buff len  (0=not allocated) */
    char              * values_buff_next; /* Addr of free space in buff  */

    ONE_FIELD_rec_typ   pair [1];       /* allocated as pair [max_pairs] */

} ADDINFO_rec_typ, * ADDINFO_rec_ptr;

/* Table header length needed for calculations */
#define ADI_TABLE_HEADER_LEN (sizeof(ADDINFO_rec_typ) - sizeof(ONE_FIELD_rec_typ))

/* ------------------------------------------------------------- */    
/* -- ADDINFO definitions                                     -- */    
/* --                                                         -- */    
/* -- (Moved from ESAINIT.H)                                  -- */    
/* ------------------------------------------------------------- */   

/*
 *  Defining the format of addinfo fields in a message from ESS
 */
#define ADINF_NUM_PRS        3       /* # chars defining pairs inside msg */
#define ADINF_KEY_LEN        2       /* # chars defining kwd len in a msg */

/* Note - the following with _S is used when ESS does not say what the length is. 
   The newer ESS versions send the length at the end of a start-service message,
   and it is kept in envir_ptr->addinfo_val_len.
   Because of the SHORT in addinfo table definitions, it can be maximum 4 bytes
   to hold maximum of 65536.
   The _N definition should ideally be get rid of, and the envir value used.
*/
#define ADINF_VAL_LEN_S      3       /* # chars defining value len(hex) in msg */  
#define ADINF_VAL_LEN_N      4       /* same but for newer versions       */


#define ADINF_TYP_LEN        2       /* #chars defining keyword type in a msg */   

/*
 *    keyword types
 */

#define M_ADDINFO_ENTITY    "00"
#define M_ADDINFO_1A        "1A"
#define M_ADDINFO_1B        "1B"
#define M_ADDINFO_2A        "2A"
#define M_ADDINFO_2B        "2B"
#if 0       /* ::ADI:: unused */
#define M_ADDINFO_3E        "3E"
#endif
#define M_ADDINFO_UD        "UD"     

/* --------------------------------------------------------------------- */
/* --New package Definitions                                          -- */
/* --------------------------------------------------------------------- */

typedef enum {
              ADI_NEXT_FIRST, ADI_NEXT_NOTFIRST
             } ADI_next_flag;

typedef enum {
              ADI_VALUE_MANDATORY, ADI_VALUE_OPT, ADI_VALUE_NONE
             } ADI_value_flag;

typedef enum {
              ADI_RESET_KWDS, ADI_RESET_VALUES
             } ADI_reset_flag;

/* Value maximum length limit due to table vallen defined as short */  
#define ADI_VALUE_MAXIMUM_LENGTH 32767 

/* --------------------------------------------------------------------- */
/* -- Functions                                                       -- */
/* --------------------------------------------------------------------- */

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_find                               *
 *                                                             *
 * DESCRIPTION    : Find a keyword by name in ADDINFO table    *
 *                                                             *
 * INPUT          : keyword name                               *
 *                  ADDINFO table address                      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Index of keyword entry (if RC= OK)         *
 *                                                             *
 * RETURN VALUE   : return code                                *
 *                  ESA_OK      - output pointer has entry     *
 *                  ESA_KEY_NOT_FOUND - kwd not found          *
 *                  ESA_ERR     - Error in input               *
 *                                                             *
 **************************************************************/
 typedef ESA_RC ADI_kwd_find_TYP (void      * DiagHndl,
                      char                  * IN_kwd,
                      ADDINFO_rec_ptr         IN_addinfo_table,
                      int                   * OUT_addinfo_entry_index,
                      ADMIN_PARAMS_rec_typ  * admin_params);

 extern  ADI_kwd_find_TYP ADI_kwd_find_CS;
 typedef ADI_kwd_find_TYP * ADI_kwd_find_PTR;


 ESA_RC ADI_kwd_find (void                  * DiagHndl,
                      char                  * IN_kwd,
                      ADDINFO_rec_ptr         IN_addinfo_table,
                      int                   * OUT_addinfo_entry_index,
                      ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_get_next                           *
 *                                                             *
 * DESCRIPTION    : Get pointer to next entry in ADDINFO table *
 *                                                             *
 * INPUT          :                                            *
 *                  ADDINFO table address                      *
 *                  ADDINFO table start from index             *
 *                  flag = FIRST if first time here (start from*
 *                         index will be ignored)              *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         :                                            *
 *                  ADDINFO table index to next keyword (valid *
 *                         only if RC=OK)                      *
 *                                                             *
 * RETURN VALUE   : return code                                *
 *                  ESA_OK      - output pointer has entry     *
 *                  ESA_ERR     - Error in input               *
 *                  ESA_EOF     - No more entries              *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_kwd_get_next_TYP (void       * DiagHndl, 
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           int                     IN_addinfo_start_index,
                           ADI_next_flag           IN_next_flag,
                           int                   * OUT_addinfo_entry_index,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_kwd_get_next_TYP  ADI_kwd_get_next_CS;
 typedef  ADI_kwd_get_next_TYP  * ADI_kwd_get_next_PTR;

ESA_RC ADI_kwd_get_next ( void                  * DiagHndl,
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           int                     IN_addinfo_start_index,
                           ADI_next_flag           IN_next_flag,
                           int                   * OUT_addinfo_entry_index,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_find_by_prefix                     *
 *                                                             *
 * DESCRIPTION    : Search a keyword in additional info        *
 *                  Options - find next match                  *
 *                            next if value empty/non-empty    *
 *                                                             *
 * INPUT          : keyword prefix                             *
 *                  flag - find with value or even if empty    *
 *                  where to start search (if not first time)  *
 *                  first time/not - use start index or not    *
 *                  addinfo table                              * 
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Index to keyword entry (if rc = ESA_OK)    *
 *                                                             *
 * RETURN VALUE   : return code                                *
 *                  ESA_OK      - output pointer has entry     *
 *                  ESA_ERR     - Input error                  *
 *                  ESA_KEY_NOT_FOUND - Not found              *
 *                                                             *
 **************************************************************/
 
 typedef ESA_RC ADI_kwd_find_by_prefix_TYP (void     * DiagHndl,
                               char                  * IN_kwd_prefix,
                               ADI_value_flag          IN_find_empty,
                               int                     IN_addinfo_start_index,
                               ADI_next_flag           IN_next_flag,
                               ADDINFO_rec_ptr         IN_addinfo_table,
                               int                   * OUT_addinfo_entry_index,
                               ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_kwd_find_by_prefix_TYP  ADI_kwd_find_by_prefix_CS;
 typedef  ADI_kwd_find_by_prefix_TYP  * ADI_kwd_find_by_prefix_PTR;

 ESA_RC ADI_kwd_find_by_prefix(void                  * DiagHndl,
                               char                  * IN_kwd_prefix,
                               ADI_value_flag          IN_find_empty,
                               int                     IN_addinfo_start_index,
                               ADI_next_flag           IN_next_flag,
                               ADDINFO_rec_ptr         IN_addinfo_table,
                               int                   * OUT_addinfo_entry_index,
                               ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_and_value_add                      *
 *                                                             *
 * DESCRIPTION    : Insert a keyword into ADDINFO table and    *
 *                  fill the value. Value can be empty.        *
 *                  No check is done for duplicate keywords -  *
 *                  it is the caller's responsibility.         *
 *                                                             *
 * INPUT          : keyword type     -  single/list            *
 *                  keyword name                               *
 *                  value            -  optional (use NULL)    *
 *                  ADDINFO table                              *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         :                                            *
 *                  Index to newly created keyword entry  -    *
 *                         optional (use NULL)                 * 
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK      - output pointer has entry     *
 *                  ESA_ERR     - Input error                  *
 *                  ESA_EOF     - No room left in table        *
 *                  ESA_SOS     - Short on storage             *
 *                                                             *
 **************************************************************/

 typedef ESA_RC  ADI_kwd_and_value_add_TYP (void     * DiagHndl,
                               ADDINFO_typ             IN_kwd_type,
                               char                  * IN_kwd_name,
                               char                  * IN_val,
                               ADDINFO_rec_ptr         IN_addinfo_table,
                               int                   * OUT_addinfo_entry_index,
                               ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_kwd_and_value_add_TYP  ADI_kwd_and_value_add_CS;
 typedef  ADI_kwd_and_value_add_TYP  * ADI_kwd_and_value_add_PTR;

 ESA_RC  ADI_kwd_and_value_add(void                  * DiagHndl,
                               ADDINFO_typ             IN_kwd_type,
                               char                  * IN_kwd_name,
                               char                  * IN_val,
                               ADDINFO_rec_ptr         IN_addinfo_table,
                               int                   * OUT_addinfo_entry_index,
                               ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_delete                             *
 *                                                             *
 * DESCRIPTION    : Delete an entry from addinfo table         *
 *                  The table will be compressed.              *
 *                                                             *
 * INPUT          : Addinfo  table                             *
 *                  entry index to keyword entry               *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : none                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK      - output pointer has entry     *
 *                  ESA_ERR     - Input error                  *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_kwd_delete_TYP (void       * DiagHndl,
                         ADDINFO_rec_ptr         IN_addinfo_table,
                         int                     IN_addinfo_entry_index,
                         ADMIN_PARAMS_rec_typ  * admin_params);

extern   ADI_kwd_delete_TYP  ADI_kwd_delete_CS;
typedef  ADI_kwd_delete_TYP  * ADI_kwd_delete_PTR;

 ESA_RC ADI_kwd_delete ( void                  * DiagHndl, 
                         ADDINFO_rec_ptr         IN_addinfo_table,
                         int                     IN_addinfo_entry_index,
                         ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_find_and_delete                    *
 *                                                             *
 * DESCRIPTION    : Find the kwd and then delete it from table *
 *                                                             *
 * INPUT          :                                            *
 *                  Addinfo table                              *
 *                  Keyword name                               *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was returned     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_KEY_NOT_FOUND - Keyword has no value   *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_kwd_find_and_delete_TYP (void * DiagHndl,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  char                  *  IN_kwd,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_kwd_find_and_delete_TYP  ADI_kwd_find_and_delete_CS;
 typedef  ADI_kwd_find_and_delete_TYP  * ADI_kwd_find_and_delete_PTR;

 ESA_RC ADI_kwd_find_and_delete (void   *  DiagHndl,  
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  char                  *  IN_kwd,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_dup_check                          *
 *                                                             *
 * Description    : Find if keyword is duplicated, if not      *
 *                  return index to it.                        *
 *                                                             *
 * Input          :                                            *
 *                  keyword name                               *
 *                  flag - whether contents of value count     *
 *                  addinfo table                              *
 *                  admin_params                               *
 *                                                             *
 * Output         : Index to entry if keyword (if RC NE ERR)   *
 *                                                             *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Found and Unique       *
 *                  ESA_ERR           - Input error            *
 *                  ESA_DUP_KEY       - duplicate              *
 *                  ESA_KEY_NOT_FOUND - Not found              *
 *                                                             *
 **************************************************************/

 typedef ESA_RC  ADI_kwd_dup_check_TYP (void    * DiagHndl,
                          char                  * IN_kwd_name,
                          ADI_value_flag          IN_find_empty,
                          ADDINFO_rec_ptr         IN_addinfo_table,
                          int                   * OUT_addinfo_entry_index,
                          ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_kwd_dup_check_TYP  ADI_kwd_dup_check_CS;
 typedef  ADI_kwd_dup_check_TYP  * ADI_kwd_dup_check_PTR;

 ESA_RC  ADI_kwd_dup_check (void                * DiagHndl,
                          char                  * IN_kwd_name,
                          ADI_value_flag          IN_find_empty,
                          ADDINFO_rec_ptr         IN_addinfo_table,
                          int                   * OUT_addinfo_entry_index,
                          ADMIN_PARAMS_rec_typ  * admin_params);

  /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_value_get                              *
 *                                                             *
 * DESCRIPTION    : Get value of keyword                       *
 *                                                             *
 * INPUT          : Addinfo table                              *
 *                  index to keyword entry                     *
 *                  size of storage area to receive value      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : keyword value - may be empty               *
 *                  value length                               *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was returned     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - Length not enough (len * 
 *                                      required is returned)  *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_value_get_TYP (void  * DiagHndl,  
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  int                      IN_max_val_len,
                  char                  *  OUT_kwd_val,
                  int                   *  OUT_kwd_val_len,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_value_get_TYP  ADI_value_get_CS;
 typedef  ADI_value_get_TYP  * ADI_value_get_PTR;

 ESA_RC ADI_value_get (void              * DiagHndl,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  int                      IN_max_val_len,
                  char                  *  OUT_kwd_val,
                  int                   *  OUT_kwd_val_len,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_value_set                              *
 *                                                             *
 * DESCRIPTION    : Set value of keyword in addinfo table      *
 *                                                             *
 * INPUT          : Value to set                               *
 *                  Addinfo table                              *
 *                  Index to keyword entry                     *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was set          *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - value too long         * 
 *                  ESA_SOS           - Short on storage       *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_value_set_TYP (void *  DiagHndl, 
                  char                  *  IN_kwd_val,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_value_set_TYP  ADI_value_set_CS;
 typedef  ADI_value_set_TYP  * ADI_value_set_PTR;

 ESA_RC ADI_value_set (void             *  DiagHndl,
                  char                  *  IN_kwd_val,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_find_value_get                     *
 *                                                             *
 * DESCRIPTION    : Find the kwd and then get the value        *
 *                                                             *
 * INPUT          :                                            *
 *                  Addinfo table                              *
 *                  Keyword name                               *
 *                  Length of field receiving value            *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         :                                            *
 *                  Value                                      *
 *                  Value length                               *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was returned     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_KEY_NOT_FOUND - Keyword not found      *
 *                  ESA_LENGTH_ERR    - Length not enough (len * 
 *                                      required is returned)  *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_kwd_find_value_get_TYP (void * DiagHndl,  
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  char                  *  IN_kwd,
                  int                      IN_max_val_len,
                  char                  *  OUT_kwd_val,
                  int                   *  OUT_kwd_val_len,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_kwd_find_value_get_TYP  ADI_kwd_find_value_get_CS;
 typedef  ADI_kwd_find_value_get_TYP  * ADI_kwd_find_value_get_PTR;

 ESA_RC ADI_kwd_find_value_get (void    *  DiagHndl, 
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  char                  *  IN_kwd,
                  int                      IN_max_val_len,
                  char                  *  OUT_kwd_val,
                  int                   *  OUT_kwd_val_len,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_kwd_find_value_set                     *
 *                                                             *
 * DESCRIPTION    : Find the kwd and then set the value        *
 *                                                             *
 * INPUT          : keyword name                               *
 *                  Value to set                               *
 *                  Addinfo table                              *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was set          *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - value too long         * 
 *                  ESA_SOS           - Short on storage       *
 *                  ESA_KEY_NOT_FOUND - keyword not found      *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_kwd_find_value_set_TYP (void * DiagHndl,
                  char                  *  IN_kwd,
                  char                  *  IN_kwd_val,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_kwd_find_value_set_TYP  ADI_kwd_find_value_set_CS;
 typedef  ADI_kwd_find_value_set_TYP  * ADI_kwd_find_value_set_PTR;

  ESA_RC ADI_kwd_find_value_set (void    *  DiagHndl, 
                  char                  *  IN_kwd,
                  char                  *  IN_kwd_val,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  ADMIN_PARAMS_rec_typ  *  admin_params);


 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_value_reset                            *
 *                                                             *
 * DESCRIPTION    : Clear value of keyword in addinfo table    *
 *                                                             *
 * INPUT          :                                            *
 *                  Addinfo table                              *
 *                  entry index to keyword entry               *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was returned     *
 *                  ESA_ERR           - Input error            *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_value_reset_TYP (void * DiagHndl,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_value_reset_TYP  ADI_value_reset_CS;
 typedef  ADI_value_reset_TYP  * ADI_value_reset_PTR;

 ESA_RC ADI_value_reset (void           *  DiagHndl,
                  ADDINFO_rec_ptr          IN_addinfo_table,
                  int                      IN_addinfo_entry_index,
                  ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_value_concat                           *
 *                                                             *
 * DESCRIPTION    : Concatenate value to existing one          *
 *                                                             *
 * INPUT          :                                            *
 *                  Value to be added                          *
 *                  Separator to put before addition           *
 *                  Addinfo table                              *
 *                  Index to keyword entry                     *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - value was returned     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - Total value too long   *
 *                  ESA_SOS           - Short on storage       *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_value_concat_TYP (void     * DiagHndl,
                         char                  * IN_additional_val,
                         char                    IN_separator,
                         ADDINFO_rec_ptr         IN_addinfo_table,
                         int                     IN_addinfo_entry_index,
                         ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_value_concat_TYP  ADI_value_concat_CS;
 typedef  ADI_value_concat_TYP  * ADI_value_concat_PTR;

 ESA_RC ADI_value_concat (void                 * DiagHndl,
                         char                  * IN_additional_val,
                         char                    IN_separator,
                         ADDINFO_rec_ptr         IN_addinfo_table,
                         int                     IN_addinfo_entry_index,
                         ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_reset                            *
 *                                                             *
 * DESCRIPTION    : Reset table values so the table can be     *
 *                  re-used.                                   *
 *                                                             *
 * INPUT          :                                            *
 *                  table address                              *
 *                  flag - reset entries or just values        *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Oll Korrect            *
 *                  ESA_ERR           - Input error            *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_reset_TYP (void     * DiagHndl,
                        ADDINFO_rec_ptr         IN_addinfo_table,
                        ADI_reset_flag          IN_reset_flag,
                        ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_table_reset_TYP  ADI_table_reset_CS;
 typedef  ADI_table_reset_TYP  * ADI_table_reset_PTR;

 ESA_RC ADI_table_reset (void                 * DiagHndl,
                        ADDINFO_rec_ptr         IN_addinfo_table,
                        ADI_reset_flag          IN_reset_flag,
                        ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_alloc                            *
 *                                                             *
 * DESCRIPTION    : Allocate space for addinfo tables.         *
 *                  Each table is allocated separately, to     *
 *                  allow separate release or re-alloc.        *
 *                                                             *
 * INPUT          :                                            *
 *                  number of keywords in each table           *
 *                  number of tables needed                    *
 *                  caller eye catcher, for storage debug      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Vector of addinfo tables addresses         *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - ptrs returned          *
 *                  ESA_ERR           - Input error            *
 *                  ESA_SOS           - Short on storage       *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 ESA_RC ADI_table_alloc (int                     IN_num_keywords,
                         int                     IN_num_tables,
                         char                  * IN_eye_catcher,
                         ADDINFO_rec_ptr         OUT_addinfo_table[],
                         ADMIN_PARAMS_rec_typ  * admin_params);

 typedef ESA_RC ADI_table_alloc_TYP (void  * DiagHndl,
                        int                     IN_num_keywords,
                        int                     IN_num_tables,
                        char                  * IN_eye_catcher,
                        ADDINFO_rec_ptr         OUT_addinfo_table[],
                        ADMIN_PARAMS_rec_typ  * admin_params);
 extern   ADI_table_alloc_TYP    ADI_table_alloc_CS;
 typedef  ADI_table_alloc_TYP  * ADI_table_alloc_PTR;


 ESA_RC ADI_table_alloc_EX (void                 * DiagHndl,
                        int                     IN_num_keywords,
                        int                     IN_num_tables,
                        char                  * IN_eye_catcher,
                        ADDINFO_rec_ptr         OUT_addinfo_table[],
                        ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_free                             *
 *                                                             *
 * DESCRIPTION    : Free space of addinfo table                *
 *                                                             *
 * INPUT          :                                            *
 *                  address of addinfo table to free           *
 *                     (Ptr set to zero after free operation)  *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - table was freed        *
 *                  ESA_ERR           - Input error            *
 *                                                             *
 **************************************************************/
 ESA_RC ADI_table_free (
                       ADDINFO_rec_ptr       * IN_addinfo_table,
                       ADMIN_PARAMS_rec_typ  * admin_params);


 typedef ESA_RC ADI_table_free_TYP (void  * DiagHndl,
                       ADDINFO_rec_ptr       * IN_addinfo_table,
                       ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_table_free_TYP  ADI_table_free_CS;
 typedef  ADI_table_free_TYP  * ADI_table_free_PTR;

 ESA_RC ADI_table_free_EX (void              * DiagHndl,
                       ADDINFO_rec_ptr       * IN_addinfo_table,
                       ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_realloc                          *
 *                                                             *
 * DESCRIPTION    : Re-Allocate space for addinfo table        *
 *                                                             *
 * INPUT          :                                            *
 *                  number of keywords to ADD                  *
 *                  caller eye catcher, for storage debug      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Vector of addinfo tables addresses         *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - ptrs returned          *
 *                  ESA_ERR           - Input error            *
 *                  ESA_SOS           - Short on storage       *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_realloc_TYP (void     * DiagHndl,
                          int                     IN_num_kwds_add,
                          ADDINFO_rec_ptr         IN_addinfo_table,
                          ADDINFO_rec_ptr       * OUT_addinfo_table,
                          ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_table_realloc_TYP  ADI_table_realloc_CS;
 typedef  ADI_table_realloc_TYP  * ADI_table_realloc_PTR;

 ESA_RC ADI_table_realloc (void                 * DiagHndl,
                          int                     IN_num_kwds_add,
                          ADDINFO_rec_ptr         IN_addinfo_table,
                          ADDINFO_rec_ptr       * OUT_addinfo_table,
                          ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_copy                             *
 *                                                             *
 * DESCRIPTION    : Copy table contents to another.            *
 *                  The target table must be able to contain at*
 *                  least the full entries from the source     *
 *                  table - the number of free entries in the  *
 *                  target table is more than the source full  *
 *                  entries.                                   *
 *                                                             *
 * INPUT          :                                            *
 *                  Table to copy TO                           *
 *                  Table to copy FROM                         *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Contents copied        *
 *                  ESA_ERR           - Input error            *
 *                  ESA_EOF           - Target table too small *
 *                  ESA_SOS           - Short on storage       *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_copy_TYP (void     * DiagHndl,
                       ADDINFO_rec_ptr         IN_addinfo_table_to,
                       ADDINFO_rec_ptr         IN_addinfo_table_from,
                       ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_table_copy_TYP  ADI_table_copy_CS;
 typedef  ADI_table_copy_TYP  * ADI_table_copy_PTR;

 ESA_RC ADI_table_copy (void                 * DiagHndl,
                       ADDINFO_rec_ptr         IN_addinfo_table_to,
                       ADDINFO_rec_ptr         IN_addinfo_table_from,
                       ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_diag                             *
 *                                                             *
 * DESCRIPTION    : Display table contents (for diagnosys).    *
 *                  The display is thru the DIAG mechanism.    *
 *                  A flag lets you control the display of     *
 *                  keywords that has no value.                *
 *                                                             *
 * INPUT          :                                            *
 *                  addinfo table address                      *
 *                  print_if_empty   -  1 print in any case    *
 *                                   -  0 print only if value  *
 *                                        length > 0           *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Contents displayed     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_diag_TYP (void     * DiagHndl, 
                       ADDINFO_rec_ptr         IN_addinfo_table,
                       int                     IN_print_if_empty,
                       ADMIN_PARAMS_rec_typ  * admin_params);

extern   ADI_table_diag_TYP  ADI_table_diag_CS;
typedef  ADI_table_diag_TYP  * ADI_table_diag_PTR;

 ESA_RC ADI_table_diag (void                 * DiagHndl,
                       ADDINFO_rec_ptr         IN_addinfo_table,
                       int                     IN_print_if_empty,
                       ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_from_buffer                      *
 *                                                             *
 * DESCRIPTION    : Build addinfo table from a buffer of       *
 *                  null-terminated pairs (kwd,type,value).    *
 *                                                             *
 * INPUT          :                                            *
 *                  Buffer of null-terminated pairs            *
 *                  Buffer length                              *
 *                  addinfo table address                      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : None                                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Contents displayed     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_from_buffer_TYP (void  * DiagHndl,
                           char                  * IN_buff,
                           int                     IN_buff_len,
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_table_from_buffer_TYP  ADI_table_from_buffer_CS;
 typedef  ADI_table_from_buffer_TYP  * ADI_table_from_buffer_PTR;

 ESA_RC ADI_table_from_buffer (void              * DiagHndl, 
                           char                  * IN_buff,
                           int                     IN_buff_len,
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_table_to_buffer                        *
 *                                                             *
 * DESCRIPTION    : Unpack addinfo table to a buffer of        *
 *                  null-terminated pairs (kwd,type,value).    *
 *                                                             *
 * INPUT          :                                            *
 *                  Buffer allocated length                    *
 *                  addinfo table address                      *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Buffer of keywords and values              *
 *                  Length of buffer contents                  *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - Contents displayed     *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - Buffer too short       *
 *                  ESA_FATAL         - Other errors           *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_table_to_buffer_TYP (void    * DiagHndl,
                           int                     IN_buff_len,
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           char                  * OUT_buff,
                           int                   * OUT_buff_len,
                           ADMIN_PARAMS_rec_typ  * admin_params);

extern   ADI_table_to_buffer_TYP  ADI_table_to_buffer_CS;
typedef  ADI_table_to_buffer_TYP  * ADI_table_to_buffer_PTR;

 ESA_RC ADI_table_to_buffer (void                * DiagHndl,
                           int                     IN_buff_len,
                           ADDINFO_rec_ptr         IN_addinfo_table,
                           char                  * OUT_buff,
                           int                   * OUT_buff_len,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_list_search                            *
 *                                                             *
 * DESCRIPTION    : Locate an item in addinfo list value       *
 *                                                             *
 * INPUT          : list     - list string (items spearted by  *
 *                             commas)                         *
 *                  item     - searched item                   *
 *                  sep      - the separator used in the list  *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : Pointer to item inside list (if rc=OK)     *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK           - Item found, ptr returned*
 *                  ESA_ERR          - Input error             *
 *                  ESA_KEY_NOT_FOUND- Item not found          *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_list_search_TYP (void      *  DiagHndl, 
                         char                  *  IN_list, 
                         char                  *  IN_item, 
                         char                     IN_separator,
                         char                  ** OUT_ptr,
                         ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_list_search_TYP  ADI_list_search_CS;
 typedef  ADI_list_search_TYP  * ADI_list_search_PTR;

 ESA_RC ADI_list_search (void                  *  DiagHndl,
                         char                  *  IN_list, 
                         char                  *  IN_item, 
                         char                     IN_separator,
                         char                  ** OUT_ptr,
                         ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_list_diff                              *
 *                                                             *
 * DESCRIPTION    : Build a list of items found in first       *
 *                  list, but not in second list.              *
 *                                                             *
 * INPUT          : first list                                 *
 *                  second list                                *
 *                  separator used in input lists              *
 *                  sepearator to be used in output list       *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : List of items not in list2                 *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK           - Item found, ptr returned*
 *                  ESA_ERR          - Input error             *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_list_diff_TYP (void         *  DiagHndl,
                          char                  *  IN_list1,
                          char                  *  IN_list2,
                          char                     IN_input_sep,
                          char                     IN_output_sep,
                          char                  *  OUT_list,
                          ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_list_diff_TYP  ADI_list_diff_CS;
 typedef  ADI_list_diff_TYP  * ADI_list_diff_PTR;

ESA_RC ADI_list_diff (    void                  *  DiagHndl, 
                          char                  *  IN_list1,
                          char                  *  IN_list2,
                          char                     IN_input_sep,
                          char                     IN_output_sep,
                          char                  *  OUT_list,
                          ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_list_convert_sep                       *
 *                                                             *
 * DESCRIPTION    : Convert string containing old seperators   *
 *                  to new seperators                          *
 *                                                             *
 * INPUT          : list to convert                            *
 *                  source entry separator                     *
 *                  source subfield  separator                 *
 *                  target entry separator                     *
 *                  target subfield  separator                 *
 *                  admin_params                               *
 *                                                             *
 * input/output   : input list converted                       *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK           - Item found, ptr returned*
 *                  ESA_ERR          - Input error             *
 *                  ESA_KEY_NOT_FOUND- Item not found          *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_list_convert_sep_TYP (void * DiagHndl,
                   char                  *  INOUT_list,
                   char                     IN_src_entry_sep,
                   char                     IN_src_subf_sep,
                   char                     IN_trg_entry_sep,
                   char                     IN_trg_subf_sep,
                   ADMIN_PARAMS_rec_typ  *  admin_params);

 extern   ADI_list_convert_sep_TYP  ADI_list_convert_sep_CS;
 typedef  ADI_list_convert_sep_TYP  * ADI_list_convert_sep_PTR;

 ESA_RC ADI_list_convert_sep (void       *  DiagHndl, 
                   char                  *  INOUT_list,
                   char                     IN_src_entry_sep,
                   char                     IN_src_subf_sep,
                   char                     IN_trg_entry_sep,
                   char                     IN_trg_subf_sep,
                   ADMIN_PARAMS_rec_typ  *  admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_list_to_string                         *
 *                                                             *
 * DESCRIPTION    : Convert one-dimentional addinfo list (1    *
 *                  subfield in each row) to a comma-separated *
 *                  string.                                    *
 *                                                             *
 * INPUT          :                                            *
 *                  value list                                 *
 *                  maximum length for output                  *
 *                  entry separator for output                 *
 *                  subfield separator for output              *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : String made from list                      *
 *                  Length of string (if RC /= ERR)            *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - output prepared        *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - Output too short       *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_list_to_string_TYP (void      * DiagHndl,
                            char                  * IN_list,
                            int                     IN_max_out_len,
                            char                    IN_entry_separator,
                            char                    IN_subfield_separator,
                            char                  * OUT_string,
                            int                   * OUT_max_len,
                            ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_list_to_string_TYP  ADI_list_to_string_CS;
 typedef  ADI_list_to_string_TYP  * ADI_list_to_string_PTR;

 ESA_RC ADI_list_to_string (void                  * DiagHndl,
                            char                  * IN_list,
                            int                     IN_max_out_len,
                            char                    IN_entry_separator,
                            char                    IN_subfield_separator,
                            char                  * OUT_string,
                            int                   * OUT_max_len,
                            ADMIN_PARAMS_rec_typ  * admin_params);

 /**************************************************************
 *                                                             *
 * PROCEDURE NAME : ADI_list_from_string                       *
 *                                                             *
 * DESCRIPTION    : Convert comma-separated string to addinfo  *
 *                  list.                                      *
 *                                                             *
 * INPUT          :                                            *
 *                  value list                                 *
 *                  maximum length for output                  *
 *                  entry separator for output                 *
 *                  subfield separator for output              *
 *                  admin_params                               *
 *                                                             *
 * OUTPUT         : String made from list                      *
 *                  Length of string (if RC /= ERR)            *
 *                                                             *
 * RETURN VALUE   : ESA_RC                                     *
 *                  ESA_OK            - output prepared        *
 *                  ESA_ERR           - Input error            *
 *                  ESA_LENGTH_ERR    - Output too short       *
 *                                                             *
 **************************************************************/

 typedef ESA_RC ADI_list_from_string_TYP (void    * DiagHndl, 
                            char                  * IN_string,
                            int                     IN_max_out_len,
                            char                    IN_entry_separator,
                            char                    IN_subfield_separator,
                            char                  * OUT_list,
                            int                   * OUT_max_len,
                            ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_list_from_string_TYP  ADI_list_from_string_CS;
 typedef  ADI_list_from_string_TYP  * ADI_list_from_string_PTR;

 ESA_RC ADI_list_from_string (void                * DiagHndl,
                            char                  * IN_string,
                            int                     IN_max_out_len,
                            char                    IN_entry_separator,
                            char                    IN_subfield_separator,
                            char                  * OUT_list,
                            int                   * OUT_max_len,
                            ADMIN_PARAMS_rec_typ  * admin_params);

 /***************************************************************
 *                                                              *
 * PROCEDURE NAME : ADI_list_entry_append_start                 *
 *                                                              *
 * DESCRIPTION    : Call before adding a new entry to a list,   *
 *                  for first and subsequent entries.           * 
 *                                                              *
 * INPUT          : Pointer to start of list field              *
 *                : Offset  to current position in field        *
 *                  admin_params                                *
 *                                                              *
 * OUTPUT         : Offset updated to new position              *
 *                                                              *
 * RETURN VALUE   : ESA_RC                                      *
 *                  ESA_OK            - offset returned         *
 *                  ESA_ERR           - Input error             *
 *                                                              *
 ***************************************************************/

 typedef ESA_RC ADI_list_entry_append_start_TYP (void * DiagHndl,
                           char                  * IN_list_ptr,
                           int                   * INOUT_entry_offset,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 extern    ADI_list_entry_append_start_TYP  ADI_list_entry_append_start_CS;
 typedef   ADI_list_entry_append_start_TYP  * ADI_list_entry_append_start_PTR;

 ESA_RC ADI_list_entry_append_start (void        * DiagHndl,
                           char                  * IN_list_ptr,
                           int                   * INOUT_entry_offset,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 /***************************************************************
 *                                                              *
 * PROCEDURE NAME : ADI_list_subfield_get_next                  *
 *                                                              *
 * DESCRIPTION    : Used in processing of subfields in a list.  *
 *                                                              *
 *                  Will return the subfield value, and update  *
 *                  the offset for next time.                   *
 *                  Call the first time with offset = 0, and    *
 *                  make the next call with the offset returned *
 *                  last time.                                  *
 *                                                              *
 *                  When all the subfields in the entry will be *
 *                  processed, the function will return         *
 *                  ESA_KEY_NOT_FOUND (with no value), but the  *
 *                  offset will advance to next subf.           *
 *                  When all entries are done return ESA_EOF    *
 *                                                              *
 *                  NOTE !!!! rc = ESA_EOF/ESA_KEY_NOT_FOUND    *
 *                            will be returned WITH the value at*
 *                            the last call.                    *
 *                                                              *
 *                  The caller will do:                         *
 *                                                              *
 *             ADI_value_get()  Get value into temp field       *
 *                                                              *         
 *             subf_offset = 0                                  *
 *             While (1) {                                      *
 *                                                              *
 *                 rc= ADI_list_subfield_get_next(subf_offset)  *
 *                                                              *
 *                 if (rc EQ ESA_EOF) {                         *
 *                    .... process end of all data              *  
 *                    break;                                    *
 *                 }                                            *
 *                                                              *
 *                 if (rc EQ ESA_KEY_NOT_FOUND) {               *
 *                     process appropriate to new entry         *
 *                     continue;                                *
 *                 }                                            *
 *                                                              * 
 *                 if (rc NE ESA_OK)                            *
 *                    error - die                               * 
 *                                                              * 
 *                 .... process subfield data                   *
 *                                                              *  
 *                                                              *
 *             }  end while                                     *
 *                                                              *
 *                                                              *
 *                                                              *
 * INPUT          :                                             *
 *                  Ptr to entire value field (type list)       *
 *                  Current offset inside the a list value      *
 *                  admin_params                                *
 *                                                              *
 * OUTPUT         : Offset updated to next subf                 *
 *                  subfield content returned                   * 
 *                                                              *
 * RETURN VALUE   : ESA_RC                                      *
 *                  ESA_OK            - Pointer updated         *
 *                  ESA_ERR           - Input error             *
 *                  ESA_EOF           - End of value reached    *
 *                  ESA_KEY_NOT_FOUND - End of entry reached    *
 *                                                              *
 ***************************************************************/

 typedef ESA_RC ADI_list_subfield_get_next_TYP (void * DiagHndl,
                           char                  * IN_value,
                           size_t                * INOUT_next_subf,
                           char                  * OUT_subf_data, 
                           ADMIN_PARAMS_rec_typ  * admin_params);

 extern    ADI_list_subfield_get_next_TYP ADI_list_subfield_get_next_CS;
 typedef   ADI_list_subfield_get_next_TYP * ADI_list_subfield_get_next_PTR;

 ESA_RC ADI_list_subfield_get_next (void         * DiagHndl,
                           char                  * IN_value,
                           size_t                * INOUT_next_subf,
                           char                  * OUT_subf_data, 
                           ADMIN_PARAMS_rec_typ  * admin_params);

 /***************************************************************
 *                                                              *
 * PROCEDURE NAME : ADI_list_subfield_append_TYP                *
 *                                                              *
 * DESCRIPTION    : Call before adding a new subf to a list     *
 *                                                              *
 * INPUT          : Pointer to start of list field              *
 *                  Value of subfield to append                 *
 *                  Offset  to current position in list         *
 *                  admin_params                                *
 *                                                              *
 * OUTPUT         : Offset updated to new position              *
 *                                                              *
 * RETURN VALUE   : ESA_RC                                      *
 *                  ESA_OK            - offset returned         *
 *                  ESA_ERR           - Input error             *
 *                                                              *
 ***************************************************************/

 typedef ESA_RC ADI_list_subfield_append_TYP (void * DiagHndl,
                           char                  * IN_list_ptr,
                           char                  * IN_value_add,
                           int                   * INOUT_subfield_offset,
                           ADMIN_PARAMS_rec_typ  * admin_params);

 extern   ADI_list_subfield_append_TYP ADI_list_subfield_append_CS;
 typedef  ADI_list_subfield_append_TYP * ADI_list_subfield_append_PTR;

 ESA_RC ADI_list_subfield_append (void           * DiagHndl,
                           char                  * IN_list_ptr,
                           char                  * IN_value_add,
                           int                   * INOUT_subfield_offset,
                           ADMIN_PARAMS_rec_typ  * admin_params);

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_ADDINFO_C ();
void DATA_COMP_ADDINFO__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_ADDINFO__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
   DATA_COMP_ADDINFO_C ();
}
#endif
#endif  /* ADI_H_included */

