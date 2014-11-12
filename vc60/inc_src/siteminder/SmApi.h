
#ifndef _SmApi_h_
#define _SmApi_h_

/*
Copyright (C) 1997-2003, Netegrity, Inc. All rights reserved.

Netegrity, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.


SiteMinder Authentication and Active Expression Server API
*/

#ifndef SM_EXTERN
#if defined(__unix)
#define SM_EXTERN
#else
#define SM_EXTERN __stdcall
#endif
#endif


/*
// Server-supplied version indicates the server's compliance level.
// Client-supplied version indicates the client's compliance level
*/
#define Sm_Api_Version_V3       0x0300
#define Sm_Api_Version_V4       0x0400
#define Sm_Api_Version_V4_1     0x0401

/*
// authentication credentials - bit flags that can be ORed together if more
// than one set of credentials is required
//
*/

enum Sm_Api_Credentials_t
{
/* credentiala */
 Sm_AuthApi_Cred_None = 0x00                           /* no credentials required; used for anonymous realms */
,Sm_AuthApi_Cred_Basic = 0x01                          /* username and password required */
,Sm_AuthApi_Cred_Digest = 0x02                         /* digest required */
,Sm_AuthApi_Cred_X509Cert = 0x04                       /* X509 cert required */
,Sm_AuthApi_Cred_X509CertUserDN = 0x08                 /* X509 cert user DN required */
,Sm_AuthApi_Cred_X509CertIssuerDN = 0x10               /* X509 cert issuer DN required */
,Sm_AuthApi_Cred_CertOrBasic = 0x20                    /* Use certificate if available, otherwise basic */
,Sm_AuthApi_Cred_NTChalResp = 0x40                     /* NT Challenge/Response */
,Sm_AuthApi_Cred_CertOrForm = 0x80					   /* Use certificate if available, otherwise form */


/* modifiers */
,Sm_AuthApi_Cred_SSLRequired = 0x01000000              /* SSL required */
,Sm_AuthApi_Cred_FormRequired = 0x02000000             /* Credentials form required */
,Sm_AuthApi_Cred_AllowSaveCreds = 0x04000000           /* Save credentials hint */
,Sm_AuthApi_Cred_PreserveSessionId = 0x08000000        /* Session id should be preserved if the current session is still valid */
,Sm_AuthApi_Cred_DoNotChallenge = 0x10000000           /* Do not challenge for credentials */
};


/* reason codes - 32000 and above are user-defined */
enum Sm_Api_Reason_t
{
 Sm_Api_Reason_None = 0
,Sm_Api_Reason_PwMustChange = 1
,Sm_Api_Reason_InvalidSession = 2
,Sm_Api_Reason_RevokedSession = 3
,Sm_Api_Reason_ExpiredSession = 4
,Sm_Api_Reason_AuthLevelTooLow = 5
,Sm_Api_Reason_UnknownUser = 6
,Sm_Api_Reason_UserDisabled = 7
,Sm_Api_Reason_InvalidSessionId = 8
,Sm_Api_Reason_InvalidSessionIp = 9
,Sm_Api_Reason_CertificateRevoked = 10
,Sm_Api_Reason_CRLOutOfDate = 11
,Sm_Api_Reason_CertRevokedKeyCompromised = 12
,Sm_Api_Reason_CertRevokedAffiliationChange = 13
,Sm_Api_Reason_CertOnHold = 14
,Sm_Api_Reason_TokenCardChallenge = 15
,Sm_Api_Reason_ImpersonatedUserNotInDir = 16
,Sm_Api_Reason_Anonymous = 17
,Sm_Api_Reason_PwWillExpire = 18
,Sm_Api_Reason_PwExpired = 19
,Sm_Api_Reason_ImmedPWChangeRequired = 20
,Sm_Api_Reason_PWChangeFailed = 21
,Sm_Api_Reason_BadPWChange = 22
,Sm_Api_Reason_PWChangeAccepted = 23
,Sm_Api_Reason_ExcessiveFailedLoginAttempts = 24
,Sm_Api_Reason_AccountInactivity = 25
,Sm_Api_Reason_NoRedirectConfigured = 26
,Sm_Api_Reason_ErrorMessageIsRedirect = 27
,Sm_Api_Reason_Next_Tokencode = 28

,Sm_Api_Reason_New_PIN_Select = 29
,Sm_Api_Reason_New_PIN_Sys_Tokencode = 30
,Sm_Api_Reason_New_User_PIN_Tokencode = 31
,Sm_Api_Reason_New_PIN_Accepted = 32
,Sm_Api_Reason_Guest = 33
,Sm_Api_Reason_PWSelfChange = 34

,Sm_Api_Reason_ServerException = 35
,Sm_Api_Reason_UnknownScheme = 36
,Sm_Api_Reason_UnsupportedScheme = 37
,Sm_Api_Reason_Misconfigured = 38
,Sm_Api_Reason_BufferOverflow = 39

,Sm_Api_Reason_SetPersistentSessionFailed = 40
,Sm_Api_Reason_UserLogout = 41
,Sm_Api_Reason_IdleSession = 42
,Sm_Api_Reason_PolicyServerEnforcedTimeout = 43
,Sm_Api_Reason_PolicyServerEnforcedIdle = 44

,Sm_Api_Reason_ImpersonationNotAllowed = 45
,Sm_Api_Reason_ImpersonationNotAllowedUser = 46

};

/*
// Sm_Api_Reason_MaxDefined denotes the maximum defined Sm_Api_Reason enumerator.
*/
#define Sm_Api_Reason_MaxDefined Sm_Api_Reason_ImpersonationNotAllowedUser

/*
// Clients that use the values below should be aware
// that multiple reasons can exist concurrently, and
// that when a user is enabled, all of the flags in the
// disabled mask should be cleared
*/
enum Sm_Api_DisabledReason_t
{
/* disabled mask */
 Sm_Api_Disabled_DisabledMask = 0x00ffffff
,Sm_Api_Disabled_Enabled = 0

/* disabled bits */
,Sm_Api_Disabled_AdminDisabled = 0x00000001
,Sm_Api_Disabled_MaxLoginFail = 0x00000002
,Sm_Api_Disabled_Inactivity = 0x00000004
,Sm_Api_Disabled_PWExpired = 0x00000008

/* qualifiers */
,Sm_Api_Disabled_PWMustChange = 0x01000000
};


/*
// Scheme Types
*/
enum Sm_Api_SchemeType_t
{
 Sm_Api_SchemeType_Basic = 1
,Sm_Api_SchemeType_CryptoCard = 2
,Sm_Api_SchemeType_Encotone = 3
,Sm_Api_SchemeType_HTMLForm = 4
,Sm_Api_SchemeType_BasicOverSSL = 5
,Sm_Api_SchemeType_RadiusServer = 6
,Sm_Api_SchemeType_SafeWordServer = 7
,Sm_Api_SchemeType_ACEServer = 8
,Sm_Api_SchemeType_X509ClientCert = 9
,Sm_Api_SchemeType_X509ClientCertAndBasic = 10
,Sm_Api_SchemeType_X509ClientCertOrBasic = 11
,Sm_Api_SchemeType_RadiusChapPap = 12
,Sm_Api_SchemeType_Anonymous = 13
,Sm_Api_SchemeType_NTLM = 14
,Sm_Api_SchemeType_Custom = 15
,Sm_Api_SchemeType_ACEServerHTMLForm = 16
,Sm_Api_SchemeType_SafeWordHTMLForm = 17
,Sm_Api_SchemeType_XMLDsig = 18
,Sm_Api_SchemeType_X509ClientCertOrForm = 19
,Sm_Api_SchemeType_X509ClientCertAndForm = 20
,Sm_Api_SchemeType_MSPassport = 21
,Sm_Api_SchemeType_XMLDocumentCredentialCollector = 22
,Sm_Api_SchemeType_SAML = 23
,Sm_Api_SchemeType_WSSec = 24
,Sm_Api_SchemeType_SAMLSessionTicket = 25
,Sm_Api_SchemeType_SAMLArtifact = 26
,Sm_Api_SchemeType_Impersonation = 27
};

enum Sm_DirectoryCapability_t
{
 Sm_DirCapability_CreatePasswordPolicy      = 0x00000001  /* attributes: passworddata, disabled, userpassword */
,Sm_DirCapability_CreateRegistrationPolicy  = 0x00000002  /* attributes: guid, emailaddress, challengeresp, userpassword */
,Sm_DirCapability_ResetUserPassword         = 0x00000004  /* attributes: disabled, userpassword */
,Sm_DirCapability_ChangeUserPassword        = 0x00000008  /* attributes: userpassword */
,Sm_DirCapability_DisableUser               = 0x00000010  /* attributes: disabled */
,Sm_DirCapability_DmsCapable                = 0x00000020  /* enabled for DMS */
,Sm_DirCapability_Recursive                 = 0x00000040  /* supports recursion (nested groups, etc) */
,Sm_DirCapability_Sorting                   = 0x00000080  /* supports sorting */
,Sm_DirCapability_Paging                    = 0x00000100  /* supports paging */

,Sm_DirCapability_DisabledAttr              = 0x00100000
,Sm_DirCapability_UniversalIdAttr           = 0x00200000
,Sm_DirCapability_AnonymousIdAttr           = 0x00400000
,Sm_DirCapability_PasswordDataAttr          = 0x00800000
,Sm_DirCapability_UserPasswordAttr          = 0x01000000
,Sm_DirCapability_EmailAddressAttr          = 0x02000000
,Sm_DirCapability_ChallengeRespAttr         = 0x04000000
};

/*
// Password Policy Behavior - used by Policy API to define password policy characteristics
*/
enum Sm_PasswordPolicyBehavior_t
{
/*
** bits 0 and 1 are reserved for policy recursion and exclusion
*/
 Sm_PasswordPolicy_DontTrackLogins          = 0x00000004 /* don't perform directory updates at login time */
,Sm_PasswordPolicy_AllowFailedWrites		= 0x00000008 /* don't fail authentication if passworddata updates fail */
,Sm_PasswordPolicy_InactivityForcePWChange	= 0x00000010 /* if the user is marked inactive, don't disable, force a PW change */
,Sm_PasswordPolicy_PWExpiredForcePWChange	= 0x00000020 /* if the user has an expired password, don't disable, force a PW change */
,Sm_PasswordPolicyBehavior_FullReenable 	= 0x00000040 /* after N-strikes re-enablement, is the user fully enabled vs. one attempt per re-enablement period. */
,Sm_PasswordPolicy_StopPriorityChaining     = 0x00000080 /* don't evaluate policies with lower priority ratings */
,Sm_PasswordPolicy_ExpireDisablePassword    = 0x00000100 /* on password expiration, disable only the password, not the user's account */
,Sm_PasswordPolicy_FailuresDisablePassword  = 0x00000200 /* on excess authentication failures, disable only the password, not the user's account */
/*
// these bits describe preprocessing of password from user before checking or storing it
*/
,Sm_PasswordPolicy_ForceCase                = 0x00000400 /* force case as per Sm_PasswordPolicy_CaseSelect */
,Sm_PasswordPolicy_CaseSelect               = 0x00000800 /* when forcing case, set => upper case, clear => lower case */
,Sm_PasswordPolicy_CaseBits                 = 0x00000c00 /* convenience combination */
,Sm_PasswordPolicy_StripLeadingWhiteSpace   = 0x00001000 /* remove leading white space */
,Sm_PasswordPolicy_StripTrailingWhiteSpace  = 0x00002000 /* remove trailing white space */
,Sm_PasswordPolicy_StripFlankingWhiteSpace  = 0x00003000 /* convenience combination */
,Sm_PasswordPolicy_StripEmbeddedWhiteSpace  = 0x00004000 /* remove embedded white space */
,Sm_PasswordPolicy_WhiteSpaceBits           = 0x00007000 /* convenience combination */
,Sm_PasswordPolicy_PreProcessBits           = 0x00007c00 /* convenience combination */
};


