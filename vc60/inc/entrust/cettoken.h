/*******************************************************************************
 * cettoken.h - Hardware Security Token Support Functions
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef CETTOKEN_H
#define CETTOKEN_H
  
#if !defined( ENTAPI )
#include <entbdefs.h> 
#else
#include <toolkit/entapi/tkbdefs.h>
#endif 

/*      
   The token support functions will typically be called before creating
   an Entrust user context (via a call to ETLogin), in order to 
   determine if security tokens are present on the current system. 
   If so, the functions defined below can be used to determine, on a per
   token basis, the capabilities and user profiles they support.
   
   User profile names obtained from tokens can then be used
   in the ETLogin function to login with a token-based profile.
*/

#ifdef __cplusplus
extern "C" {
#endif                                                        
            
#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

/*
   Get the total number of user profiles defined on all available tokens.
*/                                               
ETEXPORT32 INT16 ETEXPORT ETGetNumberOfTokenProfiles(const char* entrustIniFile);
/*
   Get the token-based user profile name specified by index.
   The string copied to profile will be at most MAX_NAME_SIZE long.
*/
ETEXPORT32 EntLog ETEXPORT ETGetTokenProfileName(const char* entrustIniFile,
											 const SYSINT index,
											 char* profile); 
/*
   For the token associated with the specified profile, get:
   - a text string describing the token type
   - the slot number of the token
   The string copied to tokenString will be at most MAX_ENTSTR_SIZE long.
*/                                               
ETEXPORT32 EntLog ETEXPORT ETGetTokenProfileInfo(	const char* entrustIniFile,
												const char* profile, 
												char* tokenString, 
												INT16* slot);

/*
   Change the directory path information associated with the indexed 
   token based user profile. Though the actual profile is stored on the
   token, the path information prefixing it must point to a valid 
   file system directory, which is used as the location for supplementary
   files, such as personal address books and cache files.
   This function allows the path information stored on the token to be
   updated, for example, if the user has moved to a different system and
   the supplementary files location is different.
   The path parameter should be fully qualified, but should NOT be terminated
   with a "\". For example setting path to "D:\entrust\myfiles" is valid,
   where myfiles is a directory name.
   
*/                                               
ETEXPORT32 EntLog ETEXPORT ETSetTokenProfilePath(	const char* entrustIniFile, 
												const SYSINT index, 
												const char* path);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* CETTOKEN_H */
