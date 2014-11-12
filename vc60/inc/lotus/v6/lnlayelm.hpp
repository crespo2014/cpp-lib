//===========================================================================
//
// Module:		LNLAYELM.HPP
//
// Description:
//
//		Class library definition for the LNLayoutElement class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYELM_HPP
#define LNLAYELM_HPP

class LNIMPEXPCL LNLayoutElement : public LNRTElement
{

public:
	
	LNLayoutElement();
	LNLayoutElement(const LNRTObject &object);
	LNLayoutElement(const LNLayoutElement &layout);

	~LNLayoutElement();

	LNLayoutElement& operator=(const LNRTObject &object);
	LNLayoutElement& operator=(const LNLayoutElement &layout);

	LNColor GetBackgroundColor () const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTELEMENT; }

	LNSTATUS GetFontStyle (LNFontStyle * pStyle) const;

	LNNUMBER GetHeight () const;

	LNNUMBER GetLeftMargin () const;

	LNNUMBER GetTop () const;

	LNUNITS GetUnits() const;

	LNNUMBER GetWidth() const;

	LNSTATUS SetBackgroundColor (const LNColor & color);

	virtual LNSTATUS SetFontStyle (const LNFontStyle & style);

	LNSTATUS SetHeight(LNNUMBER height);

	LNSTATUS SetLeftMargin (LNNUMBER margin);

	LNSTATUS SetPosition(LNPOSITION position);

	LNSTATUS SetTop (LNNUMBER top);

	LNSTATUS SetUnits(LNUNITS units);

	LNSTATUS SetWidth(LNNUMBER width);

protected:
	LNLayoutElement(LNLayoutElementBody *body);

	LNLayoutElement& operator=(LNLayoutElementBody *body);

	LNLayoutElementBody* GetLayoutElementBody () const { return (LNLayoutElementBody *) Body; }

private:	
	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

