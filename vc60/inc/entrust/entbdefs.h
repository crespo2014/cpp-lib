/*******************************************************************************
 * entbdefs.h - Header file for the Entrust/File API basic definitions.
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef ENTBDEFS_H
#define ENTBDEFS_H

/*Entrust toolkits are compiled using a structure member alignment of 8*/
#if _MSC_VER >= 1100
#pragma pack(push, 8)
#endif

#include <time.h>

typedef int                     BOOL;

#if (_MSC_VER < 1100) && !defined(unix) && !defined(MACOS)
   typedef int bool;
#endif
#if (defined(solaris) && ((__SUNPRO_CC < 0x500) || (__SUNPRO_CC_COMPAT == 4)))
   typedef int bool;
#endif
#if (defined(aix) && (!defined(__IBMCPP__) || (defined(__IBMCPP__) && (__IBMCPP__ < 400))))
   typedef int bool;
#endif


typedef short int             	INT16;
typedef unsigned short int    	UINT16;

#if (_MSC_VER >= 1200) || (WINVER >= 0x0500)
/*
	// Note: libraries included with MSVC 6.0 do not currently use these types
	// it is possible that a library making explicit use of the MS version of
	// these types may not link correctly once this header is included in an
	// application.
	//
	// If this occurs the app should #undefine INT32 and UINT32 before including
	// that library's headers, then re-define them using the following defines.
*/


	#include <basetsd.h>
	#define INT32 long 
	#define UINT32 unsigned long
	typedef long                  	ETINT32;
	typedef unsigned long         	ETUINT32;
#else

/* for _XBS5_LP64_OFF64 */
	typedef int                	INT32;
	typedef unsigned           	UINT32;
#endif
typedef unsigned char         	BYTE;
typedef unsigned int            UINT;
typedef int                     INT;
typedef INT16                   EntLog;

#if !defined(_os_spec_h) && !defined(_EADMDEFS_H_) && !defined(__ADMTK_H__)

/* SYSINT is used to handle differences on the Mac without
   required IFDEF's wherever 16 bit inputs are used. */
#ifdef MACOS
typedef INT32					SYSINT;
#else
typedef INT16					SYSINT;
#endif

/* define TRUE and FALSE */
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/* maximum buffer size for GString's and BinData's */
#define MAX_ENTBUFFER_SIZE 16384
#define MAX_VIRUSSTR_SIZE  1024

/* 
 * Password rules
 */
typedef struct
{
	UINT32	life;
	UINT32	hist;
	UINT32	len;
	UINT32	sloTimeout;
	struct {
		BOOL nonalpha;
		BOOL upper;
		BOOL lower;
		BOOL digit;
		BOOL okBlanks;
		BOOL ok2repeat;
		BOOL caseIgnore;
		BOOL disableSLO;
	} flags;
} EntrustPassRules;

/* Trusted Services options
 *
 * Note these fields must be set in the ArchiveOptions structure
 * to enable Trusted services.
 *
 *  useReserved = TRUE
 *	reserved1 = service;
 */
typedef enum
{
	TIMESTAMP_SERVICE		= 0x01,
	NOTARY_SERVICE			= 0x02,	/* future service */
	NON_REPUDIATION_SERVICE	= 0x04	/* future service */
} TRUSTED_SERVICES;

typedef enum
{
	THA_MD5,
	THA_SHA1,
	THA_SHA256,
	THA_UNKNOWN
} TIMESTAMP_HASH_ALG;

