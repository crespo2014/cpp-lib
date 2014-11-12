//===========================================================================
//
// Module:	LNCLASSI.H
//
// Description:
//
//		C++ API class ID codes.
//
//===========================================================================
//
// Copyright (c) 1995-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNCLASSI_H
#define LNCLASSI_H


enum LNCLASSID
{
	LNCLASS_BEGIN = 0,			// marks beginning of range of valid class IDs

	#include "lnclids.h"		// bring in other class IDs, starting at 1

	LNCLASSID_LNDATETIMERANGES,	// for compatibility with C++ API Release 4.x
	LNCLASS_END					// marks end of valid class ID range
};

#endif	// LNCLASSI_H

