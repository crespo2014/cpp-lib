//==========================================================================
//
// Module:		LNSCRLB.HPP
//
// Description:
//
//		Class library definition for the LNScriptLibrary and related classes.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNSCRLB_HPP
#define LNSCRLB_HPP

//
//	Class definition for LNScriptLibrary.
//
class LNIMPEXPCL LNScriptLibrary : public LNNote
{
public:
	LNSTATUS CreateJavaCode( const LNAgentJava &java, LNAgentJava *retJava);
    LNBOOL GetAllowDesignRefreshToModify () const;
	virtual LNCLASSID GetClassID() const
      {return (LNCLASSID)LNCLASSID_LNSCRIPTLIBRARY;}
    LNString GetInheritsFromTemplateName () const;
    LNSTATUS GetJavaCode (LNAgentJava *java) const;
    LNSTATUS GetLotusScript (LNLotusScript *script) ;
    LNBOOL GetPropagateAllowDesignChange () const;
    LNSCRIPTLIBRARYTYPE GetType () const;
	LNScriptLibrary( const LNScriptLibrary &other );
	LNScriptLibrary();
	LNScriptLibrary( const LNNote &other );
    void SetAllowDesignRefreshToModify (LNBOOL allow) ;
    LNSTATUS SetInheritsFromTemplateName (const LNString &name) ;
    LNSTATUS SetLotusScript (const LNLotusScript& script) ;
    LNSTATUS SetName (const LNString& name) ;
    void SetPropagateAllowDesignChange (LNBOOL propagate) ;
	LNScriptLibrary& operator=( const LNScriptLibrary &other );
	LNScriptLibrary& operator=( const LNNote &other );
	~LNScriptLibrary();
protected:
private:
	LNScriptLibrary & operator=( LNScriptLibraryBody *note );
	LNScriptLibrary( LNScriptLibraryBody *note );
	LNScriptLibrary( LNDatabaseBody *db, NOTEID idnote );
	void ValidateNoteType( LNNOTETYPE notetype ) const;
	void ValidateNoteType( const LNNote &note ) const;
	void ValidateNoteType( const LNNoteBody *note ) const;
};
#endif	//LNSCRLB_HPP
