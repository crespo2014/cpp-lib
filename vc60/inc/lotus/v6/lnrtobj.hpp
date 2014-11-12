//===========================================================================
//
// Module:  LNRTOBJ.HPP
//
// Description:
//
//  Class library definition for LNRTObject, LNRTObjectBody and related classes.
//	(The core rich text editing engine).
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTOBJ_HPP
#define LNRTOBJ_HPP


// Exposed Rich Text Types
 
#include "lnrttype.hpp"


LNBOOL ISRTTYPE(LNRTTYPE type1, LNRTTYPE type2);


typedef LNINT LNRTOBJECTBODYFLAGS;
typedef LNINT LNRTSEARCHFLAGS;

#define LNRTSEARCHFLAGS_DEFAULT 0
#define LNRTSEARCHFLAGS_MATCH_ACCENT INTL_ACCENT_SENSITIVE
#define LNRTSEARCHFLAGS_MATCH_CASE INTL_CASE_SENSITIVE


// LNRTCOPYOPTIONS is for internal use only, but it must be exposed in the toolkit
// because it is a parameter to a protected function on an exposed class.

enum LNRTCOPYOPTIONS
{
	LNRTCOPYOPTIONS_COPY_VALUE_RESET_PTRS,   // Same as (old) copychildren = FALSE
	LNRTCOPYOPTIONS_COPY_VALUE_IGNORE_PTRS,
	LNRTCOPYOPTIONS_COPY_VALUE_AND_CHILDREN  // Same as (old) copychildren = TRUE
};


#define LNRTOBJECT_OFFSET_AFTER_ELEMENT_MASK	(0x80000000)

class LNIMPEXPCL LNRTObject : public LNSmartPtr
{



public:
	
	LNRTObject();
	LNRTObject(const LNRTObject &object);

	~LNRTObject();

	LNRTObject& operator=(const LNRTObject &object);
	
	virtual LNBOOL operator==(const LNRTObject &object) const;

	virtual LNBOOL operator!=(const LNRTObject &object) const;

	LNSTATUS Copy(const LNRTObject &object);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTOBJECT; }

	LNSTATUS GetNextSibling(LNRTObject *object) const;
	
	LNSTATUS GetParentContainer(LNRTTYPE type, LNRTContainer *container) const;

	LNSTATUS GetPreviousSibling(LNRTObject *object) const;

	LNSTATUS GetText(LNString *buf) const;
	LNSTATUS GetText(const LNRTCursor &start, const LNRTCursor &end, LNString *buf) const;

	virtual LNRTTYPE GetType() const;
	
	LNBOOL IsType(LNRTTYPE type) const;

	LNSTATUS GetCDRecords(LNCompositeDataArray *array);

protected:

	LNRTObject(LNRTObjectBody *body);
	LNRTObject(LNStylizedTextBody *stylizedTextBody, LNINT offset);

	LNRTObject& operator=(LNRTObjectBody *body);

	virtual LNSTATUS CopyRTObject(const LNRTObject &object, LNRTCOPYOPTIONS options);

	virtual LNSTATUS FindContainer(LNRTTYPE type, LNRTObject *basecontainer) const;



	virtual LNINT GetNormalizedOffset() const;

	virtual LNINT GetRawOffset() const { return (Offset & (~LNRTOBJECT_OFFSET_AFTER_ELEMENT_MASK)); }

	LNSTATUS GetParentContainer(LNRTObject *basecontainer) const;
	
	LNRTBaseContainerBody* GetRTBaseContainerBody() const;

	LNRTObjectBody* GetRTObjectBody() const { return (LNRTObjectBody *) Body; }

   	virtual LNINT GetSize() const;

	virtual LNBOOL HasOffset() const;

	LNSTATUS InsertNextSibling(LNRTObject *object);

	LNSTATUS InsertPreviousSibling(LNRTObject *object);

	LNBOOL IsAfterElement() const { return (0 != (Offset & LNRTOBJECT_OFFSET_AFTER_ELEMENT_MASK)); }

	LNBOOL IsDirty() const;

	LNBOOL IsLeftOf(const LNRTObject &object) const;

	virtual LNBOOL IsValid() const;

	LNSTATUS RemoveThis(LNBOOL preserveChildren = FALSE);

	void SetAfterElement (LNBOOL newFlag);

	virtual LNSTATUS SetDirty(LNBOOL dirty = TRUE);

	virtual void SetOffset(LNINT newOffset);

	virtual void SetRTChar(LNStylizedTextBody *stylizedTextBody, LNINT offset);

	virtual LNSTATUS Update(LNINT offset, LNRichTextBody *rtItem, LNINT *newoffset);

	virtual void ValidateRTType(const LNRTObject &other) const {}
	virtual void ValidateRTType(const LNRTObjectBody *other) const {}
		
private:


	LNINT Offset; // 1-based
};





typedef struct
{
	LNRTObject StartRTObject; 
	LNRTObject EndRTObject;
	LNRTObject ClosestCommonAncestor; 
	LNRTObject ObjectAfterSelection;
} LNRTSelection;



#endif

