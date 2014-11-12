//===========================================================================
//
// Module:	LNENUMS.H
//
// Description:
//
//		C++ API enumerations and bit masks.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNENUMS_H
#define LNENUMS_H

// LNDBTYPE: database type.

enum LNDBTYPE
{
	LNDBTYPE_CLIPBOARD = DBCLASS_NOTECLIPBOARD,
	LNDBTYPE_DESKTOP = DBCLASS_DESKTOP,
	LNDBTYPE_ENCAPS_MAIL_FILE = DBCLASS_ENCAPSMAILFILE,
	LNDBTYPE_GIANT_NOTEFILE = DBCLASS_GIANTNOTEFILE,
	LNDBTYPE_HUGE_NOTEFILE = DBCLASS_HUGENOTEFILE,
	LNDBTYPE_LARGE_ENCAPS_MAIL_FILE = DBCLASS_LRGENCAPSMAILFILE,
	LNDBTYPE_NOTEFILE = DBCLASS_NOTEFILE,
	LNDBTYPE_OBJECT_STORE = DBCLASS_OBJSTORE,
	LNDBTYPE_ONE_DOC_FILE = DBCLASS_ONEDOCFILE,
	LNDBTYPE_TEMPLATEFILE = DBCLASS_TEMPLATEFILE,
	LNDBTYPE_TESTFILE = DBCLASS_NSFTESTFILE,
	LNDBTYPE_V2_NOTEFILE = DBCLASS_V2NOTEFILE,
	LNDBTYPE_V3_NOTEFILE = DBCLASS_V3NOTEFILE,
	LNDBTYPE_V3_ONE_DOC_FILE = DBCLASS_V3ONEDOCFILE,
	LNDBTYPE_V4_NOTEFILE = DBCLASS_V4NOTEFILE,
	LNDBTYPE_V5_NOTEFILE = DBCLASS_V5NOTEFILE
};

// LNDBOPENFLAGS: flags used by LNDatabase::Open.

typedef DWORD LNDBOPENFLAGS;

#define LNDBOPENFLAGS_DEFAULT				0
#define LNDBOPENFLAGS_OPEN_WITH_SCAN_LOCK	DBOPEN_WITH_SCAN_LOCK
#define LNDBOPENFLAGS_PURGE_DELETIONS		DBOPEN_PURGE
#define LNDBOPENFLAGS_NO_USER_INFO			DBOPEN_NO_USERINFO
#define LNDBOPENFLAGS_FORCE_FIXUP			DBOPEN_FORCE_FIXUP
#define LNDBOPENFLAGS_FIXUP_FULL_NOTE_SCAN	DBOPEN_FIXUP_FULL_NOTE_SCAN
#define LNDBOPENFLAGS_FIXUP_KEEP_BAD_NOTES	DBOPEN_FIXUP_NO_NOTE_DELETE
#define LNDBOPENFLAGS_USE_CLUSTER_FAILOVER	DBOPEN_CLUSTER_FAILOVER
#define LNDBOPENFLAGS_DISCONNECT_ON_ERROR	DBOPEN_CLOSE_SESS_ON_ERROR
#define LNDBOPENFLAGS_NO_LOGGING			DBOPEN_NOLOG
#define LNDBOPENFLAGS_DELAY_COMMIT			0x00010000L

// LNFTINDEXFLAGS: flags used by LNDatabase::CreateFTIndex.

typedef WORD LNFTINDEXFLAGS;

#define LNFTINDEXFLAGS_CASE_SENSITIVE			FT_INDEX_CASE_SENS
#define LNFTINDEXFLAGS_DEFAULT					FT_INDEX_AUTOOPTIONS
#define LNFTINDEXFLAGS_INDEX_ALL_BREAKS			FT_INDEX_PSW
#define LNFTINDEXFLAGS_INDEX_ATTACHMENTS		FT_INDEX_ATT
#define LNFTINDEXFLAGS_INDEX_ENCRYPTED_FIELDS	FT_INDEX_ENCRYPTED_FIELDS
#define LNFTINDEXFLAGS_INDEX_STEMS				FT_INDEX_STEM_INDEX
#define LNFTINDEXFLAGS_OPTIMIZE					FT_INDEX_OPTIMIZE
#define LNFTINDEXFLAGS_REINDEX					FT_INDEX_REINDEX
#define LNFTINDEXFLAGS_SUMMARY_ONLY				FT_INDEX_SUMMARY_ONLY
#define LNFTINDEXFLAGS_INDEX_BINARY_ATTACHMENTS	FT_INDEX_ATT_BINARY

// LNFTSEARCHORDER: full-text search options used by LNFTSearchOptions class.

typedef DWORD LNFTSEARCHORDER;

#define LNFTSEARCHORDER_BY_RELEVANCE FT_SEARCH_SCORES
#define LNFTSEARCHORDER_NEWEST_FIRST FT_SEARCH_SORT_DATE
#define LNFTSEARCHORDER_OLDEST_FIRST \
			(FT_SEARCH_SORT_DATE | FT_SEARCH_SORT_ASCEND)


