/******************************************************************************
 * entapi.h - Header file for the EntrustFile C++ Language API.
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.
 *****************************************************************************/

#ifndef ENTAPI_H
#define ENTAPI_H

#ifdef	MACOS
#include	<files.h>

#endif

#if !defined( ENTAPI )
#include "entname.h"
#include <enthdr.h>
#include <entflist.h>
#include <entbdefs.h>
#include <entbdata.h>
#include <entgstr.h>


// class declarations
class EntrustFileSMIME;
class LoginContext;
class HVIRUSSCANNER;
class VIRUSLIBINIT;

#else //ENTAPI

#include <toolkit/entapi/entname.h>
#include <toolkit/entapi/enthdr.h>
#include <toolkit/entapi/entflist.h>
#include <toolkit/entapi/tkbdefs.h>

// Inclusions for each of the services
#include <toolkit/entapi/entrlistsrv.h>
#if defined(_WIN32)
#include <toolkit/entapi/entsmimesrv.h>
#endif

#include <base/etfile/etf_smim.h>
#include <base/etfile/os_spec.h>
#include <base/etfile/bindata.h>
#include <base/etfile/gstring.h>
#include <base/thread/e_thread.h>
#include <base/etfile/identlog.h>

#endif // ENTAPI

// Class declarations
class AppContext;
class EntrustLoginInterface;
class EntrustFile;
class MatchedNameList;
class EntrustFileSecAPI;
class CliObject;
class CliFileEncryptor;
class CliFileDecryptor;
class TKctx;
class TLS_Flags;
class RListService;
class EntRListService;
#if defined(_WIN32)
class EntSMIMEService;
#endif
class ET_Key;

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

//
// EXPT/EXPT32 modifiers
// ---------------------
// The EXPT and EXPT32 modifiers are defined in ENTBDEFS.H,
// The following table summarizes their values on different platforms.
//
// Platform        	EXPT             		EXPT32
// --------         ----					------
// Win16			__export __far
// Win32									__declspec( dllexport )
// Mac
// Unix
//

// Timestamp info structure
// Used to extract timestamp info from an archive or protected message
class TimestampInfo {

public:
	EXPT32 EXPT TimestampInfo(const EntFile& ctx);
	EXPT32 EXPT ~TimestampInfo();

	EntCertificate*		m_server;		/* the timestamp server certificate */
	EntCertificate*		m_serverCA;		/* the timestamp server's CA */
	GString				m_serialNumber;	/* the timestamp serial number */
	time_t				m_date;			/* date of timestamp */
	EntLog				m_error;		/* error or status */
	TIMESTAMP_HASH_ALG	m_hashAlg;		/* alg used to create the timestamp hash */
	EntLog				m_constructorError;
};

// The UNPROTECT_INFO structure contains information about a protected message.
typedef struct {
	SECURITY_OPERATION	 secOperation;
	ENCRYPTION_ALGORITHM encryptionQuality;
	SIGNING_QUALITY		 signingQuality;
	GString				 originator;
	GString				 idu_type;
	GString				 supportedAlgorithms;
	time_t				 signingTime;
	void*				 reserved; // for future use.
} UNPROTECT_INFO;

//
// The CertificateData structure type contains basic information extracted from
// an X.509 public key certificate.
//
typedef struct
{
	GString OwnerName;	// the common name of the signature originator
	GString OwnerUniqueName; // the X.500 distinguished name of the signature originator
	GString CAName;		// the originator's Certification Authority
} CertificateData;

// Returns the Version string of the EntrustFile Library
EXPT32 const char* EXPT QueryEntFileVersion(void);

//
// CreateUser function
//
// This function is used when creating or restoring an Entrust user.
// Pass in the reference number and one time password
// (supplied by the Entrust/Authority), the initial user password to use,
// the location of the Entrust INI file, and
// a path to the user profile (which will be created).
//
// For the creating parameter, specify TRUE for creating a user,
// FALSE if restoring an existing user.
// If performing a restore and the specified user profile already exists,
// that profile will be updated with new key information, but retain existing
// option settings.
//
EXPT32 EntLog EXPT CreateUser	(	const INT32 refNum,
									const GString& oneTimePassword,
								 	const GString& userPassword,
								 	const GString& entrustIniFile,
						 			const GString& userProfile,
								 	BOOL creating);

//
// CreateUserFromPKCS12 This function is used when creating an Entrust user
// from a PKCS #12 message.  The resulting user is an Entrust Solo User.
// The function takes the name of the file to be imported along with the password used to
// protect that file.  The file name of the profile to be created along with the password for the profile must also be supplied.
EXPT32 EntLog EXPT CreateUserFromPKCS12(const GString &importFileName, const GString &importPassword, const GString &profileFileName, const GString &profilePassword, const GString &iniFile);


#ifdef _WIN32
// Bring up the Create / Recover User GUI - for use by Entelligence only (Win32 / C++)
EXPT32 EntLog CreateUser(const GString& EntrustIniFile, GString& EntrustProfile);
EXPT32 EntLog RecoverUser(const GString& EntrustIniFile, GString& EntrustProfile);
EXPT32 EntLog CreateUser( const GString& EntrustIniFile, GString& EntrustProfile,
						  const GString& szAuthCode, const GString& szRefNum, UINT32 uFlags, LPVOID pReserved );
EXPT32 EntLog RecoverUser( const GString& EntrustIniFile, GString& EntrustProfile,
						   const GString& szAuthCode, const GString& szRefNum, UINT32 uFlags,  LPVOID pReserved );

// Parse SMIME protected file and retreive the SECURITY_OPERATION needed to unprotect
// External signature file is only needed if clear signed is expected
EXPT32 EntLog GetSMIMESecurityOperation(const char* pszProtectedFile,
                                        SECURITY_OPERATION& operation,
                                        const char* pszExternalSignatureFile = NULL);
#endif

