//===========================================================================
//
// Module:		LNDB.HPP
//
// Description:
//
//		Class library definition for LNDatabase and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNDB_HPP
#define LNDB_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

#ifndef LNACL_HPP
#include "lnacl.hpp"
#endif

class LNSelectiveReplication {};
//
//	Class definition for LNSearchOptions.
//
class LNIMPEXPCL LNSearchOptions : public LNNotesClass
{

public:
	LNSearchOptions();

	LNSearchOptions( const LNSearchOptions &other );

	~LNSearchOptions();

	LNSearchOptions & operator=( const LNSearchOptions &other );

	LNDatetime GetBeginDate() const;

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNSEARCHOPTIONS;}

	LNDatetime GetCompletedDate() const;
	LNString GetDesignFlagsPattern() const;
	LNString GetDesignFlagsAny() const;
	LNString GetDesignFlagsNone() const;
	LNString GetDesignFlagsAll() const;

	LNDatetime GetEndDate() const;

	LNINT GetMaxNotes() const;

	LNNOTETYPE GetNoteType() const;

	LNSTATUS SetBeginDate( const LNString &begindate );
	LNSTATUS SetBeginDate( const LNDatetime &begindate );
	LNSTATUS SetDesignFlagsPattern(const LNString &pattern);

	LNSTATUS SetEndDate( const LNString &enddate );
	LNSTATUS SetEndDate( const LNDatetime &enddate );

	LNSTATUS SetMaxNotes( LNINT maxnotes );

	LNSTATUS SetNoteType( LNNOTETYPE notetype );

private:
//	LNSTATUS ParsePattern();
	LNSTATUS SetCompletedDate( TIMEDATE *completeddate );

	TIMEDATE BeginDate;
	TIMEDATE CompletedDate;
	TIMEDATE EndDate;
	LNINT MaxNotes;
	LNNOTETYPE NoteType;
	LNString Pattern;
	LNString Any;
	LNString None;
	LNString All;
};

//
//	Class definition for LNFTIndexStatistics.
//
class LNIMPEXPCL LNFTIndexStatistics : public LNNotesClass
{

public:
	LNFTIndexStatistics();

	LNFTIndexStatistics( const LNFTIndexStatistics &other );

	~LNFTIndexStatistics();

	LNFTIndexStatistics & operator=( const LNFTIndexStatistics &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNFTINDEXSTATISTICS;}

	LNINT GetNumberOfBytesIndexed() const;

	LNINT GetNumberOfDocsAdded() const;

	LNINT GetNumberOfDocsDeleted() const;

	LNINT GetNumberOfDocsUpdated() const;

private:
	void Assign( FT_INDEX_STATS stats );

	FT_INDEX_STATS Statistics;
};

//
//	Class definition for LNFTSearchOptions.
//
class LNIMPEXPCL LNFTSearchOptions : public LNNotesClass
{

public:
	LNFTSearchOptions();

	LNFTSearchOptions( const LNFTSearchOptions &other );

	~LNFTSearchOptions();

	LNFTSearchOptions & operator=( const LNFTSearchOptions &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNFTSEARCHOPTIONS;}

	LNBOOL GetDatabaseIndex() const;

	LNBOOL GetDomainSearch() const;

	LNBOOL GetFileIndex() const;

	LNBOOL GetFuzzySearch() const;

	LNINT GetMaxDocuments() const;

	LNFTSEARCHORDER GetSortOrder() const;

	LNBOOL GetStemWords() const;

	LNBOOL GetThesaurusWords() const;

	LNBOOL GetURLFormat() const;

	void SetDatabaseIndex( LNBOOL dbindex );

	void SetDomainSearch( LNBOOL domainflag );

	void SetFileIndex( LNBOOL fileindex );

	void SetFuzzySearch( LNBOOL fuzzyflag );

	LNSTATUS SetMaxDocuments( LNINT maxdocuments );

