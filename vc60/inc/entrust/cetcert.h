/*******************************************************************************
 * cetcert.h - Certificate information declarations.                                             
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.          
 ******************************************************************************/

#ifndef CETCERT_H    
#define CETCERT_H

#include <time.h>
#if !defined( ENTAPI )
#include <entbdefs.h>  
#else
#include <toolkit/entapi/tkbdefs.h>
#endif  

#ifdef __cplusplus
extern "C" {
#endif                                                        

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

/* 
   An ETContext internally maintains storage for an X.509 Public Key
   Certificate, in order to support the certificate utility functions
   defined in this header file.
   This storage is loaded with certificate information when any of the
   following functions is called:
   - ETLoadCertificate()
   - ETLoadCertificateFromList()
   - ETGetEncryptionCertificate()
   - ETSetEncryptionCertificate()
   - ETGetUserEncryptionCertificate()
   - ETGetUserVerificationCertificate()
   - ETGetIssuerVerificationCertificate()
   - ETStartDecryptVerify(), if the indicated header type is
                             HT_SIGN_ONLY or HT_SIGN_AND_ENCRYPT.
   - ETGetArchiveResults(), if the applicable encapsulated file is digitally signed,
   							and the saveVerificationCertificates flag was set to
   							TRUE in the previous call to ETSetArchiveDecryptVerify.
   
   Any of the above functions will overwrite the previously stored certificate.
   The certificate storage is de-allocated when ETLogout() is called.  
*/
/*
   ETLoadCertificate can be used to copy an external certificate into the
   ETContext's certificate storage.
   Set isASCIIencoded to TRUE if the provided certificate is in ASCII encoded format.	                                               
*/
ETEXPORT32 EntLog ETEXPORT ETLoadCertificate(const ETContext ctx, const ETBinData32* certificate, const BOOL isASCIIencoded); 
					 
/*
   ETLoadCertificateFromList copies the indexed entry of the internally stored CertificateList into the
   ETContext's certificate storage.
   See CertificateList definitions below for more information.
*/
ETEXPORT32 EntLog ETEXPORT ETLoadCertificateFromList(const ETContext ctx, 
												 const UINT16 index); 

/*
   ETGetCertificate sets up the provided ETBinData32 to point to the internal certificate
   storage (which is binary). Use ETASCIIencode (defined in CETAPI.H) to convert the
   certificate to ASCII format.
*/
ETEXPORT32 EntLog ETEXPORT ETGetCertificate(const ETContext ctx, ETBinData32* certificate);
/*
   These functions provide name information from the certificate. Pointers to
   internal storage are returned.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertSubject(const ETContext ctx, char** subjectName);  /* unique name */
ETEXPORT32  EntLog ETEXPORT ETGetCertSubjectCommonName(const ETContext ctx, char** commonName); /* common name if present */
ETEXPORT32  EntLog ETEXPORT ETGetCertIssuer(const ETContext ctx, char** issuerName); /* unique name of issuing CA */
/*                            
   These functions provide miscellaneous information from the certificate. The
   information is copied to the provided pointers.
   Note that all certificates may not contain all information fields, as several
   of these fields are optional certificate extensions.

*/
/* GetValidity returns the validity period of the certificate. Values returned are
in the format: number of seconds since 00:00 January 1st 1970.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertValidity(	const ETContext ctx, 
											time_t* validNotBefore, 
											time_t* validNotAfter);
/*  
   ETGetCertPrivateKeyEndValidity returns the end validity period of the private signing key
   associated with the verification public key certificate. 
   Note that this is only applicable to signature verification certificates. 
   Values returned are in the format: number of seconds since 00:00 January 1st 1970.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertPrivateKeyEndValidity(const ETContext ctx, 
													   time_t* validNotAfter);
/*  
   ETGetCertDistributionPoint returns the CRL or ARL distribution point: the location in
   the directory where this certificate's revocation list can be found.
   A pointer to internal storage is returned.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertDistributionPoint(const ETContext ctx, 
												   char** distributionPoint);
/*  
   ETGetCertEMailAddress returns the RFC822 electronic mail address of the certificate's owner,
   as conveyed in the certificate's subjectAltName field.
   A pointer to internal storage is returned.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertEMailAddress(const ETContext ctx, 
											  char** eMailAddress);
/*
   ETGetCertSerialNumber and ETGetCertLongSerialNumber return the certificates serial number.
   This may be a simple 32 bit value, or a longer data string. In the latter
   case ETGetCertSerialNumber() will return an error (ENT_CERT_FIELD_NOT_FOUND)
   indicating that ETGetCertLongSerialNumber()
   should be called to get the extended value.
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertSerialNumber(const ETContext ctx, UINT32* serialNumber);

/* This function will return ENT_CERT_FIELD_NOT_FOUND if the certificate serial
   number is a simple 32 bit integer (in which case ETGetCertSerialNumber() should
   be called instead).
*/
ETEXPORT32  EntLog ETEXPORT ETGetCertLongSerialNumber(const ETContext ctx, ETBinData32* serialNumber);

/* The version numbers start at zero, so 0 implies X.509 version 1 certificates,
   2 implies X.509 version 3 certificates, etc. 
*/ 
ETEXPORT32  EntLog ETEXPORT ETGetCertVersion(const ETContext ctx, INT16* versionNumber);
	
/* ETGetCertKeyUsage sets the supported parameter TRUE if the specified keyUsage is applicable
   to the certificate, FALSE otherwise.
*/
ETEXPORT32 EntLog ETEXPORT ETGetCertKeyUsage(const ETContext ctx, 
										 const KEY_USAGE keyUsage, 
										 BOOL* supported);

/* ETGetCertFingerprint returns the MD5 fingerprint of your certificate 
   in the string format HH:HH:HH:... where HH are
   hex digits - 16 pairs of hex digits make up the fingerprint.
   Certificate fingerprints can be used in out of band comparisons with
   the certificate originator for authentication purposes.
   A pointer to internal storage is passed via the fingerPrint parameter.
*/
ETEXPORT32 EntLog ETEXPORT ETGetCertFingerprint(const ETContext ctx, 
											char** fingerPrint);

/* The following two functions can be used to retrieve any certificate policy
   OIDs (Object IDentifiers) which may be present in the certificate.
*/
ETEXPORT32 EntLog ETEXPORT ETGetCertNumberOfPolicyOIDs(const ETContext ctx, 
												   UINT32* numPolicyOIDs);
/* A pointer to internal storage is passed via the certPolicyOID parameter. */
ETEXPORT32 EntLog ETEXPORT ETGetCertPolicyOID(const ETContext ctx, 
										  const UINT32 index, 
										  char** certPolicyOID);
/*
   ETResetCertificate initializes the certificate storage to an empty state.
*/
ETEXPORT32 void ETEXPORT ETResetCertificate(const ETContext ctx); 

/* CertificateList Definitions 
   An ETContext internally maintains storage for list of X.509 Public Key
   Certificates, in order to support the certificate list utility functions
   defined below.
   This storage is loaded with certificate list information when any of the
   following functions is called:
   - ETEndUnprotect()
   - ETFileUnprotect()
   Certificates from the list can be examined in detail by using the 
   ETLoadCertificateFromList() function followed by the ETGetCert...() information
   functions defined above.
   
   Any of the above functions will overwrite the previously stored certificate list.
   The certificate list storage is de-allocated when ETLogout() is called.
   Note that certificate lists can be used to create entries in your Personal Address
   Book (PAB), using the ETImportCertificateList() function. */

/* ETGetNumberOfCertificates returns the number of certificates in the internal list */
ETEXPORT32 UINT16 ETEXPORT ETGetNumberOfCertificates(const ETContext ctx);

/* ETResetCertificateList initializes the internal certificate list to empty. */
ETEXPORT32 EntLog ETEXPORT ETResetCertificateList(const ETContext ctx);

/* ETAddCertificateToList adds a copy of the internally stored certificate
   (for example, populated by ETLoadCertificate() ),
   to the end of the internal certificate list */
ETEXPORT32 EntLog ETEXPORT ETAddCertificateToList(const ETContext ctx);

/* ETDeleteCertificateFromList removes the certificate specified by index 
   from the internal certificate list */
ETEXPORT32 EntLog ETEXPORT ETDeleteCertificateFromList(const ETContext ctx,
												   const UINT16 index);


/*
   Certificate Verification Options (CVO) utilities allow control
   of various certificate verification options, associated
   with a specified Entrust login context (ETContext object).
   The default settings are indicated below.
   Settings manipulated through these utilities affect all certificate
   verification operations performed by that login context.
*/

/* ETCVO_SetRevocationChecking allows ARL and CRL checking to be enabled or
   disabled. By default it is enabled.
*/
ETEXPORT32 EntLog ETEXPORT ETCVO_SetRevocationChecking(	const ETContext ctx,
													const BOOL enable); 
	
/* ETCVO_GetRevocationChecking sets the enabled flag indicating 
   if revocation checking
   is enabled (TRUE) or disabled (FALSE).
*/
ETEXPORT32 EntLog ETEXPORT ETCVO_GetRevocationChecking(	const ETContext ctx,
													BOOL* enabled);
/* ETSetCertificateListToCache sets the internal certificate cache storage, 
    which can be manipulated by the certificate list functions above, to the
    specified cache. This allows a cache to be examined or modified.
    CCH_ALL cannot be specified as the cacheType. */
ETEXPORT32 EntLog ETEXPORT ETSetCertificateListToCache(const ETContext ctx, const CACHE_TYPE cacheType);

/* aa28176 - does the cert in ctx's m_entCert contain the input extKeyUsage OID?
  The char* passed should be a period-separated sequence of numbers without spaces to represent the OID
  Returns	ENT_OK if found.  
			CERT_EXT_NO_MATCH if the certificate does not contain it
			other errors possible if problems occur with the certificate.
*/
ETEXPORT32 EntLog ETEXPORT ETCertHasExtKeyUsage( const ETContext ctx, const char* toSearchFor );



#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif  

