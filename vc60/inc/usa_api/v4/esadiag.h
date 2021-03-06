/*****************************************************
* Title           : Diagnostics
* File Name       : esadiag.h
* Author          : Atzmon (@ Liraz)
* Creation Date   : 20-Feb-94
* Description     : Interface to diagnostic printouts
* Assumptions and
*   Considerations:
*****************************************************/

/*
 * Version Information:
 * ====================
 * File name       : %name: esadiag.h %
 * Instance        : %instance: 1 %
 * Created by      : %created_by: leonid_s %
 * Created on      : %date_created: Thu Sep 23 12:24:12 2004 %
 * Current Version : %version: 6 %
 * Last Modified by: %derived_by: leonid_s %
 * Last Modified on: %date_modified: Thu Jan 08 11:22:23 2004 %
 */

#ifndef ESA_DIAG_INCLUDED
#define ESA_DIAG_INCLUDED

typedef int  ESA_DIAG_LEVEL_typ;
typedef int  ESA_DIAG_COMP_typ;

#define ENTER_DIAG_LEVEL_1     2
#define ENTER_DIAG_LEVEL_2     5
#define ENTER_DIAG_LEVEL_3     8
#define ENTER_DIAG_LEVEL_4    11
#define ENTER_DIAG_LEVEL_5    14

#if defined (MVS)
#define ESA_DIAGLL_printf               EDG0001
#define ESA_DIAGR_check                 EDG0002
#define ESA_DIAGR_enter                 EDG0003
#define ESA_DIAGR_exit                  EDG0004
#define ESA_DIAGR_get_debug_level       EDG0005
#define ESA_DIAGR_initialize            EDG0006
#define ESA_DIAGR_printf                EDG0007
#define ESA_DIAGR_set_debug_levels      EDG0008
#define ESA_DIAGR_set_debug_levels_file EDG0009
#define ESA_DIAGR_terminate             EDG0010
#define ESA_DIAG_check                  EDG0011
#define ESA_DIAG_enter                  EDG0012
#define ESA_DIAG_exit                   EDG0013
#define ESA_DIAG_get_debug_level        EDG0014
#define ESA_DIAG_initialize             EDG0015
#define ESA_DIAG_printf                 EDG0016
#define ESA_DIAG_set_debug_levels       EDG0017
#define ESA_DIAG_set_debug_levels_file  EDG0018
#define ESA_rc2str                      EDG0019
#define ESA_DIAG_activate               EDG0020
#define ESA_DIAG_deactivate             EDG0021
#define ESA_DIAGR_activate              EDG0022
#define ESA_DIAGR_deactivate            EDG0023
#define ESA_DIAG_get_lvls_arr_size      EDG0024
#define ESA_DIAG_get_file_name_size     EDG0025
#define ESA_DIAG_get_shdw_fname_size    EDG0026
#define ESA_DIAGR_get_diag_info         EDG0027
#define ESA_DIAG_COMP_LEVELS            EDG0028
#define ESA_DIAG_initializeEx           EDG0029
#define ESA_DIAGR_initializeEx          EDG0030
#define ESA_DIAGR_exitEx                EDG0031
#define ESA_DIAG_exitEx                 EDG0032
#define DATA_COMP_ESADIAG_C             EDG0033
#define DATA_COMP_ESADIAG__             EDG0034
#define ESA_vsprintf                    EDG0035
#define ESA_DIAG_memory_status          EDG0036
#define ESA_DIAG_print_stack            EDG0037
#define ESA_DIAG_close_files            EDG0038
#define ConvertTimeToTMStruct           EDG0039
#endif /* MVS */

/* include STDARG since some functions have a va_list parameter */
#ifdef   WNTINC
#include "stdarg.h"
#include "string.h"
#include "time.h"
#else
#include STDARG
#include STRING
#include TIME
#endif

#if defined (UNIX)
#include <sys/types.h>    /* A2Z001, 05-Nov-2001 */
#endif

