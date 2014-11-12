/******************************************************************************
 * enterr.h - Header file for the EntrustFile API EntLog return codes.
 *
 * Copyright (c) 1994-2002 Entrust Ltd.   All rights reserved.
 *****************************************************************************/

#ifndef ENTERR_H
#define ENTERR_H

/** <rc><name>ENT_OK</name><num>0</num></rc> */
#define ENT_OK 	0	/* success return code */


enum {
	ENT_PKCS12_EXPORT_UNABLE_TO_ADD_SAFEBAG					= -13099,	/*Unable to append a SafeBag to a SafeContent.*/
	ENT_PKCS12_EXPORT_FILE_NOT_SET							= -13098,	/*A valid file name must be provided in order to export.*/
	ENT_PKCS12_EXPORT_CERTLIST_NOT_SET						= -13097,	/*You can not export an empty list of certs.*/
	ENT_PKCS12_EXPORT_HASH_COUNT_TO_SMALL					= -13096,	/*The hash count provided is lower than that allowed by the client side settings.*/
	ENT_PKCS12_EXPORT_NOT_ALLOWED_TO_EXPORT					= -13095,	/*The user must have the ability to export given to him by the administrator via the policy cert.*/
	ENT_PKCS12_EXPORT_NO_EXPORT_EXTENSION					= -13094,	/*The certificats being exported must contain the export extension.  This is not true in the case of a Solo User*/
	ENT_PKCS12_EXPORT_INVALID_KEY_USAGE						= -13093,	/*The exported certificate must be a signing or encryption certificate */
	ENT_PKCS12_EXPORT_UNABLE_TO_ADD_AUTHENTICATEDSAFE		= -13092,	/*Unable to append a ContentInfo to the Authenticated Safe structure.*/
	ENT_PKCS12_EXPORT_UNABLE_TO_CREATE_FILE					= -13091,	/*Unable to open or create the export file with the specified name.*/
	ENT_PKCS12_EXPORT_UNABLE_TO_WRITE_FILE					= -13090,	/*Unable to write the contents of the PFX to the specified file.  The size of the PFX is not the same as that of the output.*/
	ENT_PKCS12_IMPORT_BAD_CONTENT_TYPE						= -13089,	/*The contentType of one of the ContentInfos is wrong.*/
	ENT_PKCS12_IMPORT_EMPTY_CONTENTS						= -13088,	/*The contents expected was not null*/
	ENT_PKCS12_IMPORT_NOT_X509_CERTIFICATE					= -13087,	/*Only X.509 certificates are supported for PKCS #12 import*/
	ENT_PKCS12_IMPORT_INVALID_LOCAL_KEY_ID					= -13086,	/*There should only be one LKI for a key or cert and it should be an ASN.1 Octet String*/
	ENT_PKCS12_IMPORT_MAC_NOT_VALID							= -13085,	/*MAC validation failed either the wrong password was supplied or the file has been tampered with.*/
	ENT_PKCS12_IMPORT_UNSUPPORTED_ALGORITHM					= -13084,	/*Keys must be protected with pbeWithSHA1And3_KeyTripleDES_CBC and certs with pbeWithSHA1And40BitRC2_CBC*/
	ENT_PKCS12_IMPORT_NULL_PARAMETERS						= -13083,	/*The Salt and iteration count were not specified for the generation of a Symmetric Key.*/
	ENT_PKCS12_IMPORT_INVALID_KEY_BAG_TYPE					= -13082,	/*The private key must be a valid key protected in a PKCS #8 Shrouded Key Bag*/
	ENT_PKCS12_IMPORT_NO_ASSOCIATED_PRIVATE_KEY				= -13081,	/*There was no private key associated with the local key identifier provided.*/
	ENT_PKCS12_IMPORT_NO_DECRYPTION_KEY_PRESENT				= -13080,	/**/
	ENT_PKCS12_IMPORT_NO_SIGNING_KEY_PRESENT				= -13079,	/**/
	ENT_PKCS12_IMPORT_NO_CA_CERTIFICATE_PRESENT				= -13078,	/*There must be a CA and Root Certificate in the PKCS #12 message.  These certificates can be the same certificate or two seperate certificates.*/
	ENT_PKCS12_IMPORT_NO_ENCRYPTION_CERTIFICATE_PRESENT		= -13077,	/**/
	ENT_PKCS12_IMPORT_NO_VERIFICATION_CERTIFICATE_PRESENT	= -13076,	/**/
	ENT_PKCS12_IMPORT_ISSUERS_DO_NOT_MATCH					= -13075	/*The DNs for the issuers of the verification and encryption certificates do not match.*/
};

enum {

	/** <rc><name>ENT_BAD_HDR_SUPPLIED</name><num>-3999</num></rc> */
	ENT_BAD_HDR_SUPPLIED	= -3999, /* the supplied header was badly formatted */

	/** <rc><name>ENT_NO_SUCH_HDR_TYPE</name><num>-3998</num></rc> */
	ENT_NO_SUCH_HDR_TYPE	= -3998, /* ExtractHeaderType returned an out of range value */

	/** <rc><name>ENT_NO_SUCH_SEC_OP</name><num>-3997</num></rc> */
	ENT_NO_SUCH_SEC_OP		= -3997, /* An out of range SECURITY_OPERATION value was found */

	/** <rc><name>ENT_NOOP_IN_PROGRESS</name><num>-3996</num></rc> */
	ENT_NOOP_IN_PROGRESS	= -3996, /* A perform or end security operation was requested
	but no valid operation was in progress */

	/** <rc><name>ENT_NO_SUCH_ALGORITHM</name><num>-3995</num></rc> */
	ENT_NO_SUCH_ALGORITHM	= -3995, /* out of range SecurityOptions.m_EncryptionAlgorithm */

	/** <rc><name>ENT_NULL_FILENAME_PTR</name><num>-3994</num></rc> */
	ENT_NULL_FILENAME_PTR	= -3994, /* a supplied file name ptr was NULL */

	/** <rc><name>ENT_INVALID_OP_STATE</name><num>-3993</num></rc> */
	ENT_INVALID_OP_STATE	= -3993, /* the internal operational state was not appropriate
	for the required function (e.g. calling DecryptVerify partway through an encryption). */

	/** <rc><name>ENT_ILLEGAL_OP_STATE</name><num>-3992</num></rc> */
	ENT_ILLEGAL_OP_STATE	= -3992, /* the internal operational state code is out of range */

	/** <rc><name>ENT_SIG_VERIFY_FAILED</name><num>-3991</num></rc> */
	ENT_SIG_VERIFY_FAILED	= -3991, /* a digital signature verification failed */

	/** <rc><name>ENT_DECRYPT_FAILED</name><num>-3990</num></rc> */
	ENT_DECRYPT_FAILED		= -3990, /* a file decryption operation failed. */

	/** <rc><name>ENT_UNEXPECTED_NULL_PTR</name><num>-3989</num></rc> */
	ENT_UNEXPECTED_NULL_PTR = -3989, /* a pointer input parameter was unexpectedly found to be NULL */

	/** <rc><name>ENT_BAD_GROUPLIST_INDEX</name><num>-3988</num></rc> */
	ENT_BAD_GROUPLIST_INDEX = -3988, /* a supplied group list index was out of range */

	/** <rc><name>ENT_NO_MATCHING_GROUP</name><num>-3987</num></rc> */
	ENT_NO_MATCHING_GROUP   = -3987, /* no group with a matching name was found */

	/** <rc><name>ENT_GROUP_NAME_TOO_LONG</name><num>-3986</num></rc> */
	ENT_GROUP_NAME_TOO_LONG = -3986, /* the group name exceeded  MAX_GROUP_NAME_LENGTH */

	/** <rc><name>ENT_PROCESSING</name><num>-3985</num></rc> */
	ENT_PROCESSING		 	= -3985, /* file processing is proceeding successfully (not an error) */

	/** <rc><name>ENT_STRING_TRUNCATED</name><num>-3984</num></rc> */
	ENT_STRING_TRUNCATED  	= -3984, /* a string exceeding its allowable max length was truncated */

	/** <rc><name>ENT_CANNOT_OPEN_FILE</name><num>-3983</num></rc> */
	ENT_CANNOT_OPEN_FILE    = -3983, /* a specified input file cannot be opened */

	/** <rc><name>ENT_NOT_ENTRUST_FILE</name><num>-3982</num></rc> */
	ENT_NOT_ENTRUST_FILE    = -3982, /* a specified input file did not have a valid Entrust file format */

	/** <rc><name>ENT_NOT_SUPPORTED</name><num>-3981</num></rc> */
	ENT_NOT_SUPPORTED		= -3981, /* feature is not supported in this release */

	/** <rc><name>ENT_ARCHIVE_NOT_SUPPORTED</name><num>-3980</num></rc> */
	ENT_ARCHIVE_NOT_SUPPORTED= -3980, /* multi-file archives not supported in this release */

	/** <rc><name>ENT_SWITCHED_TO_LITE</name><num>-3979</num></rc> */
	ENT_SWITCHED_TO_LITE    = -3979,  /* could not connect to public directory */

	/** <rc><name>ENT_BAD_SEARCH_BASE_INDEX</name><num>-3978</num></rc> */
	ENT_BAD_SEARCH_BASE_INDEX= -3978,  /* a supplied search base index is out of range */

	/** <rc><name>ENT_CANT_IMPORT_EXISTING_GRP</name><num>-3977</num></rc> */
	ENT_CANT_IMPORT_EXISTING_GRP=-3977, /* Cannot import a shared group if a shared group with the same name already exists */

	/** <rc><name>ENT_BAD_FILE_INDEX</name><num>-3976</num></rc> */
	ENT_BAD_FILE_INDEX		= -3976,  /* A supplied file index was out of range */

	/** <rc><name>ENT_CERT_ATTR_NOT_FOUND</name><num>-3975</num></rc> */
	ENT_CERT_ATTR_NOT_FOUND	= -3975, /* A certificate attribute for this EntrustName does not exist. */

	/** <rc><name>ENT_OUTPUT_FILE_EXISTS</name><num>-3974</num></rc> */
	ENT_OUTPUT_FILE_EXISTS	= -3974, /* Output file already exists and overwrite not enabled. */

	/** <rc><name>ENT_DUPLICATE_FILE_NAME</name><num>-3973</num></rc> */
	ENT_DUPLICATE_FILE_NAME	= -3973, /* An output file with the same name has already been generated. */

	/** <rc><name>ENT_INPUT_NAME_IS_OUTPUT_NAME</name><num>-3972</num></rc> */
	ENT_INPUT_NAME_IS_OUTPUT_NAME = -3972, /* The output file is the same as the input file. */

	/** <rc><name>ENT_ARCHIVE_PROBLEM</name><num>-3971</num></rc> */
	ENT_ARCHIVE_PROBLEM 	= -3971, /* Warnings or errors were generated for one or more of the encapsulated files. */

	/** <rc><name>ENT_SOURCE_IS_DEST</name><num>-3970</num></rc> */
	ENT_SOURCE_IS_DEST		= -3970, /* Destination and source pointers for a memory copy operation are the same. */

	/** <rc><name>ENT_TOKEN_BAD_PROF_INDEX</name><num>-3969</num></rc> */
	ENT_TOKEN_BAD_PROF_INDEX= -3969, /* A supplied token profile index was out of range */

	/** <rc><name>ENT_TOKEN_BAD_PROFILE</name><num>-3968</num></rc> */
	ENT_TOKEN_BAD_PROFILE	= -3968, /* A token-based profile matching the supplied name could not be found. */

	/** <rc><name>ENT_INVALID_PKCS7_SEQUENCE</name><num>-3967</num></rc> */
	ENT_INVALID_PKCS7_SEQUENCE = -3967, /* Invalid PKCS #7 sequence */

	/** <rc><name>ENT_MOREDATA_NEEDED</name><num>-3966</num></rc> */
	ENT_MOREDATA_NEEDED		= -3966, /* More data required to make it a valid pkcs #7 sequence */

	/** <rc><name>ENT_INVALID_IDU_TYPE</name><num>-3965</num></rc> */
	ENT_INVALID_IDU_TYPE	= -3965, /* Invalid idu type */

	/** <rc><name>ENT_NO_SERVICES_RECEIVED</name><num>-3964</num></rc> */
	ENT_NO_SERVICES_RECEIVED = -3964, /* Neither encryption nor signing performed */

	/** <rc><name>ENT_NO_SUCH_ENC_QUALITY</name><num>-3963</num></rc> */
	ENT_NO_SUCH_ENC_QUALITY = -3963, /* encryption algorithm is incorrect */

	/** <rc><name>ENT_NO_SUCH_SIG_QUALITY</name><num>-3962</num></rc> */
	ENT_NO_SUCH_SIG_QUALITY = -3962, /* signing algorithm is incorrect */

	/** <rc><name>ENT_OID_SETVALUE_FAIL</name><num>-3961</num></rc> */
	ENT_OID_SETVALUE_FAIL	= -3961, /* setvalue for asn oid failed */

	/** <rc><name>ENT_BAD_ASNOID</name><num>-3960</num></rc> */
	ENT_BAD_ASNOID			= -3960, /* asn oid is unrecognized */

	/** <rc><name>ENT_CONTINUE_NEEDED</name><num>-3959</num></rc> */
	ENT_CONTINUE_NEEDED		= -3959, /* call the function again to get data */

	/** <rc><name>ENT_UNKNOWN_KEY_USAGE</name><num>-3958</num></rc> */
	ENT_UNKNOWN_KEY_USAGE	= -3958,  /* unrecognized key usage */

	/** <rc><name>ENT_CERT_FIELD_NOT_FOUND</name><num>-3957</num></rc> */
	ENT_CERT_FIELD_NOT_FOUND= -3957,  /* a requested information field was not found in the certificate */

	/** <rc><name>ENT_BAD_INDEX</name><num>-3956</num></rc> */
	ENT_BAD_INDEX			= -3956,   /* a specified index was out of range. */

	/** <rc><name>ENT_INFO_MISSING</name><num>-3955</num></rc> */
	ENT_INFO_MISSING		= -3955, /* Required or requested information could not be found. */

	/** <rc><name>ENT_TIMESTAMP_FAILED</name><num>-3954</num></rc> */
	ENT_TIMESTAMP_FAILED	= -3954, /* file timestamp operation failed */

	/** <rc><name>ENT_NOT_TIMESTAMPED</name><num>-3953</num></rc> */
	ENT_NOT_TIMESTAMPED		= -3953, /* file not timestamped */

	/** <rc><name>ENT_TIMESTAMP_VERIFY_FAILED</name><num>-3952</num></rc> */
	ENT_TIMESTAMP_VERIFY_FAILED = -3952,  /* timestamp verification failed */

	/** <rc><name>ENT_TIMESTAMP_HEADER_NOT_SUPPLIED</name><num>-3951</num></rc> */
	ENT_TIMESTAMP_HEADER_NOT_SUPPLIED = -3951

	};

enum {

	/** <rc><name>ENM_BAD_ATTR_INDEX</name><num>-3950</num></rc> */
	ENM_BAD_ATTR_INDEX		= -3950, /* a supplied attribute index was out of range */

	/** <rc><name>ENM_BAD_ATTRVAL_INDEX</name><num>-3949</num></rc> */
	ENM_BAD_ATTRVAL_INDEX	= -3949, /* a supplied attribute value index was out of range */

	/** <rc><name>ENM_BAD_NAMELIST_INDEX</name><num>-3948</num></rc> */
	ENM_BAD_NAMELIST_INDEX	= -3948, /* a supplied name list index was out of range */

	/** <rc><name>ENM_NULL_NAME_PTR</name><num>-3947</num></rc> */
	ENM_NULL_NAME_PTR		= -3947, /* the MatchedName pointer of an EntrustName was NULL */

	/** <rc><name>ENM_NAME_NOT_FOUND</name><num>-3946</num></rc> */
	ENM_NAME_NOT_FOUND		= -3946, /* the name was not found in the name list. */

	/** <rc><name>ENM_ADD_NAME_FAILURE</name><num>-3945</num></rc> */
	ENM_ADD_NAME_FAILURE    = -3945  /* could not add an entry to a name list */
};

enum {
	/** <rc><name>MIME_NOT_IMPLEMENTED</name><num>-3944</num></rc>  */
	MIME_NOT_IMPLEMENTED	= -3944, /* Not yet implemented */

	/** <rc><name>MIME_BAD_VERSION</name><num>-3943</num></rc>  */
	MIME_BAD_VERSION		= -3943, /* MIME version header invalid  */

	/** <rc><name>MIME_BAD_HEADER</name><num>-3942</num></rc>  */
	MIME_BAD_HEADER			= -3942, /* Header syntax error */

	/** <rc><name>MIME_SPECIFIC_ERROR</name><num>-3941</num></rc>  */
	MIME_SPECIFIC_ERROR		= -3941, /* Use the specific internal string */

	/**<rc><name>MIME_ERROR_READING_FILE</name><num>-3939</num></rc>  */
	MIME_ERROR_READING_FILE	= -3939, /* Error reading from a file */

	/** <rc><name>MIME_FILE_ERROR</name><num>-3938</num></rc>  */
	MIME_FILE_ERROR			= -3938, /* Generic File error */

	/** <rc><name>MIME_ALLOCATION_ERROR</name><num>-3937</num></rc>  */
	MIME_ALLOCATION_ERROR	= -3937, /* Memory allocation error */

	/** <rc><name>MIME_INTERNAL_ERROR</name><num>-3936</num></rc>  */
	MIME_INTERNAL_ERROR		= -3936 /* Not to be seen by the public (or small children) */
};

enum {

	/** <rc><name>HDR_BAD_GSTR_INDEX</name><num>-3899</num></rc> */
	HDR_BAD_GSTR_INDEX		= -3899 /* a supplied index was out of range */
};

enum {

	/** <rc><name>CNM_INVALID_LISTID</name><num>-3850</num></rc> */
	CNM_INVALID_LISTID		= -3850, /* a supplied var of type ListID was out of range */

	/** <rc><name>CNM_ADD_NAME_FAILURE</name><num>-3849</num></rc> */
	CNM_ADD_NAME_FAILURE	= -3849, /* could not add an entry to a name list */

	/** <rc><name>CNM_NAME_TRUNCATED</name><num>-3848</num></rc> */
	CNM_NAME_TRUNCATED  	= -3848  /* a string exceeding MAX_NAME_SIZE was truncated */
};


/* More EntAPI errors */
enum {

	/** <rc><name>ENT_RR_CERTIFICATE_HOLD</name><num>-3833</num></rc> */
	ENT_RR_CERTIFICATE_HOLD = -3833, /* revocation reason - certificate hold */

	/** <rc><name>ENT_RR_CA_COMPROMISE</name><num>-3832</num></rc> */
	ENT_RR_CA_COMPROMISE = -3832, /* revocation reason - CA comprimised */
	
	/** <rc><name>ENT_BUFFER_TOO_SMALL</name><num>-3831</num></rc> */
	ENT_BUFFER_TOO_SMALL	= -3831, /* Supplied buffer too small */

	/** <rc><name>ENT_EMPTY_CERTIFICATE</name><num>-3830</num></rc> */
	ENT_EMPTY_CERTIFICATE	= -3830, /* supplied certificate was empty */

	/** <rc><name>VIRUS_FOUND</name><num>-3829</num></rc> */
	VIRUS_FOUND			= -3829,	/* A file contains a virus */

	/** <rc><name>VIRUS_LIB_INFECTED</name><num>-3828/num></rc> */
	VIRUS_LIB_INFECTED	= -3828,	/* The virus dll is infected */

	/** <rc><name>VIRUS_NO_SUPPORT</name><num>-3827</num></rc> */
	VIRUS_NO_SUPPORT	= -3827,	/* Virus function not supported */

	/** <rc><name>VIRUS_UNKNOWN</name><num>-3826</num></rc> */
	VIRUS_UNKNOWN		= -3826,	/* Unknow virus error */

	/** <rc><name>VIRUS_INIT_FAILED</name><num>-3825</num></rc> */
	VIRUS_INIT_FAILED	= -3825,	/* Cannot initialize the virus libs */

	/** <rc><name>VIRUS_SCAN_ERROR</name><num>-3824</num></rc> */
	VIRUS_SCAN_ERROR	= -3824,	/* Error occured during file scan. */

