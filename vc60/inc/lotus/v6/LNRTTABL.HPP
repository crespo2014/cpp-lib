//==========================================================================================
//
// Module:	LNRTTABL.HPP
//
// Description
//
//  Class Library description for LNTable, LNTableBody, LNTableCell,
//  LNTableCellBody.
//
//==========================================================================================
//
// Copyright (c) 1997-2003 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTTABL_HPP
#define LNRTTABL_HPP

#include "editdflt.h"


enum LNTABLEBORDERSTYLE
{
	LNTABLEBORDERSTYLE_NONE		=	CDBORDERSTYLE_NONE,
	LNTABLEBORDERSTYLE_DASHED	=	CDBORDERSTYLE_DASHED,
	LNTABLEBORDERSTYLE_DOTTED	=	CDBORDERSTYLE_DOTTED,
	LNTABLEBORDERSTYLE_DOUBLE	=	CDBORDERSTYLE_DOUBLE,
	LNTABLEBORDERSTYLE_GROOVE	=	CDBORDERSTYLE_GROOVE,
	LNTABLEBORDERSTYLE_INSET	=	CDBORDERSTYLE_INSET,
	LNTABLEBORDERSTYLE_OUTSET	=	CDBORDERSTYLE_OUTSET,
	LNTABLEBORDERSTYLE_RIDGE	=	CDBORDERSTYLE_RIDGE,
	LNTABLEBORDERSTYLE_SOLID	=	CDBORDERSTYLE_SOLID
};

#define LNCELLBORDERSTYLE			LNTABLEBORDERSTYLE
#define	LNCELLBORDERSTYLE_SOLID		LNTABLEBORDERSTYLE_SOLID
#define	LNCELLBORDERSTYLE_GROOVE	LNTABLEBORDERSTYLE_GROOVE
#define	LNCELLBORDERSTYLE_RIDGE		LNTABLEBORDERSTYLE_RIDGE

enum LNCELLBORDERTYPE
{
	LNCELLBORDERTYPE_NONE   = TABLE_BORDER_NONE,
	LNCELLBORDERTYPE_SINGLE = TABLE_BORDER_SINGLE,
	LNCELLBORDERTYPE_DOUBLE = TABLE_BORDER_DOUBLE
};

enum LNTABLECOLORSTYLE
{
	LNTABLECOLORSTYLE_NONE = 0,
	LNTABLECOLORSTYLE_SOLID,
	LNTABLECOLORSTYLE_ALTERNATING_ROWS,
	LNTABLECOLORSTYLE_ALTERNATING_COLUMNS,
	LNTABLECOLORSTYLE_LEFT_TOP,
	LNTABLECOLORSTYLE_LEFT,
	LNTABLECOLORSTYLE_RIGHT_TOP,
	LNTABLECOLORSTYLE_RIGHT,
	LNTABLECOLORSTYLE_TOP
};

#ifndef TRANS_LEFTTORIGHT_COLUMN
	#define TRANS_LEFTTORIGHT_COLUMN	1
	#define TRANS_ROLLING				2
	#define TRANS_TOPTOBOTTOM_ROW		3
	#define TRANS_WIPE					4
	#define TRANS_BOXES_INCREMENT		5
	#define TRANS_EXPLODE				6
	#define TRANS_DISSOLVE				7
#endif

enum LNTRANSITIONEFFECT
{
	LNTRANSITIONEFFECT_NONE,
	LNTRANSITIONEFFECT_LEFT_TO_RIGHT = TRANS_LEFTTORIGHT_COLUMN,
	LNTRANSITIONEFFECT_ROLLING = TRANS_ROLLING,
	LNTRANSITIONEFFECT_TOP_TO_BOTTOM = TRANS_TOPTOBOTTOM_ROW,
	LNTRANSITIONEFFECT_WIPE = TRANS_WIPE,
	LNTRANSITIONEFFECT_BOX_BY_BOX = TRANS_BOXES_INCREMENT,
	LNTRANSITIONEFFECT_EXPLODE = TRANS_EXPLODE,
	LNTRANSITIONEFFECT_DISSOLVE = TRANS_DISSOLVE
};