	LNSTATUS SetSortOrder( LNFTSEARCHORDER sortorder );

	void SetStemWords( LNBOOL stemwords );

	void SetThesaurusWords( LNBOOL theswords );

	void SetURLFormat( LNBOOL urlflag );

private:
	DWORD GetOptions() const {return Options;}

	WORD MaxDocuments;
	DWORD Options;
};

#ifndef LNRTTYPE_HPP
#include "lnrttype.hpp"
#endif
//
//	Class definition for LNDatabase.
//
class LNIMPEXPCL LNDatabase : public LNSmartPtr
{
friend class LNCalendar;
friend class LNCalendarEntryArray;
friend class LNNote;
friend class LNNoteArray;
friend class LNNotesSession;

public:
	LNDatabase() : LNSmartPtr() {}
	LNDatabase( const LNDatabase &other ) : LNSmartPtr(other) {}

	~LNDatabase() {}
	
	LNDatabase & operator=( const LNDatabase &other );

	LNBOOL AgentExists( const LNString &agentname ) const;

	LNSTATUS CreateAgent( const LNString &agentname, LNBOOL shared, LNAgent *newagent );
	LNSTATUS CreateAgent( LNAgent &agent, LNAgent *newagent);

	LNSTATUS DeleteAgent( const LNString &agentname );
	LNSTATUS DeleteAgent( LNAgent *agent );

	LNSTATUS GetAgent( const LNString &agentname, LNAgent *agent );
	LNSTATUS GetAgent( const char *agentname, LNAgent *agent )
		{ return GetAgent(LNString(agentname), agent); }
	LNSTATUS GetAgent( const NOTEID idnote, LNAgent *agent );
	LNSTATUS GetAgent( const UNID *unidnote, LNAgent *agent );
	LNSTATUS GetAgent( NOTEHANDLE handle, LNAgent *agent )
		{ return GetNote(handle, (LNNote *) agent); }
	
	LNSTATUS GetAgents( LNAgentArray *agents, LNBOOL getPrivate = TRUE );

	LNBOOL AppletExists( const LNString &appletname ) const;

	LNSTATUS CreateApplet( const LNString &appletname,
							const LNString &codepath,
							const LNText &files,
							LNAppletResource *newapplet = 0 );
	LNSTATUS CreateApplet( LNAppletResource &applet, LNAppletResource *newapplet);

	LNSTATUS DeleteApplet( const LNString &appletname );
	LNSTATUS DeleteApplet( LNAppletResource *applet );

	LNSTATUS GetApplet( const LNString &appletname, LNAppletResource *applet );
	LNSTATUS GetApplet( const char *appletname, LNAppletResource *applet )
		{ return GetApplet(LNString(appletname), applet); }
	LNSTATUS GetApplet( const NOTEID idnote, LNAppletResource *applet );
	LNSTATUS GetApplet( const UNID *unidnote, LNAppletResource *applet );
	LNSTATUS GetApplet( NOTEHANDLE handle, LNAppletResource *applet )
		{ return GetNote(handle, (LNNote *) applet); }
	
	LNSTATUS GetApplets( LNAppletResourceArray *applets );
	
	LNSTATUS CreateDocument( LNDocument *newdoc );
	LNSTATUS CreateDocument( LNDocument *newdoc, const LNString &form );
	LNSTATUS CreateDocument( LNDocument &document, LNDocument *newdoc = 0 );

	LNSTATUS DeleteDocument( LNDocument *document );
	
	LNSTATUS GetDocument( const NOTEID idnote, LNDocument *doc );
	LNSTATUS GetDocument( const UNID *unidnote, LNDocument *doc );
	LNSTATUS GetDocument( NOTEHANDLE handle, LNDocument *doc )
		{ return GetNote(handle, (LNNote *) doc); }

	LNSTATUS GetDocuments( LNDocumentArray *docs );

	LNSTATUS CreateForm( const LNString &formname, LNForm *newform );
	LNSTATUS CreateForm( LNForm &form, LNForm *newform );

	LNSTATUS DeleteForm( const LNString &formname )
		{ return DeleteFormXYZ(formname); }
	LNSTATUS DeleteForm( LNForm *form )
		{ return DeleteFormXYZ(form); }

	LNBOOL FormExists( const LNString &formname ) const;
	
	LNSTATUS GetDefaultForm( LNForm *form ) const;

	LNSTATUS GetForm( const LNString &formname, LNForm *form )
		{ return GetFormXYZ(formname,form); }
	LNSTATUS GetForm( const char *formname, LNForm *form )
		{ return GetFormXYZ(LNString(formname), form); }
	LNSTATUS GetForm( const NOTEID idnote, LNForm *form )
		{ return GetFormXYZ(idnote,form); }
	LNSTATUS GetForm( const UNID *unidnote, LNForm *form )
		{ return GetFormXYZ(unidnote,form); }
	LNSTATUS GetForm( NOTEHANDLE handle, LNForm *form )
		{ return GetNote(handle, (LNNote *) form); }
	
	LNSTATUS GetForms( LNFormArray *forms );

	// Framesets
	LNBOOL FramesetExists( const LNString &framesetname) const;

	LNSTATUS CreateFrameset( const LNString &framesetname, 
	const LNFrameSplitOptions &options, LNFrameset* newframeset = 0);
	LNSTATUS CreateFrameset( LNFrameset &frameset, LNFrameset *newframeset = 0);

	LNSTATUS DeleteFrameset( const LNString &framesetname );
	LNSTATUS DeleteFrameset( LNFrameset *Frameset );

	LNSTATUS GetFrameset( const LNString &framesetname, LNFrameset *Frameset );
	LNSTATUS GetFrameset( const char *framesetname, LNFrameset *Frameset )
		{ return GetFrameset(LNString(framesetname), Frameset); }
	LNSTATUS GetFrameset( const NOTEID idnote, LNFrameset *Frameset );
	LNSTATUS GetFrameset( const UNID *unidnote, LNFrameset *Frameset );
	LNSTATUS GetFrameset( NOTEHANDLE handle, LNFrameset *Frameset )
		{ return GetNote(handle, (LNNote *) Frameset); }
	
	LNSTATUS GetFramesets( LNFramesetArray *framesets );

	// Image resources
	LNBOOL ImageExists( const LNString &imagename) const;


	LNSTATUS CreateImage( const LNString &imagename, 
		const LNString &filepath, LNImageResource *newimage = 0);
	LNSTATUS CreateImage( LNImageResource &image, LNImageResource *newimage = 0);

	LNSTATUS DeleteImage( const LNString &imagename );
	LNSTATUS DeleteImage( LNImageResource *Image );

	LNSTATUS GetImage( const LNString &imagename, LNImageResource *Image );
	LNSTATUS GetImage( const char *imagename, LNImageResource *Image )
		{ return GetImage(LNString(imagename), Image); }
	LNSTATUS GetImage( const NOTEID idnote, LNImageResource *Image );
	LNSTATUS GetImage( const UNID *unidnote, LNImageResource *Image );
	LNSTATUS GetImage( NOTEHANDLE handle, LNImageResource *Image )
		{ return GetNote(handle, (LNNote *) Image); }
	
	LNSTATUS GetImages( LNImageResourceArray *images );

		// Navigators
	LNBOOL NavigatorExists( const LNString &navigatorname) const;

	LNSTATUS CreateNavigator( const LNString &navigatorname, LNNavigator *newnavigator = 0);
	LNSTATUS CreateNavigator( LNNavigator &navigator, LNNavigator *newnavigator = 0);

	LNSTATUS DeleteNavigator( const LNString &navigatorname );
	LNSTATUS DeleteNavigator( LNNavigator *Navigator );

