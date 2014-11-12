/*
 * Version Information:
 * ====================
 * File name       : %name: apicomp.h %
 * Instance        : %instance: 1 %
 * Created on      : %date_created: Tue Apr 12 13:31:02 2005 %
 * Current Version : %version: 4 %
 * Last Modified on: %date_modified: %
 */

/*************************5*********************************
* Title            : List of Diagnostics Components for PM *
************************************************************/

#ifndef APICOMP_H_INCLUDE
#define APICOMP_H_INCLUDED
#ifdef MVS
#define DATA_COMP_APICOMP__ cmpes00
#endif

/****************************************************
 * ESA_DIAG components
 ****************************************************/

/*-------------------------- For use in PM function    --------
        ESA_COMP_START_USA_API           1  
---------------------------------------------------------------*/
#define ESA_COMP_APIINIT                 2   
#define ESA_COMP_ADDUSER                 3   
#define ESA_COMP_DELUSER                 4   
#define ESA_COMP_UPDUSER                 5   
#define ESA_COMP_REVUSER                 6   
#define ESA_COMP_UPDPASS                 7   
#define ESA_COMP_ADDUG                   8   
#define ESA_COMP_DELUG                   9   
#define ESA_COMP_UPDUG                   10  
#define ESA_COMP_ADDU2UG                 11  
#define ESA_COMP_DELU2UG                 12  
#define ESA_COMP_UPDU2UG                 13  
#define ESA_COMP_ADDACE                  14  
#define ESA_COMP_DELACE                  15  
#define ESA_COMP_UPDACE                  16  
#define ESA_COMP_MOVUSER                 17  
#define ESA_COMP_RENUSER                 18  
#define ESA_COMP_MOVUG                   19  
#define ESA_COMP_RENUG                   20  
#define ESA_COMP_MOVOE                   21  
#define ESA_COMP_MOVRES                  22  
#define ESA_COMP_RENRES                  23  
#define ESA_COMP_ADDOE                   24  
#define ESA_COMP_DELOE                   25  
#define ESA_COMP_UPDOE                   26  
#define ESA_COMP_GETOES                  27  
#define ESA_COMP_ISMASKMATCH             28  
#define ESA_COMP_ISINOE                  29  
#define ESA_COMP_GTUSERS                 30  
#define ESA_COMP_GETUGS                  31  
#define ESA_COMP_GTUG2UC                 32  
#define ESA_COMP_GETRES                  33  
#define ESA_COMP_GTRSACL                 34  
#define ESA_COMP_ADDRES                  35  
#define ESA_COMP_DELRES                  36  
#define ESA_COMP_UPDRES                  37  
#define ESA_COMP_STRSPRM                 38  
#define ESA_COMP_GTRSPRM                 39  
#define ESA_COMP_RSPRMMOD                40  
#define ESA_COMP_RSALERT                 41  
#define ESA_COMP_RSUSDIS                 42  
#define ESA_COMP_RSPWDMOD                43  
#define ESA_COMP_RSLOGEVT                44  
#define ESA_COMP_RSUSER                  45  
#define ESA_COMP_RSS_LOGIN               46  
#define ESA_COMP_RSS_LOGOUT              47  
#define ESA_COMP_RSS_CHECK               48  
#define ESA_COMP_API_LOAD                49  
#define ESA_COMP_APITERM                 50   
#define ESA_COMP_RSSINIT                 51   
#define ESA_COMP_RSSTERM                 52   
#define ESA_COMP_RSS_VERIFY_PWD          53 
#define ESA_COMP_API_LOGIN_MODE          54
#define ESA_COMP_USAAPI                  55
#define ESA_COMP_SCRIPT                  56

#define ESA_COMP_TRANS_START             58
#define ESA_COMP_TRANS_END               59
#define ESA_COMP_START_INTERCEPT         60
#define ESA_COMP_TRNSEVNT                61
#define ESA_COMP_FORCEINTRCPT            62
#define ESA_COMP_RNOE                    63
#define ESA_COMP_GETCONNECTION           64  
#define ESA_COMP_ADDCONNECTION           65  
#define ESA_COMP_DELCONNECTION           66  
#define ESA_COMP_UPDCONNECTION           67  
#define ESA_COMP_VERSION                 68

/*-------------------------- Interceptor */
#define ESA_COMP_RSS_INTERCEPT           70
/*-----------------------        OS PM Functions */

#define ESA_COMP_OS_SCRIPT               71  
#define ESA_COMP_OS_EVENT                72  
#define ESA_COMP_OS_ATTACH               73  
#define ESA_COMP_OS_WAIT                 74  
#define ESA_COMP_OS_LOCK_I               75  
#define ESA_COMP_OS_LOCK_T               76  
#define ESA_COMP_OS_LOCK                 77  
#define ESA_COMP_OS_UNLOCK               78  
#define ESA_COMP_OS_MBX_ATT              79  
#define ESA_COMP_OS_MBX_CRE              80  
#define ESA_COMP_OS_MBX_RD               81  
#define ESA_COMP_OS_MBX_WR               82  
#define ESA_COMP_OS_MBX_GNRL             83  
#define ESA_COMP_OS_GET_PASSWD           84  
#define ESA_COMP_ESAOSCS                 85 

/*--------- XModule Components -----------*/

#define XSA_DIAG_COMP_PARAMS             94
#define XSA_DIAG_COMP_NORM               95
#define XSA_DIAG_COMP_COMM               96
#define XSA_DIAG_COMP_LANG               97
#define XSA_DIAG_COMP_CONN               98
/*----------------------------------------------------------
        ESA_COMP_END_USA_API             99                 
------------------------------------------------------------*/


/*----------------------- Free for PM needs from 351 to 511 */
#define ESA_FIRST_PLATFORM_COMP          351

#define ESA_LAST_PLATFORM_COMP           511
/*----------------------------------------------------------*/

#endif /* API_COMP_H_INCLUDED */