/*
// Policy Behavior - used by Policy API to define user and password policies
*/

/*
** Bit 0x01 determines if user policy excludes 'users', rather than includes
*/
#define Sm_PolicyBehavior_Exclude_Mask      0x01
#define Sm_PolicyBehavior_Exclude_No        0x00
#define Sm_PolicyBehavior_Exclude_Yes       0x01

/*
** Bit 0x02 determines if user policy is recursive, such as whether or not nested groups should be supported
*/
#define Sm_PolicyBehavior_Recursive_Mask    0x02
#define Sm_PolicyBehavior_Recursive_No      0x00
#define Sm_PolicyBehavior_Recursive_Yes     0x02


/*
// Get User Property
//
// If the function succeeds, the return value is the number of characters in the output buffer.
// If the function fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_GetUserProp)
(
const void*             lpParam,            /* the function parameter */
const char*             lpszPropName,       /* the name of the user property (null-terminated) */
const int               nBytesValueBuf,     /* the maximum size of the user property buffer */
char*                   lpszValueBuf        /* the output buffer to hold the null-terminated user property */
);

/*
// Set User Property
//
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_SetUserProp)
(
const void*             lpParam,            /* the function parameter */
const char*             lpszPropName,       /* the name of the user property (null-terminated) */
const int               nBytesValueBuf,     /* the size of the user property buffer */
const char*             lpszValueBuf        /* the user property buffer */
);

/*
// Get Directory DN Property if the user is related to DN
//
// If the function succeeds, the return value is the number of characters in the output buffer.
// If the function fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_GetDnProp)
(
const void*             lpParam,            /* the function parameter */
const char*             lpDn,               /* the DN of a directory object */
const char*             lpszPropName,       /* the name of the user property (null-terminated) */
const int               nBytesValueBuf,     /* the maximum size of the user property buffer */
char*                   lpszValueBuf        /* the output buffer to hold the null-terminated user property */
);

/*
// Set Directory DN Property if the user is related to DN
//
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_SetDnProp)
(
const void*             lpParam,            /* the function parameter */
const char*             lpDn,               /* the DN of a directory object */
const char*             lpszPropName,       /* the name of the user property (null-terminated) */
const int               nBytesValueBuf,     /* the size of the user property buffer */
const char*             lpszValueBuf        /* the user property buffer */
);

/*
// Authenticate User
//
// If the authentication succeeds, the return value is 0
// If the authentication fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_AuthenticateUser)
(
const void*             lpParam,            /* the function parameter */
const char*             lpszPassword,       /* the user password (null-terminated) */
const int               nBytesUserMsg,      /* maximum size of the user message buffer */
char*                   lpszUserMsg,        /* output buffer to hold the null-terminated user message */
const int               nBytesErrMsg,       /* maximum size of the error buffer */
char*                   lpszErrMsg          /* output buffer to hold the null-terminated error message */
);

/*
// Logging functions
*/
typedef void (SM_EXTERN *Sm_Api_LogFunc) (const char* lpszBuffer);                                 /* string to log (null-terminated) */
typedef void (SM_EXTERN *Sm_Api_ErrorFunc) (const char* lpszBuffer);                               /* string to log (null-terminated) */
typedef void (SM_EXTERN *Sm_Api_TraceFunc) (const char* lpszCheckpoint, const char* lpszBuffer);   /* string to log (null-terminated) */


/*
// SiteMinder context structure
*/

typedef void* (SM_EXTERN *Sm_Api_GetBufferFunc) (const void *pHandle);
typedef void* (SM_EXTERN *Sm_Api_AllocBufferFunc) (const void *pHandle, const int nSize);
typedef void (SM_EXTERN *Sm_Api_FreeBufferFunc) (const void *pHandle);
typedef int (SM_EXTERN *Sm_Api_GetBufferSizeFunc) (const void *pHandle);

typedef struct
{
void*                      pHandle;
Sm_Api_GetBufferFunc       fGetBuffer;
Sm_Api_AllocBufferFunc     fAllocBuffer;
Sm_Api_FreeBufferFunc      fFreeBuffer;
Sm_Api_GetBufferSizeFunc   fGetBufferSize;
} Sm_Api_AppSpecificContext_t;


typedef struct
{
int                            nVersion;           /* the server API version */
Sm_Api_LogFunc                 fLog;               /* log function */
Sm_Api_TraceFunc               fTrace;             /* trace function */
Sm_Api_ErrorFunc               fError;             /* error function */
Sm_Api_AppSpecificContext_t*   pAppSpecific;       /* application-specific buffer management */
} Sm_Api_Context_t;


/*
// user context structure
*/

typedef struct
{
unsigned char           bIsUserContext;     /* the 'user context available?' flag */
char*                   lpszUserName;       /* the user DN (null-terminated) */
char*                   lpszUserPath;       /* the path to the user object (null-terminated) */
char*                   lpszDirPath;        /* the path to the directory (null-terminated) */
void*                   lpReserved1;        /* reserved */
char*                   lpszDirServer;      /* the directory server */
char*                   lpszDirNamespace;   /* the directory namespace */
char*                   lpszSessionId;      /* the session id */
Sm_Api_GetDnProp        fGetDnProp;         /* the function to call to retrieve properties of a directory DN */
Sm_Api_SetDnProp        fSetDnProp;         /* the function to call to set properties of a directory DN */
void*                   lpParam;            /* the function parameter */
Sm_Api_GetUserProp      fGetProp;           /* the function to call to retrieve user properties */
Sm_Api_SetUserProp      fSetProp;           /* the function to call to set user properties */
Sm_Api_AuthenticateUser fAuthenticate;      /* the function to call to validate user password */
} Sm_Api_UserContext_t;