// LNREPLICATIONPRIORITY: database replication priority.

enum LNREPLICATIONPRIORITY
{
	LNREPLICATIONPRIORITY_HIGH = REPLFLG_PRIORITY_HI,
	LNREPLICATIONPRIORITY_LOW = REPLFLG_PRIORITY_LOW,
	LNREPLICATIONPRIORITY_MEDIUM = REPLFLG_PRIORITY_MED
};

// Extended note types. Used internally to resolve ambiguity of note types
enum LNNOTETYPEEXT
{
	// all these notes has NOTE_CLASS_FORM
	LNNOTETYPEEXT_UNKNOWN,
	LNNOTETYPEEXT_FORM,			
	LNNOTETYPEEXT_SUBFORM,		
	LNNOTETYPEEXT_PAGE,			
	LNNOTETYPEEXT_FRAMESET,		
	LNNOTETYPEEXT_IMAGE,		
	LNNOTETYPEEXT_APPLET,		
	LNNOTETYPEEXT_SHARED_ACTIONS,

	// all these notes has NOTE_CLASS_FILTER
	LNNOTETYPEEXT_AGENT,
	LNNOTETYPEEXT_SCRIPT_LIBRARY,
	LNNOTETYPEEXT_DATABASE_SCRIPT,
	LNNOTETYPEEXT_AGENT_DATA,
	LNNOTETYPEEXT_QUERY_OBJECT,
	LNNOTETYPEEXT_OUTLINE,

	// all these notes has NOTE_CLASS_VIEW
	LNNOTETYPEEXT_VIEW_FOLDER,
	LNNOTETYPEEXT_NAVIGATOR
};

// LNNOTETYPE: note type (class).

typedef DWORD LNNOTETYPE;

#define LNNOTETYPE_ACL						MAKELONG((WORD)NOTE_CLASS_ACL,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_AGENT 					MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_AGENT)
#define LNNOTETYPE_PRIVATE_AGENT 			MAKELONG((WORD)(NOTE_CLASS_FILTER | NOTE_CLASS_PRIVATE),(WORD)LNNOTETYPEEXT_AGENT)
	#define LNNOTETYPE_SCRIPT_LIBRARY		MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_SCRIPT_LIBRARY)
	#define LNNOTETYPE_DATABASE_SCRIPT		MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_DATABASE_SCRIPT)
	#define LNNOTETYPE_AGENT_DATA			MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_AGENT_DATA)
	#define LNNOTETYPE_PRIVATE_AGENT_DATA	MAKELONG((WORD)(NOTE_CLASS_FILTER | NOTE_CLASS_PRIVATE),(WORD)LNNOTETYPEEXT_AGENT_DATA)
	#define LNNOTETYPE_QUERY_OBJECT			MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_QUERY_OBJECT)
	#define LNNOTETYPE_OUTLINE				MAKELONG((WORD)NOTE_CLASS_FILTER,(WORD)LNNOTETYPEEXT_OUTLINE)
#define LNNOTETYPE_ALL						MAKELONG((WORD)NOTE_CLASS_ALL, (WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_ALL_NON_DATA				MAKELONG((WORD)NOTE_CLASS_ALLNONDATA , (WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_ALL_UNIQUE				MAKELONG((WORD)NOTE_CLASS_SINGLE_INSTANCE , (WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_DEFAULT_FORM				MAKELONG((WORD)(NOTE_CLASS_FORM | NOTE_CLASS_DEFAULT),(WORD)LNNOTETYPEEXT_FORM)
#define LNNOTETYPE_DEFAULT_VIEW_FOLDER		MAKELONG((WORD)(NOTE_CLASS_VIEW | NOTE_CLASS_DEFAULT),(WORD)LNNOTETYPEEXT_VIEW_FOLDER)
#define LNNOTETYPE_DESIGN					MAKELONG((WORD)NOTE_CLASS_DESIGN,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_DOCUMENT					MAKELONG((WORD)NOTE_CLASS_DOCUMENT,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_FIELD					MAKELONG((WORD)NOTE_CLASS_FIELD,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_FORM						MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_FORM)
	#define LNNOTETYPE_SUBFORM				MAKELONG((WORD)NOTE_CLASS_FORM, (WORD)LNNOTETYPEEXT_SUBFORM)
	#define LNNOTETYPE_PAGE					MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_PAGE)
	#define LNNOTETYPE_FRAMESET				MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_FRAMESET)
	#define LNNOTETYPE_IMAGE				MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_IMAGE)
	#define LNNOTETYPE_APPLET				MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_APPLET)
	#define LNNOTETYPE_SHARED_ACTIONS		MAKELONG((WORD)NOTE_CLASS_FORM,(WORD)LNNOTETYPEEXT_SHARED_ACTIONS)
