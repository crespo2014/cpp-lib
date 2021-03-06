/**************************************************************
* Title            : Messages services                        *
* File Name        : ctsamsg.h                                *
* Author           : Doron Cohen                              *
* Creation Date    : 03/04/94                                 *
* Description      :                                          *
* Assumptions and                                             *
*   Considerations :                                          *
* $Author:   avi_w  $
* $Workfile:   ctsamsg.h  $
* $Revision:   1.0  $
* $Log:   //EAGLE1/VERSIONS/300/COMMON/INC/ctsamsg.h_v  $
 * 
 *    Rev 1.0   Aug 31 1998 19:02:06   avi_w
 *  
 * 
 *    Rev 1.4   Jan 21 1998 18:53:40   leonid_s
 * 300-Beta with AS400 & VMS changes 
 *
 *    Rev 1.3   Jul 27 1997 10:32:34   Danko
 * converting_from_sccs
 *
 *    Rev 1.2   Jul 24 1997 08:29:48   leonid_s
 *     SCCSID("%Z%%M% \
 *
 *
 *    Rev 1.1   Jul 08 1997 10:08:52   avi_w
 *
**************************************************************/
/* SCCSID %Z%%M% */

#ifndef CTSAMSG_H_included
#define CTSAMSG_H_included

#ifdef EXT
#undef EXT
#endif
#ifndef CTSAMSG_owner
#define EXT extern
#else
#define EXT
#endif

#ifdef MVS
#define CTSAMSG_initdest               ctsms01
#define CTSAMSG_termdest               ctsms02
#define CTSAMSG_load                   ctsms03
#define CTSAMSG_print                  ctsms04
#define CTSAMSG_print_direct           ctsms05
#define CTSAMSG_free                   ctsms06
#define CTSAMSG_dump                   ctsms07
#define CTSAMSG_dest_table_alloc       ctsms08
#define CTSAMSG_dest_table_free        ctsms09
#define CTSAMSG_dest_table_init        ctsms10
#define CTSAMSG_initialize             ctsms11
#endif

#ifdef     WNTINC
#include   "stdarg.h"
#else
#include   STDARG
#endif

#define CTSAMSG_MAX_GEN_NAME       "LOGS_MAX_GEN"
#define CTSAMSG_MAX_LINES_NAME     "LOGS_MAX_LINES"
#define CTSAMSG_MAX_INTERVAL_NAME  "LOGS_MAX_DAYS"

#define CTSAMSG_MAX_GEN_VAL            7
#define CTSAMSG_MAX_LINES_VAL       1000
#define CTSAMSG_MAX_INTERVAL_VAL       0

#define CTSAMSG_MSG_LEN             2048
#define CTSAMSG_MSGID_LEN             12
#define CTSAMSG_FORMAT_LEN           133
#define CTSAMSG_DEST_LEN            1024
#define CTSAMSG_LINE_LEN            1024

#define CTSAMSG_DEFAULT_BUFFER_INIT  500
#define CTSAMSG_DEFAULT_BUFFER_INC   250

#define CTSAMSG_size(num)                 \
        (num)*sizeof(CTSAMSG_MSG_rec_typ)

#define CTSAMSG_ALERT_CHAR 'a'
#define CTSAMSG_BS_CHAR    'b'
#define CTSAMSG_FF_CHAR    'f'
#define CTSAMSG_NL_CHAR    'n'
#define CTSAMSG_CR_CHAR    'r'
#define CTSAMSG_HT_CHAR    't'
#define CTSAMSG_VT_CHAR    'v'

#define CTSAMSG_ALERT_CODE '\a'
#define CTSAMSG_BS_CODE    '\b'
#define CTSAMSG_FF_CODE    '\f'
#define CTSAMSG_NL_CODE    '\n'
#define CTSAMSG_CR_CODE    '\r'
#define CTSAMSG_HT_CODE    '\t'
#define CTSAMSG_VT_CODE    '\v'

/* Macro to be used by caller to CTSAMSG_load to check result &
 * report error to stderr if failed.
 */

#define LOAD_REPORT(F,RC) \
    if ((RC) NE ESA_OK)   \
       fprintf (stderr,   \
           "CTSAMSG_load failed on file %s, rc = %ld...proceeding\n",\
           (F), (RC));

/* CTSAMSG entities type definitions */

typedef char CTSAMSG_MSG_typ    [ CTSAMSG_MSG_LEN    + 1 ];
typedef char CTSAMSG_MSGID_typ  [ CTSAMSG_MSGID_LEN  + 1 ];
typedef char CTSAMSG_FORMAT_typ [ CTSAMSG_FORMAT_LEN + 1 ];

/* Duplicate msgid action flag */

typedef enum {
    DUP_IGNORE, DUP_OVERRIDE, DUP_FAIL
} CTSAMSG_DUPLICATE_typ;

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
    DEST_FILE, DEST_FILE_APPEND, DEST_ERR, DEST_USER, DEST_CONSOLE,
    DEST_CONSOLE2
} CTSAMSG_DEST_TYPE_typ;

/* Loaded Messages entry   */

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

/* Destination Handling Functions */

typedef ESA_RC CTSAMSG_INITFUNC (void              *dest_name,
                                 void             **handle);

typedef ESA_RC CTSAMSG_PRTFUNC (void                    *dest_name,
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

/* Messages Parameters */

typedef struct S_PARAMS_STRUCT {
    CTSAMSG_HANDLE_rec_typ     * ctsamsg_handle;
    CTSAMSG_DEST_TABLE_rec_typ * ctsamsg_dest;
} CTSAMSG_PARAMS_rec_typ, *CTSAMSG_PARAMS_rec_ptr;

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_initialize                       *
*                                                             *
* Description      : Initialize CTSAMSG handle                *
*                                                             *
* Input            :  1) dh             -  esa_diag handle    *
*                                                             *
* Output           :  1) handle         -  ctsamsg handle     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_initialize ( CTSAMSG_HANDLE_rec_typ * handle,
                                void                   * dh );

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_load                             *
*                                                             *
* Description      : Load Messages file into storage          *
*                                                             *
* Input            :  1) msg_file_name  -  file name          *
*                     2) handle         -  buffer handle      *
*                     3) dupflag        -  duplicate entries  *
*                                          action flag        *
*                          IGNORE   - will ignore new entries *
*                                     that already exist      *
*                          OVERRIDE - will update existing    *
*                                     entries with newly read *
*                                     format                  *
*                          FAIL     - will fail entire loading*
*                                     if entries already exist*
*                     4) rlsflag        -  release unused     *
*                                                             *
*                          YES      - will release any unused *
*                                     buffer storage area     *
*                                     when loading finished   *
*                          NO       - will leave unused areas *
*                                     at the end of the buffer*
*                                                             *
* Output           : None                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_load (char                   * msg_file_name,
                         CTSAMSG_HANDLE_rec_typ * handle,
                         CTSAMSG_DUPLICATE_typ    dupflag,
                         CTSAMSG_FLAG_typ         rlsflag) ;

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_free                             *
*                                                             *
* Description      : Free messages buffer and clears handle   *
*                                                             *
* Input / Output   : handle                                   *
*                                                             *
* Return Value     : None                                     *
*                                                             *
**************************************************************/

EXT void CTSAMSG_free (CTSAMSG_HANDLE_rec_typ * handle);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_initdest                         *
*                                                             *
* Description      : Initialize destinations                  *
*                                                             *
* Input            :  1) dest      -  dest table              *
*                     2) handle    -  ctsamsg handle          *
*                                                             *
* Output           : none                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
* Comments         : For each destination, the destination    *
*                    initialization function is called.       *
*                    It is the responsibility of the          *
*                    initialization function to allocate an   *
*                    handle (for printing function usage)     *
*                    and set the appropriate handle pointer.  *
*                    All destination are initialized until    *
*                    a destination initialization routine     *
*                    returns an ESA_FATAL rc or the requested *
*                    number of destinations is reached .      *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_initdest (CTSAMSG_DEST_TABLE_rec_typ * dest,
                             CTSAMSG_HANDLE_rec_typ     * handle);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_termdest                         *
