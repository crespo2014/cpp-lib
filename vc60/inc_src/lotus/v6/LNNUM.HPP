//===========================================================================
//
// Module:		LNNUM.HPP
//
// Description:
//
//		Class library definition for LNNumbers and related classes.
//
//===========================================================================
//
// Copyright (c) 1995-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNNUM_HPP
#define LNNUM_HPP

//
//	Class definition for LNNumbersElement.
//
class LNIMPEXPCL LNNumbersElement : public LNNotesClass
{
public:
	LNNumbersElement( const LNNumbersElement &other );

	~LNNumbersElement();

	LNNumbersElement& operator=( const LNNUMBER &number );
	LNNumbersElement& operator=( const LNNumbersElement &numberselem )
		{ return operator=(numberselem.operator LNNUMBER()); }

	operator LNNUMBER() const;

	LNCLASSID GetClassID() const { return LNCLASSID_LNNUMBERSELEMENT; }

private:
	LNNumbersElement();	// Disabled.
	LNNumbersElement( LNNumbersBody *numbody, LNINT index );

	LNNumbersBody *Body;
	LNINT Index;	
};

//
//	Class definition for LNNumbers.
//
class LNIMPEXPCL LNNumbers : public LNItem
{
public:
	LNNumbers() {}
	LNNumbers( const LNNumbers &other ) : LNItem(other) {}
	LNNumbers( const LNItem &other );

	~LNNumbers() {}

	LNNumbers& operator=( const LNNumbers &other );
	LNNumbers& operator=( const LNItem &other );

	LNNumbers& operator<<( const LNNumbers &numbers );
	LNNumbers& operator<<( const LNNUMBER &number );
	LNNumbers& operator<<( const LNNumbersElement &numberselem );

	LNNumbersElement operator[]( LNINT n ) const;

	LNSTATUS Append( const LNNumbers &numbers )
		{ return Insert(GetCount(), numbers); }
	LNSTATUS Append( const LNNUMBER &number )
		{ return Insert(GetCount(), number); }
	LNSTATUS Append( const LNNumbersElement &numberselem )
		{ return Insert(GetCount(), numberselem.operator LNNUMBER()); }

	LNSTATUS Delete( LNINT n, LNINT count = 1 );

	LNSTATUS DeleteAll();

	LNCLASSID GetClassID() const { return LNCLASSID_LNNUMBERS; }

	LNINT GetCount() const;

	LNSTATUS GetText( LNString *text, const LNString &separator = ";" ) const;
	LNSTATUS GetText
		( const LNNumberFormat &fmt, const LNInternational &ifmt,
		  LNString *text, const LNString &separator = ";" ) const;

	LNSTATUS Insert( LNINT n, const LNNumbers &numbers );
	LNSTATUS Insert( LNINT n, const LNNUMBER &number );
	LNSTATUS Insert( LNINT n, const LNNumbersElement &numberselem )
		{ return Insert(n, numberselem.operator LNNUMBER()); }

	LNSTATUS SetValue( const LNNumbers &numbers );
	LNSTATUS SetValue( const LNNUMBER &number );
	LNSTATUS SetValue( const LNNumbersElement &numberselem )
		{ return SetValue(numberselem.operator LNNUMBER()); }

protected:
	void Assign( LNNoteBody *noteb, LNNumbersBody *numbersb )
		{ LNItem::Assign(noteb, (LNItemBody *) numbersb); }

	LNNumbersBody * GetNumbersBody() const
		{ return (LNNumbersBody *) GetItemBody(); }
};


#endif

