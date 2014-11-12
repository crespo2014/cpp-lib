//===========================================================================
//
// Module:		LNSBFORM.HPP
//
// Description:
//
//		Class library definition for the LNSubform class.
//
//===========================================================================
//
// Copyright (c) 1998-2003 Lotus Development Corporation. 
// All rights reserved.  This software is subject to the Lotus 
// Software Agreement, Restricted Rights for U.S. government users,
// and applicable export regulations.
//
//===========================================================================

#ifndef LNSBFORM_HPP
#define LNSBFORM_HPP

//
//	Class definition for LNSubform.
//
class LNIMPEXPCL LNSubform : public LNNote
{
friend class LNSubformArray;

public:
	LNSubform();
	LNSubform( const LNSubform &other );
	LNSubform( const LNNote &other );

	~LNSubform();

	LNSubform & operator=( const LNSubform &other );
	LNSubform & operator=( const LNNote &other );

	LNCLASSID GetClassID() const {return LNCLASSID_LNSUBFORM;}

	//
	// General Subform methods:
	//
	virtual LNString GetAlias() const;
	LNSTATUS SetAlias(const LNString &alias);

	virtual LNString GetName() const;
	LNSTATUS SetName(const LNString &name);
	//
	// Subform Attributes:
	//
	LNSTATUS GetActions(LNActions *actions) const;
	LNSTATUS SetActions(const LNActions &actions);

    LNBOOL GetAllowDesignRefreshToModify () const;
    void SetAllowDesignRefreshToModify (LNBOOL allow);

	LNString GetComment() const;
	LNSTATUS SetComment(const LNString &comment);

	LNSTATUS GetEventFormula(LNFORMULAEVENT event, LNFormula *formula) const;
	LNSTATUS SetEventFormula(const LNFormula &formula, LNFORMULAEVENT event);

	LNSTATUS GetGlobalLotusScript(LNLotusScript *script) const;
	LNSTATUS SetGlobalLotusScript(const LNLotusScript &script);

	LNBOOL GetHideFromBrowsers() const;
	void SetHideFromBrowsers( LNBOOL flag );

	LNBOOL GetHideFromClients() const;
	void SetHideFromClients( LNBOOL flag );

	LNBOOL GetIncludeInSubformDialog() const;
	void SetIncludeInSubformDialog( LNBOOL option );

	LNBOOL GetIncludeInNewFormDialog() const;
	void SetIncludeInNewFormDialog( LNBOOL flag );

	LNBOOL GetHideFromR3Users() const;
	void SetHideFromR3Users( LNBOOL flag);

	LNString GetInheritsFromTemplateName () const;
    LNSTATUS SetInheritsFromTemplateName (const LNString &name);

	LNSTATUS GetJavaScript (LNJavaScript *script) const;
    LNSTATUS SetJavaScript (const LNJavaScript &jscript);

	LNSTATUS GetLotusScript(LNLotusScript *script) const;
	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNBOOL GetPropagateAllowDesignChange () const;
    void SetPropagateAllowDesignChange (LNBOOL propagate);

	LNSTATUS GetSubformBody( LNRichText *richtext ) const;

	LNSTATUS GetSubformField( const LNString &fieldname, LNFormField *field) const; 

private:
	LNSubform( LNDatabaseBody *db, NOTEID idnote );

	LNSubform & operator=( LNSubformBody *formb );

	LNSubformBody * GetLNSubformBody() const {return (LNSubformBody *)Body;}

	virtual void ValidateNoteType( const LNNote &note ) const;
	virtual void ValidateNoteType( const LNNoteBody *note ) const;
	virtual void ValidateNoteType( LNNOTETYPE type ) const;
};


#endif	//LNFORM_HPP