/*****************************************************************
 *  PROCEDURE NAME : ESA_DIAG_initialize
 *  DESCRIPTION    : Calls ESA_DIAG_initializeEx that initializes the ESA_DIAG module.
 *  INPUT          : log_file_name    - Name of log file.
 *                   shadow_file_name - Name of shadow file.
 *                   procname         - Name of program.
 *  OUTPUT         : handle
 *  RETURN VALUE   : None
 *  RE-ENTRANT     : No
 ****************************************************************/

extern void ESA_DIAG_initialize (const char  * log_file_name,
                                 const char  * shadow_file_name,
                                 const char  * procname,
                                 void       ** handle);

/*****************************************************************
 *  PROCEDURE NAME : ESA_DIAG_initializeEx
 *  DESCRIPTION    : Initializes the ESA_DIAG module.
 *  INPUT          : log_file_name    - Name of log file.
 *                   shadow_file_name - Name of shadow file.
 *                   procname         - Name of program.
 *                   min_free_space   - Free space limit to keep when DIAG issued
 *  OUTPUT         : handle
 *  RETURN VALUE   : None
 *  RE-ENTRANT     : No
 ****************************************************************/

extern void ESA_DIAG_initializeEx (const char  * log_file_name,
                                   const char  * shadow_file_name,
                                   const char  * procname,
                                   int           min_free_space,
								   int           pid_number,  
                                   void       ** handle);

/****************************************************
 * Procedure Name: ESA_DIAGR_initialize
 * Description   : Calls ESA_DIAGR_initializeEx that initializes the ESA_DIAG module.
 * Input         : log_file_name    - Name of log file.
 *                 shadow_file_name - Name of shadow file.
 *                 procname         - Name of program.
 * output        : handle
 * Return Value  : None
 * Side Effects  : Global variables are set.
 * Scope         : Global
 * Comments      : 1. The special strings "STDOUT" and "STDERR",
 *                    if supplied in log_file_name and/or
 *                    shadow_file_name, will use these predefined
 *                    streams.
 *                 2. If the file == NULL DEVICE, no file is open.
 *                    See platform.h for the meaning of NULL DEVICE.
 * RE-ENTRANT    : Yes
 ****************************************************/

extern void ESA_DIAGR_initialize (const char  * log_file_name,
                                  const char  * shadow_file_name,
                                  const char  * procname,
                                  void       ** handle);

/****************************************************
 * Procedure Name: ESA_DIAGR_initializeEx
 * Description   : Initializes the ESA_DIAG module.
 * Input         : log_file_name    - Name of log file.
 *                 shadow_file_name - Name of shadow file.
 *                 procname         - Name of program.
 *                 min_free_space   - Free space limit to keep when DIAG issued
 * output        : handle
 * Return Value  : None
 * Side Effects  : Global variables are set.
 * Scope         : Global
 * Comments      : 1. The special strings "STDOUT" and "STDERR",
 *                    if supplied in log_file_name and/or
 *                    shadow_file_name, will use these predefined
 *                    streams.
 *                 2. If the file == NULL DEVICE, no file is open.
 *                    See platform.h for the meaning of NULL DEVICE.
 * RE-ENTRANT    : Yes
 ****************************************************/

extern void ESA_DIAGR_initializeEx (const char  * log_file_name,
                                    const char  * shadow_file_name,
                                    const char  * procname,
                                    int           min_free_space,
									int           pid_number,
                                    void       ** handle);

/****************************************************
 * Procedure Name: ESA_DIAGR_terminate
 * Description   : Terminates the ESA_DIAG module.
 * Input         : handle
 * output        : None
 * Return Value  : None
 * Side Effects  :
 * Scope         : Global
 * Comments      :
 * RE-ENTRANT    : Yes
 ****************************************************/

extern void ESA_DIAGR_terminate (void * handle);

/****************************************************
 * Procedure Name: ESA_DIAGLL_printf
 * Description   : printf-like diagnostics
 * Input         : Component, level, format, arguments
 * Output        :
 * Return Value  :
 * Side Effects  : VARARGS is used
 * Scope         : Global
 ****************************************************/

