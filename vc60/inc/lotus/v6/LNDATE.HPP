//===========================================================================
//
// Module:		LNDATE.HPP
//
// Description:
//
//		Class library definitions for date and time related classes.
//
//===========================================================================
//
// Copyright (c) 1996-2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNDATE_HPP
#define LNDATE_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif


const BYTE MAX_DECIMAL_DIGITS = 16;		// allows any number up to 15

//
//	Class definition for LNInternational.
//
class LNIMPEXPCL LNInternational : public LNNotesClass
{
friend class LNDatetime;
friend class LNDatetimeRange;
friend class LNNumber;
friend class LNNotesSession;

public:
	LNInternational();
	LNInternational( const LNInternational &other );
	LNInternational( const INTLFORMAT &intlformat );

	~LNInternational();

	LNInternational & operator=( const LNInternational &other );
	LNInternational & operator=( const INTLFORMAT &intlformat );

	LNString GetAMString() const;

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNINTERNATIONAL;}

	LNINT GetCurrencyDigits() const;

	LNBOOL GetCurrencySpace() const;

	LNString GetCurrencySymbol() const;

	LNBOOL GetCurrencySymbolSuffix() const;

	LNDATEORDER GetDateOrder() const;

	LNString GetDateSeparator() const;

	LNString GetDecimalSeparator() const;

	LNBOOL GetDSTObserved() const;

	INTLFORMAT * GetINTLFORMAT();

	LNBOOL GetLeadingZero() const;

	LNString GetPMString() const;

	LNString GetThousandSeparator() const;

	LNBOOL GetUseMetricMeasurements() const;

	LNBOOL Get24HourFormat() const;

	LNString GetTimeSeparator() const;

	LNTIMEZONE GetTimeZone() const;

	LNString GetTodayString() const;

	LNString GetTomorrowString() const;

	LNString GetYesterdayString() const;

	LNSTATUS SetAMString( const LNString &amstring );

	LNSTATUS SetCurrencyDigits( LNINT digits );

	void SetCurrencySpace( LNBOOL currspace );

	LNSTATUS SetCurrencySymbol( const LNString &currencystring );

	void SetCurrencySymbolSuffix( LNBOOL currplace );

	LNSTATUS SetDateOrder( LNDATEORDER dateorder );

	LNSTATUS SetDateSeparator( const LNString &datesep );

	LNSTATUS SetDecimalSeparator( const LNString &decimalsep );

	void SetDSTObserved( LNBOOL daylight );

	void SetLeadingZero( LNBOOL leadzero );

	LNSTATUS SetPMString( const LNString &pmstring );

	LNSTATUS SetThousandSeparator( const LNString &thousandsep );

	void Set24HourFormat( LNBOOL format );

	LNSTATUS SetTimeSeparator( const LNString &timesep );

	LNSTATUS SetTimeZone( LNTIMEZONE timezone );

	LNSTATUS SetTodayString( const LNString &todaystring );

	LNSTATUS SetTomorrowString( const LNString &tomorrowstring );

	LNSTATUS SetYesterdayString( const LNString &yesterdaystring );

private:
	// functions:

	LNInternational( const LNNotesSession *session, INTLFORMAT *intlformat );

	LNBOOL IsValid() const { return Valid; }
	
	INTLFORMAT InternationalSettings;

	// data:

	LNBOOL Valid;
};




enum LNDATETIMESPECIAL 
{
	LNDATETIMESPECIAL_MINIMUM = TIMEDATE_MINIMUM,
	LNDATETIMESPECIAL_MAXIMUM = TIMEDATE_MAXIMUM,
	LNDATETIMESPECIAL_WILDCARD = TIMEDATE_WILDCARD,
	LNDATETIMESPECIAL_NOTACTIVE,
	
	// the following are retained for compatibility:

	LNDATETIME_MINIMUM = LNDATETIMESPECIAL_MINIMUM,
	LNDATETIME_MAXIMUM = LNDATETIMESPECIAL_MAXIMUM,
	LNDATETIME_WILDCARD = LNDATETIMESPECIAL_WILDCARD,
	LNDATETIME_NOTACTIVE = LNDATETIMESPECIAL_NOTACTIVE
};

//
//	Class definition for LNDatetime.
//
class LNIMPEXPCL LNDatetime : public LNNotesClass
{
public:
	LNDatetime();
	LNDatetime( const LNDatetime &other );
	LNDatetime( const LNString &datestring, LNSTATUS *lnerror=0 );
	LNDatetime( const LNDATETIMESPECIAL specialcase );
	LNDatetime( const TIMEDATE &timedate );

	~LNDatetime() {}

	LNDatetime & operator=( const LNDatetime &other );
	LNDatetime & operator=( const LNString &other );
	LNDatetime & operator=( const LNDATETIMESPECIAL specialcase );
	LNDatetime & operator=( const TIMEDATE &timedate );

	LNBOOL operator==( const LNDatetime &other ) const
		{ return Compare(other) == 0; }

	LNBOOL operator!=( const LNDatetime &other ) const
		{ return Compare(other) != 0; }

	LNBOOL operator<=( const LNDatetime &other ) const
		{ return Compare(other) <= 0; }

	LNBOOL operator>=( const LNDatetime &other ) const
		{ return Compare(other) >= 0; }

	LNBOOL operator<( const LNDatetime &other ) const
		{ return Compare(other) < 0; }

	LNBOOL operator>( const LNDatetime &other ) const
		{ return Compare(other) > 0; }

	LNSINT operator-( const LNDatetime &other ) const;

	operator LNString() const;

	LNSTATUS AdjustDate
		( LNSINT months, LNSINT days, LNSINT years );
	
	LNSTATUS AdjustTime
		( LNSINT hours, LNSINT minutes, LNSINT seconds, LNSINT hundredths = 0 );
	
	LNSTATUS AdjustDay( LNSINT days )
		{ return AdjustDate(0, days, 0); }

	LNSTATUS AdjustHour( LNSINT hours )
		{ return AdjustTime(hours, 0, 0, 0); }

	LNSTATUS AdjustHundredth( LNSINT hundredths )
		{ return AdjustTime(0, 0, 0, hundredths); }

	LNSTATUS AdjustMinute( LNSINT minutes )
		{ return AdjustTime(0, minutes, 0, 0); }

	LNSTATUS AdjustMonth( LNSINT months )
		{ return AdjustDate(months, 0, 0); }

	LNSTATUS AdjustSecond( LNSINT seconds )
		{ return AdjustTime(0, 0, seconds, 0); }

	LNSTATUS AdjustTimeZone( LNTIMEZONE zone );

	LNSTATUS AdjustYear( LNSINT years )
		{ return AdjustDate(0, 0, years); }

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDATETIME;}

	LNSTATUS GetDate( LNINT *month, LNINT *day, LNINT *year ) const;

	LNINT GetDay() const;

	LNDAYOFWEEK GetDayOfWeek() const;

	LNINT GetDayOfYear() const;

	LNBOOL GetDSTInEffect() const;

	LNINT GetHour() const;

	LNINT GetHundredth() const;

	LNINT GetMinute() const;

	LNINT GetMonth() const;

	LNINT GetSecond() const;

	LNSTATUS GetText( LNString *text ) const;
	LNSTATUS GetText
		( const LNDatetimeFormat &fmt, const LNInternational &ifmt,
		  LNString *text ) const
		{ return GetText(text, (LNDatetimeFormat *) &fmt, (LNInternational *) &ifmt); }

	LNSTATUS GetTime( LNINT *hour, LNINT *minute, LNINT *second,
		LNINT *hundredth=0 ) const;

	TIME * GetTIME() const;
	
	TIMEDATE * GetTIMEDATE() const;

	LNTIMEZONE GetTimeZone() const;

	LNINT GetYear() const;

	LNBOOL IsDateDefined() const { return DateDefined; }

	LNBOOL IsDateWildCard() const
		{ return (SpecialCase == LNDATETIMESPECIAL_WILDCARD && !DateDefined); }

	LNBOOL IsDefined() const { return DateDefined || TimeDefined; }

	LNBOOL IsDSTInEffect() const;

	LNBOOL IsLeapYear() const;

	LNBOOL IsMaximum() const
		{ return (SpecialCase == LNDATETIMESPECIAL_MAXIMUM); }

	LNBOOL IsMinimum() const
		{ return (SpecialCase == LNDATETIMESPECIAL_MINIMUM); }

	LNBOOL IsNull() const
		{ return (SpecialCase == LNDATETIMESPECIAL_NOTACTIVE && !DateDefined); }

	LNBOOL IsSpecialCase() const
		{ return (SpecialCase != LNDATETIMESPECIAL_NOTACTIVE);}

	LNBOOL IsTimeDefined() const { return TimeDefined; }

	LNBOOL IsTimeWildCard() const
		{ return (SpecialCase == LNDATETIMESPECIAL_WILDCARD && !TimeDefined); }

	LNBOOL IsWildCard() const
		{ return (SpecialCase == LNDATETIMESPECIAL_WILDCARD); }

	LNSTATUS SetDate( LNINT month, LNINT day, LNINT year = 0 );

	void SetDateToWildCard();

	LNSTATUS SetDay( LNINT day );

	void SetDSTInEffect(LNBOOL dst);

	LNSTATUS SetHour( LNINT hour );

	LNSTATUS SetHundredth( LNINT hundredth );

	LNSTATUS SetMinute( LNINT minute );

	LNSTATUS SetMonth( LNINT month );

	LNSTATUS SetSecond( LNINT second );

	LNSTATUS SetTime( LNINT hour, LNINT minute, LNINT second=0,
		LNINT hundredth=0 );

	void SetTimeToWildCard();

	LNSTATUS SetTimeZone( LNTIMEZONE timezone );

	LNSTATUS SetYear( LNINT year );

