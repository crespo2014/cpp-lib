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

#ifndef LNTXTPOPUP_HPP
#define LNTXTPOPUP_HPP


class LNIMPEXPCL LNTextPopup : public LNHotspot
{

public:
	
	LNTextPopup();

	LNTextPopup(const LNRTObject &other);
	LNTextPopup(const LNTextPopup &popup);
	
	LNTextPopup(const LNString &popupText, const LNString &text);
	LNTextPopup(const LNString &popupText, const LNGraphic &graphic);

	~LNTextPopup();
	
	LNTextPopup& operator=(const LNRTObject &other);
	LNTextPopup& operator=(const LNTextPopup &popup);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNTEXTPOPUP; }

	LNString GetPopupText() const;

	LNSTATUS SetPopupText(const LNString &popupText);

protected:

	LNTextPopup(LNTextPopupBody *body);

	LNTextPopup(const LNString &popupText);

	LNTextPopup& operator=(LNTextPopupBody *body);

    LNTextPopupBody* GetTextPopupBody() const { return (LNTextPopupBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



#endif