//
// The EntFile class is the main class of the EntrustFile Toolkit. It maintains
// an Entrust user context and provides a variety of member functions for
// security operations (encrypting, decrypting, digital signing and verification)
// at both the file and buffer level.
//
class EntFile
{
	friend class EntCertificate;
	friend class EntCertificateList;
	friend class RListService;
    friend class SMIMEService;
    friend class SMIMEProt;
    friend class SMIMEUnprot;

public:

// This function is used for logging in with an Entrust user profile
// and password. The noX500Dir flag is ignored in Lite mode, and should
// only be set TRUE in a full Entrust environment where network
// connectivity to the Entrust network infrastructure is not available
// or not desired.  The constructor error (if any) is returned.
// The method performs the same function as the Constructor below.  It's
// existance is for those who want to keep all memory management in the dll.
//
	EXPT32 static EntLog Login( EntFile*& login,
								const GString& userProfile,
								const GString& password,
								const GString& entrustIniFile,
								const BOOL noX500Dir = FALSE);

// This function will logout the current user.  After this function is
// called, the EntFile object will have a NULL value.
// The method performs the same function as the Destructor below.  It's
// existance is for those who want to keep all memory management in the dll.
//
	EXPT32 static void Logout( EntFile*& login );

// This constructor is used for logging in with an Entrust user profile
// and password. The noX500Dir flag is ignored in Lite mode, and should
// only be set TRUE in a full Entrust environment where network
// connectivity to the Entrust network infrastructure is not available
// or not desired.
//
	EXPT32 EXPT EntFile(const GString& userProfile,
						const GString& password,
						const GString& entrustIniFile,
						const BOOL noX500Dir = FALSE);

//
//
// EntFile destructor, and a constructor error utility function
//
	EXPT32 EXPT ~EntFile(void);
	EXPT32 EntLog EXPT GetConstructorError(void);

//
// GetLoginInformation provides information about the current login session.
// To use, specify the type of information desired using the loginInfo parameter,
// and provide a pointer to the appropriate data storage in the infoPtr structure.
// For example, to determine if the Toolkit is running in "offline mode" (e.g. cannot
// connect to Entrust/Directory), you would call it as follows:
// EntFile myEntFile(...);
// BOOL offlineFlag;
// EntLog rc;
// rc = myEntFile.GetLoginInformation(LG_BOOL_OFFLINE, &offlineFlag);
// For LG_STRING_* enums, use a pointer to a GString object.
// For LG_INT16_* enums, use a pointer to an INT16.
//
   EXPT32 EntLog EXPT GetLoginInformation(	const LOGIN_INFO loginInfo,
											void* infoPtr);

//
// GetPolicyCertificateInformation is similar to GetLoginInformation
// except that it provides information about the policy certificate and uses
// the POLICY_CERTIFICATE_INFO enumeration to specify what data and type
// is to be returned.
//
   EXPT32 EntLog EXPT GetPolicyCertificateInformation( const POLICY_CERTIFICATE_INFO eInfo,
													   void *pValue);

//
// DirectorySearch will search the specified SearchLocation, based on the
// specified search expression (searchExpr) and search base (searchBaseDN).
// Matching names will be passed back in matchingNames, and each name will
// have associated attribute information based on the criteria defined in
// attribsToReturn. The searchDepth parameter controls the depth of an X.500
// directory search, with the default being the subtree starting at searchBase.
// If searchBaseDN contains a zero length string, the default X.500 search base
// is used. The default search base and all available search bases can be
// queried using the GetSearchBase() and GetSearchBaseName() functions.
// Note that if the client type is CL_LITE, the seachExpr, searchBaseDN,
// attribsToReturn, and searchDepth parameters will be ignored, and all
// names in the specified location(s) (i.e. Public Address Book and/or Personal
// Address Book) will be returned.
// The searchDepth parameter specifies how much of the directory subtree
// (starting at searchBase) should be searched.
//
	EXPT32 EntLog EXPT DirectorySearch(	const GString& searchExpr,
										const GString& searchBaseDN,
     									const GString& attribsToReturn,
   			  							EntrustNameList& matchingNames,
	    								SEARCH_LOCATION location,
	    								SEARCH_DEPTH searchDepth = SD_SEARCH_SUBTREE );

// HI-Haider June 30th, 99: not for the Mac
//#if defined(_WIN32) || defined(MACOS)
#if defined(_WIN32)
//
// SetCancelDialog receives the window handle for the cancel dialog and cancels a
// DirectorySearch when a button-click event is detected in the dialog.
//
	EXPT32 EntLog EXPT SetCancelDialog(HWND handle);
#endif // _WIN32

//
// SetCancel sets the DirectorySearch cancel to TRUE/FALSE.  This can be called from a
// seperate thread as DirectorySearch is running and will cancel DirectorySearch if the
// parameter is set to TRUE.  The <cancel> parameter must be reset to FALSE following the
// the search.
//
	EXPT32 EntLog EXPT SetCancel( BOOL cancel =TRUE );

//
// GetSearchBase copies the distinguished name of the default X.500 search base,
// (the first entry in list of available search bases) to the searchBaseDN parameter.
//
	EXPT32 EntLog EXPT GetSearchBase  (GString& searchBaseDN);

//
// GetNumberOfSearchBases returns the number of available search bases,
// or -1 on error.
//
	EXPT32 INT16 EXPT GetNumberOfSearchBases  (void);

//
// SearchBaseIsAncestor returns TRUE if <searchBase1> is an ancestor of <searchBase2>.
// For example o=org,c=ca is an ancestor of ou=dev,ou=emp,o=org,c=ca
//
	EXPT32 BOOL EXPT SearchBaseIsAncestor(const GString& searchBase1, const GString& searchBase2 );

//
// GetSearchBaseName returns name information about the search base selected by index
// (which must be from 0 to (GetNumberOfSearchBases() - 1).
// searchBaseDN is the indexed search base's distinguished name (which can be used
// in a subsequent call to DirectorySearch() ), and
// searchBaseFriendlyName is a more user friendly name assigned by the Entrust
// administrator.
//
	EXPT32 EntLog EXPT GetSearchBaseName(	SYSINT index,
											GString& searchBaseDN,
											GString& searchBaseFriendlyName);
//
// DisconnectDirectory explicitly disconnects the EntFile user context from the
// Entrust/Directory LDAP (Lightweight Directory Access Protocol) daemon.
// Its use is optional and only applies to X.500 mode.
// It is intended for use by applications when they do not require access to
// directory services, in order to reduce the system overhead of maintaining
// an idle LDAP session.
// Any operation which uses directory access (such as ValidateRecipients and DirectorySearch)
// will implicitly re-connect to the LDAP daemon if required.
// Calling DisconnectDirectory when there is no LDAP connection in place
// has no effect.
//
	EXPT32 void EXPT DisconnectDirectory(void);


//	SignAlgToString takes a SIGNING_QUALITY value, and returns a string format of
//	that value that includes the hash algorithum with signing key type.
	EXPT32 EntLog SignAlgToString( const SIGNING_QUALITY& signType, GString& outStr );

// GetAlgorithmAvailability takes an algorithm specifier, and sets the 'available'
// BOOL according to if the algorithm is available or not.
// If available, algDescription will contain a descriptive string. This string
// can be presented to the user during the algorithm selection process.
// If the specified algorithm is not available, algDescription will be a zero length
// string.
	EXPT32 EntLog EXPT GetAlgorithmAvailability(const ENCRYPTION_ALGORITHM algorithm,
												BOOL& available,
												GString& algDescription );

// GetSigningAlgorithmAvailability takes a signing algorithm specifier, and sets the 'available'
// BOOL "true" if the algorithm is available and "false" if it is not.
// If available, signAlgDescription will contain a descriptive string.  This string
// can be presented to the user during the algorithm selection process.
// If the specified algorithm is not available, signAlgDescription will be a zero length
// string.
	EXPT32 EntLog EXPT GetSigningAlgorithmAvailability(const SIGNING_QUALITY signAlgorithm,
											   BOOL& available,
											   GString& signAlgDescription);

// GetAlgorithmSupported takes an algorithm specifier <algorithm> and a delimited list of supported
// algorithm OIDs <supportedAlgs>, and sets the available BOOL according to if the algorithm is in
// the list or not.
	EXPT32 EntLog EXPT GetAlgorithmSupported(const GString& supportedAlgs,
											 const ENCRYPTION_ALGORITHM algorithm,
											 BOOL& available  );

// GetUpperAlgorithmEnum returns the highest symmetric encryption algorithm
// available (from the perspective of the ENCRYPTION_ALGORITHM enum). To determine the
// full range of algorithms available, an application should loop
// from 0 to the returned upperAlgorithm, calling GetAlgorithmAvailability() for each index.
// Note that there may be gaps in the supported list based on export or administrative
// restrictions on algorithm use - the enum value associated with a particular algorithm
// will always be the same.
//
	EXPT32 EntLog EXPT GetUpperAlgorithmEnum(ENCRYPTION_ALGORITHM& upperAlgorithm);

//
// UpdateCertificateCaches is intended to be called if a user is currently online
// but is planning on going offline. It attempts to retrieve and cache encryption
// certificates and associated revocation lists for the names in the specified name list,
// plus those names defined in the available Groups (see the Group Functions definitions
// for more information on groups).
//
	EXPT32 void EXPT UpdateCertificateCaches(
								EntrustNameList& nlRecipients );


//
// Core security operation functions
//
// StartEncryptWithHeader is used to start an ENCRYPT ONLY operation. The header
// parameter refers to the EntHeader created by CreateHeader after a
// StartSignEncrypt/SignEncrypt/EndSignEncrypt operation set done with SO_ENCRYPT_ONLY.
// This method will use <header> to start another encrypt only operation set for
// SignEncrypt/EndSignEncrypt.
//
	EXPT32 EntLog StartEncryptWithHeader( EntHeader& header);

//
// StartSignEncrypt is used to start an encrypt and/or sign operation.
// The following variants of StartSignEncrypt are supported
// (names preceded by "my" are user variables)
// myEntLog = StartSignEncrypt(SO_ENCRYPT_ONLY,		myOptions);
// myEntLog = StartSignEncrypt(SO_SIGN_ONLY,		myOptions);
// myEntLog = StartSignEncrypt(SO_SIGN_AND_ENCRYPT, myOptions);
// Call SetBufferTimestamping(TRUE) if you want to timestamped also.
//
	EXPT32 EntLog EXPT StartSignEncrypt(SECURITY_OPERATION secOp,
										const SecurityOptions& options = defaultSecurityOptions);
//
// Once StartSignEncrypt is called, subsequent calls to SignEncrypt are made
// to actually process the plaintext data. For example:
// For encrypting or signing and encrypting:
//  myEntLog = SignEncrypt(myPlainText, myCipherText);
// For signing only, outBuffer = inBuffer:
//  myEntLog = SignEncrypt(myPlainText, myDummyPlainText);
//
	EXPT32 EntLog EXPT SignEncrypt(const BinData& inBuffer, BinData& outBuffer);
//
// Once all input data has been processed, the operation is completed by a
// call to EndSignEncrypt.
// When encrypting or encrypting and signing, the outBuffer will contain any
// residual ciphertext.
// When just signing, the returned outBuffer will be empty. For example:
// For encrypting or signing and encrypting:
//  myEntLog = EndSignEncrypt(myResidualCipherText);
// For signing only, returned outBuffer is empty:
//  myEntLog = EndSignEncrypt(myDummyBuffer);
// Call CreateTimestampHeader() to get the timestamp header data if the buffer was timestamped.
//
	EXPT32 EntLog EXPT EndSignEncrypt( BinData& out );

//
// StartDecryptVerify is used to start a decrypt and/or signature verification
// operation. The actions to take are based on the content of the header
// passed in.
// If the header indicates that the associated message was signed,
// the certificateData parameter will contain information about the originator.
// Otherwise, certificateData is not modified.
// The headerType parameter will return information about the provided header.
// Optional parameter verificationCertificate, if non-NULL, and if headerType
// is HT_SIGN_ONLY or HT_SIGN_AND_ENCRYPT, will return the
// verification certificate stored in the header.
// There are two variants of StartDecryptVerify
// (names preceded by "my" are user variables):
// myEntLog = StartDecryptVerify(myHeader, myCertificateData, myType);
// myEntLog = StartDecryptVerify(myHeader, myCertificateData, myType, &myCert);
// Timestampheader is passed in when verifiying a timestamp on this file/buffer
// Call SetBufferTimestampVerify(TRUE) if you want the supplied timestamp header verified.
// and call SetTimestampResult(timestampheader) to supply the timestamp you want to verify.

