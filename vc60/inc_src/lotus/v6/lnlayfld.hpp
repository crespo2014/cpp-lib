//===========================================================================
//
// Module:		LNLAYFLD.HPP
//
// Description:
//
//		Class library definition for the LNLayoutField class.
//
//===========================================================================
//
// Copyright (c) 2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLAYFLD_HPP
#define LNLAYFLD_HPP

class LNIMPEXPCL LNLayoutField : public LNLayoutElement
{

public:
	
	LNLayoutField();
	LNLayoutField(const LNRTObject &object);
	LNLayoutField(const LNLayoutField &layout);

	LNLayoutField (const LNFormField & text);
	LNLayoutField (const LNString & name, LNRTTYPE fieldType);

	~LNLayoutField();

	LNLayoutField & operator=(const LNRTObject &object);
	LNLayoutField & operator=(const LNLayoutField &layout);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLAYOUTFIELD; }

	LNSTATUS GetFormField (LNFormField * pField) const;

	LNSTATUS GetHTMLTags(LNHTMLTags * pTags) const;

	LNBOOL GetRTLReadingOrder () const;

	LNSTATUS SetFormField (const LNFormField & text);

	LNSTATUS SetHTMLTags(const LNHTMLTags & tags);

	LNSTATUS SetRTLReadingOrder (LNBOOL rtl = TRUE);

protected:

	LNLayoutFieldBody* GetLayoutFieldBody () const { return (LNLayoutFieldBody *) Body; }

private:	
	LNLayoutField(LNLayoutFieldBody *body);

	LNLayoutField& operator=(LNLayoutFieldBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

