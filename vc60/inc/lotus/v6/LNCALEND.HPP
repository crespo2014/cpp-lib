//===========================================================================
//
// Module:		LNCALEND.HPP
//
// Description:
//
//		Class library definition for the LNCalend class.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNCALEND_HPP
#define LNCALEND_HPP

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif

enum LNCALENTRYTYPE
{
//-----calendar entry types
	LNCALENTRYTYPE_ANY = 0x00,
	LNCALENTRYTYPE_APPOINTMENT = 0x01,
	LNCALENTRYTYPE_ANNIVERSARY = 0x02,
	LNCALENTRYTYPE_EVENT = 0x04,
	LNCALENTRYTYPE_MEETING = 0x08,
	LNCALENTRYTYPE_REMINDER = 0x10
};


// The event types as they are stored in the Note
#define LNPERSONAL 		"0"
#define LNANNIVERSARY 	"1"
#define LNEVENT 		"2"
#define LNMEETING 		"3"
#define LNREMINDER 		"4"


//	Class definition for LNCalendarEntry
//
class LNIMPEXPCL LNCalendarEntry : public LNDocument
{
friend class LNCalendarEntryArray;
public:
	LNCalendarEntry() {}
	~LNCalendarEntry() {}

	LNCalendarEntry( const LNCalendarEntry &other ) : LNDocument(other) {}
	LNCalendarEntry( const LNDocument &other ) : LNDocument(other) {}

	LNCalendarEntry & operator=( const LNCalendarEntry &other )
		{ LNDocument::operator=(other); return *this; }

	LNCalendarEntry & operator=( const LNDocument &other )
		{ LNDocument::operator=(other); return *this; }

	LNCalendarEntry & operator=( const LNNote &other )
		{ LNDocument::operator=(other); return *this; }
	
	LNSTATUS GetAlarmDatetime(LNDatetime *date) const;
	
	LNSTATUS GetAlarmDescription(LNString *description) const;
	
	LNSTATUS GetAlarmOffsetMinutes(LNSINT *offset) const;
	
	LNString GetBriefDescription() const;
	
	LNCLASSID GetClassID() const {return LNCLASSID_LNCALENDARENTRY;}
	
	LNDatetimeRange GetDatetimeRange() const;
	
	LNSTATUS GetDetailedDescription(LNRichText *description) const;
	
	LNCALENTRYTYPE GetEntryType() const;
	
	LNBOOL GetIsAlarmEnabled() const;
	
	LNBOOL GetIsPenciledIn() const;
	
	LNBOOL GetIsPrivate() const;
	
	LNSTATUS GetOptionalAttendees(LNText *attendees) const;
	
	LNString GetOwner() const;
	
	LNSTATUS GetRequiredAttendees(LNText *attendees) const;
	
	LNBOOL IsAlarmRelative() const;
	
	LNBOOL IsRepeating() const;

	LNSTATUS Save(LNNOTESAVEFLAGS options=LNNOTESAVEFLAGS_DEFAULT, LNBOOL send=TRUE);
	
	LNSTATUS SetAlarmDatetime(const LNDatetime time);
	
	LNSTATUS SetAlarmDescription(const LNString &description);
	
	LNSTATUS SetAlarmOffsetMinutes(LNSINT &offset);
	
	LNSTATUS SetBriefDescription(const LNString &description);
	
	LNSTATUS SetDatetimeRange(const LNDatetimeRange &date);
	
	LNSTATUS SetDetailedDescription(const LNRichText &description);

	void SetIsAlarmEnabled(LNBOOL alarm);
	
	void SetIsPenciledIn(LNBOOL status);
	
	void SetIsPrivate(LNBOOL status);
	
	LNSTATUS SetOptionalAttendees(const LNText &invitees);
	
	LNSTATUS SetRequiredAttendees(const LNText &invitees);
private:
	LNCalendarEntry & operator=( LNDocumentBody *body )
		{ LNDocument::operator=(body); return *this; }
	LNCalendarEntry( LNDatabaseBody *db, NOTEID idnote ) : LNDocument(db, idnote) {}
	LNSTATUS SetDefaults(LNCALENTRYTYPE type, const LNString &name);
	LNSTATUS SetEntryType(LNCALENTRYTYPE type);
};


