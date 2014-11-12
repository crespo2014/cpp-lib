//===========================================================================
//
// Module:	LNERRORS.H
//
// Description:
//
//		C++ API error and warning codes.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif


//-----	Error codes:


// General and session error codes:

LNERRDEF( ASSERT_FAILED, "Assertion failed" )
LNERRDEF( NO_ERROR_MESSAGE, "(no error message available)" )
LNERRDEF( NOT_FOUND, "No match found" )
LNERRDEF( NOT_IMPLEMENTED, "Function has not been implemented" )
LNERRDEF( OBSOLETE, "Function or type no longer supported" )
LNERRDEF( ILLEGAL_OPERATION, "This function is inappropriate for this object" )
LNERRDEF( UNANTICIPATED_FUNCTION_CALLED, \
	"This function should not be called in this situation" )
LNERRDEF( UNEXPECTED_CALLED, "unexpected() function called" )
LNERRDEF( TERMINATE_CALLED, "terminate() function called" )
LNERRDEF( WRONG_VERSION, \
	"API program is incompatible with this version of the API library" )
LNERRDEF( SESSION_NOT_INITIALIZED, "Notes session has not been initialized" )
LNERRDEF( SESSION_ALREADY_INITIALIZED, \
	"Notes session has already been initialized" )
LNERRDEF( CANNOT_REINIT_SESSION, \
	"Cannot initialize a new Notes session after calling Term" )
#ifdef MAC
LNERRDEF( NO_NOTES_INI, "The Notes Preferences file cannot be found")
#else
LNERRDEF( NO_NOTES_INI, \
	"The NOTES.INI file cannot be found on the search path (PATH)")
#endif
LNERRDEF( INVALID_LOGENTRY, "LogEntry object is invalid" )
LNERRDEF( ADDIN_ALREADY_INITIALIZED, \
	"Notes Addin has already been initialized" )
LNERRDEF( ADDIN_INVALID_LINEID, \
	"An invalid Addin Status Line ID has been passed in" )
LNERRDEF( CANNOT_DELETE_DEFAULT_STATUS_LINE, \
	"Cannot delete the default status line for this Addin" )
LNERRDEF( OBJECT_NOT_IN_LIST, "Object not in object list" )
LNERRDEF( NO_SORT_KEY, "LNSortedObjectList::AddObject requires sort key" )
LNERRDEF( OBJECT_ALREADY_IN_LIST, "Object already in object list" )
LNERRDEF( OBJECT_NOT_ON_HEAP, \
	"Object must be on heap to be added to object list" )
LNERRDEF( EXPECTED_DATA_NOT_FOUND, \
	"Expected data was not found" )
#ifdef OS390
LNERRDEF( FLOAT_OVERFLOW, \
	"Notes floating-point number is too large to convert to OS/390 format" )
#endif
LNERRDEF( UNSUPPORTED_PLATFORM, "The current platform is not supported." )


// Parameter errors codes:

LNERRDEF( NULL_POINTER_PARAMETER, \
	"Null pointer or invalid object passed to function" )
LNERRDEF( ARGUMENT_CANNOT_BE_NULL, \
	 "Argument passed to function cannot be NULL; initialize it first")
LNERRDEF( INVALID_PARAMETER, "Invalid parameter passed to function" )
LNERRDEF( PARAMETER_OUT_OF_RANGE, "Function parameter is out of range" )
LNERRDEF( SUBSCRIPT_OUT_OF_RANGE, "Array subscript is out of range" )
LNERRDEF( CLOSED_OBJECT_PARAMETER, "Object passed to function must be open" )
LNERRDEF( OBJECT_CLOSED, "Object has already been closed" )
LNERRDEF( OBJECT_NOT_INITIALIZED, "Object has not been initialized" )
LNERRDEF( UNINITIALIZED_OBJECT_PARAMETER, \
	"Uninitialized object passed to function" )
LNERRDEF( NO_NAME, "Object must have a name" )
LNERRDEF( INVALID_CONVERSION, "Couldn't perform conversion" )
LNERRDEF( NOT_INSERTABLE_TYPE, "Cannot insert this type into this object" )
LNERRDEF( OBJECT_MISMATCH, "Object is not of correct type")
LNERRDEF( OBJECT_CORRUPTED, "Object or data is corrupted" )
LNERRDEF( NULL_STRING_PARAMETER, "Null string passed to function" )
LNERRDEF( STRING_TOO_LONG, \
	"String length exceeds maximum allowed for this function" )
LNERRDEF( CANNOT_GET_STRING_SIZE, \
	"Error encountered while using LNL to determine string size" )
LNERRDEF( INVALID_UNID_STRING, "Invalid universal ID string" )


// Memory error codes:

LNERRDEF( NO_MEMORY, "Insufficient memory" )
LNERRDEF( NEED_MORE_MEMORY, \
	"The memory allocated for the output parameter is too small" )
