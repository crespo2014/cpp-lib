//
// Module:		LNADMINP.HPP
//
// Description:
//
//		Class library definition for the LNAdministrationProcess class.
//
//===========================================================================
//
// Copyright (c) 1999 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================
#ifndef LNAP_HPP
#define LNAP_HPP

#ifndef LNDOC_HPP
#include "lndoc.hpp"
#endif
//--------------------------------------------------------------------------
// Class name:	LNAdministrationProcess
//
//	Description:
//
//--------------------------------------------------------------------------

enum LNADMINDELETETYPE
{
	LNADMINDELETETYPE_DELETEONHOME = 0,
	LNADMINDELETETYPE_DELETEONREPLICAS,
	LNADMINDELETETYPE_DONTDELETE
};

class LNIMPEXPCL LNAdministrationProcess : public LNSmartPtr
{
friend class LNNotesSession;

public:
	LNAdministrationProcess (void);
	LNAdministrationProcess (const LNAdministrationProcess & other);
	LNAdministrationProcess (const LNString & server);

	~LNAdministrationProcess (void);

	LNAdministrationProcess & operator= (const LNAdministrationProcess & other);

	LNSTATUS 	Close();
	LNDatabase  GetAdminDatabase() const;
	LNCLASSID 	GetClassID() const {return LNCLASS_LNADMINISTRATIONPROCESS;}
	LNDatabase  GetNamesDatabase() const;
	LNSTATUS	ProcessRequests();
	LNSTATUS	RequestDeleteInACL( const LNString &username, const LNString &mailserver,
				const LNString &mailfile, LNADMINDELETETYPE type = LNADMINDELETETYPE_DONTDELETE);
	LNSTATUS	RequestDeleteInNAB( const LNString &username, const LNString &mailserver,
				const LNString &mailfile, LNADMINDELETETYPE type = LNADMINDELETETYPE_DONTDELETE);
	LNSTATUS	RequestMoveReplica( const LNString &srcdb_path, const LNString &srcdb_server, 
				const LNString &title, const LNString &destdb_path, const LNString &destdb_server);
	LNSTATUS	RequestMoveComplete( const LNCertifier &newcertifier, 
				const LNString &user, const LNString &organization = "");	
	LNSTATUS	RequestMoveUserInHierarchy( const LNCertifier &currentcertifier, 
				const LNString &user, const LNString &newcertifier);	
	LNSTATUS	RequestNewReplica( const LNString &srcdb_path, const LNString &srcdb_server, 
				const LNString &title, const LNString &destdb_path, const LNString &destdb_server);
	LNSTATUS	RequestRecertify(const LNCertifier &certifier, const LNString &name);
	LNSTATUS	RequestRename(const LNCertifier &certifier, const LNString &name, const LNString &firstname, const LNString &middleinitial, 
				const LNString &lastname, const LNString &organization);
//	LNSTATUS	SetAdminDatabase(const LNDatabase &db);
//	LNSTATUS	SetNamesDatabase(const LNDatabase &db);

private:

	LNAdministrationProcess & operator=( LNAdministrationProcessBody *adminpb );

	LNAdministrationProcessBody* GetAdministrationProcessBody() const
			{return (LNAdministrationProcessBody *)Body;}

};


#endif //LNAP_HPP

