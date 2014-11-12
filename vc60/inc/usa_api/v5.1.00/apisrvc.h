/**********************************************************************
*
*   H Source      : apisrvc.h
*   Description   : Agent Callable services for USA-APIs
*   %full_filespec: apisrvc.h#12:incl:2 %
*   %date_created : Mon Apr 08 16:28:31 2002 %
*
**********************************************************************/

#ifndef APISRVC_H_INCLUDED
#define APISRVC_H_INCLUDED
#ifdef UNIX
/* Sachin - Adding the varagrs.h because va_list declaration is not being resolved */
#include <stdarg.h>
#endif

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ==================================================================== */
/* ==                                                                == */
/* == This header file contains definitions of                       == */
/* ==          SA-Agent callable services functions.                 == */
/* ==                                                                == */
/* ==  Function addresses are available to any USA-API from          == */
/* ==  admin_params->cs_func                                         == */
/* ==                                                                == */
/* ==================================================================== */

/********************************************************************
 * Procedure Name: INIT_AgentVersion                                *
 * Description   : Services Manager Version                         *
 * Input         : None                                             *
 * Output        : MSversion                                        *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
#ifdef MVS
#define INIT_AgentVersion smvers
#endif 
char * INIT_AgentVersion (void);


typedef char * SM_VERSION_FUNC_TYP (void);

extern  SM_VERSION_FUNC_TYP INIT_AgentVersion;

typedef SM_VERSION_FUNC_TYP * SM_VERSION_FUNC_PTR;

/********************************************************************
 * Procedure Name: DIAG_refresh                                     *
 * Description   : Reload debug levels for all components           *
 * Input         : None                                             *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
#ifdef MVS
#define DIAG_refresh_CS         diafrsh
#endif 

typedef ESA_RC DIAG_REFRESH_FUNC_TYP (void);

extern  DIAG_REFRESH_FUNC_TYP DIAG_refresh_CS;

typedef DIAG_REFRESH_FUNC_TYP * DIAG_REFRESH_FUNC_PTR;

/********************************************************************
 * Procedure Name: DIAG_printf                                      *
 * Description   : printf-like diagnostics                          *
 * Input         : Component, level, format, arguments              *
 * Output        : None                                             *
 * Return Value  : None                                             *
 * Side Effects  : VARARGS is used                                  *
 ********************************************************************/
#ifdef MVS
#define DIAG_printf_CS          diagprt
#endif

typedef void DIAG_PRINTF_FUNC_TYP (ESA_DIAG_COMP_typ    comp,
                                   ESA_DIAG_LEVEL_typ   level,
                                   const char         * format, ... );

extern  DIAG_PRINTF_FUNC_TYP DIAG_printf_CS;            

typedef DIAG_PRINTF_FUNC_TYP * DIAG_PRINTF_FUNC_PTR;

/********************************************************************
 * Procedure Name: ESA_DIAGR_printf                                 *
 * Description   : printf-like diagnostics                          *
 * Input         : DiagHndl, Component, level, format, arguments    *
 * Output        : None                                             *
 * Return Value  : None                                             *
 * Side Effects  : VARARGS is used                                  *
 ********************************************************************/
#ifdef MVS
#define DIAGR_printf_CS          diagprt_EX
#endif

typedef void DIAGR_PRINTF_FUNC_TYP (void               * DiagHndl,
				  				    ESA_DIAG_COMP_typ    comp,
                                    ESA_DIAG_LEVEL_typ   level,
                                    const char         * format, ... );

extern  DIAGR_PRINTF_FUNC_TYP DIAGR_printf_CS;            

typedef DIAGR_PRINTF_FUNC_TYP * DIAGR_PRINTF_FUNC_PTR;


/********************************************************************
 * Procedure Name: ESA_DIAGR_vprintf                                *
 * Description   : printf-like diagnostics                          *
 * Input         : DiagHndl, Component, level, format, arg_list     *
 * Output        : None                                             *
 * Return Value  : None                                             *
 * Side Effects  : VARARGS is used                                  *
 ********************************************************************/
#ifdef MVS
#define DIAGR_vprintf_CS          diagvprt_EX
#endif

