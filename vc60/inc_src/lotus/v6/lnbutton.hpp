//==========================================================================================
//
// Module:	LNBUTTON.HPP
//
// Description
//
//  Class Library description for LNButton, LNButtonBody.
//
//==========================================================================================
//
// Copyright (c) 1998-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNBUTTON_HPP
#define LNBUTTON_HPP

#include "editdflt.h"

//  The value is HOTSPOTREC_RUNFLAG_INIT_DONE, defined in edit\hmem.h in the
//  core sources.  It indicates that the hotspot has been fully initialized
//  inside Notes, and is not supposed to be written to disk (but it is!).

#ifndef HOTSPOTREC_RUNFLAG_INIT_DONE
#define	HOTSPOTREC_RUNFLAG_INIT_DONE	0x10000000L
#endif


enum LNBUTTONWIDTHTYPE
{
LNBUTTONWIDTHTYPE_MAXIMUM,
LNBUTTONWIDTHTYPE_MINIMUM,
LNBUTTONWIDTHTYPE_FIXED,
LNBUTTONWIDTHTYPE_FIT_CONTENT
};


class LNIMPEXPCL LNButton : public LNRTElement
{

public:

	LNButton();
	LNButton(const LNRTObject &object);
	LNButton(const LNButton &button);

	LNButton(const LNString &label, const LNFormula &formula);
	LNButton(const LNString &label, const LNJavaScript &javascript);
	LNButton(const LNString &label, const LNSimpleAction &action);
	LNButton(const LNString &label, const LNSimpleActions &actions);
	LNButton(const LNString &label, const LNLotusScript &script);

	~LNButton();

	LNButton& operator=(const LNRTObject &object);
	LNButton& operator=(const LNButton &button);

	LNACTIONTYPE GetActionType() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNBUTTON; }

	LNSTATUS GetFormula(LNFormula *formula) const;

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS GetJavaScript(LNJavaScript *jsScript) const;

	LNString GetLabel() const;

	LNFontStyle GetLabelFontStyle() const;

	LNSTATUS GetLotusScript(LNLotusScript *script) const;

	LNSTATUS GetSimpleActions(LNSimpleActions *actions) const;

	LNUNITS GetUnits() const;

	LNNUMBER GetWidth() const;

	LNBUTTONWIDTHTYPE GetWidthType() const;

	LNBOOL GetWrapText() const;

	LNSTATUS SetFormula(const LNFormula &formula);

	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	LNSTATUS SetJavaScript(const LNJavaScript &jsScript);

	LNSTATUS SetLabel(const LNString &label);

	LNSTATUS SetLabelFontStyle(const LNFontStyle &fontstyle);

	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNSTATUS SetSimpleAction(const LNSimpleAction &action);

	LNSTATUS SetSimpleActions(const LNSimpleActions &actions);

	LNSTATUS SetUnits(LNUNITS units);

	LNSTATUS SetWidth(LNNUMBER number);

	LNSTATUS SetWidthType(LNBUTTONWIDTHTYPE widthtype);

	LNSTATUS SetWrapText(LNBOOL wraptext);

protected:

	LNButton(LNButtonBody *body);

	LNButton& operator=(LNButtonBody *body);

	LNButtonBody* GetButtonBody() const { return (LNButtonBody *) Body; }	

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



#endif

