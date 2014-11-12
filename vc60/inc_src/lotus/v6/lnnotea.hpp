//===========================================================================
//
// Module:		LNNOTEA.HPP
//
// Description:
//
//		Class library definition for LNNoteArray and related classes.
//
//===========================================================================
//
// Copyright (c) 1998-2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNNOTEA_HPP
#define LNNOTEA_HPP
//
//	Class definition for LNNoteArray.
//
class LNIMPEXPCL LNNoteArray : public LNSmartPtr
{

public:
	LNNoteArray();
	LNNoteArray( const LNDatabase &db );

	LNNoteArray( const LNNoteArray &other );
	LNNoteArray( const LNViewFolder &viewfolder );
	LNNoteArray( const LNVFNavigator &viewfolder );

	virtual ~LNNoteArray();
	
	LNNoteArray & operator=( const LNNoteArray &other );

	LNNote operator[]( LNINT n ) const;

	virtual LNSTATUS Add( const LNNote &note );
	virtual LNSTATUS Add( NOTEID noteid );
	virtual LNSTATUS Add( const LNNoteArray &notes );
	virtual LNSTATUS Add( const LNViewFolder &viewfolder );
	virtual LNSTATUS Add( const LNVFNavigator &nav );
	virtual LNSTATUS Add( HANDLE idtable );

	virtual LNSTATUS Copy( LNNoteArray *newarray ) const;

	virtual LNBOOL Contains( const LNNote &note ) const;
	virtual LNBOOL Contains( NOTEID noteid ) const;

	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNNOTEARRAY;}
	
	LNINT GetCount() const;

	LNDatabase GetDatabase() const {return Db;}

	NOTEID GetNoteID( LNINT n ) const;

	virtual LNNotesSession * GetSession() const
		{ return Db.GetSession(); }

	virtual LNSTATUS Remove( const LNNote &note );
	virtual LNSTATUS Remove( NOTEID noteid );
	virtual LNSTATUS Remove( const LNNoteArray &notes );
	virtual LNSTATUS Remove( const LNViewFolder &viewfolder );
	virtual LNSTATUS Remove( const LNVFNavigator &nav );
	virtual LNSTATUS Remove( HANDLE idtable );

	virtual LNSTATUS RemoveAll();

protected:
	void CreateLNIDTable( HANDLE idtable );

	LNDatabaseBody * GetDatabaseBody() const {return Db.GetDatabaseBody();}

	HANDLE GetIDTable() const;

	void GetNote( LNINT n, LNNote *note ) const;

private:
	void Assign( LNDatabaseBody *db, LNIDTable *ids, LNNOTETYPE type );

	LNDatabase Db;
	LNNOTETYPE NoteType;
};

//
//	Class definition for LNAgentArray.
//
class LNIMPEXPCL LNAgentArray : public LNNoteArray
{

public:
	LNAgentArray() : LNNoteArray() {}
	LNAgentArray( const LNAgentArray &other ) : LNNoteArray(other) {}

	virtual ~LNAgentArray() {}

	LNAgentArray & operator=( const LNAgentArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNAgent operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNAGENTARRAY;}

private:
};

//
//	Class definition for LNAppletResourceArray.
//
class LNIMPEXPCL LNAppletResourceArray : public LNNoteArray
{

public:
	LNAppletResourceArray() : LNNoteArray() {}
	LNAppletResourceArray( const LNAppletResourceArray &other ) : LNNoteArray(other) {}

	virtual ~LNAppletResourceArray() {}

	LNAppletResourceArray & operator=( const LNAppletResourceArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNAppletResource operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNAPPLETRESOURCEARRAY;}

private:
};

//
//	Class definition for LNCalendarEntryArray.
//
class LNIMPEXPCL LNCalendarEntryArray : public LNNoteArray
{

public:
	LNCalendarEntryArray() : LNNoteArray() {}
	LNCalendarEntryArray( const LNCalendarEntryArray &other ) : LNNoteArray(other) {}
	
	virtual ~LNCalendarEntryArray() {}
	
	LNCalendarEntryArray & operator=( const LNCalendarEntryArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNCalendarEntry operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNCALENDARENTRYARRAY;}
private:
	LNCalendarEntryArray( const LNDatabase &db ) : LNNoteArray( db ) {}
};

//
//	Class definition for LNDocumentArray.
//
class LNIMPEXPCL LNDocumentArray : public LNNoteArray
{

public:
	LNDocumentArray() : LNNoteArray() {}
	LNDocumentArray( const LNDocumentArray &other ) : LNNoteArray(other) {}


	virtual ~LNDocumentArray() {}

	LNDocumentArray & operator=( const LNDocumentArray &other )
		{LNNoteArray::operator=(other); return *this;}
	
	LNDocument operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNDOCUMENTARRAY;}

	LNBOOL IsFTSearch() const;

private:
	LNINT GetFTSearchScore( LNINT n ) const;
};

//
//	Class definition for LNFormArray.
//
class LNIMPEXPCL LNFormArray : public LNNoteArray
{

public:
	LNFormArray() : LNNoteArray() {}
	LNFormArray( const LNFormArray &other ) : LNNoteArray(other) {}

