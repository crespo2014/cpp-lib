//===========================================================================
//
// Module:	LNCAPI.H
//
// Description:
//
//		C API header files included by C++ API header files.
//
//===========================================================================
//
// Copyright (c) 1995-2001 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNCAPI_H
#define LNCAPI_H

#ifndef COLORID_DEFS
#include <colorid.h>
#endif

#ifndef DESIGN_DEFS
#include <design.h>
#endif

#ifndef EDIT_ODS_DEFS
#include <editods.h>
#endif

#ifndef FT_DEFS
#include <ft.h>
#endif

#ifndef IDTABLE_DEFS
#include <idtable.h>
#endif

#ifndef INTL_DEFS
#include <intl.h>
#endif

#ifndef MISC_DEFS
#include <misc.h>
#endif

#ifndef NAMES_DEFS
#include <names.h>		// needed for MAILSYSTEM_xxx constants
#endif

#ifndef NIF_DEFS
#include <nif.h>
#endif

#ifndef NIF_COLLATE_DEFS
#include <nifcoll.h>	// needed for NIF_STAT_xxx constants in LNVIEW.HPP
#endif

#ifndef NSF_DATA_DEFS
#include <nsfdata.h>
#endif

#ifndef NSF_NOTE_DEFS
#include <nsfnote.h>
#endif

#ifndef NSF_DB_DEFS
#include <nsfdb.h>
#endif

#ifndef FILE_DEFS
#include <osfile.h>		// need this for FILE_CLASS values
#endif

#ifndef MEMORY_DEFS
#include <osmem.h>
#endif

#ifndef OSMISC_DEFS
#include <osmisc.h>		// needed for OSTranslate
#endif

#ifndef TIMEDATE_DEFS
#include <ostime.h>
#endif

#ifndef VIEWFMT_DEFS
#include <viewfmt.h>
#endif

#ifndef OLE_ODS_DEFS	// needed for LNForm Auto Launch stuff.
#include <oleods.h>
#endif

#endif	// LNCAPI_H

