//===========================================================================
//
// Module:	LNFONT.HPP
//
// Description:
//
//		Class library definition for LNFontStyle, LNFontTable, and related
//		classes (including LNCompositeItemBody).
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNFONT_HPP
#define LNFONT_HPP

#ifndef EDITODS_DEFS
#include <editods.h>
#endif


#define LNFONTID FONTID

/* Give users access to the default Notes FontIDs. */
/* Note that there numerous other valid FontIDs, these are just some common defaults. */

#define LNFONTID_PLAIN			DEFAULT_FONT_ID
#define LNFONTID_BOLD 			DEFAULT_BOLD_FONT_ID
#define LNFONTID_SMALL			DEFAULT_SMALL_FONT_ID	
#define LNFONTID_PERMANENT_PEN	DEFAULT_PPEN_FONT_ID
#define LNFONTID_FOREIGN		FOREIGN_FONT_ID


/*	Font Style Bit Fields */

// Attributes
typedef WORD LNFONTATTRIBUTEFLAGS;
#define LNFONTATTRIBUTEFLAGS_PLAIN			0x0000
#define LNFONTATTRIBUTEFLAGS_BOLD 			0x0001
#define LNFONTATTRIBUTEFLAGS_ITALIC 		0x0002
#define LNFONTATTRIBUTEFLAGS_UNDERLINE 		0x0004
#define LNFONTATTRIBUTEFLAGS_STRIKETHROUGH 	0x0008
#define LNFONTATTRIBUTEFLAGS_SUPERSCRIPT 	0x0010
#define LNFONTATTRIBUTEFLAGS_SUBSCRIPT 		0x0020
#define LNFONTATTRIBUTEFLAGS_SHADOW			0x0080
#define LNFONTATTRIBUTEFLAGS_EMBOSS			0x0100
#define LNFONTATTRIBUTEFLAGS_EXTRUDE		0x0200

#define LNFONTATTRIBUTEFLAGS_ALL			0xFFFF




/* Font Style Masks */


typedef DWORD LNSETFONTSTYLEFLAGS;
const DWORD LNSETFONTSTYLEFLAGS_ALL				= (DWORD)0xFFFFFFFFL;
const DWORD LNSETFONTSTYLEFLAGS_COLOR			= (DWORD)0x00010000L;
const DWORD LNSETFONTSTYLEFLAGS_FACE			= (DWORD)0x00020000L;
const DWORD LNSETFONTSTYLEFLAGS_SIZE			= (DWORD)0x00040000L;

const DWORD LNSETFONTSTYLEFLAGS_ALL_ATTRIBUTES	= (DWORD)LNFONTATTRIBUTEFLAGS_ALL;
													// Including the following
const DWORD LNSETFONTSTYLEFLAGS_BOLD			= (DWORD)LNFONTATTRIBUTEFLAGS_BOLD;
const DWORD LNSETFONTSTYLEFLAGS_ITALIC			= (DWORD)LNFONTATTRIBUTEFLAGS_ITALIC;
const DWORD LNSETFONTSTYLEFLAGS_UNDERLINE		= (DWORD)LNFONTATTRIBUTEFLAGS_UNDERLINE;
const DWORD LNSETFONTSTYLEFLAGS_STRIKETHROUGH	= (DWORD)LNFONTATTRIBUTEFLAGS_STRIKETHROUGH;
const DWORD LNSETFONTSTYLEFLAGS_SUPERSCRIPT		= (DWORD)LNFONTATTRIBUTEFLAGS_SUPERSCRIPT;
const DWORD LNSETFONTSTYLEFLAGS_SUBSCRIPT		= (DWORD)LNFONTATTRIBUTEFLAGS_SUBSCRIPT;
const DWORD LNSETFONTSTYLEFLAGS_SHADOW			= (DWORD)LNFONTATTRIBUTEFLAGS_SHADOW;
const DWORD LNSETFONTSTYLEFLAGS_EMBOSS			= (DWORD)LNFONTATTRIBUTEFLAGS_EMBOSS;
const DWORD LNSETFONTSTYLEFLAGS_EXTRUDE			= (DWORD)LNFONTATTRIBUTEFLAGS_EXTRUDE;


// Faces


typedef BYTE LNFACEID;
#define LNFACEID_ROMAN			FONT_FACE_ROMAN
#define LNFACEID_HELVETICA		FONT_FACE_SWISS
#define LNFACEID_COURIER 		FONT_FACE_TYPEWRITER
#define LNFACEID_MULTILINGUAL	FONT_FACE_UNICODE

// For user convenience we have included the same names that Notes uses
#define LNFACEID_SWISS			FONT_FACE_SWISS
#define	LNFACEID_TYPEWRITER		FONT_FACE_TYPEWRITER




