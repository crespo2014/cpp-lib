//===========================================================================
//
// Module:      LNFORM.HPP
//
// Description:
//
//      Class library definition for the LNForm class.
//
//===========================================================================
//
// Copyright (c) 1996-2003 Lotus Development Corporation. 
// All rights reserved.  This software is subject to the Lotus 
// Software Agreement, Restricted Rights for U.S. government users,
// and applicable export regulations.
//
//===========================================================================

#ifndef LNFORM_HPP
#define LNFORM_HPP

//
//  Class definition for LNForm:
//

class LNIMPEXPCL LNForm : public LNNote
{
friend class LNFormArray;
friend class LNFormFieldArray;

public:
    LNForm();
    LNForm( const LNForm &other );
    LNForm( const LNNote &other );

    ~LNForm();

    LNForm & operator=( const LNForm &other );
    LNForm & operator=( const LNNote &other );

    LNCLASSID GetClassID() const {return LNCLASSID_LNFORM;}

    //
    // General Form methods:
    //

    LNString GetAlias() const;
    LNSTATUS SetAlias( const LNString &alias );

    LNString GetName() const;
    LNSTATUS SetName( const LNString &name );

    LNString GetComment() const;
    LNSTATUS SetComment( const LNString &comment );

    //
    // Formula methods:
    //

    LNSTATUS GetHelpRequestFormula( LNFormula *formula ) const;
    LNSTATUS SetHelpRequestFormula( const LNFormula &formula );

    LNSTATUS GetHTMLAttributesFormula( LNFormula *formula ) const;
    LNSTATUS SetHTMLAttributesFormula( const LNFormula &formula );

    LNSTATUS GetHTMLHeadContentFormula( LNFormula *formula ) const;
    LNSTATUS SetHTMLHeadContentFormula( const LNFormula &formula );

    LNSTATUS GetTargetFrameFormula( LNFormula *formula ) const;
    LNSTATUS SetTargetFrameFormula( const LNFormula &formula );

    LNSTATUS GetWebQueryOpenFormula( LNFormula *formula ) const;
    LNSTATUS SetWebQueryOpenFormula( const LNFormula &formula );

    LNSTATUS GetWebQuerySaveFormula( LNFormula *formula ) const;
    LNSTATUS SetWebQuerySaveFormula( const LNFormula &formula );
        
    LNSTATUS GetWindowTitleFormula( LNFormula *formula ) const;
    LNSTATUS SetWindowTitleFormula( const LNFormula &formula );

    //
    // Event methods:
    //

    LNSTATUS GetJavaScript(LNJavaScript *script) const;
    LNSTATUS SetJavaScript(const LNJavaScript &script);

    LNSTATUS GetGlobalLotusScript (LNLotusScript * pScript) const;
    LNSTATUS SetGlobalLotusScript (const LNLotusScript & newScript);

    LNSTATUS GetLotusScript (LNLotusScript * pScript) const;
    LNSTATUS SetLotusScript (const LNLotusScript & newScript);

    LNSTATUS GetEventFormula(LNFORMULAEVENT event, LNFormula *formula ) const;
    LNSTATUS SetEventFormula( const LNFormula &formula, LNFORMULAEVENT event );

    //
    // Form Attributes:
    //

    LNINCLUDEINMENUOPTION GetIncludeInMenuOption() const;
    LNSTATUS SetIncludeInMenuOption( LNINCLUDEINMENUOPTION option );

    LNFORMTYPE GetFormType() const;
    LNSTATUS SetFormType( const LNFORMTYPE type );

    LNBOOL GetIncludeInSearchBuilder() const;
    void SetIncludeInSearchBuilder( LNBOOL flag );

    LNBOOL GetIsAnonymousForm() const;
    void SetIsAnonymousForm( LNBOOL flag );

    LNBOOL GetMergeReplicationConflicts() const;
    void SetMergeReplicationConflicts( LNBOOL flag );

    LNBOOL GetCreateVersionsAutomatically() const;
    void SetCreateVersionsAutomatically( LNBOOL flag );
    
    LNVERSIONINGOPTION GetVersioningOption() const;
    LNSTATUS SetVersioningOption( LNVERSIONINGOPTION voption );

    //
    // Defaults:
    //

    LNColor GetActiveLinkColor() const;
    LNSTATUS SetActiveLinkColor( const LNColor &color );

    LNCONTEXTPANEOPTION GetContextPaneOption() const;
    LNSTATUS SetContextPaneOption( LNCONTEXTPANEOPTION option );

    LNBOOL GetDisableFieldExchange() const;
    void SetDisableFieldExchange( LNBOOL flag );

    LNBOOL GetEditOnOpen() const;
    void SetEditOnOpen( LNBOOL flag );

    LNString GetFrame() const;
    LNSTATUS SetFrame( const LNString &frame );

    LNString GetFrameset() const;
    LNSTATUS SetFrameset( const LNString &frameset );

    LNBOOL GetGenerateHTMLForAllFields() const;
    void SetGenerateHTMLForAllFields( LNBOOL flag );

    LNINHERITDOCOPTION GetInheritDocumentOption() const;
    LNSTATUS SetInheritDocumentOption( LNINHERITDOCOPTION option = LNINHERITDOCOPTION_NONE );

    LNString GetInheritDocumentFieldName() const;
    LNSTATUS SetInheritDocumentFieldName( const LNString &name );

    LNBOOL GetInheritFormulaValues() const;
    void SetInheritFormulaValues( LNBOOL flag );

    LNBOOL GetIsDefaultForm() const;
    void SetIsDefaultForm( LNBOOL flag );