extern void ESA_DIAGLL_printf (ESA_DIAG_COMP_typ    comp,
                               ESA_DIAG_LEVEL_typ   level,
                               void               * handle,
                               const char         * format,
                               va_list              arg_list);

/****************************************************
 * Procedure Name: ESA_DIAG_printf
 * Description   : printf-like diagnostics
 * Input         : Component, level, format, arguments
 * Output        :
 * Return Value  :
 * Side Effects  : VARARGS is used
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_printf (ESA_DIAG_COMP_typ    comp,
                             ESA_DIAG_LEVEL_typ   level,
                             const char         * format, ...);

/****************************************************
 * Procedure Name: ESA_DIAGR_printf
 * Description   : printf-like diagnostics
 * Input         : Component, level, format, arguments
 * Output        :
 * Return Value  :
 * Side Effects  : VARARGS is used
 * Scope         : Global
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_printf (void               * handle,
                              ESA_DIAG_COMP_typ    comp,
                              ESA_DIAG_LEVEL_typ   level,
                              const char         * format, ...);

/****************************************************
 * Procedure Name: ESA_DIAG_enter
 * Description   : Push calling func name on stack, print message
 * Input         : component, level, func name
 * Output        : None
 * Return Value  : None
 * Side Effects  : None
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_enter (ESA_DIAG_COMP_typ    comp,
                            ESA_DIAG_LEVEL_typ   level,
                            const char         * funcname);

/****************************************************
 * Procedure Name: ESA_DIAG_enter
 * Description   : Push calling func name on stack, print message
 * Input         : component, level, func name
 * Output        : None
 * Return Value  : None
 * Side Effects  : None
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_enter (void               * handle,
                             ESA_DIAG_COMP_typ    comp,
                             ESA_DIAG_LEVEL_typ   level,
                             const char         * funcname);

/****************************************************
 * Procedure Name: ESA_DIAG_exit
 * Description   : pop function stack, print message
 * Input         : Component, level
 * Output        : None
 * Return Value  : None
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_exit (ESA_DIAG_COMP_typ    comp,
                           ESA_DIAG_LEVEL_typ   level,
                           const char         * funcname,
                           ESA_RC               rc_ret);

extern void ESA_DIAG_exitEx (ESA_DIAG_COMP_typ   comp,
                    ESA_DIAG_LEVEL_typ  level,
                    const char        * funcname,
                    ESA_RC              rc_ret,
                    ESA_RC              rc_func,
					int                 line,
					char              * source);


/****************************************************
 * Procedure Name: ESA_DIAGR_exit
 * Description   : pop function stack, print message
 * Input         : Component, level
 * Output        : None
 * Return Value  : None
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_exit (void               * handle,
                            ESA_DIAG_COMP_typ    comp,
                            ESA_DIAG_LEVEL_typ   level,
                            const char         * funcname,
                            ESA_RC               rc_ret);

extern void ESA_DIAGR_exitEx (void               * handle,
                       ESA_DIAG_COMP_typ    comp,
                       ESA_DIAG_LEVEL_typ   level,
                       const char         * funcname,
                       ESA_RC               rc_ret,
                       ESA_RC               rc_func,
                       int                  line,
                       char               * source);

/****************************************************
 * Procedure Name: ESA_DIAG_set_debug_levels
 * Description   : Set debug level for all components
 * Input         : Array of levels
 * Output        : None
 * Return Value  : None
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_set_debug_levels (
    ESA_DIAG_LEVEL_typ * level_array);

/****************************************************
 * Procedure Name: ESA_DIAG_set_debug_levels
 * Description   : Set debug level for all components
 * Input         : Array of levels
 * Output        : None
 * Return Value  : None
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_set_debug_levels (
    void               * handle,
    ESA_DIAG_LEVEL_typ * level_array);

/****************************************************
 * Procedure Name: ESA_DIAG_get_debug_level
 * Description   : return diag level of a component
 * Input         : Component
 * Output        : None
 * Return Value  : Level
 * Re-entrant    : No
 ****************************************************/

