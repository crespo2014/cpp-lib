//===========================================================================
//
// Module:  LNRTLINK.HPP
//
// Description:
//
//  Class library definition for LNDatabaseLink, LNDocumentLink, LNViewLink, and 
//	related classes.
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTLINK_HPP
#define LNRTLINK_HPP

#ifndef LNVIEW_HPP
#include "lnview.hpp"
#endif

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif



// Anchor links were released with Notes version and C API 4.6
// The C++ API version 2.0 is built with the C API 4.5.1, so 
// conditionally include SIG_CD_ANCHOR, CDANCHOR, and _CDANCHOR here.

// We can include the necessary definitions for anchor links because
// we know they are going to be released in later versions, and they
// don't change any function prototypes. Notes versions which don't understand
// anchor links treat the anchor links as document links, and ignore the
// anchor locations.

// From ods.h
#ifndef SIG_CD_ANCHOR

#define SIG_CD_ANCHOR			(203 | WORDRECORDLENGTH)

typedef struct
{
	WSIG Header;					/*	Header Jive					*/
	WORD Datalength;
	DWORD Reserved;
	/* Actual anchor text follows.		*/
} CDANCHOR;

// From odstypes.h and ods.h
#ifndef odsmacro

#if defined(GCC) && defined(SUN)
#define odsmacro(name, num, size) enum{_/*##*/name = num};
#else
#define odsmacro(name, num, size) enum{_##name = num};
#endif
odsmacro(CDANCHOR, 559, sizeof(CDANCHOR))
#undef odsmacro

#else  /*	#ifdef odsmacro */

odsmacro(CDANCHOR, 559, sizeof(CDANCHOR))

#endif /*	#ifdef odsmacro */

#endif /*	#ifndef SIG_CD_ANCHOR */





class LNIMPEXPCL LNDatabaseLink : public LNRTElement
{

public:
	
	LNDatabaseLink();

	LNDatabaseLink(const LNRTObject &object);
	LNDatabaseLink(const LNDatabaseLink &link);

	LNDatabaseLink(const LNDatabase &db);

	LNDatabaseLink(const TIMEDATE DBreplicaID, const LNString &description, 
		const LNNotesSession *session);

	~LNDatabaseLink();

	LNDatabaseLink& operator=(const LNRTObject &object);
	LNDatabaseLink& operator=(const LNDatabaseLink &link);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNDATABASELINK; }

	LNString GetDescription() const;

	LNSTATUS GetHTMLTags(LNHTMLTags *tags) const;

	LNSTATUS GetTargetFrame(LNString *framename) const;

	LNSTATUS GetLinkedDatabase(LNDatabase *db) const;

	TIMEDATE * GetLinkedDatabaseReplicaID() const;

	LNSTATUS GetLinkedServerHint(LNString *name) const;

	LNSTATUS SetDescription(const LNString &comment);

	LNSTATUS SetHTMLTags(const LNHTMLTags &tags);

	LNSTATUS SetTargetFrame(const LNString &framename);

	LNBOOL ValidateLink() const;

protected:
	
 	LNINT GetLinkID() const;

	LNRTLinkBody *GetRTLinkBody() const { return (LNRTLinkBody *) Body; }

	LNSTATUS SetLinkID(LNINT id);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};




class LNIMPEXPCL LNViewLink : public LNDatabaseLink
{
public:

	LNViewLink();

	LNViewLink(const LNRTObject &object);
	LNViewLink(const LNViewLink &link);

	LNViewLink(const LNDatabase &db, const LNViewFolder &view);

	LNViewLink(const TIMEDATE DBreplicaID, const UNID *viewUNID, const LNString &description, 
		const LNNotesSession *session);

	~LNViewLink();

	LNViewLink& operator=(const LNRTObject &object);
	LNViewLink& operator=(const LNViewLink &link);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNVIEWLINK; }

	LNSTATUS GetLinkedView(LNViewFolder *view) const;

	UNID * GetLinkedViewUniversalID() const;	

protected:
	
	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};




class LNIMPEXPCL LNDocumentLink : public LNViewLink
{
public:
	
	LNDocumentLink();

	LNDocumentLink(const LNRTObject &object);
	LNDocumentLink(const LNDocumentLink &link);

	LNDocumentLink(const LNViewFolder &view, const LNDocument &document);

	LNDocumentLink(const TIMEDATE DBreplicaID, const UNID *viewUNID, const UNID *noteUNID, 
		const LNString &description, const LNNotesSession *session);

	~LNDocumentLink();

	LNDocumentLink& operator=(const LNRTObject &object);
	LNDocumentLink& operator=(const LNDocumentLink &link);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNDOCUMENTLINK; }

	LNSTATUS GetLinkedDocument(LNDocument *doc) const;

	UNID * GetLinkedDocumentUniversalID() const;

protected:
	
	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};




class LNIMPEXPCL LNAnchorLink : public LNDocumentLink
{
public:
	
	LNAnchorLink();

	LNAnchorLink(const LNRTObject &object);
	LNAnchorLink(const LNAnchorLink &link);

	LNAnchorLink(const LNViewFolder &view, const LNAnchorLocation &location);

	LNAnchorLink(const LNViewFolder &view, const LNDocument &document, 
		const LNString &anchorText);
	
	LNAnchorLink(const TIMEDATE DBreplicaID, const UNID *viewUNID, 
		const UNID *noteUNID, const LNString &description, 
		const LNString &anchorText, const LNNotesSession *session);

	~LNAnchorLink();

	LNAnchorLink& operator=(const LNRTObject &object);
	LNAnchorLink& operator=(const LNAnchorLink &link);

	LNSTATUS GetAnchorLocation(LNAnchorLocation *loc) const;

	LNString GetAnchorText() const;

	LNSTATUS SetAnchorText(const LNString &text);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNANCHORLINK; }

protected:
	
	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



class LNIMPEXPCL LNAnchorLocation : public LNRTElement
{
public:
	
	LNAnchorLocation();

	LNAnchorLocation(const LNRTObject &object);
	LNAnchorLocation(const LNAnchorLocation &location);

	LNAnchorLocation(const LNString &anchorText);

	~LNAnchorLocation();

	LNAnchorLocation& operator=(const LNRTObject &object);
	LNAnchorLocation& operator=(const LNAnchorLocation &location);

	LNString GetAnchorText() const;

	LNSTATUS GetCDAnchor(CDANCHOR *cdrecord) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNANCHORLOCATION; }

	LNSTATUS SetAnchorText(const LNString &text);

protected:
	
	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

