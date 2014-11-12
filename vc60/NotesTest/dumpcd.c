/****************************************************************************

    FILE:       dumpcd.c

    PROGRAM:    nsf_dump

    DESCRIPTION:
	This file contains routines that print the contents of
	Compound Text (CD) records to the dumpfile. These routines
	mostly just dump structures defined in Lotus C API for Domino and Notes
	header file editods.h.

	Note: #ifdef APITESTMODE is for internal use only.
****************************************************************************/

/* C include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lotus C API for Domino and Notes include files */
#include <global.h>
#include <intl.h>
#include <nsf.h>
#include <misc.h>
#include <osmem.h>
#include <osmisc.h>
#include <ostime.h>
#include <stdnames.h>
#include <textlist.h>
#include <editdflt.h>
#include <editods.h>
#include <actods.h>
#include <oleods.h>
#include <actprop.h>
#include <rsrcods.h>
#include <fsods.h>

/* NSF_DUMP - specific include file */
#include "nsf_dump.h"

/* declare globals defined in nsf_dump.c */
extern DWORD       nl;
extern DWORD       nw;
extern DWORD       nc;

/* Literal tables */

	/* Hotspot Type Table */
#define NUM_HOTSPOT_TYPES 23
struct
{
	WORD    wHotSpotType;
	char   *szTypeStr;
}   HotSpotTypeTable[NUM_HOTSPOT_TYPES] =
{
	HOTSPOTREC_TYPE_POPUP,      "POPUP",
	HOTSPOTREC_TYPE_HOTREGION,  "HOTREGION",
	HOTSPOTREC_TYPE_BUTTON,     "BUTTON",
	HOTSPOTREC_TYPE_FILE,       "FILE",
	HOTSPOTREC_TYPE_SECTION,    "SECTION",
	HOTSPOTREC_TYPE_ANY,        "ANY",
	HOTSPOTREC_TYPE_HOTLINK,        "HOTLINK",
	HOTSPOTREC_TYPE_BUNDLE,         "BUNDLE",
	HOTSPOTREC_TYPE_V4_SECTION,     "V4 SECTION",
	HOTSPOTREC_TYPE_SUBFORM,        "SUBFORM",
	HOTSPOTREC_TYPE_ACTIVEOBJECT,   "ACTIVE OBJECT",
	HOTSPOTREC_TYPE_OLERICHTEXT,    "OLE RICH TEXT",
	HOTSPOTREC_TYPE_EMBEDDEDVIEW,   "EMBEDDED VIEW",
	HOTSPOTREC_TYPE_EMBEDDEDFPANE,  "EMBEDDED FOLDER PANE",
	HOTSPOTREC_TYPE_EMBEDDEDNAV,    "EMBEDDED NAVIGATOR",
	HOTSPOTREC_TYPE_FILEUPLOAD,     "FILE UPLOAD PLACEHOLDER",
	HOTSPOTREC_TYPE_MOUSEOVER,		"MOUSE OVER TEXT POPUP",
	HOTSPOTREC_TYPE_EMBEDDEDOUTLINE,"EMBEDDED OUTLINE",
	HOTSPOTREC_TYPE_EMBEDDEDCTL,	"EMBEDDED CONTROL WINDOW",
	HOTSPOTREC_TYPE_EMBEDDEDCALENDARCTL, "EMBEDDED CALENDAR CONTROL",
	HOTSPOTREC_TYPE_EMBEDDEDSCHEDCTL, "EMBEDDED SCHEDULE CONTROL",
	HOTSPOTREC_TYPE_RCLINK,			"RESOURCE LINK",
	HOTSPOTREC_TYPE_EMBEDDEDEDITCTL, "EMBEDDEDEDITCTL"
};

	/* LayoutFieldTypeTable - used via GetLiteralString() */
LITERAL_NAME_ENTRY LayoutFieldTypeTable [] =
{
	{LAYOUT_FIELD_TYPE_TEXT,        "TYPE_TEXT"},
	{LAYOUT_FIELD_TYPE_CHECK,       "TYPE_CHECK"},
	{LAYOUT_FIELD_TYPE_RADIO,       "TYPE_RADIO"},
	{LAYOUT_FIELD_TYPE_LIST,        "TYPE_LIST"},
	{LAYOUT_FIELD_TYPE_COMBO,       "TYPE_COMBO"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN FIELD TYPE"}
};

	/* StorageLinkTypeTable - used via GetLiteralString() */
LITERAL_NAME_ENTRY StorageLinkTypeTable [] =
{
	{STORAGE_LINK_TYPE_OBJECT,                      "TYPE_OBJECT"},
	{STORAGE_LINK_TYPE_NOTE,                        "TYPE_NOTE"},
	{STORAGE_LINK_TYPE_URL_CONVERTED,       "TYPE_URL_CONVERTED"},
	{STORAGE_LINK_TYPE_URL_MIME,            "TYPE_URL_MIME"},
	{STORAGE_LINK_TYPE_MIME_PART,			"TYPE_MIME_PART"},	/* New for R5.0 */
	{STORAGE_LINK_TYPE_MIME_OBJECT,			"TYPE_MIME_OBJECT"},/* New for R5.0 */

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN LINK TYPE"}
};

	/* StorageLinkLoadTable - used via GetLiteralString() */
LITERAL_NAME_ENTRY StorageLinkLoadTable [] =
{
	{STORAGE_LINK_LOAD_DEFERRED,    "LOAD_DEFERRED"},
	{STORAGE_LINK_LOAD_ON_DEMAND,   "LOAD_ON_DEMAND"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN FIELD TYPE"}
};

	/* Domino and Notes DDE format types - used via GetLiteralString() */
LITERAL_NAME_ENTRY DDEFormatTable [] =
{
	{DDEFORMAT_TEXT,                "TEXT"},
	{DDEFORMAT_METAFILE,    "METAFILE"},
	{DDEFORMAT_BITMAP,              "BITMAP"},
	{DDEFORMAT_RTF,                 "RTF"},
	{DDEFORMAT_OWNERLINK,   "OWNERLINK"},
	{DDEFORMAT_OBJECTLINK,  "OBJECTLINK"},
	{DDEFORMAT_NATIVE,              "NATIVE"},
	{DDEFORMAT_ICON,                "ICON"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN FORMAT"}
};

	/* CDBAR border types - used via GetLiteralString() */

LITERAL_NAME_ENTRY BarRecBorderTable [] =
{
	{BARREC_BORDER_SHADOW,          "SHADOW"},
	{BARREC_BORDER_NONE,            "NONE"},
	{BARREC_BORDER_SINGLE,          "SINGLE"},
	{BARREC_BORDER_DOUBLE,          "DOUBLE"},
	{BARREC_BORDER_TRIPLE,          "TRIPLE"},
	{BARREC_BORDER_TWOLINE,         "TWOLINE"},
	{BARREC_BORDER_WINDOWCAPTION,   "WINDOWCAPTION"},
	{BARREC_BORDER_OTHER,			"GRADIENT or OTHER (if DATAFLAGS record follows)"},
	{BARREC_BORDER_GRADIENT,		"GRADIENT or OTHER (if DATAFLAGS record follows)"},
	{BARREC_BORDER_TAB,             "TAB"},
	{BARREC_BORDER_DIAG,            "DIAGONAL"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN BORDER TYPE"}
};


	/* CDACTION types - used via GetLiteralString() */
LITERAL_NAME_ENTRY ActionTypeTable [] =
{
	{ACTION_RUN_FORMULA,    "ACTION_RUN_FORMULA"},
	{ACTION_RUN_SCRIPT,             "ACTION_RUN_SCRIPT"},
	{ACTION_RUN_AGENT,              "ACTION_RUN_AGENT"},
	{ACTION_OLDSYS_COMMAND, "ACTION_OLDSYS_COMMAND"},
	{ACTION_SYS_COMMAND,    "ACTION_SYS_COMMAND"},
	{ACTION_PLACEHOLDER,    "ACTION_PLACEHOLDER"},
	{ACTION_RUN_JAVASCRIPT,	"ACTION_RUN_JAVASCRIPT"}, /* New for R5.0 */

	/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN ACTION TYPE"}
};

	/* CDACTIONBAR Line types - used via GetLiteralString() */
LITERAL_NAME_ENTRY ActionBarLineTable [] =
{
	{ACTION_LINE_SINGLE,    "ACTION_LINE_SINGLE"},
	{ACTION_LINE_DOUBLE,    "ACTION_LINE_DOUBLE"},
	{ACTION_LINE_TRIPLE,    "ACTION_LINE_TRIPLE"},
	{ACTION_LINE_TWO,               "ACTION_LINE_TWO"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN LINE STYLE TYPE"}
};

	/* CDACTIONBAR Border types - used via GetLiteralString() */
LITERAL_NAME_ENTRY ActionBarBorderTable [] =
{
	{ACTION_BORDER_NONE, "ACTION_BORDER_NONE"},
	{ACTION_BORDER_MAX,  "ACTION_BORDER_MAX"},
	{ACTION_BORDER_VAR,  "ACTION_BORDER_VAR"},
	{ACTION_BORDER_ABS,  "ACTION_BORDER_ABS"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN BORDER STYLE TYPE"}
};


	/* ActiveObjectTypeTable - used via GetLiteralString() */
LITERAL_NAME_ENTRY ActiveObjectTypeTable [] =
{
	{ACTIVEOBJECT_TYPE_JAVA,        "JAVA"},
	{ACTIVEOBJECT_TYPE_PLUGIN,      "PLUGIN"},
	{ACTIVEOBJECT_TYPE_OBJECT,      "OBJECT"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN OBJECT TYPE"}
};

	/* ActiveObjectUnitsTable - used via GetLiteralString() */
LITERAL_NAME_ENTRY ActiveObjectUnitsTable [] =
{
	{ACTIVEOBJECT_UNIT_PIXELS,              "PIXELS"},
	{ACTIVEOBJECT_UNIT_HIMETRICS,   "HIMETRIC"},
	{ACTIVEOBJECT_UNIT_INCHES,              "INCHES"},
	{ACTIVEOBJECT_UNIT_PERCENT,             "PERCENT"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,             "UNKNOWN OBJECT UNITS"}
};
	/*	BorderStyle for CDBORDERINFO */
LITERAL_NAME_ENTRY BorderStyleTable [] =
{
	{CDBORDERSTYLE_NONE,	"NONE"},
	{CDBORDERSTYLE_SOLID,	"SOLID"},
	{CDBORDERSTYLE_DOUBLE,	"DOUBLE"},
	{CDBORDERSTYLE_INSET,	"INSET"},
	{CDBORDERSTYLE_OUTSET,	"OUTSET"},
	{CDBORDERSTYLE_RIDGE,	"RIDGE"},
	{CDBORDERSTYLE_GROOVE,	"GROOVE"},
	{CDBORDERSTYLE_DOTTED,	"DOTTED"},
	{CDBORDERSTYLE_DASHED,	"DASHED"},
	{CDBORDERSTYLE_PICTURE,	"PICTURE"},
	{CDBORDERSTYLE_GRAPHIC,	"GRAPHIC"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN BORDER STYLE"}
};

	/*	ViewerType for CDPRETABLEBEGIN */
LITERAL_NAME_ENTRY ViewerTypeTable [] =
{
	{CDTABLEVIEWER_ONCLICK,			"ONCLICK"},
	{CDTABLEVIEWER_ONLOADTIMER,		"ONLOADTIMER"},
	{CDTABLEVIEWER_ONLOADCYCLEONCE,	"ONLOADCYCLEONCE"},
	{CDTABLEVIEWER_TABS,			"TABS"},
	{CDTABLEVIEWER_FIELDDRIVEN,		"FIELDDRIVEN"},
	{CDTABLEVIEWER_CYCLEONCE,		"CYCLEONCE"},
	{CDTABLEVIEWER_CAPTIONS,		"CAPTIONS"},
	{CDTABLEVIEWER_LAST,			"LAST"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN VIEWER TYPE"}
};

	/* All Alignment vlaues - used via GetLiteralString() */
LITERAL_NAME_ENTRY AlignmentTable [] =
{
	{ALIGNMENT_TOPLEFT,			"TOPLEFT"},
	{ALIGNMENT_TOPCENTER,		"TOPCENTER"},
	{ALIGNMENT_TOPRIGHT,		"TOPRIGHT"},
	{ALIGNMENT_MIDDLELEFT,		"MIDDLELEFT"},
	{ALIGNMENT_MIDDLECENTER,	"MIDDLECENTER"},
	{ALIGNMENT_MIDDLERIGHT,		"MIDDLERIGHT"},
	{ALIGNMENT_BOTTOMLEFT,		"BOTTOMLEFT"},
	{ALIGNMENT_BOTTOMCENTER,	"BOTTOMCENTER"},
	{ALIGNMENT_BOTTOMRIGHT,		"BOTTOMRIGHT"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN ALIGNMENT"}
};

	/* Repeat Values - used via GetLiteralString() */
LITERAL_NAME_ENTRY RepeatValueTable [] =
{
	{REPEAT_ONCE,	"ONCE"},
	{REPEAT_VERT,	"VERTICAL"},
	{REPEAT_HORIZ,	"HORIZONTAL"},
	{REPEAT_BOTH,	"BOTH"},
	{REPEAT_SIZE,	"SIZE"},
	{REPEAT_CENTER,	"CENTER"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN REPEAT VALUE"}
};

	/* CD Native Image Types - used via GetLiteralString() */
LITERAL_NAME_ENTRY NativeImageTable [] =
{
	{CDIMAGETYPE_GIF,		"GIF"},
	{CDIMAGETYPE_JPEG,		"JPEG"},
	{CDIMAGETYPE_BMP,		"BMP"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN IMAGE TYPE"}
};
	/* CD EXT2FIELD Preferences		*/
LITERAL_NAME_ENTRY PreferencesFromTable [] =
{
	{NPREF_CLIENT,	"CLIENT"},
	{NPREF_FIELD,	"FIELD"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN PREFERENCES TYPE"}
};

	/* CD EXT2FIELD Currency Selections		*/
LITERAL_NAME_ENTRY CurrencySelectionTable [] =
{
	{NCURFMT_COMMON,	"COMMON"},
	{NCURFMT_CUSTOM,	"CUSTOM"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN CURRENCY SELECTION"}
};

	/* CD EXT2FIELD DTYearFmt values		*/
LITERAL_NAME_ENTRY DTYearFmtValues [] =
{
	{0,             "DTYearFmt NOT SET"},
	{DT_YFMT_YY,	"YY"},
	{DT_YFMT_YYYY,	"YYYY"},
	{DT_YFMT_GE,	"GE"},
	{DT_YFMT_GEE,	"GEE"},
	{DT_YFMT_GGE,	"GGE"},
	{DT_YFMT_GGEE,	"GGEE"},
	{DT_YFMT_GGGE,	"GGGE"},
	{DT_YFMT_GGGEE,	"GGGEE"},
			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTYearFmt VALUE"}
};

	/* CD EXT2FIELD DTDOWFmt values		*/
LITERAL_NAME_ENTRY DTDOWFmtValues [] =
{
	{0,             "DTDOWFmt NOT SET"},
	{DT_WFMT_WWW,	"WWW"},
	{DT_WFMT_WWWW,	"WWWW"},
	{DT_WFMT_WWWP,	"WWWP"},
	{DT_WFMT_WWWWP,	"WWWWP"},
			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTDOWFmt VALUE"}
};

	/* CD EXT2FIELD DTMonthFmt values		*/
LITERAL_NAME_ENTRY DTMonthFmtValues [] =
{
	{0,             "DTMonthFmt NOT SET"},
	{DT_MFMT_M,		"M"},
	{DT_MFMT_MM,	"MM"},
	{DT_MFMT_MMM,	"MMM"},
	{DT_MFMT_MMMM,	"MMMM"},
			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTMonthFmt VALUE"}
};
	/* CD EXT2FIELD DTDayFmt values		*/
LITERAL_NAME_ENTRY DTDayFmtValues [] =
{
	{0,             "DTDayFmt NOT SET"},
	{DT_DFMT_D,	"D"},
	{DT_DFMT_DD,"DD"},
			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTDayFmt VALUE"}
};
	/* CD EXT2FIELD DTDShow Values	*/
LITERAL_NAME_ENTRY DTDShowValues [] =
{
	{0,             "DTDShow NOT SET"},
	{DT_DSHOW_ALL,	"ALL"},
	{DT_DSHOW_YM,	"YM"},
	{DT_DSHOW_WMD,	"WMD"},
	{DT_DSHOW_W,	"W"},
	{DT_DSHOW_M,	"M"},
	{DT_DSHOW_MD,	"MD"},
	{DT_DSHOW_MDY,	"MDY"},
	{DT_DSHOW_D,	"D"},
	{DT_DSHOW_Y,	"Y"},
			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTDShow VALUE"}
};

	/* CD EXT2FIELD  DTTShow Values		*/
LITERAL_NAME_ENTRY DTTShowValues [] =
{
	{0,             "DTTShow NOT SET"},
	{DT_TSHOW_H,	"H"},
	{DT_TSHOW_HM,	"HM"},
	{DT_TSHOW_HMS,	"HMS"},
	{DT_TSHOW_ALL,	"ALL"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN DTTShow VALUE"}
};
	/* CD Resource Types - used via GetLiteralString() */
LITERAL_NAME_ENTRY ResourceTypeTable [] =
{
	{CDRESOURCE_TYPE_EMPTY,			"EMPTY"},
	{CDRESOURCE_TYPE_URL,			"URL"},
	{CDRESOURCE_TYPE_NOTELINK,		"NOTELINK"},
	{CDRESOURCE_TYPE_NAMEDELEMENT,	"NAMEDELEMENT"},
	{CDRESOURCE_TYPE_NOTEIDLINK,	"NOTEIDLINK"},
	{CDRESOURCE_TYPE_ACTION,		"ACTION"},
	{CDRESOURCE_TYPE_NAMEDITEMELEMENT, "NAMEDITEMELEMENT"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN RESOURCE TYPE"}
};

	/* CD Resource Classes - used via GetLiteralString() */
LITERAL_NAME_ENTRY ResourceClassTable [] =
{
	{CDRESOURCE_CLASS_UNKNOWN,			"UNKNOWN"},
	{CDRESOURCE_CLASS_DOCUMENT,			"DOCUMENT"},
	{CDRESOURCE_CLASS_VIEW,				"VIEW"},
	{CDRESOURCE_CLASS_FORM,				"FORM"},
	{CDRESOURCE_CLASS_NAVIGATOR,		"NAVIGATOR"},
	{CDRESOURCE_CLASS_DATABASE,			"DATABASE"},
	{CDRESOURCE_CLASS_FRAMESET,			"FRAMESET"},
	{CDRESOURCE_CLASS_PAGE,				"PAGE"},
	{CDRESOURCE_CLASS_IMAGE,			"IMAGE"},
	{CDRESOURCE_CLASS_ICON,				"ICON"},
	{CDRESOURCE_CLASS_HELPABOUT,		"HELPABOUT"},
	{CDRESOURCE_CLASS_HELPUSING,		"HELPUSING"},
	{CDRESOURCE_CLASS_SERVER,			"SERVER"},
	{CDRESOURCE_CLASS_APPLET,			"APPLET"},
	{CDRESOURCE_CLASS_FORMULA,			"FORMULA"},
	{CDRESOURCE_CLASS_AGENT,			"AGENT"},
	{CDRESOURCE_CLASS_FILE,				"FILE"},
	{CDRESOURCE_CLASS_FILEATTACHMENT,	"FILEATTACHEMENT"},
	{CDRESOURCE_CLASS_OLEEMBEDDING,		"OLEEMBEDDING"},
	{CDRESOURCE_CLASS_SHAREDIMAGE,		"SHAREDIMAGE"},
	{CDRESOURCE_CLASS_FOLDER,			"FOLDER"},
	{CDRESOURCE_CLASS_PORTFOLIO,		"PROTFOLIO"},
	{CDRESOURCE_CLASS_OUTLINE,			"OUTLINE"},

			/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN RESOURCE CLASS"}
};

		/* CD Area Element Shape - used via GetLiteralString() */
LITERAL_NAME_ENTRY AreaShapeTable [] =
{
	{AREA_SHAPE_RECT,		"RECTANGLE"},
	{AREA_SHAPE_CIRCLE,		"CIRCLE"},
	{AREA_SHAPE_POLYGON,	"POLYGON"},
	{AREA_SHAPE_DEFAULT,	"DEFAULT"},

				/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN AREA SHAPE"}
};

		/* CD Event Action Type - used via GetLiteralString() */
LITERAL_NAME_ENTRY EventActionTable [] =
{	
	{ACTION_TYPE_FORMULA,		"FORMULA"},
	{ACTION_TYPE_CANNED_ACTION,	"CANNED_ACTION"},
	{ACTION_TYPE_LOTUS_SCRIPT,	"LOTUS_SCRIPT"},
	{ACTION_TYPE_JAVASCRIPT,	"JAVASCRIPT"},

				/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN EVENT ACTION TYPE"}
};
	
	/* CD Event HTML Event - used via GetLiteralString() */
LITERAL_NAME_ENTRY  EventHTMLTable [] =
{
	{HTML_EVENT_ONCLICK,		"ONCLICK"},
	{HTML_EVENT_ONDBLCLICK,		"ONDBLCLICK"},
	{HTML_EVENT_ONMOUSEDOWN,	"ONMOUSEDOWN"},
	{HTML_EVENT_ONMOUSEUP,		"ONMOUSEUP"},
	{HTML_EVENT_ONMOUSEOVER,	"ONMOUSEOVER"},
	{HTML_EVENT_ONMOUSEMOVE,	"ONMOUSEMOVE"},
	{HTML_EVENT_ONMOUSEOUT,		"ONMOUSEOUT"},
	{HTML_EVENT_ONKEYPRESS,		"ONKEYPRESS"},
	{HTML_EVENT_ONKEYDOWN,		"ONKEYDOWN"},
	{HTML_EVENT_ONKEYUP,		"ONKEYUP"},
	{HTML_EVENT_ONFOCUS,		"ONFOCUS"},
	{HTML_EVENT_ONBLUR,			"ONBLUR"},
	{HTML_EVENT_ONLOAD,			"ONLOAD"},
	{HTML_EVENT_ONUNLOAD,		"ONUNLOAD"},
	{HTML_EVENT_HEADER,			"HEADER"},
	{HTML_EVENT_ONSUBMIT,		"ONSUBMIT"},
	{HTML_EVENT_ONRESET,		"ONRESET"},
	{HTML_EVENT_ONCHANGE,		"ONCHANGE"},
	{HTML_EVENT_ONERROR,		"ONERROR"},
	{HTML_EVENT_ONHELP,			"ONHELP"},
	{HTML_EVENT_ONSELECT,		"ONSELECT"},

		/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN HTML EVENT"}
};
	/* CD Embedded Control Types - used via GetLiteralString() */
LITERAL_NAME_ENTRY  EmbeddedCtlTypes [] =
{
	{EMBEDDEDCTL_EDIT,		"EDIT"},
	{EMBEDDEDCTL_COMBO,		"COMBO"},
	{EMBEDDEDCTL_LIST,		"LIST"},
	{EMBEDDEDCTL_TIME,		"TIME"},
	{EMBEDDEDCTL_KEYGEN,	"KEYGEN"},
	{EMBEDDEDCTL_FILE,		"FILE"},

	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN EMBEDDED CONTROL TYPE"}
};
	/* CD Transition Types - used via GetLiteralString() */
LITERAL_NAME_ENTRY  TransitionTypes [] =
{
	{TRANS_LEFTTORIGHT_COLUMN,	"LEFTTORIGHT_COLUMN"},
	{TRANS_ROLLING,				"ROLLING"},
	{TRANS_TOPTOBOTTOM_ROW,		"TOPTOBOTTOM_ROW"},
	{TRANS_WIPE,				"WIPE"},
	{TRANS_BOXES_INCREMENT,		"BOXES_INCREMENT"},
	{TRANS_EXPLODE,				"EXPLODE"},
	{TRANS_DISSOLVE,			"DISSOLVE"},
/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN TRANSITION TYPE"}
};

	/* ScrollBarStyle for CDFRAME used via GetLiteralString() */
LITERAL_NAME_ENTRY  ScrollStyle [] =
{
	{ALWAYS_ScrollStyle,	"SCROLLING = ALWAYS"},
	{NEVER_ScrollStyle,		"SCROLLING = NEVER"},
	{AUTO_ScrollStyle,		"SCROLLING = AUTO"},
	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN SCROLLING TYPE"}
};
	/*  FRAMESETLENGTH types used via GetLiteralString() */
LITERAL_NAME_ENTRY  FrameSetLengthType [] =
{
	{PIXELS_LengthType,		"LengthType = PIXELS"},
	{PERCENTAGE_LengthType,	"LengthType = PERCENTAGE"},
	{RELATIVE_LengthType,	"LengthType = RELATIVE"},
	/* This must be the last entry! */
	{LITERAL_TABLE_END,			"UNKNOWN LengthType"}
};
LITERAL_NAME_ENTRY SignatureTypeTable [] =
{
	{SIG_CD_FRAME,				"CD_FRAME"},
	{SIG_CD_FRAMESET,			"CD_FRAMESET"},
	{SIG_CD_FRAMESETHEADER,		"CD_FRAMESETHEADER"},
	{SIG_CD_CAPTION,			"CD_CAPTION"},
	{SIG_CD_LINKCOLORS,			"CD_LINKCOLORS"},
	{SIG_CD_TABLECELL_HREF,		"CD_TABLECELL_HREF"},
	{SIG_CD_ACTIONBAREXT,		"CD_ACTIONBAREXT"},
	{SIG_CD_IDNAME,				"CD_IDNAME"},
	{SIG_CD_TABLECELL_IDNAME,	"CD_TABLECELL_IDNAME"},
	{SIG_CD_IMAGESEGMENT,		"CD_IMAGESEGMENT"},
	{SIG_CD_IMAGEHEADER,		"CD_IMAGEHEADER"},
	{SIG_CD_V5HOTSPOTBEGIN,		"CD_V5HOTSPOTBEGIN"},
	{SIG_CD_V5HOTSPOTEND,		"CD_V5HOTSPOTEND"},
	{SIG_CD_PARAGRAPH,			"CD_PARAGRAPH"},
	{SIG_CD_PABDEFINITION,		"CD_PABDEFINITION"},
	{SIG_CD_PABREFERENCE,		"CD_PABREFERENCE"},
	{SIG_CD_TEXT,				"CD_TEXT"},
	{SIG_CD_HEADER,				"CD_HEADER"},
	{SIG_CD_LINKEXPORT2,		"CD_LINKEXPORT2"},
	{SIG_CD_BITMAPHEADER,		"CD_BITMAPHEADER"},
	{SIG_CD_BITMAPSEGMENT,		"CD_BITMAPSEGMENT"},
	{SIG_CD_COLORTABLE,			"CD_COLORTABLE"},
	{SIG_CD_GRAPHIC,			"CD_GRAPHIC"},
	{SIG_CD_PMMETASEG,			"CD_PMMETASEG"},
	{SIG_CD_WINMETASEG,			"CD_WINMETASET"},
	{SIG_CD_MACMETASEG,			"CD_MACMETASEG"},
	{SIG_CD_CGMMETA,			"CD_CGMMETA"},
	{SIG_CD_PMMETAHEADER,		"CD_PMMETAHEADER"},
	{SIG_CD_WINMETAHEADER,		"CD_WINMETAHEADER"},
	{SIG_CD_MACMETAHEADER,		"CD_MACMETAHEADER"},
	{SIG_CD_TABLEBEGIN,			"CD_TABLEBEGIN"},
	{SIG_CD_TABLECELL,			"CD_TABLECELL"},
	{SIG_CD_TABLEEND,			"CD_TABLEEND"},
	{SIG_CD_STYLENAME,			"CD_STYLENAME"},
	{SIG_CD_STORAGELINK,		"CD_STORAGELINK"},
	{SIG_CD_TRANSPARENTTABLE,	"CD_TRANSPARENTTABLE"},
	{SIG_CD_HORIZONTALRULE,		"CD_HORIZONTALRULE"},
	{SIG_CD_ALTTEXT,			"CD_ALTTEXT"},
	{SIG_CD_ANCHOR,				"CD_ANCHOR"},
	{SIG_CD_HTMLBEGIN,			"CD_HTMLBEGIN"},
	{SIG_CD_HTMLEND,			"CD_HTMLEND"},
	{SIG_CD_HTMLFORMULA,		"CD_HTMLFORMULA"},
	{SIG_CD_NESTEDTABLEBEGIN,	"CD_NESTEDTABLEBEGIN"},
	{SIG_CD_NESTEDTABLECELL,	"CD_NESTEDTABLECELL"},
	{SIG_CD_NESTEDTABLEEND,		"CD_NESTEDTABLEEND"},
	{SIG_CD_COLOR,				"CD_COLOR"},
	{SIG_CD_TABLECELL_COLOR,	"CD_TABLECELL_COLOR"},
	{SIG_CD_BLOBPART,			"CD_BLOBPART"},
	{SIG_CD_BEGIN,				"CD_BEGIN"},
	{SIG_CD_END,				"CD_END"},
	{SIG_CD_VERTICALALIGN,		"CD_VERTICALALIGN"},
	{SIG_CD_FLOATPOSITION,		"CD_FLOATPOSITION"},
	{SIG_CD_TIMERINFO,			"CD_TIMERINFO"},
	{SIG_CD_TABLEROWHEIGHT,		"CD_TABLEROWHEIGHT"},
	{SIG_CD_TABLELABEL,			"CD_TABLELABEL"},
	{SIG_CD_BIDI_TEXT,			"CD_BIDI_TEXT"},
	{SIG_CD_BIDI_TEXTEFFECT,	"CD_BIDI_TEXTEFFECT"},
	{SIG_CD_REGIONBEGIN,		"CD_REGIONBEGIN"},
	{SIG_CD_REGIONEND,			"CD_REGIONEND"},
	{SIG_CD_TRANSITION,			"CD_TRANSITION"},
	{SIG_CD_PLACEHOLDER,		"CD_PLACEHOLDER"},
	{SIG_CD_EMBEDDEDOUTLINE,	"CD_EMBEDDEDOUTLINE"},
	{SIG_CD_EMBEDDEDVIEW,		"CD_EMBEDDEDVIEW"},
	{SIG_CD_CELLBACKGROUNDDATA,	"CD_CELLBACKGROUNDDATA"},
	{SIG_CD_TARGET,				"CD_TARGET"},
	{SIG_CD_MAPELEMENT,			"CD_MAPELEMENT"},
	{SIG_CD_AREAELEMENT,		"CD_AREAELEMENT"},
	{SIG_CD_HREF,				"CD_HREF"},
	{SIG_CD_EMBEDDEDCTL,		"CD_EMBEDDEDCTL"},
	{SIG_CD_HTML_ALTTEXT,		"CD_HTML_ALTTEXT"},
	{SIG_CD_EVENT,				"CD_EVENT"},
	{SIG_CD_PRETABLEBEGIN,		"CD_PRETABLEBEGIN"},
	{SIG_CD_BORDERINFO,			"CD_BORDERINFO"},
	{SIG_CD_EMBEDDEDSCHEDCTL,	"CD_EMBEDDEDSCHEDCTL"},
	{SIG_CD_EXT2_FIELD,			"CD_EXT2_FIELD"},
	{SIG_CD_DOCUMENT_PRE_26,	"CD_DOCUMENT_PRE_26"},
	{SIG_CD_FIELD_PRE_36,		"CD_FIELD_PRE_36"},
	{SIG_CD_FIELD,				"CD_FIELD"},
	{SIG_CD_DOCUMENT,			"CD_DOCUMENT"},
	{SIG_CD_METAFILE,			"CD_METAFILE"},
	{SIG_CD_BITMAP,				"CD_BITMAP"},
	{SIG_CD_FONTTABLE,			"CD_FONTTABLE"},
	{SIG_CD_LINK,				"CD_LINK"},
	{SIG_CD_LINKEXPORT,			"CD_LINKEXPORT"},
	{SIG_CD_KEYWORD,			"CD_KEYWORD"},
	{SIG_CD_LINK2,				"CD_LINK2"},
	{SIG_CD_CGM,				"CD_CGM"},
	{SIG_CD_TIFF,				"CD_TIFF"},
	{SIG_CD_PATTERNTABLE,		"CD_PATTERNTABLE"},
	{SIG_CD_DDEBEGIN,			"CD_DDEBEGIN"},
	{SIG_CD_DDEEND,				"CD_DDEEND"},
	{SIG_CD_OLEBEGIN,			"CD_OLEBEGIN"},
	{SIG_CD_OLEEND,				"CD_OLEEND"},
	{SIG_CD_HOTSPOTBEGIN,		"CD_HOTSPOTBEGIN"},
	{SIG_CD_HOTSPOTEND,			"CD_HOTSPOTEND"},
	{SIG_CD_BUTTON,				"CD_BUTTON"},
	{SIG_CD_BAR,				"CD_BAR"},
	{SIG_CD_V4HOTSPOTBEGIN,		"CD_V4HOTSPOTBEGIN"},
	{SIG_CD_V4HOTSPOTEND,		"CD_V4HOTSPOTEND"},
	{SIG_CD_EXT_FIELD,			"CD_EXT_FIELD"},
	{SIG_CD_LSOBJECT,			"CD_LSOBJECT"},
	{SIG_CD_HTMLHEADER,			"CD_HTMLHEADER"},
	{SIG_CD_HTMLSEGMENT,		"CD_HTMLSEGMENT"},
	{SIG_CD_LAYOUT,				"CD_LAYOUT"},
	{SIG_CD_LAYOUTFIELD,		"CD_LAYOUTFIELD"},
	{SIG_CD_PABHIDE,			"CD_PABHIDE"},
	{SIG_CD_PABFORMREF,			"CD_PABFORMREF"},
	{SIG_CD_ACTIONBAR,			"CD_ACTIONBAR"},
	{SIG_CD_ACTION,				"CD_ACTION"},
	{SIG_CD_DOCAUTOLAUNCH,		"CD_DOCAUTOLAUNCH"},
	{SIG_CD_LAYOUTGRAPHIC,		"CD_LAYOUTGRAPHIC"},
	{SIG_CD_OLEOBJINFO,			"CD_OLEOBJINFO"},
	{SIG_CD_LAYOUTBUTTON,		"CD_LAYOUTBUTTON"},
	{SIG_CD_TEXTEFFECT,			"CD_TEXTEFFECT"},
	{SIG_QUERY_HEADER,			"QUERY_HEADER"},
	{SIG_QUERY_TEXTTERM,		"QUERY_TEXTTERM"},
	{SIG_QUERY_BYFIELD,			"QUERY_BYFIELD"},
	{SIG_QUERY_BYDATE,			"QUERY_BYDATE"},
	{SIG_QUERY_BYAUTHOR,		"QUERY_BYAUTHOR"},
	{SIG_QUERY_FORMULA,			"QUERY_FORMULA"},
	{SIG_QUERY_BYFORM,			"QUERY_BYFORM"},
	{SIG_QUERY_BYFOLDER,		"QUERY_BYFOLDER"},
	{SIG_QUERY_USESFORM,		"QUERY_USESFORM"},
	{SIG_QUERY_TOPIC,			"QUERY_TOPIC"},
	{SIG_ACTION_HEADER,			"ACTION_HEADER"},
	{SIG_ACTION_MODIFYFIELD,	"ACTION_MODIFYFIELD"},
	{SIG_ACTION_REPLY,			"ACTION_REPLY"},
	{SIG_ACTION_FORMULA,		"ACTION_FORMULA"},
	{SIG_ACTION_LOTUSSCRIPT,	"ACTION_LOTUSSCRIPT"},
	{SIG_ACTION_SENDMAIL,		"ACTION_SENDMAIL"},
	{SIG_ACTION_DBCOPY,			"ACTION_DBCOPY"},
	{SIG_ACTION_DELETE,			"ACTION_DELETE"},
	{SIG_ACTION_BYFORM,			"ACTION_BYFORM"},
	{SIG_ACTION_MARKREAD,		"ACTION_MARKREAD"},
	{SIG_ACTION_MARKUNREAD,		"ACTION_MARKUNREAD"},
	{SIG_ACTION_MOVETOFOLDER,	"ACTION_MOVETOFOLDER"},
	{SIG_ACTION_COPYTOFOLDER,	"ACTION_COPYTOFOLDER"},
	{SIG_ACTION_REMOVEFROMFOLDER,"ACTION_REMOVEFROMFOLDER"},
	{SIG_ACTION_NEWSLETTER,		"ACTION_NEWSLETTER"},
	{SIG_ACTION_RUNAGENT,		"ACTION_RUNAGENT"},
	{SIG_ACTION_SENDDOCUMENT,	"ACTION_SENDDOCUMENT"},
	{SIG_ACTION_FORMULAONLY,	"ACTION_FORMULAONLY"},
	{SIG_ACTION_JAVAAGENT,		"ACTION_JAVVAGENT"},
	{SIG_ACTION_JAVA,			"ACTION_JAVA"},
	{SIG_VIEWMAP_DATASET,		"VIEWMAP_DATASET"},
	{SIG_CD_VMHEADER,			"CD_VMHEADER"},
	{SIG_CD_VMBITMAP,			"CD_VMBITMAP"},
	{SIG_CD_VMPOLYGON_BYTE,		"CD_VMPOLYGON_BYTE"},
	{SIG_CD_VMPOLYLINE_BYTE,	"CD_VMPOLYLINE_BYTE"},
	{SIG_CD_VMREGION,			"CD_VMREGION"},
	{SIG_CD_VMACTION,			"CD_VMACTION"},
	{SIG_CD_VMELLIPSE,			"CD_VMELLIPSE"},
	{SIG_CD_VMRNDRECT,			"CD_VMRNDRECT"},
	{SIG_CD_VMBUTTON,			"CD_VMBUTTON"},
	{SIG_CD_VMACTION_2,			"CD_VMACTION_2"},
	{SIG_CD_VMTEXTBOX,			"CD_VMTEXTBOX"},
	{SIG_CD_VMPOLYGON,			"CD_VMPOLYGON"},
	{SIG_CD_VMPOLYLINE,			"CD_VMPOLYLINE"},
	{SIG_CD_VMPOLYRGN,			"CD_VMPOLYRGN"},
	{SIG_CD_VMCIRCLE,			"CD_VMCIRCLE"},
	{SIG_CD_VMPOLYRGN_BYTE,		"CD_VMPOLYRGN_BYTE"},
	{SIG_CD_ALTERNATEBEGIN,		"CD_ALTERNATEBEGIN"},
	{SIG_CD_ALTERNATEEND,		"CD_ALTERNATEEND"},
	{SIG_CD_OLERTMARKER,		"CD_OLERTMARKER"},
	{SIG_CD_ACTIONEXT,			"CD_ACTIONEXT"},
	{SIG_CD_EXT_EMBEDDEDSCHED,	"CD_EXT_EMBEDDEDSCHED"},
	{SIG_CD_INLINE,			    "CD_INLINE"},
	{SIG_CD_EMBEDDEDCALCTL,		"CD_EMBEDDEDCALCTL"},
	{SIG_CD_POSITIONING,		"CD_POSITIONING"},
	{SIG_CD_LAYER,				"CD_LAYER"},
	{SIG_CD_BOXSIZE,			"CD_BOXSIZE"},
	{SIG_CD_BACKGROUNDPROPERTIES,	"CD_BACKGROUNDPROPERTIES"},
	{SIG_CD_EVENT_LANGUAGE_ENTRY, "CD_EVENT_LANGUAGE_ENTRY"},
	{SIG_CD_FILEHEADER,			"CD_FILEHEADER"},
	{SIG_CD_FILESEGMENT,		"CD_FILESEGMENT"},
	{SIG_CD_DECSFIELD,			"CD_DECSFIELD"},
	{SIG_CD_TEXTPROPERTIESTABLE,"CD_TEXTPROPERTIESTABLE"},
	{SIG_CD_SPAN_BEGIN,			"CD_SPAN_BEGIN"},
	{SIG_CD_SPAN_END,			"CD_SPAN_END"},
	{SIG_CD_EMBEDDEDEDITCTL,	"CD_EMBEDDEDEDITCTL"},
	{SIG_CD_TEXTPROPERTY,		"CD_TEXTPROPERTY"},
	{SIG_CD_HREF2,				"CD_HREF2"},
	{SIG_CD_BACKGROUNDCOLOR,	"CD_BACKGROUNDCOLOR"},
	{SIG_CD_V6HOTSPOTBEGIN_CONTINUATION,	"CD_V6HOTSPOTBEGIN_CONTINUATION"}, 		 	
	{SIG_CD_CLIENT_BLOBPART,	"CD_CLIENT_BLOBPART"},	
	{SIG_CD_CLIENT_EVENT,		"CD_CLIENT_EVENT"},	
	{SIG_CD_HREFBORDER,			"CD_HREFBORDER"},
	{SIG_CD_DATAFLAGS,			"CD_DATAFLAGS"},
	{SIG_CD_FIELDHINT,			"CD_FIELDHINT"},
	{SIG_CD_TABLECELL_HREF2,	"CD_TABLECELL_HREF2"},
	{SIG_CD_LARGE_PARAGRAPH,	"CD_LARGEPARAGRAPH"},
	{SIG_CD_IGNORE,				"CD_IGNORE"},
	{SIG_CD_TABLEDATAEXTENSION,	"CD_TABLEDATAEXTENSION"},
	/*	This must be the last entry in the list */
	{LITERAL_TABLE_END,             "UNKNOWN SIGNATURE"}
};

	/* All CDVERTICALALIGN values - used via GetLiteralString() */
LITERAL_NAME_ENTRY VerticalAlignValues [] =
{
	{VERTICAL_ALIGNMENT_BASELINE,	"BASELINE"},
	{VERTICAL_ALIGNMENT_CENTER,		"CENTER"},
	{VERTICAL_ALIGNMENT_TOP,		"TOP"},
	{VERTICAL_ALIGNMENT_BOTTOM,		"BOTTOM"},

	/*	This must be the last entry in the list */
	{LITERAL_TABLE_END,             "UNKNOWN ALIGNMENT"}
};
/************************************************************************

    FUNCTION:   DumpOneCDRecord

    PURPOSE:    Dump one Compound Text (CD) Record

    ALGORITHM:  This is the action routine for EnumCompositeBuffer
		specified in DumpOneItem().

    INPUTS:
	 char      *RecordPtr       -   pointer to start of CD record data
					This data is in Canonical format.
	 WORD       RecordType      -   CD record type (SIG_CD_*)
	 DWORD      RecordLength    -   length of CD record
	 void far * Unused

*************************************************************************/

#ifdef OS400
extern "C"
#endif

STATUS  LNPUBLIC  DumpOneCDRecord( char   *RecordPtr,
				     WORD    RecordType,
				     DWORD   RecordLength,
				     void   *Unused )
{
    fprintf( dumpfile,"  CD Record : %ld\n", ++dwCDRecord );
    fprintf( dumpfile,"   Record Length = %ld bytes.\n", RecordLength );
    fprintf( dumpfile,"   Record Type   = " );

    switch (RecordType)
    {
	case SIG_CD_PARAGRAPH:
	    DumpCDParagraph( RecordPtr, RecordLength );
	    break;

	case SIG_CD_PABDEFINITION:
	    DumpCDPabdefinition( RecordPtr, RecordLength );
	    break;

	case SIG_CD_PABREFERENCE:
	    DumpCDPabreference( RecordPtr, RecordLength );
	    break;

	case SIG_CD_TEXT:
    case SIG_CD_BIDI_TEXT: /* New for R5.0 */
	    DumpCDText( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_HEADER:
	    DumpCDHeader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_LINKEXPORT2:
	    DumpCDLinkexport2( RecordPtr, RecordLength );
	    break;

	case SIG_CD_BITMAPHEADER:
	    DumpCDBitmapheader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_BITMAPSEGMENT:
	    DumpCDBitmapsegment( RecordPtr, RecordLength );
	    break;

	case SIG_CD_COLORTABLE:
	    DumpCDColortable( RecordPtr, RecordLength );
	    break;

	case SIG_CD_GRAPHIC:
	    DumpCDGraphic( RecordPtr, RecordLength );
	    break;

	case SIG_CD_PMMETASEG:
	    DumpCDPmmetaseg( RecordPtr, RecordLength );
	    break;

	case SIG_CD_WINMETASEG:
	    DumpCDWinmetaseg( RecordPtr, RecordLength );
	    break;

	case SIG_CD_MACMETASEG:
	    DumpCDMacmetaseg( RecordPtr, RecordLength );
	    break;

	case SIG_CD_CGMMETA:
	    DumpCDCgmmeta( RecordPtr, RecordLength );
	    break;

	case SIG_CD_PMMETAHEADER:
	    DumpCDPmmetaheader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_WINMETAHEADER:
	    DumpCDWinmetaheader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_MACMETAHEADER:
	    DumpCDMacmetaheader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_TABLEBEGIN:
	case SIG_CD_NESTEDTABLEBEGIN: /* New for R5.0 */
	    DumpCDTablebegin( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_TABLECELL:
	case SIG_CD_NESTEDTABLECELL:  /* New for R5.0 */
	    DumpCDTablecell( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_TABLEEND:
	case SIG_CD_NESTEDTABLEEND:   /* New for R5.0 */
	    DumpCDTableend( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_STYLENAME:
	    DumpCDStylename( RecordPtr, RecordLength );
	    break;

	case SIG_CD_FIELD_PRE_36:
	    DumpCDField( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_FIELD:
	    DumpCDField( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_DOCUMENT:
	    DumpCDDocument( RecordPtr, RecordLength );
	    break;

	case SIG_CD_METAFILE:
	    DumpCDMetafile( RecordPtr, RecordLength );
	    break;

	case SIG_CD_BITMAP:
	    DumpCDBitmap( RecordPtr, RecordLength );
	    break;

	case SIG_CD_FONTTABLE:
	    DumpCDFonttable( RecordPtr, RecordLength );
	    break;

	case SIG_CD_LINK:
	    DumpCDLink( RecordPtr, RecordLength );
	    break;

	case SIG_CD_LINKEXPORT:
	    DumpCDLinkexport( RecordPtr, RecordLength );
	    break;

	case SIG_CD_KEYWORD:
	    DumpCDKeyword( RecordPtr, RecordLength );
	    break;

	case SIG_CD_LINK2:
	    DumpCDLink2( RecordPtr, RecordLength );
	    break;

	case SIG_CD_CGM:
	    DumpCDCgm( RecordPtr, RecordLength );
	    break;

	case SIG_CD_TIFF:
	    DumpCDTiff( RecordPtr, RecordLength );
	    break;

	case SIG_CD_PATTERNTABLE:
	    DumpCDPatterntable( RecordPtr, RecordLength );
	    break;

	case SIG_CD_DDEBEGIN:
	    DumpCDDdebegin( RecordPtr, RecordLength );
	    break;

	case SIG_CD_DDEEND:
	    DumpCDDdeend( RecordPtr, RecordLength );
	    break;

	case SIG_CD_OLEBEGIN:
	    DumpCDOlebegin( RecordPtr, RecordLength );
	    break;

	case SIG_CD_OLEEND:
	    DumpCDOleend( RecordPtr, RecordLength );
	    break;

	case SIG_CD_HOTSPOTBEGIN:
	case SIG_CD_V4HOTSPOTBEGIN: /* New for R4.0 */
	case SIG_CD_V5HOTSPOTBEGIN: /* New for R5.0 */
	case SIG_CD_V6HOTSPOTBEGIN_CONTINUATION: /* New for Notes/Domino 6 */
	    DumpCDHotspotbegin( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_HOTSPOTEND:
	case SIG_CD_V4HOTSPOTEND: /* New for R4.0 */
	case SIG_CD_V5HOTSPOTEND: /* New for R5.0 */
	    DumpCDHotspotend( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_BUTTON:
	    DumpCDButton( RecordPtr, RecordLength );
	    break;

		/* Records added in Release 4.0 */
	case SIG_CD_BAR:
		DumpCDBar( RecordPtr, RecordLength );
		break;

	case SIG_CD_EXT_FIELD:
		DumpCDExtfield( RecordPtr, RecordLength );
		break;

	case SIG_CD_PABHIDE:
		DumpCDPabhide( RecordPtr, RecordLength );
		break;

	case SIG_CD_PABFORMREF:
		DumpCDPabformref( RecordPtr, RecordLength );
		break;

		/* Records added in Release 4.5 */
	case SIG_CD_LAYOUT:
		DumpCDLayout( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYOUTEND:
		DumpCDLayoutEnd( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYOUTTEXT:
		DumpCDLayoutText( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYOUTFIELD:
		DumpCDLayoutField( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYOUTGRAPHIC:
		DumpCDLayoutGraphic( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYOUTBUTTON:
		DumpCDLayoutButton( RecordPtr, RecordLength );
		break;

	case SIG_CD_TEXTEFFECT:
	case SIG_CD_BIDI_TEXTEFFECT:  /* New for R5.0 */
		DumpCDTextEffect( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_TRANSPARENTTABLE:
		DumpCDTransparentTable( RecordPtr, RecordLength );
		break;

	case SIG_CD_STORAGELINK:
		DumpCDStorageLink( RecordPtr, RecordLength );
		break;

	case SIG_CD_ACTION:
		DumpCDAction( RecordPtr, RecordLength );
		break;

	case SIG_CD_ACTIONBAR:
		DumpCDActionbar( RecordPtr, RecordLength );
		break;

	case SIG_CD_DOCAUTOLAUNCH:
		DumpCDDocautolaunch( RecordPtr, RecordLength );
		break;

	case SIG_CD_OLEOBJINFO:
		DumpCDOleObjInfo( RecordPtr, RecordLength );
		break;

		/* Records added in Release 4.6 */
	case SIG_CD_ANCHOR:
		DumpCDAnchor( RecordPtr, RecordLength );
		break;

	case SIG_CD_ALTTEXT:
	case SIG_CD_HTML_ALTTEXT: /* New for R5.0 */
		DumpCDAltText( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_OLERTMARKER:
		DumpCDOleRTMarker( RecordPtr, RecordLength );
		break;

	case SIG_CD_ALTERNATEBEGIN:
		DumpCDAlternateBegin( RecordPtr, RecordLength );
		break;

	case SIG_CD_ALTERNATEEND:
		DumpCDAlternateEnd( RecordPtr, RecordLength );
		break;

	case SIG_CD_HORIZONTALRULE:
		DumpCDHRule( RecordPtr, RecordLength );
		break;

	case SIG_CD_HTMLBEGIN:
		DumpCDHtmlBegin( RecordPtr, RecordLength );
		break;

	case SIG_CD_HTMLEND:
		DumpCDHtmlEnd( RecordPtr, RecordLength );
		break;

	case SIG_CD_HTMLFORMULA:
		DumpCDHtmlFormula( RecordPtr, RecordLength );
		break;

	case SIG_CD_HTMLHEADER:
		DumpCDHtmlHeader( RecordPtr, RecordLength );
		break;

	case SIG_CD_HTMLSEGMENT:
		DumpCDHtmlSegment( RecordPtr, RecordLength );
		break;

	case SIG_CD_LSOBJECT:
		DumpCDLSObject( RecordPtr, RecordLength );
		break;

	/* Records added in R5.0 */
	case SIG_CD_COLOR:
	case SIG_CD_TABLECELL_COLOR:
	case SIG_CD_BACKGROUNDCOLOR:  /* New for Notes/Domino 6 */
		DumpCDColor( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_BEGIN:
		DumpCDBeginRecord( RecordPtr, RecordLength );
		break;

	case SIG_CD_END:
		DumpCDEndRecord( RecordPtr, RecordLength );
		break;

	case SIG_CD_VERTICALALIGN:
		DumpCDVerticalAlign( RecordPtr, RecordLength );
		break;

	case SIG_CD_FLOATPOSITION:
		DumpCDFloat( RecordPtr, RecordLength );
		break;

	case SIG_CD_TIMERINFO:
		DumpCDTimerInfo( RecordPtr, RecordLength );
		break;

	case SIG_CD_TABLEROWHEIGHT:
		DumpCDTableRowHeight( RecordPtr, RecordLength );
		break;

	case SIG_CD_TABLELABEL:
		DumpCDTableLabel( RecordPtr, RecordLength );
		break;

	case SIG_CD_REGIONBEGIN:
		DumpCDRegionBegin( RecordPtr, RecordLength );
		break;

	case SIG_CD_REGIONEND:
		DumpCDRegionEnd( RecordPtr, RecordLength );
		break;

	case SIG_CD_TRANSITION:
		DumpCDTransition( RecordPtr, RecordLength );
		break;

	case SIG_CD_EMBEDDEDOUTLINE:
		DumpCDEmbeddedOutline( RecordPtr, RecordLength );
		break;

	case SIG_CD_EMBEDDEDVIEW:
		DumpCDEmbeddedView( RecordPtr, RecordLength );
		break;

	case SIG_CD_CELLBACKGROUNDDATA:
		DumpCDCellBackgroundData( RecordPtr, RecordLength );
		break;

	case SIG_CD_TARGET:
		DumpCDTarget( RecordPtr, RecordLength );
		break;

	case SIG_CD_MAPELEMENT:
		DumpCDMapElement( RecordPtr, RecordLength );
		break;

	case SIG_CD_AREAELEMENT:
		DumpCDAreaElement( RecordPtr, RecordLength );
		break;

	case SIG_CD_HREF:
	case SIG_CD_TABLECELL_HREF:
	case SIG_CD_HREF2: /* New for Notes/Domino 6 */
	case SIG_CD_HREFBORDER: /* New for Notes/Domino 6 */
	case SIG_CD_TABLECELL_HREF2: /* New for Notes/Domino 6 */
		DumpCDResource( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_EMBEDDEDCTL:
		DumpCDEmbeddedCtl( RecordPtr, RecordLength );
		break;

	case SIG_CD_EVENT:
	case SIG_CD_CLIENT_EVENT: /* New for Notes/Domino 6 */
		DumpCDEvent( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_IDNAME:
	case SIG_CD_TABLECELL_IDNAME:
		DumpCDIDName( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_PRETABLEBEGIN:
		DumpCDPreTableBegin( RecordPtr, RecordLength );
		break;

	case SIG_CD_BORDERINFO:
		DumpCDBorderInfo( RecordPtr, RecordLength );
		break;

	case SIG_CD_EMBEDDEDSCHEDCTL:
		DumpCDEmbeddedSchedCtl( RecordPtr, RecordLength );
		break;

	case SIG_CD_EXT2_FIELD:
		DumpCDExt2Field( RecordPtr, RecordLength );
		break;

	case SIG_CD_ACTIONBAREXT:
		DumpCDActionBarExt( RecordPtr, RecordLength );
		break;

	case SIG_CD_IMAGESEGMENT:
		DumpCDImageSegment( RecordPtr, RecordLength );
		break;

	case SIG_CD_IMAGEHEADER:
		DumpCDImageHeader( RecordPtr, RecordLength );
		break;

	case SIG_CD_BLOBPART:
	case SIG_CD_CLIENT_BLOBPART: /* new in Notes/Domino 6 */
		DumpCDBlobPart( RecordPtr, RecordLength, RecordType );
		break;

	case SIG_CD_PLACEHOLDER:
		DumpCDPlaceHolder ( RecordPtr, RecordLength );
		break;

	case SIG_CD_LINKCOLORS:
		DumpCDLinkColors ( RecordPtr, RecordLength );
		break;

	case SIG_CD_CAPTION:
		DumpCDCaption ( RecordPtr, RecordLength );
		break;

	/* Records added in Release 5.0.1 */
	case SIG_CD_FRAME:
		DumpCDFrame ( RecordPtr, RecordLength );
		break;

	case SIG_CD_FRAMESET:
		DumpCDFrameSet ( RecordPtr, RecordLength );
		break;

	case SIG_CD_FRAMESETHEADER:
		DumpCDFrameSetHeader( RecordPtr, RecordLength );
		break;

	/* Records added in Notes/Domino 6 */

	case SIG_CD_ACTIONEXT:
		DumpCDActionExt( RecordPtr, RecordLength );
		break;

	case SIG_CD_EXT_EMBEDDEDSCHED:
		DumpCDEmbeddedSchedCtlExtra( RecordPtr, RecordLength );
		break;

	case SIG_CD_INLINE:
		DumpCDInline( RecordPtr, RecordLength );
		break;

	case SIG_CD_EMBEDDEDCALCTL:
		DumpCDEmbeddedCalCtl( RecordPtr, RecordLength );
		break;

	case SIG_CD_LAYER:
	    DumpCDLayer( RecordPtr, RecordLength );
	    break;

	case SIG_CD_POSITIONING:
	    DumpCDPositioning( RecordPtr, RecordLength );
	    break;

	case SIG_CD_BOXSIZE:
	    DumpCDBoxSize( RecordPtr, RecordLength );
	    break;

	case SIG_CD_BACKGROUNDPROPERTIES:
	    DumpCDBackgroundProperties( RecordPtr, RecordLength );
	    break;

	case SIG_CD_EVENT_LANGUAGE_ENTRY:
	    DumpCDEventEntry( RecordPtr, RecordLength );
	    break;
	
	case SIG_CD_TEXTPROPERTIESTABLE:
		DumpCDTextPropertiesTable ( RecordPtr, RecordLength );
		break;

	case SIG_CD_FILEHEADER:
	    DumpCDFileHeader( RecordPtr, RecordLength );
	    break;

	case SIG_CD_FILESEGMENT:
	    DumpCDFileSegment( RecordPtr, RecordLength );
	    break;

	case SIG_CD_DECSFIELD:
	    DumpCDDECSField( RecordPtr, RecordLength );
	    break;

	case SIG_CD_SPAN_BEGIN:
	case SIG_CD_SPAN_END:
	    DumpCDSpanRecord( RecordPtr, RecordLength, RecordType );
	    break;

	case SIG_CD_EMBEDDEDEDITCTL:
		DumpCDEmbeddedEditCtl( RecordPtr, RecordLength );
		break;

	case SIG_CD_TEXTPROPERTY:
		DumpCDTextProperty ( RecordPtr, RecordLength );
		break;

	case SIG_CD_DATAFLAGS:
		DumpCDDataFlags ( RecordPtr, RecordLength );
		break;

	case SIG_CD_FIELDHINT:
		DumpCDFieldHint ( RecordPtr, RecordLength );
		break;

	case SIG_CD_LARGE_PARAGRAPH:
		DumpCDLargeParagraph ( RecordPtr, RecordLength );
		break;

	case SIG_CD_TABLEDATAEXTENSION:
		DumpCDTableDataExtension ( RecordPtr, RecordLength );
		break;

	case SIG_CD_IGNORE:
		DumpCDIgnore ( RecordPtr, RecordLength );
		break;

	default:
	    fprintf( dumpfile, "Unidentified.\n");
	    fprintf( dumpfile, "    Unknown Type = 0x%X.\n", RecordType );
	    NSFDDUMPDumpMemory( RecordPtr, (WORD) RecordLength );
	    break;
   }
   return NOERROR;
}

/************************************************************************

    FUNCTION:   DumpCDParagraph

*************************************************************************/

void  LNPUBLIC   DumpCDParagraph( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile,"  PARAGRAPH\n" );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDPabdefinition

*************************************************************************/

void  LNPUBLIC   DumpCDPabdefinition( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDPABDEFINITION  pabd;
    WORD             wIndex;
    DWORD            dwLen;


    fprintf( dumpfile,"  PABDEFINITION\n" );

/*    p = (void *) malloc(ODSLength(_CDPABDEFINITION));
    memcpy(p, RecordPtr, ODSLength(_CDPABDEFINITION));

    p = (void *) malloc(RecordLength);
    memcpy(p, RecordPtr,  RecordLength);
*/

    ODSReadMemory( &p, _CDPABDEFINITION, &pabd, 1 );

#ifndef APITESTMODE
    fprintf( dumpfile, "    PABID = %u\n", pabd.PABID );
#endif

    fprintf( dumpfile, "    JustifyMode = %u\n", pabd.JustifyMode );
    fprintf( dumpfile, "    LineSpacing = %u\n", pabd.LineSpacing );
    fprintf( dumpfile, "    ParagraphSpacingBefore = %u\n",
	     pabd.ParagraphSpacingBefore );
    fprintf( dumpfile, "    ParagraphSpacingAfter = %u\n",
	       pabd.ParagraphSpacingAfter );
    fprintf( dumpfile, "    LeftMargin = %u\n", pabd.LeftMargin );
    fprintf( dumpfile, "    RightMargin = %u\n", pabd.RightMargin );
    fprintf( dumpfile, "    FirstLineLeftMargin = %u\n",
	       pabd.FirstLineLeftMargin );

#ifndef APITESTMODE
    fprintf( dumpfile, "    Tabs = %u\n", pabd.Tabs );

    for (wIndex = 0; wIndex < pabd.Tabs; wIndex++)
    {
	fprintf( dumpfile, "    Tab[%u] = %d\n",
		     wIndex, pabd.Tab[wIndex] );
    }

    fprintf( dumpfile, "    Flags = 0x%X: ", pabd.Flags );
	if (0 != (pabd.Flags & PABFLAG_PAGINATE_BEFORE))
		fprintf (dumpfile, "PAGINATE_BEFORE ");
	if (0 != (pabd.Flags & PABFLAG_KEEP_WITH_NEXT))
		fprintf (dumpfile, "KEEP_WITH_NEXT ");
	if (0 != (pabd.Flags & PABFLAG_KEEP_TOGETHER))
		fprintf (dumpfile, "KEEP_TOGETHER ");
	if (0 != (pabd.Flags & PABFLAG_PROPAGATE))
		fprintf (dumpfile, "PROPAGATE ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_RO))
		fprintf (dumpfile, "HIDE_RO ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_RW))
		fprintf (dumpfile, "HIDE_RW ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_PR))
		fprintf (dumpfile, "HIDE_PR ");
	if (0 != (pabd.Flags & PABFLAG_DISPLAY_RM))
		fprintf (dumpfile, "DISPLAY_RM ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_CO))
		fprintf (dumpfile, "HIDE_CO ");
	if (0 != (pabd.Flags & PABFLAG_BULLET))
		fprintf (dumpfile, "BULLET ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_IF))
		fprintf (dumpfile, "HIDE_IF ");
	if (0 != (pabd.Flags & PABFLAG_NUMBEREDLIST))
		fprintf (dumpfile, "NUMBEREDLIST ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_PV))
		fprintf (dumpfile, "HIDE_PV ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_PVE))
		fprintf (dumpfile, "HIDE_PVE ");
	if (0 != (pabd.Flags & PABFLAG_HIDE_NOTES))
		fprintf (dumpfile, "HIDE_NOTES ");
	fprintf( dumpfile, "\n");

	fprintf( dumpfile, "    TabTypes = 0x%lx\n", pabd.TabTypes );

    fprintf( dumpfile, "    Flags2 = 0x%X: ", pabd.Flags2 );
	if (0 != (pabd.Flags2 & PABFLAG2_HIDE_WEB))
		fprintf (dumpfile, "HIDE_WEB ");
	if ( pabd.Flags2 & PABFLAG2_CHECKEDLIST )
		fprintf( dumpfile, "CHECKEDLIST " );
	if ( pabd.Flags2 & PABFLAG2_LM_OFFSET )
		fprintf( dumpfile, "LM_OFFSET " );
	if ( pabd.Flags2 & PABFLAG2_LM_PERCENT )
		fprintf( dumpfile, "LM_PERCENT " );
	if ( pabd.Flags2 & PABFLAG2_FLLM_OFFSET )
		fprintf( dumpfile, "FLLM_OFFSET " );
	if ( pabd.Flags2 & PABFLAG2_FLLM_PERCENT )
		fprintf( dumpfile, "FLLM_PERCENT " );
	if ( pabd.Flags2 & PABFLAG2_RM_OFFSET )
		fprintf( dumpfile, "RM_OFFSET " );
	if ( pabd.Flags2 & PABFLAG2_RM_PERCENT )
		fprintf( dumpfile, "RM_PERCENT " );
	if ( pabd.Flags2 & PABFLAG2_LM_DEFAULT )
		fprintf( dumpfile, "LM_DEFAULT " );
	if ( pabd.Flags2 & PABFLAG2_FLLM_DEFAULT )
		fprintf( dumpfile, "FLLM_DEFAULT " );
	if ( pabd.Flags2 & PABFLAG2_RM_DEFAULT )
		fprintf( dumpfile, "RM_DEFAULT " );
	if ( pabd.Flags2 & PABFLAG2_CIRCLELIST )
		fprintf( dumpfile, "CIRCLELIST " );
	if ( pabd.Flags2 & PABFLAG2_SQUARELIST )
		fprintf( dumpfile, "SQUARELIST " );
	if ( pabd.Flags2 & PABFLAG2_UNCHECKEDLIST )
		fprintf( dumpfile, "UNCHECKEDLIST " );
	if ( pabd.Flags2 & PABFLAG2_BIDI_RTLREADING )
		fprintf( dumpfile, "BIDI_RTLREADING " );
	if ( pabd.Flags2 & PABFLAG2_MORE_FLAGS )
		fprintf( dumpfile, "MORE_FLAGS " );

	fprintf( dumpfile, "\n");

/*************************************************************************/
    /* CDPABDEFINITION record may be followed by an array of 6 WORDS
       which specify extension margin information */

    dwLen = RecordLength - (DWORD)ODSLength(_CDPABDEFINITION) ;
    if (dwLen > 0)
    {
        int i = 0;
        int NumExtMargins = 6;
        WORD ExtMargins;

        fprintf( dumpfile, "    Extended Margin Data = \n" );

        for (i = 0; i < NumExtMargins; i++)
        {
            ODSReadMemory(&p, _WORD, &ExtMargins, 1);
            fprintf( dumpfile, "        Margin[%d]        = %u\n", i, ExtMargins);
        }
    }

/*************************************************************************/


    /*	CDPABDEFINITION record may be also followed by one or two optional DWORDs */

	
	if ( pabd.Flags2 & PABFLAG2_MORE_FLAGS )
	{
	    dwLen = RecordLength - ((DWORD)ODSLength(_CDPABDEFINITION) + (6 * sizeof(WORD)));

	    if (dwLen > 0)
	    {
           DWORD dwExt;

           ODSReadMemory(&p, _DWORD, &dwExt, 1);

	 	     fprintf( dumpfile, "    Extended PAB Flags = \n" );
	        fprintf( dumpfile, "        PAB Flag Extension       = %u", dwExt );

		     if( dwExt & EXTENDEDPABFLAGS3 ) fprintf( dumpfile, " EXTENDEDPABFLAGS3 " );
	 				fprintf( dumpfile, "\n" );

		     dwLen = RecordLength - ((DWORD)ODSLength(_CDPABDEFINITION) + (6 * sizeof(WORD)) + sizeof(DWORD));
		     if (dwLen > 0)
           {
               ODSReadMemory(&p, _DWORD, &dwExt, 1);

	 	         fprintf( dumpfile, "    Extended Flags3 Data = \n" );
               fprintf( dumpfile, "        Flags3           = %u\n", dwExt );

	    	      if( dwExt & PABFLAG3_HIDE_EE )
                   fprintf( dumpfile, " HIDE_EE " );

	  	         if( dwExt & PABFLAG3_HIDE_MOBILE )
                   fprintf( dumpfile, " HIDE_MOBILE " );
           }
	    }
	}

#endif

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPabreference

*************************************************************************/

void  LNPUBLIC   DumpCDPabreference( char *RecordPtr,
					DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDPABREFERENCE   pabr;

    fprintf( dumpfile,"  PABREFERENCE\n" );

    ODSReadMemory( &p, _CDPABREFERENCE, &pabr, 1 );

#ifndef APITESTMODE
    fprintf( dumpfile, "   PABID = %u\n", pabr.PABID );
#endif

    return;
}

/************************************************************************

    FUNCTION:   DumpCDText

*************************************************************************/

void    LNPUBLIC  DumpCDText( char *RecordPtr, DWORD RecordLength, WORD RecordType )
{
    CDTEXT        cdt;
    char far *    p = RecordPtr;
    DWORD         dwLen;

	if(SIG_CD_TEXT == RecordType)
		fprintf( dumpfile,"  TEXT\n" );
	else
		fprintf( dumpfile,"  BIDI_TEXT\n");

   /* Call ODSReadMemory to convert the CDTEXT record pointed to by p from
      Canonical format to Host format and store the result in cdt.
    */
    ODSReadMemory( &p, _CDTEXT, &cdt, 1 );

	fprintf( dumpfile, "   FontID = " );
    DumpFontIDFields( (FONTIDFIELDS *)&cdt.FontID );

    dwLen = RecordLength - (DWORD)ODSLength(_CDTEXT) ;
    if (dwLen > 0)
    {
	fprintf( dumpfile, "   Text Data = " );

	PrintText( p, dwLen );
	WordCount( p, (WORD)(RecordLength - ODSLength(_CDTEXT) ));
	fprintf( dumpfile, "   word count = %ld.\n", nw );
    }

    return;
}


/************************************************************************

    FUNCTION:   DumpCDHeader

*************************************************************************/

void  LNPUBLIC   DumpCDHeader( char *RecordPtr, DWORD RecordLength )
{
    CDHEADER      cdhdr;
    char far *    p = RecordPtr;
    WORD          wTextLen;

    fprintf( dumpfile,"  HEADER/FOOTER record\n" );

    ODSReadMemory( &p, _CDHEADER, &cdhdr, 1 );

    fprintf( dumpfile,"    FontPitchAndFamily = %u\n",
		  cdhdr.FontPitchAndFamily );
    fprintf( dumpfile,"    FontName = %s\n", cdhdr.FontName );

	fprintf( dumpfile, "   FontID = " );
    DumpFontIDFields( (FONTIDFIELDS*)&cdhdr.Font );

    fprintf( dumpfile,"    HeadLength = %u\n", cdhdr.HeadLength );

    wTextLen = ((WORD)RecordLength) - ODSLength( _CDHEADER ) ;

    PrintText( (char far *)p, wTextLen );
    WordCount( (char far *)p, wTextLen );
    fprintf( dumpfile, "    word count = %lu\n", nw );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDLinkexport2

*************************************************************************/

void  LNPUBLIC   DumpCDLinkexport2( char *RecordPtr, DWORD RecordLength )
{
    char far *      p = RecordPtr;
    CDLINKEXPORT2   cdLinkExp2;
	DWORD                   textLen;

    fprintf( dumpfile,"  LINKEXPORT2\n" );

    ODSReadMemory( &p, _CDLINKEXPORT2, &cdLinkExp2, 1 );

	PrintNOTELINK( "\t", &cdLinkExp2.NoteLink );

	textLen = RecordLength - (DWORD)ODSLength(_CDLINKEXPORT2);
    fprintf( dumpfile, "\tDisplay Comment = " );
	if (textLen)
	PrintText( p, textLen ) ;
	else
		fprintf( dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDBitmapheader

*************************************************************************/

void  LNPUBLIC   DumpCDBitmapheader( char *RecordPtr, DWORD RecordLength )
{
    char far *         p = RecordPtr;
    CDBITMAPHEADER     cdBitmapHeader;

    fprintf( dumpfile,"  BITMAPHEADER\n");

    ODSReadMemory( &p, _CDBITMAPHEADER, &cdBitmapHeader, 1 );

    fprintf( dumpfile, "    Dest: Width = %u  Height = %u\n",
			    cdBitmapHeader.Dest.width,
			    cdBitmapHeader.Dest.height );
    fprintf( dumpfile, "    Crop: Width = %u  Height = %u\n",
			    cdBitmapHeader.Crop.width,
			    cdBitmapHeader.Crop.height );
    fprintf( dumpfile, "    Flags = 0x%X: ", cdBitmapHeader.Flags);
	if (CDBITMAP_FLAG_REQUIRES_PALETTE & cdBitmapHeader.Flags)
		fprintf( dumpfile, "REQUIRES_PALETTE " );
	if (CDBITMAP_FLAG_COMPUTE_PALETTE & cdBitmapHeader.Flags)
		fprintf( dumpfile, "COMPUTE_PALETTE " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    wReserved = 0x%X\n", cdBitmapHeader.wReserved );
	fprintf( dumpfile, "    lReserved = 0x%lX\n", cdBitmapHeader.lReserved );
    fprintf( dumpfile, "    Width  = %u\n", cdBitmapHeader.Width );
    fprintf( dumpfile, "    Height = %u\n", cdBitmapHeader.Height );
    fprintf( dumpfile, "    BitsPerPixel = %u\n",
			    cdBitmapHeader.BitsPerPixel );
    fprintf( dumpfile, "    SamplesPerPixel = %u\n",
			    cdBitmapHeader.SamplesPerPixel );
    fprintf( dumpfile, "    BitsPerSample = %u\n",
			    cdBitmapHeader.BitsPerSample );
    fprintf( dumpfile, "    SegmentCount = %u\n",
			    cdBitmapHeader.SegmentCount );
    fprintf( dumpfile, "    ColorCount = %u\n",
			    cdBitmapHeader.ColorCount );
    fprintf( dumpfile, "    PatternCount = %u\n",
			    cdBitmapHeader.PatternCount );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDBitmapsegment

*************************************************************************/

void  LNPUBLIC   DumpCDBitmapsegment( char *RecordPtr, DWORD RecordLength )
{
    char far *      p = RecordPtr;
    CDBITMAPSEGMENT     cdBitmapSeg;
	int                             index;
	
    fprintf( dumpfile,"  BITMAPSEGMENT\n");

    ODSReadMemory( &p, _CDBITMAPSEGMENT, &cdBitmapSeg, 1 );

	for (index = 0; index < 2; index++)
		fprintf( dumpfile, "    Reserved[%d] = 0x%lX\n",
			index, cdBitmapSeg.Reserved[index] );
    fprintf( dumpfile, "    ScanlineCount = %u\n", cdBitmapSeg.ScanlineCount );
    fprintf( dumpfile, "    DataSize = %u\n", cdBitmapSeg.DataSize );
    fprintf( dumpfile, "    <start of compressed raster data>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDBITMAPSEGMENT)) );
    fprintf( dumpfile, "    <end of compressed raster data>\n" );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDColortable

*************************************************************************/

void  LNPUBLIC   DumpCDColortable( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDCOLORTABLE     CDColorTable;

    fprintf( dumpfile,"  COLORTABLE\n" );

    ODSReadMemory( &p, _CDCOLORTABLE, &CDColorTable, 1 );

    fprintf( dumpfile, "    <start of color table entries>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDCOLORTABLE)) );
    fprintf( dumpfile, "    <end of color table entries>\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDGraphic

*************************************************************************/

void  LNPUBLIC   DumpCDGraphic( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDGRAPHIC        cdGraphic;

    fprintf( dumpfile, "  GRAPHIC\n" );

    ODSReadMemory( &p, _CDGRAPHIC, &cdGraphic, 1 );

    fprintf( dumpfile, "    DestSize: Width = %u  Height = %u\n",
			    cdGraphic.DestSize.width,
			    cdGraphic.DestSize.height );
    fprintf( dumpfile, "    CropSize: Width = %u  Height = %u\n",
			    cdGraphic.CropSize.width,
			    cdGraphic.CropSize.height );
    fprintf( dumpfile, "    CropOffset: L = %u T = %u R = %u B = %u\n",
			    cdGraphic.CropOffset.left,
			    cdGraphic.CropOffset.top,
			    cdGraphic.CropOffset.right,
			    cdGraphic.CropOffset.bottom );
    fprintf( dumpfile, "    fResize = %s\n",
			    (cdGraphic.fResize?"TRUE":"FALSE") );
    fprintf( dumpfile, "    Version = %u\n", cdGraphic.Version + 1);
	if (cdGraphic.Version < CDGRAPHIC_VERSION3)
	{
		fprintf( dumpfile, "    bFlags = 0x%X: unused before CDGRAPHIC_VERSION3\n",
			cdGraphic.bFlags );
	}
	else
	{
		fprintf( dumpfile, "    bFlags = 0x%X: ",
			cdGraphic.bFlags );
		if (CDGRAPHIC_FLAG_DESTSIZE_IS_PIXELS & cdGraphic.bFlags)
			fprintf( dumpfile, "DESTSIZE_IS_PIXELS ");
		if (CDGRAPHIC_FLAG_SPANSLINES & cdGraphic.bFlags )
			fprintf( dumpfile, "SPANSLINES " );
		fprintf( dumpfile, "\n");
	}
	fprintf( dumpfile, "    wReserved = 0x%X\n", cdGraphic.wReserved );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDPmmetaseg

*************************************************************************/

void  LNPUBLIC   DumpCDPmmetaseg( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDPMMETASEG      cdPMSeg;

    fprintf( dumpfile, "  PMMETASEG\n" );

    ODSReadMemory( &p,  _CDPMMETASEG, &cdPMSeg, 1 );

    fprintf( dumpfile, "    DataSize = %u\n", cdPMSeg.DataSize );
    fprintf( dumpfile, "    SegSize = %u\n", cdPMSeg.SegSize );
    fprintf( dumpfile, "    <start of PM metafile bits>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDPMMETASEG)) );
    fprintf( dumpfile, "    <end of PM metafile bits>\n" );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDWinmetaseg

*************************************************************************/

void  LNPUBLIC   DumpCDWinmetaseg (char *RecordPtr, DWORD RecordLength)
{
    char far *       p = RecordPtr;
    CDWINMETASEG     cdWINSeg;
	
    fprintf (dumpfile, "  WINMETASEG\n");

    ODSReadMemory( &p, _CDWINMETASEG, &cdWINSeg, 1 );

    fprintf( dumpfile, "    DataSize = %u\n", cdWINSeg.DataSize );
    fprintf( dumpfile, "    SegSize = %u\n", cdWINSeg.SegSize );
    fprintf( dumpfile, "    <start of Win metafile bits>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDWINMETASEG)) );
    fprintf( dumpfile, "    <end of Win metafile bits>\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDMacmetaseg

*************************************************************************/

void  LNPUBLIC   DumpCDMacmetaseg (char *RecordPtr, DWORD RecordLength)
{
    char far *       p = RecordPtr;
    CDMACMETASEG     cdMacSeg;

    fprintf (dumpfile, "  MACMETASEG\n" );

    ODSReadMemory( &p, _CDMACMETASEG, &cdMacSeg, 1 );

    fprintf( dumpfile, "    DataSize = %u\n", cdMacSeg.DataSize );
    fprintf( dumpfile, "    SegSize = %u\n", cdMacSeg.SegSize );
    fprintf( dumpfile, "    <start of Mac metafile bits>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDMACMETASEG)) );
    fprintf( dumpfile, "    <end of Mac metafile bits>\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDCgmmeta

*************************************************************************/

void  LNPUBLIC   DumpCDCgmmeta (char *RecordPtr, DWORD RecordLength)
{
    char far *       p = RecordPtr;
    CDCGMMETA        cdCGMSeg;
	
    fprintf( dumpfile, "  CGMMETA\n" );

    ODSReadMemory( &p, _CDCGMMETA, &cdCGMSeg, 1 );

    fprintf( dumpfile, "    mm = %d\n", cdCGMSeg.mm );
    fprintf( dumpfile, "    xExt = %d\n",cdCGMSeg.xExt );
    fprintf( dumpfile, "    yExt = %d\n", cdCGMSeg.yExt );
    fprintf( dumpfile, "    OriginalSize: Width = %u Height = %u\n",
		cdCGMSeg.OriginalSize.width,
		cdCGMSeg.OriginalSize.height );
    fprintf( dumpfile, "    <start of CGM metafile bits>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDCGMMETA)) );
    fprintf( dumpfile, "    <end of CGM metafile bits>\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPmmetaheader

*************************************************************************/

void  LNPUBLIC   DumpCDPmmetaheader( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDPMMETAHEADER   cdPMMetaHeader;
		
    fprintf( dumpfile, "  PMMETAHEADER\n" );

    ODSReadMemory( &p, _CDPMMETAHEADER, &cdPMMetaHeader, 1 );

    fprintf( dumpfile, "    mm = %d\n", cdPMMetaHeader.mm );
    fprintf( dumpfile, "    xExt = %d\n", cdPMMetaHeader.xExt );
    fprintf( dumpfile, "    yExt = %d\n", cdPMMetaHeader.yExt );
    fprintf( dumpfile, "    OriginalDisplaySize: Width = %u Height= %u\n",
		cdPMMetaHeader.OriginalDisplaySize.width,
		cdPMMetaHeader.OriginalDisplaySize.height );
    fprintf( dumpfile, "    Meta File Size = %lu\n",
		cdPMMetaHeader.MetafileSize );
    fprintf( dumpfile, "    SegCount = %u\n",
		cdPMMetaHeader.SegCount );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDWinmetaheader

*************************************************************************/

void  LNPUBLIC   DumpCDWinmetaheader( char *RecordPtr,
					DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDWINMETAHEADER  cdWinMetaHeader;
	
    fprintf( dumpfile, "  WINMETAHEADER\n" );

    ODSReadMemory( &p, _CDWINMETAHEADER, &cdWinMetaHeader, 1 );

    fprintf( dumpfile, "    mm = %d\n", cdWinMetaHeader.mm );
    fprintf( dumpfile, "    xExt = %d\n", cdWinMetaHeader.xExt );
    fprintf( dumpfile, "    yExt = %d\n", cdWinMetaHeader.yExt );
    fprintf( dumpfile, "    OriginalDisplaySize: Width = %u Height= %u\n",
		cdWinMetaHeader.OriginalDisplaySize.width,
		cdWinMetaHeader.OriginalDisplaySize.height );
    fprintf( dumpfile, "    MetafileSize = %lu\n",
		cdWinMetaHeader.MetafileSize );
    fprintf( dumpfile, "    SegCount = %u\n",
		cdWinMetaHeader.SegCount );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDMacmetaheader

*************************************************************************/

void  LNPUBLIC   DumpCDMacmetaheader( char *RecordPtr,
					DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDMACMETAHEADER  cdMACMetaHeader;
	
    fprintf( dumpfile, "  MACMETAHEADER\n" );

    ODSReadMemory( &p, _CDMACMETAHEADER, &cdMACMetaHeader, 1 );

    fprintf( dumpfile, "    OriginalDisplaySize: Width = %u Height= %u\n",
		cdMACMetaHeader.OriginalDisplaySize.width,
		cdMACMetaHeader.OriginalDisplaySize.height );
    fprintf( dumpfile, "    Meta File Size = %lu\n",
		cdMACMetaHeader.MetafileSize );
    fprintf( dumpfile, "    Meta Seg Count = %u\n",
		cdMACMetaHeader.SegCount );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDTablebegin

*************************************************************************/

void  LNPUBLIC   DumpCDTablebegin( char * RecordPtr, DWORD RecordLength, WORD RecordType )
{
    char far *       p = RecordPtr;
    CDTABLEBEGIN     cdTableBegin;

	if(SIG_CD_TABLEBEGIN == RecordType)
		fprintf( dumpfile, "  TABLEBEGIN\n" );
	else
		fprintf( dumpfile, "  NESTEDTABLEBEGIN\n");

    ODSReadMemory( &p, _CDTABLEBEGIN, &cdTableBegin, 1 );

    fprintf( dumpfile, "    LeftMargin              = %u\n",
		     cdTableBegin.LeftMargin );
    fprintf( dumpfile, "    HorizInterCellSpace     = %u\n",
		     cdTableBegin.HorizInterCellSpace );
    fprintf( dumpfile, "    VertInterCellSpace      = %u\n",
		     cdTableBegin.VertInterCellSpace );
    fprintf( dumpfile, "    V4HorizInterCellSpace   = %u\n",
		     cdTableBegin.V4HorizInterCellSpace );
    fprintf( dumpfile, "    V4VertInterCellSpace    = %u\n",
		     cdTableBegin.V4VertInterCellSpace );
    fprintf( dumpfile, "    Flags = 0x%X: ", cdTableBegin.Flags);

    /* If all the CDTABLE_SOLID bits are set, the color style is SOLID
       and we need to zero out all the CDTABLE_SOLID bits to determine
       which remaining flags may be set */

	if ((CDTABLE_SOLID & cdTableBegin.Flags ) == CDTABLE_SOLID)
    {
		fprintf( dumpfile, "SOLID " );
        cdTableBegin.Flags = cdTableBegin.Flags ^ CDTABLE_SOLID;
    }
 	if (CDTABLE_AUTO_CELL_WIDTH & cdTableBegin.Flags)
        fprintf (dumpfile, "AUTO_CELL_WIDTH ");
    if (CDTABLE_V4_BORDERS & cdTableBegin.Flags)
        fprintf (dumpfile, "V4_BORDERS ");
    if (CDTABLE_3D_BORDER_EMBOSS & cdTableBegin.Flags)
        fprintf (dumpfile, "3D_BORDER_EMBOSS ");
    if (CDTABLE_3D_BORDER_EXTRUDE & cdTableBegin.Flags)
    	fprintf (dumpfile, "3D_BORDER_EXTRUDE ");
    if (CDTABLE_BIDI_RTLTABLE & cdTableBegin.Flags )
	   	fprintf( dumpfile, "BIDI_RTLTABLE " );
    if (CDTABLE_ALIGNED_RIGHT & cdTableBegin.Flags )
	   	fprintf( dumpfile, "ALIGNED_RIGHT " );
    if (CDTABLE_COLLAPSIBLE & cdTableBegin.Flags )
    	fprintf( dumpfile, "COLLAPSIBLE " );
    if (CDTABLE_LEFTTOP & cdTableBegin.Flags )
	   	fprintf( dumpfile, "LEFTTOP " );
    if (CDTABLE_TOP & cdTableBegin.Flags )
	    fprintf( dumpfile, "TOP " );
    if (CDTABLE_LEFT & cdTableBegin.Flags )
    	fprintf( dumpfile, "LEFT " );
    if (CDTABLE_ALTERNATINGCOLS & cdTableBegin.Flags )
    	fprintf( dumpfile, "ALTERNATINGCOLS " );
    if (CDTABLE_ALTERNATINGROWS & cdTableBegin.Flags )
    		fprintf( dumpfile, "ALTERNATINGROWS " );
    if (CDTABLE_RIGHTTOP & cdTableBegin.Flags )
    	fprintf( dumpfile, "RIGHTTOP " );
    if (CDTABLE_RIGHT & cdTableBegin.Flags )
    	fprintf( dumpfile, "RIGHT " );
    if (CDTABLE_ALIGNED_CENTER & cdTableBegin.Flags )
    	fprintf( dumpfile, "ALIGNED_CENTER " );
    if (CDTABLE_TEXTFLOWS & cdTableBegin.Flags )
    	fprintf( dumpfile, "TEXTFLOWS " );
    	fprintf( dumpfile, "\n");
    return;
}

/************************************************************************

    FUNCTION:   DumpCDTablecell

*************************************************************************/

void  LNPUBLIC   DumpCDTablecell( char * RecordPtr, DWORD RecordLength, WORD RecordType )
{
    char far *       p = RecordPtr;
    CDTABLECELL      cdTableCell;
    WORD             Border;
    WORD             LeftBorder;
    WORD             RightBorder;
    WORD             TopBorder;
    WORD             BottomBorder;
static  char *       pachBorders[4] = {"NONE", "SINGLE", "DOUBLE", "Unknown (3)"};
	
    if(SIG_CD_TABLECELL == RecordType)
		fprintf (dumpfile, "  TABLECELL\n");
	else
		fprintf( dumpfile, "  NESTEDTABLECELL\n");

    ODSReadMemory( &p, _CDTABLECELL, &cdTableCell, 1 );

    fprintf( dumpfile, "        Row             = %u\n",
		cdTableCell.Row );
    fprintf( dumpfile, "        Column          = %u\n",
		cdTableCell.Column );
    fprintf( dumpfile, "        LeftMargin      = %u\n",
		cdTableCell.LeftMargin );
    fprintf( dumpfile, "        RightMargin     = %u\n",
		cdTableCell.RightMargin );
    fprintf( dumpfile, "        FractionalWidth = %u\n",
		cdTableCell.FractionalWidth );

    Border = (WORD)cdTableCell.Border;

    LeftBorder  = ( (WORD)(Border & CDTC_M_Left  ) >> CDTC_S_Left  );
    RightBorder = ( (WORD)(Border & CDTC_M_Right ) >> CDTC_S_Right );
    TopBorder   = ( (WORD)(Border & CDTC_M_Top   ) >> CDTC_S_Top );
    BottomBorder= ( (WORD)(Border & CDTC_M_Bottom) >> CDTC_S_Bottom );

    fprintf( dumpfile, "        Left Border     = %s\n",
		    pachBorders[LeftBorder] );

    fprintf( dumpfile, "        Right Border    = %s\n",
		    pachBorders[RightBorder] );

    fprintf( dumpfile, "        Top Border      = %s\n",
		    pachBorders[TopBorder] );

    fprintf( dumpfile, "        Bottom Border   = %s\n",
		    pachBorders[BottomBorder] );

    fprintf( dumpfile, "    Flags = 0x%X: ", cdTableCell.Flags);
	if (CDTABLECELL_USE_BKGCOLOR & cdTableCell.Flags)
		fprintf (dumpfile, "USE_BKGCOLOR ");
	if (CDTABLECELL_USE_V42BORDERS & cdTableCell.Flags)
		fprintf (dumpfile, "USE_V42BORDERS ");
	if (CDTABLECELL_INVISIBLEH & cdTableCell.Flags)
		fprintf (dumpfile, "INVISIBLEH ");
	if (CDTABLECELL_INVISIBLEV & cdTableCell.Flags)
		fprintf (dumpfile, "INVISIBLEV ");
	if (CDTABLECELL_USE_GRADIENT & cdTableCell.Flags)
		fprintf( dumpfile, "USE_GRADIENT " );
	if (CDTABLECELL_VALIGNCENTER & cdTableCell.Flags)
		fprintf( dumpfile, "VALIGNCENTER " );
	if (CDTABLECELL_GRADIENT_LTR & cdTableCell.Flags)
		fprintf( dumpfile, "GRADIENT_LTR " );
	if (CDTABLECELL_VALIGNBOTTOM & cdTableCell.Flags)
		fprintf( dumpfile, "VALIGNBOTTOM " );


	fprintf( dumpfile, "\n");

		/* Are the extended border width fields present? */
	if (CDTABLECELL_USE_V42BORDERS & cdTableCell.Flags)
	{
			/* Print the extended border widths */
		Border = cdTableCell.v42Border;

		LeftBorder  = ( (WORD)(Border & CDTC_M_V42_Left  ) >> CDTC_S_V42_Left  );
		RightBorder = ( (WORD)(Border & CDTC_M_V42_Right ) >> CDTC_S_V42_Right );
		TopBorder   = ( (WORD)(Border & CDTC_M_V42_Top   ) >> CDTC_S_V42_Top );
		BottomBorder= ( (WORD)(Border & CDTC_M_V42_Bottom) >> CDTC_S_V42_Bottom );

		fprintf( dumpfile, "        Left Border width   = %d\n", LeftBorder );

		fprintf( dumpfile, "        Right Border width  = %d\n", RightBorder );

		fprintf( dumpfile, "        Top Border width    = %d\n", TopBorder );

		fprintf( dumpfile, "        Bottom Border width = %d\n", BottomBorder );
	}
	else
		fprintf( dumpfile, "        v42Border Unused (0x%X)\n",
		cdTableCell.v42Border );
    fprintf( dumpfile, "        RowSpan         = %d\n",
		cdTableCell.RowSpan );

#ifndef APITESTMODE
    fprintf( dumpfile, "        ColumnSpan      = %d\n",
		cdTableCell.ColumnSpan );
    fprintf( dumpfile, "        BackgroundColor = %d (0x%X)\n",
		cdTableCell.BackgroundColor, cdTableCell.BackgroundColor );
#endif
    return;
}

/************************************************************************

    FUNCTION:   DumpCDTableend

*************************************************************************/

void  LNPUBLIC   DumpCDTableend( char * RecordPtr, DWORD RecordLength, WORD RecordType )
{
    char far *     p = RecordPtr;
    CDTABLEEND     cdTableEnd;
	
    if(SIG_CD_TABLEEND == RecordType)
		fprintf( dumpfile, "  TABLEEND\n" );
	else
		fprintf( dumpfile, "  NESTEDTABLEEND\n");

    ODSReadMemory( &p, _CDTABLEEND, &cdTableEnd, 1 );

    fprintf( dumpfile, "    Spare               = 0x%X\n\n",
				cdTableEnd.Spare );
    return;
}

/************************************************************************

    FUNCTION:   DumpCDStylename

*************************************************************************/

void  LNPUBLIC  DumpCDStylename( char * RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDSTYLENAME      cdStyleName;

    fprintf( dumpfile, "  STYLENAME\n" );

    ODSReadMemory( &p, _CDSTYLENAME, &cdStyleName, 1 );

    fprintf( dumpfile, "    Flags = 0x%X: ", cdStyleName.Flags);
	if (STYLE_FLAG_FONTID & cdStyleName.Flags)
		fprintf (dumpfile, "STYLE_FLAG_FONTID ");
	if (STYLE_FLAG_INCYCLE & cdStyleName.Flags)
		fprintf (dumpfile, "STYLE_FLAG_INCYCLE ");
	if (STYLE_FLAG_PERMANENT & cdStyleName.Flags)
		fprintf (dumpfile, "STYLE_FLAG_PERMANENT ");
	fprintf( dumpfile, "\n");

#ifndef APITESTMODE
    fprintf( dumpfile, "    PABID: %u\n", cdStyleName.PABID );
#endif

    fprintf( dumpfile, "    Style Name: %s\n", cdStyleName.StyleName );
	
		/* If there's a FONTID . . . */
	if (STYLE_FLAG_FONTID & cdStyleName.Flags)
	{
			/* . . . read and print it! */
		fprintf( dumpfile, "    FontID = " );
	    DumpFontIDFields( (FONTIDFIELDS *) (p) );
		p += sizeof (FONTID);
	}

		/* If this is a permanent style . . . */
	if (STYLE_FLAG_PERMANENT & cdStyleName.Flags)
	{
		WORD    userNameLen;

			/* Read the length of the user name */
		ODSReadMemory ( &p, _WORD, &userNameLen, 1);

			/* Print the length and the name */
		fprintf (dumpfile, "    User name length = %d\n", userNameLen);
		fprintf (dumpfile, "    User name = ");
		PrintText (p, userNameLen);
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDField

    PURPOSE:    Dump either a CDFIELD record or a CDFIELD_PRE_36 record
		
    DESCRIPTION:
	This function handles both CDFIELD and CDFIELD_PRE_36 records
	because they share identical structure except for the text
	list of legal keyword values.  The third input parameter
	specifies which type of field is pointed to by RecordPtr.

	Call ODSReadMemory to convert the CDFIELD (or CDFIELD_PRE_36)
	structure from canonical format to host format, storing the
	result in cdField (or cdFieldPre36). This advances pointer p to
	the next byte in the canonical format buffer after the CDFIELD
	structure. This may be the start of the Default Value Formula,
	the Input Translation Formula, Input Validity Check Formula, or
	Item Name.

*************************************************************************/

void  LNPUBLIC   DumpCDField( char *RecordPtr, DWORD RecordLength,
				  WORD RecordType )
{
    char far *       p = RecordPtr;
    CDFIELD          cdField;
    CDFIELD_PRE_36   cdFieldPre36;
    WORD             wFieldFlags;
    WORD             wDataType;
    char *           szDataType;
    WORD             wInputListDelim;
    WORD             wDisplayListDelim;
    NFMT             NumberFormat;
    TFMT             TimeFormat;
    FONTID           FontID;
    WORD             NameLength;
    WORD             DescLength;
    WORD             TextValueLength;
	WORD             DVLength;              /* Length of Default Value formula */
	WORD             ITLength;              /* Length of Input Translation formula */
	WORD             IVLength;              /* Length of Input Validation formula */

    if (RecordType == SIG_CD_FIELD)
    {
	fprintf( dumpfile, "  FIELD\n" );

	ODSReadMemory( &p, _CDFIELD, &cdField, 1 );

	wFieldFlags       = cdField.Flags;
	wDataType         = cdField.DataType;
	wInputListDelim   = cdField.ListDelim & LD_MASK ;
	wDisplayListDelim = cdField.ListDelim & LDD_MASK ;
	NumberFormat      = cdField.NumberFormat;
	TimeFormat        = cdField.TimeFormat;
	FontID            = cdField.FontID;
	DVLength          = cdField.DVLength;
	ITLength          = cdField.ITLength;
	IVLength          = cdField.IVLength;
	NameLength        = cdField.NameLength;
	DescLength        = cdField.DescLength;
	TextValueLength   = cdField.TextValueLength;
    }
    else if (RecordType == SIG_CD_FIELD_PRE_36)
    {
	fprintf( dumpfile, "  FIELD_PRE_36\n" );

	ODSReadMemory( &p, _CDFIELD_PRE_36, &cdFieldPre36, 1 );

	wFieldFlags       = cdFieldPre36.Flags;
	wDataType         = cdFieldPre36.DataType;
	wInputListDelim   = cdFieldPre36.ListDelim & LD_MASK ;
	wDisplayListDelim = cdFieldPre36.ListDelim & LDD_MASK ;
	NumberFormat      = cdFieldPre36.NumberFormat;
	TimeFormat        = cdFieldPre36.TimeFormat;
	FontID            = cdFieldPre36.FontID;
	DVLength          = cdFieldPre36.DVLength;
	ITLength          = cdFieldPre36.ITLength;
	IVLength          = cdFieldPre36.IVLength;
	NameLength        = cdFieldPre36.NameLength;
	DescLength        = cdFieldPre36.DescLength;
	TextValueLength   = 0; /*is only in CDFIELD, not CDFIELD_PRE_36*/
    }
    else /* should never get here */
    {
	fprintf( dumpfile,
	"    Error: unrecognized CDFIELD type %u.\n", RecordType );
	return;
    }

    fprintf( dumpfile, "   Field Flags = 0x%X : ", wFieldFlags );
    if (wFieldFlags & FREADWRITERS)
	fprintf( dumpfile, "FREADWRITERS " );
    if (wFieldFlags & FEDITABLE)
	fprintf( dumpfile, "FEDITABLE " );
    if (wFieldFlags & FNAMES)
	fprintf( dumpfile, "FNAMES " );
    if (wFieldFlags & FSTOREDV)
	fprintf( dumpfile, "FSTOREDV " );
    if (wFieldFlags & FREADERS)
	fprintf( dumpfile, "FREADERS " );
    if (wFieldFlags & FSECTION)
	fprintf( dumpfile, "FSECTION " );
    if (wFieldFlags & FSPARE3)
	fprintf( dumpfile, "FSPARE3 " );
    if (wFieldFlags & FV3FAB)
	fprintf( dumpfile, "FV3FAB " );
    if (wFieldFlags & FCOMPUTED)
	fprintf( dumpfile, "FCOMPUTED " );
    if (wFieldFlags & FKEYWORDS)
	fprintf( dumpfile, "FKEYWORDS " );
    if (wFieldFlags & FPROTECTED)
	fprintf( dumpfile, "FPROTECTED " );
    if (wFieldFlags & FREFERENCE)
	fprintf( dumpfile, "FREFERENCE " );
    if (wFieldFlags & FSIGN)
	fprintf( dumpfile, "FSIGN " );
    if (wFieldFlags & FSEAL)
	fprintf( dumpfile, "FSEAL " );
    if (wFieldFlags & FKEYWORDS)
    {
		fprintf (dumpfile, "\n     Keyword Type = ");
		
		if (0 != (wFieldFlags & FKEYWORDS_UI_ALLOW_NEW))
			fprintf( dumpfile, "standard, allow new keyword values" );
	else if (0 != (wFieldFlags & FKEYWORDS_UI_CHECKBOX))
	    fprintf( dumpfile, "checkbox" );
	else if (0 != (wFieldFlags & FKEYWORDS_UI_RADIOBUTTON))
	    fprintf( dumpfile, "radio button" );
	else
	{
	    fprintf( dumpfile, "standard" );
	
	}
    }
    fprintf( dumpfile, "\n");

    /* DataType */

    szDataType = GetLiteralString( TypeStringTablePtr, wDataType );
    fprintf( dumpfile, "   Data Type = %s\n", szDataType );

    /* ListDelim */

	fprintf( dumpfile, "   Input List Delimeters = " );
    if (wInputListDelim)
    {
	if (wInputListDelim & LDELIM_SPACE)
	    fprintf(dumpfile, "space " );
	if (wInputListDelim & LDELIM_COMMA)
	    fprintf(dumpfile, "comma " );
	if (wInputListDelim & LDELIM_SEMICOLON)
	    fprintf(dumpfile, "semicolon " );
	if (wInputListDelim & LDELIM_NEWLINE)
	    fprintf(dumpfile, "newline " );
	if (wInputListDelim & LDELIM_BLANKLINE)
	    fprintf(dumpfile, "blankline " );
    }
	else
		fprintf( dumpfile, "<none>" );
	fprintf( dumpfile, "\n" );

	fprintf( dumpfile, "   Display List Delimeter = " );
    if (wDisplayListDelim)
    {
	if (wDisplayListDelim == LDDELIM_SPACE)
	    fprintf(dumpfile, "space " );
	else if (wDisplayListDelim == LDDELIM_COMMA)
	    fprintf(dumpfile, "comma " );
	else if (wDisplayListDelim == LDDELIM_SEMICOLON)
	    fprintf(dumpfile, "semicolon " );
	else if (wDisplayListDelim == LDDELIM_NEWLINE)
	    fprintf(dumpfile, "newline " );
	else if (wDisplayListDelim == LDDELIM_BLANKLINE)
	    fprintf(dumpfile, "blankline " );
    }
	else
		fprintf( dumpfile, "<none>" );
	fprintf( dumpfile, "\n" );

    /* Number format, if applicable */

    if ( wDataType == TYPE_NUMBER ||
	  wDataType == TYPE_NUMBER_RANGE )
    {
	BYTE Digits = NumberFormat.Digits; /* No. decimal digits */
	BYTE Format = NumberFormat.Format; /* Display Format */
	BYTE Attributes = NumberFormat.Attributes;

	fprintf( dumpfile, "   Number format: digits = 0x%X\n", Digits );
	fprintf( dumpfile, "                  format = " );
	switch (Format)
	{
	    case NFMT_GENERAL:
		fprintf( dumpfile, "General\n" );
		break;
	    case NFMT_FIXED:
		fprintf( dumpfile, "Fixed\n" );
		break;
	    case NFMT_SCIENTIFIC:
		fprintf( dumpfile, "Scientific\n" );
		break;
	    case NFMT_CURRENCY:
		fprintf( dumpfile, "Curency\n" );
		break;
	    default:
		fprintf( dumpfile, "unrecognized (0x%X)\n", Format );
	}
	fprintf( dumpfile, "             attributes = ");
	if (Attributes & NATTR_PUNCTUATED)
	    fprintf( dumpfile, "Punctuated at thousands, " );
	if (Attributes & NATTR_PARENS)
	    fprintf( dumpfile, "Parentheses on negative, " );
	if (Attributes & NATTR_PERCENT)
	    fprintf( dumpfile, "Percentage." );
	fprintf( dumpfile, "\n" );
    }


    /* Time format, if applicable */

#ifndef APITESTMODE

    if ( wDataType == TYPE_TIME ||
	  wDataType == TYPE_TIME_RANGE )
    {
	BYTE Date = TimeFormat.Date ; /* Date Display Format */
	BYTE Time = TimeFormat.Time ; /* Time Display Format */
	BYTE Zone = TimeFormat.Zone ; /* Time Zone Display Format */
	BYTE Structure = TimeFormat.Structure ;

	fprintf( dumpfile, "   Date Format   = " );
	if (Date == TDFMT_FULL)
	    fprintf( dumpfile, "year, month, and day.\n" );
	else if (Date == TDFMT_CPARTIAL)
	    fprintf( dumpfile, "month and day, year if not this year\n" );
	else if (Date == TDFMT_PARTIAL)
	    fprintf( dumpfile, "month and day\n" );
	else if (Date == TDFMT_DPARTIAL)
	    fprintf( dumpfile, "year and month\n" );
	else if (Date == TDFMT_FULL4)
		fprintf( dumpfile, "year (4 digit), month and day\n" );
	else if (Date == TDFMT_CPARTIAL4)
		fprintf( dumpfile, "month and day, year (4 digit) if not this year\n" );
	else if (Date == TDFMT_DPARTIAL4)
		fprintf( dumpfile, "year (4 digit) and month\n" );
	
	fprintf( dumpfile, "   Time Format   = " );
	if (Time == TTFMT_FULL)
	    fprintf( dumpfile, "hour, minute, and second\n" );
	else if (Time == TTFMT_PARTIAL)
	    fprintf( dumpfile, "hour and minute\n" );
	else if (Time == TTFMT_HOUR)
		fprintf( dumpfile, "hour\n" );

    fprintf( dumpfile, "   Zone display = " );
	if (Zone == TZFMT_NEVER)
	    fprintf( dumpfile, "Adjust all times to local zone\n" );
	else if (Zone == TZFMT_SOMETIMES)
	    fprintf( dumpfile, "Show only if zone not local\n" );
	else if (Zone == TZFMT_ALWAYS)
	     fprintf( dumpfile, "Always show time zone\n" );

	fprintf( dumpfile, "   Overall Format = ");
	if (Structure == TSFMT_DATE)
	    fprintf( dumpfile, "date only\n" );
	else if (Structure == TSFMT_TIME)
	    fprintf( dumpfile, "time only\n" );
	else if (Structure == TSFMT_DATETIME)
	    fprintf( dumpfile, "date and time\n" );
	else if (Structure == TSFMT_CDATETIME)
	    fprintf( dumpfile, "date time or time today or time yesterday\n" );
    }
#endif

    /* Font ID */

	fprintf( dumpfile, "   FontID = " );
    DumpFontIDFields( (FONTIDFIELDS*)&FontID );

    /* Default Value Formula.*/

    if (DVLength>0)
    {
	/* p already points to the start of the Default Value Formula */

		fprintf( dumpfile, "   Default Value Formula =\n" );
		PrintFormula ( p, DVLength );


	/* advance p to the next byte after the compiled formula */
	p = (  ((char*)p) + DVLength  );
    }

    /* Input Translation Formula */

    if (ITLength>0)
    {
		fprintf( dumpfile, "   Input Translation Formula =\n" );
		PrintFormula ( p, ITLength );

	/* advance p past the input translation formula */
	p = (  ((char *)p) + ITLength  );
    }

    /* Input Validation Formula */

    if (IVLength>0)
    {
		fprintf( dumpfile, "   Input Validation Formula =\n" );
		PrintFormula ( p, IVLength );

	/* advance p past the input validation formula */
	p = (  ((char *)p) + IVLength  );
    }

    /* Item Name */

	fprintf( dumpfile, "   Item Name   = " );
	if (0 != NameLength)
	{
		PrintText( (char far *)p, NameLength );
		p = ( ((char far *)p) + NameLength );
	}
	else
		fprintf (dumpfile, "<none>\n");

    /* Description */

    fprintf( dumpfile, "   Description = " );
	if (0 != DescLength)
	{
		PrintText( (char far *)p, DescLength );
		p = ( ((char far *)p) + DescLength );
	}
	else
		fprintf (dumpfile, "<none>\n");

    /* List of key word values */

    if ( (TextValueLength > 0) && (wFieldFlags & FKEYWORDS) )
    {
	LIST  List;
	WORD *awLengths;
	WORD  i;
	
	ODSReadMemory( &p, _LIST, (void *)&List, 1 );

			/* Is this a text list or a formula? */
		if (0 != List.ListEntries)
		{
				/* Number of entries is non-zero - it's a text list */
			fprintf (dumpfile, "   Number of keywords = %d\n", List.ListEntries);

				/* allocate an array of length words */
			awLengths = (WORD*)calloc( List.ListEntries, sizeof(WORD) );

			/* populate the array with length words */
		if (awLengths != (WORD*)NULL)
		{
		    ODSReadMemory( &p, _WORD, (void *)awLengths,
			    List.ListEntries );
		    for (i = 0; i < List.ListEntries; i++)
		    {
			fprintf( dumpfile, "     Key word %d = ", i );
			PrintText( p, awLengths[i] );
			p = (  ((char far *)p) + awLengths[i]  );
		    }

		    free(awLengths);
		}
		}
		else
		{
				/* Number of entries is zero - it's a formula */
			fprintf (dumpfile, "   Keyword formula =\n");
			PrintFormula (p, (WORD) (TextValueLength - (WORD) ODSLength (_WORD)));
		}
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDDocument

*************************************************************************/

void  LNPUBLIC   DumpCDDocument( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDDOCUMENT       cdDocument;
    WORD             wFlags;
    WORD             wIndex;
	DWORD            textFieldNameLength;
	
    fprintf( dumpfile, "  DOCUMENT\n" );

    ODSReadMemory( &p, _CDDOCUMENT, &cdDocument, 1 );

	textFieldNameLength = RecordLength - ((DWORD)ODSLength(_CDDOCUMENT));

    fprintf( dumpfile, "   PaperColor    = %u (0x%X)\n",
	    cdDocument.PaperColor, cdDocument.PaperColor );

    wFlags = cdDocument.FormFlags;

    fprintf( dumpfile, "   FormFlags = 0x%X: ", wFlags );
    if (wFlags & TPL_FLAG_REFERENCE)
	fprintf( dumpfile, "TPL_FLAG_REFERENCE " );
    if (wFlags & TPL_FLAG_MAIL)
	fprintf( dumpfile, "TPL_FLAG_MAIL " );
    if (wFlags & TPL_FLAG_NOTEREF)
	fprintf( dumpfile, "TPL_FLAG_NOTEREF " );
    if (wFlags & TPL_FLAG_NOTEREF_MAIN)
	fprintf( dumpfile, "TPL_FLAG_NOTEREF_MAIN " );
    if (wFlags & TPL_FLAG_RECALC)
	fprintf( dumpfile, "TPL_FLAG_RECALC " );
    if (wFlags & TPL_FLAG_BOILERPLATE)
	fprintf( dumpfile, "TPL_FLAG_BOILERPLATE " );
    if (wFlags & TPL_FLAG_FGCOLOR)
	fprintf( dumpfile, "TPL_FLAG_FGCOLOR " );
    if (wFlags & TPL_FLAG_SPARESOK)
	fprintf( dumpfile, "TPL_FLAG_SPARESOK " );
    if (wFlags & TPL_FLAG_ACTIVATE_OBJECT_COMP)
	fprintf( dumpfile, "TPL_FLAG_ACTIVATE_OBJECT_COMP " );
    if (wFlags & TPL_FLAG_ACTIVATE_OBJECT_EDIT)
	fprintf( dumpfile, "TPL_FLAG_ACTIVATE_OBJECT_EDIT " );
    if (wFlags & TPL_FLAG_ACTIVATE_OBJECT_READ)
	fprintf( dumpfile, "TPL_FLAG_ACTIVATE_OBJECT_READ " );
    if (wFlags & TPL_FLAG_SHOW_WINDOW_COMPOSE)
	fprintf( dumpfile, "TPL_FLAG_SHOW_WINDOW_COMPOSE " );
    if (wFlags & TPL_FLAG_SHOW_WINDOW_EDIT)
	fprintf( dumpfile, "TPL_FLAG_SHOW_WINDOW_EDIT " );
    if (wFlags & TPL_FLAG_SHOW_WINDOW_READ)
	fprintf( dumpfile, "FLAG_SHOW_WINDOW_READ " );
    if (wFlags & TPL_FLAG_UPDATE_RESPONSE)
	fprintf( dumpfile, "TPL_FLAG_UPDATE_RESPONSE " );
    if (wFlags & TPL_FLAG_UPDATE_PARENT)
	fprintf( dumpfile, "TPL_FLAG_UPDATE_PARENT " );
    if (wFlags & TPL_FLAG_NOINITIALFOCUS)
	fprintf( dumpfile, "TPL_FLAG_NOINITIALFOCUS " );
    if (wFlags & TPL_FLAG_SIGNWHENSAVED)
	fprintf( dumpfile, "TPL_FLAG_SIGNWHENSAVED " );
	if (wFlags & TPL_FLAG_NOFOCUSWHENF6)
	fprintf( dumpfile, "TPL_FLAG_NOFOCUSWHENF6 " );
	if (wFlags & TPL_FLAG_RENDERPASSTHROUGH)
	fprintf( dumpfile, "TPL_FLAG_RENDERPASSTHROUGH " );
	if (wFlags & TPL_FLAG_NOADDFIELDNAMESTOINDEX)
	fprintf( dumpfile, "TPL_FLAG_NOADDFIELDNAMESTOINDEX " );
    fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "   NotePrivileges  = %u (0x%X)\n",
	    cdDocument.NotePrivileges, cdDocument.NotePrivileges );

    fprintf( dumpfile, "   FormFlags2 = 0x%X: ", cdDocument.FormFlags2 );
    if (cdDocument.FormFlags &  TPL_FLAG_SPARESOK)
    {
	wFlags = cdDocument.FormFlags2;
	if (wFlags & TPL_FLAG_INCLUDEREF)
	    fprintf( dumpfile, "TPL_FLAG_INCLUDEREF " );
	if (wFlags & TPL_FLAG_RENDERREF)
	    fprintf( dumpfile, "TPL_FLAG_RENDERREF " );
	if (wFlags & TPL_FLAG_RENDCOLLAPSE)
	    fprintf( dumpfile, "TPL_FLAG_RENDCOLLAPSE " );
	if (wFlags & TPL_FLAG_EDITONOPEN)
	    fprintf( dumpfile, "TPL_FLAG_EDITONOPEN " );
	if (wFlags & TPL_FLAG_OPENCNTXT)
	    fprintf( dumpfile, "TPL_FLAG_OPENCNTXT " );
	if (wFlags & TPL_FLAG_CNTXTPARENT)
	    fprintf( dumpfile, "TPL_FLAG_CNTXTPARENT " );
	if (wFlags & TPL_FLAG_MANVCREATE)
	    fprintf( dumpfile, "TPL_FLAG_MANVCREATE " );
	if (wFlags & TPL_FLAG_UPDATE_SIBLING)
	    fprintf( dumpfile, "TPL_FLAG_UPDATE_SIBLING " );
	if (wFlags & TPL_FLAG_ANONYMOUS)
	    fprintf( dumpfile, "TPL_FLAG_ANONYMOUS " );
	if (wFlags & TPL_FLAG_NAVIG_DOCLINK_IN_PLACE)
	    fprintf( dumpfile, "TPL_FLAG_NAVIG_DOCLINK_IN_PLACE " );
	if (wFlags & TPL_FLAG_INTERNOTES)
	    fprintf( dumpfile, "TPL_FLAG_INTERNOTES " );
	if (wFlags & TPL_FLAG_DISABLE_FX)
	    fprintf( dumpfile, "TPL_FLAG_DISABLE_FX " );
	if (wFlags & TPL_FLAG_NOMENUS)
		fprintf( dumpfile, "TPL_FLAG_NOMENUS " );
	if (wFlags & TPL_FLAG_CHECKDISPLAY)
		fprintf( dumpfile, "TPL_FLAG_CHECKDISPLAY " );
	if (wFlags & TPL_FLAG_FORMISRTL)
		fprintf( dumpfile, "TPL_FLAG_FORMISRTL " );
	if (wFlags & TPL_FLAG_HIDEBKGRAPHIC)
		fprintf( dumpfile, "TPL_FLAG_HIDEBKGRAPHIC " );
    }
    else
	fprintf( dumpfile, "(n/a)" );
    fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "   InherFieldNameLength  = ");
    if (cdDocument.FormFlags &  TPL_FLAG_SPARESOK)
	fprintf( dumpfile, "%u", cdDocument.InherFieldNameLength );
    else
	fprintf( dumpfile, "(n/a)" );
    fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "   PaperColorExt = " );
    if (cdDocument.FormFlags &  TPL_FLAG_SPARESOK)
    {
	fprintf( dumpfile, "%u", (cdDocument.PaperColorExt & ODS_COLOR_MASK) );
    }
    else
	fprintf( dumpfile, "(n/a)" );
    fprintf( dumpfile, "\n" );
	
	fprintf( dumpfile, "    PaperColorValue\n" );
	DumpColorValue( cdDocument.PaperColorValue );

	wFlags = cdDocument.FormFlags3;
	fprintf( dumpfile, "    FormFlags3 = 0x%X: ", cdDocument.FormFlags3 );
	if( wFlags & TPL_FLAG_RESIZEHEADER )
		fprintf( dumpfile, "TPL_FLAG_RESIZEHEADER " );
	else
		fprintf( dumpfile, "(n/a)" );
	fprintf( dumpfile, "\n" );

    for (wIndex = 0; wIndex < 1; wIndex++)
    {
	fprintf( dumpfile, "   Spare[%d] = ", wIndex);
	if (cdDocument.FormFlags &  TPL_FLAG_SPARESOK)
	    fprintf( dumpfile, "0x%X", cdDocument.Spare[wIndex] );
	else
	    fprintf( dumpfile, "(n/a)" );
	fprintf( dumpfile, "\n" );
    }

    fprintf( dumpfile, "   Inherit Field Name = " );
    if (cdDocument.FormFlags &  TPL_FLAG_SPARESOK)
    {
		if (cdDocument.InherFieldNameLength)
		{
		PrintText( (char far *) p, (DWORD)cdDocument.InherFieldNameLength );
			p = ((char far *) p) + cdDocument.InherFieldNameLength;
			textFieldNameLength -= cdDocument.InherFieldNameLength;
		}
		else
			fprintf ( dumpfile, "\n");
    }
    else
	fprintf( dumpfile, "(n/a)\n" );

	fprintf( dumpfile, "   Text Field Name = " );
	if (textFieldNameLength)
		PrintText ( (char far *) p,     textFieldNameLength );
	else
		fprintf ( dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDMetafile

*************************************************************************/

void  LNPUBLIC   DumpCDMetafile( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  METAFILE\n" );

    return;
}


/************************************************************************

    FUNCTION:   DumpCDBitmap

*************************************************************************/

void  LNPUBLIC   DumpCDBitmap( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  BITMAP\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDFonttable

*************************************************************************/

void  LNPUBLIC   DumpCDFonttable( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDFONTTABLE      cdFontTab;
    CDFACE           cdFace;
    WORD             wIndex;

    fprintf( dumpfile,"  FONTTABLE\n" );

   /* p points to the item value in canonical format after the
      datatype word. The item value starts with a CDFONTTABLE structure.
      Call ODSReadMemory() to convert this CDFONTTABLE to host format and
      store it in cdFontTab. ODSReadMemory() advances p to point
      to the next byte in the input buffer after the CDFONTTABLE.
    */

    ODSReadMemory( &p, _CDFONTTABLE, &cdFontTab, 1 );

    for (wIndex = 0; wIndex < cdFontTab.Fonts; wIndex++)
    {
	ODSReadMemory( &p, _CDFACE, &cdFace, 1 );
	fprintf( dumpfile, "    Font %u:\n", wIndex );
	fprintf( dumpfile, "       Face    = %u\n", cdFace.Face );
	fprintf( dumpfile, "       Family  = %u\n", cdFace.Family );
	fprintf( dumpfile, "       Name    = %s\n", cdFace.Name );
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLink

*************************************************************************/

void  LNPUBLIC   DumpCDLink( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  LINK\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLinkexport

*************************************************************************/

void  LNPUBLIC   DumpCDLinkexport( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  LINKEXPORT\n " );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDKeyword

*************************************************************************/

void  LNPUBLIC   DumpCDKeyword( char *RecordPtr, DWORD RecordLength )
{
    char far *  p = RecordPtr;
    CDKEYWORD   cdKeyword;
	char far *      pOnOff;                 /* Pointer to on/off flag */
	WORD far *      pKeyLen;                /* Pointer into keyword length array */
	WORD            keyCount;               /* Number of keywords in list */
	WORD            keyLen;                 /* Length of current keyword */
	char far *      pName;                  /* Pointer to name */
	WORD            index;                  /* Keyword counter */
	WORD            j;                              /* String counter */

    fprintf (dumpfile, "  KEYWORD\n");

    ODSReadMemory( &p, _CDKEYWORD, &cdKeyword, 1 );

	fprintf( dumpfile, "   FontID = " );
    DumpFontIDFields( (FONTIDFIELDS *)&cdKeyword.FontID );
	fprintf (dumpfile, "    Keywords: %u\n", cdKeyword.Keywords);
	fprintf (dumpfile, "    Flags = 0x%X: ", cdKeyword.Flags);
	if (CDKEYWORD_RADIO & cdKeyword.Flags)
		fprintf (dumpfile, "CDKEYWORD_RADIO ");
	fprintf (dumpfile, "\n");
	fprintf (dumpfile, "    Column: %d\n",
		((cdKeyword.Flags & CDKEYWORD_COLS_MASK) >> CDKEYWORD_COLS_SHIFT));
	fprintf (dumpfile, "    Frame: ");
	switch (cdKeyword.Flags & CDKEYWORD_FRAME_MASK)
	{
		case CDKEYWORD_FRAME_STANDARD:
			fprintf (dumpfile, "CDKEYWORD_FRAME_STANDARD\n");
			break;

		case CDKEYWORD_FRAME_NONE:
			fprintf (dumpfile, "CDKEYWORD_FRAME_NONE\n");
			break;

		case CDKEYWORD_FRAME_3D:
		default:
			fprintf (dumpfile, "CDKEYWORD_FRAME_3D\n");
			break;
	}
	switch (cdKeyword.Flags & CDKEYWORD_FRAME_SHIFT )
	{
		case CDKEYWORD_KEYWORD_RTL:
			fprintf( dumpfile, "KEYWORD_RTL" );
			break;
		case CDKEYWORD_RO_ACTIVE:
			fprintf( dumpfile, "RO_ACTIVE" );
			break;
		default:
			break;
	}

	fprintf (dumpfile, "    Keywords:\n");
	pOnOff = RecordPtr + sizeof (CDKEYWORD);
	pKeyLen = (WORD far *) (pOnOff + cdKeyword.Keywords);
	ODSReadMemory (&pKeyLen, _WORD, &keyCount, 1);
	pName = ((char far *) pKeyLen) + (sizeof (WORD) * (keyCount + 1));
	for (index = 0; index < keyCount; index++)
	{
		fprintf (dumpfile, "      %s ",
			('1' == pOnOff[index]) ? "On: " : "Off:");
		ODSReadMemory (&pKeyLen, _WORD, &keyLen, 1);
		for (j = 0; j < keyLen; j++)
		{
			fputc (*(pName++), dumpfile);
		}
		fputc ('\n', dumpfile);
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLink2

*************************************************************************/

void  LNPUBLIC   DumpCDLink2( char *RecordPtr, DWORD RecordLength )
{
    char far *  p = RecordPtr;
    CDLINK2             cdLink2;
	DWORD           dwLen;

    fprintf( dumpfile, "  LINK2\n" );

    ODSReadMemory( &p, _CDLINK2, &cdLink2, 1 );

    fprintf( dumpfile, "\tLink ID = %u\n", cdLink2.LinkID );
    dwLen = RecordLength - (DWORD)ODSLength(_CDLINK2) ;
    if (dwLen > 0)
    {
	fprintf( dumpfile, "   Display Comment = " );
	PrintText( p, dwLen );
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDCgm

*************************************************************************/

void  LNPUBLIC   DumpCDCgm( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  CGM\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDTiff

*************************************************************************/

void  LNPUBLIC   DumpCDTiff( char *RecordPtr, DWORD RecordLength )
{
    fprintf( dumpfile, "  TIFF\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPatterntable

*************************************************************************/

void  LNPUBLIC   DumpCDPatterntable( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDPATTERNTABLE       CDPatternTable;

    fprintf( dumpfile, "  PATTERNTABLE\n" );

    ODSReadMemory( &p, _CDPATTERNTABLE, &CDPatternTable, 1 );

    fprintf( dumpfile, "    <start of pattern table entries>\n" );
    NSFDDUMPDumpMemory( p, (WORD)(RecordLength-ODSLength(_CDPATTERNTABLE)) );
    fprintf( dumpfile, "    <end of pattern table entries>\n" );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDDdebegin

*************************************************************************/

void  LNPUBLIC   DumpCDDdebegin( char *RecordPtr, DWORD RecordLength )
{
    char far *  p = RecordPtr;
    CDDDEBEGIN  cdDDEBegin;
	char *          szFormat;
	
    fprintf( dumpfile, "  DDEBEGIN\n" );

    ODSReadMemory( &p, _CDDDEBEGIN, &cdDDEBegin, 1 );

    fprintf( dumpfile, "    ServerName        = %s\n",
		cdDDEBegin.ServerName );
    fprintf( dumpfile, "    TopicName         = %s\n",
		cdDDEBegin.TopicName );
    fprintf( dumpfile, "    ItemName          = %s\n",
		cdDDEBegin.ItemName );

	fprintf( dumpfile, "    Flags             = 0x%X: ",
				cdDDEBegin.Flags );
	if (DDEFLAGS_AUTOLINK & cdDDEBegin.Flags)
		fprintf( dumpfile, "AUTOLINK ");
	if (DDEFLAGS_MANUALLINK & cdDDEBegin.Flags)
		fprintf( dumpfile, "MANUALLINK ");
	if (DDEFLAGS_EMBEDDED & cdDDEBegin.Flags)
		fprintf( dumpfile, "EMBEDDED ");
	if (DDEFLAGS_INITIATE & cdDDEBegin.Flags)
		fprintf( dumpfile, "INITIATE ");
	if (DDEFLAGS_CDP & cdDDEBegin.Flags)
		fprintf( dumpfile, "CDP ");
	if (DDEFLAGS_NOTES_LAUNCHED & cdDDEBegin.Flags)
		fprintf( dumpfile, "NOTES_LAUNCHED ");
	if (DDEFLAGS_CONV_ACTIVE & cdDDEBegin.Flags)
		fprintf( dumpfile, "CONV_ACTIVE ");
	if (DDEFLAGS_EMBEDEXTRACTED & cdDDEBegin.Flags)
		fprintf( dumpfile, "EMBEDEXTRACTED ");
	if (DDEFLAGS_NEWOBJECT & cdDDEBegin.Flags)
		fprintf( dumpfile, "NEWOBJECT ");
	fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "    PasteEmbedDocName = %s\n",
		cdDDEBegin.PasteEmbedDocName );
    fprintf( dumpfile, "    EmbeddedDocCount  = %u\n",
		cdDDEBegin.EmbeddedDocCount );

    szFormat = GetLiteralString( DDEFormatTable, cdDDEBegin.ClipFormat );
    fprintf( dumpfile, "    ClipFormat (%u) = %s\n",
		cdDDEBegin.ClipFormat, szFormat );
	
	fprintf( dumpfile, "    Embedded document name = %s\n", p );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDDdeend

*************************************************************************/

void  LNPUBLIC   DumpCDDdeend( char *RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDDDEEND         cdDDEEnd;
	
    fprintf( dumpfile, "  DDEEND\n" );

    ODSReadMemory( &p, _CDDDEEND, &cdDDEEnd, 1 );

    fprintf( dumpfile, "    Flags               = 0x%lX\n",
		cdDDEEnd.Flags );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOlebegin

*************************************************************************/

void  LNPUBLIC   DumpCDOlebegin( char *RecordPtr, DWORD RecordLength )
{
    char far *  p = RecordPtr;
	CDOLEBEGIN      cdOleBegin;

    fprintf (dumpfile, "  OLEBEGIN\n");

    ODSReadMemory (&p, _CDOLEBEGIN, &cdOleBegin, 1);

	fprintf (dumpfile, "    (Notes) Version = %u\n", cdOleBegin.Version);

	fprintf (dumpfile, "    Flags = 0x%X: ", cdOleBegin.Flags);
	if (OLEREC_FLAG_OBJECT & cdOleBegin.Flags)
		fprintf (dumpfile, "OBJECT ");
	if (OLEREC_FLAG_LINK & cdOleBegin.Flags)
		fprintf (dumpfile, "LINK ");
	if (OLEREC_FLAG_AUTOLINK & cdOleBegin.Flags)
		fprintf (dumpfile, "AUTOLINK ");
	if (OLEREC_FLAG_MANUALLINK & cdOleBegin.Flags)
		fprintf (dumpfile, "MANUALLINK ");
	if (OLEREC_FLAG_NEWOBJECT & cdOleBegin.Flags)
		fprintf (dumpfile, "NEWOBJECT ");
	if (OLEREC_FLAG_PASTED & cdOleBegin.Flags)
		fprintf (dumpfile, "PASTED ");
	if (OLEREC_FLAG_SAVEOBJWHENCHANGED & cdOleBegin.Flags)
		fprintf (dumpfile, "SAVEOBJWHENCHANGED ");
	if (OLEREC_FLAG_NOVISUALIZE & cdOleBegin.Flags)
		fprintf (dumpfile, "NOVISUALIZE ");
	fprintf (dumpfile, "\n");

    fprintf( dumpfile, "    ClipFormat = %u: ",
		cdOleBegin.ClipFormat );
	switch (cdOleBegin.ClipFormat)
	{
		case DDEFORMAT_TEXT:
			fprintf( dumpfile, "TEXT\n" );
			break;
		
		case DDEFORMAT_METAFILE:
			fprintf( dumpfile, "METAFILE\n" );
			break;
		
		case DDEFORMAT_BITMAP:
			fprintf( dumpfile, "BITMAP\n" );
			break;
		
		case DDEFORMAT_RTF:
			fprintf( dumpfile, "RTF\n" );
			break;
		
		case DDEFORMAT_OWNERLINK:
			fprintf( dumpfile, "OWNERLINK\n" );
			break;
		
		case DDEFORMAT_OBJECTLINK:
			fprintf( dumpfile, "OBJECTLINK\n" );
			break;
		
		case DDEFORMAT_NATIVE:
			fprintf( dumpfile, "NATIVE\n" );
			break;
		
		case DDEFORMAT_ICON:
			fprintf( dumpfile, "ICON\n" );
			break;
		
		default:
			fprintf( dumpfile, "Unknown\n" );
			break;
	}

	fprintf (dumpfile, "    AttachNameLength = %u\n",
		cdOleBegin.AttachNameLength);
	fprintf (dumpfile, "    ClassNameLength = %u\n",
		cdOleBegin.ClassNameLength);
	fprintf (dumpfile, "    TemplateNameLength = %u\n",
		cdOleBegin.TemplateNameLength);

	fprintf (dumpfile, "    Attachment Name = ");
    PrintText( (char far *)p, cdOleBegin.AttachNameLength );
    p = ( ((char far *)p) + cdOleBegin.AttachNameLength );

	if (cdOleBegin.ClassNameLength)
	{
		fprintf (dumpfile, "    Class Name = ");
		PrintText( (char far *)p, cdOleBegin.ClassNameLength );
		p = ( ((char far *)p) + cdOleBegin.ClassNameLength );
	}

	if (cdOleBegin.TemplateNameLength)
	{
		fprintf (dumpfile, "    Template Name = ");
		PrintText( (char far *)p, cdOleBegin.TemplateNameLength );
		p = ( ((char far *)p) + cdOleBegin.TemplateNameLength );
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOleend

*************************************************************************/

void  LNPUBLIC   DumpCDOleend( char *RecordPtr, DWORD RecordLength )
{
    char far *  p = RecordPtr;
	CDOLEEND        cdOleEnd;

    fprintf (dumpfile, "  OLEEND\n");

    ODSReadMemory( &p, _CDOLEEND, &cdOleEnd, 1 );

	fprintf (dumpfile, "    Flags (unused) = 0x%X\n",
		cdOleEnd.Flags);

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHotspotbegin

*************************************************************************/

void  LNPUBLIC   DumpCDHotspotbegin (
	char *  RecordPtr,
	DWORD   RecordLength,
	WORD    RecordType )
{
    char far *       p = RecordPtr;
    CDHOTSPOTBEGIN   cdHotSpot;
    DWORD            dwFlags;
    WORD             i;
    char *           szHotSpotType;

/* Hotspot type table moved to beginning of source file! */

	if (SIG_CD_HOTSPOTBEGIN == RecordType)
		fprintf( dumpfile, "  HOTSPOTBEGIN\n" );
	else if (SIG_CD_V4HOTSPOTBEGIN == RecordType)
		fprintf( dumpfile, "  V4HOTSPOTBEGIN\n" );
	else if (SIG_CD_V5HOTSPOTBEGIN == RecordType)
		fprintf( dumpfile, "  V5HOTSPOTBEGIN\n");
	else if (SIG_CD_V6HOTSPOTBEGIN_CONTINUATION == RecordType)
		fprintf( dumpfile, "  V6HOTSPOTBEGIN_CONTINUATION\n");
	else
	{
		fprintf( dumpfile, "  Unknown hotspot type: %u (0x%X)\n",
			RecordType, RecordType );
		return;
	}

    ODSReadMemory( &p, _CDHOTSPOTBEGIN, &cdHotSpot, 1 );

    for (i=0;i<NUM_HOTSPOT_TYPES;i++)
    {
	if(cdHotSpot.Type == HotSpotTypeTable[i].wHotSpotType)
	{
	    szHotSpotType = HotSpotTypeTable[i].szTypeStr;
	    break;
	}
    }
    if (i==NUM_HOTSPOT_TYPES)
    {
	szHotSpotType = "Unknown";
    }
    fprintf( dumpfile, "    Type (0x%X) = %s\n", cdHotSpot.Type, szHotSpotType );

    dwFlags = cdHotSpot.Flags;
    fprintf( dumpfile, "    Flags = 0x%X: ", dwFlags );
    if (dwFlags & HOTSPOTREC_RUNFLAG_BEGIN)         fprintf( dumpfile, "BEGIN " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_END)           fprintf( dumpfile, "END " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_BOX)           fprintf( dumpfile, "BOX " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_NOBORDER)      fprintf( dumpfile, "NOBORDER " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_FORMULA)       fprintf( dumpfile, "FORMULA " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_MOVIE)         fprintf( dumpfile, "MOVIE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_IGNORE)        fprintf( dumpfile, "IGNORE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ACTION)        fprintf( dumpfile, "ACTION " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_SCRIPT)        fprintf( dumpfile, "SCRIPT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_INOTES)        fprintf( dumpfile, "INOTES " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ISMAP)         fprintf( dumpfile, "ISMAP " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_INOTES_AUTO)   fprintf( dumpfile, "INOTES_AUTO " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ISMAP_INPUT)   fprintf( dumpfile, "ISMAP_INPUT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_SIGNED)        fprintf( dumpfile, "SIGNED " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ANCHOR)        fprintf( dumpfile, "ANCHOR " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_COMPUTED)	    fprintf( dumpfile, "COMPUTED " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_TEMPLATE)      fprintf( dumpfile, "TEMPLATE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_HIGHLIGHT)     fprintf( dumpfile, "HIGHLIGHT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_EXTACTION)     fprintf( dumpfile, "EXTACTION " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_NAMEDELEM)     fprintf( dumpfile, "NAMEDELEM " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_WEBJAVASCRIPT) fprintf( dumpfile, "WEBJAVASCRIPT " );
    fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "    Data Length = %u\n", cdHotSpot.DataLength );

    if (cdHotSpot.DataLength==0)
	return;

		/* Figure out what kind of information is stored for this hotspot */
	if (HOTSPOTREC_TYPE_ACTIVEOBJECT == cdHotSpot.Type)
	{
		fprintf (dumpfile, "    Hot Spot Active Object =\n");
		DumpActiveObject (p, cdHotSpot.DataLength);
	}
	else if (HOTSPOTREC_TYPE_OLERICHTEXT == cdHotSpot.Type)
	{
		fprintf (dumpfile, "    Hot Spot OLE Rich Text Object =\n");
		DumpHSOleRichText (p, cdHotSpot.DataLength);
	}
	else if (dwFlags & HOTSPOTREC_RUNFLAG_ACTION)
	{
		fprintf (dumpfile, "    Hot Spot Action =\n");
		PrintNotesActions (p, cdHotSpot.DataLength);
	}
	else if (dwFlags & HOTSPOTREC_RUNFLAG_SCRIPT)
	{
			/* Print the Lotus Script source (if available) */
		fprintf( dumpfile, "    Hot Spot Script =\n" );
		PrintScriptSource (p, cdHotSpot.DataLength);
	}
    else if ((dwFlags & HOTSPOTREC_RUNFLAG_FORMULA)
		|| (cdHotSpot.Type == HOTSPOTREC_TYPE_BUTTON))
	{
			/* Print the formula */
		fprintf( dumpfile, "    Hot Spot Formula =\n" );
		PrintFormula ( p, cdHotSpot.DataLength );
	}
    else  /* data is text */
    {
	fprintf( dumpfile, "    Hot Spot Data : \n" );
	PrintText( (char far *)p,  cdHotSpot.DataLength );
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHotspotend

*************************************************************************/

void  LNPUBLIC   DumpCDHotspotend (
	char *  RecordPtr,
	DWORD   RecordLength,
	WORD    RecordType )
{
	if (SIG_CD_HOTSPOTEND == RecordType)
		fprintf( dumpfile, "  HOTSPOTEND\n" );
	else if (SIG_CD_V4HOTSPOTEND == RecordType)
		fprintf( dumpfile, "  V4HOTSPOTEND\n" );
	else if (SIG_CD_V5HOTSPOTEND == RecordType)
		fprintf( dumpfile, "  V5HOTSPOTEND\n");
	else
	{
		fprintf( dumpfile, "  Unknown hotspot type: %u (0x%X)\n",
			RecordType, RecordType );
		return;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDButton

*************************************************************************/

void  LNPUBLIC   DumpCDButton( char *RecordPtr, DWORD RecordLength )
{
    char far *    p = RecordPtr;
    CDBUTTON      cdButton;
    WORD          wFlags;

    fprintf( dumpfile, "  BUTTON\n" );

    ODSReadMemory( &p, _CDBUTTON, &cdButton, 1 );

    wFlags = cdButton.Flags;
    fprintf( dumpfile, "    Flags = 0x%X: ", wFlags );

	/* New flags introduced in Domino 5.03 */
	if (wFlags & BUTTON_UNUSED)				  fprintf( dumpfile, "UNUSED " );
	if (wFlags & BUTTON_RUNFLAG_SCRIPT)		  fprintf( dumpfile, "SCRIPT " );
	if (wFlags & BUTTON_RUNFLAG_NOWRAP)		  fprintf( dumpfile, "NOWRAP " );
	if (wFlags & BUTTON_ODS_MASK)			  fprintf( dumpfile, "ODS_MASK " );
	if (wFlags & BUTTON_RUNFLAG_RTL)		  fprintf( dumpfile, "RTL " );
	if (wFlags & BUTTON_RUNFLAG_FIXED)		  fprintf( dumpfile, "FIXED ");
	if (wFlags & BUTTON_RUNFLAG_MINIMUM)	  fprintf( dumpfile, "MINIMUM " );
	if (wFlags & BUTTON_RUNFLAG_CONTENT)	  fprintf( dumpfile, "CONTENT " );
	if (wFlags & BUTTON_RUNFLAG_PROPORTIONAL) fprintf( dumpfile, "PROPORTIONAL " );       /* New for Notes/Domino 6 */
	if (wFlags & BUTTON_FOCUS_ON)			  fprintf( dumpfile, "FOCUS_ON " );			  /* New for Notes/Domino 6 */
	if (wFlags & BUTTON_RUNFLAG_WIDTH_MASK)   fprintf( dumpfile, "WIDTH_MASK " );
	if (wFlags & BUTTON_EDGE_ROUNDED)		  fprintf( dumpfile, "EDGE_ROUNDED " );       /* New for Notes/Domino 6 */
	if (wFlags & BUTTON_EDGE_SQUARE)		  fprintf( dumpfile, "BUTTON_EDGE_SQUARE " ); /* New for Notes/Domino 6 */
	fprintf( dumpfile, "\n" );

    fprintf( dumpfile, "    Width  = %u\n", cdButton.Width );
    fprintf( dumpfile, "    Height = %u\n", cdButton.Height );
    fprintf( dumpfile, "    Lines  = %u\n", cdButton.Lines );
	fprintf( dumpfile, "   FontID = " );
    DumpFontIDFields( (FONTIDFIELDS *)&cdButton.FontID );

    fprintf( dumpfile, "    Button text = ");
    PrintText( (char far *)p, RecordLength - ODSLength(_CDBUTTON) );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDBar

*************************************************************************/

void    LNPUBLIC  DumpCDBar( char * RecordPtr, DWORD RecordLength )
{
    char far *       p = RecordPtr;
    CDBAR                cdBar;
    DWORD            dwFlags;
	WORD                 dataLen;

    fprintf (dumpfile, "  BAR\n");

    ODSReadMemory (&p, _CDBAR, &cdBar, 1);
	dataLen = (WORD) RecordLength - ODSLength (_CDBAR);
    dwFlags = cdBar.Flags;

    fprintf (dumpfile, "    Flags = 0x%X: ", dwFlags);
    if (dwFlags & BARREC_DISABLED_FOR_NON_EDITORS) fprintf (dumpfile, "DISABLED_FOR_NON_EDITORS ");
    if (dwFlags & BARREC_EXPANDED)          fprintf (dumpfile, "EXPANDED ");
    if (dwFlags & BARREC_PREVIEW)           fprintf (dumpfile, "PREVIEW ");
    if (dwFlags & BARREC_BORDER_INVISIBLE)  fprintf (dumpfile, "BORDER_INVISIBLE ");
    if (dwFlags & BARREC_ISFORMULA)         fprintf (dumpfile, "ISFORMULA ");
    if (dwFlags & BARREC_HIDE_EXPANDED)     fprintf (dumpfile, "HIDE_EXPANDED ");
    if (dwFlags & BARREC_AUTO_EXP_READ)     fprintf (dumpfile, "AUTO_EXP_READ ");
    if (dwFlags & BARREC_AUTO_EXP_PRE)      fprintf (dumpfile, "AUTO_EXP_PRE ");
    if (dwFlags & BARREC_AUTO_EXP_EDIT)     fprintf (dumpfile, "AUTO_EXP_EDIT ");
    if (dwFlags & BARREC_AUTO_EXP_PRINT)    fprintf (dumpfile, "AUTO_EXP_PRINT ");
    if (dwFlags & BARREC_AUTO_COL_READ)     fprintf (dumpfile, "AUTO_COL_READ ");
    if (dwFlags & BARREC_AUTO_COL_PRE)      fprintf (dumpfile, "AUTO_COL_PRE ");
    if (dwFlags & BARREC_AUTO_COL_EDIT)     fprintf (dumpfile, "AUTO_COL_EDIT ");
    if (dwFlags & BARREC_AUTO_COL_PRINT)    fprintf (dumpfile, "AUTO_COL_PRINT ");
    if (dwFlags & BARREC_AUTO_ED_EXP_READ)  fprintf (dumpfile, "AUTO_ED_EXP_READ ");
    if (dwFlags & BARREC_AUTO_ED_EXP_PRE)   fprintf (dumpfile, "AUTO_ED_EXP_PRE ");
    if (dwFlags & BARREC_AUTO_ED_EXP_EDIT)  fprintf (dumpfile, "AUTO_ED_EXP_EDIT ");
    if (dwFlags & BARREC_AUTO_ED_EXP_PRINT) fprintf (dumpfile, "AUTO_ED_EXP_PRINT ");
    if (dwFlags & BARREC_AUTO_ED_COL_READ)  fprintf (dumpfile, "AUTO_ED_COL_READ ");
    if (dwFlags & BARREC_AUTO_ED_COL_PRE)   fprintf (dumpfile, "AUTO_ED_COL_PRE ");
    if (dwFlags & BARREC_AUTO_ED_COL_EDIT)  fprintf (dumpfile, "AUTO_ED_COL_EDIT ");
    if (dwFlags & BARREC_AUTO_ED_COL_PRINT) fprintf (dumpfile, "AUTO_ED_COL_PRINT ");
    if (dwFlags & BARREC_INTENDED)          fprintf (dumpfile, "INTENDED ");
    if (dwFlags & BARREC_HAS_COLOR)         fprintf (dumpfile, "HAS_COLOR ");
    if (dwFlags & BARREC_INDENTED)          fprintf (dumpfile, "INDENTED ");
    fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    Border Type (%d) = %s\n", GETBORDERTYPE (dwFlags),
		GetLiteralString (BarRecBorderTable, GETBORDERTYPE (dwFlags)));

	fprintf (dumpfile, "    FontID = ");
    DumpFontIDFields ((FONTIDFIELDS *) (&cdBar.FontID));

		/* Check for a color value */
	if (dwFlags & BARREC_HAS_COLOR)
	{
		WORD              color;

		ODSReadMemory (&p, _WORD, &color, 1);
		fprintf (dumpfile, "    Color = %d\n", color);
		dataLen -= ODSLength (_WORD);
	}

	if (dwFlags & BARREC_ISFORMULA)
	{
		fprintf (dumpfile, "    Formula =\n");
		PrintFormula (p, dataLen);
		p = ((char FAR *) p) + dataLen;
	}
	else
	{
		fprintf (dumpfile, "    Title = ");
		PrintText ((char far *)p, dataLen);
		p = ((char FAR *) p) + dataLen;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDExtfield

*************************************************************************/

void    LNPUBLIC  DumpCDExtfield( char * RecordPtr, DWORD RecordLength )
{
    char far *      p = RecordPtr;
    CDEXTFIELD          cdExtField;
	DWORD                   dwFlags1;
	DWORD                   dwFlags2;
	char            *       pString;
	static char     *       FrameStrings [] = {"3D", "STANDARD", "NONE", "Invalid"};
	static char     *       HelperStrings [] = {"NONE", "ADDRDLG", "ACLDLG", "VIEWDLG"};

    fprintf( dumpfile, "  EXTFIELD\n" );

	ODSReadMemory( &p, _CDEXTFIELD, &cdExtField, 1 );
	dwFlags1 = cdExtField.Flags1;
	dwFlags2 = cdExtField.Flags2;

    fprintf( dumpfile, "    Flags1 = 0x%lX: ", dwFlags1 );
    if (dwFlags1 & FEXT_LOOKUP_EACHCHAR)        fprintf( dumpfile, "LOOKUP_EACHCHAR " );
    if (dwFlags1 & FEXT_KWSELRECALC)            fprintf( dumpfile, "KWSELRECALC " );
    if (dwFlags1 & FEXT_KWHINKYMINKY)           fprintf( dumpfile, "KWHINKYMINKY " );
    if (dwFlags1 & FEXT_AFTERVALIDATION)        fprintf( dumpfile, "AFTERVALIDATION " );
    if (dwFlags1 & FEXT_ACCEPT_CARET)           fprintf( dumpfile, "ACCEPT_CARET " );
    if (dwFlags1 & FEXT_KEYWORDS_UI_COMBO)      fprintf( dumpfile, "UI_COMBO " );
    if (dwFlags1 & FEXT_KEYWORDS_UI_LIST)       fprintf( dumpfile, "UI_LIST " );
    fprintf( dumpfile, "\n" );

	fprintf( dumpfile, "    Column value: %u\n",
		((dwFlags1 & FEXT_KEYWORD_COLS_MASK) >> FEXT_KEYWORD_COLS_SHIFT));

	pString = FrameStrings
		[(dwFlags1 & FEXT_KEYWORD_FRAME_MASK) >> FEXT_KEYWORD_FRAME_SHIFT];
	fprintf( dumpfile, "    Frame type = %s\n", pString);

    fprintf( dumpfile, "    Flags2 = 0x%lX: ", dwFlags2 );
    if (dwFlags2 & FEXT_KW_CHOICE_RECALC)   fprintf( dumpfile, "KW_CHOICE_RECALC " );
	if (dwFlags2 & FEXT_HTML_IN_FIELDDEF)   fprintf( dumpfile, "HTML_IN_FIELDDEF ");
	if (dwFlags2 & FEXT_HIDEDELIMITERS)		fprintf( dumpfile, "HIDEDELIMITERS " );
	if (dwFlags2 & FEXT_KW_RTL_READING_ORDER)	fprintf( dumpfile, "KW_RTL_READING_ORDER " );
	if (dwFlags2 & FEXT_USEAPPLETINBROWSER)	fprintf( dumpfile, "USEAPPLETINBROWSER " );
	if (dwFlags2 & FEXT_CONTROL)			fprintf( dumpfile, "CONTROL " );
	if (dwFlags2 & FEXT_LITERALIZE)			fprintf( dumpfile, "LITERALIZE " );
	if (dwFlags2 & FEXT_CONTROLDYNAMIC)		fprintf( dumpfile, "CONTROLDYNAMIC " );
	if (dwFlags2 & FEXT_CONTROL)	     	fprintf( dumpfile, "CONTROL " );
	if (dwFlags2 & FEXT_RUNEXITINGONCHANGE)	fprintf( dumpfile, "RUNEXITINGONCHANGE " );
	if (dwFlags2 & FEXT_TIMEZONE)	     	fprintf( dumpfile, "TIMEZONE " );	
	if (dwFlags2 & FEXT_PROPORTIONALHEIGHT)	fprintf( dumpfile, "PROPORTIONALHEIGHT " );	
	if (dwFlags2 & FEXT_PROPORTIONALWIDTH)	fprintf( dumpfile, "PROPORTIONALWIDTH " );	
    fprintf( dumpfile, "\n" );

	if (FIELD_HELPER_VIEWDLG <= cdExtField.EntryHelper)
	{
		pString = HelperStrings[cdExtField.EntryHelper];
		fprintf ( dumpfile, "    Helper type: %s\n", pString);
	}
	else
	{
		fprintf ( dumpfile, "    Helper type: UNKNOWN - 0x%X\n", cdExtField.EntryHelper);
	}

	if (0 != cdExtField.EntryDBNameLen)
	{
		fprintf ( dumpfile, "    Entry helper DB name = ");
		PrintText( (char far *)p, cdExtField.EntryDBNameLen);
		p = ((char far *) p) + cdExtField.EntryDBNameLen;
	}

	if (0 != cdExtField.EntryViewNameLen)
	{
		fprintf ( dumpfile, "    Entry helper view name = ");
		PrintText( (char far *)p, cdExtField.EntryViewNameLen);
		p = ((char far *) p) + cdExtField.EntryViewNameLen;
	}

	fprintf ( dumpfile, "    Entry helper column number = %d\n",
		cdExtField.EntryColumnNumber);

		/* Is there an HTML formula following this record? */
	if (dwFlags2 & FEXT_HTML_IN_FIELDDEF)
	{
		WORD            htmlLength;
		WORD            wSpareFlags;
		WORD            wTrueLength;

		ODSReadMemory (&p, _WORD, &htmlLength, 1);              /* Read the HTML formula length */
		ODSReadMemory (&p, _WORD, &wSpareFlags, 1);             /* Read the spare flags word */

			/* If this field is edited by someone using a release of                 */
			/* Domino and Notes prior to 4.6, this record may be truncated.          */
		    /* If that happens, Domino and Notes ignores the (missing) HTML formula. */
		wTrueLength = ODSLength (_CDEXTFIELD) + cdExtField.EntryDBNameLen
			+ cdExtField.EntryViewNameLen + (2 * ODSLength (_WORD)) + htmlLength;

		if (wTrueLength > cdExtField.Header.Length)
		{
			fprintf (dumpfile, "    Record overwritten by Notes prior to 4.6.\n");
			fprintf (dumpfile, "    HTML formula was lost.\n");
			fprintf (
				dumpfile,
				"		Header length=%d  True length=%d  HTML length=%d\n",
				cdExtField.Header.Length,
				wTrueLength,
				htmlLength);
		}
		else
		{
			fprintf (dumpfile, "    HTML formula length = %d\n", htmlLength);
			fprintf (dumpfile, "    HTML formula = ");
			PrintFormula (p, htmlLength);
			p = ((char far *) p) + htmlLength;
		}
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPabhide

*************************************************************************/

void    LNPUBLIC  DumpCDPabhide( char * RecordPtr, DWORD RecordLength )
{
    char far *      p = RecordPtr;
    CDPABHIDE           cdPABHide;

    fprintf( dumpfile, "  PABHIDE\n" );

	ODSReadMemory( &p, _CDPABHIDE, &cdPABHide, 1 );

#ifndef APITESTMODE
	fprintf ( dumpfile, "    PABID = %u\n", cdPABHide.PABID);
#endif

		/* Decompile and print the Hide When formula */
	fprintf ( dumpfile, "    Hide When Formula =\n" );
	PrintFormula ( p, ((WORD) (RecordLength - ODSLength(_CDPABHIDE))) );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDPabformref

*************************************************************************/

void    LNPUBLIC  DumpCDPabformref( char * RecordPtr, DWORD RecordLength )
{
    char far *      p = RecordPtr;
    CDPABFORMULAREF     cdPABFormRef;

    fprintf( dumpfile, "  PABFORMREF\n" );

    ODSReadMemory( &p, _CDPABFORMULAREF, &cdPABFormRef, 1 );

#ifndef APITESTMODE
	fprintf ( dumpfile, "    Source PABID = %u\n", (unsigned int) cdPABFormRef.SourcePABID);
	fprintf ( dumpfile, "    Dest PABID = %u\n", (unsigned int) cdPABFormRef.DestPABID);
#endif

    return;
}

/************************************************************************

    FUNCTION:   DumpCDAction

*************************************************************************/

void    LNPUBLIC  DumpCDAction( char * RecordPtr, DWORD RecordLength )
{
    char far *          p = RecordPtr;


    CDACTION            cdAction;
	DWORD                   dataLen;

    fprintf (dumpfile, "  ACTION\n");

    ODSReadMemory (&p, _CDACTION, &cdAction, 1);

	fprintf (dumpfile, "    Type       = %s\n",
		GetLiteralString (ActionTypeTable, cdAction.Type));
	fprintf (dumpfile, "    IconIndex  = %hu\n", cdAction.IconIndex);
    fprintf (dumpfile, "    Flags = 0x%lX: ",  cdAction.Flags);
    if (cdAction.Flags & ACTION_SHOW_IN_MENU)
		fprintf (dumpfile, "SHOW_IN_MENU " );
    if (cdAction.Flags & ACTION_SHOW_IN_BAR)
		fprintf (dumpfile, "SHOW_IN_BAR " );
    if (cdAction.Flags & ACTION_SHOW_WHEN_PREVIEWING)
		fprintf (dumpfile, "SHOW_WHEN_PREVIEWING " );
    if (cdAction.Flags & ACTION_SHOW_WHEN_READING)
		fprintf (dumpfile, "SHOW_WHEN_READING " );
    if (cdAction.Flags & ACTION_SHOW_WHEN_EDITING)
		fprintf (dumpfile, "SHOW_WHEN_EDITING " );
    if (cdAction.Flags & ACTION_SHOW_ON_OLE_LAUNCH)
		fprintf (dumpfile, "SHOW_ON_OLE_LAUNCH " );
    if (cdAction.Flags & ACTION_SHOW_WHEN_PREVEDITING)
		fprintf (dumpfile, "SHOW_WHEN_PREVEDITING " );
    if (cdAction.Flags & ACTION_OLE_CLOSE_WHEN_CHOSEN)
		fprintf (dumpfile, "OLE_CLOSE_WHEN_CHOSEN " );
    if (cdAction.Flags & ACTION_NO_FORMULA)
		fprintf (dumpfile, "NO_FORMULA " );
    if (cdAction.Flags & ACTION_OLE_DOC_WINDOW_TO_FRONT)
		fprintf (dumpfile, "OLE_DOC_WINDOW_TO_FRONT " );
    if (cdAction.Flags & ACTION_HIDE_FROM_NOTES)
		fprintf (dumpfile, "HIDE_FROM_NOTES " );
    if (cdAction.Flags & ACTION_HIDE_FROM_WEB)
		fprintf (dumpfile, "HIDE_FROM_WEB " );
	if (cdAction.Flags & ACTION_READING_ORDER_RTL )
		fprintf( dumpfile, "READING_ORDER_RTL " );
	if (cdAction.Flags & ACTION_SHARED )
		fprintf( dumpfile, "SHARED " );
	if (cdAction.Flags & ACTION_MODIFIED )
		fprintf( dumpfile, "MODIFIED " );
	if (cdAction.Flags & ACTION_ALWAYS_SHARED )
		fprintf( dumpfile, "ALWAYS_SHARED " );
	if (cdAction.Flags & ACTION_ALIGN_ICON_RIGHT )
		fprintf( dumpfile, "ALIGN_ICON_RIGHT " );
	if (cdAction.Flags & ACTION_IMAGE_RESOURCE_ICON )
		fprintf( dumpfile, "IMAGE_RESOURCE_ICON " );
	if (cdAction.Flags & ACTION_FRAME_TARGET)
		fprintf( dumpfile, "FRAME_TARGET " );
	if (cdAction.Flags & ACTION_TEXT_ONLY_IN_MENU)
		fprintf( dumpfile, "TEXT_ONLY_IN_MENU " );
	if (cdAction.Flags & ACTION_BUTTON_TO_RIGHT )
		fprintf( dumpfile, "BUTTON_TO_RIGHT " );
	if (cdAction.Flags & ACTION_HIDE_FROM_MOBILE )
		fprintf( dumpfile, "HIDE_FROM_MOBILE " );
	fprintf (dumpfile, "\n" );
	fprintf (dumpfile, "    TitleLen   = %hu\n", cdAction.TitleLen);
	fprintf (dumpfile, "    FormulaLen = %hu\n", cdAction.FormulaLen);
	fprintf (dumpfile, "    ShareId    = %hu\n", cdAction.ShareId);

	if (0 != cdAction.TitleLen)
	{
		fprintf (dumpfile, "    Title      = ");
		PrintText ((char far *) p, cdAction.TitleLen);
		p = ((char far *) p) + cdAction.TitleLen + (1 & cdAction.TitleLen);
								/* Account for any padding */
	}

	dataLen = RecordLength - ODSLength (_CDACTION)
		- cdAction.TitleLen - (1 & cdAction.TitleLen)
		- cdAction.FormulaLen - (1 & cdAction.FormulaLen);

	fprintf (dumpfile, "    Action ");
	switch (cdAction.Type)
	{
		case ACTION_RUN_FORMULA:                /* Contains a formula */
			fprintf (dumpfile, "Formula:\n");
			PrintFormula (p, (WORD) dataLen);
			break;

		case ACTION_RUN_SCRIPT:                 /* Contains Lotus Script */
			fprintf (dumpfile, "Script:\n");
			PrintScriptSource (p, dataLen);
			break;
		case ACTION_RUN_JAVASCRIPT:
			fprintf( dumpfile, "  <Begin Java Script source>\n" );
			PrintText( p, (WORD) dataLen );
			fprintf( dumpfile, "  <End Java Script source>\n" );
			break;
		case ACTION_RUN_AGENT:                  /* Contains Action records */
			fprintf (dumpfile, "Notes Actions: \n");
			PrintNotesActions (p, dataLen);
			break;

		case ACTION_OLDSYS_COMMAND:             /* Old command codes */
		case ACTION_SYS_COMMAND:                /* New command codes */
			{
				WORD    command [2] = {0, 0};

				ODSReadMemory (&p, _WORD, command, 2);
				fprintf (dumpfile, "command code:  %d, %d",
					command[0], command[1]);
				if (command[1] == ACTION_SYS_CMD_CATEGORIZE)
 				    fprintf (dumpfile, " - Categorize\n");
				if (command[1] == ACTION_SYS_CMD_EDIT)
 				    fprintf (dumpfile, " - Edit Document\n");
				if (command[1] == ACTION_SYS_CMD_SEND)
 				    fprintf (dumpfile, " - Send Document\n");
				if (command[1] == ACTION_SYS_CMD_FORWARD)
 				    fprintf (dumpfile, " - Forward\n");
				if (command[1] == ACTION_SYS_CMD_MOVE_TO_FOLDER)
 				    fprintf (dumpfile, " - Move To Folder\n");
				if (command[1] == ACTION_SYS_CMD_REMOVE_FROM_FOLDER)
 				    fprintf (dumpfile, " - Remove From Folder\n");
				else
   			        fprintf (dumpfile, "\n");
				break;
			}

		case ACTION_PLACEHOLDER:                /* Placeholder (???) */
			fprintf (dumpfile, "PLACEHOLDER\n");
			break;

		default:                /* Unknown code */
			fprintf (dumpfile, "type unknown: %d (0x%X)\n", cdAction.Type, cdAction.Type);
			break;
	}

	p = ((char far *) p) + dataLen;

	if ((0 != cdAction.FormulaLen) && (0 == (cdAction.Flags & ACTION_NO_FORMULA)))
	{
		fprintf (dumpfile, "    Formula    = ");
		PrintFormula (p, cdAction.FormulaLen);
		p = ((char far *) p) + cdAction.FormulaLen + (1 & cdAction.FormulaLen);
								/* Account for any padding */
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDActionbar

*************************************************************************/

void    LNPUBLIC  DumpCDActionbar( char * RecordPtr, DWORD RecordLength )
{
    char far *          p = RecordPtr;
    CDACTIONBAR         cdActionBar;

    fprintf (dumpfile, "  ACTIONBAR\n");

    ODSReadMemory (&p, _CDACTIONBAR, &cdActionBar, 1);

    fprintf (dumpfile, "    BackColor   = %hu\n", cdActionBar.BackColor);
	fprintf (dumpfile, "    LineColor   = %hu\n", cdActionBar.LineColor);
	fprintf (dumpfile, "    LineStyle   = %s\n",
		GetLiteralString (ActionBarLineTable, cdActionBar.LineStyle));
	fprintf (dumpfile, "    BorderStyle = %s\n",
		GetLiteralString (ActionBarBorderTable, cdActionBar.BorderStyle));
	fprintf (dumpfile, "    BorderWidth = %hu\n", cdActionBar.BorderWidth);

#ifndef APITESTMODE
    fprintf (dumpfile, "    dwFlags = 0x%lX: ",  cdActionBar.dwFlags);
    if (cdActionBar.dwFlags & ACTION_BAR_FLAG_NO_SYS_COLOR)
		fprintf (dumpfile, "NO_SYS_COLOR " );
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_ALIGN_RIGHT)
		fprintf (dumpfile, "ALIGN_RIGHT ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_TRANS_BUTTONS)
		fprintf (dumpfile, "TRANS_BUTTONS ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_SYS_BUTTONS)
		fprintf (dumpfile, "SYS_BUTTONS ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_BTNBCK_IMGRSRC)
		fprintf (dumpfile, "BTNBCK_IMGSRC " );
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_BARBCK_IMGRSRC)
		fprintf (dumpfile, "BARBCK_IMGRSRC ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_SET_PADDING)
		fprintf (dumpfile, "SET_PADDING ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_USE_APPLET)
		fprintf (dumpfile, "USE_APPLET ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_SET_HEIGHT)
		fprintf (dumpfile, "SET_HEIGHT ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_ABSOLUTE_HEIGHT)
		fprintf (dumpfile, "ABSOLUTE_HEIGHT ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_BACKGROUND_HEIGHT)
		fprintf (dumpfile, "BACKGROUND_HEIGHT ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_SET_WIDTH)
		fprintf (dumpfile, "SET_WIDTH ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_BACKGROUND_WIDTH)
		fprintf (dumpfile, "BACKGROUND_WIDTH ");
	if (cdActionBar.dwFlags & ACTION_BAR_FLAG_SHOW_HINKY_ALWAYS)
		fprintf (dumpfile, "ACTION_BAR_FLAG_SHOW_HINKY_ALWAYS ");
    fprintf (dumpfile, "\n" );

	fprintf (dumpfile, "    ShareID     = %lu\n", cdActionBar.ShareID);
	fprintf (dumpfile, "    FontID      = ");
	DumpFontIDFields((FONTIDFIELDS *) (&cdActionBar.FontID));
	fprintf( dumpfile, "    BtnHeight   = %hu\n", cdActionBar.BtnHeight);
	fprintf( dumpfile, "    HeightSpc   = %hu\n", cdActionBar.HeightSpc);
	
#endif

    return;
}

/************************************************************************

    FUNCTION:   DumpCDDocautolaunch

*************************************************************************/

void    LNPUBLIC  DumpCDDocautolaunch( char * RecordPtr, DWORD RecordLength )
{
    char far *                  p = RecordPtr;
    CDDOCAUTOLAUNCH             cdDocAutoLaunch;

    fprintf (dumpfile, "  DOCAUTOLAUNCH\n");

    ODSReadMemory (&p, _CDDOCAUTOLAUNCH, &cdDocAutoLaunch, 1);

    fprintf (dumpfile, "    ObjectType (0x%lX) = ",
		cdDocAutoLaunch.ObjectType);
    if (AUTOLAUNCH_OBJTYPE_NONE == cdDocAutoLaunch.ObjectType)
		fprintf (dumpfile, "NONE ");
    if (cdDocAutoLaunch.ObjectType & AUTOLAUNCH_OBJTYPE_OLE_CLASS)
		fprintf (dumpfile, "OLE_CLASS ");
    if (cdDocAutoLaunch.ObjectType & AUTOLAUNCH_OBJTYPE_OLEOBJ)
		fprintf (dumpfile, "OLEOBJ ");
    if (cdDocAutoLaunch.ObjectType & AUTOLAUNCH_OBJTYPE_DOCLINK)
		fprintf (dumpfile, "DOCLINK ");
    if (cdDocAutoLaunch.ObjectType & AUTOLAUNCH_OBJTYPE_ATTACH)
		fprintf (dumpfile, "ATTACH ");
    if (cdDocAutoLaunch.ObjectType & AUTOLAUNCH_OBJTYPE_URL)
		fprintf (dumpfile, "URL ");
    fprintf (dumpfile, "\n");

    fprintf (dumpfile, "    HideWhenFlags = 0x%lX: ",
		cdDocAutoLaunch.HideWhenFlags);
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_OPEN_CREATE)
		fprintf (dumpfile, "OPEN_CREATE ");
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_OPEN_EDIT)
		fprintf (dumpfile, "OPEN_EDIT ");
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_OPEN_READ)
		fprintf (dumpfile, "OPEN_READ ");
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_CLOSE_CREATE)
		fprintf (dumpfile, "CLOSE_CREATE ");
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_CLOSE_EDIT)
		fprintf (dumpfile, "CLOSE_EDIT ");
    if (cdDocAutoLaunch.HideWhenFlags & HIDE_CLOSE_READ)
		fprintf (dumpfile, "CLOSE_READ ");
    fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    LaunchWhenFlags = 0x%lX: ",
		cdDocAutoLaunch.LaunchWhenFlags);
    if (cdDocAutoLaunch.LaunchWhenFlags & LAUNCH_WHEN_CREATE)
		fprintf (dumpfile, "CREATE ");
    if (cdDocAutoLaunch.LaunchWhenFlags & LAUNCH_WHEN_EDIT)
		fprintf (dumpfile, "EDIT ");
    if (cdDocAutoLaunch.LaunchWhenFlags & LAUNCH_WHEN_READ)
		fprintf (dumpfile, "READ ");
    fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    OleFlags = 0x%lX: ",
		cdDocAutoLaunch.OleFlags);
    if (cdDocAutoLaunch.OleFlags & OLE_EDIT_INPLACE)
		fprintf (dumpfile, "OLE_EDIT_INPLACE ");
    if (cdDocAutoLaunch.OleFlags & OLE_MODAL_WINDOW)
		fprintf (dumpfile, "OLE_MODAL_WINDOW ");
    if (cdDocAutoLaunch.OleFlags & OLE_ADV_OPTIONS)
		fprintf (dumpfile, "OLE_ADV_OPTIONS ");
    fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    CopyToFieldFlags = 0x%lX: ",
		cdDocAutoLaunch.CopyToFieldFlags);
    if (cdDocAutoLaunch.CopyToFieldFlags & FIELD_COPY_NONE)
		fprintf (dumpfile, "NONE ");
    if (cdDocAutoLaunch.CopyToFieldFlags & FIELD_COPY_FIRST)
		fprintf (dumpfile, "FIRST ");
    if (cdDocAutoLaunch.CopyToFieldFlags & FIELD_COPY_NAMED)
		fprintf (dumpfile, "NAMED ");
    fprintf (dumpfile, "\n");
	
	fprintf (dumpfile, "    Spare1          = %lX\n", cdDocAutoLaunch.Spare1);
	fprintf (dumpfile, "    Spare2          = %lX\n", cdDocAutoLaunch.Spare2);
	fprintf (dumpfile, "    FieldNameLength = %hu\n", cdDocAutoLaunch.FieldNameLength);
	fprintf (dumpfile, "    OleObjClass     = ");
	PrintOleGuid (&cdDocAutoLaunch.OleObjClass);

	if (0 != cdDocAutoLaunch.FieldNameLength)
	{
		fprintf (dumpfile, "    FieldName       = ");
		PrintText ((char far *) p, cdDocAutoLaunch.FieldNameLength);
		p = ((char far *) p) + cdDocAutoLaunch.FieldNameLength;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOleObjInfo

*************************************************************************/

void    LNPUBLIC  DumpCDOleObjInfo( char * RecordPtr, DWORD RecordLength )
{
    char far *          p = RecordPtr;
    CDOLEOBJ_INFO       cdOleObjInfo;
	char *                  szFormat;

    fprintf( dumpfile, "  OLEOBJ_INFO\n" );

    ODSReadMemory (&p, _CDOLEOBJ_INFO, &cdOleObjInfo, 1);

	fprintf (dumpfile, "    FileObjNameLength = %hu\n",
		cdOleObjInfo.FileObjNameLength);
	fprintf (dumpfile, "    DescriptionNameLength   = %hu\n",
		cdOleObjInfo.DescriptionNameLength);
	fprintf (dumpfile, "    FieldNameLength   = %hu\n",
		cdOleObjInfo.FieldNameLength);
	fprintf (dumpfile, "    TextIndexObjNameLength  = %hu\n",
		cdOleObjInfo.TextIndexObjNameLength);

	fprintf (dumpfile, "    OleObjClass       = ");
	PrintOleGuid (&cdOleObjInfo.OleObjClass);

	fprintf (dumpfile, "    StorageFormat (%hu) = ", cdOleObjInfo.StorageFormat);
	switch (cdOleObjInfo.StorageFormat)
	{
		case OLE_STG_FMT_STRUCT_STORAGE:
			fprintf (dumpfile, "OLE_STG_FMT_STRUCT_STORAGE\n");
			break;

		case OLE_STG_FMT_ISTORAGE_ISTREAM:
			fprintf( dumpfile, "OLE_STG_FMT_ISTORAGE_ISTREAM\n");
			break;

		case OLE_STG_FMT_STRUCT_STREAM:
			fprintf( dumpfile, "OLE_STG_FMT_STRUCT_STREAM\n");
			break;

		default:
			fprintf (dumpfile, "*** UNKOWN FORMAT CODE ***\n");
			break;
	}

    szFormat = GetLiteralString( DDEFormatTable, cdOleObjInfo.DisplayFormat );
    fprintf( dumpfile, "    ClipFormat (%u) = %s\n",
		cdOleObjInfo.DisplayFormat, szFormat );

	fprintf (dumpfile, "    Flags = 0x%lX: ",
		cdOleObjInfo.Flags);
    if (cdOleObjInfo.Flags & OBJINFO_FLAGS_SCRIPTED)
		fprintf (dumpfile, "SCRIPTED ");
    if (cdOleObjInfo.Flags & OBJINFO_FLAGS_RUNREADONLY)
		fprintf (dumpfile, "RUNREADONLY ");
    if (cdOleObjInfo.Flags & OBJINFO_FLAGS_CONTROL)
		fprintf (dumpfile, "CONTROL ");
    if (cdOleObjInfo.Flags & OBJINFO_FLAGS_FITTOWINDOW)
		fprintf (dumpfile, "FITTOWINDOW ");
	if (cdOleObjInfo.Flags & OBJINFO_FLAGS_FITBELOWFIELDS)
		fprintf (dumpfile, "FITBELOWFIELDS ");
	if (cdOleObjInfo.Flags & OBJINFO_FLAGS_UPDATEFROMDOCUMENT)
		fprintf (dumpfile, "UPDATEFROMDOCUMENT ");
	if (cdOleObjInfo.Flags & OBJINFO_FLAGS_INCLUDERICHTEXT)
		fprintf (dumpfile, "INCLUDERICHTEXT ");
	if (cdOleObjInfo.Flags & OBJINFO_FLAGS_ISTORAGE_ISTREAM)
		fprintf (dumpfile, "ISTORAGE_ISTREAM ");
	if (cdOleObjInfo.Flags & OBJINFO_FLAGS_HTMLDATA)
		fprintf (dumpfile, "HTMLDATA ");
    fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    StorageFormatAppearedIn = %d.%d\n",
		(0xFF00 & cdOleObjInfo.StorageFormatAppearedIn) >> 8,
		(0xFF & cdOleObjInfo.StorageFormatAppearedIn));

	fprintf (dumpfile, "    HTMLDataLength    = %hu\n", cdOleObjInfo.HTMLDataLength);
	fprintf (dumpfile, "    AssociatedFILEsLength    = %hu\n", cdOleObjInfo.AssociatedFILEsLength);
	fprintf (dumpfile, "    Reserved3         = %hX\n", cdOleObjInfo.Reserved3);
	fprintf (dumpfile, "    Reserved4         = %lX\n", cdOleObjInfo.Reserved4);

	if (0 != cdOleObjInfo.FileObjNameLength)
	{
		fprintf (dumpfile, "    FileObjName       = ");
		PrintText ((char far *) p, cdOleObjInfo.FileObjNameLength);
		p = ((char far *) p) + cdOleObjInfo.FileObjNameLength;
	}

	if (0 != cdOleObjInfo.DescriptionNameLength)
	{
		fprintf (dumpfile, "    DescriptionName   = ");
		PrintText ((char far *) p, cdOleObjInfo.DescriptionNameLength);
		p = ((char far *) p) + cdOleObjInfo.DescriptionNameLength;
	}

	if (0 != cdOleObjInfo.FieldNameLength)
	{
		fprintf (dumpfile, "    FieldName         = ");
		PrintText ((char far *) p, cdOleObjInfo.FieldNameLength);
		p = ((char far *) p) + cdOleObjInfo.FieldNameLength;
	}

	if (0 != cdOleObjInfo.TextIndexObjNameLength)
	{
		fprintf (dumpfile, "    TextIndexObjName  = ");
		PrintText ((char far *) p, cdOleObjInfo.TextIndexObjNameLength);
		p = ((char far *) p) + cdOleObjInfo.TextIndexObjNameLength;
	}

	if (0 != cdOleObjInfo.HTMLDataLength)
	{
		fprintf (dumpfile, "    HTMLData = ");
		PrintText ((char far *) p, cdOleObjInfo.HTMLDataLength);
		p = ((char far *) p) + cdOleObjInfo.HTMLDataLength;
	}

	if (0 != cdOleObjInfo.AssociatedFILEsLength)
	{
		fprintf (dumpfile, "    AssociatedFILEsLength = ");
		PrintText ((char far *) p, cdOleObjInfo.AssociatedFILEsLength);
		p = ((char far *) p) + cdOleObjInfo.AssociatedFILEsLength;
	}

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLayout

*************************************************************************/

void    LNPUBLIC  DumpCDLayout (char * RecordPtr, DWORD RecordLength)
{
    char far *  p = RecordPtr;
    CDLAYOUT    cdLayout;
	int			wIndex;

    fprintf (dumpfile, "  LAYOUT\n");

    ODSReadMemory (&p, _CDLAYOUT, &cdLayout, 1);

	fprintf (dumpfile, "    wLeft       = %d\n", cdLayout.wLeft);
	fprintf (dumpfile, "    wWidth      = %d\n", cdLayout.wWidth);
	fprintf (dumpfile, "    wHeight     = %d\n", cdLayout.wHeight);
	fprintf (dumpfile, "    Flags = 0x%X: ", cdLayout.Flags);
	if (LAYOUT_FLAG_SHOWBORDER & cdLayout.Flags)
		fprintf (dumpfile, "SHOWBORDER ");
	if (LAYOUT_FLAG_SHOWGRID & cdLayout.Flags)
		fprintf (dumpfile, "SHOWGRID ");
	if (LAYOUT_FLAG_SNAPTOGRID & cdLayout.Flags)
		fprintf (dumpfile, "SNAPTOGRID ");
	if (LAYOUT_FLAG_3DSTYLE & cdLayout.Flags)
		fprintf (dumpfile, "3DSTYLE ");
	if (LAYOUT_FLAG_RTL & cdLayout.Flags)
		fprintf (dumpfile, "RLT ");
	if (LAYOUT_FLAG_DONTWRAP & cdLayout.Flags)
		fprintf (dumpfile, "DONTWRAP ");
	fprintf (dumpfile, "\n");
	fprintf (dumpfile, "    wGridSize   = %d\n", cdLayout.wGridSize);
    for (wIndex = 0; wIndex < 14; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLayout.Reserved[wIndex] );

    return;
}

/************************************************************************

    FUNCTION:   DumpLayoutElementHeader

	Internal function to dump common fields

*************************************************************************/

void DumpLayoutElementHeader (ELEMENTHEADER *pElemHead)
{
	fprintf (dumpfile, "      wLeft       = %d\n", pElemHead->wLeft);
	fprintf (dumpfile, "      wTop        = %d\n", pElemHead->wTop);
	fprintf (dumpfile, "      wWidth      = %d\n", pElemHead->wWidth);
	fprintf (dumpfile, "      wHeight     = %d\n", pElemHead->wHeight);
	fprintf (dumpfile, "      FontID      = ");
    DumpFontIDFields ((FONTIDFIELDS *)&(pElemHead->FontID));
	fprintf (dumpfile, "      byBackColor = %d\n", pElemHead->byBackColor);

	return;
}

/************************************************************************

    FUNCTION:   DumpCDLayoutEnd

*************************************************************************/

void    LNPUBLIC  DumpCDLayoutEnd (char * RecordPtr, DWORD RecordLength)
{
    fprintf (dumpfile, "  LAYOUTEND\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLayoutText

*************************************************************************/

void    LNPUBLIC  DumpCDLayoutText (char * RecordPtr, DWORD RecordLength)
{
    char far *          p = RecordPtr;
    CDLAYOUTTEXT        cdLayoutText;
	int					wIndex;

    fprintf (dumpfile, "  LAYOUTTEXT\n");

    ODSReadMemory (&p, _CDLAYOUTTEXT, &cdLayoutText, 1);

	fprintf (dumpfile, "    ElementHeader record:\n");
	DumpLayoutElementHeader (&(cdLayoutText.ElementHeader));

	fprintf (dumpfile, "    Flags = 0x%X: ", cdLayoutText.Flags);
	if (LAYOUT_TEXT_FLAG_TRANS & cdLayoutText.Flags)
		fprintf (dumpfile, "TRANS ");
	if (LAYOUT_TEXT_FLAG_LEFT & cdLayoutText.Flags)
		fprintf (dumpfile, "LEFT ");
	if (LAYOUT_TEXT_FLAG_CENTER & cdLayoutText.Flags)
		fprintf (dumpfile, "CENTER ");
	if (LAYOUT_TEXT_FLAG_RIGHT & cdLayoutText.Flags)
		fprintf (dumpfile, "RIGHT ");
	if (LAYOUT_TEXT_FLAG_VCENTER & cdLayoutText.Flags)
		fprintf (dumpfile, "VCENTER ");
	if (LAYOUT_TEXT_FLAG_LTR & cdLayoutText.Flags)
		fprintf (dumpfile, "LTR ");
	if (LAYOUT_TEXT_FLAG_RTL & cdLayoutText.Flags)
		fprintf (dumpfile, "RTL ");
	fprintf (dumpfile, "\n");
	for (wIndex = 0; wIndex < 16; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLayoutText.Reserved[wIndex]);
    return;
}

/************************************************************************

    FUNCTION:   DumpCDLayoutField

*************************************************************************/

void    LNPUBLIC  DumpCDLayoutField (char * RecordPtr, DWORD RecordLength)
{
    char far *          p = RecordPtr;
    CDLAYOUTFIELD       cdLayoutField;
	char *                  szFieldType;

    fprintf (dumpfile, "  LAYOUTFIELD\n");

    ODSReadMemory (&p, _CDLAYOUTFIELD, &cdLayoutField, 1);

	fprintf (dumpfile, "    ElementHeader record:\n");
	DumpLayoutElementHeader (&(cdLayoutField.ElementHeader));

	fprintf (dumpfile, "    Flags = 0x%X: ", cdLayoutField.Flags);
	if (LAYOUT_FIELD_FLAG_SINGLELINE & cdLayoutField.Flags)
		fprintf (dumpfile, "SINGLELINE ");
	if (LAYOUT_FIELD_FLAG_VSCROLL & cdLayoutField.Flags)
		fprintf (dumpfile, "VSCROLL ");
	if (LAYOUT_FIELD_FLAG_MULTISEL & cdLayoutField.Flags)
		fprintf (dumpfile, "MULTISEL ");
	if (LAYOUT_FIELD_FLAG_STATIC & cdLayoutField.Flags)
		fprintf (dumpfile, "STATIC ");
	if (LAYOUT_FIELD_FLAG_NOBORDER & cdLayoutField.Flags)
		fprintf (dumpfile, "NOBORDER ");
	if (LAYOUT_FIELD_FLAG_IMAGE & cdLayoutField.Flags)
		fprintf (dumpfile, "IMAGE ");
	if (LAYOUT_FIELD_FLAG_TRANS & cdLayoutField.Flags)
		fprintf (dumpfile, "TRANS ");
	if (LAYOUT_FIELD_FLAG_LEFT & cdLayoutField.Flags)
		fprintf (dumpfile, "LEFT ");
	if (LAYOUT_FIELD_FLAG_CENTER & cdLayoutField.Flags)
		fprintf (dumpfile, "CENTER ");
	if (LAYOUT_FIELD_FLAG_RIGHT & cdLayoutField.Flags)
		fprintf (dumpfile, "RIGHT ");
	if (LAYOUT_FIELD_FLAG_VCENTER & cdLayoutField.Flags)
		fprintf (dumpfile, "VCENTER ");
	if (LAYOUT_FIELD_FLAG_LTR & cdLayoutField.Flags)
		fprintf (dumpfile, "LTR ");
	if (LAYOUT_FIELD_FLAG_RTL & cdLayoutField.Flags)
		fprintf (dumpfile, "RTL ");
	fprintf (dumpfile, "\n");

    szFieldType = GetLiteralString (LayoutFieldTypeTable, cdLayoutField.bFieldType);
	fprintf (dumpfile, "    bFieldType = %s\n", szFieldType);

    return;
}

/************************************************************************

    FUNCTION:   DumpCDLayoutGraphic

*************************************************************************/

void    LNPUBLIC  DumpCDLayoutGraphic (char * RecordPtr, DWORD RecordLength)
{
    char far *          p = RecordPtr;
    CDLAYOUTGRAPHIC     cdLayoutGraphic;
	int					wIndex;

    fprintf (dumpfile, "  LAYOUTGRAPHIC\n");

    ODSReadMemory (&p, _CDLAYOUTGRAPHIC, &cdLayoutGraphic, 1);

	fprintf (dumpfile, "    ElementHeader record:\n");
	DumpLayoutElementHeader (&(cdLayoutGraphic.ElementHeader));

	fprintf (dumpfile, "    Flags = 0x%X: ", cdLayoutGraphic.Flags);
	if (LAYOUT_GRAPHIC_FLAG_BUTTON & cdLayoutGraphic.Flags)
		fprintf (dumpfile, "BUTTON ");
	fprintf (dumpfile, "\n");
	for (wIndex = 0; wIndex < 16; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLayoutGraphic.Reserved[wIndex]);
    return;
}

/************************************************************************

    FUNCTION:   DumpCDLayoutButton

*************************************************************************/

void    LNPUBLIC  DumpCDLayoutButton (char * RecordPtr, DWORD RecordLength)
{
    char far *          p = RecordPtr;
    CDLAYOUTBUTTON      cdLayoutButton;
	int					wIndex;

    fprintf (dumpfile, "  LAYOUTBUTTON\n");

    ODSReadMemory (&p, _CDLAYOUTBUTTON, &cdLayoutButton, 1);

	fprintf (dumpfile, "    ElementHeader record:\n");
	DumpLayoutElementHeader (&(cdLayoutButton.ElementHeader));

	fprintf (dumpfile, "    Flags = 0x%X: ", cdLayoutButton.Flags);
	fprintf (dumpfile, "\n");
	for (wIndex = 0; wIndex < 16; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLayoutButton.Reserved[wIndex]);
    return;
}

/************************************************************************

    FUNCTION:   DumpCDTextEffect

*************************************************************************/

void    LNPUBLIC  DumpCDTextEffect (char * RecordPtr, DWORD RecordLength, WORD RecordType)
{
    char far *          p = RecordPtr;
    CDTEXTEFFECT        cdTextEffect;
    DWORD                       dwLen;

    if(SIG_CD_TEXTEFFECT == RecordType)
		fprintf (dumpfile,"  TEXTEFFECT\n");
	else
		fprintf (dumpfile,"  BIDI_TEXTEFFECT\n");

    ODSReadMemory (&p, _CDTEXTEFFECT, &cdTextEffect, 1);

	fprintf (dumpfile, "   FontID = ");
    DumpFontIDFields ((FONTIDFIELDS *)&cdTextEffect.FontEffectID);

    dwLen = RecordLength - (DWORD) ODSLength(_CDTEXTEFFECT) ;
    if (dwLen > 0)
    {
	fprintf (dumpfile, "   Text Data = ");

	PrintText (p, dwLen);
	WordCount (p, (WORD) dwLen);
	fprintf (dumpfile, "   word count = %ld.\n", nw);
    }

    return;
}

/************************************************************************

    FUNCTION:   DumpCDTransparentTable

*************************************************************************/

void  LNPUBLIC   DumpCDTransparentTable (char *RecordPtr, DWORD RecordLength)
{
    char far *                  p = RecordPtr;
    CDTRANSPARENTTABLE  cdTransparentTable;

    fprintf (dumpfile,"  TRANSPARENTTABLE\n");

    ODSReadMemory (&p, _CDTRANSPARENTTABLE, &cdTransparentTable, 1);
	fprintf (dumpfile, "    Reserved = (0x%X)\n", cdTransparentTable.Reserved);
	fprintf (dumpfile, "    TransparentCount = %d\n",
		cdTransparentTable.TransparentCount);
    fprintf (dumpfile, "    <start of transparent color table entries>\n");
    NSFDDUMPDumpMemory (p, (WORD)(RecordLength-ODSLength(_CDCOLORTABLE)));
    fprintf (dumpfile, "    <end of transparent color table entries>\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDStorageLink

*************************************************************************/

void  LNPUBLIC   DumpCDStorageLink (char *RecordPtr, DWORD RecordLength)
{
    char far *          p = RecordPtr;
    CDSTORAGELINK       cdStorageLink;
	char *                  pString;
	int					wIndex;

    fprintf (dumpfile,"  STORAGELINK\n");

    ODSReadMemory (&p, _CDSTORAGELINK, &cdStorageLink, 1);

    pString = GetLiteralString (StorageLinkTypeTable, cdStorageLink.StorageType);
	fprintf (dumpfile, "    StorageType  = %s\n", pString);

    pString = GetLiteralString (StorageLinkLoadTable, cdStorageLink.LoadType);
	fprintf (dumpfile, "    LoadType     = %s\n", pString);

	fprintf (dumpfile, "    Flags        = 0x%X: ", cdStorageLink.Flags);
	fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    DataLength   = %d\n", cdStorageLink.DataLength);
	
	for (wIndex = 0; wIndex < 6; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdStorageLink.Reserved[wIndex]);

	switch (cdStorageLink.StorageType)
	{
		case STORAGE_LINK_TYPE_OBJECT:
		case STORAGE_LINK_TYPE_URL_CONVERTED:
		case STORAGE_LINK_TYPE_URL_MIME:
			fprintf (dumpfile, "    Link         = ");
			PrintText (p, cdStorageLink.DataLength);
			break;

		default:
			fprintf (dumpfile, "    Link         = <Start of Link Data>\n");
			NSFDDUMPDumpMemory (p, cdStorageLink.DataLength);
			fprintf (dumpfile, "    <End of Link Data>\n");
			break;
	}

    return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObject

    PURPOSE:    Print the Domino and Notes active object records in the
	            specified buffer.

**************************************************************************/

void LNPUBLIC DumpActiveObject (
	char *                  RecordPtr,
	DWORD                   RecordLength
) {
    char far *          p = RecordPtr;
	ACTIVEOBJECT    activeObject;
	char *                  pszString;
	int                             index;

    fprintf (dumpfile,"    ACTIVEOBJECT\n");

    ODSReadMemory (&p, _ACTIVEOBJECT, &activeObject, 1);

		/* Check record version number */
	if (ACTIVEOBJECT_VERSION1 != activeObject.Version)
	{
		fprintf (dumpfile, "      Unknown active object version: %d\n",
			activeObject.Version);
		return;
	}

	fprintf (dumpfile, "      Version = %d\n", activeObject.Version);

	pszString = GetLiteralString (ActiveObjectTypeTable,
		activeObject.ObjectType);
	fprintf (dumpfile, "      Object type = %s\n", pszString);
	
	fprintf( dumpfile, "      Flags = 0x%X: ", activeObject.Flags);
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_MAYSCRIPT )
		fprintf( dumpfile, "MAYSCRIPT " );
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_CORBA_APPLET )
		fprintf( dumpfile, "CORBA_APPLET " );
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_CORBA_SSL )
		fprintf( dumpfile, "CORBA_SSL " );
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_MAIL_PLUGIN )
		fprintf( dumpfile, "MAIL_PLUGIN " );
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_NOCORBADOWNLOAD )
		fprintf( dumpfile, "NOCORBADOWNLOAD " );
	if( activeObject.Flags & ACTIVEOBJECT_FLAG_DIGESTAPPLETFILES )
		fprintf( dumpfile, "DIGESTAPPLETFILES " );
	fprintf( dumpfile, "\n" );
		pszString = GetLiteralString (ActiveObjectUnitsTable,
		activeObject.WidthUnitType);
	fprintf (dumpfile, " WidthUnit Type (0x%X) = %s\n",
		activeObject.WidthUnitType, pszString);
	pszString = GetLiteralString (ActiveObjectUnitsTable,
		activeObject.HeightUnitType);
	fprintf (dumpfile, " HeightUnit Type (0x%X) = %s\n",
		activeObject.HeightUnitType, pszString);
	fprintf (dumpfile, "      Width = %d\n", activeObject.Width);
	fprintf (dumpfile, "      Height = %d\n", activeObject.Height);
	
	pszString = GetLiteralString (ActiveObjectUnitsTable,
		activeObject.SpaceUnitType);
	fprintf (dumpfile, "      Space unit type (0x%X) = %s\n",
		activeObject.SpaceUnitType, pszString);
	fprintf (dumpfile, "      HSpace = %d\n", activeObject.HSpace);
	fprintf (dumpfile, "      VSpace = %d\n", activeObject.VSpace);
	
	fprintf (dumpfile, "      DocURLNameLength = %d\n", activeObject.DocURLNameLength);
	fprintf (dumpfile, "      CodebaseLength = %d\n", activeObject.CodebaseLength);
	fprintf (dumpfile, "      CodeLength = %d\n", activeObject.CodeLength);
	fprintf (dumpfile, "      ObjectNameLength = %d\n", activeObject.ObjectNameLength);
	fprintf (dumpfile, "      StorageLinkCount = %d\n", activeObject.StorageLinkCount);
	fprintf (dumpfile, "      ParamCount = %d\n", activeObject.ParamCount);

	fprintf (dumpfile, "      Used[] =");
	for (index = 0; index < 16; index++)
		fprintf( dumpfile, " 0x%2.2X", activeObject.Used[index] );
	fprintf (dumpfile, "\n");

		/* Print the URL string */
	fprintf (dumpfile, "      URL string = ");
	if (0 != activeObject.DocURLNameLength)
	{
		PrintText (p, activeObject.DocURLNameLength);
		p += activeObject.DocURLNameLength;
	}
	else
	{
		fprintf (dumpfile, "\n");
	}

		/* Print the codebase string */
	fprintf (dumpfile, "      Codebase string = ");
	if (0 != activeObject.CodebaseLength)
	{
		PrintText (p, activeObject.CodebaseLength);
		p += activeObject.CodebaseLength;
	}
	else
	{
		fprintf (dumpfile, "\n");
	}

		/* Print the code string */
	fprintf (dumpfile, "      Code string = ");
	if (0 != activeObject.CodeLength)
	{
		PrintText (p, activeObject.CodeLength);
		p += activeObject.CodeLength;
	}
	else
	{
		fprintf (dumpfile, "\n");
	}

		/* Print the object name string */
	fprintf (dumpfile, "      Object name = ");
	if (0 != activeObject.ObjectNameLength)
	{
		PrintText (p, activeObject.ObjectNameLength);
		p += activeObject.ObjectNameLength;
	}
	else
	{
		fprintf (dumpfile, "\n");
	}

		/* Print the parameter records */
	for (index = 0; index < activeObject.ParamCount; index++)
	{
		DumpActiveObjectParameter (index, &p);
	}

		/* Print the storage link records */
	for (index = 0; index < activeObject.StorageLinkCount; index++)
	{
		DumpActiveObjectLink (index, &p);
	}

	return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObjectParameter

    PURPOSE:    Print the Domino and Notes active object parameter record.

**************************************************************************/

void LNPUBLIC DumpActiveObjectParameter (
	int                             index,
	char **                 ppRecord
) {
    char far *          p = *ppRecord;
	ACTIVEOBJECTPARAM       objectParam;

    fprintf (dumpfile,"    Parameter %d - ACTIVEOBJECTPARAM\n", index);

    ODSReadMemory (&p, _ACTIVEOBJECTPARAM, &objectParam, 1);

	fprintf (dumpfile, "      Length = %d\n", objectParam.Length);
	fprintf (dumpfile, "      FormulaLength = %d\n", objectParam.FormulaLength);
	fprintf (dumpfile, "      Reserved = 0x%X\n", objectParam.Reserved);

		/* Print the string data */
	fprintf (dumpfile, "      String = ");
	PrintText (p, objectParam.Length);
	p += objectParam.Length;

		/* Print the formula, if any */
	if (0 != objectParam.FormulaLength)
	{
		fprintf (dumpfile, "      Formula = ");
		PrintFormula (p, objectParam.FormulaLength);
		p += objectParam.FormulaLength;
	}

		/* Update caller's pointer to start of next record */
	*ppRecord = p;

	return;
}

/*************************************************************************

    FUNCTION:   DumpActiveObjectLink

    PURPOSE:    Print the Domino and Notes active object link record.

**************************************************************************/

void LNPUBLIC DumpActiveObjectLink (
	int                             index,
	char **                 ppRecord
) {
    char far *          p = *ppRecord;
	ACTIVEOBJECTSTORAGELINK objectLink;
	char *                  pString;

    fprintf (dumpfile,"    Storage link %d - ACTIVEOBJECTSTORAGELINK\n", index);

    ODSReadMemory (&p, _ACTIVEOBJECTSTORAGELINK, &objectLink, 1);

	fprintf (dumpfile, "      Length = %d\n", objectLink.Length);

    pString = GetLiteralString (StorageLinkTypeTable, objectLink.LinkType);
	fprintf (dumpfile, "      LinkType (0x%X) = %s\n", objectLink.LinkType, pString);

	fprintf (dumpfile, "      Reserved = 0x%lX\n", objectLink.Reserved);

		/* Print the link data */
    fprintf (dumpfile, "      Link = ");
    PrintText (p, objectLink.Length);
	p += objectLink.Length;

		/* Update caller's pointer to start of next record */
	*ppRecord = p;

	return;
}

/************************************************************************

    FUNCTION:   DumpCDAnchor

*************************************************************************/

void  LNPUBLIC   DumpCDAnchor (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDANCHOR                    cdAnchor;

    fprintf (dumpfile, "  ANCHOR\n");

    ODSReadMemory (&p, _CDANCHOR, &cdAnchor, 1);

	fprintf (dumpfile, "    Datalength = %d\n", cdAnchor.Datalength);
	fprintf (dumpfile, "    Reserved =   %d (0x%X)\n",
		cdAnchor.Reserved, cdAnchor.Reserved);

		/* Print the anchor text */
	fprintf (dumpfile, "    Anchor text:\n");
	PrintText (p, cdAnchor.Datalength);

    return;
}

/************************************************************************

    FUNCTION:   DumpCDAltText

*************************************************************************/

void  LNPUBLIC   DumpCDAltText (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {
    char far *                  p = RecordPtr;
    CDALTTEXT                   cdAltText;

    if(SIG_CD_ALTTEXT == RecordType)
		fprintf (dumpfile, "  ALTTEXT\n");
	else
		fprintf (dumpfile, "  HTML_ALTTEXT\n");

    ODSReadMemory (&p, _CDALTTEXT, &cdAltText, 1);

	fprintf (dumpfile, "    wLength =   %d\n", cdAltText.wLength);
	fprintf (dumpfile, "    Reserved1 = %d (0x%X)\n",
		cdAltText.Reserved1, cdAltText.Reserved1);
	fprintf (dumpfile, "    Reserved2 = %ld (0x%lX)\n",
		cdAltText.Reserved2, cdAltText.Reserved2);

		/* Print the alternate text */
	PrintText (p, cdAltText.wLength);

    return;
}

/************************************************************************

    FUNCTION:   DumpCDAlternateBegin

*************************************************************************/

void  LNPUBLIC   DumpCDAlternateBegin (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDALTERNATEBEGIN    cdAlternateBegin;

    fprintf (dumpfile, "  ALTERNATEBEGIN\n");

    ODSReadMemory (&p, _CDALTERNATEBEGIN, &cdAlternateBegin, 1);

	fprintf (dumpfile, "    Type = %d\n", cdAlternateBegin.Type);
	fprintf (dumpfile, "    SequenceNumber = %ld\n", cdAlternateBegin.SequenceNumber);
	fprintf (dumpfile, "    Flags = 0x%lX: ", cdAlternateBegin.Flags);
		/* None defined */
	fprintf (dumpfile, "\n");
	fprintf (dumpfile, "    DataLength = %d\n", cdAlternateBegin.DataLength);

		/* Data format?? */

	return;
}

/************************************************************************

    FUNCTION:   DumpCDAlternateEnd

*************************************************************************/

void  LNPUBLIC   DumpCDAlternateEnd (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDALTERNATEEND              cdAlternateEnd;

    fprintf (dumpfile, "  ALTERNATEEND\n");

    ODSReadMemory (&p, _CDALTERNATEEND, &cdAlternateEnd, 1);

	fprintf (dumpfile, "    Flags = 0x%lX: ", cdAlternateEnd.Flags);
		/* None defined */
	fprintf (dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHRule

*************************************************************************/

void  LNPUBLIC   DumpCDHRule (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHRULE                             cdHRule;

    fprintf (dumpfile, "  HRULE\n");

    ODSReadMemory (&p, _CDHRULE, &cdHRule, 1);

	fprintf (dumpfile, "    Flags = 0x%X: ", cdHRule.Flags);
	if (0 != (HRULE_FLAG_USECOLOR & cdHRule.Flags))
		fprintf (dumpfile, "USECOLOR ");
	if (0 != (HRULE_FLAG_USEGRADIENT & cdHRule.Flags))
		fprintf (dumpfile, "USEGRADIENT ");
	if (0 != (HRULE_FLAG_FITTOWINDOW & cdHRule.Flags))
		fprintf (dumpfile, "FITTOWINDOW ");
	if (0 != (HRULE_FLAG_NOSHADOW & cdHRule.Flags))
		fprintf (dumpfile, "NOSHADOW ");
	fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    Width  = %d\n", cdHRule.Width);
	fprintf (dumpfile, "    Height = %d\n", cdHRule.Height);
	fprintf (dumpfile, "    Color  = %d\n", cdHRule.Color);
	fprintf (dumpfile, "    GradientColor = %d\n", cdHRule.GradientColor);

	return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlBegin

*************************************************************************/

void  LNPUBLIC   DumpCDHtmlBegin (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHTMLBEGIN                 cdHtmlBegin;
	int                                     index;

    fprintf (dumpfile, "  HTMLBEGIN\n");

    ODSReadMemory (&p, _CDHTMLBEGIN, &cdHtmlBegin, 1);

	fprintf (dumpfile, "    Spares: ");
	for (index = 0; index < 4; index++)
		fprintf (dumpfile, "[%d]=%d (0x%X)  ", index,
			cdHtmlBegin.Spares[index], cdHtmlBegin.Spares[index]);
	fprintf (dumpfile, "\n");

	return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlEnd

*************************************************************************/

void  LNPUBLIC   DumpCDHtmlEnd (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHTMLEND                   cdHtmlEnd;
	int                                     index;

    fprintf (dumpfile, "  HTMLEND\n");

    ODSReadMemory (&p, _CDHTMLEND, &cdHtmlEnd, 1);

	fprintf (dumpfile, "    Spares: ");
	for (index = 0; index < 4; index++)
		fprintf (dumpfile, "[%d]=%d (0x%X)  ", index,
			cdHtmlEnd.Spares[index], cdHtmlEnd.Spares[index]);
	fprintf (dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlFormula

*************************************************************************/

void  LNPUBLIC   DumpCDHtmlFormula (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHTMLFORMULA               cdHtmlFormula;
	WORD                            dataLen;

    fprintf (dumpfile, "  HTMLFORMULA\n");

    ODSReadMemory (&p, _CDHTMLFORMULA, &cdHtmlFormula, 1);

	fprintf (dumpfile, "    dwFlags = 0x%lX: ", cdHtmlFormula.dwFlags);
	if (0 != (cdHtmlFormula.dwFlags & CDHTMLFORMULA_FLAG_ATTR))
		fprintf (dumpfile, "ATTR ");
	if (0 != (cdHtmlFormula.dwFlags & CDHTMLFORMULA_FLAG_ALT))
		fprintf (dumpfile, "ALT ");
	if (0 != (cdHtmlFormula.dwFlags & CDHTMLFORMULA_FLAG_ACTION_LABEL))
		fprintf (dumpfile, "ACTION_LABEL ");
	fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    cbLevel = %u\n",
		cdHtmlFormula.Reserved, cdHtmlFormula.cbLevel);
	fprintf (dumpfile, "    cbReserved = %u\n",
		cdHtmlFormula.Reserved, cdHtmlFormula.Reserved);
	fprintf (dumpfile, "    Reserved = %ld (0x%lX)\n",
		cdHtmlFormula.Reserved, cdHtmlFormula.Reserved);

	fprintf (dumpfile, "    Formula content:\n");
	dataLen = (WORD) (RecordLength - ODSLength (_CDHTMLFORMULA));
	if (0 == dataLen)
	{
		fprintf (dumpfile, "- - No data - -\n");
	}
	else
	{
		NSFDDUMPDumpMemory (p, dataLen);
	}
    return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlHeader

*************************************************************************/

void  LNPUBLIC   DumpCDHtmlHeader (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHTMLHEADER                cdHtmlHeader;

    fprintf (dumpfile, "  HTMLHEADER\n");

    ODSReadMemory (&p, _CDHTMLHEADER, &cdHtmlHeader, 1);

	fprintf (dumpfile, "    wSegments = %d\n", cdHtmlHeader.wSegments);

	return;
}

/************************************************************************

    FUNCTION:   DumpCDHtmlSegment

*************************************************************************/

void  LNPUBLIC   DumpCDHtmlSegment (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDHTMLSEGMENT               cdHtmlSegment;

    fprintf (dumpfile, "  HTMLSEGMENT\n");

    ODSReadMemory (&p, _CDHTMLSEGMENT, &cdHtmlSegment, 1);

	fprintf (dumpfile, "    wSegments = %d\n", cdHtmlSegment.wHTMLLength);
	fprintf (dumpfile, "    Raw HTML  =\n");
	PrintText (p, cdHtmlSegment.wHTMLLength);

	return;
}

/************************************************************************

    FUNCTION:   DumpCDLSObject

*************************************************************************/

void  LNPUBLIC   DumpCDLSObject (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *      p = RecordPtr;
    CDLSOBJECT      cdLSObject;
	WORD			wIndex;

    fprintf (dumpfile, "  LSOBJECT\n");
    ODSReadMemory (&p, _CDLSOBJECT, &cdLSObject, 1);

	fprintf( dumpfile, "    CodeSize = %X\n", cdLSObject.CodeSize );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLSObject.Reserved[wIndex] );
	fprintf (dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpCDOleRTMarker

*************************************************************************/

void  LNPUBLIC   DumpCDOleRTMarker (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    CDOLERTMARKER               cdOleRTMarker;

    fprintf (dumpfile, "  OLERTMARKER\n");

    ODSReadMemory (&p, _CDOLERTMARKER, &cdOleRTMarker, 1);

	fprintf (dumpfile, "    Flags = 0x%lX: ", cdOleRTMarker.Flags);
		/* No flags are defined yet */
	fprintf (dumpfile, "\n");

    return;
}

/************************************************************************

    FUNCTION:   DumpHSOleRichText

*************************************************************************/

void  LNPUBLIC   DumpHSOleRichText (
	char *          RecordPtr,
	DWORD           RecordLength
) {
    char far *                  p = RecordPtr;
    HSOLERICHTEXT               hsOleRichText;

    fprintf (dumpfile, "  HSOLERICHTEXT\n");

    ODSReadMemory (&p, _HSOLERICHTEXT, &hsOleRichText, 1);

	fprintf (dumpfile, "    Flags = 0x%lX: ", hsOleRichText.Flags);
	if (0 != (OLERT_FLAG_CHANGED & hsOleRichText.Flags))
		fprintf (dumpfile, "CHANGED ");
	if (0 != (OLERT_FLAG_NEW & hsOleRichText.Flags))
		fprintf (dumpfile, "* * * Warning: OLERT_FLAG_NEW should not be stored to disk! ");
	fprintf (dumpfile, "\n");

	fprintf (dumpfile, "    cFileObjName = %d\n", hsOleRichText.cFileObjName);
	fprintf (dumpfile, "    Reserved1    = %d\n", hsOleRichText.Reserved1);
	fprintf (dumpfile, "    Reserved2    = %d\n", hsOleRichText.Reserved2);
	fprintf (dumpfile, "    Reserved3    = %d\n", hsOleRichText.Reserved3);
	fprintf (dumpfile, "    Reserved4    = %d\n", hsOleRichText.Reserved4);

	fprintf (dumpfile, "    File object name = ");
	PrintText (p, hsOleRichText.cFileObjName);
	p += hsOleRichText.cFileObjName;

    return;
}

/************************************************************************

    FUNCTION:   DumpCDColor

*************************************************************************/
void  LNPUBLIC   DumpCDColor (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {

	char far *	p = RecordPtr;
	CDCOLOR		cdcolor;
	if( SIG_CD_COLOR == RecordType)
		fprintf( dumpfile,"  COLOR\n");
	if( SIG_CD_BACKGROUNDCOLOR == RecordType)
		fprintf( dumpfile,"  BACKGROUNDCOLOR\n");
	else /* SIG_CD_TABLECELL_COLOR */
		fprintf( dumpfile,"  TABLECELL_COLOR\n");

	ODSReadMemory( &p, _CDCOLOR, &cdcolor, 1);
	fprintf( dumpfile, "   Color\n" );
	DumpColorValue(cdcolor.Color);
	return;
}

/************************************************************************

    FUNCTION:   DumpCDBeginRecord

*************************************************************************/
void  LNPUBLIC   DumpCDBeginRecord (
	char *          RecordPtr,
	DWORD           RecordLength
)
{
	char far *		p = RecordPtr;
	CDBEGINRECORD	cdbeginrecord;
	char *			pString;

	ODSReadMemory( &p, _CDBEGINRECORD, &cdbeginrecord, 1);
	fprintf( dumpfile, "  BEGINRECORD\n");
	fprintf( dumpfile, "    Version = 0x%X\n", cdbeginrecord.Version);
	pString = GetLiteralString(SignatureTypeTable, cdbeginrecord.Signature);
	fprintf( dumpfile, "    Signature (0x%X) = SIG_%s\n", cdbeginrecord.Signature, pString);
	return;
}

/************************************************************************

    FUNCTION:   DumpCDEndRecord

*************************************************************************/
void  LNPUBLIC   DumpCDEndRecord (
	char *          RecordPtr,
	DWORD           RecordLength
) {	

	char far *		p = RecordPtr;
	CDENDRECORD		cdendrecord;
	char *			pString;

	ODSReadMemory( &p, _CDENDRECORD, &cdendrecord, 1);
	fprintf( dumpfile, "  ENDRECORD\n");
	fprintf( dumpfile, "    Version = 0x%X\n", cdendrecord.Version);
	pString = GetLiteralString(SignatureTypeTable, cdendrecord.Signature);
	fprintf( dumpfile, "    Signature (0x%X) = SIG_%s\n", cdendrecord.Signature, pString);
	return;
}

/************************************************************************

    FUNCTION:   DumpCDVerticalAlign

*************************************************************************/
void  LNPUBLIC   DumpCDVerticalAlign (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDVERTICALALIGN	cdVerticalAlign;
	char *			pString;
	
	ODSReadMemory( &p, _CDVERTICALALIGN, &cdVerticalAlign, 1);
	fprintf( dumpfile, "  VERTICALALIGN\n");
	pString = GetLiteralString( VerticalAlignValues, cdVerticalAlign.Alignment);
	fprintf( dumpfile, "    Alignment (0x%X) = %s\n", cdVerticalAlign.Alignment, pString);
	return;
	
}

/************************************************************************

    FUNCTION:   DumpCDFloat

*************************************************************************/
void  LNPUBLIC   DumpCDFloat (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char *		p = RecordPtr;
	CDFLOAT		cdFloat;

	ODSReadMemory( &p, _CDFLOAT, &cdFloat, 1);
	fprintf( dumpfile, "  FLOAT\n");
	if( cdFloat.Float == FLOAT_LEFT )
		fprintf( dumpfile, "    Float (0x%X) = FLOAT_LEFT\n", cdFloat.Float);
	else
		fprintf( dumpfile, "    Float (0x%X) = FLOAT_RIGHT\n", cdFloat.Float);
	return;
}

/************************************************************************

    FUNCTION:   DumpCDTimerInfo

*************************************************************************/
void  LNPUBLIC   DumpCDTimerInfo (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDTIMERINFO	cdTimerInfo;
	WORD		wIndex;

	ODSReadMemory( &p, _CDTIMERINFO, &cdTimerInfo, 1);
	fprintf( dumpfile, "  TIMERINFO\n");
	fprintf( dumpfile, "    Interval = %lu\n", cdTimerInfo.Interval);
	for (wIndex = 0; wIndex < 4; wIndex++)
    	fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdTimerInfo.Reserved[wIndex] );
	
	return;

}

/************************************************************************

    FUNCTION:   DumpCDTableRowHeight

*************************************************************************/
void  LNPUBLIC   DumpCDTableRowHeight (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *			p = RecordPtr;
	CDTABLEROWHEIGHT	cdTableRowHeight;

	ODSReadMemory( &p, _CDTABLEROWHEIGHT, &cdTableRowHeight, 1);
	fprintf( dumpfile, "  TABLEROWHEIGHT\n");
	fprintf( dumpfile, "    RowHeight = %d\n", cdTableRowHeight.RowHeight);
	return;

}

/************************************************************************

    FUNCTION:   DumpCDTableLabel

*************************************************************************/
void  LNPUBLIC   DumpCDTableLabel (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDTABLELABEL	cdTableLabel;
	WORD			wIndex;

	ODSReadMemory( &p, _CDTABLELABEL, &cdTableLabel, 1);
	fprintf( dumpfile, "  TABLELABEL\n");
	fprintf( dumpfile, "    Label = %s\n", cdTableLabel.Label);
	for( wIndex = 0; wIndex < 3; wIndex++)
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdTableLabel.Reserved[wIndex]);
	
	fprintf( dumpfile, "    Flags = 0x%X: ", cdTableLabel.Flags );
	if( cdTableLabel.Flags & CDTABLELABEL_TABLABEL)
		fprintf( dumpfile, "TABLABEL ");
	if( cdTableLabel.Flags & CDTABLELABEL_ROWLABEL)
		fprintf(dumpfile, "ROWLABEL");
	fprintf(dumpfile, "\n");
	return;
}

/************************************************************************

    FUNCTION:   DumpCDRegionBegin

*************************************************************************/
void  LNPUBLIC   DumpCDRegionBegin (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDREGIONBEGIN	cdRegionBegin;

	ODSReadMemory( &p, _CDREGIONBEGIN, &cdRegionBegin, 1 );
	fprintf( dumpfile, "  REGIONBEGIN\n" );
	fprintf( dumpfile, "    Version = 0x%X\n", cdRegionBegin.Version );
	fprintf( dumpfile, "    Flags = 0x%X\n", cdRegionBegin.Flags );
	fprintf( dumpfile, "    RegionNum = %d\n", cdRegionBegin.RegionNum );
	fprintf( dumpfile, "    RegionName = %s\n", cdRegionBegin.RegionName );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDRegionEnd

*************************************************************************/
void  LNPUBLIC   DumpCDRegionEnd (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDREGIONEND	cdRegionEnd;

	ODSReadMemory( &p, _CDREGIONEND, &cdRegionEnd, 1 );
	fprintf( dumpfile, "  REGIONEND\n" );
	fprintf( dumpfile, "    RegionNum = %d\n", cdRegionEnd.RegionNum );
	fprintf( dumpfile, "    RegionName = %s\n", cdRegionEnd.RegionName );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDTransition

*************************************************************************/
void  LNPUBLIC   DumpCDTransition (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDTRANSITION	cdTransition;
	WORD			wIndex;
	char *			pString;

	ODSReadMemory( &p, _CDTRANSITION, &cdTransition, 1 );
	fprintf( dumpfile, "  TRANSITION\n" );
	pString = GetLiteralString( TransitionTypes, cdTransition.Type );
	fprintf( dumpfile, "    Type = %s\n", pString );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdTransition.Reserved[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedOutline

*************************************************************************/
void  LNPUBLIC   DumpCDEmbeddedOutline (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDEMBEDDEDOUTLINE	cdEmbeddedOutline;
	WORD				wIndex;
	DWORD				dwFlags;
	char *				pString;

	ODSReadMemory( &p, _CDEMBEDDEDOUTLINE, &cdEmbeddedOutline, 1 );
	fprintf( dumpfile, "  EMBEDDEDOUTLINE\n" );

	dwFlags = cdEmbeddedOutline.Flags;
	fprintf( dumpfile, "    Flags 0x%X: ", dwFlags );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_DISPLAYHORZ )		fprintf( dumpfile, "DISPLAYHORZ " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_HASIMAGELABEL )		fprintf( dumpfile, "HASIMAGELABEL " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TILEIMAGE )			fprintf( dumpfile, "TILEIMAGE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_USEAPPLET_INBROWSER )fprintf( dumpfile, "USEAPPLET_INBROWSER " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TYPE_TITLE )			fprintf( dumpfile, "TYPE_TITLE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_SHOWTWISTIE )		fprintf( dumpfile, "SHOWTWISTIE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TITLEFIXED )			fprintf( dumpfile, "TITLEFIXED " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TOPLEVELFIXED )		fprintf( dumpfile, "TOPLEVELFIXED " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_SUBLEVELFIXED )		fprintf( dumpfile, "SUBLEVELFIXED " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TREE_STYLE )			fprintf( dumpfile, "TREE_STYLE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_HASNAME )			fprintf( dumpfile, "HASNAME " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_HASTARGETFRAME )		fprintf( dumpfile, "HASTARGETFRAME " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_ALLTHESAME )			fprintf( dumpfile, "ALLTHESAME " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_BACK_ALLTHESAME )	fprintf( dumpfile, "BACK_ALLTHESAME " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_EXPAND_DATA )		fprintf( dumpfile, "EXPAND_DATA " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_EXPAND_ALL )			fprintf( dumpfile, "EXPAND_ALL " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_EXPAND_FIRST )		fprintf( dumpfile, "EXPAND_FIRST " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_EXPAND_SAVED )		fprintf( dumpfile, "EXPAND_SAVED " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_EXPAND_NONE )		fprintf( dumpfile, "EXPAND_NONE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_HASROOTNAME )		fprintf( dumpfile, "HASROOTNAME " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_RTLREADING )			fprintf( dumpfile, "RTLREADING " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_TWISTIEIMAGE )		fprintf( dumpfile, "TWISTIEIMAGE " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_HANDLEFOLDERUNREAD )	fprintf( dumpfile, "HANDLEFOLDERUNREAD " );
	if( dwFlags & EMBEDDEDOUTLINE_FLAG_NEWSTYLE_TWISTIE )	fprintf( dumpfile, "NEWSTYLE_TWISTIE " );
	fprintf( dumpfile, "\n" );
	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    Unused[%d] = (0x%X)\n", wIndex, cdEmbeddedOutline.Unused[wIndex] );
	fprintf( dumpfile, "    Alignment = (0x%X)\n", cdEmbeddedOutline.Alignment );

	fprintf( dumpfile, "    SpaceBetweenEntries = %d\n", cdEmbeddedOutline.SpaceBetweenEntries );
	
	fprintf( dumpfile, "    LabelLength = %d\n", cdEmbeddedOutline.LabelLength );
	if( cdEmbeddedOutline.LabelLength > 0 )
	{
		fprintf( dumpfile, "    Label = " );
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.LabelLength );
		p = ((char far *) p) + cdEmbeddedOutline.LabelLength;
	}
	fprintf( dumpfile, "    Style = %u\n", cdEmbeddedOutline.Style );
	fprintf( dumpfile, "    Title_VOffset = %u\n", cdEmbeddedOutline.Title_VOffset );
	fprintf( dumpfile, "    Title_HOffset = %u\n", cdEmbeddedOutline.Title_HOffset );
	fprintf( dumpfile, "    Title_Height  = %u\n", cdEmbeddedOutline.Title_Height );
	fprintf( dumpfile, "    TopLevel_VOffset = %u\n", cdEmbeddedOutline.TopLevel_VOffset );
	fprintf( dumpfile, "    TopLevel_HOffset = %u\n", cdEmbeddedOutline.TopLevel_HOffset );
	fprintf( dumpfile, "    TopLevel_Height  = %u\n", cdEmbeddedOutline.TopLevel_Height );
	fprintf( dumpfile, "    SubLevel_VOffset = %u\n", cdEmbeddedOutline.SubLevel_VOffset );
	fprintf( dumpfile, "    SubLevel_HOffset = %u\n", cdEmbeddedOutline.SubLevel_HOffset );
	fprintf( dumpfile, "    SubLevel_Height  = %u\n", cdEmbeddedOutline.SubLevel_Height );
	fprintf( dumpfile, "    NameLength = %d\n", cdEmbeddedOutline.NameLength );
	if(( cdEmbeddedOutline.NameLength > 0) && (cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASNAME))
	{
		fprintf( dumpfile, "    Frame Name = " );
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.NameLength );
		p = ((char far *) p) + cdEmbeddedOutline.NameLength;
	}
	fprintf( dumpfile, "    TargetFrameLength = %d\n", cdEmbeddedOutline.TargetFrameLength );
	if(( cdEmbeddedOutline.TargetFrameLength > 0 ) && ( cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASTARGETFRAME ))
	{
		fprintf( dumpfile, "    Target Frame = " );
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.TargetFrameLength );
		p = ((char far *) p) + cdEmbeddedOutline.TargetFrameLength;
	}
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		fprintf( dumpfile, "    SelectFontID[%d] = ", wIndex );
		DumpFontIDFields((FONTIDFIELDS *)&cdEmbeddedOutline.SelectFontID[wIndex] );
	}
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		fprintf( dumpfile, "    MouseFontID[%d] = ", wIndex );
		DumpFontIDFields((FONTIDFIELDS *)&cdEmbeddedOutline.MouseFontID[wIndex] );
	}
	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    Font_VOffset[%d] = %u\n", wIndex, cdEmbeddedOutline.Font_VOffset[wIndex] );
	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    Font_HOffset[%d] = %u\n", wIndex, cdEmbeddedOutline.Font_HOffset[wIndex] );
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		pString = GetLiteralString( AlignmentTable, cdEmbeddedOutline.Align[wIndex] );
		fprintf( dumpfile, "    Align[%d] (0x%X) = %s\n", wIndex, cdEmbeddedOutline.Align[wIndex], pString );
	}
	fprintf( dumpfile, "    Control_BackColor\n" );
	DumpColorValue( cdEmbeddedOutline.Control_BackColor );
	for( wIndex = 0; wIndex < 9; wIndex++ )
	{
		fprintf( dumpfile, "    BackColor[%d]\n", wIndex );
		DumpColorValue( cdEmbeddedOutline.BackColor[wIndex] );
	}
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		fprintf( dumpfile, "    SelectFontColor[%d]\n", wIndex );
		DumpColorValue( cdEmbeddedOutline.SelectFontColor[wIndex] );
	}
	for( wIndex = 0; wIndex < 4; wIndex++)
		fprintf( dumpfile, "    Repeat[%d] = (0x%X)\n", wIndex, cdEmbeddedOutline.Repeat );
	for( wIndex = 0; wIndex < 4; wIndex++ )
	{
		pString = GetLiteralString( AlignmentTable, cdEmbeddedOutline.Background_Align[wIndex] );
		fprintf( dumpfile, "    Background_Align[%d] = %s\n", wIndex, pString );
	}
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Background_VOffset[%d] = %u\n", wIndex, cdEmbeddedOutline.Background_VOffset[wIndex] );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Background_HOffset[%d] = %u\n", wIndex, cdEmbeddedOutline.Background_HOffset[wIndex] );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    wBackground_Image[%d] = (0x%X)\n", wIndex, cdEmbeddedOutline.wBackground_Image[wIndex] );
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		fprintf( dumpfile, "    NormalFontColor[%d]\n", wIndex );
		DumpColorValue( cdEmbeddedOutline.NormalFontColor[wIndex] );
	}
	for( wIndex = 0; wIndex < 3; wIndex++ )
	{
		fprintf( dumpfile, "    MouseFontColor[%d]\n", wIndex );
		DumpColorValue( cdEmbeddedOutline.MouseFontColor[wIndex] );
	}
	fprintf( dumpfile, "    RootLength = %d\n", cdEmbeddedOutline.RootLength );
	if(( cdEmbeddedOutline.RootLength > 0 ) && ( cdEmbeddedOutline.Flags & EMBEDDEDOUTLINE_FLAG_HASROOTNAME ))
	{
		fprintf( dumpfile, "    Root Name = " );
		PrintText(( char far *) p, (WORD)cdEmbeddedOutline.RootLength );
		p = ((char far *) p) + cdEmbeddedOutline.RootLength;
	}
	fprintf( dumpfile, "    TopLevel_PixelHeight = %u\n", cdEmbeddedOutline.TopLevel_PixelHeight );
	fprintf( dumpfile, "    wColWidth = %u\n", cdEmbeddedOutline.wColWidth );
	fprintf( dumpfile, "    SpareWord = %u\n", cdEmbeddedOutline.SpareWord );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdEmbeddedOutline.Spare[wIndex] );

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedView

*************************************************************************/
void  LNPUBLIC   DumpCDEmbeddedView (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDEMBEDDEDVIEW	cdEmbeddedView;
	DWORD			dwFlags;
	WORD			wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDVIEW, &cdEmbeddedView, 1 );
	fprintf( dumpfile, "  EMBEDDEDVIEW\n" );

	dwFlags = cdEmbeddedView.Flags;
	fprintf( dumpfile, "    Flags 0x%X = ", dwFlags );
	if( dwFlags & EMBEDDEDVIEW_FLAG_TRANSPARENT )						fprintf( dumpfile, "TRANSPARENT " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_USEAPPLET_INBROWSER )				fprintf( dumpfile, "USEAPPLET_INBROWSER " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_USEAPPLET_VIEWPROP )				fprintf( dumpfile, "USEAPPLET_VIEWPROP " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_USE_WEBLINES )						fprintf( dumpfile, "USE_WEBLINES " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_MOUSE_TRACK_ON )		fprintf( dumpfile, "MOUSE_TRACK_ON " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_HEADER_OFF )			fprintf( dumpfile, "HEADER_OFF " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_SHOW_AS_WEB_LINK )		fprintf( dumpfile, "SHOW_AS_WEB_LINK " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_SHOW_ACTION_BAR )		fprintf( dumpfile, "SHOW_ACTION_BAR " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_SHOW_SELECTION_MARGIN ) fprintf( dumpfile, "SHOW_SELECTION_MARGIN " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_SIMPLE_VIEW_SHOW_CURRENT_THREAD )	fprintf( dumpfile, "SHOW_CURRENT_THREAD " );
	if( dwFlags & EMBEDDEDVIEW_FLAG_NOT_USE_WEBVIEW_DEFAULT )			fprintf( dumpfile, "NOT_USE_WEBVIEW_DEFAULT " );
	fprintf( dumpfile, "\n" );
	DumpFontIDFields((FONTIDFIELDS *)&cdEmbeddedView.SpareFontID );
	fprintf( dumpfile, "    RestrictFormulaLength = %d\n", cdEmbeddedView.RestrictFormulaLength );
	fprintf( dumpfile, "    WebLines = %d\n", cdEmbeddedView.WebLines );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdEmbeddedView.Spare[wIndex] );
	fprintf( dumpfile, "    Restrict Formula = " );
	PrintFormula( p, cdEmbeddedView.RestrictFormulaLength );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDCellBackgroundData

*************************************************************************/
void  LNPUBLIC   DumpCDCellBackgroundData (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *				p = RecordPtr;
	CDCELLBACKGROUNDDATA	cdCellBackgroundData;
	char *					pString;
	WORD					wIndex;

	ODSReadMemory( &p, _CDCELLBACKGROUNDDATA, &cdCellBackgroundData, 1 );
	fprintf( dumpfile, "  CELLBACKGROUNDDATA\n" );
	pString = GetLiteralString( RepeatValueTable, cdCellBackgroundData.Repeat );
	fprintf( dumpfile, "    Repeat (0x%X) = %s\n", cdCellBackgroundData.Repeat, pString );
	wIndex = 0;
	fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdCellBackgroundData.Spare[wIndex] );
	fprintf( dumpfile, "    SpareDWORD = 0x%X\n", cdCellBackgroundData.SpareDWORD );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDTarget

*************************************************************************/
void  LNPUBLIC   DumpCDTarget (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDTARGET	cdTarget;

	ODSReadMemory( &p, _CDTARGET, &cdTarget, 1 ) ;
	fprintf( dumpfile, "  TARGET\n" );
	fprintf( dumpfile, "    TargetLength = %d\n", cdTarget.TargetLength );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdTarget.Flags );
	if( cdTarget.Flags & FLAG_TARGET_IS_FORMULA )
	{
		fprintf( dumpfile, "TARGET_IS_FORMULA " );
    }
	fprintf( dumpfile, "\n" );
	if( cdTarget.Flags & FLAG_TARGET_IS_FORMULA )
    {
     	fprintf( dumpfile, "    Target Formula:\n" );
		PrintFormula( p, cdTarget.TargetLength );
	}
    else
    {
        fprintf( dumpfile, "    Target Frame = " );
        if (cdTarget.TargetLength)
             PrintText (p, cdTarget.TargetLength);
        else
             fprintf ( dumpfile, "\n");
    }
	return;
}


/************************************************************************

    FUNCTION:   DumpCDMapElement

*************************************************************************/
void  LNPUBLIC   DumpCDMapElement (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDMAPELEMENT	cdMapElement;
	WORD			wIndex;

	ODSReadMemory( &p, _CDMAPELEMENT, &cdMapElement, 1 );
	fprintf( dumpfile, "  MAPELEMENT\n" );
	fprintf( dumpfile, "    Flags = (0x%X)\n", cdMapElement.Flags );
	fprintf( dumpfile, "    MapNameLength = %d\n", cdMapElement.MapNameLength );
	fprintf( dumpfile, "    LastDefaultRegionID = %u\n", cdMapElement.LastDefaultRegionID );
	fprintf( dumpfile, "    LastRectRegionID = %u\n", cdMapElement.LastRectRegionID );
	fprintf( dumpfile, "    LastCircleRegionID = %u\n", cdMapElement.LastCircleRegionID );
	fprintf( dumpfile, "    LastPolyRegionID = %u\n", cdMapElement.LastPolyRegionID );
	for( wIndex = 0; wIndex < 16; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdMapElement.Reserved[wIndex] );
	if( cdMapElement.MapNameLength > 0 )
	{
		fprintf( dumpfile, "    Map Name = " );
		PrintText( p, cdMapElement.MapNameLength );
	}
	return;
}

/************************************************************************

    FUNCTION:   DumpCDAreaElement

*************************************************************************/
void  LNPUBLIC   DumpCDAreaElement (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDAREAELEMENT	cdAreaElement;
	char *			pString;
	WORD			wIndex;

	ODSReadMemory( &p, _CDAREAELEMENT, &cdAreaElement, 1 );
	fprintf( dumpfile, "  AREAELEMENT\n" );
	fprintf( dumpfile, "    Flags = (0x%X)\n", cdAreaElement.Flags );
	pString = GetLiteralString( AreaShapeTable, cdAreaElement.Shape );
	fprintf( dumpfile, "    Shape = %u, %s\n", cdAreaElement.Shape, pString );
	fprintf( dumpfile, "    TabIndex = %d\n", cdAreaElement.TabIndex );
	fprintf( dumpfile, "    AccessKey = %u\n", cdAreaElement.AccessKey );
	for( wIndex = 0; wIndex < 16; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdAreaElement.Reserved[wIndex] );
	
	switch( cdAreaElement.Shape )
	{
	case AREA_SHAPE_RECT:
		{
			CDRECT	cdRect;

			ODSReadMemory( &p, _CDRECT, &cdRect, 1 );
			fprintf( dumpfile, "    Record Type = RECT\n" );
			fprintf( dumpfile, "      left   = %d\n", cdRect.left );
			fprintf( dumpfile, "      top    = %d\n", cdRect.top );
			fprintf( dumpfile, "      right  = %d\n", cdRect.right );
			fprintf( dumpfile, "      bottom = %d\n", cdRect.bottom );
			break;
		}
	case AREA_SHAPE_CIRCLE:
		{
			CDRECT	cdRect;
			
			ODSReadMemory( &p, _CDRECT, &cdRect, 1 );
			fprintf( dumpfile, "    Record Type = RECT\n" );
			fprintf( dumpfile, "      left = %d, top = %d, right = %d, bottom = %d\n",
										cdRect.left, cdRect.top, cdRect.right, cdRect.bottom );
			fprintf( dumpfile, "      Center x = %d (right(%d) + left(%d) / 2)\n",
										((cdRect.right + cdRect.left) / 2), cdRect.right, cdRect.left );
			fprintf( dumpfile, "      Center y = %d (bottom(%d) + top(%d) / 2)\n",
										((cdRect.bottom + cdRect.top) / 2), cdRect.bottom, cdRect.top );
			fprintf( dumpfile, "      Radius   = %d (right(%d) - left(%d) / 2)\n",
										((cdRect.right - cdRect.left) / 2), cdRect.right, cdRect.left );
			break;
		}
	case AREA_SHAPE_POLYGON:
		{
			WORD	num_pts;
			int		i;
			CDPOINT	cdPoint;

			ODSReadMemory( &p, _WORD, &num_pts, 1);
			if( num_pts > 0 )
			{
				fprintf( dumpfile, "    Number of Points = %d\n", num_pts );
				for( i = 0; i < num_pts; i++ )
				{
					ODSReadMemory( &p, _CDPOINT, &cdPoint, 1 );
					fprintf( dumpfile, "    Record Type = POINT\n" );
					fprintf( dumpfile, "      x = %d\n", cdPoint.x );
					fprintf( dumpfile, "      y = %d\n", cdPoint.y );
				}
			}
			break;
		}
	case AREA_SHAPE_DEFAULT:
	default:
		{
			fprintf( dumpfile, "    DEFAULT\n" );
			break;
		}
	}
	return;
}

/************************************************************************

    FUNCTION:   DumpCDResource

*************************************************************************/

void  LNPUBLIC   DumpCDResource (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {
	char far *	p = RecordPtr;
	CDRESOURCE	cdResource;
	char *		pString;
	WORD		wIndex;

	if (SIG_CD_HREF == RecordType)
		fprintf( dumpfile, "  HREF\n" );
	else if (SIG_CD_HREF2 == RecordType)
		fprintf( dumpfile, "  HREF2\n" );
	else if (SIG_CD_HREFBORDER == RecordType)
		fprintf( dumpfile, "  HREFBORDER\n" );
	else if (SIG_CD_TABLECELL_HREF == RecordType)
		fprintf( dumpfile, "  TABLECELL_HREF\n" );
	else if (SIG_CD_TABLECELL_HREF2 == RecordType)
		fprintf( dumpfile, "  TABLECELL_HREF2\n" );
	else
	{
		fprintf( dumpfile, "  Unknown resource type: %u (0x%X)\n",
			RecordType, RecordType );
		return;
	}

	ODSReadMemory( &p, _CDRESOURCE, &cdResource, 1 );

	fprintf( dumpfile, "    Flags = 0x%X: ", cdResource.Flags );
	if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )			fprintf( dumpfile, "FORUMULA " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_NOTELINKINLINE )	fprintf( dumpfile, "NOTELINKINLINE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_ABSOLUTE )			fprintf( dumpfile, "ABSOLUTE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_USEHINTFIRST )		fprintf( dumpfile, "USEHINTFIRST " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_CANNEDIMAGE )		fprintf( dumpfile, "CANNEDIMAGE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_PRIVATE_DATABASE )	fprintf( dumpfile, "PRIVATE_DATABASE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_PRIVATE_DESKTOP )	fprintf( dumpfile, "PRIVATE_DESKTOP " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_REPLICA_WILDCARD )	fprintf( dumpfile, "REPLICA_WILDCARD " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_SIMPLE )			fprintf( dumpfile, "SIMPLE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_DESIGN_MODE )		fprintf( dumpfile, "DESIGN_MODE " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_RESERVED1 )			fprintf( dumpfile, "RESERVED1 " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_RESERVED2 )			fprintf( dumpfile, "RESERVED2 " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_RESERVED3 )			fprintf( dumpfile, "RESERVED3 " );
	if( cdResource.Flags & CDRESOURCE_FLAGS_RESERVED4 )			fprintf( dumpfile, "RESERVED4 " );
	fprintf( dumpfile, "\n" );
	
	pString = GetLiteralString( ResourceTypeTable, cdResource.Type );
	fprintf( dumpfile, "    Type (0x%X) = %s\n", cdResource.Type, pString );

	pString = GetLiteralString( ResourceClassTable, cdResource.ResourceClass );
	fprintf( dumpfile, "    ResourceClass (0x%X) = %s\n", cdResource.ResourceClass, pString );

	fprintf( dumpfile, "    Length1 = %d\n", cdResource.Length1 );
	fprintf( dumpfile, "    ServerHintLength = %d\n", cdResource.ServerHintLength );
	fprintf( dumpfile, "    FileHintLength = %d\n", cdResource.FileHintLength );
	for( wIndex = 0; wIndex < 8; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdResource.Reserved[wIndex] );

	if( cdResource.ServerHintLength > 0 )
	{
		fprintf( dumpfile, "    SERVER-HINT = " );
		PrintText((char far *) p, (WORD)cdResource.ServerHintLength );
		p = ((char far *) p) + cdResource.ServerHintLength;
	}
	if( cdResource.FileHintLength > 0 )
	{
		fprintf( dumpfile, "    FILE-HINT = " );
		PrintText((char far *) p, (WORD)cdResource.FileHintLength );
		p = ((char far *) p) + cdResource.FileHintLength;
	}
	switch( cdResource.Type )
	{
	case CDRESOURCE_TYPE_URL:
		if( cdResource.Length1 > 0 )
		{
			fprintf( dumpfile, "    URL = " );
			if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
				PrintFormula( p, cdResource.Length1 );
			else
				PrintText((char far *)p, (WORD)cdResource.Length1 );
			p = ((char far *) p) + cdResource.Length1;
		}
		break;

	case CDRESOURCE_TYPE_NOTELINK:
		{
			if( cdResource.Flags & CDRESOURCE_FLAGS_NOTELINKINLINE )
			{
				NOTELINK	rscLink;

				fprintf( dumpfile, "    NOTELINKINLINE\n" );
				ODSReadMemory( &p, _NOTELINK, &rscLink, 1 );
				PrintNOTELINK( "\t", &rscLink );
			}
			else
			{
				WORD	rscLinkWord;
				
				ODSReadMemory( &p, _WORD, &rscLinkWord, 1 );
				fprintf( dumpfile, "    LINK-ID = 0x%X\n", rscLinkWord );
			}
			fprintf( dumpfile, "    ANCHOR = " );
			PrintText((char far *)p, (WORD)cdResource.Length1);
		}
		break;
		
	case CDRESOURCE_TYPE_NAMEDELEMENT:
		{
			DBID	rscDBID;

			ODSReadMemory( &p, _DBID, &rscDBID, 1 );
			fprintf( dumpfile, "    Replica ID = %#010lx - %#010lx\n",
											rscDBID.Innards[1], rscDBID.Innards[0]);
			if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
				PrintFormula( p, cdResource.Length1 );
			else
				PrintText((char far *)p, (WORD)cdResource.Length1 );
			p = ((char far *) p) + cdResource.Length1;
		}
		break;

	case CDRESOURCE_TYPE_ACTION:
		{
			if( cdResource.Flags & CDRESOURCE_FLAGS_FORMULA )
				PrintFormula( p, cdResource.Length1 );
		}
		break;
		
	case CDRESOURCE_TYPE_NOTEIDLINK:
	case CDRESOURCE_TYPE_NAMEDITEMELEMENT:
	default:
		break;
	}
	return;
}
/************************************************************************

    FUNCTION:   DumpCDEmbeddedCtl

*************************************************************************/

void  LNPUBLIC   DumpCDEmbeddedCtl (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDEMBEDDEDCTL	cdEmbeddedCtl;
	char *			pString;
	WORD			wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDCTL, &cdEmbeddedCtl, 1 );
	fprintf( dumpfile, "  EMBEDDEDCTL\n" );
	fprintf( dumpfile, "    CtlStyle 0x%X = ", cdEmbeddedCtl.CtlStyle );
	switch( cdEmbeddedCtl.CtlType )
	{
	case EMBEDDEDCTL_EDIT:
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_EDITMULTILINE )	fprintf( dumpfile, " MULTILINE" );
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_EDITVSCROLL )	fprintf( dumpfile, " VSCROLL" );
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_EDITPASSWORD )	fprintf( dumpfile, " PASSWORD" );
		fprintf( dumpfile, "\n" );
		break;

	case EMBEDDEDCTL_COMBO:
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_EDITCOMBO )	fprintf( dumpfile, " COMBO" );
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_VALID )	fprintf( dumpfile, " VALID" );
		fprintf( dumpfile, "\n" );
		break;

	case EMBEDDEDCTL_LIST:
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_LISTMULTISEL ) fprintf( dumpfile, " MULTISEL" );
		fprintf( dumpfile, "\n" );
		break;

	case EMBEDDEDCTL_TIME:
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_CALENDAR )	fprintf( dumpfile, " CALENDAR" );
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_TIME )		fprintf( dumpfile, " TIME" );
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_DURATION )	fprintf( dumpfile, " DURATION" );
		fprintf( dumpfile, "\n" );
		break;

	case EMBEDDEDCTL_TIMEZONE:
		if( cdEmbeddedCtl.CtlStyle & EC_STYLE_TIMEZONE ) fprintf( dumpfile, " TIMEZONE" );
		fprintf( dumpfile, "\n" );
		break;

	case EMBEDDEDCTL_COLOR:
		fprintf( dumpfile, " COLOR\n" );
		break;

	default:
		break;
	}
	fprintf( dumpfile, "    Flags = 0x%X: ", cdEmbeddedCtl.Flags );
	if( cdEmbeddedCtl.Flags & EC_FLAG_DIALOGUNITS )		fprintf( dumpfile, " DIALOGUNITS" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_FITTOCONTENTS )	fprintf( dumpfile, " FITTOCONTENTS" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_ALWAYSACTIVE )	fprintf( dumpfile, " ALWAYSACTIVE" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_FITTOWINDOW )		fprintf( dumpfile, " FITTOWINDOW" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_POSITION_TOP )	fprintf( dumpfile, " POSITION_TOP" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_POSITION_BOTTOM )	fprintf( dumpfile, " POSITION_BOTTOM" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_POSITION_ASCENT )	fprintf( dumpfile, " POSITION_ASCENT" );
	if( cdEmbeddedCtl.Flags & EC_FLAG_POSITION_HEIGHT )	fprintf( dumpfile, " POSIITON_HEIGHT" );
	fprintf( dumpfile, "\n" );
	if( EC_DIALOGUNITS( cdEmbeddedCtl.Flags ))
		fprintf( dumpfile, "    Width and Height are in dialog units\n" );
	else
		fprintf( dumpfile, "    Width and Height are in twips\n" );
	fprintf( dumpfile, "    Width = %u\n", cdEmbeddedCtl.Width );
	fprintf( dumpfile, "    Height = %u\n", cdEmbeddedCtl.Height );
	fprintf( dumpfile, "    Version 0x%X: ", cdEmbeddedCtl.Version );
	if( cdEmbeddedCtl.Version == EMBEDDEDCTL_VERSION1 )		fprintf( dumpfile, "VERSION1" );
	fprintf( dumpfile, "\n" );
	pString = GetLiteralString( EmbeddedCtlTypes, cdEmbeddedCtl.CtlType );
	fprintf( dumpfile, "    CtlType 0x%X = %s\n", cdEmbeddedCtl.CtlType, pString );
	fprintf( dumpfile, "    MaxChars = %u\n", cdEmbeddedCtl.MaxChars );
	fprintf( dumpfile, "    MaxLines = %u\n", cdEmbeddedCtl.MaxLines );
	fprintf( dumpfile, "    Percentage = %u\n", cdEmbeddedCtl.Percentage );
	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdEmbeddedCtl.Spare[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDEvent

*************************************************************************/

void  LNPUBLIC   DumpCDEvent (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {

	char far *	p = RecordPtr;
	CDEVENT		cdEvent;
	char *		pString;
	WORD		wIndex;
	WORD		ExtraSig;

	if( SIG_CD_CLIENT_EVENT == RecordType)
		fprintf( dumpfile,"  CLIENT_EVENT\n");
	else /* SIG_CD_EVENT */
		fprintf( dumpfile,"  EVENT\n");
	ODSReadMemory( &p, _CDEVENT, &cdEvent, 1 );

	fprintf( dumpfile, "    Flags = (0x%X)\n", cdEvent.Flags );
			if( cdEvent.Flags & EVENT_HAS_LIBRARIES ) fprintf( dumpfile, " EVENT_HAS_LIBRARIES " );
	pString = GetLiteralString( EventHTMLTable, cdEvent.EventType );
	fprintf( dumpfile, "    EventType = 0x%X: %s\n", cdEvent.EventType, pString );
	pString = GetLiteralString( EventActionTable, cdEvent.ActionType );
	fprintf( dumpfile, "    ActionType = 0x%X: %s\n", cdEvent.ActionType, pString );
	fprintf( dumpfile, "    ActionLength = %u\n", cdEvent.ActionLength );
	fprintf( dumpfile, "    SignatureLength = %u\n", cdEvent.SignatureLength );
	for( wIndex = 0; wIndex < 14; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdEvent.Reserved[wIndex] );
	if( cdEvent.ActionLength > 0 )
	{
		switch( cdEvent.ActionType )
		{
			case ACTION_TYPE_FORMULA:
				PrintFormula( p, (WORD) cdEvent.ActionLength );
				break;
			case ACTION_TYPE_CANNED_ACTION:
				NSFDDUMPDumpMemory( p, (WORD) cdEvent.ActionLength );
				break;
			case ACTION_TYPE_LOTUS_SCRIPT:
				PrintScriptSource( p, (WORD) cdEvent.ActionLength );
				break;
			case ACTION_TYPE_JAVASCRIPT:
				PrintText( p, (WORD) cdEvent.ActionLength );
				break;
			default:
				NSFDDUMPDumpMemory( p, (WORD) cdEvent.ActionLength );
				break;
		}
		p = ((char far *) p) + cdEvent.ActionLength;
	}
	if( cdEvent.SignatureLength > 0 )
	{
		ODSReadMemory( &p, _WORD, &ExtraSig, 1 );
		pString = GetLiteralString( SignatureTypeTable, ExtraSig );
		fprintf( dumpfile, "    Additional Signature = SIG_%s\n", pString);
	}
	return;
}

/************************************************************************

    FUNCTION:   DumpCDIDName

*************************************************************************/

void  LNPUBLIC   DumpCDIDName (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {
	
	char far *	p = RecordPtr;
	CDIDNAME	cdIDName;
	WORD		wIndex;

	ODSReadMemory( &p, _CDIDNAME, &cdIDName, 1 );
	if( SIG_CD_IDNAME == RecordType )
		fprintf( dumpfile, "   IDNAME\n");
	else /* SIG_CD_TABLECELL_IDNAME */
		fprintf( dumpfile, "   TABLECELL_IDNAME\n");

	fprintf( dumpfile, "    Length = %d\n", cdIDName.Length );
	if( cdIDName.Length > 0 )
	{
		fprintf( dumpfile, "    ID = ");
		PrintText( (char far *) p, (WORD)cdIDName.Length );
		p = ((char far *) p) + cdIDName.Length;
	}
	fprintf( dumpfile, "    wClassLen = %d\n", cdIDName.wClassLen );
	if( cdIDName.wClassLen > 0 )
	{
		fprintf( dumpfile, "    Class = " );
		PrintText( (char far *) p, (WORD)cdIDName.wClassLen );
		p = ((char far *) p) + cdIDName.wClassLen;
	}
	fprintf( dumpfile, "    wStyleLen = %d\n", cdIDName.wStyleLen );
	if( cdIDName.wStyleLen > 0 )
	{
		fprintf( dumpfile, "    Style = " );
		PrintText( (char far *) p, (WORD)cdIDName.wStyleLen );
		p = ((char far *) p) + cdIDName.wStyleLen;
	}
	fprintf( dumpfile, "    wTitleLen = %d\n", cdIDName.wTitleLen );
	if( cdIDName.wTitleLen > 0 )
	{
		fprintf( dumpfile, "    Title = " );
		PrintText( (char far *) p, (WORD)cdIDName.wTitleLen );
		p = ((char far *) p) + cdIDName.wTitleLen;
	}
	fprintf( dumpfile, "    wExtraLen = %d\n", cdIDName.wExtraLen );
	if( cdIDName.wExtraLen > 0 )
	{
		fprintf( dumpfile, "    Extra = " );
		PrintText( (char far *) p, (WORD)cdIDName.wExtraLen );
		p = ((char far *) p) + cdIDName.wExtraLen;
	}
	fprintf( dumpfile, "    wNameLen = %d\n", cdIDName.wNameLen );
	if( cdIDName.wNameLen > 0 )
	{
		fprintf( dumpfile, "    Name = " );
		PrintText( (char far *) p, (WORD)cdIDName.wNameLen );
	}
	for( wIndex = 0; wIndex < 10; wIndex++ )
		fprintf( dumpfile, "    reserved[%d] = (0x%X)\n", wIndex, cdIDName.reserved[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDPreTableBegin

*************************************************************************/

void  LNPUBLIC   DumpCDPreTableBegin (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDPRETABLEBEGIN	cdPreTableBegin;
	DWORD			dwFlags;
	char *			pString;
	WORD			wIndex;

	ODSReadMemory( &p, _CDPRETABLEBEGIN, &cdPreTableBegin, 1 );
	fprintf( dumpfile, "  PRETABLEBEGIN\n" );
	dwFlags = cdPreTableBegin.Flags;
	fprintf( dumpfile, "    Flags 0x%X: ", dwFlags );
	if( dwFlags & CDPRETABLE_AUTO_CELL_WIDTH )	fprintf( dumpfile, "AUTO_CELL_WIDTH " );
	if( dwFlags & CDPRETABLE_DONTWRAP )			fprintf( dumpfile, "DONTWRAP " );
	if( dwFlags & CDPRETABLE_DROPSHADOW )		fprintf( dumpfile, "DROPSHADOW " );
	if( dwFlags & CDPRETABLE_FIELDDRIVEN )		fprintf( dumpfile, "FIELDDRIVEN " );
	if( dwFlags & CDPRETABLE_V4SPACING )		fprintf( dumpfile, "V4SPACING " );
	if( dwFlags & CDPRETABLE_USEBORDERCOLOR )	fprintf( dumpfile, "USEBORDERCOLOR " );
	if( dwFlags & CDPRETABLE_WIDTHSAMEASWINDOW )fprintf( dumpfile, "WIDTHSAMEASWINDOW ");
	if( dwFlags & CDPRETABLE_SHOWTABS )			fprintf( dumpfile, "SHOWTABS " );
	if( dwFlags & CDPRETABLE_SHOWTABSONLEFT )	fprintf( dumpfile, "SHOWTABSONLEFT " );
	if( dwFlags & CDPRETABLE_SHOWTABSONBOTTOM )	fprintf( dumpfile, "SHOWTABSONBOTTOM " );
	if( dwFlags & CDPRETABLE_SHOWTABSONRIGHT )	fprintf( dumpfile, "SHOWTABSONRIGHT " );
	fprintf( dumpfile, "\n");
	fprintf( dumpfile, "    Rows = %u\n", cdPreTableBegin.Rows );
	fprintf( dumpfile, "    Columns = %u\n", cdPreTableBegin.Columns );
	fprintf( dumpfile, "    ColumnSizingBits1 = 0x%X\n", cdPreTableBegin.ColumnSizingBits1 );
	fprintf( dumpfile, "    ColumnSizingBits2 = 0x%X\n", cdPreTableBegin.ColumnSizingBits2 );
    if (cdPreTableBegin.ViewerType)
	    pString = GetLiteralString( ViewerTypeTable, cdPreTableBegin.ViewerType );
    else
        pString = "";
	fprintf( dumpfile, "    ViewerType 0x%X: %s\n", cdPreTableBegin.ViewerType, pString );
	fprintf( dumpfile, "    Spare = 0x%X\n", cdPreTableBegin.Spare );
	fprintf( dumpfile, "    MinRowHeight = %u\n", cdPreTableBegin.MinRowHeight );
	wIndex = 0;
	fprintf( dumpfile, "    Spares[%d] = (0x%X)\n", wIndex, cdPreTableBegin.Spares[wIndex] );
	fprintf( dumpfile, "    StyleColor1 = 0x%X\n", cdPreTableBegin.StyleColor1 );
	fprintf( dumpfile, "    StyleColor2 = 0x%X\n", cdPreTableBegin.StyleColor2 );
	fprintf( dumpfile, "    InnerBorderColor\n" );
	DumpColorValue( cdPreTableBegin.InnerBorderColor );
	fprintf( dumpfile, "    NameLength = %d\n", cdPreTableBegin.NameLength );
	if( cdPreTableBegin.NameLength > 0 )
	{
		fprintf( dumpfile, "    Name = " );
		PrintText( (char far *) p, (WORD)cdPreTableBegin.NameLength );
		p = ((char far *) p) + cdPreTableBegin.NameLength;
	}
	fprintf( dumpfile, "    ImagePacketLength = %d\n", cdPreTableBegin.ImagePacketLength );
	if( cdPreTableBegin.ImagePacketLength > 0 )
	{
		fprintf( dumpfile, "    Image Packet = ");
		PrintText( (char far *) p, (WORD)cdPreTableBegin.ImagePacketLength );
		p = ((char far *) p) + cdPreTableBegin.ImagePacketLength;
	}
	fprintf( dumpfile, "    RowLabelDataLength = %d\n", cdPreTableBegin.RowLabelDataLength );
	if (cdPreTableBegin.RowLabelDataLength > 0 )
	{
		fprintf( dumpfile, "    Row Label Data = " );
		PrintText( (char far *) p, (WORD)cdPreTableBegin.RowLabelDataLength );
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDBorderInfo

*************************************************************************/

void  LNPUBLIC   DumpCDBorderInfo (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDBORDERINFO	cdBorderInfo;
	WORD			wIndex;
	char *			pString;

	ODSReadMemory( &p, _CDBORDERINFO, &cdBorderInfo, 1 );
	fprintf( dumpfile, "  BORDERINFO\n" );
	fprintf( dumpfile, "    Flags = 0x%X\n", cdBorderInfo.Flags );
	pString = GetLiteralString( BorderStyleTable, cdBorderInfo.BorderStyle );
	fprintf( dumpfile, "    BorderStyle (0x%X) = %s\n", cdBorderInfo.BorderStyle, pString );
	fprintf( dumpfile, "    BorderWidthTop    = %u\n", cdBorderInfo.BorderWidthTop );
	fprintf( dumpfile, "    BorderWidthLeft   = %u\n", cdBorderInfo.BorderWidthLeft );
	fprintf( dumpfile, "    BorderWidthBottom = %u\n", cdBorderInfo.BorderWidthBottom );
	fprintf( dumpfile, "    BorderWidthRight  = %u\n", cdBorderInfo.BorderWidthRight );
	fprintf( dumpfile, "    dwSpare = 0x%X\n", cdBorderInfo.dwSpare );
	fprintf( dumpfile, "    BorderFlags 0x%X: ", cdBorderInfo.BorderFlags );
	if( cdBorderInfo.BorderFlags & CDBORDER_FLAGS_DROP_SHADOW )	fprintf( dumpfile, "DROP_SHADOW " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    DropShadowWidth  = %u\n", cdBorderInfo.DropShadowWidth );
	fprintf( dumpfile, "    InnerWidthTop    = %u\n", cdBorderInfo.InnerWidthTop );
	fprintf( dumpfile, "    InnerWidthLeft   = %u\n", cdBorderInfo.InnerWidthLeft );
	fprintf( dumpfile, "    InnerWidthBottom = %u\n", cdBorderInfo.InnerWidthBottom );
	fprintf( dumpfile, "    InnerWidthRight  = %u\n", cdBorderInfo.InnerWidthRight );
	fprintf( dumpfile, "    OuterWidthTop    = %u\n", cdBorderInfo.OuterWidthTop );
	fprintf( dumpfile, "    OuterWidthLeft   = %u\n", cdBorderInfo.OuterWidthLeft );
	fprintf( dumpfile, "    OuterWidthBottom = %u\n", cdBorderInfo.OuterWidthBottom );
	fprintf( dumpfile, "    OuterWidthRight  = %u\n", cdBorderInfo.OuterWidthRight );
	fprintf( dumpfile, "    Color\n" );
	DumpColorValue( cdBorderInfo.Color );
	for( wIndex = 0; wIndex < 5; wIndex++ )
		fprintf( dumpfile, "    wSpares[%d] = 0x%X\n", wIndex, cdBorderInfo.wSpares[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedSchedCtl

*************************************************************************/

void  LNPUBLIC   DumpCDEmbeddedSchedCtl (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDEMBEDDEDSCHEDCTL	cdEmbeddedSchedCtl;
	WORD				wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDSCHEDCTL, &cdEmbeddedSchedCtl, 1 );
	fprintf( dumpfile, "  EMBEDDEDSCHEDCTL\n" );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdEmbeddedSchedCtl.Flags );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_USE_COLORS1 ) fprintf( dumpfile, "USE_COLORS1 " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_NO_INITFROMITEMS ) fprintf( dumpfile, "NO_INITFROMITEMS " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_NO_REFRESHFROMITEMS ) fprintf( dumpfile, "NO_REFRESHFROMITEMS " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ALLOW_FILTERING ) fprintf( dumpfile, "ALLOW_FILTERING " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_USE_COLORS2 ) fprintf( dumpfile, "USE_COLORS2 " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_NO_SHOWLEGEND ) fprintf( dumpfile, "NO_SHOWLEGEND " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_SHOWINTERVALINDICATOR ) fprintf( dumpfile, "SHOWINTERVALINDICATOR " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_SHOW_TWISTIES ) fprintf( dumpfile, "SHOW_TWISTIES " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ALLOW_EDIT_INPLACE ) fprintf( dumpfile, "ALLOW_EDIT_INPLACE  " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ATTENDEE_WIDTH_DEFINED ) fprintf( dumpfile, "ATTENDEE_WIDTH_DEFINED " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ATTENDEE_WIDTH_FIXED ) fprintf( dumpfile, "ATTENDEE_WIDTH_FIXED " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_PEOPLE_INVISIBLE ) fprintf( dumpfile, "PEOPLE_INVISIBLE " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ROOMS_VISIBLE ) fprintf( dumpfile, "ROOMS_VISIBLE " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_RESOURCES_VISIBLE ) fprintf( dumpfile, "RESOURCES_VISIBLE " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_PEOPLE_FIXEDHEIGHT ) fprintf( dumpfile, "PEOPLE_FIXEDHEIGHT " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ROOMS_FIXEDHEIGHT ) fprintf( dumpfile, "ROOMS_FIXEDHEIGHT " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_RESOURCES_FIXEDHEIGHT ) fprintf( dumpfile, "RESOURCES_FIXEDHEIGHT " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_ATTENDEE_LINES_DEFINED ) fprintf( dumpfile, "ATTENDEE_LINES_DEFINED " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_RTL_READING ) fprintf( dumpfile, "RTL_READING " );
	if( cdEmbeddedSchedCtl.Flags & EMBEDDEDSCHED_FLAG_NO_LAUNCH ) fprintf( dumpfile, "NO_LAUNCH " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    TargetFrameLength = %d\n", cdEmbeddedSchedCtl.TargetFrameLength );
	if( cdEmbeddedSchedCtl.TargetFrameLength > 0 )
	{
		fprintf( dumpfile, "    Target Frame = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtl.TargetFrameLength );
		p = ((char far *) p) + cdEmbeddedSchedCtl.TargetFrameLength;
	}
	fprintf( dumpfile, "    DisplayStartDTItemFormulaLength = %d\n", cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength );
	if( cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength > 0 )
	{
		fprintf( dumpfile, "    Display Start Date Time Item Formula = " );
		PrintFormula( p, cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtl.DisplayStartDTItemFormulaLength;
	}
	fprintf( dumpfile, "    HrsPerDayItemFormulaLength = %d\n", cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength );
	if( cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength > 0 )
	{
		fprintf( dumpfile, "    HrsPerDay Item Formula = " );
		PrintFormula( p, cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtl.HrsPerDayItemFormulaLength;
	}
	fprintf( dumpfile, "    ReqPeopleItemsFormulaLength = %d\n", cdEmbeddedSchedCtl.ReqPeopleItemsFormulaLength );
	if( cdEmbeddedSchedCtl.ReqPeopleItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    Req People Items Formula = " );
		PrintFormula( p, cdEmbeddedSchedCtl.ReqPeopleItemsFormulaLength );
	}
	fprintf( dumpfile, "    BusyTimeColor\n" );
	DumpColorValue( cdEmbeddedSchedCtl.BusyTimeColor );
	fprintf( dumpfile, "    FreeTimeColor\n" );
	DumpColorValue( cdEmbeddedSchedCtl.FreeTimeColor );
	fprintf( dumpfile, "    NoDataColor\n" );
	DumpColorValue( cdEmbeddedSchedCtl.NoDataColor );
	fprintf( dumpfile, "    DataRestrictedColor\n" );
	DumpColorValue( cdEmbeddedSchedCtl.DataRestrictedColor );
	fprintf( dumpfile, "    GridLineColor\n" );
	DumpColorValue( cdEmbeddedSchedCtl.GridLineColor );
	fprintf( dumpfile, "    NameColWidth = %d\n", cdEmbeddedSchedCtl.NameColWidth );
	fprintf( dumpfile, "    PeopleLines = %d\n", cdEmbeddedSchedCtl.PeopleLines );
	fprintf( dumpfile, "    RoomsLines = %d\n", cdEmbeddedSchedCtl.RoomsLines );
	fprintf( dumpfile, "    ResourcesLines = %d\n", cdEmbeddedSchedCtl.ResourcesLines );
	for( wIndex = 0; wIndex < 5; wIndex++ )
		fprintf( dumpfile, "    SpareWORD[%d] = (0x%X)\n", wIndex, cdEmbeddedSchedCtl.SpareWORD[wIndex] );
	for( wIndex = 0; wIndex < 13; wIndex++ )
		fprintf( dumpfile, "    SpareDWORD[%d] = (0x%X)\n", wIndex, cdEmbeddedSchedCtl.SpareDWORD[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDExt2Field

*************************************************************************/

void  LNPUBLIC   DumpCDExt2Field (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDEXT2FIELD	cdExt2Field;
	char *		pString;
	DWORD		Style;

	ODSReadMemory( &p, _CDEXT2FIELD, &cdExt2Field, 1 );
	fprintf( dumpfile, "  EXT2FIELD\n" );
	fprintf( dumpfile, "    Numeric Symbol Data\n" );
	pString = GetLiteralString( PreferencesFromTable, cdExt2Field.NumSymPref );
	fprintf( dumpfile, "    NumSysPref = %u: %s\n", cdExt2Field.NumSymPref, pString );
	fprintf( dumpfile, "    NumSymFlags = 0x%X: ", cdExt2Field.NumSymFlags );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    DecimalSymLength = %d\n", cdExt2Field.DecimalSymLength );
	fprintf( dumpfile, "    MilliSepSymLength = %d\n", cdExt2Field.MilliSepSymLength );
	fprintf( dumpfile, "    NegativeSymLength = %d\n", cdExt2Field.NegativeSymLength );
	fprintf( dumpfile, "    MilliGroupSize = %d\n", cdExt2Field.MilliGroupSize );
	fprintf( dumpfile, "    VerticalSpacing = (0x%X)\n", cdExt2Field.VerticalSpacing );
	fprintf( dumpfile, "    HorizontalSpacing = (0x%X)\n", cdExt2Field.HorizontalSpacing );
	fprintf( dumpfile, "    Unused2 = (0x%X)\n", cdExt2Field.Unused2 );
	fprintf( dumpfile, "    FirstFieldLimitType = (0x%X)\n", cdExt2Field.FirstFieldLimitType );
	fprintf( dumpfile, "    Currency Data\n" );
	pString = GetLiteralString( PreferencesFromTable, cdExt2Field.CurrencyPref );
	fprintf( dumpfile, "    CurrencyPref = %u: %s\n", cdExt2Field.CurrencyPref, pString );
	pString = GetLiteralString( CurrencySelectionTable, cdExt2Field.CurrencyType );
	fprintf( dumpfile, "    CurrencyType = %u: %s\n", cdExt2Field.CurrencyType, pString );
	fprintf( dumpfile, "    CurrencyFlags = 0x%X: ", cdExt2Field.CurrencyFlags );
	if( cdExt2Field.CurrencyFlags & NCURFMT_SYMFOLLOWS )	fprintf( dumpfile, " SYMFOLLOWS" );
	if( cdExt2Field.CurrencyFlags & NCURFMT_USESPACES )		fprintf( dumpfile, " USESPACES" );
	if( cdExt2Field.CurrencyFlags & NCURFMT_ISOSYMUSED )	fprintf( dumpfile, " ISOSYMUSED" );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    CurrencySymLength = %d\n", cdExt2Field.CurrencySymLength );
	fprintf( dumpfile, "    ISOCountry = 0x%X\n", cdExt2Field.ISOCountry );
	fprintf( dumpfile, "    Unused3 = (0x%X)\n", cdExt2Field.Unused3 );
	fprintf( dumpfile, "    Unused4 = (0x%X)\n", cdExt2Field.Unused4 );
	fprintf( dumpfile, "    Date/Time Formatting data\n" );
	pString = GetLiteralString( PreferencesFromTable, cdExt2Field.DTPref );
	fprintf( dumpfile, "    DTPref = %u: %s\n", cdExt2Field.DTPref, pString );
	fprintf( dumpfile, "	DTFlags = 0x%X: ", cdExt2Field.DTFlags );
   	if( cdExt2Field.DTFlags & DT_VALID )		fprintf( dumpfile, " VALID" );
	if( cdExt2Field.DTFlags & DT_4DIGITYEAR )	fprintf( dumpfile, " 4DIGITYEAR" );
	if( cdExt2Field.DTFlags & DT_ALPHAMONTH )	fprintf( dumpfile, " ALPHAMONTH" );
	if( cdExt2Field.DTFlags & DT_SHOWTIME )		fprintf( dumpfile, " SHOWTIME" );
	if( cdExt2Field.DTFlags & DT_SHOWDATE )		fprintf( dumpfile, " SHOWDATE" );
	if( cdExt2Field.DTFlags & DT_24HOUR )		fprintf( dumpfile, " 24HOUR" );
	Style = DT_GET_STYLE( cdExt2Field.DTFlags );
	if( Style == DT_STYLE_YMD )
		fprintf( dumpfile, " STYLE_YMD" );
	else if( Style == DT_STYLE_MDY )
		fprintf( dumpfile, " STYLE_MDY" );
	else if( Style == DT_STYLE_DMY )
		fprintf( dumpfile, " STYLE_DMY" );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    DTFlags2 = 0x%X: ", cdExt2Field.DTFlags2 );
	if( cdExt2Field.DTFlags2 & DT_USE_TFMT )	fprintf( dumpfile, " USE_TFMT" );
	fprintf( dumpfile, "\n" );
	pString = GetLiteralString( DTDOWFmtValues, cdExt2Field.DTDOWFmt );
	fprintf( dumpfile, "    DTDOWFmt = 0x%X: %s\n", cdExt2Field.DTDOWFmt, pString );
	pString = GetLiteralString( DTYearFmtValues, cdExt2Field.DTYearFmt );
	fprintf( dumpfile, "    DTYearFmt = 0x%X: %s\n", cdExt2Field.DTYearFmt, pString );
	pString = GetLiteralString( DTMonthFmtValues, cdExt2Field.DTMonthFmt );
	fprintf( dumpfile, "    DTMonthFmt = 0x%X: %s\n", cdExt2Field.DTMonthFmt, pString );
	pString = GetLiteralString( DTDayFmtValues, cdExt2Field.DTDayFmt );
	fprintf( dumpfile, "    DTDayFmt = 0x%X: %s\n", cdExt2Field.DTDayFmt, pString );
	fprintf( dumpfile, "    DTDsep1Len = %d\n", cdExt2Field.DTDsep1Len );
	fprintf( dumpfile, "    DTDsep2Len = %d\n", cdExt2Field.DTDsep2Len );
	fprintf( dumpfile, "    DTDsep3Len = %d\n", cdExt2Field.DTDsep3Len );
	fprintf( dumpfile, "    DTTsepLen = %d\n", cdExt2Field.DTTsepLen );
	pString = GetLiteralString( DTDShowValues, cdExt2Field.DTDShow );
	fprintf( dumpfile, "    DTDShow = 0x%X: %s\n", cdExt2Field.DTDShow, pString );
	fprintf( dumpfile, "    DTDSpecial = 0x%X: ", cdExt2Field.DTDSpecial );
	if( cdExt2Field.DTDSpecial == DT_DSPEC_NONE )
		fprintf( dumpfile, " NONE" );
	else
	{
		if( cdExt2Field.DTDSpecial & DT_DSPEC_TODAY )	fprintf( dumpfile, " TODAY" );
		if( cdExt2Field.DTDSpecial & DT_DSPEC_Y4 )		fprintf( dumpfile, " Y4" );
		if( cdExt2Field.DTDSpecial & DT_DSPEC_21Y4 )	fprintf( dumpfile, " 21Y4" );
		if( cdExt2Field.DTDSpecial & DT_DSPEC_CURYR )	fprintf( dumpfile, " CURYR" );
	}
	fprintf( dumpfile, "\n" );
	pString = GetLiteralString( DTTShowValues, cdExt2Field.DTTShow );
	fprintf( dumpfile, "    DTTShow = 0x%X: %s\n", cdExt2Field.DTTShow, pString );
	fprintf( dumpfile, "    DTTZone = 0x%X: ", cdExt2Field.DTTZone );
	if (cdExt2Field.DTTZone == TZFMT_NEVER)
	    fprintf( dumpfile, "Adjust all times to local zone\n" );
	else if (cdExt2Field.DTTZone == TZFMT_SOMETIMES)
	    fprintf( dumpfile, "Show only if zone not local\n" );
	else if (cdExt2Field.DTTZone == TZFMT_ALWAYS)
	     fprintf( dumpfile, "Always show time zone\n" );
	fprintf( dumpfile, "    Unused5 = (0x%X)\n", cdExt2Field.Unused5 );
	fprintf( dumpfile, "    ECFlags = (0x%X)", cdExt2Field.ECFlags );
	if( cdExt2Field.ECFlags & EC_FLAG_WIDTH_PROPORTIONAL )	fprintf( dumpfile, " WIDTH_PROPORTIONAL" );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    Unused612 = (0x%X)\n", cdExt2Field.Unused612 );
	fprintf( dumpfile, "    wCharacters = %d\n", cdExt2Field.wCharacters );
	fprintf( dumpfile, "    wInputEnabledLen = %d\n", cdExt2Field.wInputEnabledLen );
	fprintf( dumpfile, "    Unused7 = (0x%X)\n", cdExt2Field.Unused7 );
	if( cdExt2Field.DecimalSymLength > 0 )
	{
		fprintf( dumpfile, "    Decimal Symbol\n" );
		PrintText( p, cdExt2Field.DecimalSymLength );
		p = ((char far *) p) + cdExt2Field.DecimalSymLength;
	}
	if( cdExt2Field.MilliSepSymLength > 0 )
	{
		fprintf( dumpfile, "    Milli. Sep. Symbol\n" );
		PrintText( p, cdExt2Field.MilliSepSymLength );
		p = ((char far *) p) + cdExt2Field.MilliSepSymLength;
	}
	if( cdExt2Field.NegativeSymLength > 0 )
	{
		fprintf( dumpfile, "    Negative Symbol\n" );
		PrintText( p, cdExt2Field.NegativeSymLength );
		p = ((char far *) p) + cdExt2Field.NegativeSymLength;
	}
	if( cdExt2Field.CurrencySymLength > 0 )
	{
		fprintf( dumpfile, "    Currency Symbol\n" );
		PrintText( p, cdExt2Field.CurrencySymLength );
		p = ((char far *) p) + cdExt2Field.CurrencySymLength;
	}
	if( cdExt2Field.DTDsep1Len > 0 )
	{
		fprintf( dumpfile, "    DTDsep1 = " );
		PrintText( p, (BYTE)cdExt2Field.DTDsep1Len );
		p = ((char far *) p) + cdExt2Field.DTDsep1Len;
	}
	if( cdExt2Field.DTDsep2Len > 0 )
	{
		fprintf( dumpfile, "    DTDsep2 = " );
		PrintText( p, (BYTE)cdExt2Field.DTDsep2Len );
		p = ((char far *) p) + cdExt2Field.DTDsep2Len;
	}
	if( cdExt2Field.DTDsep3Len > 0 )
	{
		fprintf( dumpfile, "    DTDsep3 = " );
		PrintText( p, (BYTE)cdExt2Field.DTDsep3Len );
		p = ((char far *) p) + cdExt2Field.DTDsep3Len;
	}
	if( cdExt2Field.DTTsepLen > 0 )
	{
		fprintf( dumpfile, "    DTTsep = " );
		PrintText( p, (BYTE)cdExt2Field.DTTsepLen );
		p = ((char far *) p) + cdExt2Field.DTTsepLen;
	}
	if( cdExt2Field.wInputEnabledLen > 0 )
	{
		fprintf( dumpfile, "    wInputEnabled = " );
		PrintText( p, (BYTE)cdExt2Field.wInputEnabledLen );
		p = ((char far *) p) + cdExt2Field.wInputEnabledLen;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDActionBarExt

*************************************************************************/

void  LNPUBLIC   DumpCDActionBarExt (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDACTIONBAREXT	cdActionBarExt;
	WORD			wIndex;

	ODSReadMemory( &p, _CDACTIONBAREXT, &cdActionBarExt, 1 );
	fprintf( dumpfile, "  ACTIONBAREXT\n" );
	fprintf( dumpfile, "    BackColor\n" );
	DumpColorValue( cdActionBarExt.BackColor );
	fprintf( dumpfile, "    LineColor\n" );
	DumpColorValue( cdActionBarExt.LineColor );
	fprintf( dumpfile, "    FontColor\n" );
	DumpColorValue( cdActionBarExt.FontColor );
	fprintf( dumpfile, "    ButtonColor\n" );
	DumpColorValue( cdActionBarExt.ButtonColor );
	fprintf( dumpfile, "    BtnBorderDisplay = 0x%X", cdActionBarExt.BtnBorderDisplay );
	if (cdActionBarExt.BtnBorderDisplay == ACTION_SET_3D_ONMOUSEOVER)
 	    fprintf (dumpfile, " ONMOUSEOVER");
	if (cdActionBarExt.BtnBorderDisplay == ACTION_SET_3D_ALWAYS)
 	    fprintf (dumpfile, " ALWAYS");
	if (cdActionBarExt.BtnBorderDisplay == ACTION_SET_3D_NEVER)
 	    fprintf (dumpfile, " NEVER");
	if (cdActionBarExt.BtnBorderDisplay == ACTION_SET_3D_NOTES)
 	    fprintf (dumpfile, " NOTES");
    fprintf (dumpfile, "\n");
	fprintf( dumpfile, "    wAppletHeight = %u\n", cdActionBarExt.wAppletHeight );
	fprintf( dumpfile, "    wBarBackgroundRepeat = %x", cdActionBarExt.wBarBackgroundRepeat );
	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_REPEATONCE )	
		fprintf( dumpfile, " REPEATONCE" );
	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_REPEATVERT )	
		fprintf( dumpfile, " REPEATVERT" );
 	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_REPEATHORIZ )	
		fprintf( dumpfile, " REPEATHORIZ" );
 	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_TILE )
		fprintf( dumpfile, " TILE" );
 	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_CENTER_TILE )
		fprintf( dumpfile, " CENTER_TILE" );
 	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_REPEATSIZE )
		fprintf( dumpfile, " REPEATSIZE" );
 	if( cdActionBarExt.wBarBackgroundRepeat == ACTIONBAR_BACKGROUND_REPEATCENTER )
		fprintf( dumpfile, " REPEATCENTER" );
	fprintf( dumpfile, "    \n");
	fprintf( dumpfile, "    BtnWidthStyle = %x", cdActionBarExt.BtnWidthStyle );
	if( cdActionBarExt.BtnWidthStyle == ACTIONBAR_BUTTON_WIDTH_DEFAULT )
		fprintf( dumpfile, " DEFAULT" );
	if( cdActionBarExt.BtnWidthStyle == ACTIONBAR_BUTTON_WIDTH_BACKGROUND )
		fprintf( dumpfile, " BACKGROUND" );
	if( cdActionBarExt.BtnWidthStyle == ACTIONBAR_BUTTON_WIDTH_ABSOLUTE )
		fprintf( dumpfile, " ABSOLUTE (fixed)\n    wBtnWidthAbsolute = %d", cdActionBarExt.wBtnWidthAbsolute);
	fprintf( dumpfile, "    \n");
	fprintf( dumpfile, "    BtnTextJustify = %x", cdActionBarExt.BtnTextJustify );
	if( cdActionBarExt.BtnTextJustify == ACTIONBAR_BUTTON_TEXT_LEFT )
		fprintf( dumpfile, " LEFT" );
	if( cdActionBarExt.BtnTextJustify == ACTIONBAR_BUTTON_TEXT_CENTER )
		fprintf( dumpfile, " CENTER" );
	if( cdActionBarExt.BtnTextJustify == ACTIONBAR_BUTTON_TEXT_RIGHT )
		fprintf( dumpfile, " RIGHT" );
	fprintf( dumpfile, "    \n");
	fprintf( dumpfile, "    wBtnInternalMargin = %x\n", cdActionBarExt.wBtnInternalMargin );
	fprintf( dumpfile, "    dwFlags = %x", cdActionBarExt.dwFlags );
	if( cdActionBarExt.dwFlags  & ACTIONBAREXT_WIDTH_STYLE_VALID_FLAG)
		fprintf( dumpfile, " WIDTH_STYLE_VALID" );
	fprintf( dumpfile, "    \n");
	fprintf( dumpfile, "    barFontID = " );
	DumpFontIDFields( (FONTIDFIELDS *)&cdActionBarExt.barFontID );
  	fprintf( dumpfile, "    barHeight \n");
	DumpLengthValue( cdActionBarExt.barHeight);
	for( wIndex = 0; wIndex < 12; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdActionBarExt.Spare[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDImageSegment

*************************************************************************/

void  LNPUBLIC   DumpCDImageSegment (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDIMAGESEGMENT	cdImageSegment;

	ODSReadMemory( &p, _CDIMAGESEGMENT, &cdImageSegment, 1 );
	fprintf( dumpfile, "  IMAGESEGMENT\n" );
	fprintf( dumpfile, "    DataSize = %lu\n", cdImageSegment.DataSize );
	fprintf( dumpfile, "    SegSize = %lu\n", cdImageSegment.SegSize );
	fprintf( dumpfile, "\n  < Begin Image Data >" );
	NSFDDUMPDumpMemory( p, cdImageSegment.DataSize );
	fprintf( dumpfile, "  < End Image Data >\n" );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDImageHeader

*************************************************************************/

void  LNPUBLIC   DumpCDImageHeader (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDIMAGEHEADER	cdImageHeader;
	char *			pString;

	ODSReadMemory( &p, _CDIMAGEHEADER, &cdImageHeader, 1 );
	fprintf( dumpfile, "  IMAGEHEADER\n" );
	pString = GetLiteralString( NativeImageTable, cdImageHeader.ImageType );
	fprintf( dumpfile, "    ImageType (0x%X) = %s\n", cdImageHeader.ImageType, pString );
	fprintf( dumpfile, "    Width = %u\n", cdImageHeader.Width );
	fprintf( dumpfile, "    Height = %u\n", cdImageHeader.Height );
	fprintf( dumpfile, "    ImageDataSize = %lu\n", cdImageHeader.ImageDataSize );
	fprintf( dumpfile, "    SegCount = %lu\n", cdImageHeader.SegCount );
	fprintf( dumpfile, "    Flags = (0x%X)\n", cdImageHeader.Flags );
	fprintf( dumpfile, "    Reserved = (0x%X)\n", cdImageHeader.Reserved );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDBlobPart

*************************************************************************/

void  LNPUBLIC   DumpCDBlobPart (
	char *          RecordPtr,
	DWORD           RecordLength,
	WORD			RecordType
) {

	char far *	p = RecordPtr;
	CDBLOBPART	cdBlobPart;
	char *		pString;
	WORD		wIndex;

	if( SIG_CD_CLIENT_BLOBPART == RecordType)
		fprintf( dumpfile,"  CLIENT_BLOBPART\n");
	else /* SIG_CD_BLOBPART */
		fprintf( dumpfile,"  BLOBPART\n");

	ODSReadMemory( &p, _CDBLOBPART, &cdBlobPart, 1 );
	pString = GetLiteralString( SignatureTypeTable, cdBlobPart.OwnerSig );
	fprintf( dumpfile, "    OwnerSig = SIG_%s\n", pString );
	fprintf( dumpfile, "    Length = %u\n", cdBlobPart.Length );
	fprintf( dumpfile, "    BlobMax = %u\n", cdBlobPart.BlobMax );
	for( wIndex = 0; wIndex < 8; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdBlobPart.Reserved[wIndex] );
	fprintf( dumpfile, "  <Begin Java Script source>\n" );
	PrintText( p, (WORD) cdBlobPart.Length );
	fprintf( dumpfile, "  <End Java Script source>\n" );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDPlaceHolder

*************************************************************************/

void  LNPUBLIC   DumpCDPlaceHolder (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDPLACEHOLDER	cdPlaceHolder;
	WORD			wIndex;
	char *			szHotSpotType;
	DWORD			dwFlags;


	ODSReadMemory( &p, _CDPLACEHOLDER, &cdPlaceHolder, 1 );
	fprintf( dumpfile, "  PLACEHOLDER\n");
	
	for ( wIndex = 0; wIndex < NUM_HOTSPOT_TYPES; wIndex++ )
    {
		if(cdPlaceHolder.Type == HotSpotTypeTable[wIndex].wHotSpotType)
		{
			szHotSpotType = HotSpotTypeTable[wIndex].szTypeStr;
			break;
		}
    }
    if ( wIndex == NUM_HOTSPOT_TYPES )
    {
		szHotSpotType = "Unknown";
    }

	fprintf( dumpfile, "    Type (0x%X) = %s\n", cdPlaceHolder.Type, szHotSpotType );

	dwFlags = cdPlaceHolder.Flags;
	fprintf( dumpfile, "    Flags = 0x%X: ", dwFlags );
	if( dwFlags & PLACEHOLDER_FLAG_FITTOWINDOW )		fprintf( dumpfile, "FITTOWINDOW ");
	if( dwFlags & PLACEHOLDER_FLAG_DRAWBACKGROUND )		fprintf( dumpfile, "DRAWBACKGROUND " );
	if( dwFlags & PLACEHOLDER_FLAG_USEPERCENTAGE )		fprintf( dumpfile, "USEPERCENTAGE " );
	if( dwFlags & PLACEHOLDER_FLAG_SCROLLBARS )			fprintf( dumpfile, "SCROLLBARS " );
	if( dwFlags & PLACEHOLDER_FLAG_CONTENTSONLY )		fprintf( dumpfile, "CONTENTSONLY " );
	if( dwFlags & PLACEHOLDER_FLAG_ALIGNCENTER )		fprintf( dumpfile, "ALIGNCENTER " );
	if( dwFlags & PLACEHOLDER_FLAG_FITTOWINDOWHEIGHT )	fprintf( dumpfile, "FITTOWINDOWHEIGHT " );
	if( dwFlags & PLACEHOLDER_FLAG_TILEIMAGE )			fprintf( dumpfile, "TILEIMAGE " );
	if( dwFlags & PLACEHOLDER_FLAG_DISPLAYHORZ )		fprintf( dumpfile, "DISPLAYHORZ " );
	if( dwFlags & PLACEHOLDER_FLAG_DONTEXPANDSELECTIONS ) fprintf( dumpfile, "DONTEXPANDSELECTIONS " );
	if( dwFlags & PLACEHOLDER_FLAG_EXPANDCURRENT )		fprintf( dumpfile, "EXPANDCURRENT ");
	if( dwFlags & PLACEHOLDER_FLAG_FITCONTENTSWIDTH )	fprintf( dumpfile, "FITTOCONTENTSWIDTH " );
	if( dwFlags & PLACEHOLDER_FLAG_FIXEDWIDTH )			fprintf( dumpfile, "FIXEDWIDTH " );
	if( dwFlags & PLACEHOLDER_FLAG_FIXEDHEIGHT )		fprintf( dumpfile, "FIXEDHEIGHT " );
	if( dwFlags & PLACEHOLDER_FLAG_FITCONTENTS )		fprintf( dumpfile, "FITCONTENTS " );
	if( dwFlags & PLACEHOLDER_FLAG_PROP_WIDTH )			fprintf( dumpfile, "PROP_WIDTH " );
	if( dwFlags & PLACEHOLDER_FLAG_PROP_BOTH )			fprintf( dumpfile, "PROP_BOTH " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    Width = %u  Height = %u\n", cdPlaceHolder.Width, cdPlaceHolder.Height );
	fprintf( dumpfile, "    FontID = " );
	DumpFontIDFields( (FONTIDFIELDS *)&cdPlaceHolder.FontID );
	fprintf( dumpfile, "    Characters = %u\n", cdPlaceHolder.Characters );
	fprintf( dumpfile, "    SpaceBetween = %u\n", cdPlaceHolder.SpaceBetween );
	fprintf( dumpfile, "    TextAlignment = 0x%X: ", cdPlaceHolder.TextAlignment );
	if( cdPlaceHolder.TextAlignment == PLACEHOLDER_ALIGN_LEFT )		fprintf( dumpfile, "ALIGN_LEFT " );
	if( cdPlaceHolder.TextAlignment == PLACEHOLDER_ALIGN_CENTER )	fprintf( dumpfile, "ALIGN_CENTER " );
	if( cdPlaceHolder.TextAlignment == PLACEHOLDER_ALIGN_RIGHT )	fprintf( dumpfile, "ALIGN_RIGHT" );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    SpaceWord = %u\n", cdPlaceHolder.SpaceWord );
	fprintf( dumpfile, "    SubFontID[0] = " );
	DumpFontIDFields( (FONTIDFIELDS *)&cdPlaceHolder.SubFontID[0] );
	fprintf( dumpfile, "    SubFontID[1] = " );
	DumpFontIDFields( (FONTIDFIELDS *)&cdPlaceHolder.SubFontID[1] );
	fprintf( dumpfile, "    DataLength = %lu\n", cdPlaceHolder.DataLength );
	fprintf( dumpfile, "    BackgroundColor\n" );
	DumpColorValue( cdPlaceHolder.BackgroundColor );
	fprintf( dumpfile, "    ColorRGB\n" );
	DumpColorValue( cdPlaceHolder.ColorRGB );
	fprintf( dumpfile, "    SpareWord = (0x%X)\n", cdPlaceHolder.SpareWord);
	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdPlaceHolder.Spare[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDLinkColors

*************************************************************************/

void  LNPUBLIC   DumpCDLinkColors (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *		p = RecordPtr;
	CDLINKCOLORS	cdLinkColors;
	WORD			wIndex;

	ODSReadMemory( &p, _CDLINKCOLORS, &cdLinkColors, 1 );
	fprintf( dumpfile, "  LINKCOLORS\n");
	fprintf( dumpfile, "    dwFlags = 0x%X\n" );
	fprintf( dumpfile, "    unvisitedColor\n" );
	DumpColorValue( cdLinkColors.unvisitedColor );
	fprintf( dumpfile, "    activeColor\n" );
	DumpColorValue( cdLinkColors.activeColor );
	fprintf( dumpfile, "    visitedColor\n" );
	DumpColorValue ( cdLinkColors.visitedColor );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdLinkColors.dwSpares[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDCaption

*************************************************************************/

void  LNPUBLIC   DumpCDCaption (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDCAPTION	cdCaption;
	DWORD		dwLen;
	WORD		wIndex;

	ODSReadMemory( &p, _CDCAPTION, &cdCaption, 1);
	fprintf( dumpfile, "  CAPTION\n");
	fprintf( dumpfile, "    wLength = %d\n", cdCaption.wLength );
	fprintf( dumpfile, "    Position = 0x%X: ", cdCaption.Position );
	if( cdCaption.Position == CAPTION_POSITION_BELOW_CENTER )
		fprintf( dumpfile, "POSITION_BELOW_CENTER ");
	if( cdCaption.Position == CAPTION_POSITION_MIDDLE_CENTER )
		fprintf( dumpfile, "POSITION_MIDDLE_CENTER" );
	fprintf(dumpfile, "\n");
	fprintf( dumpfile, "    FontID = ");
	DumpFontIDFields( (FONTIDFIELDS *)&cdCaption.FontID );
	fprintf( dumpfile, "    FontColor\n" );
	DumpColorValue(cdCaption.FontColor);
	for( wIndex = 0; wIndex < 11; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdCaption.Reserved[wIndex] );
	
	dwLen = RecordLength - (DWORD)ODSLength(_CDCAPTION);
	if( dwLen > 0 )
	{
		fprintf( dumpfile, "    Caption Text Data = ");
		PrintText( p, dwLen );
	}
	return;
}

/************************************************************************

    FUNCTION:   DumpCDFrame

*************************************************************************/

void  LNPUBLIC   DumpCDFrame (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDFRAME		cdFrame;

	ODSReadMemory( &p, _CDFRAME, &cdFrame, 1 );
	fprintf( dumpfile, "  FRAME\n" );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdFrame.Flags );
	if( cdFrame.Flags & fFRBorderEnable )	fprintf( dumpfile, "BorderEnable ");
	if( cdFrame.Flags & fFRMarginWidth )	fprintf( dumpfile, "MarginWidth " );
	if( cdFrame.Flags & fFRMarginHeight )	fprintf( dumpfile, "MarginHeight " );
	if( cdFrame.Flags & fFRFrameBorderColor ) fprintf( dumpfile, "FrameBorderColor " );
	if( cdFrame.Flags & fFRScrolling )		fprintf( dumpfile, "Scrolling " );
	if( cdFrame.Flags & fFRNotesOnlyBorder )		fprintf( dumpfile, "NotesOnlyBorder " );
	if( cdFrame.Flags & fFRNotesOnlyArrows  )		fprintf( dumpfile, "NotesOnlyArrows  " );
	if( cdFrame.Flags & fFRNotesOpenPercent )		fprintf( dumpfile, "NotesOpenPercent " );
	if( cdFrame.Flags & fFRNotesInitialFocus )		fprintf( dumpfile, "NotesInitialFocus " );
	if( cdFrame.Flags & fFRNotesReadingOrder )		fprintf( dumpfile, "NotesReadingOrder " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    DataFlags = 0x%X ", cdFrame.DataFlags );
	if( cdFrame.DataFlags & fFRNotesBorder )	fprintf( dumpfile, "NotesBorder ");
	if( cdFrame.DataFlags & fFRNotesBorderFontAndColor )	fprintf( dumpfile, "NotesBorderFontAndColor ");
	if( cdFrame.DataFlags & fFRNotesBorderCaption )	fprintf( dumpfile, "NotesBorderCaption ");
	if( cdFrame.DataFlags & fFRNotesCaptionFontName )	fprintf( dumpfile, "NotesCaptionFontName ");
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    FRAMEBORDER attribute, BorderEnable = 0x%X\n", cdFrame.BorderEnable );
	fprintf( dumpfile, "    NORESIZE attribute, NoResize = 0x%X\n", cdFrame.NoResize );
	fprintf( dumpfile, "    ScrollBarStyle = %s\n", GetLiteralString( ScrollStyle, cdFrame.ScrollBarStyle ) );
	fprintf( dumpfile, "    MarginWidth = %d\n", cdFrame.MarginWidth );
	fprintf( dumpfile, "    MarginHeight = %d\n", cdFrame.MarginHeight );
	fprintf( dumpfile, "    dwReserved = (0x%X)\n", cdFrame.dwReserved );
	fprintf( dumpfile, "    FrameNamelength = %d\n", cdFrame.FrameNameLength );
	fprintf( dumpfile, "    Reserved1 = (0x%X)\n", cdFrame.Reserved1 );
	fprintf( dumpfile, "    FrameBorderColor\n" );
	DumpColorValue( cdFrame.FrameBorderColor );
	fprintf( dumpfile, "    wReserved = (0x%X)\n", cdFrame.wReserved );

	if( cdFrame.FrameNameLength > 0 )
	{
		fprintf( dumpfile, "    Frame Name String = " );
		PrintText(( char far *)p, (WORD)cdFrame.FrameNameLength );
		p = ((char far *) p) + cdFrame.FrameNameLength;
	}
	if( cdFrame.FrameTargetLength > 0 )
	{
		fprintf( dumpfile, "    Target Frame Name = " );
		PrintText(( char far *)p, (WORD)cdFrame.FrameTargetLength );
		p = ((char far *) p) + cdFrame.FrameTargetLength;
	}
return;
}

/************************************************************************

    FUNCTION:   DumpCDFrameSet

*************************************************************************/

void  LNPUBLIC   DumpCDFrameSet (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDFRAMESET	cdFrameSet;
	WORD		index;
	char *		LengthType;

	ODSReadMemory( &p, _CDFRAMESET, &cdFrameSet, 1 );
	fprintf( dumpfile, "  FRAMESET\n" );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdFrameSet.Flags );
	if( cdFrameSet.Flags & fFSBorderEnable )		fprintf( dumpfile, "BorderEnable " );
	if( cdFrameSet.Flags & fFSFrameBorderDims )		fprintf( dumpfile, "FrameBorderDims " );
	if( cdFrameSet.Flags & fFSFrameSpacingDims )	fprintf( dumpfile, "FrameSpacingDims " );
	if( cdFrameSet.Flags & fFSFrameBorderColor )	fprintf( dumpfile, "FrameBorderColor " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    BorderEnable = 0x%X\n", cdFrameSet.BorderEnable );
	fprintf( dumpfile, "    byAvail1 = (0x%X)\n", cdFrameSet.byAvail1 );
	fprintf( dumpfile, "    Reserved1 = (0x%X)\n", cdFrameSet.Reserved1 );
	fprintf( dumpfile, "    Reserved2 = (0x%X)\n", cdFrameSet.Reserved2 );
	fprintf( dumpfile, "    FrameBorderWidth = %d\n", cdFrameSet.FrameBorderWidth );
	fprintf( dumpfile, "    Reserved3 = (0x%X)\n", cdFrameSet.Reserved3 );
	fprintf( dumpfile, "    FrameSpacingWidth = %d\n", cdFrameSet.FrameSpacingWidth );
	fprintf( dumpfile, "    Reserved4 = (0x%X)\n", cdFrameSet.Reserved4 );
	fprintf( dumpfile, "    ReservedColor1\n" );
	DumpColorValue( cdFrameSet.ReservedColor1 );
	fprintf( dumpfile, "    ReservedColor2\n" );
	DumpColorValue( cdFrameSet.ReservedColor2 );
	fprintf( dumpfile, "    RowQty = %d\n", cdFrameSet.RowQty );
	fprintf( dumpfile, "    ColQty = %d\n", cdFrameSet.ColQty );
	fprintf( dumpfile, "    Reserved5 = (0x%X)\n", cdFrameSet.Reserved5 );
	fprintf( dumpfile, "    Reserved6 = (0x%X)\n", cdFrameSet.Reserved6 );
	fprintf( dumpfile, "    FrameBorderColor\n" );
	DumpColorValue( cdFrameSet.FrameBorderColor );
	fprintf( dumpfile, "    Reserved7[0] = (0x%X)\n", cdFrameSet.Reserved7[0] );
	fprintf( dumpfile, "    Reserved7[1] = (0x%X)\n", cdFrameSet.Reserved7[1] );
	
	if( cdFrameSet.RowQty )
	{
		FRAMESETLENGTH	FrameSetLength;
		fprintf( dumpfile, "    RowQty Information\n" );
		for( index = 0; index < cdFrameSet.RowQty; index++ )
		{
			ODSReadMemory( &p, _FRAMESETLENGTH, &FrameSetLength, 1 );
			LengthType = GetLiteralString( FrameSetLengthType, FrameSetLength.Type );
			fprintf( dumpfile, "    Type = %d, %s\n", FrameSetLength.Type, LengthType );
			fprintf( dumpfile, "	Value = %d\n", FrameSetLength.Value );
		}
	}
	if( cdFrameSet.ColQty )
	{
		FRAMESETLENGTH	FrameSetLength;
		fprintf( dumpfile, "    ColQty Information\n" );
		for( index = 0; index < cdFrameSet.ColQty; index++ )
		{
			ODSReadMemory( &p, _FRAMESETLENGTH, &FrameSetLength, 1 );
			LengthType = GetLiteralString( FrameSetLengthType, FrameSetLength.Type );
			fprintf( dumpfile, "    Type = %d, %s\n", FrameSetLength.Type, LengthType );
			fprintf( dumpfile, "	Value = %d\n", FrameSetLength.Value );
		}
	}
	return;

}

/************************************************************************

    FUNCTION:   DumpCDFrameSetHeader

*************************************************************************/

void  LNPUBLIC   DumpCDFrameSetHeader (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDFRAMESETHEADER	cdFrameSetHeader;
	WORD				wIndex;

	ODSReadMemory( &p, _CDFRAMESETHEADER, &cdFrameSetHeader, 1 );
	fprintf( dumpfile, "  FRAMESETHEADER\n" );
	fprintf( dumpfile, "    Version = (0x%X)\n", cdFrameSetHeader.Version );
	fprintf( dumpfile, "    RecCount = %d\n", cdFrameSetHeader.RecCount );
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdFrameSetHeader.Reserved[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDActionExt

*************************************************************************/

void    LNPUBLIC  DumpCDActionExt( char * RecordPtr, DWORD RecordLength )
{
    char far *          p = RecordPtr;

    CDACTIONEXT            cdActionExt;
	WORD				   wIndex;

    fprintf (dumpfile, "  ACTIONEXT\n");

    ODSReadMemory (&p, _CDACTIONEXT, &cdActionExt, 1);

    fprintf (dumpfile, "    Flags = 0x%lX: \n",  cdActionExt.dwFlags);

    fprintf (dumpfile, "    Control Type = 0x%lX: ",  cdActionExt.wControlType);
    if (cdActionExt.wControlType & ACTION_CONTROL_TYPE_BUTTON)
		fprintf (dumpfile, "CONTROL_TYPE_BUTTON " );
    if (cdActionExt.wControlType & ACTION_CONTROL_TYPE_CHECKBOX)
		fprintf (dumpfile, "CONTROL_TYPE_CHECKBOX " );
    if (cdActionExt.wControlType & ACTION_CONTROL_TYPE_MENU_SEPARATOR)
		fprintf (dumpfile, "ACTION_CONTROL_TYPE_MENU_SEPARATOR " );
	fprintf (dumpfile, "\n" );

	fprintf (dumpfile, "    wControlFormulaLen		= %hu\n", cdActionExt.wControlFormulaLen);
	fprintf (dumpfile, "    wLabelFormulaLen		= %hu\n", cdActionExt.wLabelFormulaLen);
	fprintf (dumpfile, "    wParentLabelFormulaLen	= %hu\n", cdActionExt.wParentLabelFormulaLen);

	for( wIndex = 0; wIndex < 3; wIndex++ )
		fprintf( dumpfile, "    dwExtra[%d] = (0x%X)\n", wIndex, cdActionExt.dwExtra[wIndex] );

	if( cdActionExt.wControlFormulaLen > 0 )					/* variable data */
	{
		fprintf( dumpfile, "    Control Formula = " );
		PrintFormula ( p, cdActionExt.wControlFormulaLen );	
		p = ((char far *) p) + cdActionExt.wControlFormulaLen;

	}	

	if( cdActionExt.wLabelFormulaLen > 0 )						/* variable data */
	{
		fprintf( dumpfile, "    Label Formula = " );
		PrintFormula ( p, cdActionExt.wLabelFormulaLen );	
		p = ((char far *) p) + cdActionExt.wLabelFormulaLen;
	}	

	if( cdActionExt.wParentLabelFormulaLen > 0 )                /* variable data */
	{
		fprintf( dumpfile, "    Parent Label Formula = " );
		PrintFormula ( p, cdActionExt.wParentLabelFormulaLen );
		p = ((char far *) p) + cdActionExt.wParentLabelFormulaLen;
	}	

    return;
}



/************************************************************************

    FUNCTION:   DumpCDEmbeddedSchedCtlExtra

*************************************************************************/

void  LNPUBLIC   DumpCDEmbeddedSchedCtlExtra (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDEMBEDDEDSCHEDCTLEXTRA	cdEmbeddedSchedCtlExtra;
	WORD				wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDSCHEDCTLEXTRA, &cdEmbeddedSchedCtlExtra, 1 );
	fprintf( dumpfile, "  EMBEDDEDSCHEDCTLEXTRA\n" );
	fprintf( dumpfile, "    FixedPartLength = %d bytes\n", cdEmbeddedSchedCtlExtra.FixedPartLength );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdEmbeddedSchedCtlExtra.Flags );
	if( cdEmbeddedSchedCtlExtra.Flags & EMBEDDEDSCHEDEXT_FLAG_PEOPLE_TITLE_FORMULA )
		fprintf( dumpfile, "PEOPLE_TITLE_FORMULA " );
	if( cdEmbeddedSchedCtlExtra.Flags & EMBEDDEDSCHEDEXT_FLAG_ROOMS_TITLE_FORMULA )
		fprintf( dumpfile, "ROOMS_TITLE_FORMULA " );
	if( cdEmbeddedSchedCtlExtra.Flags & EMBEDDEDSCHEDEXT_FLAG_RESOURCES_TITLE_FORMULA )
		fprintf( dumpfile, "RESOURCES_TITLE_FORMULA " );
	if( cdEmbeddedSchedCtlExtra.Flags & EMBEDDEDSCHEDEXT_FLAG_SUGG_COLORS_DEFINED )
		fprintf( dumpfile, "SUGG_COLORS_DEFINED " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    SchedHdrBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.SchedHdrBkgndColor );
	fprintf( dumpfile, "    SchedHdrFontColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.SchedHdrFontColor );
	fprintf( dumpfile, "    SchedBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.SchedBkgndColor );
	fprintf( dumpfile, "    NameHdrBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameHdrBkgndColor );
	fprintf( dumpfile, "    NameHdrFontColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameHdrFontColor );
	fprintf( dumpfile, "    NameBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameBkgndColor );
	fprintf( dumpfile, "    NameMouseBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameMouseBkgndColor );
	fprintf( dumpfile, "    NameSelectBkgndColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameSelectBkgndColor );
	fprintf( dumpfile, "    NameFontColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameFontColor );
	fprintf( dumpfile, "    NameMouseFontColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameMouseFontColor );
	fprintf( dumpfile, "    NameSelectFontColor\n" );
		DumpColorValue( cdEmbeddedSchedCtlExtra.NameSelectFontColor );
 	fprintf( dumpfile, "    OptPeopleItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    OptPeopleItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptPeopleItemsFormulaLength;
	}
	fprintf( dumpfile, "    ReqRoomsItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    ReqRoomsItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ReqRoomsItemsFormulaLength;
	}
	fprintf( dumpfile, "    OptRoomsItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    OptRoomsItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptRoomsItemsFormulaLength;
	}
	fprintf( dumpfile, "    ReqResourcesItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    ReqResourcesItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ReqResourcesItemsFormulaLength;
	}
	fprintf( dumpfile, "    OptResourcesItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    OptResourcesItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.OptResourcesItemsFormulaLength;
	}
	fprintf( dumpfile, "    IntervalStartDTItemFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength );
	if( cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength > 0 )
	{
		fprintf( dumpfile, "    IntervalStartDTItemFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalStartDTItemFormulaLength;
	}
	fprintf( dumpfile, "    IntervalEndDTItemFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength );
	if( cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength > 0 )
	{
		fprintf( dumpfile, "    IntervalEndDTItemFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalEndDTItemFormulaLength;
	}
	fprintf( dumpfile, "    SchedulerNameLength = %d\n", cdEmbeddedSchedCtlExtra.SchedulerNameLength );
	if( cdEmbeddedSchedCtlExtra.SchedulerNameLength > 0 )
	{
		fprintf( dumpfile, "    SchedulerName = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.SchedulerNameLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.SchedulerNameLength;
	}
	fprintf( dumpfile, "    PeopleTitleLength = %d\n", cdEmbeddedSchedCtlExtra.PeopleTitleLength );
	if( cdEmbeddedSchedCtlExtra.PeopleTitleLength > 0 )
	{
		fprintf( dumpfile, "    PeopleTitle = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.PeopleTitleLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.PeopleTitleLength;
	}
	fprintf( dumpfile, "    RoomsTitleLength = %d\n", cdEmbeddedSchedCtlExtra.RoomsTitleLength );
	if( cdEmbeddedSchedCtlExtra.RoomsTitleLength > 0 )
	{
		fprintf( dumpfile, "    RoomsTitle = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.RoomsTitleLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.RoomsTitleLength;
	}
	fprintf( dumpfile, "    ResourcesTitleLength = %d\n", cdEmbeddedSchedCtlExtra.ResourcesTitleLength );
	if( cdEmbeddedSchedCtlExtra.ResourcesTitleLength > 0 )
	{
		fprintf( dumpfile, "    ResourcesTitle = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.ResourcesTitleLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.ResourcesTitleLength;
	}
	fprintf( dumpfile, "    IntervalChangeEventFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength );
	if( cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength > 0 )
	{
		fprintf( dumpfile, "    IntervalChangeEventFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.IntervalChangeEventFormulaLength;
	}
	fprintf( dumpfile, "    ProfileColor\n" );
	DumpColorValue( cdEmbeddedSchedCtlExtra.ProfileColor );
	fprintf( dumpfile, "    SchedDetailItemsFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength );
	if( cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength > 0 )
	{
		fprintf( dumpfile, "    SchedDetailItemsFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.SchedDetailItemsFormulaLength;
	}
	fprintf( dumpfile, "    DetailDisplayFormFormulaLength = %d\n", cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength );
	if( cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength > 0 )
	{
		fprintf( dumpfile, "    DetailDisplayFormFormula = " );
		PrintText((char far *)p, (WORD)cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength );
		p = ((char far *) p) + cdEmbeddedSchedCtlExtra.DetailDisplayFormFormulaLength;
	}
	fprintf( dumpfile, "    SuggBkgndColor\n" );
	DumpColorValue( cdEmbeddedSchedCtlExtra.SuggBkgndColor );
	fprintf( dumpfile, "    SuggMouseBkgndColor\n" );
	DumpColorValue( cdEmbeddedSchedCtlExtra.SuggMouseBkgndColor );
	fprintf( dumpfile, "    SuggSelectBkgndColor\n" );
	DumpColorValue( cdEmbeddedSchedCtlExtra.SuggSelectBkgndColor );
	for( wIndex = 0; wIndex < 1; wIndex++ )
		fprintf( dumpfile, "    wReserved[%d] = (0x%X)\n", wIndex, cdEmbeddedSchedCtlExtra.wReserved[wIndex] );
	for( wIndex = 0; wIndex < 7; wIndex++ )
		fprintf( dumpfile, "    dwReserved[%d] = (0x%X)\n", wIndex, cdEmbeddedSchedCtlExtra.dwReserved[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDInline

*************************************************************************/

void  LNPUBLIC   DumpCDInline (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDINLINE		cdInline;
	WORD		wIndex;

	ODSReadMemory( &p, _CDINLINE, &cdInline, 1 );
	fprintf( dumpfile, "  INLINE\n" );
	
	fprintf( dumpfile, "    wDatalength = %u\n", cdInline.wDatalength );
	fprintf( dumpfile, "    dwFlags = 0x%X: ", cdInline.dwFlags );
		if( cdInline.dwFlags & INLINE_FLAG_UNKNOWN ) fprintf( dumpfile, " UNKNOWN " );
		if( cdInline.dwFlags & INLINE_FLAG_SCRIPT_LIB ) fprintf( dumpfile, " SCRIPT_LIB " );
		if( cdInline.dwFlags & INLINE_FLAG_STYLE_SHEET ) fprintf( dumpfile, " STYLE_SHEET " );
		if( cdInline.dwFlags & INLINE_FLAG_HTML ) fprintf( dumpfile, " HTML " );
		if( cdInline.dwFlags & INLINE_FLAG_TYPES_MASK ) fprintf( dumpfile, " TYPES_MASK " );
		if( cdInline.dwFlags & INLINE_FLAG_HTMLFILERES ) fprintf( dumpfile, " HTMLFILERES " );
	fprintf( dumpfile, "\n");

	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    dwReserved[%d] = (0x%X)\n", wIndex, cdInline.dwReserved[wIndex] );
		
	return;
}


/************************************************************************

    FUNCTION:   DumpCDEmbeddedCalCtl

*************************************************************************/

void  LNPUBLIC   DumpCDEmbeddedCalCtl (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	        p = RecordPtr;
	CDEMBEDDEDCALCTL	cdEmbeddedCalCtl;
	WORD		        wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDCALCTL, &cdEmbeddedCalCtl, 1 );
	fprintf( dumpfile, "  EMBEDDEDCALCTL\n" );
	
	fprintf( dumpfile, "    Flags = 0x%X: ", cdEmbeddedCalCtl.Flags );
  	   if( cdEmbeddedCalCtl.Flags & EMBEDDEDCAL_FLAG_NON_TRANSPARENT_BKGND )
		   fprintf( dumpfile, " NON_TRANSPARENT_BKGND " );
  	   if( cdEmbeddedCalCtl.Flags & EMBEDDEDCAL_FLAG_HASTARGETFRAME )
		   fprintf( dumpfile, " HASTARGETFRAME " );
	fprintf( dumpfile, "\n");

	fprintf( dumpfile, "    HeaderBkgnd\n" );
	DumpColorValue( cdEmbeddedCalCtl.HeaderBkgnd );

	fprintf( dumpfile, "    SelectionColor\n" );
	DumpColorValue( cdEmbeddedCalCtl.SelectionColor );

	fprintf( dumpfile, "    TargetFrameLength = %u\n", cdEmbeddedCalCtl.TargetFrameLength );

	for( wIndex = 0; wIndex < 10; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdEmbeddedCalCtl.Spare[wIndex] );
	
	if( cdEmbeddedCalCtl.TargetFrameLength > 0 )
	{
		fprintf( dumpfile, "    TargetFrame = " );
		PrintText((char far *)p, (WORD)cdEmbeddedCalCtl.TargetFrameLength );
		p = ((char far *) p) + cdEmbeddedCalCtl.TargetFrameLength;
	}

	return;
}


/************************************************************************

    FUNCTION:   DumpCDPositioning

*************************************************************************/

void  LNPUBLIC   DumpCDPositioning (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDPOSITIONING		cdPositioning;

	ODSReadMemory( &p, _CDPOSITIONING, &cdPositioning, 1 );
	fprintf( dumpfile, "  POSITIONING\n" );
	fprintf( dumpfile, "    Scheme = %u", cdPositioning.Scheme );
  	if( CDPOSITIONING_SCHEME_STATIC == cdPositioning.Scheme)
			fprintf( dumpfile, "     SCHEME_STATIC" );
  	if( CDPOSITIONING_SCHEME_ABSOLUTE == cdPositioning.Scheme)
			fprintf( dumpfile, "     SCHEME_ABSOLUTE" );
  	if( CDPOSITIONING_SCHEME_RELATIVE == cdPositioning.Scheme)
			fprintf( dumpfile, "     SCHEME_RELATIVE" );
  	if( CDPOSITIONING_SCHEME_FIXED == cdPositioning.Scheme)
			fprintf( dumpfile, "     SCHEME_FIXED" );
	fprintf( dumpfile, "\n");
	fprintf( dumpfile, "    Reserved = %u\n", cdPositioning.bReserved );
	fprintf( dumpfile, "    ZIndex = %u\n", cdPositioning.ZIndex );
  	fprintf( dumpfile, "    *** Top *** \n");
	DumpLengthValue( cdPositioning.Top);
  	fprintf( dumpfile, "    *** Left *** \n");
	DumpLengthValue( cdPositioning.Left);
  	fprintf( dumpfile, "    *** Bottom *** \n");
	DumpLengthValue( cdPositioning.Bottom);
  	fprintf( dumpfile, "    *** Right *** \n");
	DumpLengthValue( cdPositioning.Right);
	fprintf( dumpfile, "    BrowserLeftOffset = %X\n", cdPositioning.BrowserLeftOffset );
	fprintf( dumpfile, "    BrowserRightOffset = %X\n", cdPositioning.BrowserRightOffset );
	
	return;
}


/************************************************************************

    FUNCTION:   DumpCDLayer

*************************************************************************/

void  LNPUBLIC   DumpCDLayer (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDLAYER				cdLayer;
	WORD				wIndex;

	ODSReadMemory( &p, _CDLAYER, &cdLayer, 1 );
	fprintf( dumpfile, "  LAYER\n" );

	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdLayer.Reserved[wIndex] );

	return;
}


/************************************************************************

    FUNCTION:   DumpCDBoxSize

*************************************************************************/

void  LNPUBLIC   DumpCDBoxSize (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *			p = RecordPtr;
	CDBOXSIZE			cdBoxSize;
	WORD				wIndex;

	ODSReadMemory( &p, _CDBOXSIZE, &cdBoxSize, 1 );
	fprintf( dumpfile, "  BOXSIZE\n" );

  	fprintf( dumpfile, "    *** Width *** \n");
	DumpLengthValue( cdBoxSize.Width);
  	fprintf( dumpfile, "    *** Height *** \n");
	DumpLengthValue( cdBoxSize.Height);
	for( wIndex = 0; wIndex < 4; wIndex++ )
	{
		fprintf( dumpfile, "    *** Reserved[%d] *** \n", wIndex);
		DumpLengthValue( cdBoxSize.Reserved[wIndex]);
	}
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    dwReserved[%d] = (0x%X)\n", wIndex, cdBoxSize.dwReserved[wIndex] );

	return;
}


/************************************************************************

    FUNCTION:   DumpCDBackgroundProperties

*************************************************************************/

void  LNPUBLIC   DumpCDBackgroundProperties (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDBACKGROUNDPROPERTIES		cdBackgroundProperties;
	char *					pString;
	WORD		wIndex;

	ODSReadMemory( &p, _CDBACKGROUNDPROPERTIES, &cdBackgroundProperties, 1 );
	fprintf( dumpfile, "  BACKGROUNDPROPERTIES\n" );
	pString = GetLiteralString( RepeatValueTable, cdBackgroundProperties.Repeat );
	fprintf( dumpfile, "    Repeat (0x%X) = %s\n", cdBackgroundProperties.Repeat, pString );

	fprintf( dumpfile, "    Reserved = %u\n", cdBackgroundProperties.bReserved );
	
	fprintf( dumpfile, "    *** lvReservedX  *** \n");
	DumpLengthValue( cdBackgroundProperties.lvReservedX);
	fprintf( dumpfile, "    *** lvReservedY  *** \n");
	DumpLengthValue( cdBackgroundProperties.lvReservedY);
	for( wIndex = 0; wIndex < 4; wIndex++ )
		fprintf( dumpfile, "    Reserved[%d] = (0x%X)\n", wIndex, cdBackgroundProperties.dwReserved[wIndex] );

	return;
}


/************************************************************************

    FUNCTION:   DumpCDEventEntry

*************************************************************************/

void  LNPUBLIC   DumpCDEventEntry (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	        p = RecordPtr;
	CDEVENTENTRY		cdEventEntry;

	ODSReadMemory( &p, _CDEVENTENTRY, &cdEventEntry, 1 );
	fprintf( dumpfile, "  EVENTENTRY\n" );
	
	fprintf( dumpfile, "    Platform = 0x%X: ", cdEventEntry.wPlatform );
  	   if( cdEventEntry.wPlatform & PLATFORM_TYPE_CLIENT_ODS )
		   fprintf( dumpfile, " TYPE_CLIENT_ODS " );
   	   if( cdEventEntry.wPlatform & PLATFORM_TYPE_WEB_ODS )
		   fprintf( dumpfile, " TYPE_WEB_ODS " );
	fprintf( dumpfile, "\n");
	fprintf( dumpfile, "    EventId = 0x%X\n ", cdEventEntry.wEventId );
	fprintf( dumpfile, "    ActionType = 0x%X\n ", cdEventEntry.wActionType );
	fprintf( dumpfile, "    Reserved = 0x%X\n ", cdEventEntry.wReserved );
	fprintf( dumpfile, "    Reserved = 0x%X\n ", cdEventEntry.dwReserved );
	
	return;
}


/************************************************************************

    FUNCTION:   DumpCDFileHeader

*************************************************************************/

void  LNPUBLIC   DumpCDFileHeader (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDFILEHEADER	cdFileHeader;

	ODSReadMemory( &p, _CDFILEHEADER, &cdFileHeader, 1 );
	fprintf( dumpfile, "  FILEHEADER\n" );
	
	fprintf( dumpfile, "    FileExtLen = %X\n", cdFileHeader.FileExtLen );
	fprintf( dumpfile, "    FileDataSize = %X\n", cdFileHeader.FileDataSize );
	fprintf( dumpfile, "    SegCount = %X\n", cdFileHeader.SegCount );
	fprintf( dumpfile, "    Flags = %X\n", cdFileHeader.Flags );
	fprintf( dumpfile, "    Reserved = %X\n", cdFileHeader.Reserved );

	if( cdFileHeader.FileExtLen > 0 )
	{
		fprintf( dumpfile, "    FileExt = " );
		PrintText((char far *)p, (WORD)cdFileHeader.FileExtLen );
		p = ((char far *) p) + cdFileHeader.FileExtLen;
	}

	return;
}


/************************************************************************

    FUNCTION:   DumpCDFileSegment

*************************************************************************/

void  LNPUBLIC   DumpCDFileSegment (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDFILESEGMENT	cdFileSegment;

	ODSReadMemory( &p, _CDFILESEGMENT, &cdFileSegment, 1 );
	fprintf( dumpfile, "  FILESEGMENT\n" );
	
	fprintf( dumpfile, "    DataSize = %X\n", cdFileSegment.DataSize );
	fprintf( dumpfile, "    SegSize = %X\n", cdFileSegment.SegSize );
	fprintf( dumpfile, "    Flags = %X\n", cdFileSegment.Flags );
	fprintf( dumpfile, "    Reserved = %X\n", cdFileSegment.Reserved );

	return;
}

/************************************************************************

    FUNCTION:   DumpCDDECSField

*************************************************************************/

void  LNPUBLIC   DumpCDDECSField (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDDECSFIELD		cdDECSField;
	WORD			wIndex;

	ODSReadMemory( &p, _CDDECSFIELD, &cdDECSField, 1 );
	fprintf( dumpfile, "  DECSFIELD\n" );
	
	fprintf( dumpfile, "    Flags = %X\n", cdDECSField.Flags );
	fprintf( dumpfile, "    ExternalNameLength = %X\n", cdDECSField.ExternalNameLength ); 	
	fprintf( dumpfile, "    MetadataNameLength = %X\n", cdDECSField.MetadataNameLength );
	fprintf( dumpfile, "    DCRNameLength = %X\n", cdDECSField.DCRNameLength );

	for( wIndex = 0; wIndex < 8; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdDECSField.Spare[wIndex] );

	if( cdDECSField.ExternalNameLength > 0 )
	{
		fprintf( dumpfile, "    ExternalName = " );
		PrintText((char far *)p, (WORD)cdDECSField.ExternalNameLength );
		p = ((char far *) p) + cdDECSField.ExternalNameLength;
	}

	if( cdDECSField.MetadataNameLength > 0 )
	{
		fprintf( dumpfile, "    MetadataName = " );
		PrintText((char far *)p, (WORD)cdDECSField.MetadataNameLength );
		p = ((char far *) p) + cdDECSField.MetadataNameLength;
	}

	if( cdDECSField.DCRNameLength > 0 )
	{
		fprintf( dumpfile, "    DCRName = " );
		PrintText((char far *)p, (WORD)cdDECSField.DCRNameLength );
		p = ((char far *) p) + cdDECSField.DCRNameLength;
	}

	return;
}

/************************************************************************

    FUNCTION:   DumpCDTextPropertiesTable

*************************************************************************/

void  LNPUBLIC   DumpCDTextPropertiesTable (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDTEXTPROPERTIESTABLE	cdTextPropertiesTable;

	ODSReadMemory( &p, _CDTEXTPROPERTIESTABLE, &cdTextPropertiesTable, 1 );
	fprintf( dumpfile, "  TEXTPROPERTIESTABLE\n" );

	fprintf( dumpfile, "    NumberOfEntries = %d\n", cdTextPropertiesTable.NumberOfEntries );
	
	return;
}

/************************************************************************

    FUNCTION:   DumpCDSpanRecord

*************************************************************************/

void  LNPUBLIC   DumpCDSpanRecord (
	char *       RecordPtr,
	DWORD        RecordLength,
	WORD		 RecordType
) {

	char far *			p = RecordPtr;
	CDSPANRECORD		cdSpanRecord;


	if (SIG_CD_SPAN_BEGIN == RecordType)
		fprintf( dumpfile, "  SPANRECORD - Begin\n" );
	else if (SIG_CD_SPAN_END == RecordType)
		fprintf( dumpfile, "  SPANRECORD - End\n" );
	else
	{
		fprintf( dumpfile, "  Unknown span type: %u (0x%X)\n",
			RecordType, RecordType );
		return;
	}

	ODSReadMemory( &p, _CDSPANRECORD, &cdSpanRecord, 1 );


	fprintf( dumpfile, "   PropID = %d \n", cdSpanRecord.PropID );

	return;
}

/************************************************************************

    FUNCTION:   DumpCDEmbeddedEditCtl

*************************************************************************/

void  LNPUBLIC   DumpCDEmbeddedEditCtl (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *			p = RecordPtr;
	CDEMBEDDEDEDITCTL		cdEmbeddedEditCtl;
	WORD				wIndex;

	ODSReadMemory( &p, _CDEMBEDDEDEDITCTL, &cdEmbeddedEditCtl, 1 );
	fprintf( dumpfile, "  EMBEDDEDEDITCTL\n" );
	fprintf( dumpfile, "    Flags = 0x%X: ", cdEmbeddedEditCtl.Flags );
	if( cdEmbeddedEditCtl.Flags & EMBEDDEDEDITCTL_FLAG_HASNAME ) fprintf( dumpfile, " HASNAME " );
	if( cdEmbeddedEditCtl.Flags & EMBEDDEDEDITCTL_FLAG_HIDE_ACTIONBAR ) fprintf( dumpfile, " HIDEACTIONBAR " );
	fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "    NameLength = %d\n", cdEmbeddedEditCtl.NameLength );
	if( cdEmbeddedEditCtl.NameLength > 0 )
	{
		fprintf( dumpfile, "    Name = " );
		PrintText((char far *)p, (WORD)cdEmbeddedEditCtl.NameLength );
		p = ((char far *) p) + cdEmbeddedEditCtl.NameLength;
	}
	for( wIndex = 0; wIndex < 5; wIndex++ )
		fprintf( dumpfile, "    SpareWORD[%d] = (0x%X)\n", wIndex, cdEmbeddedEditCtl.SpareWORD[wIndex] );
	for( wIndex = 0; wIndex < 11; wIndex++ )
		fprintf( dumpfile, "    SpareDWORD[%d] = (0x%X)\n", wIndex, cdEmbeddedEditCtl.SpareDWORD[wIndex] );
	return;
}

/************************************************************************

    FUNCTION:   DumpCDTextProperty

*************************************************************************/

void  LNPUBLIC   DumpCDTextProperty (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *	p = RecordPtr;
	CDTEXTPROPERTY	cdTextProperty;

	ODSReadMemory( &p, _CDTEXTPROPERTY, &cdTextProperty, 1 );
	fprintf( dumpfile, "  TEXTPROPERTY\n" );

	fprintf( dumpfile, "    TextStyleName = %s\n", cdTextProperty.TextStyleName );
	fprintf( dumpfile, "    LangName = %s\n", cdTextProperty.LangName );
	fprintf( dumpfile, "    PropID = %X\n", cdTextProperty.PropID );
	fprintf( dumpfile, "    Flags = %X\n", cdTextProperty.Flags );
	fprintf( dumpfile, "    Reserved2 = %X\n", cdTextProperty.Reserved2 );
	fprintf( dumpfile, "    Reserved3 = %X\n", cdTextProperty.Reserved3 );
	
	return;
}

/************************************************************************

    FUNCTION:   DumpCDDataFlags

*************************************************************************/

void  LNPUBLIC   DumpCDDataFlags (
	char *          RecordPtr,
	DWORD           RecordLength
) {

	char far *		p = RecordPtr;
	CDDATAFLAGS		cdDataFlags;
	WORD            dataLen;
	WORD			wIndex;

	ODSReadMemory( &p, _CDDATAFLAGS, &cdDataFlags, 1 );
	dataLen = (WORD) RecordLength - ODSLength (_CDDATAFLAGS);
	fprintf( dumpfile, "  DATAFLAGS\n" );

	fprintf( dumpfile, "   elemType = %d", cdDataFlags.elemType );
		if( CD_SECTION_ELEMENT == cdDataFlags.elemType)
			fprintf( dumpfile, " SECTION_ELEMENT" );
		if( CD_FIELDLIMIT_ELEMENT == cdDataFlags.elemType)
			fprintf( dumpfile, " FIELDLIMIT_ELEMENT" );
		if( CD_BUTTONEX_ELEMENT == cdDataFlags.elemType)
			fprintf( dumpfile, " BUTTONEX_ELEMENT" );
		fprintf( dumpfile, "\n" );
	fprintf( dumpfile, "   Reserved = %X\n", cdDataFlags.dwReserved );

  	fprintf( dumpfile, "   Number of nFlags = %X ", cdDataFlags.nFlags );

	/* Variable part */
	if( cdDataFlags.nFlags > 0 )
	{
		for (wIndex = 0; wIndex<cdDataFlags.nFlags; wIndex++)
		{
			DWORD              databorder;
			ODSReadMemory (&p, _DWORD, &databorder, 1);
			if( CD_SECTION_ELEMENT == cdDataFlags.elemType)
			{
				if( BARREC_DATA_BORDER_GRADIENT == databorder)
					fprintf( dumpfile, " GRADIENT" );
				if( BARREC_DATA_BORDER_TAB == databorder)
					fprintf( dumpfile, " TAB" );
				if( BARREC_DATA_BORDER_DIAG == databorder)
					fprintf( dumpfile, " DIAG" );
			}
			if( CD_BUTTONEX_ELEMENT == cdDataFlags.elemType)
			{
				if (databorder & BUTTON_SPEC_DEFAULT)
				{	
					fprintf( dumpfile, " DEFAULT" );
				}

				databorder = GETDATABORDERTYPE (databorder);
				databorder -= BAR_DATA_BORDER_OFFSET;

				if( BUTTON_TYPE_NORMAL == databorder)
					fprintf( dumpfile, " BUTTON_TYPE_NORMAL" );
				if( BUTTON_TYPE_OK == databorder)
					fprintf( dumpfile, " BUTTON_TYPE_OK");
				if( BUTTON_TYPE_CANCEL == databorder)
					fprintf( dumpfile, " BUTTON_TYPE_CANCEL");
				if( BUTTON_TYPE_HELP == databorder)
					fprintf( dumpfile, " BUTTON_TYPE_HELP");
			}
			if( CD_FIELDLIMIT_ELEMENT == cdDataFlags.elemType)
			{
			}

			dataLen -= ODSLength (_DWORD);
		}
		fprintf( dumpfile, "\n" );
	}

	return;
}


/************************************************************************

    FUNCTION:   DumpCDFieldHint

*************************************************************************/

void    LNPUBLIC  DumpCDFieldHint(
	char *			RecordPtr,
	DWORD			RecordLength
) {
    char far *      p = RecordPtr;
    CDFIELDHINT		cdFieldHint;

    fprintf( dumpfile, "  FIELDHINT\n" );
	ODSReadMemory( &p, _CDFIELDHINT, &cdFieldHint, 1 );

 	fprintf( dumpfile, "    Flags = %X", cdFieldHint.Flags );
	if( cdFieldHint.Flags & FIELDHINT_LIMITED)
		fprintf( dumpfile, "     FIELDHINT_LIMITED" );
	fprintf( dumpfile, "\n");
	fprintf( dumpfile, "    Spare = %X\n", cdFieldHint.Spare );
	fprintf( dumpfile, "    Spare2 = %X\n", cdFieldHint.Spare2 );

	if (0 != cdFieldHint.HintTextLength)
	{
		fprintf ( dumpfile, "    Hint Text = ");
		PrintText( (char far *)p, cdFieldHint.HintTextLength);
		p = ((char far *) p) + cdFieldHint.HintTextLength;
	}

    return;
}


/************************************************************************

    FUNCTION:   DumpCDLargeParagraph

*************************************************************************/

void    LNPUBLIC  DumpCDLargeParagraph(
	char *			RecordPtr,
	DWORD			RecordLength
) {
    char far *      	p = RecordPtr;
    CDLARGEPARAGRAPH	cdLargeParagraph;
     WORD	wIndex;

    fprintf( dumpfile, "  LARGEPARAGRAPH\n" );
	ODSReadMemory( &p, _CDLARGEPARAGRAPH, &cdLargeParagraph, 1 );

 	fprintf( dumpfile, "    Version = %X", cdLargeParagraph.Version );
	if( cdLargeParagraph.Version & LARGEPARAGRAPH_VERSION1)
		fprintf( dumpfile, "      LARGEPARAGRAPH_VERSION1" );
	if( cdLargeParagraph.Version & LARGEPARAGRAPH_CURRENT_VERSION)
		fprintf( dumpfile, "      LARGEPARAGRAPH_CURRENT_VERSION" );
	fprintf( dumpfile, "\n");
 	fprintf( dumpfile, "    Flags = %X", cdLargeParagraph.Flags );
	if( cdLargeParagraph.Flags & CDLARGEPARAGRAPH_BEGIN)
		fprintf( dumpfile, "        LARGEPARAGRAPH_BEGIN" );
	if( cdLargeParagraph.Flags & CDLARGEPARAGRAPH_END)
		fprintf( dumpfile, "        LARGEPARAGRAPH_END" );
	fprintf( dumpfile, "\n");
	for( wIndex = 0; wIndex < 2; wIndex++ )
		fprintf( dumpfile, "    Spare[%d] = (0x%X)\n", wIndex, cdLargeParagraph.Spare[wIndex] );

    return;
}


/************************************************************************

    FUNCTION:   DumpCDIgnore

*************************************************************************/

void    LNPUBLIC  DumpCDIgnore(
	char *			RecordPtr,
	DWORD			RecordLength
) {
    char far *      	p = RecordPtr;
    CDIGNORE	cdIgnore;
     WORD	wIndex;

    fprintf( dumpfile, "  IGNORE\n" );
	ODSReadMemory( &p, _CDIGNORE, &cdIgnore, 1 );

 	fprintf( dumpfile, "    wNotesVersion = %X", cdIgnore.wNotesVersion );
	if( cdIgnore.wNotesVersion & CDIGNORE_NOTES_VERSION_6_0_0)
		fprintf( dumpfile, "     NOTES_VERSION_6_0_0" );
	if( cdIgnore.wNotesVersion & CDIGNORE_NOTES_VERSION_CURRENT)
		fprintf( dumpfile, "     NOTES_VERSION_CURRENT" );
	fprintf( dumpfile, "\n");
 	fprintf( dumpfile, "    dwFlags = %X", cdIgnore.dwFlags );
	if( cdIgnore.dwFlags & FLAG_CDIGNORE_BEGIN)
		fprintf( dumpfile, "     CDIGNORE_BEGIN" );
	if( cdIgnore.dwFlags & FLAG_CDIGNORE_END)
		fprintf( dumpfile, "     CDIGNORE_END" );
	fprintf( dumpfile, "\n");
	for( wIndex = 0; wIndex < 6; wIndex++ )
		fprintf( dumpfile, "    Unused[%d] = (0x%X)\n", wIndex, cdIgnore.dwUnused[wIndex] );

    return;
}

/************************************************************************

    FUNCTION:   DumpCDTableDataExtension

*************************************************************************/

void  LNPUBLIC   DumpCDTableDataExtension (
	char *          RecordPtr,
	DWORD           RecordLength
) {
	char far *		p = RecordPtr;
	CDTABLEDATAEXTENSION	cdTableDataExtension;
	COLOR_VALUE		*cvPtr;

	ODSReadMemory( &p, _CDTABLEDATAEXTENSION, &cdTableDataExtension, 1 );
	fprintf( dumpfile, "  TABLEDATAEXTENSION\n" );
	
	fprintf( dumpfile, "    dwColumnSizeToFitBits1 = %X\n", cdTableDataExtension.dwColumnSizeToFitBits1 );
	fprintf( dumpfile, "    dwColumnSizeToFitBits2 = %X\n", cdTableDataExtension.dwColumnSizeToFitBits2 );
	fprintf( dumpfile, "    wEqualSizeTabsWidthX = %X\n", cdTableDataExtension.wEqualSizeTabsWidthX );
	fprintf( dumpfile, "    wTabsIndentWidthX = %X\n", cdTableDataExtension.wTabsIndentWidthX );
	fprintf( dumpfile, "    wAvailable3 = %X\n", cdTableDataExtension.wAvailable3 );
	fprintf( dumpfile, "    wAvailable4 = %X\n", cdTableDataExtension.wAvailable4 );
	fprintf( dumpfile, "    dwAvailable5 = %X\n", cdTableDataExtension.dwAvailable5 );
	fprintf( dumpfile, "    dwAvailable6 = %X\n", cdTableDataExtension.dwAvailable6 );
	fprintf( dumpfile, "    dwAvailable7 = %X\n", cdTableDataExtension.dwAvailable7 );
	fprintf( dumpfile, "    dwAvailable8 = %X\n", cdTableDataExtension.dwAvailable8 );
	fprintf( dumpfile, "    dwAvailable9 = %X\n", cdTableDataExtension.dwAvailable9 );
	fprintf( dumpfile, "    --------\n");
  	fprintf( dumpfile, "    wcTabLabelFont = \n");


	if( cdTableDataExtension.wcTabLabelFont > 0 )
	{
		if( cdTableDataExtension.wcTabLabelFont >= ((sizeof(FONTID)) + (sizeof(DWORD)) + (sizeof(COLOR_VALUE ))))
			{
			fprintf( dumpfile, "    Tab Label Font FONTID = " );
			DumpFontIDFields((FONTIDFIELDS *)p);
			p += (sizeof(FONTID));

			fprintf( dumpfile, "    Tab Label Font DWORD = " );
			fprintf( dumpfile, "%X\n", p );
			p += (sizeof(DWORD));

	 	    fprintf( dumpfile, "    Tab Label Font COLOR_VALUE = \n" );
			cvPtr = (COLOR_VALUE *) p;
			DumpColorValue(*cvPtr);
			p += (sizeof(COLOR_VALUE));
			}

		else /* older builds may not have COLOR_VALUE */
		{
			fprintf( dumpfile, "    Tab Label Font FONTID = " );
			DumpFontIDFields((FONTIDFIELDS *)p);
			p += (sizeof(FONTID));

			fprintf( dumpfile, "    Tab Label Font DWORD = " );
			fprintf( dumpfile, "%X\n", p );
			p += (sizeof(DWORD));

			fprintf( dumpfile, "\n");
		}	
	}

	fprintf( dumpfile, "    --------\n");

	fprintf( dumpfile, "    wAvailableLength11 = %X", cdTableDataExtension.wAvailableLength11 );
	if( cdTableDataExtension.wAvailableLength11 > 0 )
	{
		PrintText(p, (WORD)cdTableDataExtension.wAvailableLength11 );
		p += cdTableDataExtension.wAvailableLength11;
	}
	fprintf( dumpfile, "\n");

	fprintf( dumpfile, "    wAvailableLength12 = %X", cdTableDataExtension.wAvailableLength12 );
	if( cdTableDataExtension.wAvailableLength12 > 0 )
	{
		PrintText(p, (WORD)cdTableDataExtension.wAvailableLength12 );
		p += cdTableDataExtension.wAvailableLength12;
	}
	fprintf( dumpfile, "\n");

	fprintf( dumpfile, "    wExtension2Length = %X", cdTableDataExtension.wExtension2Length );
	if( cdTableDataExtension.wExtension2Length > 0 )
	{
		PrintText(p, (WORD)cdTableDataExtension.wExtension2Length );
		p += cdTableDataExtension.wExtension2Length;
	}
	fprintf( dumpfile, "\n");

	return;
}