LNERRDEF( ALREADY_ALLOCATED, \
	"Memory for this object has already been allocated" )
LNERRDEF( CANNOT_ALLOC_WHILE_DELETING, \
	"Cannot allocate memory while LNDeleteAllObjects executes" )
LNERRDEF( NOT_LNNEW_BLOCK, "LNDelete: memory block not allocated by LNNew" )
LNERRDEF( CANNOT_CREATE_MUTEX, \
	"Memory initialization error: unable to create mutex" )
LNERRDEF( CANNOT_GET_MUTEX, \
	"Memory allocation error: unable to obtain mutex" )
LNERRDEF( CANNOT_GET_TLS, \
	"Memory initialization error: unable to obtain thread-local storage" )

	
// Database error codes:

LNERRDEF( INVALID_DATABASE_NAME, "Invalid or missing database pathname" )
LNERRDEF( DATABASE_CLOSED, \
	"Unable to perform operation due to unopened database" )
LNERRDEF( WRONG_DATABASE, \
	"Specified note(s) and note array must be in the same database" )
LNERRDEF( DB_IS_DIRECTORY, "Database pathname is a directory" )
LNERRDEF( NOT_TEMPLATE_DATABASE, "Database is not a design template" )
LNERRDEF( DATABASE_ALREADY_EXISTS,
	"Cannot create database: the specified pathname already exists" )


// ACL error codes:

LNERRDEF( CANNOT_CREATE_ACL, "Cannot create ACL in new database" )
LNERRDEF( ACL_OBJECT_ALREADY_EXISTS, "Can only get one LNACL object" )
LNERRDEF( ACL_CLOSED, "ACL must be open in order to use this function" )
LNERRDEF( INVALID_ROLE_NAME_CHARACTER, "Invalid role character" )
LNERRDEF( INVALID_DEFAULT_ACL_NAME, "Cannot change default ACL entry name")


// Note and item error codes:

LNERRDEF( NOTE_ALREADY_EXISTS,"The note already exists in the database" )
LNERRDEF( CANNOT_CREATE_NOTE, "Unable to create new note" )
LNERRDEF( NOTE_CLOSED, "Unable to perform operation due to unopened note" )
LNERRDEF( CANNOT_ADD_NEW_NOTE, "Cannot add new note without saving it first" )
LNERRDEF( NOTE_MISMATCH, "Incorrect note type specified" )
LNERRDEF( CANNOT_GET_NOTE_SIZE, "Unable to calculate note size" )
LNERRDEF( NOTE_ITEM, "Function invalid for items in a note" )
LNERRDEF( UNDEFINED_ITEM, \
	"Item is uninitialized, possibly because the note containing the item has been closed" )
LNERRDEF( ITEM_ALREADY_EXISTS, "Item already exists in the note" )
LNERRDEF( ITEM_MISMATCH, "Incorrect item type specified" )
LNERRDEF( OFFSET_OUT_OF_RANGE, "Offset is beyond the range of the item" )
LNERRDEF( CANNOT_CONVERT_DATE, "Couldn't convert date or time" )
LNERRDEF( CANNOT_ADJUST_DATE, "Couldn't adjust date or time" )
LNERRDEF( SPECIAL_DATETIME,
	"This operation cannot be performed on a special date/time value" )
LNERRDEF( NOT_SUPPORTED_FOR_FT_RESULT, \
	"This operation cannot be performed on the result of a full-text search" )
LNERRDEF( NOT_NOTE_ITEM, \
	"This operation cannot be performed on an item that is not in a note" )
LNERRDEF( CANNOT_INSERT_DATETIMES, \
	"Cannot insert the specified LNDatetimes object at the specified position; use Append instead" )
LNERRDEF( ENTRY_MUST_BE_DATETIME, \
	"The LNDatetimes entry at the specified position cannot be a date/time range" )
LNERRDEF( ENTRY_MUST_BE_DATETIME_RANGE, \
	"The LNDatetimes entry at the specified position must be a date/time range" )
LNERRDEF( ITEM_NOT_FOUND, \
	"Item does not exist in the note" )
LNERRDEF( NOTE_NAME_TOO_LONG, \
	"Note name is too long or cascades too many levels" )
LNERRDEF( UNABLE_TO_CREATE_ITEM, \
    "Unable to create item in the note" ) 
LNERRDEF( UNABLE_TO_RETRIEVE_ITEM, \
    "Unable to retrieve item from the note" ) 
LNERRDEF( NOTE_MUST_HAVE_NAME, \
    "Note must have a valid name before it can be saved" )
LNERRDEF( NOTE_NAME_ENDING_BACKSLASH, \
	"Names may not end with the '\\' symbol" )


// Document and mail message error codes:

LNERRDEF( NO_MAIL_DATABASE, "Cannot locate mail database" )
LNERRDEF( INVALID_MAIL_DATABASE, \
	"Document's database is not the user's mail file" )
