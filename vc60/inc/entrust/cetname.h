/******************************************************************************
 * cetname.h - Name List manipulation routines.                                             
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.          
 *****************************************************************************/

#ifndef CETNAME_H
#define CETNAME_H

#if !defined( ENTAPI )
#include <entbdefs.h>
#else
#include <toolkit/entapi/tkbdefs.h>
#include <base/etfile/entlog.h>
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
   An ETContext internally maintains the following 6 name lists:
   NL_SearchResults: this name list contains the results of an
		ETDirectorySearch call. If subsequent searches are made, the
		new results are appended to the end of the list. The ETResetNameList
		function can be used to re-initialize the list to an empty state.
   NL_Recipients: this name list contains names of intended recipients
		for an  encryption operation. This list is usually a
		subset of names retrieved in the NL_SearchResults list.
   NL_Invalid: this name list is used to store the names of
		intended recipients who did not have valid public key
		certificates.
   NL_Group1, NL_Group2, NL_Group3: these name lists are provided for
   		convenience when editting recipient groups,
    	which are shorthand ways of referring to sets of recipients.
    	They can be used interchangeably (the numbers in the names
    	have no special significance other than to distinguish them
    	from one another).
    	 
   Typically, the use of these lists would be as follow:
   - ETDirectorySearch is called one or more times, each time
	 resulting in populating of the NLSearchResults list.
   - Based on user preferences, names are copied from the
     NL_SearchResults to the NL_Recipients list.
   - The ETValidateRecipients or ETCreateHeader function is called
     to determine what subset of the NL_Recipients list have
     valid certificates and therefore can be encrypted for.
     Names without valid certificates will be moved from the
     NL_recipients list to the NL_Invalid list.
   - The validation failure reason for names in the NL_Invalid list
     can be determined by calling the ETGetValidateFailReason() function. 
     
    The name list entries contain the following information,
   which can be extracted via a set of utility functions:
   - a unique name which is used to distinguish this entry from others.
   - a list of "attributes". Each attribute defines an information type,
     such as common name, organizational unit, phone number, etc. The
     set of attributes is defined by the directory administrator.
   - per attribute, a list of values. For example, a user might have
     multiple "phone number" entries.
   Note that the unique name, attributes and values are all
   stored internally as character strings.
*/      

/*      Define the list types maintained. This type is used in the
	in the utility calls to indicate which list is being accessed.
*/
typedef enum 
{
	NL_SearchResults,
	NL_Recipients,
	NL_Invalid,
	NL_Group1,
	NL_Group2,
	NL_Group3
} ListID;

/*
   ETGetNumberOfNames returns the number of elements in the list, or -1
   if an error occured.
*/
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfNames(const ETContext ctx, ListID id);
/*
   ETGetUniqueName copies to uniqueName the unique name of the element 
   indicated by the ListID and entryIndex (the first element is index 0). 
   The copied string is at most MAX_NAME_SIZE in length.
*/
ETEXPORT32 EntLog ETEXPORT ETGetUniqueName( const ETContext ctx, 
										ListID id, 
										SYSINT entryIndex,
										char* uniqueName); 
/*
   ETGetUniqueNameReference copies to uniqueNameRef a pointer to the 
   unique name of the element indicated by the ListID and entryIndex 
   (the first element is index 0). 
   In cases where a unique name exceeds MAX_NAME_SIZE, this function
   can be used to access it. The name storage is owned by the Toolkit,
   and will be re-allocated on the next call to this function.
*/
ETEXPORT32 EntLog ETEXPORT ETGetUniqueNameReference( 
										const ETContext ctx, 
										ListID id, 
										SYSINT entryIndex,
										char** uniqueNameRef); 

/*
   ETAddName adds a name entry, with the supplied unique name,
   to the indicated list. Typically, this will only be used
   to add elements to NL_Recipients.
   The return integer is the index where the name was added, and -1 if
   an error occured.
*/
ETEXPORT32 INT16 ETEXPORT ETAddName(const ETContext ctx, 
								ListID id, 
								const char* uniqueName);
 
/*
   ETRemoveName removes the entry with the indicated unique name
   from the specified list.
*/
ETEXPORT32 EntLog ETEXPORT ETRemoveName(const ETContext ctx, 
									ListID id, 
									const char* uniqueName);