private:
	int Compare( const LNDatetime &other ) const;
	
	LNSTATUS GetText( LNString *text, LNDatetimeFormat *fmt,
		LNInternational *ifmt ) const;

	LNSTATUS SetDatetime( const TIMEDATE *datetime );

	TIME Datetime;
	WORD DateDefined;
	WORD TimeDefined;
	WORD SpecialCase;
};

//
//	Class definition for LNDatetimeFormat.
//
class LNIMPEXPCL LNDatetimeFormat : public LNNotesClass
{
friend class LNDatetime;
friend class LNDatetimeRange;

public:
	LNDatetimeFormat();
	LNDatetimeFormat( const TFMT &tfmt )
		{ memcpy(&DatetimeFormat, &tfmt, sizeof(TFMT)); }
	LNDatetimeFormat( const LNDatetimeFormat &other );

	~LNDatetimeFormat() {}

	LNDatetimeFormat & operator=( const LNDatetimeFormat &other );
	LNDatetimeFormat & operator=( const TFMT &tfmt )
		{ memcpy(&DatetimeFormat, &tfmt, sizeof(TFMT)); return *this; }

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDATETIMEFORMAT;}

	LNDATEFORMAT GetDateFormat() const
		{return (LNDATEFORMAT)DatetimeFormat.Date;}

	LNDATETIMEDISPLAY GetDatetimeDisplay() const
		{return (LNDATETIMEDISPLAY)DatetimeFormat.Structure;}

	TFMT * GetTFMT() { return &DatetimeFormat; }

	LNTIMEFORMAT GetTimeFormat() const
		{return (LNTIMEFORMAT)DatetimeFormat.Time;}

	LNTIMEZONEDISPLAY GetTimeZoneDisplay() const
		{return (LNTIMEZONEDISPLAY)DatetimeFormat.Zone;}

	LNSTATUS SetDateFormat( LNDATEFORMAT format );

	LNSTATUS SetDatetimeDisplay( LNDATETIMEDISPLAY format );

	LNSTATUS SetTimeFormat( LNTIMEFORMAT format );

	LNSTATUS SetTimeZoneDisplay( LNTIMEZONEDISPLAY format );

private:
	TFMT DatetimeFormat;
};

//
//	Class definition for LNDatetimeRange.
//
class LNIMPEXPCL LNDatetimeRange : public LNNotesClass
{
public:
	LNDatetimeRange();
	LNDatetimeRange( const LNDatetimeRange &other );
	LNDatetimeRange( const LNDatetime &datetime );
	LNDatetimeRange( const LNDatetimesElement &dtelem );
	LNDatetimeRange( const TIMEDATE_PAIR &tdpair );
	LNDatetimeRange( const TIMEDATE &td );

	~LNDatetimeRange() {}

	LNDatetimeRange & operator=( const LNDatetimeRange &other );
	LNDatetimeRange & operator=( const LNDatetime &datetime );
	LNDatetimeRange & operator=( const LNDatetimesElement &dtelem )
		{ return operator=(LNDatetimeRange(dtelem)); }

	operator LNString() const;

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDATETIMERANGE;}

	LNDatetime GetBegin() const { return LNDatetime(DatetimeRange.Lower); }

	LNDatetime GetEnd() const { return LNDatetime(DatetimeRange.Upper); }

	LNSTATUS GetText( LNString *text ) const { return GetText(text,0,0); }
	LNSTATUS GetText
		( const LNDatetimeFormat &fmt, const LNInternational &ifmt,
		  LNString *text ) const
		{ return GetText(text, (LNDatetimeFormat *) &fmt,(LNInternational *) &ifmt); }

	TIMEDATE_PAIR * GetTIMEDATEPAIR() const;

	LNBOOL IsBeginDefined() const { return BeginDateDefined; }

	LNBOOL IsEndDefined() const { return EndDateDefined; }

	LNBOOL IsNull() const { return !BeginDateDefined; }
	
	LNSTATUS SetBegin( const LNDatetime &begin );
	LNSTATUS SetBegin( const LNString &begin )
		{ return SetBegin(LNDatetime(begin)); }

	LNSTATUS SetEnd( const LNDatetime &end );
	LNSTATUS SetEnd( const LNString &end )
		{ return SetEnd(LNDatetime(end)); }

private:
	LNSTATUS GetText( LNString *text, LNDatetimeFormat *fmt,
		LNInternational *ifmt ) const;

	TIMEDATE_PAIR DatetimeRange;
	LNBOOL BeginDateDefined;
	LNBOOL EndDateDefined;
};

#endif	//LNDATE_HPP