LNERRDEF( PARENTDB_DOESNT_MATCH, \
	"Can't make response document, parent's database doesn't match the doc's" )
LNERRDEF( SERVER_MAIL_NOTSUPPORTED, "Server mail function not supported" )
LNERRDEF( INVALID_MAIL_MESSAGE, "Invalid mail message" )
LNERRDEF( CANNOT_COPY_MAIL_MESSAGE, \
	"Prevent copying function enabled, can't copy message" )

// Events error codes
LNERRDEF(UNSUPPORTED_EVENT, "Unsupported event for design note of this type" )

// Image resource error codes:

LNERRDEF(INVALID_BMP_FORMAT, "Invalid BMP format" )
LNERRDEF(UNSUPPORTED_BMP_FORMAT, "Unsupported BMP format" )
LNERRDEF(BMP_IMAGE_NOT_SUPPORTED, \
		 "BMP image is not supported by this function on the current platform" )
LNERRDEF(IMAGE_RESOURCE_WRONG_DB, \
		 "Attempt to insert image resource from another database" )

// View/folder error codes:

LNERRDEF( INVALID_VIEW_FOLDER, "Invalid view or folder" )
LNERRDEF( INVALID_CALENDAR_VIEW_FOLDER, "Invalid calendar view or folder" )
LNERRDEF( CANNOT_INITIALIZE_VIEW_FOLDER, \
	"Error initializing view or folder data" )
LNERRDEF( EMPTY_ARRAY_PARAMETER, \
	"Empty array, view/folder, or navigator passed to function" )
LNERRDEF( VIEW_FOLDER_NOT_SAVED, \
	"View or folder must be saved before accessing entries" )
LNERRDEF( VIEW_FOLDER_CLOSED, \
	"View or folder must be open in order to use this function" )
LNERRDEF( WRONG_VIEW_FOLDER, \
	"Object is not associated with this view or folder" )
LNERRDEF( INVALID_VIEW_FOLDER_VERSION, \
	"Unsupported view or folder version" )
LNERRDEF( CANNOT_READ_VIEW_FOLDER_DESIGN, \
	"Unable to read view or folder design information" )
LNERRDEF( DESIGN_ALREADY_EXISTS, \
	"Design object already exists for this view or folder" )
LNERRDEF( NO_COLLECTION, \
	"No collection open for this view, folder, or navigator" )
LNERRDEF( TOO_MANY_KEYS, \
	"LNVFFindKeys object already has maximum number of keys" )
LNERRDEF( ITEM_TABLE_TOO_BIG, \
	"LNVFFindKeys ITEM_TABLE exceeds maximum size" )
LNERRDEF( UNREAD_NOT_SUPPORTED,
	"This operation requires the LNViewFolder::Open LNVFOPENFLAGS_USE_UNREAD_LIST flag" )
LNERRDEF( TOO_MANY_COLUMNS, "Cannot add the requested number of columns" )
LNERRDEF( NOT_SUPPORTED_FOR_SEARCH_NAVIGATOR, \
	"This operation cannot be performed on a navigator obtained using FTSearch or Find" )
LNERRDEF( CANNOT_DELETE_CATEGORY, "Cannot delete category or total entry" )
LNERRDEF( CANNOT_GET_CATEGORY, "Cannot get document for category or total entry" )
LNERRDEF( NO_ENTRIES, "No entries in this view, folder, or navigator" )
LNERRDEF( CANNOT_CREATE_VFENTRY, "Cannot create view or folder entry" )
LNERRDEF( CANNOT_DELETE_ENTRIES, \
	"Cannot delete entries that do not belong to this navigator" )
LNERRDEF( CANNOT_TRANSLATE_SPECIAL_VALUE, \
	"LNVFEntry::operator[]: cannot translate special @function value" )
LNERRDEF( CANNOT_EVALUATE_COLUMN_FORMULA, \
	"LNVFEntry::operator[]: cannot evaluate column formula" )
LNERRDEF( NIFREADENTRIES, "Unexpected NIFReadEntries failure" )
LNERRDEF( VIEW_FOLDER_NAME_TOO_LONG, \
	"View or folder name (including alias) is too long" )
LNERRDEF( VIEW_FOLDER_DUPLICATE_NAME, \
	"A view or folder with the specified name and sharing option already exists" )
LNERRDEF( NOT_FOLDER, "This operation can only be performed on a folder" )
LNERRDEF( NOT_SUPPORTED_FOR_FOLDER, \
	"This operation cannot be performed on a folder" )
LNERRDEF( NOT_CALENDAR, \
	"This operation can only be performed on a calendar view or folder" )
LNERRDEF( NOT_SUPPORTED_FOR_CALENDAR, \
	"This operation cannot be performed on a calendar view or folder" )
LNERRDEF( DESIGN_ONLY, \
	"This operation is not supported with the LNVFOPENFLAGS_DESIGN_ONLY flag" )
