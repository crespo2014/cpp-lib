
#ifndef _SmPolicyApi45_h_
#define _SmPolicyApi45_h_


/*
Copyright (C) 1997-2004, Netegrity, Inc. All rights reserved.

Netegrity, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

SiteMinder Policy API
*/

#include "SmApi.h"

#define SM_POLICY_API_VERSION       0x0450
#define SM_POLICY_API_VERSION_5_0   0x0500
#define SM_POLICY_API_VERSION_6_0   0x0600
#define SM_POLICY_API_VERSION_6_0_1 0x0601
#define BFSIZE                      1024
#define TIMESIZE                    24
#define SM_POLICY_API_SAML_VER_1_0  0x0100
#define SM_POLICY_API_SAML_VER_1_1  0x0101


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  Policy API Return Codes                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/
enum Sm_PolicyApi_Status_t
{
     Sm_PolicyApi_Success                     =  0
    ,Sm_PolicyApi_Failure                     = -1
    ,Sm_PolicyApi_InvalidHandle               = -2
    ,Sm_PolicyApi_ErrorLogin                  = -3
    ,Sm_PolicyApi_NoPrivilege                 = -4
    ,Sm_PolicyApi_InvalidPasswordSyntax       = -5
    ,Sm_PolicyApi_InvalidPassword             = -6

    ,Sm_PolicyApi_DuplicateEntry              = -7
    ,Sm_PolicyApi_DoesNotExist                = -8
    ,Sm_PolicyApi_NotFound                    = -9
    ,Sm_PolicyApi_BadArgument                 = -10
    ,Sm_PolicyApi_WrongNumberOfElements       = -11
    ,Sm_PolicyApi_UserDirNotPartOfDomain      = -12
    ,Sm_PolicyApi_UserDirNotValid             = -13
    ,Sm_PolicyApi_ErrorUserDir                = -14

    ,Sm_PolicyApi_AgentNotFound               = -15
    ,Sm_PolicyApi_AgentTypeNotFound           = -16
    ,Sm_PolicyApi_AgentTypeAttrNotFound       = -17
    ,Sm_PolicyApi_AgentTypeMismatch           = -18
    ,Sm_PolicyApi_ODBCQuerySchemeNotFound     = -19
    ,Sm_PolicyApi_UserDirNotFound             = -20
    ,Sm_PolicyApi_DomainNotFound              = -21
    ,Sm_PolicyApi_AdminNotFound               = -22
    ,Sm_PolicyApi_SchemeNotFound              = -23
    ,Sm_PolicyApi_RegistrationSchemeNotFound  = -24
    ,Sm_PolicyApi_PasswordPolicyNotFound      = -25
    ,Sm_PolicyApi_SchemeIsRequired            = -26
    ,Sm_PolicyApi_PasswordPolicyConfig        = -27
    ,Sm_PolicyApi_RealmNotFound               = -28
    ,Sm_PolicyApi_NoChildren                  = -29
    ,Sm_PolicyApi_RuleNotFound                = -30
    ,Sm_PolicyApi_ResponseNotFound            = -31
    ,Sm_PolicyApi_ResponseAttrNotFound        = -32
    ,Sm_PolicyApi_PolicyNotFound              = -33
    ,Sm_PolicyApi_PolicyLinkNotFound          = -34
    ,Sm_PolicyApi_UserPolicyNotFound          = -35
    ,Sm_PolicyApi_BadGroup                    = -36
    ,Sm_PolicyApi_GroupNotFound               = -37
    ,Sm_PolicyApi_Invalid                     = -38
    ,Sm_PolicyApi_InvalidHandleVersion        = -39
    ,Sm_PolicyApi_GenerateSecretFailure       = -40
    ,Sm_PolicyApi_DomainNotAffiliate	      = -41

    ,Sm_PolicyApi_InvalidOid                  = -100
    ,Sm_PolicyApi_NotImplemented              = -101
    ,Sm_PolicyApi_NotSearchable               = -102
    ,Sm_PolicyApi_NotStorable                 = -103
    ,Sm_PolicyApi_NotCollection               = -104
    ,Sm_PolicyApi_NotUnique                   = -105
    ,Sm_PolicyApi_InvalidProp                 = -106
    ,Sm_PolicyApi_NotInitted                  = -107
    ,Sm_PolicyApi_NoSession                   = -108
    ,Sm_PolicyApi_OidInUseByRealm             = -109
    ,Sm_PolicyApi_OidInUseByRule              = -110
    ,Sm_PolicyApi_OidInUseByAdmin             = -111
    ,Sm_PolicyApi_MissingProperty             = -112
    ,Sm_PolicyApi_GroupMemberName             = -113
    ,Sm_PolicyApi_RadiusIpAddrNotUnique       = -114
    ,Sm_PolicyApi_GroupAgentType              = -115
    ,Sm_PolicyApi_RadiusRealmNotUnique        = -116
    ,Sm_PolicyApi_RealmFilterNotUnique        = -117
    ,Sm_PolicyApi_InvalidCharacters           = -118
    ,Sm_PolicyApi_AgentTypeCantBeDeleted      = -119
    ,Sm_PolicyApi_ProvNotImplemented          = -120
    ,Sm_PolicyApi_ProvNotUnique               = -121
    ,Sm_PolicyApi_RealmCantBeUsedInRule       = -122
    ,Sm_PolicyApi_OidInUseByCertMap           = -123
    ,Sm_PolicyApi_OidInUseBySelfReg           = -124
    ,Sm_PolicyApi_OidInUseByUserDirectory     = -125
    ,Sm_PolicyApi_SchemeCantBeDeleted         = -126
    ,Sm_PolicyApi_BasicSchemeUpdate           = -127
    ,Sm_PolicyApi_NonHtmlForm                 = -128
    ,Sm_PolicyApi_IllegalRealmOperation       = -129
	,Sm_PolicyApi_NameNotUnique               = -130

	/* This Error Code is obsolete and is present for backward compatibility only. */
	,Sm_PolicyApi_InvalidRuleResponseMapping  = -131

	,Sm_PolicyApi_FeatureNotSupported         = -132
};

/*
 These values are used to identify the structures that are allocated/freed
 by the API implementation
*/
enum Sm_PolicyApi_Structs_t
{
     Sm_PolicyApi_NULL_ID               = 0
    ,Sm_PolicyApi_Rule_ID               = 1
    ,Sm_PolicyApi_Policy_ID             = 2
    ,Sm_PolicyApi_Realm_ID              = 3
    ,Sm_PolicyApi_Response_ID           = 4
    ,Sm_PolicyApi_UserDir_ID            = 5
    ,Sm_PolicyApi_Agent_ID              = 6
    ,Sm_PolicyApi_Domain_ID             = 7
    ,Sm_PolicyApi_PolicyLink_ID         = 8
    ,Sm_PolicyApi_ResponseAttr_ID       = 9
    ,Sm_PolicyApi_User_ID               = 10
    ,Sm_PolicyApi_Scheme_ID             = 11
    ,Sm_PolicyApi_Admin_ID              = 12
    ,Sm_PolicyApi_Group_ID              = 13
    ,Sm_PolicyApi_ODBCQueryScheme_ID    = 14
    ,Sm_PolicyApi_Object_ID             = 15
    ,Sm_PolicyApi_AgentType_ID          = 16
    ,Sm_PolicyApi_AgentTypeAttr_ID      = 17
    ,Sm_PolicyApi_RegistrationScheme_ID = 18
    ,Sm_PolicyApi_PasswordPolicy_ID     = 19
    ,Sm_PolicyApi_IPAddress_ID          = 20
    ,Sm_PolicyApi_AuthAzMap_ID          = 21
    ,Sm_PolicyApi_CertMap_ID            = 22
    ,Sm_PolicyApi_PasswordMsgField_ID   = 23
     ,Sm_PolicyApi_VariableType_ID       = 25
     ,Sm_PolicyApi_Variable_ID           = 26


    ,Sm_PolicyApi_TrustedHost_ID = 27
    ,Sm_PolicyApi_HostConfig_ID = 28
    ,Sm_PolicyApi_AgentConfig_ID = 29
	,Sm_PolicyApi_Association_ID = 30
    ,Sm_PolicyApi_RegularExpression_ID  = 31
    ,Sm_PolicyApi_Server_ID  = 32



    ,Sm_PolicyApi_Affiliate_ID          = 36
    ,Sm_PolicyApi_AffiliateAttr_ID      = 37

    ,Sm_PolicyApi_SharedSecretPolicy_ID = 38
};

