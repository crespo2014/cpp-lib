//===========================================================================
//
// Module:		LNAGENT.HPP
//
// Description:
//
//		Class library definition for the LNAgent and LNAgentRunData classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNAGENT_HPP
#define LNAGENT_HPP

#ifndef STD_NAME_DEFS
#include <stdnames.h>
#endif
#ifndef ODS_DEFS
#include <ods.h>
#endif

#ifndef NSF_OBJECTS_DEFS
#include <nsfobjec.h>
#endif

#ifndef QUERYODS_DEFS
#include <queryods.h>
#endif

#ifndef AGENT_DEFS
#include <agents.h>
#endif

// Types of formula used by formula agent.
 
enum LNAGENTFORMULATYPE
{
	LNAGENTFORMULATYPE_MODIFY,
	LNAGENTFORMULATYPE_CREATE,
	LNAGENTFORMULATYPE_SELECT
};

// Security option flags.

typedef WORD LNAGENTEXECUTEFLAGS;

#define LNAGENTEXECUTEFLAGS_ENFORCE_SECURITY	0x0001
#define LNAGENTEXECUTEFLAGS_REOPEN_DB			0x0002
#define LNAGENTEXECUTEFLAGS_DEFAULT				0x0004

// Output options for Lotus Script agent.

enum LNAGENTOUTPUTOPTION
{
	LNAGENTOUTPUTOPTION_NONE,
	LNAGENTOUTPUTOPTION_LOG,
	LNAGENTOUTPUTOPTION_MEMORY,
	LNAGENTOUTPUTOPTION_MEMORY_APPEND
};

// Options for agent schedule.

enum LNAGENTSCHEDULE
{
	LNAGENTSCHEDULE_EVERY_N_HOURS_AND_MINUTES,
	LNAGENTSCHEDULE_EVERY_30_MINUTES,
	LNAGENTSCHEDULE_EVERY_HOUR,
	LNAGENTSCHEDULE_EVERY_2_HOURS,
	LNAGENTSCHEDULE_EVERY_4_HOURS,
	LNAGENTSCHEDULE_EVERY_8_HOURS,
	LNAGENTSCHEDULE_EVERY_DAY,
	LNAGENTSCHEDULE_EVERY_SUNDAY,
	LNAGENTSCHEDULE_EVERY_MONDAY,
	LNAGENTSCHEDULE_EVERY_TUESDAY,
	LNAGENTSCHEDULE_EVERY_WEDNESDAY,
	LNAGENTSCHEDULE_EVERY_THURSDAY,
	LNAGENTSCHEDULE_EVERY_FRIDAY,
	LNAGENTSCHEDULE_EVERY_SATURDAY,
	LNAGENTSCHEDULE_EVERY_MONTH,
	LNAGENTSCHEDULE_NEVER,
	LNAGENTSCHEDULE_MANUALLY_FROM_ACTIONS_MENU,
	LNAGENTSCHEDULE_MANUALLY_FROM_AGENT_LIST,
	LNAGENTSCHEDULE_BEFORE_NEW_MAIL_ARRIVES,
	LNAGENTSCHEDULE_IF_NEW_MAIL_ARRIVES,
	LNAGENTSCHEDULE_IF_DOCUMENTS_CREATED_OR_MODIFIED,
	LNAGENTSCHEDULE_IF_DOCUMENTS_PASTED
};

// Options for the type of documents that agent will act on.

enum LNAGENTDOCUMENTSOPTION
{
	LNAGENTDOCUMENTSOPTION_ALL_IN_DB = ASSISTSEARCH_TYPE_ALL,
	LNAGENTDOCUMENTSOPTION_NEW_AND_MODIFIED = ASSISTSEARCH_TYPE_MODIFIED,
	LNAGENTDOCUMENTSOPTION_UNREAD_IN_VIEW = ASSISTSEARCH_TYPE_UNREAD,
	LNAGENTDOCUMENTSOPTION_ALL_IN_VIEW = ASSISTSEARCH_TYPE_VIEW,
	LNAGENTDOCUMENTSOPTION_SELECTED = ASSISTSEARCH_TYPE_SELECTED,
	LNAGENTDOCUMENTSOPTION_RUN_ONCE = ASSISTSEARCH_TYPE_UI
};

