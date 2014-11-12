/******************************************************************************
 * cetapi.h - Header file for the Entrust/File C Language API.
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.
 *****************************************************************************/

#ifndef CETAPI_H
#define CETAPI_H

#ifdef	MACOS
#ifndef	__FILES__
#include	<files.h>

#endif
#endif

#include <time.h>
#if !defined( ENTAPI )
#include <cetname.h>
#include <cethdr.h>
#include <cetflist.h>
#include <cetcert.h>
#include <entbdefs.h>
#else
#include <toolkit/entapi/cetname.h>
#include <toolkit/entapi/cethdr.h>
#include <toolkit/entapi/cetflist.h>
#include <toolkit/entapi/cetcert.h>
#include <toolkit/entapi/tkbdefs.h>
#endif

/*
   ETEXPORT/ETEXPORT32 modifiers
   -------------------------
   The ETEXPORT and ETEXPORT32 modifiers are defined in ENTBDEFS.H,
   The following table summarizes their values on different platforms.

   Platform        	ETEXPORT             			ETEXPORT32
   --------         ------						--------
   Win16			__export __far __pascal
   Win32			__stdcall					__declspec( dllexport )
   Mac
   Unix
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif


/* Returns the Version string of the Entrust/Engine Library */
ETEXPORT32 const char* ETEXPORT ETQueryEntFileVersion(void);

/*
   Returns the name and absolute path of the profile being used.
   The memory for [value] MUST be allocated by the calling
   application.  [size] is the allocated buffer size.
*/
ETEXPORT32 EntLog ETQueryCurrentProfile( const ETContext ctx, INT32 size, char* value );

/*
   Returns the UINT32 value <valueNumeric> stored in for ProfileOptionID <poid>.
*/
ETEXPORT32 EntLog ETGetProfileOptionInt(const ETContext ctx, const ProfileOptionID poid, UINT32* valueNumeric);

/*
   Set the UINT32 value <valueNumeric> in the ProfileOptionID <poid>.
*/
ETEXPORT32 EntLog ETSetProfileOptionInt(const ETContext ctx, const ProfileOptionID poid, UINT32 valueNumeric);

/*
   Returns the string value <value> for the ProfileOptionID <poid>.
   The memory for [value] MUST be allocated by the calling
   application.  [size] is the allocated buffer size.
*/
ETEXPORT32 EntLog ETGetProfileOptionStr(const ETContext ctx, const ProfileOptionID poid, INT32 size, char* value);

/*
   Set the string value <value> in the ProfileOptionID <poid>.
*/
ETEXPORT32 EntLog ETSetProfileOptionStr(const ETContext ctx, const ProfileOptionID poid, const char* value);

/*
   Returns the name and absolute path of the inifile being used.
   The memory for [value] MUST be allocated by the calling
   application.  [size] is the allocated buffer size.
*/
ETEXPORT32 EntLog ETQueryCurrentIniFile(const ETContext ctx, INT32 size, char* value);

/*
   Logon interface

   This function is used to login to Entrust when a valid user profile
   already exists.
*/
ETEXPORT32 EntLog ETEXPORT ETLogin(	ETContext* ctx,
								const char* userProfile,
								const char* password,
								const char* entrustIniFile);

/*
   Thread Logon interface

   This function is used to login in a new thread ONLY when [thrCtx] has
   been created.  The regular login (ETLogin, ETLoginNoX500Dir) MUST be called first.
   The same thrCtx should not be "logged in" more than once in each thread.
*/
ETEXPORT32 EntLog ETEXPORT ETThreadLogin( ETContext* ctx, ETThreadCtx thrCtx );

/*
	This function will return the ETThreadCtx to be used in other threads.  It is
	one of the input parameters to the above function ETThreadLogin.
*/
ETEXPORT32 EntLog ETEXPORT ETGetThreadLoginContext( ETContext ctx, ETThreadCtx* thrCtx );

/*
   Logon interface (no X.500 directory access)

   This login variant can be used in a full Entrust environment where network
   connectivity to the Entrust network infrastructure is not available
   or not desired. In Lite mode, ETLoginNoX500Dir is equivalent to ETLogin.
*/
ETEXPORT32 EntLog ETEXPORT ETLoginNoX500Dir(ETContext* ctx,
										const char* userProfile,
										const char* password,
										const char* entrustIniFile);
/*
   CreateUser function

   This function is used when creating or restoring an Entrust user.
   Pass in the reference number and one time password
   (supplied by the Entrust/Authority), the initial user password to use,
   the location of the Entrust INI file, and
   a path to the user profile (which will be created).

   For the creating parameter, specify TRUE for creating a user,
   FALSE if restoring an existing user.
   If performing a restore and the specified user profile already exists,
   that profile will be updated with new key information, but retain existing
   option settings.

*/
ETEXPORT32 EntLog ETEXPORT ETCreateUser	(	const INT32 refNum,
										const char* oneTimePassword,
										const char* userPassword,
										const char* entrustIniFile,
					 					const char* userProfile,
					 					BOOL creating);


/* ETCreateUserFromPKCS12 is used when creating an Entrust user 
 from a PKCS #12 message.  The resulting user is an Entrust Solo User.
 The function takes the name of the file to be imported along with the password used to 
 protect that file.  The file name of the profile to be created along with the password for the profile must also be supplied.
*/
ETEXPORT32 EntLog ETEXPORT ETCreateUserFromPKCS12	(const char* importFileName, 
											 const char* importPassword, 
											 const char* profileFileName, 
											 const char* profilePassword,
											 const char* iniFile);




										
/*
   ETLogout frees up the storage associated with the user context.
*/
ETEXPORT32 void ETEXPORT ETLogout(ETContext ctx);

/*
   ETGetLoginInformation provides information about the current login session.
   To use, specify the type of information desired using the loginInfo parameter,
   and provide a pointer to the appropriate data storage in the infoPtr structure.
   For example, to determine if the Toolkit is running in "offline mode" (e.g. cannot
   connect to Entrust/Directory), you would call as follows:
   ETContext ctx;
   ETLogin(&ctx, ...);
   BOOL offlineFlag;
   EntLog rc;
   rc = ETGetLoginInformation(ctx, LG_BOOL_OFFLINE, &offlineFlag);
   For LG_STRING_* enums, use a pointer to a char[MAX_ENTSTR_SIZE] (the string
   data will be copied to the location referenced).
   For LG_INT16_* enums, use a pointer to an INT16.

*/
ETEXPORT32 EntLog ETEXPORT ETGetLoginInformation(	const ETContext ctx,
												const LOGIN_INFO loginInfo,
												void* infoPtr);

/*
   ETGetPolicyCertificateInformation is similar to ETGetLoginInformation 
   except that it provides information about the policy certificate and uses
   the POLICY_CERTIFICATE_INFO enumeration to specify what data and type
   is to be returned.
*/
ETEXPORT32 EntLog ETEXPORT ETGetPolicyCertificateInformation( const ETContext etContext,
												   const POLICY_CERTIFICATE_INFO eInfo,
												   void *pValue);

/*
   ETDirectorySearch will search the specified SearchLocation, based on the
   specified search expression (searchExpr) and search base (searchBaseDN).
   Matching names will be buffered internally in NL_SearchResults
   (see CETNAME.H), and each name will have
   associated attributed information based on the criteria defined in
   attribsToReturn. The searchDepth parameter controls the depth of an X.500
   directory search.
   If searchBaseDN is NULL or points to a zero length string,
   the default X500SearchBase is used.
   The default search base and all available search bases can be
   queried using the ETGetSearchBase() and ETGetSearchBaseName() functions.
   Note that if the client type is CL_LITE, the seachExpr, searchBaseDN,
   attribsToReturn and searchDepth parameters will be ignored, and all names in the
   specified location(s) (i.e. Public Address Book and/or Personal
   Address Book) will be stored in NL_SearchResults.

*/
ETEXPORT32 EntLog ETEXPORT ETDirectorySearch(	const ETContext ctx,
											const char* searchExpr,
											const char* searchBaseDN,
     										const char* attribsToReturn,
	    									SEARCH_LOCATION searchLocation,
	    									SEARCH_DEPTH searchDepth);

#if defined(_WIN32)
/*/
  
   SetCancelDialog receives the window handle for the cancel dialog and cancels a 
   ETDirectorySearch when a button-click event is detected in the dialog.
 */
ETEXPORT32 EntLog ETEXPORT ETSetCancelDialog(const ETContext ctx, HWND handle);
#endif /* _WIN32*/

