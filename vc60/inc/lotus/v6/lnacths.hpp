//==========================================================================================
//
// Module:	LNACTIONHOTS.HPP
//
// Description
//
//  Class Library description for LNActionHotspot and LNActionHotspotBody.
//
//==========================================================================================
//
// Copyright (c) 1998-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNACTIONHOTSPOT_HPP
#define LNACTIONHOTSPOT_HPP



class LNIMPEXPCL LNActionHotspot : public LNHotspot
{

public:

	LNActionHotspot();
	LNActionHotspot(const LNRTObject &object);
	LNActionHotspot(const LNActionHotspot &hotspot);

	LNActionHotspot(const LNFormula &formula, const LNString &text);
	LNActionHotspot(const LNFormula &formula, const LNGraphic &graphic);

	LNActionHotspot(const LNJavaScript &javascript, const LNString &text);
	LNActionHotspot(const LNJavaScript &javascript, const LNGraphic &graphic);

	LNActionHotspot(const LNLotusScript &script, const LNString &text);
	LNActionHotspot(const LNLotusScript &script, const LNGraphic &graphic);

	LNActionHotspot(const LNSimpleAction &action, const LNString &text);
	LNActionHotspot(const LNSimpleAction &action, const LNGraphic &graphic);
	LNActionHotspot(const LNSimpleActions &actions, const LNString &text);
	LNActionHotspot(const LNSimpleActions &actions, const LNGraphic &graphic);

	~LNActionHotspot();

	LNActionHotspot& operator=(const LNRTObject &object);
	LNActionHotspot& operator=(const LNActionHotspot &hotspot);

	LNACTIONTYPE GetActionType() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNACTIONHOTSPOT; }

	LNSTATUS GetFormula(LNFormula *formula) const;

	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS GetJavaScript(LNJavaScript *javascript) const;

	LNSTATUS GetLotusScript(LNLotusScript *script) const;

	LNSTATUS GetSimpleActions(LNSimpleActions *actions) const;

	LNSTATUS GetTargetFrame(LNString *framename) const;
	
	LNSTATUS SetFormula(const LNFormula &formula);

 	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	LNSTATUS SetJavaScript(const LNJavaScript &javascript);

	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNSTATUS SetSimpleAction(const LNSimpleAction &action);

	LNSTATUS SetSimpleActions(const LNSimpleActions &actions);


	LNSTATUS SetTargetFrame(const LNString &framename);

protected:

	LNActionHotspot(LNActionHotspotBody *body);

	LNActionHotspot(const LNFormula &formula);
	LNActionHotspot(const LNJavaScript &javascript);
	LNActionHotspot(const LNLotusScript &script);
	LNActionHotspot(const LNSimpleAction &action);
	LNActionHotspot(const LNSimpleActions &actions);

	LNActionHotspot& operator=(LNActionHotspotBody *body);

	LNActionHotspotBody* GetActionHotspotBody() const { return (LNActionHotspotBody *) Body; }	

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};



#endif