/*
// These values are used to identify the properties that can by get/set/removed
// by the API
*/
enum Sm_PolicyApi_Objects_t
{
     Sm_PolicyApi_NULL_Domain_Prop          = 0
    ,Sm_PolicyApi_Rule_Prop                 = 1     /* Domain */
    ,Sm_PolicyApi_RuleGroup_Prop            = 2     /* Domain */
    ,Sm_PolicyApi_Policy_Prop               = 3     /* Domain */
    ,Sm_PolicyApi_PolicyLink_Prop           = 4     /* Domain */
    ,Sm_PolicyApi_UserPolicy_Prop           = 5     /* Domain */
    ,Sm_PolicyApi_Realm_Prop                = 6     /* Domain */
    ,Sm_PolicyApi_ResponseGroup_Prop        = 7     /* Domain */
    ,Sm_PolicyApi_Response_Prop             = 8     /* Domain */
    ,Sm_PolicyApi_ResponseAttr_Prop         = 9     /* Domain */
    ,Sm_PolicyApi_UserDir_Prop              = 10    /* Global or Domain */
    ,Sm_PolicyApi_Scheme_Prop               = 11    /* Global */
    ,Sm_PolicyApi_Agent_Prop                = 12    /* Global */
    ,Sm_PolicyApi_AgentGroup_Prop           = 13    /* Global  */
    ,Sm_PolicyApi_AgentType_Prop            = 14    /* Global */
    ,Sm_PolicyApi_AgentTypeAttr_Prop        = 15    /* Global */
    ,Sm_PolicyApi_Domain_Prop               = 16    /* Global */
    ,Sm_PolicyApi_Admins_Prop               = 17    /* Global or Domain */
    ,Sm_PolicyApi_ODBCQueryScheme_Prop      = 18    /* Global */
    ,Sm_PolicyApi_RegistrationScheme_Prop   = 19    /* Global */
    ,Sm_PolicyApi_PasswordPolicy_Prop       = 20    /* Global */
    ,Sm_PolicyApi_AuthAzMap_Prop            = 21    /* Global */
    ,Sm_PolicyApi_CertMap_Prop              = 22    /* Global */
    ,Sm_PolicyApi_ActiveExpr_Prop           = 23    /* Domain */
    ,Sm_PolicyApi_VariableType_Prop         = 24    /* Global */
    ,Sm_PolicyApi_Variable_Prop             = 25    /* Domain */
    ,Sm_PolicyApi_TrustedHost_Prop          = 26    /* Global */
    ,Sm_PolicyApi_HostConfig_Prop           = 27    /* Global */
    ,Sm_PolicyApi_AgentConfig_Prop			= 28	/* Global */
	,Sm_PolicyApi_Association_Prop			= 29	/* Global */

    ,Sm_PolicyApi_RegularExpr_Prop          = 28    /* Password Policy */


    ,Sm_PolicyApi_AffiliateDomain_Prop      = 32    /* Global */
    ,Sm_PolicyApi_Affiliate_Prop            = 33    /* Domain */

    ,Sm_PolicyApi_SharedSecretPolicy_Prop = 34	/* Global */
};

enum Sm_PolicyApi_Groups_t
{
     Sm_PolicyApi_NULL_Group_Prop       = 0
    ,Sm_PolicyApi_Rule_Group_Prop       = 1
    ,Sm_PolicyApi_Response_Group_Prop   = 2
    ,Sm_PolicyApi_Agent_Group_Prop      = 3
};

enum Sm_PolicyApi_ManagementCommands_t
{
     Sm_PolicyApi_ManagementCommand_FlushAll            = 1     /* no data field required */
    ,Sm_PolicyApi_ManagementCommand_FlushUsers          = 2     /* no data field required */
    ,Sm_PolicyApi_ManagementCommand_FlushRealms         = 3     /* no data field required */
    ,Sm_PolicyApi_ManagementCommand_ChangeDynamicKeys   = 4     /* no data field required */
    ,Sm_PolicyApi_ManagementCommand_ChangePersistentKey = 5     /* data field may contain optional key value */
    ,Sm_PolicyApi_ManagementCommand_ChangeSessionKey    = 6     /* data field may contain optional key value */
    ,Sm_PolicyApi_ManagementCommand_RolloverSharedSecrets = 7
};


/*
// admin rights
*/
enum Sm_PolicyApi_AdminRights_t
{
     Sm_PolicyApi_AdminRights_ManageAllDomains      = 0x01
    ,Sm_PolicyApi_AdminRights_ManageObjects         = 0x02
    ,Sm_PolicyApi_AdminRights_ManageUsers           = 0x04
    ,Sm_PolicyApi_AdminRights_ManageKeys            = 0x08
    ,Sm_PolicyApi_AdminRights_ManagePasswordPolicy  = 0x08
    ,Sm_PolicyApi_AdminRights_ManageReports         = 0x10  // obsolete
	,Sm_PolicyApi_AdminRights_RegisterTrustedHosts  = 0x20
};

/*
// IP address type
*/
enum Sm_PolicyApi_IPAddressType_t
{
     Sm_PolicyApi_IPAddressType_SingleHost            = 1
    ,Sm_PolicyApi_IPAddressType_HostName              = 2
    ,Sm_PolicyApi_IPAddressType_AddressAndSubNetMask  = 3
    ,Sm_PolicyApi_IPAddressType_Range                 = 4
};


/*
// Authentication and Authorization type
*/
enum Sm_PolicyApi_AuthAzMapType_t{
     Sm_PolicyApi_AuthAzMapType_DN          = 1
    ,Sm_PolicyApi_AuthAzMapType_UniversalId = 2
    ,Sm_PolicyApi_AuthAzMapType_Attr        = 3
};


/*
// Directory type in Certificate Mapping
*/
enum Sm_PolicyApi_DirType_t
{
     Sm_PolicyApi_DirType_LDAP  = 1
    ,Sm_PolicyApi_DirType_WinNT = 2
    ,Sm_PolicyApi_DirType_ODBC  = 3
};

/*
// Certificate Mapping Attribute type
*/
enum Sm_PolicyApi_CertMapAttrType_t
{
     Sm_PolicyApi_CertMapAttrType_Single  = 1
    ,Sm_PolicyApi_CertMapAttrType_Custom  = 2
    ,Sm_PolicyApi_CertMapAttrType_Exact   = 3
};

/*
// These defines are used in the nFlags of Sm_PolicyApi_CertMap_t
*/
enum Sm_PolicyApi_CertMapFlags_t
{
     Sm_PolicyApi_CertMapFlags_CertRequired          = 0x01
    ,Sm_PolicyApi_CertMapFlags_UseDistributionPoints = 0x02
    ,Sm_PolicyApi_CertMapFlags_VerifySignature       = 0x04
    ,Sm_PolicyApi_CertMapFlags_CRLCheck              = 0x08
    ,Sm_PolicyApi_CertMapFlags_Cache                 = 0x10
};

enum Sm_PolicyApi_DomainFlags_t
{
    Sm_PolicyApi_DomainFlags_GlobalPoliciesApply     = 0x02
};

/*
// Policy Api initialization flags.
// These flags are used in the Sm_PolicyApi_Init call
*/
enum Sm_PolicyApi_InitFlags_t
{
     Sm_PolicyApi_InitFlags_Enablecache               = 0x01
    ,Sm_PolicyApi_InitFlags_PreLoadCache              = 0x02
    ,Sm_PolicyApi_InitFlags_LoadAgentTypeDictionary   = 0x04
    ,Sm_PolicyApi_InitFlags_DisableValidation         = 0x08
    ,Sm_PolicyApi_InitFlags_DisableAudit              = 0x10
    ,Sm_PolicyApi_InitFlags_DisableCacheUpdates       = 0x20
    ,Sm_PolicyApi_InitFlags_DisableManagementWatchDog = 0x40
};



enum Sm_PolicyApi_PasswordMsgId_t
{
     Sm_PolicyApi_PasswordMsgId_None                        = 0
    ,Sm_PolicyApi_PasswordMsgId_ChangePassword              = 1
    ,Sm_PolicyApi_PasswordMsgId_PassswordGeneralFailure     = 1000
    ,Sm_PolicyApi_PasswordMsgId_PasswordShort               = 1001
    ,Sm_PolicyApi_PasswordMsgId_PasswordLong                = 1002
    ,Sm_PolicyApi_PasswordMsgId_PasswordOldPasswordBad      = 1003
    ,Sm_PolicyApi_PasswordMsgId_PasswordReuse               = 1004
    ,Sm_PolicyApi_PasswordMsgId_PasswordSimilar             = 1005
    ,Sm_PolicyApi_PasswordMsgId_PasswordRepeatingChars      = 1006
    ,Sm_PolicyApi_PasswordMsgId_PasswordDictionaryMatch     = 1007
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentLetters      = 1008
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentDigits       = 1009
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentAlphaNum     = 1010
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentPunctuation  = 1011
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNonPrintable = 1012
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNonAlphaNum  = 1013
    ,Sm_PolicyApi_PasswordMsgId_PasswordProfileMatch        = 1014
    ,Sm_PolicyApi_PasswordMsgId_PasswordGraceDays           = 1015
    ,Sm_PolicyApi_PasswordMsgId_PasswordSystemPIN           = 1016
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserMaxNumPIN       = 1017
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserMinMaxNumPIN    = 1018
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserMaxAlphaPIN	    = 1019
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserMinMaxAlphaPIN  = 1020
    ,Sm_PolicyApi_PasswordMsgId_PasswordAcceptPIN           = 1021
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentLowerAlpha   = 1022
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentUpperAlpha   = 1023
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoLowerAlpha = 1024
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoUpperAlpha = 1025
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoDigits     = 1026
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoPunctuation  = 1027
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoNonPrintable = 1028
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoNonAlphaNum  = 1029
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoAlphaNum   = 1030
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentMatchRegExp  = 1031
    ,Sm_PolicyApi_PasswordMsgId_PasswordContentNoMatchRegExp  = 1032
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserMinNumPIN       = 1033
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserDigitsPIN       = 1034
    ,Sm_PolicyApi_PasswordMsgId_PasswordUserAlphaNumPIN     = 1035
};