/*
// resource context structure
*/

typedef struct
{
char*             lpszServer;         /* the server of the resource being requested (null-terminated) */
char*             lpszResource;       /* the resource being requested (null-terminated) */
char*             lpszAction;         /* the action being requested (null-terminated) */
} Sm_Api_RequestContext_t;


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  SiteMinder Authentication API                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// This structure specifies the available user credentials.
// The authentication scheme can choose which credentials it needs to honor
*/

typedef struct
{
char*   lpszUsername;               /* User name (null-terminated) */
char*   lpszPassword;               /* User password (null-terminated) */
int     nBytesChapPassword;         /* Length of a CHAP password */
char*   lpszChapPassword;           /* CHAP password */
int     nBytesChapChallenge;        /* Length of a CHAP challenge */
char*   lpszChapChallenge;          /* CHAP challenge */
char*   lpReserved1;                /* Reserved */
char*   lpszCertUserDN;             /* Certificate User DN (null-terminated) */
char*   lpszCertIssuerDN;           /* Certificate Issuer DN (null-terminated) */
int     nCertBinLen;                /* Length of a binary certifcate */
void*   lpCertBinary;               /* The binary certificate */
char*   lpszDirPath;                /* the path to the directory (null-terminated) */
char*   lpszDirServer;              /* the directory server (null-terminated) */
char*   lpszDirNamespace;           /* the directory namespace (null-terminated) */
char*   lpszNewPassword;            /* New user password (null-terminated) */
char*   lpszPasswordToken;          /* Password token from Password Services(null-terminated) */
} Sm_AuthApi_UserCredentials_t;


/*
// API entry points
*/
#define Sm_AuthApi_Init_FuncName            "SmAuthInit"
#define Sm_AuthApi_Release_FuncName         "SmAuthRelease"
#define Sm_AuthApi_Query_FuncName           "SmAuthQuery"
#define Sm_AuthApi_Authenticate_FuncName    "SmAuthenticate"


/*
// authentication API return status
*/
enum Sm_AuthApi_Status_t
{
 Sm_AuthApi_Success = 0
,Sm_AuthApi_Failure = 1
,Sm_AuthApi_Accept = 2
,Sm_AuthApi_Reject = 3
,Sm_AuthApi_Challenge = 4
,Sm_AuthApi_Attempt = 5
,Sm_AuthApi_NoUserContext = 6
,Sm_AuthApi_SuccessUserDN = 7
,Sm_AuthApi_SuccessUserFilter = 8
};


/*
// The return status value from the authenticatin function (Sm_AuthApi_Authenticate_FuncName)
// is expected to be constructed using the SM_MAKEAUTH_STATUSVALUE macro.
//
// status is of type Sm_AuthApi_Status_t
// reason is of type Sm_Reason_Status_t
*/

#define SM_MAKEAUTH_STATUSVALUE(status,reason)       (Sm_AuthApi_Status_t)(((int)reason << 16) | (int)status)
#define SM_GET_STATUS(statusvalue)                   (Sm_AuthApi_Status_t)((int)statusvalue & 0x0000ffff)
#define SM_GET_REASON(statusvalue)                   (Sm_Api_Reason_t)(((int)statusvalue & 0xffff0000) >> 16)


/*
// authentication API query codes
*/
enum Sm_AuthApi_QueryCode_t
{
/* request the description (returned in the status buffer) and the version (returned in the status code) */
Sm_AuthApi_QueryDescription = 0

/*
// request the requred credentials and redirect location. The required credentials will be returned in
// the status code as one of the values in the Sm_Api_Credentials_t enum.  The redirect location will be
// returned in the status buffer.
*/
,Sm_AuthApi_QueryCredentialsReq = 1
};


/*
// size of the query status bufer
*/
#define Sm_AuthApi_StatusBufSize   1024


/*
// return values
//
// Sm_AuthApi_Success
// Sm_AuthApi_Failure
//
*/

typedef enum Sm_AuthApi_Status_t (SM_EXTERN *Sm_AuthApi_Query_t)
(
const char* lpszParam,                  /* parameter (null-terminated) */
const char* lpszSharedSecret,           /* shared secret (null-terminated) */
const enum Sm_AuthApi_QueryCode_t code,      /* query code */
char* lpszStatusBuffer,                 /* status buffer to hold the null-terminated string */
int* lpnStatusCode                      /* status code */
);


/*
// Authentication scheme providers are responsible for defining these
// entry points as well as documenting their use of credentials.
*/

/*
// return values
//
// Sm_AuthApi_Success
// Sm_AuthApi_Failure
//
*/
typedef enum Sm_AuthApi_Status_t (SM_EXTERN *Sm_AuthApi_Init_t)
(
const char* lpszParam,                  /* parameter (null-terminated) */
const char* lpszSharedSecret            /* shared secret (null-terminated) */
);


/*
// return values
//
// Sm_AuthApi_Success
// Sm_AuthApi_Failure
//
*/
typedef enum Sm_AuthApi_Status_t (SM_EXTERN *Sm_AuthApi_Release_t)
(
    const char* lpszParam,                  /* parameter (null-terminated) */
    const char* lpszSharedSecret            /* shared secret (null-terminated) */
);


