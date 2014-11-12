//===========================================================================
//
// Module:  LNPARAGR.HPP
//
// Description:
//
//  Class library definition for LNParagraphStyle and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNPARAGR_HPP
#define LNPARAGR_HPP

#ifndef EDITDFLT_DEFS
#include <editdflt.h>
#endif


// Alignment is also known as justification.

typedef WORD LNALIGNMENT;
#define LNALIGNMENT_LEFT		JUSTIFY_LEFT	/* flush left, ragged right */
#define LNALIGNMENT_CENTER		JUSTIFY_CENTER	/* centered */
#define LNALIGNMENT_RIGHT		JUSTIFY_RIGHT	/* flush right, ragged left */
#define LNALIGNMENT_FULL		JUSTIFY_BLOCK	/* full block justification */
#define LNALIGNMENT_NONE		JUSTIFY_NONE	/* no line wrapping AT ALL (except hard CRs) */


// Paragraph indentation

enum LNINDENTATION
{
	LNINDENTATION_NONE,
	LNINDENTATION_INDENT,
	LNINDENTATION_OUTDENT
};


// Spacing between lines

typedef WORD LNLINESPACING;

// The value stored for LNLINESPACING must be equal to (2*(Line Spacing-1))
// That way users can work with values not defined here. Although the GUI
// only supports the three defined types, you can set others (such as triple 
// spacing) with the API and get the behavior you expect.

// For example,
//	 Line Spacing					LNLINESPACING 
//									(stored in CDPABDEFINITION.LineSpacing)
//	   Single          1				0
//	   One and a half  1.5				1
//	   Double		   2				2
//	   Two and a half  2.5				3
//	   Triple		   3				4
//	    etc.
//			
#define LNLINESPACING_SINGLE  0  // single spacing
#define LNLINESPACING_1_5     1  // 1.5 spacing		
#define LNLINESPACING_DOUBLE  2	 // double spacing


enum LNLISTSTYLE
{
	LNLISTSTYLE_NONE,
	LNLISTSTYLE_BULLET,				// display paragraph with bullet
	LNLISTSTYLE_NUMBERED,			// display paragraph with number
	LNLISTSTYLE_EMPTY_CHECKMARK,	//	New list styles available in R5
	LNLISTSTYLE_FILLED_CHECKMARK,
	LNLISTSTYLE_CIRCLE,
	LNLISTSTYLE_SQUARE,
	LNLISTSTYLE_LOWERALPHA,
	LNLISTSTYLE_UPPERALPHA,
	LNLISTSTYLE_LOWERROMAN,
	LNLISTSTYLE_UPPERROMAN
};


// Position of text relative to the tab stop

enum LNTABALIGNMENT
{
	LNTABALIGNMENT_LEFT = TAB_LEFT,			/* default - flush left starting at tab pos. */
	LNTABALIGNMENT_RIGHT = TAB_RIGHT,		/* text is right justified before tab pos. */
	LNTABALIGNMENT_CENTER = TAB_CENTER,		/* text is centered around tab pos. */
	LNTABALIGNMENT_DECIMAL = TAB_DECIMAL,	/* text is placed so that decimal point is aligned with tab pos. */
	LNTABALIGNMENT_DEFAULT = TAB_DEFAULT
};


// Position of the tab relative to the left margin

typedef LNNUMBER LNTABPOSITION;		// floatint-point number number






class LNIMPEXPCL LNTabs : public LNSmartPtr
{

public:

	LNTabs();

	LNTabs(LNUNITS units);

	LNTabs(const LNTabs &other);

	~LNTabs();

	LNTabs& operator=(const LNTabs &other);

	LNTABPOSITION operator[](LNINT n) const;

	LNSTATUS Add(const LNTABPOSITION &position, LNTABALIGNMENT alignment = LNTABALIGNMENT_LEFT);

	LNSTATUS GetAlignment(const LNTABPOSITION &position, LNTABALIGNMENT *alignment);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABS; }

	LNINT GetCount() const;

	LNUNITS GetUnits() const;

	LNSTATUS Remove(const LNTABPOSITION &position);

	LNSTATUS RemoveAll();

	LNSTATUS SetAlignment(const LNTABPOSITION &position, LNTABALIGNMENT alignment);

	LNSTATUS SetInterval(const LNNUMBER &interval, LNTABALIGNMENT alignment = LNTABALIGNMENT_LEFT);

	LNSTATUS SetUnits(LNUNITS units);

protected:

	LNTabs(LNPABDefinitionBody *body);

	LNTabs& operator=(LNPABDefinitionBody *body);


private:

	// The body object for LNTabs is an LNPABDefinitionBody (CDPABDEFINITION).
};






class LNIMPEXPCL LNParagraphStyle : public LNSmartPtr
{


public:
	
	LNParagraphStyle();

	LNParagraphStyle(const CDPABDEFINITION &pabdef, LNUNITS units);

	LNParagraphStyle(const CDPABDEFINITION &pabdef, const LNFormula &formula, LNUNITS units);

	LNParagraphStyle(const LNParagraphStyle &other);
	