enum Sm_PolicyApi_PasswordMsgFieldId_t
{
     Sm_PolicyApi_PasswordMsgFieldId_None   = 0
    ,Sm_PolicyApi_PasswordMsgFieldId_Min    = 1
    ,Sm_PolicyApi_PasswordMsgFieldId_Max    = 2
    ,Sm_PolicyApi_PasswordMsgFieldId_OldPW  = 3
    ,Sm_PolicyApi_PasswordMsgFieldId_NewPW  = 4
    ,Sm_PolicyApi_PasswordMsgFieldId_Days   = 5
    ,Sm_PolicyApi_PasswordMsgFieldId_Token  = 6
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordProfileMatch =7
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordDictionaryMatch=8
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordGeneralFailure =9
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordSimilar=10
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordReuse  =11
    ,Sm_PolicyApi_PasswordMsgFieldId_PasswordOldPasswordBad=12
    ,Sm_PolicyApi_PasswordMsgFieldId_ChangePassword  =13
};

enum Sm_PolicyApi_FieldType_t
{
     Sm_PolicyApi_FieldType_None = 0
    ,Sm_PolicyApi_FieldType_Int = 1
    ,Sm_PolicyApi_FieldType_String = 2
};

// Return types for Variables
enum Sm_PolicyApi_VarReturnTypes_t
{
     Sm_PolicyApi_VarReturnTypes_Boolean   = 1
    ,Sm_PolicyApi_VarReturnTypes_Number    = 2
    ,Sm_PolicyApi_VarReturnTypes_String    = 3
    ,Sm_PolicyApi_VarReturnTypes_Date      = 4
};

// Affiliate attribute types
enum Sm_PolicyApi_AffiliateAttrType_t
{
     Sm_PolicyApi_Affiliate_HTTP_Header_Variable    = 1
    ,Sm_PolicyApi_Affiliate_HTTP_Cookie_Variable    = 2
};


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  Policy API Structures                          ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Object Structure
*/
typedef struct Sm_PolicyApi_Oid_s
{
    int             iStructId;
    int             iObjectId;
    char            pszOid[BFSIZE];
    struct Sm_PolicyApi_Oid_s *next;
} Sm_PolicyApi_Oid_t;


/*
// Variable Type Structure
*/

typedef struct Sm_PolicyApi_VariableType_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszFilter[BFSIZE];
    struct Sm_PolicyApi_VariableType_s*    next;
} Sm_PolicyApi_VariableType_t;

/*
// Variable Structure
*/

typedef struct Sm_PolicyApi_Variable_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszVariableTypeOid[BFSIZE];
    char            pszDefinition[BFSIZE];
    char            pszMetaData[BFSIZE];
    int             nReturnType;
    bool            bPreFetchFlag;
    char            pszDomainOid[BFSIZE];
    Sm_PolicyApi_Oid_t* pNestedVariableList;  // linked list of nested variable OIDs
    struct Sm_PolicyApi_Variable_s*   next;
} Sm_PolicyApi_Variable_t;


/*
// Agent Structure
*/
typedef struct Sm_PolicyApi_Agent_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszIpAddr[BFSIZE];
    char            pszSecret[BFSIZE];
    char            pszAgentTypeOid[BFSIZE];
    int             nRealmHintAttrId;
    struct Sm_PolicyApi_Agent_s*    next;
} Sm_PolicyApi_Agent_t;


/*
// AgentType Structure
*/
typedef struct Sm_PolicyApi_AgentType_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    int             nRfcId;
    int             nAgentType;
    int             nResourceType;
    int             nAgentTypeSpecific;
    struct Sm_PolicyApi_AgentType_s*    next;
} Sm_PolicyApi_AgentType_t;


/*
// AgentType Attribute Structure
*/
typedef struct Sm_PolicyApi_AgentTypeAttr_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszAgentTypeOid[BFSIZE];
    struct Sm_PolicyApi_AgentTypeAttr_s*    next;
} Sm_PolicyApi_AgentTypeAttr_t;


/*
// ODBC Query Scheme Structure
*/
typedef struct Sm_PolicyApi_ODBCQueryScheme_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszQueryEnumerate[BFSIZE];
    char            pszQueryGetObjInfo[BFSIZE];
    char            pszQueryLookup[BFSIZE];
    char            pszQueryInitUser[BFSIZE];
    char            pszQueryAuthenticateUser[BFSIZE];
    char            pszQueryGetUserProp[BFSIZE];
    char            pszQuerySetUserProp[BFSIZE];
    char            pszQueryGetUserProps[BFSIZE];
    char            pszQueryLookupUser[BFSIZE];
    char            pszQueryGetGroups[BFSIZE];
    char            pszQueryIsGroupMember[BFSIZE];
    char            pszQueryGetGroupProp[BFSIZE];
    char            pszQuerySetGroupProp[BFSIZE];
    char            pszQueryGetGroupProps[BFSIZE];
    char            pszQueryLookupGroup [BFSIZE];
    char            pszQuerySetPassword [BFSIZE];
    struct          Sm_PolicyApi_ODBCQueryScheme_s* next;
} Sm_PolicyApi_ODBCQueryScheme_t;


/*
// UserDirectory Structure
*/
typedef struct Sm_PolicyApi_UserDir_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszNamespace[BFSIZE];
    char            pszServer[BFSIZE];
    char            pszSearchRoot[BFSIZE];
    char            pszUserLookupStart[BFSIZE];
    char            pszUserLookupEnd[BFSIZE];
    char            pszUsername[BFSIZE];
    char            pszPassword[BFSIZE];
    int             nSearchResults;
    int             nSearchScope;
    int             nSearchTimeout;
    bool            bSecureConnection;
    bool            bRequireCredentials;
    char            pszDisabledAttr[BFSIZE];
    char            pszUniversalIDAttr[BFSIZE];
    char            pszODBCQuerySchemeOid[BFSIZE];
    char            pszAnonymousId[BFSIZE];
    char            pszPasswordData[BFSIZE];
    char            pszPasswordAttribute[BFSIZE];
    char            pszEmailAddressAttr[BFSIZE];
    char            pszChallengeRespAttr[BFSIZE];
    struct Sm_PolicyApi_UserDir_s*  next;
} Sm_PolicyApi_UserDir_t;


/*
// Authentication and Authorization directory
// mapping Structure
*/
typedef struct Sm_PolicyApi_AuthAzMap_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszAuthDirOid[BFSIZE];
    char            pszAuthDirName[BFSIZE];
    char            pszAzDirOid[BFSIZE];
    char            pszAzDirName[BFSIZE];
    Sm_PolicyApi_AuthAzMapType_t nMapType;
    struct Sm_PolicyApi_AuthAzMap_s *next;
} Sm_PolicyApi_AuthAzMap_t;


/*
// Domain Structure
*/
typedef struct Sm_PolicyApi_Domain_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    struct Sm_PolicyApi_Domain_s*   next;
    Sm_PolicyApi_DomainFlags_t      iFlags;
} Sm_PolicyApi_Domain_t, Sm_PolicyApi_AffiliateDomain_t;



/*
// Admins Structure
*/
typedef struct Sm_PolicyApi_Admin_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszPassword[BFSIZE];
    char            pszUserDirOid[BFSIZE];
    char            pszSchemeOid[BFSIZE];
    Sm_PolicyApi_AdminRights_t      nRights;
    struct Sm_PolicyApi_Admin_s*    next;
} Sm_PolicyApi_Admin_t;


/*
// Scheme Structure
*/
typedef struct Sm_PolicyApi_Scheme_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    int             nLevel;
    char            pszLib[BFSIZE];
    char            pszParam[BFSIZE];
    char            pszSecret[BFSIZE];
    bool            bIsTemplate;
    bool            bIsUsedbyAdmin;
    Sm_Api_SchemeType_t nType;
    bool            bAllowSaveCreds;
    bool            bIsRadius;
    bool            bIgnorePwCheck;
    struct Sm_PolicyApi_Scheme_s*   next;
} Sm_PolicyApi_Scheme_t;


/*
// Registration Scheme Structure
*/
typedef struct Sm_PolicyApi_RegistrationScheme_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszUserDirOid[BFSIZE];
    char            pszWelcomePageURL[BFSIZE];
    char            pszTemplatePath[BFSIZE];
    bool            bEnableLogging;
    struct Sm_PolicyApi_RegistrationScheme_s*  next;
} Sm_PolicyApi_RegistrationScheme_t;

/*
// Password Policy Structure
// nPasswordBehavior is policy behavior flags defined in SmApi.h
*/
typedef struct Sm_PolicyApi_PasswordPolicy_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    bool            bEntireDir;
    bool            bIsEnabled;
    char            pszUserDirectoryOid[BFSIZE];
    char            pszPath[BFSIZE];
    char            pszClass[BFSIZE];
    int             nResolution;
    int             nLoginMaxFailures;
    int             nLoginMaxInactivity;
    int             nLoginInactivityWarn;
    int             nLoginDaysGrace;
    char            pszDictionaryName[BFSIZE];
    int             nDictionaryPartial;
    int             nExpirationDelay;
    int             nReenablement;
    int             nPasswordBehavior;
    char            pszPasswordServicesRedirect[BFSIZE];
    int             nPWMaxLength;
    int             nPWMinLength;
    int             nPWMaxRepeatingChar;
    int             nPWMinAlphaNum;
    int             nPWMinAlpha;
    int             nPWMinNonAlpha;
    int             nPWMinNonPrintable;
    int             nPWMinNumbers;
    int             nPWMinPunctuation;
    int             nPWReuseCount;
    int             nPWReuseDelay;
    int             nPWPercentDifferent;
    int             nPWPercentSequence;
    int             nPWSpecialsLength;
    struct Sm_PolicyApi_PasswordPolicy_s*  next;
    // new fields
    int             nPriority;
    int             nPWMinLowerAlpha;
    int             nPWMinUpperAlpha;
    int             nReserved1;
    int             nReserved2;
    int             nReserved3;
    char            pszReserved4[BFSIZE];
} Sm_PolicyApi_PasswordPolicy_t;

