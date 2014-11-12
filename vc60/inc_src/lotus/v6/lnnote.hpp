//===========================================================================
//
// Module:		LNNOTE.HPP
//
// Description:
//
//		Class library definition for the LNNote and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNNOTE_HPP
#define LNNOTE_HPP

#ifdef MAC
#include <Menus.h>
#undef GetItem
#endif

enum LNDESIGNERVERSION {
/*	Designer minimum version */
/*	"minimum version" means "you need at least this version to safely save 
	this design element." */
LNDESIGNERVERSION_5,		
LNDESIGNERVERSION_6,		
LNDESIGNERVERSION_7,		
LNDESIGNERVERSION_8,		
LNDESIGNERVERSION_9,		
LNDESIGNERVERSION_10,
LNDESIGNERVERSION_UNDEFINED
};

//
//	Class definition for LNNote.
//
class LNIMPEXPCL LNNote : public LNSmartPtr
{
friend class LNNoteArray;

public:
	LNNote();
	LNNote( const LNNote &other );

	~LNNote();
	
	LNNote & operator=( const LNNote &other );

	virtual LNSTATUS Close();
	
	LNSTATUS CreateAttachment
		( const LNString &path, LNAttachment *newattachment ) const
		{ return CreateAttachment(path, "", TRUE, newattachment); }
	LNSTATUS CreateAttachment
		( const LNString &path, const LNString &attachmentname = "",
		  LNBOOL compress = TRUE, LNAttachment *newattachment = 0) const;
	LNSTATUS CreateAttachment
		( const LNAttachment &att, LNAttachment *newattachment = 0 ) const;
	LNSTATUS CreateAttachment
		( const LNAttachment &att, const LNString &attachmentname,
		  LNAttachment *newattachment = 0 ) const;

	LNSTATUS CreateItem
		( const LNString &name, LNItem *newitem,
		  LNITEMFLAGS flags = LNITEMFLAGS_AUTO_SUMMARY,
		  LNITEMOPTION options = LNITEMOPTION_APPEND_ONLY ) const;
	LNSTATUS CreateItem
		( const LNString &name, LNITEMTYPE type, void *data, LNINT datalen,
		  LNITEMFLAGS flags = LNITEMFLAGS_AUTO_SUMMARY,
		  LNITEMOPTION options = LNITEMOPTION_APPEND_ONLY,
		  LNItem *newitem = 0 ) const;
	LNSTATUS CreateItem
		( const LNItem &item, LNITEMOPTION options = LNITEMOPTION_APPEND_ONLY,
		  LNItem *newitem = 0 ) const;
	LNSTATUS CreateItem
		( const LNString &name, const LNItem &item,
		  LNITEMFLAGS flags = LNITEMFLAGS_AUTO_SUMMARY,
		  LNITEMOPTION options = LNITEMOPTION_APPEND_ONLY,
		  LNItem *newitem = 0 ) const;
	
	LNSTATUS CreateOLEObject
		( const LNString &path, const LNOLEGUID &guid,
		  LNOLECLIPBOARDFORMAT displayFormat, const LNString &fieldName = "",
		  const LNString &userType = "", const LNString &attachName = "",
		  LNOLEObject *newObject = 0) const;

	LNSTATUS DeleteAllItems() const;
	
	LNSTATUS DeleteAttachment
		( const LNString &attachname, LNBOOL deletert = TRUE ) const;
	LNSTATUS DeleteAttachment( LNAttachment *att, LNBOOL deletert = TRUE ) const;

	LNSTATUS DeleteItem( const LNString &name ) const;
	LNSTATUS DeleteItem( LNItem *item ) const;

	LNSTATUS DeleteOLEObject
		( const LNString &attachmentName, LNBOOL deletert = TRUE ) const;
	LNSTATUS DeleteOLEObject( LNOLEObject *oleObj, LNBOOL deletert = TRUE ) const;
	
	LNSTATUS Decrypt() const;
	
	LNSTATUS Detach( const LNString &attname, const LNString &path ) const;

	LNSTATUS Encrypt( LNENCRYPTOPTION option = LNENCRYPTOPTION_PUBLIC );
	LNSTATUS Encrypt( const LNString &keyname );
	LNSTATUS Encrypt( const LNText &keynames );

	LNDatetime GetAddedToFile() const;
	
	LNString GetAlias() const;

	LNSTATUS GetAttachment( const LNString &attname, LNAttachment *att ) const;
	
	LNSTATUS GetAttachments( LNAttachmentArray *attachments ) const;