/*
// V3-compliant interface
//
// return values are constructed using the SM_MAKEAUTH_STATUSVALUE macro
// returning a status only (Sm_AuthApi_Status_t value) is allowed
//
// Sm_AuthApi_Accept
// Sm_AuthApi_Reject
// Sm_AuthApi_Challenge
// Sm_AuthApi_Attempt
// Sm_AuthApi_Failure
// Sm_AuthApi_NoUserContext
// Sm_AuthApi_Success
// Sm_AuthApi_SuccessUserDN
//
*/
typedef enum Sm_AuthApi_Status_t (SM_EXTERN *Sm_AuthApi_Authenticate_t)
(
const Sm_Api_Context_t*                 lpApiContext,           /* the structure that provides API context */
const Sm_Api_UserContext_t*             lpUserContext,          /* the structure that provides user context */
const Sm_AuthApi_UserCredentials_t*     lpUserCredentials,      /* the structure that provides user credentials */
const enum Sm_Api_Reason_t                   nChallengeReason,       /* the reason for the original challenge; 0 otherwise */
const char*                             lpszParam,              /* the parameter to be passed to the server (null-terminated) */
const char*                             lpszSharedSecret,       /* the sharedsecret to be passed to the server (null-terminated) */
const int                               nBytesUserMsg,          /* maximum size of the user message buffer */
char*                                   lpszUserMsg,            /* output buffer to hold the null-terminated user message */
const int                               nBytesErrMsg,           /* maximum size of the error buffer */
char*                                   lpszErrMsg              /* output buffer to hold the null-terminated error message */
);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  SiteMinder Active Expression API               ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/*
// returns supported version number, does something, does something else
*/

#define Sm_ActiveExprApi_QueryVersion_FuncName "SmQueryVersion"

typedef int (SM_EXTERN *Sm_ActiveExprApi_QueryVersion_t)
(
const Sm_Api_Context_t*         lpApiContext
);


/*
// V3-compliant interface
//
// 'active expression' = <@ lib="<Lib-Spec>" func="<Function-Spec>" param="<Param-String>" @>
//
// If the function succeeds, the return value should be the number of characters in the output buffer.
// If the function fails, the return value should be -1.
// If the number of characters in the output buffer is zero, the attribute will not be sent.
*/

typedef int (SM_EXTERN *Sm_ActiveExprApi_t)
(
const Sm_Api_Context_t*         lpApiContext,   /* the structure that provides API context */
const Sm_Api_UserContext_t*     lpUserContext,  /* the structure that provides user context */
const Sm_Api_RequestContext_t*  lpReqContext,   /* the structure that provides request context */
const char*                     lpszParam,      /* the parameter string (null-terminated) */
const int                       nBytesOutBuf,   /* the maximum size of the output buffer */
char*                           lpszOutBuf,     /* the output buffer to hold the null-terminated attribute value */
const int                       nBytesErrBuf,   /* the maximum size of the error message buffer */
char*                           lpszErrBuf      /* the output buffer to hold the null-terminated error message */
);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  SiteMinder Directory API                       ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

/* utility functions */
#define Sm_DirApi_FreeString_FuncName                      "SmDirFreeString"
#define Sm_DirApi_FreeStringArray_FuncName                 "SmDirFreeStringArray"

#define Sm_DirApi_Init_FuncName                            "SmDirInit"
#define Sm_DirApi_Release_FuncName                         "SmDirRelease"
#define Sm_DirApi_QueryVersion_FuncName                    "SmDirQueryVersion"

#define Sm_DirApi_InitDirInstance_FuncName                 "SmDirInitDirInstance"
#define Sm_DirApi_InitUserInstance_FuncName                "SmDirInitUserInstance"

/* directory/user functions */
#define Sm_DirApi_ReleaseInstance_FuncName                 "SmDirReleaseInstance"
#define Sm_DirApi_ValidateInstance_FuncName                "SmDirValidateInstance"
#define Sm_DirApi_GetLastErrMsg_FuncName                   "SmDirGetLastErrMsg"

/* directory functions */
#define Sm_DirApi_GetDirConnection_FuncName                "SmDirGetDirConnection"
#define Sm_DirApi_GetDirObjInfo_FuncName                   "SmDirGetDirObjInfo"
#define Sm_DirApi_Search_FuncName                          "SmDirSearch"
#define Sm_DirApi_SearchCount_FuncName                     "SmDirSearchCount"
#define Sm_DirApi_Enumerate_FuncName                       "SmDirEnumerate"
#define Sm_DirApi_Lookup_FuncName                          "SmDirLookup"
#define Sm_DirApi_ValidateUsername_FuncName                "SmDirValidateUsername"
#define Sm_DirApi_ValidateUserDN_FuncName                  "SmDirValidateUserDN"
#define Sm_DirApi_AddEntry_FuncName                        "SmDirAddEntry"
#define Sm_DirApi_RemoveEntry_FuncName                     "SmDirRemoveEntry"
#define Sm_DirApi_AddMemberToGroup_FuncName                "SmDirAddMemberToGroup"
#define Sm_DirApi_RemoveMemberFromGroup_FuncName           "SmDirRemoveMemberFromGroup"
#define Sm_DirApi_GetGroupMembers_FuncName                 "SmDirGetGroupMembers"
#define Sm_DirApi_AddMemberToRole_FuncName                 "SmDirAddMemberToRole"
#define Sm_DirApi_RemoveMemberFromRole_FuncName            "SmDirRemoveMemberFromRole"
#define Sm_DirApi_GetRoleMembers_FuncName                  "SmDirGetRoleMembers"

/* user functions */
#define Sm_DirApi_AuthenticateUser_FuncName                "SmDirAuthenticateUser"
#define Sm_DirApi_ValidateUserPolicyRelationship_FuncName  "SmDirValidateUserPolicyRelationship"
#define Sm_DirApi_ChangeUserPassword_FuncName              "SmDirChangeUserPassword"
#define Sm_DirApi_GetUserDisabledState_FuncName            "SmDirGetUserDisabledState"
#define Sm_DirApi_SetUserDisabledState_FuncName            "SmDirSetUserDisabledState"