	/** <rc><name>VIRUS_SELFTEST_FAILED</name><num>-3823</num></rc> */
	VIRUS_SELFTEST_FAILED = -3823,	/* Error occured self scan. */

	/** <rc><name>VIRUS_SELFTEST_NO_CRC</name><num>-3822</num></rc> */
	VIRUS_SELFTEST_NO_CRC = -3822,	/* The EXECRC.EXE is missing. */

	/** <rc><name>VIRUS_DLL_READ_ERROR</name><num>-3821</num></rc> */
	VIRUS_DLL_READ_ERROR = -3821,	/* The DLL is missing. */

	/** <rc><name>VIRUS_GET_PROP_ERROR</name><num>-3820</num></rc> */
	VIRUS_GET_PROP_ERROR = -3820,	/* Cannot get virus property. */

	/** <rc><name>VIRUS_SET_PROP_ERROR</name><num>-3819</num></rc> */
	VIRUS_SET_PROP_ERROR = -3819,	/* Cannot set virus property. */

	/** <rc><name>VIRUS_FOUND_AND_REAIRABLE</name><num>-3818</num></rc> */
	VIRUS_FOUND_AND_REPAIRABLE = -3818,	/* Virus was found and is repairable. */

	/** <rc><name>VIRUS_FOUND_AND_DEL</name><num>-3817</num></rc> */
	VIRUS_FOUND_AND_DEL = -3817,	/* Infected file was removed. */

	/** <rc><name>VIRUS_CANNOT_DEL</name><num>-3816</num></rc> */
	VIRUS_CANNOT_DEL = -3816,	/* Infected file cannot be deleted. */

	/** <rc><name>VIRUS_CANNOT_REPAIR</name><num>-3815</num></rc> */
	VIRUS_CANNOT_REPAIR = -3815,	/* Infected file was removed. */

	/** <rc><name>VIRUS_FOUND_AND_REPAIRED</name><num>-3814</num></rc> */
	VIRUS_FOUND_AND_REPAIRED = -3814,	/* Infected file was repaired. */

	/** <rc><name>VIRUS_FOUND_AND_MOVED</name><num>-3813</num></rc> */
	VIRUS_FOUND_AND_MOVED = -3813,	/* Infected file was moved. */

	/** <rc><name>VIRUS_FOUND_AND_NO_MOVED</name><num>-3812</num></rc> */
	VIRUS_FOUND_AND_NO_MOVED = -3812,	/* Infected file could not be moved. */

	/** <rc><name>VIRUS_NO_WRITE</name><num>-3811</num></rc> */
	VIRUS_DIS_NO_WRITE = -3811,	/* Virus scanning disabled when not generating output file. */

	/** <rc><name>ENT_TIMESTAMP_NOT_SUPPORTED</name><num>-3810</num></rc> */
	ENT_TIMESTAMP_NOT_SUPPORTED = -3810, /* Timestamp not supported */

	/** <rc><name>ENT_RR_UNSPECIFIED</name><num>-3809</num></rc> */
	ENT_RR_UNSPECIFIED = -3809, /* Unknown revocation reason */

	/** <rc><name>ENT_RR_KEY_COMPROMISE</name><num>-3808</num></rc> */
	ENT_RR_KEY_COMPROMISE = -3808, /* Key was compromised */

	/** <rc><name>ENT_RR_AFFILIATION_CHANGED</name><num>-3807</num></rc> */
	ENT_RR_AFFILIATION_CHANGED = -3807, /* Affiliation change */

	/** <rc><name>ENT_RR_SUPERSEDED</name><num>-3806</num></rc> */
	ENT_RR_SUPERSEDED = -3806, /* cert was superseded */

	/** <rc><name>ENT_RR_CESSATION_OF_OPERATION</name><num>-3805</num></rc> */
	ENT_RR_CESSATION_OF_OPERATION = -3805, /* cert cessation */

	/* <rc><name>ENT_NOOP_UNDER_SSO</name><num>-3804</num></rc> */
	ENT_NOOP_UNDER_SSO = -3804, /* Single Sign-On will handle this operation now. */

	/* <rc><name>ENT_WRONG_INI_SET</name><num>-3803</num></rc> */
	ENT_WRONG_INI_SET = -3803, /* Ini File setting is incorrect. */

	/* <rc><name>ENT_ALREADY_IMPORTED_IGNORE</name><num>-3802</num></rc> */
	ENT_ALREADY_IMPORTED_IGNORE = -3802, /* RecipList already imported, ignore it. */

	/* <rc><name>ENT_ALREADY_IMPORTED_CREATE_NEW</name><num>-3801</num></rc> */
	ENT_ALREADY_IMPORTED_CREATE_NEW = -3801 /* RecipList already imported, reimport. */
};

enum {
	/** <rc><name>ENT_INVALID_CACHETYPE</name><num>-3800</num></rc> */
	ENT_INVALID_CACHETYPE = -3800,		/* invalid cache type specified */

	/** <rc><name>ENT_INVALID_CACHETYPE</name><num>-3799</num></rc> */
	ENT_X500_MODE_ONLY = -3799,			/* operation can only be performed in X500 mode */

	/** <rc><name>ENT_INVALID_CACHE_OP</name><num>-3798</num></rc> */
	ENT_INVALID_CACHE_OP = -3798,			/* invalid cache operation specified */

	/** <rc><name>ENT_NO_DEFAULT_ALGORITHM</name><num>-3797</num></rc> */
	ENT_NO_DEFAULT_ALGORITHM = -3797,			/* user does not have a default algorithm specified*/

	/** <rc><name>ENT_DEFAULT_VALUE</name><num>-3796</num></rc> */
	ENT_DEFAULT_VALUE = -3796,			/* No client side settings, using default value*/

	/** <rc><name>ENT_KEY_USAGE_NOT_FOUND</name><num>-3795</num></rc> */
	ENT_KEY_USAGE_NOT_FOUND	= -3795,

	/** <rc><name>ENT_FILE_PERMISSIONS_NOT_SET</name><num>-3794</num></rc> */
	ENT_FILE_PERMISSIONS_NOT_SET	= -3794,

	/** <rc><name>ENT_INVALID_DN_SYNTAX</name><num>-3793</num></rc> */
	ENT_INVALID_DN_SYNTAX	= -3793


};

#if !defined( ENTAPI )

enum
{
	/** <rc><name>GKA_FILE_WRITE_ACCESS</name><num>-11999</num></rc> */
	GKA_FILE_WRITE_ACCESS	= -11999,	/* Could not write to Group Key file. */

	/** <rc><name>GKA_FILE_OPEN_ACCESS</name><num>-1191199899</num></rc> */
	GKA_FILE_OPEN_ACCESS	= -11998,	/* Could not open Group Key file. */

	/** <rc><name>GKA_FILE_READ_ACCESS</name><num>-11997</num></rc> */
	GKA_FILE_READ_ACCESS	= -11997,	/* Could not read Group Key file. */

	/** <rc><name>GKA_SECTION_NOT_FOUND</name><num>-11996</num></rc> */
	GKA_SECTION_NOT_FOUND	= -11996,	/* Could not file Section in Group Key file. */

	/** <rc><name>GKA_NO_RECIPIENTS_FOUND</name><num>-11995</num></rc> */
	GKA_NO_RECIPIENTS_FOUND	= -11995,	/* Could not find recipients in list. */

	/** <rc><name>GKA_FILE_TAMPERED</name><num>-11994</num></rc> */
	GKA_FILE_TAMPERED		= -11994,	/* File tampered with or corrupt. */

	/** <rc><name>GKA_INVALID_GROUP_NAME</name><num>-11993</num></rc> */
	GKA_INVALID_GROUP_NAME  = -11993,  /* Invalid Group Key group name. */

	/** <rc><name>CSS_AUTH_NO_PERMISSION</name><num>-11800</num></rc> */
	CSS_AUTH_NO_PERMISSION				= -11800,	/* The Entrust/Authority says NO. */

	/** <rc><name>CSS_AUTH_SAYS_ROAMING</name><num>-11799</num></rc> */
	CSS_AUTH_SAYS_ROAMING				= -11799,	/* The Entrust/Authority says must be roaming */

	/** <rc><name>CSS_AUTH_SAYS_NO_ROAMING</name><num>-11798</num></rc> */
	CSS_AUTH_SAYS_NO_ROAMING			= -11798,	/* The Entrust/Authority says NO roaming */

	/** <rc><name>CSS_AUTH_SAYS_TOKENS</name><num>-11797</num></rc> */
	CSS_AUTH_SAYS_TOKENS				= -11797,	/* The Entrust/Authority says must be token user */

	/** <rc><name>CSS_AUTH_SAYS_NO_PAB</name><num>-11796</num></rc> */
	CSS_AUTH_SAYS_NO_PAB				= -11796,	/* The Entrust/Authority says NO PAB */

	/** <rc><name>CSS_AUTH_SAYS_NO_ROAMING_OR_DESKTOP</name><num>-11795</num></rc> */
	CSS_AUTH_SAYS_NO_ROAMING_OR_DESKTOP	= -11795,	/* The Entrust/Authority says the user cannot be roaming or desktop */

	/** <rc><name>CSS_AUTH_SAYS_NO_SERVER_LOGIN</name><num>-11794</num></rc> */
	CSS_AUTH_SAYS_NO_SERVER_LOGIN		= -11794,	/* The Entrust/Authority says the user cannot use server login. */

	/** <rc><name>CSS_AUTH_SAYS_NO_IDENTITY</name><num>-11793</num></rc> */
	CSS_AUTH_SAYS_IDENTITY				= -11793	/* The Entrust/Authority says the user must use an identity device. */

};

enum {
	/* These are errors that are returned by the Entrust Login Interface */
 
	/* <rc><name>ELI_NOT_PRESENT</name><num>-8599</num></rc> */
	ELI_NOT_PRESENT								= -8689, /* Could not start Entrust Single Login Interface. */
		
	/* <rc><name>ELI_USER_CANCELLED</name><num>-8598</num></rc> */
	ELI_USER_CANCELLED							= -8598, /* User selected "Cancel" */

	/* These are errors that indicate errors communicating the the Entrust Login Interface */
    
    /* <rc><name>BELI_ALLOC_FAILED</name><num>-8599</num></rc> */
	BELI_ALLOC_FAILED							= -8599, /* Could not allocate memory */

	/* <rc><name>BELI_USER_CANCELLED</name><num>-8598</num></rc> */
	BELI_USER_CANCELLED							= -8598, /* Replaced by ELI_USER_CANCELLED now. */

	/* <rc><name>BELI_BUFFER_TOO_BIG</name><num>-8593</num></rc> */
	BELI_BUFFER_TOO_BIG							= -8593, /* Buffer is too big to fit in the Base<->ELI channel */

	/* <rc><name>BELI_BUFFER_TOO_SMALL</name><num>-8592</num></rc> */
	BELI_BUFFER_TOO_SMALL						= -8592, /* Buffer is too small to hold response from the Base<->ELI channel */

	/* <rc><name>BELI_ELI_CORRUPT</name><num>-8591</num></rc> */
	BELI_ELI_CORRUPT							= -8591, /* ELI is corrupt  */

	/* <rc><name>BELI_CANNOT_PARSE_REQUEST_TOKEN</name><num>-8590</num></rc> */
	BELI_CANNOT_PARSE_REQUEST_TOKEN				= -8590, /* Received a bad request token from a base instance */

	/* <rc><name>BELI_CANNOT_CREATE_RESPONSE_TOKEN</name><num>-8589</num></rc> */
	BELI_CANNOT_CREATE_RESPONSE_TOKEN			= -8589, /* Could not create the response a base instance requested */

	/* <rc><name>BELI_ERROR_CREATING_REQUEST_MESSAGE</name><num>-8588</num></rc> */
	BELI_ERROR_CREATING_REQUEST_MESSAGE			= -8588, /* Base failed to generate a LoginInfoRequest message */

	/* <rc><name>BELI_ERROR_PROCESSING_RESPONSE_MESSAGE</name><num>-8587</num></rc> */
	BELI_ERROR_PROCESSING_RESPONSE_MESSAGE		= -8587, /* Base failed to process a LoginInfoResponse */

	/* <rc><name>BELI_ERROR_UNEXPECTED_TOKEN_TYPE</name><num>-8586</num></rc> */
	BELI_ERROR_UNEXPECTED_TOKEN_TYPE			= -8586, /* Base received the wrong kind of response message */

	/* <rc><name>BELI_ERROR_WRONG_BASE_ID</name><num>-8585</num></rc> */
	BELI_ERROR_WRONG_BASE_ID					= -8585, /* Received message was not for this Base instance */

	/* <rc><name>BELI_ERROR_WRONG_VERSION</name><num>-8584</num></rc> */
	BELI_ERROR_WRONG_VERSION					= -8584, /* Received message had the wrong version */

	/* <rc><name>BELI_ERROR_DECODING_PROFILE_NAME</name><num>-8583</num></rc> */
	BELI_ERROR_DECODING_PROFILE_NAME			= -8583, /* Base failed to decode profile name in response message */

	/* <rc><name>BELI_ERROR_CREATING_PASSKEY_CONFOUNDER</name><num>-8582</num></rc> */
	BELI_ERROR_CREATING_PASSKEY_CONFOUNDER		= -8582, /* Base failed to generate a proper passkey confounder */

	/* <rc><name>BELI_ERROR_INVALID_PASSKEY_CONFOUNDER</name><num>-8581</num></rc> */
	BELI_ERROR_INVALID_PASSKEY_CONFOUNDER		= -8581, /* Received passkey confounder was invalid */

	/* <rc><name>BELI_ERROR_NO_PASSKEY</name><num>-8580</num></rc> */
	BELI_ERROR_NO_PASSKEY						= -8580, /* The passkey has been zeroed after the timeout */

	/* <rc><name>BELI_ERROR_CREATING_TIMER</name><num>-8579</num></rc> */
	BELI_ERROR_CREATING_TIMER					= -8579, /* Failed to start the thread that times out the passkey */

	/* <rc><name>BELI_ERROR_COMM_NO_APP_CONTEXT</name><num>-8578</num></rc> */
	BELI_ERROR_COMM_NO_APP_CONTEXT				= -8578, /* Attempted to use Base-ELI communication without a context */

	/* <rc><name>BELI_ERROR_COMM_ALREADY_INITALIZED</name><num>-8577</num></rc> */
	BELI_ERROR_COMM_ALREADY_INITALIZED			= -8577, /* Attempted to create a second Base ID for the same comm object */

	/* <rc><name>BELI_ERROR_COMM_ALREADY_CREATED</name><num>-8576</num></rc> */
	BELI_ERROR_COMM_ALREADY_CREATED				= -8576, /* Attempted to create a second Base-ELI communication object */

	/* <rc><name>BELI_ERROR_PASSWORD_CHANGE_NOT_ALLOWED</name><num>-8575</num></rc> */
	BELI_ERROR_PASSWORD_CHANGE_NOT_ALLOWED		= -8575, /* Base attempted to change the profile password in single login mode */

	/* <rc><name>BELI_NO_REQ_TOKEN_MISSING_PATH</name><num>-8574</num></rc> */
	BELI_NO_REQ_TOKEN_MISSING_PATH				= -8574, /* Specified profile or INI file is not a full path. */

	/* <rc><name>BELI_NO_SUCH_DIR</name><num>-8573</num></rc> */
	BELI_NO_SUCH_DIR							= -8573, /* Path to profile or INI file does not exist. */

	/* <rc><name>ENT_NOOP_UNDER_SSO</name><num>-8572</num></rc> */
	BELI_MULTIPLE_BASES_WITH_THIS_PROFILE		= -8572, /* Cannot perform this operation unless user logged in exactly once */

    /* <rc><name>BELI_APP_REGISTRATION_FAILED</name><num>-8570</num></rc> */
	BELI_APP_REGISTRATION_FAILED                = -8570, /* App registration failed */

    BELI_BASE_UNKNOWN_ELI_REQUEST               = -8569, /* Base has received a request from ELI it does not understand */
	
    BELI_CAN_NOT_LOGOUT_LEGACY                  = -8568, /* Base can not logout on ELI request because it supports a legacy application */
	
    BELI_CAN_NOT_LOGOUT_BUSY                    = -8567, /* Base can not logout on ELI request because the application is busy */
	
    BELI_ERROR_CREATING_RX_THREAD               = -8566, /* failed to start the thread that handles messages from ELI */
	
    BELI_ERROR_DISCONNECTED                     = -8565, /* Error communicating with ELI because connection was closed */
	
    BELI_ERROR_NOT_CONNECTED_YET                = -8564, /* Error, attempting to communicate without a valid connection */

	/* <rc><name>EXPRESS_MSG_CORRUPT</name><num>-8550</num></rc> */
	EXPRESS_MSG_CORRUPT							= -8550, /* Entrust format email message has been tampered with */
	
	/* These always show up as warnings */

	/* <rc><name>BELI_ALREADY_STARTED_ELI</name><num>-8548</num></rc> */
	BELI_ALREADY_STARTED_ELI					= -8548 /* ELI is already started */
};

/* Timestamp errors */
enum{

	/* <rc><name>TSTAMP_UNEXPECTED_NULL_POINTER</name><num>-8099</num></rc> */
	TSTAMP_UNEXPECTED_NULL_POINTER				= -8099, /* Unexpected NULL pointer. */

	/* <rc><name>TSTAMP_NOT_SUPPORTED</name><num>-8098</num></rc> */
	TSTAMP_NOT_SUPPORTED						= -8098, /* Timestamp is not supported in current Entrust DLL. */

	/* <rc><name>TSTAMP_HASHER_NOT_INIT</name><num>-8097</num></rc> */
	TSTAMP_HASHER_NOT_INIT 						= -8097, /* Timestamp hasher has not been initialized. */

	/* <rc><name>TSTAMP_CANCELLED</name><num>-8096</num></rc> */
	TSTAMP_CANCELLED 							= -8096, /* Timestamp operation was cancelled. */

	/* <rc><name>TSTAMP_HASH_CORRUPTED</name><num>-8095</num></rc> */
	TSTAMP_HASH_CORRUPTED 						= -8095, /* Timestamp hash is corrupted. */

	/* <rc><name>TSTAMP_UNKNOWN_SIGN_ALGORITHM</name><num>-8094</num></rc> */
	TSTAMP_UNKNOWN_SIGN_ALGORITHM 				= -8094, /* Received an unknown timestamp signing algorithm from the server. */

	/* <rc><name>TSTAMP_NO_SERVER_CONFIG</name><num>-8093</num></rc> */
	TSTAMP_NO_SERVER_CONFIG 					= -8093, /* No timestamp server configuration - cannot connect to timestamp server. */

	/* <rc><name>TSTAMP_UNKNOWN_HASH_ALGORITHM</name><num>-8092</num></rc> */
	TSTAMP_UNKNOWN_HASH_ALGORITHM 				= -8092, /* Received an unknown timestamp hash algorithm from the server. */

	/* <rc><name>TSTAMP_UNSUPPORTED_HASH_ALGORITHM</name><num>-8091</num></rc> */
	TSTAMP_UNSUPPORTED_HASH_ALGORITHM 			= -8091, /* Hash algorithm not supported - check your Timestamp server configuration. */

	/* <rc><name>TSTAMP_NO_RESPONSE_BUFFER</name><num>-8090</num></rc> */
	TSTAMP_NO_RESPONSE_BUFFER 					= -8090, /* There is no timestamp response buffer available. */

	/* <rc><name>TSTAMP_ERROR_RESPONSE_FROM_SERVER</name><num>-8089</num></rc> */
	TSTAMP_ERROR_RESPONSE_FROM_SERVER			= -8089, /* Reply error from timestamp server. */

	/* <rc><name>TSTAMP_UNEXPECTED_RESPONSE_FROM_SERVER</name><num>-8088</num></rc> */
	TSTAMP_UNEXPECTED_RESPONSE_FROM_SERVER		= -8088, /* Unexpected reply error from timestamp server. */

	/* <rc><name>TSTAMP_TIMEOUT_ERROR</name><num>-8087</num></rc> */
	TSTAMP_TIMEOUT_ERROR 						= -8087, /* Timeout while waiting for a reply from the timestamp server. */

