//===========================================================================
//
// Module:		LNSEARCH.HPP
//
// Description:
//
//		Class library definition for the LNSearch... classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSEARCH_HPP
#define LNSEARCH_HPP

//These type codes identify the type of simple search.
enum LNSEARCHTYPE
{
	LNSEARCHTYPE_BY_AUTHOR,
	LNSEARCHTYPE_BY_DATE,
	LNSEARCHTYPE_BY_TEXT_IN_FIELD,
	LNSEARCHTYPE_BY_NUMBER_IN_FIELD,
	LNSEARCHTYPE_BY_DATE_IN_FIELD,
	LNSEARCHTYPE_BY_FIELDS_IN_FORM,
	LNSEARCHTYPE_IN_FOLDER,
	LNSEARCHTYPE_BY_FORM_USED,
	LNSEARCHTYPE_TEXT_TERMS,
	LNSEARCHTYPE_PLAIN_TEXT
};

// Types of timedate search conditions used in specific LNSearch subclasses.
enum LNSEARCHDATECOND
{
	LNSEARCHDATECOND_ON,
	LNSEARCHDATECOND_AFTER,
	LNSEARCHDATECOND_BEFORE,
	LNSEARCHDATECOND_NOT_ON,
	LNSEARCHDATECOND_IN_THE_LAST,
	LNSEARCHDATECOND_IN_THE_NEXT,
	LNSEARCHDATECOND_OLDER_THAN,
	LNSEARCHDATECOND_AFTER_THE_NEXT,
	LNSEARCHDATECOND_BETWEEN,
	LNSEARCHDATECOND_NOT_BETWEEN
};

// Types of timedate search conditions used in specific LNSearch subclasses.
enum LNSEARCHNUMBERCOND
{
	LNSEARCHNUMBERCOND_EQUAL,
	LNSEARCHNUMBERCOND_NOT_EQUAL,
	LNSEARCHNUMBERCOND_GREATER,
	LNSEARCHNUMBERCOND_LESS,
	LNSEARCHNUMBERCOND_BETWEEN,
	LNSEARCHNUMBERCOND_NOT_BETWEEN
};

//==============================================================

class LNSearchByAuthorBody;
class LNSearchByDateBody;
class LNSearchByTextInFieldBody;
class LNSearchByFieldsInFormBody;
class LNSearchByFormUsedBody;
class LNSearchByNumberInFieldBody;
class LNSearchByTextTermsBody;
class LNSearchByDateInFieldBody;
class LNSearchInFolderBody;
class LNsearchBody;

class LNIMPEXPCL LNSearch : public LNSmartPtr 
{
	friend class LNSearchesBody;

public:
	
	LNSearch(){}

	LNSearch (const LNSearch &other) : SearchType(other.SearchType)
	{
		LNSmartPtr::operator=(other);
	}

	~LNSearch () {}

	LNSearch & operator= (const LNSearch & other) 
	{ 
		if (this != &other)
		{
			LNSmartPtr::operator=(other);
			SearchType = other.SearchType;
		}
		return (*this);
	}

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCH; }

	LNSEARCHTYPE GetSearchType() const {return SearchType;}

protected:

	LNSearch (LNSEARCHTYPE type) : SearchType(type) {};
	void SetSearchType(LNSEARCHTYPE type) { SearchType = type;}
	LNSearch(LNSearchBody *search);
	LNSearchBody *GetSearchBody() const;

private:

LNSEARCHTYPE SearchType;

};
 
//==================================================================
class LNIMPEXPCL LNSearchByAuthor : public  LNSearch
{
public:

	LNSearchByAuthor ();

	LNSearchByAuthor (const LNSearchByAuthor & other);

    LNSearchByAuthor ( const LNSearch &other );

	LNSearchByAuthor ( const LNText &authors, LNBOOL contains );

	~LNSearchByAuthor ();

	LNSearchByAuthor & operator= (const LNSearchByAuthor & other);

	LNSearchByAuthor & operator= (const LNSearch & other);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYAUTHOR;}

	LNText GetAuthorList () const;

	LNBOOL GetContains() const;

	LNSTATUS SetAuthorList (const LNText &authorList);

	void SetContains (LNBOOL flag );

protected:

//	LNSearchByAuthor (LNSearchByAuthorBody * pBody);

};

class LNIMPEXPCL LNSearchByDate : public LNSearch
{
public:

	LNSearchByDate ();

	LNSearchByDate (const LNSearchByDate & other);

    LNSearchByDate ( const LNSearch &other );

	LNSearchByDate ( LNBOOL dateCreated,
					 LNSEARCHDATECOND Condition,
				     const LNDatetime &Date1,
				     const LNDatetime &Date2,
				     LNINT NumDays );

	~LNSearchByDate ();

	LNSearchByDate & operator= (const LNSearchByDate & other);