#define Sm_DirApi_GetUserAttr_FuncName                     "SmDirGetUserAttr"
#define Sm_DirApi_GetUserAttrMulti_FuncName                "SmDirGetUserAttrMulti"
#define Sm_DirApi_SetUserAttr_FuncName                     "SmDirSetUserAttr"
#define Sm_DirApi_SetUserAttrMulti_FuncName                "SmDirSetUserAttrMulti"
#define Sm_DirApi_GetUserGroups_FuncName                   "SmDirGetUserGroups"
#define Sm_DirApi_GetUserRoles_FuncName                    "SmDirGetUserRoles"
#define Sm_DirApi_GetUserProperties_FuncName               "SmDirGetUserProperties"
#define Sm_DirApi_GetUserClasses_FuncName                  "SmDirGetUserClasses"


/*
// directory provider capabilities
*/

enum Sm_DirApi_Capability_t
{
 Sm_DirApi_Capability_ForceResetUserPassword  = 0x00000001
,Sm_DirApi_Capability_ChangeUserPassword      = 0x00000002
,Sm_DirApi_Capability_DisableUser             = 0x00000004
,Sm_DirApi_Capability_SetUserAttributes       = 0x00000008
,Sm_DirApi_Capability_Recursive               = 0x00000010
};


/*
// policy resolution
*/

enum Sm_PolicyResolution_t
{                                          /* policy object... */
 Sm_PolicyResolution_Unknown      = 0      /* ...unknown */
,Sm_PolicyResolution_User         = 1      /* ...is the specified user object */
,Sm_PolicyResolution_UserGroup    = 2      /* ...is a member (directly or indirectly through another group) of the specified user group object */
,Sm_PolicyResolution_UserProp     = 3      /* ...matches the specified filter (user scope) */
,Sm_PolicyResolution_UserRole     = 4      /* ...is the occupant of the specified role */
,Sm_PolicyResolution_Org          = 5      /* ...is a member (directly or indirectly through another org) of the specified org object (this supports orgs and org units) */
,Sm_PolicyResolution_Query        = 6      /* ...is contained in the result set of a directory-specific query */
,Sm_PolicyResolution_All          = 7      /* ...is located in the specified directory */
,Sm_PolicyResolution_GroupProp    = 8      /* ...is policy-related to a "group"-like DN matching the specified filter */
,Sm_PolicyResolution_OrgProp      = 9      /* ...is policy-related to a "org"-like DN matching the specified filter */
,Sm_PolicyResolution_DnProp       = 10     /* ...is policy-related to any DN matching the specified filter */

,Sm_PolicyResolution_Max		   = 13 	/* last */
};

static const char *lpszPolicyResolutionNames[] =
{
  (char *) "Unknown"                    /* Sm_PolicyResolution_Unknown */
, (char *) "User"                       /* Sm_PolicyResolution_User */
, (char *) "User Group"                 /* Sm_PolicyResolution_UserGroup */
, (char *) "User Attribute"             /* Sm_PolicyResolution_UserProp */
, (char *) "User Role"                  /* Sm_PolicyResolution_UserProp */
, (char *) "Organization"               /* Sm_PolicyResolution_Org */
, (char *) "Query"                      /* Sm_PolicyResolution_Query */
, (char *) "All"                        /* Sm_PolicyResolution_All */
, (char *) "Group Attribute"            /* Sm_PolicyResolution_GroupProp */
, (char *) "Org Attribute"              /* Sm_PolicyResolution_OrgProp */
, (char *) "DN Attribute"               /* Sm_PolicyResolution_DnProp */
};


typedef void (SM_EXTERN *Sm_DirApi_FreeString_t)
(
char*                           lpszString
);

typedef void (SM_EXTERN *Sm_DirApi_FreeStringArray_t)
(
char**                           lpszStringArray
);


/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_Init_t)
(
const Sm_Api_Context_t*         lpApiContext,
void**                          ppHandle,
const char*                     lpszParameter
);


typedef void (SM_EXTERN *Sm_DirApi_Release_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle
);

/* returns supported version number and capabilities */
typedef int (SM_EXTERN *Sm_DirApi_QueryVersion_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
unsigned long*                  pnCapabilities
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_InitDirInstance_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void**                          ppInstanceHandle,
const char*                     lpszUniqueKey,
const char*                     lpszParameter,
const char*                     lpszUsername,
const char*                     lpszPassword,
const int                       bRequireCredentials,
const int                       bSecureConnection,
const int                       nSearchResults,
const int                       nSearchTimeout
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_InitUserInstance_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void**                          ppInstanceHandle,
void*                           pDirInstanceHandle,
const char*                     lpszUserDN
);

typedef void (SM_EXTERN *Sm_DirApi_ReleaseInstance_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_ValidateInstance_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle
);

typedef char* (SM_EXTERN *Sm_DirApi_GetLastErrMsg_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle
);

typedef void* (SM_EXTERN *Sm_DirApi_GetDirConnection_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetDirObjInfo_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszObject,
char**                          lpszDN,
char**                          lpszClass,
int*                            pnSmPolicyResolution
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_Search_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
char***                         lpszDNs,
const char*                     lpszSearchFilter,
const char*                     lpszSearchRoot,
const int                       nSearchResults,
const int                       nSearchTimeout,
const int                       nSearchScope
);


