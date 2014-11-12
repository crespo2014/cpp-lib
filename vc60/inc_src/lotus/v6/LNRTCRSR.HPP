//===========================================================================
//
// Module:  LNRTCRSR.HPP
//
// Description:
//
//  Class library definition for LNRTCursor and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTCRSR_HPP
#define LNRTCRSR_HPP


class LNIMPEXPCL LNRTCursor : public LNSmartPtr
{


public:

	LNRTCursor();
	LNRTCursor(const LNRTCursor &cursor);

	~LNRTCursor();
	
	LNRTCursor& operator=(const LNRTCursor &cursor);

	LNRTCursor operator+(LNINT n) const;

	LNRTCursor& operator++();    // prefix
	LNRTCursor& operator++(int); // postfix

	LNRTCursor& operator+=(LNINT n);
	
	LNRTCursor operator-(LNINT n) const;
	
	LNRTCursor& operator--();    // prefix
	LNRTCursor& operator--(int); // postfix
	
	LNRTCursor& operator-=(LNINT n);
	
	LNSINT operator-(const LNRTCursor &cursor) const;
	
	LNBOOL operator<(const LNRTCursor &cursor) const;
	
	LNBOOL operator<=(const LNRTCursor &cursor) const;
	
	LNBOOL operator>(const LNRTCursor &cursor) const;
	
	LNBOOL operator>=(const LNRTCursor &cursor) const;
	
	LNBOOL operator==(const LNRTCursor &cursor) const;
	
	LNBOOL operator!=(const LNRTCursor &cursor) const;

	LNSTATUS Copy(const LNRTCursor &cursor);

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNRTCURSOR; }
	
	LNSTATUS GetFontStyle(LNFontStyle *style) const;

	LNSTATUS GetObject(LNRTObject *object) const
		{ return GetRTObject(object); }

	LNSTATUS GetParagraphStyle(LNParagraphStyle *style) const;

	LNSTATUS GetParentContainer(LNRTTYPE type, LNRTContainer *container) const;

	LNSTATUS GotoEnd(LNRTTYPE type);
	LNSTATUS GotoEnd(const LNRTContainer &container);

	LNSTATUS GotoFirst(char ch);
	LNSTATUS GotoFirst(LNRTTYPE type, LNRTObject *object = 0);
	LNSTATUS GotoFirst(const LNString &searchstring);

	LNSTATUS GotoLast(char ch);
	LNSTATUS GotoLast(LNRTTYPE type, LNRTObject *object = 0);
	LNSTATUS GotoLast(const LNString &searchstring);
	
	LNSTATUS GotoNext(char ch);
	LNSTATUS GotoNext(LNRTTYPE type, LNRTObject *object = 0);
	LNSTATUS GotoNext(const LNString &searchstring);
	
	LNSTATUS GotoObject(const LNRTObject &object);

	LNSTATUS GotoPrevious(char ch);
	LNSTATUS GotoPrevious(LNRTTYPE type, LNRTObject *object = 0);
	LNSTATUS GotoPrevious(const LNString &searchstring);

	LNSTATUS GotoStart(LNRTTYPE type);
	LNSTATUS GotoStart(const LNRTContainer &container);

	LNBOOL IsAtEnd() const;
	
	LNBOOL IsAtStart() const;

	LNSTATUS RemoveScope();

	LNSTATUS SetScope(const LNRTContainer &container);

	LNSTATUS SetSearchOptions(LNRTSEARCHFLAGS options);
	
protected:

	LNRTCursor(const LNRTElement &element, LNBOOL after = FALSE);
	LNRTCursor(LNStylizedTextBody *stylizedTextBody, LNINT offset, LNBOOL after = FALSE);

	LNRTCursor& operator=(LNRTCursorBody *body);

	LNSTATUS Assign(LNStylizedTextBody *stylizedTextBody, LNINT offset, LNBOOL after = FALSE);


	LNSTATUS GetNextObject(LNRTObject *object) const;

	LNINT GetOffset() const;

	LNSTATUS GetPreviousObject(LNRTObject *object) const;

	LNRTCursorBody* GetRTCursorBody() const { return (LNRTCursorBody *) Body; }

	LNBOOL IsInsertablePosition(LNRTTYPE type) const;

	LNBOOL IsValid() const;
	LNBOOL IsValid(const LNRTObject &basecontainer) const;
	LNBOOL IsValid(const LNRTBaseContainerBody *containerBody) const;

private:

	LNSTATUS GetRTObject(LNRTObject *object) const;
};




#endif