	LNSearchByDate & operator= (const LNSearch & other);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYDATE;}

	LNBOOL GetIsDateCreated();

	LNSEARCHDATECOND GetDateCondition () const;

	LNDatetime GetDate1 () const;

	LNDatetime GetDate2 () const;

	LNINT GetNumberOfDays () const;

	void SetIsDateCreated(LNBOOL flag);

	LNSTATUS SetDateCondition (LNSEARCHDATECOND condition);

	LNSTATUS SetDate1 (const LNDatetime &date);

	LNSTATUS SetDate2 (const LNDatetime &date);

	LNSTATUS SetNumberOfDays (LNINT days);

protected:

//	LNSearchByDate (LNSearchByDateBody * pBody);

};

class LNIMPEXPCL LNSearchByTextInField : public LNSearch 
{
public:

	LNSearchByTextInField ();

	LNSearchByTextInField (const LNSearchByTextInField & other);

	LNSearchByTextInField (const LNSearch & other);

    LNSearchByTextInField(LNBOOL contains,
					const LNString &fieldName,
					const LNString &searchString);

	~LNSearchByTextInField ();

	LNSearchByTextInField & operator= (const LNSearchByTextInField & other);

	LNSearchByTextInField & operator= (const LNSearch & other);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYTEXTINFIELD;}

	LNBOOL GetContains() const;

	LNString GetFieldName () const;

	LNString GetSearchString() const;

	void SetContains(LNBOOL flag );

	LNSTATUS SetFieldName (const LNString &name);

	LNSTATUS SetSearchString( const LNString &searchString);

protected:

//	LNSearchByDate (LNSearchByTextInFieldBody * pBody);
};


class LNIMPEXPCL LNSearchByNumberInField : public LNSearch 
{
public:

	LNSearchByNumberInField ();

	LNSearchByNumberInField (const LNSearchByNumberInField & other);

	LNSearchByNumberInField (const LNSearch & other);

	LNSearchByNumberInField (	const LNString &fieldName,
							LNSEARCHNUMBERCOND numberCond,
							const LNNUMBER &number1,
							const LNNUMBER &number2);

	~LNSearchByNumberInField ();

	LNSearchByNumberInField & operator= (const LNSearchByNumberInField & other);

	LNSearchByNumberInField & operator= (const LNSearch & other);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYNUMBERINFIELD;}

	LNString GetFieldName () const;

	LNSEARCHNUMBERCOND GetNumberCondition() const;

	LNNUMBER GetNumber1 () const;

	LNNUMBER GetNumber2 () const;

	LNSTATUS SetFieldName (const LNString &name);

	LNSTATUS SetNumberCondition (LNSEARCHNUMBERCOND condition);

	LNSTATUS SetNumber1 (const LNNUMBER & newValue);

	LNSTATUS SetNumber2 (const LNNUMBER & newValue);

protected:

//	LNSearchByNumberInField (LNSearchByNumberInFieldBody * pBody);
};

class LNIMPEXPCL LNSearchByDateInField : public LNSearch 
{
public:

	LNSearchByDateInField ();

	LNSearchByDateInField (const LNSearchByDateInField & other);

	LNSearchByDateInField ( const LNSearch &other );

	LNSearchByDateInField	(	const LNString &fieldName,
							LNSEARCHDATECOND dateCond,
							const LNDatetime &date1,
							const LNDatetime &date2);

	~LNSearchByDateInField ();

	LNSearchByDateInField & operator= (const LNSearchByDateInField & other);

	LNSearchByDateInField & operator= (const LNSearch & other);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYDATEINFIELD;}

	LNString GetFieldName () const;

	LNSEARCHDATECOND GetDateCondition () const;

	LNDatetime GetDate1 () const;

	LNDatetime GetDate2 () const;

	LNINT GetNumberOfDays() const;

	LNSTATUS SetDate1 (const LNDatetime & newDate);

	LNSTATUS SetDate2 (const LNDatetime & newDate);

	LNSTATUS SetFieldName (const LNString &name);

	LNSTATUS SetNumberOfDays(LNINT days);

	LNSTATUS SetDateCondition (LNSEARCHDATECOND condition);

protected:

//	LNSearchByDateInField (LNSearchByDateInFieldBody * pBody);
};

class LNIMPEXPCL LNSearchByFieldsInForm : public LNSearch
{
public:
	
	LNSearchByFieldsInForm ();

	LNSearchByFieldsInForm (const LNSearchByFieldsInForm & other);

	LNSearchByFieldsInForm (const LNSearch & other);

	LNSearchByFieldsInForm ( const LNString &formName, 
							 const LNText &fieldNames, 
							 const LNText &fieldConditions);

	~LNSearchByFieldsInForm ();

	LNSearchByFieldsInForm & operator= (const LNSearchByFieldsInForm & other);