LNERRDEF( TIME_SLOTS_OVERLAP, "Starting and ending time slot hours overlap" )
LNERRDEF( INVALID_SECONDARY_SORT_COLUMN, \
	"Secondary sort column cannot be the current column" )
LNERRDEF( NO_SECONDARY_SORT_COLUMN_AVAILABLE, \
	"No columns available to use as secondary sort column" )
LNERRDEF( INVALID_HEADING_SORT_VIEW_FOLDER, \
	"LNVFColumn::SetHeadingSortViewFolder: cannot specify the current view or folder" )
LNERRDEF( VIEW_FOLDER_MUST_HAVE_NAME, \
	"View or folder must have a valid name before it can be saved" )
LNERRDEF( CANNOT_CHANGE_INTERNAL_NAME, \
	"Cannot change column's internal name if value is based on field name" )
LNERRDEF( CANNOT_CREATE_COLLECTION, \
	"Cannot create view or folder collection because LNVFOPENFLAGS_NO_CREATE was specified" )
LNERRDEF( TOO_MANY_FIND_KEYS, \
	"Find: number of search keys exceeds number of indexed columns" )
LNERRDEF( INVALID_FOR_NON_CATEGORIZED, "Property is invalid for non-categorized views" )
LNERRDEF( EMPTY_AUTHORS_LIST, \
		 "Non-empty Authors list should be specified if not all authors are allowed" )
LNERRDEF( EMPTY_READERS_LIST, \
		 "Non-empty Readers list should be specified if not all readers are allowed" )
	
// Form and form field error codes:

LNERRDEF( FORM_MUST_HAVE_NAME, \
	"Form must have a valid name before it can be saved" )
LNERRDEF( FORM_CLOSED, "Unable to perform operation due to unopened form" )
LNERRDEF( FORM_NAME_TOO_LONG, \
	"Form name (including alias) is too long" )
LNERRDEF( FORM_DUPLICATE_NAME, \
	"A form with the specified name already exists" )
LNERRDEF( NOT_FORM_NOTE, "This operation can only be performed on a form, subform, or page note" )
LNERRDEF( FIELD_ALREADY_IN_FORM, \
	"A form field with this name is already a member of the form" )
LNERRDEF( INVALID_FIELD_NAME, \
	"Illegal characters in the field name" )
LNERRDEF(OBJECT_PRE_46, \
	"Object, created with Notes 4.6 and above, was edited with Notes 4.5, or lower" )
LNERRDEF(NO_CFFORMULA, \
	"No formula specified for computed field" )
LNERRDEF(FIELD_TOO_LARGE, \
	"Field is too large" )
LNERRDEF(NOT_A_CHOICES_FORMULA, \
	"Field does not contain a formula for choices" )
LNERRDEF(NOT_A_CHOICES_LIST, \
	"Field does not contain a list for choices" )
LNERRDEF(MULTIPLE_FORMS, \
	"Database contains more than one form with the specified name" )
LNERRDEF(CANNOT_RESIZE_FIELD, \
    "Field of this type does not allow to set its size" )  
LNERRDEF(CANNOT_SET_WIDTH_IN_PERCENTAGE, \
    "Field of this type does not allow to set its width in percentage" )
LNERRDEF(CANNOT_SET_DYNAMIC_HEIGHT, \
    "Field of this type does not allow to set dynamic height" ) 
LNERRDEF(CANNOT_CHANGE_FIELD_STYLE, \
    "Field of this type does not allow to change its style" )
LNERRDEF(UNANTICIPATED_FIELD_PROPERTY, \
    "Field of this type does not have specified feature" )
LNERRDEF(INVALID_LAYOUT_FIELD, \
	"Invalid field type for layout region" )

// framesets error codes
LNERRDEF(DATABASE_LINKS_NOT_SUPPORTED, \
		 "Database link is not allowed in a frame" )
LNERRDEF(LAST_FRAME, \
		 "Last frame can not be removed from a frameset" )

// Page error code
LNERRDEF(CANNOT_INSERT_INTO_PAGE, \
		 "Rich text containing fields, shared fields, \
		  subforms, and some of the embedded controls \
		  can not be inserted into a page" )

// Script library error codes

LNERRDEF(DUPLICATE_SCRIPT_LIBRARY_NAME, \
	"Script library with the specified name and type already exists" )
LNERRDEF(INVALID_LIBRARY_TYPE, "The script library type is inappropriate" )

// Subform error codes

LNERRDEF( SUBFORM_MUST_HAVE_NAME, \
	"Subform must have a valid name before it can be saved" )
LNERRDEF( SUBFORM_DUPLICATE_NAME, \
	"A subform with the specified name already exists in the rich text" )
LNERRDEF(CANNOT_INSERT_INTO_SUBFORM, \
	"Cannot insert an object of this type into a subform" )