/* Symmetric cipher options */
/* Note: default strength is the strongest available */
typedef enum
{
	EA_CAST	= 0, /* default strength CAST, CBC mode
				    key lengths are: PEM-based domestic: 64, PEM-based export: 40,
				    PKCS7 domestic: 128, PKCS7 export: 40.
					The 64 bit PEM-based domestic is for interop with Entrust v2.1 */
	EA_DES = 1,      /* DES */
	EA_CAST_128 = 2, /* CBC mode */
	EA_CAST_80 = 3,  /* CBC mode, decryptable by non-domestic recipients */
	EA_CAST_64 = 4,  /* CBC mode, decryptable by non-domestic recipients */
	EA_CAST_40 = 5,  /* CBC mode, decryptable by non-domestic recipients */
	EA_TRIPLE_DES = 6, /* CBC mode, 3 key, encrypt-decrypt-encrypt */
	EA_RC2 = 7,		 /* default strength RC2, CBC mode
 				    key lengths are: PEM-based domestic: 128, PEM-based export: 40,
				    PKCS7 domestic: 128, PKCS7 export: 40. */
	EA_RC2_128 = 8,  /* CBC mode */
	EA_RC2_40 = 9,	 /* CBC mode, for non-domestic recipients */
	EA_IDEA_128 = 10,	 /* CBC mode */
	EA_AES = 11,	/*Advanced Encryption Standard Symmetric Algorithm*/
	EA_AES_256 = 12,	/*Advanced Encryption Standard Symmetric Algorithm with 256 bit key length*/
	EA_AES_192 = 13,	/* Advanced Encryption Standard symmetric algorithm with 192 bit key length */
	EA_AES_128 = 14,	/* Advanced Encryption Standard symmetric algorithm with 128 bit key length */
	EA_DEFAULT = 15,	 /* use the default symmetric algorithm */
	EA_LAST = EA_AES_128 /* just for upper bounding, move as required. */
	
} ENCRYPTION_ALGORITHM;

static const char* textEncAlgs[] =
{
	"CAST",
	"DES",
	"CAST-128",
	"CAST-80",
	"CAST-64",
	"CAST-40",
	"TRIPLE DES",
	"RC2",
	"RC2-128",
	"RC2-40",
	"IDEA",
	"AES",
	"AES-256",
	"AES-192",
	"AES-128"
};

/* Allowable client types. */
typedef enum
{
    CL_UNKNOWN = 0,	 /* invalid or unknown client type  */
    CL_DEMO,         /* Demo version of Client */
    CL_LITE,         /* Entrust/Lite Client */
    CL_500,		     /* Entrust/500 Client */
    CL_NO_X500
} CLIENT_TYPE;

/*Check to see if any other toolkits have devined this.*/
#if !defined(KMPBDEFS_H)

/* Options for the DirectorySearch function, specifying which directory */
/* to search.                                                           */
typedef enum
{
	SL_PUBLIC_DATA_SOURCE,
	SL_PRIVATE_DATA_SOURCE,
	SL_PUBLIC_AND_PRIVATE_DATA_SOURCE
} SEARCH_LOCATION;

/* Search depth for X.500 Directory searches. */
typedef enum  {
	SD_SEARCH_OBJECT,   /* search that node only */
	SD_SEARCH_ONELEVEL, /* search that node and immediate subordinates */
	SD_SEARCH_SUBTREE,  /* search that node and all sub-nodes */
	SD_NULL             /* null value can be used for Lite or PAB searches */
} SEARCH_DEPTH;

#endif

/* Enumeration for specifying the operation or
   combination of operations to be performed.
   Also used to report how incoming secured information has
   been protected.
   Note: the SO_CERT_ONLY value is only used to identity incoming
   certificate only PKCS7 messages
   To create a cert only message,
   use EntFile::CreatePKCS7CertOnlyMessage() or
   ETCreatePKCS7CertOnlyMessage() functions. */
typedef enum
{
	SO_SIGN_ONLY,
	SO_ENCRYPT_ONLY,
	SO_SIGN_AND_ENCRYPT,
	SO_CLEAR_SIGN_ONLY, /* for StartProtect and FileProtect only */
	SO_CERT_ONLY,		/* output only, from FileUnprotect() or EndUnprotect().  */
#if defined(_WIN32)
	SO_DIGEST_ONLY,
	SO_RECEIPT,
	SO_HARVEST,
#else
    SO_DIGEST_ONLY
#endif
} SECURITY_OPERATION;