	/* <rc><name>TSTAMP_NO_SOCKET</name><num>-8086</num></rc> */
	TSTAMP_NO_SOCKET 							= -8086, /* Unable to send a request to the timestamp server - no socket available. */

	/* <rc><name>TSTAMP_NO_SERVER</name><num>-8085</num></rc> */
	TSTAMP_NO_SERVER 							= -8085, /* No timestamp server specified - cannot connect. */

	/* <rc><name>TSTAMP_CANNOT_CONNECT</name><num>-8084</num></rc> */
	TSTAMP_CANNOT_CONNECT 						= -8084, /* Unable to connect to the timestamp server - check your configuration and check that the server is running. */

	/* <rc><name>TSTAMP_COMM_ERROR</name><num>-8083</num></rc> */
	TSTAMP_COMM_ERROR 							= -8083, /* Communication subsystem error - check your network configuration. */

	/* <rc><name>TSTAMP_MISMATCHED_HASHES</name><num>-8081</num></rc> */
	TSTAMP_MISMATCHED_HASHES 					= -8081, /* The timestamp hash does not match the computed hash -- timestamp is invalid. */

	/* <rc><name>TSTAMP_ERROR_BUILDING_PKCS7_OBJECT</name><num>-8080</num></rc> */
	TSTAMP_ERROR_BUILDING_PKCS7_OBJECT			= -8080, /* Error constructing output data (PKCS#7) */

	/* <rc><name>TSTAMP_INVALID_PKCS7_TIMESTAMP_OBJECT</name><num>-8079</num></rc> */
	TSTAMP_INVALID_PKCS7_TIMESTAMP_OBJECT		= -8079, /* Error decoding input data (PKCS#7) */

	/* <rc><name>TSTAMP_PKCS7_SIGNERS_CERT_NOT_SUPPLIED</name><num>-8078</num></rc> */
	TSTAMP_PKCS7_SIGNERS_CERT_NOT_SUPPLIED		= -8078, /* Signer's certificate not found in timestamped data (PKCS#7) */

	/* <rc><name>TSTAMP_PKCS7_EXTCERT_NOT_SUPPORTED</name><num>-8077</num></rc> */
	TSTAMP_PKCS7_EXTCERT_NOT_SUPPORTED			= -8077, /* Signer's certificate is in the extended format which is not supported (PKCS#7) */

	/* <rc><name>TSTAMP_SERVER_DID_NOT_GRANT_REQUEST</name><num>-8076</num></rc> */
	TSTAMP_SERVER_DID_NOT_GRANT_REQUEST			= -8076, /* The server did not grant your timestamping request. */

	/* <rc><name>TSTAMP_TOKEN_NOT_SIGNED_BY_TIMESTAMPER</name><num>-8075</num></rc> */
	TSTAMP_TOKEN_NOT_SIGNED_BY_TIMESTAMPER		= -8075, /* The timestamp was not signed by a timestamping agent. */

	/* <rc><name>TSTAMP_SERVER_CERT_NOT_IN_TOKEN</name><num>-8074</num></rc> */
	TSTAMP_SERVER_CERT_NOT_IN_TOKEN				= -8074, /* The timestamping agent's certificate was not found in the timestamp. */

	/* <rc><name>TSTAMP_SERVER_CA_CERT_NOT_IN_TOKEN</name><num>-8073</num></rc> */
	TSTAMP_SERVER_CA_CERT_NOT_IN_TOKEN			= -8073, /* The certificate of the timestamping agent's certificate issuer was not found in the timestamp. */

	/* <rc><name>TSTAMP_NOT_A_TIMESTAMPING_PROFILE</name><num>-8072</num></rc> */
	TSTAMP_NOT_A_TIMESTAMPING_PROFILE			= -8072, /* The profile is not a timestamping agent profile. */

	/* <rc><name>TSTAMP_UNKNOWN_POLICY</name><num>-8071</num></rc> */
	TSTAMP_UNKNOWN_POLICY						= -8071, /* The timestamp contains an unknown policy identifier. */

	/* <rc><name>TSTAMP_UNKNOWN_TSA</name><num>-8070</num></rc> */
	TSTAMP_UNKNOWN_TSA 							= -8070, /* The timestamp was generated by an unknown timestamping agent. */

	/* <rc><name>TSTAMP_TSA_CERT_REVOKED</name><num>-8069</num></rc> */
	TSTAMP_TSA_CERT_REVOKED 					= -8069, /* The certificate of the timestamping agent is revoked. */

	/* <rc><name>TSTAMP_TSA_PRIV_KEY_EXPIRED_AT_TC</name><num>-8068</num></rc> */
	TSTAMP_TSA_PRIV_KEY_EXPIRED_AT_TC			= -8068, /* The timestamp was signed with an expired private key -- timestamp is invalid. */	

	/* <rc><name>TSTAMP_ERROR_RETRIEVING_SERVER_LIST</name><num>-8067</num></rc> */
	TSTAMP_ERROR_RETRIEVING_SERVER_LIST			= -8067 /* The list of timestamp servers could not be retrieved from the policy certificate. */
};

#if !defined( IDUP )

enum {

	// LDAP errors

	/** <rc><name>LDAP_LDAP_SUCCESS</name><num>-6299</num></rc> */
	LDAP_LDAP_SUCCESS						= -6299,		/* Successful ldap operation returns this */

	/** <rc><name>LDAP_LDAP_OPERATIONS_ERROR</name><num>-6298</num></rc> */
	LDAP_LDAP_OPERATIONS_ERROR				= -6298,		/* Operations error */

	/** <rc><name>LDAP_LDAP_PROTOCOL_ERROR</name><num>-6297</num></rc> */
	LDAP_LDAP_PROTOCOL_ERROR				= -6297,		/* Protocol error */

	/** <rc><name>LDAP_LDAP_TIMELIMIT_EXCEEDED</name><num>-6296</num></rc> */
	LDAP_LDAP_TIMELIMIT_EXCEEDED			= -6296,		/* Time limit exceeded */

	/** <rc><name>LDAP_LDAP_SIZELIMIT_EXCEEDED</name><num>-6295</num></rc> */
	LDAP_LDAP_SIZELIMIT_EXCEEDED			= -6295,		/* Size limit exceeded */

	/** <rc><name>LDAP_LDAP_COMPARE_FALSE</name><num>-6294</num></rc> */
	LDAP_LDAP_COMPARE_FALSE					= -6294,		/* Compare false */

	/** <rc><name>LDAP_LDAP_COMPARE_TRUE</name><num>-6293</num></rc> */
	LDAP_LDAP_COMPARE_TRUE					= -6293,		/* Compare true */

	/** <rc><name>LDAP_LDAP_STRONG_AUTH_NOT_SUPPORTED</name><num>-6292</num></rc> */
	LDAP_LDAP_STRONG_AUTH_NOT_SUPPORTED		= -6292,		/* Strong authentication not supported */

	/** <rc><name>LDAP_LDAP_STRONG_AUTH_REQUIRED</name><num>-6291</num></rc> */
	LDAP_LDAP_STRONG_AUTH_REQUIRED			= -6291,		/* Strong authentication required */

	/** <rc><name>LDAP_LDAP_PARTIAL_RESULTS</name><num>-6290</num></rc> */
	LDAP_LDAP_PARTIAL_RESULTS				= -6290,		/* Partial results were returned */

	/** <rc><name>LDAP_LDAP_REFERRAL</name><num>-6289</num></rc> */
	LDAP_LDAP_REFERRAL						= -6289,		/* Indicates next field contains a referral */

	/** <rc><name>LDAP_LDAP_ADMIN_LIMIT_EXCEEDED</name><num>-6288</num></rc> */
	LDAP_LDAP_ADMIN_LIMIT_EXCEEDED			= -6288,		/* Admin's limit has been exceeded */

	/** <rc><name>LDAP_LDAP_UNAVAILABLE_CRITICAL_EXTENSION</name><num>-6287</num></rc> */
	LDAP_LDAP_UNAVAILABLE_CRITICAL_EXTENSION	= -6287,	/* Unavailable critical extension */

	/** <rc><name>LDAP_LDAP_CONFIDENTIALITY_REQUIRED</name><num>-6286</num></rc> */
	LDAP_LDAP_CONFIDENTIALITY_REQUIRED		= -6286,		/* Confidentiality required */

	/** <rc><name>LDAP_LDAP_SASL_BIND_IN_PROGRESS</name><num>-6285</num></rc> */
	LDAP_LDAP_SASL_BIND_IN_PROGRESS			= -6285,		/* SASL bind is in progress */

	/** <rc><name>LDAP_LDAP_NO_SUCH_ATTRIBUTE</name><num>-6283</num></rc> */
	LDAP_LDAP_NO_SUCH_ATTRIBUTE				= -6283,		/* No such attribute */

	/** <rc><name>LDAP_LDAP_UNDEFINED_TYPE</name><num>-6282</num></rc> */
	LDAP_LDAP_UNDEFINED_TYPE				= -6282,		/* Undefined attribute type */

	/** <rc><name>LDAP_LDAP_INAPPROPRIATE_MATCHING</name><num>-6281</num></rc> */
	LDAP_LDAP_INAPPROPRIATE_MATCHING		= -6281,		/* Inappropriate matching */

	/** <rc><name>LDAP_LDAP_CONSTRAINT_VIOLATION</name><num>-6280</num></rc> */
	LDAP_LDAP_CONSTRAINT_VIOLATION			= -6280,		/* Constraint violation */

	/** <rc><name>LDAP_LDAP_TYPE_OR_VALUE_EXISTS</name><num>-6279</num></rc> */
	LDAP_LDAP_TYPE_OR_VALUE_EXISTS			= -6279,		/* Type or value exists */

	/** <rc><name>LDAP_LDAP_INVALID_SYNTAX</name><num>-6278</num></rc> */
	LDAP_LDAP_INVALID_SYNTAX				= -6278,		/* Invalid syntax */

	/** <rc><name>LDAP_LDAP_NO_SUCH_OBJECT</name><num>-6267</num></rc> */
	LDAP_LDAP_NO_SUCH_OBJECT				= -6267,		/* No such entry found in directory */

	/** <rc><name>LDAP_LDAP_ALIAS_PROBLEM</name><num>-6266</num></rc> */
	LDAP_LDAP_ALIAS_PROBLEM					= -6266,		/* Alias problem */

	/** <rc><name>LDAP_LDAP_INVALID_DN_SYNTAX</name><num>-6265</num></rc> */
	LDAP_LDAP_INVALID_DN_SYNTAX				= -6265,		/* Invalid DN syntax */

	/** <rc><name>LDAP_LDAP_IS_LEAF</name><num>-6264</num></rc> */
	LDAP_LDAP_IS_LEAF						= -6264,		/* Object is a leaf */

	/** <rc><name>LDAP_LDAP_ALIAS_DEREF_PROBLEM</name><num>-6263</num></rc> */
	LDAP_LDAP_ALIAS_DEREF_PROBLEM			= -6263,		/* Alias dereferencing problem */
	
	/** <rc><name>LDAP_LDAP_INAPPROPRIATE_AUTH</name><num>-6251</num></rc> */
	LDAP_LDAP_INAPPROPRIATE_AUTH			= -6251,		/* Inappropriate authentication */

	/** <rc><name>LDAP_LDAP_INVALID_CREDENTIALS</name><num>-6250</num></rc> */
	LDAP_LDAP_INVALID_CREDENTIALS			= -6250,		/* Invalid credentials */

	/** <rc><name>LDAP_LDAP_INSUFFICIENT_ACCESS</name><num>-6249</num></rc> */
	LDAP_LDAP_INSUFFICIENT_ACCESS			= -6249,		/* Insufficient access */

	/** <rc><name>LDAP_LDAP_BUSY</name><num>-6248</num></rc> */
	LDAP_LDAP_BUSY							= -6248,		/* DSA is busy */

	/** <rc><name>LDAP_LDAP_UNAVAILABLE</name><num>-6247</num></rc> */
	LDAP_LDAP_UNAVAILABLE					= -6247,		/* DSA is unavailable */

	/** <rc><name>LDAP_LDAP_UNWILLING_TO_PERFORM</name><num>-6246</num></rc> */
	LDAP_LDAP_UNWILLING_TO_PERFORM			= -6246,		/* DSA is unwilling to perform */

	/** <rc><name>LDAP_LDAP_LOOP_DETECT</name><num>-6245</num></rc> */
	LDAP_LDAP_LOOP_DETECT					= -6245,		/* Loop detected */

	/** <rc><name>LDAP_LDAP_NAMING_VIOLATION</name><num>-6235</num></rc> */
	LDAP_LDAP_NAMING_VIOLATION				= -6235,		/* Naming violation */

	/** <rc><name>LDAP_LDAP_OBJECT_CLASS_VIOLATION</name><num>-6234</num></rc> */
	LDAP_LDAP_OBJECT_CLASS_VIOLATION		= -6234,		/* Object class violation */

	/** <rc><name>LDAP_LDAP_NOT_ALLOWED_ON_NONLEAF</name><num>-6233</num></rc> */
	LDAP_LDAP_NOT_ALLOWED_ON_NONLEAF		= -6233,		/* Operation not allowed on nonleaf */

	/** <rc><name>LDAP_LDAP_NOT_ALLOWED_ON_RDN</name><num>-6232</num></rc> */
	LDAP_LDAP_NOT_ALLOWED_ON_RDN			= -6232,		/* Operation not allowed on RDN */

	/** <rc><name>LDAP_LDAP_ALREADY_EXISTS</name><num>-6231</num></rc> */
	LDAP_LDAP_ALREADY_EXISTS				= -6231,		/* Already exists */

	/** <rc><name>LDAP_LDAP_NO_OBJECT_CLASS_MODS</name><num>-6230</num></rc> */
	LDAP_LDAP_NO_OBJECT_CLASS_MODS			= -6230,		/* Cannot modify object class */

	/** <rc><name>LDAP_LDAP_RESULTS_TOO_LARGE</name><num>-6229</num></rc> */
	LDAP_LDAP_RESULTS_TOO_LARGE				= -6229,		/* Results too large */

	/** <rc><name>LDAP_LDAP_AFFECTS_MULTIPLE_DSAS</name><num>-6228</num></rc> */
	LDAP_LDAP_AFFECTS_MULTIPLE_DSAS			= -6228,		/* Operation affects multiple DSAs */

	/** <rc><name>LDAP_LDAP_OTHER</name><num>-6219</num></rc> */
	LDAP_LDAP_OTHER							= -6219,		/* Unknown error */

	/** <rc><name>LDAP_LDAP_SERVER_DOWN</name><num>-6218</num></rc> */
	LDAP_LDAP_SERVER_DOWN					= -6218,		/* Can't contact LDAP server */

	/** <rc><name>LDAP_LDAP_LOCAL_ERROR</name><num>-6217</num></rc> */
	LDAP_LDAP_LOCAL_ERROR					= -6217,		/* Local error */

	/** <rc><name>LDAP_LDAP_ENCODING_ERROR</name><num>-6216</num></rc> */
	LDAP_LDAP_ENCODING_ERROR				= -6216,		/* Encoding error */

	/** <rc><name>LDAP_LDAP_DECODING_ERROR</name><num>-6215</num></rc> */
	LDAP_LDAP_DECODING_ERROR				= -6215,		/* Decoding error */

	/** <rc><name>LDAP_LDAP_TIMEOUT</name><num>-6214</num></rc> */
	LDAP_LDAP_TIMEOUT						= -6214,		/* Timed out */

	/** <rc><name>LDAP_LDAP_AUTH_UNKNOWN</name><num>-6213</num></rc> */
	LDAP_LDAP_AUTH_UNKNOWN					= -6213,		/* Unknown authentication method */

	/** <rc><name>LDAP_LDAP_FILTER_ERROR</name><num>-6212</num></rc> */
	LDAP_LDAP_FILTER_ERROR					= -6212,		/* Bad search filter */

	/** <rc><name>LDAP_LDAP_USER_CANCELLED</name><num>-6211</num></rc> */
	LDAP_LDAP_USER_CANCELLED				= -6211,		/* User cancelled operation */

	/** <rc><name>LDAP_LDAP_PARAM_ERROR</name><num>-6210</num></rc> */
	LDAP_LDAP_PARAM_ERROR					= -6210,		/* Bad parameter to an ldap routine */

	/** <rc><name>LDAP_LDAP_NO_MEMORY</name><num>-6209</num></rc> */
	LDAP_LDAP_NO_MEMORY						= -6209,		/* Memory allocation failure */

	/** <rc><name>LDAP_LDAP_CONNECT_ERROR</name><num>-6208</num></rc> */
	LDAP_LDAP_CONNECT_ERROR					= -6208,		/* Failed to establish or maintain connection */

	/** <rc><name>LDAP_LDAP_NOT_SUPPORTED</name><num>-6207</num></rc> */
	LDAP_LDAP_NOT_SUPPORTED					= -6207,		/* Option not supported */

	/** <rc><name>LDAP_LDAP_CONTROL_NOT_FOUND</name><num>-6206</num></rc> */
	LDAP_LDAP_CONTROL_NOT_FOUND				= -6206,		/* Control not found */

	/** <rc><name>LDAP_LDAP_NO_RESULTS_RETURNED</name><num>-6205</num></rc> */
	LDAP_LDAP_NO_RESULTS_RETURNED			= -6205,		/* No results returned from query */

	/** <rc><name>LDAP_LDAP_MORE_RESULTS_TO_RETURN</name><num>-6204</num></rc> */
	LDAP_LDAP_MORE_RESULTS_TO_RETURN		= -6204,		/* More results are available to return */

	/** <rc><name>LDAP_LDAP_CLIENT_LOOP</name><num>-6203</num></rc> */
	LDAP_LDAP_CLIENT_LOOP					= -6203,		/* Client loop detected */

	/** <rc><name>LDAP_LDAP_REFERRAL_LIMIT_EXCEEDED</name><num>-6202</num></rc> */
	LDAP_LDAP_REFERRAL_LIMIT_EXCEEDED		= -6202,		/* Max. number of referrals exceeded */

	/** <rc><name>LDAP_LDAP_UNSOLICITED</name><num>-6201</num></rc> */
	LDAP_LDAP_UNSOLICITED					= -6201,		/* Unsolicited notification is detected */

	/** <rc><name>LDAP_LDAP_NTLM_BIND_ERROR</name><num>-12400</num></rc> */
	LDAP_LDAP_NTLM_BIND_ERROR				= -12400,		/* NTLM bind failed */

	/** <rc><name>LDAP_LDAP_NTLM_ALREADY_INIT</name><num>-12399</num></rc> */
	LDAP_LDAP_NTLM_ALREADY_INIT				= -12399,		/* NTLM module already initialized */

	/** <rc><name>LDAP_LDAP_NTLM_LOAD_DLL</name><num>-12398</num></rc> */
	LDAP_LDAP_NTLM_LOAD_DLL					= -12398,		/* Failed to load DLL security.dll */

	/** <rc><name>LDAP_LDAP_NTLM_GET_SEC_INIT</name><num>-12397</num></rc> */
	LDAP_LDAP_NTLM_GET_SEC_INIT				= -12397,		/* Could not get security initialization routine */

	/** <rc><name>LDAP_LDAP_NTLM_SEC_INIT</name><num>-12396</num></rc> */
	LDAP_LDAP_NTLM_SEC_INIT					= -12396,		/* Failed to initialize the security package */

	/** <rc><name>LDAP_LDAP_NTLM_NOT_INIT</name><num>-12395</num></rc> */
	LDAP_LDAP_NTLM_NOT_INIT					= -12395,		/* NTLM module not initialized */

	/** <rc><name>LDAP_LDAP_NTLM_MISSING_NTLM_PACK</name><num>-12394</num></rc> */
	LDAP_LDAP_NTLM_MISSING_NTLM_PACK		= -12394,		/* NTLM Package missing */

	/** <rc><name>LDAP_LDAP_NTLM_ACQ_CREDS</name><num>-12393</num></rc> */
	LDAP_LDAP_NTLM_ACQ_CREDS				= -12393,		/* Failed to acquire credentials */

	/** <rc><name>LDAP_LDAP_NTLM_INIT_CONTEXT</name><num>-12392</num></rc> */
	LDAP_LDAP_NTLM_INIT_CONTEXT				= -12392,		/* Failed to initizalize context */

