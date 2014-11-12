//===========================================================================
//
// Module:	LNMAIL.HPP
//
// Description:
//
//		Class library definition and related data for LNMailMessage class.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNMAIL_HPP
#define LNMAIL_HPP

#ifndef LNTEXT_HPP
#include "lntext.hpp"
#endif

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif

//-----	Mail importance.

enum LNMAILIMPORTANCE
{
	LNMAILIMPORTANCE_HIGH,			// very important
	LNMAILIMPORTANCE_NORMAL,		// normal importance (default)
	LNMAILIMPORTANCE_LOW			// not important
};

//-----	Delivery priority.

enum LNDELIVERYPRIORITY
{
	LNDELIVERYPRIORITY_HIGH,		// high priority
	LNDELIVERYPRIORITY_NORMAL,		// normal priority (default)
	LNDELIVERYPRIORITY_LOW			// low priority
};

//-----	Delivery report.  

enum LNDELIVERYREPORT
{
	LNDELIVERYREPORT_ON_FAILURE,	// report delivery failure only (default)
	LNDELIVERYREPORT_CONFIRM,		// confirm delivery
	LNDELIVERYREPORT_CONFIRM_ONLY,	// confirm delivery, don't deliver message
	LNDELIVERYREPORT_TRACE,			// trace entire path
	LNDELIVERYREPORT_TRACE_ONLY,	// trace entire path, don't deliver message
	LNDELIVERYREPORT_NONE			// no delivery report
};

//-----	Mood stamp.

enum LNMOODSTAMP
{
	LNMOODSTAMP_NORMAL,				// normal memo (default)
	LNMOODSTAMP_PERSONAL,			// personal memo
	LNMOODSTAMP_CONFIDENTIAL,		// confidential memo
	LNMOODSTAMP_PRIVATE,			// private memo
	LNMOODSTAMP_THANK_YOU,			// thank you memo
	LNMOODSTAMP_FLAME,				// flame (urgent) memo
	LNMOODSTAMP_GOOD_JOB,			// good job memo
	LNMOODSTAMP_JOKE,				// joke memo 
	LNMOODSTAMP_FYI,				// for your information memo
	LNMOODSTAMP_QUESTION,			// question memo
	LNMOODSTAMP_REMINDER			// reminder memo
};

//-----	Recipient type (for internal use only).

enum LNRECIPIENTTYPE
{
	LNRECIPIENTTYPE_PRIMARY,		// primary recipient(s)
	LNRECIPIENTTYPE_CC,				// cc recipient(s)
	LNRECIPIENTTYPE_BCC				// bcc recipient(s)
};

//---------------------------------------------------------------------------
// Class name:	LNMailMessage
//
//	Description:
//
//	Container of data and objects pertaining to a LNMailMessage
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNMailMessage : public LNDocument
{

public:
	LNMailMessage() {}
	~LNMailMessage() {}

	LNMailMessage( const LNMailMessage &other ) : LNDocument(other) {}
	LNMailMessage( const LNDocument &other ) : LNDocument(other) {}

	LNMailMessage & operator=( const LNMailMessage &other )
		{ LNDocument::operator=(other); return *this; }

	LNMailMessage & operator=( const LNDocument &other )
		{ LNDocument::operator=(other); return *this; }

	LNMailMessage & operator=( const LNNote &other )
		{ LNDocument::operator=(other); return *this; }

	LNSTATUS GetBCC( LNText *names ) const
		{ return GetRecipients( LNRECIPIENTTYPE_BCC, names ); }
	
	LNSTATUS GetBody( LNRichText *body ) const;

	LNSTATUS GetCC( LNText *names ) const
		{ return GetRecipients( LNRECIPIENTTYPE_CC, names ); }

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNMAILMESSAGE; }

	LNSTATUS GetDateSent( LNDatetime *date ) const;

	LNDELIVERYPRIORITY GetDeliveryPriority() const;

	LNDELIVERYREPORT GetDeliveryReport() const;

	LNMAILIMPORTANCE GetMailImportance() const;

	LNMOODSTAMP GetMoodStamp() const;

	LNBOOL GetPreventCopying() const;

	LNSTATUS GetRecipients( LNText *names ) const
		{ return GetRecipients( LNRECIPIENTTYPE_PRIMARY, names ); }

	LNBOOL GetReturnReceipt() const;

	LNSTATUS GetSender( LNString *name ) const;

	LNSTATUS GetSubject( LNText *text ) const;

	LNBOOL IsSentByAgent() const;

	LNSTATUS SetBCC( const LNString &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_BCC, names ); }

	LNSTATUS SetBCC( const LNText &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_BCC, names ); }

	LNSTATUS SetCC( const LNString &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_CC, names ); }

	LNSTATUS SetCC( const LNText &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_CC, names ); }

	LNSTATUS SetDeliveryPriority( LNDELIVERYPRIORITY option ) const;

	LNSTATUS SetDeliveryReport( LNDELIVERYREPORT option ) const;

	LNSTATUS SetMailImportance( LNMAILIMPORTANCE option ) const;

	LNSTATUS SetMoodStamp( LNMOODSTAMP option ) const;

	LNSTATUS SetPreventCopying( LNBOOL flag ) const;

	LNSTATUS SetRecipients( const LNString &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_PRIMARY, names ); }

	LNSTATUS SetRecipients( const LNText &names ) const
		{ return SetRecipients( LNRECIPIENTTYPE_PRIMARY, names ); }

	LNSTATUS SetReturnReceipt( LNBOOL flag ) const;

	LNSTATUS SetSubject( const LNString &text ) const;
	LNSTATUS SetSubject( const LNText &text ) const;

private:
	LNMailMessage & operator=( LNDocumentBody *body )
		{ LNDocument::operator=(body); return *this; }

	char GetCharValue( const LNString &name ) const;
	
	LNSTATUS GetRecipients( LNRECIPIENTTYPE type, LNString *names ) const;
	LNSTATUS GetRecipients( LNRECIPIENTTYPE type, LNText *names ) const;

	LNSTATUS SetCharValue( const LNString &name, char value ) const;

	LNSTATUS SetRecipients( LNRECIPIENTTYPE type, const LNString &names ) const;
	LNSTATUS SetRecipients( LNRECIPIENTTYPE type, const LNText &names ) const;
};


#endif	//LNMAIL_HPP

