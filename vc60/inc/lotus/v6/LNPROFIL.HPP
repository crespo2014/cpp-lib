//===========================================================================
//
// Module:		LNPROFILE.HPP
//
// Description:
//
//		Class library definition for the LNProfileDocument and LNCalendarProfileDocument class.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNPROFILE_HPP
#define LNPROFILE_HPP

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif

#define LNPROFILECALENDAR MAIL_CALENDAR_PROFILE_FORM
#define LNPROFILEDELEGATION MAIL_DELEGATION_PROFILE_FORM
#define LNPROFILERESOURCE MAIL_RESOURCE_PROFILE_FORM
 

typedef WORD LNCALENDARPROFILEMEETINGTYPE;  

#define	LNMEETINGTYPE_APPOINTMENT 0x0001
#define	LNMEETINGTYPE_ANNIVERSARY 0x0002
#define LNMEETINGTYPE_EVENT 0x0004


enum LNPROFAUTOTYPE
{
	LNCALPROFNOAUTO,
	LNCALPROFAUTOALL,
	LNCALPROFAUTOSEL,
	LNCALPROFAUTODEL
};

extern "C"
STATUS LNCALLBACK ProcessProfile( DBHANDLE hDB, void far *Ctx, char *ProfileName, 
									WORD ProfileNameLength, char *OwnerName,
									WORD OwnerNameLength,  NOTEID ProfileNoteID );

class LNIMPEXPCL LNProfileDocument : public LNSmartPtr
{
friend class LNProfileDocumentArray;
public:
	LNProfileDocument();
	LNProfileDocument( const LNProfileDocument &other );

	~LNProfileDocument();
	
	LNProfileDocument & operator=( const LNProfileDocument &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNPROFILEDOCUMENT;}

	LNString GetProfileName() const;

	LNString GetOwnerName() const;

	LNSTATUS SetOwnerName(const LNString &owner);

	LNSTATUS GetProfileField(const LNString &fieldname, LNItem *field);

	LNSTATUS SetProfileField(const LNString &fieldname, const LNItem &item);

	LNSTATUS SaveProfile();

protected:
	LNProfileDocument & operator=( LNProfileDocumentBody *profile );
};


class LNIMPEXPCL LNCalendarProfileDocument : public LNProfileDocument
{
friend class LNCalendarProfileDocumentArray;
public:
	LNCalendarProfileDocument();
	LNCalendarProfileDocument( const LNCalendarProfileDocument &other );
	LNCalendarProfileDocument & operator=( const LNProfileDocument &other );

	~LNCalendarProfileDocument();

	LNSTATUS GetAppointmentOffsetMinutes(LNSINT *leadtime);

	LNSTATUS SetAppointmentOffsetMinutes(LNSINT leadtime);

	LNSTATUS GetAnniversaryOffsetDays(LNSINT *leadtime);

	LNSTATUS SetAnniversaryOffsetDays(LNSINT leadtime);

	LNPROFAUTOTYPE GetAutoProcessForMeetings();

	LNSTATUS SetAutoProcessForMeetings(LNPROFAUTOTYPE autoprocess);

	LNSTATUS GetAutoProcessForMeetingsList(LNText *namelist);

	LNSTATUS SetAutoProcessForMeetingsList(const LNText &namelist);

	LNBOOL GetAutoRemoveFromInbox();

	LNSTATUS SetAutoRemoveFromInbox(LNBOOL remove);

	LNSTATUS GetAvailableDays(LNText *daylist);

	LNSTATUS SetAvailableDays(const LNText &AvailableDays);

	LNBOOL GetCheckForConflicts();

	LNSTATUS SetCheckForConflicts(LNBOOL type);

	LNCLASSID GetClassID() const {return LNCLASSID_LNCALENDARPROFILEDOCUMENT;}

	LNSTATUS GetDefaultDuration(LNSINT *duration);

	LNSTATUS SetDefaultDuration(LNSINT duration);

	LNBOOL GetEnableAlarmNotification();

	LNSTATUS SetEnableAlarmNotification(LNBOOL enable);

	LNSTATUS GetEventOffsetDays(LNSINT *leadtime);

	LNSTATUS SetEventOffsetDays(LNSINT eadtime);

	LNSTATUS GetFreeTimeReadersList(LNText *list);

	LNSTATUS SetFreeTimeReadersList(LNText &list);

	LNSTATUS GetFridayFreeTimes(LNDatetimes *times);
 
	LNSTATUS SetFridayFreeTimes(const LNDatetimes &time);

	LNBOOL GetHideNewEntriesFromViewing();

	LNSTATUS SetHideNewEntriesFromView(LNBOOL hide);

	LNSTATUS GetMondayFreeTimes(LNDatetimes *dates);
 
	LNSTATUS SetMondayFreeTimes(const LNDatetimes &time);

	LNSTATUS GetReminderOffsetMinutes(LNSINT *leadtime);

	LNSTATUS SetReminderOffsetMinutes(LNSINT leadtime);

	LNSTATUS GetSundayFreeTimes(LNDatetimes *times);
 
	LNSTATUS SetSundayFreeTimes(const LNDatetimes &times);

	LNSTATUS GetTaskOffsetMinutes(LNSINT *leadtime);

	LNSTATUS SetTaskOffsetMinutes(LNSINT leadtime);

	LNSTATUS GetThursdayFreeTimes(LNDatetimes *times);
 
	LNSTATUS SetThursdayFreeTimes(const LNDatetimes &time);

	LNSTATUS GetTuesdayFreeTimes(LNDatetimes *times);
 
	LNSTATUS SetTuesdayFreeTimes(const LNDatetimes &time);

	LNSTATUS GetWednesdayFreeTimes(LNDatetimes *times);

	LNSTATUS SetWednesdayFreeTimes(const LNDatetimes &time);

	LNSTATUS GetSaturdayFreeTimes(LNDatetimes *times);

	LNSTATUS SetSaturdayFreeTimes(const LNDatetimes &time);

protected:
	LNCalendarProfileDocument & operator=( LNProfileDocumentBody *profile );
};


//
//	Class definition for LNProfileArray.
//
class LNIMPEXPCL LNProfileDocumentArray : public LNSmartPtr
{

public:
	LNProfileDocumentArray();
	LNProfileDocumentArray( const LNProfileDocumentArray &other );

	~LNProfileDocumentArray();

	LNProfileDocumentArray & operator=( const LNProfileDocumentArray &other );

	LNProfileDocument operator[]( LNINT n ) const;

	LNCLASSID GetClassID() const {return LNCLASSID_LNPROFILEDOCUMENTARRAY;}

	LNINT GetCount() const;

	LNDatabase GetDatabase() const;

private:
	LNProfileDocumentArray & operator=( LNProfileDocumentArrayBody *parray )
		{ LNSmartPtr::operator=((LNBody *)parray); return *this; }
	void Assign( LNDatabaseBody *datab, LNProfileDocumentArrayBody *profileb );
};


#endif // LNPROFILE_HPP

