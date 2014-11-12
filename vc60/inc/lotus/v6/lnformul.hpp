//===========================================================================
//
// Module:	LNFORMUL.HPP
//
// Description:
//
//		Class definitions for LNFormula and LNFormulaBody.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNFORMUL_HPP
#define LNFORMUL_HPP

#include <nsfsearc.h>	// for HCOMPUTE

// LNFORMULAFLAGS: flags returned by LNFormula::Evaluate.

typedef WORD LNFORMULAFLAGS;

#define LNFORMULAFLAGS_NOTE_SELECTED	0x0001
#define LNFORMULAFLAGS_DELETE_NOTE		0x0002
#define LNFORMULAFLAGS_NOTE_MODIFIED	0x0004

//---------------------------------------------------------------------------
// 	Class name:	LNFormula
//
//	Description:
//
//	LNFormula represents a Notes formula.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNFormula : public LNSmartPtr
{
public:
	LNFormula() {}
	LNFormula( const LNString &text ) { Init(text); }
	LNFormula( const char *text ) { Init(text); }
	LNFormula( const char *code, LNINT length, LNBOOL select = FALSE );
	LNFormula( const LNFormula &formula ) : LNSmartPtr(formula) {}
	~LNFormula() {}
	LNFormula & operator=( const LNFormula &formula )
		{ LNSmartPtr::operator=(formula); return *this; }
	LNFormula & operator=( const LNString &text );
	LNFormula & operator=( const char *text )
		{ return operator=(LNString(text)); }

	LNCLASSID GetClassID() const { return LNCLASSID_LNFORMULA; }

	LNSTATUS Evaluate( LNItem *result ) const;
	LNSTATUS Evaluate
		( LNItem *result, const LNNote &note, LNFORMULAFLAGS *flags = 0 ) const;
	char * GetCode() const;
	LNINT GetCodeLength() const;
	LNString GetText() const;
	LNSTATUS SetCode( const char *code, LNINT length, LNBOOL select = FALSE );
	LNSTATUS SetText
		( const LNString &text, LNINT *erroffset = 0, LNINT *errlength = 0 );

private:
	LNFormulaBody * GetFormulaBody() const { return (LNFormulaBody *) Body; }
	FORMULAHANDLE GetCodeHandle() const;
	void Init( const LNString &text );
};


#endif	// LNFORMUL_HPP

