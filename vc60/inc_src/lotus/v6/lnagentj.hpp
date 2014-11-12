//===========================================================================
//
// Module:		LNAGENTJ.HPP
//
// Description:
//
//		Class library definition for the LNAgentJava... classes.
//
//===========================================================================
//
// Copyright (c) 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNAGENTJ_HPP
#define LNAGENTJ_HPP

// These includes are used for Java services only
/* NOTES_JAVA
	#include "jni.h"
	#include "javadefs.h"
	#include "lnjm.hpp"
NOTES_JAVA */
// End of includes for Java services

//==============================================================
//
// LNAgentJava class declaration
//
class LNIMPEXPCL LNAgentJava
{
public:

	LNAgentJava ();
	LNAgentJava (const LNAgentJava & other);

	~LNAgentJava ();
	LNAgentJava & operator= (const LNAgentJava &other);
	LNSTATUS ExportFile( const LNString &name, const LNString &path = "" );
	LNSTATUS ExportAllFiles(const LNString &path = ""); 
	LNString GetBaseClassName () const;
	LNCLASSID GetClassID () const { return LNCLASSID_LNAGENTJAVA;}
	LNString GetCodePath() const ; 
	LNText GetFilenames() const ;
	LNText GetLibraryNames() const;
	LNBOOL GetIsImportedJava() const;
	LNSTATUS ImportFile( const LNString &filename, const LNString &path = "");
	LNSTATUS ImportFiles(const LNText &filenames, const LNString &path = "");
	LNSTATUS ReimportFile (const LNString &filename, const LNString &path = "" );
	LNSTATUS ReimportAllFiles( const LNString &path = "" );
	LNSTATUS RemoveAllFiles();
	LNSTATUS RemoveFile(const LNString &filename);
	LNSTATUS ReorderFilename( const LNString &filename, LNINT newPosition );
	LNSTATUS SetBaseClassName (const LNString &name);
	LNSTATUS SetCodePath ( const LNString &codepath );
	LNSTATUS SetLibraryNames( const LNText &librarynames);
protected:

private:

/* NOTES_JAVA
	LNString GetClassPath() const;
	LNSTATUS SetClassPath ( const LNString &classpath );
	// This constructor is used for Java services only
	LNAgentJava ( const LNString &classpath,
				  const LNString &classname, 
				  const LNString &path, 
				  const LNText &filenames,
				  LNNoteBody *notebody = 0,
				  const LNText *libraries = 0);
NOTES_JAVA */
	LNAgentJava ( const LNString &baseclass, 
				  const LNString &codepath, 
				  const LNText &filenames,
				  LNNoteBody *notebody = 0,
				  const LNText *libraries = 0);

	LNAgentJava (	const LNString &baseclass, 
					const LNString &codepath, 
					const LNString &sourcejar,
					LNNoteBody *notebody = 0,
					const LNString *objectjar = 0,
					const LNString *resourcejar = 0,
					const LNText *librarynames = 0);

	LNAgentJava (LNNoteBody *notebody);
	LNNoteBody * GetNoteBody() const;
	LNSTATUS LoadJavaCodeInfo();
	LNSTATUS SetIsImportedJava(LNBOOL imported);
	LNSTATUS SaveJavaCodeInfo();

	LNString ClassPath;
	LNString BaseClassName;
	LNString CodePath;
	LNText CodeFiles;
	LNString SourceJar;
	LNString ObjectJar;
	LNString ResourceJar;
	LNText LibraryNames;
	LNBOOL IsImportedJava;  // TRUE if imported java, FALSE - if 'native' java (new in R5) 
	LNBOOL IsProcessedJava; // if TRUE java files does not need additional processing
							// (conversion to jar's)
	LNNoteBody * NoteBody;

/* NOTES_JAVA
	// Data members are used for Java services only
	LNText SourceJarFileList;
	LNText ResourceJarFileList;
	LNBOOL ObjectJarExists;

	JavaMachine *JM;
	// End of the data members for Java services
NOTES_JAVA */

};

#endif
