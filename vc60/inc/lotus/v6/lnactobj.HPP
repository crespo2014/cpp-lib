//=====================================================================
//
// Module:	LNACTOBJ.HPP
//
// Description
//
//  Class Library declarations for:
//		LNActiveObject				LNActiveObjectBody
//		LNActiveObjectParameter		LNActiveObjectParameterBody
//		LNActiveObjectParameters	LNActiveObjectParametersBody
//		LNActiveObjectInternalLink
//		LNActiveObjectInternalLinks
//
//=====================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//=====================================================================

#ifndef LNACTOBJ_HPP
#define LNACTOBJ_HPP

#ifndef EDIT_ODS_DEFS
#include "editods.h"
#endif

//=====================================================================
//
//		Enumerations
//
//=====================================================================

enum LNACTIVEOBJECTTYPE
{
	LNACTIVEOBJECTTYPE_UNKNOWN = 0,
	LNACTIVEOBJECTTYPE_JAVA_APPLET,
	LNACTIVEOBJECTTYPE_PLUGIN,
	LNACTIVEOBJECTTYPE_OBJECT
};

enum LNACTIVEOBJECTUNITTYPE
{
	LNACTIVEOBJECTUNITTYPE_PIXELS,
	LNACTIVEOBJECTUNITTYPE_PERCENT
};

//=====================================================================
//
//		Class LNActiveObjectParameter
//
//=====================================================================

class LNIMPEXPCL LNActiveObjectParameter : public LNSmartPtr
{

public:
	LNActiveObjectParameter (void);
	LNActiveObjectParameter (const LNActiveObjectParameter & other);
	LNActiveObjectParameter (const LNString &name);

	~LNActiveObjectParameter (void);

	LNActiveObjectParameter & operator= (const LNActiveObjectParameter & other);

	virtual LNCLASSID GetClassID (void) const
						{ return (LNCLASSID_LNACTIVEOBJECTPARAMETER); }

	LNString		GetParameterName (void) const;
	LNINT			GetSize (void) const;
	LNString		GetValueString (void) const;
	LNSTATUS		GetValueFormula (LNFormula * pFormula) const;

	LNBOOL			IsValueFormula (void) const;
	LNBOOL			IsValueString (void) const;

	LNSTATUS		SetParameterName (const LNString & newName);
	LNSTATUS		SetValueString (const LNString & stringValue);
	LNSTATUS		SetValueFormula (const LNFormula & valueFormula);

protected:
	LNActiveObjectParameter (LNActiveObjectParameterBody * body);

	LNActiveObjectParameter & operator= (LNActiveObjectParameterBody * body);

	LNActiveObjectParameterBody * GetActiveObjectParameterBody (void) const;

private:
	void			CreateBody (LNActiveObjectParameterBody * pBody);
};


//=====================================================================
//
//		Class LNActiveObjectParameters
//
//=====================================================================

class LNIMPEXPCL LNActiveObjectParameters : public LNSmartPtr
{

public:
	LNActiveObjectParameters (void);
	LNActiveObjectParameters (const LNActiveObjectParameters & applet);

	~LNActiveObjectParameters (void);

	LNActiveObjectParameters & operator= (const LNActiveObjectParameters & other);

	LNActiveObjectParameter & operator[] (LNINT n);

	LNSTATUS		Append (const LNActiveObjectParameter & newParameter);

	LNSTATUS		CreateFormulaParameter (const LNString & name, const LNFormula & value);
	LNSTATUS		CreateStringParameter (const LNString & name, const LNString & value);

	LNSTATUS		Delete (LNINT index, LNINT count = 1);

	LNCLASSID		GetClassID (void) const
						{ return (LNCLASSID_LNACTIVEOBJECTPARAMETERS); }

	LNINT			GetCount (void) const;

	LNINT			GetSize (void) const;

	LNSTATUS		Insert (LNINT position, const LNActiveObjectParameter & newParameter);

protected:
	LNActiveObjectParameters (LNActiveObjectParametersBody * body);

	LNActiveObjectParameters & operator= (LNActiveObjectParametersBody * body);

	LNActiveObjectParametersBody * GetActiveObjectParametersBody (void) const;

private:
	void			CreateBody (LNActiveObjectParametersBody * pBody);
};


//=====================================================================
//
//		Class LNActiveObject
//
//=====================================================================

class LNIMPEXPCL LNActiveObject : public LNRTElement
{

public:
	LNActiveObject (void);
	LNActiveObject (const LNRTObject & object);
	LNActiveObject (const LNActiveObject & applet);

	~LNActiveObject (void);

	LNActiveObject & operator= (const LNRTObject & other);
	LNActiveObject & operator= (const LNActiveObject & other);

	LNSTATUS				GetActiveObjectParameters (
								LNActiveObjectParameters * parameters) const;
	LNACTIVEOBJECTTYPE		GetActiveObjectType (void) const;
	LNString				GetAlternateText (void) const;
	LNCLASSID				GetClassID (void) const
								{ return (LNCLASSID_LNACTIVEOBJECT); }
	LNString				GetCodeBase (void) const;
	LNINT					GetHeight (void) const;
	LNACTIVEOBJECTUNITTYPE	GetHeightUnits (void) const;
	LNString				GetURL (void) const;
	LNINT					GetWidth (void) const;
	LNACTIVEOBJECTUNITTYPE	GetWidthUnits (void) const;

	LNSTATUS				SetActiveObjectParameters (
								const LNActiveObjectParameters & parameters);
	LNSTATUS				SetAlternateText (const LNString & newText);
	LNSTATUS				SetCodeBase (const LNString & newPath);
	LNSTATUS				SetHeight (LNINT newHeight);
	LNSTATUS				SetHeightUnits (LNACTIVEOBJECTUNITTYPE newUnits);
	LNSTATUS				SetURL (const LNString & newURL);
	LNSTATUS				SetWidth (LNINT newWidth);
	LNSTATUS				SetWidthUnits (LNACTIVEOBJECTUNITTYPE newUnits);

protected:
	LNActiveObject (LNActiveObjectBody * body);

	LNActiveObject & operator= (LNActiveObjectBody * body);

	LNActiveObjectBody *	GetActiveObjectBody (void) const;

	virtual void			ValidateRTType(const LNRTObject &other) const;
	virtual void			ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

