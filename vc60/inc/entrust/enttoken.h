/*******************************************************************************
 * enttoken.h - Hardware Security Token Support Functions
 *
 * Copyright (c) 1995-2000 Entrust Technologies  All rights reserved.
 ******************************************************************************/

#ifndef ENTTOKEN_H
#define ENTTOKEN_H
  
#if !defined( ENTAPI )
#include <entbdefs.h> 
#else
#include <toolkit/entapi/tkbdefs.h>
#endif 

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

//
// Get the total number of user profiles defined on all available tokens.
//                                               
EXPT32 INT16 EXPT GetNumberOfTokenProfiles(const GString& entrustIniFile);
//
// Get the token-based user profile name specified by index.
//
EXPT32 EntLog EXPT GetTokenProfileName(const GString& entrustIniFile,
									   const SYSINT index, 
									   GString& profile);
//
// For the token associated with the specified profile, get:
// - a text string describing the token type.
// - the slot number of the token
//                                               
EXPT32 EntLog EXPT GetTokenProfileInfo(	const GString& entrustIniFile,
										const GString& profile, 
										GString& tokenString, 
										INT16& slot);
//
// Change the directory path information associated with the indexed 
// token based user profile. Though the actual profile is stored on the
// token, the path information prefixing it must point to a valid 
// file system directory, which is used as the location for supplementary
// files, such as personal address books and cache files.
// This function allows the path information stored on the token to be
// updated, for example, if the user has moved to a different system and
// the supplementary files location is different.
// The path parameter should be fully qualified, but should NOT be terminated
// with a "\". For example setting path to "D:\entrust\myfiles" is valid,
// where myfiles is a directory name.
// 
//                                               
EXPT32 EntLog EXPT SetTokenProfilePath(	const GString& entrustIniFile, 
										const SYSINT index, 
										const GString& path);

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif

