/********************************************************************
 *
 * Version Information:
 * ====================
 * File name       : %name: ClsNotifierPlugin.h %
 * Instance        : %instance: 3 %
 * Created by      : %created_by: auziel %
 * Created on      : %date_created: Mon Feb 02 17:50:51 2004 %
 * Current Version : %version: 1 %
 * Last Modified by: %derived_by: auziel %
 * Last Modified on: %date_modified: Mon Feb 02 17:50:52 2004 %
 *
 ********************************************************************
 *																	
 * Mod.ID		Who     When		Description						
 * ==================================================================
 * SA241202#01	Shlomi	24/12/02	Add support for DIAG level updates.
 ********************************************************************/

//////////////////////////////////////////////////////////////////////
//
// ClsNotifierPlugin.h: interface for the ClsNotifierPlugin class.
//
//////////////////////////////////////////////////////////////////////

#ifndef NOTIFIER_PLUGIN_INTERFACE_INCLUDE_H
#define NOTIFIER_PLUGIN_INTERFACE_INCLUDE_H

#include <string>
#include "SoiNotifier.h"

namespace notifier
{
const int NOTIFIER_HEADER = 3105;

class ClsNotifierPlugin  
{
public:
	static ClsNotifierPlugin *plugin;
	NotifierPluginHeader m_header;

	ClsNotifierPlugin(const std::string description, const int version = NOTIFIER_HEADER);
	virtual ~ClsNotifierPlugin();

	static ESA_RC Init(
					NotifierPluginModule *thisModule, 
					const char *rssName,
					NOTIFY_MSG_FUNC_PTR NotifyMsgFunc,
					const ADMIN_PARAMS_rec_typ *adminParam
					);
	
	static ESA_RC Start(
					NotifierPluginModule *thisModule,
					const ADMIN_PARAMS_rec_typ *adminParam
					);

	static ESA_RC Stop(
					NotifierPluginModule *thisModule,
					const ADMIN_PARAMS_rec_typ *adminParam
					);

	static ESA_RC Term(
					NotifierPluginModule *thisModule,
					const ADMIN_PARAMS_rec_typ *adminParam
					);
// SA241202#01 start
	static ESA_RC UpdateDiagLevels(
					NotifierPluginModule *thisModule,
					const ESA_DIAG_LEVEL_typ *diagLevelArray,
					const ADMIN_PARAMS_rec_typ *adminParam
					);
// SA241202#01 end
	static ESA_RC LoadPlugin(
					NotifierPluginModule *module
					);

protected:

	virtual ESA_RC Init(
					const std::string rssName,
					NOTIFY_MSG_FUNC_PTR NotifyMsgFunc,
					const ADMIN_PARAMS_rec_typ *adminParam
					) = 0;

	virtual ESA_RC Start(
					const ADMIN_PARAMS_rec_typ *adminParam
					) = 0;

	virtual ESA_RC Stop(
					const ADMIN_PARAMS_rec_typ *adminParam
					) = 0;

	virtual ESA_RC Term(
					const ADMIN_PARAMS_rec_typ *adminParam
					) = 0;
// SA241202#01 start
	virtual ESA_RC UpdateDiagLevels(
					const ESA_DIAG_LEVEL_typ *diagLevelArray,
					const ADMIN_PARAMS_rec_typ *adminParam
					) = 0;
// SA241202#01 end
};
}

#endif // NOTIFIER_PLUGIN_INTERFACE_INCLUDE_H