typedef void DIAGR_VPRINTF_FUNC_TYP (void               * DiagHndl,
                                     ESA_DIAG_COMP_typ    comp,
                                     ESA_DIAG_LEVEL_typ   level,
                                     const char         * format,
                                     va_list              arg_list);

extern  DIAGR_VPRINTF_FUNC_TYP DIAGR_vprintf_CS;            

typedef DIAGR_VPRINTF_FUNC_TYP * DIAGR_VPRINTF_FUNC_PTR;

/********************************************************************
 * Procedure Name: DIAG_get_debug_level                             *
 * Description   : return diag level of a component                 *
 * Input         : comp - Component id                              *
 * Output        : None                                             *
 * Return Value  : Level of diagnostics                             *
 ********************************************************************/
#ifdef MVS
#define DIAG_get_debug_level diadbgl
#endif 

typedef ESA_DIAG_LEVEL_typ DIAG_GET_DEBUG_LEVEL_FUNC_TYP (
                                          ESA_DIAG_COMP_typ  comp);

extern DIAG_GET_DEBUG_LEVEL_FUNC_TYP ESA_DIAG_get_debug_level;

typedef DIAG_GET_DEBUG_LEVEL_FUNC_TYP * DIAG_GET_DEBUG_LEVEL_FUNC_PTR;

/********************************************************************
 * Procedure Name: DIAG_enter                                       *
 * Description   : Push calling func name on stack, print message   *
 * Input         : comp - component id                              *
 *                 level     - diagnostics level                    *
 *                 func name - for display                          *
 * Output        : None                                             *
 * Return Value  : None                                             *
 ********************************************************************/
#ifdef MVS
#define DIAG_enter_CS           diagent
#endif
typedef void DIAG_ENTER_FUNC_TYP (ESA_DIAG_COMP_typ    comp,
                                  ESA_DIAG_LEVEL_typ   level,
                                  const char         * funcname);

extern  DIAG_ENTER_FUNC_TYP DIAG_enter_CS;           /* act function */

typedef DIAG_ENTER_FUNC_TYP * DIAG_ENTER_FUNC_PTR;/* pntr to func */

/********************************************************************
 * Procedure Name: ESA_DIAGR_enter                                  *
 * Description   : Push calling func name on stack, print message   *
 * Input         : DiagHndl                                         * 
 *                 comp - component id                              *
 *                 level     - diagnostics level                    *
 *                 func name - for display                          *
 * Output        : None                                             *
 * Return Value  : None                                             *
 ********************************************************************/
#ifdef MVS
#define DIAGR_enter_CS           diagent_EX
#endif
typedef void DIAGR_ENTER_FUNC_TYP (void               * DiagHndl,
								   ESA_DIAG_COMP_typ    comp,
                                   ESA_DIAG_LEVEL_typ   level,
                                   const char         * funcname);

extern  DIAGR_ENTER_FUNC_TYP DIAGR_enter_CS;         /* act function */

typedef DIAGR_ENTER_FUNC_TYP * DIAGR_ENTER_FUNC_PTR;/* pntr to func */

/********************************************************************
 * Procedure Name: DIAG_exit                                        *
 * Description   : Pop function stack, print message                *
 * Input         : comp      - component id                         *
 *                 level     - diagnostics level                    *
 *                 func name - for display                          *
 *                 rc_ret    - return-code for display              *
 * Output        : None                                             *
 * Return Value  : None                                             *
 ********************************************************************/
#ifdef MVS
#define DIAG_exit_CS            diagext
#endif 

typedef void DIAG_EXIT_FUNC_TYP (ESA_DIAG_COMP_typ   comp,
                                 ESA_DIAG_LEVEL_typ  level,
                                 const char        * funcname,
                                 ESA_RC              rc_ret);

extern  DIAG_EXIT_FUNC_TYP DIAG_exit_CS;            /* act function */

typedef DIAG_EXIT_FUNC_TYP * DIAG_EXIT_FUNC_PTR; /* pntr to func */

/********************************************************************
 * Procedure Name: ESA_DIAGR_exit                                   *
 * Description   : Pop function stack, print message                *
 * Input         : DiagHndl                                         *
 *                 comp      - component id                         *
 *                 level     - diagnostics level                    *
 *                 func name - for display                          *
 *                 rc_ret    - return-code for display              *
 * Output        : None                                             *
 * Return Value  : None                                             *
 ********************************************************************/