enum LNTABLEROWDISPLAY
{
	LNTABLEROWDISPLAY_UNKNOWN,				// Something we don't recognize
	LNTABLEROWDISPLAY_ALL,					// "Show all table rows"
	LNTABLEROWDISPLAY_TABS,					// "Pick row via tab buttons"
	LNTABLEROWDISPLAY_PERIODIC,				// "Switch row every n milliseconds"
	LNTABLEROWDISPLAY_BY_FIELD,				// "Switch rows programmatically"
	LNTABLEROWDISPLAY_BY_FIELD_WITH_TABS,	// ditto, with tabs
	LNTABLEROWDISPLAY_ONCE_ON_OPEN,			// "Switch row..."/"Once when opened"
	LNTABLEROWDISPLAY_ONCE_ON_CLICK,		// "Switch row..."/"Once on click"
	LNTABLEROWDISPLAY_SWITCH_ON_CLICK		// "Switch row..."/"Advance on click"
};

enum LNTABLEWIDTHTYPE
{
	LNTABLEWIDTHTYPE_FIXED_LEFT,
	LNTABLEWIDTHTYPE_FIXED_CENTER,
	LNTABLEWIDTHTYPE_FIXED_RIGHT,
	LNTABLEWIDTHTYPE_FIT_MARGINS,
	LNTABLEWIDTHTYPE_FIT_WINDOW
};

enum LNCELLALIGNMENT
{
	LNCELLALIGNMENT_TOP = 0,
	LNCELLALIGNMENT_CENTER,
	LNCELLALIGNMENT_BOTTOM
};

enum LNCELLCOLORSTYLE
{
	LNCELLCOLORSTYLE_NONE = 0,
	LNCELLCOLORSTYLE_HORIZONTAL_GRADIENT,
	LNCELLCOLORSTYLE_VERTICAL_GRADIENT
};

enum LNCELLIMAGEPLACEMENT
{
	LNCELLIMAGEPLACEMENT_UNKNOWN,
	LNCELLIMAGEPLACEMENT_CENTER,
	LNCELLIMAGEPLACEMENT_REPEAT_ONCE,
	LNCELLIMAGEPLACEMENT_REPEAT_VERTICAL,
	LNCELLIMAGEPLACEMENT_REPEAT_HORIZONTAL,
	LNCELLIMAGEPLACEMENT_RESIZE,
	LNCELLIMAGEPLACEMENT_TILE
};

// The following symbols are deprecated:

#define LNTABLEBORDERSTYLE_EMBOSS	LNCELLBORDERSTYLE_GROOVE
#define LNTABLEBORDERSTYLE_EMBOSSED LNCELLBORDERSTYLE_GROOVE
#define LNTABLEBORDERSTYLE_EXTRUDE	LNCELLBORDERSTYLE_RIDGE
#define LNTABLEBORDERSTYLE_EXTRUDED LNCELLBORDERSTYLE_RIDGE
#define LNTABLEBORDERSTYLE_STANDARD	LNCELLBORDERSTYLE_SOLID

#define LNTABLEBORDERTYPE			LNCELLBORDERTYPE
#define LNTABLEBORDERTYPE_NONE		LNCELLBORDERTYPE_NONE
#define LNTABLEBORDERTYPE_SINGLE	LNCELLBORDERTYPE_SINGLE
#define LNTABLEBORDERTYPE_DOUBLE	LNCELLBORDERTYPE_DOUBLE


class LNIMPEXPCL LNTableCell : public LNRTContainer
{

public:

	LNTableCell();
	LNTableCell(const LNRTObject &other);
	LNTableCell(const LNTableCell &other);

	~LNTableCell();

