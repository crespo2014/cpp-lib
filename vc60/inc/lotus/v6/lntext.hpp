//===========================================================================
//
// Module:		LNTEXT.HPP
//
// Description:
//
//		Class library definitions for LNText related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNTEXT_HPP
#define LNTEXT_HPP

//
//	Class definition for LNTextElement.
//
class LNIMPEXPCL LNTextElement : public LNNotesClass
{
public:
	LNTextElement( const LNTextElement &other );

	~LNTextElement();

	LNTextElement& operator=( const LNString &string );
	LNTextElement& operator=( const LNTextElement &textelem )
		{ return operator=(textelem.operator LNString()); }

	operator LNString() const;

	LNCLASSID GetClassID() const { return LNCLASSID_LNTEXTELEMENT; }

private:
	LNTextElement();	// Disabled.
	LNTextElement( LNTextBody *textb, LNINT index );

	LNTextBody *Body;
	LNINT Index;	
};

//
//	Class definition for LNText.
//
class LNIMPEXPCL LNText : public LNItem
{
public:
	LNText() {}
	LNText( const LNText &other ) : LNItem(other) {}
	LNText( const LNItem &other );

	~LNText() {}

	LNText& operator=( const LNText &other );
	LNText& operator=( const LNItem &other );

	LNText& operator<<( const LNText &text );
	LNText& operator<<( const LNString &string );
	LNText& operator<<( const LNTextElement &textelem );

	LNTextElement operator[]( LNINT n ) const;

	LNSTATUS Append( const LNText &text ) { return Insert(GetCount(), text); }
	LNSTATUS Append( const LNString &string )
		{ return Insert(GetCount(), string); }
	LNSTATUS Append( const LNTextElement &textelem )
		{ return Insert(GetCount(), textelem.operator LNString()); }

	LNSTATUS Delete( LNINT n, LNINT count = 1 );

	LNSTATUS DeleteAll();

	LNSTATUS FindEntry( const LNString &searchstring, LNINT *foundindex );

	LNCLASSID GetClassID() const { return LNCLASSID_LNTEXT; }

	LNINT GetCount() const;

	LNSTATUS GetText( LNString *text, const LNString &separator = ";" ) const;

	LNSTATUS Insert( LNINT n, const LNText &text );
	LNSTATUS Insert( LNINT n, const LNString &string );
	LNSTATUS Insert( LNINT n, const LNTextElement &textelem )
		{ return Insert(n, textelem.operator LNString()); }

	LNSTATUS SetValue( const LNText &text );
	LNSTATUS SetValue( const LNString &string, LNBOOL convert = TRUE );
	LNSTATUS SetValue( const LNTextElement &textelem )
		{ return SetValue(textelem.operator LNString()); }

protected:
	void Assign( LNNoteBody *noteb, LNTextBody *textb )
		{ LNItem::Assign(noteb, (LNItemBody *) textb); }

	LNTextBody * GetTextBody() const { return (LNTextBody *) GetItemBody(); }

private:
};


#endif

