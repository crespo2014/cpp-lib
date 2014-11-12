//===========================================================================
//
// Module:		LNREG.HPP
//
// Description:
//
//		Class library definitions for the registration related classes.
//
//===========================================================================
//
// Copyright (c) 1997-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNREG_HPP
#define LNREG_HPP

#ifndef USERREG_DEFS
#include "reg.h"
#endif

#define fREGSetInternetPassword 0x1000

#define MAXMINPWLENGTH 31
#define MAXPWQUALITY 16


enum LNIDTYPE
{
	LNIDTYPE_DERIVED = KFM_IDFILE_TYPE_DERIVED,
	LNIDTYPE_FLAT = KFM_IDFILE_TYPE_FLAT,
	LNIDTYPE_STANDARD = KFM_IDFILE_TYPE_STD
};

enum LNCLIENTTYPE
{
	LNCLIENTTYPE_DESKTOP,
	LNCLIENTTYPE_FULL,
	LNCLIENTTYPE_MAIL
};

//
//	Class definition for LNRegistrationOptions.
//
class LNIMPEXPCL LNRegistrationOptions : public LNNotesClass
{
friend class LNCertifier;
friend class LNNotesSession;

public:
	LNRegistrationOptions();

	LNRegistrationOptions( const LNRegistrationOptions &other );

	~LNRegistrationOptions() {}

	LNRegistrationOptions & operator=( const LNRegistrationOptions &other );

	LNString GetAdministrator() const { return Administrator; }

	LNCLASSID GetClassID() const { return LNCLASSID_LNREGISTRATIONOPTIONS; }

	LNCLIENTTYPE GetClientType() const;

	LNString GetComment() const { return Comment; }

	LNString GetCountry() const { return Country; }

	LNBOOL GetCreateAddressBookEntry() const
		{ return (Flags & fREGCreateAddrBookEntry) != 0; }

	LNBOOL GetCreateIDFile() const
		{ return (Flags & fREGCreateIDFileNow) != 0; }

	LNBOOL GetCreateMailDatabase() const
		{ return (Flags & fREGCreateMailFileNow) != 0; }

	LNBOOL GetCreateMailDatabaseUsingAdminp() const
		{ return (Flags & fREGCreateMailFileUsingAdminp) != 0; }

	LNBOOL GetCreateNorthAmericanID() const
		{ return (Flags & fREGUSARequested) != 0; }

	LNString GetForwardingAddress() const { return ForwardingAddress; }

	LNIDTYPE GetIDType() const { return (LNIDTYPE)IDType; }

	LNString GetLocalAdministrator() const { return LocalAdministrator; }

	LNString GetLocation() const { return Location; }

	LNString GetMailFilepath() const { return MailFilepath; }

	LNMAILPROGRAM GetMailProgram() const { return (LNMAILPROGRAM)MailProgram; }

	LNString GetMailServer() const { return MailServer; }

	LNINT GetMinPasswordLength() const { return (LNINT)MinPasswordQuality; }
    
        LNINT GetMinPasswordQuality() const { return (LNINT)MinPasswordQuality; }

	LNString GetNetworkName() const { return NetworkName; }

	LNString GetOrganizationUnit() const { return OrganizationUnit; }

	LNBOOL GetOverwriteAddressBook() const
		{ return (Flags & fREGOkayToModifyAddrbook) != 0; }

	LNBOOL GetOverwriteIDFile() const
		{ return (Flags & fREGOkayToModifyID) != 0; }

	LNString GetPassword() const { return Password; }

	LNString GetProfileNames() const { return ProfileNames; }

	LNString GetRegistrationServer() const { return RegistrationServer; }

	LNBOOL GetSaveIDInAddressBook() const
		{ return (Flags & fREGSaveIDInAddrBook) != 0; }

	LNBOOL GetSaveIDInFile() const
		{ return (Flags & fREGSaveIDInFile) != 0; }

	LNBOOL GetSaveInternetPassword() const
		{ return (Flags & fREGSetInternetPassword) != 0; }

	LNString GetTitle() const { return Title; }

	LNSTATUS SetAdministrator( const LNString &administrator )
	{
		Administrator = administrator;
		return LNNOERROR;
	}

	LNSTATUS SetClientType( LNCLIENTTYPE clienttype );

	LNSTATUS SetComment( const LNString &comment )
	{
		Comment = comment;
		return LNNOERROR;
	}

	LNSTATUS SetCountry( const LNString &country )
	{
		Country = country;
		return LNNOERROR;
	}