LNERRDEF(SUBFORM_MISSING_DATABASE, \
	"The subform must be contained by a database" )
LNERRDEF( NO_SUBFORM_NOTE, "Cannot locate subform note" )
LNERRDEF( SUBFORM_NAME_TOO_LONG, \
		 "Subform name (including alias) is too long")
LNERRDEF(MULTIPLE_SUBFORMS, \
	"Database contains more than one subform with the specified name" )

// Shared field errors

LNERRDEF(SHARED_FIELD_ALREADY_EXISTS, \
	"Shared field with this name already exists in database" )
LNERRDEF(SHARED_FIELD_WRONG_DB, \
	"Attempt to insert shared field from another database" )
LNERRDEF(SHARED_FIELD_NOT_FOUND, \
	"Specified shared field does not exist in the database")


// Agent error codes:

LNERRDEF( AGENT_CLOSED, "Agent must be open in order to use this function" )
LNERRDEF( INVALID_AGENT_TYPE, "The agent type is inappropriate" )
LNERRDEF( AGENT_MUST_HAVE_NAME, "Agent must have a name" )
LNERRDEF( AGENT_NAME_TOO_LONG, "Agent name is too long" )
LNERRDEF( AGENT_ALREADY_INITIALIZED, "Agent already initialized" )
LNERRDEF( AGENT_NOT_INITIALIZED, "Agent was not initialized" )
LNERRDEF( AGENT_NO_RUN_DATA, "Unable to retrieve run data for the agent" )
LNERRDEF( AGENT_DUPLICATE_NAME, "An agent with the specified name already exists" )
LNERRDEF( PRIVATE_SYNCH_MAIL_AGENT, "Synchronized new mail agent can not be private" )
LNERRDEF( MULTIPLE_SYNCH_MAIL_AGENTS, \
		 "Only one synchronized new mail agent may be enabled at a time" )
LNERRDEF( JAVA_CODE_IS_MISSING, "Java code is missing" )
LNERRDEF( NOT_SUPPORTED_PRIOR_46, \
		 "This function is not supported for the Notes releases prior to R4.6" ) 
LNERRDEF( JAVA_FILE_NOT_IN_LIST,
	"Specified java file is not listed in the agent note" )
LNERRDEF( INVALID_IN_FOLDER_SEARCH,
    "Specified in search folder does not exist in the database" )
LNERRDEF( INVALID_FIELDS_IN_FORM_SEARCH,
		 "Specified 'Fields In Form' search is invalid" )
LNERRDEF( INVALID_BY_FORM_USED_SEARCH, "Specified 'By Form Used' search is invalid" )


// General rich text error codes:

LNERRDEF( RICHTEXT_NOT_EMPTY, "An empty richtext object is expected" )
LNERRDEF( UNEXPECTED_RICHTEXT_TYPE, \
	"A different rich text type is expected" )
LNERRDEF( INVALID_RICHTEXT, "Rich text object is invalid" )
LNERRDEF( INVALID_SELECTION, "Selection of rich text is invalid" )
LNERRDEF( INVALID_HOT_REGION, \
	"Rich text hotspot cannot contain tables, sections, or other hotspots" )
LNERRDEF( INVALID_HOTSPOT_ACTION, "This action is not supported in hotspots" )
LNERRDEF( INVALID_GRAPHIC, "Graphic rich text object is invalid" )
LNERRDEF( CANNOT_ADD_CHILD_TO_ELEMENT, \
	"Cannot add a child to a richtext element" )
LNERRDEF( CANNOT_ACCESS_RTCHAR, \
	"Users cannot access rich text characters directly" )
LNERRDEF( RTOBJECT_NOT_IN_CONTAINER, \
	"Rich text object is not member of container" )
LNERRDEF( RTOBJECT_ALREADY_IN_CONTAINER, \
	"Rich text object is already a member of container" )
LNERRDEF( RTPARSER_STACK_OVERFLOW, "Rich text parser stack overflow" )
LNERRDEF( RTPARSER_STACK_EMPTY, "Rich text parser stack is empty" )
LNERRDEF( RTPARSER_INVALID_STACK, "Rich text parser stack is invalid" )
LNERRDEF( RTPARSER_BAD_GRAPHIC, "Rich Text Parser encountered corrupted CD Graphic collection" )
LNERRDEF( RTPARSER_BAD_LAYOUT, "Rich text parser encoutered corrupted layout region" )
LNERRDEF( UNAVAILABLE_CDRECORD, "Cannot use LNCompositeData to manipulate the given CD Record type" )
LNERRDEF( CANNOT_CREATE_ATTACHMENT_IF_SIGNED, \
	"Cannot create new attachment from an attachment that is signed")
LNERRDEF( CANNOT_CREATE_ATTACHMENT, \
	"Cannot create new attachment")
LNERRDEF( ATTACHMENT_MUST_HAVE_NOTE, \
	"Cannot create an attachment or embedded object without a note")
LNERRDEF( ATTACHMENT_ARG_IS_NULL, \
	"Cannot create new attachment from uninitialized argument")
LNERRDEF( INVALID_CURSOR, "Rich text cursor is invalid" )
LNERRDEF( CURSOR_ARGS_INCORRECT, \
	"Cursor arguments are incorrect; start cursor is after end cursor")
LNERRDEF( CURSOR_HAS_NO_PARENT, \
	"Cursor does not have a parent container; it is invalid")
LNERRDEF( CANNOT_CONVERT_NULLS, \
	"Cannot convert nulls in stylized text to new paragraphs")
LNERRDEF( INVALID_PARAGRAPH_MARGIN, "Rich text paragraph margin or indentation is invalid" )
LNERRDEF( TOO_MANY_TABSTOPS, "The tab array is already full" )
LNERRDEF( CANNOT_CREATE_FONT_STYLE, "Error creating LNFontStyle object" )
LNERRDEF( TOO_MANY_FONTS, "Too many fonts in the font table" )
LNERRDEF( EMPTY_FONT_TABLE, "You must have at least one font in the font table" )
LNERRDEF( INCONSISTENT_STANDARD_FONT, \
	"Cannot set font style to Notes standard name but non-default pitch or family" )
LNERRDEF( FACE_ALREADY_EXISTS, "The specified face already exists in the font table" )
LNERRDEF( COLOR_NOT_FOUND, "Colors are not in index" )
LNERRDEF( BUTTONTYPE_UNKNOWN, "The type of this button is unknown" )
LNERRDEF( INVALID_ANCHOR_LINK, "Anchor link data is inconsistent" )
LNERRDEF( ANCHOR_LOCATION_NOT_IN_RICH_TEXT, \
	"Anchor location is not in a rich text item" )
LNERRDEF( NOT_ANCHOR_LINK, "The link is not an anchor link" )
LNERRDEF( ACTIVEOBJECTTYPE_UNKNOWN, "The type of this active object is unknown" )
LNERRDEF( RT_ITEM_TRUNCATED, "Cannot initialize rich text;  item may be truncated" )
LNERRDEF( TEXT_TOO_BIG, "LNStylizedText object cannot exceed 40 KB" )
LNERRDEF( BORDERTYPE_UNKNOWN, "The border type of this object is unknown" )
LNERRDEF( UNSPECIFIED_OBJECT_TYPE, "Can not determin the object type" )
LNERRDEF( COMP_ARRAY_OPERATION_FAILED, "Operation on composite data array failed" )
LNERRDEF( NO_GRADIENT_COLOR, "No gradient color present" )
LNERRDEF( NO_URL_FORMULA, "No URL Formula present")
LNERRDEF( UNKNOWN_FIELD_VALUE, "Unknown rich text field value")

// Table and table cell error codes:

LNERRDEF( OBJECT_IS_NOT_TABLE, "Input object is not a table")
LNERRDEF( TABLE_LEFTMARGIN_EXCEEDS_RIGHTMARGIN, \
	"Left margin cannot be greater than right margin")
LNERRDEF( TABLE_TOO_WIDE, "Table cannot be wider than 22.75 inches")
LNERRDEF( COLWIDTH_EXCEEDS_TABLE_WIDTH, \
	"Column width cannot exceed table width")
LNERRDEF( COLWIDTH_OUT_OF_RANGE, \
	"Column width cannot be greater than current table width - minimum width for remaining cells")
LNERRDEF( COLWIDTH_TOO_SMALL, "Column width is too small")
LNERRDEF( FRACT_WIDTH_OUT_OF_RANGE, \
	"Fractional width exceeds maximum of 20 inches")
LNERRDEF( COUNT_CANNOT_BE_ZERO, \
	"Cannot insert/append zero rows or columns")
LNERRDEF( COUNT_EXCEEDS_MAXROWS, \
	"Count plus exisiting rows exceeds max rows of 255")
LNERRDEF( TABLE_TOO_MANY_ROWS, \
	"A table can have a maximum of 255 rows; number input exceeds this maximum")
LNERRDEF( COUNT_EXCEEDS_MAXCOLUMNS, \
	"Count plus exisiting columns exceeds max columns of 64")
LNERRDEF( TABLE_TOO_MANY_COLUMNS, \
	"A table can have a maximum of 64 columns; number input exceeds this maximum")
LNERRDEF( ROW_OUT_OF_RANGE, "Row position is out of range" )
LNERRDEF( COLUMN_OUT_OF_RANGE, "Column position is out of range")
LNERRDEF( CANNOT_DELETE_ALL, \
	"Cannot delete all rows or columns; table requires 1 row and column")
LNERRDEF( CANNOT_DELETE_PAST_END, \
	"Starting position plus count is greater than rows/columns in table")