	LNTableCell& operator=(const LNRTObject &other);
	LNTableCell& operator=(const LNTableCell &other);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convertNewLines = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, LNRTObject *newObject = 0);

	LNColor	GetBackgroundColor() const;

	LNCELLBORDERTYPE GetBottomBorderType() const;

	LNINT GetBottomBorderWidth() const;

	LNSTATUS GetCDTableCell(CDTABLECELL *tablecell) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLECELL; }

	LNCELLCOLORSTYLE GetColorStyle () const;

	LNINT GetColumnIndex() const;

	LNSTATUS GetGradientColor (LNColor * color) const;

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS GetImageNameFormula (LNFormula * pName) const;

	LNSTATUS GetImageNameString (LNString * pName) const;

	LNCELLIMAGEPLACEMENT GetImagePlacement () const;

	LNCELLBORDERTYPE GetLeftBorderType() const;
	
	LNINT GetLeftBorderWidth() const;

	LNSTATUS GetMergeBoundaries
		(LNINT * row1, LNINT * col1, LNINT * row2, LNINT * col2) const;

	LNCELLBORDERTYPE GetRightBorderType() const;
	
	LNINT GetRightBorderWidth() const;

	LNINT GetRowIndex() const;

 	LNSTATUS GetTable(LNTable *table) const;

	LNCELLBORDERTYPE GetTopBorderType() const;
	
	LNINT GetTopBorderWidth() const;

	LNTRANSITIONEFFECT GetTransitionEffect ();

	LNCELLALIGNMENT GetVerticalAlignment() const;

	LNBOOL GetTransparent () const;

	LNBOOL HasImage() const;

	LNBOOL IsCellMerged() const;
	LNBOOL IsCellMergedHorizontally() const;
	LNBOOL IsCellMergedVertically() const;

	LNBOOL IsImageNameFormula () const;

	LNBOOL IsImageNameString () const;


	LNSTATUS SetBackgroundColor(const LNColor & color);

	LNSTATUS SetBottomBorderType(const LNCELLBORDERTYPE border);
	
	LNSTATUS SetBottomBorderWidth(LNINT width = 1);

 	LNSTATUS SetCDTableCell(const CDTABLECELL &tablecell);

	void SetCDTableCellColumnSpan(BYTE span);

	void SetCDTableCellFlags(BYTE flags);

	void SetCDTableCellRowSpan(BYTE span);

	LNSTATUS SetColorStyle (LNCELLCOLORSTYLE style);

	LNSTATUS SetGradientColor (const LNColor & color);

	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	LNSTATUS SetImage (const LNImageResource & newImage);

	LNSTATUS SetImageNameFormula (const LNFormula & imageName);

	LNSTATUS SetImageNameString (const LNString & imageName);

	LNSTATUS SetImagePlacement (const LNCELLIMAGEPLACEMENT placement);

	LNSTATUS SetLeftBorderType(const LNCELLBORDERTYPE border);
	
	LNSTATUS SetLeftBorderWidth(LNINT width = 1);

	LNSTATUS SetRightBorderType(const LNCELLBORDERTYPE border);

	LNSTATUS SetRightBorderWidth(LNINT width = 1);
	
	LNSTATUS SetTopBorderType(const LNCELLBORDERTYPE border);

	LNSTATUS SetTopBorderWidth(LNINT width = 1);

	LNSTATUS SetTransitionEffect (LNTRANSITIONEFFECT effect);

	LNSTATUS SetTransparent(LNBOOL transparent = TRUE);

	LNSTATUS SetVerticalAlignment (LNCELLALIGNMENT align);

protected:

	LNTableCell(LNTableCellBody *body);

	LNTableCell& operator=(LNTableCellBody *body);

	LNTableCellBody* GetTableCellBody() const;

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



class LNIMPEXPCL LNTable : public LNRTContainer
{

public:
	LNSTATUS SetLeftMarginPercent(LNINT leftMargin);
	LNNUMBER GetRightMargin();
	LNSTATUS SetRightMarginPercent(LNINT rightMargin);
	LNSTATUS SetRightMargin(const LNNUMBER &rightMargin);

	LNTable();	

	~LNTable();
	
	LNTable(const LNRTObject &object);
	LNTable(const LNTable &table);
	LNTable(LNINT rows, LNINT cols);

	LNTable& operator=(const LNRTObject &object);
	LNTable& operator=(const LNTable &table);