#define LNNOTETYPE_HELP_ABOUT				MAKELONG((WORD)NOTE_CLASS_INFO,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_HELP_INDEX				MAKELONG((WORD)NOTE_CLASS_HELP_INDEX, (WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_HELP_USING				MAKELONG((WORD)NOTE_CLASS_HELP,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_ICON						MAKELONG((WORD)NOTE_CLASS_ICON,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_NOTIFY_DELETION			MAKELONG((WORD)NOTE_CLASS_NOTIFYDELETION, (WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_REPLICATION_FORMULA		MAKELONG((WORD)NOTE_CLASS_REPLFORMULA,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_PRIVATE					MAKELONG((WORD)NOTE_CLASS_PRIVATE,(WORD)LNNOTETYPEEXT_UNKNOWN)
#define LNNOTETYPE_VIEW_FOLDER				MAKELONG((WORD)NOTE_CLASS_VIEW,(WORD)LNNOTETYPEEXT_VIEW_FOLDER)
#define LNNOTETYPE_PRIVATE_VIEW_FOLDER		MAKELONG((WORD)(NOTE_CLASS_VIEW | NOTE_CLASS_PRIVATE),(WORD)LNNOTETYPEEXT_VIEW_FOLDER)
	#define LNNOTETYPE_NAVIGATOR			MAKELONG((WORD)NOTE_CLASS_VIEW,(WORD)LNNOTETYPEEXT_NAVIGATOR)
#define LNNOTETYPE_UNKNOWN					MAKELONG((WORD)NOTE_CLASS_NONE,(WORD)LNNOTETYPEEXT_UNKNOWN)

// LNNOTEOPENFLAGS: flags used by LNNote::Open.

typedef DWORD LNNOTEOPENFLAGS;

#define LNNOTEOPENFLAGS_ABSTRACT				OPEN_ABSTRACT
#define LNNOTEOPENFLAGS_DEFAULT					0
#define LNNOTEOPENFLAGS_MARK_READ				OPEN_MARK_READ
#define LNNOTEOPENFLAGS_NO_DEFAULT_NOTE_CHECK	OPEN_NOVERIFYDEFAULT
#define LNNOTEOPENFLAGS_NO_OBJECTS				OPEN_NOOBJECTS
#define LNNOTEOPENFLAGS_SHARE					OPEN_SHARE
#define LNNOTEOPENFLAGS_SUMMARY_ONLY			OPEN_SUMMARY
#define LNNOTEOPENFLAGS_EXPAND					OPEN_EXPAND
#define LNNOTEOPENFLAGS_RESPONSE_ID_TABLE		OPEN_RESPONSE_ID_TABLE	
#define LNNOTEOPENFLAGS_WITH_FOLDERS			OPEN_WITH_FOLDERS


// LNNOTESAVEFLAGS: flags used by LNNote::Save.

typedef WORD LNNOTESAVEFLAGS;

#define LNNOTESAVEFLAGS_CHECK_FIELD_NAMES		UPDATE_NAME_KEY_WARNING
#define LNNOTESAVEFLAGS_DELAY_COMMIT			UPDATE_NOCOMMIT
#define LNNOTESAVEFLAGS_DEFAULT					0x0000
#define LNNOTESAVEFLAGS_FORCE					UPDATE_FORCE
#define LNNOTESAVEFLAGS_INCREMENTAL				UPDATE_INCREMENTAL
#define LNNOTESAVEFLAGS_NO_REVISION_HISTORY		UPDATE_NOREVISION

// LNITEMNAMESIZE: maximum item name length, in bytes.

const LNINT LNITEMNAMESIZE = 256;

// LNFORMULAEVENT: event which may have lotus script as well as formula code in it.

enum LNFORMULAEVENT				
{
//	Order is important and follows Notes UI

	// events on forms which are also 
	// implemented as separate methods
	LNFORMULAEVENT_WINDOW_TITLE,			
	LNFORMULAEVENT_HTML_HEADER_CONTENT,
	LNFORMULAEVENT_HTML_BODY_ATTRIBUTES,	
	LNFORMULAEVENT_WEB_QUERY_OPEN,
	LNFORMULAEVENT_WEB_QUERY_SAVE,			
	LNFORMULAEVENT_HELP_REQUEST,	
	LNFORMULAEVENT_TARGET_FRAME,

	// extra view events which are also 
	// implemented as separate methods
	LNFORMULAEVENT_VIEW_SELECTION,
	LNFORMULAEVENT_FORM_FORMULA,
	LNFORMULAEVENT_TARGET_FRAME_SINGLE_CLICK,	
	LNFORMULAEVENT_TARGET_FRAME_DOUBLE_CLICK,

	// extra shared field events which are
	// also implemented as the field separate methods
	LNFORMULAEVENT_DEFAULT_VALUE,
	LNFORMULAEVENT_INPUT_TRANSLATION,
	LNFORMULAEVENT_INPUT_VALIDATION,	
	LNFORMULAEVENT_HTML_FIELD_ATTRIBUTES,