	EXPT32 EntLog EXPT StartDecryptVerify(	EntHeader& header,
											CertificateData& certificateData,
											HEADER_TYPE& headerType,
											EntCertificate* verificationCertificate = NULL);
//
// Once StartDecryptVerify is called, subsequent calls to DecryptVerify
// are made to actually process the signed/encrypted data. For example:
// For signed only data, outBuffer = inBuffer:
//  myEntLog = DecryptVerify(mySignedData, myDummyText);
// For encrypted, and possibly signed, data:
//  myEntLog = DecryptVerify(myCipherText, myPlainText);
//
	EXPT32 EntLog EXPT DecryptVerify(const BinData& inBuffer, BinData& outBuffer);
//
// Once all input data has been processed, the operation is completed by a call
// to EndDecryptVerify.
// When decrypting or decrypting and verifying, the outBuffer will contain
// any residual plaintext. When just verifying a signature, the outBuffer
// is unchanged. For example:
// For decrypting or verifying and decrypting
//  myEntLog = EndDecryptVerify(myResidualPlainText);
// For verifying only, out buffer is unchanged
//  myEntLog = EndDecryptVerify(myDummyBuffer);
// Call GetTimestampResult() to determine the timestamp verification results (if the buffer
// was timestamped originally)

EXPT32 EntLog EXPT EndDecryptVerify( BinData& outBuffer );

//
// The following four functions support the export of the signing key and the decryption key
// in PKCS#8 format.

//
// ExportSigningKeyPKCS8 returns the signing key in PKCS8 format.
//
EXPT32 EntLog EXPT ExportSigningKeyPKCS8(const BinData deskey, BinData& signingKey);

//
// GetNumberOfDecryptionKeys returns number of decryption keys the Profile has, including
// the current key and key history.
//
EXPT32 INT32 EXPT GetNumberOfDecryptionKeys();

//
// ExportDecryptionKeyPKCS8 returns the requested decryption key in PKCS8 format. The keys
// are indexed according to their age starting at 0 for the current key.
//
EXPT32 EntLog EXPT ExportDecryptionKeyPKCS8(INT32 index, const BinData desKey, BinData& decryptionKey);

//
// GetDecrypionKeyId returns the requested decryption key ID.
//
EXPT32 EntLog EXPT GetDecryptionKeyId(INT32 index, BinData& id);



/*******************************************************************************
 *
 * FUNCTION:	EntFile::CalculateMAC
 *
 * DESCRIPTION:	One-step MAC calculation and output.
 *
 ******************************************************************************/

EXPT32 EntLog EXPT CalculateMAC(
	const BinData	&dataIn,					// In: Data to calculate MAC on
	BinData			&macOut,					// Out: Calculated MAC
	BinData			passwordIn,					// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,				// In: Algorithm
	UINT32	 		macLength = 8					// In: Desired length of MAC, in bytes
);

// Starts a MAC calculation session, using current ciphermode
EXPT32 EntLog EXPT StartCalculateMAC(
	const BinData	&passwordIn,	// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,	// In: Algorithm
	UINT32			macLength = 8	// In: Desired length of MAC, in bytes
);

// Updates a MAC calculation session
EXPT32 EntLog EXPT UpdateCalculateMAC(
	const BinData	&dataIn					// In: Data to calculate MAC on
);

// Ends a MAC calculation session and outputs the MAC
EXPT32 EntLog EXPT EndCalculateMAC(
	BinData			&macOut				// Out: Calculated MAC
);


/*******************************************************************************
 *
 * FUNCTION:	EntFile::VerifyMAC
 *
 * DESCRIPTION:	One-step MAC verification. Returns ENT_OK if MAC verifies or
 * SK_MAC_CHECK_FAILED if it fails. May also return other EntLogs.
 *
 ******************************************************************************/

EXPT32 EntLog EXPT VerifyMAC(
	const BinData	&dataIn,					// In: Data to calculate MAC on
	const BinData	&macIn,						// In: MAC to check
	const BinData	&passwordIn,				// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,				// In: Algorithm
	UINT32	 		macLength = 8				// In: Length of MAC, in bytes
);

// Starts a MAC verification session, using current ciphermode
EXPT32 EntLog EXPT StartVerifyMAC(
	const BinData	&passwordIn,	// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,	// In: Algorithm
	UINT32	 		macLength = 8	// In: Length of MAC, in bytes
);

// Updates a MAC verification session
EXPT32 EntLog EXPT UpdateVerifyMAC(
	const BinData	&dataIn					// In: Data to calculate MAC on
);

// Ends a MAC verification session. Returns ENT_OK if MAC passes.
EXPT32 EntLog EXPT EndVerifyMAC(
	const BinData	&macIn			// In: MAC to check
);
/*******************************************************************************
 *
 * FUNCTION:	EntFile::CalculateHMAC
 *
 * DESCRIPTION:	One-step HMAC calculation and output.
 *
 ******************************************************************************/

EXPT32 EntLog EXPT CalculateHMAC(
	const BinData	&dataIn,					// In: Data to calculate MAC on
	BinData			&macOut,					// Out: Calculated MAC
	BinData			passwordIn,					// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,				// In: Algorithm
	UINT32	 		macLength					// In: Desired length of MAC, in bytes
);

// Starts an HMAC calculation session, using current ciphermode
EXPT32 EntLog EXPT StartCalculateHMAC(
	const BinData	&passwordIn,	// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn	// In: Algorithm
);

// Updates an HMAC calculation session
EXPT32 EntLog EXPT UpdateCalculateHMAC(
	const BinData	&dataIn					// In: Data to calculate MAC on
);

// Ends an HMAC calculation session and outputs the MAC
EXPT32 EntLog EXPT EndCalculateHMAC(
	BinData			&macOut,				// Out: Calculated MAC
	UINT32			macLength				// In: Desired length of MAC, in bytes
);


/*******************************************************************************
 *
 * FUNCTION:	EntFile::VerifyHMAC
 *
 * DESCRIPTION:	One-step HMAC verification. Returns ENT_OK if MAC verifies or
 * SK_MAC_CHECK_FAILED if it fails. May also return other EntLogs.
 *
 ******************************************************************************/

EXPT32 EntLog EXPT VerifyHMAC(
	const BinData	&dataIn,					// In: Data to calculate MAC on
	const BinData	&macIn,						// In: MAC to check
	const BinData	&passwordIn,				// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn,				// In: Algorithm
	UINT32	 		macLength					// In: Length of MAC, in bytes
);

// Starts an HMAC verification session, using current ciphermode
EXPT32 EntLog EXPT StartVerifyHMAC(
	const BinData	&passwordIn,	// In: Password to create MACing key
	ENCRYPTION_ALGORITHM	algIn	// In: Algorithm
);

// Updates an HMAC verification session
EXPT32 EntLog EXPT UpdateVerifyHMAC(
	const BinData	&dataIn					// In: Data to calculate MAC on
);

// Ends an HMAC verification session. Returns ENT_OK if MAC passes.
EXPT32 EntLog EXPT EndVerifyHMAC(
	const BinData	&macIn,			// In: MAC to check
	UINT32	 		macLength		// In: Length of MAC, in bytes
);

//
// Stand alone virus detection support
//
//
// Retrieve the VirusDetectInfo structure for the file at index <index>.  The method
// "ScanFilesforVirus" must be called first.  Otherwise, an error will be returned.
	EXPT32 EntLog EXPT GetVirusInfo( int index, VirusDetectInfo& output);

//
// This method takes a list of file names and a set of options.  Each of the files in
// the list will be scanned for viruses according to the options in the <op> parameter.
// Use "GetVirusInfo" above to retrieve data in each file.
// The <moveToDir> is used only if the op parameter is set to "MOVE_INFECTED_FILES",
// then moveToDir should be set to the destination directory.  Otherwise, it is ignored.
	EXPT32 EntLog EXPT ScanFilesForVirus( const EntFileList& inputFileList, // In file list
										  VirusDetectOptions op,			// In options
										  const char* moveToDir =0);		// In move destination

//
// This method takes a file name, a set of options and a reference to a VirusDetectInfo structure.
// The file denoted by <filename> will be scanned for viruses according to the settings in <op>.  The
// results will be returned in <output>.
	EXPT32 EntLog EXPT ScanFileForVirus( const GString& filename,			// In file name
										  VirusDetectOptions op,			// In options
										  VirusDetectInfo& output);			// Out info

//
// This method sets the VirusDetectOption [op] for the decryption methods that automatically do
// virus scanning.  It's setting will NOT be used by the above two methods.  It's default
// setting is: DO_NOTHING.
// If the [op] parameter is set to "MOVE_INFECTED_FILES", then moveToDir should be set to the
// destination directory, otherwise it is ignored.
//
	EXPT32 void EXPT SetVirusOp(VirusDetectOptions op, const char* moveToDir =0);


//
// Stand alone timestamp buffer based support
//

// Start a buffer based timestamp only operation
	EXPT32 EntLog EXPT StartTimestamp(void);

// Once StartTimestamp() is called, subsequent calls to Timestamp() are made
// to actually process the plaintext data.

	EXPT32 EntLog EXPT Timestamp(const BinData &in);

//
// Once all input data has been processed, the operation is completed by a
// call to EndTimestamp.
// Call CreateTimestampHeader() to get the timestamp header data

	EXPT32 EntLog EXPT EndTimestamp(void);

//
// StartVerifyTimestamp() is used to start a timestamp only verification
// operation.  The timestamp header to verify is passed in.

	EXPT32 EntLog EXPT StartVerifyTimestamp(const BinData*	timestampHeader);

// Once StartVerifyTimestamp() is called, subsequent calls to VerifyTimestamp()
// are made to actually process the data.

	EXPT32 EntLog EXPT VerifyTimestamp(const BinData &in);

// Once all input data has been processed, the operation is completed by a call
// to EndVerifyTimestamp().  A call to GetTimestampResult() to determine the
// timestamp verification results.

	EXPT32 EntLog EXPT EndVerifyTimestamp(void);
//
// Shared timestamp functions - used by stand-alone timestamp and buffer based with
// timestamp flag set via SetBufferTimestamping();
//

// Get the timestamp header data as a result of timestamping a buffer based operation of the stand-alone
// timestamp operation.

