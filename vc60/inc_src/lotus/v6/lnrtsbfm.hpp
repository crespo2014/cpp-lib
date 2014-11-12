//===========================================================================
//
// Module:  LNRTSBFM.HPP
//
// Description:
//
//  Class library definition for LNRTSubform and related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTSBFM_HPP
#define LNRTSBFM_HPP


#include "lnsbform.hpp"


class LNIMPEXPCL LNRTSubform : public LNRTElement
{

public:
	
	LNRTSubform();

	LNRTSubform(const LNRTObject &other);
	LNRTSubform(const LNRTSubform &other);
	
	~LNRTSubform();
	
	LNRTSubform& operator=(const LNRTObject &other);
	LNRTSubform& operator=(const LNRTSubform &other);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTSUBFORM; }

	LNString GetName() const;

	LNSTATUS GetSubform(LNSubform *subform) const;

private:

	LNSTATUS Expand();

	LNRTSubform(LNRTSubformBody *body);
	LNRTSubform(const LNSubform &subform);
	LNRTSubform(const LNString &subformname);

	LNRTSubform& operator=(LNRTSubformBody *body);

	LNRTSubformBody* GetRTSubformBody() const { return (LNRTSubformBody *) Body; }

	LNSTATUS SetSubform(LNSubform *subform);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


class LNIMPEXPCL LNRTComputedSubform : public LNRTElement
{

public:
	
	LNRTComputedSubform();

	LNRTComputedSubform(const LNRTObject &other);
	LNRTComputedSubform(const LNRTComputedSubform &other);
	
	LNRTComputedSubform(const LNFormula &formula);

	~LNRTComputedSubform();
	
	LNRTComputedSubform& operator=(const LNRTObject &other);
	LNRTComputedSubform& operator=(const LNRTComputedSubform &other);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTCOMPUTEDSUBFORM; }

	LNSTATUS GetFormula(LNFormula *formula) const;

	LNSTATUS SetFormula(const LNFormula &formula);

protected:

	LNRTComputedSubform(LNRTSubformBody *body);

	LNRTComputedSubform& operator=(LNRTSubformBody *body);

	LNRTSubformBody* GetRTSubformBody() const { return (LNRTSubformBody *) Body; }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

