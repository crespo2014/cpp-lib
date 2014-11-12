//===========================================================================
//
// Module:  LNHOTLNK.HPP
//
// Description:
//
//  Class library definition for LNLinkHotspot and related classes.
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNHOTLNK_HPP
#define LNHOTLNK_HPP

class LNIMPEXPCL LNLinkHotspot : public LNHotspot
{

public:
	
	LNLinkHotspot();

	LNLinkHotspot(const LNRTObject &other);
	LNLinkHotspot(const LNLinkHotspot &other);
	
	LNLinkHotspot(const LNDatabaseLink &link, const LNString &text);
	LNLinkHotspot(const LNDatabaseLink &link, const LNGraphic &graphic);
	LNLinkHotspot(const LNNamedElement &namedelement, const LNString &text);
	LNLinkHotspot(const LNNamedElement &namedelement, const LNGraphic &graphic);

	~LNLinkHotspot();
	
	LNLinkHotspot& operator=(const LNRTObject &other);
	LNLinkHotspot& operator=(const LNLinkHotspot &other);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNLINKHOTSPOT; }

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS GetLink(LNDatabaseLink *link) const;

	LNSTATUS GetNamedElement(LNNamedElement *namedelement) const; 
	
	LNSTATUS GetTargetFrame(LNString *framename) const;

	LNBOOL IsNamedElement() const;  

	LNSTATUS SetNamedElement(const LNNamedElement &namedelement);

	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	LNSTATUS SetTargetFrame(const LNString &framename);

	LNSTATUS SetLink(const LNDatabaseLink &link);

protected:

	LNLinkHotspot(const LNDatabaseLink &link);

	LNLinkHotspot(const LNNamedElement &namedelement);

	LNLinkHotspot(LNResourceLinkBody *body);

	LNLinkHotspot& operator=(LNResourceLinkBody *body);

	LNResourceLinkBody* GetResourceLinkBody() const { return (LNResourceLinkBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};

#endif