	LNSearchByFieldsInForm & operator= (const LNSearch & other);

//	LNSearchByFieldsInForm & operator[] (LNINT n);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYFIELDSINFORM; }

	LNSTATUS SetField( const LNString &fieldname, const LNString &searchText);

	LNSTATUS RemoveField( const LNString &fieldname );

	LNText GetFieldNames() const;

	LNString GetFormName () const;

	LNSTATUS GetFieldSearchString( const LNString &fieldName, LNString *condition);

	LNSTATUS SetFormName ( const LNString &formname );

protected:

//	LNSearchByFieldsInForm (LNSearchByFieldsInFormBody * pBody);
};

class LNIMPEXPCL LNSearchByFormUsed : public LNSearch
{
public:

	LNSearchByFormUsed ();

	LNSearchByFormUsed (const LNSearchByFormUsed & other);

	LNSearchByFormUsed (const LNSearch & other);

	LNSearchByFormUsed ( const LNText &formnames );

	~LNSearchByFormUsed ();

	LNSearchByFormUsed & operator= (const LNSearchByFormUsed & other);

	LNSearchByFormUsed & operator= (const LNSearch & other);

//	LNSearchByFormUsed & operator[] (LNINT n);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYFORMUSED; }

	LNText GetFormNames() const;

	LNSTATUS SetFormNames( const LNText &formnames );

protected:
	LNSearchByFormUsed (LNSearchByFormUsedBody * pBody);
};

class LNIMPEXPCL LNSearchInFolder : public LNSearch
{
public:

	LNSearchInFolder ();

	LNSearchInFolder (const LNSearchInFolder & other);

	LNSearchInFolder (const LNSearch & other);

	LNSearchInFolder (const LNString &folderName);

	~LNSearchInFolder ();

	LNSearchInFolder & operator= (const LNSearchInFolder & other);

	LNSearchInFolder & operator= (const LNSearch & other);

//	LNSearchInFolder & operator[] (LNINT n);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHINFOLDER; }

	LNString GetFolderName() const;

	LNSTATUS SetFolderName(const LNString &foldername);

protected:

//	LNSearchInFolder (LNSearchInFolderBody * pBody);
};

class LNIMPEXPCL LNSearchByTextTerms : public LNSearch
{
public:

	LNSearchByTextTerms ();

	LNSearchByTextTerms (const LNSearchByTextTerms & other);

	LNSearchByTextTerms (const LNSearch & other);

	LNSearchByTextTerms ( LNBOOL any, const LNText &words );

	~LNSearchByTextTerms ();

	LNSearchByTextTerms & operator= (const LNSearchByTextTerms & other);

	LNSearchByTextTerms & operator= (const LNSearch & other);

//	LNSearchByTextTerms & operator[] (LNINT n);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYTEXTTERMS; }

	LNBOOL GetIsAny() const;

	LNText GetSearchStrings() const;

	void SetIsAny(LNBOOL flag);

	LNSTATUS SetSearchStrings( const LNText &words);

protected:

//	LNSearchByTextTerms (LNSearchByTextTermsBody * pBody);
};

class LNIMPEXPCL LNSearchByPlainText : public LNSearch
{
public:

	LNSearchByPlainText ();

	LNSearchByPlainText (const LNSearchByPlainText & other);

	LNSearchByPlainText (const LNSearch & other);

	LNSearchByPlainText ( const LNString &text );

	~LNSearchByPlainText ();

	LNSearchByPlainText & operator= (const LNSearchByPlainText & other);

	LNSearchByPlainText & operator= (const LNSearch & other);

//	LNSearchByPlainText & operator[] (LNINT n);

	LNCLASSID GetClassID () const { return LNCLASSID_LNSEARCHBYPLAINTEXT; }

	LNString GetSearchString() const;

	LNSTATUS SetSearchString( const LNString &text);

protected:

//	LNSearchByPlainText (LNSearchByPlainTextBody * pBody);
};

class LNIMPEXPCL LNSearches : public LNSmartPtr
{

	public:
		LNSearches ();
		LNSearches (const LNSearches & other);

		~LNSearches ();

		LNSearches &	operator= (const LNSearches & other);

		LNSearch	operator[] (LNINT n) const;

		LNSTATUS	Append (const LNSearch & newSearch);
		LNSTATUS	Delete (LNINT index, LNINT count = 1);
		virtual LNCLASSID	GetClassID () const
								{ return (LNCLASSID_LNSEARCHES); }
		LNINT	GetCount () const;
		LNSTATUS	Insert (LNINT position, const LNSearch & newSearch);
protected:
		LNSearches (LNSearchesBody * pBody);
private:
		void	CreateBody (LNSearchesBody * pBody);
		LNSearchesBody *GetSearchesBody () const;
};


#endif

