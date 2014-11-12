//===========================================================================
//
// Module:		LNOUTLN.HPP
//
// Description:
//
//		Class library definition for the LNOutline and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNOUTLN_HPP
#define LNOUTLN_HPP

//
//	Class definition for LNOutline.
//
class LNIMPEXPCL LNOutline : public LNNote
{
public:
    LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNOUTLINE;}
	LNString GetComment() const;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
    LNString GetInheritsFromTemplateName () const;
    LNBOOL GetPropagateAllowDesignChange () const;
	LNOutline();
	LNOutline( const LNOutline &other );
	LNOutline( const LNNote &other );
	LNSTATUS SetAlias(const LNString &alias);
    void SetAllowDesignRefreshToModify (LNBOOL allow) ;
	LNSTATUS SetComment(const LNString &comment);
    LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;
	void SetHideFromBrowsers(LNBOOL hide);
	void SetHideFromClients(LNBOOL hide);
    LNSTATUS SetName (const LNString& name) ;
    void SetPropagateAllowDesignChange (LNBOOL propagate) ;
	LNOutline& operator=( const LNOutline &other );
	LNOutline& operator=( const LNNote &other );
	~LNOutline();
protected:

private:
	LNOutline & operator=( LNOutlineBody *note );
	LNOutline( LNOutlineBody *note );
	LNOutlineBody * GetOutlineBody()
	{ return (LNOutlineBody *)Body;}

	LNOutline( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const; 
	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 

};
#endif // LNSCRLB_HPP