	LNSTATUS GetNavigator( const LNString &navigatorname, LNNavigator *Navigator );
	LNSTATUS GetNavigator( const char *navigatorname, LNNavigator *Navigator )
		{ return GetNavigator(LNString(navigatorname), Navigator); }
	LNSTATUS GetNavigator( const NOTEID idnote, LNNavigator *Navigator );
	LNSTATUS GetNavigator( const UNID *unidnote, LNNavigator *Navigator );
	LNSTATUS GetNavigator( NOTEHANDLE handle, LNNavigator *Navigator )
		{ return GetNote(handle, (LNNote *) Navigator); }
	
	LNSTATUS GetNavigators( LNNavigatorArray *navigators );


	// Outlines
	LNBOOL OutlineExists( const LNString &outlinename ) const;

	LNSTATUS CreateOutline( const LNString &outlinename, LNOutline *newoutline = 0 );
	LNSTATUS CreateOutline( LNOutline &outline, LNOutline *newoutline);

	LNSTATUS DeleteOutline( const LNString &outlinename );
	LNSTATUS DeleteOutline( LNOutline *outline );

	LNSTATUS GetOutline( const LNString &outlinename, LNOutline *outline );
	LNSTATUS GetOutline( const char *outlinename, LNOutline *outline )
		{ return GetOutline(LNString(outlinename), outline); }
	LNSTATUS GetOutline( const NOTEID idnote, LNOutline *outline );
	LNSTATUS GetOutline( const UNID *unidnote, LNOutline *outline );
	LNSTATUS GetOutline( NOTEHANDLE handle, LNOutline *outline )
		{ return GetNote(handle, (LNNote *) outline); }
	
	LNSTATUS GetOutlines( LNOutlineArray *outlines );

	// Pages
	LNBOOL PageExists( const LNString &pagename) const;

	LNSTATUS CreatePage( const LNString &pagename, LNPage *newpage = 0);
	LNSTATUS CreatePage( LNPage &page, LNPage *newpage = 0);

	LNSTATUS DeletePage( const LNString &pagename );
	LNSTATUS DeletePage( LNPage *Page );

	LNSTATUS GetPage( const LNString &pagename, LNPage *Page );
	LNSTATUS GetPage( const char *pagename, LNPage *Page )
		{ return GetPage(LNString(pagename), Page); }
	LNSTATUS GetPage( const NOTEID idnote, LNPage *Page );
	LNSTATUS GetPage( const UNID *unidnote, LNPage *Page );
	LNSTATUS GetPage( NOTEHANDLE handle, LNPage *Page )
		{ return GetNote(handle, (LNNote *) Page); }
	
	LNSTATUS GetPages( LNPageArray *pages );

	//profiles
	LNSTATUS DeleteProfileDocument(const LNString &name, const LNString &owner="");
	LNSTATUS DeleteCalendarProfileDocument(const LNString &owner );
	LNSTATUS GetProfileDocuments(const LNString &name, LNProfileDocumentArray *docs);
	LNSTATUS OpenCalendarProfileDocument(const LNString &owner, LNCalendarProfileDocument *profile);
	LNSTATUS OpenProfileDocument (const LNString &name, const LNString &owner, LNProfileDocument *profile);


	LNBOOL ScriptLibraryExists( const LNString &ScriptLibraryname, 
		const LNSCRIPTLIBRARYTYPE scriptlibrarytype = LNSCRIPTLIBRARYTYPE_UNKNOWN ) const;

	LNSTATUS CreateScriptLibrary( const LNString &ScriptLibraryname, 
		const LNSCRIPTLIBRARYTYPE scriptlibrarytype, 
		LNScriptLibrary *newScriptLibrary = 0);
	LNSTATUS CreateScriptLibrary( LNScriptLibrary &ScriptLibrary, LNScriptLibrary *newScriptLibrary = 0);

