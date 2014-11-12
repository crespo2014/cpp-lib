//===========================================================================
//
// Module:  LNFORMF.HPP
//
// Description:
//
//  Class library definition for LNFormField and related classes.
//
//===========================================================================
//
// Copyright (c) 1998-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNFORMF_HPP
#define LNFORMF_HPP

#ifndef LNSCRIPT_HPP
#include "lnscript.hpp"
#define LNSCRIPT_HPP
#endif


typedef WORD LNSECURITYFLAGS ;

#define LNSECURITYFLAGS_NONE					0x0000
#define LNSECURITYFLAGS_SIGN					FSIGN
#define LNSECURITYFLAGS_ENCRYPT					FSEAL
#define LNSECURITYFLAGS_REQUIRE_EDITOR_ACCESS	FPROTECTED

typedef WORD LNVALUESEPARATOR ;

#define LNVALUESEPARATOR_NONE           0x00
#define LNVALUESEPARATOR_SPACE			0x01
#define LNVALUESEPARATOR_COMMA			0x02
#define LNVALUESEPARATOR_SEMICOLON		0x04
#define LNVALUESEPARATOR_NEW_LINE		0x08
#define LNVALUESEPARATOR_BLANK_LINE	    0x10
#define LNVALUESEPARATOR_DEFAULT		LNVALUESEPARATOR_SEMICOLON

enum LNCOMPUTEOPTION
{
	LNCOMPUTEOPTION_EDITABLE,
	LNCOMPUTEOPTION_COMPUTED,
	LNCOMPUTEOPTION_COMPUTED_FOR_DISPLAY,
	LNCOMPUTEOPTION_COMPUTED_WHEN_COMPOSED
};

enum LNWEBDISPLAYOPTION
{
	LNWEBDISPLAYOPTION_HTML,
	LNWEBDISPLAYOPTION_JAVA_APPLET
};

class LNIMPEXPCL LNFormField : public LNRTElement
{
	friend class LNRTInputParser;

public:
	LNSTATUS Unshare();
	
	LNFormField();

	LNFormField(const LNRTObject &other);
	LNFormField(const LNFormField &other);

	LNFormField(const LNString &name, LNRTTYPE type = LNRTTYPE_FORM_FIELD);
	
	~LNFormField();
	
	LNFormField& operator=(const LNRTObject &other);
	LNFormField& operator=(const LNFormField &other);

	LNBOOL GetAllowMultiValues() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNFORMFIELD; }

	LNBOOL GetComputeAfterValidation() const;

	LNCOMPUTEOPTION GetComputeOption() const;

	LNDatetimeFormat GetDatetimeFormat() const;

	LNVALUESEPARATOR GetDisplayValueSeparator() const;

	LNFontStyle GetFontStyle() const;

	LNBOOL GetGiveDefaultFocus() const;

	LNSTATUS GetFieldSize(LNINT *width, LNINT *height, LNBOOL *widthInTwips) const;

	LNBOOL	GetFormulaLiteralize() const;

	LNString GetHelpDescription() const;

	LNFormula GetHTMLAttributesFormula() const;

	LNHTMLTags GetHTMLTags() const;

	LNFormula GetInputTranslationFormula() const; 

	LNFormula GetInputValidationFormula() const;

	LNVALUESEPARATOR GetInputValueSeparators() const;

	LNBOOL GetIsDynamicHeight() const;

	LNBOOL GetIsFitToWindow() const;

	LNBOOL GetIsNotesStyle() const;

	LNSTATUS GetJavaScript(LNJavaScript *jscript) const;

	LNSTATUS GetLotusScript(LNLotusScript *script) const;

	LNString GetName() const;

	LNNumberFormat GetNumberFormat() const;

	LNINT GetPositionInTabOrder() const;

	LNBOOL GetRTLReadingOrder() const;

	LNSECURITYFLAGS GetSecurityFlags() const;

	LNBOOL GetShowDelimiters() const;

	LNBOOL GetStoreAsHTMLAndMIME() const;

	LNBOOL GetTabExitsField() const;

	virtual LNRTTYPE GetType() const;

	LNFormula GetValueFormula() const;

	LNWEBDISPLAYOPTION GetWebDisplayOption() const;

	LNBOOL IsControlledSectionField() const;

	LNBOOL IsShared() const;

	void SetAllowMultiValues(LNBOOL flag);

	void SetComputeAfterValidation(LNBOOL flag);

	LNSTATUS SetComputeOption(LNCOMPUTEOPTION computeoption);
	
	LNSTATUS SetDatetimeFormat(const LNDatetimeFormat &format);

	LNSTATUS SetDisplayValueSeparator(LNVALUESEPARATOR separator);

	LNSTATUS SetFontStyle(const LNFontStyle &fontstyle);

	void SetFormulaLiteralize(LNBOOL flag);

	void SetGiveDefaultFocus(LNBOOL flag);

	LNSTATUS SetFieldSize(LNINT width, LNINT height, LNBOOL widthInTwips);

	LNSTATUS SetHelpDescription(const LNString &desc);

	LNSTATUS SetHTMLAttributesFormula(const LNFormula &formula);

	LNSTATUS SetHTMLTags(const LNHTMLTags &tags);

	LNSTATUS SetInputTranslationFormula(const LNFormula &formula);

	LNSTATUS SetInputValidationFormula(const LNFormula &formula);

	LNSTATUS SetInputValueSeparators(LNVALUESEPARATOR separator);

	LNSTATUS SetIsDynamicHeight(LNBOOL dynamic);

	LNSTATUS SetJavaScript(const LNJavaScript &jsevents);

	LNSTATUS SetLotusScript(const LNLotusScript &script);

	LNSTATUS SetName(const LNString &fieldname);

	LNSTATUS SetIsNotesStyle(LNBOOL notesstyle);

	LNSTATUS SetNumberFormat(const LNNumberFormat &format);

	LNSTATUS SetPositionInTabOrder(LNINT pos);

	void SetRTLReadingOrder(LNBOOL flag);

	LNSTATUS SetSecurityFlags(LNSECURITYFLAGS flags);

	void SetShowDelimiters(LNBOOL flag);

	void SetStoreAsHTMLAndMIME(LNBOOL flag);

	void SetTabExitsField(LNBOOL flag);

    LNSTATUS SetValueFormula(const LNFormula &formula);

	LNSTATUS SetWebDisplayOption(LNWEBDISPLAYOPTION option );

	LNSTATUS Share();

	LNSTATUS Validate();