// The Notes font pitch and family is similar to the Microsoft Windows definitions,
// found in WINGDI.H

// The Windows LOGFONT structure defines the attributes of a font. 

// typedef struct tagLOGFONT { // lf 
//    LONG lfHeight; 
//    LONG lfWidth; 
//    LONG lfEscapement; 
//    LONG lfOrientation; 
//    LONG lfWeight; 
//    BYTE lfItalic; 
//    BYTE lfUnderline; 
//    BYTE lfStrikeOut; 
//    BYTE lfCharSet; 
//    BYTE lfOutPrecision; 
//    BYTE lfClipPrecision; 
//    BYTE lfQuality; 
//    BYTE lfPitchAndFamily; 
//    TCHAR lfFaceName[LF_FACESIZE]; 
// } LOGFONT; 
 

// lfPitchAndFamily specifies the pitch and family of the font. 
// The two low-order bits specify the pitch of the font and can 
// be one of the following values: 

// #define DEFAULT_PITCH           0
// #define FIXED_PITCH             1
// #define VARIABLE_PITCH          2

// Bit 2 is set for Microsoft True Type fonts

// For Windows NT 4.0 and Windows 95, bit 3 is set for monospaced fonts.

// Bits 4 through 7 of the member specify the font family and can 
// be one of the following values: 

// #define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
// #define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. */
//                                     /* Times Roman, Century Schoolbook, etc. */
// #define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. */
//                                     /* Helvetica, Swiss, etc. */
// #define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. */
//                                     /* Pica, Elite, Courier, etc. */
// #define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
// #define FF_DECORATIVE       (5<<4)  /* Old English, etc. */

// The proper value can be obtained by using the Boolean OR operator 
// to join one pitch constant with one family constant. 

// Since the C++ API doesn't include the Windows header files, we need
// to create new #defines for our exposed values, to facilitate converting
// between the types.



/* Font Pitch Values (low 2 bits) */

typedef BYTE LNFONTPITCH;
#define LNFONTPITCH_DEFAULT			0x00
#define LNFONTPITCH_FIXED 			0x01
#define LNFONTPITCH_VARIABLE 		0x02	



const BYTE LNFONTPITCHMASK = 0x02;

#define LNFONT_TRUE_TYPE            0x04	/* TrueType flag (bit 2) */

// #if(WINVER >= 0x0400)
#define LNFONT_MONOSPACED           0x08	/* Monospace flag (bit 3) */
// #endif /* WINVER >= 0x0400 */




/* Font Family Values (high 4 bits) */

typedef BYTE LNFONTFAMILY;
#define LNFONTFAMILY_DONT_CARE		0x00
#define LNFONTFAMILY_ROMAN			0x10
#define LNFONTFAMILY_SWISS			0x20
#define LNFONTFAMILY_MODERN			0x30
#define LNFONTFAMILY_SCRIPT			0x40
#define LNFONTFAMILY_DECORATIVE		0x50
#define LNFONTFAMILY_UNKNOWN		0xF0




#ifndef LNRTOBJ_HPP
#include "lnrtobj.hpp"
#endif


class LNIMPEXPCL LNFontTable : public LNItem
{

public:

	LNFontTable();
	LNFontTable(const LNFontTable &other);
	LNFontTable(const LNItem &other);

	~LNFontTable();
	
	LNFontTable& operator=(const LNFontTable &other);
	LNFontTable& operator=(const LNItem &other);
	
	LNBOOL operator==(const LNFontTable &fontTable) const;

	LNBOOL operator!=(const LNFontTable &fontTable) const;

	LNFontTable& operator<<(const CDFACE &face);

	CDFACE operator[](LNINT index) const;

	LNSTATUS Append(const CDFACE &face);
	LNSTATUS Append(BYTE cdfacefamily, const LNString &name, LNFACEID *faceid = 0);
	LNSTATUS Append(LNFONTPITCH pitch, LNFONTFAMILY family, const LNString &facename, 
		LNBOOL truetype = FALSE, LNBOOL monospace = FALSE, LNFACEID *faceid = 0);

	LNSTATUS DeleteByFaceID(LNFACEID faceid);

	LNSTATUS DeleteByName(const LNString &name);

	LNSTATUS DeleteByPosition(LNINT pos, LNINT count);
	
	LNSTATUS GetCDFaceByFaceID(LNFACEID faceid, CDFACE *face) const;

	LNSTATUS GetCDFaceByName(const LNString &name, CDFACE *face) const;