/*
// Regular Expression Structure
*/

typedef struct Sm_PolicyApi_RegularExpression_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            ExpressionDef[BFSIZE];
    int             matchExpression;
    struct Sm_PolicyApi_RegularExpression_s *next;
} Sm_PolicyApi_RegularExpression_t;

/*
// Certificate mapping structure
*/
typedef struct Sm_PolicyApi_CertMap_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszUserDirOid[BFSIZE];
    char            pszIssuerDN[BFSIZE];
    char            pszCaDN[BFSIZE];
    char            pszMapAttr[BFSIZE];
    Sm_PolicyApi_CertMapFlags_t    nFlags;
    Sm_PolicyApi_CertMapAttrType_t nAttrType;
    Sm_PolicyApi_DirType_t         nDirType;
    struct Sm_PolicyApi_CertMap_s *next;
} Sm_PolicyApi_CertMap_t;



/*
// Realm Structure
*/
typedef struct Sm_PolicyApi_Realm_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszResourceFilter[BFSIZE];
    char            pszAgentOid[BFSIZE];
    char            pszSchemeOid[BFSIZE];
    char            pszParentRealmOid[BFSIZE];
    char            pszDomainOid[BFSIZE];
    char            pszAzUserDirOid[BFSIZE];
    char            pszRegSchemeOid[BFSIZE];
    bool            bProcessAuthEvents;
    bool            bProcessAzEvents;
    bool            bProtectAll;
    int             nMaxTimeout;
    int             nIdleTimeout;
    bool            bSyncAudit;
    struct Sm_PolicyApi_Realm_s*    next;

} Sm_PolicyApi_Realm_t;


/*
// Rule Structure
*/
typedef struct Sm_PolicyApi_Rule_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszRealmOid[BFSIZE];
    char            pszAction[BFSIZE];
    char            pszResource[2*BFSIZE];
    bool            bAllowAccess;
    bool            bRegularExpression;
    char            pszActiveExpr[BFSIZE];
    bool            bIsEnabled;
    long            nStartTime;
    long            nEndTime;
    unsigned char   pszTimeGrid[TIMESIZE];
    struct Sm_PolicyApi_Rule_s* next;
    char            pszAgentOid[BFSIZE];
} Sm_PolicyApi_Rule_t;


/*
// Response Structure
*/
typedef struct Sm_PolicyApi_Response_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszAgentTypeOid[BFSIZE];
    char            pszDomainOid[BFSIZE];
    struct Sm_PolicyApi_Response_s* next;
} Sm_PolicyApi_Response_t;


/*
// Response Attributes Structure
*/
typedef struct Sm_PolicyApi_ResponseAttr_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszAgentTypeAttrOid [BFSIZE];
    char            pszValue[BFSIZE];
    int             iTTL;
    int             iFlags;
    struct Sm_PolicyApi_ResponseAttr_s* next;
    char            pszActiveExpr[BFSIZE];
    Sm_PolicyApi_Oid_t*   pVariableList; // Linked List of Variable oids used by the active expression
} Sm_PolicyApi_ResponseAttr_t;



typedef struct Sm_PolicyApi_IPAddress_s
{
    int                          iStructId;
    Sm_PolicyApi_IPAddressType_t iIPAddressType;
    unsigned long                nIPAddress;
    unsigned long                nEndIPAddress;
    unsigned long                nSubnetMask;
    char                         pszHostName[BFSIZE];
    struct  Sm_PolicyApi_IPAddress_s  *next;
} Sm_PolicyApi_IPAddress_t;


/*
// Policy Structure
*/
typedef struct Sm_PolicyApi_Policy_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszActiveExpr[BFSIZE];
    bool            bIsEnabled;
    char            pszDomainOid[BFSIZE];
    long            nStartTime;
    long            nEndTime;
    unsigned char   pszTimeGrid[TIMESIZE];
    Sm_PolicyApi_IPAddress_t  *pIPAddress;
    struct Sm_PolicyApi_Policy_s*   next;
    char            pszVariableExpr[BFSIZE];
    Sm_PolicyApi_Oid_t*   pVariableList; // Linked List of Variable OIDs used by this expression
} Sm_PolicyApi_Policy_t;



/*
// PolicyLink Structure
*/
typedef struct Sm_PolicyApi_PolicyLink_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszRuleOid[BFSIZE];
    char            pszResponseOid[BFSIZE];
    struct Sm_PolicyApi_PolicyLink_s*   next;
} Sm_PolicyApi_PolicyLink_t;

/*
// Users Structure
*/
typedef struct Sm_PolicyApi_User_s
{
    int             iStructId;
    char            pszUserPolicyOid[BFSIZE];
    char            pszUserDirOid[BFSIZE];
    char            pszPath[BFSIZE];
    char            pszClass[BFSIZE];
    Sm_PolicyResolution_t nPolicyResolution;
    int             nFlags;
    struct Sm_PolicyApi_User_s* next;
} Sm_PolicyApi_User_t;

/*
// PasswordState Structure
*/
typedef struct Sm_PolicyApi_UserPasswordState_s
{
    int             iLoginFailures;
    time_t          tLastLogin;
    time_t          tPrevLogin;
    time_t          tDisabled;
    time_t          tLastPWChange;
} Sm_PolicyApi_UserPasswordState_t;

/*
// Groups Structure
*/
typedef struct Sm_PolicyApi_Group_s
{
    int             iStructId;
    char            pszOid[BFSIZE];
    char            pszName[BFSIZE];
    char            pszDesc[BFSIZE];
    char            pszAgentTypeOid[BFSIZE];
    struct Sm_PolicyApi_Group_s*    next;
} Sm_PolicyApi_Group_t;

/*
// Management Command Structure
*/
typedef struct Sm_PolicyApi_ManagementCommand_s
{
    Sm_PolicyApi_ManagementCommands_t  iCommand;
    char                               pszData[BFSIZE];
} Sm_PolicyApi_ManagementCommand_t;



typedef struct Sm_PolicyApi_PasswordMsgField_s
{
    int             iStructId;
    Sm_PolicyApi_PasswordMsgFieldId_t nId;
    Sm_PolicyApi_FieldType_t nType;
    char pszMsg[BFSIZE];
    int nValue;
    struct Sm_PolicyApi_PasswordMsgField_s* next;
} Sm_PolicyApi_PasswordMsgField_t;


typedef struct Sm_PolicyApi_TrustedHost_s
{
    int     iStructId;
    char    pszOid[BFSIZE];
    char    pszName[BFSIZE];
    char    pszDesc[BFSIZE];
    char    pszIPAddr[BFSIZE];
    char    pszSecret[BFSIZE];
    bool    bIs4xHost;
    struct  Sm_PolicyApi_TrustedHost_s* next;
    bool    bRolloverEnabled;
} Sm_PolicyApi_TrustedHost_t;


typedef struct Sm_PolicyApi_Server_s
{
    int     iStructId;
	char	pszIpAddr[BFSIZE];
	int		iPort[3];
	int		iClusterSeq;
    struct Sm_PolicyApi_Server_s* next;
} Sm_PolicyApi_Server_t;


typedef struct Sm_PolicyApi_HostConfig_s
{
    int     iStructId;
    char    pszOid[BFSIZE];
    char    pszName[BFSIZE];
    char    pszDesc[BFSIZE];
    char    pszIPAddress[BFSIZE];
    bool    bEnableFailOver;
    int     iMaxSocketsPerPort;
    int     iMinSocketsPerPort;
    int     iNewSocketStep;
    int     iRequestTimeout;
    struct  Sm_PolicyApi_HostConfig_s* next;
    Sm_PolicyApi_Server_t* pServer;
    Sm_PolicyApi_Server_t* pCluster;
	int		iFailoverThreshold;
} Sm_PolicyApi_HostConfig_t;


typedef struct Sm_PolicyApi_AgentConfig_s
{
	int		iStructId;
	char	pszOid[BFSIZE];
	char	pszName[BFSIZE];
	char	pszDesc[BFSIZE];
	struct  Sm_PolicyApi_AgentConfig_s* next;
} Sm_PolicyApi_AgentConfig_t;

typedef struct Sm_PolicyApi_Association_s
{
	int		iStructId;
    char	pszOid[BFSIZE];
    char	pszName[BFSIZE];
    char*	pszValue;
	int		iFlags;
	struct  Sm_PolicyApi_Association_s* next;
} Sm_PolicyApi_Association_t;




/*
// Affiliate object structure
*/
typedef struct Sm_PolicyApi_Affiliate_s
{
    int         iStructId;
    char        pszOid[BFSIZE];
    char        pszName[BFSIZE];
    char        pszDesc[BFSIZE];
    char        pszAffiliateDomainOid[BFSIZE];
    char        pszPassword[BFSIZE];
    bool        bIsEnabled;
    bool        bAllowNotification;
    char        pszAuthURL[BFSIZE];
    char        pszAudience[BFSIZE];
    long        nValidityDuration;
    bool        bSharedSession;
    long        nSyncInterval;
    long        nSkewTime;
    long        nStartTime;
    long        nEndTime;
    unsigned char   pszTimeGrid[TIMESIZE];
    Sm_PolicyApi_IPAddress_t  *pIPAddress;
    struct Sm_PolicyApi_Affiliate_s*	next;
    long        nSAMLVersion;
} Sm_PolicyApi_Affiliate_t;


