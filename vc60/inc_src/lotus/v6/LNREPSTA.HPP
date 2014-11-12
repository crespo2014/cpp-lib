//===========================================================================
//
// Module:		LNREPLICATIONSTATISTICS.HPP
//
// Description:	Class library definition for the LNReplicationStatistics class.
//
//===========================================================================
//
// Copyright (c) 1997 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNREPLICATIONSTATISTICS_HPP
#define LNREPLICATIONSTATISTICS_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

#ifndef LNREPLICATIONFILESTATISTICS_HPP
#include "lnrepfst.hpp"
#endif

#ifndef REPLR_DEFS
#include <repl.h>
#endif

//
//	Class definition for LNReplicationStatistics.
//
class LNIMPEXPCL LNReplicationStatistics : public LNNotesClass
{
friend class LNNotesSession;
friend class LNReplicationFileStatistics;

public:
	LNReplicationStatistics();
	~LNReplicationStatistics();

	LNReplicationStatistics( const LNReplicationStatistics &other );
	LNReplicationStatistics & operator=( const LNReplicationStatistics &other );

	LNCLASSID	GetClassID() const 
				{ return LNCLASS_LNREPLICATIONSTATISTICS; }

	LNSTATUS	GetLastError() const
				{ return (LNSTATUS)Stats.LastError; }

	LNINT		GetNumberOfErrors() const
				{ return (LNINT)Stats.NumberErrors;}

	LNReplicationFileStatistics	GetReceivedStatistics()
				{ return LNReplicationFileStatistics(&Stats.Pull); }

	LNReplicationFileStatistics	GetSentStatistics()
				{ return LNReplicationFileStatistics(&Stats.Push); }

	LNINT 		GetStubsInitialized() const
				{ return (LNINT)Stats.StubsInitialized; }

	LNINT 		GetTotalUnreadExchanges() const
				{ return (LNINT)Stats.TotalUnreadExchanges; }

private:
	
	LNReplicationStatistics(REPLSERVSTATS* replstats);

	REPLSERVSTATS 				Stats;

};

#endif	//LNREPLICATIONSTATISTICS_HPP

