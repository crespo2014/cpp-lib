//===========================================================================
//
// Module:		LNLAYTXT.HPP
//
// Description:
//
//		Class library definition for the LNLayoutText class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYTXT_HPP
#define LNLAYTXT_HPP

class LNIMPEXPCL LNLayoutText : public LNLayoutElement
{

public:
	
	LNLayoutText();
	LNLayoutText(const LNRTObject &object);
	LNLayoutText(const LNLayoutText &layout);

	LNLayoutText (const LNString & string);
	LNLayoutText (const LNStylizedText & text);

	~LNLayoutText();

	LNLayoutText & operator=(const LNRTObject &object);
	LNLayoutText & operator=(const LNLayoutText &layout);

	LNALIGNMENT GetAlignment () const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTTEXT; }

	LNBOOL GetRTLReadingOrder () const;

	LNSTATUS GetStylizedText (LNStylizedText * pText) const;

	LNSTATUS GetText (LNString * pText) const;

	LNBOOL GetTransparent () const;

	LNBOOL GetVerticalCenter () const;

	LNSTATUS SetAlignment (LNALIGNMENT alignment);

	virtual LNSTATUS SetFontStyle (const LNFontStyle & style);

	LNSTATUS SetRTLReadingOrder (LNBOOL rtl = TRUE);

	LNSTATUS SetStylizedText (const LNStylizedText & text);

	LNSTATUS SetText (const LNString & text);

	LNSTATUS SetTransparent (LNBOOL transparent = TRUE);

	LNSTATUS SetVerticalCenter (LNBOOL center = TRUE);

protected:

	LNLayoutTextBody* GetLayoutTextBody () const { return (LNLayoutTextBody *) Body; }

private:	
	LNLayoutText(LNLayoutTextBody *body);

	LNLayoutText& operator=(LNLayoutTextBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

