//===========================================================================
//
// Module:  LNURLLNK.HPP
//
// Description:
//
//  Class library definition for LNURLLink and related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNURLLNK_HPP
#define LNURLLNK_HPP

#include "editdflt.h"

//  The value is HOTSPOTREC_RUNFLAG_INIT_DONE, defined in edit\hmem.h in the
//  core sources.  It indicates that the hotspot has been fully initialized
//  inside Notes, and is not supposed to be written to disk (but it is!).

#ifndef HOTSPOTREC_RUNFLAG_INIT_DONE
#define	HOTSPOTREC_RUNFLAG_INIT_DONE	0x10000000L
#endif


class LNIMPEXPCL LNURLLink : public LNHotspot
{

public:
	
	LNURLLink();

	LNURLLink(const LNRTObject &other);
	LNURLLink(const LNURLLink &URL);
	
	LNURLLink(const LNString &URL, const LNString &text);
	LNURLLink(const LNString &URL, const LNGraphic &graphic);

	~LNURLLink();
	
	LNURLLink& operator=(const LNRTObject &other);
	LNURLLink& operator=(const LNURLLink &URL);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNURLLINK; }

	LNSTATUS GetHTMLTags(LNHTMLTags *tags) const;
	
	LNSTATUS GetTargetFrame(LNString *framename) const;

	LNString GetURL() const;

	LNSTATUS GetURLFormula(LNFormula *formula) const;

	LNBOOL IsURLFormula() const;

	LNSTATUS SetHTMLTags(const LNHTMLTags &tags);

	LNSTATUS SetTargetFrame(const LNString &framename);

	LNSTATUS SetURL(const LNString &URL);
	
	LNSTATUS SetURLFormula(const LNFormula &formula);

protected:

	LNURLLink(LNResourceLinkBody *body);

	LNURLLink(const LNString &URL);
	LNURLLink(LNFormula &URLFormula);

	LNURLLink& operator=(LNResourceLinkBody *body);

    LNResourceLinkBody* GetResourceLinkBody() const { return (LNResourceLinkBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};

#endif