/*
	
	SetCancel sets the ETDirectorySearch cancel to TRUE/FALSE.  This can be called from a
	seperate thread as ETDirectorySearch is running and will cancel ETDirectorySearch if the 
	parameter is set to TRUE.  The <cancel> parameter must be reset to FALSE following the
	the search.
 */
ETEXPORT32 EntLog ETEXPORT ETSetCancel( const ETContext ctx, BOOL cancel );

/*
   ETGetSearchBase copies the distinguished name of the default X.500 search base,
   (the first entry in list of available search bases) to the searchBaseDN parameter.
   The maximum length of the copied string is MAX_ENTSTR_SIZE.
*/
ETEXPORT32 EntLog ETEXPORT ETGetSearchBase(	const ETContext ctx,
									  	char* searchBaseDN);

/*
   ETGetNumberOfSearchBases returns the number of available search bases,
   or -1 on error.
*/
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfSearchBases  (const ETContext ctx);

/*
   ETGetSearchBaseName returns name information about the search base selected by index
   (which must be from 0 to (ETGetNumberOfSearchBases() - 1).
   searchBaseDN is the indexed search base's distinguished name (which can be used
   in a subsequent call to ETDirectorySearch() ), and
   searchBaseFriendlyName is a more user friendly name assigned by the Entrust
   administrator.
   Both strings are copied to pointers provided by the caller, and the
   maximum length of each copied string is MAX_ENTSTR_SIZE
*/
ETEXPORT32 EntLog ETEXPORT ETGetSearchBaseName(	const ETContext ctx,
											SYSINT index,
											char* searchBaseDN,
											char* searchBaseFriendlyName);

/*
   ETGetAlgorithmAvailability takes an algorithm specifier, and sets the available
   BOOL according to if the algorithm is available or not.
   If available, algDescription will contain a descriptive string. This string
   can be presented to the user during the algorithm selection process.
   The string copied to algDescription will be at most MAX_ENTSTR_SIZE in length.
   If the specified algorithm is not available, algDescription will be a zero length
   string.
*/
ETEXPORT32 EntLog ETEXPORT ETGetAlgorithmAvailability(	const ETContext ctx,
													const ENCRYPTION_ALGORITHM algorithm,
													BOOL* available,
													char* algDescription );

/*
   ETGetSigningAlgorithmAvailability takes a signing algorithm specifier, and sets the available
   BOOL according to if the algorithm is available or not.
   If available, signAlgDescription will contain a descriptive string. This string
   can be presented to the user during the algorithm selection process.
   The string copied to signAlgDescription will be at most MAX_ENTSTR_SIZE in length.
   If the specified algorithm is not available, signAlgDescription will be a zero length
   string.
*/
ETEXPORT32 EntLog ETEXPORT ETGetSigningAlgorithmAvailability(	const ETContext ctx,
													const SIGNING_QUALITY signAlgorithm,
													BOOL* available,
													char* signAlgDescription );
/*
   GetUpperAlgorithmEnum returns the highest symmetric encryption algorithm
   available (from the perspective of the ENCRYPTION_ALGORITHM enum). To determine the
   full range of algorithms available, an application should loop
   from 0 to returned upperAlgorithm, calling ETGetAlgorithmAvailability() for each index.
   Note that there may be gaps in the supported list based on export or administrative
   restrictions on algorithm use - the enum value associated with a particular algorithm
   will always be the same.
*/
ETEXPORT32 EntLog ETEXPORT ETGetUpperAlgorithmEnum(	const ETContext ctx,
												ENCRYPTION_ALGORITHM* upperAlgorithm);


/*
   ETDisconnectDirectory explicitly disconnects the EntFile user context from the
   Entrust/Directory LDAP (Lightweight Directory Access Protocol) daemon.
   Its use is optional and only applies to X.500 mode.
   It is intended for use by applications when they do not require access to
   directory services, in order to reduce the system overhead of maintaining
   an idle LDAP session.
   Any operation which uses directory access (such as ETValidateRecipients and
   ETDirectorySearch) will implicitly re-connect to the LDAP daemon if required.
   Calling ETDisconnectDirectory when there is no LDAP connection in place
   has no effect.
*/
ETEXPORT32 void ETEXPORT ETDisconnectDirectory(const ETContext ctx);

/*
   ETUpdateCertificateCaches is intended to be called if a user is currently online
   but is planning on going offline. It attempts to retrieve and cache encryption
   certificates and associated revocation lists for the names in the specified name list,
   plus those names defined in the available Groups (see the Group Functions definitions
   for more information on groups).
*/
	ETEXPORT32 void ETEXPORT ETUpdateCertificateCaches(
								const ETContext ctx,
								const ListID id );

/*
   Core security operation functions

   StartEncryptWithHeader is used to start an ENCRYPT ONLY operation. The header
   parameter refers to the EntHeader created by CreateHeader after a 
   StartSignEncrypt/SignEncrypt/EndSignEncrypt operation set done with SO_ENCRYPT_ONLY.
   This method will use <header> to start another encrypt only operation set for
   SignEncrypt/EndSignEncrypt.
*/
ETEXPORT32 EntLog ETStartEncryptWithHeader( const ETContext ctx );

/*

   ETStartSignEncrypt is used to start an encrypt and/or sign operation.
   The following variants of ETStartSignEncrypt are supported
   (names preceded by "my" are user variables)
   myEntLog = ETStartSignEncrypt(myContext, SO_ENCRYPT_ONLY,    	myOptions);
   myEntLog = ETStartSignEncrypt(myContext, SO_SIGN_ONLY,		 	myOptions);
   myEntLog = ETStartSignEncrypt(myContext, SO_SIGN_AND_ENCRYPT, 	myOptions);
   Call SetBufferTimestamping(TRUE) if you want to timestamped also.
*/
ETEXPORT32 EntLog ETEXPORT ETStartSignEncrypt(	const ETContext ctx,
										 	SECURITY_OPERATION secOp,
										 	SecurityOptions options);
/*
   Once ETStartSignEncrypt is called, subsequent calls to ETSignEncrypt
   are made to actually process the plaintext data. For example:
   For encrypting or signing and encrypting:
    myEntLog = ETSignEncrypt(myContext, myPlainText, myCipherText);
   For signing only, outBuffer = inBuffer:
    myEntLog = ETSignEncrypt(myContext, myPlainText, myDummyPlainText);
*/
ETEXPORT32 EntLog ETEXPORT ETSignEncrypt(	const ETContext ctx,
										const ETBinData* inBuffer,
										ETBinData*  outBuffer);
/*
   Once all input data has been processed, the operation is completed by a
   call to ETEndSignEncrypt.
   When encrypting or encrypting and signing, the outBuffer will contain
   any residual ciphertext.
   When just signing, the returned outBuffer will be empty. For example:
   For encrypting or signing and encrypting:
    myEntLog = ETEndSignEncrypt(myContext, myResidualCipherText);
   For signing only, returned outBuffer is empty:
    myEntLog = ETEndSignEncrypt(myContext, myDummyBuffer);
   Call CreateTimestampHeader() to get the timestamp header data if the buffer was timestamped.
*/
ETEXPORT32 EntLog ETEXPORT ETEndSignEncrypt(const ETContext ctx,
										ETBinData* outBuffer );

/*
   ETStartDecryptVerify is used to start a decrypt and/or signature
   verification operation.
   NOTE: ETAddHeaderString must be called and provided with the entire header
   (via multiple calls if required) prior to calling ETStartDecryptVerify.

   The actions to take are based on the content of the header passed in.
   If the header indicates that the associated message was signed, the
   certificateData parameter will contain information about the originator.
   Otherwise, certificateData is not modified.
   The headerType parameter will return information about the provided header.
   Note that if headerType is HT_SIGN_ONLY or HT_SIGN_AND_ENCRYPT, the
   verification certificate stored in the header will be copied to the internal
   EntCertificate data storage, and can be accessed via the functions
   defined in CETCERT.H.
   There is only variant of ETStartDecryptVerify
   (names preceded by "my" are user variables)
   myEntLog = ETStartDecryptVerify(myContext, myCertificateData, myHeaderType);
   Call ETSetBufferTimestampVerify(TRUE) and ETSetTimestampResult(timestampheader) before
   calling this function when you want to verify a timestamp header.
*/
ETEXPORT32 EntLog ETEXPORT ETStartDecryptVerify(const ETContext ctx,
											ETCertificateData* certificateData,
											HEADER_TYPE* headerType);

/*
   Once ETStartDecryptVerify is called, subsequent calls to ETDecryptVerify
   are made to actually process the signed/encrypted data. For example:
   For signed only data, outBuffer = inBuffer
   	myEntLog = ETDecryptVerify(myContext, mySignedData, myDummyText);
   For encrypted, and possibly signed, data:
   	myEntLog = ETDecryptVerify(myContext, myCipherText, myPlainText);
*/
ETEXPORT32 EntLog ETEXPORT ETDecryptVerify(	const ETContext ctx,
										const ETBinData* inBuffer,
										ETBinData* outBuffer);
/*
   Once all input data has been processed, the operation is completed by a
   call to ETEndDecryptVerify.
   When decrypting or decrypting and verifying, the outBuffer will contain
   any residual plaintext.
   When just verifying a signature, the outBuffer is unchanged. For example:
   For decrypting or verifying and decrypting:
    myEntLog = ETEndDecryptVerify(myContext, myResidualPlainText);
   For verifying only, outBuffer is unchanged:
	myEntLog = ETEndDecryptVerify(myContext, myDummyBuffer);
   Call ETGetTimestampResult() to determine the timestamp verification results (if the buffer
   was timestamped originally)
*/
ETEXPORT32 EntLog ETEXPORT ETEndDecryptVerify(	const ETContext ctx,
											ETBinData* out );

/*
 * Stand alone virus detection support
 */
/*
 * This method takes a file name, a set of options and a reference to a VirusDetectInfo structure.
 * The file denoted by <filename> will be scanned for viruses according to the settings in <op>.  The
 * results will be returned in <output>.
 */
ETEXPORT32 EntLog ETScanFileForVirus( const ETContext ctx,
								    ETFileSpecification filename,	/* In file name */
								    VirusDetectOptions op,			/* In options */
								    VirusDetectInfo* output);		/* out info */
/*
   Timestamp support
*/

/* Start a buffer based timestamp only operation - no sign or encrypt, just timestamp */
ETEXPORT32 EntLog ETEXPORT ETStartTimestamp(const ETContext ctx);

/* Once ETStartTimestamp() is called, subsequent calls to ETTimestamp() are made
   to process the plaintext data. */

ETEXPORT32 EntLog ETEXPORT ETTimestamp(const ETContext ctx, const ETBinData* in);

/*
   Once all input data has been processed, the operation is completed by a
   call to ETEndTimestamp(). Call ETCreateTimestampHeader() to get the timestamp header data */

ETEXPORT32 EntLog ETEXPORT ETEndTimestamp(const ETContext ctx);

/*
   ETStartDecryptVerify() is used to start a timestamp only verification
   operation.  The timestamp header to verify is passed in. */

ETEXPORT32 EntLog ETEXPORT ETStartVerifyTimestamp(const ETContext ctx, const ETBinData *timestampHeader);

/* Once ETStartVerifyTimestamp() is called, subsequent calls to ETVerifyTimestamp()
   are made to actually process the signed/encrypted data. For example: */

ETEXPORT32 EntLog ETEXPORT ETVerifyTimestamp(const ETContext ctx, const ETBinData* in);

/* Once all input data has been processed, the operation is completed by a call
   to ETEndVerifyTimestamp().  A call to
   Call ETGetTimestampResult() to determine the timestamp verification results. */

ETEXPORT32 EntLog ETEXPORT ETEndVerifyTimestamp(const ETContext ctx);

/* Shared timestamp support functions */
/* Get the timestamp header data as a result of timestamping a buffer based operation of the stand-alone
   timestamp operation. */

ETEXPORT32 EntLog ETEXPORT ETCreateTimestampHeader(const ETContext ctx, ETBinData* timestampHeader);

/* Set the timestamp header to verify. Call before ETStartDecryptVerify() */

ETEXPORT32 EntLog ETEXPORT ETSetTimestampResult(const ETContext ctx, const ETBinData* timestampHeader);

/* Enable timestamping mode, TRUE = timestamp, FALSE = no timestamp.
   Call before StartEncryptSign(). */

ETEXPORT32 void ETEXPORT ETSetBufferTimestamping(const ETContext ctx, const BOOL TimestampFlag);
ETEXPORT32 BOOL ETEXPORT ETQueryBufferTimestamping(const ETContext ctx);

/* Enable timestamp verification, TRUE = verify, FALSE = no verification.
   Call before StartDecryptVerify(). */

ETEXPORT32 void ETEXPORT ETSetBufferTimestampVerify(const ETContext ctx, const BOOL TimestampVerifyFlag);
ETEXPORT32 BOOL ETEXPORT ETQueryBufferTimestampVerify(const ETContext ctx);

/*
   ETValidateRecipients will move any recipients from NL_Recipients
   (see CETNAME.H) that do not have certificates
   to the NL_Invalid list. This function can be used to determine, prior
    to calling ETCreateHeader, which recipients do not have valid certificates.
*/
ETEXPORT32 EntLog ETEXPORT ETValidateRecipients(const ETContext ctx);
/*
   ETValidateNameList is a more general form of ETValidateRecipients, which
   can be used to validate any of the available name lists (see ListID in
   CETNAME.H), EXCEPT for NL_Invalid, which is used as the destination
   for any names which do not have valid public key certificates.
*/
ETEXPORT32 EntLog ETEXPORT ETValidateNameList( const ETContext ctx, ListID id);
/*
   ETCreateHeader will move any recipients that do not have certificates
   from NL_Recipients to NL_Invalid (via an internal call to
   ETValidateRecipients). It will then generate a PEM-style header.
   (See CETHDR.H).
   NOTE: if the data being secured is SIGNED ONLY, the NL_Recipients list
   must be empty before calling this function (recipients are only specified
   for encryption operations).

*/
ETEXPORT32 EntLog ETEXPORT ETCreateHeader( const ETContext ctx );

/* ETCreateMinimalHeader is similar to ETCreateHeader (above), with the
   following differences based on the security operation performed:
   if signed, the user's verification certificate is not included in the
   header. If encrypted, the user's encryption certificate is not included.
*/
ETEXPORT32 EntLog ETEXPORT ETCreateMinimalHeader( const ETContext ctx );

/*
   Personal Address Book functions
*/
/*
   HavePAB determines the existance of a user's Personal Address Book.
   NOTE: Return code of 0 means a PAB exists.
*/
ETEXPORT32 EntLog ETEXPORT ETHavePAB(const ETContext ctx);
/*

   ETCreatePAB creates an (initially empty) Personal Address Book.
   As of v2.0, the PAB file name will be the user profile name,
   minus the ".epf" extension, if present, and appended with
   a ".pab" extension, So a user with profile name entuser.epf will
   have a Personal Address Book file named entuser.pab,
   in the same directory as the profile.

*/
ETEXPORT32 EntLog ETEXPORT ETCreatePAB(const ETContext ctx, const char* ignoredValue);

/*
   ETEditPABEntry will search the list of names loaded by the last call to
   ETDirectorySearch for an entry whose unique name matches [uniqueName] .
   It will replace the value of the attribute specified by [attr] with
   [newValue].
   If the list is empty, ENM_NAME_NOT_FOUND will be returned.
*/
ETEXPORT32 EntLog ETEditPABEntry( const ETContext ctx,
							  const char* uniqueName,
							  const char* newValue,
							  const char* attr );
/*
   GetAddressVerificationString searches the PAB for an entry
   matching uniqueName, and returns an Address Verification String
   in authString. The maximum length of the copied string is MAX_AUTHSTR_SIZE.

*/
ETEXPORT32 EntLog ETEXPORT ETGetAddressVerificationString(	const ETContext ctx,
														const char* uniqueName,
														char* authString);
/*
   DeleteAddressFromPAB deletes the entry matching uniqueName from the
   Personal Address Book
*/
ETEXPORT32 EntLog ETEXPORT ETDeleteAddressFromPAB(	const ETContext ctx,
												const char* uniqueName);
/*
   ETImportCertificate takes an import fileName, adds the user and certificate
   information from it to the PAB, and returns the uniqueName of the
   user whose certificates were imported. The string copied to uniqueName
   will be at most MAX_NAME_SIZE in length.
   The import certificate file will typically have been generated by another
   user calling the ETExportMyCertificate() function.
*/
ETEXPORT32 EntLog ETEXPORT ETImportCertificate(	const ETContext ctx,
											const char* fileName,
											char* uniqueName);

/* Make a new PAB entry based on the internal stored certificate list.
   The name of the person or entity whose certificates were imported is returned via the
   uniqueName parameter.
   See the certificate list definitions in CETCERT.H for more information. */
ETEXPORT32 EntLog ETEXPORT ETImportCertificateList(	const ETContext ctx,
												char* uniqueName);
