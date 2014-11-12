//===========================================================================
//
// Module:	LNSESSIO.HPP
//
// Description:
//
//		Class library definition for the LNNotesSession, LNDatabaseArray, and
//		LNCreateDatabaseOptions classes.
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSESSIO_HPP
#define LNSESSIO_HPP

#ifndef LNSERVERADDIN_HPP
#include "lnsaddin.hpp"
#endif

#ifndef LNLOGENTRY_HPP
#include "lnlogent.hpp"
#endif

#ifndef LNDB_HPP
#include "lndb.hpp"
#endif

#ifndef LNMAIL_HPP
#include "lnmail.hpp"
#endif

#ifndef NSF_DB_DEFS
#include <nsfdb.h>
#endif

#ifndef NSF_SEARCH_DEFS
#include <nsfsearc.h>
#endif

#ifndef STD_NAME_DEFS
#include <stdnames.h>
#endif

#ifndef LNMQ_HPP
#include "lnmq.hpp"
#endif

#ifndef LNREPLICATIONSTATISTICS_HPP
#include "lnrepsta.hpp"
#endif

#ifndef LNREPLICATIONOPTIONS_HPP
#include "lnrepopt.hpp"
#endif

#ifndef LNCALEND_HPP
#include "lncalend.hpp"
#endif


#ifndef LNAP_HPP
#include "lnadminp.hpp"
#endif

//-----	Flags for LNNotesSession::GetDatabases.

typedef WORD LNGETDBFLAGS;

#define LNGETDBFLAGS_DATABASES	0x0001	// get databases
#define LNGETDBFLAGS_TEMPLATES	0x0002	// get database templates
#define LNGETDBFLAGS_RECURSE	0x0004	// recurse into subdirectories


//-----	Options for LNCreateDatabaseOptions::Get/SetLocalEncryption.

enum LNLOCALENCRYPTION
{
	LNLOCALENCRYPTION_NONE		=	DBCREATE_ENCRYPT_NONE,
	LNLOCALENCRYPTION_SIMPLE	=	DBCREATE_ENCRYPT_SIMPLE,
	LNLOCALENCRYPTION_MEDIUM	=	DBCREATE_ENCRYPT_MEDIUM,
	LNLOCALENCRYPTION_STRONG	=	DBCREATE_ENCRYPT_STRONG
};

//-----	Mail program used by Notes.

enum LNMAILPROGRAM
{
	LNMAILPROGRAM_NOTES = MAILSYSTEM_NOTES,
	LNMAILPROGRAM_CCMAIL = MAILSYSTEM_CCMAIL,
	LNMAILPROGRAM_VIM = MAILSYSTEM_VIMMAIL,
	LNMAILPROGRAM_NONE = MAILSYSTEM_NONE,
	LNMAILPROGRAM_UNKNOWN = 9999
};

#ifndef LNREG_HPP
#include "lnreg.hpp"
#endif

//-----	Other data.

typedef WORD LNNOTESVERSION;

//---------------------------------------------------------------------------
// 	Class name:	LNCreateDatabaseOptions
//
//	Description:
//
//	Options used by the LNNotesSession CreateDatabase functions.
//
//---------------------------------------------------------------------------

//-----	Values of Flags member. For internal use only.

#define	LNCREATEDBFLAG_OVERWRITE		0x0001
#define	LNCREATEDBFLAG_DESIGN_ONLY		0x0002
#define	LNCREATEDBFLAG_INHERIT_DESIGN	0x0004

class LNIMPEXPCL LNCreateDatabaseOptions : public LNNotesClass
{
public:
	LNCreateDatabaseOptions();
	LNCreateDatabaseOptions( const LNCreateDatabaseOptions &options )
		: LNNotesClass(options) { Copy(options); }

	~LNCreateDatabaseOptions() {}

	LNCreateDatabaseOptions & operator=( const LNCreateDatabaseOptions &options );

	virtual LNCLASSID GetClassID() const
		{ return LNCLASSID_LNCREATEDATABASEOPTIONS; }

	LNBOOL GetCopyACL() const
		{ return (CopyFlags & DBCOPY_NO_ACL) == 0; }

	LNBOOL GetCopyDesignOnly() const
		{ return (Flags & LNCREATEDBFLAG_DESIGN_ONLY) != 0; }

