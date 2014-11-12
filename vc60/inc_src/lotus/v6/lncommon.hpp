//===========================================================================
//
// Module:	LNCOMMON.HPP
//
// Description:
//
// 		Class library definition for common C++ API classes.
//
//===========================================================================
//
// Copyright (c) 1996-2003 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNCOMMON_HPP
#define LNCOMMON_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

//---------------------------------------------------------------------------
// 	Class name:	LNNotesClass
//
//	Description:
//
//	Abstract base class for all classes in Notes C++ API.
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNNotesClass
{

public:
	virtual ~LNNotesClass();

	static void operator delete( void *object )
		{ LNDelete(object); }

	static void * operator new( size_t size )
		{ return LNNew(size); }	

	virtual LNSTATUS Close() { return LNNOERROR; }

	virtual LNCLASSID GetClassID() const = 0;

	virtual const char * GetClassName() const
#ifdef EBCDIC_TRANSLATION_REQUIRED
		{ return LNGetClassName(GetClassID(), TRUE); }
#else
		{ return LNGetClassName(GetClassID(), FALSE); }
#endif

	virtual LNNotesSession * GetSession() const
		{ return Session; }

	virtual LNBOOL IsBody() const { return FALSE; }

	virtual LNBOOL IsOnHeap() const;

protected:
	LNNotesClass();
	LNNotesClass( const LNNotesSession *session );
	LNNotesClass( const LNNotesClass &object );

	LNNotesClass & operator=( const LNNotesClass &object );

	void SetSession( const LNNotesSession *session )
		{Session = (LNNotesSession *)session;}

private:
	LNElement *Element;
	LNNotesSession *Session;

#ifdef LNNOTESCLASS_OBJECT_LIST

	LNNotesClass *Next, *Previous;

#endif

};

//---------------------------------------------------------------------------
// 	Class name:	LNColor
//
//	Description:
//
//	LNColor represents a Notes extended color value.  The extended colors
//	introduced in Release 5 of Notes and Domino can support full 24-bit
//	RGB color values.
//---------------------------------------------------------------------------

	// This declaration is stolen from the Notes core;  it's something
	// they hadn't exposed yet that is needed when processing COLOR_VALUE
	// records from ODS structures.
#ifndef _COLOR_VALUE
#define _COLOR_VALUE	690
#endif

class LNIMPEXPCL LNColor
{
public:
	LNColor (const LNCOLOR r4Color = LNCOLOR_BLACK);
	LNColor (const LNINT red, const LNINT green, const LNINT blue);
	LNColor (const COLOR_VALUE & colorValue);
	LNColor (const LNColor & other );

	~LNColor (void) { ; }

	LNColor & operator= (const LNCOLOR r4Color);
	LNColor & operator= (const COLOR_VALUE & colorValue);
	LNColor & operator= (const LNColor & other);

	LNBOOL operator== (const LNColor & other) const;
	LNBOOL operator== (const LNCOLOR other) const;
	LNBOOL operator!= (const LNColor & other) const;
	LNBOOL operator!= (const LNCOLOR other) const;

	virtual LNCLASSID GetClassID (void) const
		{ return (LNCLASSID_LNCOLOR); }

	LNINT GetBlueValue (void) const { return (m_RGBColor.Component3); }
	LNINT GetGreenValue (void) const { return (m_RGBColor.Component2); }
	LNINT GetRedValue (void) const { return (m_RGBColor.Component1); }

	LNINT GetRGBColor (void) const;

	LNCOLOR GetRelease4Color (void) const { return (m_r4Color); }

	operator LNCOLOR (void) const { return (m_r4Color); }

	COLOR_VALUE GetColorValue (void) const { return (m_RGBColor); }

	operator COLOR_VALUE () const { return (m_RGBColor); }

	LNBOOL GetIsRGB (void) const;

	LNBOOL GetHasNoColor (void) const;

	LNBOOL GetUseSystemDefaultColor (void) const;

	LNBOOL GetApplicationFlag1 (void) const;
	LNBOOL GetApplicationFlag2 (void) const;
	LNBOOL GetApplicationFlag3 (void) const;
	LNBOOL GetApplicationFlag4 (void) const;

	void SetBlueValue (const LNINT blue);
	void SetGreenValue (const LNINT green);
	void SetRedValue (const LNINT red);