/*
   ETExportMyCertificate exports the current user's public key certificates
   to the indicated file, and copies the address verification string to
   authString. The maximum length of the copied string is MAX_AUTHSTR_SIZE.
   Note that the current user must have a valid PAB in order to
   export their certificates.
*/
ETEXPORT32 EntLog ETEXPORT ETExportMyCertificate(	const ETContext ctx,
												const char* fileName,
												char* authString);


/* ETExportCertificateListPKCS12 exports the current user's public key certificates 
and keys specified in the internal Certificate List to the indicated file.
The user is required to re-authenticate using the profile password.  The 
certificats and corresponding keys will be protected with keys generated using 
the exportPassword and hashCount.  The user should use the default hashCount 
unless they have reason not to.*/
ETEXPORT32 EntLog ETEXPORT ETExportCertificateListPKCS12(const ETContext ctx,
							  const char *userPassword, 
							  const char*outputFileName, 
							  const char *exportPassword, 
							  UINT32 hashCount);

/*ETGetPKCS12ExportableCertificates sets the internal Certificate List in preperation for exporting a PKCS #12 message. Certificates can
be removed from the certificate list in the normal fashion.*/
ETEXPORT32 EntLog ETEXPORT ETGetPKCS12ExportableCertificates(const ETContext ctx);

ETEXPORT32 EntLog ETEXPORT ETShowAddrBook(const ETContext ctx,
                                const char *    profile,
                                const char *    ERAName,
                                AB_CmdMsgId msg_id,
                                ListID          rl_ID,
                                ArchiveOptions *opts_ID );
/*
   Information
*/
/*
   ETQueryConnectStatus returns TRUE if the user is connected to the directory, FALSE otherwise.
*/
ETEXPORT32 BOOL ETEXPORT ETQueryConnectStatus(const ETContext ctx);

/*
   Check whether timestamping is available
   (checks to see if there are any timestamp servers defined)
*/
ETEXPORT32 BOOL ETEXPORT ETQueryTimestampAvailable(const ETContext ctx);

/*
   Disable the built-in inactivity timeout.
   Call with a 'TRUE' parameter to disable.
   Call with a 'FALSE' parameter to re-enable.
*/
ETEXPORT32 EntLog ETEXPORT ETDisableTimeout(const ETContext ctx, BOOL disable);


/*
   Indicates if the user has as a DSA signing key.
*/
ETEXPORT32 EntLog ETEXPORT ETIsDSAUser(const ETContext ctx, BOOL* DSAUser);

/*
   Indicates if the user has as a Elliptic Curve DSA signing key.
*/
ETEXPORT32 EntLog ETEXPORT ETIsECDSAUser(const ETContext ctx, BOOL* DSAUser);


/*
   Indicates if the user is logged on through single sign-on.
*/
ETEXPORT32 EntLog ETEXPORT ETIsLoggedIn(const ETContext ctx, BOOL* loggedIn);

/*
   ETGetUserInfo retrieves information about the current Entrust user.
   The user's unique name and common name attribute "cn" are returned
   in the first entry of the NL_SearchResults name list (see CETNAME.H).
   The Certification Authority name is copied to CAName, which will be
   at most MAX_NAME_SIZE in length.
   The userAttributes argument is no longer used, and can be set to
   an empty string "";
*/
ETEXPORT32 EntLog ETEXPORT ETGetUserInfo(	const ETContext ctx,
										const char* userAttributes,
										char* CAName);
/*
   ETGetUserBasicInfo retrieves basic information about the
   current Entrust user, specifically, the user's unique name and the name
   of the user's Certification Authority are copied to the storage pointed
   to by the supplied pointers. Each string will be at most
   MAX_NAME_SIZE in length.
*/
ETEXPORT32 EntLog ETEXPORT ETGetUserBasicInfo(	const ETContext ctx,
											char* userName,
											char* CAName);
/*
   ETGetUserEncryptionCertificate returns a reference to the
   encryption certificate of the current user, and stores it in an internal
   EntCertificate data structure (accessed via the functions defined in CETCERT.H).
*/
ETEXPORT32 EntLog ETEXPORT ETGetUserEncryptionCertificate(	const ETContext ctx,
														ETBinData32* certificate);
/*
   ETGetUserVerificationCertificate returns a reference to the
   verification certificate of the current user, and stores it in an internal
   EntCertificate data structure (accessed via the functions defined in CETCERT.H).
*/
ETEXPORT32 EntLog ETEXPORT ETGetUserVerificationCertificate(const ETContext ctx,
														ETBinData32* certificate);
/*
   ETGetIssuerVerificationCertificate returns returns a reference to the
   the verification certificate of the issuer (Certification Authority)
   of the current user's certificates. It also stores it in an internal
   EntCertificate data structure (accessed via the functions defined in CETCERT.H).
*/
ETEXPORT32 EntLog ETEXPORT ETGetIssuerVerificationCertificate(const ETContext ctx,
														ETBinData32* certificate);

/*
   ETGetTimestampServerVerificationCertificate returns a reference to the
   verification certificate of the timestamp server, and stores it in an internal
   EntCertificate data structure (accessed via the functions defined in CETCERT.H).
*/

ETEXPORT32 EntLog ETEXPORT ETGetTimestampServerVerificationCertificate(const ETContext ctx,
														ETBinData32* certificate);

/*
   ETGetTimestampServerIssuerVerificationCertificate returns returns a reference to the
   the verification certificate of the issuer (Certification Authority)
   of the timestamp server's certificates. It also stores it in an internal
   EntCertificate data structure (accessed via the functions defined in CETCERT.H).
*/
ETEXPORT32 EntLog ETEXPORT ETGetTimestampServerIssuerVerificationCertificate(const ETContext ctx,
														ETBinData32* certificate);

/*
  	GetSecurityOptions returns the currently enabled security options
  	(set via a call to StartSignEncrypt).
*/
ETEXPORT32 SecurityOptions ETEXPORT ETGetSecurityOptions(const ETContext ctx);
/*
   Setting and Querying Additional Options

   These functions allow setting and querying of additional options
   for buffer based security operations.
   Options are applied at the start of a security operation, such as
   ETStartSignEncrypt() (for the ASCII encoding options)
   and ETStartDecryptVerify() (for the ASCII decoding options).
   Options set via these functions will apply for the duration of the user
   login context.
   These options are in addition to those explicitly set using the structures
   FileSecureOptions, FileUnsecureOptions, and SecurityOptions.
*/
	/* These functions apply to ASCII encoding of data for buffer based
	   signing and/or encrypting of data. The default is no ASCII encoding. */
	ETEXPORT32 void ETEXPORT ETSetBufferASCIIencoding(const ETContext ctx, BOOL ASCIIencodingOn);
	ETEXPORT32 BOOL ETEXPORT ETQueryBufferASCIIencoding(const ETContext ctx);

	/* These functions apply to decoding of ASCII encoded data for buffer based
	   decryption and/or verification of data. The default is no ASCII decoding. */
	ETEXPORT32 void ETEXPORT ETSetBufferASCIIdecoding(const ETContext ctx, BOOL ASCIIdecodingOn);
	ETEXPORT32 BOOL ETEXPORT ETQueryBufferASCIIdecoding(const ETContext ctx);

/*
   Password functions
*/
/*
   ETValidatePassword returns 0 if the supplied password matches that
   of the current user.
*/
ETEXPORT32 EntLog ETEXPORT ETValidatePassword(	const ETContext ctx,
											const char* ExistingPassword );

/*
   ETChangePassword validates the supplied oldPassword, and if valid,
   changes the user password to newPassword.

   With Single Login, call the version of this function that takes no parameters.
   ELI (the Entrust Login Interface) will take over from there.

*/
ETEXPORT32 EntLog ETEXPORT ETChangePassword(const ETContext ctx,
									 	const char* oldPassword,
									 	const char* newPassword );

/*
   If using Single Login, use this version of ChangePassword to bring up the user interface.
*/
ETEXPORT32 EntLog ETEXPORT ETChangePasswordUI(const ETContext ctx);	

/*
   ETCheckPassword checks the provided string against the password rules.
   Note that this does not check if the provided string is the password of the
   current user - use ETValidatePassword() for that.
*/
ETEXPORT32 EntLog ETEXPORT ETCheckPassword(const ETContext ctx, const char* newPass);

/*
   Return set of password rules that apply to current user
   The application owns the storage for the EntrustPassRules structure.
*/
ETEXPORT32 EntLog ETEXPORT ETGetPasswordRules(const ETContext ctx, EntrustPassRules* rules);