	LNSTATUS GetCDFaceByPosition(LNINT pos, CDFACE *face) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNFONTTABLE; }

	LNINT GetCount() const;

	LNSTATUS GetFaceByFaceID(LNFACEID faceid, LNFONTPITCH *pitch = 0, LNFONTFAMILY *family = 0, 
		LNString *name = 0, LNBOOL *truetype = 0, LNBOOL *monospace = 0) const;

	LNSTATUS GetFaceByName(const LNString &name, LNFACEID *faceid = 0, LNFONTPITCH *pitch = 0, 
		LNFONTFAMILY *family = 0, LNBOOL *truetype = 0, LNBOOL *monospace = 0) const;

	LNSTATUS GetFaceByPosition(LNINT pos, LNFACEID *faceid = 0, LNFONTPITCH *pitch = 0, LNFONTFAMILY *family = 0, 
		LNString *name = 0, LNBOOL *truetype = 0, LNBOOL *monospace = 0) const;
	
	LNSTATUS Insert(LNINT pos, const CDFACE &face);
	LNSTATUS Insert(LNINT pos, BYTE cdfacefamily, const LNString &name, 
		LNFACEID *faceid = 0);
	LNSTATUS Insert(LNINT pos, LNFONTPITCH pitch, LNFONTFAMILY family, 
		const LNString &facename, LNBOOL truetype = FALSE, 
		LNBOOL monospace = FALSE, LNFACEID *faceid = 0);

protected:

	LNFontTable(LNFontTableBody *body);
	
	LNFontTable& operator=(LNFontTableBody *body);

 	LNSTATUS AddFace(BYTE family, const char *name, LNFACEID *faceid);
	
	LNFontTableBody* GetFontTableBody() const { return (LNFontTableBody *) Body; }

	LNSTATUS InsertFace(LNINT pos, LNFACEID faceid, BYTE family, 
		const LNString &name, LNFACEID *outputFaceid);

	// Must step through text objects and reset font styles in conjunction with this.
	LNSTATUS Merge(const LNFontTable &other);

	virtual LNSTATUS Update();
};




class LNIMPEXPCL LNFontStyle : public LNSmartPtr
{

public:

	LNFontStyle();
	LNFontStyle(const LNFontStyle &other);
	LNFontStyle(LNFONTID fontid, const LNFontTable *fontTable = 0);
	LNFontStyle(LNFONTPITCH pitch, LNFONTFAMILY family, const LNString &facename, 
		LNBOOL truetype = FALSE, LNBOOL monospaced = FALSE);

	~LNFontStyle();
	
	LNFontStyle& operator=(const LNFontStyle &other);

	LNBOOL operator==(const LNFontStyle &other) const;

	LNBOOL operator!=(const LNFontStyle &other) const;

	LNSTATUS Copy(const LNFontStyle &other);

	LNFONTATTRIBUTEFLAGS GetAttributes() const;

	// Get standard and special faces
	// If the face is > STATIC_FONT_FACES, then it is a special face, kept in the
	// notes font table. faceids with the same value can have different faces
	// if they are associated with different font tables.

	// CDFACE is a notes data structure (see the C API as well as LNFontTable)
	// The faceid LNFACEID is the same as the Face field in the CDFACE data structure.
																				
	LNSTATUS GetCDFace(CDFACE *fontface) const;

	LNColor GetColor() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNFONTSTYLE; }

	LNFACEID GetFaceID() const; 

	LNString GetFaceName() const;

	LNFONTFAMILY GetFamily() const;

	LNFONTID GetFontID() const;
	
	LNSTATUS GetFontTable(LNFontTable *fontTable) const;

	LNFONTPITCH GetPitch() const;

	LNINT GetPointSize() const;

	LNINT GetShadowOffset() const;

	LNBOOL IsMonospaced() const;

	LNBOOL IsTrueType() const;
	
	LNSTATUS SetAttributes(LNFONTATTRIBUTEFLAGS attribs);

	LNSTATUS SetCDFace(CDFACE fontface);

	LNSTATUS SetColor(const LNColor & color);

	LNSTATUS SetDefaults();

	LNSTATUS SetFaceID(LNFACEID faceid);

	LNSTATUS SetFontID(LNFONTID fontid, LNSETFONTSTYLEFLAGS mask=LNSETFONTSTYLEFLAGS_ALL);

	LNSTATUS SetPointSize(LNINT fontsize);

protected:

   	LNFontStyle(LNFontStyleBody *body);
	LNFontStyle(LNFONTID fontid, LNNoteBody *noteBody);

	LNFontStyle& operator=(LNFontStyleBody *body);

	LNSTATUS Assign(LNFONTID fontid, const LNFontTable *fontTable = 0);
	LNSTATUS Assign(LNFONTID fontid, LNNoteBody *noteBody);

	LNFontStyleBody* GetFontStyleBody() const { return (LNFontStyleBody *) Body; }

	LNSTATUS SetFontStyle(const LNFontStyle &style, LNSETFONTSTYLEFLAGS mask=LNSETFONTSTYLEFLAGS_ALL);
};



#endif