extern ESA_DIAG_LEVEL_typ ESA_DIAG_get_debug_level (
    ESA_DIAG_COMP_typ comp);

/****************************************************
 * Procedure Name: ESA_DIAG_get_debug_level
 * Description   : return diag level of a component
 * Input         : Component
 * Output        : None
 * Return Value  : Level
 * Re-entrant    : Yes
 ****************************************************/

extern ESA_DIAG_LEVEL_typ ESA_DIAGR_get_debug_level (
    void           * handle,
    ESA_DIAG_COMP_typ comp);

/****************************************************
 * Procedure Name: ESA_DIAG_set_debug_levels_file
 * Description   : Read levels from file, set debug level for
 *                 all components
 * Input         : File name
 * Output        :
 * Return Value  : ESA_RC
 * Side Effects  : Static array is modified
 * Re-entrant    : No
 ****************************************************/

extern ESA_RC ESA_DIAG_set_debug_levels_file (const char        * fname,
									          int                 p_main_name);

/****************************************************
 * Procedure Name: ESA_DIAG_set_debug_levels_file
 * Description   : Read levels from file, set debug level for
 *                 all components
 * Input         : File name
 * Output        :
 * Return Value  : ESA_RC
 * Side Effects  : Static array is modified
 * Re-entrant    : Yes
 ****************************************************/

extern ESA_RC ESA_DIAGR_set_debug_levels_file (void       * handle,
                                        const char        * fname,
										int                 MainName);

/****************************************************
 * Procedure Name: ESA_DIAG_check
 * Description   : Check whether log files can be opened
 * Input         : None
 * Output        : buffer - string with reason of failure (strerror)
 * Return Value  : ESA_RC
 * Side Effects  : If access() is N/A, files are opened & closed.
 * Scope         : Global
 * Comments      : 1. Uses access(), if available, else fopen().
 *                 2. NULL filenames, the null device
 *                    (/dev/null on UNIX) and stdout/stderr are assumed
 *                    to be writable.
 *                 3. If buffer is NULL, it's ignored.
 * Re-entrant    : No
 ****************************************************/

extern ESA_RC ESA_DIAG_check (char * errbuf);

/****************************************************
 * Procedure Name: ESA_DIAGR_check
 * Description   : Check whether log files can be opened
 * Input         : None
 * Output        : buffer - string with reason of failure (strerror)
 * Return Value  : ESA_RC
 * Side Effects  : If access() is N/A, files are opened & closed.
 * Scope         : Global
 * Comments      : 1. Uses access(), if available, else fopen().
 *                 2. NULL filenames, the null device
 *                    (/dev/null on UNIX) and stdout/stderr are assumed
 *                    to be writable.
 *                 3. If buffer is NULL, it's ignored.
 * Re-entrant    : Yes
 ****************************************************/

extern ESA_RC ESA_DIAGR_check (void * handle,
                               char * errbuf);

/****************************************************
 * Procedure Name: ESA_rc2str
 * Description   : Translate ESA_RC code to string
 * Input         : RC
 * Output        :
 * Return Value  : const char *
 * Side Effects  :
 * Scope         : Global
 ****************************************************/

extern const char * ESA_rc2str (ESA_RC rc);

/****************************************************
 * Procedure Name: ESA_DIAG_activate
 * Description   : Set the 'can_write' flag in diag structure
 * Input/Output  : None
 * Return Value  : None
 * Side Effects  : Flag in static structure is set
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_activate (void);

/****************************************************
 * Procedure Name: ESA_DIAG_deactivate
 * Description   : Clear the 'can_write' flag in diag structure
 * Input/Output  : None
 * Return Value  : None
 * Side Effects  : Flag in static structure is cleared
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAG_deactivate (void);

/****************************************************
 * Procedure Name: ESA_DIAGR_activate
 * Description   : Set the 'can_write' flag in diag structure
 * Input/Output  : handle
 * Return Value  : None
 * Side Effects  : Flag is set
 * Scope         : Global
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_activate (void * handle);

/****************************************************
 * Procedure Name: ESA_DIAGR_deactivate
 * Description   : Clear the 'can_write' flag in diag structure
 * Input/Output  : Handle
 * Return Value  : None
 * Side Effects  : Flag is cleared
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern void ESA_DIAGR_deactivate (void * handle);

#if defined (UNIX) || defined (NOVELL)

/*****************************************************************
 * Procedure Name: ESA_DIAG_perror
 * Description   : Writes system error message, plus user's message to
 *                 the log file.
 * Input         : User's message
 * Output        : None
 * Return Value  : None
 * Comments      : UNIX & Novell only.
 ****************************************************************/

