//===========================================================================
//
// Module:		LNREPOPT.HPP
//
// Description:
//		
//		Class library definition for the LNReplicationOptions class.
//
//===========================================================================
//
// Copyright (c) 1997, 1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNREPOPT_HPP
#define LNREPOPT_HPP

#ifndef LNSESSIO_HPP
#include "lnsessio.hpp"
#endif

#ifndef LNDB_HPP
#include "lndb.hpp"
#endif

#ifndef LNTEXT_HPP
#include "lntext.hpp"
#endif

#ifndef REPLR_DEFS
#include <repl.h>
#endif

//----- enumeration of the Replication Direction types

enum LNREPLICATIONDIRECTION
{
	LNREPLICATIONDIRECTION_BOTH,   		//default, both directions
	LNREPLICATIONDIRECTION_RECEIVE,		//replicate from the server to the local machine
	LNREPLICATIONDIRECTION_SEND		    //replicate from the local machine to the server
};

//----- enumeration of the type of replication files

enum LNREPLICATIONFILETYPE
{
	LNREPLICATIONFILETYPE_SPECIFIC,		//replicate with specific file list if any
	LNREPLICATIONFILETYPE_NSF,			//database only
	LNREPLICATIONFILETYPE_NTF,			//design templates only
	LNREPLICATIONFILETYPE_ALL			//both databases and templates, default
};

//
//	Class definition for LNReplicationOptions.
//
class LNIMPEXPCL LNReplicationOptions : public LNNotesClass
{
public:
	LNReplicationOptions();
	LNReplicationOptions( const LNReplicationOptions &other );

	~LNReplicationOptions();

	LNReplicationOptions & operator=( const LNReplicationOptions &other );

	LNCLASSID GetClassID() const { return LNCLASS_LNREPLICATIONOPTIONS; }

	LNBOOL GetCloseSession() const
//		{ return (Opts & REPL_OPTION_CLOSE_SESS) ? TRUE : FALSE; }
	{
		if (Opts & REPL_OPTION_CLOSE_SESS)
			return TRUE;
		else
			return FALSE;
	}

	LNREPLICATIONDIRECTION GetDirection() const;

	LNText GetFileList() const { return FileList; }

	LNREPLICATIONFILETYPE GetFileType() const;

	LNString GetPort() const { return Port; }

	LNREPLICATIONPRIORITY GetPriority() const;

	void SetCloseSession(LNBOOL close);

	LNSTATUS SetDirection( LNREPLICATIONDIRECTION where );

	LNSTATUS SetFileList( LNDatabaseArray &dbarray );
	LNSTATUS SetFileList( const LNText &filelist );

	LNSTATUS SetFileType( LNREPLICATIONFILETYPE whichfiles );

	LNSTATUS SetPort( const LNString &port );

	LNSTATUS SetPriority( LNREPLICATIONPRIORITY priority );

private:
	void CopyOpts( const LNReplicationOptions &other );
							    
	LNText FileList;
	LNString Port;
    DWORD Opts;
};

#endif	//LNREPOPT_HPP