protected:
private:	
	LNFormField(LNFormFieldBody *body);

	LNFormField& operator=(LNFormFieldBody *body);

	LNFormFieldBody* GetFormFieldBody() const { return (LNFormFieldBody *) Body; }

	LNFormFieldBody* GetSharedFormFieldBody() const;

	LNSTATUS SetSharedField(const LNSharedField &sharedfield);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

};

// LNKeywordsField related enums

enum LNKWCHOICES
{
	LNKWCHOICES_LIST,
	LNKWCHOICES_FORMULA,
	LNKWCHOICES_ADDRESS_DIALOG,
	LNKWCHOICES_ACL_DIALOG,
	LNKWCHOICES_VIEW_DIALOG
};

enum LNKWINTERFACEOPTION
{
     LNKWINTERFACEOPTION_DIALOG_LIST,
	 LNKWINTERFACEOPTION_CHECKBOX,
     LNKWINTERFACEOPTION_RADIO_BUTTON,
	 LNKWINTERFACEOPTION_LISTBOX,
	 LNKWINTERFACEOPTION_COMBOBOX
};

enum LNKWFRAMEOPTION
{
     LNKWFRAMEOPTION_NONE,
	 LNKWFRAMEOPTION_3D,
	 LNKWFRAMEOPTION_STANDARD
};

class LNIMPEXPCL LNKeywordsField : public LNFormField
{
	friend class LNFormFieldBody;
	friend class LNRTContainerBody;
	friend class LNRTInputParser;

public:
	
	LNKeywordsField();


	LNKeywordsField(const LNRTObject &other);

	LNKeywordsField(const LNKeywordsField &other);

	LNKeywordsField(const LNString &name);
	
	~LNKeywordsField();

	
	LNKeywordsField& operator=(const LNRTObject &other);

	LNKeywordsField& operator=(const LNKeywordsField &other);


	LNBOOL GetAllowValuesNotInList() const;

	LNFormula GetChoicesFormula() const;

	LNText GetChoicesList() const;

	LNString GetChoicesView() const;

	LNINT GetChoicesViewColumnNumber() const;

	LNString GetChoicesViewDatabase() const;