//
//	Class definition for LNAgentRunData.
//

class LNIMPEXPCL LNAgentRunData
{

public:
	LNAgentRunData() { DocCount = 0; ExitCode = LNNOERROR; }
	LNAgentRunData( const LNAgentRunData &other );

	~LNAgentRunData() {}

	LNAgentRunData & operator=( const LNAgentRunData &other );

	virtual LNCLASSID GetClassID() { return LNCLASSID_LNAGENTRUNDATA; }

	LNDatetime GetAgentModificationDatetime() const { return LastModTime; }
	LNINT GetProcessedDocumentsCount() const { return DocCount; }
	TIMEDATE GetRunDatabaseID() const { return RunDbID; }
	LNDatetime GetRunDatetime() const { return LastRunTime; }
	LNSTATUS GetRunExitCode() const { return ExitCode; }
	LNString GetRunLog() const { return Log; }

private:

	LNAgentRunData( const ODS_ASSISTRUNINFO &summary, const char *log);

	LNDatetime LastRunTime;
	LNINT DocCount;
	LNDatetime LastModTime;
	TIMEDATE RunDbID;
	LNSTATUS ExitCode;
	LNString Log;
};

// Agent open flags. Not currently used.

typedef DWORD LNAGENTOPENFLAGS;

#define LNAGENTOPENFLAGS_DEFAULT 0

//
//	Class definition for LNAgent.
//
class LNIMPEXPCL LNAgent : public LNNote
{
friend class LNAgentArray;

public:
	LNAgent();
	LNAgent( const LNAgent &other );
	LNAgent( const LNNote &other );

	~LNAgent();

	LNAgent & operator=( const LNAgent &other );
	LNAgent & operator=( const LNNote &other );

	LNCLASSID GetClassID() const {return LNCLASS_LNAGENT;}

	LNSTATUS Execute(LNAGENTEXECUTEFLAGS flags = LNAGENTEXECUTEFLAGS_DEFAULT,
		LNAGENTOUTPUTOPTION option = LNAGENTOUTPUTOPTION_LOG, LNINT timelimit = 0) const;

	LNSTATUS Execute(const LNDocument &doc, 
		LNAGENTEXECUTEFLAGS flags = LNAGENTEXECUTEFLAGS_DEFAULT,
		LNAGENTOUTPUTOPTION option = LNAGENTOUTPUTOPTION_LOG, LNINT timelimit = 0) const;

	LNSTATUS Execute(const LNDocumentArray &docs,
		LNAGENTEXECUTEFLAGS flags = LNAGENTEXECUTEFLAGS_DEFAULT,
		LNAGENTOUTPUTOPTION option = LNAGENTOUTPUTOPTION_LOG) const;

	LNSTATUS ConvertR3MacroToAgent();

	LNSTATUS CreateJavaCode( const LNString &baseclassname, 
		const LNString &path, const LNText &filenames, LNAgentJava *javacode = 0 );

	LNSTATUS CreateJavaCode(  const LNString &baseclass,
							  const LNString &codepath,
							  const LNString &sourcejar, 
							  LNAgentJava *javacode,
							  const LNString *objectjar,
							  const LNString *resourcejar,
							  const LNText * librarynames);
/* NOTES_JAVA
	LNSTATUS CreateJavaCode(const LNString &classpath, 
							const LNString &baseclassname, 
							const LNString &codepath, 
							const LNText &filenames,
							LNAgentJava *javacode = 0,
							const LNText *librarynames = 0);
NOTES_JAVA */
	LNSTATUS CreateJavaCode( const LNAgentJava &javacode, LNAgentJava *newjavacode = 0);

    LNACTIONTYPE GetActionType() const;
	LNAGENTDOCUMENTSOPTION GetAgentDocumentsOption () const;

	LNText GetAgentOutputFromMemory() const;