	// events which are implemented through
	// SetFormulaEvent only
	LNFORMULAEVENT_QUERY_OPEN,			
	LNFORMULAEVENT_POST_OPEN,
	LNFORMULAEVENT_QUERY_MODECHANGE,	
	LNFORMULAEVENT_POST_MODECHANGE,
	LNFORMULAEVENT_POST_RECALC,			
	LNFORMULAEVENT_REGION_DOUBLECLICK,	
	LNFORMULAEVENT_QUERY_OPENDOCUMENT,
	LNFORMULAEVENT_QUERY_RECALC,	
	LNFORMULAEVENT_QUERY_ADDTOFOLDER,	
	LNFORMULAEVENT_QUERY_PASTE,		
	LNFORMULAEVENT_POST_PASTE,	
	LNFORMULAEVENT_QUERY_DRAGDROP,	
	LNFORMULAEVENT_POST_DRAGDROP,
	LNFORMULAEVENT_QUERY_SAVE,
	LNFORMULAEVENT_POST_SAVE,	
	LNFORMULAEVENT_QUERY_CLOSE,	
	LNFORMULAEVENT_COUNT	// number of enumeration values
};

// LNITEMTYPE: note item types.

typedef LNINT LNITEMTYPE;

#define LNITEMTYPE_ANY				0xFFFFFFFFL
#define LNITEMTYPE_SPECIAL			0x80000000L
#define LNITEMTYPE_COMPOSITE_OLE_FLAG		0x40000000L
#define LNITEMTYPE_COMPOSITE_ACTION_FLAG	0x20000000L

#define LNITEMTYPE_ACTION			TYPE_ACTION
#define LNITEMTYPE_ASSISTANT_INFO	TYPE_ASSISTANT_INFO
#define LNITEMTYPE_CALENDAR_FORMAT	TYPE_CALENDAR_FORMAT
#define LNITEMTYPE_COLLATION		TYPE_COLLATION
#define LNITEMTYPE_DATETIMES		TYPE_TIME_RANGE
#define LNITEMTYPE_ERROR			TYPE_ERROR
#define LNITEMTYPE_FONTTABLE		(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL)
#define LNITEMTYPE_FORMULA			TYPE_FORMULA
#define LNITEMTYPE_FORM_VIEW_ACTION	(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_ACTION_FLAG)
#define LNITEMTYPE_HIGHLIGHTS		TYPE_HIGHLIGHTS
#define	LNITEMTYPE_HTML				TYPE_HTML
#define LNITEMTYPE_ICON				TYPE_ICON
#define LNITEMTYPE_LSOBJECT			TYPE_LSOBJECT
#define LNITEMTYPE_NOTELINKS		TYPE_NOTELINK_LIST
#define LNITEMTYPE_NOTEREFS			TYPE_NOTEREF_LIST
#define LNITEMTYPE_NUMBERS			TYPE_NUMBER_RANGE
#define LNITEMTYPE_OBJECT			TYPE_OBJECT
#define LNITEMTYPE_OLE_OBJECT		(TYPE_COMPOSITE | LNITEMTYPE_SPECIAL | LNITEMTYPE_COMPOSITE_OLE_FLAG)
#define LNITEMTYPE_QUERY			TYPE_QUERY
#define LNITEMTYPE_RICHTEXT			TYPE_COMPOSITE
#define LNITEMTYPE_SCHED_LIST		TYPE_SCHED_LIST
#define LNITEMTYPE_SEAL				TYPE_SEAL
#define LNITEMTYPE_SEALDATA			TYPE_SEALDATA
#define LNITEMTYPE_SEAL_LIST		TYPE_SEAL_LIST
#define LNITEMTYPE_SIGNATURE		TYPE_SIGNATURE
#define LNITEMTYPE_TEXT				TYPE_TEXT_LIST
#define LNITEMTYPE_UNAVAILABLE		TYPE_UNAVAILABLE
#define LNITEMTYPE_UNKNOWN			(TYPE_INVALID_OR_UNKNOWN | LNITEMTYPE_SPECIAL)
#define LNITEMTYPE_UNSUPPORTED		TYPE_INVALID_OR_UNKNOWN
#define LNITEMTYPE_USERDATA			TYPE_USERDATA
#define LNITEMTYPE_USERID			TYPE_USERID
#define LNITEMTYPE_VIEW_FORMAT		TYPE_VIEW_FORMAT
#define LNITEMTYPE_VIEWMAP_DATASET	TYPE_VIEWMAP_DATASET
#define LNITEMTYPE_VIEWMAP_LAYOUT	TYPE_VIEWMAP_LAYOUT
#define LNITEMTYPE_WORKSHEET_DATA	TYPE_WORKSHEET_DATA
// LNITEMTYPE_DATETIMERANGES is defined for compatibility with previous
// C++ API releases, but is no longer used.
#define LNITEMTYPE_DATETIMERANGES	(LNITEMTYPE_DATETIMES | LNITEMTYPE_SPECIAL)

// LNITEMFLAGS: note item flags.

typedef WORD LNITEMFLAGS;

#define LNITEMFLAGS_NONE			0
#define LNITEMFLAGS_AUTHORS			ITEM_READWRITERS
#define LNITEMFLAGS_AUTO_SUMMARY	0x0008
#define LNITEMFLAGS_ENCRYPT			ITEM_SEAL
#define LNITEMFLAGS_NAMES			ITEM_NAMES
#define LNITEMFLAGS_PLACEHOLDER		ITEM_PLACEHOLDER
#define LNITEMFLAGS_PROTECTED		ITEM_PROTECTED
#define LNITEMFLAGS_READERS			ITEM_READERS
#define LNITEMFLAGS_SIGN			ITEM_SIGN
#define LNITEMFLAGS_SUMMARY			ITEM_SUMMARY
#define LNITEMFLAGS_UNCHANGED		ITEM_UNCHANGED