/*      
	ETGetNumberOfAttributes returns the number of attributes defined 
	for the specified list entry, or -1 on error.
*/
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfAttributes(	const ETContext ctx, 
												ListID id, 
												SYSINT entryIndex);
/*
	ETGetAttribute copies the indexed attribute name to attribute.
	The copied string is at most MAX_ENTSTR_SIZE in length.
*/
ETEXPORT32 EntLog ETEXPORT ETGetAttribute(  const ETContext ctx, 
										ListID id, 
										SYSINT entryIndex,
										SYSINT attributeIndex, 
										char* attribute);
/*
   ETGetNumberOfAttributeValues returns, via pointer numAttrValues, 
   the number of values associated with the indexed attribute.
*/
ETEXPORT32 EntLog ETEXPORT ETGetNumberOfAttributeValues(const ETContext ctx, 
													ListID id, 
													SYSINT entryIndex,  
													SYSINT attributeIndex, 
													INT16 *numAttrValues);
		
/* ETGetAttributeValue copies a string containing the indexed value to "value".
   The copied string is at most MAX_ENTSTR_SIZE in length.
*/
ETEXPORT32 EntLog ETEXPORT ETGetAttributeValue(	const ETContext ctx, 
											ListID id, 
											SYSINT entryIndex,
											SYSINT attributeIndex,
											SYSINT valueIndex, 
											char* value);   
/*
   ETGetEncryptionCertificate extracts the binary encryption public key
   certificate associated with the indexed entry, 
   if a certificate attribute exists for that entry.
   The certificate is stored in an internal EntCertificate data structure
   which can be accessed via the functions defined in CETCERT.H, and 
   a reference to it is provided by the certificate pointer.
   This function can be called after ETValidateRecipients() to examine
   the encryption certificates of the recipients.
*/
ETEXPORT32 EntLog ETEXPORT ETGetEncryptionCertificate(	const ETContext ctx,
                                                    ListID id,
                                                    SYSINT entryIndex,
                                                    ETBinData32* certificate);

/*
   ETSetAttributeValue adds an attribute-value pair to the indexed entry.
   If the specified attribute already exists, processing is as follows:
     If the replace BOOL is TRUE, any existing values are removed, 
     and the specified value is added.
     If replace is FALSE, the specified value is added to the list of
     existing values.
   If the specified attribute does not already exist, replace is
   ignored and a new attribute with the specified value is added.
   Return values attributeIndex and valueIndex indicate where within
   the entry the values were added.
*/
ETEXPORT32 EntLog ETEXPORT ETSetAttributeValue(	const ETContext ctx, 
											const ListID id, 
											const SYSINT entryIndex,
											const char* attribute, 
											const char* value,
											const BOOL replace,
											INT16* attributeIndex,
											INT16* valueIndex );
/*
   ETSetEncryptionCertificate sets the encryption public key certificate
   attribute for the specified entry to the value of the provided
   certificate structure. This function can be used 
   if the application wants to prevent the Toolkit from retrieving the
   associated recipient's encryption certificate via the 
   Entrust public key infrastructure. Certificates supplied in this
   manner are still validated before use.
   Set isASCIIencoded to TRUE if the certificate is PEM encoded in
   ASCII format.
   Note that the provided certificate is also loaded into the user
   context's internal EntCertificate structure and can be examined
   via the functions defined in CETCERT.H.
*/
ETEXPORT32 EntLog ETEXPORT ETSetEncryptionCertificate(
												const ETContext ctx,
												ListID id,
												SYSINT entryIndex,
												const ETBinData32* certificate,
												const BOOL isASCIIencoded);  

/*
   ETGetValidateFailReason returns an EntLog specifying why the indexed entry
   of the NL_Invalid list failed validation as an intended encryption recipient.
   This function would typically be called after 
   ETValidateRecipients or ETCreateHeader.
*/
ETEXPORT32 EntLog ETEXPORT ETGetValidateFailReason(const ETContext ctx, 
											   SYSINT entryIndex);
 
/* ETResetNameList deletes all entries from the specified name list.
*/
ETEXPORT32 void ETEXPORT ETResetNameList(const ETContext ctx, ListID id);
	
#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif  