	LNBOOL GetCreateFTIndex() const
		{ return (CopyFlags & DBCOPY_NO_FULLTEXT) == 0; }

	LNBOOL GetInheritDesign() const
		{ return (Flags & LNCREATEDBFLAG_INHERIT_DESIGN) != 0; }

	LNLOCALENCRYPTION GetLocalEncryption() const
		{ return (LNLOCALENCRYPTION) Encryption; }

	LNBOOL GetPreserveNoteModifiedTime() const
		{ return (CopyFlags & DBCOPY_KEEP_NOTE_MODTIME) != 0; }

	LNINT GetSizeLimitInMB() const { return SizeLimit; }

	LNBOOL GetOverwriteExistingFile() const
		{ return (Flags & LNCREATEDBFLAG_OVERWRITE) != 0; }

	void SetCopyACL( LNBOOL flag );

	void SetCopyDesignOnly( LNBOOL flag );

	void SetCreateFTIndex( LNBOOL flag );

	void SetInheritDesign( LNBOOL flag );

	LNSTATUS SetLocalEncryption( LNLOCALENCRYPTION option );

	void SetPreserveNoteModifiedTime( LNBOOL flag );

	LNSTATUS SetSizeLimitInMB( LNINT size );

	void SetOverwriteExistingFile( LNBOOL flag );

private:
	DWORD CopyFlags;
	WORD CreateFlags;
	WORD Flags;
	BYTE Encryption;
	LNINT SizeLimit;

	void Copy( const LNCreateDatabaseOptions &options );

	DWORD GetCopyFlags() const { return CopyFlags; }

	WORD GetCreateFlags() const { return CreateFlags; }

	BYTE GetEncryptionByte() const { return Encryption; }

	LNINT GetSizeLimitInBytes() const { return SizeLimit * 1024 * 1024; }
};

//---------------------------------------------------------------------------
// 	Class name:	LNDatabaseArray
//
//	Description:
//
//	Array of all or some Notes databases on the local or a remote machine.
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNDatabaseArray : public LNSmartPtr
{
public:
	LNDatabaseArray() {}
	LNDatabaseArray( const LNDatabaseArray &dbarray ) : LNSmartPtr(dbarray) {}

	~LNDatabaseArray() {}

	LNDatabaseArray & operator=( const LNDatabaseArray &dbarray )
		{ LNSmartPtr::operator=(dbarray); return *this; }

	LNDatabase operator[]( LNINT n );

	virtual LNCLASSID GetClassID() const { return LNCLASSID_LNDATABASEARRAY; }

	LNINT GetCount() const;

private:
	LNDatabaseArray & operator=( LNDatabaseArrayBody *dbarray )
		{ LNSmartPtr::operator=((LNBody *)dbarray); return *this; }

	LNDatabaseArrayBody * GetDatabaseArrayBody() const
		{ return (LNDatabaseArrayBody *) Body; }
};

