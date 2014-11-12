//===========================================================================
//
// Module:  LNPARSTL.HPP
//
// Description:
//
//  Class library definition for LNNamedStyle and related paragraph classes.
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNPARSTL_HPP
#define LNPARSTL_HPP




class LNIMPEXPCL LNNamedStyle : public LNParagraphStyle
{


public:
	
	LNNamedStyle();

	LNNamedStyle(const LNString &name);
	
	LNNamedStyle(const LNString &name, const LNParagraphStyle &style);

	LNNamedStyle(const LNString &name, const LNParagraphStyle &style, const LNFontStyle &fontstyle);
	
	LNNamedStyle(const LNParagraphStyle &style);
	LNNamedStyle(const LNNamedStyle &other);
	
	~LNNamedStyle();
	
	LNNamedStyle& operator=(const LNParagraphStyle &style);
	LNNamedStyle& operator=(const LNNamedStyle &other);

	LNSTATUS AssignToCycleList();

	virtual LNSTATUS Copy(const LNParagraphStyle &other);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNNAMEDSTYLE; }

	LNSTATUS GetFontStyle(LNFontStyle *fontstyle) const;

	LNBOOL GetIsAvailableToAllDocuments() const;

	LNString GetName() const;

	LNString GetUserName() const;

	LNBOOL HasFontStyle() const;

	LNBOOL IsOnCycleList() const;

	LNSTATUS Redefine(const LNParagraphStyle &style);

	LNSTATUS RemoveFromCycleList();

	virtual LNSTATUS SetDefaults();

	LNSTATUS SetFontStyle(const LNFontStyle &fontstyle);

	LNSTATUS SetIsAvailableToAllDocuments(LNBOOL alldocs);

	LNSTATUS SetName(const LNString &name);

protected:

	LNNamedStyle(LNNamedStyleBody *body);

	LNNamedStyle& operator=(LNNamedStyleBody *body);

	LNNamedStyleBody* GetNamedStyleBody() const { return (LNNamedStyleBody *) Body; }

	LNBOOL IsEqual(const LNPABDefinition &pabdef, const LNPABStyleName &stylename) const;
};


#endif

