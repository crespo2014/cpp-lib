//===========================================================================
//
// Module:  LNSFIELD.HPP
//
// Description:
//
//		Class library definition for LNSimpleFieldValue and related classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSFIELD_HPP
#define LNSFIELD_HPP


//===========================================================================
//
//		Data types and constants
//
//===========================================================================

	// Operators for simple field actions
enum LNSIMPLEACTIONOPERATOR
{
	LNSIMPLEACTIONOPERATOR_UNKNOWN = 0,
	LNSIMPLEACTIONOPERATOR_REPLACE,
	LNSIMPLEACTIONOPERATOR_APPEND,
	LNSIMPLEACTIONOPERATOR_REMOVE
};

	// Operators for simple field searches
enum LNSIMPLESEARCHOPERATOR
{
	LNSIMPLESEARCHOPERATOR_UNKNOWN = 0,
	LNSIMPLESEARCHOPERATOR_CONTAINS,
	LNSIMPLESEARCHOPERATOR_DOES_NOT_CONTAIN,
	LNSIMPLESEARCHOPERATOR_IS_IN_THE_LAST,
	LNSIMPLESEARCHOPERATOR_IS_IN_THE_NEXT,
	LNSIMPLESEARCHOPERATOR_IS_OLDER_THAN,
	LNSIMPLESEARCHOPERATOR_IS_DUE_IN,
	LNSIMPLESEARCHOPERATOR_IS_BETWEEN,
	LNSIMPLESEARCHOPERATOR_IS_NOT_BETWEEN,
	LNSIMPLESEARCHOPERATOR_IS_EQUAL,
	LNSIMPLESEARCHOPERATOR_IS_NOT_EQUAL,
	LNSIMPLESEARCHOPERATOR_IS_GREATER,
	LNSIMPLESEARCHOPERATOR_IS_LESS
};

//===========================================================================
//
//		Class definition for LNSimpleFieldValue
//
//===========================================================================

class LNIMPEXPCL LNSimpleFieldValue : public LNSmartPtr
{

	public:
		LNSimpleFieldValue (void);
		LNSimpleFieldValue (const LNSimpleFieldValue & other);

		~LNSimpleFieldValue (void);

		LNSimpleFieldValue &operator= (const LNSimpleFieldValue & other);

		LNSIMPLEACTIONOPERATOR GetActionOperator (void) const;
		virtual LNCLASSID	GetClassID (void) const
								{ return (LNCLASSID_LNSIMPLEFIELDVALUE); }
		LNString			GetFieldName (void) const;
		LNSIMPLESEARCHOPERATOR GetSearchOperator (void) const;
		
		LNSTATUS			GetValueItem (LNItem * pItem) const;
		LNITEMTYPE			GetValueItemType (void) const;

		LNSTATUS			SetActionOperator (LNSIMPLEACTIONOPERATOR newOp);
		LNSTATUS			SetFieldName (const LNString & newName);
		LNSTATUS			SetSearchOperator (LNSIMPLESEARCHOPERATOR newOp);
		LNSTATUS			SetValueItem (LNItem & newItem);

	protected:
		void				CreateBody (LNSimpleFieldValueBody * pFrom);
		LNSimpleFieldValue (LNSimpleFieldValueBody * pBody);
		virtual LNINT		GetSize (void) const;
		virtual	LNSTATUS	Update (void * pStartPtr, void * * ppEndPtr);

	private:
		LNSimpleFieldValueBody * GetSimpleFieldValueBody (void) const;
};


#endif