	LNSTATUS DeleteScriptLibrary( const LNString &ScriptLibraryname, 
		const LNSCRIPTLIBRARYTYPE scriptlibrarytype );
	LNSTATUS DeleteScriptLibrary( LNScriptLibrary *ScriptLibrary );

	LNSTATUS GetScriptLibrary( const LNString &ScriptLibraryname, 
		const LNSCRIPTLIBRARYTYPE scriptlibrarytype,
		LNScriptLibrary *ScriptLibrary );
	LNSTATUS GetScriptLibrary( const char *ScriptLibraryname, 
		const LNSCRIPTLIBRARYTYPE ScriptLibraryType,
		LNScriptLibrary *ScriptLibrary )
		{ return GetScriptLibrary(LNString(ScriptLibraryname), 
											ScriptLibraryType, 
											ScriptLibrary); }
	LNSTATUS GetScriptLibrary( const NOTEID idnote, LNScriptLibrary *ScriptLibrary );
	LNSTATUS GetScriptLibrary( const UNID *unidnote, LNScriptLibrary *ScriptLibrary );
	LNSTATUS GetScriptLibrary( NOTEHANDLE handle, LNScriptLibrary *ScriptLibrary )
		{ return GetNote(handle, (LNNote *) ScriptLibrary); }
	
	LNSTATUS GetScriptLibraries( LNScriptLibraryArray *ScriptLibraries, 
		const LNSCRIPTLIBRARYTYPE scriptlibrarytype = LNSCRIPTLIBRARYTYPE_UNKNOWN);

#if defined XML_TOOLKIT	|| defined IRIS_BUILD
	LNBOOL SharedActionsExist() const;
#endif
	LNSTATUS CreateSharedActions( const LNActions &actions, LNNote *newSharedActionsNote = 0);
	LNSTATUS CreateSharedActions( LNNote &sharedActionsNote, LNNote *newsharedActionsNote = 0);
	LNSTATUS GetSharedActions(LNNote *sharedActionsNote);

	LNBOOL SharedFieldExists( const LNString &sharedfieldname ) const;

	LNSTATUS CreateSharedField( const LNFormField &field, LNSharedField *sharedfield = 0);
	LNSTATUS CreateSharedField( const LNString &name, LNRTTYPE fieldtype, LNSharedField *sharedfield = 0);
	LNSTATUS CreateSharedField( LNSharedField &sharedfield, LNSharedField *newsharedfield = 0);

	LNSTATUS GetSharedField( const LNString &sharedfieldname, LNSharedField *sharedfield); 
	LNSTATUS GetSharedFields( LNSharedFieldArray *array );

	LNSTATUS DeleteSharedField( const LNString &sharedfieldname);
	LNSTATUS DeleteSharedField( LNSharedField *sharedfield);

	LNBOOL SubformExists( const LNString &subformname ) const;

	LNSTATUS CreateSubform( const LNString &subformname, LNSubform *subform = 0);
	LNSTATUS CreateSubform( LNSubform &subform, LNSubform *newSubform = 0);

	LNSTATUS GetSubform( const LNString &subformname, LNSubform *subform);
	LNSTATUS GetSubforms( LNSubformArray *array );

	LNSTATUS DeleteSubform( const LNString &subformname);
	LNSTATUS DeleteSubform( LNSubform *subform);
	
	LNSTATUS CreateNote( LNNOTETYPE notetype, LNNote *newnote );
	LNSTATUS CreateNote( LNNote &note, LNNote *newnote = 0 );
	
