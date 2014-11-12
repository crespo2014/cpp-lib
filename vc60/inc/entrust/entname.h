/*******************************************************************************
 * entname.h - EntrustName and EntrustNameList class declarations.                                             
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.          
 ******************************************************************************/

#ifndef ENTNAME_H    
#define ENTNAME_H

#if !defined( ENTAPI )
#include <entcert.h>
#include <entgstr.h>  
#else
#include <toolkit/entapi/entcert.h>
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/gstring.h>
#include <base/etfile/entlog.h>
#endif  

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class MatchedName;
class MatchedNameList;
      
//
// An EntrustName contains information about a directory entry (e.g. an
// X.500 directory entry). The entry contains the following information,
// which can be extracted via a set of utility member functions:
// - a unique name which is used to distinguish this entry from others.
// - a list of "attributes". Each attribute defines an information type,
//   such as common name, organizational unit, phone number, etc. The
//   set of attributes is defined by the directory administrator.
// - per attribute, a list of values. For example, a user might have
//   multiple "phone number" entries.
// Note that the unique name, attributes and values are all
// represented as GString objects, which internally store a character string.
//      
class EntrustName {
public:               
	EXPT32 EXPT EntrustName(); // constructor
	EXPT32 EXPT EntrustName(const EntrustName& name); // constructor
	EXPT32 EntrustName& EXPT operator=( const EntrustName& name);
					 
	EXPT32 EXPT ~EntrustName(); // destructor
	//
	// GetUniqueName returns a GString containing the unique name field of the
	// EntrustName.
	//
	EXPT32 GString EXPT GetUniqueName(void);
	//
	// GetNumberOfAttributes returns the number of attributes defined for the 
	// EntrustName object, or -1 on error.
	//
	EXPT32 INT16 EXPT GetNumberOfAttributes(void);
	//
	// GetAttribute returns the attribute name indicated by index.
	//
	EXPT32 EntLog EXPT GetAttribute(GString& attribute, SYSINT index);
	//
	// GetNumberOfAttributeValues returns, via pointer numAttrValues, the number of
	// values associated with the attribute indicated by index.
	//
	EXPT32 EntLog EXPT GetNumberOfAttributeValues(INT16 *numAttrValues, SYSINT attributeIndex);
	//
	// GetAttributeValue returns, via a GString, the value
	// indexed by attributeIndex and valueIndex.
	//
	EXPT32 EntLog EXPT GetAttributeValue(GString& value, SYSINT attributeIndex, SYSINT valueIndex);  

	//
	// GetEncryptionCertificate returns, via an EntCertificate object, 
	// the encryption public key certificate associated with the EntrustName, 
	// if a certificate attribute exists.
	// It can be called after EntFile::ValidateRecipients() to examine
	// the encryption certificates of the recipients.
	//
	EXPT32 EntLog EXPT GetEncryptionCertificate(EntCertificate& cert);  

	//
	// SetAttributeValue adds an attribute-value pair to the EntrustName.
	// If the specified attribute already exists, processing is as follows:
	//   If the replace BOOL is TRUE, any existing values are removed, 
	//   and the specified value is added.
	//   If replace is FALSE, the specified value is added to the list of
	//   existing values.
	// If the specified attribute does not already exist, replace is
	// ignored and a new attribute with the specified value is added.
	// Return values attributeIndex and valueIndex indicate where within
	// the EntrustName the values were added.
	//
	EXPT32 EntLog EXPT SetAttributeValue(	const GString& attribute, 
											const GString& value,
											const BOOL replace,
											INT16* attributeIndex,
											INT16* valueIndex );

	//
	// SetEncryptionCertificate sets the encryption public key certificate
	// attribute for the EntrustName to cert. This function can be used 
	// if the application wants to prevent the Toolkit from retrieving the
	// associated recipient's encryption certificate via the 
	// Entrust public key infrastructure. Certificates supplied in this
	// manner are still validated before use.
	//
	EXPT32 EntLog EXPT SetEncryptionCertificate(EntCertificate& cert);

	//
	// GetValidateFailReason returns an EntLog specifying why the
	// EntrustName failed validation as an intended encryption recipient. 
	// ENT_OK is returned if there is no failure reason.
	// Recipient validation is checked by EntFile::ValidateRecipients, and
	// EntFile::CreateHeader.
	//
	EXPT32 EntLog EXPT GetValidateFailReason(void); 

	// These 2 functions are not exported and are for internal use only. 	
	EntLog AssignMatchedName(MatchedName* matchedName);
	EntLog CopyMatchedName(MatchedName* matchedName, BOOL create = FALSE);

	MatchedName* m_MatchedName;
		
private:
	BOOL m_Alloc;

};

//
// An EntrustNameList is simply a list of EntrustNames. It is returned from
// directory searches (in which the list contains the directory entries which
// matched a specified search criteria), and used to specify recipients for
// encryption operations. The member functions provide some simple utilities
// the access the EntrustName objects in the list.
//
class EntrustNameList {
public:
	EXPT32 EXPT EntrustNameList(void);
	EXPT32 EXPT EntrustNameList(const EntrustNameList& list);
	EXPT32 EXPT ~EntrustNameList(void); 
	//
	// GetNumberOfNames returns the number of EntrustNames in the list.
	//
	EXPT32 INT16 EXPT GetNumberOfNames(void);
	//
	// GetEntrustName returns the EntrustName indicated by index.
	//
	EXPT32 EntLog EXPT GetEntrustName(EntrustName& name, SYSINT index); 
	
	// GetEntrustName returns the EntrustName indicated by UniqueName.
	//
	EXPT32 EntLog EXPT GetEntrustName(EntrustName& name, const GString& uniqueName); 
	//
	// GetUniqueName returns the unique name field of the
	// EntrustName indicated by index.
	//
	EXPT32 EntLog EXPT GetUniqueName(GString& uniqueName, SYSINT index); 
	//
	// GetValidateFailReason returns an EntLog specifying why the indexed
	// EntrustName failed validation as an intended encryption recipient.
	// This function would typically be called after 
	// EntFile::ValidateRecipients or EntFile::CreateHeader,
	// on members of the "nlInvalid" EntrustNameList.
	// ENT_OK is returned if there is no failure reason.
	//
	EXPT32 EntLog EXPT GetValidateFailReason(SYSINT index); 

	//
	// AddEntrustName adds the supplied EntrustName to the EntrustNameList.
	// The return integer is the index where the name was added.
	//
	EXPT32 INT16 EXPT AddEntrustName(EntrustName& name);
 
	//
	// AddEntrustName adds an EntrustName (with the supplied
	// unique name as a GString) to the EntrustNameList.
	// The return int is the index where the name was added.
	//
	EXPT32 INT16 EXPT AddEntrustName(GString& uniqueName);
 
	//
	// RemoveEntrustName searches the EntrustNameList for an entry
	// whose Unique Name matches the Unique Name of the supplied
	// EntrustName parameter. That entry is then deleted from the list. 
	//
	EXPT32 EntLog EXPT RemoveEntrustName(EntrustName& name);
	//
	// RemoveEntrustName searches the EntrustNameList for an entry
	// whose Unique Name matches the uniqueName provided.
	// That entry is then deleted from the list. 
	//
	EXPT32 EntLog EXPT RemoveEntrustName(GString& uniqueName);
	//
	// Reset deletes all entries from the list.
	//
	EXPT32 void EXPT Reset(void);

	// 
	// Assignment operator
	//
	EXPT32 EntrustNameList& operator=( const EntrustNameList& list );

	MatchedNameList* m_MatchedNameList;
	
};

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif  