typedef enum
{
	RCP_TO = 0,
	RCP_CC = 1,
	RCP_BCC = 2

} RECIPIENT_TYPE;

/* Operating system designation used to indicate the source operating system of a
   secured file. */
typedef enum
{
	OS_WINDOWS,
	OS_MACINTOSH,
	OS_UNIX
} SOURCE_OS;

/* VERIFICATION_SOURCE indicates the source which was used to
   validate a signing certificate. */
typedef enum
{
	VS_NO_SOURCE,
	VS_BY_OUR_CA,
	VS_BY_PAB,
	VS_BY_CROSS_CERTIFICATION,
	VS_BY_PAB_NO_KEYFILE
} VERIFICATION_SOURCE;

typedef enum
{
	/* backwards compatibility */
	SQ_SHA1 = 0,
	SQ_MD5 = 1,
	SQ_MD2 = 2,

	/* RSA hashers */
	SQ_SHA1WITHRSA = SQ_SHA1,
	SQ_MD5WITHRSA = SQ_MD5,
	SQ_MD2WITHRSA = SQ_MD2,

	/* DSA hashers */
	SQ_SHA1WITHDSA =3,
	SQ_SHA1WITH_ECDSA =4,

	/* SHA256 Hasher */
	SQ_SHA256WITHRSA = 5,

	/* Unknown Alg */
	SQ_UNKNOWN 
} SIGNING_QUALITY;

/* Check to see if any other toolkits have devined this.*/
#if !defined(ENTCDEFS_H) && !defined(KMPBDEFS_H)
typedef enum
{
	KU_DIGITAL_SIGNATURE = 0,
	KU_NON_REPUDIATION,
	KU_KEY_ENCIPHERMENT,
	KU_DATA_ENCIPHERMENT,
	KU_KEY_AGREEMENT,
	KU_KEY_CERT_SIGN,
	KU_CRL_SIGN,
	KU_UNKNOWN	/* used when key usage could not be determined. */
} KEY_USAGE;

#endif


/* flags controlling data which can optionally be sent
   in a protected message.
*/
#define PRF_INCLUDE_ENC_CERT	0x0001
#define PRF_INCLUDE_CA_CERT		0x0002
#define PRF_INCLUDE_VER_CERT	0x0004

typedef UINT16 PROTECT_FLAGS;

/* Default Protection Flags */
static PROTECT_FLAGS defaultProtectFlags =	PRF_INCLUDE_ENC_CERT |
											PRF_INCLUDE_CA_CERT  |
											PRF_INCLUDE_VER_CERT;


typedef struct {
	SECURITY_OPERATION	 secOperation;
	ENCRYPTION_ALGORITHM encryptionQuality;
	SIGNING_QUALITY		 signingQuality;
	char *				 idu_type;
	PROTECT_FLAGS		 protect_flags;
} PROTECT_OPTIONS;

/* Security header types, indicating the operation(s) which were  */
/* performed on the associated data.                              */
typedef enum
{
	HT_BAD_HEADER,			 /* header could not be decoded */
	HT_ENCRYPT_ONLY,
	HT_SIGN_AND_ENCRYPT,
	HT_SIGN_ONLY
} HEADER_TYPE;

 /* How was an Archive File protected? */
typedef struct {
	HEADER_TYPE				hdrType;
	ENCRYPTION_ALGORITHM	encryptionInfo;
	SIGNING_QUALITY			signingInfo;
} ARCHIVE_INFO;

