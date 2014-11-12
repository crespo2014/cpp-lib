//===========================================================================
//
// Module:	LNRT.HPP
//
// Description:
//
//	Class declarations of the LNRichText item classes, and the CD Record 
//	parsers.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRT_HPP
#define LNRT_HPP



#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

#ifndef LNMBLOCK_HPP
#include "lnmblock.hpp"
#endif

#ifndef LNFONT_HPP
#include "lnfont.hpp"
#endif

#ifndef LNRTOBJ_HPP
#include "lnrtobj.hpp"
#endif

#ifndef LNFILE_HPP
#include "lnfile.hpp"
#endif

#ifndef IXPORT_H
#define IXPORT_H


#include <ixedit.h>
#include <ixport.h>
#include <osenv.h>
#include <ossignal.h>
#include <oserr.h>
#endif


#include "lndb.hpp"




class LNIMPEXPCL LNRichText : public LNItem
{

public:

	LNRichText();
	LNRichText(const LNString &text);
	LNRichText(const LNItem &item);
	LNRichText(const LNRichText &richtext);
	
	~LNRichText();
	
	LNRichText& operator=(const LNItem &item);
	LNRichText& operator=(const LNRichText &richtext);

	LNRichText& operator<<(const LNString &text);
	LNRichText& operator<<(const LNRichText &richtext);
	LNRichText& operator<<(const LNRTObject &object);

	LNSTATUS Append(const LNString &text, LNBOOL convertNewLines = FALSE);
	LNSTATUS Append(const LNRichText &richtext);
	LNSTATUS Append(const LNRTObject &object, LNRTObject *newObject = 0);
	LNSTATUS Append(const LNRTObject &object, LNBOOL addParagraph, 
		LNRTObject *newObject = 0);

