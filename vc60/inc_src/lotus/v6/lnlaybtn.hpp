//===========================================================================
//
// Module:		LNLAYBTN.HPP
//
// Description:
//
//		Class library definition for the LNLayoutButton class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYBTN_HPP
#define LNLAYBTN_HPP

class LNIMPEXPCL LNLayoutButton : public LNLayoutElement
{

public:
	
	LNLayoutButton();
	LNLayoutButton(const LNRTObject &object);
	LNLayoutButton(const LNLayoutButton &layout);

	LNLayoutButton (const LNButton & button);

	LNLayoutButton (const LNString & label, const LNFormula & formula);
	LNLayoutButton (const LNString & label, const LNSimpleAction & action);
	LNLayoutButton (const LNString & label, const LNSimpleActions & actions);
	LNLayoutButton (const LNString & label, const LNLotusScript & script);

	~LNLayoutButton();

	LNLayoutButton & operator=(const LNRTObject &object);
	LNLayoutButton & operator=(const LNLayoutButton &layout);

	LNALIGNMENT GetAlignment () const;

	LNSTATUS GetButton (LNButton * pButton) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTBUTTON; }

	LNSTATUS GetHTMLTags(LNHTMLTags * pTags) const;

	LNBOOL GetRTLReadingOrder () const;

	LNSTATUS SetAlignment (LNALIGNMENT alignment);

	LNSTATUS SetButton(const LNButton & button);

	virtual LNSTATUS SetFontStyle (const LNFontStyle & style);

	LNSTATUS SetHTMLTags(const LNHTMLTags & tags);

	LNSTATUS SetRTLReadingOrder (LNBOOL rtl = TRUE);

protected:

	LNLayoutButtonBody* GetLayoutButtonBody () const { return (LNLayoutButtonBody *) Body; }

private:	
	LNLayoutButton(LNLayoutButtonBody *body);

	LNLayoutButton& operator=(LNLayoutButtonBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

