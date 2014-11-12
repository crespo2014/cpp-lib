//===========================================================================
//
// Module:		LNVIEW.HPP
//
// Description:
//
//		Class definitions and data for the view and folder classes.
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNVIEW_HPP
#define LNVIEW_HPP

//Default Cache Size for ViewFolder
#define LNDEFAULTVFCACHESIZE 100 //Default cache size of 100

// LNNAVIGATION: navigation targets for the LNVFNavigator::Goto function.

enum LNNAVIGATION					// go to:
{
	LNNAVIGATION_CHILD = 0,			// child of current entry
	LNNAVIGATION_FIRST,				// first entry
	LNNAVIGATION_FIRST_SIBLING,		// first sibling of current entry
	LNNAVIGATION_LAST,				// last entry
	LNNAVIGATION_LAST_SIBLING,		// last sibling of current entry
	LNNAVIGATION_MAIN,				// main topic for current entry
	LNNAVIGATION_NEXT,				// next entry
	LNNAVIGATION_NEXT_CATEGORY,		// next category entry
	LNNAVIGATION_NEXT_MAIN,			// next main topic
	LNNAVIGATION_NEXT_NON_CATEGORY,	// next non-category entry
	LNNAVIGATION_NEXT_PARENT,		// next sibling of current entry's parent
	LNNAVIGATION_NEXT_SIBLING,		// next sibling of current entry
	LNNAVIGATION_NEXT_UNREAD,		// next unread entry
	LNNAVIGATION_NEXT_UNREAD_MAIN,	// next unread entry or main topic
	LNNAVIGATION_PARENT,			// parent of current entry
	LNNAVIGATION_PREV,				// previous entry
	LNNAVIGATION_PREV_CATEGORY,		// previous category entry
	LNNAVIGATION_PREV_MAIN,			// previous main topic
	LNNAVIGATION_PREV_NON_CATEGORY,	// previous non-category entry
	LNNAVIGATION_PREV_PARENT,		// previous sibling of current entry's parent
	LNNAVIGATION_PREV_SIBLING,		// previous sibling of current entry
	LNNAVIGATION_PREV_UNREAD,		// previous unread entry
	LNNAVIGATION_PREV_UNREAD_MAIN,	// previous unread entry or main topic
	LNNAVIGATION_COUNT				// number of enumeration values
};

// LNVFCALENDARFORMATS
typedef BYTE LNVFCALENDARFORMATS;

#define LNVFCALENDARFORMATS_TWO_DAY		VIEW_CAL_FORMAT_TWO_DAY		//0x01
#define LNVFCALENDARFORMATS_ONE_WEEK	VIEW_CAL_FORMAT_ONE_WEEK	//0x02
#define LNVFCALENDARFORMATS_TWO_WEEKS	VIEW_CAL_FORMAT_TWO_WEEKS	//0x04	
#define LNVFCALENDARFORMATS_ONE_MONTH	VIEW_CAL_FORMAT_ONE_MONTH	//0x08
// This one is not exposed	
//#define LNVFCALENDARFORMATS_ONE_YEAR	VIEW_CAL_FORMAT_ONE_YEAR	//0x10
#define LNVFCALENDARFORMATS_ONE_DAY		VIEW_CAL_FORMAT_ONE_DAY		//0x20  	
#define LNVFCALENDARFORMATS_FORMAT_ALL	VIEW_CAL_FORMAT_ALL			//0xff

enum LNVFCALENDARINITIALFORMAT
{
	LNVFCALENDARINITIALFORMAT_LAST_VIEWED = 0, 
	LNVFCALENDARINITIALFORMAT_TWO_DAY = LNVFCALENDARFORMATS_TWO_DAY,
	LNVFCALENDARINITIALFORMAT_ONE_WEEK = LNVFCALENDARFORMATS_ONE_WEEK,
	LNVFCALENDARINITIALFORMAT_TWO_WEEKS = LNVFCALENDARFORMATS_TWO_WEEKS,
	LNVFCALENDARINITIALFORMAT_ONE_MONTH = LNVFCALENDARFORMATS_ONE_MONTH,
	// This one is not exposed	
//	LNVFCALENDARINITIALFORMAT_ONE_YEAR = LNVFCALENDARFORMATS_ONE_YEAR,
	LNVFCALENDARINITIALFORMAT_ONE_DAY = LNVFCALENDARFORMATS_ONE_DAY 
};

// LNVFCOMPARISON: comparison for LNViewFolder and LNVFNavigator Find function

enum LNVFCOMPARISON
{
	LNVFCOMPARISON_EQ		= FIND_FIRST_EQUAL,
							// find first entry that matches key
	LNVFCOMPARISON_LAST_EQ	= FIND_LAST_EQUAL,
							// find last entry that matches key
	LNVFCOMPARISON_LT		= FIND_LESS_THAN,
							// find last entry that is less than key
	LNVFCOMPARISON_GT		= FIND_GREATER_THAN
							// find first entry that is greater than key
};

// LNVFENTRYTYPE: view/folder entry type

enum LNVFENTRYTYPE
{
	LNVFENTRYTYPE_CATEGORY,		// category
	LNVFENTRYTYPE_MAIN,			// main topic
	LNVFENTRYTYPE_RESPONSE,		// response
	LNVFENTRYTYPE_TOTAL			// total or statistical entry
};

// LNVFHEADINGDISPLAY: how to display column headings

enum LNVFHEADINGDISPLAY
{
	LNVFHEADINGDISPLAY_NONE,	// do not display column headings
	LNVFHEADINGDISPLAY_SIMPLE,	// display simple column headings (default)
	LNVFHEADINGDISPLAY_BEVELED	// display beveled column headings
};

// LNVFHEADINGSORTOPTION: how to sort column when user clicks on column heading

enum LNVFHEADINGSORTOPTION
{
	LNVFHEADINGSORTOPTION_NONE					= 0,
								// do not re-sort column (default)
	LNVFHEADINGSORTOPTION_ASCENDING				= VCF1_M_ResortAscending,
								// re-sort column in ascending order
	LNVFHEADINGSORTOPTION_DESCENDING			= VCF1_M_ResortDescending,
								// re-sort column in desending order
	LNVFHEADINGSORTOPTION_BOTH					= (VCF1_M_ResortAscending |
												   VCF1_M_ResortDescending),
								// cycle between ascend/descend order
	LNVFHEADINGSORTOPTION_CHANGE_VIEW_FOLDER	= VCF1_M_ResortToView
								// switch to another view/folder
};