	LNSTATUS AppendRenderedDocument(LNDocument &doc);
	LNSTATUS AppendRenderedDocument(LNDocument &doc, const LNString &form);
	LNSTATUS AppendRenderedDocument(LNDocument &doc, LNForm &form);

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
		const LNString &attachmentname = "", LNBOOL compress = TRUE, 
		LNRTAttachment *newrtattachment = 0 ) const;
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

	LNSTATUS CreateControlledSection(const LNString &title, 
		LNRTCursor *start, LNRTCursor *end, LNSection *newSection = 0);

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

	LNSTATUS CreateHorizontalRule(const LNNUMBER width, const LNNUMBER height, 
		LNRTCursor *end, LNHorizontalRule *rule = 0);

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

	LNSTATUS CreateOLEObject(const LNString &path, const LNOLEGUID &guid,
		LNOLECLIPBOARDFORMAT displayFormat, const LNString &progID,
        const LNString &userType, LNRTCursor *cursor,
		const LNString &attachmentName = "", LNRTOLEObject *pNewObject = 0) const;
	LNSTATUS CreateOLEObject(const LNRTOLEObject &rtObj, LNRTCursor *cursor,
		LNRTOLEObject *pNewObject = 0) const;
	LNSTATUS CreateOLEObject(const LNOLEObject &oleObj,
		LNOLECLIPBOARDFORMAT displayFormat, const LNString & progID,
		LNRTCursor *cursor, LNRTOLEObject *pNewObject = 0) const;

	LNSTATUS CreateRTComputedSubform(const LNFormula &formula, 
		LNRTCursor *cursor, LNRTComputedSubform *newObject = 0);
	LNSTATUS CreateRTSubform(const LNString &subformname, 
		LNRTCursor *cursor, LNRTSubform *newObject = 0);
	LNSTATUS CreateRTSubform(const LNSubform &subform, 
		LNRTCursor *cursor, LNRTSubform *newObject = 0);

	LNSTATUS CreateStringSection(const LNString &title, LNRTCursor *start, 
		LNRTCursor *end, LNSection *newSection = 0);
	LNSTATUS CreateFormulaSection(const LNFormula &title, LNRTCursor *start, 
		LNRTCursor *end, LNSection *newSection = 0);
    LNSTATUS CreateSection(LNRTCursor *start, LNRTCursor *end,
		LNSection *newSection = 0)
		{ return CreateStringSection("", start, end, newSection); }

	LNSTATUS CreateTable(LNINT rows, LNINT cols, LNRTCursor *cursor, 
		LNTable *newTable = 0);

	LNSTATUS CreateTextPopup(const LNString &popupText, LNRTCursor *start, 
		LNRTCursor *end, LNTextPopup *newPopup = 0);

    LNSTATUS CreateURLLink(const LNString &URL, LNRTCursor *start, 
		LNRTCursor *end, LNURLLink *newLink = 0);

	LNSTATUS CreateURLLinkFormula(const LNFormula &urlFormula, LNRTCursor *start, 
	LNRTCursor *end, LNURLLink *newLink = 0);

	LNSTATUS CreateViewLink(const LNDatabase &db, const LNViewFolder &view, 
		LNRTCursor *cursor, LNViewLink *newLink = 0);
	LNSTATUS CreateViewLink(const TIMEDATE DBreplicaID, const UNID *viewUNID, 
		const LNString &description, const LNNotesSession *session, 
		LNRTCursor *cursor, LNViewLink *newLink = 0);

	LNSTATUS Delete(LNRTCursor *start, LNRTCursor *end);
	LNSTATUS Delete(LNRTCursor *start, LNINT poscount);
	LNSTATUS Delete(LNRTObject *object);

	LNSTATUS DeleteAttachment(const LNString& name, LNBOOL del = TRUE);
	LNSTATUS DeleteAttachment(const LNAttachment *att, LNBOOL del = TRUE);

	LNSTATUS DeleteFormField(const LNString &name);

	LNSTATUS DeleteOLEObject(const LNString &name, LNBOOL del = TRUE);
	LNSTATUS DeleteOLEObject(LNRTOLEObject &rtObj, LNBOOL del = TRUE);

	LNSTATUS DeleteRTSubform(const LNString &name);
	
    LNSTATUS Export(const LNString &filename, const LNRTCursor &start, 
		const LNRTCursor &end,const LNString &exporttype = "");
    LNSTATUS Export(const LNString &filename, const LNString &exportdll, 
		const LNRTCursor &start, const LNRTCursor &end, 
		const LNString &altlib = "");    

	LNSTATUS GetAttachment(const LNString& name, LNRTAttachment *att) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRICHTEXT; }
	
	LNSTATUS GetCursor(LNRTCursor *cursor) const;					 

	LNSTATUS GetEndCursor(LNRTCursor *cursor) const;					 

	LNSTATUS GetFontStyle(const LNRTCursor &cursor, LNFontStyle *style) const;

	LNSTATUS GetFormField(const LNString &name, LNFormField *field) const;

	LNSTATUS GetOLEObject(const LNString &name, LNRTOLEObject *rtObj) const;

	LNBOOL GetPageBreakBefore(const LNRTCursor &cursor);

	LNSTATUS GetParagraphStyle(const LNRTCursor &cursor, 
		LNParagraphStyle *style) const;

	LNSTATUS GetRichText(const LNRTCursor &start, const LNRTCursor &end,
		LNRichText *richtext) const;
	LNSTATUS GetRichText(const LNRTObject &object,
		LNRichText *richtext) const;

	LNRTContainer& GetRTContainer() const;

	LNSTATUS GetRTSubform(const LNString &name, LNRTSubform *rtSubform) const;

	LNSTATUS GetText(LNString *text, LNRTCursor *cursor=0) const;
	LNSTATUS GetText(const LNRTCursor &start, const LNRTCursor &end, 
		LNString *text, LNRTCursor *cursor=0) const;

	LNRTTYPE GetType() const;
	
	LNBOOL HasAttachments() const;

	LNBOOL HasOLEObjects (void) const;

	virtual LNINT GetValueSize() const;

    LNSTATUS Import(const LNString &filename, LNRTCursor *cursor, 
		const LNString &importtype = "");
    LNSTATUS Import(const LNString &filename, const LNString &importdll, 
		LNRTCursor *cursor, const LNString &altlib = "");

	LNSTATUS Insert(const LNString &text, LNRTCursor *cursor, 
		LNBOOL convertNewLines = FALSE);
	LNSTATUS Insert(const LNRichText &richtext, LNRTCursor *cursor);
	LNSTATUS Insert(const LNRTObject &object, LNRTCursor *cursor, 
		LNRTObject *newObject = 0);

	LNSTATUS InsertImageResource( const LNImageResource &image, 
		LNINT width, LNINT height, LNRTCursor *cursor, LNRTObject *rtImage = 0);

	LNSTATUS InsertImageResource( const LNString &imageresourcename, 
		LNINT width, LNINT height, LNRTCursor *cursor, LNRTObject *rtImage = 0);

