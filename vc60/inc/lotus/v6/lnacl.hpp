//===========================================================================
//
// Module:	LNACL.HPP
//
// Description:
//
//		Class library definition for LNACL, LNACLENTRY, LNACLENTRYBODY,
//		LNACLENTRYARRAY and LNACLROLEARRAY classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNACL_HPP
#define LNACL_HPP

#include "lnstring.hpp"
#include "lncommon.hpp"

extern "C" 
{
#include <acl.h>
#include <miscerr.h>
}

const WORD MAX_NUM_OF_ROLES = 80;

#define FROM_ACL   		0x01
#define FROM_ACLENTRY 	0x02
#define LINEOTEXT   	256
#define PRIVBYTES       (ACL_PRIVCOUNT+7)/8

#define DEFAULT			ERR_ACL_DEFAULT_NAME

//enumeration of the ACL levels 
enum LNACLLEVEL
{
	// user or server has no access to the db
	LNACLLEVEL_NO_ACCESS = ACL_LEVEL_NOACCESS,
	// user or server can add new data docs. to a db
	LNACLLEVEL_DEPOSITOR = ACL_LEVEL_DEPOSITOR,
	// user or server can only view data docs. in the db
	LNACLLEVEL_READER = ACL_LEVEL_READER,	
	// user or server can create and/or edit their own docs.
	// and examine existing ones in the db
	LNACLLEVEL_AUTHOR = ACL_LEVEL_AUTHOR,	
	// user or server can create and/or edit any data docs.
	LNACLLEVEL_EDITOR = ACL_LEVEL_EDITOR,	
	// user or server can create and/or edit any data docs.	
	// and/or design documents
	LNACLLEVEL_DESIGNER = ACL_LEVEL_DESIGNER,
	// user or server can create and/or maintain any type of	  					
	// documents, including the ACL.
	LNACLLEVEL_MANAGER = ACL_LEVEL_MANAGER
};

//enumeration of the ACL user types
enum LNACLUSERTYPE
{
	LNACLUSERTYPE_PERSON,  		// ACL Entry is a person
	LNACLUSERTYPE_SERVER,  		// ACL Entry is a server
	LNACLUSERTYPE_GROUP,   		// ACL Entry is a group
	LNACLUSERTYPE_PERSONGROUP,	// ACL Entry is a group of persons
	LNACLUSERTYPE_SERVERGROUP, 	// ACL Entry is a group of servers
	LNACLUSERTYPE_UNKNOWN
};


extern "C"
void LNCALLBACK CountEntries (void *, char far *, WORD, 
			ACL_PRIVILEGES far *, WORD);

extern "C"
void LNCALLBACK EnumerateRoles (void *, char far *, WORD, 
         	ACL_PRIVILEGES far *, WORD);


//-----	Bit masks for the LNACL Flags data member.

#define ACLFLAG_NEWACL		0x0001	// 1 = ACL note doesn't exist on disk
#define ACLFLAG_ACLOPEN		0x0002	// 1 = ACL opened


//---------------------------------------------------------------------------
// Class name:	LNACL
//
//	Description:
//
//	Container of data and objects pertaining to a ACL note
//
//---------------------------------------------------------------------------

class LNIMPEXPCL LNACL : public LNNotesClass
{
friend class LNDatabaseBody;
friend class LNACLEntryArray;
friend class LNACLRoleArray;
friend class LNACLEntryBody;

public:

	LNACL();
	virtual ~LNACL();
						
	//ACLEntry related functions:

	LNSTATUS CreateEntry(const LNString &entryname, LNACLLEVEL level, 
			LNACLEntry *entry=0);
	LNSTATUS CreateEntry(const LNACLEntry &aclentry, 
			LNACLEntry* newentry=0);

	LNSTATUS DeleteAllEntries();

	LNSTATUS DeleteEntry(const LNString &entryname);
	LNSTATUS DeleteEntry(const LNACLEntry &entry);

	LNSTATUS GetDefaultEntry(LNACLEntry* aclentry);
	LNSTATUS GetEntry(const LNString &entryname, LNACLEntry *aclentry);

	LNSTATUS GetEntries(LNACLEntryArray* entries,
			LNACLLEVEL minlevel=LNACLLEVEL_NO_ACCESS);

