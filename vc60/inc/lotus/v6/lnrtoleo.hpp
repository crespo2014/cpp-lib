//===========================================================================
//
// Module:  LNRTOLEO.HPP
//
// Description:
//
//  Class library definition for LNRTOLEObject and related classes.
//
//===========================================================================
//
// Copyright (c) 1997-1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTOLEOBJECT_HPP
#define LNRTOLEOBJECT_HPP

#ifndef LNIMAGE_HPP
#include "lnimage.hpp"
#endif

#ifndef LNGRPHIC_HPP
#include "lngrphic.hpp"
#endif

#ifndef LNOLEOBJ_HPP
#include "lnoleobj.hpp"
#endif

	// Type of embedded OLE object - fully embedded or link
enum LNOLEOBJECTTYPE
{
	LNOLEOBJECTTYPE_UNKNOWN		= 0,
	LNOLEOBJECTTYPE_EMBEDDED	= 1,
	LNOLEOBJECTTYPE_AUTOLINK	= 2,
	LNOLEOBJECTTYPE_MANUALLINK	= 3
};

typedef DWORD LNRTOLEOBJECTFLAGS;
#define LNRTOLEOBJECTFLAGS_NEW_OBJECT			0x00000010
#define LNRTOLEOBJECTFLAGS_PASTED				0x00000020
#define LNRTOLEOBJECTFLAGS_SAVE_WHEN_CHANGED	0x00000040
#define LNRTOLEOBJECTFLAGS_NO_VISUALIZE			0x00000080


class LNIMPEXPCL LNRTOLEObject : public LNRTElement
{
	friend class LNRichTextBody;
	friend class LNRTContainerBody;
	friend class LNRTInputParser;
	friend class LNRTOLEObjectBody;

public:
	LNRTOLEObject (void);
	LNRTOLEObject (const LNRTObject& object);
	LNRTOLEObject (const LNRTOLEObject& oleObject);

	~LNRTOLEObject (void);

	LNRTOLEObject&		operator= (const LNRTObject& object);
	LNRTOLEObject&		operator= (const LNRTOLEObject& oleObject);
	
	LNSTATUS			Detach (const LNString & fullFileName, LNBOOL overWrite = FALSE);

	LNString			GetAttachmentName (void) const;

	virtual LNCLASSID	GetClassID (void) const { return LNCLASS_LNRTOLEOBJECT; }

	LNBOOL				GetNewObjectFlag (void) const;
	LNBOOL				GetPastedFlag (void)  const;
	LNBOOL				GetSaveWhenChangedFlag (void) const;
	LNBOOL				GetNoVisualizeFlag (void) const;

	LNSTATUS			GetGraphic (LNGraphic *graphic) const;
	LNString			GetOLEClassName (void) const;
	LNOLECLIPBOARDFORMAT GetOLEClipboardFormat (void) const;
	LNSTATUS			GetOLEObject (LNOLEObject *oleObject) const;
	LNOLEOBJECTTYPE		GetOLEObjectType (void) const;

	LNSTATUS			SetNewObjectFlag (LNBOOL newFlag);
	LNSTATUS			SetPastedFlag (LNBOOL newFlag);
	LNSTATUS			SetSaveWhenChangedFlag (LNBOOL newFlag);
	LNSTATUS			SetNoVisualizeFlag (LNBOOL newFlag);

	LNSTATUS			SetGraphic (const LNGraphic & newGraphic);
	LNSTATUS			SetOLEClassName (const LNString & newName);
	LNSTATUS			SetOLEClipboardFormat (LNOLECLIPBOARDFORMAT newFormat);
	LNSTATUS			SetOLEObjectType (LNOLEOBJECTTYPE newType);

protected:
	LNRTOLEObject (const LNOLEObject& baseObject);
	LNRTOLEObject (const LNNote &note, LNOLECLIPBOARDFORMAT displayFormat,
		const LNString &progID, LNString * pAttachmentName);
	LNRTOLEObject (LNRTOLEObjectBody * pBody);

	LNRTOLEObjectBody	*GetRTOLEObjectBody () const;
	LNSTATUS			SetOLEObject (const LNOLEObject & newObject); 

	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

