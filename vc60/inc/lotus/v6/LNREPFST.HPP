//===========================================================================
//
// Module:		LNREPLICATIONFILESTATISTICS.HPP
//
// Description:	Class library definition for the LNReplicationFileStatistics 
//				class.
//
//===========================================================================
//
// Copyright (c) 1997 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNREPLICATIONFILESTATISTICS_HPP
#define LNREPLICATIONFILESTATISTICS_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

#ifndef REPLR_DEFS
#include "repl.h"
#endif


//
//	Class definition for LNReplicationFileStatistics.
//
class LNIMPEXPCL LNReplicationFileStatistics : public LNNotesClass
{
friend class LNReplicationStatistics;

public:
	LNReplicationFileStatistics();
	~LNReplicationFileStatistics();

	LNReplicationFileStatistics
			( const LNReplicationFileStatistics &other );

	LNReplicationFileStatistics & operator=
			( const LNReplicationFileStatistics &other );

	LNCLASSID GetClassID() const 
			{return LNCLASS_LNREPLICATIONFILESTATISTICS;}

	LNINT 	GetFailures() const
			{ return FileStats.Failed; }

	LNINT 	GetFilesCompleted() const
			{ return FileStats.FilesCompleted; }

	LNINT 	GetNotesAdded() const
			{ return FileStats.NotesAdded; }

	LNINT 	GetNotesDeleted() const
			{ return FileStats.NotesDeleted; }

	LNINT 	GetNotesUpdated() const
			{ return FileStats.NotesUpdated; }

	LNINT 	GetNumberOfErrors() const
			{ return FileStats.NumberErrors; }

	LNINT 	GetSuccesses() const
			{ return FileStats.Successful; }

	LNINT 	GetTotalFiles() const
			{ return FileStats.TotalFiles; }

private:
	LNReplicationFileStatistics(REPLFILESTATS* filestats);

	REPLFILESTATS  FileStats;

};

#endif	//LNREPLICATIONFILESTATISTICS_HPP