	LNAgentRunData GetAgentRunData() const; 
	LNAGENTSCHEDULE GetAgentSchedule() const;
	LNBOOL GetAllowDesignRefreshToModify() const;
	LNBOOL GetAllowPublicAccessUsers () const;
	LNBOOL GetChooseServerWhenEnabled() const;
	LNString GetComment () const;
	LNINT GetDayOfMonth() const;
	LNDatetime GetEndDate() const;
	LNINT GetEndHour () const;
	LNSTATUS GetFormula (LNFormula *formula, LNAGENTFORMULATYPE *type ) const ;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
	LNBOOL GetHideFromR4Clients() const;
	LNSTATUS GetHoursAndMinutes(LNINT *hourts, LNINT *minutes) const;
	LNString GetInheritsFromTemplateName () const;
	LNBOOL GetIsEnabled() const;
	LNBOOL GetIsShared() const;
	LNSTATUS GetJavaCode( LNAgentJava *javacode) const;
	LNSTATUS GetLotusScript( LNLotusScript *script ) const;
	LNBOOL GetPropagateAllowDesignChange( );
	LNBOOL GetRunAsWebUser() const;
	LNBOOL GetRunOnWeekends() const;
	LNSTATUS GetSearches(LNSearches *searches) const;
	LNString GetServerName() const;
	LNBOOL GetShowSearchInSearchBarMenu () const;
	LNSTATUS GetSimpleActions(LNSimpleActions *actions) const;
	LNDatetime GetStartDate() const;
	LNINT GetStartHour() const;
	LNBOOL GetStoreHighlightsInDocuments () const;
	LNBOOL IsR3Macro() const;

	LNSTATUS Open( LNAGENTOPENFLAGS flags = LNAGENTOPENFLAGS_DEFAULT );

	virtual LNSTATUS Save(LNNOTESAVEFLAGS flags = LNNOTESAVEFLAGS_DEFAULT); 

	LNSTATUS SetAgentDocumentsOption ( LNAGENTDOCUMENTSOPTION wSearchType );
	LNSTATUS SetAgentSchedule(LNAGENTSCHEDULE option);
	LNSTATUS SetAlias(const LNString &alias);
	LNSTATUS SetAllowDesignRefreshToModify ( LNBOOL allowed );
	LNSTATUS SetAllowPublicAccessUsers (LNBOOL available);
	LNSTATUS SetChooseServerWhenEnabled( LNBOOL choose );
	LNSTATUS SetComment ( const LNString &comment );
	LNSTATUS SetDayOfMonth( LNINT day );
	LNSTATUS SetEndDate( const LNDatetime &datetime ) ;
    LNSTATUS SetEndHour ( LNINT time );
	LNSTATUS SetFormula (const LNFormula &formula, LNAGENTFORMULATYPE type = LNAGENTFORMULATYPE_MODIFY);
	LNSTATUS SetHideFromBrowsers(LNBOOL hide);	
	LNSTATUS SetHideFromClients( LNBOOL hide );
	LNSTATUS SetHideFromR4Clients( LNBOOL hide );
	LNSTATUS SetHoursAndMinutes(LNINT hours, LNINT minutes);
	LNSTATUS SetInheritsFromTemplateName ( const LNString &name);
	LNSTATUS SetIsEnabled(LNBOOL enable);
	LNSTATUS SetLotusScript( const LNLotusScript &script );
	LNSTATUS SetName ( const LNString &name );
	LNSTATUS SetPropagateAllowDesignChange( LNBOOL enable);
	LNSTATUS SetRunAsWebUser( LNBOOL run );	
	LNSTATUS SetRunOnWeekends( LNBOOL dont );
	LNSTATUS SetSearches(const LNSearches &searches);
	LNSTATUS SetServerName( const LNString &name);
	LNSTATUS SetShowSearchInSearchBarMenu ( LNBOOL show );
	LNSTATUS SetSimpleActions(const LNSimpleActions &actions);
	LNSTATUS SetStartDate( const LNDatetime &datetime ) ;
	LNSTATUS SetStartHour( LNINT time ) ; 
	LNSTATUS SetStoreHighlightsInDocuments (LNBOOL store);

private:

	LNAgent( LNDatabaseBody *db, NOTEID idnote );
	LNAgent & operator=( LNAgentBody *agentb ); // disabled
	LNAgentBody * GetAgentBody() const { return (LNAgentBody *) Body; }

	virtual void ValidateNoteType( const LNNote &note ) const;
	virtual void ValidateNoteType( const LNNoteBody *note ) const;
	virtual void ValidateNoteType( LNNOTETYPE type ) const;
};


#endif	//LNAGENT_HPP