/* The LOGIN_INFO enumeration defines different types of information about
   the current login session which can be obtained by functions
   EntFile::GetLoginInformation() or ETGetLoginInformation()
*/
typedef enum
{
	LG_BOOL_PROFILE_CHANGED = 0,/* has the profile been updated, e.g. due to key update */
	LG_BOOL_DN_CHANGED = 1,			/* has the user's distinguished name been changed */
	LG_BOOL_OFFLINE = 2,			/* are we offline (e.g. cannot access Entrust/Directory) */
	LG_BOOL_OPTIONS_CORRUPT = 3,	/* integrity check on profile options has failed */
	LG_BOOL_PASSWORD_EXPIRED = 4, 
	LG_STRING_ALLOWED_SYM_ENC_ALGS = 5,	/* allowed/supported symmetric encryption algorithms */
	LG_STRING_ALLOWED_HASH_ALGS = 6,	/* allowed/supported hash algorithms */
	LG_BOOL_PERMIT_NON_ROAMING = 7,		/* can the user use a local .epf or token */
	LG_BOOL_PERMIT_ROAMING = 8,			/* can the user use a roaming profile */
	LG_BOOL_ENFORCE_TOKEN_USAGE = 9,	/* must user have a token-based profile */
	LG_BOOL_PERMIT_PAB_USAGE = 10,		/* can user use Personal Address Books for end-user trust relationships */
	LG_BOOL_PERMIT_CAPAB_USAGE = 11,	/* can user use CA PABs */
	LG_BOOL_PERMIT_GROUPKEY_EXPORT = 12, /* can user export group keys */
	LG_STRING_MOTD = 13,				/* optional message of the day from administrator */
	LG_INT16_CLIENTTYPE = 14,			/* client type */
	LG_STRING_SIGNING_KEY_TYPE = 15,	/* default signing key type (e.g. RSA, DSA, ECDSA) */
	LG_STRING_ASYM_KEY_TYPE= 16,		/* default asymmetric encryption key type */
	LG_INT16_DEFAULT_SYM_ALG = 17,		/* default symmetric encryption algorithm enum (ENCRYPTION_ALGORITHM) */
	LG_BOOL_IS_ROAMING_USER = 18,		/* is the logged in user roaming or desktop */
	LG_BOOL_PASSWORD_DATA_CORRUPT = 19,	/* SJW - 31/05/2000 - PRSaa23397  - password history corrupt */
	LG_INT_ENC_KEY_STATUS = 20,			/* aa17451 - access to encryption key status */
	LG_INT_SIG_KEY_STATUS = 21,			/* aa17451 - access to signature key status */
	LG_INT_NUM_KEY_PAIRS = 22			/* the user's current number of key pairs (one or two) */
} LOGIN_INFO;

/*
   The POLICY_CERTIFICATE_INFO enumeration is similar to 
   LOGIN_INFO except that it defines what information about
   the policy certificate can be returned by functions
   EntFile::GetPolicyCertificateInformation() or 
   ETGetPolicyCertificateInformation().
*/

