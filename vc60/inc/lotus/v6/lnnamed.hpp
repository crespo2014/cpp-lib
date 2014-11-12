//===========================================================================
//
// Module:	LNNAMED.HPP
//
// Description:
//
//	Class declarations of the LNNamedElement class
//
//===========================================================================
//
// Copyright (c) 2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNNAMED_HPP
#define LNNAMED_HPP

class LNIMPEXPCL LNNamedElement : public LNNotesClass
{
	public:

	// Constructors
	LNNamedElement();
	LNNamedElement(const LNNamedElement &namedelement);
	LNNamedElement(const LNString &name, LNNAMEDELEMENT type, TIMEDATE *replicaID = 0);
	LNNamedElement(const LNString &name, LNNAMEDELEMENT type, LNNAMEDELEMENTDB specialDb );
	LNNamedElement(const LNFormula &formula, LNNAMEDELEMENT type);
	LNNamedElement(const LNString &name, LNNAMEDELEMENT type, LNDatabase &db);
	~LNNamedElement(){}

	LNNamedElement& operator=(const LNNamedElement &namedelement);
	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNNAMEDELEMENT; }

	LNBOOL IsFormula() const { return IsFormulaElement;}

	LNSTATUS GetName( LNString *name ) const;
	LNSTATUS SetName( const LNString &name);

	LNSTATUS GetFormula(LNFormula *formula ) const;
	LNSTATUS SetFormula(const LNFormula &formula);

	LNNAMEDELEMENT GetType( ) const { return Type; }
	LNSTATUS SetType( LNNAMEDELEMENT type) { Type = type; return LNNOERROR; }

	LNSTATUS GetReplicaID(TIMEDATE *replicaID) const;
	LNSTATUS SetReplicaID( TIMEDATE replicaID);

	LNSTATUS GetNamedElementDatabase( LNNAMEDELEMENTDB *specialdb ) const;
	LNSTATUS SetNamedElementDatabase( LNNAMEDELEMENTDB specialdb );

	protected:
	private:
	LNBOOL IsWildcardDatabase() const { return IsWildcardDb;}

    LNBOOL IsWildcardDb;
	LNBOOL IsFormulaElement;

    LNString Name;
	LNFormula Formula;
	LNNAMEDELEMENT Type;
	TIMEDATE ReplicaID;
	LNNAMEDELEMENTDB Database;
};
 
#endif

