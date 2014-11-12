/*******************************************************************************
 * cetflist.h - Input File List declarations.
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef CETFLIST_H
#define CETFLIST_H
  
#if !defined( ENTAPI )
#include <entbdefs.h> 
#else
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/entlog.h>
#endif 

#ifdef	MACOS
#ifndef	__FILES__
#include	<files.h>
#endif
#endif

/*
   The ETFileSpecification type contains file information
   used for the file oriented security functions
   ETSetFileSignEncrypt and ETSetFileDecryptVerify.
*/
#ifdef	MACOS
typedef FSSpec* ETFileSpecification;
#else
typedef char* ETFileSpecification;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

/*
   The Entrust user context maintains one input file list, which is
   used to specify a list of files to secure when creating an
   Entrust archive file (see CETAPI.H, function ETSetArchiveSignEncrypt).

   When input files are opened for securing, the file names
   are created by concatenating the specified root directory
   with the file specification. See the description of 
   ETGetFullFileSpecification below for concatentation rules.
   EXCEPTION: On the Macintosh platform, rootDirectory arguments
   and ignored, and all file information is conveyed through the
   FileSpecification structure.
  
   Note that relative path information supplied with the file
   specification is preserved in the archive file, while
   root directory information is not.

   EXAMPLE for Windows:
   This example shows multiple ways a given input file could be specified.
   The absolute path is the input file's complete designation.
   archived info is the file name information which will be available
   when the encapsulated file is decrypted/verified.
   
   absolute path       rootDirectory     fileInfo            archived info
   -------------       -------------     --------            -------------
   c:\tmp\test\my.txt                    c:\tmp\test\my.txt  c:\tmp\test\my.txt
   c:\tmp\test\my.txt  c:\               tmp\test\my.txt     tmp\test\my.txt
   c:\tmp\test\my.txt  c:\tmp\           test\my.txt         test\my.txt
   c:\tmp\test\my.txt  c:\tmp\test\      my.txt              my.txt
   
   Notes:
   - when the encapsulated file within the archive is decrypted and/or
     verified, the file name of the plaintext file generated is obtained
     by concatenating a specified output root directory with the archived
     relative path information.
   - if the specified rootDirectory + fileInfo does not designate an absolute
     path, it will be treated as a relative path from the current directory.
   - if drive information is included in the absolute path, it is generally
     advisable to parse it and place it in the rootDirectory argument,
     so that a recipient without the same drive designation can still extract
     the file without having to suppress the archived path information.
      
  
*/
	/*
	   Add the specified file to the list.
	   Note: rootDirectory is ignored on the Mac.
	*/
	ETEXPORT32 EntLog ETEXPORT ETAddFile(	const ETContext ctx, 
										const char* rootDirectory,
										const ETFileSpecification fileInfo);
	/*
	   Retrieve the number of file specifications in the list, or -1 on error.
	*/
	ETEXPORT32 INT16 ETEXPORT ETGetNumberOfFiles(const ETContext ctx);
	/*
	   Retrieve the file specification element in the list indicated by index.
	   The first element is index 0.
	   The strings copied to the storage pointed to by rootDirectory and
	   fileInfo will be at most MAX_NAME_SIZE in length.
	   Note: rootDirectory will return an empty string on the Mac.
	*/
	ETEXPORT32 EntLog ETEXPORT ETGetFile(	const ETContext ctx, 
										char* rootDirectory,
										ETFileSpecification fileInfo, 
										SYSINT index);
	/*
	
	 Retrieve the full file specification of the entry indicated by index,
	 by concatenating the rootDirectory and fileInfo.
	 The first element is index 0.
	 Concatentation rules for Unix and Windows platforms are as follows:
	 (where separator is '\' on Windows and '/' on Unix, and '|' is
	 the concatentation operator).
	
	 If rootDirectory ends with a separator, or fileInfo starts with
	 a separator, fileSpec = rootDirectory | fileInfo.
	 Otherwise, fileSpec = rootDirectory | separator | fileInfo 
	 The string copied to the storage pointed to by fileSpec
	 will be at most MAX_NAME_SIZE in length.
	*/
	ETEXPORT32 EntLog ETEXPORT ETGetFullFileSpecification(	const ETContext ctx, 
														ETFileSpecification fileSpec, 
														SYSINT index);
	/*
	   Reset deletes the current contents of the list.
	*/
	ETEXPORT32 void ETEXPORT ETResetFileList(const ETContext ctx);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