typedef enum
{
	PC_STRING_ENT_ROLE_MAP = 0,		// "entrustRoleMap"
	PC_INT_ENT_USER_ROLE = 1,		// "entrustUserRole"
	// "entrustPasswordRules"
		PC_INT_ENT_PASS_RULES_LIFE = 2,
		PC_INT_ENT_PASS_RULES_HISTORY = 3,
		PC_INT_ENT_PASS_RULES_LENGTH = 4,
		PC_INT_ENT_PASS_RULES_SLO_TIMEOUT = 5,
		PC_BOOL_ENT_PASS_RULES_NONALPHA = 6,
		PC_BOOL_ENT_PASS_RULES_UPPER = 7,
		PC_BOOL_ENT_PASS_RULES_LOWER = 8,
		PC_BOOL_ENT_PASS_RULES_DIGIT = 9,
		PC_BOOL_ENT_PASS_RULES_BLANKS_OK = 10,
		PC_BOOL_ENT_PASS_RULES_REPEAT_OK = 11,
		PC_BOOL_ENT_PASS_RULES_IGNORE_CASE = 12,
		PC_BOOL_ENT_PASS_RULES_DISABLE_SLO = 13,
	PC_STRING_ENT_ATTR_NAME = 14,			// "entrustAttrName"
	PC_INT_ENT_CLIENT_ENC_KEY_TYPE = 15,	// "entrustClientNKeyType"
	PC_STRING_ENT_ALLOWED_SYM_ALGMS = 16,	// "entrustAllowedSymmetricAlgms"
	PC_STRING_ENT_ALLOWED_HASH_ALGMS = 17,	// "entrustAllowedHashAlgms"
	// "entrustCSetFlags"
		PC_BOOL_ENT_CSET_PERMIT_ROAMING = 18,
		PC_BOOL_ENT_CSET_PERMIT_NON_ROAMING = 19,
		PC_BOOL_ENT_CSET_ENFORCE_TOKEN_USAGE = 20,
		PC_BOOL_ENT_CSET_PERMIT_PAB_USAGE = 21,
		PC_BOOL_ENT_CSET_PERMIT_CAPAB_USAGE = 22,
		PC_BOOL_ENT_CSET_PERMIT_GROUPKEY_EXPORT = 23,
	PC_BOOL_ENT_CSET_PERMIT_SERVER_LOGIN = 24,	// "entrustAllowServerLogin"
	PC_BOOL_ENT_CSET_ENFORCE_IDENTITY_USE = 25, // "entrustEnforceIdentityUse"
	PC_STRING_ENT_MESSAGE_OF_THE_DAY = 26,		// "entrustMessageOfTheDay"
	// "entrustApplicationFlags"
		PC_BOOL_ENT_APP_SMIME_ONLY = 27,
	PC_STRING_ENT_SIGN_KEY_TYPE = 28,		// "entrustSignKeyType"
	PC_STRING_ENT_ENC_KEY_TYPE = 29,		// "entrustEncKeyType"
	PC_STRING_ENT_BUS_CTRL_POL_OIDS = 30,	// "entrustBusCtrlPolOids"
	// "entrustBusCtrlFlags"
		PC_BOOL_ENT_BUS_CTRL_IGNORE_POLICIES = 31,
		PC_BOOL_ENT_BUS_CTRL_REQUIRE_POLICY = 32,
		PC_BOOL_ENT_BUS_CTRL_PKIX_COMPLIANCE = 33,
		PC_BOOL_ENT_BUS_CTRL_FPKI_COMPLIANCE = 34,
	PC_INT_ENT_POLICY_CERT_LIFETIME = 35,	// "entrustPCertLifetime"
	PC_STRING_ENT_DNE_ENCODING = 36,		// "entrustDNEncoding"
	PC_BOOL_ENT_CERT_CONSIST_CHECKING = 37,	// "entrustCertConsistencyChecking"
	PC_STRING_ENT_USER_ENC_ALGM = 38,		// "entrustUserEncAlgm"
	PC_INT_ENT_CRL_GRACE_PERIOD = 39,		// "entrustCRLGracePeriod"
	PC_STRING_ENT_HTTP_PROXY_SETTING = 40,	// "entrustHTTPProxySetting"
	PC_BOOL_ENT_SKIP_RL_CHECKS = 41,		// "entrustSkipRLChecks"
	PC_BOOL_ENT_OFFLINE_PROFILE_USE = 42,	// "entrustOfflineProfileUse"
	PC_BOOL_ENT_ALLOW_PKCS12_EXPORT = 43,	// "entrustAllowPCKS12Export"
	PC_INT_ENT_CLIENT_N_KEY_TYPE = 44,		// NEW -- "entrustClientNKeyType"
	// Number 45 intentionally left blank
	PC_BOOL_ENT_PREVENT_MANUAL_APP_REG = 46,// "entrustPreventManualAppRegistration"
	PC_INT_ENT_PASS_MAX_ATTEMPTS = 47,		// "entrustPasswordMaxAttempts"
	PC_INT_ENT_PASS_MIN_TIME = 48,			// "entrustPasswordMinTime"
	PC_INT_ENT_PASS_MIN_SUSPEND = 49,		// "entrustPasswordMinSuspend"
	PC_BOOL_ENT_ALLOW_CAPI_EXPORT = 50,		// "entrustAllowCAPIExport"
	// "entrustICEAdminPolicy"
		PC_BOOL_ENT_ICE_ADMIN_POLICY_REQUIRE_SIG = 51,				// -- requireSignature
		PC_BOOL_ENT_ICE_ADMIN_POLICY_IGNORE_LOCAL_SETTINGS = 52,	// -- ignoreLocalSettings
	// "entrustEnableCacheUsage"
		PC_BOOL_ENT_ENABLE_ARL_CACHE = 53,
		PC_BOOL_ENT_ENABLE_CRL_CACHE = 54,
		PC_BOOL_ENT_ENABLE_XCERT_CACHE = 55,
		PC_BOOL_ENT_ENABLE_CERT_CACHE = 56,
	PC_STRING_ENT_SECURE_DELIVERY_SERVICE_SMTP = 57,	// "entrustSecureDeliveryServiceSMTP"
	PC_STRING_ENT_CONTENT_SCANNER_SERVICE_SMTP = 58,	// "entrustContentScannerServiceSMTP"
	// PC_STRING_ENT_EXPRESS_SEARCH_ORDER = 59,			// "entrustExpressSearchSourceOrder"
	// "entrustCAPIPolicy"
		PC_BOOL_ENT_ALLOW_NO_CAPI_KEY_PROTECTION = 60,
		PC_BOOL_ENT_ALLOW_CAPI_PRIVATE_KEY_EXPORT = 61,
	PC_STRING_ENT_SEARCH_BASE_SEARCH_ORDER = 62			// "entrustSearchBaseSearchOrder"

} POLICY_CERTIFICATE_INFO;