/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_SearchCount_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
int*                            pnCount,
const char*                     lpszSearchFilter,
const char*                     lpszSearchRoot,
const int                       nSearchResults,
const int                       nSearchTimeout,
const int                       nSearchScope
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_Enumerate_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
char***                         lpszDNs,
char***                         lpszClasses
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
//
// search expression grammar for 'lpszPattern':
//
// [<class> =] <value>
//
// <class> = empty-string | user | group (empty-string implies user & group)
// <value> = wildcarded-string
*/
typedef int (SM_EXTERN *Sm_DirApi_Lookup_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszPattern,
char***                         lpszDNs,
char***                         lpszClasses
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_ValidateUsername_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUsername,
char**                          lpszNewUsername
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_ValidateUserDN_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
//
// Valid entry types:
//
// Sm_PolicyResolution_Unknown
// Sm_PolicyResolution_User
// Sm_PolicyResolution_UserGroup
// Sm_PolicyResolution_UserRole
// Sm_PolicyResolution_Org
*/
typedef int (SM_EXTERN *Sm_DirApi_AddEntry_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const enum Sm_PolicyResolution_t     nEntryType,
const char*                     lpszEntryDN,
const char**                    lpszAttrNames,
const char**                    lpszAttrValues
);


/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_RemoveEntry_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const enum Sm_PolicyResolution_t     nEntryType,
const char*                     lpszEntryDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_AddMemberToGroup_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszMemberDN,
const char*                     lpszGroupDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_RemoveMemberFromGroup_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszMemberDN,
const char*                     lpszGroupDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetGroupMembers_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszGroupDN,
char***                         lpszMembers
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_AddMemberToRole_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszMemberDN,
const char*                     lpszRoleDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_RemoveMemberFromRole_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszMemberDN,
const char*                     lpszRoleDN
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetRoleMembers_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszRoleDN,
char***                         lpszMembers
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_AuthenticateUser_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszPassword,
enum Sm_Api_Reason_t*                pnReason,
char**                          lpszUserMsg,
char**                          lpszErrMsg
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_ValidateUserPolicyRelationship_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const enum Sm_PolicyResolution_t     nPolicyResolution,
const int                       bRecursive,
const char*                     lpszPolicyDN,
const char*                     lpszPolicyClass
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_ChangeUserPassword_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszOldPassword,
const char*                     lpszNewPassword,
const char*                     lpszPasswordAttr,
const int                       bDoNotRequireOldPassword
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserDisabledState_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszDisabledAttr,
enum Sm_Api_DisabledReason_t*        pnDisabledReason
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_SetUserDisabledState_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszDisabledAttr,
const enum Sm_Api_DisabledReason_t   nDisabledReason
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserAttr_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszAttrName,
char**                          lpszAttrData
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserAttrMulti_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszAttrName,
char***                         lpszAttrData
);


/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_SetUserAttr_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszAttrName,
const char*                     lpszAttrData
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_SetUserAttrMulti_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const char*                     lpszAttrName,
const char**                    lpszAttrData
);


/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserGroups_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const int                       bRecursive,
char***                         lpszGroups
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserRoles_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
char***                         lpszRoles
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserProperties_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
const int                       bMandatory,
char***                         lpszProperties
);

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_DirApi_GetUserClasses_t)
(
const Sm_Api_Context_t*         lpApiContext,
void*                           pHandle,
void*                           pInstanceHandle,
const char*                     lpszUserDN,
char***                         lpszClasses
);


/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  SiteMinder Tunnel Service API                  ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/

#define Sm_TunnelApi_Init_FuncName               "SmTunnelInit"
#define Sm_TunnelApi_Release_FuncName            "SmTunnelRelease"
#define Sm_TunnelApi_QueryVersion_FuncName       "SmQueryVersion"

/*
// Tunnel context structure
*/

typedef struct
{
char* lpszClientIp;
char* lpszTransactionId;
char* lpszParameter;
} Sm_Api_TunnelContext_t;

/*
// If the function succeeds, the return value is 0
// If the function fails, the return value is -1
*/
typedef int (SM_EXTERN *Sm_TunnelApi_Init_t)
(
void**                          ppServiceHandle,
const Sm_Api_Context_t*         lpApiContext,
const int                       nBytesStatusBuf,
char*                           lpszStatusBuf
);

typedef void (SM_EXTERN *Sm_TunnelApi_Release_t)
(
void*                           pServiceHandle,
const Sm_Api_Context_t*         lpApiContext
);

/* returns supported version number */
typedef int (SM_EXTERN *Sm_TunnelApi_QueryVersion_t)
(
const Sm_Api_Context_t*         lpApiContext
);

/*
// V4-compliant interface
//
// If the function succeeds, the return value should be the number of bytes in the output buffer.
// If the function fails, the return value should be -1.
//
// The status buffer will be sent back if populated by the API
*/

typedef int (SM_EXTERN *Sm_TunnelApi_t)
(
void*                           pServiceHandle,
const Sm_Api_Context_t*         lpApiContext,
const Sm_Api_RequestContext_t*  lpReqContext,
const Sm_Api_TunnelContext_t*   lpTunnelContext,
const int                       nBytesInBuf,
void*                           lpInBuf,
const int                       nBytesOutBuf,
void*                           lpOutBuf,
const int                       nBytesStatusBuf,
char*                           lpszStatusBuf
);



/*
/////////////////////////////////////////////////////////////////////////
////                                                                 ////
////                  SiteMinder DMS Workflow API                    ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
*/


/*
// API entry points
*/
#define Sm_DmsWorkflowApi_Init_FuncName            "SmDmsWorkflowInit"
#define Sm_DmsWorkflowApi_Release_FuncName         "SmDmsWorkflowRelease"
#define Sm_DmsWorkflowApi_Preprocess_FuncName      "SmDmsWorkflowPreprocess"
#define Sm_DmsWorkflowApi_Postprocess_FuncName     "SmDmsWorkflowPostprocess"

/*
// Get a Directory Object Attribute, given the object DN
//
// If the function succeeds, the return value is the number of characters in the output buffer.
// If the function fails, the return value is -1.
*/

typedef int (SM_EXTERN *Sm_Api_GetDmsDnProp)
(
const void*             lpParam,            /* the function parameter */
const char*             lpszDN,             /* the DN of the object */
const char*             lpszPropName,       /* the name of the object property (null-terminated) */
const int               nBytesValueBuf,     /* the maximum size of the object property buffer */
char*                   lpszValueBuf        /* the output buffer to hold the null-terminated object property */
);