	LNSTATUS CreateEncryptedNote	// here for backwards compatiblity
		( LNNote &note, LNNote *newnote, LNENCRYPTOPTION option )
		{ return CreateEncryptedNote(note, option, newnote); }	
	LNSTATUS CreateEncryptedNote( LNNote &note, LNNote *newnote = 0 )
		{ return CreateEncryptedNote(note, LNENCRYPTOPTION_PUBLIC, newnote); }	
	LNSTATUS CreateEncryptedNote
		( LNNote &note, LNENCRYPTOPTION option, LNNote *newnote = 0 );
	LNSTATUS CreateEncryptedNote
		( LNNote &note, const LNString &keyname, LNNote *newnote = 0);
	LNSTATUS CreateEncryptedNote
		( LNNote &note, const LNText &keynames, LNNote *newnote = 0);

	LNSTATUS DeleteNote( LNNote *note );
        LNSTATUS DeleteNote( LNNote *note, LNNOTEDELETEFLAGS option );
	LNSTATUS DeleteNote( NOTEID id );
        LNSTATUS DeleteNote( NOTEID id, LNNOTEDELETEFLAGS option  );

	LNSTATUS DeleteNotes( const LNNoteArray &notes );

	LNSTATUS GetNote( const NOTEID idnote, LNNote *note );
	LNSTATUS GetNote( const UNID *unidnote, LNNote *note );
	LNSTATUS GetNote( NOTEHANDLE handle, LNNote *note );

	LNSTATUS GetNotes( LNNoteArray *notes );
	