typedef struct {
	ENCRYPTION_ALGORITHM m_EncryptionAlgorithm;
} SecurityOptions;

typedef struct {
	BOOL	asciiEncode;
	BOOL	deletePlaintextAfter;
	ENCRYPTION_ALGORITHM m_EncryptionAlgorithm;
} FileSecureOptions;

typedef struct {
	BOOL	writeOutput;
	BOOL	deleteCiphertextAfter;
} FileUnSecureOptions;

typedef struct {
	BOOL isShared; /* is it a shared group ? */
} GroupOptions;

/* Recipient List option specifiers */
typedef enum
{
    ET_RL_OPT_SIGN = 0,
    ET_RL_OPT_ENCRYPT,
    ET_RL_OPT_TIMESTAMP,
    ET_RL_OPT_INPLACE,
    ET_RL_OPT_COMPRESS,
    ET_RL_OPT_ASCIIENCODE,
    ET_RL_OPT_MAILOPERATION,
    ET_RL_OPT_ENCRYPTALGORITHM,
    ET_RL_OPT_FILEEXTENSION,

    /* MSP options */
    ET_RL_OPT_POLICY,
    ET_RL_OPT_CLASSIFICATION,
    ET_RL_OPT_CATEGORY,
    ET_RL_OPT_PRIVACYMARK,
    ET_RL_OPT_ENCRYPTFORMAT,

	ET_RL_OPT_EXTRARLOPTIONS   //aa05517
} EntOptType;

/* Determine the functionality of the specific recip list by masking the
 * capability returned from GetCapability with the desired piece of
 * functionality. Usually used to enable/disable visual UI elements.
 * i.e. Enable the Remove button only if the capability allows it. */
typedef enum
{
    ET_RL_EXPORT                = 0x0001,
    ET_RL_SAVE                  = 0x0002,
    ET_RL_REMOVE                = 0x0004,
    ET_RL_MOD_NAME              = 0x0008,
    ET_RL_MOD_RECIP             = 0x0010,
    ET_RL_MOD_OPTS              = 0x0020,
    ET_RL_UNDO                  = 0x0040,
    ET_RL_EXPORT_SELF_CONTAINED = 0x0100
} EntRListCapability;