/*
   Entrust Archive Functions

   These functions are similar to the file secure/unsecure functions above,
   except they can be used to generate and process Entrust archive files, which
   contain secured versions of one or more plaintext files.

   Compatibility between archive and file functions:
   - Using the file secure functions ETSetFileSignEncrypt()/ETDoFileSignEncrypt() is
     equivalent to using ETSetArchiveSignEncrypt()/ETDoArchiveSignEncrypt() on an
     input file list with one entry.
   - Using the file unsecure functions
     ETGetFileInfo()/ETSetFileDecryptVerify()/ETDoFileDecryptVerify() is equivalent
     to using ETLoadArchive()/ETGetArchiveInfo()/
     ETSetArchiveDecryptVerify()/ETDoArchiveDecryptVerify() on an
     Entrust archive with one encapsulated file. If the single file functions are used
     on an Entrust archive encapsulating multiple files, only the first encapsulated
     file will be processed.

    In general it is recommended to use the archive functions. The single file
    processing functions are retained for convenience and backwards compatibility.

   ETSetArchiveSignEncrypt and ETDoArchiveSignEncrypt will digitally sign and/or encrypt
   an input file list and generate a single secured output file which is compatible
   with the Entrust/Client file format.

   The input file list is prepared using the functions defined in CETFLIST.H.

   If the files are to be encrypted, the recipients list should contain the list
   of intended recipients before this function is called. Recipients who do not
   have valid certificates will be moved to the NL_Invalid name list.

   The secOp, and fileOptions parameters provided will be applied
   to each plaintext file in inputFileList, and outputFile is the specification
   for the output archive file.

   NOTE: archiveOptions.fileOptions.deletePlaintextAfter is treated as FALSE,
   even if set to TRUE, to avoid accidental destruction of input files. Use
   the SecureDeleteFile() function to remove undesired files after the archive
   has been generated.

*/

ETEXPORT32 EntLog ETEXPORT ETSetArchiveSignEncrypt(
										const ETContext ctx,
										const ArchiveOptions* archiveOptions,
										const ETFileSpecification outputFile,
										ListID recipients );

/*
   ETDoArchiveSignEncrypt, if the proceed flag is FALSE, will cancel processing of the
   file operation(s) specified by the previous call to ETSetArchiveSignEncrypt.
   If proceed is TRUE, then a portion of the current input file
   will be processed, and a status EntLog will be returned.
   Parameter currentFileIndex is used to indicate which file (of an input file
   list) is currently being processed.
   The percentOfFileDone return parameter indicates what percentage of the current file
   has been processed so far.
   Parameter totalPercentDone is used to indicate how much of the total job
   (processing all input files) has been completed.
*/

ETEXPORT32 EntLog ETEXPORT ETDoArchiveSignEncrypt (
											const ETContext ctx,
											const BOOL proceed,
											INT16* currentFileIndex,
											INT16* percentOfFileDone,
											INT16* totalPercentDone );

/*
   ETLoadArchive specifies an existing Entrust archive file to process.
   Parameter archiveFile specifies the input Entrust archive file, and
   numberOfFilesInArchive returns the number of files encapsulated in the
   archive.
*/
ETEXPORT32 EntLog ETEXPORT ETLoadArchive (	const ETContext ctx,
										const ETFileSpecification archiveFile,
										INT16* numberOfFilesInArchive );

/*
   ETGetArchiveInfo returns information about a secured file
   encapsulated in an Entrust archive. It returns:
   - the name of the encapsulated file, converted if necessary to
     match the file naming conventions of the local operating system.
   - the byte length of the encapsulated file.
   The input parameter suppressPathInfo, if TRUE, will cause any
   path information which may be present in the fileName to be
   stripped off.
*/
ETEXPORT32 EntLog ETEXPORT ETGetArchiveInfo (	const ETContext ctx,
											const SYSINT index,
											ETFileSpecification fileName,
											INT32* fileLength,
											BOOL suppressPathInfo);

/*
   ETSetArchiveInfo allows you to prevent a specified encapsulated file
   from being extracted from the archive when it is processed. By default,
   all files in the archive will be processed.
*/
ETEXPORT32 EntLog ETEXPORT ETSetArchiveInfo (	const ETContext ctx,
											const SYSINT index,
									   		const BOOL excludeThisFile );
/*
   ETSetArchiveDecryptVerify begins the process of extracting the encapsulated
   files from the archive, and should be followed by multiple calls to
   ETDoArchiveSignEncrypt.
   writeOutput specifies if the output files should be written.
   outputDir specifies a destination directory for the output files.
   usePathInfo, if TRUE, will cause output files to be written using the
   path information (if any) stored with them, relative to outputDir.
   If usePathInfo is FALSE, all output files will be written to outputDir.
   overwriteFiles determines if output files will be written over
   existing files of the same name in the destination directory.
   numFilesToProcess returns the number of encapsulated files which will
   be processed.
   The saveVerificationCertificates flag, if TRUE, will save the
   verification certificates of any encapsulated files which are signed,
   so that they can be retrieved during a subsequent call to GetArchiveResults().
*/

ETEXPORT32 EntLog ETEXPORT ETSetArchiveDecryptVerify (
											const ETContext ctx,
											const BOOL writeOutput,
											const ETFileSpecification outputDir,
											const BOOL usePathInfo,
											const BOOL overwriteFiles,
											const BOOL saveVerificationCertificates,
											INT16* numFilesToProcess);


/*
   ETDoArchiveDecryptVerify performs the actual processing (decrypting/verifying) of
   the subset of encapsulated files within an archive selected during previous
   calls to ETLoadArchive and ETSetArchiveInfo.
   If the proceed flag is FALSE, it will cancel processing of the archive.
   If proceed is TRUE, then a portion of one of the encapsulated files
   will be processed, and a status EntLog will be returned.
   Parameter currentFileIndex is used to indicate which of the selected
   encapsulated files is currently being processed.
   The percentOfFileDone return parameter indicates what percentage of the current
   encapsulated file has been processed so far.
   Parameter totalPercentDone is used to indicate how much of the total job
   (processing of all selected encapsulated files) has been completed.
*/
ETEXPORT32 EntLog ETEXPORT ETDoArchiveDecryptVerify (
											const ETContext ctx,
											const BOOL proceed,
											INT16* currentFileIndex,
											INT16* percentOfFileDone,
											INT16* totalPercentDone );
/*
   ETGetArchiveResults returns information about a secured file
   which was extracted from an Entrust archive.
   It should be called after ETDoArchiveDecryptVerify() returns a
   completion indication.
   If the encapsulated file was signed, and the saveVerificationCertificates
   flag was set TRUE in the previous call to SetArchiveDecryptVerify(),
   the signature verification public key certificate of the originator
   will be saved internally and can be accessed via the functions
   defined in CETCERT.H.
   This function returns:
   - the name of the encapsulated file, converted if necessary to
     match the file naming conventions of the local operating system.
   - the headerType indicating if and how the file was secured,
   - information about the signer of the file (if applicable)
   - status of the decrypt and/or verification operations performed
     on the encapsulated file, including the operating system
     where the archive was created.
*/
ETEXPORT32 EntLog ETEXPORT ETGetArchiveResults (const ETContext ctx,
											const SYSINT index,
											ETFileSpecification fileName,
											HEADER_TYPE* headerType,
											ETCertificateData* certifData,
											DecryptVerifyStatus* status);
/*
   ETGetAllArchiveResults returns information about a secured file
   which was extracted from an Entrust archive.
   It is similar to ETGetArchiveResults(), but returns an ARCHIVE_INFO struct
   instead of HEADER_TYPE.
*/
ETEXPORT32 EntLog ETEXPORT ETGetAllArchiveResults(	const ETContext ctx,
												const SYSINT index,
												ETFileSpecification fileName,
												ARCHIVE_INFO* archiveInfo,
												ETCertificateData* certifData,
												DecryptVerifyStatus* status );
/*
   ETGetArchiveEncryptInfo returns information on how an entrust archive
   was encrypted and/or signed, whether or not the file was timestamped
   and certificate information.  If the file was signed, the signature
   verification public key certificate of the originator will be saved
   internally and can be accessed via the functions defined in CETCERT.H
   If the archive was timestamped, timestamp information can be returned
   by ETGetArchiveTimestampInfo.
 */
ETEXPORT32 EntLog ETEXPORT ETGetArchiveEncryptInfo( const ETContext ctx,
												ETFileSpecification inputFile,
				 			   					ARCHIVE_INFO *archiveInfo,
												ETCertificateData* certifData,
												BOOL* timestamped);
