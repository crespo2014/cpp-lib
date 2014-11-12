//===========================================================================
//
// Module:  LNFORMUP.HPP
//
// Description:
//
//  Class library definition for LNFormulaPopup and LNFormulaPopupBody.
//
//===========================================================================
//
// Copyright (c) 1998-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNFORMULAPOPUP_HPP
#define LNFORMULAPOPUP_HPP


class LNIMPEXPCL LNFormulaPopup : public LNHotspot
{

public:
	
	LNFormulaPopup();

	LNFormulaPopup(const LNRTObject &other);
	LNFormulaPopup(const LNFormulaPopup &popup);
	
	LNFormulaPopup(const LNFormula &formula, const LNString &text);
	LNFormulaPopup(const LNFormula &formula, const LNGraphic &graphic);

	~LNFormulaPopup();
	
	LNFormulaPopup& operator=(const LNRTObject &other);
	LNFormulaPopup& operator=(const LNFormulaPopup &popup);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNFORMULAPOPUP; }

	LNSTATUS GetFormula(LNFormula *formula) const;

	LNSTATUS SetFormula(const LNFormula &formula);

protected:

	LNFormulaPopup(LNFormulaPopupBody *body);

	LNFormulaPopup(const LNFormula &formula);

	LNFormulaPopup& operator=(LNFormulaPopupBody *body);

    LNFormulaPopupBody* GetFormulaPopupBody() const { return (LNFormulaPopupBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