//---------------------------------------------------------------------------
// 	Class name:	LNNotesSession
//
//	Description:
//
//	Container of data and objects pertaining to a Notes session.
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNNotesSession : public LNNotesClass
{
friend class LNCalendar;				
public:
	LNNotesSession();
	~LNNotesSession();

	static void operator delete( void *object );
	static void * operator new( size_t size );

	LNSTATUS AbbreviateName( const LNString &name, LNString *shortname ) const;
	
	LNSTATUS CanonicalizeName( const LNString &name, LNString *longname ) const;
	
	LNSTATUS CompactDatabase
		( const LNString &path, LNINT *newsize = 0, LNINT *oldsize = 0 ) const;
	LNSTATUS CompactDatabase
		( const LNDatabase &db, LNINT *newsize = 0, LNINT *oldsize = 0 ) const;
	LNSTATUS CompleteLogEntry( LNLogEntry *logentry ) const;

	LNSTATUS CreateAdministrationProcess(const LNString &server, LNAdministrationProcess *adminp);
	
	LNSTATUS CreateCertifier( const LNIDFile &idfile, const LNRegistrationOptions &options,
		const LNString &org, const LNDatetime &expiration, LNCertifier *cert,
		const LNString &logfile = "" );
	LNSTATUS CreateCertifier( const LNString &idfilepath, const LNRegistrationOptions &options,
		const LNString &org, const LNDatetime &expiration, LNCertifier *cert,
		const LNString &logfile = "" );

	LNSTATUS CreateDatabase
		( const LNString &path, const LNString &server = "", LNDatabase *db = 0 )
		{ return CreateDatabase(path, server, LNCreateDatabaseOptions(), db); }
	LNSTATUS CreateDatabase
		( const LNString &path, const LNString &server,
		  const LNCreateDatabaseOptions &options, LNDatabase *db = 0 );

	LNSTATUS CreateDatabaseCopy
		( const LNDatabase &srcdb, const LNString &newdb_path,
		  const LNString &newdb_server = "", LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb, newdb_path, newdb_server, LNCreateDatabaseOptions(),
				 newdb, FALSE);
		}
	LNSTATUS CreateDatabaseCopy
		( const LNDatabase &srcdb, const LNString &newdb_path,
		  const LNString &newdb_server, const LNCreateDatabaseOptions &options,
		  LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb, newdb_path, newdb_server, options, newdb, FALSE);
		}
	LNSTATUS CreateDatabaseCopy
		( const LNString &srcdb_path, const LNString &srcdb_server,
		  const LNString &newdb_path, const LNString &newdb_server = "",
		  LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb_path, srcdb_server, newdb_path, newdb_server,
				 LNCreateDatabaseOptions(), newdb, FALSE);
		}
	LNSTATUS CreateDatabaseCopy
		( const LNString &srcdb_path, const LNString &srcdb_server,
		  const LNString &newdb_path, const LNString &newdb_server,
		  const LNCreateDatabaseOptions &options, LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb_path, srcdb_server, newdb_path, newdb_server, options,
				 newdb, FALSE);
		}
	
	LNSTATUS CreateDatabaseFromTemplate
		( const LNDatabase &templatedb, const LNString &newdb_path,
		  const LNString &newdb_server = "", LNDatabase *newdb = 0 )
		{
			return CreateDatabaseFromTemplate
				(templatedb, newdb_path, newdb_server, LNCreateDatabaseOptions(),
				 newdb);
		}
	LNSTATUS CreateDatabaseFromTemplate
		( const LNDatabase &templatedb, const LNString &newdb_path,
		  const LNString &newdb_server, const LNCreateDatabaseOptions &options,
		  LNDatabase *newdb = 0 );
	LNSTATUS CreateDatabaseFromTemplate
		( const LNString &templatedb_path, const LNString &templatedb_server,
		  const LNString &newdb_path, const LNString &newdb_server = "",
		  LNDatabase *newdb = 0 )
		{
			return CreateDatabaseFromTemplate
				(templatedb_path, templatedb_server, newdb_path, newdb_server,
				 LNCreateDatabaseOptions(), newdb);
		}
	LNSTATUS CreateDatabaseFromTemplate
		( const LNString &templatedb_path, const LNString &templatedb_server,
		  const LNString &newdb_path, const LNString &newdb_server,
		  const LNCreateDatabaseOptions &options, LNDatabase *newdb = 0 );

	LNSTATUS CreateDatabaseReplica
		( const LNDatabase &srcdb, const LNString &newdb_path,
		  const LNString &newdb_server = "", LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb, newdb_path, newdb_server, LNCreateDatabaseOptions(),
				 newdb, TRUE);
		}
	LNSTATUS CreateDatabaseReplica
		( const LNDatabase &srcdb, const LNString &newdb_path,
		  const LNString &newdb_server, const LNCreateDatabaseOptions &options,
		  LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb, newdb_path, newdb_server, options, newdb, TRUE);
		}
	LNSTATUS CreateDatabaseReplica
		( const LNString &srcdb_path, const LNString &srcdb_server,
		  const LNString &newdb_path, const LNString &newdb_server = "",
		  LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb_path, srcdb_server, newdb_path, newdb_server,
				 LNCreateDatabaseOptions(), newdb, TRUE);
		}
	LNSTATUS CreateDatabaseReplica
		( const LNString &srcdb_path, const LNString &srcdb_server,
		  const LNString &newdb_path, const LNString &newdb_server,
		  const LNCreateDatabaseOptions &options, LNDatabase *newdb = 0 )
		{
			return CreateDatabaseCopyOrReplica
				(srcdb_path, srcdb_server, newdb_path, newdb_server, options,
				 newdb, TRUE);
		}

	LNSTATUS CreateLogEntry
		( LNLogEntry *logentry, const LNString &formname = LOG_EVENT_FORM ) const;

	LNSTATUS CreateMailMessage( LNMailMessage *message );

	LNSTATUS CreateMessageQueue
		( const LNString& mqname, LNINT quota, LNMessageQueue*newmq = 0 );
	LNSTATUS CreateMessageQueue
		( const LNString& mqname, LNMessageQueue*newmq = 0 );

	LNSTATUS DeleteDatabase( const LNString &path, const LNString &server = "" );
	LNSTATUS DeleteDatabase( LNDatabase *db );

	LNSTATUS DiscardLogEntry( LNLogEntry *logentry ) const;

	LNSTATUS ExecuteServer
		( const LNString &server, const LNString &command, 
		  LNString *response ) const;

	LNSTATUS FreeTimeSearch
		(const LNDatetimeRange &range, LNINT duration, LNDatetimes *freetime);
	LNSTATUS FreeTimeSearch
		(const LNDatetimeRange &range, LNINT duration, LNDatetimes *freetime, 
		const LNString &username) const;
	LNSTATUS FreeTimeSearch
		(const LNDatetimeRange &range, LNINT duration, LNDatetimes *freetime,
		LNText &usernames)const;
	LNSTATUS FreeTimeSearch
		(const LNDatetimes &ranges, LNINT duration, LNDatetimes *freetime);
	LNSTATUS FreeTimeSearch
		(const LNDatetimes &ranges, LNINT duration, LNDatetimes *freetime, 
		const LNString &username) const;
	LNSTATUS FreeTimeSearch
		(const LNDatetimes &ranges, LNINT duration, LNDatetimes *freetime,
		LNText &usernames) const;

	LNSTATUS GetAddressBooks
		( LNDatabaseArray *dbarray, const LNString &server = "" );

	LNSTATUS GetCalendar(LNCalendar *calendar, const LNString &server = "", 
		const LNString &dbname = "", const LNString &username = "");

	LNSTATUS GetCertifier( const LNIDFile &idfile, const LNDatetime &expiration,
		LNCertifier *cert, const LNString &password = "", const LNString &logfile = "" );
	LNSTATUS GetCertifier( const LNString &idfilepath, const LNDatetime &expiration,
		LNCertifier *cert, const LNString &password = "", const LNString &logfile = "" );

	virtual LNCLASSID GetClassID() const
		{ return LNCLASSID_LNNOTESSESSION; }

	LNDatetime GetCurrentDatetime() const;

	LNSTATUS GetDatabase
		( const LNString &path, LNDatabase *db, const LNString &server = "" );
	LNSTATUS GetDatabase
		( const char *path, LNDatabase *db, const LNString &server = "" )
		{ return GetDatabase(LNString(path), db, server); }
	LNSTATUS GetDatabase
		( const DBID &replicaid, LNDatabase *db, const LNString &server = "" );
	LNSTATUS GetDatabase( DBHANDLE handle, LNDatabase *db );

	LNDBOPENFLAGS GetDatabaseOpenFlags() const;
	
	LNSTATUS GetDatabases
		( LNDatabaseArray *dbarray, const LNString &server = "",
		  const LNString &dir = "",
		  LNGETDBFLAGS flags = LNGETDBFLAGS_DATABASES | LNGETDBFLAGS_RECURSE );

	LNString GetDataDirectory();

	LNString GetEnvironmentString( const LNString &variable ) const;
	
	LNSINT GetEnvironmentValue( const LNString &variable ) const;

	LNSTATUS GetIDFile( const LNString &filepath, LNIDFile *idfile ) const;

	LNInternational GetInternational() const;

	LNSTATUS GetLocationDocument( LNDocument *doc );

	LNSTATUS GetMailDatabase( LNDatabase *db );

	LNMAILPROGRAM GetMailProgram();

	LNString GetMailServer();

	LNSTATUS GetMessageQueue( const LNString &mqname, LNMessageQueue *mq );

	LNSTATUS GetNotesVersion
		( LNNOTESVERSION *version, const LNString &server = "" );

	LNString GetPort() const { return Port; }

	LNText GetPorts();

	LNRTPARSERERRORHANDLER GetRTParserErrorHandler() const;

	LNSTATUS GetServerAddin
		( const LNString &task, const LNString &text, LNServerAddin *AddinPtr);

	LNSTATUS GetServerNames( LNText *names ) const;

	LNBOOL GetSignHotspotsInRichText() const;

	LNBOOL GetThrowAllErrors();
	
	LNString GetUserName()
		{ return GetUserNameText(); }

	LNINT GetViewFolderCacheSize();

	LNSTATUS Init( int argc, char *argv[] )
		{ return Initialize(LNGetAPIProgramVersion(), argc, argv, TRUE, 0); }
	LNSTATUS Init(LNBOOL initnotes)
		{ return Initialize(LNGetAPIProgramVersion(), 0, 0, initnotes, 0); }