//
//	Class definition for LNCalendar.
//
class LNIMPEXPCL LNCalendar : public LNDatabase
{
public:
	LNCalendar() {}
	LNCalendar(const LNCalendar &other);
		
	~LNCalendar() {}
	
	LNSTATUS CreateEntry(LNCalendarEntry &entry, LNCalendarEntry *newentry = 0);
	LNSTATUS CreateEntry(const LNDatetimeRange &date, const LNString &description, LNCALENTRYTYPE type=LNCALENTRYTYPE_APPOINTMENT, LNCalendarEntry *entry=0);

	LNSTATUS CreateInvitation(const LNDatetimeRange &date, const LNString &description, const LNText &invitees, LNCalendarEntry *entry = 0);
	
	LNSTATUS DeleteEntry(const LNDatetimeRange &date);
	LNSTATUS DeleteEntry(LNCalendarEntry *entry);
	
	LNSTATUS DeleteEntries
		(const LNDatetimeRange &date, LNCALENTRYTYPE type = LNCALENTRYTYPE_ANY,
		 LNBOOL fullycontained = TRUE);
	LNSTATUS DeleteEntries
		(const LNDatetimes &dateRanges, LNCALENTRYTYPE type = LNCALENTRYTYPE_ANY,
		 LNBOOL fullycontained = TRUE);

	LNCLASSID GetClassID() const {return LNCLASSID_LNCALENDAR;}
		
	LNSTATUS GetEntry(const LNDatetimeRange &dateRange, LNCalendarEntry *result);
	
	LNSTATUS GetEntries(const LNDatetimeRange &dateRange, LNCalendarEntryArray *entries, LNBOOL fullycontained = TRUE, const LNString &matchstring = "");
	LNSTATUS GetEntries(const LNDatetimes &dateRanges, LNCalendarEntryArray *entries, LNBOOL fullycontained = TRUE, const LNString &matchstring = "");
	
	LNBOOL IsAvailable(const LNDatetimeRange &dateRange, LNCALENTRYTYPE type = LNCALENTRYTYPE_ANY);

private:
	LNSTATUS FindCSDocForDate(const LNDatetimeRange &date, LNCALENTRYTYPE type, LNCalendarEntryArray *document, LNBOOL fullycontained, LNBOOL all);
	LNBOOL DoesDateFallInRange(const LNDatetimeRange &theRange, const LNDatetime &theDate);
	LNBOOL DoDatesOverlap(const LNDatetimeRange &date1, const LNDatetimeRange &date2);
};


#endif // LNCALEND_HPP

//===========================================================================
//                             REVISION HISTORY
//===========================================================================
//
//  Date	Who	Description
// --------	---	-----------
// 08/07/00 SMJ Fixed a problem with IsAvailable
//
// ------------ Build 124
//
// 04/13/99 SMJ  Changes for notices
// ----------- Build 78
// 11/02/98 SMJ Moved LNCalendarEntryArray to LNNOTEA
//
//------------ Build 70
//
// 10/21/98 SMJ Changed GetEntries interface and FindCSDocForDate interface
//
// -------- Build 67
// 09/21/98	DAS	Changed LNCalendar::DeleteEntries parameter from BOOL to LNBOOL.
//
// 09/13/98	DAS	Replaced all references to LNDatetimeRanges with LNDatetimes.
//				LNDatetimeRanges is no longer used.
//
// ------------	Build 65
//
// 08/14/98	DAS	Changed LNCalendarEntry::Get/SetAlarmOffsetMinutes to use
//				LNSINT rather than LNNumber parameters.
//
// ------------	Build 62
//
// 06/09/98 SMJ	Fixed SDK BEGIN problem
//
// 05/29/98	SMJ	Added icon numbers for _VIEWICON
//
// 05/27/98	SMJ	Added some more fields
//
// ------------	Build 54
//
// 04/02/98	SMJ	Added Save method to LNCalendarEntry
//
// ------------	Build 51
//
// 03/20/98	SMJ	Added a create method to LNCalendarEntryArray that takes a database
//
// ------------	Build 50
//
// 03/06/98 SMJ Added LNCALDATETIME which is needed for the entry to be 
//				displayed in the Calendar View
//
// 02/06/98	SMJ	Added LNCalendarEntryArray and fixed a couple things
//
// 01/23/98	SMJ	Added the LNCalendar class
//
// 12/12/97	SMJ	Initial Revision
//===========================================================================