/* ArchiveOptions apply when a new Entrust archive file
   is created. The useReserved flag (which should be set to
   FALSE) and reserved fields are intended for forwards
   compatibility, so that new options can be added in future
   releases without altering the interface. */

typedef struct {
	SECURITY_OPERATION 	secOp;
  	FileSecureOptions 	fileOptions;
  	BOOL 				compress;    /* use file compression ? */
  	BOOL 				useReserved; /* use the reserved fields ? Set to FALSE */
  	INT16				reserved1;   /* reserved for future use */
  	INT16				reserved2;
  	INT16				reserved3;
} ArchiveOptions;

/* Possible commands to the Address Book */
typedef enum
{
    AB_GET_RECIPIENTS = 0,  /* allows users to select recipients */
    AB_SHOW_NOWAIT,         /* show the ab and don't wait */
    AB_SHOW_WAIT            /* show the ab and wait */
} AB_CmdMsgId;


/* status information for a file extracted from an archive */
typedef struct {
	EntLog				decryptionError;
	EntLog				verificationError;
	EntLog				fileError;
	VERIFICATION_SOURCE	verificationSource;
	SOURCE_OS			sourceOS;
} DecryptVerifyStatus;


/* SSL key types.  Used for the SSL Sign/Verfiy methods. */
typedef enum
{
	SSL_RSA,
	SSL_DSA,
	SSL_ANONYMOUS
}EntSSL_Alg ;


/* Cache types */
typedef enum {
	CCH_NONE = 0,		/* no caches*/
	CCH_ALL,			/* all caches*/
	CCH_USER_CERT,		/* encryption & verification certificates*/
	CCH_CRL,			/* certificate revocation list*/
	CCH_ARL,			/* authority revocation list*/
	CCH_CROSS_CERT		/* cross certificates*/
} CACHE_TYPE;

/* Cache operations */
typedef enum {
	CO_SAVE = 0,	/* save in-memory cache to disk*/
	CO_LOAD,		/* load in-memory cache from disk, replacing current in-memory cache*/
	CO_DELETE		/* delete in-memory cache*/
} CACHE_OPERATION;


/* Virus detection options */
typedef enum
{
	MOVE_INFECTED_FILES,
	DELETE_INFECTED_FILES,
	FIX_INFECTED_FILES,
	DO_NOTHING
} VirusDetectOptions;

typedef struct{
	char moveToDir[MAX_VIRUSSTR_SIZE];
	char fileName[MAX_VIRUSSTR_SIZE];
	char virusName[MAX_VIRUSSTR_SIZE];
	EntLog	virusStatus;
} VirusDetectInfo;

typedef enum
{
	USE_SYMANTEC			= 0x01,
	USE_MCAFEE				= 0x02,
	USE_OTHER1				= 0x04,	/* future service */
	USE_OTHER2				= 0x08	/* future service */
} VIRUS_SCANNERS;

/* This is the default value used by modern browsers for the hash count of a PKCS #12 message.*/
#define DEFAULT_P12_HASH_COUNT 2000	
/*The version of PKCS #12 implimented is version 3.*/	
#define PKCS12_VERSION 3			

/* Default Security Options selects EA_CAST encryption algorithm. */
static SecurityOptions defaultSecurityOptions = { EA_CAST };

/* maximum length of a recipient group's name. */
#define MAX_GROUP_NAME_SIZE 20

/* C interface specific declarations ----------------------------------*/

/* Maximum size of names */
#define MAX_NAME_SIZE 512

/* general purpose length limit for returned strings. */
#define MAX_ENTSTR_SIZE 1024

/* length of an authentication string (include terminating null) */
#define MAX_AUTHSTR_SIZE 15


/* ETCertificateData and ETCertificateData2 provide information
   extracted from X.509 public key certificates. */