/*
   ETGetArchiveTimestampInfo returns information about a secured file
   which was extracted from an Entrust archive.
   It should be called after ETDoArchiveDecryptVerify() returns a
   completion indication.
   If the encapsulated file was signed, and the saveVerificationCertificates
   flag was set TRUE in the previous call to SetArchiveDecryptVerify(),
   the signature verification public key certificate of the originator,
   the timestamp server and timestamp server CA will be saved internally
   and can be accessed via the functions defined in CETCERT.H.
   This function returns:
   - the name of the encapsulated file, converted if necessary to
     match the file naming conventions of the local operating system.
   - the headerType indicating if and how the file was secured,
   - information about the signer of the file (if applicable)
   - status of the decrypt and/or verification operations performed
     on the encapsulated file, including the operating system
     where the archive was created.
*/
ETEXPORT32 EntLog ETEXPORT ETGetArchiveTimestampResult(const ETContext		ctx,
												 const SYSINT			index,
												 char*					serialNumber,
												 time_t*				date,
												 TIMESTAMP_HASH_ALG*	hashAlg,
												 EntLog*				status);

/* Buffer based timestamp result - similiar to Archive above */
ETEXPORT32 EntLog ETEXPORT ETGetTimestampResult(const ETContext		ctx,
											char*				serialNumber,
											time_t*				date,
											TIMESTAMP_HASH_ALG*	hashAlg,
											EntLog*				status);
/*
  
   Stand alone virus detection support
    
  
   Retrieve the VirusDetectInfo structure for the file at index <index>.  The method
   "ScanFilesforVirus" must be called first.  Otherwise, an error will be returned.
*/
ETEXPORT32 EntLog  ETGetVirusInfo( const ETContext ctx, int index, VirusDetectInfo* output);

/*
   This method takes a list of file names and a set of options.  Each of the files in
   the list will be scanned for viruses according to the options in the <op> parameter.
   Use "GetVirusInfo" above to retrieve data in each file.
   The <moveToDir> is used only if the op parameter is set to "MOVE_INFECTED_FILES", 
   then moveToDir should be set to the destination directory.  Otherwise, it is ignored.
*/
ETEXPORT32 EntLog  ETScanFilesForVirus( const ETContext ctx,
									  VirusDetectOptions op,			/*  In options */
									  ETFileSpecification moveToDir);	/* In file name */			

/*
   This method sets the VirusDetectOption for the decryption methods that automatically do 
   virus scanning.  It's setting will NOT be used by the above two methods.  It's default
   setting is: DO_NOTHING.
   If the [op] parameter is set to "MOVE_INFECTED_FILES", then moveToDir should be set to the 
   destination directory.  Otherwise, it is ignored.
 */
ETEXPORT32 EntLog ETSetVirusOp(const ETContext ctx, VirusDetectOptions op, ETFileSpecification moveToDir );

/*
   SLL signing methods.
   ====================
   ETSSL_StartSign takes no parameters. It is used to start a SSL signing operation.
*/
ETEXPORT32 EntLog ETSSL_StartSign( const ETContext ctx );

/*
   ETSSL_UpdateSign accepts four BinData parameters.
   - sha_inBuffer:
   - md_inBuffer:
   - sha_outBuffer:
   - md_outBuffer:
*/
ETEXPORT32 EntLog ETSSL_UpdateSign( const ETContext ctx,
							    const ETBinData32* sha_inBuffer,
							    const ETBinData32* md_inBuffer );

/*
   ETSSL_EndSign accepts three parameters:
   - sha_inBuffer:
   - md_inBuffer:
   - outBuffer:
*/
ETEXPORT32 EntLog ETSSL_EndSign( const ETContext ctx,
							 ETBinData32* outBuffer );

/*
   SSL Verification methods.
   =========================
   ETSSL_StartVerify is used to start off the Verification procedure
   for a SSL signed message.  The verification certificate must be
   loaded into [ctx] using "ETLoadCertificate" before calling this
   function is used to verify the signature in the [inSig] parameter.
 */
ETEXPORT32 EntLog ETSSL_StartVerify( const ETContext ctx,
								 const ETBinData32* inSig );

/*
   ETSSL_UpdateVerify accepts four BinData parameters.
   - sha_inBuffer:
   - md_inBuffer:
   - sha_outBuffer:
   - md_outBuffer:
*/
ETEXPORT32 EntLog ETSSL_UpdateVerify( const ETContext ctx,
								  const ETBinData32* sha_inBuffer,
								  const ETBinData32* md_inBuffer );

/*
   ETSSL_EndVerify accepts three parameters:
   - sha_inBuffer:
   - md_inBuffer:
   - alg:
*/
ETEXPORT32 EntLog ETSSL_EndVerify( const ETContext ctx,
							   EntSSL_Alg* alg );

/*
   Group Key Functions
   ===================
  
   importProtectedGroupKeys - takes a protected group key file (generated by the
   exportProtectedGroupKeys function), and, if the current user was on the recipient
   list for the export, adds the decryption keys to the current user's group key list.
   The friendly name for the group will be returned via the groupName parameter, and
   the distinguished name (DN) is also provided via the groupDN parameter.
   The encryption certificate corresponding to the most recent decryption key is returned
   for informational purposes.
   <groupName> and <groupDN> should be of size MAX_NAME_SIZE!
*/
ETEXPORT32 EntLog ETImportProtectedGroupKeys( const ETContext ctx,
										    const char* fileName,
											char* groupName,
											char* groupDN,
	  										ETBinData32* matchingCert);

/*
   deleteGroupKeys - delete the decryption keys, associated with a group (specified
   by friendly name) from the user's group key list.
*/
ETEXPORT32 EntLog ETDeleteGroupKeys(const ETContext ctx, const char* groupName);

/*
   getNumberOfGroupKeySets - The number of groups for which the current user has group keys.
   They are referred to as group key "sets" since a given group may have more than 1
   key associated with it.
*/
ETEXPORT32 INT32 ETGetNumberOfGroupKeySets(const ETContext ctx);

/*
   getGroupKeyInfo - This function returns the friendly and distinguished names of
   the specified group with which a group key is associated. 
   The number of keys associated with a specified group is also returned (since
   due to key updates, there may be more than one decryption key associated with
   a specific group).
   <groupName> and <groupDN> should be of size MAX_NAME_SIZE!
*/
ETEXPORT32 EntLog ETGetGroupKeyInfo( const ETContext ctx,
								   INT32 index,
								   char* groupName,
								   char* groupDN,
								   INT32*	numKeysForGroup);


/* File Based Functions
   ====================
   ETSetFileSignEncrypt and ETDoFileSignEncrypt will digitally sign and/or encrypt
   an input file and generate a secured output file which is compatible with the
   Entrust/Client file format.
   If the file is to be encrypted, the NL_Recipients list should contain the list
   of intended recipients before this function is called. Recipients who do not
   have valid certificates will be moved to the NL_Invalid list (see CETNAME.H).
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** USE THE ARCHIVE FUNCTIONS INSTEAD (ETSetArchiveSignEncrypt)
*/
ETEXPORT32 EntLog ETEXPORT ETSetFileSignEncrypt(const ETContext ctx,
											const SECURITY_OPERATION secOp,
  											const FileSecureOptions* fileOptions,
  											const ETFileSpecification inputFile,
  											const ETFileSpecification outputFile);

/*
   ETDoFileSignEncrypt, if the proceed flag is FALSE, will cancel processing of the
   file operation specified by the previous call to ETSetFileSignEncrypt.
   If proceed is TRUE, then a portion of the input file
   will be processed, and a status EntLog will be returned.
   The percentDone return parameter indicates what percentage of the file has been
   processed so far.
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** USE THE ARCHIVE FUNCTIONS INSTEAD (ETDoArchiveSignEncrypt)
*/
ETEXPORT32 EntLog ETEXPORT ETDoFileSignEncrypt (const ETContext ctx,
											const BOOL proceed,
											INT16* percentDone );

/*
   ETGetFileInfo returns information about an Entrust secured file. It returns:
   - the headerType indicating if and how the file was secured,
   - information about the signer of the file (if applicable)
   - the "native" name of the source file which was secured,
   - a "local" version of the source file name, which is a converted
     version of the native file name, intended to
     help resolve cases where the source and destination systems
     have different file naming conventions,
   - the type of operating system where the file was generated
   Note that the information provided by certificateData for a signed file should
   not be trusted until the file's signature has been successfully verified
   using ETSetFileDecryptVerify() and ETDoFileDecryptVerify().
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** USE THE ARCHIVE FUNCTIONS INSTEAD (ETGetArchiveInfo)
*/

ETEXPORT32 EntLog ETEXPORT ETGetFileInfo (	const ETContext ctx,
										const ETFileSpecification inputFile,
										HEADER_TYPE* headerType,
										ETCertificateData* certificateData,
										ETFileSpecification nativeFileName,
										ETFileSpecification localFileName,
										SOURCE_OS* sourceOperatingSystem );