/*
// Affiliate Attribute object structure
*/
typedef struct Sm_PolicyApi_AffiliateAttr_s
{
    int	        iStructId;
    Sm_PolicyApi_AffiliateAttrType_t        nAttrType;
    char        pszValue[BFSIZE];
    struct Sm_PolicyApi_AffiliateAttr_s*    next;
} Sm_PolicyApi_AffiliateAttr_t;



/*
// SharedSecretPolicy object structure
*/

enum Sm_PolicyApi_SecretRolloverPeriod_t
{
	 RolloverNEVER = 0
	,RolloverHOURS = 1
	,RolloverDAYS = 2
	,RolloverWEEKS = 3
	,RolloverMONTHS = 4
};

typedef struct Sm_PolicyApi_SharedSecretPolicy_s
{
    int     iStructId;
    bool    bIsEnabled;
    int     iRolloverPeriod;
    int     iRolloverFrequency;
} Sm_PolicyApi_SharedSecretPolicy_t;

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  Policy API Functions                           ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

#if defined(__unix)
extern "C" {
#endif

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////        Policy API Initialization and Release Functions.         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// This function has to be the first function called by the API client
// session. This needs to be called once per client session.
*/
int SM_EXTERN Sm_PolicyApi_Init (void** ppInitHandle, const Sm_PolicyApi_InitFlags_t nInitFlag);
int SM_EXTERN Sm_PolicyApi_InitEx (void** ppInitHandle, const Sm_PolicyApi_InitFlags_t nInitFlag, const unsigned version);

/*
// This function has to be the last function that is called by the API
// client session. This needs to be called once per client session.
// Failure to call this function will result in a memory leak.
*/
int SM_EXTERN Sm_PolicyApi_Release(void* pInitHandle);


/*
//////////////////////////////////////////////////////////////////////////
////                                                                  ////
////           Policy API Login and Logout Functions.                 ////
//// These functions can be called multiple times in a client session ////
////                                                                  ////
//////////////////////////////////////////////////////////////////////////
*/

/*
// Login:
// The user has to login before making other Policy API calls.
*/
int SM_EXTERN Sm_PolicyApi_Login (
        void        *pInitHandle,
        void        **ppSessionHandle,
        const int   nCheckCreds,
        const char  *pszUserName,
        const char  *pszPassword,
        const char  *pszClientIP,
        char        **pszUserMsg,
        char        **pszErrMsg);

/*
// Logout:
// This function logs out a user session from the Policy API
// Failure to call this function will result in a memory leak
*/
int SM_EXTERN Sm_PolicyApi_Logout (void* pSessionHandle);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////        Policy API Memory Management Functions.                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// This function should be called to free up the memory that was
// allocated by the API for various structures.
// NOTE: This function is required for version SM_POLICY_API_VERSION_6_0
// and later clients
*/
int SM_EXTERN Sm_PolicyApi_FreeMemoryEx(
    void*       pInitHandle,
    void*       pMem);

/*
// This function should be called to free up the memory that was
// allocated by the API for various structures.  This call is deprecated
// for SM_POLICY_API_VERSION_6_0 and later clients
*/
int SM_EXTERN Sm_PolicyApi_FreeMemory(void* pMem);

/*
// Frees up the memory used for string arrays that are allocated by
// the API.
*/
int SM_EXTERN Sm_PolicyApi_FreeStringArray(
        char* pszStringArray[]);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                            Agent                                ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create an Agent
*/
int SM_EXTERN Sm_PolicyApi_AddAgent (
        void* pSessionHandle,
        Sm_PolicyApi_Agent_t* pstructAgent,
        const bool bUpdate);

/*
// Deletes an Agent
*/
int SM_EXTERN Sm_PolicyApi_DeleteAgent (
        void* pSessionHandle,
        const char* pszAgentOid);

/*
// Get the contents of an Agent object
*/
int SM_EXTERN Sm_PolicyApi_GetAgent (
        void* pSessionHandle,
        const char* pszAgentOid,
        Sm_PolicyApi_Agent_t** ppstructAgent);

/*
// Get the contents of an AgentType object
*/
int SM_EXTERN Sm_PolicyApi_GetAgentType (
        void* pSessionHandle,
        const char* pszAgentTypeOid,
        Sm_PolicyApi_AgentType_t** ppstructAgentType);


/*
// Get the attributes of an AgentType object
*/
int SM_EXTERN Sm_PolicyApi_GetAgentTypeAttr (
        void* pSessionHandle,
        const char* pszOid,
        Sm_PolicyApi_AgentTypeAttr_t** ppstructAgentTypeAttr);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                   ODBC Query Scheme                             ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create ODBC Query object
*/
int SM_EXTERN Sm_PolicyApi_CreateODBCQueryScheme (
        void* pSessionHandle,
        Sm_PolicyApi_ODBCQueryScheme_t* pstructODBCQueryScheme,
        const bool bUpdate);

/*
// Delete ODBC Query object
*/
int SM_EXTERN Sm_PolicyApi_DeleteODBCQueryScheme (
        void* pSessionHandle,
        const char* pszODBCQuerySchemeOid);

/* Get ODBC Query object contents*/
int SM_EXTERN Sm_PolicyApi_GetODBCQueryScheme (
        void* pSessionHandle,
        const char* pszODBCQuerySchemeOid,
        Sm_PolicyApi_ODBCQueryScheme_t** pstructODBCQueryScheme);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                   User Directory                                ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create a User Directory object
*/
int SM_EXTERN Sm_PolicyApi_CreateUserDir (
        void* pSessionHandle,
        Sm_PolicyApi_UserDir_t* pstructUserDir,
        const bool bUpdate);

/*
// Delete a User Directory
// Note: Removes Directory Users from Policies
*/
int SM_EXTERN Sm_PolicyApi_DeleteUserDir (
        void* pSessionHandle,
        const char* pszUserDirOid);

/*
// Get a User Dir object's contents
*/
int SM_EXTERN Sm_PolicyApi_GetUserDir (
        void* pSessionHandle,
        const char* pszUserDirOid,
        Sm_PolicyApi_UserDir_t** ppstructUserDir);

/*
// Associate an existing User Dir with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddUserDirToDomain(
        void* pSessionHandle,
        const char* pszUserDirOid,
        const char* pszDomainOid);

/*
// Disassociate an existing User Dir with a Domain
*/
int SM_EXTERN Sm_PolicyApi_RemoveUserDirFromDomain(
        void* pSessionHandle,
        const char* pszUserDirOid,
        const char* pszDomainOid);

/*
// Retrieve the search order of User Dirs for a Domain
*/
int SM_EXTERN Sm_PolicyApi_GetUserDirSearchOrder(
        void* pSessionHandle,
        const char* pszDomainOid,
        char** pszArray[]);

/*
// Set the search order of User Dirs for a Domain
*/
int SM_EXTERN Sm_PolicyApi_SetUserDirSearchOrder(
        void* pSessionHandle,
        const char* pszDomainOid,
        char* pszArray[]);

/*
// Get directory capabilities
// The directory capabilities are enumerated in Sm_DirectoryCapability_t.
// Sm_DirectoryCapability_t is defined in SmApi.h
*/
int SM_EXTERN Sm_PolicyApi_GetUserDirCapabilities (
        void* pSessionHandle,
        const char* pszUserDirOid,
        unsigned long* pCapabilities);

/*
// Returns a list of all User specification
*/
int SM_EXTERN Sm_PolicyApi_GetDirectoryContents (
        void* pSessionHandle,
        const char* pszUserDirOid,
        Sm_PolicyApi_User_t** ppStructUserSpec);


/*
// Lookup user specification in a directory
*/
int SM_EXTERN Sm_PolicyApi_LookupDirectoryEntry (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszSearchPattern,
        Sm_PolicyApi_User_t **ppStructUserSpec);

/*
// Validate user specification in a directory
*/
int SM_EXTERN Sm_PolicyApi_ValidateDirectoryEntry (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszPath,
        Sm_PolicyApi_User_t **ppUserEntry);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////            Authentication and Authorization Mapping             ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/
/*
// Create an authentication and authorization map
*/
int SM_EXTERN Sm_PolicyApi_CreateAuthAzMap (
        void *pSessionHandle,
        Sm_PolicyApi_AuthAzMap_t *pAuthAzMap,
        const bool bUpdate);

/*
// Delete an authentication and authorization map object
*/
int SM_EXTERN Sm_PolicyApi_DeleteAuthAzMap (
        void *pSessionHandle,
        const char *pszAuthAzMapOid);

/*
// Get an authentication and authorization map object
*/
int SM_EXTERN Sm_PolicyApi_GetAuthAzMap (
        void *pSessionHandle,
        const char *pszAuthAzMapOid,
        Sm_PolicyApi_AuthAzMap_t **ppAuthAzMap);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                       Certificate Mapping                       ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create certificate map
*/
int SM_EXTERN Sm_PolicyApi_CreateCertMap (
        void *pSessionHandle,
        Sm_PolicyApi_CertMap_t *pCertMap,
        const bool bUpdate);

/*
// Delete certificate map object
*/
int SM_EXTERN Sm_PolicyApi_DeleteCertMap (
        void *pSessionHandle,
        const char *pszCertMapOid);

/*
// Get certificate map object
*/
int SM_EXTERN Sm_PolicyApi_GetCertMap (
        void *pSessionHandle,
        const char *pszCertMapOid,
        Sm_PolicyApi_CertMap_t **ppCertMap);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Domain                                 ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddDomain (
        void* pSessionHandle,
        Sm_PolicyApi_Domain_t* pstructDomain,
        const bool bUpdate);

/*
// Delete a domain.
// Note: Also deletes its children (Rules,Responses,Realms,Policies)
*/
int SM_EXTERN Sm_PolicyApi_DeleteDomain (
        void* pSessionHandle,
        const char* pszDomainOid);

/*
// Get the contents of a Domain object
*/
int SM_EXTERN Sm_PolicyApi_GetDomain (
        void* pSessionHandle,
        const char* pszDomainOid,
        Sm_PolicyApi_Domain_t** ppstructDomain);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Admin                                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/


/*
// Create an Admin
*/
int SM_EXTERN Sm_PolicyApi_AddAdmin (
        void* pSessionHandle,
        Sm_PolicyApi_Admin_t* pstructAdmin,
        const bool bUpdate);

/*
// Delete an Admin.
*/
int SM_EXTERN Sm_PolicyApi_DeleteAdmin (
        void* pSessionHandle,
        const char* pszAdminOid);

/*
// Get the contents of a Admin object
*/
int SM_EXTERN Sm_PolicyApi_GetAdmin (
        void* pSessionHandle,
        const char* pszAdminOid,
        Sm_PolicyApi_Admin_t** ppstructAdmin);

/*
// Associate an existing Admin with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddAdminToDomain(
        void* pSessionHandle,
        const char* pszAdminOid,
        const char* pszDomainOid);

/*
// Disassociate an existing Admin with a Domain
*/
int SM_EXTERN Sm_PolicyApi_RemoveAdminFromDomain(
        void* pSessionHandle,
        const char* pszAdminOid,
        const char* pszDomainOid);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                   Authentication Scheme                         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create a Scheme
*/
int SM_EXTERN Sm_PolicyApi_AddScheme (
        void* pSessionHandle,
        Sm_PolicyApi_Scheme_t* pstructScheme,
        const bool bUpdate);

/*
// Delete a Scheme.
*/
int SM_EXTERN Sm_PolicyApi_DeleteScheme (
        void* pSessionHandle,
        const char* pszSchemeOid);

/*
// Get the contents of a Scheme object
*/
int SM_EXTERN Sm_PolicyApi_GetScheme (
        void* pSessionHandle,
        const char* pszSchemeOid,
        Sm_PolicyApi_Scheme_t** ppstructScheme);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                      Registration Scheme                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create a Registration Scheme
*/
int SM_EXTERN Sm_PolicyApi_AddRegistrationScheme (
        void* pSessionHandle,
        Sm_PolicyApi_RegistrationScheme_t* pstructRegistrationScheme,
        const bool bUpdate);

/*
// Delete a Registration Scheme.
*/
int SM_EXTERN Sm_PolicyApi_DeleteRegistrationScheme (
        void* pSessionHandle,
        const char* pszRegistrationSchemeOid);

/*
// Get the contents of a Registration Scheme object
*/
int SM_EXTERN Sm_PolicyApi_GetRegistrationScheme (
        void* pSessionHandle,
        const char* pszRegistrationSchemeOid,
        Sm_PolicyApi_RegistrationScheme_t** ppstructRegistrationScheme);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                       Password Policy                           ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Create a Password Policy
*/
int SM_EXTERN Sm_PolicyApi_AddPasswordPolicy (
        void* pSessionHandle,
        Sm_PolicyApi_PasswordPolicy_t* pstructPasswordPolicy,
        const bool bUpdate);

/*
// Delete a Password Policy.
*/
int SM_EXTERN Sm_PolicyApi_DeletePasswordPolicy (
        void* pSessionHandle,
        const char* pszPasswordPolicyOid);

/*
// Get the contents of a Password Policy object
*/
int SM_EXTERN Sm_PolicyApi_GetPasswordPolicy (
        void* pSessionHandle,
        const char* pszPasswordPolicyOid,
        Sm_PolicyApi_PasswordPolicy_t** ppstructPasswordPolicy);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                       Regular Expression                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Add a Regular Expression to a Password Policy
*/
int SM_EXTERN Sm_PolicyApi_AddRegularExpressionToPasswordPolicy(
        void *pSessionHandle,
        const char *pszPasswordPolicyOid,
        Sm_PolicyApi_RegularExpression_t *pstructRegExpr);

/*
// Remove a Regular Expression from a Password Policy
*/
int SM_EXTERN Sm_PolicyApi_RemoveRegularExpressionFromPasswordPolicy(
        void *pSessionHandle,
        const char *pszRegularExpressionOid,
        const char *pszPasswordPolicyOid);

/*
// Get all Regular Expression objects belonging to a given Password Policy
*/
int SM_EXTERN Sm_PolicyApi_GetRegularExpressions(
        void *pSessionHandle,
        const char *pszPasswordPolicyOid,
        Sm_PolicyApi_RegularExpression_t **ppstructRegExpr);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Domain objects                         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Realm                                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Adds a Realm and associate it with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddRealm (
        void* pSessionHandle,
        Sm_PolicyApi_Realm_t* pStructRealm,
        const bool bUpdate);
/*
// Deletes a Realm
// Note: Can't delete a Realm if any existing Rules are linked
*/
int SM_EXTERN Sm_PolicyApi_DeleteRealm (
        void* pSessionHandle,
        const char* pszRealmOid);

/*
// Get the contents of a Realm
*/
int SM_EXTERN Sm_PolicyApi_GetRealm (
        void* pSessionHandle,
        const char* pszRealmOid,
        Sm_PolicyApi_Realm_t** ppstructRealm);

/*
// Flush Realm
*/
int SM_EXTERN Sm_PolicyApi_FlushRealm (
        void* pSessionHandle,
        const char* pszRealmOid);

/*
// If Domain Oid is passed, it retrieves top level realms
// If Realm Oid is passed, it retrieves all Oids(realms and rules) whose parent
// is the given Realm Oid
*/
int SM_EXTERN Sm_PolicyApi_GetChildren(
        void* pSessionHandle,
        const char* pszOid,
        Sm_PolicyApi_Oid_t** ppStructObject);




/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Rule                                   ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Adds a Rule and associates the rule with a domain
*/
int SM_EXTERN Sm_PolicyApi_AddRule (
        void* pSessionHandle,
        Sm_PolicyApi_Rule_t* pStructRule,
        const bool bUpdate);

/*
// Adds a Global Rule at the system level
*/
int SM_EXTERN Sm_PolicyApi_AddGlobalRule (
		void* pSessionHandle,
        Sm_PolicyApi_Rule_t* pStructRule,
        const bool bUpdate);

/*
// Deletes a Rule
*/
int SM_EXTERN Sm_PolicyApi_DeleteRule (
        void* pSessionHandle,
        const char* pszRuleOid);

/*
// Gets the Contents of a Rule
*/
int SM_EXTERN Sm_PolicyApi_GetRule (
        void* pSessionHandle,
        const char* pszRuleOid,
        Sm_PolicyApi_Rule_t** ppstructRule);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Response                               ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Creates a Response and associates it with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddResponse (
        void* pSessionHandle,
        Sm_PolicyApi_Response_t* pStructResponse,
        const bool bUpdate);

/*
// Creates a Global Response at the system level
*/
int SM_EXTERN Sm_PolicyApi_AddGlobalResponse (
		void* pSessionHandle,
        Sm_PolicyApi_Response_t* pStructResponse,
        const bool bUpdate);

/*
// Deletes a Response
// Note: deletes any related Response Attributes
*/
int SM_EXTERN Sm_PolicyApi_DeleteResponse (
        void* pSessionHandle,
        const char* pszResponseOid);

/*
// Get the contents of a Response
*/
int SM_EXTERN Sm_PolicyApi_GetResponse (
        void* pSessionHandle,
        const char* pszResponseOid,
        Sm_PolicyApi_Response_t** ppstructResponse);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Response Attributes                    ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Creates a Response Attribute and associates it with a Response
*/
int SM_EXTERN Sm_PolicyApi_AddResponseAttr (
        void* pSessionHandle,
        const char* pszResponseOid,
        Sm_PolicyApi_ResponseAttr_t* pstructResponseAttr);

/*
// Deletes a Response Attribute
*/
int SM_EXTERN Sm_PolicyApi_RemoveResponseAttr (
        void* pSessionHandle,
        const char* szResponseAttrOid);


/*
// Get the Response Attributes that belong to a Response
*/
int SM_EXTERN Sm_PolicyApi_GetResponseAttrs (
        void* pSessionHandle,
        const char* pszResponseOid,
        Sm_PolicyApi_ResponseAttr_t** ppstructResponseAttr);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Policy                                 ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Adds a Policy and associates it with a domain
*/
int SM_EXTERN Sm_PolicyApi_AddPolicy (
        void* pSessionHandle,
        Sm_PolicyApi_Policy_t* pStructPolicy,
        const bool bUpdate);

/*
// Adds a Global Policy at the system level
*/
int SM_EXTERN Sm_PolicyApi_AddGlobalPolicy (
		void* pSessionHandle,
        Sm_PolicyApi_Policy_t* pStructPolicy,
        const bool bUpdate);

/*
// Deletes a Policy
// Note: deletes all related PolicyLinks and User Policies
*/
int SM_EXTERN Sm_PolicyApi_DeletePolicy (
        void* pSessionHandle,
        const char* pszPolicyOid);

/*
// Gets the contents of a Policy
*/
int SM_EXTERN Sm_PolicyApi_GetPolicy (
        void* pSessionHandle,
        const char* pszPolicyOid,
        Sm_PolicyApi_Policy_t** ppstructPolicy);




/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Policy Link                            ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Adds a PolicyLink to a Policy
*/
int SM_EXTERN Sm_PolicyApi_AddPolicyLink (
        void* pSessionHandle,
        const char* pszPolicyOid,
        Sm_PolicyApi_PolicyLink_t *pstructPolicyLink);

/*
// Deletes a PolicyLink
*/
int SM_EXTERN Sm_PolicyApi_RemovePolicyLinkFromPolicy (
        void* pSessionHandle,
        const char* pszPolicyLinkOid,
        const char* pszPolicyOid);

/*
// For the specified Policy and Domain, return all of the PolicyLinks
*/
int SM_EXTERN Sm_PolicyApi_GetPolicyLinks (
        void* pSessionHandle,
        const char* pszPolicyOid,
        Sm_PolicyApi_PolicyLink_t** ppstructPolicyLink);

/*
// Change the Response part of a particular PolicyLink
*/
int SM_EXTERN Sm_PolicyApi_SetResponseInPolicyLink (
        void* pSessionHandle,
        const char* pszPolicyOid,
        Sm_PolicyApi_PolicyLink_t* ppstructPolicyLink);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                     User Policies                               ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Adds directory entries to a Policy.  Can only add one User specification
// (can be an aggregate) at a time
//
// iPolicyFlags is policy behavior flags defined in SmApi.h
*/
int SM_EXTERN Sm_PolicyApi_AddUsersToPolicy (
        void* pSessionHandle,
        const char* pszPolicyOid,
        Sm_PolicyApi_User_t *pStructUsers,
        int   iPolicyFlags);

/*
// Remove User specification from a Policy. Can only remove one User
// (can be an aggregate) at a time
*/
int SM_EXTERN Sm_PolicyApi_RemoveUsersFromPolicy (
        void* pSessionHandle,
        const char* pszPolicyOid,
        const char* pszUserPolicyOid);

/*
// Get a list of Users who belong to a Policy
*/
int SM_EXTERN Sm_PolicyApi_GetPolicyUsers (
        void* pSessionHandle,
        const char* pszPolicyOid,
        const char* pszUserDirOid,
        Sm_PolicyApi_User_t **ppStructUsers);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                        Trusted Hosts                            ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Gets the Contents of a Trusted Host Object
*/
int SM_EXTERN Sm_PolicyApi_GetTrustedHost (
    void*       pSessionHandle,
    const char* pszTrustedHostOid,
    Sm_PolicyApi_TrustedHost_t**    ppstructTrustedHost);

/*
// Creates a Trusted Host Object
*/
int SM_EXTERN Sm_PolicyApi_AddTrustedHost (
	void*		                pSessionHandle,
	Sm_PolicyApi_TrustedHost_t*	pstructTrustedHost,
	bool                        bUpdate,
	bool                        bGenSharedSecret);


/*
// Deletes a Trusted Host Object
*/
int SM_EXTERN Sm_PolicyApi_DeleteTrustedHost (
    void*       pSessionHandle,
    const char*     pszTrustedHostOid);

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                      Host Configurations                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Creates or Updates a Host Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_AddHostConfig (
    void*       pSessionHandle,
    Sm_PolicyApi_HostConfig_t*  pstructHostConfig,
    const bool  bUpdate);

/*
// Gets the Contents of a Host Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_GetHostConfig (
    void*       pSessionHandle,
    const char* pszHostConfigOid,
    Sm_PolicyApi_HostConfig_t** ppstructHostConfig);

/*
// Deletes a Host Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_DeleteHostConfig (
    void*       pSessionHandle,
    const char* pszHostConfigOid);

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                      Agent Configurations                       ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Creates or Updates a Agent Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_AddAgentConfig (
	void*						pSessionHandle,
	Sm_PolicyApi_AgentConfig_t*	pstructAgentConfig,
	const bool					bUpdate);

/*
// Gets the Contents of a Agent Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_GetAgentConfig (
	void*							pSessionHandle,
	const char*						pszAgentConfigOid,
	Sm_PolicyApi_AgentConfig_t**	ppstructAgentConfig);

/*
// Deletes a Agent Configuration Object
*/
int SM_EXTERN Sm_PolicyApi_DeleteAgentConfig (
	void*		pSessionHandle,
	const char*	pszAgentConfigOid);

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                    Agent Config Associations                    ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/


/*
// Creates a name-value and associates it with an Agent Config Object
*/
int SM_EXTERN Sm_PolicyApi_AddAgentConfigAssociation (
	void* 							pSessionHandle,
	const char* 					pszAgentConfigOid,
	Sm_PolicyApi_Association_t* 	pstructAssociation,
	bool							bUpdate);

/*
// Deletes a name-value pair associated with an Agent Config Object
*/
int SM_EXTERN Sm_PolicyApi_RemoveAgentConfigAssociation (
	void* 							pSessionHandle,
	const char* 					pszAssociationOid);

/*
// Gets name-value pairs associated with an Agent Config Object
*/
int SM_EXTERN Sm_PolicyApi_GetAgentConfigAssociations (
	void* 							pSessionHandle,
	const char* 					pszAgentConfigOid,
	Sm_PolicyApi_Association_t** 	ppstructAssociations);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////              Retrieve Global and Domain Objects                 ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Get domain based objects. This function returns Oids of the
// objects contained within the domain.
*/
int SM_EXTERN Sm_PolicyApi_GetDomainObjects (
        void* pSessionHandle,
        const char* pszDomainOid,
        const Sm_PolicyApi_Objects_t nObjectId,
        Sm_PolicyApi_Oid_t** ppstructObject);

/*
// Get Global objects.
*/
int SM_EXTERN Sm_PolicyApi_GetGlobalObjects (
        void* pSessionHandle,
        const Sm_PolicyApi_Objects_t nObjectId,
        Sm_PolicyApi_Oid_t** ppstructObject);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          Group                                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Creates a new Group of any type (rule, response, agent)
*/
int SM_EXTERN Sm_PolicyApi_AddGroup (
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszDomainOid,
        Sm_PolicyApi_Group_t* pStructGroup,
        const bool bUpdate);

/*
// Deletes a Group of any type (rule, response, agent)
*/
int SM_EXTERN Sm_PolicyApi_DeleteGroup (
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszGroupOid,
        const char* pszDomainOid);

/*
// Deletes a Group of any type (rule, response, agent)
*/
int SM_EXTERN Sm_PolicyApi_GetGroup (
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszGroupOid,
        const char* pszDomainOid,
        Sm_PolicyApi_Group_t** ppStructGroup);

/*
// Get members of a group.
// The group can be of any type (rule, response, agent)
*/
int SM_EXTERN Sm_PolicyApi_GetGroupOids(
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszGroupOid,
        const char* pszDomainOid,
        Sm_PolicyApi_Oid_t** ppStructObjects);

/*
// Add rule/group, response/group, and agent/group from its
// respective groups.
*/
int SM_EXTERN Sm_PolicyApi_AddToGroup(
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszItemOid,
        const char* pszGroupOid,
        const char* pszDomainOid);

/*
// Remove rules, responses, and agent from its respective groups.
*/
int SM_EXTERN Sm_PolicyApi_RemoveFromGroup(
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszItemOid,
        const char* pszGroupOid,
        const char* pszDomainOid);

/*
// Check if szOid is a group.
*/
int SM_EXTERN Sm_PolicyApi_IsGroup(
        void* pSessionHandle,
        Sm_PolicyApi_Groups_t dwGroup,
        const char* pszOid,
        const char* pszDomainOid,
        bool* bIsGroup);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                          User Management                        ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Management Command
*/
int SM_EXTERN Sm_PolicyApi_ManagementCommand (
        void* pSessionHandle,
        Sm_PolicyApi_ManagementCommand_t* pstructManagementCommand);

/*
// Get a list of groups a user is member of.
*/
int SM_EXTERN Sm_PolicyApi_GetUserGroups (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        const bool bRecursive,
        char** pszGroups[]);

/*
// Set disable user state
*/
int SM_EXTERN Sm_PolicyApi_SetDisabledUserState (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        const Sm_Api_DisabledReason_t nDisabledReason,
        char **pszErrMsg);

/*
// Get reason for disablement of a user.
*/
int SM_EXTERN Sm_PolicyApi_GetDisabledUserState (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        Sm_Api_DisabledReason_t *nDisabledReason,
        char **pszErrMsg);
/*
// Set User Password State
*/
int SM_EXTERN Sm_PolicyApi_SetUserPasswordState (
        void 		*pSessionHandle,
        const char 	*pszUserDirOid,
        const char 	*pszUserDN,
        Sm_PolicyApi_UserPasswordState_t *pPasswordState,
        bool            	bEmptyHistory
        );

/*
// Get User Password State.
*/
int SM_EXTERN Sm_PolicyApi_GetUserPasswordState (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        Sm_PolicyApi_UserPasswordState_t *pPasswordState
        );

/*
// Disable user
*/
int SM_EXTERN Sm_PolicyApi_DisableUser (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        char **pszErrMsg);


/*
// Enable user
*/
int SM_EXTERN Sm_PolicyApi_EnableUser (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        char **pszErrMsg);

/*
// Change:
// Change password of a user account. Set bChangePassword to true
// to change the password.
//
// Validation:
// This function can also be used for validating a old and new password.
// Set bValidateNewPassword to true to validate a new password.
// Set bValidateOldPassword to true to validate a old password.
*/
int SM_EXTERN Sm_PolicyApi_SetPassword (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        const char *pszNewPassword,
        const char *pszOldPassword,
        bool  bChangePassword,
        bool  bValidateNewPassword,
        bool  bValidateOldPassword,
        char **pszErrMsg);


/*
// Get password services message. Call this function when Sm_PolicyApi_SetPassword
// returns Sm_PolicyApi_InvalidPasswordSyntax error code.
*/
int SM_EXTERN Sm_PolicyApi_GetPasswordMsg (
        void *pSessionHandle,
        const char *pszPasswordMsg,
        unsigned int *nVersion,
        unsigned int *nMsgId,
        unsigned int *nArgs,
        Sm_PolicyApi_PasswordMsgField_t** ppStructMsgField);


/*
// Flush a user from a User Cache
*/
int SM_EXTERN Sm_PolicyApi_FlushUser (
        void *pSessionHandle,
        const char *pszUserDirOid,
        const char *pszUserDN,
        char **pszErrMsg);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                       Variable Functions                         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Get the contents of an VariableType object
*/
int SM_EXTERN Sm_PolicyApi_GetVariableType (
        void* pSessionHandle,
        const char* pszVariableTypeOid,
        Sm_PolicyApi_VariableType_t** ppstructVariableType);


/*
// Adds a Variable and associate it with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddVariable (
        void* pSessionHandle,
        Sm_PolicyApi_Variable_t* pstructVariable,
        const bool bUpdate);

/*
// Deletes a Variable
// Note: Can't delete a Variable if any existing Variable expressions are linked to it
*/
int SM_EXTERN Sm_PolicyApi_DeleteVariable (
        void* pSessionHandle,
        const char* pszVariableOid);

/*
// Get the contents of a Variable
*/
int SM_EXTERN Sm_PolicyApi_GetVariable (
        void* pSessionHandle,
        const char* pszVariableOid,
        Sm_PolicyApi_Variable_t** ppstructVariable);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                Affiliate Domain Functions                       ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Add an affiliate domain
*/
int SM_EXTERN Sm_PolicyApi_AddAffiliateDomain (
        void* pSessionHandle,
        Sm_PolicyApi_AffiliateDomain_t* pstructAffiliateDomain,
        const bool bUpdate);

/*
// Get an affiliate domain
*/
int SM_EXTERN Sm_PolicyApi_GetAffiliateDomain (
        void* pSessionHandle,
        const char* pszAffiliateDomainOid,
        Sm_PolicyApi_Domain_t** ppstructDomain);

/*
// Get affiliate domain based objects. This function returns Oids of the
// objects contained within the affiliate domain.
*/
int SM_EXTERN Sm_PolicyApi_GetAffiliateDomainObjects (
        void* pSessionHandle,
        const char* pszAffiliateDomainOid,
        const Sm_PolicyApi_Objects_t nObjectId,
        Sm_PolicyApi_Oid_t** ppstructObject);

/*
// Deletes an affiliate domain.
*/
int SM_EXTERN Sm_PolicyApi_DeleteAffiliateDomain (
        void* pSessionHandle,
        const char* pszAffiliateDomainOid);

/*
////////////    User Dir functions for Affiliate Domains    /////////////
*/
/*
// Associate an existing User Dir with an Affiliate Domain
*/
int SM_EXTERN Sm_PolicyApi_AddUserDirToAffiliateDomain(
        void* pSessionHandle,
        const char* pszUserDirOid,
        const char* pszAffiliateDomainOid);

/*
// Disassociate an existing User Dir with an Affiliate Domain
*/
int SM_EXTERN Sm_PolicyApi_RemoveUserDirFromAffiliateDomain(
        void* pSessionHandle,
        const char* pszUserDirOid,
        const char* pszAffiliateDomainOid);

/*
// Retrieve the search order of User Dirs for an Affiliate Domain
*/
int SM_EXTERN Sm_PolicyApi_GetAffiliateDomainUserDirSearchOrder(
        void* pSessionHandle,
        const char* pszAffiliateDomainOid,
        char** pszArray[]);

/*
// Set the search order of User Dirs for an Affiliate Domain
*/
int SM_EXTERN Sm_PolicyApi_SetAffiliateDomainUserDirSearchOrder(
        void* pSessionHandle,
        const char* pszAffiliateDomainOid,
        char* pszArray[]);

/*
/////////////    Admin functions for Affiliate Domains    ///////////////
*/
/*
// Associate an existing Admin with a Domain
*/
int SM_EXTERN Sm_PolicyApi_AddAdminToAffiliateDomain(
        void* pSessionHandle,
        const char* pszAdminOid,
        const char* pszAffiliateDomainOid);

/*
// Disassociate an existing Admin with a Domain
*/
int SM_EXTERN Sm_PolicyApi_RemoveAdminFromAffiliateDomain(
        void* pSessionHandle,
        const char* pszAdminOid,
        const char* pszAffiliateDomainOid);


/*
/////////////////////////////////////////////////////////////////////////////
////                                                                     ////
////            Affiliate Object Functions                               ////
////                                                                     ////
/////////////////////////////////////////////////////////////////////////////
*/

/*
// Create an affiliate object
*/
int SM_EXTERN Sm_PolicyApi_AddAffiliate (
        void* pSessionHandle,
        Sm_PolicyApi_Affiliate_t* pstructAffiliate,
        const bool bUpdate);

/*
// Get an affiliate object
*/
int SM_EXTERN Sm_PolicyApi_GetAffiliate (
        void* pSessionHandle,
        const char* pszAffiliateOid,
        Sm_PolicyApi_Affiliate_t** ppstructAffiliate);

/*
// Get all affiliates for a domain as a linked list.
*/
int SM_EXTERN Sm_PolicyApi_GetAllAffiliates (
        void* pSessionHandle,
        const char* pszAffiliateDomainOid,
        Sm_PolicyApi_Affiliate_t** ppstructAffiliates);

/*
// Delete an affiliate object. This will then delete the agent,
// realm, rule, policy, and policy link objects associated with the
// affiliate object
*/
int SM_EXTERN Sm_PolicyApi_DeleteAffiliate (
        void* pSessionHandle,
        const char* pszAffiliateOid);

/*
/////////////////       User functions for Affiliates      ///////////////////
*/
/*
// Adds directory entries to an Affiliate.  Can only add one User specification
// (can be an aggregate) at a time
//
// iPolicyFlags is policy behavior flags defined in SmApi.h
*/
int SM_EXTERN Sm_PolicyApi_AddUsersToAffiliate (
        void* pSessionHandle,
        const char* pszAffiliateOid,
        Sm_PolicyApi_User_t *pStructUsers,
        int   iPolicyFlags);

/*
// Remove User specification from an Affiliate. Can only remove one User
// (can be an aggregate) at a time
*/
int SM_EXTERN Sm_PolicyApi_RemoveUsersFromAffiliate (
        void* pSessionHandle,
        const char* pszAffiliateOid,
        const char* pszUserPolicyOid);

/*
// Get a list of Users who belong to an Affiliate
*/
int SM_EXTERN Sm_PolicyApi_GetAffiliateUsers (
        void* pSessionHandle,
        const char* pszAffiliateOid,
        const char* pszUserDirOid,
        Sm_PolicyApi_User_t **ppStructUsers);

/*
// Add a new attribute to an affiliate.
*/
int SM_EXTERN Sm_PolicyApi_AddAttributeToAffiliate (
        void* pSessionHandle,
        const Sm_PolicyApi_AffiliateAttr_t* pstructAffiliateAttr,
        const char* pszAffiliateOid);

/*
// Remove an attribute from an affiliate.
*/
int SM_EXTERN Sm_PolicyApi_RemoveAttributeFromAffiliate (
        void* pHandle,
        const Sm_PolicyApi_AffiliateAttr_t* pstructAffiliateAttr,
        const char* pszAffiliateOid);

/*
// Get all attributes for an affiliate.
*/
int SM_EXTERN Sm_PolicyApi_GetAllAffiliateAttributes (
        void* pHandle,
        const char* pszAffiliateOid,
        Sm_PolicyApi_AffiliateAttr_t** ppstructAffiliateAttr);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  Shared Secret Policy                           ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Get the current shared secret policy
*/
int SM_EXTERN Sm_PolicyApi_GetSharedSecretPolicy (
    void*       pSessionHandle,
    Sm_PolicyApi_SharedSecretPolicy_t** ppstructSecretPolicy);

/*
// Set the shared secret policy
*/
int SM_EXTERN Sm_PolicyApi_SetSharedSecretPolicy (
    void*       pSessionHandle,
    Sm_PolicyApi_SharedSecretPolicy_t* ppstructSecretPolicy);

/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                       Utility Functions                         ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// Rename any object
*/
int SM_EXTERN Sm_PolicyApi_RenameObject(
        void* pSessionHandle,
        const char* pszOid,
        const char* pszNewName);



#if defined(__unix)
}
#endif

#endif

/* end of file SmPolicyApi45.h */