typedef struct
{
	char OwnerName[ MAX_NAME_SIZE ];		/* common name */
	char OwnerUniqueName[ MAX_NAME_SIZE ];	/* X.500 distinguished name */
	char CAName[ MAX_NAME_SIZE ];			/* Certification Authority name */
} ETCertificateData;

typedef struct {
	SECURITY_OPERATION	  secOperation;
	ENCRYPTION_ALGORITHM  encryptionQuality;
	SIGNING_QUALITY		  signingQuality;
	char originator[ MAX_NAME_SIZE ];
	char idu_type[ MAX_NAME_SIZE ];
	char supportedAlgorithms[ MAX_ENTSTR_SIZE ];
	time_t					signingTime;
	void*					reserved;
} ETUNPROTECT_INFO;

/* A context handle used for accessing underlying EntFile member functions */
typedef void* ETContext;

/* A context handle used for accessing underlying EntFile member functions for threads */
typedef void* ETThreadCtx;

/* A context handle used for accessing underlying EntTokenManager member functions */
typedef void* ETTokenMgr;

/* Binary data structures for signing and encrypting */
typedef struct
{
	UINT16 size;
	BYTE* data;
} ETBinData;

typedef struct
{
	UINT32 size;
	BYTE* data;
} ETBinData32;


/* Profile Options */
typedef enum
{	/* weird case */
	POID_unknown = -1,

	/* options */
	POID_logoffTimeoutMinutes = 0,
	POID_compressPlaintext,
	POID_asciiEncodeAfterEnc,
	POID_virusScanDuringDec,
	POID_signWhenEnc,
	POID_timeStampWhenEnc,
	POID_preferredEncAlg,
	POID_keyFileLocation,
	POID_entrustDir,
	POID_encryptDir,
	POID_decryptDir,
	POID_encryptFiles,
	POID_deletePlaintext,
	POID_deleteCiphertext,
	POID_encOverwriteExisting,
	POID_decOverwriteExisting,
	POID_encryptedFileExtension,
	POID_writeOutput,
	POID_encIncludeSubdirs,
	POID_decIncludeSubdirs,
	POID_myEyesOnly,
	POID_launchApp,
	POID_encInPlaceOperation,
	POID_decInPlaceOperation,
	POID_mailOperation,
	POID_recipientSource,
	POID_searchBase,
	POID_ignoreHierarchy,
	POID_rememberPassword,
	POID_displayMailWarning,
	POID_displayNetworkDecWarning,
	POID_profileType,
	POID_loginSection,
	POID_loginMessage,
	POID_selectedRecipients,
	POID_encryptVrefnum,
	POID_encryptDirid,
	POID_decryptVrefnum,
	POID_decryptDirid,
	POID_useSMIME, 
	POID_SMIMEEncryptWith,
	POID_SMIMESignWith, 
	POID_deleteAfterDecrypt,
	POID_deleteAfterEncrypt,
	POID_warnSecureDelete,
	POID_extraRLOptions,  //aa05517

	POID_frontier
} ProfileOptionID;

/* ShowProfileOptions flags */
#define SPO_MODELESS    0x0001

/* export declarations */
#if defined(_WINDOWS) && !defined(_WIN32)
#	ifndef WIN16
#		define WIN16
#	endif
#	define EXPT   __export
#	define EXPT32
#	define ETEXPORT __export __far __pascal
#	define ETEXPORT32
#else
#	if defined(_WIN32) && !defined(_MAC)
#		ifndef STRICT
#		define STRICT 1
#		endif
#		include <windows.h>
#		define EXPT
#		define EXPT32 __declspec( dllexport )
#		define ETEXPORT __stdcall
#		define ETEXPORT32 __declspec( dllexport )
#	else /* not WIN16 or WIN32 */
#		define EXPT
#		define EXPT32
#		define ETEXPORT
#		define ETEXPORT32
#	endif
#endif

#endif /* os_spec_h */

#if _MSC_VER >= 1100
#pragma pack(pop)
#endif

#if defined(unix)
extern char* itoa( int value, char* str, int base );
#endif

#endif