    LNBOOL GetRefreshFieldsAutomatically() const;
    void SetRefreshFieldsAutomatically( LNBOOL flag );

    LNBOOL GetShowMailSendOnClose() const;
    void SetShowMailSendOnClose( LNBOOL flag );

    LNBOOL GetStoreFormInDocument() const;
    void SetStoreFormInDocument( LNBOOL flag );

    LNBOOL GetTreatContentsAsHTML( ) const;
    void SetTreatContentsAsHTML( LNBOOL flag );

    LNColor GetUnvisitedLinkColor( ) const;
    LNSTATUS SetUnvisitedLinkColor( const LNColor &color );

    LNColor GetVisitedLinkColor( ) const;
    LNSTATUS SetVisitedLinkColor( const LNColor &color );

    //
    // Design Properties:
    //

    LNBOOL GetAllowDesignRefreshToModify() const;
    void SetAllowDesignRefreshToModify( LNBOOL flag );

    LNBOOL GetHideFromBrowsers() const;
    void SetHideFromBrowsers( LNBOOL flag );

    LNBOOL GetHideFromClients() const;
    void SetHideFromClients( LNBOOL flag );

    LNBOOL GetHideFromR4Clients() const;
    void SetHideFromR4Clients( LNBOOL flag );

    LNString GetInheritsFromTemplateName() const;
    LNSTATUS SetInheritsFromTemplateName( const LNString &name );

    LNBOOL GetPropagateAllowDesignChange() const;
    void SetPropagateAllowDesignChange(LNBOOL propagate);

    //
    // Launch:
    //

    LNAUTOLAUNCHOBJECTTYPE GetAutoLaunchObjectType() const;
    LNSTATUS SetAutoLaunchObjectType( LNAUTOLAUNCHOBJECTTYPE option );

    LNBOOL GetLaunchOLEObjectInPlace( ) const;
    void SetLaunchOLEObjectInPlace( LNBOOL flag );

    LNCREATEOBJECTINFIELDOPTION GetCreateObjectInFieldOption( ) const;
    LNSTATUS SetCreateObjectInFieldOption( LNCREATEOBJECTINFIELDOPTION option );

    LNString GetCreateObjectInFieldName( ) const;
    LNSTATUS SetCreateObjectInFieldName( const LNString  &fieldname );

    LNLAUNCHOBJECTWHENFLAGS GetLaunchObjectWhenFlags( ) const;
    LNSTATUS SetLaunchObjectWhenFlags( LNLAUNCHOBJECTWHENFLAGS Flags);

    LNHIDEDOCUMENTWHENFLAGS GetHideDocumentWhenFlags( ) const;
    LNSTATUS SetHideDocumentWhenFlags( LNHIDEDOCUMENTWHENFLAGS Flags );

    LNBOOL GetPresentDocumentAsDialog( ) const;
    void SetPresentDocumentAsDialog( LNBOOL flag );

    //
    // Background:
    //

    LNColor GetBackgroundColor() const;
    LNSTATUS SetBackgroundColor( LNColor color );

    LNSTATUS GetBackgroundGraphic( LNGraphic *graphic ) const;
    LNSTATUS SetBackgroundGraphic( const LNGraphic &graphic );


    LNBOOL GetDoNotTileBackgroundGraphic() const;
    void SetDoNotTileBackgroundGraphic( LNBOOL flag );

	LNBOOL GetHideBackgroundGraphicInDesignMode() const;
	void SetHideBackgroundGraphicInDesignMode( LNBOOL flag );

    LNBOOL GetHideBackgroundGraphicIn16ColorMode() const;
    void SetHideBackgroundGraphicIn16ColorMode( LNBOOL flag );

    LNSTATUS RemoveBackgroundGraphic();

    LNBOOL GetUserCanOverrideBackground() const;
    void SetUserCanOverrideBackground( LNBOOL flag );

    //
    // Action and Action Bar Methods:
    //

    LNSTATUS GetActions( LNActions *actions ) const;
    LNSTATUS SetActions( const LNActions &newList );

    //
    // Security:
    //

    LNBOOL GetAllowAllAuthors() const;
    void SetAllowAllAuthors( LNBOOL flag );

    LNBOOL GetAllowAllReaders() const;
    void SetAllowAllReaders( LNBOOL flag );

    LNBOOL GetAllowPublicAccessUsers () const;
    void SetAllowPublicAccessUsers ( LNBOOL flag );

    LNText GetAuthors() const;
    LNSTATUS SetAuthors( const LNText &authorslist );

    LNText GetDefaultEncryptionKeys( ) const;
    void SetDefaultEncryptionKeys( const LNText &keys );

    LNBOOL GetDisablePrintingAndCopying  () const;
    void SetDisablePrintingAndCopying  ( LNBOOL flag );

    LNText GetReaders() const;
    LNSTATUS SetReaders( const LNText &readerslist );

    //
    // Form Field methods:
    //

    LNSTATUS GetFormBody( LNRichText *richtext ) const;
    LNSTATUS GetFormField( const LNString &fieldname, LNFormField *field ) const;
    LNSTATUS GetFormFields( LNFormFieldArray *array, LNRTTYPE type = LNRTTYPE_FORM_FIELD ) const;
    LNBOOL HasFormField( const LNString &fieldname ) const;

private:
    LNForm( LNDatabaseBody *db, NOTEID idnote );

    LNForm & operator=( LNFormBody *formb );

    virtual void ValidateNoteType( const LNNote &note ) const;
    virtual void ValidateNoteType( const LNNoteBody *note ) const;
    virtual void ValidateNoteType( LNNOTETYPE type ) const;
};


#endif  //LNFORM_HPP

