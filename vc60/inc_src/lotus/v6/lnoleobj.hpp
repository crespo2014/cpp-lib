//===========================================================================
//
// Module:  LNOLEOBJ.HPP
//
// Description:
//
//  Class library definition for LNOLEObject and related classes.
//
//===========================================================================
//
// Copyright (c) 1997-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNOLEOBJECT_HPP
#define LNOLEOBJECT_HPP

#include "lngrphic.hpp"


//
//		LNOLEObject - access to OLE objects stored in Notes
//

class LNIMPEXPCL LNOLEObject : public LNItem
{

public:
	LNOLEObject (void) {}
	LNOLEObject (const LNItem & object);
	LNOLEObject (const LNOLEObject & oleObject) : LNItem (oleObject) {}

	~LNOLEObject (void) {}

	LNOLEObject &		operator= (const LNItem & object);
	LNOLEObject &		operator= (const LNOLEObject & oleObject)
		{ LNItem::operator= (oleObject); return (*this); }
	
	LNSTATUS			Detach (const LNString & fullFileName);

	virtual LNCLASSID	GetClassID (void) const { return LNCLASS_LNOLEOBJECT; }

	LNBOOL				GetScriptedFlag (void) const;
	LNBOOL				GetRunReadOnlyFlag (void) const;
	LNBOOL				GetIsOLEControlFlag (void) const;
	LNBOOL				GetFitToWindowFlag (void) const;
	LNBOOL				GetFitBelowFieldsFlag (void) const;
	LNBOOL				GetUpdateFromDocumentFlag (void) const;
	LNBOOL				GetIncludeRichTextFlag (void) const;

	LNString			GetFieldName (void) const;
	LNSTATUS			GetOLEClassID (LNOLEGUID *oleClassID) const;
	LNOLECLIPBOARDFORMAT GetOLEClipboardFormat (void) const;
	LNString			GetOLEUserType (void) const;
	LNString			GetAttachmentName (void) const;
	LNSTATUS			GetOLEILockBytes (LNILockBytes *pILockBytes) const;
	LNSTATUS			GetOLEIStorage (DWORD accessMode, LNIStorage *pIStorage) const;
	
	LNBOOL				IsInRichText (void) const;

	LNSTATUS			SetScriptedFlag (LNBOOL newFlag);
	LNSTATUS			SetRunReadOnlyFlag (LNBOOL newFlag);
	LNSTATUS			SetIsOLEControlFlag (LNBOOL newFlag);
	LNSTATUS			SetFitToWindowFlag (LNBOOL newFlag);
	LNSTATUS			SetFitBelowFieldsFlag (LNBOOL newFlag);
	LNSTATUS			SetUpdateFromDocumentFlag (LNBOOL newFlag);
	LNSTATUS			SetIncludeRichTextFlag (LNBOOL newFlag);

	LNSTATUS			SetFieldName (const LNString & newFieldName);
	LNSTATUS			SetOLEClassID (LNOLEGUID *oleClassID);
	LNSTATUS			SetOLEUserType (const LNString & newType);

protected:

private:
	LNOLEObjectBody	*	GetOLEObjectBody (void) const;
};

//
//		LNOLEObjectArray - Array of LNOLEObject objects
//

class LNIMPEXPCL LNOLEObjectArray : public LNItemArray
{
public:
	LNOLEObjectArray (void) {}
	LNOLEObjectArray (const LNOLEObjectArray &other) : LNItemArray(other) {}

	~LNOLEObjectArray (void) {}

	LNOLEObjectArray & operator= (const LNOLEObjectArray &other)
		{ LNItemArray::operator= (other); return (*this); }

	LNOLEObject operator[] (LNINT n) const
		{ return (LNItemArray::operator[] (n)); }

	LNCLASSID GetClassID (void) const { return (LNCLASSID_LNOLEOBJECTARRAY); }
};


#endif

