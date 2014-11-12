/******************************************************************************
 * cethdr.h - Entrust header utilities for the C language interface.                                             
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.          
 *****************************************************************************/

#ifndef CETHDR_H
#define CETHDR_H

#if !defined( ENTAPI )
#include <entbdefs.h>
#else
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/etfile.h>
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
   An ETContext internally maintains a header object which
   can be created and manipulated via a set of utility functions.
   Internally, the PEM style Entrust header is maintained as a list of 
   character strings. A list of strings is used to support the possibility
   of headers which are greater than the maximum string length of 64 kbytes.
*/      
/*
   ETAddStringToHeader appends the supplied string to the end of the header.
*/
ETEXPORT32 void ETEXPORT ETAddStringToHeader(	const ETContext ctx, 
											const char* headerData);
/*
   Retrieve the total number of characters in the header.
*/
ETEXPORT32 UINT32 ETEXPORT ETGetHeaderLength(const ETContext ctx);
/*
   Retrieve the number of string elements in the header.
*/
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfStringsInHeader(const ETContext ctx);
/*
   Retrieve a pointer to the string element in the list indicated by index.
   The first element is index 0.
*/
ETEXPORT32 EntLog ETEXPORT ETGetHeaderString(const ETContext ctx, 
									char** headerData, 
									SYSINT index);

/*	
   ETGetHeaderType returns the type of the security header, which the 
   application  stripped off of an incoming signed and/or encrypted message.
   NOTE: this function only returns a valid result if called after the 
   entire header has been passed in via ETAddHeaderString. 	
*/	
ETEXPORT32 HEADER_TYPE ETEXPORT ETGetHeaderType(const ETContext ctx);
/*
   ETResetHeader deletes the current contents of the header string list.
*/	           
ETEXPORT32 void ETEXPORT ETResetHeader(const ETContext ctx);
	           
#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif	
