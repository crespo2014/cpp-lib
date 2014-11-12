//===========================================================================
//
// Module:		LNITEM.HPP
//
// Description:
//
//		Class library definitions for LNItem related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNITEM_HPP
#define LNITEM_HPP

LNITEMTYPE LNMapItemType( WORD nsfitem_type, WORD item_flags, LNCLASSID classid );
void LNUnmapItemType( LNITEMTYPE item_type, WORD *nsf_itemtype,	WORD *nsf_itemflags );

//
//	Class definition for LNItem.
//
class LNIMPEXPCL LNItem : public LNSmartPtr
{

public:
	LNItem() {}
	LNItem( const LNItem &other ) : LNSmartPtr(other) {}

	~LNItem();

	LNItem & operator=( const LNItem &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNITEM;}

	LNBOOL GetExpandOnSave() const;
	
	LNITEMFLAGS GetFlags() const;

	LNDatetime GetLastModified() const;

	LNString GetName() const;

	LNNote GetNote() const;

	LNITEMTYPE GetType() const;

	LNINT GetValueSize() const;

	LNBOOL IsDeleted() const;

	LNBOOL IsModified() const {return IsDirty();}

	LNBOOL IsNoteItem() const;

	LNBOOL IsType( LNITEMTYPE type ) const;

	LNSTATUS Read( LNINT offset, LNINT num, void *buf );

	LNSTATUS ReadODS( LNINT offset, WORD ods_type, void *buf );

	void SetExpandOnSave( LNBOOL flag );

	LNSTATUS Write( LNINT offset, LNINT num, void *buf );

	LNSTATUS WriteODS( LNINT offset, WORD ods_type, void *buf );

protected:
	LNItem( LNNoteBody *, LNItemBody *itemb ) :
		 LNSmartPtr((LNBody *) itemb) {}

	LNItem & operator=( LNItemBody *itemb );

	LNSTATUS Alloc( LNINT size, LNITEMTYPE type );

	void Assign( LNNoteBody *noteb, LNItemBody *itemb );

	LNSTATUS Expand( LNINT offset, LNINT num );

	LNItemBody * GetItemBody() const {return (LNItemBody *)Body;}

	LNBOOL IsDirty() const;

	LNSTATUS Shorten( LNINT offset, LNINT num );
};


//
//	Class definition for LNItemArray.
//
class LNIMPEXPCL LNItemArray : public LNSmartPtr
{

public:
	LNItemArray();
	LNItemArray( const LNItemArray &other );

	~LNItemArray();

	LNItemArray & operator=( const LNItemArray &other );

	LNItem operator[]( LNINT n ) const;

	LNCLASSID GetClassID() const {return LNCLASSID_LNITEMARRAY;}

	LNINT GetCount() const;

	LNNote GetNote() const;

private:
	void Assign( LNNoteBody *noteb, LNItemArrayBody *itemab );
};


#ifndef LNRT_HPP
#include "lnrt.hpp"
#endif

#ifndef LNDTS_HPP
#include "lndts.hpp"
#endif

#ifndef LNNUM_HPP
#include "lnnum.hpp"
#endif

#ifndef LNTEXT_HPP
#include "lntext.hpp"
#endif

#ifndef LNFORMUL_HPP
#include "lnformul.hpp"
#endif

#endif

