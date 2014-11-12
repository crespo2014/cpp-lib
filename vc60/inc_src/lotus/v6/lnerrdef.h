//===========================================================================
//
// Module:	LNERRDEF.H
//
// Description:
//
//		C++ API error and warning code macro definitions.
//
//===========================================================================
//
// Copyright (c) 1996-2000 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNERRDEF_H
#define LNERRDEF_H

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif


//-----	Define base error/warning code values.

#define LNERRDEF(name, msg ) , LNERR_CODE_##name
#define LNWARNDEF(name, msg ) , LNWARN_CODE_##name

enum
{
	LNERR_UNUSED_CODE = 0		// force the first real code to start at 1

#include "lnerrors.h"			// define base codes

};

//-----	Define actual error/warning code LNSTATUS values.

#undef LNERRDEF
#undef LNWARNDEF

#define LNERRDEF( name, msg )     \
	const LNSTATUS LNERR_##name = \
		(((LNSTATUS) LNSTATUS_ERROR) << 16) + LNERR_CODE_##name;

#define LNWARNDEF( name, msg )     \
	const LNSTATUS LNWARN_##name = \
		(((LNSTATUS) LNSTATUS_WARNING) << 16) + LNWARN_CODE_##name;

#include "lnerrors.h"


#endif	// LNERRDEF_H