// LNVFJUSTIFICATION: how to justify column entries

enum LNVFJUSTIFICATION
{
	LNVFJUSTIFICATION_LEFT		= VIEW_COL_ALIGN_LEFT,		// left justify
	LNVFJUSTIFICATION_RIGHT		= VIEW_COL_ALIGN_RIGHT,		// right justify
	LNVFJUSTIFICATION_CENTER	= VIEW_COL_ALIGN_CENTER		// center
};

// LNVFOPENFLAGS: flags used to open a view/folder (collection)

typedef DWORD LNVFOPENFLAGS;

#define LNVFOPENFLAGS_DEFAULT			0
							// default options
#define LNVFOPENFLAGS_REBUILD_INDEX		OPEN_REBUILD_INDEX
							// rebuild index before opening collection
#define LNVFOPENFLAGS_NO_UPDATE			OPEN_NOUPDATE
							// don't update collection before opening it
#define LNVFOPENFLAGS_NO_CREATE			OPEN_DO_NOT_CREATE
							// don't create collection if it doesn't exist
#define LNVFOPENFLAGS_USE_UNREAD_LIST	0x10000
							// associate collection with unread list
#define LNVFOPENFLAGS_DESIGN_ONLY		0x20000
							// open for access to design properties only;
							// don't open the collection

// LNVFOPENPOSITION: initial position of cursor when opening view/folder

enum LNVFOPENPOSITION
{
	LNVFOPENPOSITION_LAST_OPENED	= 0,
					// position cursor on last-opened document (default)
	LNVFOPENPOSITION_TOP			= VIEW_TABLE_GOTO_TOP_ON_OPEN,
					// position cursor on topmost (first) document	
	LNVFOPENPOSITION_BOTTOM			= VIEW_TABLE_GOTO_BOTTOM_ON_OPEN
					// position cursor on bottommost (last) document
};

// LNVFREFRESHOPTION: how to refresh the view/folder window when data changes

enum LNVFREFRESHOPTION
{
	LNVFREFRESHOPTION_DISPLAY_INDICATOR	= 0,
			// do not refresh window; display refresh indicator (default)
	LNVFREFRESHOPTION_REFRESH_TOP		= VIEW_TABLE_GOTO_TOP_ON_REFRESH,
			// refresh window and move cursor to first document
	LNVFREFRESHOPTION_REFRESH_BOTTOM	= VIEW_TABLE_GOTO_BOTTOM_ON_REFRESH,
			// refresh window and move cursor to last document
	LNVFREFRESHOPTION_REFRESH			= (VIEW_TABLE_GOTO_TOP_ON_REFRESH |
										   VIEW_TABLE_GOTO_BOTTOM_ON_REFRESH)
			// refresh window and leave cursor more or less where it is
};

// LNVFROWSPACING: spacing between view/folder rows

enum LNVFROWSPACING
{
	LNVFROWSPACING_SINGLE	= VIEW_TABLE_SINGLE_SPACE,		 // (default)
	LNVFROWSPACING_1_25		= VIEW_TABLE_ONE_POINT_25_SPACE,
	LNVFROWSPACING_1_5		= VIEW_TABLE_ONE_POINT_50_SPACE,
	LNVFROWSPACING_1_75		= VIEW_TABLE_ONE_POINT_75_SPACE,
	LNVFROWSPACING_DOUBLE	= VIEW_TABLE_DOUBLE_SPACE
};

// LNVFSEPARATOR: separator for multiple values in a column

enum LNVFSEPARATOR
{
	LNVFSEPARATOR_NONE		= 0x0000,
	LNVFSEPARATOR_SPACE		= 0x1000,
	LNVFSEPARATOR_COMMA		= 0x2000,	
	LNVFSEPARATOR_SEMICOLON	= 0x3000,
	LNVFSEPARATOR_NEWLINE	= 0x4000
};

// LNVFSORTOPTION: how to sort column entries

enum LNVFSORTOPTION
{
	LNVFSORTOPTION_NONE,		// do not sort column (default)
	LNVFSORTOPTION_ASCENDING,	// sort column in ascending order
	LNVFSORTOPTION_DESCENDING	// sort column in descending order
};

// LNVFSTYLE: view/folder style

enum LNVFSTYLE
{
	LNVFSTYLE_STANDARD,			// tabular view/folder (default)
	LNVFSTYLE_CALENDAR			// calendar view/folder
};

// LNVFTIMESLOTDISPLAY: how to display time slots for calendar view/folders

enum LNVFTIMESLOTDISPLAY
{
	LNVFTIMESLOTDISPLAY_NONE,			// no time slots (default)
	LNVFTIMESLOTDISPLAY_TIME_SLOTS,		// display time slots
	LNVFTIMESLOTDISPLAY_BITMAPS			// display time slots with bitmaps
};

// LNVFTIMESLOTDURATION: duration of time slots for calendar view/folders

enum LNVFTIMESLOTDURATION
{
	LNVFTIMESLOTDURATION_15_MINUTES	= 15,	// 15 minute slots
	LNVFTIMESLOTDURATION_30_MINUTES	= 30,	// 30 minute slots
	LNVFTIMESLOTDURATION_1_HOUR		= 60,	// 1 hour slots (default)
	LNVFTIMESLOTDURATION_2_HOURS	= 120	// 2 hour slots
};

// LNVFTOTALSOPTION: type of column totals/statistics to display, if any

enum LNVFTOTALSOPTION
{
	LNVFTOTALSOPTION_NONE	 = (NIF_STAT_NONE << VCF2_S_SubtotalCode),
							// no totals or statistics (default)
	LNVFTOTALSOPTION_TOTAL	 = (NIF_STAT_TOTAL << VCF2_S_SubtotalCode),
							// show total of all main docs at end of column
	LNVFTOTALSOPTION_AVERAGE = (NIF_STAT_AVG_PER_ENTRY << VCF2_S_SubtotalCode),
							// show average of all main docs at end of column
	LNVFTOTALSOPTION_AVERAGE_PER_CATEGORY
							 = (NIF_STAT_AVG_PER_CHILD << VCF2_S_SubtotalCode),
							// show average of main docs in each category
	LNVFTOTALSOPTION_PERCENT = (NIF_STAT_PCT_OVERALL << VCF2_S_SubtotalCode),
							// show % of total for each doc and category
	LNVFTOTALSOPTION_PERCENT_PER_CATEGORY
							 = (NIF_STAT_PCT_PARENT << VCF2_S_SubtotalCode)
							// show % of total for each category
};

// LNVFUNREADMARKDISPLAY: how to display unread marks

enum LNVFUNREADMARKDISPLAY
{
	LNVFUNREADMARKDISPLAY_NONE		= 0,	// no unread marks (default)
	LNVFUNREADMARKDISPLAY_DOCS		= VIEW_TABLE_FLAG_DISP_UNREADDOCS,
						// show unread marks for unread docs only
	LNVFUNREADMARKDISPLAY_STANDARD	= VIEW_TABLE_FLAG_DISP_ALLUNREAD
						// show unread marks for unread docs and their ancestors
};

//---------------------------------------------------------------------------
// 	Class name:	LNViewFolder
//
//	Description:
//
//	LNViewFolder represents a Notes database view or folder, and is the base
//	class for the LNView and LNFolder classes.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNViewFolder : public LNNote
{
friend class LNViewFolderArray;

public:
	LNViewFolder() {}
	LNViewFolder( const LNViewFolder &viewfolder ) : LNNote(viewfolder)
		{ ValidateNoteType(viewfolder); }
	LNViewFolder( const LNNote &other ) : LNNote(other)
		{ ValidateNoteType(other);}

	~LNViewFolder() {}
	
	LNViewFolder & operator=( const LNViewFolder &viewfolder )
		{ LNNote::operator=(viewfolder); return *this; }
	LNViewFolder & operator=( const LNNote &other )
		{ LNNote::operator=(other); return *this; }

	LNCLASSID GetClassID() const { return LNCLASSID_LNVIEWFOLDER; }

	LNSTATUS FolderAddDocument( const LNNote &doc );
	LNSTATUS FolderAddDocument( NOTEID noteid );
	
	LNSTATUS FolderAddDocuments( const LNNoteArray &docs );
	LNSTATUS FolderAddDocuments( const LNViewFolder &viewfolder );
	LNSTATUS FolderAddDocuments( const LNVFNavigator &nav );
	LNSTATUS FolderAddDocuments( HANDLE idtable );
	
	LNSTATUS FolderRemoveAllDocuments();
	
	LNSTATUS FolderRemoveDocument( const LNNote &doc );
	LNSTATUS FolderRemoveDocument( NOTEID noteid );
	
	LNSTATUS FolderRemoveDocuments( const LNNoteArray &docs );
	LNSTATUS FolderRemoveDocuments( const LNViewFolder &viewfolder );
	LNSTATUS FolderRemoveDocuments( const LNVFNavigator &nav );
	LNSTATUS FolderRemoveDocuments( HANDLE idtable );
	
	LNSTATUS FTSearch( const LNString &query, LNVFNavigator *results ) const;
	LNSTATUS FTSearch
		( const LNString &query, LNVFNavigator *results,
		  const LNFTSearchOptions &options ) const;
	LNSTATUS FTSearch
		( const LNString &query, LNVFNavigator *results,
		  const LNFTSearchOptions &options, const LNVFNavigator &input ) const;

	LNSTATUS GetChildren( LNVFNavigator *navigator ) const
		{ return GetDescendants(navigator, 1); }

	LNString GetColumnTitle( LNINT n ) const;
	
	LNSTATUS GetDescendants( LNVFNavigator *navigator ) const;
	LNSTATUS GetDescendants( LNVFNavigator *navigator, LNINT levels ) const;
	
	LNSTATUS GetEntries( LNVFNavigator *navigator ) const;
	
	LNDatabase GetEntryDatabase() const;
	
	LNSTATUS Open( LNVFOPENFLAGS flags = LNVFOPENFLAGS_DEFAULT );
	LNSTATUS Open( LNVFOPENFLAGS flags, const LNDatabase &db );
	LNSTATUS Open
		( LNVFOPENFLAGS flags, const LNString &pathname,
		  const LNString &server = "" );
	

	// LNVFNavigator functions:

	
	LNVFEntry operator[]( LNINT n ) const;

	LNSTATUS DeleteAllEntries() const;

	LNSTATUS DeleteEntries( LNVFEntry *entry, LNBOOL deletetree = FALSE ) const;
	LNSTATUS DeleteEntries
		( const LNVFPosition &position, LNBOOL deletetree = FALSE ) const;

	LNSTATUS Find
		( const LNString &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNString &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNDatetime &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNDatetime &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNNUMBER &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNNUMBER &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNVFFindKeys &keys, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	LNSTATUS Find
		( const LNVFFindKeys &keys, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 ) const;
	
	LNINT	GetCacheSize() const;

	LNSTATUS GetEntry( LNVFEntry *entry ) const;
	LNSTATUS GetEntry( LNVFEntry *entry, const LNVFPosition &position ) const;
	
	LNINT GetEntryCount() const;
	
	LNSTATUS GetPosition( LNVFPosition *position ) const;
	LNSTATUS SetPosition( const LNVFPosition &position ) const;
	
	LNSTATUS GotoChild( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_CHILD, entry); }
	LNSTATUS GotoFirst( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_FIRST, entry); }
	LNSTATUS GotoFirstSibling( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_FIRST_SIBLING, entry); }
	LNSTATUS GotoLast( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_LAST, entry); }
	LNSTATUS GotoLastSibling( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_LAST_SIBLING, entry); }
	LNSTATUS GotoMain( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_MAIN, entry); }
	LNSTATUS GotoNext( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT, entry); }
	LNSTATUS GotoNextCategory( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_CATEGORY, entry); }
	LNSTATUS GotoNextMain( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_MAIN, entry); }
	LNSTATUS GotoNextNonCategory( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_NON_CATEGORY, entry); }
	LNSTATUS GotoNextParent( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_PARENT, entry); }
	LNSTATUS GotoNextSibling( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_SIBLING, entry); }
	LNSTATUS GotoNextUnread( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_UNREAD, entry); }
	LNSTATUS GotoNextUnreadMain( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_NEXT_UNREAD_MAIN, entry); }
	LNSTATUS GotoParent( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PARENT, entry); }
	LNSTATUS GotoPrevious( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV, entry); }
	LNSTATUS GotoPreviousCategory( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_CATEGORY, entry); }
	LNSTATUS GotoPreviousMain( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_MAIN, entry); }
	LNSTATUS GotoPreviousNonCategory( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_NON_CATEGORY, entry); }
	LNSTATUS GotoPreviousParent( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_PARENT, entry); }
	LNSTATUS GotoPreviousSibling( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_SIBLING, entry); }
	LNSTATUS GotoPreviousUnread( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_UNREAD, entry); }
	LNSTATUS GotoPreviousUnreadMain( LNVFEntry *entry = 0 ) const
		{ return Goto(LNNAVIGATION_PREV_UNREAD_MAIN, entry); }
	
	LNBOOL IsCategorized() const;
	
	LNSTATUS Refresh() const;
	
	LNSTATUS ResetPosition() const;

	LNSTATUS SetCacheSize(LNINT cacheSize);


	// Common design functions (used by all design notes):

	
	LNString GetAlias() const;
	LNSTATUS SetAlias( const LNString &alias );

	LNBOOL GetAllowDesignRefreshToModify() const;
	void SetAllowDesignRefreshToModify( LNBOOL flag );

	LNString GetComment() const;
	LNSTATUS SetComment( const LNString &comment );

	LNBOOL GetHideFromBrowsers() const;
	void SetHideFromBrowsers( LNBOOL flag );

	LNBOOL GetHideFromClients() const;
	void SetHideFromClients( LNBOOL flag );

	LNBOOL GetHideFromR4Clients() const;
	void SetHideFromR4Clients( LNBOOL flag );

	LNString GetInheritsFromTemplateName() const;
	LNSTATUS SetInheritsFromTemplateName( const LNString &name );

	LNString GetName() const;
	LNSTATUS SetName( const LNString &name );

	LNBOOL GetPropagateAllowDesignChange () const;
    void SetPropagateAllowDesignChange (LNBOOL propagate);

	// View/folder design functions:

	LNSTATUS AppendColumn( LNVFColumn *newcol = 0 );
	LNSTATUS AppendColumn( const LNVFColumn &oldcol, LNVFColumn *newcol = 0 );

	LNSTATUS AppendColumns( LNINT count );

	LNSTATUS DeleteColumn( LNINT n );
	LNSTATUS DeleteColumn( LNVFColumn *column );

	LNSTATUS DeleteColumns( LNINT n, LNINT count  );

	LNSTATUS GetActions( LNActions *pactions ) const;
	LNSTATUS SetActions( const LNActions &actions );

	LNColor GetActiveLinkColor() const;
	LNSTATUS SetActiveLinkColor( const LNColor &color );

	LNBOOL GetAllowAllAuthors() const;
	void SetAllowAllAuthors( LNBOOL flag );

	LNBOOL GetAllowToOverrideTimes() const;
	void SetAllowToOverrideTimes(LNBOOL flag);

	LNBOOL GetAllowAllReaders() const;
	void SetAllowAllReaders( LNBOOL flag );

	LNBOOL GetAllowPublicAccessUsers() const;
	void SetAllowPublicAccessUsers( LNBOOL flag );

	LNColor GetAlternateRowColor() const;
	LNSTATUS SetAlternateRowColor( const LNColor &color );

	LNText GetAuthors() const;
	LNSTATUS SetAuthors( const LNText &names );

	LNColor GetBackgroundColor() const;
	LNSTATUS SetBackgroundColor( const LNColor &color );

	LNFontStyle GetBorderFontStyle() const;
	LNSTATUS SetBorderFontStyle( const LNFontStyle &style );

	LNColor GetBusyRowColor() const;
	LNSTATUS SetBusyRowColor( const LNColor &color );

	LNVFCALENDARFORMATS GetCalendarFormats() const;
	LNSTATUS SetCalendarFormats(LNVFCALENDARFORMATS flags = LNVFCALENDARFORMATS_FORMAT_ALL);

	LNFontStyle GetCalendarHeaderFontStyle() const;
	LNSTATUS SetCalendarHeaderFontStyle( const LNFontStyle &style );

	LNVFCALENDARINITIALFORMAT GetCalendarInitialFormat() const;
	LNSTATUS SetCalendarInitialFormat(LNVFCALENDARINITIALFORMAT format = LNVFCALENDARINITIALFORMAT_LAST_VIEWED);

	LNBOOL GetCollapseOnOpen() const;
	void SetCollapseOnOpen( LNBOOL flag );

	LNSTATUS GetColumn( LNINT n, LNVFColumn *column ) const;
	LNSTATUS GetColumn( const LNString &title, LNVFColumn *column ) const;

	LNINT GetColumnCount() const;

	LNFontStyle GetDateFontStyle() const;
	LNSTATUS SetDateFontStyle( const LNFontStyle &style );

	LNColor GetDateBackgroundColor() const;
	LNSTATUS SetDateBackgroundColor(const LNColor &color);

	LNColor GetDaySeparatorColor() const;
	LNSTATUS SetDaySeparatorColor( const LNColor &color );

	LNBOOL GetEnableTimeGrouping() const;
	void SetEnableTimeGrouping(LNBOOL flag);

	LNBOOL GetExtendLastColumn() const;
	void SetExtendLastColumn( LNBOOL flag );

    LNSTATUS GetEventFormula(LNFORMULAEVENT event, LNFormula *formula ) const;
    LNSTATUS SetEventFormula( const LNFormula &formula, LNFORMULAEVENT event );

	LNSTATUS GetFormFormula( LNFormula *formula ) const;
	LNSTATUS SetFormFormula( const LNFormula &formula );

	LNBOOL GetGenerateUniqueKeys() const;
	void SetGenerateUniqueKeys( LNBOOL flag );

    LNSTATUS GetGlobalLotusScript (LNLotusScript * pScript) const;
	LNSTATUS SetGlobalLotusScript(const LNLotusScript &script);

	LNVFHEADINGDISPLAY GetHeadingDisplay() const;
	LNSTATUS SetHeadingDisplay( LNVFHEADINGDISPLAY option );