	LNACLLEVEL GetAccessLevel(const LNString &entryname);
	LNACLLEVEL GetDefaultAccessLevel();

	LNSTATUS SetAccessLevel(const LNString &entryname, LNACLLEVEL level);
	LNSTATUS SetDefaultAccessLevel(LNACLLEVEL level);

	//Role related

	LNSTATUS CreateRole(const LNString &rolename);

	LNSTATUS DeleteRole(const LNString &rolename);

	LNSTATUS GetRoles(LNACLRoleArray* roles);

	LNSTATUS GetRoleMembers(const LNString &rolename, LNText* members);

	LNSTATUS RenameRole(const LNString &oldname, const LNString &newname);

	//Administration Entry Server ACL related, default is none:

    LNString GetAdminServer() const;
 
	LNBOOL	 GetUniformAccess();

	LNSTATUS SetAdminServer();
	LNSTATUS SetAdminServer(const LNString &server);

	LNSTATUS SetUniformAccess(LNBOOL flag);

	// Others

	virtual LNCLASSID GetClassID() const 
				{return LNCLASS_LNACL;}

	LNSTATUS Save();

	//place holders:
	//LNSTATUS GetHistoryHandle();
	//LNSTATUS GetHistoryCount();

protected:
	
private:
	//Copy Constructor and Assignment Operator are disabled.
	LNACL(const LNACL& other);
	LNACL& operator=(const LNACL& other);

	LNSTATUS 		Assign(LNDatabaseBody* db);
	void 			CopyACL(const LNACL &other );
	LNSTATUS 		Close();
	HANDLE 			GetACLHandle() {return AclHandle;}
	DBHANDLE 		GetDBHandle() {return DbHandle;}
	LNBOOL			IsDefault(const LNString & name);
	LNBOOL			IsDefaultSet() { return bSetDefault; }
	LNBOOL			IsRoleInList(LNString rolename);
	LNSTATUS 		IsRoleNameValid(LNString rolename);

	HANDLE   			AclHandle;
	LNBOOL				bSetDefault;
	LNDatabaseBody*		Db;
	DBHANDLE 			DbHandle;
	LNACLLEVEL			DefaultLevel;
	char 				DefaultName[MAXUSERNAME];
	DWORD	  			DwFlag;
	LNACLEntryArray* 	EntryArray;
	WORD 				Flags;
	LNACLLEVEL			MinLevel;
	LNACLRoleArray* 	RoleArray;

};


//---------------------------------------------------------------------------
// Class name:	LNACLEntry
//
//	Description:
//	
//---------------------------------------------------------------------------

class LNIMPEXPCL LNACLEntry : public LNSmartPtr
{
friend class LNACL;
friend class LNACLEntryBody;
friend class LNACLRoleArray;
friend class LNACLEntryArray;
friend void LNCALLBACK CountEntries (void *, char far *, WORD, 
 				ACL_PRIVILEGES far *, WORD);

public:

	LNACLEntry();

	LNACLEntry(const LNACLEntry& other);
	LNACLEntry& operator=(const LNACLEntry& other);

	virtual ~LNACLEntry();

	LNSTATUS DisableRole(const LNString &role);

	LNSTATUS EnableRole(const LNString &role);

	LNACLLEVEL GetAccessLevel() const;

	LNBOOL GetCanCreateDocuments() const;

	LNBOOL GetCanCreateLotusScript() const;

	LNBOOL GetCanCreatePersonalAgents() const;

	LNBOOL GetCanCreatePersonalFolders() const;

	LNBOOL GetCanCreateSharedFolders() const;

	LNBOOL GetCanDeleteDocuments() const;

	LNBOOL GetCanReadPublicDocuments() const;

	LNBOOL GetCanWritePublicDocuments() const;

	virtual LNCLASSID GetClassID() const
				{return LNCLASS_LNACLENTRY;}
	
	LNBOOL GetIsAdminServer() const;

	LNString GetName() const;

	LNSTATUS GetRoles(LNACLRoleArray* roles) const;

	LNACLUSERTYPE GetUserType() const;

	LNBOOL IsDefault() const;

	LNBOOL IsGroup() const;

	LNBOOL IsPerson() const;

