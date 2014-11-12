/********************************************************************
 *
 * Version Information:
 * ====================
 * File name       : %name: SoiNotifier.h %
 * Instance        : %instance: 4 %
 * Created by      : %created_by: ahershko %
 * Created on      : %date_created: Sun Feb 13 06:34:27 2005 %
 * Current Version : %version: 3 %
 * Last Modified by: %derived_by: ahershko %
 * Last Modified on: %date_modified: Tue Feb 24 15:19:06 2004 %
 *
 ********************************************************************
 *																	
 * Mod.ID		Who     When		Description						
 * ==================================================================
 *
 * ------------------------ Version 3.1.06 --------------------------
 *
 * SA190802#01	Shlomi	19/08/02	Handle rename of users and groups
 * SA241202#01	Shlomi	24/12/02	Add support for DIAG level updates.
 *
 * ------------------------ Version 3.1.07 --------------------------
 *
 * WSAN101417	Shlomi	02/10/03	The Notifier should send the time of when  
 *									the change was intercepted to SOI
 * AU110204		AviU				Expent the interface to support
 *									load\unload
 * AU170204		AviU				Expent the interface to support
 *									password interceptor
 * WSAN101548	AmirH	12/10/04	Support high priority actions (Apply SA080604#01 of FD5802)
 ********************************************************************/

#ifndef NOTIFIER_PLUGIN_MODULE_INCLUDE_H
#define NOTIFIER_PLUGIN_MODULE_INCLUDE_H



#include <time.h>		
#include "esaglobs.h"
#include "esaapi.h"

#ifdef WIN32
	typedef void* SOI_SHLIB_HANDLE;
#elif defined Solaris
	typedef void* SOI_SHLIB_HANDLE;
#elif defined AIX
	typedef void* SOI_SHLIB_HANDLE;
#elif defined Linux
	typedef void* SOI_SHLIB_HANDLE;
#else
#	error	"Define the currect type for your compiler"
#endif




typedef enum {AC_UPDATE, AC_DELETE, AC_RENAME, AC_ADD, AC_MOVE, AC_REVOKE}	Action;
typedef enum {YES, NO, UNKNOWN}	TriType;
typedef enum {SN_NO, SN_YES} boolType;

struct _NotifierPluginModule;

/*/////////////////////////////////////////////////////////////////////////////
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: Each message, which is sent from the Notifier to the SOI 
//				  is of following structure.
//
// Remarks		: All the char pointer (char*) fields are NULL terminated.
//
// Parameters	:
//
///////////////////////////////////////////////////////////////////////////// */
typedef struct
{
	size_t	userNameLen;
	char*	userName;			/* for rename actions */
	TriType isConnection;	
	size_t	groupNameLen;
	char*	groupName;			/* for connection upates		*/
	size_t	pwdLen;
	char*	pwd;				/* New password - if password has been changed */
	boolType onlyPwdChange;		/* AU170204: if SN_YES then this message is only for  */
								/* password change. Otherwise check the pwd  */
								/* field to verify if password has been changed. */
	int isPwdChangeInNextLogin;

} UserMsg;

typedef struct
{
	size_t groupNameLen;
	char *groupName;			/* for rename actions */
	TriType isConnection;	
	size_t userNameLen;
	char *userName;				/* // for connection upates */

} GroupMsg;

typedef struct
{
	size_t containerNameLen;
	char *containerName;		/* for rename actions */

} ContainerMsg;

typedef struct
{
	size_t userNameLen;
	char *userName;
	size_t groupNameLen;
	char *groupName;

} ConnectionMsg;

typedef struct
{
	size_t resourceNameLen;
	char *resourceName;

} ResourceMsg;

typedef union 
{
	UserMsg userInfo;
	GroupMsg groupInfo;
	ContainerMsg containerInfo;
	ConnectionMsg connectionInfo;
	ResourceMsg resourceInfo;

} MsgTypeUnion;

