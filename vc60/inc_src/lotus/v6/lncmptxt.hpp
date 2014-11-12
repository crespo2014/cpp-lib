//===========================================================================
//
// Module:  LNTXTPUP.HPP
//
// Description:
//
//  Class library definition for LNTextPopup and LNTextPopupBody.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNCOMPTEXT_HPP
#define LNCOMPTEXT_HPP


class LNIMPEXPCL LNComputedText : public LNHotspot
{

public:
	
	LNComputedText();

	LNComputedText(const LNRTObject &other);
	LNComputedText(const LNComputedText &computedText);
	
	LNComputedText(const LNFormula &formula);

	~LNComputedText();
	
	LNComputedText& operator=(const LNRTObject &other);
	LNComputedText& operator=(const LNComputedText &computedText);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNCOMPUTEDTEXT; }

	LNSTATUS GetFontStyle(LNFontStyle *style);

	LNSTATUS GetFormula(LNFormula *formula) const;

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS SetFontStyle(const LNFontStyle &style);

	LNSTATUS SetFormula(const LNFormula &formula);

	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

protected:

	LNComputedText(LNComputedTextBody *body);

	LNComputedText& operator=(LNComputedTextBody *body);

    LNComputedTextBody* GetComputedTextBody() const { return (LNComputedTextBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