	void SetColor (const LNCOLOR r4Color);
	void SetColor (const LNINT red, const LNINT green, const LNINT blue);
	void SetColor (const COLOR_VALUE & colorValue);

	void SetRGBColor (const LNINT newColor);

	void SetHasNoColor (LNBOOL newFlag);

	void SetIsRGB (LNBOOL newFlag);

	void SetUseSystemDefaultColor (LNBOOL newFlag);

	void SetApplicationFlag1 (LNBOOL newFlag);
	void SetApplicationFlag2 (LNBOOL newFlag);
	void SetApplicationFlag3 (LNBOOL newFlag);
	void SetApplicationFlag4 (LNBOOL newFlag);

protected:
	LNINT MapR4ColorToRGB (const LNCOLOR r4Color);
	LNCOLOR MapRGBToR4Color (const LNINT red, const LNINT green, const LNINT blue) const;

private:
	COLOR_VALUE		m_RGBColor;
	LNCOLOR			m_r4Color;
};

//---------------------------------------------------------------------------
// 	Class name:	LNNumber
//
//	Description:
//
//	LNNumber represents a Notes LNNUMBER (double), and provides functions to
//	convert and manipulate LNNUMBER data.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNNumber
{

public:
	LNNumber() { Value = 0; }
	LNNumber( const LNNUMBER &number ) { Value = number; }
	LNNumber( const LNString &string, LNSTATUS *error = 0 );
	LNNumber
		( const LNString &string, const LNNumberFormat &nfmt,
		  const LNInternational &ifmt, LNSTATUS *error = 0 );
	LNNumber( const LNNumber &number ) { Value = number.Value; }

	~LNNumber() {}

	LNNumber & operator=( const LNNumber &number )
		{ if (&number != this) Value = number.Value; return *this; }
	LNNumber & operator=( const LNNUMBER &number )
		{ Value = number; return *this; }
	LNNumber & operator=( const LNString &string );
	
	operator LNNUMBER() const { return Value; }
	
	LNSTATUS GetText( LNString *text ) const;
	LNSTATUS GetText
		( const LNNumberFormat &nfmt, const LNInternational &ifmt,
		  LNString *text ) const;

	LNNUMBER GetValue() const { return Value; }

	LNSTATUS SetText
		( const LNString &string, const LNNumberFormat &nfmt,
		  const LNInternational &ifmt )
		{
			return SetText(string, (LNNumberFormat *) &nfmt,
						   (LNInternational *) &ifmt);
		}

private:
	LNNUMBER Value;

	LNSTATUS GetText
		( LNString *text, LNNumberFormat *nfmt, LNInternational *ifmt ) const;

	LNSTATUS SetText
		( const LNString &string, LNNumberFormat *nfmt = 0,
		  LNInternational *ifmt = 0 );
};

//---------------------------------------------------------------------------
// 	Class name:	LNNumberFormat
//
//	Description: Display format for number fields in a form or view.
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNNumberFormat : public LNNotesClass
{
friend class LNNumber;

public:
	LNNumberFormat();
	LNNumberFormat( const NFMT &nfmt )
		{ memcpy(&NumberFormat, &nfmt, sizeof(NFMT)); }
	LNNumberFormat( const LNNumberFormat &other );

	~LNNumberFormat() {}

	LNNumberFormat & operator=( const LNNumberFormat &other );
	LNNumberFormat & operator=( const NFMT &nfmt )
		{ memcpy(&NumberFormat, &nfmt, sizeof(NFMT)); return *this; }

	LNINT GetAttributes() const
		{return (LNINT) NumberFormat.Attributes;}

	virtual LNCLASSID GetClassID() const
		{ return LNCLASSID_LNNUMBERFORMAT; }

	LNINT GetDigits() const
		{return (LNINT)NumberFormat.Digits;}

	LNNUMBERFORMAT GetFormat() const
		{return (LNNUMBERFORMAT)NumberFormat.Format;}

	NFMT * GetNFMT() { return &NumberFormat; }

	LNBOOL GetParentheses() const;

	LNBOOL GetPercentage() const;

	LNBOOL GetPunctuated() const;

	LNBOOL GetVaryingDigits() const;
	
	LNSTATUS SetDigits( LNINT digits );

	LNSTATUS SetFormat( LNNUMBERFORMAT format );

	void SetParentheses( LNBOOL parentheses );

	void SetPercentage( LNBOOL percentage );

	void SetPunctuated( LNBOOL punctuated );

	void SetVaryingDigits( LNBOOL varying );

private:
	NFMT NumberFormat;	// Structure that contains all number display information.
};