	EXPT32 EntLog EXPT CreateTimestampHeader(BinData &timestampHeader);

// Get the timestamp verification result.

	EXPT32 EntLog EXPT GetTimestampResult(TimestampInfo& timestampInfo);

// Set the timestamp header to verify. Call before StartDecryptVerify().

	EXPT32 EntLog EXPT SetTimestampResult(BinData& timestampInfo);

//
// ValidateRecipients will move any recipients that do not have
// valid certificates to the nlInvalid list. This function can
// be used to determine, prior to calling CreateHeader,
// which recipients do not have valid certificates.
//
	EXPT32 EntLog EXPT ValidateRecipients( EntrustNameList& nlRecipients,
											EntrustNameList& nlInvalid );
//
// CreateHeader will move any recipients that do not have valid certificates
// to the nlInvalid list (via an internal call to
// ValidateRecipients). It will then generate a PEM-style header.
// NOTE: if the data being secured is SIGNED ONLY, nlRecipients must be
// empty (recipients are only specified for encryption operations).
//
	EXPT32 EntLog EXPT CreateHeader(EntrustNameList& nlRecipients,
									EntHeader& header,
									EntrustNameList& nlInvalid);
//
// CreateMinimalHeader is similar to CreateHeader (above), with the following
// differences based on the security operation performed:
// if signed, the user's verification certificate is not included in the
// header. If encrypted, the user's encryption certificate is not included.
//
	EXPT32 EntLog EXPT CreateMinimalHeader(EntrustNameList& nlRecipients,
										EntHeader& header,
										EntrustNameList& nlInvalid);
//
// Address Book Functions
//
// ShowAddrBook creates a connection to the address book application and
// causes the command specified in msg_id to be executed from the address
// book.
//
    EXPT32 EntLog EXPT ShowAddrBook( const GString& profile,
                                     const GString& ERAName,
                                     AB_CmdMsgId msg_id,
                                     EntrustNameList& nameList,
                                     ArchiveOptions *opts_ID );

//
// Personal Address Book functions
//
// HavePAB determines the existance of a user's Personal Address Book.
// NOTE: Return code of 0 means a PAB exists.
//
	EXPT32 EntLog EXPT HavePAB(void);
//
// CreatePAB creates an (initially empty) Personal Address Book.
// As of v2.0, the PAB file name will be the user profile name,
// minus the ".epf" extension, if present, and appended with
// a ".pab" extension, So a user with profile name entuser.epf will
// have a Personal Address Book file named entuser.pab,
// in the same directory as the profile.
//
	EXPT32 EntLog EXPT CreatePAB(const char* ignoredValue = NULL);
//
// GetAddressVerificationString searches the PAB for an entry
// matching uniqueName, and returns an Address Verification String
// in authString.
//
	EXPT32 EntLog EXPT GetAddressVerificationString(GString& uniqueName,
											 		GString& authString);
//
// DeleteAddressFromPAB deletes the entry matching uniqueName from the
// Personal Address Book
//
	EXPT32 EntLog EXPT DeleteAddressFromPAB(GString& uniqueName);
//
// ExtractCertificates takes an import fileName (.KEY), and returns the certificates
// found in the file as EntCertificate's.  The process of reading the file is the same
// as ImportCertificate, but rather than adding the certifictes to the PAB, they are
// returned to the caller.  This is for PR ENTOT00080723 and will allow Express to
// display the certificates to the user before they chose to add them to the PAB.
// (Added September 2003 by Sarah Happé)
//
    EXPT32 EntLog EXPT ExtractCertificates(const char* filename,
                                           EntCertificate &signingCertificate,
                                           EntCertificate &encryptionCertificate);
//
// ImportCertificate takes an import fileName, adds the user and certificate
// information from it to the PAB, and returns an EntrustName containing
// information about the user whose certificates were imported.
// The import certificate file will typically have been generated by another
// user calling the ExportMyCertificate() function.
//
	EXPT32 EntLog EXPT ImportCertificate(const char* fileName, EntrustName& userName);

// Make a new PAB entry based on the provided certificate list.
// Information about the user whose certificates were imported is returned via the
// userName parameter.
// See the EntCertificateList definitions in ENTCERT.H for more information.
	EXPT32 EntLog EXPT ImportCertificateList(	EntCertificateList& certList,
												EntrustName& userName);
//
// ExportMyCertificate exports the current user's public key certificates
// to the indicated file, and return the address verification string in
// authString. Note that the current user must have a valid PAB in order to
// export their certificates.
//
	EXPT32 EntLog EXPT ExportMyCertificate(const char* fileName, GString& authString);

//
// ExportCertificateListPKCS12 exports the current user's public key certificates
// and keys specified in the CertificateList to the indicated file.
// The user is required to re-authenticate using the profile password.  The
// certificats and corresponding keys will be protected with keys generated using
// the exportPassword and hashCount.  The user should use the default hashCount
// unless they have reason not to.
	EXPT32 EntLog EXPT ExportCertificateListPKCS12(const GString &userPassword, const GString &outputFileName, const GString &exportPassword, EntCertificateList &certList, UINT32 hashCount = DEFAULT_P12_HASH_COUNT);

//
// GetPKCS12ExportableCertificates returns a list of certificates that the user
// can export via PKCS #12

	EXPT32 EntLog EXPT GetPKCS12ExportableCertificates(EntCertificateList &certList);


//
// ReplacePABEntry will search the PAB for an entry whose unique name matches
// that of the supplied EntrustName, and will then replace that entry with
// the provided EntrustName entry.
//
	EXPT32 EntLog EXPT ReplacePABEntry(const EntrustName& userName);


//
// Information
//
// GetUserInfo retrieves information about the current Entrust user.
// The common name attribute "cn", is returned in userName.
// The Certification Authority name is returned in CAName.
// The userAttributes argument is no longer used.
//
	EXPT32 EntLog EXPT GetUserInfo(	EntrustName& userName,
									const GString& userAttributes, GString& CAName);

//
// Simpler version of GetUserInfo which just returns current user name,
// and the name of the user's Certification Authority.
//
	EXPT32 EntLog EXPT GetUserInfo(	GString& userName,
									GString& CAName);

//
// GetUserEncryptionCertificate returns the encryption certificate
// of the current user.
//
	EXPT32 EntLog EXPT GetUserEncryptionCertificate(EntCertificate& certificate);
//
// GetUserVerificationCertificate returns the verification certificate
// of the current user.
//
	EXPT32 EntLog EXPT GetUserVerificationCertificate(EntCertificate& certificate);
//
// GetIssuerVerificationCertificate returns the verification certificate
// of the issuer (Certification Authority) of the current user's certificates.
//
	EXPT32 EntLog EXPT GetIssuerVerificationCertificate(EntCertificate& certificate);

//
//	GetSecurityOptions returns the currently enabled security options
// (set via a call to StartSecurityOperation).
//
	EXPT32 SecurityOptions EXPT GetSecurityOptions(void);
//
// Setting and Querying Additional Options
//
// These functions allow setting and querying of additional options
// for buffer based security operations.
// Options are applied at the start of a security operation, such as
// StartSignEncrypt() (for the ASCII encoding options)
// and StartDecryptVerify() (for the ASCII decoding options).
// Options set via these functions will apply for the duration of the
// EntFile object, and revert back to the defaults when a new EntFile object
// is created.
// These options are in addition to those explicitly set using the structures
// FileSecureOptions, FileUnsecureOptions, and SecurityOptions.
//
// These functions apply to ASCII encoding of data for buffer based
// signing and/or encrypting of data. The default is no ASCII encoding.
	EXPT32 void EXPT SetBufferASCIIencoding(BOOL ASCIIencodingOn);
	EXPT32 BOOL EXPT QueryBufferASCIIencoding(void);

// These functions apply to decoding of ASCII encoded data for buffer based
// decryption and/or verification of data. The default is no ASCII decoding.
	EXPT32 void EXPT SetBufferASCIIdecoding(BOOL ASCIIdecodingOn);
	EXPT32 BOOL EXPT QueryBufferASCIIdecoding(void);

// Enable timestamping mode, TRUE = timestamp, FALSE = no timestamp.
// Call before StartEncryptSign().
	EXPT32 void EXPT SetBufferTimestamping(const BOOL TimestampFlag);
	EXPT32 BOOL EXPT QueryBufferTimestamping(void);

// Enable timestamp verification, TRUE = verify, FALSE = no verification.
// Call before StartDecryptVerify().
	EXPT32 void EXPT SetBufferTimestampVerify(const BOOL TimestampVerifyFlag);
	EXPT32 BOOL EXPT QueryBufferTimestampVerify(void);


//
// Utility Functions
//
// GenerateRandomData fills the provided BinData buffer with length BYTES of
// random data. This function uses data from the current login context to
// provide additional entropy.
	EXPT32 EntLog EXPT GenerateRandomData(BinData& buffer, const UINT32 length);

// EnableCaching allows the application to enable or disable the use of
// local caches for certificates and revocation lists. If enabled, then if local
// copies of certificate or revocation list information is available, and valid,
// it will be used. If disabled, the caches will be ignored and the Toolkit will
// try to get the required information from the Directory.
// NOTE: Caching is ENABLED by default when you create a new EntFile object, so
// this function would typically be used to turn off caching, and then possibly
// re-enable it later on.
// The reserved parameter may be used in future releases to provide finer control
// of individual caches.