#if !defined UNIX && !defined MAC
	LNSTATUS Init(const char *pathname = 0 )
		{ return Initialize(LNGetAPIProgramVersion(), 0, 0, TRUE, pathname); }
#endif

	LNSTATUS InitThread();

	LNBOOL IsInitialized() const;

	LNBOOL IsServerAvailable(const LNString &server) const;

	LNBOOL IsThreadInitialized() const;

	LNSTATUS Replicate( const LNString &server ) const;
	LNSTATUS Replicate
		( const LNString &server, const LNReplicationOptions &options,
		  LNReplicationStatistics *stats = 0 ) const;

	LNSTATUS SetDatabaseOpenFlags( LNDBOPENFLAGS flags );

	LNSTATUS SetEnvironmentString
		( const LNString &variable, const LNString &string ) const;
	
	LNSTATUS SetEnvironmentValue( const LNString &variable, LNSINT value ) const;

	LNSTATUS SetPort( const LNString &port )
		{ return SetPortName(port); }

	LNRTPARSERERRORHANDLER SetRTParserErrorHandler(LNRTPARSERERRORHANDLER fn);

	void SetSignHotspotsInRichText( LNBOOL flag = TRUE );

	void SetThrowAllErrors( LNBOOL flag );

	LNSTATUS SetViewFolderCacheSize(LNINT cacheSize);
	
	LNSTATUS Term( LNBOOL report_leaks = FALSE );
	
	LNSTATUS TermThread();