	LNString GetAuthor() const;
	
	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNNOTE; }
	
	LNDatetime GetCreated() const;

	LNDatabase GetDatabase() const { return Db; }

	LNSTATUS GetDesignLanguage(LNString *languageString) const;
	LNSTATUS SetDesignLanguage(const LNString &languagestring);
	
	LNSTATUS GetItem( const LNString &name, LNItem *item ) const;

	LNINT GetItemCount() const;
	
	LNSTATUS GetItems
		( LNItemArray *items, LNITEMTYPE type = LNITEMTYPE_ANY ) const;
	
	LNITEMTYPE GetItemType( const LNString &name ) const;
	
	LNDatetime GetLastAccessed() const;
	
	LNDatetime GetLastModified() const;

	LNSTATUS GetDesignerVersion(LNDESIGNERVERSION *version) const;
	LNSTATUS SetDesignerVersion(LNDESIGNERVERSION version);

	LNString GetName() const;

	NOTEHANDLE GetNoteHandle( LNBOOL keep_object = FALSE );
	
	NOTEID GetNoteID() const;
	
	LNNOTETYPE GetNoteType() const;

	LNSTATUS GetOLEObject( const LNString &attName, LNOLEObject *obj ) const;
	
	LNSTATUS GetOLEObjects( LNOLEObjectArray *oleObjects ) const;

	OID * GetOriginatorID() const;
	
	LNString GetSigner() const;
	
	LNINT GetSize() const;
	
	UNID * GetUniversalID() const;
	
	LNString GetVerifier() const;
	
	LNBOOL HasAttachment( const LNString &attname) const;
	
	LNBOOL HasAttachments() const;
	
	LNBOOL HasItem( const LNString &itemname ) const;

	LNBOOL HasLinks() const;
	
	LNBOOL HasOLEObject( const LNString &attName) const;
	
	LNBOOL HasOLEObjects() const;
	
	LNBOOL IsDeleted();

	LNBOOL IsEncrypted() const;

	LNBOOL IsModified() const;

	LNBOOL IsNull() const
		{ return NoteType == NOTE_CLASS_NONE && !IsDeletionStub(); }

	LNBOOL IsOpen() const;
	
	LNBOOL IsSigned() const;
	
	virtual LNSTATUS Open( LNNOTEOPENFLAGS options=LNNOTEOPENFLAGS_DEFAULT );

	LNSTATUS RefreshNoteHandleFromObject() const;

	LNSTATUS RefreshObjectFromNoteHandle() const;

	LNSTATUS RenameItem( const LNString &oldname, const LNString &newname ) const;
	LNSTATUS RenameItem( LNItem &item, const LNString &newname ) const;
	
	LNSTATUS Save( LNNOTESAVEFLAGS options=LNNOTESAVEFLAGS_DEFAULT );
	
	LNSTATUS Sign() const;

	LNSTATUS Unsign() const;

protected:
	LNNote( LNDatabaseBody *db, NOTEID idnote );

	LNNote & operator=( LNNoteBody *note );

	void Assign( LNDatabaseBody *db, NOTEID id );
	void Assign( LNDatabaseBody *db, const UNID *unid );
	void Assign( LNDatabaseBody *db, NOTEHANDLE handle );

	virtual LNSTATUS CreateNoteBody
		( LNNOTEOPENFLAGS flags = LNNOTEOPENFLAGS_DEFAULT )
		{ return CreateNoteBody(flags, 0, FALSE); }
	virtual LNSTATUS CreateNoteBody
		( LNNOTEOPENFLAGS flags, LNINT otherflags,
		  LNBOOL otherflags_specified = TRUE );
	LNSTATUS CreateNoteBody
		( LNDatabaseBody *dbbody, LNNOTETYPE notetype, NOTEHANDLE handle,
		  LNINT flags = 0, LNBOOL flags_specified = FALSE );

	LNDatabaseBody * GetDatabaseBody() const {return Db.GetDatabaseBody();}

	LNIDTable * GetIDTable() const { return IDTable; }
	void SetIDTable( LNIDTable *idtable );
	
	LNNoteBody * GetNoteBody() const {return (LNNoteBody *)Body;}
	WORD GetNoteClass() const {return NoteType;}

	LNBOOL IsDeletionStub() const { return (NoteID & RRV_DELETED) != 0; }

	virtual void ValidateNoteType( const LNNote & ) const {}
	virtual void ValidateNoteType( const LNNoteBody * ) const {}
	virtual void ValidateNoteType( LNNOTETYPE ) const {}

private:

	LNSTATUS CheckNoteType() const;
	LNDatabase Db;	
	LNIDTable *IDTable;
	NOTEID NoteID;
	TIMEDATE LastModified;
	WORD NoteType;
	LNNOTETYPEEXT NoteTypeExt;
	OID OriginatorID;
};


#ifndef LNJSCRS_HPP
#include "lnjscrs.hpp"
#endif

#ifndef LNITEM_HPP
#include "lnitem.hpp"
#endif

#ifndef LNLINKS_HPP
#include "lnlinks.hpp"
#endif

#ifndef LNCDREC_HPP
#include "lncdrec.hpp"
#endif

#ifndef LNNAMED_HPP
#include "lnnamed.hpp"
#endif

#ifndef LNSEARCH_HPP
#include "lnsearch.hpp"
#endif

#ifndef LNAGENT_HPP
#include "lnagent.hpp"
#endif

#ifndef LNAGENTJ_HPP
#include "lnagentj.hpp"
#endif

#ifndef LNACTION_HPP
#include "lnaction.hpp"
#endif

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif

#ifndef LNFRMST_HPP
#include "lnfrmst.hpp"
#endif

#ifndef LNNAVIG_HPP
#include "lnnavig.hpp"
#endif

#ifndef LNOUTLN_HPP
#include "lnoutln.hpp"
#endif

#ifndef LNPAGE_HPP
#include "lnpage.hpp"
#endif

#ifndef LNSBFORM_HPP
#include "lnsbform.hpp"
#endif

#ifndef LNFORM_HPP
#include "lnform.hpp"
#endif

#ifndef LNFORMFA_HPP
#include "lnformfa.hpp"
#endif

#ifndef LNSCRLB_HPP
#include "lnscrlb.hpp"
#endif

#ifndef LNAPPLT_HPP
#include "lnapplt.hpp"
#endif

#ifndef LNIMAGE_HPP
#include "lnimage.hpp"
#endif

#ifndef LNVIEW_HPP
#include "lnview.hpp"
#endif

#ifndef LNATTACH_HPP
#include "lnattach.hpp"
#endif

#ifndef LNOLEOBJ_HPP
#include "lnoleobj.hpp"
#endif

#ifndef LNNOTEA_HPP
#include "lnnotea.hpp"
#endif

#ifndef LNCALEND_HPP
#include "lncalend.hpp"
#endif

#endif	//LNNOTE_HPP