#ifdef MVS
#define DIAGR_exit_CS            diagext_EX
#endif 

typedef void DIAGR_EXIT_FUNC_TYP (void              * DiagHndl,
								  ESA_DIAG_COMP_typ   comp,
                                  ESA_DIAG_LEVEL_typ  level,
                                  const char        * funcname,
                                  ESA_RC              rc_ret);

extern  DIAGR_EXIT_FUNC_TYP DIAGR_exit_CS;            /* act function */

typedef DIAGR_EXIT_FUNC_TYP * DIAGR_EXIT_FUNC_PTR; /* pntr to func */


/********************************************************************
 * Procedure Name: DIAG_get_info                                    *
 * Description   : Get DIAG file names and levels array	            *
 * Input         : handle                                           *
 *                                                                  *
 * Output        : diag_file_name_ptr - ptr to DIAG file name       *
 *		   diag_shadow_fn_ptr - ptr to DIAG shadow file name*
 *		   levels_array_ptr   - ptr to levels array         *
 *		   levels_array_size  - ptr to array size           * 
 *                                                                  *
 * Return Value  : ESA_RC                                           *
 * Comments      : Use the previous 3 functions to determine the    *
 *                 the sizes needed for allocation, before calling  *
 *                 this function.                                   *
 ********************************************************************/
typedef void DIAG_GET_INFO_FUNC_TYP
            (void                * handle,
			 char               ** diag_fn_ptr,
			 char               ** diag_shadow_fn_ptr,
			 ESA_DIAG_LEVEL_typ ** levels_array_ptr,
             char               ** origin_diag_fn_ptr, 
             char               ** proc_name_ptr,
             int                 * pid_ptr);

extern  DIAG_GET_INFO_FUNC_TYP   DIAG_get_info;   

typedef DIAG_GET_INFO_FUNC_TYP * DIAG_GET_INFO_FUNC_PTR;


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

typedef void DIAG_INITIALIZE_FUNC_TYP (char   * ThreadID,
                                  const char  * procname,
                                  void       ** handle);

extern  DIAG_INITIALIZE_FUNC_TYP   ESA_DIAGR_initialize;   

typedef DIAG_INITIALIZE_FUNC_TYP * DIAG_INITIALIZE_FUNC_PTR;

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

typedef void DIAG_TERMINATE_FUNC_TYP (void * handle);
 
extern  DIAG_TERMINATE_FUNC_TYP   ESA_DIAGR_terminate;   

typedef DIAG_TERMINATE_FUNC_TYP * DIAG_TERMINATE_FUNC_PTR;


/********************************************************************
 * Procedure Name   : MSG_print                                     *
 * Description      : Issue a message to the requested              *
 *                    destinations                                  *
 * Input            : msgid   - msgid to be printed                 *
 *                    ...     - arguments for message               *
 * Output           : None                                          *
 * Return Value     : ESA_RC                                        *
 * Comments         : The function process the arg list and         *
 *                    calls CTSAMSG_print                           *
 ********************************************************************/
#ifdef MVS
#define MSG_printf_CS        msgprnt
#define MSG_vprintf_CS          msgvprnt
#endif 

typedef ESA_RC MSG_PRINT_FUNC_TYP   (const char * msgid , ... );
typedef ESA_RC MSG_VPRINT_FUNC_TYP  (void * DiagHndl, const char * msgid, va_list arg_list);

extern  MSG_PRINT_FUNC_TYP MSG_printf_CS;
extern  MSG_VPRINT_FUNC_TYP MSG_vprintf_CS;

typedef MSG_PRINT_FUNC_TYP * MSG_PRINT_FUNC_PTR ; 
typedef MSG_VPRINT_FUNC_TYP * MSG_VPRINT_FUNC_PTR ; 