	virtual ~LNFormArray() {}
	
	LNFormArray & operator=( const LNFormArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNForm operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNFORMARRAY;}

private:
};
//
//	Class definition for LNFramesetArray.
//
class LNIMPEXPCL LNFramesetArray : public LNNoteArray
{

public:
	LNFramesetArray() : LNNoteArray() {}
	LNFramesetArray( const LNFramesetArray &other ) : LNNoteArray(other) {}

	virtual ~LNFramesetArray() {}
	
	LNFramesetArray & operator=( const LNFramesetArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNFrameset operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return (LNCLASSID)LNCLASSID_LNFRAMESETARRAY;}

private:
};

//
//	Class definition for LNImageResourceArray.
//
class LNIMPEXPCL LNImageResourceArray : public LNNoteArray
{

public:
	LNImageResourceArray() : LNNoteArray() {}
	LNImageResourceArray( const LNImageResourceArray &other ) : LNNoteArray(other) {}

	virtual ~LNImageResourceArray() {}
	
	LNImageResourceArray & operator=( const LNImageResourceArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNImageResource operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return (LNCLASSID)LNCLASSID_LNIMAGERESOURCEARRAY;}

private:
};
//
//	Class definition for LNNavigatorArray.
//
class LNIMPEXPCL LNNavigatorArray : public LNNoteArray
{

public:
	LNNavigatorArray() : LNNoteArray() {}
	LNNavigatorArray( const LNNavigatorArray &other ) : LNNoteArray(other) {}

	virtual ~LNNavigatorArray() {}
	
	LNNavigatorArray & operator=( const LNNavigatorArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNNavigator operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return (LNCLASSID)LNCLASSID_LNNAVIGATORARRAY;}

private:
};
//
//	Class definition for LNOutlineArray.
//
class LNIMPEXPCL LNOutlineArray : public LNNoteArray
{

public:
	LNOutlineArray() : LNNoteArray() {}
	LNOutlineArray( const LNOutlineArray &other ) : LNNoteArray(other) {}

	virtual ~LNOutlineArray() {}

	LNOutlineArray & operator=( const LNOutlineArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNOutline operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNOUTLINEARRAY;}

private:
};
//
//	Class definition for LNPageArray.
//
class LNIMPEXPCL LNPageArray : public LNNoteArray
{

public:
	LNPageArray() : LNNoteArray() {}
	LNPageArray( const LNPageArray &other ) : LNNoteArray(other) {}

	virtual ~LNPageArray() {}
	
	LNPageArray & operator=( const LNPageArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNPage operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return (LNCLASSID)LNCLASSID_LNPAGEARRAY;}

private:
};

//
//	Class definition for LNScriptLibraryArray.
//
class LNIMPEXPCL LNScriptLibraryArray : public LNNoteArray
{

public:
	LNScriptLibraryArray() : LNNoteArray() {}
	LNScriptLibraryArray( const LNScriptLibraryArray &other ) : LNNoteArray(other) {}

	virtual ~LNScriptLibraryArray() {}
	
	LNScriptLibraryArray & operator=( const LNScriptLibraryArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNScriptLibrary operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return (LNCLASSID)LNCLASSID_LNSCRIPTLIBRARYARRAY;}

private:
};


//
//	Class definition for LNViewFolderArray.
//
class LNIMPEXPCL LNViewFolderArray : public LNNoteArray
{

public:
	LNViewFolderArray() : LNNoteArray() {}
	LNViewFolderArray( const LNViewFolderArray &other ) : LNNoteArray(other) {}

	virtual ~LNViewFolderArray() {}

	LNViewFolderArray & operator=( const LNViewFolderArray &other )
		{LNNoteArray::operator=(other); return *this;}
	
	LNViewFolder operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNVIEWFOLDERARRAY;}

private:
};

//
//	Class definition for LNSharedFieldArray.
//
class LNIMPEXPCL LNSharedFieldArray : public LNNoteArray
{

public:
	LNSharedFieldArray() : LNNoteArray() {}
	LNSharedFieldArray( const LNSharedFieldArray &other ) : LNNoteArray(other) {}

	virtual ~LNSharedFieldArray() {}
	
	LNSharedFieldArray & operator=( const LNSharedFieldArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNSharedField operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNSHAREDFIELDARRAY;}

private:
};

//
//	Class definition for LNSubformArray.
//
class LNIMPEXPCL LNSubformArray : public LNNoteArray
{

public:
	LNSubformArray() : LNNoteArray() {}
	LNSubformArray( const LNSubformArray &other ) : LNNoteArray(other) {}

	virtual ~LNSubformArray() {}
	
	LNSubformArray & operator=( const LNSubformArray &other )
		{LNNoteArray::operator=(other); return *this;}

	LNSubform operator[]( LNINT n ) const;
	
	virtual LNCLASSID GetClassID() const {return LNCLASSID_LNSUBFORMARRAY;}

private:
};




#endif	//LNNOTEA_HPP

