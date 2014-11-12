//===========================================================================
//
// Module:	LNRTJAVA.HPP
//
// Description
//
//  Class Library description for LNRTJavaApplet, LNRTJavaAppletBody.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNRTJAVA_HPP
#define LNRTJAVA_HPP

#ifndef LNACTOBJ_HPP
#include "lnactobj.hpp"
#endif

//=====================================================================
//
//		Class:  LNRTJavaApplet
//
//=====================================================================

class LNIMPEXPCL LNRTJavaApplet : public LNActiveObject
{

public:

	LNRTJavaApplet (void);
	LNRTJavaApplet (const LNRTObject & object);
	LNRTJavaApplet (const LNRTJavaApplet & applet);

	~LNRTJavaApplet (void);

	LNRTJavaApplet & operator= (const LNRTObject & other);
	LNRTJavaApplet & operator= (const LNRTJavaApplet & other);

	LNSTATUS	ExportFile (const LNString &name, const LNString &path) const;

	LNSTATUS	ExportAllFiles (const LNString &path) const;

	LNString	GetBaseClassName (void) const;

	LNCLASSID	GetClassID (void) const { return (LNCLASSID_LNRTJAVAAPPLET); }

	LNText		GetFilenames (void) const;

	LNString	GetObjectName (void) const;

	virtual LNINT GetSize (void) const;

	LNSTATUS	ImportFile (const LNString &filename, const LNString &path);
	LNSTATUS	ImportFiles (const LNText & fileList, const LNString & path);

	LNSTATUS	ReimportAllFiles (const LNString & path);
	LNSTATUS	ReimportFile (const LNString &filename, const LNString & path);
	LNSTATUS	RemoveAllFiles (void);
	LNSTATUS	RemoveFile (const LNString &filename);
	LNSTATUS	ReorderFilename (const LNString & fileName, LNINT newPosition);

	LNSTATUS	SetBaseClassName (const LNString & newName);

	LNSTATUS	SetObjectName (const LNString & newName);

protected:

	LNRTJavaApplet (LNRTJavaAppletBody * body);

	LNRTJavaApplet & operator= (LNRTJavaAppletBody * body);

	LNRTJavaAppletBody * GetRTJavaAppletBody (void) const
			{ return ((LNRTJavaAppletBody *) Body); }

	virtual void ValidateRTType(const LNRTObject &other) const;
	virtual void ValidateRTType(const LNRTObjectBody *other) const;
};


#endif