	EXPT32 EntLog EXPT EnableCaching(const BOOL enable, const void* reserved);


// GetCacheHandle returns a reference handle to the specified cache (CT_ALL
// cannot be specified). The cache can then be manipulated via the
// EntCertificate class functions. The cacheHandle pointer should NOT be
// deleted, as it refers to internal storage which is managed as part of the
// current login context.
	EXPT32 EntLog EXPT GetCacheHandle(const CACHE_TYPE cacheType,
										EntCertificateList** cacheHandle);

// CacheOperation allows a variety of operations to be specified on an
// individual cache, or all caches.
    EXPT32 EntLog EXPT CacheOperation(const CACHE_TYPE cacheType,
										const CACHE_OPERATION cacheOp);

//
// Password functions
//
// ValidatePassword returns 0 if the supplied password matches that
// of the current user.
//
	EXPT32 EntLog EXPT ValidatePassword( const GString ExistingPassword );
//
// ChangePassword validates the supplied oldPassword, and if valid,
// changes the user password to newPassword.
//
// With Single Login, call the version of this function that takes no parameters.
// ELI (the Entrust Login Interface) will take over from there.
//
	EXPT32 EntLog EXPT ChangePassword(	const GString oldPassword,
										const GString newPassword );
//
// If using Single Login, use this version of ChangePassword to bring up the user interface.
//
	EXPT32 EntLog EXPT ChangePassword();

//
// CheckPassword checks the provided string against the password rules.
// Note that this does not check if the provided string is the password of the
// current user - use ValidatePassword() for that.
//
	EXPT32 EntLog CheckPassword(const GString& newPass);

//
// Return set of password rules that apply to current user
//
	EXPT32 EntLog GetPasswordRules(EntrustPassRules& rules);

//
// Entrust Archive Functions
//
// These functions are similar to the file secure/unsecure functions above,
// except they can be used to generate and process Entrust archive files, which
// contain secured versions of one or more plaintext files.
//
// Compatibility between archive and file functions:
// - Using the file secure functions SetFileSignEncrypt()/DoFileSignEncrypt() is
//   equivalent to using SetArchiveSignEncrypt()/DoArchiveSignEncrypt() on an
//   input file list with one entry.
// - Using the file unsecure functions
//   GetFileInfo()/SetFileDecryptVerify()/DoFileDecryptVerify() is equivalent
//   to using LoadArchive()/GetArchiveInfo()/
//   SetArchiveDecryptVerify()/DoArchiveDecryptVerify() on an
//   Entrust archive with one encapsulated file. If the single file functions are used
//   on an Entrust archive encapsulating multiple files, only the first encapsulated
//   file will be processed.
//
//  In general it is recommended to use the archive functions. The single file
//  processing functions are retained for convenience and backwards compatibility.
//
// SetArchiveSignEncrypt and DoArchiveSignEncrypt will digitally sign and/or encrypt
// an input file list and generate a single secured output file which is compatible
// with the Entrust/Client file format.
// If the files are to be encrypted, the recipients list should contain the list
// of intended recipients before this function is called. Recipients who do not
// have valid certificates will be moved to the recipientsWithoutCertificates list.
//
// The secOp, and fileOptions parameters provided will be applied
// to each plaintext file in inputFileList, and outputFile is the specification
// for the output archive file.
// NOTE: archiveOptions.fileOptions.deletePlaintextAfter is treated as FALSE,
// even if set to TRUE, to avoid accidental destruction of input files. Use
// the SecureDeleteFile() function to remove undesired files after the archive
// has been generated.
//

EXPT32 EntLog EXPT SetArchiveSignEncrypt(const ArchiveOptions& archiveOptions,
  										 const EntFileList& inputFileList,
										 const FileSpecification& outputFile,
										 EntrustNameList& recipients,
    									 EntrustNameList& recipientsWithoutCertificates );

//
// DoArchiveSignEncrypt, if the proceed flag is FALSE, will cancel processing of the
// file operation(s) specified by the previous call to SetArchiveSignEncrypt.
// If proceed is TRUE, then a portion of the current input file
// will be processed, and a status EntLog will be returned.
// Parameter currentFileIndex is used to indicate which file (of an input file
// list) is currently being processed.
// The percentOfFileDone return parameter indicates what percentage of the current file
// has been processed so far.
// Parameter totalPercentDone is used to indicate how much of the total job
// (processing all input files) has been completed.
//

EXPT32 EntLog EXPT DoArchiveSignEncrypt (	const BOOL proceed,
											INT16& currentFileIndex,
											INT16& percentOfFileDone,
											INT16& totalPercentDone );

//
// LoadArchive specifies an existing Entrust archive file to process.
// Parameter archiveFile specifies the input Entrust archive file, and
// numberOfFilesInArchive returns the number of files encapsulated in the
// archive.
//
EXPT32 EntLog EXPT LoadArchive 	(	const FileSpecification& archiveFile,
									INT16& numberOfFilesInArchive );

//
// GetArchiveInfo returns information about a secured file
// encapsulated in an Entrust archive. It returns:
// - the name of the encapsulated file
// - the byte length of the encapsulated file.
// The input parameter suppressPathInfo, if TRUE, will cause any
// path information which may be present in the fileName to be
// stripped off.
//
EXPT32 EntLog EXPT GetArchiveInfo (	const SYSINT index,
									FileSpecification& fileName,
									INT32& fileLength,
									BOOL suppressPathInfo = TRUE);

//
// SetArchiveInfo allows you to prevent a specified encapsulated file
// from being extracted from the archive when it is processed. By default,
// all files in the archive will be processed.
//
EXPT32 EntLog EXPT SetArchiveInfo (	const SYSINT index,
								   	const BOOL excludeThisFile );
//
// SetArchiveDecryptVerify begins the process of extracting the encapsulated
// files from the archive, and should be followed by multiple calls to
// DoArchiveSignEncrypt.
// writeOutput specifies if the output files should be written.
// outputDir specifies a destination directory for the output files.
// usePathInfo, if TRUE, will cause output files to be written using the
// path information (if any) stored with them, relative to outputDir.
// If usePathInfo is FALSE, all output files will be written to outputDir.
// overwriteFiles determines if output files will be written over
// existing files of the same name in the destination directory.
// numFilesToProcess returns the number of encapsulated files which will
// be processed.
// The saveVerificationCertificates flag, if TRUE, will save the
// verification certificates of any encapsulated files which are signed,
// so that they can be retrieved during a subsequent call to GetArchiveResults().
//

EXPT32 EntLog EXPT SetArchiveDecryptVerify (const BOOL writeOutput,
											const FileSpecification& outputDir,
											const BOOL usePathInfo,
											const BOOL overwriteFiles,
											const BOOL saveVerificationCertificates,
											INT16& numFilesToProcess);


//
// DoArchiveDecryptVerify performs the actual processing (decrypting/verifying) of
// the subset of encapsulated files within an archive selected during previous
// calls to LoadArchive and SetArchiveInfo.
// If the proceed flag is FALSE, it will cancel processing of the archive.
// If proceed is TRUE, then a portion of one of the encapsulated files
// will be processed, and a status EntLog will be returned.
// Parameter currentFileIndex is used to indicate which of the selected
// encapsulated files is currently being processed.
// The percentOfFileDone return parameter indicates what percentage of the current
// encapsulated file has been processed so far.
// Parameter totalPercentDone is used to indicate how much of the total job
// (processing of all selected encapsulated files) has been completed.
//
EXPT32 EntLog EXPT DoArchiveDecryptVerify (	const BOOL proceed,
											INT16& currentFileIndex,
											INT16& percentOfFileDone,
											INT16& totalPercentDone );

//
// GetArchiveResults returns information about a secured file
// which was extracted from an Entrust archive.
// It should be called after DoArchiveDecryptVerify() returns a
// completion indication.
// It returns:
// - the name of the encapsulated file (converted as required to
//   conform to local operating system conventions).
// - the headerType indicating if and how the file was secured,
// - information about the signer of the file (if applicable)
// - status of the decrypt and/or verification operations performed
//   on the encapsulated file, including the operating system where the
//   archive was created.
// - the signature verification public key certificate of the originator,
//   if the file was signed (optional).
//
EXPT32 EntLog EXPT GetArchiveResults (	const SYSINT index,
										FileSpecification& fileName,
										HEADER_TYPE& headerType,
										CertificateData& certifData,
										DecryptVerifyStatus& status,
										EntCertificate* certif = NULL);
//
// GetArchiveResults returns information about a secured file
// which was extracted from an Entrust archive.
// It should be called after DoArchiveDecryptVerify() returns a
// completion indication.
// It returns:
// - the name of the encapsulated file (converted as required to
//   conform to local operating system conventions).
// - the archiveInfo indicating if and how the file was secured and
//	 the alg used.
// - information about the signer of the file (if applicable)
// - status of the decrypt and/or verification operations performed
//   on the encapsulated file, including the operating system where the
//   archive was created.
// - the signature verification public key certificate of the originator,
//   if the file was signed (optional).
//
EXPT32 EntLog EXPT GetArchiveResults (	const SYSINT index,
										FileSpecification& fileName,
										ARCHIVE_INFO& archiveInfo,
										CertificateData& certifData,
										DecryptVerifyStatus& status,
										EntCertificate* certif = NULL);
//
// GetArchiveEncryptInfo returns information about an Entrust archive without
// decrypting the archive.  It returns the algorithms used to sign and/or encrypt
// the archive via an ARCHIVE_INFO structure and returns the OS the archive was
// encrypted/signed on and information about the signer, if any.
//
EXPT32 EntLog EXPT GetArchiveEncryptInfo( const FileSpecification& inputFile,
						                  ARCHIVE_INFO& outArchiveInfo,
									      TimestampInfo& timestampInfo,
										  EntCertificate &certif,
				    					  CertificateData& certifData,
										  BOOL& timestamped);
//
// GetArchiveTimestampInfo returns information about a secured file
// which was extracted from an Entrust archive.
// It can be called after DoArchiveDecryptVerify() or DoArchiveSignEncrypt()
// returns a completion indication.
// It returns:
// - the timestamp server certificate
// - the timestamp server CA certificate
// - the status of the timestamp operation
// - the hash algorithm used
// - date of the archive was timestamped
//
EXPT32 EntLog EXPT GetArchiveTimestampInfo(	const SYSINT	index,
											TimestampInfo&	timestampInfo);

//
// File Based Functions
//
// SetFileSignEncrypt and DoFileSignEncrypt will digitally sign and/or encrypt
// an input file and generate a secured output file which is compatible with the
// Entrust/Client file format.
// If the file is to be encrypted, the recipients list should contain the list
// of intended recipients before this function is called. Recipients who do not
// have valid certificates will be moved to the recipientsWithoutCertificates list.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** USE THE ARCHIVE FUNCTIONS INSTEAD (SetArchiveSignEncrypt)
//

EXPT32 EntLog EXPT SetFileSignEncrypt(	const SECURITY_OPERATION secOp,
  										const FileSecureOptions& fileOptions,
  										const FileSpecification& inputFile,
										const FileSpecification& outputFile,
										EntrustNameList& recipients,
    									EntrustNameList& recipientsWithoutCertificates );

//
// DoFileSignEncrypt, if the proceed flag is FALSE, will cancel processing of the
// file operation specified by the previous call to SetFileSignEncrypt.
// If proceed is TRUE, then a portion of the current input file
// will be processed, and a status EntLog will be returned.
// The percentOfFileDone return parameter indicates what percentage of the current file
// has been processed so far.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** USE THE ARCHIVE FUNCTIONS INSTEAD (DoArchiveSignEncrypt)
//
EXPT32 EntLog EXPT DoFileSignEncrypt ( 	const BOOL proceed,
										INT16& percentOfFileDone );

//
// GetFileInfo returns information about an Entrust secured file. It returns:
// - the headerType indicating if and how the file was secured,
// - information about the signer of the file (if applicable)
// - the "native" name of the source file which was secured,
// - a "local" version of the source file name, which is a converted
//   version of the native file name, intended to
//   help resolve cases where the source and destination systems
//   have different file naming conventions,
// - the type of operating system where the file was generated
//
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** USE THE ARCHIVE FUNCTIONS INSTEAD (GetArchiveInfo)
EXPT32 EntLog EXPT GetFileInfo ( 	const FileSpecification& inputFile,
							    	HEADER_TYPE& headerType,
							    	CertificateData& certifData,
									FileSpecification& nativeFileName,
									FileSpecification& localFileName,
									SOURCE_OS& sourceOS);

//
// SetFileDecryptVerify and DoFileDecryptVerify will take an Entrust/Client compatible
// secured file, decrypt and verify it (if the current user is authorized to do so),
// and write it to the file specified by outputFile.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** USE THE ARCHIVE FUNCTIONS INSTEAD (LoadArchive, SetArchiveDecryptVerify)
//
EXPT32 EntLog EXPT SetFileDecryptVerify(const FileUnSecureOptions& fileOptions,
  										const FileSpecification& inputFile,
										const FileSpecification& outputFile );

//
// DoFileDecryptVerify, if the proceed flag is FALSE, will cancel processing
// of the file operation specified by the previous call to SetFileDecryptVerify.
// If proceed is TRUE, then a portion of the input file
// will be processed, and a status EntLog will be returned.
// The percentDone return parameter indicates what percentage of the file has been
// processed so far.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** USE THE ARCHIVE FUNCTIONS INSTEAD (DoArchiveDecryptVerify, GetArchiveResults)
//
EXPT32 EntLog EXPT DoFileDecryptVerify (const BOOL proceed,
										INT16& percentDone );
//
// SecureDeleteFile securely erases the specified file by overwriting it with
// random encrypted data.
// NOTE: this function is not available on Macintosh.
//
#if !defined(MACOS)
EXPT32 EntLog EXPT SecureDeleteFile ( const FileSpecification& inputFile );
#endif

//
// Recipient List Service Functions
//
EXPT32 EntLog EXPT CreateRecipListService( EntRListService** ppRLSrv );

EXPT32 EntLog EXPT DestroyRecipListService( EntRListService* pRLSrv );
//
// Group Functions
//
// Groups provide a shorthand way to refer to a set of recipients. The Toolkit
// provides access to the same group handling mechanisms which the Entrust/Client
// uses. Upon login, previously defined groups (whether created via the Client
// or Toolkit) are loaded as part of the user context.
//
// GetNumberOfGroups returns the current number of groups defined.
//
EXPT32 INT16 EXPT GetNumberOfGroups( void );
//
// GetGroupName gets the name of the indexed group.
//
EXPT32 EntLog EXPT GetGroupName(const SYSINT index,
								GString& groupName);

//
// GetGroupIndex gets the index of the named group.
//
EXPT32 EntLog EXPT GetGroupIndex( 	const GString& groupName,
									SYSINT& index );
//
// GetGroup appends the members of the specified group to the
// supplied EntrustNameList.
// The groupOptions parameter indicates if the group is shared
// or not.
//
EXPT32 EntLog EXPT GetGroup(const GString& groupName,
							EntrustNameList& nameList,
							GroupOptions& groupOptions );
//
// AddGroup saves the provided EntrustNameList in the
// internally maintained group list.
// If a non-shared group with the specified name already exists,
// its contents are replaced
// with the provided EntrustNameList's contents.
// If a shared group with the specified name already exists,
// no action is taken, and an error code is returned.
// Return parameter indexUsed indicates where the group was placed
// in the group list.
// The parameter groupOptions is ignored, but is retained for
// backwards compatibility.
// Note that a group name can be at most MAX_GROUP_NAME_SIZE
// characters long (defined in ENTBDEFS.H).
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
//
EXPT32 EntLog EXPT AddGroup(const GString& groupName,
							EntrustNameList& newGroup,
							const GroupOptions& groupOptions,
							SYSINT& indexUsed );

//
// RemoveGroup removes the specified group from the group list.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
//
EXPT32 EntLog EXPT RemoveGroup( GString& groupName );

//
// WriteGroupsToFile saves the current group list to the user's group file.
// Note that this is done automatically when the user logs out.
// *** THIS FUNCTION WILL BE REMOVED FROM THE NEXT RELEASE.
// *** ONLY READ ACCESS WILL BE PROVIDED TO CLIENT RECIPIENT GROUPS
//
EXPT32 EntLog EXPT WriteGroupsToFile( void );

// End of Group Functions

// Protect and Unprotect Functions: these functions perform PKCS#7 formatting or
// unformatting on a buffer or file basis.

// Buffer based security operation functions
// StartProtect is used to start a data protection operation.
// recipients specifies a list of recipients for encryption (if encryption is
// requested via protectOptions).
// recipientsWithoutCertificates should be supplied as an empty list. It will be
// added to with names from recipients who for some reason could not be used
// as an encryption recipient (for example, their encryption certificate could not
// be found or failed validation).
EXPT32 EntLog EXPT StartProtect(const PROTECT_OPTIONS& protectOptions,
								EntrustNameList& recipients,
								EntrustNameList& recipientsWithoutCertificates);

// Once StartProtect is called, subsequent calls to Protect
// are made to actually input and process the plaintext data.
// Note that no output data is provided. All data is buffered by the
// Toolkit and returned to the application via the EndProtect function.
EXPT32 EntLog EXPT Protect(	const BinData &in);

// Once all input data has been supplied to Protect, the operation is completed by
// One or more calls to EndProtect.
// ETEndProtect will return one of three types of return codes...
// 1) ENT_CONTINUE_NEEDED: this means that EndProtect must be called again to retrieve
// more data.
// 2) ENT_OK: EndProtect does not have to be called again, but may have returned
// residual data.
// 3) anything else: an error has occured, as indicated by the value of the returned
//    EntLog.
//
// Output data may be returned via the csHeader and outBuffer parameters.
// If the csHeader is non zero length, its contents must be
// written out to the output file or device first.
// Next, if outBuffer is non zero length, its contents
// can be written out to the output file or device.
EXPT32 EntLog EXPT EndProtect(BinData &csHeader, BinData &out );

//
// StartUnprotect is used to start an unprotect sequence.
// An initial buffer of protected data can be supplied via startSeq.
// Output may be returned via the partialOut parameter, depending on
// type of data protection which had been applied to the input data.
// Note: if the input data is clear signed, ALL of the signed
// info header must be included within the startSeq buffer.
EXPT32 EntLog EXPT StartUnprotect(const BinData &startSeq, BinData &partialOut);

//
// Unprotect continues the unprotect sequence started by StartUnprotect.
// A buffer of protected data is supplied via the in buffer.
// Output may be returned via the out buffer parameter.
//
EXPT32 EntLog EXPT Unprotect(const BinData &in, BinData &out);

//
// Once all input data has been supplied to Unprotect, the operation is completed by
// one or more calls to EndUnprotect.
// EndUnprotect will return one of three types of return codes...
// 1) ENT_CONTINUE_NEEDED: this means that EndUnprotect must be called again to retrieve
// more data.
// 2) ENT_OK: EndUnprotect does not have to be called again, but may have returned
// residual data. The unprotectInfo parameter will point to information about the
// data which was unprotected.
// 3) anything else: an error has occured, as indicated by the value of the returned
//    EntLog.
// Note that certificates included with the message will be stored in the
// certList parameter for further examination. See ENTCERT.H for more
// information on examining certificate information.
//
EXPT32 EntLog EXPT EndUnprotect(BinData &out,
								UNPROTECT_INFO& unprotectInfo,
								EntCertificateList& certList);

//
// FileProtect takes a plaintext file specified by inFile, and a set of
// protectOptions, and a list of encryption recipients (if required)
// and generates a protected output file specified by outFile.
// Any recipients who did not have valid encryption certificates are moved
// to the recipientsWithoutCertificates list.
//
EXPT32 EntLog EXPT FileProtect(	const PROTECT_OPTIONS& protectOptions,
								EntrustNameList& recipients,
								EntrustNameList& recipientsWithoutCertificates,
								const char* inFile,
								const char* outFile);

//
// FileUnprotect takes a protected file specified by inFile,
// and generates an unprotected output file specified by outFile.
// Information about the unprotect process is provided via unprotectInfo.
// Note that certificates included with the message will be stored in the
// certList parameter for further examination. See ENTCERT.H for more
// information on examining certificate information.
//
EXPT32 EntLog EXPT FileUnprotect(	UNPROTECT_INFO& unprotInfo,
									const char* inFile,
									const char* outFile,
									EntCertificateList& certList );
//
// FileUnprotect takes a protected file specified by inFile,
// and generates an unprotected output file specified by outFile.
// Information about the unprotect process is provided via unprotectInfo,
// and any virus information is supplied via the vOutput parameter.
// Note that certificates included with the message will be stored in the
// certList parameter for further examination. See ENTCERT.H for more
// information on examining certificate information.
//
EXPT32 EntLog EXPT FileUnprotect(	UNPROTECT_INFO& unprotInfo,
									const char* inFile,
									const char* outFile,
									EntCertificateList& certList,
									VirusDetectInfo& vOutput);
//
// This version of "FileUnprotect" is used for clear-signed messages
// where the PKCS7 token and the plain text are in different files.
//
// FileUnprotect takes a PKCS7 token file specified by tknFile,
// a file that contains plain text that corresponds the PKCS7 token file,
// and generates an unprotected output file specified by outFile.
// Information about the unprotect process is provided via unprotectInfo
// and any virus information is supplied via the vOutput parameter.
// Note that certificates included with the message will be stored in the
// certList parameter for further examination. See ENTCERT.H for more
// information on examining certificate information.
//
EXPT32 EntLog EXPT FileUnprotect(	UNPROTECT_INFO& unprotInfo,
									const char* inFile,
									const char* outFile,
									const char* tknFile,
									EntCertificateList& certList,
									VirusDetectInfo& vOutput);
//
// GetFilePKCS7Info takes a protected file specified by file and returns
// information on how the file was protected via unprotInfo.  The protected
// file is not unprotected.
//
EXPT32 EntLog EXPT GetPKCS7FileInfo( UNPROTECT_INFO& unprotInfo,
											  const char* inFile,
											  EntCertificateList& certList );
//
// GetFilePKCS7Info takes a PKCS7 token file specified by tknFile, a file that contains
// plain text that corresponds to the PKCS7 token file, and retrieves information on
// how the file was protected.  The specified protected file is not unprotected.
//
EXPT32 EntLog EXPT GetPKCS7FileInfo( UNPROTECT_INFO& unprotInfo,
											  const char* inFile,
											  const char* tknFile,
											  EntCertificateList& certList);
//
// CreatePKCS7CertOnlyMessage creates a PKCS#7 certificate only message,
// with the certificates specified by the protectFlags parameter.
//
EXPT32 EntLog EXPT CreatePKCS7CertOnlyMessage(
								const PROTECT_FLAGS protectFlags,
								BinData& messageOut);

//
// This method will return the raw digest from the last PKCS7 operation.
//
EXPT32 EntLog GetMessageDigest(BinData& digest);

//
// This method will return the length of the verification key from the last verification operation.
//
EXPT32 EntLog GetSenderVerificationKeyLength(UINT32 &length);

// SSL sign methods.
// SSL_StartSign takes no parameters. It is used to start a SSL signing operation.
EXPT32 EntLog SSL_StartSign( void );

// SSL_UpdateSign accepts four BinData parameters.
// - sha_inBuffer:
// - md_inBuffer:
// - sha_outBuffer:
// - md_outBuffer:
EXPT32 EntLog SSL_UpdateSign( const BinData& sha_inBuffer,
							  const BinData& md_inBuffer );

// SSL_EndSign accepts three parameters:
// - sha_inBuffer:
// - md_inBuffer:
// - outBuffer:
EXPT32 EntLog SSL_EndSign( BinData& outBuffer );

// SSL Verification methods.
// SSL_StartVerify is used to start off the Verification procedure
// for a SSL signed message.  The [verifyCert] parameter is the
// verification Certificate for the signature in the [inSig] parameter.
EXPT32 EntLog SSL_StartVerify( EntCertificate& verifyCert,
							   const BinData& inSig );

// SSL_UpdateVerify accepts four BinData parameters.
// - sha_inBuffer:
// - md_inBuffer:
// - sha_outBuffer:
// - md_outBuffer:
EXPT32 EntLog SSL_UpdateVerify( const BinData& sha_inBuffer,
								const BinData& md_inBuffer );

// SSL_EndVerify accepts three parameters:
// - sha_inBuffer:
// - md_inBuffer:
// - alg:
EXPT32 EntLog SSL_EndVerify( EntSSL_Alg& alg );

//
// Group Key Functions
//
// importProtectedGroupKeys - takes a protected group key file (generated by the
// exportProtectedGroupKeys function), and, if the current user was on the recipient
// list for the export, adds the decryption keys to the current user's group key list.
// The friendly name for the group will be returned via the groupName parameter, and
// the distinguished name (DN) is also provided via the groupDN parameter.
// The encryption certificate corresponding to the most recent decryption key is returned
// for informational purposes.
EXPT32 EntLog EXPT ImportProtectedGroupKeys(const char* fileName,
											GString& groupName,
											GString& groupDN,
											EntCertificate& matchingCert);

// deleteGroupKeys - delete the decryption keys, associated with a group (specified
// by friendly name) from the user's group key list.
EXPT32 EntLog EXPT DeleteGroupKeys(const GString& groupName);

// getNumberOfGroupKeySets - The number of groups for which the current user has group keys.
// They are referred to as group key "sets" since a given group may have more than 1
// key associated with it.
EXPT32 INT32 EXPT GetNumberOfGroupKeySets(void);

// getGroupKeyInfo - This function returns the friendly and distinguished names of
// the specified group with which a group key is associated.
// The number of keys associated with a specified group is also returned (since
// due to key updates, there may be more than one decryption key associated with
// a specific group).
EXPT32 EntLog EXPT GetGroupKeyInfo(const INT32 index,
								   GString& groupName,
								   GString& groupDN,
								   INT32&	numKeysForGroup);

//
// Return the name and absolute path of the profile currently being used.
//
EXPT32 EntLog QueryCurrentProfile( GString& profile );

//
// Return the name and absolute path of the ini file currently being used.
//
EXPT32 EntLog QueryCurrentIniFile( GString& profile );

//
// Returns TRUE if the user is connected to the directory, FALSE otherwise.
//
EXPT32 BOOL QueryConnectStatus( );

//
// Indicates if the user has as a DSA signing key.
//
EXPT32 EntLog IsDSAUser(BOOL& DSAUser);

//
// Indicates if the user has as a EC DSA signing key.
//
EXPT32 EntLog IsECDSAUser(BOOL& ECDSAUser);

//
// Indicates if the user is logged on through single sign-on.
//
EXPT32 EntLog IsLoggedIn(BOOL& loggedIn);

//
// If <blockUntilLogoutRequested> is TRUE, the call will block
// until a logout is requested and then return TRUE.  Otherwise
// it will return TRUE if a Logout was already requested,
// FALSE otherwise.
//
EXPT32 BOOL IsLogoutRequested(BOOL blockUntilLogoutRequested);

//
// Getting and setting profile options
//
EXPT32 EntLog EXPT GetProfileOption(const ProfileOptionID poid, GString& value);

EXPT32 EntLog EXPT GetProfileOption(const ProfileOptionID poid, UINT32& valueNumeric);

EXPT32 EntLog EXPT SetProfileOption(const ProfileOptionID poid, const UINT32& valueNumeric);

EXPT32 EntLog EXPT SetProfileOption(const ProfileOptionID poid, const GString& value);

EXPT32 EntLog EXPT ShowProfileOptions();

EXPT32 EntLog EXPT ShowProfileOptions( const GString& szPlugin, UINT32 uPage, UINT32 uFlags);

//
// Getting and setting application options
//
EXPT32 EntLog EXPT GetAppOption( const GString& szSection, const GString szKey,
								 BinData& bdValue, UINT32 uFlags );
EXPT32 EntLog EXPT SetAppOption( const GString& szSection, const GString szKey,
							     const BinData& bdValue, UINT32 uFlags );

// GetApplicationContext is used for internal initialization of
// EntCertificate objects, and it not required by applications.
EXPT32 AppContext* EXPT GetApplicationContext() const;

EXPT32 void EXPT GetProfilePath(GString &path);
EXPT32 int EXPT GetSingleLoginMode(void);

// Disable the built-in inactivity timeout.
// Call with a 'FALSE' parameter to re-enable.
EXPT32 EntLog EXPT DisableTimeout(BOOL disable = TRUE);

// Check whether timestamping is available
// (checks to see if there are any timestamp servers defined)
EXPT32 BOOL EXPT QueryTimestampAvailable(void);

// Force a reauthentication if timed out and allowed.
EXPT32 EntLog EXPT Reauthenticate( void );


// This function should be called to turn on/off the Windows message pump when waiting
// occurs within the toolkit. By default, the pump is enabled.  This behaviour is correct
// unless the application implements its own message pump, or if processing messages
// on behalf of the application will generate further blocking (and thus produce a
// dead lock). To disable the message pump, call this function with FALSE.
EXPT32 static void EnableMsgPumpOnWait(BOOL enable_);

// Given the input OID, return the ASN.1 encoded value from the policy cert.
// Returns COMM_ATTCERT_ATTRIBUTE_NOT_FOUND if the policy cert does not contain this OID.
// Returns ENT_INFO_MISSING if the policy cert contains this OID but no value for it.
EXPT32 EntLog GetPolicyCertValue(const GString &oid, BinData &encodedValue);

#if defined(_WIN32)
//
// SMIME Service Functions
//
EXPT32 EntLog CreateSMIMEService(EntSMIMEService** ppSMIMESrv);
EXPT32 EntLog DestroySMIMEService(EntSMIMEService* pSMIMESrv);
#endif

// Data members of EntFile