LNERRDEF( CANNOT_APPEND_TO_TABLE, \
	"Cannot append to a table; use table cells or the cursor to insert items in cells")
LNERRDEF( TABLE_CELL_NOT_INITIALIZED, \
	"Table cell used as input must be a valid cell in table")
LNERRDEF( OBJECT_IS_NOT_TABLECELL, \
	"Object is not a table cell; cannot assign, copy, etc.")
LNERRDEF( TABLE_CELL_INPUT_INVALID, \
	"Table cell input must belong to this table")
LNERRDEF( CHILD_MUST_BE_TABLE_CELL, \
	"First child containing cursor in table must be a table cell; object corrupt")
LNERRDEF( TABLECELL_PARENT_NOT_TABLE, \
	"A table cell must have a table as a parent; this is invalid rich text")
LNERRDEF( TABLE_INVALID_CELL_WIDTH, \
	"A table cell can have a maximum border width of 10; number inout exceeds maximum")
LNERRDEF( INVALID_CELL_SPACE, "Cell spacing exceeds maximum allowable")
LNERRDEF( TABLECELL_REQUIRES_PABREF, \
	"All table cells must contain at least one PAB REFERENCE; invalid rich text")
LNERRDEF( RTPARSER_BAD_TABLE, "Rich Text Parser encountered corrupted table CD collection" )
LNERRDEF( INVALID_TRANS_EFFECT, "Invalid cell transition effect" )
LNERRDEF( SOLID_TABLECELL_BACKGROUND, "A solid cell background (e.g. color) is needed." )
LNERRDEF( INVALID_TABLE_FORMAT, "The current table format is not valid or doesn't support \
		 such action." )
LNERRDEF( TABLE_NOT_NAMED, "Table is not named" )
LNERRDEF( TABLE_NO_SELECTION_FORMULA, "Table has no selection formula" )
LNERRDEF( TABLE_NO_SELECTION_STRING, "Table has no selection string" )
LNERRDEF( TABLE_MERGE_OVERLAP, "Merge regions overlap" )
LNERRDEF( TABLECELL_NO_IMAGE, "No background image for this table cell" )
LNERRDEF( TABLECELL_NO_IMAGE_PLACEMENT,
		 "No background image placement for this table cell" )
LNERRDEF( TABLECELL_IMAGE_NAME_FORMULA, "Background image name is a formula" )
LNERRDEF( TABLECELL_IMAGE_NAME_STRING, "Background image name is a string" )
LNERRDEF( TABLE_MERGE_COLUMN_FIXED, "Cannot merge fixed-width columns" )

// File and import/export error codes:

LNERRDEF( FILE_OPENMODE, "Invalid file mode" )
LNERRDEF( FILE_GET_OFFSET, "Error getting file's offset" )
LNERRDEF( FILE_SET_OFFSET, "Error setting file's offset" )
LNERRDEF( FILE_REMOVE, "Error removing a file" )
LNERRDEF( FILE_CREATE, "Error creating a new file" )
LNERRDEF( FILE_WRITE, "Error writing to file" )
LNERRDEF( FILE_READ, "Error reading from file" )
LNERRDEF( FILE_CLOSE, "Error closing file" )
LNERRDEF( FILE_OPEN, "Error opening file" )
LNERRDEF( FILELIST_TOO_LONG, \
	"The FileList exceeds the max length in LNReplicationOptions" )
LNERRDEF( IMPORT_FILE_NOT_FOUND, \
    "Required import file name is missing" )
LNERRDEF( EXPORT_FILE_NOT_FOUND, \
    "Required export file name is missing" )
LNERRDEF( IMPORT_DLL_NOT_FOUND, \
    "Can't find any import dll that supports the input file format" )
LNERRDEF( EXPORT_DLL_NOT_FOUND, \
    "Can't find any export dll that supports the input file format" )
LNERRDEF( UNSUPPORTED_FILE_FORMAT, \
    "This file format is not currently supported" )


// OLE-specific error codes

LNERRDEF( INCOMPATIBLE_OLE_STORAGE_VERSION, \
	"Incompatible OLE object storage version number" )
LNERRDEF( OLE_OBJ_ALREADY_OPEN, \
    "OLE object is already open" )
LNERRDEF( OLE_OBJ_NOT_OPEN, \
    "OLE object is not open" )
LNERRDEF( INVALID_OLE_PAGE, \
    "OLE object page index is invalid" )
LNERRDEF( OLE_CANNOT_OPEN, \
	"Cannot open OLE object" )
LNERRDEF( OLE_COPY_FAILED, \
	"Copy of OLE object failed" )
LNERRDEF( OLE_OBJECT_MUST_HAVE_NOTE, \
	"Embedded OLE object must be in a note")
LNERRDEF( INVALID_OLE_OBJECT, \
    "OLE object is invalid" )


// Calendaring and Scheduling error codes