	~LNParagraphStyle();
	
	LNParagraphStyle& operator=(const LNParagraphStyle &other);

	virtual LNBOOL operator==(const LNParagraphStyle &other) const;

	virtual LNBOOL operator!=(const LNParagraphStyle &other) const;

	virtual LNSTATUS Copy(const LNParagraphStyle &other);

	LNALIGNMENT GetAlignment() const;

	LNSTATUS GetCDPABDefinition(CDPABDEFINITION *pabdef, WORD (*extendedMargins)[6] = 0) const;

	WORD GetCDPABDefinitionFlags (void) const;
	WORD GetCDPABDefinitionFlags2 (void) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNPARAGRAPHSTYLE; }

	LNINDENTATION GetFirstLineIndentation() const;

	LNNUMBER GetFirstLineIndentationValue() const;

	LNNUMBER GetFirstLineMargin() const;

	LNBOOL GetHideFromClients() const;

	LNBOOL GetHideFromBrowsers() const;

	// Keep this old name so legacy code will work
	LNBOOL GetHideFromNotes46() const { return GetHideFromClients(); }

	// Keep this old name so legacy code will work
	LNBOOL GetHideFromWebBrowsers() const {return GetHideFromBrowsers(); }

	LNSTATUS GetHideIfFormula(LNFormula *formula) const;

	LNBOOL GetHideWhenCopying() const;

	LNBOOL GetHideWhenEditing() const;

	LNBOOL GetHideWhenEditingPreview() const;

	LNBOOL GetHideWhenReading() const;

	LNBOOL GetHideWhenReadingPreview() const;

	LNBOOL GetHideWhenPrinting() const;

	LNBOOL GetKeepLinesTogether() const;

	LNBOOL GetKeepParagraphsTogether() const;

	LNNUMBER GetLeftMargin() const;

	LNLINESPACING GetLineSpacing() const;

	LNLISTSTYLE GetListStyle() const;

	LNBOOL GetPageBreakBefore() const;

	LNNUMBER GetRightMargin() const;

	LNLINESPACING GetSpacingAbove() const;

	LNLINESPACING GetSpacingBelow() const;

	LNSTATUS GetTabs(LNTabs *tabstops) const;

	LNUNITS GetUnits() const;

	LNBOOL IsLeftMarginPercent() const;

	LNBOOL IsNamed() const;

	LNBOOL IsRightMarginPercent() const;

	LNSTATUS SetAlignment(LNALIGNMENT alignment);

	void SetCDPABDefinitionFlags(WORD flags);

	void SetCDPABDefinitionFlags2(WORD flags2);

	virtual LNSTATUS SetDefaults();

	LNSTATUS SetFirstLineIndentation(LNINDENTATION firstline);

	LNSTATUS SetFirstLineIndentationValue(const LNNUMBER &value);

	LNSTATUS SetFirstLineMargin(const LNNUMBER &margin);

	void SetHideFromBrowsers(LNBOOL hide);

	void SetHideFromClients(LNBOOL hide);

	// Keep this old name so legacy code will work
	void SetHideFromNotes46(LNBOOL hide) { SetHideFromClients(hide); }

	// Keep this old name so legacy code will work
	void SetHideFromWebBrowsers(LNBOOL hide) { SetHideFromBrowsers(hide); }
	
	LNSTATUS SetHideIfFormula(const LNFormula &formula);

	void SetHideWhenCopying(LNBOOL hide);

	void SetHideWhenEditing(LNBOOL hide);

	void SetHideWhenEditingPreview(LNBOOL hide);

	void SetHideWhenReading(LNBOOL hide);
 
	void SetHideWhenReadingPreview(LNBOOL hide);

	void SetHideWhenPrinting(LNBOOL hide);

	void SetKeepLinesTogether(LNBOOL together);

	void SetKeepParagraphsTogether(LNBOOL together);

	LNSTATUS SetLeftMargin(const LNNUMBER &leftmargin);

	LNSTATUS SetLeftMarginPercent(LNINT leftmargin);

	LNSTATUS SetLineSpacing(LNLINESPACING spaceinterline);

	LNSTATUS SetListStyle(LNLISTSTYLE style);

	void SetPageBreakBefore(LNBOOL pagebreak);

	LNSTATUS SetRightMargin(const LNNUMBER &rightmargin);

	LNSTATUS SetRightMarginPercent(LNINT rightmargin);

	LNSTATUS SetSpacingAbove(LNLINESPACING spaceabove);

	LNSTATUS SetSpacingBelow(LNLINESPACING spacebelow);

	LNSTATUS SetUnits(LNUNITS units);

protected:

	LNParagraphStyle(LNParagraphStyleBody *body);

	LNParagraphStyle& operator=(LNParagraphStyleBody *body);

	LNParagraphStyleBody* GetParagraphStyleBody() const { return (LNParagraphStyleBody *) Body; }

	LNBOOL IsEqual(const LNPABDefinition &pabdef, const LNPABHide &pabhide) const;

	LNSTATUS SetTableCellMargins(LNINT leftMargin, LNINT rightMargin);

};


#endif