	void SetCreateAddressBookEntry( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGCreateAddrBookEntry;
		else
			Flags &= ~fREGCreateAddrBookEntry;
	}
//		{ flag ? Flags |= fREGCreateAddrBookEntry : Flags &= ~fREGCreateAddrBookEntry; }

	void SetCreateIDFile( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGCreateIDFileNow;
		else
			Flags &= ~fREGCreateIDFileNow;
	}
//		{ flag ? Flags |= fREGCreateIDFileNow : Flags &= ~fREGCreateIDFileNow; }

	void SetCreateMailDatabase( LNBOOL flag )
		{
			if (flag)
			{
				Flags &= ~fREGCreateMailFileUsingAdminp;
				Flags |= fREGCreateMailFileNow;
			}
			else
				Flags &= ~fREGCreateMailFileNow;
		}

	void SetCreateMailDatabaseUsingAdminp( LNBOOL flag )
		{
			if (flag)
			{
				Flags &= ~fREGCreateMailFileNow;
				Flags |= fREGCreateMailFileUsingAdminp;
			}
			else
				Flags &= ~fREGCreateMailFileUsingAdminp;
		}

	void SetCreateNorthAmericanID( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGUSARequested;
		else
			Flags &= ~fREGUSARequested;
	}
//		{ flag ? Flags |= fREGUSARequested : Flags &= ~fREGUSARequested; }

	LNSTATUS SetForwardingAddress( const LNString &forwardaddress )
	{
		ForwardingAddress = forwardaddress;
		return LNNOERROR;
	}

	LNSTATUS SetIDType( LNIDTYPE type );

	LNSTATUS SetLocalAdministrator( const LNString &localadmin )
	{
		LocalAdministrator = localadmin;
		return LNNOERROR;
	}

	LNSTATUS SetLocation( const LNString &location )
	{
		Location = location;
		return LNNOERROR;
	}

	LNSTATUS SetMailFilepath( const LNString &mailfilepath )
	{
		MailFilepath = mailfilepath;
		return LNNOERROR;
	}

	LNSTATUS SetMailProgram( LNMAILPROGRAM mailprogram );

	LNSTATUS SetMailServer( const LNString &mailserver )
	{
		MailServer = mailserver;
		return LNNOERROR;
	}

	LNSTATUS SetMinPasswordLength( LNINT pwlength );
    
        LNSTATUS SetMinPasswordQuality( LNINT pwquality );

	LNSTATUS SetNetworkName( const LNString &netname )
	{
		NetworkName = netname;
		return LNNOERROR;
	}

	LNSTATUS SetOrganizationUnit( const LNString &orgunit )
	{
		OrganizationUnit = orgunit;
		return LNNOERROR;
	}

	void SetOverwriteAddressBook( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGOkayToModifyAddrbook;
		else
			Flags &= ~fREGOkayToModifyAddrbook;
	}
//		{ flag ? Flags |= fREGOkayToModifyAddrbook : Flags &= ~fREGOkayToModifyAddrbook; }

	void SetOverwriteIDFile( LNBOOL flag )	
	{
		if(flag)
			Flags |= fREGOkayToModifyID;
		else
			Flags &= ~fREGOkayToModifyID;
	}
//		{ flag ? Flags |= fREGOkayToModifyID : Flags &= ~fREGOkayToModifyID; }

	LNSTATUS SetPassword( const LNString &password )
	{
		Password = password;
		return LNNOERROR;
	}

	LNSTATUS SetProfileNames( const LNString &profilenames )
	{
		ProfileNames = profilenames;
		return LNNOERROR;
	}

	LNSTATUS SetRegistrationServer( const LNString &regserver )
	{
		RegistrationServer = regserver;
		return LNNOERROR;
	}

	void SetSaveIDInAddressBook( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGSaveIDInAddrBook;
		else
			Flags &= ~fREGSaveIDInAddrBook;
	}
//		{ flag ? Flags |= fREGSaveIDInAddrBook : Flags &= ~fREGSaveIDInAddrBook; }

	void SetSaveIDInFile( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGSaveIDInFile;
		else
			Flags &= ~fREGSaveIDInFile;
	}
//		{ flag ? Flags |= fREGSaveIDInFile : Flags &= ~fREGSaveIDInFile; }