// LNITEMOPTION: options used by LNNote::CreateItem.

enum LNITEMOPTION
{
	LNITEMOPTION_APPEND_ONLY	= 0x10000,
	LNITEMOPTION_DELETE_APPEND	= 0x20000,
	LNITEMOPTION_ERROR			= 0x30000
};

// Options used by LNDateFormat, LNNumberFormat, and LNInternational classes.

enum LNDATEFORMAT
{
	LNDATEFORMAT_ALL = TDFMT_FULL,
	LNDATEFORMAT_MONTH_DAY = TDFMT_PARTIAL,
	LNDATEFORMAT_MONTH_DAY_YEAR = TDFMT_CPARTIAL,
	LNDATEFORMAT_YEAR_MONTH = TDFMT_DPARTIAL,
	LNDATEFORMAT_ALL_FULL_YEAR = TDFMT_FULL4,
	LNDATEFORMAT_MONTH_DAY_FULL_YEAR = TDFMT_CPARTIAL4,
	LNDATEFORMAT_FULL_YEAR_MONTH = TDFMT_DPARTIAL4
};

enum LNDATEORDER
{
	LNDATEORDER_DMY = DATE_DMY,
	LNDATEORDER_MDY = DATE_MDY,
	LNDATEORDER_YMD = DATE_YMD
};

// TSFMT_CDATE ordinarilly defined in MISC.H but placed here to accomodate S390 changes 7/01

#ifndef TSFMT_CDATE
#define TSFMT_CDATE 4
#endif

enum LNDATETIMEDISPLAY
{
	LNDATETIMEDISPLAY_DATE = TSFMT_DATE,
	LNDATETIMEDISPLAY_DATE_AND_TIME = TSFMT_DATETIME,
	LNDATETIMEDISPLAY_TIME = TSFMT_TIME,
	LNDATETIMEDISPLAY_TODAY_AND_TIME = TSFMT_CDATETIME,
	LNDATETIMEDISPLAY_TODAY = TSFMT_CDATE
};

enum LNDAYOFWEEK
{
	LNDAYOFWEEK_SUNDAY = 1,
	LNDAYOFWEEK_MONDAY = 2,
	LNDAYOFWEEK_TUESDAY = 3,
	LNDAYOFWEEK_WEDNESDAY = 4,
	LNDAYOFWEEK_THURSDAY = 5,
	LNDAYOFWEEK_FRIDAY = 6,
	LNDAYOFWEEK_SATURDAY = 7
};

enum LNNUMBERFORMAT
{
	LNNUMBERFORMAT_GENERAL = NFMT_GENERAL,
	LNNUMBERFORMAT_FIXED = NFMT_FIXED,
	LNNUMBERFORMAT_SCIENTIFIC = NFMT_SCIENTIFIC,
	LNNUMBERFORMAT_CURRENCY = NFMT_CURRENCY
};

// TTFMT_FULL_MAX ordinarilly defined in MISC.H but placed here to accomodate S390 changes 7/01

#ifndef TTFMT_FULL_MAX
#define TTFMT_FULL_MAX 3
#endif

enum LNTIMEFORMAT
{
	LNTIMEFORMAT_HOUR = TTFMT_HOUR,
	LNTIMEFORMAT_HOUR_MINUTE = TTFMT_PARTIAL,
	LNTIMEFORMAT_HOUR_MINUTE_SECOND = TTFMT_FULL,
	LNTIMEFORMAT_HOUR_MINUTE_SECOND_HUNDREDTHS = TTFMT_FULL_MAX
};

enum LNTIMEZONE
{
	LNTIMEZONE_GMT = 0,
	LNTIMEZONE_ZW1 = 1,
	LNTIMEZONE_ZW2 = 2,
	LNTIMEZONE_ZW3 = 3,
	LNTIMEZONE_NST = 3003,
	LNTIMEZONE_AST = 4,
	LNTIMEZONE_EST = 5,
	LNTIMEZONE_CST = 6,
	LNTIMEZONE_MST = 7,
	LNTIMEZONE_PST = 8,
	LNTIMEZONE_YST = 9,
	LNTIMEZONE_ZW9B = 3009,
	LNTIMEZONE_HST = 10,
	LNTIMEZONE_BST = 11,
	LNTIMEZONE_ZW12 = 12,
	LNTIMEZONE_ZE12C = -4512,
	LNTIMEZONE_ZE12 = -12,
	LNTIMEZONE_ZE11B = -3011,
	LNTIMEZONE_ZE11 = -11,
	LNTIMEZONE_ZE10B = -3010,
	LNTIMEZONE_ZE10 = -10,
	LNTIMEZONE_ZE9B = -3009,
	LNTIMEZONE_ZE9 = -9,
	LNTIMEZONE_ZE8 = -8,
	LNTIMEZONE_ZE7 = -7,
	LNTIMEZONE_ZE6B = -3006,
	LNTIMEZONE_ZE6 = -6,
	LNTIMEZONE_ZE5C = -4505,
	LNTIMEZONE_ZE5B = -3005,
	LNTIMEZONE_ZE5 = -5,
	LNTIMEZONE_ZE4B = -3004,
	LNTIMEZONE_ZE4 = -4,
	LNTIMEZONE_ZE3B = -3003,
	LNTIMEZONE_ZE3 = -3,
	LNTIMEZONE_ZE2 = -2,
	LNTIMEZONE_CET = -1
};