	LNSTATUS CreateFolder( const LNString &name, LNViewFolder *newfolder = 0 );
	LNSTATUS CreateFolder
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  LNViewFolder *newfolder = 0 );
	LNSTATUS CreateFolder
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  const LNViewFolder &templt, LNViewFolder *newfolder = 0 );

	LNSTATUS CreateView( const LNString &name, LNViewFolder *newview = 0 );
	LNSTATUS CreateView
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  LNViewFolder *newview = 0 );
	LNSTATUS CreateView
		( const LNString &name, LNVFSHARINGOPTION sharing,
		  const LNViewFolder &templt, LNViewFolder *newview = 0 );

	LNSTATUS CreateViewFolder
		( const LNString &name, LNViewFolder &oldviewfolder,
		  LNViewFolder *newviewfolder = 0 );

	LNSTATUS DeleteViewFolder( const LNString &viewname );
	LNSTATUS DeleteViewFolder( LNViewFolder *view );
	
	LNSTATUS GetDefaultViewFolder( LNViewFolder *view ) const;

	LNSTATUS GetViewFolder( const LNString &viewname, LNViewFolder *view );
	LNSTATUS GetViewFolder( const char *viewname, LNViewFolder *view )
		{ return GetViewFolder(LNString(viewname), view); }
	LNSTATUS GetViewFolder( const NOTEID idnote, LNViewFolder *view );
	LNSTATUS GetViewFolder( const UNID *unidnote, LNViewFolder *view );
	LNSTATUS GetViewFolder( NOTEHANDLE handle, LNViewFolder *view )
		{ return GetNote(handle, (LNNote *) view); }
	LNSTATUS GetFolders( LNViewFolderArray *folders, LNBOOL getPrivate = TRUE );
	LNSTATUS GetViews( LNViewFolderArray *views, LNBOOL getPrivate = TRUE );
	LNSTATUS GetViewFolders( LNViewFolderArray *viewfolders, LNBOOL getPrivate = TRUE );
	
	LNSTATUS MoveFolder( const LNString &source, const LNString &dest ) const;
	LNSTATUS MoveFolder
		( const LNViewFolder &source, const LNViewFolder &dest ) const;
	
	LNBOOL ViewFolderExists( const LNString &viewname ) const;
	
	LNSTATUS CreateFTIndex( LNFTINDEXFLAGS options = LNFTINDEXFLAGS_DEFAULT,
		const LNString &stopfile = "", LNFTIndexStatistics *stats = 0 );
		
	LNSTATUS DeleteFTIndex();
	
	LNSTATUS GetFTIndexFlags( LNFTINDEXFLAGS *options );
	
	LNSTATUS GetLastFTIndexed( LNDatetime *lastindex );
	
	LNBOOL IsFTIndexed();
	
	LNSTATUS FTSearch( const LNString &query, LNDocumentArray *results ) const;

	LNSTATUS FTSearch
		( const LNString &query, LNDocumentArray *results,
		  const LNFTSearchOptions &options ) const;

	LNSTATUS FTSearch
		( const LNString &query, LNDocumentArray *results,
		  const LNFTSearchOptions &options, const LNNoteArray &input ) const;
	
	LNSTATUS GetModifiedNotes
		( const LNString &start, LNNoteArray *notes, LNDatetime *end = 0 ) const
		{
			return GetModifiedNotes(LNDatetime(start), notes,
									LNNOTETYPE_DOCUMENT, end);
		}

	LNSTATUS GetModifiedNotes
		( const LNDatetime &start, LNNoteArray *notes, LNDatetime *end = 0 ) const
		{ return GetModifiedNotes(start, notes, LNNOTETYPE_DOCUMENT, end); }

	LNSTATUS GetModifiedNotes
		( const LNString &start, LNNoteArray *notes, LNNOTETYPE type,
		  LNDatetime *end = 0 ) const
		{ return GetModifiedNotes(LNDatetime(start), notes, type, end); }

	LNSTATUS GetModifiedNotes
		( const LNDatetime &start, LNNoteArray *notes, LNNOTETYPE type,
		  LNDatetime *end = 0 ) const;

	LNSTATUS Search( const LNFormula &formula, LNNoteArray *results,
		LNSearchOptions *options=0 );
		
	LNSTATUS UpdateFTIndex( LNFTIndexStatistics *stats = 0 );
	
	LNSTATUS GetUnreadList( LNNoteArray *unread, LNBOOL create = FALSE ) const;
	LNSTATUS GetUnreadList
		( LNNoteArray *unread, const LNString &username,
		  LNBOOL create = FALSE ) const;

	LNSTATUS SetUnreadList
		( LNNoteArray *unread, LNNoteArray *oldunread = 0,
		  LNBOOL flush = FALSE ) const;
	LNSTATUS SetUnreadList
		( LNNoteArray *unread, LNNoteArray *oldunread, const LNString &username,
		  LNBOOL flush = FALSE ) const;
	
	LNSTATUS UpdateUnreadList( LNNoteArray *unread ) const;

	LNSTATUS Close();
	
	LNSTATUS CreateAboutDatabaseDocument( LNDocument *newdoc );
	LNSTATUS CreateAboutDatabaseDocument( LNDocument &policydoc,
		LNDocument *newdoc = 0 );
	
	LNSTATUS CreateIcon( LNNote *newicon );
	LNSTATUS CreateIcon( LNNote &icon, LNNote *newicon = 0 );
	
	LNSTATUS CreateUsingDatabaseDocument( LNDocument *newdoc );
	LNSTATUS CreateUsingDatabaseDocument( LNDocument &helpdoc,
		LNDocument *newdoc = 0 );
	
	LNSTATUS GetAboutDatabaseDocument( LNDocument *policy );

	LNSTATUS GetACL( LNACL *acl );
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDATABASE;}
	
	LNDatetime GetCreated();

	LNText GetDatabaseCatalogCategories();
	
	DBHANDLE GetDatabaseHandle( LNBOOL keep_object = FALSE );
	
	TIMEDATE * GetDatabaseID();
	
	LNDBOPENFLAGS GetDatabaseOpenFlags() const;
	
	LNDatetime GetDataLastModified();
	
	LNDatetime GetDesignLastModified();
	
	LNBOOL GetDisableBackgroundAgents();
	
	LNBOOL GetDisableReplication();
	
	LNBOOL GetNeverReplicate();

	LNString GetFilename() const;
	
	LNString GetFilepath() const;
	
	LNBOOL GetHideDesign();
	
	LNSTATUS GetIcon( LNNote *icon );
	
	LNString GetInheritsFromTemplateName();
	
	LNDatetime GetLastModified();
	
	LNBOOL GetListInDatabaseCatalog();
	
	LNString GetOwnerName() const;

	LNNUMBER GetPercentageUsed();
	
	LNString GetPort() const;
	
	LNINT GetRemoveOldDocumentsDays();
	
	LNBOOL GetRemoveOldDocuments();
	
	TIMEDATE * GetReplicaID();
	
	LNBOOL GetReplicateReceiveSummaries();
	
	LNBOOL GetReplicateSendDeletions();
	
	LNBOOL GetReplicateSendTitleAndCatalogInfo();

	LNDatetime GetReplicationCutoffDatetime ();

	LNREPLICATIONPRIORITY GetReplicationPriority();
	
	LNString GetServer() const;

	LNBOOL GetShowInOpenDatabaseDialog();
	
	LNINT GetSize();
	
	LNString GetTemplateName();
	
	LNString GetTitle();
	
	LNDBTYPE GetType();
	
	LNSTATUS GetUsingDatabaseDocument( LNDocument *helpdoc );
	
	LNBOOL IsLocal() const { return !IsRemote(); }

	LNBOOL IsOpen() const;
	
	LNBOOL IsRemote() const;

	LNSTATUS Open();
	
	LNSTATUS Open( LNDBOPENFLAGS flags, const LNString &username = "");

	LNSTATUS SetDatabaseCatalogCategories( const LNText &txtcategories );
	
	LNSTATUS SetDisableBackgroundAgents( LNBOOL flag );
	
	LNSTATUS SetDisableReplication( LNBOOL flag );
	
	LNSTATUS SetNeverReplicate( LNBOOL flag );

	LNSTATUS SetHideDesign( LNBOOL flag );
	
	LNSTATUS SetInheritsFromTemplateName( const LNString &name );
	
	LNSTATUS SetListInDatabaseCatalog( LNBOOL flag );
		
	LNSTATUS SetOwnerName(const LNString &name);

	LNSTATUS SetRemoveOldDocumentsDays( LNINT olddocdays );
	
	LNSTATUS SetRemoveOldDocuments( LNBOOL flag );

	LNSTATUS SetReplicaID( const TIMEDATE & newID );
	
	LNSTATUS SetReplicateReceiveSummaries( LNBOOL flag );
	
	LNSTATUS SetReplicateSendDeletions( LNBOOL flag );
	
	LNSTATUS SetReplicateSendTitleAndCatalogInfo( LNBOOL flag );

	LNSTATUS SetReplicationCutoffDatetime ( const LNDatetime & newCutoff );

	LNSTATUS SetReplicationPriority( LNREPLICATIONPRIORITY reppriority );
	
	LNSTATUS SetShowInOpenDatabaseDialog( LNBOOL flag );
	
	LNSTATUS SetTemplateName( const LNString &name );

	LNSTATUS SetTitle( const LNString &title );
	
private:

	LNDatabase & operator=( LNDatabaseBody *datab );

	LNSTATUS CreateDatabaseBody( LNNotesSession *session,
		const LNString &filename, const LNString &server );
	
	LNSTATUS DeleteFormXYZ( const LNString &formname );
	LNSTATUS DeleteFormXYZ( LNForm *form );

	LNDatabaseBody * GetDatabaseBody() const {return (LNDatabaseBody *)Body;}
	
	LNSTATUS GetFormXYZ( const LNString &formname, LNForm *form );
	LNSTATUS GetFormXYZ( const NOTEID idnote, LNForm *form );
	LNSTATUS GetFormXYZ( const UNID *unidnote, LNForm *form );
};	


#ifndef LNNOTE_HPP
#include "lnnote.hpp"
#endif

#ifndef LNPROFILE_HPP
#include "lnprofil.hpp"
#endif

	
#endif	//LNDB_HPP