LNERRDEF( DATE_RANGE_INVALID_DAYS, \
	"Date range must start and end on the same day" )
LNERRDEF( INVALID_EVENT_TYPE, \
	"Any is not a valid event type for this method")
LNERRDEF(  NOT_MEETING, \
	"You can only set attendees for meetings")


// Action error codes

LNERRDEF( NO_ACTION_OPERATOR, \
	"No action operator is available" )
LNERRDEF( NO_SEARCH_OPERATOR, \
	"No search operator is available" )
LNERRDEF( SIZE_LIMIT_EXCEEDED, \
	"Record size exceeds 64k limit" )
LNERRDEF( FIELD_NOT_FOUND, \
	"Field does not exist" )
LNERRDEF( FIELD_CONTAINS_STRING, \
	"Field contains a string" )
LNERRDEF( FIELD_CONTAINS_FORMULA, \
	"Field contains a formula" )
LNERRDEF( NO_GATHER_COUNT, \
	"Gather documents is disabled" )
LNERRDEF( NO_VIEW_SUMMARY, \
	"Include summary for document in view is disabled" )

//  Positioning error codes
LNERRDEF( LEFT_OUTSIDE_CONTAINER, \
	"Left edge is outside container" )
LNERRDEF( RIGHT_OUTSIDE_CONTAINER, \
	"Right edge is outside container" )
LNERRDEF( BOTTOM_OUTSIDE_CONTAINER, \
	"Bottom edge is outside container" )

//-----	Warning codes:


LNWARNDEF( NOT_FOUND, "No match found" )
LNWARNDEF( MEMORY_LEAK, "Undeleted objects found; possible memory leak" )
LNWARNDEF( NOT_OPEN, "Object is not open" )
LNWARNDEF( ALREADY_OPEN, "Object is already open" )
LNWARNDEF( CANNOT_DELETE_DEFAULT_ENTRY, "Can not delete -Default- entry" )
LNWARNDEF( TOO_MANY_ROLES, "No more slot available to create role specified" )
LNWARNDEF( MAIL_FORM_NOT_FOUND, "There is no form to render the body item" )
LNWARNDEF( MAILER_NOSUCHUSER, "No such group" )
LNWARNDEF( MAILER_NOTUNIQUE, "Group Name not unique" )
LNWARNDEF( UNKNOWN_NAME, "Group Name unknown" )
LNWARNDEF( NO_PARENT_NOTE, "There is no parent note for this document" )
LNWARNDEF( USE_FORWARD_FUNCTION_INSTEAD, "Use Forward function instead of Send" )
LNWARNDEF( TABSTOP_ALREADY_EXISTS, "The input tab stop is already in the tab array ")
LNWARNDEF( MQ_EMPTY, "Message Queue is empty" )
LNWARNDEF( UNEXPECTED_CDRECORD, \
	"The CD Record is part of another class; manipulating it with LNCompositeData is discouraged")
LNWARNDEF( AUTOWIDTH_MUST_BE_SET, \
		  "This function is a no op unless set to window (automatic width) is TRUE")
LNWARNDEF( OLE_END_OF_DATA, "End of OLE object data")
LNWARNDEF( OLE_NEW_LOCKBYTES, "New ILockBytes created" )
LNWARNDEF( CD_LENGTH_MISMATCH, \
		  "Input length does not match CD record length")
LNWARNDEF( END_OF_DATA, "End of data reached")
LNWARNDEF( FIELD_IS_SHARED, "The field is already shared" )
LNWARNDEF( NOT_SHARED_FIELD, "The field is not shared" )
LNWARNDEF( DESIGN_ELEMENT_NOT_UNIQUE, "Design element is not unique" )
LNWARNDEF( NO_AGENT_RUN_INFO, "Agent's run info is missing" )
LNWARNDEF( TOO_MUCH_TEXT, "Rich text item has more than 64k of text" )
LNWARNDEF( CANNOT_USE_CACHE, "Cannot use view/folder cache for this operation" )
LNWARNDEF( JAVA_FILE_LIST_EMPTY, "The list of Java code files is empty" )
LNWARNDEF( NOTE_DELETED, "The note has been deleted or does not exist" )
LNWARNDEF( TEXT_TOO_BIG_FOR_NOTES, \
		  "LNStylizedText object exceeds 20 KB, which might prevent Notes from opening the document")
LNWARNDEF( UNSUPPORTED_EVENT, "Code for unsupported events is ignored" )
LNWARNDEF( NEW_HTML_TAGS, "New HTML tags record created." )
LNWARNDEF( CELL_NOT_MERGED, "Specified table cell is not merged" )
LNWARNDEF( NOT_MERGE_CELL, "Table cell is not the merge cell" )
LNWARNDEF( FILE_NOT_FOUND, "File not found" )
LNWARNDEF( FUNCTION_DEPRECATED, "This function has been deprecated. For more information, please read the documentation." )