*                                                             *
* Description      : Terminate destinations                   *
*                                                             *
* Input            :  1) dest      -  dest table              *
*                     2) handle    -  ctsamsg handle          *
*                                                             *
* Output           : none                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
* Comments         : For each destination, the destination    *
*                    termination function is called.          *
*                    It is the responsibility of the          *
*                    termination function to cleanup the      *
*                    handle (used by printing function)       *
*                    and clear the appropriate handle pointer.*
*                    All destination are terminated until     *
*                    a destination termination routine        *
*                    returns an ESA_FATAL rc or the requested *
*                    number of destinations is reached .      *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_termdest (CTSAMSG_DEST_TABLE_rec_typ * dest,
                             CTSAMSG_HANDLE_rec_typ     * handle);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_print                            *
*                                                             *
* Description      : Issue a message to the requested         *
*                    destinations                             *
*                                                             *
* Input            : 1) msgid   - msgid to be printed         *
*                    2) handle  - loaded messages handle      *
*                    3) buffer  - output buffer for formatted *
*                                 message or NULL .           *
*                    4) dest    - destinations table          *
*                    5) ...     - arguments for message       *
*                                                             *
* Output           : None                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
* Comments         : The function process the arg list and    *
*                    calls CTSAMSG_print_direct               *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_print (const char                 * msgid,
                          CTSAMSG_HANDLE_rec_typ     * handle,
                          char                       * buffer,
                          CTSAMSG_DEST_TABLE_rec_typ * dest,
                          ... );

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_print_direct                     *
*                                                             *
* Description      : Issue a message to the requested         *
*                    destinations                             *
*                                                             *
* Input            : 1) msgid   - msgid to be printed         *
*                    2) handle  - loaded messages handle      *
*                    3) buffer  - output buffer for formatted *
*                                 message or NULL .           *
*                    4) dest    - destinations table          *
*                    5) arglist - arguments for message       *
*                                                             *
* Output           : None                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
* Comments         : Message is located in the loaded messages*
*                    buffer and formatted to the output       *
*                    buffer.                                  *
*                    For each destination, the destination    *
*                    print function is called until           *
*                    a destination print function returns an  *
*                    ESA_FATAL rc or the requested            *
*                    number of destinations is reached .      *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_print_direct (
                          const char                 * msgid,
                          CTSAMSG_HANDLE_rec_typ     * handle,
                          char                       * buffer,
                          CTSAMSG_DEST_TABLE_rec_typ * dest,
                          va_list                      arglist);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_dump                             *
*                                                             *
* Description      : Dump Loaded Messages buffer contents     *
*                                                             *
* Input            : 1) handle                                *
*                                                             *
* Output           : None                                     *
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_dump (CTSAMSG_HANDLE_rec_typ * handle);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_dest_table_free                  *
*                                                             *
* Description      : Free area of destination table           *
*                                                             *
* Input/Output     : 1) dest_table - destination table pointer*
*                                                             *
* Return Value     : ESA_RC                                   *
*                                                             *
**************************************************************/

EXT ESA_RC CTSAMSG_dest_table_free (
                           CTSAMSG_DEST_TABLE_rec_typ * dest_t);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_dest_table_alloc                 *
*                                                             *
* Description      : Allocate a destination table             *
*                                                             *
* Input            : 1) numdest -  number of destinations     *
*                                                             *
* Output           : None                                     *
*                                                             *
* Return Value     : Pointer to destination table             *
*                                                             *
**************************************************************/

EXT CTSAMSG_DEST_TABLE_rec_typ * CTSAMSG_dest_table_alloc (
                                        short num_dest);

/**************************************************************
*                                                             *
* Procedure Name   : CTSAMSG_dest_table_init                  *
*                                                             *
* Description      : Initialize destination table destinations*
*                                                             *
* Input/Output     : 1) dest_t - destination table pointer    *
*                                                             *
* Return Value     : None                                     *
*                                                             *
**************************************************************/

EXT void CTSAMSG_dest_table_init (CTSAMSG_DEST_TABLE_rec_typ * dest_t);

#endif  /* CTSAMSG_H_included */
