//===========================================================================
//
// Module:		LNATTACH.HPP
//
// Description:
//
//		Class library definitions for LNAttachment classes.
//
//===========================================================================
//
// Copyright (c) 1997 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNATTACH_HPP
#define LNATTACH_HPP

//
//	Class definition for LNAttachment
//
class LNIMPEXPCL LNAttachment : public LNItem
{
public:
	LNAttachment() {}

	LNAttachment( const LNAttachment &other ) : LNItem(other) {}

	LNAttachment( const LNItem &other );

	~LNAttachment() {}

	LNAttachment& operator=( const LNAttachment &other )
		{ LNItem::operator=(other); return *this; }

	LNAttachment& operator=( const LNItem &other );
	
	LNSTATUS Detach(const LNString &filepath) const;
	
	LNCLASSID GetClassID() const { return LNCLASSID_LNATTACHMENT; }

	LNString GetAttachmentName() const;

	LNATTACHMENTTYPE GetAttachmentType() const;
	
	LNDatetime GetFileLastModified() const;
	
	LNString GetFilepath() const;

	LNINT GetFileSize() const;
	
	LNBOOL IsCompressed() const;

	LNBOOL IsFilePrivate() const;
	
	LNBOOL IsFileReadOnly() const;

	LNBOOL IsInRichText() const;
	
	LNBOOL IsSigned() const;

protected:
	LNAttachmentBody * GetAttachmentBody() const
		{ return (LNAttachmentBody *) Body; }
};

//
//	Class definition for LNAttachmentArray
//
class LNIMPEXPCL LNAttachmentArray : public LNItemArray
{
public:
	LNAttachmentArray() {}
	LNAttachmentArray( const LNAttachmentArray &other ) : LNItemArray(other) {}

	~LNAttachmentArray() {}

	LNAttachmentArray & operator=( const LNAttachmentArray &other )
		{ LNItemArray::operator=(other); return *this; }

	LNAttachment operator[]( LNINT n ) const
		{ return LNItemArray::operator[](n); }

	LNCLASSID GetClassID() const { return LNCLASSID_LNATTACHMENTARRAY; }
};


#endif

