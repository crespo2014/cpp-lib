//===========================================================================
//
// Module:		LNPAGE.HPP
//
// Description:
//
//		Class library definition for the LNPage and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNPAGE_HPP
#define LNPAGE_HPP

//
//	Class definition for LNPage.
//
class LNIMPEXPCL LNPage : public LNNote
{
public:

    LNSTATUS GetActions( LNActions *actions ) const;
    LNSTATUS SetActions( const LNActions &newList );

	LNColor GetActiveLinkColor() const;
	LNSTATUS SetActiveLinkColor(const LNColor &color);

	LNSTATUS SetAlias(const LNString &alias);

	LNBOOL GetAllowDesignRefreshToModify () const;
	void SetAllowDesignRefreshToModify (LNBOOL allow) ;

	LNBOOL GetAllowPublicAccessUsers () const;
	void SetAllowPublicAccessUsers (LNBOOL allow) ;

	LNAUTOLAUNCHOBJECTTYPE GetAutoLaunchObjectType() const;
	LNSTATUS SetAutoLaunchObjectType( LNAUTOLAUNCHOBJECTTYPE option );

	LNColor GetBackgroundColor() const;
	LNSTATUS SetBackgroundColor(const LNColor &color);

	LNSTATUS GetBackgroundGraphic(LNGraphic *graphic) const;
	LNSTATUS SetBackgroundGraphic(const LNGraphic &graphic);

    virtual LNCLASSID GetClassID() const 
	  {return LNCLASSID_LNPAGE;}

	LNString GetComment() const;
	LNSTATUS SetComment(const LNString &comment);

	LNBOOL GetDoNotTileBackgroundGraphic() const;
	void SetDoNotTileBackgroundGraphic(LNBOOL doNotTile);

	LNSTATUS GetEventFormula(LNFORMULAEVENT event, LNFormula *formula) const;
	LNSTATUS SetEventFormula( const LNFormula &formula, LNFORMULAEVENT event);

	LNString GetFrame( ) const;
	LNSTATUS SetFrame( const LNString &framename);

	LNString GetFrameset( ) const;
	LNSTATUS SetFrameset( const LNString &framesetname);

	LNBOOL GetHideBackgroundGraphicInDesignMode() const;
	void SetHideBackgroundGraphicInDesignMode(LNBOOL hide);

	LNBOOL GetHideBackgroundGraphicIn16ColorMode() const;
	void SetHideBackgroundGraphicIn16ColorMode(LNBOOL hide);

	LNBOOL GetHideFromBrowsers() const;
	void SetHideFromBrowsers(LNBOOL hide);

	LNBOOL GetHideFromClients() const;
	void SetHideFromClients(LNBOOL hide);

	LNString GetInheritsFromTemplateName () const;
	LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;

	LNSTATUS GetJavaScript (LNJavaScript *jscript) const;
	LNSTATUS SetJavaScript(const LNJavaScript &jscript);

	LNSTATUS GetLotusScript(LNLotusScript *script) const;
	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNSTATUS GetGlobalLotusScript(LNLotusScript *script) const;
	LNSTATUS SetGlobalLotusScript(const LNLotusScript &script);

	LNSTATUS SetName (const LNString& name) ;

	LNPage();
	LNPage( const LNPage &other );
	LNPage( const LNNote &other );
	LNPage& operator=( const LNPage &other );
	LNPage& operator=( const LNNote &other );
	~LNPage();
	LNSTATUS GetPageBody(LNRichText *richtext) const;
	LNBOOL GetPropagateAllowDesignChange () const;
	void SetPropagateAllowDesignChange (LNBOOL propagate) ;

	LNBOOL GetTreatContentsAsHTML() const;
	void SetTreatContentsAsHTML(LNBOOL set);  

	LNColor GetUnvisitedLinkColor() const;
	LNSTATUS SetUnvisitedLinkColor(const LNColor &color);

	LNColor GetVisitedLinkColor() const;
	LNSTATUS SetVisitedLinkColor(const LNColor &color);

protected:

private:
	LNPage & operator=( LNPageBody *note );
	LNPage( LNPageBody *note );
	LNPageBody * GetPageBody()
	{ return (LNPageBody *)Body;}

	LNPage( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const; 
	void ValidateNoteType( const LNNote &note ) const; 
	void ValidateNoteType( const LNNoteBody *note ) const; 
};
#endif // LNPAGE_HPP
