//===========================================================================
//
// Module:  LNHOTSPT.HPP
//
// Description:
//
//  Class library definition for LNHotspot and related classes.
//
//===========================================================================
//
// Copyright (c) 1997-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNHOTSPT_HPP
#define LNHOTSPT_HPP



class LNIMPEXPCL LNHotspot : public LNRTContainer
{

public:
	
	LNHotspot();

	LNHotspot(const LNRTObject &other);
	LNHotspot(const LNHotspot &other);
	
	~LNHotspot();
	
	LNHotspot& operator=(const LNRTObject &other);
	LNHotspot& operator=(const LNHotspot &other);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convertNewLines = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, LNRTObject *newObject = 0);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNHOTSPOT; }

	virtual LNSTATUS GetRichText(const LNRTCursor &start, const LNRTCursor &end,
								 LNRichText *richtext) const;
	virtual LNSTATUS GetRichText(const LNRTObject &object,
								 LNRichText *richtext) const;
	virtual LNSTATUS GetRichText(LNRichText *richtext) const;
	
	LNBOOL GetShowBorder() const;

	void SetShowBorder(LNBOOL border);

	virtual LNSTATUS SetValue(const LNGraphic &graphic);
	virtual LNSTATUS SetValue(const LNString &text, LNBOOL convertNewLines = FALSE);

protected:

	LNHotspot(LNHotspotBody *body);

	LNHotspot& operator=(LNHotspotBody *body);

	LNHotspotBody* GetHotspotBody() const { return (LNHotspotBody *) Body; }

	virtual LNSTATUS GetRichText(const LNRTCursor &start, LNINT poscount,
							 	 LNRichText *richtext) const;
	virtual LNSTATUS GetRichText(const LNRTCursor &cursor, LNRTTYPE type,
								 LNRichText *richtext) const;

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

