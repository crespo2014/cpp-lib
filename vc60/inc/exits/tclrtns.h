/*
 * tclrtns.h
 */

#include "tcl.h"
#include "tk.h"

typedef int (EssAPIRtn) ();

/*
 * ESS Tcl Variables 
 */
#define ESSENTUSERNAME          "EssEntUserName"
#define ESSENTUSERID            "EssEntUserID"
#define ESSUSERNAME             "EssUserName"
#define ESSSUPERUSER            "EssSuperUser"
#define ESSRSSUSERNAME          "EssRSSUserName"
#define ESSRSSNAME              "EssRSSName"
#define ESSRSSTYPE              "EssRSSType"
#define ESSENTITYTYPE           "EssEntityType"
#define ESSPASSWORD             "EssPassword"
#define ESSACTION               "EssAction"
#define ESSSEVERITY             "EssSeverity"
#define ESSSERIAL               "EssSerial"
#define ESSMESSAGE              "EssMessage"
#define ESSORIGIN               "EssOrigin"
#define ESSORIGINRSSTYPE	"EssOriginRssType"
#define ESSDEMO                 "EssDemo"
#define ESSMODE                 "EssMode"
#define ESSITEM                 "EssItem"
#define ESSFORMTYPE             "EssFormType"
#define ESSRETURN               "EssReturn"
#define ESSPROCESS              "EssProcess"
#define ESSADMIN                "EssAdmin"
#define ESSTRANSID              "EssTransID"
#define ESSPARENTTRANSID        "EssParentTransID"
#define ESSSTATUS               "EssStatus"
#define ESSEXTERNALID           "EssExternalID"
#define ESSUSERSYNCFLAG         "EssUserSyncFlag"
#define ESSRSSUSERSYNCFLAG      "EssRSSUserSyncFlag"
#define ESSJCNAME               "EssJCName"		/* Job code name */
#define ESSTEMPLRSSUSER         "EssTemplRSSUser"	/* RSS user may be created by template */
#define ESSSIMULATION           "EssSimulation"		/* Simulation mode flag */
#define ESSNUMCONUSERS          "EssNumConUsers"	/* Number of concurent RSS users */

/*
 * Functions
 */
#define ESSOPENDBTABLE          "EssOpenDBTable"
#define ESSREADDBTABLE          "EssReadDBTable"
#define ESSCLOSEDBTABLE         "EssCloseDBTable"
#define ESSGETFIRSTFIELD        "EssGetFirstField"
#define ESSGETNEXTFIELD         "EssGetNextField"
#define ESSGETFIRSTCHGFIELD     "EssGetFirstChgField"
#define ESSGETNEXTCHGFIELD      "EssGetNextChgField"
#define ESSGETFIELDCHANGED      "EssGetFieldChanged"
 
#define ESSGETFIELDVALUE        "EssGetFieldValue"
#define ESSGETADMINVALUE        "EssGetAdminValue"
#define ESSSETFIELDVALUE        "EssSetFieldValue"
#define ESSGETFIELDNUMBER       "EssGetFieldNumber"
#define ESSGETFIELDLABEL        "EssGetFieldLabel"
#define ESSDISPLAYMSG           "EssDisplayMessage"
#define ESSGETEXTERNALID        "EssGetExternalID"
#define ESSGETCONUSER           "EssGetConUser"		 /* Get concurent RSS user from array */
#define ESSSETRSSUSER           "EssSetRSSUser"          /* Sets one RSS user in conflict situation */

#define ESSPROCUNDEF            "UNDEFINED"
#define ESSPROCGUI              "GUI"
#define ESSPROCGTW              "GTW"
#define ESSPROCBATCH            "BATCH"
#define ESSPROCPMP              "PMP"
#define ESSPROCDATASYNC         "DATASYNC"
#define ESSPROCREFRESH          "REFRESH"
#define ESSPROCROUTER           "ROUTER"
#define ESSPROCSERVER           "SERVER"
#define ESSPROCACF2_KWD         "ACF2KWD"
#define ESSPROCCONFIG           "CONFIG"

#define FILE_NAME_SIZE          256
#define READDBTABLE_BUFFER      5120

int EssTLOpenDBTable();

int EssTLCloseDBTable();

int EssTLReadDBTable();

void set_processvar();
