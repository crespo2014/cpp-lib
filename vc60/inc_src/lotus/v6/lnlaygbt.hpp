//===========================================================================
//
// Module:		LNLAYGBT.HPP
//
// Description:
//
//		Class library definition for the LNLayoutGraphicButton class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYGBT_HPP
#define LNLAYGBT_HPP

class LNIMPEXPCL LNLayoutGraphicButton : public LNLayoutElement
{

public:
	
	LNLayoutGraphicButton();
	LNLayoutGraphicButton(const LNRTObject &object);
	LNLayoutGraphicButton(const LNLayoutGraphicButton &layout);

	LNLayoutGraphicButton (const LNActionHotspot & hotspot);

	LNLayoutGraphicButton (const LNGraphic & graphic, const LNFormula & formula);
	LNLayoutGraphicButton (const LNGraphic & graphic, const LNSimpleAction & action);
	LNLayoutGraphicButton (const LNGraphic & graphic, const LNSimpleActions & actions);
	LNLayoutGraphicButton (const LNGraphic & graphic, const LNLotusScript & script);

	~LNLayoutGraphicButton();

	LNLayoutGraphicButton & operator=(const LNRTObject &object);
	LNLayoutGraphicButton & operator=(const LNLayoutGraphicButton &layout);

	LNSTATUS GetActionHotspot (LNActionHotspot * pHotspot) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTGRAPHICBUTTON; }

	LNSTATUS GetHTMLTags(LNHTMLTags * pTags) const;

	LNSTATUS SetActionHotspot(const LNActionHotspot & hotspot);

	LNSTATUS SetHTMLTags(const LNHTMLTags & tags);

protected:

	LNLayoutGraphicButtonBody* GetLayoutGraphicButtonBody () const { return (LNLayoutGraphicButtonBody *) Body; }

private:	
	LNLayoutGraphicButton(LNLayoutGraphicButtonBody *body);

	LNLayoutGraphicButton& operator=(LNLayoutGraphicButtonBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

