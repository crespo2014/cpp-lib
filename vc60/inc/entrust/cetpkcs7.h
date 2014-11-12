/******************************************************************************
 * etpkcs7.h - Header file for the Entrust/File C Language API.                                             
 *             PKCS7 Protect and Unprotect formatting routines    
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.          
 *****************************************************************************/

#ifndef CETPKCS7_H
#define CETPKCS7_H
                    
#ifdef	MACOS
#ifndef	__FILES__
#include	<files.h>
#endif
#endif

#include <time.h>
#if !defined( ENTAPI )
#include <cetcert.h>
#include <entbdefs.h>
#else
#include <toolkit/entapi/cetcert.h>
#include <toolkit/entapi/tkbdefs.h>
#endif

/*
   ETEXPORT/ETEXPORT32 modifiers
   -------------------------
   The ETEXPORT and ETEXPORT32 modifiers are defined in ENTBDEFS.H, 
   The following table summarizes their values on different platforms.
  
   Platform        	ETEXPORT             			ETEXPORT32
   --------         ------						--------
   Win16			__export __far __pascal			
   Win32			__stdcall					__declspec( dllexport )
   Mac
   Unix
*/	

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif                                                        

/*	
   Buffer based security operation functions 

   ETStartProtect is used to start a data protection operation.
*/              
ETEXPORT32 EntLog ETEXPORT ETStartProtect(	const ETContext ctx, 
									 	const PROTECT_OPTIONS protectOptions); 
	
/*
   Once ETStartProtect is called, subsequent calls to ETProtect 
   are made to actually input and process the plaintext data.
   Note that no output data is provided. All data is buffered by the
   Toolkit and returned to the application via the ETEndProtect function.
*/
ETEXPORT32 EntLog ETEXPORT ETProtect(	const ETContext ctx, 
									const ETBinData32* inBuffer);								   

/*
   Once all input data has been supplied to ETProtect, the operation is completed by 
   one or more calls to ETEndProtect.
   ETEndProtect will return one of three types of return codes...
   1) ENT_CONTINUE_NEEDED: this means that ETEndProtect must be called again to retrieve
   more data.
   2) ENT_OK: ETEndProtect does not have to be called again, but may have returned
   residual data.
   3) anything else: an error has occured, as indicated by the value of the returned
      EntLog.

   Output data may be returned via the csHeader and outBuffer parameters.
   If the csHeader->size is non zero, the data pointed to by csHeader->data must be 
   written out to the output file or device first.
   Next, if outBuffer->size is non zero, the contents pointed to by outBuffer->data
   can be written out to the output file or device. 
   
*/ 
ETEXPORT32 EntLog ETEXPORT ETEndProtect(const ETContext ctx, 
									ETBinData32* csHeader,
									ETBinData32* outBuffer );
                                                                        
/*                                                                       
   ETStartUnprotect is used to start an unprotect sequence.
   An initial buffer of protected data can be supplied via startSeq.
   Output may be returned via the partialOut parameter, depending on
   type of data protection which had been applied to the input data.
   Note: if the input data is clear signed, ALL of the signed
   info header must be included within the startSeq buffer.                                                                        
*/              
ETEXPORT32 EntLog ETEXPORT ETStartUnprotect(const ETContext ctx,
										const ETBinData32* startSeq,
										ETBinData32* partialOut);
										
/*                                                                       
   ETUnprotect continues the unprotect sequence started by ETStartUnprotect.
   A buffer of protected data is supplied via inBuffer.
   Output may be returned via the outBuffer parameter.
*/              
ETEXPORT32 EntLog ETEXPORT ETUnprotect(	const ETContext ctx, 
									const ETBinData32* inBuffer, 
									ETBinData32* outBuffer);								   

/*
   Once all input data has been supplied to ETUnprotect, the operation is completed by 
   one or more calls to ETEndUnprotect.
   ETEndUnprotect will return one of three types of return codes...
   1) ENT_CONTINUE_NEEDED: this means that ETEndUnprotect must be called again to retrieve
   more data.
   2) ENT_OK: ETEndUnprotect does not have to be called again, but may have returned
   residual data. The unprotectInfo parameter will point to information about the
   data which was unprotected.
   3) anything else: an error has occured, as indicated by the value of the returned
      EntLog.
   Note that certificates included with the message will be stored in the
   internal certificate list for further examination. See CETCERT.H for more
   information on examining certificate information.

*/ 
ETEXPORT32 EntLog ETEXPORT ETEndUnprotect(	const ETContext ctx, 
										ETBinData32* out,
										ETUNPROTECT_INFO* unprotectInfo);
	
/*	
   File based security operation functions 

   ETFileProtect takes a plaintext file specified by inFile, and a set of
   protectOptions, and generates a protected output file specified by outFile.
*/              
ETEXPORT32 EntLog ETEXPORT ETFileProtect(	const ETContext ctx,
										const PROTECT_OPTIONS protectOptions,
										const char* inFile,
										const char* outFile);

/*	
   ETFileUnprotect takes a protected file specified by inFile, 
   and generates an unprotected output file specified by outFile.
   Information about the unprotect process is provided via unprotectInfo.
   Note that certificates included with the message will be stored in the
   internal certificate list for further examination. See CETCERT.H for more
   information on examining certificate information.
*/              
ETEXPORT32 EntLog ETEXPORT ETFileUnprotect(	const ETContext ctx,
										ETUNPROTECT_INFO* unprotectInfo,
										const char* inFile,
										const char* outFile);

/*	
   ETFileUnprotectVI (with Virus Info) takes a protected file specified by inFile, 
   and generates an unprotected output file specified by outFile.
   Information about the unprotect process is provided via unprotectInfo,
   and any virus information is supplied via the vOutput parameter.
   The application owns the storage of the VirusDetectInfo structure.
   Note that certificates included with the message will be stored in the
   internal certificate list for further examination. See CETCERT.H for more
   information on examining certificate information.
*/              
ETEXPORT32 EntLog ETEXPORT ETFileUnprotectVI(const ETContext ctx,
										ETUNPROTECT_INFO* unprotectInfo,
										const char* inFile,
										const char* outFile,
										VirusDetectInfo* vOutput);
/*	
   This version of "ETFileUnprotect" is used for processing clear-signed messages
   where the PKCS7 token and the plain text are in different files.
  
   ETFileUnprotectCS takes a PKCS7 token file specified by tknFile,
   a file that contains plain text that corresponds the PKCS7 token file,
   and generates an unprotected output file specified by outFile.
   Information about the unprotect process is provided via unprotectInfo
   and any virus information is supplied via the vOutput parameter.
   Note that certificates included with the message will be stored in the
   internal certificate list for further examination. See CETCERT.H for more
   information on examining certificate information.
*/
ETEXPORT32 EntLog ETEXPORT ETFileUnprotectCS(
									const ETContext ctx,
									ETUNPROTECT_INFO* unprotectInfo,
									const char* inFile,
									const char* outFile,
									const char* tknFile,
									VirusDetectInfo* vOutput);
/*
  ETGetPKCS7FileInfo takes a protected file specified by inFile and returns
  information about how the file was protected in unprotectInfo.  Any
  certificates included with this message will be stored internally and can be
  accessed using the functions defined in CETCERT.H.  The specified file is NOT
  unprotected.
  */
ETEXPORT32 EntLog ETEXPORT ETGetPKCS7FileInfo( const ETContext ctx,
										   ETUNPROTECT_INFO* unprotectInfo,
										   const char* inFile );
/*
  ETFilePKCS7FileInfoCS takes a PKCS7 token file specified by tknFile,
  and returns information on how the file specified by inFile was protected via
  unprotectInfo.  Any certificates included with this message will be stored internally
  and can be accessed using the functions defined in CETCERT.H.  The file specified by
  inFile is NOT unprotected.
  */
ETEXPORT32 EntLog ETEXPORT ETGetPKCS7FileInfoCS( const ETContext ctx,
											 ETUNPROTECT_INFO* unprotectInfo,
											 const char *inFile,
											 const char *tknFile );

										/*
   ETCreatePKCS7CertOnlyMessage creates a PKCS#7 certificate only message,
   with the certificates specified by the protectFlags parameter.
*/
ETEXPORT32 EntLog ETEXPORT ETCreatePKCS7CertOnlyMessage(
								const ETContext ctx,
								const PROTECT_FLAGS protectFlags,
								ETBinData32* messageOut);

/*
   This method will return the raw digest from the last PKCS7 operation.
*/
ETEXPORT32 EntLog ETEXPORT ETGetMessageDigest(const ETContext ctx,
										  ETBinData32* digest);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

