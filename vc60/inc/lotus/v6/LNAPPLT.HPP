//===========================================================================
//
// Module:		LNAPPLT.HPP
//
// Description:
//
//		Class library definition for the LNAppletResource and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNAPPLT_HPP
#define LNAPPLT_HPP

//
//	Class definition for LNAppletResource.
//
class LNIMPEXPCL LNAppletResource : public LNNote
{
public:
	LNSTATUS ExportFiles( const LNString &path, const LNText *files = 0 ) const;
    LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const 
      {return LNCLASSID_LNAPPLETRESOURCE;}
	LNString GetComment() const;
	LNText GetFilenames() const ;
	LNBOOL GetHideFromBrowsers() const;
	LNBOOL GetHideFromClients() const;
    LNString GetInheritsFromTemplateName () const;
    LNBOOL GetPropagateAllowDesignChange () const;
	LNSTATUS ImportFiles(const LNString &path, const LNText *files = 0 );
	LNAppletResource( const LNAppletResource &other );
	LNAppletResource();
	LNAppletResource( const LNNote &other );
	LNSTATUS RemoveFiles(const LNText *files = 0);
	LNSTATUS ReorderFilename( const LNString &filename, LNINT newPosition );
	LNSTATUS SetAlias(const LNString &alias);
    void SetAllowDesignRefreshToModify (LNBOOL allow) ;
	LNSTATUS SetComment(const LNString &comment);
    LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;
	void SetHideFromBrowsers(LNBOOL hide);
	void SetHideFromClients(LNBOOL hide);
    LNSTATUS SetName (const LNString& name) ;
    void SetPropagateAllowDesignChange (LNBOOL propagate) ;
	LNAppletResource & operator=( LNAppletResourceBody *note );
	LNAppletResource& operator=( const LNAppletResource &other );
	LNAppletResource& operator=( const LNNote &other );
	~LNAppletResource();
protected:

	LNAppletResource( LNAppletResourceBody *note );

private:

	LNAppletResource( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const; 
	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 

};
#endif	// LNSCRLB_HPP