	void SetSaveInternetPassword( LNBOOL flag )
	{
		if(flag)
			Flags |= fREGSetInternetPassword;
		else
			Flags &= ~fREGSetInternetPassword;
	}
//		{ flag ? Flags |= fREGSetInternetPassword : Flags &= ~fREGSetInternetPassword; }

	LNSTATUS SetTitle( const LNString &title )
	{
		Title = title;
		return LNNOERROR;
	}

private:
	void CopyData( const LNRegistrationOptions &other );

	REGFlags GetFlags() const { return Flags; }

	LNString Administrator;
	LNString Comment;
	LNString Country;
	REGFlags Flags;
	LNString ForwardingAddress;
	WORD IDType;
	LNString LocalAdministrator;
	LNString Location;
	LNString MailFilepath;
	WORD MailProgram;
	LNString MailServer;
	WORD MinPasswordLength;
        WORD MinPasswordQuality;
	LNString NetworkName;
	LNString OrganizationUnit;
	LNString Password;
	LNString ProfileNames;
	LNString RegistrationServer;
	LNString Title;
};

//
//	Class definition for LNIDFile.
//
class LNIMPEXPCL LNIDFile : public LNNotesClass
{
friend class LNNotesSession;

public:
	LNIDFile() {}

	LNIDFile( const LNIDFile &other );

	~LNIDFile() {}

	LNIDFile & operator=( const LNIDFile &other );

	LNCLASSID GetClassID() const { return LNCLASSID_LNIDFILE; }

	LNCLIENTTYPE GetClientType() const;

	LNString GetFilepath() const { return Filepath; }

	LNSTATUS GetUserName( LNString *username ) const;

	LNBOOL IsCertifier() const;
	
	LNBOOL IsHierarchical() const;
	
	LNBOOL IsNorthAmerican() const;
	
	LNBOOL IsSafe() const;	

private:
	LNIDFile( const LNNotesSession *session, const LNString &filepath );

	LNString Filepath;
};

//
//	Class definition for LNCertifier.
//
class LNIMPEXPCL LNCertifier : public LNNotesClass
{
friend class LNNotesSession;
public:
	LNCertifier();

	~LNCertifier();

	LNSTATUS CrossCertify( const LNIDFile &idfile, const LNString &regserver = "",
		const LNString &comment = "" );
	LNSTATUS CrossCertify( const LNString &idfilepath, const LNString &regserver = "",
		const LNString &comment = "" );

	LNCLASSID GetClassID() const { return LNCLASSID_LNCERTIFIER; }

	LNDatetime GetExpirationDate() const;

	LNString GetName() const;

	LNINT GetVersion() const;

	LNBOOL IsHierarchical() const;

	LNSTATUS Recertify( const LNIDFile &idfile,	const LNDatetime &expdate,
		const LNString &regserver = "", const LNString &orgunit = "" );
	LNSTATUS Recertify( const LNString &idfilepath,	const LNDatetime &expdate,
		const LNString &regserver = "", const LNString &orgunit = "" );

	LNSTATUS RegisterCertifier( const LNIDFile &idfile, const LNRegistrationOptions &options,
		const LNString &orgunit );
	LNSTATUS RegisterCertifier( const LNString &idfilepath, const LNRegistrationOptions &options,
		const LNString &orgunit );

	LNSTATUS RegisterServer( const LNIDFile &idfile, const LNRegistrationOptions &options,
		const LNString &servername, const LNString &domain );
	LNSTATUS RegisterServer( const LNString &idfilepath, const LNRegistrationOptions &options,
		const LNString &servername, const LNString &domain );

	LNSTATUS RegisterUser( const LNIDFile &idfile, const LNRegistrationOptions &options,
		const LNString &lastname, const LNString &firstname = "",
		const LNString &middleinitial = "" );
	LNSTATUS RegisterUser( const LNString &idfilepath, const LNRegistrationOptions &options,
		const LNString &lastname, const LNString &firstname = "",
		const LNString &middleinitial = "" );

protected:	
	HCERTIFIER GetCertifierContext () const {return CertContext;}

private:
	LNCertifier( const LNCertifier &other );	//disabled.

	LNCertifier & operator=( const LNCertifier &other );	//disabled.

	void Assign( const LNNotesSession *session, HCERTIFIER certctx, TIMEDATE *expiration,
		BOOL hierarchical, const LNCHAR *name, WORD version );

	HCERTIFIER CertContext;
	TIMEDATE ExpirationDate;
	BOOL Hierarchical;
	LNString Name;
	WORD Version;
};

#endif	//LNREG_HPP

