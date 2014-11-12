//===========================================================================
//
// Module:		LNHRULE.HPP
//
// Description:
//
//		Class library definition for the LNHorizontalRule class.
//
//===========================================================================
//
// Copyright (c) 2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNHRULE_HPP
#define LNHRULE_HPP

#define LNDEFAULTHRULEHEIGHT	DEFAULTHRULEHEIGHT
#define LNDEFAULTHRULEWIDTH		DEFAULTHRULEWIDTH

class LNIMPEXPCL LNHorizontalRule : public LNRTElement
{

public:
	
	LNHorizontalRule();

	LNHorizontalRule(LNNUMBER width, LNNUMBER height);
	LNHorizontalRule(const LNRTObject &object);
	LNHorizontalRule(const LNHorizontalRule &hrule);

	~LNHorizontalRule();

	LNHorizontalRule& operator=(const LNRTObject &object);
	LNHorizontalRule& operator=(const LNHorizontalRule &hrule);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNHORIZONTALRULE; }

	LNColor GetFillColor() const;

	LNColor GetGradientColor() const;

	LNNUMBER GetHeight() const;
			
	LNSTATUS GetHTMLTags (LNHTMLTags * pTags) const;

	LNUNITS GetUnits() const;

	LNBOOL GetUseFillColor() const;

	LNBOOL GetUseGradientColor() const;

	LNBOOL GetUse3DShading() const;

	LNNUMBER GetWidth() const;

	LNBOOL IsWidthPercent() const;

	LNSTATUS SetUse3DShading(LNBOOL useshading);

	LNSTATUS SetFillColor(LNColor color);

	LNSTATUS SetGradientColor(LNColor color);

	LNSTATUS SetHeight(LNNUMBER width);
	
	LNSTATUS SetHTMLTags (const LNHTMLTags & tags);

	void SetUnits(LNUNITS units);

	LNSTATUS SetUseFillColor(LNBOOL usecolor);

	LNSTATUS SetUseGradientColor(LNBOOL usegradientcolor);

	LNSTATUS SetWidthPercent(LNINT width);

	LNSTATUS SetWidth(LNNUMBER width);

protected:

	LNHorizontalRuleBody* GetHorizontalRuleBody () const { return (LNHorizontalRuleBody *) Body; }

private:	
	LNHorizontalRule(LNHorizontalRuleBody *body);

	LNHorizontalRule& operator=(LNHorizontalRuleBody *body);


	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