	LNBOOL IsRoleEnabled(const LNString &role) const;

	LNBOOL IsServer() const;

	LNSTATUS SetAccessLevel(LNACLLEVEL level);

	void SetCanCreateDocuments(LNBOOL flag);

	void SetCanCreateLotusScript(LNBOOL flag);

	void SetCanCreatePersonalAgents(LNBOOL flag);

	void SetCanCreatePersonalFolders(LNBOOL flag);

	void SetCanCreateSharedFolders(LNBOOL flag);

	void SetCanDeleteDocuments(LNBOOL flag);

	void SetCanReadPublicDocuments(LNBOOL flag);

	void SetCanWritePublicDocuments(LNBOOL flag);

	void SetIsAdminServer(LNBOOL flag);

	LNSTATUS SetName(const LNString &name);

	LNSTATUS SetUserType(LNACLUSERTYPE type);

private:

	LNACLEntry& operator=(LNACLEntryBody* other);

	LNSTATUS CreateACLEntryBody(HANDLE aclhandle, LNString entryname, 
			LNACLLEVEL level=LNACLLEVEL_NO_ACCESS);

	LNACLEntryBody* GetACLEntryBody() const { return(LNACLEntryBody*)Body; }

	LNSTATUS 	Refresh();
};


//---------------------------------------------------------------------------
// Class name:	LNACLEntryArray
//
//	Description:
//	
//---------------------------------------------------------------------------

class LNIMPEXPCL LNACLEntryArray : public LNNotesClass
{
friend class LNACL;
friend class LNACLEntry;
friend class LNACLEntryBody;
friend void LNCALLBACK CountEntries (void *, char far *, WORD, 
      				ACL_PRIVILEGES far *, WORD);

public:

	LNACLEntryArray();

	virtual ~LNACLEntryArray();

	LNACLEntry operator[](LNINT n) const;
	
	virtual LNCLASSID GetClassID() const 
				{return LNCLASS_LNACLENTRYARRAY;}
	
	LNINT GetCount() const;

protected:

private:

	LNACLEntryArray(HANDLE aclhandle, LNSTATUS* lnstat, 
				LNACLLEVEL minlevel=LNACLLEVEL_NO_ACCESS);

	LNACLEntryArray(const LNACLEntryArray& other );
	LNACLEntryArray& operator=(const LNACLEntryArray& other );

	void AddEntry (LNACLEntryBody* entrybody);

	void CleanUpObjects();

	void CopyEntryArray(const LNACLEntryArray &other );

	LNBOOL 		IsModified() { return bModified; }
	LNSTATUS 	Refresh();

	HANDLE			AclHandle;
	LNBOOL			bModified;
	LNINT			Count;
	LNObjectList	EntryList;

};


//---------------------------------------------------------------------------
// Class name:	LNACLRoleArray
//
//	Description:
//	
//---------------------------------------------------------------------------

class LNIMPEXPCL LNACLRoleArray : public LNNotesClass
{
friend class LNACL;
friend class LNACLEntryBody;
friend void LNCALLBACK EnumerateRoles (void *, char far *, WORD, 
      				ACL_PRIVILEGES far *, WORD);
friend void LNCALLBACK CountEntries (void *, char far *, WORD, 
      				ACL_PRIVILEGES far *, WORD);

public:	 
	LNACLRoleArray();

	~LNACLRoleArray();
	
	LNString operator[]( LNINT n );
	
	virtual LNCLASSID GetClassID() const 
			{return LNCLASS_LNACLROLEARRAY;}
	
	LNINT GetCount() const;

protected:

private:
	LNACLRoleArray(HANDLE aclhandle, LNSTATUS *lnstat);
	LNACLRoleArray(HANDLE aclhandle, ACL_PRIVILEGES far *privbits, LNSTATUS *lnstat);

	LNACLRoleArray(const LNACLRoleArray& other );
	LNACLRoleArray & operator=(const LNACLRoleArray& other);

	void 			CopyRoleArray(const LNACLRoleArray &other );
	LNBOOL 			IsModified() { return bModified; }

	HANDLE			AclHandle;
	LNBOOL			bModified;
	WORD 			Count;
	BYTE			RefreshSrc;
	LNString*		Role;
     
};


#endif	//LNACL_HPP