/*
   ETSetFileDecryptVerify and ETDoFileDecryptVerify will take an Entrust/Client
   compatible secured file, decrypt and verify it (if the current user is
   authorized to do so), and write it to the file specified by outputFile.
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** USE THE ARCHIVE FUNCTIONS INSTEAD (ETLoadArchive, ETSetArchiveDecryptVerify)
*/
ETEXPORT32 EntLog ETEXPORT ETSetFileDecryptVerify(	const ETContext ctx,
												const FileUnSecureOptions* fileOptions,
												const ETFileSpecification inputFile,
												const ETFileSpecification outputFile);
/*
   ETDoFileDecryptVerify, if the proceed flag is FALSE, will cancel processing of the
   file operation specified by the previous call to ETSetFileDecryptVerify.
   If proceed is TRUE, then a portion of the input file
   will be processed, and a status EntLog will be returned.
   The percentDone return parameter indicates what percentage of the file has been
   processed so far.
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** USE THE ARCHIVE FUNCTIONS INSTEAD (ETDoArchiveDecryptVerify, ETGetArchiveResults)
*/
ETEXPORT32 EntLog ETEXPORT ETDoFileDecryptVerify ( 	const ETContext ctx,
												const BOOL proceed,
												INT16* percentDone );
/*
   ETSecureDeleteFile securely erases the specified file by overwriting it with
   random encrypted data.
   NOTE: this function is not available on Macintosh.
*/
#if !defined(MACOS)
ETEXPORT32 EntLog ETEXPORT ETSecureDeleteFile (	const ETContext ctx,
											const ETFileSpecification inputFile );
#endif

/*
   Group Functions

   Groups provide a shorthand way to refer to a set of recipients. The Toolkit
   provides access to the groups defined by the Entrust/Client.
   The user context has a list of zero of more groups, each of which has a
   list of zero or more members, with each member represented by a unique name.
*/
/*
   ETGetNumberOfGroups returns the current number of groups defined.
*/
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfGroups( const ETContext ctx );
/*
   ETGetGroupName gets the name of the indexed group. Group names can be
   a maximum of MAX_GROUP_NAME_SIZE characters long (defined in ENTBDEFS.H).
   The name is copied to the storage pointed to by groupName.
*/
ETEXPORT32 EntLog ETEXPORT ETGetGroupName( 	const ETContext ctx,
										const SYSINT groupIndex,
										char* groupName );
/*
   ETGetGroupIndex gets the index of the named group.
*/
ETEXPORT32 EntLog ETEXPORT ETGetGroupIndex(	const ETContext ctx,
										const char* groupName,
										SYSINT* groupIndex );
/*
   ETGetGroup gets the members of the named group and appends them to the
   specified name list.
   The groupOptions parameter indicates if the group is shared or not.

*/
ETEXPORT32 EntLog ETEXPORT ETGetGroup(	const ETContext ctx,
									const char* groupName,
									const ListID id,
									GroupOptions* groupOptions);
/*
   ETAddGroup saves the indicated name list as a group in the
   internally maintained group list.
   If a non-shared group with the the specified name already exists,
   its contents are replaced
   If a shared group with the specified name already exists,
   no action is taken, and an error code is returned.
   Return parameter indexUsed indicates where the group was placed
   in the group list.
   Note that a group name can be at most MAX_GROUP_NAME_SIZE
   characters long (defined in ENTBDEFS.H).
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
*/
ETEXPORT32 EntLog ETEXPORT ETAddGroup(	const ETContext ctx,
									const char* groupName,
									const ListID id,
									const GroupOptions* groupOptions,
									SYSINT* indexUsed );

/*
   ETRemoveGroup removes the specified group from the group list.
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
*/
ETEXPORT32 EntLog ETEXPORT ETRemoveGroup( 	const ETContext ctx,
										const char* groupName );

/*
   ETWriteGroupsToFile saves the current group list to the user's profile.
   *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
   *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
*/
ETEXPORT32 EntLog ETEXPORT ETWriteGroupsToFile( const ETContext ctx );

/* End of Group Functions */

/* ELI fuctions */
/* Single signon functions that don't require context */
ETEXPORT32 EntLog  ETStartEntrustLoginInterface( );
ETEXPORT32 EntLog  ETAboutEntrustLoginInterface( );
ETEXPORT32 EntLog  ETEntrustLoginInterfaceControlPanel(  );

/*
	ETWhoIsLoggedIn returns the names of the user profiles currently logged on through Single Sign-On.
	It accepts three parameters:
	wholist [out]:				This is a pre-allocated array of pre-allocated character arrays.
								It returns an array of strings, each specifing the absolute path
								of a profile logged int.
	numberLoggedIn [in-out]:	This parameter represents the size of the "outer" array as
								an [in] parameter.  It returns the number of elements inserted
								into the "outer" array.
	blockSize [in]:				This parameter is the length of each of the "inner" arrays.  It
								should be long enough to hold the absolute path and filename of
								a profile.
 */
ETEXPORT32 EntLog  ETWhoIsLoggedIn( char** wholist, int* numberLoggedIn, int blockSize);

/* End of ELI functions */

/*
   ETIsEntrustFile returns TRUE if the specified file is in Entrust client
   file format (and is therefore a candidate for decrypting/verifying via
   ETSetFileDecryptVerify() ), and FALSE otherwise.
*/
ETEXPORT32 BOOL ETEXPORT ETIsEntrustFile ( const ETFileSpecification inputFile );
/*
   ETQueryClientType takes a path to the Entrust INI file and returns the
   client type.
*/
ETEXPORT32 CLIENT_TYPE ETEXPORT ETQueryClientType(const char* entrustIniFile);

/*
   ETEntLogToString converts an EntLog to a string describing the
   corresponding error.
*/
ETEXPORT32 const char* ETEXPORT ETEntLogToString( EntLog log );

/*
   ETGetEntLogString copies a textual description of the supplied EntLog
   error code to the storage pointeed to by string. The maximum
   length of the copied string is MAX_ENTSTR_SIZE.
*/
ETEXPORT32 void ETEXPORT  ETGetEntLogString( EntLog log, char* string );

/*
   ETQueryEntLogWarning returns TRUE if the supplied EntLog is a warning rather
   than an error. Numerically, the value of a warning is the value of the
   corresponding error - 16000.
*/
ETEXPORT32 BOOL ETEXPORT ETQueryEntLogWarning( EntLog log );

/* ETRemoveWarning function
 
   This function accepts a warning EntLog and returns (also changing the input
   parameter) the error code (see enterr.h) associated with it for
   comparison.
*/
ETEXPORT32 EntLog ETEXPORT ETRemoveWarning( EntLog* warn );

/*
   ETGenerateRandomData fills the buffer pointed to by buffer->data
   with buffer->size BYTES of random data. The caller must pre-allocate
   sufficient storage pointed to by buffer->data.
   This function uses data from the current login context to
   provide additional entropy.
*/
ETEXPORT32 EntLog ETEXPORT ETGenerateRandomData(const ETContext ctx, ETBinData32* buffer);

/* 
   ETEnableCaching allows the application to enable or disable the use of
   local caches for certificates and revocation lists. If enabled, then if local
   copies of certificate or revocation list information is available, and valid,
   it will be used. If disabled, the caches will be ignored and the Toolkit will
   try to get the required information from the Directory.
   NOTE: Caching is ENABLED by default when you create a new EntFile object, so
   this function would typically be used to turn off caching, and then possibly
   re-enable it later on.
   The reserved parameter may be used in future releases to provide finer control
   of individual caches.
*/
ETEXPORT32 EntLog ETEXPORT ETEnableCaching(const ETContext ctx, const BOOL enable, const void* reserved);

/*
   ETCacheOperation allows a variety of operations to be specified on an 
   individual cache, or all caches.
*/
ETEXPORT32 EntLog ETEXPORT ETCacheOperation(const ETContext ctx,
          const CACHE_TYPE cacheType,
          const CACHE_OPERATION cacheOp);
/*
   ETASCIIencode writes an ASCII encoded version of inBuffer to outBuffer.
   Note that the storage pointed to by outBuffer.data is owned by the application,
   and must be pre-allocated to at least ((inBuffer.size * 4 / 3) + 6), since the
   PEM compliant ASCII encoding will expand the data.
   This function can be used to get ASCII encoded versions of binary certificates
   returned by ETGetCertificate.
*/
ETEXPORT32 EntLog ETEXPORT ETASCIIencode(const ETBinData32* inBuffer,  ETBinData32* outBuffer);

