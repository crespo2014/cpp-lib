/*******************************************************************************
 * enthdr.h - EntHeader class declarations.
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef ENTHDR_H
#define ENTHDR_H
  
#if !defined( ENTAPI )
#include <entbdefs.h> 
#else
#include <base/etfile/etfile.h>
#include <toolkit/entapi/tkbdefs.h>
#endif 

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class GStringListUS;

//
// An EntHeader is the Entrust PEM style security header. Headers are
// stored as a list of one or more GStrings (see ENTGSTR.H).
//
class EntHeader {
public:
	EXPT32 EXPT EntHeader(void);
	//
	// This constructor populates the header with the contents of headerData.
	//
	EXPT32 EXPT EntHeader(GString &headerData);

	EXPT32 EXPT ~EntHeader(void);
	//
	// Append the provided headerData to the header.
	//
	EXPT32 void EXPT AddString(GString &headerData);
	//
	// Retrieve the total number of characters in the header.
	//
	EXPT32 UINT32 EXPT GetLength(void);
	//
	// Retrieve the number of GString elements in the list.
	//
 	EXPT32 INT16 EXPT GetNumberOfStrings(void);
	//
	// Retrieve the GString element in the list indicated by index.
	// The first element is index 0.
	//
	EXPT32 EntLog EXPT GetString(GString &headerData, SYSINT index);

	//
	// GetType returns the type of the header, which the application stripped off of
	// an incoming signed and/or encrypted message.
	//
	EXPT32 HEADER_TYPE EXPT GetType(void);
	//
	// Reset deletes the current contents of the header string list.
	//
	EXPT32 void EXPT Reset(void);

	GStringListUS *m_GStringListUS;
};

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif
