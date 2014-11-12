//===========================================================================
//
// Module:		LNDOC.HPP
//
// Description:
//
//		Class library definition for the LNDocument class.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNDOC_HPP
#define LNDOC_HPP


//-----	Reply flags used by CreateReplyMessage.

typedef WORD LNREPLYFLAGS;

#define LNREPLYFLAGS_INCLUDE_HISTORY	0x0001
#define	LNREPLYFLAGS_REPLY_TO_ALL		0x0002
#define LNREPLYFLAGS_DEFAULT			0

//
//	Class definition for LNDocument.
//
class LNIMPEXPCL LNDocument : public LNNote
{
friend class LNDocumentArray;

public:
	LNDocument();
	LNDocument( const LNDocument &other );
	LNDocument( const LNNote &other, LNINT score = 0 );

	~LNDocument();

	LNDocument & operator=( const LNDocument &other );
	LNDocument & operator=( const LNNote &other );

	LNCLASSID GetClassID() const { return LNCLASSID_LNDOCUMENT; }

	LNSTATUS ComputeWithForm( LNBOOL ignore_errors = FALSE ) const;
	
	LNSTATUS CreateForwardMessage( LNMailMessage *msg ) const;

	LNSTATUS CreateInvitationMessage( LNMailMessage *msg ) const;

	LNSTATUS CreateReplyMessage
		( LNMailMessage *msg, LNREPLYFLAGS flags = LNREPLYFLAGS_DEFAULT ) const;

	LNSTATUS GetAllResponses( LNDocumentArray *responses ) const;

	LNText GetCategories() const;

	LNSTATUS GetForm( LNString *form ) const { return GetFormNote(form); }
	LNSTATUS GetForm( LNForm *form ) const { return GetFormNote(form); }

	LNSTATUS GetParentDocument( LNDocument *parent ) const;

	LNINT GetResponseCount() const;

	LNSTATUS GetResponses( LNDocumentArray *responses ) const;

	LNINT GetFTSearchScore() const;

	LNBOOL IsAbstracted() const;

	LNBOOL IsResponse() const;

	LNSTATUS MakeResponse( const LNDocument &parent ) const;

	LNSTATUS Open( LNNOTEOPENFLAGS options = LNNOTEOPENFLAGS_DEFAULT);

	LNSTATUS Send( LNBOOL storeform=FALSE ) const;

	LNSTATUS SendTo( const LNString &recipient, LNBOOL storeform = FALSE ) const;
	LNSTATUS SendTo( const LNText &recipients, LNBOOL storeform = FALSE ) const;

	LNSTATUS SetForm(const LNString &formname) const
		{ return SetFormNote(formname); }
	LNSTATUS SetForm(const LNText &formname) const
		{ return SetFormNote(formname); }

protected:
	LNDocument( LNDatabaseBody *db, NOTEID idnote, LNINT score = 0 );

	LNDocument & operator=( LNDocumentBody *doc );

	void SetFTSearchScore( LNINT score ) { FTSearchScore = score; }

	LNDocumentBody * GetDocumentBody() const { return (LNDocumentBody*) Body; }

	virtual void ValidateNoteType( const LNNote &note ) const;
	virtual void ValidateNoteType( const LNNoteBody *note ) const;
	virtual void ValidateNoteType( LNNOTETYPE type ) const;

private:
	LNSTATUS GetFormNote( LNString *formname ) const;
	LNSTATUS GetFormNote( LNForm *form ) const;

	void SetCloseDatabase( LNBOOL flag );
	LNSTATUS SetFormNote( const LNString &formname ) const;
	LNSTATUS SetFormNote( const LNText &formname ) const;

	LNBOOL CloseDatabase;
	LNINT FTSearchScore;
};


#endif	//LNDOC_HPP