/*
	LNSTATUS GetHelpRequestFormula( LNFormula *formula );
	LNSTATUS SetHelpRequestFormula( const LNFormula &formula );
*/

	LNBOOL GetIsDefaultDesign() const;
	void SetIsDefaultDesign( LNBOOL flag );

	LNBOOL GetIsDefaultViewFolder() const;
	void SetIsDefaultViewFolder( LNBOOL flag );

	LNINT GetLinesPerHeading() const;
	LNSTATUS SetLinesPerHeading( LNINT count );

	LNINT GetLinesPerRow() const;
	LNSTATUS SetLinesPerRow( LNINT count );

    LNSTATUS GetLotusScript (LNLotusScript * pScript) const;
	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNColor GetNonMonthBackgroundColor() const;
	LNSTATUS SetNonMonthBackgroundColor(const LNColor &color);

	LNColor GetNonMonthTextColor() const;
	LNSTATUS SetNonMonthTextColor(const LNColor &color);

	LNVFOPENPOSITION GetOpenPosition() const;
	LNSTATUS SetOpenPosition( LNVFOPENPOSITION position );

	LNText GetReaders() const;
	LNSTATUS SetReaders( const LNText &names );

	LNVFREFRESHOPTION GetRefreshOption() const;
	LNSTATUS SetRefreshOption( LNVFREFRESHOPTION option );

	LNVFROWSPACING GetRowSpacing();
	LNSTATUS SetRowSpacing( LNVFROWSPACING spacing );

	LNSTATUS GetSelectionFormula( LNFormula *formula ) const;
	LNSTATUS SetSelectionFormula( const LNFormula &formula );

	LNVFSHARINGOPTION GetSharingOption() const;

	LNBOOL GetShowCalendarConflicts() const;
	void SetShowCalendarConflicts( LNBOOL flag );

	LNBOOL GetShowInViewMenu() const;
	void SetShowInViewMenu( LNBOOL flag );

	LNBOOL GetShowReplicationConflicts() const;
	void SetShowReplicationConflicts( LNBOOL flag );

	LNBOOL GetShowResponseHierarchy() const;
	void SetShowResponseHierarchy( LNBOOL flag );

	LNBOOL GetShowSelectionMargin() const;
	void SetShowSelectionMargin( LNBOOL flag );

	LNBOOL GetShrinkRows() const;
	void SetShrinkRows( LNBOOL flag );

	LNVFSTYLE GetStyle() const;
	LNSTATUS SetStyle( LNVFSTYLE style );

	LNVFTIMESLOTDISPLAY GetTimeSlotDisplay() const;
	LNSTATUS SetTimeSlotDisplay( LNVFTIMESLOTDISPLAY option );

	LNVFTIMESLOTDURATION GetTimeSlotDuration() const;
	LNSTATUS SetTimeSlotDuration( LNVFTIMESLOTDURATION duration );

	LNINT GetTimeSlotEndHour() const;
	LNSTATUS SetTimeSlotEndHour( LNINT hour );

	LNFontStyle GetTimeSlotFontStyle() const;
	LNSTATUS SetTimeSlotFontStyle( const LNFontStyle &style );

	LNINT GetTimeSlotStartHour() const;
	LNSTATUS SetTimeSlotStartHour( LNINT hour );

	LNColor GetTodayColor() const;
	LNSTATUS SetTodayColor( const LNColor &color );

	LNFontStyle GetTotalsFontStyle() const;
	LNSTATUS SetTotalsFontStyle( const LNFontStyle &style );

	LNBOOL GetTreatContentsAsHTML() const;
	void SetTreatContentsAsHTML( LNBOOL flag );

	LNVFTYPE GetType();

	LNFontStyle GetUnreadFontStyle() const;
	LNSTATUS SetUnreadFontStyle( const LNFontStyle &style );

	LNVFUNREADMARKDISPLAY GetUnreadMarkDisplay() const;
	LNSTATUS SetUnreadMarkDisplay( LNVFUNREADMARKDISPLAY option );

	LNColor GetUnvisitedLinkColor() const;
	LNSTATUS SetUnvisitedLinkColor( const LNColor &color );

	LNBOOL GetUseAlternateRowColor() const;
	void SetUseAlternateRowColor( LNBOOL flag );

	LNBOOL GetUseAppletInBrowser() const;
	void SetUseAppletInBrowser( LNBOOL flag );

	LNINT GetVersion() const;

	LNColor GetVisitedLinkColor() const;
	LNSTATUS SetVisitedLinkColor( const LNColor &color );

	LNSTATUS InsertColumn( LNINT n, LNVFColumn *newcol = 0 );
	LNSTATUS InsertColumn
		( LNINT n, const LNVFColumn &oldcol, LNVFColumn *newcol = 0 );

	LNSTATUS InsertColumns( LNINT n, LNINT count );

	LNBOOL IsCalendar() const;

	LNBOOL IsFolder();
	
	LNBOOL IsPrivate() const;

	LNBOOL IsView();	


