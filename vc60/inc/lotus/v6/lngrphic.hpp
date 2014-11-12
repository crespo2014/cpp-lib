//===========================================================================
//
// Module:  LNGRPHIC.HPP
//
// Description:
//
//		Class library definition for the LNRTGraphic and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGRPHIC_HPP
#define LNGRPHIC_HPP


//	class definition for LNRTGraphic

enum LNGRAPHICFORMAT
{
	LNGRAPHICFORMAT_VERSION1 = CDGRAPHIC_VERSION1,
	LNGRAPHICFORMAT_VERSION2 = CDGRAPHIC_VERSION2,
	LNGRAPHICFORMAT_VERSION3 = CDGRAPHIC_VERSION3
};

enum LNGRAPHICTYPE
{
	LNGRAPHICTYPE_GIF = CDIMAGETYPE_GIF,
	LNGRAPHICTYPE_JPEG = CDIMAGETYPE_JPEG,
	LNGRAPHICTYPE_BITMAP,
	LNGRAPHICTYPE_IMAGE_RESOURCE,
	LNGRAPHICTYPE_FORMULA,
	LNGRAPHICTYPE_UNKNOWN
};

class LNIMPEXPCL LNGraphic : public LNRTElement
{

public:

	LNGraphic();
	LNGraphic(const LNRTObject &other);
	LNGraphic(const LNGraphic &graphic);
	LNGraphic(const LNFormula &formula);

	~LNGraphic();

	LNGraphic&			operator=(const LNRTObject &object);
	LNGraphic&			operator=(const LNGraphic &graphic);

	LNSTATUS			GetBitmap(LNBitmap *bitmap) const;

	virtual LNCLASSID	GetClassID() const { return LNCLASSID_LNGRAPHIC; };
	
	LNINT				GetDestinationHeight(LNBOOL *pixelunits = 0) const;
	
	LNINT				GetDestinationWidth(LNBOOL *pixelunits = 0) const;

	LNGRAPHICFORMAT		GetGraphicFormat() const;

	LNGRAPHICTYPE       GetGraphicType() const;

	LNSTATUS			GetHTMLTags (LNHTMLTags * pTags) const;

	LNSTATUS			GetJavaScript(LNJavaScript *javascript) const;

	LNSTATUS			GetMetafile(LNMetafile *metaFile) const;

	LNBOOL				IsResized() const;

	LNSTATUS			SetDestinationHeight(LNINT height, LNBOOL pixelunits = TRUE); 

	LNSTATUS			SetDestinationWidth(LNINT width, LNBOOL pixelunits = TRUE); 

 	LNSTATUS			SetHTMLTags (const LNHTMLTags & tags);


	LNSTATUS			SetImageFormat(LNIMAGEFORMAT imageformat);
	
	LNSTATUS			SetJavaScript(const LNJavaScript &javascript);

protected:
	LNGraphic (LNGraphicBody * pBody);

	LNGraphic &			operator=(LNGraphicBody * pBody);

	virtual void		ValidateRTType(const LNRTObject &other) const;
	virtual void		ValidateRTType(const LNRTObjectBody *other) const;

private:
	
	LNGraphicBody		*GetGraphicBody() const;
};


#endif

