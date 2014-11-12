//===========================================================================
//
// Module:		LNDTS.HPP
//
// Description:
//
//		Class library definition for LNDatetimes and related classes.
//
//===========================================================================
//
// Copyright (c) 1995-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNDTS_HPP
#define LNDTS_HPP

//
//	Class definition for LNDatetimesElement.
//
class LNIMPEXPCL LNDatetimesElement : public LNNotesClass
{
friend class LNDatetimes;

public:
	LNDatetimesElement( const LNDatetimesElement &other );

	~LNDatetimesElement();

	LNDatetimesElement& operator=( const LNDatetime &datetime );
	LNDatetimesElement& operator=( const LNDatetimeRange &dtrange );
	LNDatetimesElement& operator=( const LNDatetimesElement &datetimeselem )
		{ return operator=(datetimeselem.GetDatetimeRange()); }
	LNDatetimesElement& operator=( const LNString &text )
		{ return operator=(LNDatetime(text)); }

	operator LNDatetime() const;

	LNCLASSID GetClassID() const { return LNCLASSID_LNDATETIMESELEMENT; }

private:
	LNDatetimesElement();	// Disabled.
	LNDatetimesElement( LNDatetimesBody *datebody, LNINT index );

	LNDatetimeRange GetDatetimeRange() const;

	LNDatetimesBody *Body;
	LNINT Index;	
};

//
//	Class definition for LNDatetimes.
//
class LNIMPEXPCL LNDatetimes : public LNItem
{
public:
	LNDatetimes() {}
	LNDatetimes( const LNDatetimes &other ) : LNItem(other) {}
	LNDatetimes( const LNItem &other );

	~LNDatetimes() {}

	LNDatetimes& operator=( const LNDatetimes &other );
	LNDatetimes& operator=( const LNItem &other );

	LNDatetimes& operator<<( const LNDatetimes &datetimes );
	LNDatetimes& operator<<( const LNDatetime &datetime );
	LNDatetimes& operator<<( const LNDatetimeRange &dtrange );
	LNDatetimes& operator<<( const LNDatetimesElement &datetimeselem );
	LNDatetimes& operator<<( const LNString &text )
		{ return operator<<(LNDatetime(text)); }

	LNDatetimesElement operator[]( LNINT n ) const;

	LNSTATUS Append( const LNDatetimes &datetimes );
	LNSTATUS Append( const LNDatetimeRange &dtrange );
	LNSTATUS Append( const LNDatetimesElement &datetimeselem )
		{ return Append(datetimeselem.GetDatetimeRange()); }
	LNSTATUS Append( const LNDatetime &datetime )
		{ return Insert(GetDatetimeCount(), datetime); }
	LNSTATUS Append( const LNString &text )
		{ return Insert(GetDatetimeCount(), LNDatetime(text)); }

	LNSTATUS Delete( LNINT n, LNINT count = 1 );

	LNSTATUS DeleteAll();

	LNCLASSID GetClassID() const { return LNCLASSID_LNDATETIMES; }

	LNINT GetCount() const;
	
	LNINT GetDatetimeCount() const;

	LNINT GetDatetimeRangeCount() const;

	LNSTATUS GetText( LNString *text, const LNString &separator = ";" ) const;
	LNSTATUS GetText
		( const LNDatetimeFormat &fmt, const LNInternational &ifmt,
		  LNString *text, const LNString &separator = ";" ) const;

	LNSTATUS Insert( LNINT n, const LNDatetimes &datetimes );
	LNSTATUS Insert( LNINT n, const LNDatetime &datetime );
	LNSTATUS Insert( LNINT n, const LNDatetimeRange &dtrange );
	LNSTATUS Insert( LNINT n, const LNDatetimesElement &datetimeselem )
		{ return Insert(n, datetimeselem.GetDatetimeRange()); }
	LNSTATUS Insert( LNINT n, const LNString &text )
		{ return Insert(n, LNDatetime(text)); }

	LNSTATUS SetValue( const LNDatetimes &datetimes );
	LNSTATUS SetValue( const LNDatetime &datetime );
	LNSTATUS SetValue( const LNDatetimeRange &dtrange );
	LNSTATUS SetValue( const LNDatetimesElement &datetimeselem )
		{ return SetValue(datetimeselem.GetDatetimeRange()); }
	LNSTATUS SetValue( const LNString &text )
		{ return SetValue(LNDatetime(text)); }

protected:
	void Assign( LNNoteBody *noteb, LNDatetimesBody *datetimesb )
		{ LNItem::Assign(noteb, (LNItemBody *) datetimesb); }

	LNDatetimesBody * GetDatetimesBody() const
		{ return (LNDatetimesBody *) GetItemBody(); }
};

// The LNDatetimeRanges and LNDatetimeRangesElement classes are no longer used.
// LNDatetimes and LNDatetimesElement are now used for both date/times and
// date/time ranges. For compatibility with previous C++ API releases, define
// the old class names as aliases for LNDatetimes and LNDatetimesElement.

#define LNDatetimeRanges LNDatetimes
#define LNDatetimeRangesElement LNDatetimesElement


#endif