private:
	LNDBOPENFLAGS DatabaseOpenFlags;
	char *DataDirectory;
	WORD Flags;
	LNVERSION LibraryVersion;
	LNMAILPROGRAM MailProgram;
	LNNOTESVERSION NotesVersion;
	LNString Port;
	LNObjectList Objects;
	LNRTPARSERERRORHANDLER RTParserErrorHandler;
	LNServerAddin *ServerAddinPtr;
	LNBOOL SignHotspotsInRichText;
	LNBOOL ThrowAllErrors;
	LNINT ThrowAllErrorsSequence;
	char *UserName;

	// copy constructor and assignment operator are private (and undefined) to
	// prevent anyone from using them

	LNNotesSession( const LNNotesSession &session );
	LNNotesSession & operator=( const LNNotesSession &session );

	// other private functions

	LNSTATUS AddObjectToList( LNNotesClass *object )
		{ return Objects.AddObject(object); }

	LNString GetUserNameText();

	LNSTATUS Initialize
		( LNVERSION version, int argc, char *argv[], LNBOOL initnotes, const char *pathname );

	LNSTATUS ConstructNetPathname
		( const LNString &path, const LNString &server, char *buffer ) const;

	LNSTATUS CreateDatabaseCopyOrReplica
		( const LNDatabase &srcdb, const LNString &newdb_path,
		  const LNString &newdb_server, const LNCreateDatabaseOptions &options,
		  LNDatabase *newdb, LNBOOL replica );
	LNSTATUS CreateDatabaseCopyOrReplica
		( const LNString &srcdb_path, const LNString &srcdb_server,
		  const LNString &newdb_path, const LNString &newdb_server,
		  const LNCreateDatabaseOptions &options, LNDatabase *newdb,
		  LNBOOL replica );

	LNSTATUS SetPortName( const LNString &port );
};

#endif	//LNSESSIO_HPP

