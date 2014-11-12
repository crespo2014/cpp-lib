//===========================================================================
//
// Module:		LNLAYGRA.HPP
//
// Description:
//
//		Class library definition for the LNLayoutGraphic class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYGRA_HPP
#define LNLAYGRA_HPP

class LNIMPEXPCL LNLayoutGraphic : public LNLayoutElement
{

public:
	
	LNLayoutGraphic();
	LNLayoutGraphic(const LNRTObject &object);
	LNLayoutGraphic(const LNLayoutGraphic &layout);

	LNLayoutGraphic (const LNGraphic & graphic);

	~LNLayoutGraphic();

	LNLayoutGraphic & operator=(const LNRTObject &object);
	LNLayoutGraphic & operator=(const LNLayoutGraphic &layout);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTGRAPHIC; }

	LNSTATUS GetGraphic(LNGraphic * pGraphic) const;

	LNSTATUS GetHTMLTags(LNHTMLTags * pTags) const;

	LNSTATUS SetGraphic(const LNGraphic & graphic);

	LNSTATUS SetHTMLTags(const LNHTMLTags & tags);

protected:

	LNLayoutGraphicBody* GetLayoutGraphicBody () const { return (LNLayoutGraphicBody *) Body; }

private:	
	LNLayoutGraphic(LNLayoutGraphicBody *body);

	LNLayoutGraphic& operator=(LNLayoutGraphicBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