/*
// dms directory context structure
*/

typedef struct
{
unsigned char           bIsUserContext;      /* the 'user context available?' flag */
char*                   lpszAdminUserName;  /* the admin user DN (null-terminated) */
char*                   lpszAdminUserPath;  /* the path to the admin user object (null-terminated) */
char*                   lpszDirPath;        /* the path to the directory (null-terminated) */
void*                   lpReserved1;        /* reserved */
char*                   lpszDirServer;      /* the directory server */
char*                   lpszDirNamespace;   /* the directory namespace */
char*                   lpszSessionId;      /* the session id */
void*                   lpDirParam;         /* the fGetDnProp function parameter */
void*                   lpAdminParam;       /* the fGetAdminProp function parameter */
Sm_Api_GetUserProp      fGetAdminProp;      /* the function to call to retrieve properties of administrator*/
Sm_Api_GetDmsDnProp     fGetDnProp;         /* the function to call to retrieve properties given a DN */
} Sm_Api_DmsContext_t;

/*
// Workflow Object attribute structure, a name/value pair, where value is a string representation
*/
typedef struct
{
const char* lpszAttrName;
const char* lpszAttrValue;
} Sm_DmsWorkflow_Attribute_t;

#define Sm_DmsWorkflow_RoleMemberDnKey "user"   /* name of member DN attribute in membership events */
#define Sm_DmsWorkflow_RoleDnKey "group"        /*  name of group DN attribute in membership events */


/*
// Workflow API return status
*/
enum Sm_DmsWorkflowApi_Status_t
{
 Sm_DmsWorkflowApi_Success = 0           /*  successful completion of this step : proceed */
,Sm_DmsWorkflowApi_Ignore  = 1          /*  event not handled : proceed */
,Sm_DmsWorkflowApi_Failure = 2          /*  workflow processing failure : cancel */
,Sm_DmsWorkflowApi_Reject  = 3          /*  workflow request rejected : cancel */
,Sm_DmsWorkflowApi_NoUserContext = 4    /*  failure due to lack of user information : cancel */
,Sm_DmsWorkflowApi_Pending = 5          /*  workflow response is pending : hold (unsupported, reserve for future use) */
,Sm_DmsWorkflowApi_SkipSuccess = 6		/*  skip processing, no error */
};


/*
// Workflow API providers are responsible for defining these
// entry points.
*/

/*
//	SmDmsWorkflowInit: Set up any required state information, private cache, etc.
//
// return values
// Sm_DmsWorkflowApi_Success
// Sm_DmsWorkflowApi_Failure
//
*/
typedef enum Sm_DmsWorkflowApi_Status_t (SM_EXTERN *Sm_DmsWorkflowApi_Init_t)
(
);


/*
//	SmDmsWorkflowRelease: Free private cache
//
// return values
// Sm_DmsWorkflowApi_Success
// Sm_DmsWorkflowApi_Failure
//
*/
typedef enum Sm_DmsWorkflowApi_Status_t (SM_EXTERN *Sm_DmsWorkflowApi_Release_t)
(
);


/*
//	SmDmsWorkflowPreProcess: Perform workflow custom steps prior to event processing
//
// Return values
// Sm_DmsWorkflowApi_Success
// Sm_DmsWorkflowApi_Failure
// Sm_DmsWorkflowApi_Ignore
// Sm_DmsWorkflowApi_Reject
// Sm_DmsWorkflowApi_NoUserContext
// Sm_DmsWorkflowApi_Pending
// Sm_DmsWorkflowApi_SkipSuccess
//
*/
typedef enum  Sm_DmsWorkflowApi_Status_t (SM_EXTERN *Sm_DmsWorkflowApi_Preprocess_t)
(
const Sm_Api_Context_t*                 lpApiContext,       /* the structure that provides API context */
const Sm_Api_DmsContext_t*              lpDmsContext,       /* the structure that provides DMS directory context */
const char *                            lpszWorkflowOid,    /* the workflow unique object ID */
const int                               nCategoryId,        /* event category ID*/
const int                               nEventId,           /* event ID */
const char *                            lpszObjectPath,     /* target object path */
const int                               nAttributes,        /* number of name/value property pairs */
const Sm_DmsWorkflow_Attribute_t*       pAttributes,        /* attributes associated with the target object/event */
const int                               nBytesErrMsg,       /* maximum size of the error buffer */
char*                                   lpszErrMsg          /* output buffer to hold the null-terminated error message */
);



/*
//	SmDmsWorkflowPostProcess: Perform workflow custom steps following successful event processing
//
// Return values
// Sm_DmsWorkflowApi_Success
// Sm_DmsWorkflowApi_Failure
// Sm_DmsWorkflowApi_Ignore
// Sm_DmsWorkflowApi_Reject
// Sm_DmsWorkflowApi_NoUserContext
//
*/
typedef enum Sm_DmsWorkflowApi_Status_t (SM_EXTERN *Sm_DmsWorkflowApi_Postprocess_t)
(
const Sm_Api_Context_t*                 lpApiContext,       /* the structure that provides API context */
const Sm_Api_DmsContext_t*              lpDmsContext,       /* the structure that provides DMS directory context */
const char *                            lpszWorkflowOid,    /* the workflow unique object ID */
const int                               nCategoryId,        /* event category ID*/
const int                               nEventId,           /* event ID */
const char *                            lpszObjectPath,     /* target object path */
const int                               nAttributes,        /* number of name/value attribute pairs */
const Sm_DmsWorkflow_Attribute_t*       pAttributes,        /* attributes associated with the target object/event */
const int                               nBytesErrMsg,       /* maximum size of the error buffer */
char*                                   lpszErrMsg          /* output buffer to hold the null-terminated error message */
);


#endif
