//===========================================================================
//
// Module:		LNFORMFA.HPP
//
// Description:
//
//		Class library definitions for LNFormFieldArray related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNFORMFA_HPP
#define LNFORMFA_HPP

//
//	Class definition for LNFormFieldArray.
//
class LNIMPEXPCL LNFormFieldArray : public LNSmartPtr
{

public:
	LNFormFieldArray();
	LNFormFieldArray( const LNFormFieldArray &other );

	~LNFormFieldArray();

	LNFormFieldArray & operator=( const LNFormFieldArray &other );

	LNFormField operator[]( LNINT n ) const;

	LNCLASSID GetClassID() const {return LNCLASSID_LNFORMFIELDARRAY;}

	LNINT GetCount() const;

	LNForm GetForm() const {return Form;}

private:
	void Assign( LNFormBody *formb, LNFormFieldArrayBody *Fieldab );

	LNForm Form;
};

#endif