enum LNTIMEZONEDISPLAY
{
	LNTIMEZONEDISPLAY_ADJUST_TO_LOCAL = TZFMT_NEVER,
	LNTIMEZONEDISPLAY_SHOW_ALWAYS = TZFMT_ALWAYS,
	LNTIMEZONEDISPLAY_SHOW_IF_NOT_LOCAL = TZFMT_SOMETIMES
};
	
// LNSTRINGCOMPAREFLAGS: flags used by global LNStringCompare functions.

typedef DWORD LNSTRINGCOMPAREFLAGS;

#define LNSTRINGCOMPAREFLAGS_MATCH_ACCENT	INTL_ACCENT_SENSITIVE
#define LNSTRINGCOMPAREFLAGS_MATCH_CASE		INTL_CASE_SENSITIVE
#define LNSTRINGCOMPAREFLAGS_DEFAULT		0

// LNVFSHARINGOPTION: view/folder sharing option (shared or private)

enum LNVFSHARINGOPTION
{
	LNVFSHARINGOPTION_SHARED,
	LNVFSHARINGOPTION_PRIVATE,
	LNVFSHARINGOPTION_PRIVATE_ON_FIRST_USE,
	LNVFSHARINGOPTION_PRIVATE_ON_FIRST_USE_IN_DESKTOP,

	// The next two and the typedef below are for backwards compatibility.
	LNVFSHARING_SHARED		= LNVFSHARINGOPTION_SHARED,
	LNVFSHARING_PERSONAL	= LNVFSHARINGOPTION_PRIVATE
};

typedef LNVFSHARINGOPTION LNVFSHARING;

// LNVFTYPE: view/folder type (view or folder)

enum LNVFTYPE
{
	LNVFTYPE_VIEW,
	LNVFTYPE_FOLDER
};

// LNENCRYPTOPTION: encryption option for LNDatabase::CreateEncryptedNote

enum LNENCRYPTOPTION
{
	LNENCRYPTOPTION_PRIVATE	= 0,
	LNENCRYPTOPTION_PUBLIC	= ENCRYPT_WITH_USER_PUBLIC_KEY
};

// Pointers to OLE interfaces

typedef void *	LNILockBytes;
typedef void *	LNIStorage;

// OLE GUID or CLSID

typedef struct 
{
    DWORD Data1;
    WORD  Data2;
    WORD  Data3;
    BYTE  Data4[8];
} LNOLEGUID;

// LNOLECLIPBOARDFORMAT: data formats for LNOLEObject and LNRTOLEObject

enum LNOLECLIPBOARDFORMAT
{
	LNOLECLIPBOARDFORMAT_TEXT		= DDEFORMAT_TEXT,
	LNOLECLIPBOARDFORMAT_METAFILE	= DDEFORMAT_METAFILE,
	LNOLECLIPBOARDFORMAT_BITMAP		= DDEFORMAT_BITMAP,
	LNOLECLIPBOARDFORMAT_RICHTEXT	= DDEFORMAT_RTF,
	LNOLECLIPBOARDFORMAT_ICON		= DDEFORMAT_ICON
};

// LNFORMTYPE: defines the type of a form. Used in LNForm class.

enum LNFORMTYPE
{
	LNFORMTYPE_DOCUMENT				= 0,	// Document
	LNFORMTYPE_RESPONSE,					// Response to topic.
	LNFORMTYPE_RESPONSE_TO_RESPONSE			// Response to response.	
};

// LNINCLUDEINMENUOPTION: defines where in the create menu a choice to 
// create a note will be put and how the choice will be displayed.  Used
// in LNForm class.

enum LNINCLUDEINMENUOPTION
{
	LNINCLUDEINMENUOPTION_CREATE		= 0,	// include a menu choice in the Create menu
	LNINCLUDEINMENUOPTION_CREATE_OTHER,			// include a choice in the Create - Other - Dialog box
	LNINCLUDEINMENUOPTION_NONE					// no menu or dialog choices for this form
};

// LNVERSIONINGOPTION: defines the versioning options for documents created using a form.

enum LNVERSIONINGOPTION
{
	LNVERSIONINGOPTION_NONE		= 0,						// No versioning options.
	LNVERSIONINGOPTION_RESPONSE	= TPL_FLAG_UPDATE_RESPONSE,	// New versions become responses.
	LNVERSIONINGOPTION_PARENT	= TPL_FLAG_UPDATE_PARENT,	// Prior versions become responses.
	LNVERSIONINGOPTION_SIBLING	= TPL_FLAG_UPDATE_SIBLING	// New versions become siblings
};