/********************************************************************
 * Procedure Name   : MSG_print_EX                                  *
 * Description      : Issue a message to the requested              *
 *                    destinations                                  *
 * Input            : DiagHndl
 *                    msgid   - msgid to be printed                 *
 *                    ...     - arguments for message               *
 * Output           : None                                          *
 * Return Value     : ESA_RC                                        *
 * Comments         : The function process the arg list and         *
 *                    calls CTSAMSG_print                           *
 ********************************************************************/
#ifdef MVS
#define MSG_printf_EX_CS           msgprnt_EX
#endif 

typedef ESA_RC MSG_PRINT_EX_FUNC_TYP   (void * DiagHndl, const char * msgid , ... );

extern  MSG_PRINT_EX_FUNC_TYP MSG_printf_EX_CS;

typedef MSG_PRINT_EX_FUNC_TYP * MSG_PRINT_EX_FUNC_PTR ; 

/********************************************************************
 * Procedure Name: LOG_event                                        * 
 * Description   : Send message to ESS, to be displayed immediately.*
 *                 Messages from msg_print will be displayed only   *
 *                 after the transaction finishes, but this function*
 *                 causes messages to be shown immediately in the   *
 *                 ESS log                                          *
 * Input           msgid    - Message code from message code file.  *
 *                 ...      - Message parameters list.              *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
#ifdef MVS
#define LOG_event_CS            logevnt
#endif 

typedef ESA_RC LOGEVT_FUNC_TYP (const char * msgid, ...);

extern  LOGEVT_FUNC_TYP   LOG_event_CS;     /* actual function */

typedef LOGEVT_FUNC_TYP * LOGEVT_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: LOG_event_EX                                     * 
 * Description   : Send message to ESS, to be displayed immediately.*
 *                 Messages from msg_print will be displayed only   *
 *                 after the transaction finishes, but this function*
 *                 causes messages to be shown immediately in the   *
 *                 ESS log                                          *
 * Input           DiagHndl
 *                 msgid    - Message code from message code file.  *
 *                 ...      - Message parameters list.              *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 ********************************************************************/
#ifdef MVS
#define LOG_event_EX_CS            logevnt
#endif 

typedef ESA_RC LOGEVT_EX_FUNC_TYP (void * DiagHndl, const char * msgid, ...);

extern  LOGEVT_EX_FUNC_TYP   LOG_event_EX_CS;       /* actual function */

typedef LOGEVT_EX_FUNC_TYP * LOGEVT_EX_FUNC_PTR; /* pointer to func */


/********************************************************************
 * Procedure Name: RSS_list_get                                      *
 * Description   : Get list of RSSs from CONTROL-SA global parameter*
 *                 file (RSSPARM).                                  *
 * Input         : None                                             *
 * Output        : rss_num  - Number of RSSs defined                *
 *                 rss_rec  - one record for each RSS               *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_list_get_CS          rsslist
#endif

typedef ESA_RC RSSLIST_GET_FUNC_TYP (unsigned int  * rss_num,
                                     RSS_rec_typ  ** rss_rec);

extern  RSSLIST_GET_FUNC_TYP    RSS_list_get_CS;    /* actual function */

typedef RSSLIST_GET_FUNC_TYP * RSSLIST_GET_FUNC_PTR;/*pointer to func*/

/********************************************************************
 * Procedure Name: PM_param_get                                     *
 * Description   : Get a parameter from PMPARM.PRM for a specific PM*
 *                 The parameter may not exist in the file.         *
 * Input         : DiagHndl                                         *
 *                 pm             - PM name                         *
 *                 param_name     - requested parameter name        *
 *                 max_value_len  - length of output field          *
 *                 optional_prm   -  TRUE  - parameter is optional  *
 *                                   FALSE - parameter must exist   *
 *                 optional_value -  TRUE  - parameter may be empty *
 *                                   FALSE - param. may not be empty*
 *                     (The 2 flags affect the RC, if the parameter *
 *                      does not exist or is empty).                *
 * Output        : param_value    - parameter value                 *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define PM_prm_get_CS           pmpget
#endif 

typedef ESA_RC PMPRM_GET_FUNC_TYP (void          * DiagHndl,
                                   RSS_typ const   pm,
                                   char const    * param_name,
                                   unsigned int    max_value_len,
                                   char          * param_value,
                                   OPTION_typ      optional_prm,
                                   OPTION_typ      optional_value);

extern  PMPRM_GET_FUNC_TYP   PM_prm_get_CS;   /* actual function */

