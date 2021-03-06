/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#ifndef WRAPPERCLASSHANDLER_INCLUDED
#define WRAPPERCLASSHANDLER_INCLUDED

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* ----------------------------------------------------------------   */
/* THIS HEADER FILE PATTERNED AFTER CORRESPONDING hpp HEADER FILE.    */
/* CHANGES TO hpp HEADER FILE MAY NEED TO BE PROPAGATED HERE AND IN   */
/* THE IMPLEMEMTATION OF THE C APIS.                                  */
/*                                                                    */
/* THIS FILE GENERATED BY CBINDINGGENERATOR TOOL.                     */
/* ----------------------------------------------------------------   */
/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE   */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifdef __cplusplus
 extern "C" {
#endif



/**
 * @class WrapperClassHandler
 * @brief
 *
 */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateWrapperClassHandler();
AXISC_STORAGE_CLASS_INFO void axiscDestroyWrapperClassHandler(AXISCHANDLE wrapperClassHandler);
AXISC_STORAGE_CLASS_INFO AXISC_BINDING_STYLE axiscGetBindingStyle(AXISCHANDLE wrapperClassHandler);
AXISC_STORAGE_CLASS_INFO int axiscGetType(AXISCHANDLE wrapperClassHandler);
AXISC_STORAGE_CLASS_INFO int axiscInit(AXISCHANDLE wrapperClassHandler);

// We do not need init and fini for the service wrapper
AXISC_STORAGE_CLASS_INFO int axiscFini(AXISCHANDLE wrapperClassHandler);


#ifdef __cplusplus
 }
#endif

#endif /* WRAPPERCLASSHANDLER_INCLUDED */