	/** <rc><name>LDAP_LDAP_NTLM_NOT_SUPPORTED</name><num>-12391</num></rc> */
	LDAP_LDAP_NTLM_NOT_SUPPORTED			= -12391,		/* NTLM not supported */

	/** <rc><name>LDAP_LDAP_NTLM_PARSE_REQ</name><num>-12390</num></rc> */
	LDAP_LDAP_NTLM_PARSE_REQ				= -12390,		/* Parse error in NTLM request */

	/** <rc><name>LDAP_LDAP_NTLM_PARSE_NEG</name><num>-12389</num></rc> */
	LDAP_LDAP_NTLM_PARSE_NEG				= -12389,		/* Parse error in NTLM negociate */

	/** <rc><name>LDAP_LDAP_NTLM_CLOSE_MODULE</name><num>-12388</num></rc> */
	LDAP_LDAP_NTLM_CLOSE_MODULE				= -12388 		/* Error while closing NTLM module */

};

enum {

	/** <rc><name>ETSMIME_NOT_SUPPORTED</name><num>-4099</num></rc> */
	ETSMIME_NOT_SUPPORTED                      = -4099, /*  "The requested S/MIME capability is not supported" */

	/** <rc><name>ETSMIME_NOT_AVAILABLE</name><num>-4098</num></rc> */
	ETSMIME_NOT_AVAILABLE                      = -4098, /*  "S/MIME support has not been enabled in this version of Entrust" */

	/** <rc><name>ETSMIME_CERT_VALIDATION_FAILED</name><num>-4097</num></rc> */
	ETSMIME_CERT_VALIDATION_FAILED				= -4097, /*  "EntrustFileSMIME::Certificate validation failed" */

	/** <rc><name>ETSMIME_CONFIDENTIALITY_ALG_NOT_SELECTED</name><num>-4096</num></rc> */
	ETSMIME_CONFIDENTIALITY_ALG_NOT_SELECTED	= -4096, /*  "EntrustFileSMIME::SetConfidentialityAlgorithm() was not called or failed" */

	/** <rc><name>ETSMIME_CORRUPT_SMIME_SEQUENCE</name><num>-4095</num></rc> */
	ETSMIME_CORRUPT_SMIME_SEQUENCE				= -4095, /*  "EntrustFileSMIME::S/MIME message is corrupt" */

	/** <rc><name>ETSMIME_ENCODED_HEADER_TOOBIG</name><num>-4094</num></rc> */
	ETSMIME_ENCODED_HEADER_TOOBIG				= -4094, /*  "EntrustFileSMIME::Encoded header is too big to be loaded in memory" */

	/** <rc><name>ETSMIME_INNERCONTENT_NOT_DATA</name><num>-4093</num></rc> */
	ETSMIME_INNERCONTENT_NOT_DATA				= -4093, /*  "EntrustFileSMIME::The S/MIME message does not have data as inner content" */

	/** <rc><name>ETSMIME_INTEGRITY_CHECK_FAILED</name><num>-4092</num></rc> */
	ETSMIME_INTEGRITY_CHECK_FAILED             = -4092, /*  "The computed content checksum did not match the value in the received S/MIME header" */

	/** <rc><name>ETSMIME_INTERNAL_ERROR</name><num>-4091</num></rc> */
	ETSMIME_INTERNAL_ERROR                     = -4091, /*  "An internal S/MIME integrity/sanity check failed" */

	/** <rc><name>ETSMIME_INVALID_PARAMETER</name><num>-4090</num></rc> */
	ETSMIME_INVALID_PARAMETER                  = -4090, /*  "An S/MIME function was supplied invalid data" */

	/** <rc><name>ETSMIME_INAPPROPRIATE_SIGNATURE_ALG</name><num>-4089</num></rc> */
	ETSMIME_INAPPROPRIATE_SIGNATURE_ALG			= -4089, /*  "The signature algorithm cannot be used with the given key." */

	/** <rc><name>ETSMIME_INVALID_SMIME_SEQUENCE</name><num>-4069</num></rc> */
	ETSMIME_INVALID_SMIME_SEQUENCE				= -4069, /*  "EntrustFileSMIME::The data does not contain a valid S/MIME message" */

	/** <rc><name>ETSMIME_MESSAGEDIGEST_ALG_NOT_SELECTED</name><num>-4068</num></rc> */
	ETSMIME_MESSAGEDIGEST_ALG_NOT_SELECTED		= -4068, /*  "EntrustFileSMIME::SetIntegrityAlgorithm() was not called or failed" */

	/** <rc><name>ETSMIME_NOTHING_TO_UNPROTECT</name><num>-4067</num></rc> */
	ETSMIME_NOTHING_TO_UNPROTECT				= -4067, /*  "EntrustFileSMIME::The S/MIME message is empty" */

	/** <rc><name>ETSMIME_SIGNATURE_ALGORITHM_NOT_RECEIVED</name><num>-4066</num></rc> */
	ETSMIME_SIGNATURE_ALGORITHM_NOT_RECEIVED    = -4066, /*  "The S/MIME message is missing a SignatureAlgorithm identifier" */

	/** <rc><name>ETSMIME_SIGNATURE_MESSAGEDIGEST_ALG_MISMATCH</name><num>-4065</num></rc> */
	ETSMIME_SIGNATURE_MESSAGEDIGEST_ALG_MISMATCH	= -4065, /*  "EntrustFileSMIME::The S/MIME signature and integrity algorithms must use the same hash type" */

	/** <rc><name>ETSMIME_SIGNATURE_VALIDATION_FAILED</name><num>-4064</num></rc> */
	ETSMIME_SIGNATURE_VALIDATION_FAILED		= -4064, /*  "EntrustFileSMIME::The signature validation failed" */

	/** <rc><name>ETSMIME_UNABLE_TO_EXTRACT_CERTIFICATE</name><num>-3763</num></rc> */
	ETSMIME_UNABLE_TO_EXTRACT_CERTIFICATE       = -4063, /*  "Error getting the X500_Certificate from a Certificate" */

	/** <rc><name>ETSMIME_UNRECOGNIZED_VERSION</name><num>-4062</num></rc> */
	ETSMIME_UNRECOGNIZED_VERSION				= -4062, /*  "EntrustFileSMIME::S/MIME message contains unrecognized version sequence" */

	/** <rc><name>ETSMIME_UNSUPPORTED_MESSAGEDIGEST_ALG</name><num>-4061</num></rc> */
	ETSMIME_UNSUPPORTED_MESSAGEDIGEST_ALG		= -4061, /*  "EntrustFileSMIME::the requested integrity algorithm is unsupported" */

	/** <rc><name>ETSMIME_FILE_WRITE_ERROR</name><num>-4060</num></rc> */
	ETSMIME_FILE_WRITE_ERROR					= -4060, /*  "EntrustFileSMIME::File write error occured" */

	/** <rc><name>ETSMIME_FILE_READ_ERROR</name><num>-4059</num></rc> */
	ETSMIME_FILE_READ_ERROR					= -4059, /*  "EntrustFileSMIME::File read error occured" */

	/** <rc><name>ETSMIME_FILE_SEEK_ERROR</name><num>-4058</num></rc> */
	ETSMIME_FILE_SEEK_ERROR					= -4058, /*  "EntrustFileSMIME::File seek error occured" */

	/** <rc><name>ETSMIME_FILE_CLOSE_ERROR</name><num>-4057</num></rc> */
	ETSMIME_FILE_CLOSE_ERROR					= -4057, /*  "EntrustFileSMIME::File close error occured" */

	/** <rc><name>ETSMIME_UNSUPPORTED_SIGNATURE_ALG</name><num>-4056</num></rc> */
	ETSMIME_UNSUPPORTED_SIGNATURE_ALG          = -4056, /*  "The requested S/MIME Signature algorithm is not supported" */

	/** <rc><name>ETSMIME_UNEXPECTED_NULL_PTR</name><num>-4055</num></rc> */
	ETSMIME_UNEXPECTED_NULL_PTR				= -4055, /*  "Unexpected NULL pointer" */

	/** <rc><name>ETSMIME_ENC_WITH_VER_CERT</name><num>-4054</num></rc> */
	ETSMIME_ENC_WITH_VER_CERT				= -4054, /*  "Data was encrypted with your verification certificate" */

	/** <rc><name></name>ETSMIME_SIGNATURE_ALGORITHM_NOT_ALLOWED<num>-4053</num></rc> */
	ETSMIME_SIGNATURE_ALGORITHM_NOT_ALLOWED	= -4053, /*  "EntrustFileSMIME::The signature validation algorithm is not allowed." */

	/** <rc><name>ETSMIME_KEY_ENCRYPTION_ALGORITHM_NOT_ALLOWED</name><num>-4052</num></rc> */
	ETSMIME_KEY_ENCRYPTION_ALGORITHM_NOT_ALLOWED	= -4052 /*  "EntrustFileSMIME::The key decryption algorithm is not allowed." */

};

enum {

	/** <rc><name>COMM_ATTCERT_NOT_IN_CACHE</name><num>-1561</num></rc> */
	COMM_ATTCERT_NOT_IN_CACHE = -1561,		 /* Policy certificate is required but could 
	not be found in the local cache and the Directory is unavailable. */

	/** <rc><name>COMM_SEP_CLIENT_WRONG_STATE_DISABLED_MGR</name><num>-1639</num></rc> */
	COMM_SEP_CLIENT_WRONG_STATE_DISABLED_MGR = -1639		/* Operation not allowed. 
	Your identity has been disabled. */

};

enum {

	// password checking error codes

	/** <rc><name>PROF_PASSWORD_TOO_SHORT</name><num>-591</num></rc> */
	PROF_PASSWORD_TOO_SHORT					= -591,		/* password was too short */

	/** <rc><name>PROF_PASSWORD_TOO_MANY_SAMECHAR</name><num>-590</num></rc> */
	PROF_PASSWORD_TOO_MANY_SAMECHAR			= -590,		/* same char repeated too often */

	/** <rc><name>PROF_PASSWORD_NO_LOWER_CASE</name><num>-589</num></rc> */
	PROF_PASSWORD_NO_LOWER_CASE				= -589,		/* does not contain lower case char, which is required */

	/** <rc><name>PROF_PASSWORD_NO_UPPER_CASE</name><num>-588</num></rc> */
	PROF_PASSWORD_NO_UPPER_CASE				= -588,		/* does not contain upper case char, which is required */

	/** <rc><name>PROF_PASSWORD_HAS_USER_NAME</name><num>-587</num></rc> */
	PROF_PASSWORD_HAS_USER_NAME				= -587,		/* has substring of profile name */

	/** <rc><name>PROF_PASSWORD_NO_NONALPHA</name><num>-586</num></rc> */
	PROF_PASSWORD_NO_NONALPHA				= -586,		/* does not contain a nonalphanumeric char, which is required */

	/** <rc><name>PROF_PASSWORD_NO_DIGIT</name><num>-585</num></rc> */
	PROF_PASSWORD_NO_DIGIT					= -585,		/* does not contain a digit, which is required */

	/** <rc><name>PROF_PASSWORD_NO_BLANK</name><num>-584</num></rc> */
	PROF_PASSWORD_NO_BLANK					= -584,		/* password must not contain blank characters */

	/** <rc><name>PROF_PASSWORD_NO_CONSECUTIVE_DUPLICATE</name><num>-583</num></rc> */
	PROF_PASSWORD_NO_CONSECUTIVE_DUPLICATE	= -583,		/* same character occurs consecutively */

	/** <rc><name>PROF_PASSWORD_NO_RECENTLY_USED</name><num>-582</num></rc> */
	PROF_PASSWORD_NO_RECENTLY_USED			= -582,		/* this is contained in the password history and therefore cannot be used */

	/** <rc><name>PROF_PASSWORD_TOO_LONG</name><num>-581</num></rc> */
	PROF_PASSWORD_TOO_LONG					= -581		/* password too long */

};

#endif

enum {

	/** <rc><name>CMPR_DEF_INIT_FAILURE</name><num>-1899</num></rc> */
	CMPR_DEF_INIT_FAILURE	= -1899, /* Deflation initialization failure */

	/** <rc><name>CMPR_INDATA_OVERFLOW</name><num>-1898</num></rc> */
	CMPR_INDATA_OVERFLOW	= -1898, /* More than 64KB was passed in to (de)compress */

	/** <rc><name>CMPR_DEF_ERROR</name><num>-1897</num></rc> */
	CMPR_DEF_ERROR			= -1897, /* Deflation error */

	/** <rc><name>CMPR_DEF_END_FAILURE</name><num>-1896</num></rc> */
	CMPR_DEF_END_FAILURE	= -1896, /* End of deflation error */

	/** <rc><name>CMPR_INF_INIT_FAILURE</name><num>-1895</num></rc> */
	CMPR_INF_INIT_FAILURE	= -1895, /* Inflation initialization failure */

	/** <rc><name>CMPR_INF_ERROR</name><num>-1894</num></rc> */
	CMPR_INF_ERROR			= -1894, /* Inflation error */

	/** <rc><name>CMPR_INF_END_FAILURE</name><num>-1893</num></rc> */
	CMPR_INF_END_FAILURE	= -1893, /* End of inflation error */

	/** <rc><name>CMPR_NOT_SUPPORTED</name><num>-1892</num></rc> */
	CMPR_NOT_SUPPORTED		= -1892	 /* Compression is not supported with this version of ETFILE */
};

enum {

	/** <rc><name>COMM_ERROR</name><num>-1699</num></rc> */
	COMM_ERROR 					= -1699, /* General Error */

	/** <rc><name>COMM_NOT_IMPLEMENTED</name><num>-1698</num></rc> */
	COMM_NOT_IMPLEMENTED 		= -1698, /* The requested feature hasn't been implemented yet */

	/** <rc><name>COMM_NULL_INPUT</name><num>-1697</num></rc> */
	COMM_NULL_INPUT 			= -1697, /* An input parameter or internal pointer was NULL */

	/** <rc><name>COMM_INVALID_ALGORITHM</name><num>-1696</num></rc> */
	COMM_INVALID_ALGORITHM 		= -1696, /* Invalid X.509 algorithm Id */

	/** <rc><name>COMM_SEARCH_SIZELIMIT</name><num>-1695</num></rc> */
	COMM_SEARCH_SIZELIMIT 		= -1695, /* The size limit was exceeded in a search operation */

	/** <rc><name>COMM_SEARCH_TIMELIMIT</name><num>-1694</num></rc> */
	COMM_SEARCH_TIMELIMIT 		= -1694, /* The time limit was exceeded in a search operation */

	/** <rc><name>COMM_SEP_UNKNOWN_RESPONSE_CLI</name><num>-1693</num></rc> */
	COMM_SEP_UNKNOWN_RESPONSE_CLI = -1693, /* The client received a bad response */

	/** <rc><name>COMM_SEP_UNKNOWN_REQUEST_MGR</name><num>-1692</num></rc> */
	COMM_SEP_UNKNOWN_REQUEST_MGR = -1692, /* The mgr received a bad request */

	/** <rc><name>COMM_SEP_MAC_FAILED_CLI</name><num>-1691</num></rc> */
	COMM_SEP_MAC_FAILED_CLI 	= -1691, /* The MAC failed at the client */

	/** <rc><name>COMM_SEP_MAC_FAILED_MGR</name><num>-1690</num></rc> */
	COMM_SEP_MAC_FAILED_MGR 	= -1690, /* The MAC failed at the mgr */

	/** <rc><name>COMM_SEP_WRONG_VERSION_MGR</name><num>-1689</num></rc> */
	COMM_SEP_WRONG_VERSION_MGR 	= -1689, /* Client using version not supported by mgr */

	/** <rc><name>COMM_SEP_UNKNOWN_CLIENT_MGR</name><num>-1688</num></rc> */
	COMM_SEP_UNKNOWN_CLIENT_MGR = -1688, /* Client DN not in X.500 */

	/** <rc><name>COMM_SEP_CLIENT_WRONG_STATE_MGR</name><num>-1687</num></rc> */
	COMM_SEP_CLIENT_WRONG_STATE_MGR = -1687, /* Client is in the wrong state */

	/** <rc><name>COMM_SEP_BAD_REF_NUM_MGR</name><num>-1686</num></rc> */
	COMM_SEP_BAD_REF_NUM_MGR 	= -1686, /* Reference number not recognized */

	/** <rc><name>COMM_SEP_ERROR_MGR</name><num>-1685</num></rc> */
	COMM_SEP_ERROR_MGR 			= -1685, /* General Error */

	/** <rc><name>COMM_SEP_ERROR_CLI</name><num>-1684</num></rc> */
	COMM_SEP_ERROR_CLI 			= -1684, /* General Error */

	/** <rc><name>COMM_SEP_VERIFY_FAIL_MGR</name><num>-1683</num></rc> */
	COMM_SEP_VERIFY_FAIL_MGR 	= -1683, /* Signature verification failed at the mgr */

	/** <rc><name>COMM_SEP_VERIFY_FAIL_CLI</name><num>-1682</num></rc> */
	COMM_SEP_VERIFY_FAIL_CLI 	= -1682, /* Signature verification failed at the client */

	/** <rc><name>COMM_SEP_SIGNING_OFF_LINE</name><num>-1681</num></rc> */
	COMM_SEP_SIGNING_OFF_LINE 	= -1681, /* Request denied, off line signing only */

	/** <rc><name>COMM_SEP_ERROR_DECODING_MGR</name><num>-1680</num></rc> */
	COMM_SEP_ERROR_DECODING_MGR = -1680,  /* Error decoding */

	/** <rc><name>COMM_SEP_ERROR_DECODING_CLI</name><num>-1679</num></rc> */
	COMM_SEP_ERROR_DECODING_CLI = -1679, /* Error Decoding */

	/** <rc><name>COMM_SEP_BAD_SEQ_NUM_MGR</name><num>-1678</num></rc> */
	COMM_SEP_BAD_SEQ_NUM_MGR 	= -1678, /* Sequence Number wrong */

	/** <rc><name>COMM_SEP_BAD_SEQ_NUM_CLI</name><num>-1677</num></rc> */
	COMM_SEP_BAD_SEQ_NUM_CLI 	= -1677, /* Seqence Number received not the same as sent */

	/** <rc><name>COMM_SEP_SERVER_ERROR_MGR</name><num>-1676</num></rc> */
	COMM_SEP_SERVER_ERROR_MGR 	= -1676, /* Entrust/Authority cannot connect to server */

	/** <rc><name>COMM_SEP_CLIENT_NOT_FOUND_MGR</name><num>-1675</num></rc> */
	COMM_SEP_CLIENT_NOT_FOUND_MGR = -1675, /* Client was not found */

	/** <rc><name>COMM_SEP_MGR_NOT_RESPONDING</name><num>-1674</num></rc> */
	COMM_SEP_MGR_NOT_RESPONDING = -1674, /*got a PAbort from LDAP entmgr not running */

	/** <rc><name>COMM_SEP_CLI_NOT_RESPONDING</name><num>-1673</num></rc> */
	COMM_SEP_CLI_NOT_RESPONDING = -1673,

	/** <rc><name>COMM_SEP_MANAGER_BUSY</name><num>-1672</num></rc> */
	COMM_SEP_MANAGER_BUSY 		= -1672,

	/** <rc><name>COMM_SEP_PSCERT_NOT_VALID_YET</name><num>-1671</num></rc> */
	COMM_SEP_PSCERT_NOT_VALID_YET = -1671,

	/** <rc><name>COMM_SEP_PSCERT_EXPIRED</name><num>-1670</num></rc> */
	COMM_SEP_PSCERT_EXPIRED 	= -1670,

	/** <rc><name>COMM_SEP_PSCERT_SIG_FAILED</name><num>-1669</num></rc> */
	COMM_SEP_PSCERT_SIG_FAILED 	= -1669,

	/** <rc><name>COMM_SEP_PSCERT_WRONGCA</name><num>-1668</num></rc> */
	COMM_SEP_PSCERT_WRONGCA		= -1668,

	/** <rc><name>COMM_SEP_PSCERT_ERROR</name><num>-1667</num></rc> */
	COMM_SEP_PSCERT_ERROR 		= -1667,

	/** <rc><name>COMM_SEP_RN_MISMATCH_CLI</name><num>-1666</num></rc> */
	COMM_SEP_RN_MISMATCH_CLI 	= -1666,

	/** <rc><name>COMM_SEP_RN_MISMATCH_MGR</name><num>-1665</num></rc> */
	COMM_SEP_RN_MISMATCH_MGR 	= -1665,

	/** <rc><name>COMM_CANNOT_CONNECT</name><num>-1664</num></rc> */
	COMM_CANNOT_CONNECT 		= -1664, /* Comm connect() failed! */
	/* CRL errors */

	/** <rc><name>COMM_CRL_PARSE_ERROR</name><num>-1663</num></rc> */
	COMM_CRL_PARSE_ERROR 		= -1663,

	/** <rc><name>COMM_CRL_NOT_FOUND</name><num>-1662</num></rc> */
	COMM_CRL_NOT_FOUND 			= -1662, /* CRL not found */

	/** <rc><name>COMM_CRL_RETRIEVE_ERROR</name><num>-1661</num></rc> */
	COMM_CRL_RETRIEVE_ERROR 	= -1661,

	/** <rc><name>COMM_ARL_PARSE_ERROR</name><num>-1660</num></rc> */
	COMM_ARL_PARSE_ERROR		= -1660, /* ARL */

	/** <rc><name>COMM_ARL_NOT_FOUND</name><num>-1659</num></rc> */
	COMM_ARL_NOT_FOUND			= -1659,

	/** <rc><name>COMM_ARL_RETREIVE_ERROR</name><num>-1658</num></rc> */
	COMM_ARL_RETREIVE_ERROR		= -1658,

	/** <rc><name>COMM_ATTCERT_PARSE_ERROR</name><num>-1657</num></rc> */
	COMM_ATTCERT_PARSE_ERROR	= -1657, /* AttributeCertificate */

	/** <rc><name>COMM_ATTCERT_NOT_FOUND</name><num>-1656</num></rc> */
	COMM_ATTCERT_NOT_FOUND		= -1656,

	/** <rc><name>COMM_ATTCERT_RETREIVE_ERROR</name><num>-1655</num></rc> */
	COMM_ATTCERT_RETREIVE_ERROR	= -1655,

	/** <rc><name>COMM_ANY_PARSE_ERROR</name><num>-1654</num></rc> */
	COMM_ANY_PARSE_ERROR		= -1654, /* CRL */

	/** <rc><name>COMM_ANY_NOT_FOUND</name><num>-1653</num></rc> */
	COMM_ANY_NOT_FOUND			= -1653,

	/** <rc><name>COMM_ANY_RETREIVE_ERROR</name><num>-1652</num></rc> */
	COMM_ANY_RETREIVE_ERROR		= -1652,

	/** <rc><name>COMM_XCERT_PARSE_ERROR</name><num>-1651</num></rc> */
	COMM_XCERT_PARSE_ERROR		= -1651, /* Cross Certificate Pairs */

	/** <rc><name>COMM_XCERT_NOT_FOUND</name><num>-1650</num></rc> */
	COMM_XCERT_NOT_FOUND		= -1650,

	/** <rc><name>COMM_XCERT_RETREIVE_ERROR</name><num>-1649</num></rc> */
	COMM_XCERT_RETREIVE_ERROR	= -1649,

	/** <rc><name>COMM_SIGN_CERTIF_OUT_OF_SYNC</name><num>-1648</num></rc> */
	COMM_SIGN_CERTIF_OUT_OF_SYNC= -1648, /* When client information does not match Entrust/Authority */

	/** <rc><name>COMM_ENC_CERTIF_OUT_OF_SYNC</name><num>-1647</num></rc> */
	COMM_ENC_CERTIF_OUT_OF_SYNC	= -1647,

	/** <rc><name>COMM_INVALID_SEP_VERSION</name><num>-1646</num></rc> */
	COMM_INVALID_SEP_VERSION	= -1646, /* Cannot do the SEP message with specified version */

	/** <rc><name>COMM_SEP_CLI_DISABLED_AT_MGR</name><num>-1645</num></rc> */
	COMM_SEP_CLI_DISABLED_AT_MGR= -1645, /* Client disabled at Entrust/Authority due to SEP errors */

	/** <rc><name>COMM_SEP_CLI_TIME_MISMATCH</name><num>-1644</num></rc> */
	COMM_SEP_CLI_TIME_MISMATCH	= -1644,	 /* Client and Entrust/Authority time differ significantly */

	/** <rc><name>COMM_CANNOT_CONNECT_BAD_SERVER</name><num>-1574</num></rc> */
	COMM_CANNOT_CONNECT_BAD_SERVER		= -1574,/* "Will not connect to bad server */

	/** <rc><name>COMM_LDAP_UNSOLICITED_NOTIFICATION</name><num>-1573</num></rc> */
	COMM_LDAP_UNSOLICITED_NOTIFICATION	= -1573,/* Unsolicited notification received from LDAP server -- connection terminated. */

	/** <rc><name>COMM_OP_CANCELLED</name><num>-1572</num></rc> */
	COMM_OP_CANCELLED					= -1572,/* LDAP operation was canceled */

	/** <rc><name>COMM_WRITE_CONNECTION_REQUIRED</name><num>-1571</num></rc> */
	COMM_WRITE_CONNECTION_REQUIRED		= -1571, /* A write connection is required to perform this operation */

	/** <rc><name>COMM_ATTCERT_ATTRIBUTE_NOT_FOUND</name><num>-1570</num></rc> */
	COMM_ATTCERT_ATTRIBUTE_NOT_FOUND	= -1570/* Attribute was not found.*/
	
};

enum {

	/** <rc><name>ASN1_ERROR</name><num>-999</num></rc> */
	ASN1_ERROR 					= -999, /* General error */

	/** <rc><name>ASN1_NOT_IMPLEMENTED</name><num>-998</num></rc> */
	ASN1_NOT_IMPLEMENTED 		= -998, /* The requested feature hasn't been implemented yet */

	/** <rc><name>ASN1_NULL_INPUT</name><num>-997</num></rc> */
	ASN1_NULL_INPUT 			= -997, /* An input parameter was NULL */

	/** <rc><name>ASN1_DECODE_FAILURE</name><num>-996</num></rc> */
	ASN1_DECODE_FAILURE 		= -996,

	/** <rc><name>ASN1_ENCODE_FAILURE</name><num>-995</num></rc> */
	ASN1_ENCODE_FAILURE 		= -995,

	/** <rc><name>ASN1_PARSE_FAILURE</name><num>-994</num></rc> */
	ASN1_PARSE_FAILURE 			= -994,

	/** <rc><name>ASN1_OID_NOT_FOUND</name><num>-993</num></rc> */
	ASN1_OID_NOT_FOUND 			= -993,

	/** <rc><name>ASN1_OUT_OF_BOUNDS</name><num>-992</num></rc> */
	ASN1_OUT_OF_BOUNDS 			= -992 /* An internal length/range check failed */
};

enum {

	/** <rc><name>UTIL_ALLOC_ERROR</name><num>-1400</num></rc> */
	UTIL_ALLOC_ERROR			= -1400,

	/** <rc><name>UTIL_NOT_HEX_FORMAT</name><num>-1401</num></rc> */
	UTIL_NOT_HEX_FORMAT			= -1401,

	/** <rc><name>UTIL_NOT_PEM_FORMAT</name><num>-1402</num></rc> */
	UTIL_NOT_PEM_FORMAT			= -1402,

	/** <rc><name>UTIL_PEM_FORMAT_ERROR</name><num>-1403</num></rc> */
	UTIL_PEM_FORMAT_ERROR		= -1403,
	/* Entrust authorization codes */

	/** <rc><name>UTIL_AUTH_INVALID_CHARS</name><num>-1404</num></rc> */
	UTIL_AUTH_INVALID_CHARS		= -1404,

	/** <rc><name>UTIL_AUTH_BAD_CHKSUM</name><num>-1405</num></rc> */
	UTIL_AUTH_BAD_CHKSUM   		= -1405
};

enum {

	/** <rc><name>CLI_INPUT_FILE_STAT_FAILED</name><num>-1299</num></rc> */
	CLI_INPUT_FILE_STAT_FAILED 				= -1299, /* Failed to get size of input file */

	/** <rc><name>CLI_OUTPUT_FILE_STAT_FAILED</name><num>-1298</num></rc> */
	CLI_OUTPUT_FILE_STAT_FAILED				= -1298, /* Failed to get size of output file */

	/** <rc><name>CLI_INPUT_FILE_OPEN_FAILED</name><num>-1297</num></rc> */
	CLI_INPUT_FILE_OPEN_FAILED				= -1297, /* Failed to open input file */

	/** <rc><name>CLI_INPUT_FILE_READ_FAILED</name><num>-1296</num></rc> */
	CLI_INPUT_FILE_READ_FAILED				= -1296, /* Failed to read input from file */

	/** <rc><name>CLI_OUTPUT_FILE_CREATE_FAILED</name><num>-1295</num></rc> */
	CLI_OUTPUT_FILE_CREATE_FAILED			= -1295, /* Failed to create file */

	/** <rc><name>CLI_OUTPUT_FILE_WRITE_FAILED</name><num>-1294</num></rc> */
	CLI_OUTPUT_FILE_WRITE_FAILED			= -1294, /* Failed to write to file */

	/** <rc><name>CLI_ARCHIVE_BAD_FORMAT</name><num>-1293</num></rc> */
	CLI_ARCHIVE_BAD_FORMAT					= -1293, /* Entrust file information in file */

	/** <rc><name>CLI_PASSWORDS_DONT_MATCH</name><num>-1292</num></rc> */
	CLI_PASSWORDS_DONT_MATCH				= -1292, /* The new and verified passwords do not match. */

	/** <rc><name>CLI_INVALID_USER_NAME</name><num>-1291</num></rc> */
	CLI_INVALID_USER_NAME					= -1291, /* A user name must be supplied */

	/** <rc><name>CLI_MIXED_ENC_AND_DEC_FILES</name><num>-1290</num></rc> */
	CLI_MIXED_ENC_AND_DEC_FILES				= -1290, /* Mixing of encrypted/signed and plaintext files. */

	/** <rc><name>CLI_BAD_ENCRYPTION_HEADER</name><num>-1289</num></rc> */
	CLI_BAD_ENCRYPTION_HEADER				= -1289, /* Invalid security header format */

	/** <rc><name>CLI_PASSWORD_TOO_SHORT</name><num>-1288</num></rc> */
	CLI_PASSWORD_TOO_SHORT					= -1288, /* New password is too short. */

	/** <rc><name>CLI_FILE_INFO_ERROR</name><num>-1287</num></rc> */
	CLI_FILE_INFO_ERROR						= -1287, /* Failed to obtain directory information for file */

	/** <rc><name>CLI_FILE_NOT_SIGNED</name><num>-1286</num></rc> */
	CLI_FILE_NOT_SIGNED						= -1286, /* This file does not have a digital signature. */

	/** <rc><name>CLI_INPUT_FILE_DELETE_FAILED</name><num>-1285</num></rc> */
	CLI_INPUT_FILE_DELETE_FAILED			= -1285, /* Problem encountered attempting to delete file */

	/** <rc><name>CLI_CREATE_USER_FAILED</name><num>-1284</num></rc> */
	CLI_CREATE_USER_FAILED					= -1284, /* Failed to create user, Check Entrust/Authority reference #/password. */

	/** <rc><name>CLI_ARCHIVE_CHECKSUM_FAILED</name><num>-1283</num></rc> */
	CLI_ARCHIVE_CHECKSUM_FAILED				= -1283, /* Cryptographic information in input file has been corrupted. */

	/** <rc><name>CLI_FILE_SHORTER_THAN_EXPECTED</name><num>-1282</num></rc> */
	CLI_FILE_SHORTER_THAN_EXPECTED			= -1282, /* Unexpected end of file encountered */

	/** <rc><name>CLI_OLD_PASSWORD_IS_NEW</name><num>-1281</num></rc> */
	CLI_OLD_PASSWORD_IS_NEW					= -1281, /* The new password cannot be the same as the old password. */

	/** <rc><name>CLI_PASSWORD_IS_USER_NAME</name><num>-1280</num></rc> */
	CLI_PASSWORD_IS_USER_NAME				= -1280, /* The password cannot be the same as the user name. */

	/** <rc><name>CLI_FILE_START_IDENTIFIER_MISSING</name><num>-1279</num></rc> */
	CLI_FILE_START_IDENTIFIER_MISSING		= -1279, /* Entrust file start identifier missing */

	/** <rc><name>CLI_ARCHIVE_START_IDENTIFIER_MISSING</name><num>-1278</num></rc> */
	CLI_ARCHIVE_START_IDENTIFIER_MISSING	= -1278, /* Entrust archive start identifier missing */

	/** <rc><name>CLI_FILE_END_IDENTIFIER_MISSING</name><num>-1277</num></rc> */
	CLI_FILE_END_IDENTIFIER_MISSING			= -1277, /* Entrust file end identifier missing */

	/** <rc><name>CLI_ARCHIVE_END_IDENTIFIER_MISSING</name><num>-1276</num></rc> */
	CLI_ARCHIVE_END_IDENTIFIER_MISSING		= -1276, /* Entrust archive end identifier missing */

	/** <rc><name>CLI_GROUP_LOAD_FAILED</name><num>-1275</num></rc> */
	CLI_GROUP_LOAD_FAILED					= -1275, /* Failed to load groups from user profile,  Bad [Groups] section format. */

	/** <rc><name>CLI_CRC_FAILED</name><num>-1274</num></rc> */
	CLI_CRC_FAILED							= -1274, /* Input file has been damaged (CRC error). */

	/** <rc><name>CLI_PASSWORD_EMPTY_FIELDS</name><num>-1273</num></rc> */
	CLI_PASSWORD_EMPTY_FIELDS				= -1273, /* All password arguments must be filled in. */

	/** <rc><name>CLI_CRYPTO_HEADER_TOO_LONG</name><num>-1272</num></rc> */
	CLI_CRYPTO_HEADER_TOO_LONG				= -1272, /* Cryptographic information exceeded maximum allowable length. */

	/** <rc><name>CLI_PASSWORD_TOO_MANY_CHAR</name><num>-1271</num></rc> */
	CLI_PASSWORD_TOO_MANY_CHAR				= -1271, /* New password contains too many instances of one character. */

	/** <rc><name>CLI_PASSWORD_NO_LOWER_CASE</name><num>-1270</num></rc> */
	CLI_PASSWORD_NO_LOWER_CASE				= -1270, /* New password must contain a lower case character. */

	/** <rc><name>CLI_PASSWORD_NO_UPPER_CASE</name><num>-1269</num></rc> */
	CLI_PASSWORD_NO_UPPER_CASE				= -1269, /* New password must contain an upper case character. */

	/** <rc><name>CLI_PASSWORD_HAS_USER_NAME</name><num>-1268</num></rc> */
	CLI_PASSWORD_HAS_USER_NAME              = -1268, /* New password cannot contain a substring of the user name. */

	/** <rc><name>CLI_ARCHIVE_TOO_LARGE</name><num>-1267</num></rc> */
	CLI_ARCHIVE_TOO_LARGE					= -1267,

	/** <rc><name>CLI_ARCHIVE_CORRUPTION</name><num>-1266</num></rc> */
	CLI_ARCHIVE_CORRUPTION					= -1266,

	/** <rc><name>CLI_SKIP_THIS_FILE</name><num>-1265</num></rc> */
	CLI_SKIP_THIS_FILE						= -1265,

	/** <rc><name>CLI_SIGVERIFY_FAILED</name><num>-1264</num></rc> */
	CLI_SIGVERIFY_FAILED					= -1264,

	/** <rc><name>CLI_SRCHBASE_LIST_LOAD_FAILED</name><num>-1263</num></rc> */
	CLI_SRCHBASE_LIST_LOAD_FAILED			= -1263,

	/** <rc><name>CLI_SEARCHBASE_NOT_FOUND</name><num>-1262</num></rc> */
	CLI_SEARCHBASE_NOT_FOUND				= -1262,

	/** <rc><name>CLI_RECLST_LOAD_FAILED</name><num>-1261</num></rc> */
	CLI_RECLST_LOAD_FAILED					= -1261,

	/** <rc><name>CLI_NOT_A_RECLIST_FILE</name><num>-1260</num></rc> */
	CLI_NOT_A_RECLIST_FILE					= -1260, /* File does not contain recipients lists. */

	/** <rc><name>CLI_RECLSTFILE_INCOMPAT_VERSION</name><num>-1259</num></rc> */
	CLI_RECLSTFILE_INCOMPAT_VERSION			= -1259, /* Recipient list file version is incompatible with current CLIAPI version. */

	/** <rc><name>CLI_RECLST_WAS_TAMPERED_WITH</name><num>-1258</num></rc> */
	CLI_RECLST_WAS_TAMPERED_WITH			= -1258,

	/** <rc><name>CLI_RECLST_HAS_PAB_ENTRIES</name><num>-1257</num></rc> */
	CLI_RECLST_HAS_PAB_ENTRIES				= -1257,

	/** <rc><name>CLI_GROUPS_CONVERTED_TO_RLS</name><num>-1256</num></rc> */
	CLI_GROUPS_CONVERTED_TO_RLS				= -1256, /* groups were automatically converted to recipient lists */

	/** <rc><name>CLI_RECLST_INVALID_ENCR_ALG</name><num>-1255</num></rc> */
	CLI_RECLST_INVALID_ENCR_ALG				= -1255,

	/** <rc><name>CLI_CRITICAL_EXT_UNKNOWN</name><num>-1254</num></rc> */
	CLI_CRITICAL_EXT_UNKNOWN				= -1254,  /* For unknown critical extension in the file header */

	/** <rc><name>CLI_INTERNAL_ERROR</name><num>-1253</num></rc> */
	CLI_INTERNAL_ERROR						= -1253,  /* Internal errors - shouldn't happen */

	/** <rc><name>CLI_SERVICE_NOT_ENABLED</name><num>-1252</num></rc> */
	CLI_SERVICE_NOT_ENABLED 				= -1249,

	/** <rc><name>CLI_BAD_OPTION</name><num>-1248</num></rc> */
	CLI_BAD_OPTION 						= -1248,  /*Specified option not available*/

	/** <rc><name>CLI_BAD_CAPABILITY</name><num>-1247</num></rc> */
	CLI_BAD_CAPABILITY  				= -1247,  /*Specified capability not available*/

	/** <rc><name>CLI_VERIFICATION_CERT_EXPIRED_AFTER_TIMESTAMP</name><num>-1246</num></rc> */
	CLI_VERIFICATION_CERT_EXPIRED_AFTER_TIMESTAMP  = -1246,  /*The cert expired after the timestamp was applied*/

	/** <rc><name>CLI_VERIFICATION_CERT_REVOKED_AFTER_TIMESTAMP</name><num>-1246</num></rc> */
	CLI_VERIFICATION_CERT_REVOKED_AFTER_TIMESTAMP  = -1245,  /*The cert was revoked after the timestamp was applied*/

	/** <rc><name>CLI_PASSWORD_NO_DIGIT</name><num>-1243</num></rc> */
	CLI_PASSWORD_NO_DIGIT				= -1243, /* New password must contain a digit. */

	/** <rc><name>CLI_PASSWORD_NO_NONALPHA</name><num>-1242</num></rc> */
	CLI_PASSWORD_NO_NONALPHA			= -1242 /* New password must contain a non-alphanumeric character. */

};

enum
{

	/** <rc><name>FENC_RECIPIENTS_NOT_FOUND</name><num>-1099</num></rc> */
	FENC_RECIPIENTS_NOT_FOUND 	= -1099, /* some recipients had no certificates (CreateEncryptHeader) */

	/** <rc><name>FENC_NOTHING_TO_DO</name><num>-1098</num></rc> */
	FENC_NOTHING_TO_DO 			= -1098, /* CreateHeader called before StartEncryption or EndSignature */

	/** <rc><name>FENC_BAD_HEADER</name><num>-1097</num></rc> */
	FENC_BAD_HEADER 			= -1097, /* Entrust header is not "right" */

	/** <rc><name>FENC_NOT_ENCRYPTED</name><num>-1096</num></rc> */
	FENC_NOT_ENCRYPTED 			= -1096, /* header indicates data is not encrypted. */

	/** <rc><name>FENC_NOT_SIGNED</name><num>-1095</num></rc> */
	FENC_NOT_SIGNED 			= -1095, /* header indicates data is not signed */

	/** <rc><name>FENC_ACCESS_DENIED</name><num>-1094</num></rc> */
	FENC_ACCESS_DENIED 			= -1094, /* user is not in recipient list (or originator) */

	/** <rc><name>FENC_INI_NOT_FOUND</name><num>-1093</num></rc> */
	FENC_INI_NOT_FOUND 			= -1093, /* unable to find the Entrust INI file supplied */

	/** <rc><name>FENC_USER_PROFILE_EXISTS</name><num>-1092</num></rc> */
	FENC_USER_PROFILE_EXISTS 	= -1092, /* cannot create a new user, profile already exists */

    /** <rc><name>FENC_INI_NO_DEMOKEYS</name><num>-1091</num></rc> */
    FENC_INI_NO_DEMOKEYS 		= -1091, /* no "DemoKeys" file defines in entrust.ini (for demo) */

    /** <rc><name>FENC_INI_NO_SERVER</name><num>-1090</num></rc> */
    FENC_INI_NO_SERVER 			= -1090, /* no "Server" defined in entrust.ini (for the real thing) */

    /** <rc><name>FENC_INI_NO_PUB</name><num>-1089</num></rc> */
    FENC_INI_NO_PUB 			= -1089, /* no public address book defined in entrust.ini (for Lite) */

    /** <rc><name>FENC_NO_CLIENTTYPE_SPECIFIED</name><num>-1088</num></rc> */
    FENC_NO_CLIENTTYPE_SPECIFIED = -1088, /* no "ClientType=" line in entrust.ini */

	/** <rc><name>FENC_PUBLICKEYFILE_OPEN_ERROR</name><num>-1087</num></rc> */
	FENC_PUBLICKEYFILE_OPEN_ERROR = -1087, /* can't open public key file */

	/** <rc><name>FENC_BAD_PASSWORD</name><num>-1086</num></rc> */
	FENC_BAD_PASSWORD 			= -1086, /* Password is not the same as passed upon creation */

	/** <rc><name>FENC_BAD_ENCRYPT_METHOD</name><num>-1085</num></rc> */
	FENC_BAD_ENCRYPT_METHOD 	= -1085, /* unknown encryption method specified in ini file */

	/** <rc><name>FENC_BAD_SEARCH_LOCATION</name><num>-1084</num></rc> */
	FENC_BAD_SEARCH_LOCATION 	= -1084, /* SearchLocation is invalid value */

	/** <rc><name>FENC_NO_PAB</name><num>-1083</num></rc> */
	FENC_NO_PAB 				= -1083, /* user has no PAB */

	/** <rc><name>FENC_BAD_CRC</name><num>-1082</num></rc> */
	FENC_BAD_CRC 				= -1082, /* decrypted file fails integrity check */

	/** <rc><name>FENC_USER_NOT_FOUND_IN_PUBLIC_STORE</name><num>-1081</num></rc> */
	FENC_USER_NOT_FOUND_IN_PUBLIC_STORE = -1081, /* using wrong EPF??? */

	/** <rc><name>FENC_USER_NAME_NOT_FOUND</name><num>-1080</num></rc> */
	FENC_USER_NAME_NOT_FOUND 	= -1080, /* get information couldn't find name */

	/** <rc><name>FENC_TOO_MANY_RECIPIENTS</name><num>-1079</num></rc> */
	FENC_TOO_MANY_RECIPIENTS 	= -1079, /* recipient size limit reached for CreateHeader */

	/** <rc><name>FENC_PUB_DOESNT_MATCH_PRIV_INFO</name><num>-1078</num></rc> */
	FENC_PUB_DOESNT_MATCH_PRIV_INFO = -1078, /* public key id doesn't match private keyid */

	/** <rc><name>FENC_PAB_NOT_FOUND</name><num>-1077</num></rc> */
	FENC_PAB_NOT_FOUND 			= -1077, /* pab defined in profile, but file not found */

	/** <rc><name>FENC_MANAGER_CLIENT_TIME_MISMATCH</name><num>-1076</num></rc> */
	FENC_MANAGER_CLIENT_TIME_MISMATCH = -1076, /* client time too out of sync with Entrust/Authority time */

	/** <rc><name>FENC_CANT_GET_CURRENT_CRL</name><num>-1075</num></rc> */
	FENC_CANT_GET_CURRENT_CRL 	= -1075, /* couldn't get a new enough CRL */

	/** <rc><name>FENC_ENCRYPTION_CERT_REVOKED</name><num>-1074</num></rc> */
	FENC_ENCRYPTION_CERT_REVOKED = -1074, /* the encryption key certificate has been revoked */

	/** <rc><name>FENC_SIGNING_CERT_REVOKED</name><num>-1073</num></rc> */
	FENC_SIGNING_CERT_REVOKED 	= -1073, /* the signing key certificate has been revoked  */

	/** <rc><name>FENC_MUST_RECOVER_SIGN_KEY</name><num>-1072</num></rc> */
	FENC_MUST_RECOVER_SIGN_KEY 	= -1072, /* Signing key expired. User must do a recovery. */

	/** <rc><name>FENC_FILE_NOT_PAB</name><num>-1071</num></rc> */
	FENC_FILE_NOT_PAB 			= -1071, /* A file designated as a PAB, doesn't appear to be one. */

	/** <rc><name>FENC_NO_X500_ARCHIVE</name><num>-1070</num></rc> */
	FENC_NO_X500_ARCHIVE 		= -1070, /* No X500 archive when attempting to call CreateUserComplete */

	/** <rc><name>FENC_DES_ENCRYPT_NOT_SUPPORTED</name><num>-1069</num></rc> */
	FENC_DES_ENCRYPT_NOT_SUPPORTED = -1069, /* This version doesn't support DES encryption (International version only) */

	/** <rc><name>FENC_DES_DECRYPT_NOT_SUPPORTED</name><num>-1068</num></rc> */
	FENC_DES_DECRYPT_NOT_SUPPORTED = -1068, /* This version doesn't support DES decryption (International version only) */

	/** <rc><name>FENC_64BIT_ENCRYPT_NOT_SUPPORTED</name><num>-1067</num></rc> */
	FENC_64BIT_ENCRYPT_NOT_SUPPORTED = -1067, /* Only 40 bit encryption allowed (International version only) */

	/** <rc><name>FENC_64BIT_DECRYPT_NOT_SUPPORTED</name><num>-1066</num></rc> */
	FENC_64BIT_DECRYPT_NOT_SUPPORTED = -1066, /* Only 40 bit encryption allowed (International version only) */

	/** <rc><name>FENC_SIGNING_KEY_UPDATE_FAILED</name><num>-1065</num></rc> */
	FENC_SIGNING_KEY_UPDATE_FAILED	 = -1065, /* Signing key rollover failed  */

	/** <rc><name>FENC_ENCRYPTION_KEY_UPDATE_FAILED</name><num>-1064</num></rc> */
	FENC_ENCRYPTION_KEY_UPDATE_FAILED= -1064, /* Encryption key rollover failed */

	/** <rc><name>FENC_PROFILE_INFORMATION_CHANGED</name><num>-1063</num></rc> */
	FENC_PROFILE_INFORMATION_CHANGED = -1063,  /* Profile had changed - informational (possibly because of key updates) */

	/** <rc><name>FENC_CANT_GET_ATTRIBUTE_CERTIFICATE</name><num>-1062</num></rc> */
	FENC_CANT_GET_ATTRIBUTE_CERTIFICATE = -1062, /* Error retrieving attribute certificate */

	/** <rc><name>FENC_UNKNOWN_COMPRESSION_ALGORITHM</name><num>-1061</num></rc> */
	FENC_UNKNOWN_COMPRESSION_ALGORITHM = -1061,	/* Unknown compression algorithm */

	/** <rc><name>FENC_FILE_VERSION_TOO_NEW</name><num>-1060</num></rc> */
	FENC_FILE_VERSION_TOO_NEW	= -1060, /* A file generated by a later ETFile and incompatible with us detected */

	/** <rc><name>FENC_ENCALGORITHM_CANT_BE_SELECTED</name><num>-1059</num></rc> */
	FENC_ENCALGORITHM_CANT_BE_SELECTED = -1059,	/* The requested encryption algorithm/parameters cannot be selected */

	/** <rc><name>FENC_BAD_HEADER_SYMMKEY_L</name><num>-1058</num></rc> */
	FENC_BAD_HEADER_SYMMKEY_L 	= -1058, /* Symmetric key (identified by Recipient-ID) parse failed */

	/** <rc><name>FENC_BAD_HEADER_IV</name><num>-1057</num></rc> */
	FENC_BAD_HEADER_IV			= -1057, /* IV parse failed */

	/** <rc><name>FENC_BAD_HEADER_SYMMKEY_C</name><num>-1056</num></rc> */
	FENC_BAD_HEADER_SYMMKEY_C	= -1056, /* Symmetric key (identified by Originator-Certificate) parse failed */

	/** <rc><name>FENC_CANT_LOCK_PROFILE</name><num>-1055</num></rc> */
	FENC_CANT_LOCK_PROFILE		= -1055, /* Unable to lock .epf for update */

	/** <rc><name>FENC_PROFILE_PASSWORD_CHANGED</name><num>-1054</num></rc> */
	FENC_PROFILE_PASSWORD_CHANGED = -1054, /* The profile password has been changed by another context */

	/** <rc><name>FENC_USER_DATA_FILES_EXIST</name><num>-1053</num></rc> */
	FENC_USER_DATA_FILES_EXIST	= -1053,	/* need to clean out profile directory */

	/** <rc><name>FENC_MGR20_WTH_DSA_NOT_SUPPORTED</name><num>-1052</num></rc> */
	FENC_MGR20_WTH_DSA_NOT_SUPPORTED= -1052, /* must use Manager v2.1 or later with DSA */

	/** <rc><name>FENCE_DOM_WITH_EXPT_MGR_USED</name><num>-1051</num></rc> */
	FENCE_DOM_WITH_EXPT_MGR_USED	= -1051, /* domestic clients cannot talk to exportable Entrust/Authority */

	/** <rc><name>FENC_V2_MGR_USED_WTH_V21_CERT</name><num>-1050</num></rc> */
	FENC_V2_MGR_USED_WTH_V21_CERT	= -1050, /* cannot have a v2 Manager with a v21 certificate */

	/** <rc><name>FENC_UNKNOWN_MGR_VERSION</name><num>-1049</num></rc> */
	FENC_UNKNOWN_MGR_VERSION		= -1049, /* unknown Entrust/Authority version, it's not v2 or v21 */

	/** <rc><name>FENC_ROLLOVER_NOT_ALLOWED</name><num>-1048</num></rc> */
	FENC_ROLLOVER_NOT_ALLOWED		= -1048,  /* m_RolloverAllowed in certificate is set to FALSE */

	/** <rc><name>FENC_RR_UNSPECIFIED</name><num>-1047</num></rc> */
	FENC_RR_UNSPECIFIED				= -1047, /* revocation reason unspecified */

	/** <rc><name>FENC_RR_KEY_COMPROMISE</name><num>-1046</num></rc> */
	FENC_RR_KEY_COMPROMISE			= -1046, /*	known or suspected key compromise */

	/** <rc><name>FENC_RR_AFFILIATION_CHANGED</name><num>-1045</num></rc> */
	FENC_RR_AFFILIATION_CHANGED		= -1045, /* subject's name or other information has changed */

	/** <rc><name>FENC_RR_SUPERSEDED</name><num>-1044</num></rc> */
	FENC_RR_SUPERSEDED				= -1044, /* certificate has been superseded */

	/** <rc><name>FENC_RR_CESSATION_OF_OPERATION</name><num>-1043</num></rc> */
	FENC_RR_CESSATION_OF_OPERATION	= -1043, /* certificate is no longer needed for the purpose for which it was originally issued.*/

	/** <rc><name>FENC_V2_MGR_USED_WITH_V3_CERT</name><num>-1042</num></rc> */
	FENC_V2_MGR_USED_WITH_V3_CERT	= -1042,	 /* cannot have a v2 Manager with a v3 certificate */

	/** <rc><name>FENC_CORRUPT_INI_FILE</name><num>-1041</num></rc> */
	FENC_CORRUPT_INI_FILE           = -1041,	 /* some ini file is has redundant sections */

	/** <rc><name>FENC_REVOKED_AFFILIATION_CHANGED</name><num>-1034</num></rc> */
	FENC_REVOKED_AFFILIATION_CHANGED = -1034,	 /* Signing cert has been revoked due to an affiliation change */

	/** <rc><name>FENC_SINGLE_KEYPAIR_NO_RSA</name><num>-1033</num></rc> */
	FENC_SINGLE_KEYPAIR_NO_RSA       = -1033,	 /* Single keypair users must use RSA for signing and encryption keys */

	/** <rc><name>FENC_SINGLE_KEYPAIR_NO_TOKENS</name><num>-1032</num></rc> */
	FENC_SINGLE_KEYPAIR_NO_TOKENS    = -1032,	 /* Single keypair users may not use hardware-based profiles */

	/** <rc><name>FENC_ENCALGORITHM_NOT_AVAILABLE</name><num>-1031</num></rc> */
	FENC_ENCALGORITHM_NOT_AVAILABLE  = -1031	/* The requested encryption algorithm or algorithm configuration is not available */
};
 
enum
{

	/** <rc><name>ELMR_CIPHER_CREATE_ERROR</name><num>-899</num></rc> */
	ELMR_CIPHER_CREATE_ERROR 	= -899,

	/** <rc><name>ELMR_NO_CIPHER</name><num>-898</num></rc> */
	ELMR_NO_CIPHER 				= -898,

	/** <rc><name>ELMR_NO_SIGNER</name><num>-897</num></rc> */
	ELMR_NO_SIGNER 				= -897,

	/** <rc><name>ELMR_NO_KEY</name><num>-896</num></rc> */
	ELMR_NO_KEY					= -896,

	/** <rc><name>ELMR_NO_TOKEN</name><num>-895</num></rc> */
	ELMR_NO_TOKEN				= -895
};

enum {

	/** <rc><name>X500_CRL_NOT_VALID_YET</name><num>-799</num></rc> */
	X500_CRL_NOT_VALID_YET 				= -799,

	/** <rc><name>X500_CRL_EXPIRED</name><num>-798</num></rc> */
	X500_CRL_EXPIRED 					= -798,

	/** <rc><name>X500_CRL_MISSING_X500CRL</name><num>-797</num></rc> */
	X500_CRL_MISSING_X500CRL			= -797,

	/** <rc><name>X500_CRL_SIGNATURE_FAILED</name><num>-796</num></rc> */
	X500_CRL_SIGNATURE_FAILED 			= -796,

	/** <rc><name>X500_CERT_NOT_VALID_YET</name><num>-795</num></rc> */
	X500_CERT_NOT_VALID_YET 			= -795,

	/** <rc><name>X500_CRL_COULD_NOT_READ_FROM_FILE</name><num>-794</num></rc> */
	X500_CRL_COULD_NOT_READ_FROM_FILE	= -794,

	/** <rc><name>X500_CRL_COULD_NOT_WRITE_TO_FILE</name><num>-793</num></rc> */
	X500_CRL_COULD_NOT_WRITE_TO_FILE	= -793,

	/** <rc><name>X500_CRL_ENCODE_ERROR</name><num>-792</num></rc> */
	X500_CRL_ENCODE_ERROR				= -792,

	/** <rc><name>X500_CRL_PARSE_ERROR</name><num>-791</num></rc> */
	X500_CRL_PARSE_ERROR				= -791,

	/** <rc><name>X500_CERT_EXPIRED</name><num>-790</num></rc> */
	X500_CERT_EXPIRED 					= -790,

	/** <rc><name>X500_CERT_MISSING_X500CERTIF</name><num>-789</num></rc> */
	X500_CERT_MISSING_X500CERTIF 		= -789,

	/** <rc><name>X500_CERT_SIGNATURE_FAILED</name><num>-788</num></rc> */
	X500_CERT_SIGNATURE_FAILED 			= -788,

	/** <rc><name>X500_CERT_KEY_ROLLOVER_TIME</name><num>-787</num></rc> */
	X500_CERT_KEY_ROLLOVER_TIME 		= -787,

	/** <rc><name>X500_ATTCERT_MISSING_X500ATTCERT</name><num>-786</num></rc> */
	X500_ATTCERT_MISSING_X500ATTCERT 	= -786,

	/** <rc><name>X500_ATTCERT_SIGNATURE_FAILED</name><num>-785</num></rc> */
	X500_ATTCERT_SIGNATURE_FAILED 		= -785,

	/** <rc><name>X500_ATTCERT_EXPIRED</name><num>-784</num></rc> */
	X500_ATTCERT_EXPIRED 				= -784,

	/** <rc><name>X500_ATTCERT_COULD_NOT_WRITE_TO_FILE</name><num>-783</num></rc> */
	X500_ATTCERT_COULD_NOT_WRITE_TO_FILE= -783,

	/** <rc><name>X500_ATTCERT_ENCODE_ERROR</name><num>-782</num></rc> */
	X500_ATTCERT_ENCODE_ERROR 			= -782,

	/** <rc><name>X500_ATTCERT_NOT_VALID_YET</name><num>-781</num></rc> */
	X500_ATTCERT_NOT_VALID_YET 			= -781,

	/** <rc><name>X500_CERT_EXT_PARM</name><num>-780</num></rc> */
	X500_CERT_EXT_PARM 					= -780,

	/** <rc><name>X500_CERT_EXT_LIST</name><num>-779</num></rc> */
	X500_CERT_EXT_LIST 					= -779,

	/** <rc><name>X500_CERT_EXT</name><num>-778</num></rc> */
	X500_CERT_EXT 						= -778,

	/** <rc><name>X500_XCERTPAIRS_COULD_NOT_WRITE_TO_FILE</name><num>-777</num></rc> */
	X500_XCERTPAIRS_COULD_NOT_WRITE_TO_FILE	= -777,

	/** <rc><name>X500_XCERTPAIRS_ENCODE_ERROR</name><num>-776</num></rc> */
	X500_XCERTPAIRS_ENCODE_ERROR 		= -776,

	/** <rc><name>X500_UNKNOWN_HASHER_TYPE</name><num>-775</num></rc> */
	X500_UNKNOWN_HASHER_TYPE 			= -775
};

enum {

	/** <rc><name>PROF_NO_SECTION_SPECIFIED</name><num>-599</num></rc> */
	PROF_NO_SECTION_SPECIFIED	= -599,	/* Section must be specified in call */

	/** <rc><name>PROF_SECTION_NOT_FOUND</name><num>-598</num></rc> */
	PROF_SECTION_NOT_FOUND		= -598,	/* Section not found (ReadProfile) */

	/** <rc><name>PROF_ENTRY_NOT_FOUND</name><num>-597</num></rc> */
	PROF_ENTRY_NOT_FOUND		= -597,	/* Entry not found (ReadProfile) */

	/** <rc><name>PROF_TOKEN_NOT_FOUND</name><num>-596</num></rc> */
	PROF_TOKEN_NOT_FOUND		= -596,	/* User's password token was not found in Profile */

	/** <rc><name>PROF_BAD_PASSWORD</name><num>-595</num></rc> */
	PROF_BAD_PASSWORD			= -595,	/* User's password is invalid */

	/** <rc><name>PROF_PROFILE_CORRUPT</name><num>-594</num></rc> */
	PROF_PROFILE_CORRUPT		= -594,	/* User's profile has been tampered with */

	/** <rc><name>PROF_CANT_GEN_PASSWORD_TOKEN</name><num>-593</num></rc> */
	PROF_CANT_GEN_PASSWORD_TOKEN= -593,	/* International client can't read old style password token */

	/** <rc><name>PROF_PROTECTION_SIZE_INVALID</name><num>-592</num></rc> */
	PROF_PROTECTION_SIZE_INVALID= -592, /* Protection not 40 or 64 */

	/** <rc><name>PROF_READONLY</name><num>-580</num></rc> */
	PROF_READONLY = -580,					// profile is not writable

	/** <rc><name>PROF_SHAREDKEY_ENTRY_NOT_FOUND</name><num>-579</num></rc> */
	PROF_SHAREDKEY_ENTRY_NOT_FOUND = -579   // didn't find the entry for the id specified
};

enum {

	/** <rc><name>ARCH_NOT_SUPPORTED</name><num>-499</num></rc> */
	ARCH_NOT_SUPPORTED			= -499,	/* archive does not support function */

	/** <rc><name>ARCH_ENTRY_NOT_FOUND</name><num>-498</num></rc> */
	ARCH_ENTRY_NOT_FOUND		= -498,	/* archive cannot find entry */

	/** <rc><name>ARCH_PAB_CORRUPT</name><num>-497</num></rc> */
	ARCH_PAB_CORRUPT			= -497,	/* PAB corruption (uniquename mismatch) */

	/** <rc><name>ARCH_CANNOT_SAVE_NEW</name><num>-496</num></rc> */
	ARCH_CANNOT_SAVE_NEW		= -496,	/* Attempt to save an entry that does not exist (PAB) */

	/** <rc><name>ARCH_IMPORT_CORRUPT</name><num>-495</num></rc> */
	ARCH_IMPORT_CORRUPT			= -495,	/* Importing corrupt file */

	/** <rc><name>ARCH_ENCRYPT_FAILED</name><num>-494</num></rc> */
	ARCH_ENCRYPT_FAILED			= -494,	/* Encryption failed */

	/** <rc><name>ARCH_DECRYPT_FAILED</name><num>-493</num></rc> */
	ARCH_DECRYPT_FAILED			= -493, /* Decryption failed */

	/** <rc><name>ARCH_WRONG_CERT_RETURNED</name><num>-492</num></rc> */
	ARCH_WRONG_CERT_RETURNED	= -492,	/* The Unique name requested wasn't the same
										   as unique name returned */

	/** <rc><name>ARCH_ENTRY_DAMAGED</name><num>-491</num></rc> */
	ARCH_ENTRY_DAMAGED          = -491,	/* GetProtString failed. */

	/** <rc><name>ARCH_PAB_SAME_CA</name><num>-490</num></rc> */
	ARCH_PAB_SAME_CA			= -490,	/* Can't import an entry with same CA */

	/** <rc><name>ARCH_PAB_CANT_UNLOCK_PAB</name><num>-489</num></rc> */
	ARCH_PAB_CANT_UNLOCK_PAB    = -489,	/* Can't get private RSA key */

	/** <rc><name>ARCH_PAB_ENTRY_EXISTS</name><num>-488</num></rc> */
	ARCH_PAB_ENTRY_EXISTS		= -488,	/* Can't import, entry exists */

	/** <rc><name>ARCH_PAB_KEY_WRITE_FAILED</name><num>-487</num></rc> */
	ARCH_PAB_KEY_WRITE_FAILED	= -487,	/* Can't write key file */

	/** <rc><name>ARCH_PAB_KEY_SIGN_FAILED</name><num>-486</num></rc> */
	ARCH_PAB_KEY_SIGN_FAILED	= -486,	/* Couldn't sign data */

	/** <rc><name>ARCH_PAB_KEY_VERIFY_FAILED</name><num>-485</num></rc> */
	ARCH_PAB_KEY_VERIFY_FAILED	= -485,	/* Verification of signature failed */

	/** <rc><name>ARCH_CERTIFICATE_NOT_FOUND</name><num>-484</num></rc> */
	ARCH_CERTIFICATE_NOT_FOUND	= -484,	/* Certificate not found */

	/** <rc><name>ARCH_CANT_GET_REVOCATION_LIST</name><num>-483</num></rc> */
	ARCH_CANT_GET_REVOCATION_LIST=-483,	/* Valid CRL/ARL couldn't be obtained. */

	/** <rc><name>ARCH_PCDEMO_LIMIT_REACHED</name><num>-482</num></rc> */
	ARCH_PCDEMO_LIMIT_REACHED	= -482,	/* PCDEMO mode has restricted size */

	/** <rc><name>ARCH_THIS_IS_YOUR_KEY</name><num>-481</num></rc> */
	ARCH_THIS_IS_YOUR_KEY		= -481,	/* Cannot import your own key */

	/********************************************************************************
	** Entrust errors corresponding to system level errors(errno)
	********************************************************************************/

	/** <rc><name>ARCH_PAB_ERRNO_E2BIG</name><num>-474</num></rc> */
	ARCH_PAB_ERRNO_E2BIG		= -474, /*Error creating the key file - Argument list too long.*/ 
	
	/** <rc><name>ARCH_PAB_ERRNO_EACCES</name><num>-473</num></rc> */
	ARCH_PAB_ERRNO_EACCES		= -473, /*Error creating the key file - Permission denied.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EAGAIN</name><num>-472</num></rc> */
	ARCH_PAB_ERRNO_EAGAIN		= -472, /*Error creating the key file - No more processes or not enough memory or maximum nesting level reached.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EBADF</name><num>-471</num></rc> */
	ARCH_PAB_ERRNO_EBADF		= -471, /*Error creating the key file - Bad file number.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ECHILD</name><num>-470</num></rc> */
	ARCH_PAB_ERRNO_ECHILD		= -470, /*Error creating the key file - No spawned processes.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EDEADLOCK</name><num>-469</num></rc> */
	ARCH_PAB_ERRNO_EDEADLOCK	= -469, /*Error creating the key file - Resource deadlock would occur.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EDOM</name><num>-468</num></rc> */
	ARCH_PAB_ERRNO_EDOM			= -468, /*Error creating the key file - Math argument.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EEXIST</name><num>-467</num></rc> */
	ARCH_PAB_ERRNO_EEXIST		= -467, /*Error creating the key file - File exists.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EINVAL</name><num>-466</num></rc> */
	ARCH_PAB_ERRNO_EINVAL		= -466, /*Error creating the key file - Invalid argument.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EMFILE</name><num>-465</num></rc> */
	ARCH_PAB_ERRNO_EMFILE		= -465, /*Error creating the key file - Too many open files.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ENOENT</name><num>-464</num></rc> */
	ARCH_PAB_ERRNO_ENOENT		= -464, /*Error creating the key file - No such file or directory.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ENOEXEC</name><num>-463</num></rc> */
	ARCH_PAB_ERRNO_ENOEXEC		= -463, /*Error creating the key file - Exec format error.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ENOMEM</name><num>-462</num></rc> */
	ARCH_PAB_ERRNO_ENOMEM		= -462, /*Error creating the key file - Not enough memory.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ENOSPC</name><num>-461</num></rc> */
	ARCH_PAB_ERRNO_ENOSPC		= -461, /*Error creating the key file - No space left on device.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_ERANGE</name><num>-460</num></rc> */
	ARCH_PAB_ERRNO_ERANGE		= -460, /*Error creating the key file - Result too large.*/
	
	/** <rc><name>ARCH_PAB_ERRNO_EXDEV</name><num>-459</num></rc> */
	ARCH_PAB_ERRNO_EXDEV		= -459 /*Error creating the key file - Cross-device link error.*/

};

enum {

	/** <rc><name>CERT_X500_NEW_FAILED</name><num>-299</num></rc> */
	CERT_X500_NEW_FAILED 		= -299,	/* C++ new operator failed on embedded X500_Certificate */

	/** <rc><name>CERT_X500_NULL</name><num>-298</num></rc> */
	CERT_X500_NULL 				= -298,	/* Embedded X500_Certificate object is null */

	/** <rc><name>CERT_INVALID_CA_NOT_OURS</name><num>-297</num></rc> */
	CERT_INVALID_CA_NOT_OURS 	= -297,	/* IsValid() found that the cert's CA is not our CA */

	/** <rc><name>CERT_NOT_OURS_OR_EXTERNAL</name><num>-296</num></rc> */
	CERT_NOT_OURS_OR_EXTERNAL 	= -296,	/* Not our CA, not found in external archive. */

	/** <rc><name>CERT_EXTERNAL_VERIFY_FAILED</name><num>-295</num></rc> */
	CERT_EXTERNAL_VERIFY_FAILED = -295,	/* PAB certif didn't match */
	/********************************************************************************
	** CRL Logs
	********************************************************************************/

	/** <rc><name>CRL_X500_NEW_FAILED</name><num>-294</num></rc> */
	CRL_X500_NEW_FAILED 		= -294,	/* C++ new operator failed on embedded X500_CRL */

	/** <rc><name>CRL_X500_NULL</name><num>-293</num></rc> */
	CRL_X500_NULL 				= -293, /* Embedded X500_CRL object is null */

	/** <rc><name>CRL_INVALID_CA_NOT_OURS</name><num>-292</num></rc> */
	CRL_INVALID_CA_NOT_OURS 	= -292, /* IsValid() found that the CRL's CA is not our CA */

	/** <rc><name>CRL_CERTIFICATE_REVOKED</name><num>-291</num></rc> */
	CRL_CERTIFICATE_REVOKED 	= -291,	/* The passed certificate is on the revokation list */

	/** <rc><name>CRL_SIGNING_CERTIFICATE_REVOKED</name><num>-290</num></rc> */
	CRL_SIGNING_CERTIFICATE_REVOKED = -290, /* An error specific to signing certificate revocation */

	/** <rc><name>CRL_HAS_EXPIRED</name><num>-289</num></rc> */
	CRL_HAS_EXPIRED 			= -289,	/* The CRL has expired. */

	/** <rc><name>CRL_EXPIRED_BUT_USEABLE</name><num>-288</num></rc> */
	CRL_EXPIRED_BUT_USEABLE 	= -288, /* The CRL expired but within the useable window */
	/********************************************************************************
	**AttributeCertificate Logs
	********************************************************************************/

	/** <rc><name>ATTCERT_X500_NEW_FAILED</name><num>-287</num></rc> */
	ATTCERT_X500_NEW_FAILED		= -287,	/* C++ new operator failed on embedded X500_AttributeCertificate */

	/** <rc><name>ATTCERT_X500_NULL</name><num>-286</num></rc> */
	ATTCERT_X500_NULL			= -286, /* Embedded X500_AttributeCertificate object is null */

	/** <rc><name>ATTCERT_INVALID_CA_NOT_OURS</name><num>-285</num></rc> */
	ATTCERT_INVALID_CA_NOT_OURS	= -285,	/* IsValid() found that the AttCerts's CA is not our CA */

	/** <rc><name>ATTCERT_PARSE_ERROR</name><num>-284</num></rc> */
	ATTCERT_PARSE_ERROR			= -284,	/* Could not get X500_EntrustCAInfo out of AttCert */
	/********************************************************************************
	** CACertificates object errors
	********************************************************************************/

	/** <rc><name>CERT_INVALID_CACERTIFICATES</name><num>-283</num></rc> */
	CERT_INVALID_CACERTIFICATES	= -283,

	/** <rc><name>CERT_INVALID_V1_CACERTIFICATE</name><num>-282</num></rc> */
	CERT_INVALID_V1_CACERTIFICATE=-282,

	/** <rc><name>CERT_INVALID_V3_CACERTIFICATE</name><num>-281</num></rc> */
	CERT_INVALID_V3_CACERTIFICATE=-281,

	/** <rc><name>CERT_MISSING_V3_CACERTIFICATE</name><num>-280</num></rc> */
	CERT_MISSING_V3_CACERTIFICATE=-280,	/* Missing CA V1 Certificate - go ask the Entrust/Authority for the V3 CA Certif */

	/** <rc><name>CERT_MISSING_V1_CACERTIFICATE</name><num>-279</num></rc> */
	CERT_MISSING_V1_CACERTIFICATE=-279,	/* Missing CA V1 Certificate - trying to validate a V1 certif,crl,arl */

	/** <rc><name>CERT_V1_CACERTIF_ALREADY_LOADED</name><num>-278</num></rc> */
	CERT_V1_CACERTIF_ALREADY_LOADED=-278, /* Attempting to set a V1 certificate twice */

	/** <rc><name>CERT_V3_CACERTIF_ALREADY_LOADED</name><num>-277</num></rc> */
	CERT_V3_CACERTIF_ALREADY_LOADED=-277, /* Attempting to set a V1 certificate twice */

	/** <rc><name>CERT_CACERTIFS_UNINITIALIZED</name><num>-276</num></rc> */
	CERT_CACERTIFS_UNINITIALIZED= -276, /* Using the CACertificate object with no certificates loaded */

	/** <rc><name>CERT_CACERTIF_DN_MISMATCH</name><num>-275</num></rc> */
	CERT_CACERTIF_DN_MISMATCH	= -275,	/* The V1 and V3 CA names do not match */

	/** <rc><name>CERT_CACERTIF_WRONG_TYPE</name><num>-274</num></rc> */
	CERT_CACERTIF_WRONG_TYPE	= -274,	/* Client tried to set a certificate that was the wrong type */
	/***********************************************************************************
	** CrossCertificatePairs object errors
	***********************************************************************************/

	/** <rc><name>CCPAIR_X500_NEW_FAILED</name><num>-273</num></rc> */
	CCPAIR_X500_NEW_FAILED		= -273,	/* C++ new operator failed on embedded X500_CertificatePairs */

	/** <rc><name>CCPAIR_X500_NULL</name><num>-272</num></rc> */
	CCPAIR_X500_NULL			= -272, /* Embedded X500_CertificatePairs object is null */

	/** <rc><name>CCPAIR_PARSE_ERROR</name><num>-271</num></rc> */
	CCPAIR_PARSE_ERROR			= -271,	/* Could not parse X500_CertificatePairs */

	/** <rc><name>CCPAIR_INVALID_DN</name><num>-270</num></rc> */
	CCPAIR_INVALID_DN			= -270,	/* Invalid DN entered in certificate search */

	/** <rc><name>CCPAIR_NOT_FOUND</name><num>-269</num></rc> */
	CCPAIR_NOT_FOUND			= -269,	/* No matches in certificate search */
	/************************************************************************************
	** Certificate Extensions
	************************************************************************************/

	/** <rc><name>CERT_EXT_MISSING_DIST_POINT</name><num>-268</num></rc> */
	CERT_EXT_MISSING_DIST_POINT	= -268,

	/** <rc><name>CRL_EXT_ISSUE_DPOINT_WRONG</name><num>-267</num></rc> */
	CRL_EXT_ISSUE_DPOINT_WRONG	= -267,

	/** <rc><name>CRL_EXT_UNKNOWN_CRITICAL</name><num>-266</num></rc> */
	CRL_EXT_UNKNOWN_CRITICAL	= -266,

	/** <rc><name>CERT_EXT_UNKNOWN_CRITICAL</name><num>-265</num></rc> */
	CERT_EXT_UNKNOWN_CRITICAL	= -265,

	/** <rc><name>CRL_EXT_DECODE_CRITICAL_ERR</name><num>-264</num></rc> */
	CRL_EXT_DECODE_CRITICAL_ERR	= -264,

	/** <rc><name>CERT_EXT_DECODE_CRITICAL_ERR</name><num>-263</num></rc> */
	CERT_EXT_DECODE_CRITICAL_ERR= -263,

	/** <rc><name>CERT_EXT_NO_MATCH</name><num>-262</num></rc> */
	CERT_EXT_NO_MATCH			= -262,

	/** <rc><name>CERTPATH_NEW_CERT_FAILED</name><num>-253</num></rc> */
	CERTPATH_NEW_CERT_FAILED = -253,
	/** <rc><name>CERTPATH_PATH_NOT_FOUND</name><num>-252</num></rc> */
	CERTPATH_PATH_NOT_FOUND = -252,
	/** <rc><name>CERTPATH_TARGET_NOT_A_CACERT</name><num>-251</num></rc> */
	CERTPATH_TARGET_NOT_A_CACERT = -251, 
	/** <rc><name>CERTPATH_PATH_NODE_NOT_A_CACERT</name><num>-250</num></rc> */
	CERTPATH_PATH_NODE_NOT_A_CACERT = -250
};

enum {

	/** <rc><name>SK_ALLOC_ERROR</name><num>-199</num></rc> */
	SK_ALLOC_ERROR 				= -199,	/* Memory allocation failed */

	/** <rc><name>SK_BAD_KEY_FORMAT</name><num>-198</num></rc> */
	SK_BAD_KEY_FORMAT 			= -198,	/* Bad key format when trying to parse */

	/** <rc><name>SK_FBER_ERROR</name><num>-197</num></rc> */
	SK_FBER_ERROR 				= -197,	/* Internal BER formatting error occurred. */

	/** <rc><name>SK_BAD_DIGEST_FORMAT</name><num>-196</num></rc> */
	SK_BAD_DIGEST_FORMAT 		= -196,	/* Bad digest format when trying to parse */

	/** <rc><name>SK_START_ENC_FAILED</name><num>-195</num></rc> */
	SK_START_ENC_FAILED 		= -195,	/* StartEncryption failed */

	/** <rc><name>SK_ENCRYPT_FAILED</name><num>-194</num></rc> */
	SK_ENCRYPT_FAILED 			= -194,	/* Encryption failed */

	/** <rc><name>SK_END_ENC_FAILED</name><num>-193</num></rc> */
	SK_END_ENC_FAILED 			= -193,	/* EndEncryption failed */

	/** <rc><name>SK_START_DEC_FAILED</name><num>-192</num></rc> */
	SK_START_DEC_FAILED 		= -192,	/* StartDecryption failed */

	/** <rc><name>SK_DECRYPT_FAILED</name><num>-191</num></rc> */
	SK_DECRYPT_FAILED 			= -191,	/* Decryption failed */

	/** <rc><name>SK_END_DEC_FAILED</name><num>-190</num></rc> */
	SK_END_DEC_FAILED 			= -190,	/* EndDecryption failed */

	/** <rc><name>SK_RSA_DEPAD_FAILED</name><num>-189</num></rc> */
	SK_RSA_DEPAD_FAILED			= -189,	/* Problem encountered during RSA decryption, contact your administrator */

	/** <rc><name>SK_BAD_KEY_LEN</name><num>-188</num></rc> */
	SK_BAD_KEY_LEN 				= -188,	/* Bad key length specified */

	/** <rc><name>SK_MODE_NOT_SUPPORTED</name><num>-187</num></rc> */
	SK_MODE_NOT_SUPPORTED 		= -187,	/* Ciphermode not supported */

	/** <rc><name>SK_DATA_TOO_BIG</name><num>-186</num></rc> */
	SK_DATA_TOO_BIG 			= -186,	/* Input data too big */

	/** <rc><name>SK_PAD_NOT_SUPPORTED</name><num>-185</num></rc> */
	SK_PAD_NOT_SUPPORTED 		= -185, /* Padding type not supported */

	/** <rc><name>SK_OP_NOT_SUPPORTED</name><num>-184</num></rc> */
	SK_OP_NOT_SUPPORTED 		= -184,	/* Operation not supported */

	/** <rc><name>SK_BAD_KEYTYPE</name><num>-183</num></rc> */
	SK_BAD_KEYTYPE 				= -183,	/* Bad key type specified */

	/** <rc><name>SK_MAC_TOO_LONG</name><num>-182</num></rc> */
	SK_MAC_TOO_LONG 			= -182,	/* Specified MAC length is too long */

	/** <rc><name>SK_BAD_NUM_FORMAT</name><num>-181</num></rc> */
	SK_BAD_NUM_FORMAT 			= -181,	/* Bad number format */

	/** <rc><name>SK_PASSKEY_FAILED</name><num>-180</num></rc> */
	SK_PASSKEY_FAILED 			= -180,	/* Failed while trying to make passkey */

	/** <rc><name>SK_WRONG_ALG_ID</name><num>-179</num></rc> */
	SK_WRONG_ALG_ID 			= -179,	/* Received algorithm ID is wrong */

	/** <rc><name>SK_BAD_IV</name><num>-178</num></rc> */
	SK_BAD_IV 					= -178,	/* Attempted to parse bad CBC IV */

	/** <rc><name>SK_RNG_FAILED</name><num>-177</num></rc> */
	SK_RNG_FAILED 				= -177,	/* Random number generator failed */

	/** <rc><name>SK_SELF_TEST_FAILED</name><num>-176</num></rc> */
	SK_SELF_TEST_FAILED 		= -176,	/* Algorithm self-test failed */

	/** <rc><name>SK_DSA_ERROR</name><num>-175</num></rc> */
	SK_DSA_ERROR 				= -175,	/* Low-level DSA failure */

	/** <rc><name>SK_ABORTED</name><num>-174</num></rc> */
	SK_ABORTED 					= -174,	/* Process was aborted by request */

	/** <rc><name>SK_BAD_FORMAT</name><num>-173</num></rc> */
	SK_BAD_FORMAT 				= -173,	/* Bad data format when trying to parse */

	/** <rc><name>SK_KEY_GEN_FAILED</name><num>-172</num></rc> */
	SK_KEY_GEN_FAILED 			= -172,	/* Key generation failed */

	/** <rc><name>SK_BSAFE_ERROR</name><num>-171</num></rc> */
	SK_BSAFE_ERROR 				= -171,	/* BSAFE error */

	/** <rc><name>SK_CAST_SELF_TEST_FAILED</name><num>-170</num></rc> */
	SK_CAST_SELF_TEST_FAILED	= -170, /* CAST Self-test failed */

	/** <rc><name>SK_DES_SELF_TEST_FAILED</name><num>-169</num></rc> */
	SK_DES_SELF_TEST_FAILED		= -169,	/* DES Self-test failed */

	/** <rc><name>SK_RSA_SELF_TEST_FAILED</name><num>-168</num></rc> */
	SK_RSA_SELF_TEST_FAILED		= -168,	/* RSA Self-test failed */

	/** <rc><name>SK_DSA_SELF_TEST_FAILED</name><num>-167</num></rc> */
	SK_DSA_SELF_TEST_FAILED		= -167,	/* DSA Self-test failed */

	/** <rc><name>SK_MD2_SELF_TEST_FAILED</name><num>-166</num></rc> */
	SK_MD2_SELF_TEST_FAILED		= -166,	/* MD2 Self-test failed */

	/** <rc><name>SK_MD5_SELF_TEST_FAILED</name><num>-165</num></rc> */
	SK_MD5_SELF_TEST_FAILED		= -165,	/* MD5 Self-test failed */

	/** <rc><name>SK_SHA_SELF_TEST_FAILED</name><num>-164</num></rc> */
	SK_SHA_SELF_TEST_FAILED		= -164,	/* SHA Self-test failed */

	/** <rc><name>SK_OP_NOT_ALLOWED</name><num>-163</num></rc> */
	SK_OP_NOT_ALLOWED			= -163, /* Operation not allowed */

	/** <rc><name>SK_SW_AUTH_FAILED</name><num>-162</num></rc> */
	SK_SW_AUTH_FAILED			= -162,	/* Software authentication failed. The FIPS validation values in your entrust.ini file may not be up to date, or your software may have been modified without your knowledge.  Please contact your administrator.*/

	/** <rc><name>SK_NON_FIPS_RNG</name><num>-161</num></rc> */
	SK_NON_FIPS_RNG				= -161,	/* Attempt to use or install a non-FIPS RNG */

	/** <rc><name>SK_PASSWORD_INCORRECT</name><num>-160</num></rc> */
	SK_PASSWORD_INCORRECT		= -160,	/* Incorrect password supplied */

	/** <rc><name>SK_NEW_PASSWORD_INVALID</name><num>-159</num></rc> */
	SK_NEW_PASSWORD_INVALID		= -159,	/* New password doesn't pass the rules */

	/** <rc><name>SK_MISC_CRYPTOKI_ERROR</name><num>-158</num></rc> */
	SK_MISC_CRYPTOKI_ERROR		= -158,	/* Misc Cryptoki error */

	/** <rc><name>SK_DEVICE_REMOVED</name><num>-157</num></rc> */
	SK_DEVICE_REMOVED			= -157,	/* Cryptoki device was removed */

	/** <rc><name>SK_CRYPTOKI_NOT_SUPPORTED</name><num>-156</num></rc> */
	SK_CRYPTOKI_NOT_SUPPORTED	= -156,	/* Cryptoki not supported in this SK config   */

	/** <rc><name>SK_BAD_ALG_FORMAT</name><num>-155</num></rc> */
	SK_BAD_ALG_FORMAT			= -155,

	/** <rc><name>SK_RNG_NOT_INIT</name><num>-154</num></rc> */
	SK_RNG_NOT_INIT				= -154,

	/** <rc><name>SK_BAD_HASHER_TYPE</name><num>-153</num></rc> */
	SK_BAD_HASHER_TYPE			= -153,

	/** <rc><name>SK_MAC_CHECK_FAILED</name><num>-152</num></rc> */
	SK_MAC_CHECK_FAILED			= -152,

	/** <rc><name>SK_VERIFY_FAILED</name><num>-151</num></rc> */
	SK_VERIFY_FAILED			= -151,

	/** <rc><name>SK_ALREADY_LOGGED_IN</name><num>-150</num></rc> */
	SK_ALREADY_LOGGED_IN		= -150,	/* User already logged in */

	/** <rc><name>SK_UNKNOWN_OID</name><num>-149</num></rc> */
	SK_UNKNOWN_OID				= -149,	/* Unknown OID received */

	/** <rc><name>SK_BAD_ENDIAN</name><num>-148</num></rc> */
	SK_BAD_ENDIAN				= -148,	/* Endian test failed */

	/** <rc><name>SK_CAST3_SELF_TEST_FAILED</name><num>-147</num></rc> */
	SK_CAST3_SELF_TEST_FAILED	= -147, /* CAST3 selftest failed */

	/** <rc><name>SK_BYPASS_SELF_TEST_FAILED</name><num>-146</num></rc> */
	SK_BYPASS_SELF_TEST_FAILED	= -146,	/* FIPS 140-1 bypass selftest failed */

	/** <rc><name>SK_INVALID_PARMS</name><num>-145</num></rc> */
	SK_INVALID_PARMS			= -145,	/* Invalid algorithm parameters */

	/** <rc><name>SK_DH_SELFTEST_FAILED</name><num>-144</num></rc> */
	SK_DH_SELFTEST_FAILED		= -144,	/* Diffie-Hellman selftest failed */

	/** <rc><name>SK_UNKNOWN_PEM_ALG</name><num>-143</num></rc> */
	SK_UNKNOWN_PEM_ALG			= -143,	/* Unknown alg received in PEM header */

	/** <rc><name>SK_INI_FILE_MISMATCH</name><num>-142</num></rc> */
	SK_INI_FILE_MISMATCH		= -142,	/* Attempt to init with different entrust.ini file */

	/** <rc><name>SK_PROFILE_NOT_FOUND</name><num>-141</num></rc> */
	SK_PROFILE_NOT_FOUND		= -141,	/* The profile was not found. */

	/** <rc><name>SK_TOKEN_NOT_FOUND</name><num>-140</num></rc> */
	SK_TOKEN_NOT_FOUND			= -140,	/* The hardware crypto token was not found. */

	/** <rc><name>SK_BAD_USERTYPE</name><num>-139</num></rc> */
	SK_BAD_USERTYPE				= -139,	/* There is a bad usertype. */

	/** <rc><name>SK_ERROR_READING_PROFILE</name><num>-138</num></rc> */
	SK_ERROR_READING_PROFILE	= -138,	/* There is an error reading the profile. */

	/** <rc><name>SK_NOT_LOGGED_IN</name><num>-137</num></rc> */
	SK_NOT_LOGGED_IN			= -137,	/* The user must be logged on. */

	/** <rc><name>SK_NOT_SUPPORTED</name><num>-136</num></rc> */
	SK_NOT_SUPPORTED			= -136,	/* The Cryptomodule does not support this operation. */

	/** <rc><name>SK_BAD_CERT_TYPE</name><num>-135</num></rc> */
	SK_BAD_CERT_TYPE			= -135,	/* Bad certificate type. */

	/** <rc><name>SK_CAST5_SELF_TEST_FAILED</name><num>-134</num></rc> */
	SK_CAST5_SELF_TEST_FAILED	= -134,	/* CAST5 self-test failed. */

	/** <rc><name>SK_TOKEN_MEMORY</name><num>-133</num></rc> */
	SK_TOKEN_MEMORY				= -133,	/* H/W token out of memory */

	/** <rc><name>SK_INCOMPATIBLE_PROFILE</name><num>-132</num></rc> */
	SK_INCOMPATIBLE_PROFILE		= -132,	/* Incompatible epf */

	/** <rc><name>SK_PWD_INFO_DAMAGED</name><num>-131</num></rc> */
	SK_PWD_INFO_DAMAGED			= -131,	/* Password-related stuff in epf failed CRC check */

	/** <rc><name>SK_TOKEN_BUSY</name><num>-130</num></rc> */
	SK_TOKEN_BUSY				= -130,	/* H/W token is busy */

	/** <rc><name>SK_PASSWORD_REQUIRED</name><num>-129</num></rc> */
	SK_PASSWORD_REQUIRED		= -129, /* Password required for this operation */

	/** <rc><name>SK_SIGN_DERIVE_FAILED</name><num>-128</num></rc> */
	SK_SIGN_DERIVE_FAILED		= -128,	// Derivation of signature dependant data failed.

	/** <rc><name>SK_4755_BAD_KEY_TOKEN</name><num>-127</num></rc> */
	SK_4755_BAD_KEY_TOKEN		= -127, // Bad IBM 4755 key token

	/** <rc><name>SK_4755_HW_ERROR</name><num>-126</num></rc> */
	SK_4755_HW_ERROR			= -126,	// IBM 4755 hardware error

	/** <rc><name>SK_4755_INTERNAL_ERROR</name><num>-125</num></rc> */
	SK_4755_INTERNAL_ERROR		= -125,	// IBM 4755 internal error

	/** <rc><name>SK_4755_IF_ERROR</name><num>-124</num></rc> */
	SK_4755_IF_ERROR			= -124, // IBM 4755 interface error

	/** <rc><name>SK_HMAC_MD5_SELF_TEST_FAILED</name><num>-123</num></rc> */
	SK_HMAC_MD5_SELF_TEST_FAILED = -123,  // HMAC-MD5 selftest failed J.Bence Sept/97

	/** <rc><name>SK_HMAC_SHA_SELF_TEST_FAILED</name><num>-122</num></rc> */
	SK_HMAC_SHA_SELF_TEST_FAILED = -122,  // HMAC-SHA selftest failed J.Bence Sept/97

	/** <rc><name>SK_MASTER_KEY_NOT_FOUND</name><num>-121</num></rc> */
	SK_MASTER_KEY_NOT_FOUND		= -121,	// MasterKey not found on token

	/** <rc><name>SK_OAEP_DEPAD_FAILED</name><num>-120</num></rc> */
	SK_OAEP_DEPAD_FAILED		= -120,	// OAEP depadding failed

	/** <rc><name>SK_OAEP_PAD_FAILED</name><num>-119</num></rc> */
	SK_OAEP_PAD_FAILED			= -119, // OAEP padding failed.

	/** <rc><name>SK_BAD_KEK</name><num>-118</num></rc> */
	SK_BAD_KEK					= -118,	// Bad Key Encrypting Key entered

	/** <rc><name>SK_BAD_ENC_KEK</name><num>-117</num></rc> */
	SK_BAD_ENC_KEK				= -117,	// Bad encrypted KEK entered

	/** <rc><name>SK_DEVICE_SPECIFIC_ERR</name><num>-116</num></rc> */
	SK_DEVICE_SPECIFIC_ERR		= -116,	// Crypto h/w device-specific error

	/** <rc><name>SK_CRYPTOKI_SESSION</name><num>-115</num></rc> */
	SK_CRYPTOKI_SESSION			= -115,	// Problem with cryptoki session

	/** <rc><name>SK_TOKEN_BAD_KEY_LENGTH</name><num>-114</num></rc> */
	SK_TOKEN_BAD_KEY_LENGTH		= -114, // Token doesn't support proper key length // D.Boucher Apr/98

	/** <rc><name>SK_NO_DOMESTIC_TOKENS</name><num>-113</num></rc> */
	SK_NO_DOMESTIC_TOKENS		= -113, // Cannot use token-based profile from domestic version with export version.

	/** <rc><name>SK_PAKE_ERROR</name><num>-112</num></rc> */
	SK_PAKE_ERROR				= -112,	// Error occurred during password authenticated key exchange.

	/** <rc><name>SK_PAKE_PROTOFAILED</name><num>-111</num></rc> */
	SK_PAKE_PROTOFAILED			= -111,	// PAKE protocol failed.

	/** <rc><name>SK_PAKE_BADTOKEN</name><num>-110</num></rc> */
	SK_PAKE_BADTOKEN			= -110,	// Bad token given to key exchange.

	/** <rc><name>SK_PAKE_ALGDENIED</name><num>-109</num></rc> */
	SK_PAKE_ALGDENIED			= -109,	// Cannot use requested algorithm with key exchange.

	/** <rc><name>SK_PAKE_ALGNOTIMPL</name><num>-108</num></rc> */
	SK_PAKE_ALGNOTIMPL			= -108,	// PAKE algorithm not implemented.

	/** <rc><name>SK_PAKE_OUTOFSEQUENCE</name><num>-107</num></rc> */
	SK_PAKE_OUTOFSEQUENCE		= -107,	// PAKE calls made out of sequence.

	/** <rc><name>SK_PAKE_BADMESSAGE</name><num>-106</num></rc> */
	SK_PAKE_BADMESSAGE			= -106,	// Bad message sent to PAKE.

	/** <rc><name>SK_PAKE_NOMEM</name><num>-105</num></rc> */
	SK_PAKE_NOMEM				= -105,	// No memory available for key exchange.

	/** <rc><name>SK_EC_KEY_GEN_FAILED</name><num>-104</num></rc> */
	SK_EC_KEY_GEN_FAILED		= -104,	// Elliptic Curve key generation failed.

	/** <rc><name>SK_EC_SELF_TEST_FAILED</name><num>-103</num></rc> */
	SK_EC_SELF_TEST_FAILED		= -103,	// Elliptic Curve self test failed.

	/** <rc><name>SK_EC_BAD_POINT</name><num>-102</num></rc> */
	SK_EC_BAD_POINT				= -102,	// Elliptic Curve bad data.

	/** <rc><name>SK_EC_BAD_CURVE_PARMS</name><num>-101</num></rc> */
	SK_EC_BAD_CURVE_PARMS		= -101,	// Elliptic Curve bad data.

	/** <rc><name>SK_EC_BAD_FIELDSIZE</name><num>-100</num></rc> */
	SK_EC_BAD_FIELDSIZE			= -100,	// Elliptic Curve bad field/key size.

	/** <rc><name>SK_EC_BAD_PARMS</name><num>-99</num></rc> */
	SK_EC_BAD_PARMS				= -99,	// Elliptic Curve bad ASN.1 parms.

	/** <rc><name>SK_EC_SELF_TEST_NOT_SUPPORTED</name><num>-98</num></rc> */
	SK_EC_SELF_TEST_NOT_SUPPORTED = -98, // Elliptic Curve no self test for this key

	/** <rc><name>SK_EC_NOT_INTEROPERABLE</name><num>-97</num></rc> */
	SK_EC_NOT_INTEROPERABLE		= -97,	// Elliptic Curve non interoperable op

	/** <rc><name>SK_EC_NO_CURVE</name><num>-96</num></rc> */
	SK_EC_NO_CURVE				= -96,	// Elliptic Curve - No system parms available.

	/** <rc><name>SK_EC_BAD_SEED</name><num>-95</num></rc> */
	SK_EC_BAD_SEED				= -95,	// Bad seed for EC signing/key generation

	/** <rc><name>SK_RMD160_SELF_TEST_FAILED</name><num>-94</num></rc> */
	SK_RMD160_SELF_TEST_FAILED	= -94,	// RMD-160 self test failed

	/** <rc><name>SK_HMAC_RMD160_SELF_TEST_FAILED</name><num>-93</num></rc> */
	SK_HMAC_RMD160_SELF_TEST_FAILED = -93,  // HMAC-RMD160 self test failed

	/** <rc><name>SK_CRYPTOKI_LIB_NOT_FOUND</name><num>-92</num></rc> */
	SK_CRYPTOKI_LIB_NOT_FOUND	= -92,	// Cryptoki (PKCS#11) lib not found

	/** <rc><name>SK_INCOMPATIBLE_CRYPTOKI_LIB</name><num>-91</num></rc> */
	SK_INCOMPATIBLE_CRYPTOKI_LIB = -91,	// Incompatible Cryptoki library

	/** <rc><name>SK_CRYPTOKI_LIB_INIT_FAILED</name><num>-90</num></rc> */
	SK_CRYPTOKI_LIB_INIT_FAILED = -90,	// Cryptoki library init failed

	/** <rc><name>SK_INCOMPATIBLE_CRYPTOKI_DEV</name><num>-89</num></rc> */
	SK_INCOMPATIBLE_CRYPTOKI_DEV = -89,	// Cryptoki device not compatible with entrust

	/** <rc><name>SK_BAD_PARAM</name><num>-88</num></rc> */
	SK_BAD_PARAM				= -88,	// Bad parameter / argument format

	/** <rc><name>SK_SO_PIN_REQUIRED</name><num>-87</num></rc> */
	SK_SO_PIN_REQUIRED			= -87,	// Cryptoki device requires SO PIN

	/** <rc><name>SK_UNBLOCK_PIN_REQUIRED</name><num>-86</num></rc> */
	SK_UNBLOCK_PIN_REQUIRED		= -86,	// Cryptoki device requires unblocking PIN

	/** <rc><name>SK_BAD_PUBLIC_KEY</name><num>-85</num></rc> */
	SK_BAD_PUBLIC_KEY			= -85,	// Bad public key received

	/** <rc><name>SK_BAD_KEK_OR_EKEK</name><num>-84</num></rc> */
	SK_BAD_KEK_OR_EKEK			= -84,	// Bad KEK or encrypted KEK

	/** <rc><name>SK_CRYPTOKI_INIT_TOKEN_NOT_SUPPORTED</name><num>-83</num></rc> */
	SK_CRYPTOKI_INIT_TOKEN_NOT_SUPPORTED = -83, // Token doesn't support init token

	/** <rc><name>SK_PIN_EXPIRED</name><num>-82</num></rc> */
	SK_PIN_EXPIRED				= -82,	// Cryptoki PIN has expired

	/** <rc><name>SK_INVALID_HARDWARE_USER_STATE</name><num>-81</num></rc> */
	SK_INVALID_HARDWARE_USER_STATE = -81,		// User's CryptokiAPI is in invalid state 

	/** <rc><name>SK_ILLEGAL_HARDWARE_RESULT</name><num>-80</num></rc> */
	SK_ILLEGAL_HARDWARE_RESULT = -80,	// Illegal result received from crypto hardware

	/** <rc><name>SK_UNWRAPPINGKEY_NOT_FOUND</name><num>-79</num></rc> */
	SK_UNWRAPPINGKEY_NOT_FOUND = -79,	// The SCMS Unwrapping Key was not found

	/** <rc><name>SK_INCONSISTENT_OBJECT_COUNT</name><num>-78</num></rc> */
	SK_INCONSISTENT_OBJECT_COUNT = -78,	// Inconsistent number of objects on token (0 or more than 1)

	/** <rc><name>SK_HW_DEVICE_ERROR</name><num>-77</num></rc> */
	SK_HW_DEVICE_ERROR = -77,			// Problem reported with crypto hardware.

	/** <rc><name>SK_CRYPTOKI_FIPS_NOT_SUPPORTED</name><num>-76</num></rc> */
	SK_CRYPTOKI_FIPS_NOT_SUPPORTED = -76,	// This crypto hardware device cannot operate in FIPS mode

	/** <rc><name>SK_RNG_SELF_TEST_FAILED</name><num>-75</num></rc> */
	SK_RNG_SELF_TEST_FAILED = -75,			// RNG self-test failed.

	/** <rc><name>SK_UNKNOWN_CRYPTOKI_ERROR_CODE</name><num>--74</num></rc> */
	SK_UNKNOWN_CRYPTOKI_ERROR_CODE = -74,	// The cryptoki error code returned is not recognized.

	/** <rc><name>SK_SHA256_SELF_TEST_FAILED</name><num>-73</num></rc> */
	SK_SHA256_SELF_TEST_FAILED = -73,		// SHA-256 Self-test failed

	/** <rc><name>SK_CRYPTOKI_KEY_TRANSFER_NOT_SUPPORTED</name><num>-72</num></rc> */
	SK_CRYPTOKI_KEY_TRANSFER_NOT_SUPPORTED = -72 // Cryptoki protected key transfer not supported.
};

#endif

#endif