typedef struct
{
	size_t size;

	size_t rssNameLen;
	char *rssName;

	size_t rssTypeLen;
	char *rssType;

	size_t objIDLen;
	char *objID;

	size_t objNameLen;
	char *objName;				/* human readable name */

	size_t adminNameLen;
	char *adminName;			/* event originator */

	OBJECT_TYPE_typ objType;
	Action action;				

	int isAddActSupported;		
	int isRenameActSupported;	
	int canDeleteSubordinates;

	MsgTypeUnion typeSpecInfo;

	BOOL	isHighPriority; /* if true then this message will by pushed to the
							   head of the SOI queue */

	time_t changeTime;				/* The time the change occur on the RSS. 0 if unknown.	 */
	time_t changeInterceptionTime;	/* The time the change intercepted by Notifier */
} ChangeMsg;

#ifdef __cplusplus
extern "C"
{
#endif

/* ////////////////////////////////////////////////////////////////////////////
//
// Authors		: Shlomi Afia
//
// Date			: Tuesday, July 09, 2002
//
// Description	: Following are function for creation and deletion of messages 
//				  of type ChangeMsg .
//
// Remarks		: 
//
///////////////////////////////////////////////////////////////////////////// */

ChangeMsg *ChangeMsg_ConstructUserMsg(
				const char *rssName,
				const char *rssType,
				const char *objID,
				const char *objName,				/* human readable name */
				const char *adminName,
				const Action action,
				const char *userName,				/* for rename actions */
				const TriType isConnection,	
				const char *groupName,				/* for connection upates */
				const int isPwdChangeInNextLogin,
				const char *pwd,
				const int onlyPwdChange,		/* true if this msg is only for pwd change */
				long changeTime,					/* The time the change occur on the RSS. 0 if unknown.				 */
				long changeInterceptionTime		/* The time the change intercepted by Notifier */
				);

ChangeMsg *ChangeMsg_ConstructGroupMsg(
				const char *rssName,
				const char *rssType,
				const char *objID,
				const char *objName,				/* human readable name */
				const char *adminName,
				const Action action,
				const char *groupName,				/* for rename actions */
				const TriType isConnection,	
				const char *userName,				/* for connection upates */	
				time_t changeTime,					/* The time the change occur on the RSS. 0 if unknown.				 */
				time_t changeInterceptionTime		/* The time the change intercepted by Notifier */
				);

ChangeMsg *ChangeMsg_ConstructContainerMsg(
				const char *rssName,
				const char *rssType,
				const char *objName,				/* human readable name */
				const char *objID,
				const char *adminName,
				const Action action,
				const char *containerName,			/* for rename actions */
				time_t changeTime,					/* The time the change occur on the RSS. 0 if unknown.				 */
				time_t changeInterceptionTime		/* The time the change intercepted by Notifier */
				);

ChangeMsg *ChangeMsg_ConstructConnectionMsg(
				const char *rssName,
				const char *rssType,
				const char *objID,
				const char *objName,				/* human readable name */
				const char *adminName,
				const Action action,
				const char *userName,
				const char *groupName,		
				time_t changeTime,					/* The time the change occur on the RSS. 0 if unknown.				 */
				time_t changeInterceptionTime		/* The time the change intercepted by Notifier */
				);

ChangeMsg *ChangeMsg_ConstructRssParamMsg(
				const char *rssName,
				const char *rssType,
				const char *objID,
				const char *objName,				/* human readable name */
				const char *adminName,
				time_t changeTime,					/* The time the change occur on the RSS. 0 if unknown.				 */
				time_t changeInterceptionTime		/* The time the change intercepted by Notifier */
				);

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: ChangeMsg_Destruct
//
// Authors		: Shlomi Afia
//
// Date		 	: Mon, Aug 5, 2002
//
// Description	: Destruct a ChangeMsg structure
//
// Remarks		:
//
// Returns		:
//
// Parameters	: 
//
////////////////////////////////////////////////////////////////////////////// */
void ChangeMsg_Destruct(ChangeMsg *msg);

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: ChangeMsg_Destruct
//
// Authors		: Shlomi Afia
//
// Date		 	: Mon, Aug 12, 2002
//
// Description	: Destruct a ChangeMsg structure
//
// Remarks		:
//
// Returns		:
//
// Parameters	: 
//
////////////////////////////////////////////////////////////////////////////// */
ChangeMsg *ChangeMsg_Duplicate(const ChangeMsg *msg);

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: ChangeMsg_ActionToString
//
// Authors		: Shlomi Afia
//
// Date		 	: Mon, Aug 5, 2002
//
// Description	: 
//
// Remarks		: 
//
// Returns		:
//
// Parameters	: 
//
////////////////////////////////////////////////////////////////////////////// */
char *ChangeMsg_ActionToString(const ChangeMsg *msg);

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: ChangeMsg_ObjTypeToString
//
// Authors		: Shlomi Afia
//
// Date		 	: Mon, Aug 5, 2002
//
// Description	: 
//
// Remarks		: 
//
// Returns		:
//
// Parameters	: 
//
////////////////////////////////////////////////////////////////////////////// */
char *ChangeMsg_ObjTypeToString(const ChangeMsg *msg);





#ifdef __cplusplus
}
#endif

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: NOTIFY_MSG_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: 
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC NOTIFY_MSG_FUNC_TYPE(
				const ChangeMsg*
				);

typedef NOTIFY_MSG_FUNC_TYPE* NOTIFY_MSG_FUNC_PTR;

/* ////////////////////////////////////////////////////////////////////////////
//
// Authors		: Shlomi Afia
//
// Date			: Tuesday, July 09, 2002
//
// Description	: Following are function prototypes for the Init, Start, Stop, Term
//				  functions that each SOI Notifier must implement. 
//
// Remarks		: Each of the following functions must return as soon as possible in 
//				  order to allow the normal flow of the calling process.
//
// Samples		: This is a sampe code for a notifier written in C
//
//		#include <stdio.h>
//		#include "SoiNotifier.h"
//		
//		#define NOTIFIER_HEADER 0x10;
//		
//		int APIENTRY DllMain( HANDLE hModule, 
//							   DWORD  ul_reason_for_call, 
//							   LPVOID lpReserved
//							 )
//		{
//			return TRUE;
//		}
//		
//		typedef struct _LocalData
//		{
//			char rssName[50];
//			NOTIFY_MSG_FUNC_PTR NotifyMessageFunc;
//		} LocalData;
//		
//		NotifierPluginHeader header;
//		LocalData localData;
//		
//		ESA_RC Init(NotifierPluginModule *thisModule, 
//					const char *rssName,
//					NOTIFY_MSG_FUNC_PTR NotifyMsgFunc,
//					const ADMIN_PARAMS_rec_typ* adminParam
//					)
//		{
//			strcpy(((LocalData *)thisModule->userData)->rssName, rssName);
//			printf("LdapNotifier::Init() for RSS %s\n", rssName);
//		
//			((LocalData *)thisModule->userData)->NotifyMessageFunc = NotifyMsgFunc;
//			
//			return ESA_OK;
//		}
//		
//		ESA_RC Start(NotifierPluginModule *thisModule,
//					 const ADMIN_PARAMS_rec_typ* adminParam
//					 )
//		{
//			ChangeMsg *msg;
//			int i;
//		
//			for (i = 0; i < 10; i++)
//			{
//				printf("LdapNotifier::Init() : Creating new Change Message ptr =  %d\n", msg);
//				
//				msg = ChangeMsg_ConstructUserMsg(((LocalData *)thisModule->userData)->rssName,
//												 NULL,
//												 NULL,
//												 NULL,
//												 AC_UPDATE,
//												 "CN=stam, DN=ldap_stam",
//												 UNKNOWN,
//												 NULL,
//												 FALSE,
//												 NULL);
//		
//				((LocalData *)thisModule->userData)->NotifyMessageFunc(msg);
//		
//				Sleep(2000);
//			}
//		
//			return ESA_OK;
//		}
//		
//		ESA_RC Stop(NotifierPluginModule *thisModule,
//					const ADMIN_PARAMS_rec_typ* adminParam
//					)
//		{
//			return ESA_OK;
//		}
//		
//		ESA_RC Term(NotifierPluginModule *thisModule,
//					const ADMIN_PARAMS_rec_typ* adminParam
//					)
//		{
//			return ESA_OK;
//		}
//
//		ESA_RC UpdateDiagLevels(NotifierPluginModule *thisModule,
//					const ESA_DIAG_LEVEL_typ *diagLevelArray,
//					const ADMIN_PARAMS_rec_typ* adminParam
//					)
//		{
//			return ESA_OK;
//		}
//
//		ESA_RC LoadPlugin(NotifierPluginModule *module)
//		{
//			module->Init = Init;
//			module->Start = Start;
//			module->Stop = Stop;
//			module->Term = Term;
//			module->UpdateDiagLevels = UpdateDiagLevels;
//			module->userData = (void *)&localData;
//		
//			return ESA_OK;
//		}
//		
//		
//		__declspec( dllexport ) NotifierPluginHeader* GetPluginHeader()
//		{
//			header.version = NOTIFIER_HEADER;
//			header.LoadPlugin = LoadPlugin;
//			return &header;
//		}
//
// 
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: INIT_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: The SOI is using this function to initialize each Notifier. 
//				  When the SOI calls this function it specifies the RSS name 
//				  and a pointer to a callback function that each Notifier will use 
//				  to notify the SOIManager about events. The Notifier should use this 
//				  function to perform any initialization steps to its RSS, like building 
//				  and setting search criteria. The Notifier can use the userDataHandle 
//				  for internal use.
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC INIT_FUNC_TYPE(
				struct _NotifierPluginModule*, 
				const char*, 
				NOTIFY_MSG_FUNC_PTR,
				const ADMIN_PARAMS_rec_typ*
				);

typedef INIT_FUNC_TYPE *INIT_FUNC_PTR;

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: START_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: By calling this function, the SOI signals to the Notifier 
//				  that it is ready to receive events. This function can be called 
//				  alternately by the SOIManager after a call to Stop().
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC START_FUNC_TYPE(
				struct _NotifierPluginModule*,
				const ADMIN_PARAMS_rec_typ*
				);

typedef START_FUNC_TYPE *START_FUNC_PTR;

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: STOP_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: By calling this function the SOIManager requests the Notifier 
//				  to stop sending events. When a Notifier has been stopped it 
//				  should store new incoming events until the SOIManager will call 
//				  the Start() function again, and pass these events to the SOIManager.
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC STOP_FUNC_TYPE(
				struct _NotifierPluginModule*,
				const ADMIN_PARAMS_rec_typ*
				);

typedef STOP_FUNC_TYPE *STOP_FUNC_PTR;

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: TERM_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: For termination. The SOIManager calls this function before it 
//				  goes down. The Notifier should use this function to save any 
//				  necessary data like search handles. The Notifier is responsible 
//				  for freeing userDataHandle allocations and setting the pointer 
//				  to NULL.
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC TERM_FUNC_TYPE(
				struct _NotifierPluginModule*,
				const ADMIN_PARAMS_rec_typ*
				);

typedef TERM_FUNC_TYPE *TERM_FUNC_PTR;

/* /////////////////////////////////////////////////////////////////////////////
//
// Function		: UPDATE_DIAG_LEVEL_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, December 24, 2002
//
// Description	: This function is called by the SOIManager when ever the diagnostics
//				  level file is changed.
//				  Notifiers, which are using threads, should update the diagnostics
//				  level table of each thread.
//
// Remarks		: 
//
// Returns      :
//
// Parameters	:
//
////////////////////////////////////////////////////////////////////////////// */
typedef ESA_RC UPDATE_DIAG_LEVEL_FUNC_TYPE(
				struct _NotifierPluginModule*,
				const ESA_DIAG_LEVEL_typ *diagLevelArray,
				const ADMIN_PARAMS_rec_typ*
				);

