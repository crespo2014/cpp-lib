//===========================================================================
//
// Module:	LNSADDIN.HPP
//
// Description:
//
//		Class library definition for LNServerAddin and LNAddinStatusLine
//		classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSADDIN_HPP
#define LNSADDIN_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

typedef LNINT LNSTATUSLINEID;

class LNIMPEXPCL LNServerAddin : public LNNotesClass
{

public:
	LNServerAddin();
	~LNServerAddin();

	void AppendLogMessage( const LNString &message );

	LNSTATUS CreateStatusLine
		( const LNString &task, const LNString &text,
		  LNSTATUSLINEID *nStatusLineID );

	LNSTATUS DeleteStatusLine( LNSTATUSLINEID nStatusLineID );

	virtual LNCLASSID GetClassID() const { return LNCLASS_LNSERVERADDIN; }

	LNString GetDefaultStatusLineTaskName();

	LNString GetDefaultStatusLineText();

	LNSTATUS GetStatusLineTaskName
		( LNSTATUSLINEID StatusLineID, LNString *TaskNamePtr );

	LNSTATUS GetStatusLineText
		( LNSTATUSLINEID StatusLineID, LNString *TextDescPtr );

	LNBOOL HaveMinutesElapsed( LNINT min );

	LNBOOL HaveSecondsElapsed( LNINT sec );

	LNBOOL Idle();
	LNBOOL Idle( LNINT mSecs );

	LNBOOL IsNewDay();

	LNSTATUS SetDefaultStatusLine( LNSTATUSLINEID *StatusLineID );

	void SetDefaultStatusLineTaskName( const LNString &NewString );

	void SetDefaultStatusLineText( const LNString &NewString );

	LNSTATUS SetStatusLineTaskName
		( LNSTATUSLINEID nStatusLineID, const LNString &NewString );

	LNSTATUS SetStatusLineText
		( LNSTATUSLINEID StatusLineID, const LNString &NewString );

	LNBOOL ShouldAddinTerminate();

private:
	LNAddinStatusLine *DefaultStatusLinePtr;
	LNObjectList LNOStatusLines;
	
	virtual LNSTATUS Close();

	void CreateDefaultStatusLine( const LNString &task, const LNString &text );

	LNSTATUS CreateStatusLine
		( const LNString &task, const LNString &text,
		  LNSTATUSLINEID StatusLineID );

	LNBOOL FindStatusLine
		( const LNObjectList &List, LNSTATUSLINEID StatusLineID, 
		  LNAddinStatusLine **CurrLinePtrPtr );

	void ServerAddinInit
		( const LNString &task, const LNString &text,
		  const LNNotesSession *session );

	// the following are disabled
	
	LNServerAddin( const LNServerAddin &addin) ;
	LNServerAddin & operator=( const LNServerAddin &addin );

};

class LNIMPEXPCL LNAddinStatusLine : public LNNotesClass
{

public:
	~LNAddinStatusLine();

	virtual LNCLASSID GetClassID() const { return LNCLASS_LNADDINSTATUSLINE; }

private:
	HANDLE DescHandle;
	LNString TaskName;
	LNString StatusText;
	LNServerAddin *ServerAddinPtr;
	LNSTATUSLINEID LineID;

	LNAddinStatusLine();
	LNAddinStatusLine( const LNString &TaskName, const LNString &StatusText );
	LNAddinStatusLine( HANDLE NewDescHandle );
	LNAddinStatusLine( const LNAddinStatusLine &statusline );
	LNAddinStatusLine & operator=( const LNAddinStatusLine &statusline );
};


#endif	//LNSADDIN_HPP

