// LNotesError.h: interface for the CLNotesError class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LNOTESERROR_H__CB78B724_E420_4F68_9C36_0CE819C91D91__INCLUDED_)
#define AFX_LNOTESERROR_H__CB78B724_E420_4F68_9C36_0CE819C91D91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Los includes de notes rompen la alineacion de las estructuras por ello hay que repuperarlas

#pragma pack(push, align)

#ifdef LOTUS8
#include "lotus\v8\global.h"
#include "lotus\v8\extmgr.h"
#include "lotus\v8\nsferr.h"
#include "lotus\v8\bsafeerr.h"
#include "lotus\v8\dname.h"
#include "lotus\v8\osmisc.h"
#include "lotus\v8\osenv.h"
#include "lotus\v8\ostime.h"
#include "lotus\v8\ns.h"
#include "lotus\v8\osmem.h"
#include "lotus\v8\nsfdb.h"
#include "lotus\v8\osfile.h"
#include "lotus\v8\acl.h"
#include "lotus\v8\kfm.h"
#include "lotus\v8\nsfsearc.h"
#include "lotus\v8\textlist.h"
#include "lotus\v8\agents.h"
#include "lotus\v8\oserr.h"
#include "lotus\v8\lookup.h"
#include "lotus\v8\reg.h"
#include "lotus\v8\nsfdata.h"
#include "lotus\v8\pool.h"
#include "lotus\v8\nsfnote.h"
#include "lotus\v8\mailserv.h"
#include "lotus\v8\easycd.h"
#include "lotus\v8\colorid.h"
#include "lotus\v8\bsafe.h"
#include "lotus\v8\editods.h" 
#pragma comment (lib,"..\\..\\..\\c++\\inc\\lotus\\v8\\lib\\notes.lib")
#endif

#ifdef LOTUS6
#include "lotus\v6\global.h"
#include "lotus\v6\extmgr.h"
#include "lotus\v6\nsferr.h"
#include "lotus\v6\bsafeerr.h"
#include "lotus\v6\dname.h"
#include "lotus\v6\osmisc.h"
#include "lotus\v6\osenv.h"
#include "lotus\v6\ostime.h"
#include "lotus\v6\ns.h"
#include "lotus\v6\osmem.h"
#include "lotus\v6\nsfdb.h"
#include "lotus\v6\osfile.h"
#include "lotus\v6\acl.h"
#include "lotus\v6\kfm.h"
#include "lotus\v6\nsfsearc.h"
#include "lotus\v6\textlist.h"
#include "lotus\v6\agents.h"
#include "lotus\v6\oserr.h"
#include "lotus\v6\lookup.h"
#include "lotus\v6\reg.h"
#include "lotus\v6\nsfdata.h"
#include "lotus\v6\pool.h"
#include "lotus\v6\nsfnote.h"
#include "lotus\v6\mailserv.h"
#include "lotus\v6\easycd.h"
#include "lotus\v6\colorid.h"
#include "lotus\v6\bsafe.h"
#include "lotus\v6\editods.h"
#include "lotus\v6\rsrcods.h"
#include "lotus\v6\actods.h"
#include "lotus\v6\ods.h"
#include "lotus\v6\editods.h"
#include "lotus\v6\editdflt.h"
#pragma comment (lib,"..\\inc\\lotus\v6\\lib\\notes.lib")
#endif

#pragma pack(pop, align)

class CLNotesError  
{
public:
	static char* getEMName(WORD id);
	char* getErrorString(STATUS ecode);
	CLNotesError();
	virtual ~CLNotesError();
private:
	char	m_err_str[500];
};

#endif // !defined(AFX_LNOTESERROR_H__CB78B724_E420_4F68_9C36_0CE819C91D91__INCLUDED_)