//	LNSTATUS InsertImageResourceFormula( const LNFormula &formula, LNRTCursor *cursor);

	LNSTATUS InsertSharedField( const LNSharedField &sharedfield, 
		LNRTCursor *cursor, LNFormField *newField = 0 );

	LNSTATUS InsertSharedField(const LNString &sharedfieldname, 
		LNRTCursor *cursor, LNFormField *newField = 0);

	LNSTATUS InsertSubform(const LNSubform &subform, LNRTCursor *cursor, 
		LNRTSubform *newRTSubform = 0);

	LNBOOL IsEmpty() const;

	LNBOOL IsPlainText() const;

	LNSTATUS MergeNextParagraph(LNRTCursor *cursor);

	LNSTATUS MergeParagraphs(LNRTCursor *start, LNRTCursor *end);

	LNSTATUS MergePreviousParagraph(LNRTCursor *cursor);   

	virtual LNSTATUS SetFontStyle(const LNRTCursor &start, 
		const LNRTCursor &end, const LNFontStyle &style, 
		LNSETFONTSTYLEFLAGS mask = LNSETFONTSTYLEFLAGS_ALL);
	LNSTATUS SetFontStyle(const LNRTCursor &cursor, const LNFontStyle &style);

	LNSTATUS SetPageBreakBefore(const LNRTCursor &cursor, LNBOOL pageBreak);

	LNSTATUS SetParagraphStyle(const LNRTCursor &start, const LNRTCursor &end,
		const LNParagraphStyle &style);
	LNSTATUS SetParagraphStyle(const LNRTCursor &cursor, 
		const LNParagraphStyle &style);

	LNSTATUS SetValue(const LNString &text, LNBOOL convertNewLines = FALSE);

	LNSTATUS StartNewParagraph(LNRTCursor *cursor);


protected:

	LNRichText(LNRichTextBody *body);

	LNRichText& operator=(LNRichTextBody *body);

	LNSTATUS Append(const LNString &text, LNBOOL convert, 
		LNNoteBody *noteBody);

	LNSTATUS GetCurrentMemoryBlock(LNINT size, LNINT *offset,
		LNMemoryBlock **memoryBlock);

	LNSTATUS GetRichText(const LNRTCursor &start, LNINT poscount,
		LNRichText *richtext) const;
	LNSTATUS GetRichText(const LNRTCursor &cursor, LNRTTYPE type,
		LNRichText *richtext) const;

	LNRichTextBody* GetRichTextBody() const { return (LNRichTextBody *) Body; }
	
	LNBOOL IsValid() const;

	virtual LNSTATUS Save(const char *newname = 0);

};

#ifndef LNRTCONT_HPP
#include "lnrtcont.hpp"
#endif


// Informational data passed to the rich text parser error recovery function