//---------------------------------------------------------------------------
// 	Class name:	LNObjectList
//
//	Description:
//
//	LNObjectList manages an unsorted doubly-linked list of objects, and is used
//	by classes that need to track objects that they've allocated, so that they
//	can destroy those objects later. This class is for internal use only.
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNObjectList : public LNNotesClass
{

public:
	LNObjectList();

	~LNObjectList();

	virtual LNSTATUS AddObject( LNNotesClass *object );

	void DeleteAllObjects();

	LNSTATUS DeleteObject( LNNotesClass *object );

	virtual LNCLASSID GetClassID() const
		{ return LNCLASSID_LNOBJECTLIST; }

	LNINT GetCount() const
		{ return Count; }

	LNNotesClass * GetFirst() const;

	LNNotesClass * GetLast() const;

	LNNotesClass * GetNext( const LNNotesClass * object ) const;

	LNNotesClass * GetPrevious( const LNNotesClass * object ) const;

	LNSTATUS RemoveObject( LNNotesClass *object );

protected:
	LNINT Count;
	LNElement *First, *Last;

	void AddElement( LNElement *element );

	LNSTATUS CheckObject( const LNNotesClass *object ) const;

	void DeleteElement( LNElement *element );

	LNSTATUS GetElement
		( const LNNotesClass *object, LNElement **element ) const;

	// copy constructor and assignment operator are undefined to prevent
	// anyone from using them

private:
	LNObjectList( const LNObjectList &objlist );
	LNObjectList & operator=( const LNObjectList &objlist );
};

//---------------------------------------------------------------------------
// 	Class name:	LNSmartPtr
//
//	Description:
//
//	LNSmartPtr is the base class for all smart pointer classes. Note that the
//	copy constructor and assignment operator in each derived class must invoke
//	the base class versions. Note also that LNSmartPtr does not inherit from
//	LNNotesClass, to keep it as small as possible.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNSmartPtr
{
public:
	LNSmartPtr() { Body = 0; }
	LNSmartPtr( LNBody *body );
	LNSmartPtr( const LNSmartPtr &ptr );

	~LNSmartPtr() { DeleteBody(); }

	LNSmartPtr & operator=( const LNSmartPtr &ptr );
	LNSmartPtr & operator=( LNBody *body );

	virtual LNBOOL DeleteBody();

	virtual LNCLASSID GetClassID() const = 0;

	virtual const char * GetClassName() const
#ifdef EBCDIC_TRANSLATION_REQUIRED
		{ return LNGetClassName(GetClassID(), TRUE); }
#else
		{ return LNGetClassName(GetClassID(), FALSE); }
#endif

	virtual LNNotesSession * GetSession() const
	{
		if (Body)
			return ((LNNotesClass *) Body)->GetSession();
		return 0;
	}
	//	{ return (Body ? ((LNNotesClass *) Body)->GetSession() : 0); }

	virtual LNBOOL IsNull() const { return Body == 0; }

protected:
	LNBody *Body;
};

//---------------------------------------------------------------------------
// 	Class name:	LNUniversalID
//
//	Description:
//
//	LNUniversalID represents a Notes universal ID (UNID), and provides
//	functions to convert an UNID to a string and versa.
//---------------------------------------------------------------------------

class LNIMPEXPCL LNUniversalID
{
public:
	LNUniversalID();
	LNUniversalID( const UNID *unid );
	LNUniversalID( const LNString &unid );
	LNUniversalID( const LNUniversalID &unid );

	~LNUniversalID() {}

	LNUniversalID & operator=( const UNID *unid );
	LNUniversalID & operator=( const LNString &unid );
	LNUniversalID & operator=( const LNUniversalID &unid );
	
	operator const UNID *() const { return &UniversalID; }
	
	LNString GetText() const;

	const UNID * GetUniversalID() const { return &UniversalID; }
	LNSTATUS GetUniversalID( UNID *unid ) const;

	LNBOOL IsNull() const;

private:
	UNID UniversalID;
};


#endif	//LNCOMMON_HPP