typedef PMPRM_GET_FUNC_TYP * PMPRM_GET_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: RSS_list_get_EX                                      *
 * Description   : Get list of RSSs from CONTROL-SA global parameter*
 *                 file (RSSPARM).                                  *
 * Input         : DiagHndl - Pointer to Diag Handle                *
 * Output        : rss_num  - Number of RSSs defined                *
 *                 rss_rec  - one record for each RSS               *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_list_get_EX_CS          rsslist_EX
#endif

typedef ESA_RC RSSLIST_GET_EX_FUNC_TYP (void          * DiagHndl,
                                        unsigned int  * rss_num,
                                        RSS_rec_typ  ** rss_rec);

extern  RSSLIST_GET_EX_FUNC_TYP    RSS_list_get_EX_CS;    /* actual function */

typedef RSSLIST_GET_EX_FUNC_TYP * RSSLIST_GET_EX_FUNC_PTR;/*pointer to func*/

/********************************************************************
 * Procedure Name: RSS_param_get                                    *
 * Description   : Get a parameter from CONTROL-SA global parameter *
 *                 file (RSSPARM) for a specific RSS.               *
 * Input         : rss            - RSS name                        *
 *                 param_name     - requested parameter name        *
 *                 max_value_len  - length of output field          *
 * Output        : param_value    - parameter value                 *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_param_get_CS           rsspget
#endif 

typedef ESA_RC RSSPRM_GET_FUNC_TYP (RSS_typ const   rss,
                                    char const    * param_name,
                                    unsigned int    max_value_len,
                                    char          * param_value);

extern  RSSPRM_GET_FUNC_TYP    RSS_param_get_CS;   /* actual function */

typedef RSSPRM_GET_FUNC_TYP * RSSPRM_GET_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: RSS_param_get_EX                                 *
 * Description   : Get a parameter from CONTROL-SA global parameter *
 *                 file (RSSPARM) for a specific RSS.               *
 * Input         : DiagHndl                                         *
 *                 rss            - RSS name                        *
 *                 param_name     - requested parameter name        *
 *                 max_value_len  - length of output field          *
 * Output        : param_value    - parameter value                 *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_param_get_EX_CS           rsspget_EX
#endif 

typedef ESA_RC RSSPRM_GET_EX_FUNC_TYP (void          * DiagHndl,
									   RSS_typ const   rss,
                                       char const    * param_name,
                                       unsigned int    max_value_len,
                                       char          * param_value);

extern  RSSPRM_GET_EX_FUNC_TYP    RSS_param_get_EX_CS;   /* actual function */

typedef RSSPRM_GET_EX_FUNC_TYP * RSSPRM_GET_EX_FUNC_PTR; /* pointer to func */

/********************************************************************
 * Procedure Name: RSS_prm_get_opt                                   *
 * Description   : Get a parameter from CONTROL-SA global parameter *
 *                 file for a specific RSS. The parameter may not   *
 *                 exist in the file.                               *
 * Input         : rss            - RSS name                        *
 *                 param_name     - requested parameter name        *
 *                 max_value_len  - length of output field          *
 *                 optional_prm   -  TRUE  - parameter is optional  *
 *                                   FALSE - parameter must exist   *
 *                 optional_value -  TRUE  - parameter may be empty *
 *                                   FALSE - param. may not be empty*
 *                     (The 2 flags affect the RC, if the parameter *
 *                      does not exist or is empty).                *
 * Output        : param_value - parameter value                    *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_prm_get_opt_CS       rsspgop
#endif 

typedef ESA_RC RSSPRM_GET_OPT_FUNC_TYP (RSS_typ const  rss,
                                        char const   * param_name,
                                        unsigned int   max_value_len,
                                        char         * param_value,
                                        OPTION_typ     optional_prm,
                                        OPTION_typ     optional_value);

extern  RSSPRM_GET_OPT_FUNC_TYP    RSS_prm_get_opt_CS; /* actual function */

typedef RSSPRM_GET_OPT_FUNC_TYP * RSSPRM_GET_OPT_FUNC_PTR;/*ptr to fnc*/