extern void ESA_DIAG_perror (const char * user_msg);

/*****************************************************************
 * Procedure Name: ESA_DIAGR_perror
 * Description   : Writes system error message, plus user's message to
 *                 the log file.
 * Input         : User's message
 * Output        : None
 * Return Value  : None
 * Comments      : UNIX & Novell only.
 ****************************************************************/

extern void ESA_DIAGR_perror (void       * handle,
                              const char * user_msg);

#endif /* UNIX/NOVELL */

/****************************************************
 * Procedure Name: ESA_DIAG_get_lvls_arr_size
 * Description   : Fetch the ESA_DIAG_HANDLE_typ.esa_comp_level size
 * Input/Output  : size_t *
 * Return Value  : ESA_RC
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern ESA_RC ESA_DIAG_get_lvls_arr_size (size_t * array_size);

/****************************************************
 * Procedure Name: ESA_DIAG_get_file_name_size
 * Description   : Fetch the 
 *                 ESA_DIAG_HANDLE_typ.esa_diag_log_file_name size
 * Input/Output  : size_t *
 * Return Value  : ESA_RC
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern ESA_RC ESA_DIAG_get_file_name_size(size_t * file_name_size);

/****************************************************
 * Procedure Name: ESA_DIAG_get_shdw_fname_size
 * Description   : Fetch the 
 *                 ESA_DIAG_HANDLE_typ.esa_diag_shadow_file_name size
 * Input/Output  : size_t *
 * Return Value  : ESA_RC
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : No
 ****************************************************/

extern ESA_RC ESA_DIAG_get_shdw_fname_size (size_t * file_name_size);

/****************************************************
 * Procedure Name: ESA_DIAGR_get_diag_info
 * Description   : Fetch information about 3 fields in
 *                 ESA_DIAG_HANDLE_typ private struct
 *		   file_name,shadow_file_name,levels_array
 * Input/Output  : [IN] handle
 *				   [OUT] diag_file_name_buffer
 *				   [IN]	diag_file_name_buffer_size
 *				   [OUT] diag_shadow_file_name_buffer
 *				   [IN] diag_shadow_file_name_buffer_size
 *				   [OUT] levels_array
 *				   [IN] levels_array_size
 *
 * Return Value  : ESA_RC
 * Side Effects  :
 * Scope         : Global
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_get_diag_info (
        void               * handle,
        char               * diag_file_name_buffer,
        size_t               diag_file_name_buffer_size,
        char               * diag_shadow_file_name_buffer,
        size_t               diag_shadow_file_name_buffer_size,
        ESA_DIAG_LEVEL_typ * levels_array,
        size_t               levels_array_size);


extern void ESA_DIAG_print_stack (void               * handle, 
                                  const char         * funcname,
                                  int                  always,
                                  ESA_DIAG_LEVEL_typ   comp);

extern void ESA_DIAG_memory_status (void       * handle,
                                    const char * funcname,
	                                ESA_RC       rc_ret);

extern void ESA_DIAG_close_files (void);

extern int ESA_vsprintf (char       * big_line,
                         const char * format,
                         va_list      arg_list);

struct tm * ConvertTimeToTMStruct (time_t * int_clock, struct tm * tm_clock);

#ifdef CTSAMSG_C
void DATA_COMP_ESADIAG_C (void);
void DATA_COMP_ESADIAG__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_ESADIAG__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
   DATA_COMP_ESADIAG_C ();
}
#endif
#endif /* ESA_DIAG_INCLUDED */