private:
	LNViewFolder( LNDatabaseBody *db, NOTEID id );
	
	LNViewFolder & operator=( LNViewFolderBody *viewfolder );
	
	LNSTATUS CreateViewFolderBody();
	
	LNSTATUS GetIDTable( HANDLE *idtable ) const;
	
	LNViewFolderBody * GetViewFolderBody() const
		{ return (LNViewFolderBody *) Body; }
	
	LNSTATUS Goto( LNNAVIGATION where, LNVFEntry *entry ) const;
	
	virtual void ValidateNoteType( const LNNote &note ) const;
	virtual void ValidateNoteType( const LNNoteBody *note ) const;
	virtual void ValidateNoteType( LNNOTETYPE type ) const;
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFColumn
//
//	Description:
//	
//	LNVFColumn provides access to column-specific view and folder design
//	attributes. LNVFColumn is a "smart pointer" for LNVFColumnBody, which
//	contains the actual implementation.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFColumn : public LNSmartPtr
{

public:
	LNVFColumn() {}
	LNVFColumn( const LNVFColumn &column ) : LNSmartPtr(column) {}

	~LNVFColumn() {}

	LNVFColumn & operator=( const LNVFColumn &column )
		{ LNSmartPtr::operator=(column); return *this; }

	LNBOOL GetCategorizedIsFlatInR5() const;
	void SetCategorizedIsFlatInR5(LNBOOL flag);

	LNCLASSID GetClassID() const { return LNCLASSID_LNVFCOLUMN; }

	LNINT GetColumnNumber() const;

	LNDatetimeFormat GetDatetimeFormat() const;
	LNSTATUS SetDatetimeFormat( const LNDatetimeFormat &format );

	LNBOOL GetDisplayValuesAsIcons() const;
	void SetDisplayValuesAsIcons( LNBOOL flag );

	LNINT GetExactWidth() const;
	LNSTATUS SetExactWidth( LNINT width );

	LNString GetFieldName() const;
	LNSTATUS SetFieldName( const LNString &name );

	LNFontStyle GetFontStyle() const;
	LNSTATUS SetFontStyle( const LNFontStyle &style );

	LNSTATUS GetFormula( LNFormula *formula ) const;
	LNSTATUS SetFormula( const LNFormula &formula );

	LNVFHEADINGSORTOPTION GetHeadingSortOption() const;
	LNSTATUS SetHeadingSortOption( LNVFHEADINGSORTOPTION option );

	LNSTATUS GetHeadingSortViewFolder( LNViewFolder *viewfolder ) const;
	LNSTATUS SetHeadingSortViewFolder( const LNViewFolder &viewfolder );

	LNBOOL GetHideColumn() const;
	void SetHideColumn( LNBOOL flag );

	LNBOOL GetHideDetailRows() const;
	void SetHideDetailRows( LNBOOL flag );

	LNString GetInternalName() const;
	LNSTATUS SetInternalName( const LNString &name );

	LNBOOL GetIsCategorized() const;
	void SetIsCategorized( LNBOOL flag );

	LNBOOL GetIsResizable() const;
	void SetIsResizable( LNBOOL flag );

	LNVFJUSTIFICATION GetJustification() const;
	LNSTATUS SetJustification( LNVFJUSTIFICATION option );

	LNNumberFormat GetNumberFormat() const;
	LNSTATUS SetNumberFormat( const LNNumberFormat &format );

	LNINT GetSecondarySortColumn() const;
	LNSTATUS SetSecondarySortColumn( LNINT n );
	LNSTATUS SetSecondarySortColumn( const LNString &title );

	LNVFSORTOPTION GetSecondarySortOption() const;
	LNSTATUS SetSecondarySortOption( LNVFSORTOPTION option );

	LNBOOL GetSeparateMultipleValues() const;
	void SetSeparateMultipleValues( LNBOOL flag );

	LNVFSEPARATOR GetSeparator() const;
	LNSTATUS SetSeparator( LNVFSEPARATOR separator );

	LNBOOL GetShowResponsesOnly() const;
	void SetShowResponsesOnly( LNBOOL flag );

	LNBOOL GetShowTwistie() const;
	void SetShowTwistie( LNBOOL flag );

	LNBOOL GetShowValuesAsLinks() const;
	void SetShowValuesAsLinks( LNBOOL flag );

	LNVFSORTOPTION GetSortOption() const;
	LNSTATUS SetSortOption( LNVFSORTOPTION option );

	LNString GetTitle() const;
	LNSTATUS SetTitle( const LNString &title );

	LNFontStyle GetTitleFontStyle() const;
	LNSTATUS SetTitleFontStyle( const LNFontStyle &style );

	LNVFJUSTIFICATION GetTitleJustification() const;
	LNSTATUS SetTitleJustification( LNVFJUSTIFICATION option );

	LNVFTOTALSOPTION GetTotalsOption() const;
	LNSTATUS SetTotalsOption( LNVFTOTALSOPTION option );

	LNBOOL GetUseAccentSensitiveSort() const;
	void SetUseAccentSensitiveSort( LNBOOL flag );

	LNBOOL GetUseCaseSensitiveSort() const;
	void SetUseCaseSensitiveSort( LNBOOL flag );

	LNSTATUS GetViewFolder( LNViewFolder *viewfolder ) const;
	
	LNINT GetWidthInCharacters() const;
	LNSTATUS SetWidthInCharacters( LNINT width );

private:
	LNVFColumn & operator=( LNVFColumnBody *column )
		{ return (LNVFColumn &) LNSmartPtr::operator=((LNBody *) column); }

	LNVFColumnBody * GetVFColumnBody() const
		{ return (LNVFColumnBody *) Body; }
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFEntry
//
//	Description:
//	
//	LNVFEntry represents an entry (row) in a database view or folder, and
//	provides access to both the corresponding document and the data items
//	displayed in the view or folder columns.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFEntry : public LNSmartPtr
{

public:
	LNVFEntry() {}
	LNVFEntry( const LNVFEntry &entry ) : LNSmartPtr(entry) {}
	
	~LNVFEntry() {}
	
	LNVFEntry & operator=( const LNVFEntry &entry )
		{ return (LNVFEntry &) LNSmartPtr::operator=(entry); }
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNVFENTRY; }
	
	LNItem operator[]( LNINT n ) const { return GetColumnItem(n, FALSE); }
	LNItem operator[]( const LNString &colname ) const
		 { return GetColumnItem(colname, FALSE); }

	LNINT GetChildCount() const;

	LNItem GetColumnItem( LNINT n, LNBOOL get_hidden_item = FALSE ) const;
	LNItem GetColumnItem
		( const LNString &colname, LNBOOL get_hidden_item = FALSE ) const;

	LNINT GetDescendantCount() const;

	LNINT GetDocLevel() const;

	LNSTATUS GetDocument( LNDocument *document ) const;
	
	LNINT GetFTSearchScore() const;
	
	LNINT GetIndentLevels() const;
	
	NOTEID GetNoteID() const;
	
	LNSTATUS GetPosition( LNVFPosition *position ) const;
	
	LNINT GetSiblingCount() const;
	
	LNVFENTRYTYPE GetType() const;
	
	LNSTATUS GetViewFolder( LNViewFolder *viewfolder ) const;
	
	LNBOOL IsCategory() const;
	
	LNBOOL IsMainTopic() const;
	
	LNBOOL IsResponse() const;
	
	LNBOOL IsTotal() const;
	
	LNBOOL IsUnread() const;

private:
	LNVFEntry( LNVFEntryBody *entry ) : LNSmartPtr((LNBody *) entry) {}
	
	LNVFEntry & operator=( LNVFEntryBody *entry )
		{ return (LNVFEntry &) LNSmartPtr::operator=((LNBody *) entry); }
	
	LNVFEntryBody * GetVFEntryBody() const
		{ return (LNVFEntryBody *) Body; }
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFFindKey
//
//	Description:
//	
//	LNVFFindKey represents one of the search keys stored in an LNVFFindKeys
//	object.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFFindKey : public LNNotesClass
{

public:
	~LNVFFindKey();
	
	operator LNString() const;
	operator LNDatetime() const;
	operator LNNUMBER() const;
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNVFFINDKEY; }

private:
	LNVFFindKey( const LNVFFindKey &key );
	LNVFFindKey( const LNString &key, LNSTATUS *error );
	LNVFFindKey( const LNDatetime &key, LNSTATUS *error );
	LNVFFindKey( const LNNUMBER &key, LNSTATUS *error );
	
	LNSTATUS Assign( const void *value, WORD size, WORD type );
	
	const void * GetValue() const { return Value; }
	
	WORD GetValueSize() const { return ValueSize; }

	// the following 2 functions are disabled

	LNVFFindKey();
	LNVFFindKey & operator=( const LNVFFindKey &key );

	// data

	char *Value;
	WORD ValueSize;
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFFindKeys
//
//	Description:
//	
//	LNVFFindKeys represents search keys used by the LNViewFolder and
//	LNVFNavigator Find functions.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFFindKeys : public LNNotesClass
{

public:
	LNVFFindKeys() { ItemTable = 0; }
	LNVFFindKeys( const LNVFFindKeys &keys ) : LNNotesClass(keys)
		{ Copy(keys); }

	~LNVFFindKeys() { Free(); }
	
	LNVFFindKeys & operator=( const LNVFFindKeys &keys );
	
	LNVFFindKey & operator[]( LNINT n );
	
	LNSTATUS Append( const LNString &key );
	LNSTATUS Append( const LNDatetime &key );
	LNSTATUS Append( const LNNUMBER &key );
	
	void DeleteAllKeys() { Keys.DeleteAllObjects(); }
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNVFFINDKEYS; }
	
	LNINT GetCount() const { return Keys.GetCount(); }

private:
	LNSTATUS Append( LNVFFindKey *key );
	
	void Copy( const LNVFFindKeys &keys );
	
	void Free();
	
	const ITEM_TABLE * GetItemTable() const;

	char *ItemTable;
	LNObjectList Keys;
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFFindOptions
//
//	Description:
//	
//	LNVFFindOptions represents search options used by the LNViewFolder and
//	LNVFNavigator Find functions.
//---------------------------------------------------------------------------

// FIND_NONCATEGORY_ONLY is not exposed in the C API 4.6x headers

#ifndef FIND_NONCATEGORY_ONLY
#define FIND_NONCATEGORY_ONLY	0x0400
#endif

// default NIFFind... search flags (for internal use only)

const WORD LNVFFINDFLAGS = FIND_PARTIAL | FIND_CASE_INSENSITIVE |
						   FIND_ACCENT_INSENSITIVE | FIND_FIRST_EQUAL;

class LNIMPEXPCL LNVFFindOptions : public LNNotesClass
{

public:
	LNVFFindOptions() { Flags = LNVFFINDFLAGS; }
	LNVFFindOptions( const LNVFFindOptions &options )
		: LNNotesClass(options) { Flags = options.Flags; }

	~LNVFFindOptions() {}

	LNVFFindOptions & operator=( const LNVFFindOptions &options );

	LNCLASSID GetClassID() const { return LNCLASSID_LNVFFINDOPTIONS; }

	LNVFCOMPARISON GetComparison() const
		{ return (LNVFCOMPARISON) (Flags & FIND_COMPARE_MASK); }
	LNSTATUS SetComparison( LNVFCOMPARISON comparison );

	LNBOOL GetMatchAccent() const
		{ return !(Flags & FIND_ACCENT_INSENSITIVE); }
	void SetMatchAccent( LNBOOL flag )
		{ SetFlag(FIND_ACCENT_INSENSITIVE, !flag); }

	LNBOOL GetMatchAnyNonCategory() const
		{ return (Flags & FIND_RETURN_ANY_NON_CATEGORY_MATCH) != 0; }
	void SetMatchAnyNonCategory( LNBOOL flag )
		{ SetFlag(FIND_RETURN_ANY_NON_CATEGORY_MATCH, flag); }

	LNBOOL GetMatchCategories() const
		{ return !(Flags & FIND_NONCATEGORY_ONLY); }
	void SetMatchCategories( LNBOOL flag )
		{ SetFlag(FIND_NONCATEGORY_ONLY, !flag); }

	LNBOOL GetMatchCase() const { return !(Flags & FIND_CASE_INSENSITIVE); }
	void SetMatchCase( LNBOOL flag ) { SetFlag(FIND_CASE_INSENSITIVE, !flag); }

	LNBOOL GetMatchOverlappingRanges() const
		{ return (Flags & FIND_RANGE_OVERLAP) != 0; }
	void SetMatchOverlappingRanges( LNBOOL flag )
		{ SetFlag(FIND_RANGE_OVERLAP, flag); }

	LNBOOL GetMatchWholeWord() const { return !(Flags & FIND_PARTIAL); }
	void SetMatchWholeWord( LNBOOL flag ) { SetFlag(FIND_PARTIAL, !flag); }

	LNBOOL GetUpdateIfNotFound() const
		{ return (Flags & FIND_UPDATE_IF_NOT_FOUND) != 0; }
	void SetUpdateIfNotFound( LNBOOL flag )
		{ SetFlag(FIND_UPDATE_IF_NOT_FOUND, flag); }

private:
	WORD GetFlags() const { return Flags; }

	void SetFlag( WORD flag, LNBOOL setflag );

	WORD Flags;
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFPosition
//
//	Description:
//	
//	LNVFPosition identifies the position of an entry in a view or folder.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFPosition : public LNNotesClass
{

public:
	LNVFPosition();
	LNVFPosition( const LNVFPosition &position );

	~LNVFPosition();
	
	LNVFPosition & operator=( const LNVFPosition &position );
	
	LNBOOL operator==( const LNVFPosition &position ) const;
	LNBOOL operator<( const LNVFPosition &position ) const;
	LNBOOL operator>( const LNVFPosition &position ) const;
	LNBOOL operator!=( const LNVFPosition &position ) const
		{ return !operator==(position); }
	LNBOOL operator<=( const LNVFPosition &position ) const
		{ return !operator>(position); }
	LNBOOL operator>=( const LNVFPosition &position ) const
		{ return !operator<(position); }
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNVFPOSITION; }

	LNINT GetDocLevel() const;

	LNString GetDocNumber( const LNString &separator ) const;
	LNString GetDocNumber( char separator = '.' ) const
		{ return GetDocNumber(LNString(&separator, 1)); }
	
	void Reset();

private:
	LNVFPosition( const COLLECTIONPOSITION *position );

	LNVFPosition & operator=( const COLLECTIONPOSITION *position );

	LNBOOL operator==( const COLLECTIONPOSITION *position ) const;
	LNBOOL operator!=( const COLLECTIONPOSITION *position ) const
		{ return !operator==(position); }
	LNBOOL operator<( const COLLECTIONPOSITION *position ) const
		{ return Compare(position) == -1; }
	LNBOOL operator<=( const COLLECTIONPOSITION *position ) const
		{ return Compare(position) != 1; }
	LNBOOL operator>( const COLLECTIONPOSITION *position ) const
		{ return Compare(position) == 1; }
	LNBOOL operator>=( const COLLECTIONPOSITION *position ) const
		{ return Compare(position) != -1; }

	LNSINT Compare( const COLLECTIONPOSITION *position ) const;

	COLLECTIONPOSITION * GetCollectionPosition() const { return Position; }

	COLLECTIONPOSITION *Position;
};

//---------------------------------------------------------------------------
// 	Class name:	LNVFNavigator
//
//	Description:
//	
//	LNVFNavigator provides functions to navigate through a view or folder.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNVFNavigator : public LNSmartPtr
{

public:
	LNVFNavigator();
	LNVFNavigator( const LNVFNavigator &navigator );
	
	~LNVFNavigator() {}
	
	LNVFNavigator & operator=( const LNVFNavigator &navigator );
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNVFNAVIGATOR; }
	
	LNSTATUS GetPosition( LNVFPosition *position ) const;
	LNSTATUS SetPosition( const LNVFPosition &position );
	
	LNSTATUS ResetPosition();

	LNVFEntry operator[]( LNINT n );

	LNSTATUS DeleteAllEntries() const;

	LNSTATUS DeleteEntries( LNVFEntry *entry, LNBOOL deletetree = FALSE ) const;
	LNSTATUS DeleteEntries
		( const LNVFPosition &position, LNBOOL deletetree = FALSE ) const;
	
	LNSTATUS Find
		( const LNString &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNString &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0, LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNDatetime &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNDatetime &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0, LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNNUMBER &key, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNNUMBER &key, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0, LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNVFFindKeys &keys, LNVFEntry *entry = 0, LNINT *count = 0,
		  LNVFNavigator *results = 0 );
	LNSTATUS Find
		( const LNVFFindKeys &keys, const LNVFFindOptions &options,
		  LNVFEntry *entry = 0, LNINT *count = 0, LNVFNavigator *results = 0 );

	LNDatabase GetEntryDatabase() const;
	
	LNSTATUS GetEntry( LNVFEntry *entry );
	LNSTATUS GetEntry( LNVFEntry *entry, const LNVFPosition &position );
	
	LNINT GetEntryCount() const;
	
	LNSTATUS GetViewFolder( LNViewFolder *viewfolder ) const;
	
	LNSTATUS GotoChild( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_CHILD, entry); }
	LNSTATUS GotoFirst( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_FIRST, entry); }
	LNSTATUS GotoFirstSibling( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_FIRST_SIBLING, entry); }
	LNSTATUS GotoLast( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_LAST, entry); }
	LNSTATUS GotoLastSibling( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_LAST_SIBLING, entry); }
	LNSTATUS GotoMain( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_MAIN, entry); }
	LNSTATUS GotoNext( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT, entry); }
	LNSTATUS GotoNextCategory( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_CATEGORY, entry); }
	LNSTATUS GotoNextMain( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_MAIN, entry); }
	LNSTATUS GotoNextNonCategory( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_NON_CATEGORY, entry); }
	LNSTATUS GotoNextParent( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_PARENT, entry); }
	LNSTATUS GotoNextSibling( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_SIBLING, entry); }
	LNSTATUS GotoNextUnread( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_UNREAD, entry); }
	LNSTATUS GotoNextUnreadMain( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_NEXT_UNREAD_MAIN, entry); }
	LNSTATUS GotoParent( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PARENT, entry); }
	LNSTATUS GotoPrevious( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV, entry); }
	LNSTATUS GotoPreviousCategory( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_CATEGORY, entry); }
	LNSTATUS GotoPreviousMain( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_MAIN, entry); }
	LNSTATUS GotoPreviousNonCategory( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_NON_CATEGORY, entry); }
	LNSTATUS GotoPreviousParent( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_PARENT, entry); }
	LNSTATUS GotoPreviousSibling( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_SIBLING, entry); }
	LNSTATUS GotoPreviousUnread( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_UNREAD, entry); }
	LNSTATUS GotoPreviousUnreadMain( LNVFEntry *entry = 0 )
		{ return Goto(LNNAVIGATION_PREV_UNREAD_MAIN, entry); }
	
	LNBOOL IsCategorized() const;
	
	LNBOOL IsFTSearch() const;
	
	LNSTATUS Refresh();

private:
	LNVFNavigator & operator=( LNVFNavigatorBody *navigatorbody );

	LNSTATUS Close();

	LNSTATUS Find
		( const LNVFFindKeys *keys, const LNVFFindOptions *options,
		  LNVFEntry *entry, LNINT *count, LNVFNavigator *results );

	LNSTATUS GetIDTable( HANDLE *idtable ) const;

	LNVFNavigatorBody * GetVFNavigatorBody() const
		{ return (LNVFNavigatorBody *) Body; }

	LNSTATUS Goto( LNNAVIGATION where, LNVFEntry *entry );

	void SetNullBodyError( LNSTATUS error )
		{ NullBodyError = error; }

	LNINT CurrentIndex;
	LNVFPosition CurrentPosition;
	LNSTATUS NullBodyError;
};


#endif	//LNVIEW_HPP

