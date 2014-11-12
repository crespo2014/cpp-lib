//===========================================================================
//
// Module:	LNLOGENT.HPP
//
// Description:  Class library definition for LNLogEntry
//
//===========================================================================
//
// Copyright (c) 1995 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNLOGENT_HPP
#define LNLOGENT_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif


class LNIMPEXPCL LNLogEntry : public LNNotesClass
{
	friend class LNNotesSession;

public:
	LNSTATUS Append(const LNDatetime &datetime, const LNString &name) const;
	LNSTATUS Append(const LNNUMBER &num, const LNString &name) const;
	LNSTATUS Append(const LNString &string, const LNString &name) const;
	LNBOOL   GetLockEntry() const;
	void     SetLockEntry(LNBOOL locked);

	// Pure virtual method in the base class LNNotesClass
	virtual LNCLASSID GetClassID() const {return LNCLASS_LNLOGENTRY;}

	LNLogEntry();
	~LNLogEntry();

private:
	WORD   EntryNumber;
	LNBOOL Locked;

	LNBOOL IsNewEntryValid() const;
	LNBOOL IsEntryValid() const;

	LNLogEntry(const LNLogEntry &logentry);
	LNLogEntry & operator=(const LNLogEntry &logentry);

};


#endif	//LNLOGENTRY_HPP



//===========================================================================
//                             REVISION HISTORY
//===========================================================================
//
//   Date	Who	Description
// --------	---	-----------
// 04/02/97	RJD	Changed definitions of classes that need to be exported in DLL.
// 08/23/96	SJB	Removed instance data Closed.
// 08/08/96	SJB	Changed Get/SetLockedEntry to Get/SetEntryLock. Made all
//				AppendXXX() methods to be just Append().
// 08/08/96	SJB	Changed #define to LNLOGENT_HPP
// 07/22/96	SJB	Is(New)EntryValid methods should be private.
// 07/22/96	SJB	Added IsNewEntryValid, IsEntryValid. Made constructor
//				and destructor public.
// 07/11/96	SJB	AppendItem methods now pass by const-reference.
// 05/31/96	SJB	Initial version.
//
//===========================================================================

