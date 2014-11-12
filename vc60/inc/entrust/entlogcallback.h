#ifndef _ENT_LOG_CALLBACK_H
#define _ENT_LOG_CALLBACK_H

/* definitions used by the logging callback interface */
typedef enum {
   LOGLEV_NONE   = 0,
   LOGLEV_ERROR  = 1,
   LOGLEV_WARN   = 2,
   LOGLEV_INFO   = 3,
   LOGLEV_DETAIL = 4,
   LOGLEV_SUPER  = 5
} LogLevel;

class GString;
typedef void (*LogCallback)(void *appdata, LogLevel loglevel,
                            const GString &logstr);

/*
 * functions for accessing log callback functions
 */

/*
 * get/set the log callback function.  If not set, it defaults to NULL
 */
EXPT32 void        SetLogCallback(LogCallback callback);
EXPT32 LogCallback GetLogCallback();

/*
 * get/set the log level value.  If not set, it defaults to LOGLEV_NONE
 */
EXPT32 void        SetLogLevel(LogLevel loglevel);
EXPT32 LogLevel    GetLogLevel();

/*
 * get/set the log appdata.  If not set, it defaults to NULL
 */
EXPT32 void        SetLogAppData(void *appdata);
EXPT32 void       *GetLogAppData();

#endif