	//	Returns the specified table cell object. 
	//	The row and column are zero-based, where (0,0) is the top left table cell.
	LNTableCell operator() (LNINT row, LNINT column);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convert = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, 
		LNRTObject *newObject = 0);

	LNSTATUS AppendColumns(LNINT count);

	//	Appends one or more columns or rows to the table. 
	//	The optional parameter is the number of columns/rows to append.
	LNSTATUS AppendRows(LNINT count);

	LNSTATUS DeleteColumns(LNINT column, LNINT count = 1);
	
	//	Deletes one or more columns or rows and their data from the table, 
	//	starting with the specified column/row. The first parameter is the 
	//	zero-based column/row number. The second optional parameter is the 
	//	number of columns/rows to delete.
	LNSTATUS DeleteRows(LNINT row, LNINT count = 1);

	LNColor GetAlternateColor () const;

	//	Returns TRUE if the table width is automatically computed by 
	//	Notes (if the table size is automatically fit to the window size).
	LNBOOL GetAutomaticWidth() const;

	LNTABLEBORDERSTYLE GetBorderStyle() const
		{ return GetCellBorderStyle(); }

	LNINT GetBottomBorderWidth() const;
	LNINT GetLeftBorderWidth() const;
	LNINT GetRightBorderWidth() const;
	LNINT GetTopBorderWidth() const;

	LNINT GetBottomInsideBorderWidth() const;
	LNINT GetLeftInsideBorderWidth() const;
	LNINT GetRightInsideBorderWidth() const;
	LNINT GetTopInsideBorderWidth() const;

	LNINT GetBottomOutsideBorderWidth() const;
	LNINT GetLeftOutsideBorderWidth() const;
	LNINT GetRightOutsideBorderWidth() const;
	LNINT GetTopOutsideBorderWidth() const;

	LNSTATUS GetCDTableBegin(CDTABLEBEGIN *tablebegin) const;

	LNSTATUS GetCDTableEnd(CDTABLEEND *tableend) const;

	LNColor GetCellBorderColor () const;

	LNCELLBORDERSTYLE GetCellBorderStyle() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTABLE; }

	LNColor GetColor () const;

	LNTABLECOLORSTYLE GetColorStyle () const;

	LNINT GetColumnCount() const;
	
	LNNUMBER GetColumnSpacing(); 
	
 	//	The first parameter is the zero-based column number. The optional second 
	//	parameter specifies the units of measurement. See LNUNITS () for more information.
	LNNUMBER GetColumnWidth(LNINT column);

	LNBOOL GetDropShadow() const;

	LNINT GetDropShadowWidth() const;

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNBOOL GetIsColumnWidthFixed(const LNINT column) const;

	//	Returns the left margin setting in the specified units.  
	//	See LNUNITS () for more information.
	LNNUMBER GetLeftMargin();
	
	LNNUMBER GetMinimumRowHeight() const;
	
	LNINT GetRowCount() const;

	LNTABLEROWDISPLAY GetRowDisplay (void) const;

	LNString GetRowName ( const LNINT row) const;

	LNSTATUS GetRowSelectionFormula (LNFormula * pFormula) const;
	LNSTATUS GetRowSelectionString (LNString * pString) const;

	LNNUMBER GetRowSpacing();

	LNString GetRowTabLabel (LNINT row) const;

	LNINT GetRowTimeInterval () const;

	LNColor GetTableBorderColor() const;

	LNTABLEBORDERSTYLE GetTableBorderStyle() const;

	LNString GetTableName (void) const;

	LNUNITS	GetUnits() const;

	LNBOOL GetUseR4Spacing() const;

	LNTABLEWIDTHTYPE GetWidthType() const;

	LNBOOL GetWrapTextAroundTable() const;

	LNBOOL GetWrapTextBetweenCells() const;

	LNNUMBER GetWrapTextBetweenCellsHeight() const;

	LNSTATUS InsertColumns(LNINT column, LNINT count = 1);
	
	//	Inserts one or more columns or rows in the table, before the specified column/row. 
	//	The first parameter is the zero-based column/row number. The optional 
	//	second parameter is the number of columns/rows to insert.
	LNSTATUS InsertRows(LNINT row, LNINT count = 1);

	LNBOOL IsRowSelectionString (void) const;
	LNBOOL IsRowSelectionFormula (void) const;

	LNSTATUS MergeCells (LNINT row1, LNINT col1, LNINT row2, LNINT col2);
	LNSTATUS MergeCells (LNTableCell &cell1, LNTableCell &cell2);

	LNSTATUS Outline(LNCELLBORDERTYPE style);
	LNSTATUS Outline(LNCELLBORDERSTYLE style = LNCELLBORDERSTYLE_SOLID);

	LNSTATUS SetAllBorderWidths( LNINT width );
	LNSTATUS SetBottomBorderWidth( LNINT width );
	LNSTATUS SetLeftBorderWidth( LNINT width );
	LNSTATUS SetRightBorderWidth( LNINT width );
	LNSTATUS SetTopBorderWidth( LNINT width );

	LNSTATUS SetAllInsideBorderWidths( LNINT width );
	LNSTATUS SetBottomInsideBorderWidth( LNINT width );
	LNSTATUS SetLeftInsideBorderWidth( LNINT width );
	LNSTATUS SetRightInsideBorderWidth( LNINT width );
	LNSTATUS SetTopInsideBorderWidth( LNINT width );

	LNSTATUS SetAllOutsideBorderWidths( LNINT width );
	LNSTATUS SetBottomOutsideBorderWidth( LNINT width );
	LNSTATUS SetLeftOutsideBorderWidth( LNINT width );
	LNSTATUS SetRightOutsideBorderWidth( LNINT width );
	LNSTATUS SetTopOutsideBorderWidth( LNINT width );

	LNSTATUS SetAlternateColor (const LNColor & color);

	//	Modifies automatic width computation flag.  TRUE fits the table to the window size.
	LNSTATUS SetAutomaticWidth(const LNBOOL flag);
	
	LNSTATUS SetBackgroundColor(const LNColor & color);

	LNSTATUS SetBorderStyle(LNTABLEBORDERSTYLE newStyle)
		{ return SetCellBorderStyle(newStyle); }

	LNSTATUS SetCellBorderColor (const LNColor & color);

	LNSTATUS SetCellBorderStyle(LNCELLBORDERSTYLE newStyle);

	LNSTATUS SetColor (const LNColor & color);

	LNSTATUS SetColorStyle (LNTABLECOLORSTYLE style);

	LNSTATUS SetColumnSpacing(const LNNUMBER &spacing);
	
	//	The first parameter is the zero-based column number. The second parameter is the new width. 
	//	If automatic width is set, this function does nothing and returns a warning.
	LNSTATUS SetColumnWidth(LNINT column, const LNNUMBER &width);

	void SetDropShadow( LNBOOL flag );

	LNSTATUS SetDropShadowWidth( LNINT width );

	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	LNSTATUS SetIsColumnWidthFixed(const LNINT column, const LNBOOL newFlag);
	
	//	Modifies the left margin setting. The first parameter is the new margin. 
	//	This function returns an error if the specified margin is out of range.
	LNSTATUS SetLeftMargin(const LNNUMBER &margin);
	
	LNSTATUS SetMinimumRowHeight( const LNNUMBER &height );

	LNSTATUS SetRowDisplay ( const LNTABLEROWDISPLAY type);
	
	LNSTATUS SetRowName ( const LNINT row, const LNString name);
	
	LNSTATUS SetRowSelectionString ( const LNString & rowTag );
	LNSTATUS SetRowSelectionFormula ( const LNFormula & rowFormula );

	//	Gets or Sets the spacing between columns in the specified units., 
	//	as defined by LNUITS enum.
	LNSTATUS SetRowSpacing(const LNNUMBER &spacing);

	LNSTATUS SetRowTabLabel (const LNINT row, const LNString &label);

	LNSTATUS SetRowTimeInterval (LNINT interval);
	
	LNSTATUS SetTableBorderColor( const LNColor &color );

	LNSTATUS SetTableBorderStyle( LNTABLEBORDERSTYLE style );

	LNSTATUS SetTableName ( const LNString & name );

	//	Turns off the background color in every table cell in this table. 
	//	This function is only supported for Notes versions 4.5 and later.
	LNSTATUS SetTransparent(const LNBOOL newFlag = TRUE);

	void SetUnits(const LNUNITS units);

	void SetUseR4Spacing( LNBOOL flag );

	LNSTATUS SetWidthType( LNTABLEWIDTHTYPE type );

	void SetWrapTextAroundTable( LNBOOL flag );

	void SetWrapTextBetweenCells( LNBOOL flag );

	LNSTATUS SetWrapTextBetweenCellsHeight( const LNNUMBER &height );

	LNSTATUS SplitCells (LNINT row1, LNINT col1, LNINT row2, LNINT col2);
	LNSTATUS SplitCells (LNTableCell &cell1, LNTableCell &cell2);

protected:

	LNTable(LNTableBody *body);

	LNTable& operator=(LNTableBody *body);

	LNTableBody* GetTableBody() const; 

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNNUMBER Convert(LNINT twips) const;
	LNINT Convert(const LNNUMBER &number) const;
};

#endif