	LNKWCHOICES GetChoicesOption() const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNKEYWORDSFIELD; }

	LNBOOL GetDontDisplayHelperButton( ) const;

	LNINT GetInterfaceColumnCount() const;

	LNKWFRAMEOPTION GetInterfaceFrameOption() const;

	LNKWINTERFACEOPTION GetInterfaceOption() const;

	LNBOOL GetLookUpNames() const;

	LNBOOL GetRefreshChoicesOnDocRefresh( ) const;

	LNBOOL GetRefreshFieldsOnChange( ) const;


	void SetAllowValuesNotInList(LNBOOL allow);

	LNSTATUS SetChoicesFormula(const LNFormula &formula);

	LNSTATUS SetChoicesList(const LNText &keywords);

	LNSTATUS SetChoicesView(const LNString &view);

	LNSTATUS SetChoicesViewColumnNumber(LNINT columnNumber);

	LNSTATUS SetChoicesViewDatabase(const LNString &database);

	LNSTATUS SetChoicesOption(LNKWCHOICES option);

	void SetDontDisplayHelperButton( LNBOOL flag);

	LNSTATUS SetInterfaceColumnCount(LNINT columnsNumber);

	LNSTATUS SetInterfaceFrameOption(LNKWFRAMEOPTION frame);

	LNSTATUS SetInterfaceOption(LNKWINTERFACEOPTION uioption);

	void SetLookUpNames(LNBOOL lookUpNames);

	void SetRefreshChoicesOnDocRefresh( LNBOOL flag);

	void SetRefreshFieldsOnChange( LNBOOL flag);

protected:

	LNKeywordsField(LNFormFieldBody *body);

	LNKeywordsField& operator=(LNFormFieldBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

};

// LNNamesField related enums

enum LNNAMESCHOICES
{
	LNNAMESCHOICES_NONE,
	LNNAMESCHOICES_ADDRESS_DIALOG,
	LNNAMESCHOICES_ACL_DIALOG,
	LNNAMESCHOICES_VIEW_DIALOG
};

class LNIMPEXPCL LNNamesField : public LNFormField
{
	friend class LNFormFieldBody;
	friend class LNRTContainerBody;
	friend class LNRTInputParser;

public:
	
	LNNamesField();


	LNNamesField(const LNRTObject &other);

	LNNamesField(const LNNamesField &other);

	LNNamesField(const LNString &name, LNRTTYPE type);
	
	~LNNamesField();

	
	LNNamesField& operator=(const LNRTObject &other);

	LNNamesField& operator=(const LNNamesField &other);


	LNBOOL GetAllowValuesNotInList() const;

	LNNAMESCHOICES GetChoicesOption() const;

	LNINT GetChoicesViewColumnNumber() const;

	LNString GetChoicesView() const;

	LNString GetChoicesViewDatabase() const;

	LNBOOL GetDontDisplayHelperButton( ) const;

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNNAMESFIELD; }

	LNBOOL GetLookUpNames() const;


	void SetAllowValuesNotInList(LNBOOL allow);

	LNSTATUS SetChoicesOption(LNNAMESCHOICES option);

	LNSTATUS SetChoicesViewDatabase(const LNString &database);

	LNSTATUS SetChoicesView(const LNString &view);

	LNSTATUS SetChoicesViewColumnNumber(LNINT columnNumber);

	void SetDontDisplayHelperButton( LNBOOL flag);

	void SetLookUpNames(LNBOOL lookUpNames);

protected:

	LNNamesField(LNFormFieldBody *body);

	LNNamesField& operator=(LNFormFieldBody *body);

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;

};

//
//	Class definition for LNSharedField.
//
class LNIMPEXPCL LNSharedField : public LNNote
{
friend class LNSharedFieldArray;
friend class LNDatabase;
friend class LNFormField;

public:
	LNSharedField();
	LNSharedField( const LNSharedField &other );
	LNSharedField( const LNNote &other );
	~LNSharedField();
	LNSharedField & operator=( const LNSharedField &other );
	LNCLASSID GetClassID() const {return LNCLASSID_LNSHAREDFIELD;}

	// Generic properties
    LNBOOL GetAllowDesignRefreshToModify () const;
    void SetAllowDesignRefreshToModify (LNBOOL allow);

	LNString GetInheritsFromTemplateName () const;
    LNSTATUS SetInheritsFromTemplateName (const LNString &name);

	LNBOOL GetPropagateAllowDesignChange () const;
    void SetPropagateAllowDesignChange (LNBOOL propagate);

	// Specific shared field methods
    LNSTATUS GetEventFormula(LNFORMULAEVENT event, LNFormula *formula ) const;
    LNSTATUS SetEventFormula( const LNFormula &formula, LNFORMULAEVENT event );

	LNSTATUS GetField( LNFormField *field ) const;
	virtual LNSTATUS SetName ( const LNString &name );

private:
	LNSharedField( LNDatabaseBody *db, NOTEID idnote );

	LNSharedField & operator=( LNSharedFieldBody *sharedfieldbody );
     
	virtual void ValidateNoteType( const LNNote &note ) const;
	virtual void ValidateNoteType( const LNNoteBody *note ) const;
	virtual void ValidateNoteType( LNNOTETYPE type ) const;
};

//-----------------------------------

#endif