/********************************************************************
 * Procedure Name: RSS_prm_get_opt_EX                               *
 * Description   : Get a parameter from CONTROL-SA global parameter *
 *                 file for a specific RSS. The parameter may not   *
 *                 exist in the file.                               *
 * Input         : DiagHndl
 *                 rss            - RSS name                        *
 *                 param_name     - requested parameter name        *
 *                 max_value_len  - length of output field          *
 *                 optional_prm   -  TRUE  - parameter is optional  *
 *                                   FALSE - parameter must exist   *
 *                 optional_value -  TRUE  - parameter may be empty *
 *                                   FALSE - param. may not be empty*
 *                     (The 2 flags affect the RC, if the parameter *
 *                      does not exist or is empty).                *
 * Output        : param_value - parameter value                    *
 * Return Value  : ESA_OK             upon success                  *
 *                 ESA_KEY_NOT_FOUND  on any other situation        *
 ********************************************************************/
#ifdef MVS
#define RSS_prm_get_opt_EX_CS       rsspgop_EX
#endif 

typedef ESA_RC RSSPRM_GET_OPT_EX_FUNC_TYP (void          * DiagHndl, 
                                           RSS_typ const   rss,
                                           char const    * param_name,
                                           unsigned int    max_value_len,
                                           char          * param_value,
                                           OPTION_typ      optional_prm,
                                           OPTION_typ      optional_value);

extern  RSSPRM_GET_OPT_EX_FUNC_TYP    RSS_prm_get_opt_EX_CS; /* actual function */

typedef RSSPRM_GET_OPT_EX_FUNC_TYP * RSSPRM_GET_OPT_EX_FUNC_PTR;/*ptr to fnc*/


/********************************************************************
 * Procedure Name: KWD_get_typ                                       *
 * Description   : Get keyword type from CONTROL-SA global keywords *
 *                 file for a specific RSS.                         *
 * Input         : rss         -  RSS name                          *
 *                 object_type -  number representing the entity.   *   
 *                 keyword    - name of keyword requested           *
 * Output        : keyword_type - returns the type                  *
 *                                for example TYPE_1A               *
 * Return Value  : ESA_OK        - upon success                     *
 *                 other values  - upon error                       *
 ********************************************************************/
#ifdef MVS
#define KWD_get_typ_CS           rssktyp
#endif

typedef ESA_RC RSSKWD_TYP_FUNC_TYP (RSS_typ           rss,
                                    OBJECT_TYPE_typ   object_type,
                                    char            * keyword,
                                    ADDINFO_typ     * keyword_type);

extern  RSSKWD_TYP_FUNC_TYP  KWD_get_typ_CS;   /* actual function */

typedef RSSKWD_TYP_FUNC_TYP * RSSKWD_TYP_FUNC_PTR;

/********************************************************************
 * Procedure Name: KWD_get_typ_EX                                   *
 * Description   : Get keyword type from CONTROL-SA global keywords *
 *                 file for a specific RSS.                         *
 * Input         : DiagHndl
 *                 rss         -  RSS name                          *
 *                 object_type -  number representing the entity.   *   
 *                 keyword    - name of keyword requested           *
 * Output        : keyword_type - returns the type                  *
 *                                for example TYPE_1A               *
 * Return Value  : ESA_OK        - upon success                     *
 *                 other values  - upon error                       *
 ********************************************************************/
#ifdef MVS
#define KWD_get_typ_EX_CS           rssktyp_EX
#endif

typedef ESA_RC RSSKWD_TYP_EX_FUNC_TYP (void            * DiagHndl,
									   RSS_typ           rss,
                                       OBJECT_TYPE_typ   object_type,
                                       char            * keyword,
                                       ADDINFO_typ     * keyword_type);

extern  RSSKWD_TYP_EX_FUNC_TYP  KWD_get_typ_EX_CS;   /* actual function */

typedef RSSKWD_TYP_EX_FUNC_TYP * RSSKWD_TYP_EX_FUNC_PTR;