// LNCONTEXTPANEOPTION: defines the type of context pane specified in a form.

enum LNCONTEXTPANEOPTION
{
	LNCONTEXTPANEOPTION_NONE	= 0,	// No context pane specified in this form.
	LNCONTEXTPANEOPTION_DOCLINK,		
	LNCONTEXTPANEOPTION_PARENT		
};

// LNINHERITDOCOPTION: defines whether a document will be stored
// in a rich text field of a newly created document and the 
// storage method to use.

enum LNINHERITDOCOPTION
{
	LNINHERITDOCOPTION_NONE					= 0,	// Document will not be stored.
	LNINHERITDOCOPTION_RICH_TEXT,					// Stored as rich text.
	LNINHERITDOCOPTION_COLLAPSIBLE_RICH_TEXT,		// Stored as collapsible rich text,
	LNINHERITDOCOPTION_LINK							// Stored as link
};

// LNAUTOLAUNCHOBJECTTYPE: defines a form's auto launch object type for 
// documents that use the form.

enum LNAUTOLAUNCHOBJECTTYPE
{
	LNAUTOLAUNCHOBJECTTYPE_NONE			= AUTOLAUNCH_OBJTYPE_NONE,		// No auto launch options specified
	LNAUTOLAUNCHOBJECTTYPE_ATTACHMENT	= AUTOLAUNCH_OBJTYPE_ATTACH,	// Launches the first attachment
	LNAUTOLAUNCHOBJECTTYPE_DOCLINK		= AUTOLAUNCH_OBJTYPE_DOCLINK,	// Launches the first Doclink
	LNAUTOLAUNCHOBJECTTYPE_OLE_OBJECT	= AUTOLAUNCH_OBJTYPE_OLEOBJ,	// Launches the first OLE object
	LNAUTOLAUNCHOBJECTTYPE_OLE_CLASS	= AUTOLAUNCH_OBJTYPE_OLE_CLASS,	// OLE Class ID (GUID)
	LNAUTOLAUNCHOBJECTTYPE_URL			= AUTOLAUNCH_OBJTYPE_URL		// Launches the url in the URL field
};

// LNCREATEOBJECTINFIELDOPTION: When an object is autolaunched, modified by the user, and saved,
// it is copied to and displayed in the document in the field specified by this option.

enum LNCREATEOBJECTINFIELDOPTION
{
	LNCREATEOBJECTINFIELDOPTION_NONE 			= FIELD_COPY_NONE,	// Don't copy or display the object to any field.
	LNCREATEOBJECTINFIELDOPTION_FIRST_RT_FIELD	= FIELD_COPY_FIRST,	// Displays the object in the first rich text field.
	LNCREATEOBJECTINFIELDOPTION_NAMED_RT_FIELD	= FIELD_COPY_NAMED	// Use the RT field name specified by an LNString. 
};

// LNLAUNCHOBJECTWHENFLAGS: Flags used by the auto launch feature in forms
// to determine when an object, contained in a document will autolaunch.

typedef DWORD LNLAUNCHOBJECTWHENFLAGS;

#define LNLAUNCHOBJECTWHENFLAGS_CREATING	LAUNCH_WHEN_CREATE
#define LNLAUNCHOBJECTWHENFLAGS_EDITING		HIDE_OPEN_EDIT
#define LNLAUNCHOBJECTWHENFLAGS_READING		LAUNCH_WHEN_READ

// LNHIDEDOCUMENTWHENFLAGS: Flags used by the auto launch feature in 
// forms to determine when to hide the notes document. 

typedef DWORD LNHIDEDOCUMENTWHENFLAGS;

#define LNHIDEDOCUMENTWHENFLAGS_OPEN_CREATING	HIDE_OPEN_CREATE
#define LNHIDEDOCUMENTWHENFLAGS_OPEN_EDITING	HIDE_OPEN_EDIT
#define LNHIDEDOCUMENTWHENFLAGS_OPEN_READING	HIDE_OPEN_READ
#define LNHIDEDOCUMENTWHENFLAGS_CLOSE_CREATING	HIDE_CLOSE_CREATE
#define LNHIDEDOCUMENTWHENFLAGS_CLOSE_EDITING	HIDE_CLOSE_EDIT
#define LNHIDEDOCUMENTWHENFLAGS_CLOSE_READING	HIDE_CLOSE_READ

//	LNATTACHMENTTYPE: type of data stored in an attachment.

enum LNATTACHMENTTYPE
{
	LNATTACHMENTTYPE_DOS				= HOST_MSDOS,
	LNATTACHMENTTYPE_OLE				= HOST_OLE,
	LNATTACHMENTTYPE_MAC				= HOST_MAC,
	LNATTACHMENTTYPE_UNKNOWN			= HOST_UNKNOWN,
	LNATTACHMENTTYPE_HPFS				= HOST_HPFS,
	LNATTACHMENTTYPE_OLELIB				= HOST_OLELIB,
	LNATTACHMENTTYPE_BYTEARRAY_EXTENT	= HOST_BYTEARRAY_EXT,
	LNATTACHMENTTYPE_BYTEARRAY_PAGE		= HOST_BYTEARRAY_PAGE,
	LNATTACHMENTTYPE_CD_STORAGE			= HOST_CDSTORAGE,
	LNATTACHMENTTYPE_STREAM				= HOST_STREAM,
	LNATTACHMENTTYPE_RESOURCE_LINK		= HOST_LINK
};

