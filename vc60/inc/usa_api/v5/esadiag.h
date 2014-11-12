/*****************************************************
* Title           : Diagnostics
* File Name       : esadiag.h
* Author          : Atzmon (@ Liraz)
* Creation Date   : 20-Feb-94
* Description     : Interface to diagnostic printouts
* Assumptions and
*   Considerations:
* $Author:   avi_w  $
* $Workfile:   esadiag.h  $
* $Revision:   1.0  $
* $Log:   //EAGLE1/VERSIONS/300/COMMON/INC/esadiag.h_v  $
 * 
 *    Rev 1.0   Aug 31 1998 19:02:06   avi_w
 *  
 * 
 *    Rev 1.4   Jan 21 1998 18:53:42   leonid_s
 * 300-Beta with AS400 & VMS changes 
 *
 *    Rev 1.3   Jul 27 1997 10:32:36   Danko
 * converting_from_sccs
 *
 *    Rev 1.2   Jul 24 1997 08:29:56   leonid_s
 *     SCCSID("%Z%%M% \
 *
 *
 *    Rev 1.1   Jul 08 1997 10:08:56   avi_w
 *
*****************************************************/
/* SCCSID %Z%%M% */

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
#endif /* MVS */

/* include STDARG since some functions have a va_list parameter */

#ifdef   WNTINC
#include "stdarg.h"
#else
#include STDARG
#endif

/*****************************************************************
 *  PROCEDURE NAME : ESA_DIAG_initialize
 *  DESCRIPTION    : Initializes the ESA_DIAG module.
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

/****************************************************
 * Procedure Name: ESA_DIAGR_initialize
 * Description   : Initializes the ESA_DIAG module.
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

extern void ESA_DIAG_exit (ESA_DIAG_COMP_typ  comp,
                           ESA_DIAG_LEVEL_typ level,
                           const char       * funcname,
                           ESA_RC             rc_ret);

/****************************************************
 * Procedure Name: ESA_DIAGR_exit
 * Description   : pop function stack, print message
 * Input         : Component, level
 * Output        : None
 * Return Value  : None
 * Re-entrant    : Yes
 ****************************************************/

extern void ESA_DIAGR_exit (void             * handle,
                            ESA_DIAG_COMP_typ  comp,
                            ESA_DIAG_LEVEL_typ level,
                            const char       * funcname,
                            ESA_RC             rc_ret);

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

extern ESA_RC ESA_DIAG_set_debug_levels_file (const char * fname);

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
                                               const char * fname);

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

#endif /* ESA_DIAG_INCLUDED */
