//===========================================================================
//
// Module:		LNNAVIG.HPP
//
// Description:
//
//		Class library definition for the LNNavigator and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNNAVIG_HPP
#define LNNAVIG_HPP

//
//	Class definition for LNNavigator.
//
class LNIMPEXPCL LNNavigator : public LNNote
{
public:
    LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNNAVIGATOR;}
	LNString GetComment() const;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
    LNString GetInheritsFromTemplateName () const;
    LNBOOL GetPropagateAllowDesignChange () const;
	LNNavigator();
	LNNavigator( const LNNavigator &other );
	LNNavigator( const LNNote &other );
	LNSTATUS SetAlias(const LNString &alias);
    void SetAllowDesignRefreshToModify (LNBOOL allow) ;
	LNSTATUS SetComment(const LNString &comment);
    LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;
	void SetHideFromBrowsers(LNBOOL hide);
	void SetHideFromClients(LNBOOL hide);
    LNSTATUS SetName (const LNString& name) ;
    void SetPropagateAllowDesignChange (LNBOOL propagate) ;
	LNNavigator& operator=( const LNNavigator &other );
	LNNavigator& operator=( const LNNote &other );
	~LNNavigator();
protected:

private:
	LNNavigator & operator=( LNNavigatorBody *note );
	LNNavigator( LNNavigatorBody *note );
	LNNavigatorBody * GetNavigatorBody()
	{ return (LNNavigatorBody *)Body;}

	LNNavigator( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const; 
	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 

};
#endif // LNNAVIG_HPP
