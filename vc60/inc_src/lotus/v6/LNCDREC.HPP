//===========================================================================
//
// Module:		LNCDREC.HPP
//
// Description:
//
//		Class library definition for the classes which handle
//      miscellaneos CD records used in many places.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNCDREC_HPP
#define LNCDREC_HPP

#ifndef RSRCODS_DEFS
#include <rsrcods.h>
#endif

enum LNNAMEDELEMENT
{
	LNNAMEDELEMENT_PAGE,
	LNNAMEDELEMENT_FORM,
	LNNAMEDELEMENT_FRAMESET,
	LNNAMEDELEMENT_VIEW,
	LNNAMEDELEMENT_SIMPLE_VIEW,
	LNNAMEDELEMENT_FOLDER,
	LNNAMEDELEMENT_SIMPLE_FOLDER,
	LNNAMEDELEMENT_NAVIGATOR
};


enum LNNAMEDELEMENTDB
{
	LNNAMEDELEMENTDB_MAIL,	// REPLICA_ID_CURRENT_MAILFILE
	LNNAMEDELEMENTDB_ADDRESS_BOOK,	// REPLICA_ID_CURRENT_ADDRBOOK
	LNNAMEDELEMENTDB_SUBSCRIPTIONS,	// REPLICA_ID_CURRENT_SUBSCRIPTION_DB
	LNNAMEDELEMENTDB_BOOKMARKS,	// REPLICA_ID_CURRENT_BOOKMARKS_DB
	LNNAMEDELEMENTDB_CURRENT,	// current database (replica ID = 0)
	LNNAMEDELEMENTDB_OTHER	// some other database (replica ID != 0)
};

//
//  Class definition of LNHTMLTags
//
class LNIMPEXPCL LNHTMLTags : public LNNotesClass
{
public:
	// General methods

	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNHTMLTAGS;}
	void Clear();
	LNHTMLTags() { Clear (); }
	LNHTMLTags(WORD cdSignature);
	LNHTMLTags( const LNHTMLTags &other )
	{
		this->operator=(other);
	}
	LNHTMLTags& operator=( const LNHTMLTags &other )
	{
		CdSignature = other.CdSignature;
		Name = other.Name;
		Id = other.Id;
		Class = other.Class;
		Style = other.Style;
		Title = other.Title;
		Extra = other.Extra;
		return (*this);
	}
	~LNHTMLTags(){}
	LNBOOL IsNull() const;
	LNINT GetSize() const;

	// Properties

	LNString GetClassTag() const { return Class; }
	void SetClassTag( const LNString &tag ) { Class = tag; }

	LNString GetIdTag() const { return Id; }
	void SetIdTag( const LNString &tag ) { Id = tag; }

	LNString GetHTMLCode() const { return Extra; }
	void SetHTMLCode( const LNString &code ) { Extra = code; }

	LNString GetName() const { return Name; }
	void SetName( const LNString &name ) { Name = name; }

	LNString GetStyleTag() const { return Style; }
	void SetStyleTag( const LNString &tag ) { Style = tag; }

	LNString GetTitleTag() const { return Title; }
	void SetTitleTag( const LNString &tag ) { Title = tag; }

	LNSTATUS Load (char **ppData);
	LNSTATUS Update(char **ppData) const;

	LNSTATUS Load (LNItemBody *itemBody, LNINT offset, LNINT *newOffset);
	LNSTATUS Update(LNItemBody *itemBody, LNINT offset, LNINT *newOffset) const;

	LNSTATUS Load (const LNRTObject &object);
	LNSTATUS Update(LNRTObject *object) const;

	void LoadVariableData(CDIDNAME cdidname, char *ptr);
	void UpdateRecordData(CDIDNAME *cdidname) const;
	void UpdateVariableData(CDIDNAME cdidname, char **pPtr) const;

	WORD GetCDSignature (void) const;
	void SetCDSignature (WORD newSignature);

protected:

private:

	WORD		CdSignature;
	LNString	Id;
	LNString	Class;
	LNString	Style;
	LNString	Title;
	LNString	Extra;
	LNString	Name;
};
#endif // LNCDREC_HPP
