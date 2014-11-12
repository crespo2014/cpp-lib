//===========================================================================
//
// Module:		LNLAYOUT.HPP
//
// Description:
//
//		Class library definition for the LNLayout class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYOUT_HPP
#define LNLAYOUT_HPP


class LNIMPEXPCL LNLayout : public LNRTContainer
{

public:
	
	LNLayout();
	LNLayout(const LNRTObject &object);
	LNLayout(const LNLayout &layout);

	~LNLayout();

	LNLayout& operator=(const LNRTObject &object);
	LNLayout& operator=(const LNLayout &layout);

	LNSTATUS CreateLayoutButton (const LNString & label, const LNSimpleActions & actions,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutButton * pButton = NULL);
	LNSTATUS CreateLayoutButton (const LNString & label, const LNSimpleAction & action,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutButton * pButton = NULL);
	LNSTATUS CreateLayoutButton (const LNString & label, const LNFormula & formula,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutButton * pButton = NULL);
	LNSTATUS CreateLayoutButton (const LNString & label, const LNLotusScript & script,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutButton * pButton = NULL);
	LNSTATUS CreateLayoutButton (const LNButton & button, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNNUMBER width, LNNUMBER height,
		LNLayoutButton * pButton = NULL);

	LNSTATUS CreateLayoutField (const LNString & name, LNRTTYPE type,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutField * pField = NULL);
	LNSTATUS CreateLayoutField (const LNFormField & templateField,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNNUMBER width, LNNUMBER height, LNLayoutField * pField = NULL);

	LNSTATUS CreateLayoutGraphic (const LNGraphic & graphic, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNLayoutGraphic * pGraphic = NULL);

	LNSTATUS CreateLayoutGraphicButton (const LNGraphic & graphic,
		const LNSimpleActions & actions, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNLayoutGraphicButton * pButton = NULL);
	LNSTATUS CreateLayoutGraphicButton (const LNGraphic & graphic,
		const LNSimpleAction & action, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNLayoutGraphicButton * pButton = NULL);
	LNSTATUS CreateLayoutGraphicButton (const LNGraphic & graphic,
		const LNFormula & formula, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNLayoutGraphicButton * pButton = NULL);
	LNSTATUS CreateLayoutGraphicButton (const LNGraphic & graphic,
		const LNLotusScript & script, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNLayoutGraphicButton * pButton = NULL);
	LNSTATUS CreateLayoutGraphicButton (const LNActionHotspot & templateHotspot,
		LNRTCursor * pCursor, LNNUMBER left, LNNUMBER top,
		LNLayoutGraphicButton * pButton = NULL);

	LNSTATUS CreateLayoutText (const LNString & text, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNNUMBER width, LNNUMBER height,
		LNLayoutText * pText);
	LNSTATUS CreateLayoutText (const LNStylizedText & text, LNRTCursor * pCursor,
		LNNUMBER left, LNNUMBER top, LNNUMBER width, LNNUMBER height,
		LNLayoutText * pText = NULL);

	LNALIGNMENT GetAlignment () const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUT; }

	LNNUMBER GetGridSize () const;

	LNNUMBER GetHeight () const;

	LNNUMBER GetLeftMargin () const;

	LNBOOL GetShowBorder () const;

	LNBOOL GetShowGrid () const;

	LNBOOL GetSnapToGrid () const;

	LNUNITS GetUnits() const;

	LNNUMBER GetWidth() const;

	LNBOOL GetWrapText () const;

	LNBOOL Get3DStyle () const;

	LNSTATUS SetAlignment (LNALIGNMENT newAlignment = LNALIGNMENT_LEFT);

	LNSTATUS SetGridSize (LNNUMBER size);

	LNSTATUS SetHeight(LNNUMBER height);

	LNSTATUS SetLeftMargin (LNNUMBER margin);

	LNSTATUS SetShowBorder (LNBOOL flag = TRUE);

	LNSTATUS SetShowGrid (LNBOOL flag = TRUE);

	LNSTATUS SetSnapToGrid (LNBOOL flag = TRUE);

	LNSTATUS SetUnits(LNUNITS units);

	LNSTATUS SetWidth(LNNUMBER width);

	LNSTATUS SetWrapText (LNBOOL wrap = TRUE);

	LNSTATUS Set3DStyle (LNBOOL style = TRUE);

protected:
	LNLayoutBody* GetLayoutBody () const { return (LNLayoutBody *) Body; }

private:	
	LNLayout(LNLayoutBody *body);

	LNLayout& operator=(LNLayoutBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