	CliObject*			m_CliObject;


private:

// Check whether use of input hash algorithm is permitted for this user
EXPT32 EntLog AuthPermitsHashAlg( const SIGNING_QUALITY algorithm );

	// Get/Set methods
#if defined(ENTAPI)
	EntrustFileSMIME*&	GetEntrustFileSMIME();
	EntrustFileSecAPI*&	GetEntrustFileSecAPI();
	MatchedNameList*& 	GetMatchedNameList();
	CliFileEncryptor*&	GetEncryptor();
	CliFileDecryptor*&	GetDecryptor();
	INT16&				GetOperationalState();
	INT16&				GetFileEncryptState();
	INT16&				GetFileDecryptState();
	SecurityOptions& 	GetSecurityOptionsInternal();
	GString&			GetSearchBase();
	GString&			GetEntrustIni();
	EntrustParameters&  GetParameters();
	GString&			GetProfile();
	IdentityDeviceMode&	GetIdentityFlag();
	BOOL&				GetToken();

	INT32&				GetScannerUsed();
	EntLog&				ConstructorError();
	AppContext&			getAppctx();
	LoginContext*&	    		getLoginCxt();
	EntLog				AuthPermitsSymmAlg( const ENCRYPTION_ALGORITHM algorithm );
	EntLog				InternalChangePassword(	const GString oldPassword,
								const GString newPassword );