//	LNACTIONTYPE:  type of action performed by a button, action hotspot, agent, or action

enum LNACTIONTYPE
{
	LNACTIONTYPE_UNKNOWN = 0,
	LNACTIONTYPE_FORMULA,
	LNACTIONTYPE_LOTUSSCRIPT,
	LNACTIONTYPE_SIMPLE_ACTIONS,
	LNACTIONTYPE_COMMAND,
	LNACTIONTYPE_JAVA,
	LNACTIONTYPE_JAVASCRIPT
};

//	LNSCRIPTLIBRARYTYPE:  type of the script library

enum LNSCRIPTLIBRARYTYPE
{
	LNSCRIPTLIBRARYTYPE_UNKNOWN = 0,
	LNSCRIPTLIBRARYTYPE_LOTUSSCRIPT,
	LNSCRIPTLIBRARYTYPE_JAVA
};

//  Base types of frameset
enum LNFRAMESETBASETYPE
{
	LNFRAMESETBASETYPE_DEFAULT = 0,
	LNFRAMESETBASETYPE_L = LNFRAMESETBASETYPE_DEFAULT,
	LNFRAMESETBASETYPE_R,	
	LNFRAMESETBASETYPE_T,
	LNFRAMESETBASETYPE_B,
	LNFRAMESETBASETYPE_LR,//
	LNFRAMESETBASETYPE_TB,//
	LNFRAMESETBASETYPE_LT,
	LNFRAMESETBASETYPE_TL,
	LNFRAMESETBASETYPE_LB,
	LNFRAMESETBASETYPE_BL,//
	LNFRAMESETBASETYPE_RB,
	LNFRAMESETBASETYPE_BR,//
	LNFRAMESETBASETYPE_RTB,
	LNFRAMESETBASETYPE_LTB,
	LNFRAMESETBASETYPE_TLB,
	LNFRAMESETBASETYPE_TBL
};


// LNCHARSET: specifies input character set for LNStringTranslate

enum LNCHARSET
{
	LNCHARSET_UNICODE,
	LNCHARSET_UTF8
};

// LNUNITS:	identifies the units of user input and output values. Generally,
//			Notes data is stored in TWIPS.

enum LNUNITS
{
	LNUNITS_INCHES,
	LNUNITS_CENTIMETERS,
	LNUNITS_TWIPS,
	LNUNITS_DEFAULT
};


enum LNNOTEDELETEFLAGS
{
    LNNOTEDELETEFLAGS_FORCE     = UPDATE_FORCE,
    LNNOTEDELETEFLAGS_NOCOMMIT  = UPDATE_NOCOMMIT,
    LNNOTEDELETEFLAGS_NOSTUB    = UPDATE_NOSTUB
};

// LNCOLOR: representation of an 8-bit color value. LNCOLOR_xxx values map
//			the first 0-15 Notes color values. Notes allows 240 total 8-bit
//			values. The LNColor class supports RGB colors added in Notes 5.0.

typedef WORD LNCOLOR;

#define LNCOLOR_BLACK 			NOTES_COLOR_BLACK
#define LNCOLOR_WHITE			NOTES_COLOR_WHITE
#define LNCOLOR_RED				NOTES_COLOR_RED
#define LNCOLOR_GREEN			NOTES_COLOR_GREEN
#define LNCOLOR_BLUE			NOTES_COLOR_BLUE
#define LNCOLOR_MAGENTA			NOTES_COLOR_MAGENTA
#define LNCOLOR_YELLOW			NOTES_COLOR_YELLOW
#define LNCOLOR_CYAN			NOTES_COLOR_CYAN
#define LNCOLOR_DARK_RED		NOTES_COLOR_DKRED
#define LNCOLOR_DARK_GREEN		NOTES_COLOR_DKGREEN
#define LNCOLOR_DARK_BLUE		NOTES_COLOR_DKBLUE
#define LNCOLOR_DARK_MAGENTA	NOTES_COLOR_DKMAGENTA
#define LNCOLOR_DARK_YELLOW		NOTES_COLOR_DKYELLOW
#define LNCOLOR_DARK_CYAN		NOTES_COLOR_DKCYAN
#define LNCOLOR_GRAY			NOTES_COLOR_GRAY
#define LNCOLOR_LIGHT_GRAY		NOTES_COLOR_LTGRAY

//
//	Position constants
//

typedef enum
{
	LNPOSITION_NONE = 0,
	LNPOSITION_LEFT,
	LNPOSITION_CENTER,
	LNPOSITION_RIGHT
} LNPOSITION;


#endif	// LNENUMS_H