typedef UPDATE_DIAG_LEVEL_FUNC_TYPE *UPDATE_DIAG_LEVEL_FUNC_PTR;

typedef struct _NotifierPluginModule
{
	char *description;		

	SOI_SHLIB_HANDLE pluginHandle;	/* filled in by calling app */

	INIT_FUNC_PTR Init;
	START_FUNC_PTR Start;
	STOP_FUNC_PTR Stop;
	TERM_FUNC_PTR Term;
	UPDATE_DIAG_LEVEL_FUNC_PTR UpdateDiagLevels;	

	void *userData;			
	
} NotifierPluginModule;

#ifdef __cplusplus
extern "C"
{
#endif

NotifierPluginModule *NotifierPluginModule_Construct();

void NotifierPluginModule_Destruct(NotifierPluginModule*);

#ifdef __cplusplus
}
#endif

typedef struct 
{
	int version;												
	char *description;					/* description of plugin */

	/* /////////////////////////////////////////////////////////////////////////////
	//
	// Function		: LoadPlugin
	//
	// Authors		: Shlomi Afia
	//
	// Date		    : Tuesday, July 09, 2002
	//
	// Description	: Called by the SOI in order to load the Notifier plug-in. 
	//				  The Notifier returns through this function a pointer to a structure 
	//				  of type NotifierPluginModule that includes function pointers to all
	//				  the rest of its implemented functions, which are describe above. 
	//
	// Remarks		: 
	//
	// Returns      : ESA_RC
	//
	// Parameters	: NotifierPluginModule
	//
	////////////////////////////////////////////////////////////////////////////// */
	ESA_RC (*LoadPlugin)(struct _NotifierPluginModule *module);	/* module retrieval function */
	
} NotifierPluginHeader;