	void SetEntrustFile(EntrustFile*);
	void SetEntrustFileSMIME(EntrustFileSMIME*);
	void SetEntrustFileSecAPI(EntrustFileSecAPI*);
	void SetMatchedNameList(MatchedNameList*);
	void SetEncryptor(CliFileEncryptor*);
	void SetDecryptor(CliFileDecryptor*);
	void SetOperationalState(INT16&);
	void SetFileEncryptState(INT16&);
	void SetFileDecryptState(INT16&);
	void SetSecurityOptionsInternal(SecurityOptions&);
	void SetSearchBase(GString&);
	void SetEntrustIni(GString&);
	void SetProfile(GString&);
	void setConstructorError(EntLog&);
	void setAppctx(AppContext&);
	void setLoginCxt(LoginContext*);
	void SetIdentityFlag(IdentityDeviceMode&);
	void SetToken(BOOL);
#ifdef _MULTITHREAD_
	EntrustMutex&		GetCliObjMx();
	EntrustMutex&		GetGeneralMx();
	void				SetKeyId(TSDKEY val);
	TLS_Flags*&			GetCtx();
	TSDKEY&				GetKeyId();
#else
	TKctx*&				GetCtx();
	void*				GetCliObjMx();
	void*				GetGeneralMx();
#endif

#endif // ENTAPI