struct LNRTPARSERERRORDATA
{
	const LNItem *Item; // Rich text item, not fully initialized
	LNINT     Offset;   // From the beginning of the rich text, excluding the initial type word
	WORD      CDSig;    // The signature of the cd record at the given offset
	LNINT     CDSize;   // The size of the cd record at the given offset
	LNSTATUS  Status;   // Error status found
};


// Function prototype for rich text error recovery function. This is called
// when the rich text parser encounters a problem, and can be set to throw an
// error or continue processing.

typedef LNSTATUS (*LNRTPARSERERRORHANDLER)(const LNRTPARSERERRORDATA &);



#ifndef LNCDREC_HPP
#include "lncdrec.hpp"
#endif

#ifndef LNRTELEM_HPP
#include "lnrtelem.hpp"
#endif

#ifndef LNRTCRSR_HPP
#include "lnrtcrsr.hpp"
#endif

#ifndef LNPARAGR_HPP
#include "lnparagr.hpp"
#endif

#ifndef LNPARSTL_HPP
#include "lnparstl.hpp"
#endif

#ifndef LNRTLINK_HPP
#include "lnrtlink.hpp"
#endif

#ifndef LNFORMF_HPP
#include "lnformf.hpp"
#endif

#ifndef LNRTTABL_HPP
#include "lnrttabl.hpp"
#endif

#ifndef LNHOTSPT_HPP
#include "lnhotspt.hpp"
#endif

#ifndef LNRSCLNK_HPP
#include "lnrsclnk.hpp"
#endif

#ifndef LNHOTLNK_HPP
#include "lnhotlnk.hpp"
#endif

#ifndef LNRTHOTS_HPP
#include "lnrthots.hpp"
#endif

#ifndef LNRTOLEOBJECT_HPP
#include "lnrtoleo.hpp"
#endif

#ifndef LNRTBITMAP_HPP
#include "lnbitmap.hpp"
#endif

#ifndef LNMETAFL_HPP
#include "lnmetafl.hpp"
#endif

#ifndef LNIMAGE_HPP
#include "lnimage.hpp"
#endif

#ifndef LNGRPHIC_HPP
#include "lngrphic.hpp"
#endif

#ifndef LNURLLINK_HPP
#include "lnurllnk.hpp"
#endif

#ifndef LNTXTPOPUP_HPP
#include "lntxtpup.hpp"
#endif

#ifndef LNFORMULAPOPUP_HPP
#include "lnformup.hpp"
#endif

#ifndef LNCOMPTEXT_HPP
#include "lncmptxt.hpp"
#endif

#ifndef LNSCRIPT_HPP
#include "lnscript.hpp"
#endif

#ifndef LNSACTION_HPP
#include "lnsactio.hpp"
#endif

#ifndef LNBUTTON_HPP
#include "lnbutton.hpp"
#endif

#ifndef LNRTJAVA_HPP
#include "lnrtjava.hpp"
#endif

#ifndef LNRTSBFM_HPP
#include "lnrtsbfm.hpp"
#endif

#ifndef LNACTIONHOTSPOT_HPP
#include "lnacths.hpp"
#endif

#ifndef LNSECTIO_HPP
#include "lnsectio.hpp"
#endif

#ifndef LNHRULE_HPP
#include "lnhrule.hpp"
#endif

#ifndef LNLAYOUT_HPP
#include "lnlayout.hpp"
#endif

#ifndef LNLAYELM_HPP
#include "lnlayelm.hpp"
#endif

#ifndef LNLAYBTN_HPP
#include "lnlaybtn.hpp"
#endif

#ifndef LNLAYFLD_HPP
#include "lnlayfld.hpp"
#endif

#ifndef LNLAYGRA_HPP
#include "lnlaygra.hpp"
#endif

#ifndef LNLAYGBT_HPP
#include "lnlaygbt.hpp"
#endif

#ifndef LNLAYTXT_HPP
#include "lnlaytxt.hpp"
#endif

#endif

