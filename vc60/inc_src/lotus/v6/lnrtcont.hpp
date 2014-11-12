//===========================================================================
//
// Module:  LNRTCONT.HPP
//
// Description:
//
//  Class library definition for LNRTContainer, LNRTContainerBody, 
//	LNRTBaseContainerBody and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTCONT_HPP
#define LNRTCONT_HPP

#ifndef LNRTOBJB_HPP
#include "lnrtobjb.hpp"
#endif


class LNIMPEXPCL LNRTContainer : public LNRTObject
{								

public:
	
	LNRTContainer();
	LNRTContainer(const LNRTObject &object);
	LNRTContainer(const LNRTContainer &container);

	~LNRTContainer();
	
	LNRTContainer& operator=(const LNRTObject &object);
	LNRTContainer& operator=(const LNRTContainer &container);

	LNRTContainer& operator<<(const LNString &text);
	LNRTContainer& operator<<(const LNRichText &richtext);
	LNRTContainer& operator<<(const LNRTObject &object);

	virtual LNSTATUS Append(const LNString &text, LNBOOL convert = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, LNRTObject *newObj = 0);

	LNSTATUS ClearHotspot(LNHotspot *hotspot);

	LNSTATUS CreateActionHotspot(const LNFormula &formula, LNRTCursor *start,
		LNRTCursor *end, LNActionHotspot *newHotspot = 0);
	LNSTATUS CreateActionHotspot(const LNLotusScript &script, LNRTCursor *start,
		LNRTCursor *end, LNActionHotspot *newHotspot = 0);
	LNSTATUS CreateActionHotspot(const LNSimpleAction &action, LNRTCursor *start,
		LNRTCursor *end, LNActionHotspot *newHotspot = 0);
	LNSTATUS CreateActionHotspot(const LNSimpleActions &actions, LNRTCursor *start,
		LNRTCursor *end, LNActionHotspot *newHotspot = 0);

	LNSTATUS CreateAnchorLink(const LNViewFolder &view, 
		const LNAnchorLocation &loc, LNRTCursor *cursor, 
		LNAnchorLink *newLink = 0);
	LNSTATUS CreateAnchorLink(const LNViewFolder &view, 
		const LNDocument &document, const LNString &anchorText, 
		LNRTCursor *cursor, LNAnchorLink *newLink = 0);
	LNSTATUS CreateAnchorLink(const LNAnchorLocation &loc, LNRTCursor *cursor, 
		LNAnchorLink *newLink = 0);
	LNSTATUS CreateAnchorLink(const LNDocument &document, const LNString &anchorText, 
		LNRTCursor *cursor, LNAnchorLink *newLink = 0);
	LNSTATUS CreateAnchorLink(const TIMEDATE DBreplicaID, 
		const UNID *viewUNID, const UNID *noteUNID, 
		const LNString &description, const LNString &anchorText, 
		const LNNotesSession *session, LNRTCursor *cursor, 
		LNAnchorLink *newLink = 0);

	LNSTATUS CreateAnchorLocation(const LNString &anchorText, 
		LNRTCursor *cursor, LNAnchorLocation *newAnchorLocation = 0);

	LNSTATUS CreateAttachment(const LNString &path, LNRTCursor *cursor, 
		LNRTAttachment *newrtattachment ) const;
	LNSTATUS CreateAttachment(const LNString &path,  LNRTCursor *cursor,
		const LNString &attachmentname = "", LNBOOL compress = TRUE, LNRTAttachment *newrtattachment = 0 ) const;
	LNSTATUS CreateAttachment(const LNRTAttachment &rtatt, 
		LNRTCursor *cursor, LNRTAttachment *newrtattachment = 0 ) const;
	LNSTATUS CreateAttachment(const LNAttachment &att, LNRTCursor *cursor, 
		LNRTAttachment *newrtattachment = 0 ) const;

    LNSTATUS CreateButton(const LNString &label, const LNFormula &formula, 
		LNRTCursor *cursor, LNButton *newButton = 0);
	LNSTATUS CreateButton(const LNString &label, const LNSimpleAction &action, 
		LNRTCursor *cursor, LNButton *newButton = 0);
	LNSTATUS CreateButton(const LNString &label, const LNSimpleActions &actions, 
		LNRTCursor *cursor, LNButton *newButton = 0);
	LNSTATUS CreateButton(const LNString &label, const LNLotusScript &script, 
		LNRTCursor *cursor, LNButton *newButton = 0);


	LNSTATUS CreateComputedText(const LNFormula &formula, LNRTCursor *cursor,
		LNComputedText *computedText = 0);

	LNSTATUS CreateDatabaseLink(const LNDatabase &db, LNRTCursor *cursor, 
		LNDatabaseLink *newLink = 0);
	LNSTATUS CreateDatabaseLink(const TIMEDATE DBreplicaID, 
		const LNString &description, const LNNotesSession *session, 
		LNRTCursor *cursor, LNDatabaseLink *newLink = 0);

	LNSTATUS CreateDocumentLink(const LNViewFolder &view, 
		const LNDocument &document, LNRTCursor *cursor, 
		LNDocumentLink *newLink = 0);
	LNSTATUS CreateDocumentLink(const LNDocument &document, LNRTCursor *cursor, 
		LNDocumentLink *newLink = 0);
	LNSTATUS CreateDocumentLink(const TIMEDATE DBreplicaID,
		const UNID *viewUNID, const UNID *noteUNID, const LNString &desc, 
		const LNNotesSession *session, LNRTCursor *cursor, 
		LNDocumentLink *newLink = 0);

	LNSTATUS CreateFormField(const LNString &name, LNRTTYPE type, 
		LNRTCursor *cursor, LNFormField *newField = 0);

	LNSTATUS CreateFormulaPopup(const LNFormula &formula, LNRTCursor *start,
		LNRTCursor *end, LNFormulaPopup *newPopup = 0);

	LNSTATUS CreateHorizontalRule(const LNNUMBER width, const LNNUMBER height, LNRTCursor *cursor, 
		LNHorizontalRule *rule = 0);

	LNSTATUS CreateJavaApplet (const LNString & baseClassName,
		LNRTCursor * cursor, LNRTJavaApplet * newApplet = 0);
	LNSTATUS CreateJavaApplet (const LNString & baseClassName,
		const LNString & alternateText, const LNString & appletFile,
		const LNString & appletPath, LNRTCursor * cursor,
		LNRTJavaApplet * newApplet = 0);
	LNSTATUS CreateJavaApplet (const LNString & baseClassName,
		const LNString & alternateText, const LNText & appletFileList,
		const LNString & appletPath, LNRTCursor * cursor,
		LNRTJavaApplet * newApplet = 0);

	LNSTATUS CreateLayoutRegion (LNRTCursor * cursor, LNLayout * newLayout = 0);

	LNSTATUS CreateLinkHotspot(const LNDatabaseLink &link, LNRTCursor *start,
		LNRTCursor *end, LNLinkHotspot *newLink = 0);

	LNSTATUS CreateLinkHotspot(const LNNamedElement &namedelement, LNRTCursor *start,
		LNRTCursor *end, LNLinkHotspot *newLink = 0);

	LNSTATUS CreateOLEObject (const LNString & path, const LNOLEGUID & guid,
		LNOLECLIPBOARDFORMAT displayFormat, const LNString & progID,
		const LNString & userType, LNRTCursor * cursor,
		const LNString & attachmentName, LNRTOLEObject * pNewObject);
	LNSTATUS CreateOLEObject (const LNRTOLEObject & rtObj, LNRTCursor * cursor,
		LNRTOLEObject * pNewObject);
	LNSTATUS CreateOLEObject (const LNOLEObject & oleObj,
		LNOLECLIPBOARDFORMAT displayFormat, const LNString & progID,
		LNRTCursor * cursor, LNRTOLEObject * pNewObject);

	LNSTATUS CreateRTComputedSubform(const LNFormula &formula, 
		LNRTCursor *cursor, LNRTComputedSubform *newObject = 0);
	LNSTATUS CreateRTSubform(const LNSubform &subform, 
		LNRTCursor *cursor, LNRTSubform *newObject = 0);
	LNSTATUS CreateRTSubform(const LNString &subformname, 
		LNRTCursor *cursor, LNRTSubform *newObject = 0);

    LNSTATUS CreateStringSection(const LNString &title, LNRTCursor *start, 
		LNRTCursor *end, LNSection *newSection = 0, LNBOOL controlled = FALSE);
	LNSTATUS CreateFormulaSection(const LNFormula &titleformula,
		LNRTCursor *start, LNRTCursor *end, LNSection *newSection = 0);
    LNSTATUS CreateSection(LNRTCursor *start, LNRTCursor *end,
		LNSection *newSection = 0)
		{ return CreateStringSection("", start, end, newSection); }

    LNSTATUS CreateTable(LNINT rows, LNINT cols, LNRTCursor *cursor, 
		LNTable *newTable = 0);

	LNSTATUS CreateTextPopup(const LNString &popupText, LNRTCursor *start, 
		LNRTCursor *end, LNTextPopup *newPopup = 0);

    LNSTATUS CreateURLLink(const LNString &URL, LNRTCursor *start, 
		LNRTCursor *end, LNURLLink *newLink = 0);

	LNSTATUS CreateURLLinkFormula(const LNFormula &urlFormula,
										   LNRTCursor *start,
										   LNRTCursor *end, LNURLLink *newLink=0);

	LNSTATUS CreateViewLink(const LNDatabase &db, const LNViewFolder &view, 
		LNRTCursor *cursor, LNViewLink *newLink = 0);
	LNSTATUS CreateViewLink(const TIMEDATE DBreplicaID, const UNID *viewUNID,
		const LNString &description, const LNNotesSession *session, 
		LNRTCursor *cursor, LNViewLink *newLink = 0);

	virtual LNSTATUS Delete(LNRTCursor *start, LNRTCursor *end);
	virtual LNSTATUS Delete(LNRTCursor *start, LNINT poscount);
	virtual LNSTATUS Delete(LNRTObject *object);

	LNSTATUS DeleteFormField(const LNString &fieldname);

	LNSTATUS DeleteRTSubform(const LNString &subformname);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTCONTAINER; }

	virtual LNSTATUS GetCursor(LNRTCursor *cursor) const;					 
	
	virtual LNSTATUS GetEndCursor(LNRTCursor *cursor) const;					 

	LNSTATUS GetFirstChild(LNRTObject *child) const;

	LNSTATUS GetFontStyle(const LNRTCursor &cursor, LNFontStyle *style) const;

	LNSTATUS GetFormField(const LNString &name, LNFormField *field) const;

	LNSTATUS GetLastChild(LNRTObject *child) const;

	LNSTATUS GetParagraphStyle(const LNRTCursor &cursor, 
		LNParagraphStyle *style) const;

	virtual LNSTATUS GetRichText(const LNRTCursor &start, 
		const LNRTCursor &end, LNRichText *richtext) const;
	virtual LNSTATUS GetRichText(const LNRTObject &object,
		LNRichText *richtext) const;

	LNSTATUS GetRTSubform(const LNString &name, LNRTSubform *rtSubform) const;

	virtual LNSTATUS Insert(const LNString &text, LNRTCursor *cursor, 
		LNBOOL convertNewLines = FALSE);
	virtual LNSTATUS Insert(const LNRichText &richtext, LNRTCursor *cursor);
	virtual LNSTATUS Insert(const LNRTObject &object, LNRTCursor *cursor, 
		LNRTObject *newObject = 0);

	LNSTATUS InsertImageResource(const LNImageResource &imageresource,
									LNINT widthInPixels, 
									LNINT heightInPixels,
									LNRTCursor *cursor, 
									LNRTObject *rtImage = 0);

	LNSTATUS InsertImageResource(const LNString &imageresourcename,
									LNINT widthInPixels, 
									LNINT heightInPixels,
									LNRTCursor *cursor, 
									LNRTObject *rtImage = 0);

	LNSTATUS InsertImageResourceFormula(const LNFormula &formula,
									LNRTCursor *cursor, 
									LNRTObject *rtImage = 0);

	LNSTATUS InsertSharedField(const LNSharedField &sharedfield, 
		LNRTCursor *cursor, LNFormField *newField = 0);

	LNSTATUS InsertSharedField(const LNString &sharedfieldname, 
		LNRTCursor *cursor, LNFormField *newField = 0);

	LNSTATUS InsertSubform(const LNSubform &subform, LNRTCursor *cursor, 
		LNRTSubform *newRTSubform = 0);

	
	LNSTATUS MergeNextParagraph(LNRTCursor *cursor);

	LNSTATUS MergeParagraphs(LNRTCursor *start, LNRTCursor *end);

	LNSTATUS MergePreviousParagraph(LNRTCursor *cursor);

	LNSTATUS SetFontStyle(const LNRTCursor &start, const LNRTCursor &end,
		const LNFontStyle &style, LNSETFONTSTYLEFLAGS mask = LNSETFONTSTYLEFLAGS_ALL);
	LNSTATUS SetFontStyle(const LNRTCursor &cursor, const LNFontStyle &style); 

	LNSTATUS SetParagraphStyle(const LNRTCursor &start, const LNRTCursor &end,
		const LNParagraphStyle &style);
	LNSTATUS SetParagraphStyle(const LNRTCursor &cursor, const LNParagraphStyle &style);

	virtual LNSTATUS SetValue(const LNString &text, LNBOOL convertNewLines = FALSE);

	LNSTATUS StartNewParagraph(LNRTCursor *cursor);

protected:

	LNRTContainer(LNRTContainerBody *body);

	LNRTContainer& operator=(LNRTContainerBody *body);

	LNSTATUS AdjustParagraphStyle(const LNParagraphStyle &style, 
		LNParagraphStyle *newstyle) const;

	LNSTATUS Append(const LNRTObject &object, LNBOOL addParagraph,
		LNRTObject *newObject = 0);

	LNSTATUS AppendChild(LNRTObject *child);

	virtual LNSTATUS ConvertLinks(const LNRichText &origRT, 
		const LNRichText &destRT);

	virtual LNSTATUS FindParagraphStyle(const LNRTObject &currObject, 
		LNParagraphStyle &style) const;

	LNSTATUS FindSameParagraphStyle(const LNParagraphStyle &style,
		LNPABDefinition *pabdef, LNPABStyleName *stylename, 
		LNPABHide *pabhide) const;

	WORD GetNewPABID();

	virtual LNSTATUS GetRichText(const LNRTCursor &start, LNINT poscount,
		LNRichText *richtext) const;
	virtual LNSTATUS GetRichText(const LNRTCursor &cursor, LNRTTYPE type,
		LNRichText *richtext) const;

	LNRTContainerBody*	GetRTContainerBody() const { return (LNRTContainerBody *) Body; }

	virtual LNBOOL IsSelectionValid(const LNRTCursor &start, 
		const LNRTCursor &end, LNBOOL split, LNRTSelection *selection) const;
	virtual LNBOOL IsSelectionValid(const LNRTCursor &start, 
		LNINT poscount, LNBOOL split, LNRTSelection *selection) const;
	virtual LNBOOL IsSelectionValid(const LNRTCursor &cursor, LNRTTYPE type,
		LNRTSelection *selection) const;
	virtual LNBOOL IsSelectionValid(const LNRTObject &object, 
		LNRTSelection *selection) const;

	LNSTATUS ResetPABReferences(LNPABReference *start, LNPABReference *end,
		WORD PABID, WORD sourcePABID);

	// Called from LNRichTextBody only
	virtual LNSTATUS SetTopContainer(LNRichTextBody *rtbody);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};





class LNIMPEXPCL LNStylizedText : public LNRTContainer
{

public:
	
	LNStylizedText();
	LNStylizedText(const LNString &text);
	LNStylizedText(const LNRTObject &object);
	LNStylizedText(const LNStylizedText &stylizedText);

	LNStylizedText& operator=(const LNRTObject &object);
	LNStylizedText& operator=(const LNStylizedText &stylizedText);
	
	~LNStylizedText();
	
	virtual LNSTATUS Append(const LNString &text, LNBOOL convert = FALSE);
	virtual LNSTATUS Append(const LNRichText &richtext);
	virtual LNSTATUS Append(const LNRTObject &object, LNRTObject *newObject = 0);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNSTYLIZEDTEXT; }

	virtual LNSTATUS GetFontStyle(LNFontStyle *style) const;

	virtual LNSTATUS SetFontStyle(const LNFontStyle &style);

protected:

	LNINT GetByteCount() const;

	LNINT GetCharacterCount() const;

	LNStylizedTextBody* GetStylizedTextBody() const { return (LNStylizedTextBody *) Body; }

	LNSTATUS SplitText(LNINT splitpos);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