/********************************************************************
 * Procedure Name: INIT_intercept_send                                   *
 * Description   : Cause a refresh of object details in the ESS.    *
 *                 Function should be used when object details were *
 *                 changed.                                         *
 * Input         : intercept_rec    - interception description      *
 * Output        : None                                             *
 * Return Value  : ESA_RC                                           *
 * Note - Function exists in V4.0.0 and above.                      *
 *        Replaces function intercept_set                           *
 ********************************************************************/
#ifdef MVS
#define INIT_intercept_send_CS  intsend
#endif 

typedef ESA_RC INTERCEPT_SEND_FUNC_TYP (void * DiagHndl, INTERCEPT_rec_ptr intercept_rec);

extern  INTERCEPT_SEND_FUNC_TYP INIT_intercept_send_CS;/* actual function */

typedef INTERCEPT_SEND_FUNC_TYP * INTERCEPT_SEND_FUNC_PTR;
                                                 /* pointer to func  */

/********************************************************************
* Procedure Name: get_timestamp                                     *
* Description   : Return current time as string                     *
* Input         : None                                              *
* Output        : timestr - time string                             *
* Return Value  : None                                              *
*********************************************************************/
#ifdef MVS
#define INIT_get_timestamp     gettims
#endif 

typedef void GET_TIMESTR_FUNC_TYP (void * DiagHndl, TIMESTAMP_typ   timestr);

extern  GET_TIMESTR_FUNC_TYP   INIT_get_timestamp;  

typedef GET_TIMESTR_FUNC_TYP * GET_TIMESTAMP_FUNC_PTR;


/**********************************************************************************
 * Procedure Name: Encrypt_int_CS                                                 *
 * Description   : Internal encryption.                                           *
 * Input         : DiagHndl     - Pointer to Diagnostics Hnadle                   *
 *                 InBuf        - String for Encryption                           *
 *                 InBufLen     - Length of the string for Encryption             *
 *               : OutBufLen    - Maximum Length of the Encrypted string.         *
 * Output        : OutBuf       - Encrypted string.                               *
 *               : OutBufLen    - Length of the Encrypted string.                 *
 *               : ErrMsg       - Pointer to Error message structure              * 
 * Return Value  : ESA_OK       - Encryption o.k                                  *  
 *                 other values - Encryption failed                               *
 **********************************************************************************/
#ifdef MVS
#define Encrypt_int_CS           EncrCS
#endif

typedef ESA_RC ENCRYPT_INT_FUNC_TYP (void               * DiagHndl,
									 void               * InBuf,
                                     int                  InBufLen,
									 void               * OutBuf,
                                     int                * OutBufLen,
                                     ERR_STRUCT_rec_typ * ErrMsg);

extern  ENCRYPT_INT_FUNC_TYP Encrypt_int_CS;   /* actual function */

typedef ENCRYPT_INT_FUNC_TYP * ENCRYPT_INT_FUNC_PTR;



/**********************************************************************************
 * Procedure Name: Decrypt_int_CS                                                 *
 * Description   : Internal decryption.                                           *
 * Input         : DiagHndl     - Pointer to Diagnostics Hnadle                   *
 *                 InBuf        - String for Decryption                           *
 *                 InBufLen     - Length of the string for Decryption             *
 * Output        : OutBuf       - Decrypted string.                               *
 *               : OutBufLen    - Length of the Decrypted string.                 *
 *               : ErrMsg       - Pointer to Error message structure              * 
 * Return Value  : ESA_OK       - Decryption o.k                                  *  
 *                 other values - Decryption failed                               *
 **********************************************************************************/
#ifdef MVS
#define Decrypt_int_CS           DecrCS
#endif

typedef ESA_RC DECRYPT_INT_FUNC_TYP (void               * DiagHndl,
									 void               * InBuf,
                                     int                  InBufLen,
									 void               * OutBuf,
                                     int                * OutBufLen,
                                     ERR_STRUCT_rec_typ * ErrMsg);

extern  DECRYPT_INT_FUNC_TYP Decrypt_int_CS;   /* actual function */

typedef DECRYPT_INT_FUNC_TYP * DECRYPT_INT_FUNC_PTR;


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#ifdef ESAINIT_C
void DATA_COMP_APISRVC__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_APISRVC__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif   /* ifndef APISRVC_H_INCLUDED */