	// Never use these directly.  Use the Get methods.
	EntrustFile*		m_EntrustFile;
	MatchedNameList* 	m_MatchedNameList;
	CliFileEncryptor*	m_encryptor;
	CliFileDecryptor*	m_decryptor;
	INT16				m_OperationalState;
	INT16				m_FileEncryptState;
	INT16				m_FileDecryptState;
	SecurityOptions 	m_SecurityOptions;
	GString				m_SearchBase;
	GString				m_EntrustIni;
	GString				m_Profile;
	EntLog				m_ConstructorError;
	TKctx*				m_ctx;

	enum SecurityServices {
		// These are the services you can request.  The first four go together
		// since the crypto required for any of them provides all of them.
		SMIM_CONFIDENTIALITY			= 0x01,
		SMIM_INTEGRITY					= 0x02,
		SMIM_DIGEST						= 0x04,
		SMIM_MAX_SERVICE				= SMIM_DIGEST
	};


	EntLog				GroupLoad();

	EntLog CommonLogin(	const GString& UserProfile,
						const GString& Password,
						const GString& EntrustIniFile,
						const BOOL noX500Dir = FALSE );

	EntLog ThreadLogin(void);	// Multithreaded env only

	EntLog CheckIdentity(const GString& entrustIniFile,
						 BOOL& changePassword,
						 GString& ProfileName,
						 GString& OldPasswordOut,
						 GString& NewPasswordOut,
						 int& IdentityMode);
	EntLog GetSymmAlgorithm(const ENCRYPTION_ALGORITHM SpecAlgorithm,
		ENCRYPTION_ALGORITHM &ActualAlgorithm,
		GString &AlgorithmString);

	EntLog SetProtectFlags(const PROTECT_FLAGS protFlags);

	EntLog SetIduInformation(const char* idu_type);

	EntLog GetUnprotectServicesInfo(UNPROTECT_INFO& unprotInfo);

	EntLog GetReceivedServices(int&	services, int&	size);

	EntLog SetEncryptionQuality(const ENCRYPTION_ALGORITHM encryptionQuality);

	EntLog SetSigningQuality(const SIGNING_QUALITY signingQuality);

	EntLog StringToSignAlg( const GString& inStr, SIGNING_QUALITY& signType );

	EntLog GetEncryptionQuality(ENCRYPTION_ALGORITHM& encryptionQuality);

	EntLog GetSigningInfo(SIGNING_QUALITY& signingQuality,
							time_t& signingTime,
							GString& supportedAlgorithms);

	EntLog GetDigestInfo(SIGNING_QUALITY& signingQuality);

	EntLog MakeWarning( EntLog );

	EntLog SetRevocationReason( INT16 );

	bool NeedsFileName( EntLog rc );

	void destroyContext();

	// ELI stuff
	EXPT32 EntLog RegisterApplication(const GString& applPath);
	EXPT32 EntLog CheckSLARegistry(const GString& applPath);

	EXPT32 EntLog CheckPassword(const GString &newPW, const GString& oldPW);

	EXPT32 EntLog ChangeIdentityPassword(GString& oldPW, GString& newPW);

	EXPT32 EntFile(const GString& UserProfile,
				GString& Password,
				const GString& EntrustIniFile,
				const BOOL noX500Dir,
				const UINT32 eliMode,
				const GString* applPath = NULL);

	// static functions

	EXPT32 static EntLog POIDtoText( ProfileOptionID id, GString& str );

protected:

	ET_Key*&			GetMACKey();
	EntLog				GetEntrustFile(EntrustFile*& outFile);
	EntrustFile*&		GetEntrustFile();
	EntLog				CheckTLS(void);		// Multithreaded env only
};


//
// Single login functions that don't require context
//
EXPT32 EntLog StartEntrustLoginInterface();
EXPT32 EntLog AboutEntrustLoginInterface();
EXPT32 EntLog EntrustLoginInterfaceControlPanel();
EXPT32 EntLog WhoIsLoggedIn(GString* wholist, int& numberLoggedIn);
EXPT32 EntLog EntrustLoginInterfaceTimeoutAll();
EXPT32 void EntrustLoginInterfaceForceDialog();

//
// IsEntrustFile returns TRUE if the specified file is in Entrust client file
// format (and is therefore a candidate for decrypting/verifying via
// EntFile::SetFileDecryptVerify() ), and FALSE otherwise.
//
EXPT32 BOOL EXPT IsEntrustFile ( const FileSpecification& inputFile );
//
// QueryClientType takes a path to the Entrust INI file and returns
// the client type.
//
EXPT32 CLIENT_TYPE EXPT QueryClientType( const GString& EntrustIniFile );
//
// EntLogToString converts an EntLog to a string describing the corresponding
// error.
//
EXPT32 const char* EXPT EntLogToString( EntLog log );
//
// QueryEntLogWarning returns TRUE if the supplied EntLog is a warning rather than
// an error. Numerically, the value of a warning is the value of the
// corresponding error - 16000.
//
EXPT32 BOOL EXPT QueryEntLogWarning( EntLog log );


// RemoveWarning function
//
// This function accepts a warning EntLog and returns (also changing the input
// parameter) the error code (see enterr.h) associated with it for
// comparison.
EXPT32 EntLog RemoveWarning( EntLog& warn );

// Compares 2 Distinguished Names.  Returns an error if dn1 or dn2 are invalid DNs,
// and sets the value of "equal" appropriately if dn1 and dn2 are equal.
EXPT32 EntLog EntCompareDistinguishedNames(const GString &dn1, const GString &dn2, BOOL &equal);



#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif

