/*
 * Version Information:
 * ====================
 * File name       : %name: esacomp.h %
 * Instance        : %instance: 3 %
 * Created on      : %date_created: Mon May 23 08:36:54 2005 %
 * Current Version : %version: 26 %
 * Last Modified on: %date_modified: %
 */
/***********************************************
 * Mod.ID  Who      When         Description
 * =============================================
 *         Leonid   23/07/04     Memory Leak 
 **********************************************/

/*************************5***************************************
* Title            : List of Diagnostics Components for SManager *
******************************************************************/

#ifndef ESACOMP_H_INCLUDE
#define ESACOMP_H_INCLUDED
#ifdef MVS
#define DATA_COMP_ESACOMP__ cmpes01
#endif

/****************************************************
 * ESA_DIAG components
 ****************************************************/

#define ESA_MAX_COMPS                    512

#define ESA_COMP_DEFAULT                 0

#define ESA_COMP_START_USA_API           1
/* component definitions from 2 to 98 in "apicomp.h"  Only for PM use */
#define ESA_COMP_END_USA_API             99

/*----------------------- Common Code Functions */
#define ESA_COMP_START_SA_AGENT          100
/*-------------------------- COMMON */
#define ESA_COMP_ACSADM                  101 
#define ESA_COMP_ACSALOC                 102 
#define ESA_COMP_ACSAPI                  103
#define ESA_COMP_ACSCARF                 104 
#define ESA_COMP_ACSCDCS                 105 
#define ESA_COMP_ACSCHED                 106 
#define ESA_COMP_ACSCMN                  107 
#define ESA_COMP_ACSGPCF                 108 
#define ESA_COMP_ACSINFO                 109 
#define ESA_COMP_ACSKWD                  110 
#define ESA_COMP_ACSLOCK                 111 
#define ESA_COMP_ACSPROC                 112 
#define ESA_COMP_ACSRSS                  113 
#define ESA_COMP_ACSRSSX                 114 
#define ESA_COMP_ACSSTBS                 115 
#define ESA_COMP_API_ADDINFO             116 /*addinfo, esaadi, esaadil*/
#define ESA_COMP_CTSAMSG                 117
#define ESA_COMP_ESADMP                  118 
#define ESA_COMP_ESAINIT                 119 
#define ESA_COMP_ESAQOS                  120 
#define ESA_COMP_QUEUE                   121 
#define ESA_COMP_ESARSSF                 122 
#define ESA_COMP_PREPOST                 123
#define ESA_COMP_ACSPM                   124 
/*-------------------------- CDCS */
#define ESA_COMP_ACSCI                   125
#define ESA_COMP_ACSGETF                 126 
#define ESA_COMP_ACSGPF                  127 
#define ESA_COMP_ACSMGET                 128 
#define ESA_COMP_ACSMSET                 129 
#define ESA_COMP_WRITEOSF                130 
#define ESA_COMP_PM                      131 
/*-------------------------- CD */
#define ESA_COMP_ACSCHCD                 132
#define ESA_COMP_ACSHNDF                 133 
#define ESA_COMP_ACSINTF                 134 
#define ESA_COMP_ACSRVCD                 135 
#define ESA_COMP_ACSUPDF                 136 
#define ESA_COMP_P_CSACD                 137 /* To disp.user msg,count level by CMN_out_comfirm*/

/*-------------------------- CE */
#define ESA_COMP_ACSPMPF                 139 
#define ESA_COMP_ACSRVCS                 140 
#define ESA_COMP_ACSSETF                 141 
#define ESA_COMP_ACSSYNC                 142 
#define ESA_COMP_P_CSACS                 143 /* To disp.user msg,count level by CMN_out_comfirm*/

/*-------------------------- CE */
#define ESA_COMP_CECDPOOL                145
#define ESA_COMP_CECDSRVC                146 
#define ESA_COMP_CECOMCON                147 
#define ESA_COMP_CECOMIPC                148 
#define ESA_COMP_CECSMSGT                149 
#define ESA_COMP_CECSPOOL                150
#define ESA_COMP_CECSSRVC                151
#define ESA_COMP_CEDISPAT                152
#define ESA_COMP_CEERRMSG                153
#define ESA_COMP_CEMSGBOD                154
#define ESA_COMP_CEPRCSTS                155
#define ESA_COMP_CEPRIORT                156
#define ESA_COMP_CEPROCNM                157
#define ESA_COMP_CESESSMN                158
#define ESA_COMP_CESOCKET                159 
#define ESA_COMP_PRSCTSCE                160 
#define ESA_COMP_UTFCONV                 161 
/*--------------------------      Interceptor */
#define ESA_COMP_CC_RSS_INTERCEPT        162

/*-------------------------- UTILS */
#define ESA_COMP_UTILS                   164


#define ESA_COMP_END_SA_AGENT            170

/*----------------------------------------------------------------------------------*/  
/*--------- Diagnostic Parameters & Levels:       Level  Level  Level  Level  Level */
/*----------------------------------------------------------------------------------*/  

#define ESA_DUMP_MSG_IN_HEXA             186 /*To Output msg in HEXA, set level GT DIAG_AVOID  */
#define ESA_DUMP_ADDINFO_IN_HEXA         187 /*To Output addinfo in HEXA, level GT DIAG_AVOID  */
#define ESA_DUMP_ALLOC_SPACE_IN_HEXA     188 /*To Output alloc space in HEXA, lvl GT DIAG_AVOID*/
#define ESA_FUNC_NAME_LENGTH             189 /*Function name length of the diags. Default 26   */
#define ESA_STATISTICS_DIAG_LEVEL        190 /*If level DIAG_AVOID, skipped statistics         */   
#define ESA_GLOBAL_DIAG_LEVEL            191 /*DIAG_AVOID    1, GLOBAL Component Not in use    */    
#define ESA_BASIC_DIAG_LEVEL             192 /*DIAG_BASIC    2 Explain for 192 - 206 components*/
#define ESA_DATA_DIAG_LEVEL              193 /*DIAG_DATA     4 --- ESA_ADDINFO_DIAG_LEVEL (203)*/          
#define ESA_USAAPI_DIAG_LEVEL            194 /*DIAG_USAAPI   6   1) its spec level DIAG_ADDINFO*/     
#define ESA_OS_DIAG_LEVEL                195 /*DIAG_OS       8   2) To avoid all 'ADDINFO'     */
#define ESA_MESSAGE_DIAG_LEVEL           196 /*DIAG_MSG      10      diagnostics               */
#define ESA_APC_DIAG_LEVEL               197 /*DIAG_APC      12     - set level of the comp.203*/
#define ESA_CONFIRM_DIAG_LEVEL           198 /*DIAG_CONFIRM  14      to DIAG_AVOID (1)         */
#define ESA_ALLOC_DIAG_LEVEL             199 /*DIAG_ALLOC    16  3) To output 'basics' ADDINFO */   
#define ESA_LOCK_DIAG_LEVEL              200 /*DIAG_LOCK     18      diagnostics               */    
#define ESA_EVENT_DIAG_LEVEL             201 /*DIAG_EVENT    20     - set level of the comp.203*/   
#define ESA_OTHER_DIAG_LEVEL             202 /*DIAG_OTHER    22       to DIAG_BASIC (2)        */   
#define ESA_ADDINFO_DIAG_LEVEL           203 /*DIAG_ADDINFO  24  4) To output all ADDINFO  .   */
#define ESA_DETAILES_DIAG_LEVEL          204 /*DIAG_DETAILES 26      diagnostics               */   
#define ESA_LOOP_DIAG_LEVEL              205 /*DIAG_MORE     28     - set level of the comp.203*/   
#define ESA_ENTER_EXIT_DIAG_LEVEL        206 /*DIAG_COMMON   30       to DIAG_BASIC+ 1 (3)     */
#define ESA_WITHOUT_USAAPI_DIAG          207 /* Level= 1 -> avoid diag. from USA-API functions */   
#define ESA_WITHOUT_OS_DIAG              208 /* Level= 1 -> avoid diag. from OS functions      */


/*--------  For Files  ------------------------------------------------------------------------*/  
#define ESA_COMP_DIAG_TAB                212 /* Not in use. Have to be empty or 0              */   
#define ESA_COMP_MAX_GEN_VAL             213 /* Maximum Diagnostic Files (for recycle)         */   
#define ESA_COMP_MAX_LINES_VAL           214 /* Maximum lines in diagnostic file               */   
#define ESA_COMP_MAX_INTERVAL_VAL        215 /* Not in use (Max.time of the diag.file in sec.  */
#define ESA_COMP_DIAG_TO_MEMORY          216 /* Diag to memory equal to 500000* Level bytes    */   
#define ESA_COMP_DIAG_MEMORY_LEAK        217 /* Leak Diag,if Level=6|7(api),8|9(os),16|17(Lock)*/


/*-------   For Messages --------------------<list element1>,<list element2>,..,<list elementn>*/
#define ESA_COMP_START_STRING_LEVELS     220 /* Level not in use                               */
#define ESA_COMP_GLOBAL_LOG_I_MESSAGES   221 /* List of Inform.Msges for Global log (2 - all)  */
#define ESA_COMP_GLOBAL_LOG_E_MESSAGES   222 /* List of Error Msges for Global log (2 - all)   */
#define ESA_COMP_GLOBAL_LOG_S_MESSAGES   223 /* List of System Msges for Global log (2 - all)  */
#define ESA_COMP_GLOBAL_LOG_W_MESSAGES   224 /* List of Warning Msges for Global log (2 - all) */

/*-------   For Rsses   ---------------------<list element1>,<list element2>,..,<list elementn>*/
#define ESA_COMP_RSS_NAMES_DIAG          226 /*List of MS names for use diag. (via Trans.)     */    
#define ESA_COMP_RSS_TYPES_DIAG          227 /*List of MS types for use diag. (via Trans.)     */
#define ESA_COMP_RSS_NAMES_STATISTICS    228 /*List of MS names for use statistics.(via Trans.)*/
#define ESA_COMP_RSS_TYPES_STATISTICS    229 /*List of MS types for use statistics.(via Trans.)*/
#define ESA_COMP_END_STRING_LEVELS       230 /* Level not in use                               */
/*--------  For Errors  -----------------------------------------------------------------------*/  
#define ESA_COMP_DIAG_IF_TRANS_FAILED    231 /*Output Diag.from memory when trans. failed      */   

/*--------  For Processes  --------------------------------------------------------------------*/  
#define ESA_COMP_FOR_USAAPI              249 /*The Level set on from   1 to  99 components     */
#define ESA_COMP_FOR_OS                  250 /*The Level set on from 330 to 349 components     */ 
#define ESA_COMP_CD                      251 /*The Level set on from 100 to 170 components     */   
#define ESA_COMP_CE                      252 /*The Level set on from 100 to 170 components     */     
#define ESA_COMP_CS                      253 /*The Level set on from 100 to 170 components     */     
#define ESA_COMP_OFLI                    254 /*The Level set on from 100 to 170 components     */     
#define ESA_COMP_ONLI                    255 /*The Level set on from 100 to 170 components     */     
#define ESA_COMP_OTHER_PROC              256 /*The Level set on from 100 to 170 components     */     
/*---------------------------------------------------------------------------------------------*/

/*---------------------------- CPP (Online , Offline ------------------------------------------*/
#define ESA_COMP_RSS_ADAPTER             320 
#define ESA_COMP_ESS_IMAGE               321 
#define ESA_COMP_ENTITY                  322 
#define ESA_MODULE_COI                   323
#define ESA_MODULE_ODU                   324
/*-------------------------end CPP ------------------------------------------------------------*/

/*-----------------------        OS CC Functions ----------------------------------------------*/
#define ESA_COMP_CC_START_OS              330 
#define ESA_COMP_CC_OS_SCRIPT             331  
#define ESA_COMP_CC_OS_EVENT              332  
#define ESA_COMP_CC_OS_ATTACH             333  
#define ESA_COMP_CC_OS_WAIT               234  
#define ESA_COMP_CC_OS_LOCK_I             335  
#define ESA_COMP_CC_OS_LOCK_T             336  
#define ESA_COMP_CC_OS_LOCK               337  
#define ESA_COMP_CC_OS_UNLOCK             338  
#define ESA_COMP_CC_OS_MBX_ATT            339  
#define ESA_COMP_CC_OS_MBX_CRE            340  
#define ESA_COMP_CC_OS_MBX_RD             341  
#define ESA_COMP_CC_OS_MBX_WR             342  
#define ESA_COMP_CC_OS_MBX_GNRL           343  
#define ESA_COMP_CC_OS_GET_PASSWD         344  
#define ESA_COMP_CC_ESAOSCS               345 
#define ESA_COMP_OS_TCP                   346  
#define ESA_COMP_OS_SSL                   347
  
#define ESA_COMP_CC_END_OS                349
/*---------------------------------------------------------------------------------------------*/

/*-----For OSes and Interceptor that already use old ESA_COMP_ definitions --------------------*/
/* Commented by AAk for synchronization wiht apicomp.h
#define ESA_COMP_OS_SCRIPT      ESA_COMP_CC_OS_SCRIPT  
#define ESA_COMP_OS_EVENT       ESA_COMP_CC_OS_EVENT   
#define ESA_COMP_OS_ATTACH      ESA_COMP_CC_OS_ATTACH  
#define ESA_COMP_OS_WAIT        ESA_COMP_CC_OS_WAIT    
#define ESA_COMP_OS_LOCK_I      ESA_COMP_CC_OS_LOCK_I  
#define ESA_COMP_OS_LOCK_T      ESA_COMP_CC_OS_LOCK_T  
#define ESA_COMP_OS_LOCK        ESA_COMP_CC_OS_LOCK    
#define ESA_COMP_OS_UNLOCK      ESA_COMP_CC_OS_UNLOCK  
#define ESA_COMP_OS_MBX_ATT     ESA_COMP_CC_OS_MBX_ATT 
#define ESA_COMP_OS_MBX_CRE     ESA_COMP_CC_OS_MBX_CRE 
#define ESA_COMP_OS_MBX_RD      ESA_COMP_CC_OS_MBX_RD  
#define ESA_COMP_OS_MBX_WR      ESA_COMP_CC_OS_MBX_WR  
#define ESA_COMP_OS_MBX_GNRL    ESA_COMP_CC_OS_MBX_GNRL
#define ESA_COMP_OS_GET_PASSWD  ESA_COMP_CC_OS_GET_PASSWD
#define ESA_COMP_ESAOSCS        ESA_COMP_CC_ESAOSCS      
#define ESA_COMP_RSS_INTERCEPT  ESA_COMP_CC_RSS_INTERCEPT */
/*---------------------------------------------------------------------------------------------*/

/*------------------------- Only for PM use ---------------------------------------------------
#define ESA_FIRST_PLATFORM_COMP          351
  in "apicomp.h"  Only for PM use 
#define ESA_LAST_PLATFORM_COMP           511
-----------------------------------------------------------------------------------------------*/

#ifdef ESAINIT_C
void DATA_COMP_ESACOMP__ (char * FilePtr, char * TimeStampPtr, int * LinePtr);
void DATA_COMP_ESACOMP__ (char * FilePtr, char * TimeStampPtr, int * LinePtr)
{
          *LinePtr     = __LINE__;
   strcpy (FilePtr     , __FILE__);
   strcpy (TimeStampPtr, __TIMESTAMP__);
}
#endif
#endif /* ESA_COMP_H_INCLUDED */
