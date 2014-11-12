//===========================================================================
//
// Module:  LNRTHOTS.HPP
//
// Description:
//
//	Class Library definition for classes LNRTEmbeddedObject, 
//	LNRTEmbeddedObjectBody, LNRTAttachment, and LNRTAttachmentBody.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTHOTSPOT_HPP
#define LNRTHOTSPOT_HPP

#ifndef LNIMAGE_HPP
#include "lnimage.hpp"
#endif

#ifndef LNGRPHIC_HPP
#include "lngrphic.hpp"
#endif

#ifndef LNATTACH_HPP
#include "lnattach.hpp"
#endif

class LNIMPEXPCL LNRTEmbeddedObject : public LNRTElement
{


public:

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTEMBEDDEDOBJECT; }

protected:

	LNRTEmbeddedObject();
	LNRTEmbeddedObject(const LNRTEmbeddedObject &object);
	LNRTEmbeddedObject(const LNRTObject &object);

	~LNRTEmbeddedObject();

	LNRTEmbeddedObject& operator=(const LNRTObject &object);
	LNRTEmbeddedObject& operator=(const LNRTEmbeddedObject &object);

	LNSTATUS GetData(WORD *length, char **buf) const;

	DWORD GetHotspotFlags() const;

	WORD GetHotspotType() const;

	LNSTATUS SetData(WORD length, WORD dataLength, char *data);

	LNSTATUS SetHotspotFlags(DWORD flags);

	LNSTATUS SetHotspotType(WORD typeOfHotSpot);

private:

	LNRTEmbeddedObjectBody *GetEmbeddedObjectBody() const; 

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};




class LNIMPEXPCL LNRTAttachment : public LNRTEmbeddedObject
{

public:

	LNRTAttachment();
	LNRTAttachment(const LNRTObject &object);
	LNRTAttachment(const LNRTAttachment &fileAttachment);

	LNRTAttachment&	operator=(const LNRTObject &object);
	LNRTAttachment&	operator=(const LNRTAttachment &object);

	LNSTATUS Attach(const LNString &fullFileName, LNBOOL compress = TRUE);
	
	LNSTATUS Detach(const LNString &fullFileName);

	LNSTATUS GetAttachment(LNAttachment *attach) const;
	
	LNString GetAttachmentName() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTATTACHMENT; }

	LNString GetDisplayText() const;

	LNFontStyle GetDisplayTextFontStyle() const;
	
	LNString GetFilename() const;

	LNString GetFilepath() const;

	LNSTATUS GetGraphic(LNGraphic *graphic) const;

	LNSTATUS SetAttachment(const LNAttachment &attachment); 

	LNSTATUS SetDisplayText(const LNString &name);

	LNSTATUS SetDisplayTextFontStyle(const LNFontStyle &fontstyle);

	LNSTATUS SetGraphic(const LNGraphic &graphic);

protected:
		

	LNRTAttachment(const LNAttachment &attachment);
	LNRTAttachment(const LNString &fileName, const LNString &attachmentName);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

private:

	LNRTAttachmentBody	*GetAttachmentBody() const;
};



#endif