/*
 *	The load\unload functions name - the implimentor must use this names
 *	so the Observer will know which symbols to load.
 */
#define LOAD_NOTIFIER_FUNC_NAME		"GetPluginHeader"
#define UNLOAD_NOTIFIER_FUNC_NAME	"UnloadLibrary"

#ifdef WIN32
#define DLL_NOTIFIER_EXPORT __declspec(dllexport)
#else
#define DLL_NOTIFIER_EXPORT
#endif

/**
 *	LOAD_NOTIFIER_FUNC_TYPE - Load the notifier library
 *	
 *	Notifier writer must impliment this function and make any
 *  initilizetion.
 *  The function name must be GetPluginHeader
 *
 *	@param 
 *	@return Struct with the functions pointer
 *
 */
/* /__declspec( dllexport ) NotifierPluginHeader* GetPluginHeader(void*); */
typedef NotifierPluginHeader* LOAD_NOTIFIER_FUNC_TYPE(void*);
typedef LOAD_NOTIFIER_FUNC_TYPE* LOAD_NOTIFIER_FUNC_PTR;

/**
 *	UNLOAD_NOTIFIER_FUNC_TYPE - Unload the notifier library
 *	
 *	Notifier writer must impliment this function and make lbrary 
 *  cleaning.
 *  The function name must be UnloadLibrary
 *  
 */
typedef void UNLOAD_NOTIFIER_FUNC_TYPE(void*);
typedef UNLOAD_NOTIFIER_FUNC_TYPE* UNLOAD_NOTIFIER_FUNC_PTR;



/*
//////////////////////////////////////////////////////////////////////////////
//
// Function		: GET_NOTIFIER_PLUGIN_HEADER_FUNC_TYPE
//
// Authors		: Shlomi Afia
//
// Date		    : Tuesday, July 09, 2002
//
// Description	: Returns a pointer structure of type NotifierPluginHeader that 
//				  describe this Notifier plug-in module:
//
// Remarks		: 
//
// Returns      : NotifierPluginHeader
//
// Parameters	:
//
//////////////////////////////////////////////////////////////////////////////
typedef NotifierPluginHeader *GET_NOTIFIER_PLUGIN_HEADER_FUNC_TYPE(
				void		// a function from a DLL
				);    

typedef GET_NOTIFIER_PLUGIN_HEADER_FUNC_TYPE* GET_NOTIFIER_PLUGIN_HEADER_FUNC_PTR;
*/

#endif /* NOTIFIER_PLUGIN_MODULE_INCLUDE_H */