/*
   ETASCIIdecode writes a binary version of the PEM compliant ASCII encoded inBuffer
   to outBuffer.
   Note that the storage pointed to by outBuffer.data is owned by the application,
   and must be pre-allocated to at least ((inBuffer.size * 3 / 4) + 10), since the
   decoding converts every 4 bytes of input data to 3 bytes of binary output data.
*/
ETEXPORT32 EntLog ETEXPORT ETASCIIdecode(const ETBinData32* inBuffer,  ETBinData32* outBuffer);

/*
   String utilities for Visual Basic callers
*/
/*
   ETGetStringAddress returns the address of the supplied string.
*/
ETEXPORT32 void* ETEXPORT ETGetStringAddress (const char* string);

/*
   ETGetStringLength returns the length of the null terminated character
   string pointed to by string. The terminating null character is
   not included in the count.
*/
ETEXPORT32 INT16 ETEXPORT ETGetStringLength (const char* string);

/*
   ETStringCopy copies up to maxLength-1 characters from the string
   pointed to by source, to the storage pointed to by destination, terminating
   the destination string with a null character.
   If a null character is found in the source string before maxLength-1
   characters has been copied, only the characters up to and including the
   null character are copied from source.
*/
ETEXPORT32 void ETEXPORT ETStringCopy (	char* destination,
									const char* source,
									SYSINT maxLength);

/*
   ETByteCopy copies length bytes from the storage pointed to by source, to the
   storage pointed to by destination.
*/
ETEXPORT32 EntLog ETEXPORT ETByteCopy (	BYTE* destination,
									const BYTE* source,
									SYSINT length);

/*
	ETReauthenticate causes Single login to reauthenticate the user if the user
	is timed out. Used to cause a login to be required for arbitrary operations
	by the application designer.
*/
ETEXPORT32 BOOL ETEXPORT ETReauthenticate( const ETContext ctx );

/*******************************************************************************
 *
 * FUNCTION:	ETCalculateMAC
 *  
 * DESCRIPTION:	One-step MAC calculation and output.	
 *
 ******************************************************************************/
	
ETEXPORT32 EntLog ETEXPORT ETCalculateMAC( 
	ETContext				ctx,
	const ETBinData32*		dataIn,				/* In: Data to calculate MAC on */
	ETBinData32*			macOut,				/* Out: Calculated MAC */
	ETBinData32*			passwordIn,				/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,				/* In: Algorithm */
	UINT32	 				macLength			/* In: Desired length of MAC, in bytes*/
);

/* Starts a MAC calculation session, using current ciphermode*/
ETEXPORT32 EntLog ETEXPORT ETStartCalculateMAC(
	ETContext				ctx,
	const ETBinData32*		passwordIn,	/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,		/* In: Algorithm */
	UINT32					macLength	/* In: Desired length of MAC, in bytes*/
);
		
/* Updates a MAC calculation session */
ETEXPORT32 EntLog ETEXPORT ETUpdateCalculateMAC(
	ETContext			ctx,
	const ETBinData32*	dataIn					/* In: Data to calculate MAC on */
);

/* Ends a MAC calculation session and outputs the MAC */	
ETEXPORT32 EntLog ETEXPORT ETEndCalculateMAC(
	ETContext		ctx,
	ETBinData32*	macOut				/* Out: Calculated MAC */
);                             		


/*******************************************************************************
 *
 * FUNCTION:	ETVerifyMAC
 *  
 * DESCRIPTION:	One-step MAC verification. Returns ENT_OK if MAC verifies or
 * SK_MAC_CHECK_FAILED if it fails. May also return other EntLogs.
 *
 ******************************************************************************/
	
ETEXPORT32 EntLog ETEXPORT ETVerifyMAC( 
	ETContext			ctx,
	const ETBinData32*	dataIn,					/* In: Data to calculate MAC on */
	const ETBinData32*	macIn,					/* In: MAC to check */
	const ETBinData32*	passwordIn,				/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,				/* In: Algorithm */
	UINT32	 			macLength				/* In: Length of MAC, in bytes */
);

/* Starts a MAC verification session, using current ciphermode */
ETEXPORT32 EntLog ETEXPORT ETStartVerifyMAC(
	ETContext				ctx,
	const ETBinData32*		passwordIn,	/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,		/* In: Algorithm */
	UINT32					macLength	/* In: Length of MAC, in bytes */
);
	
/* Updates a MAC verification session */
ETEXPORT32 EntLog ETEXPORT ETUpdateVerifyMAC(
	ETContext			ctx,
	const ETBinData32*	dataIn			/* In: Data to calculate MAC on */
);
	
/* Ends a MAC verification session. Returns ENT_OK if MAC passes. */	
ETEXPORT32 EntLog ETEXPORT ETEndVerifyMAC(
	ETContext			ctx,
	const ETBinData32*	macIn			/* In: MAC to check */
);

/*******************************************************************************
 *
 * FUNCTION:	ETCalculateHMAC
 *  
 * DESCRIPTION:	One-step HMAC calculation and output.	
 *
 ******************************************************************************/
	
ETEXPORT32 EntLog ETEXPORT ETCalculateHMAC( 
	ETContext				ctx,
	const ETBinData32*		dataIn,				/* In: Data to calculate MAC on */
	ETBinData32*			macOut,				/* Out: Calculated MAC */
	ETBinData32*			passwordIn,				/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,				/* In: Algorithm */
	UINT32	 				macLength			/* In: Desired length of MAC, in bytes*/
);

/* Starts an HMAC calculation session, using current ciphermode*/
ETEXPORT32 EntLog ETEXPORT ETStartCalculateHMAC(
	ETContext				ctx,
	const ETBinData32*		passwordIn,	/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn		/* In: Algorithm */
);
		
/* Updates an HMAC calculation session */
ETEXPORT32 EntLog ETEXPORT ETUpdateCalculateHMAC(
	ETContext			ctx,
	const ETBinData32*	dataIn					/* In: Data to calculate MAC on */
);

/* Ends an HMAC calculation session and outputs the MAC */	
ETEXPORT32 EntLog ETEXPORT ETEndCalculateHMAC(
	ETContext		ctx,
	ETBinData32*	macOut,				/* Out: Calculated MAC */
	UINT32			macLength			/* In: Desired length of MAC, in bytes*/
);                             		


/*******************************************************************************
 *
 * FUNCTION:	ETVerifyHMAC
 *  
 * DESCRIPTION:	One-step HMAC verification. Returns ENT_OK if MAC verifies or
 * SK_MAC_CHECK_FAILED if it fails. May also return other EntLogs.
 *
 ******************************************************************************/
	
ETEXPORT32 EntLog ETEXPORT ETVerifyHMAC( 
	ETContext			ctx,
	const ETBinData32*	dataIn,					/* In: Data to calculate MAC on */
	const ETBinData32*	macIn,					/* In: MAC to check */
	const ETBinData32*	passwordIn,				/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn,				/* In: Algorithm */
	UINT32	 			macLength				/* In: Length of MAC, in bytes */
);

/* Starts an HMAC verification session, using current ciphermode */
ETEXPORT32 EntLog ETEXPORT ETStartVerifyHMAC(
	ETContext				ctx,
	const ETBinData32*		passwordIn,	/* In: Password to create MACing key */
	ENCRYPTION_ALGORITHM	algIn		/* In: Algorithm */
);
	
/* Updates an HMAC verification session */
ETEXPORT32 EntLog ETEXPORT ETUpdateVerifyHMAC(
	ETContext			ctx,
	const ETBinData32*	dataIn			/* In: Data to calculate MAC on */
);
	
/* Ends an HMAC verification session. Returns ENT_OK if MAC passes. */	
ETEXPORT32 EntLog ETEXPORT ETEndVerifyHMAC(
	ETContext			ctx,
	const ETBinData32*	macIn,			/* In: MAC to check */
	UINT32	 			macLength		/* In: Length of MAC, in bytes */
);

/* Given the input OID, return the ASN.1 encoded value from the policy cert. 
   Returns COMM_ATTCERT_ATTRIBUTE_NOT_FOUND if the policy cert does not contain this OID.
   Returns ENT_INFO_MISSING if the policy cert contains this OID but no value for it. */
ETEXPORT32 EntLog ETEXPORT ETGetPolicyCertValue( ETContext ctx, const char* oid, ETBinData32* encodedValue);

// Compares 2 Distinguished Names.  Returns an error if dn1 or dn2 are invalid DNs,
// and sets the value of "equal" appropriately if dn1 and dn2 are equal. 
ETEXPORT32 EntLog ETEXPORT ETCompareDistinguishedNames(const char* dn1, const char* dn2, BOOL* equal);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif

