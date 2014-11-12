/*******************************************************************************
 * entcert.h - EntCertificate class declarations.                                             
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.          
 ******************************************************************************/

#ifndef ENTCERT_H    
#define ENTCERT_H

#include <time.h>
#if !defined( ENTAPI )
#include <entbdefs.h>  
#include <entbdata.h>
#else
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/bindata.h>
#endif  

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class EntFile;
class CTctx;
class CTLctx;
class CertifInfo; 
class CertificateList;
class CVOctx;
      
//
// An EntCertificate stores an X.509 public key certificate.
// Member functions allow access to various information fields within
// the certificate.
// Each EntCertificate object created is associated with an 
// EntFile user context, and become invalid if that EntFile object is deleted.
//
class EntCertificate {

public:        
	// Constructor must be supplied a reference to a valid EntFile object.
	EXPT32 EXPT EntCertificate(const EntFile& entUser); 
	                                               
	       
	// Copy Constructor must be supplied a reference to a valid EntCertificate object.
	EXPT32 EXPT EntCertificate(const EntCertificate& cert); 

	//
	// This constructor can be used to populate the certificate with
	// the contents of the provided BinData, which will be copied to internal storage.
	// Set isASCIIencoded to TRUE if the provided certificate is in ASCII encoded format.	                                               
	//
	EXPT32 EXPT EntCertificate(const EntFile& entUser, const BinData& certificate, const BOOL isASCIIencoded); 
					 
	EXPT32 EXPT ~EntCertificate(); // destructor
	
	EXPT32 void EXPT Reset(); // initialize object
	//
	// LoadCertificate populates the EntCertificate object with
	// the contents of the provided BinData, which will be copied to internal storage.
	// Set isASCIIencoded to TRUE if the provided certificate is in ASCII encoded format.	                                               
	//
	EXPT32 EntLog EXPT LoadCertificate(const BinData& certificate, const BOOL isASCIIencoded); 

	// GetConstructorError returns the status of the constructor call.	
	EXPT32 EntLog EXPT GetConstructorError();
	
	//
	// GetCertificate copies the raw certificate to the provided BinData, optionally
	// in an ASCII encoded format.
	//
	EXPT32 EntLog EXPT GetCertificate(BinData& certificate, const BOOL ASCIIencode);
	//
	// These functions provide name information from the certificate.
	//
	EXPT32  EntLog EXPT GetSubject(GString& subjectName); // unique name
	EXPT32  EntLog EXPT GetSubjectCommonName(GString& commonName); // cn attribute, if present
	EXPT32  EntLog EXPT GetIssuer(GString& issuerName); // unique name of issuing CA.
	//                            
	// These functions provide miscellaneous information from the certificate.
	// Note that all certificates may not contain all information fields, as several
	// of these fields are optional certificate extensions.
	//  
	// GetValidity returns the validity period of the certificate. Values returned are
	// in the format: number of seconds since 00:00 January 1st 1970.
	EXPT32  EntLog EXPT GetValidity(time_t& validNotBefore, time_t& validNotAfter);
	//  
	// GetPrivateKeyEndValidity returns the end validity period of the private signing key
	// associated with the verification public key certificate. 
	// Note that this is only applicable to signature verification certificates. 
	// Values returned are in the format: number of seconds since 00:00 January 1st 1970.
	EXPT32  EntLog EXPT GetPrivateKeyEndValidity(time_t& validNotAfter);
	//  
	// GetDistributionPoint returns the CRL or ARL distribution point: the location in
	// the directory where this certificate's revocation list can be found.
	EXPT32  EntLog EXPT GetDistributionPoint(GString& distributionPoint);
	//  
	// GetEMailAddress returns the RFC822 electronic mail address of the certificate's owner,
	// as conveyed in the certificate's subjectAltName field.
	EXPT32  EntLog EXPT GetEMailAddress(GString& eMailAddress);
	//
	// GetSerialNumber and GetLongSerialNumber return the certificates serial number.
	// This may be a simple 32 bit value, or a longer data string. In the latter
	// case GetSerialNumber() will return an error (ENT_CERT_FIELD_NOT_FOUND)
	// indicating that GetLongSerialNumber()
	// should be called to get the extended value.
	EXPT32  EntLog EXPT GetSerialNumber(UINT32& serialNumber);

	// This function will return ENT_CERT_FIELD_NOT_FOUND if the certificate serial
	// number is a simple 32 bit integer (in which case GetSerialNumber() should
	// be called instead).
	EXPT32  EntLog EXPT GetLongSerialNumber(BinData& serialNumber);
	//
	// The version numbers start at zero, so 0 implies X.509 version 1 certificates,
	// 2 implies X.509 version 3 certificates, etc. 
	EXPT32  EntLog EXPT GetVersion(INT16& version);
	
	// HasKeyUsage returns TRUE if keyUsage is applicable to the certificate, FALSE otherwise.
	EXPT32 BOOL EXPT HasKeyUsage( );

	// GetKeyUsage sets the supported parameter TRUE if the specified keyUsage is applicable
	// to the certificate, FALSE otherwise.
	EXPT32 EntLog EXPT GetKeyUsage(const KEY_USAGE keyUsage, BOOL& supported);

	// GetFingerprint returns the MD5 fingerprint of your certificate 
	// in the string format HH:HH:HH:... where HH are
	// hex digits - 16 pairs of hex digits make up the fingerprint.
	// Certificate fingerprints can be used in out of band comparisons with
	// the certificate originator for authentication purposes.
	EXPT32 EntLog EXPT GetFingerprint(GString& fingerPrint);

	// The following two functions can be used to retrieve any certificate policy
	// OIDs (Object IDentifiers) which may be present in the certificate.
	EXPT32 EntLog EXPT GetNumberOfCertificatePolicyOIDs(UINT32& numPolicyOIDs);
	EXPT32 EntLog EXPT GetCertificatePolicyOID(const UINT32 index, GString& certPolicyOID);

	// Assignment Operator
	EXPT32 EntCertificate& EXPT operator=( const EntCertificate& cert );

	// Equality Operators
	EXPT32 BOOL EXPT operator==( const EntCertificate& cert );
	EXPT32 BOOL EXPT operator==( const GString& dn );

	// Static utility functions
	EXPT32 static BOOL EXPT MatchDNs( const GString& dn1, const GString& dn2 );

	// data members, for use by "C" implementation
	BinData m_bincert;
	CertifInfo* m_certinfo;
	

	// If the certificate object has been verified, GetVerificationSource sets <source> to the
	// source that verified the certificate and sets the <verified> parameter to TRUE. Otherwise, 
	// <verified> is set to FALSE and <source> is set to VS_NO_SOURCE.  
	EXPT32 EntLog EXPT GetVerificationSource(VERIFICATION_SOURCE& source, BOOL& verified);

	// aa28176 - does the cert contain the input extKeyUsage OID?
	// the GString passed should be a period-separated sequence of numbers without spaces to represent the OID
	// Returns	ENT_OK if found.  
	//			CERT_EXT_NO_MATCH if the certificate does not contain it
	//			other errors possible if problems occur with the certificate.
	EXPT32 EntLog EXPT HasExtKeyUsage( const GString& toSearchFor );

	// GetSHA1Fingerprint returns the SHA1 fingerprint of your certificate 
	// in the string format HH:HH:HH:... where HH are
	// hex digits - 16 pairs of hex digits make up the fingerprint.
	// Certificate fingerprints can be used in out of band comparisons with
	// the certificate originator for authentication purposes.
	EXPT32 EntLog EXPT GetSHA1Fingerprint(GString& fingerPrint);

private:

	CTctx* m_ctx;
	EntLog m_constructorError;

};

//
// EntCertificateList() class definition.
// EntCertificateLists store lists of certificates, which can be examined in more
// detail with the GetEntry() function and the EntCertificate member functions
// defined above.
// Note that certificate lists can be used to create entries in your Personal Address
// Book (PAB), using the EntFile::ImportCertificateList() function.

class EntCertificateList {
    friend class EntFile;
    friend class SMIMEUnprot;
    friend class SMIMEProt;
    friend class SMIMESgnr;
    friend class SMIMERecipientName;
public:
	EXPT32 EXPT EntCertificateList(const EntFile& entUser);
	EXPT32 EXPT ~EntCertificateList(void);

	EXPT32 UINT16 EXPT GetNumberOfEntries(void);
	EXPT32 EntLog EXPT GetEntry(const UINT16 index, 
								EntCertificate& certificate ); 


	// AddEntry adds an EntCertificate to the end of the list.
	EXPT32 EntLog EXPT AddEntry(const EntCertificate& certificate ); 

	// DeleteEntry removes the EntCertificate specified by index
	// from the list.
	EXPT32 EntLog EXPT DeleteEntry(const UINT16 index ); 

	// GetConstructorError returns the status of the constructor call.	
	EXPT32 EntLog EXPT GetConstructorError();

	// Reset empties the certificate list.
	EXPT32 EntLog EXPT Reset();

	//Get the type of cache this list is pointing to, if any
	CACHE_TYPE GetCacheType();

private:
	CTLctx* m_ctx;
	EntLog m_constructorError;
	CertificateList* GetCertificateList();
	void SetCertificateList(CertificateList& certList);
	EntCertificateList(EntFile& entUser, const CACHE_TYPE cacheType);
};


//
// EntCertificateVerificationOptions allows control
// of various certificate verification options, associated
// with a specified Entrust login context (EntFile object).
// The default settings are indicated below.
// Settings manipulated through this class affect all certificate
// verification operations performed by that EntFile object.
// An EntCertificateVerificationOptions object, once created,
// is only useable for the lifetime of the associated EntFile object.
//
class EntCertificateVerificationOptions
{
	friend class EntFile;
public:
	// Constructor must be supplied a reference to a valid EntFile object.
	EXPT32 EXPT EntCertificateVerificationOptions(const EntFile& entUser);
	EXPT32 EXPT ~EntCertificateVerificationOptions();

	// SetRevocationChecking allows ARL and CRL checking to be enabled or
	// disabled. By default it is enabled.
	EXPT32 EntLog EXPT SetRevocationChecking(const BOOL enable); 
	
	// GetRevocationChecking sets the enabled parameter to indicate
	// if revocation checking
	// is enabled (TRUE) or disabled (FALSE).
	EXPT32 EntLog EXPT GetRevocationChecking(BOOL& enabled);

private:
	CVOctx* m_ctx;	
};


#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif  
