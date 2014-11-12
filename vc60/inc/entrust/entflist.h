/*******************************************************************************
 * entflist.h - EntFileList class declarations.
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef ENTFLIST_H
#define ENTFLIST_H
  
#if !defined( ENTAPI )
#include <entbdefs.h> 
#include <entgstr.h>
#else
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/gstring.h>
#include <base/etfile/entlog.h>
#endif 

#ifdef	MACOS
#ifndef	__FILES__
#include	<files.h>
#endif
#endif

//
// The FileSpecification type contains file information
// used for the file oriented security member functions of
// EntFile:SetFileSignEncrypt and SetFileDecryptVerify.
//

#ifdef	MACOS
typedef FSSpec* FileSpecification;
#else
typedef GString FileSpecification;
#endif

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class CliFileList;

//
// An EntFileList stores a list of file specifications, used to
// specify the files which are to be secured in an Entrust 
// archive file.
// When input files are opened for securing, the file names
// are created by concatenating the specified root directory
// with the file specification.
// See the second form of GetFile below for concatentation rules.
// EXCEPTION: On the Macintosh platform, rootDirectory arguments
// and ignored, and all file information is conveyed through the
// FileSpecification structure.
//
// Note that relative path information supplied with the file
// specification is preserved in the archive file, while
// root directory information is not.

// EXAMPLE for Windows:
// This example shows multiple ways a given input file could be specified.
// The absolute path is the input file's complete designation.
// archived info is the file name information which will be available
// when the encapsulated file is decrypted/verified.
// 
// absolute path       rootDirectory     fileInfo            archived info
// -------------       -------------     --------            -------------
// c:\tmp\test\my.txt                    c:\tmp\test\my.txt  c:\tmp\test\my.txt
// c:\tmp\test\my.txt  c:\               tmp\test\my.txt     tmp\test\my.txt
// c:\tmp\test\my.txt  c:\tmp\           test\my.txt         test\my.txt
// c:\tmp\test\my.txt  c:\tmp\test\      my.txt              my.txt
// 
// Notes:
// - when the encapsulated file within the archive is decrypted and/or
//   verified, the file name of the plaintext file generated is obtained
//   by concatenating a specified output root directory with the archived
//   relative path information.
// - if the specified rootDirectory + fileInfo does not designate an absolute
//   path, it will be treated as a relative path from the current directory.
// - if drive information is included in the absolute path, it is generally
//   advisable to parse it and place it in the rootDirectory argument,
//   so that a recipient without the same drive designation can still extract
//   the file without having to suppress the archived path information.
//    
//
class EntFileList {
public:                       
	//
	// This constructor creates an empty list.
	//
	EXPT32 EXPT EntFileList(void);
	EXPT32 EXPT EntFileList(const EntFileList& list);
	EXPT32 EntFileList& EXPT operator=( const EntFileList& list );
	//
	// This constructor starts the list with an initial entry.
	// Note: rootDirectory is ignored on the Mac.
	//
	EXPT32 EXPT EntFileList(const GString& rootDirectory,
							const FileSpecification& fileInfo);

	EXPT32 EXPT ~EntFileList(void);
	//
	// Add the specified file to the list.
	// Note: rootDirectory is ignored on the Mac.
	//
	EXPT32 EntLog EXPT AddFile(	const GString& rootDirectory,
								const FileSpecification& fileInfo);
	//
	// Retrieve the number of file specifications in the list.
	//
 	EXPT32 INT16 EXPT GetNumberOfFiles(void) const;
	//
	// Retrieve the root directory and file specification elements
	// in the list indicated by index. The first element is index 0.
	// Note: rootDirectory will return an empty string on the Mac.
	//
	EXPT32 EntLog EXPT GetFile( GString& rootDirectory,
								FileSpecification& fileInfo, 
								SYSINT index) const;
	//
	// Retrieve the full file specification of the entry indicated by index,
	// by concatenating the rootDirectory and fileInfo.
	// The first element is index 0.
	// Concatentation rules for Unix and Windows platforms are as follows:
	// (where separator is '\' on Windows and '/' on Unix, and '|' is
	// the concatentation operator).
	//
	// If rootDirectory ends with a separator, or fileInfo starts with
	// a separator, fileSpec = rootDirectory | fileInfo.
	// Otherwise, fileSpec = rootDirectory | separator | fileInfo 
	//
	EXPT32 EntLog EXPT GetFile( FileSpecification& fileSpec, 
								SYSINT index) const;
	//
	// Reset deletes the current contents of the list.
	//
	EXPT32 void EXPT Reset(void);
	
	CliFileList *m_CliFileList;
};

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif
