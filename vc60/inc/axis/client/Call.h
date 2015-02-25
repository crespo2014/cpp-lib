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
 *
 */
/**
 * @file Call.hpp
 *
 * This file Contains the Call class and equivalent C function tables
 * that all web service stubs generated by WSDL2Ws tool use to talk
 * to Axis Engine.
 *
 */
#ifndef CALL_INCLUDED
#define CALL_INCLUDED

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


#include <axis/GDefine.h>
#include <axis/TypeMapping.h>
#include <axis/AxisUserAPI.h>
#include <axis/AxisUserAPIArrays.h>
#include <axis/WSDDDefines.h>
#include <axis/IHeaderBlock.h>

/* A separate call class object should be used by each thread */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateCall();
AXISC_STORAGE_CLASS_INFO void axiscDestroyCall(AXISCHANDLE call);
AXISC_STORAGE_CLASS_INFO void axiscSetSOAPVersion(AXISCHANDLE call, AXISC_SOAP_VERSION version);
AXISC_STORAGE_CLASS_INFO int axiscSetTransportPropertyCall(AXISCHANDLE call, AXISC_TRANSPORT_INFORMATION_TYPE type, 
	const char * value);
AXISC_STORAGE_CLASS_INFO const char * axiscGetTransportPropertyCall(AXISCHANDLE call, const char * key, 
	AxiscBool response);
AXISC_STORAGE_CLASS_INFO int axiscSetHandlerPropertyCall(AXISCHANDLE call, AxiscChar * name, 
	void * value, int len);

/**
	 * set the protocol that the underlying transport will use. 
	 * If there is not transport set then the transport protocol is stored locally until there is a transport.
	 * 
	 * @param protocol the protocol that you want. Allowed values are  defined in GDefine.hpp AXIS_PROTOCOL_TYPE
	 * @return AXIS_SUCCESS if the protocol was set correctly in the underlying transport or, if there is no transport then the value was stored safely.
	 */
AXISC_STORAGE_CLASS_INFO int axiscSetProtocol(AXISCHANDLE call, AXISC_PROTOCOL_TYPE protocol);

/**
     * Get the protocol that the transport is or will use.
     * @return the transport protocol being used.
     */
AXISC_STORAGE_CLASS_INFO AXISC_PROTOCOL_TYPE axiscGetProtocol(AXISCHANDLE call);
AXISC_STORAGE_CLASS_INFO int axiscUnInitialize(AXISCHANDLE call);
AXISC_STORAGE_CLASS_INFO int axiscInitializeCall(AXISCHANDLE call, AXISC_PROVIDERTYPE nStyle);
AXISC_STORAGE_CLASS_INFO int axiscInvoke(AXISCHANDLE call);

/**
     * Sets an Attribute to the SOAPMethod, using the given Attribute data.
     * You must ensure the prefix has a valid namespace declared, otherwise an
     * invalid SOAP message will be produced.
     * It is safer to use setSOAPMethodAttribute(const AxisChar *pLocalname, const AxisChar *pPrefix, const AxisChar* pUri, const AxisChar *pValue)
     * 
     * @param pLocalname The local name of the Attribute.
     * @param pPrefix The prefix of the Attribute.
     * @param pValue The value of the Attribute.
     */

/**
     * Sets an Attribute to the SOAPMethod, using the given Attribute data.
     *
     * @param pLocalname The local name of the Attribute.
     * @param pPrefix The prefix of the Attribute.
     * @param pUri The namespace uri of the Attribute.
     * @param pValue The value of the Attribute.
     */
AXISC_STORAGE_CLASS_INFO void axiscSetSOAPMethodAttribute(AXISCHANDLE call, const AxiscChar * pLocalname, 
	const AxiscChar * pPrefix, const AxiscChar * pUri, 
	const AxiscChar * pValue);

/* Method for adding complex parameters */
AXISC_STORAGE_CLASS_INFO void axiscAddCmplxParameter(AXISCHANDLE call, void * pObject, 
	void * pSZFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Method for adding complex type array parameters */
AXISC_STORAGE_CLASS_INFO void axiscAddCmplxArrayParameter(AXISCHANDLE call, Axisc_Array * pArray, 
	void * pSZFunct, void * pDelFunct, void * pSizeFunct, 
	const AxiscChar * pName, const AxiscChar * pNamespace);

/* Method for adding basic type array parameters */
AXISC_STORAGE_CLASS_INFO void axiscAddBasicArrayParameter(AXISCHANDLE call, Axisc_Array * pArray, 
	AXISC_XSDTYPE nType, const AxiscChar * pName);

/* Method for adding parameters of basic types */
AXISC_STORAGE_CLASS_INFO void axiscAddParameter(AXISCHANDLE call, void * pValue, 
	const char * pchName, AXISC_XSDTYPE nType);

/**
	 * Adds an attachment and references it from a parameter in the SOAP body. Axis C++ will delete the storage for
	 * the ISoapAttachment and IAttributes passed to this method during ~Call.
	 * 
	 * @param attachment The attachment to add to the MIME message, referenced from the SOAP body (mandatory)
	 * @param pName The name of the parameter (mandatory)
	 * @param attributes An array of pointers to attributes that will be added to the attachment reference in the 
	 * SOAP body (optional)
	 * @param nAttributes The number of elements in the attributes array
	 */
AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentParameter(AXISCHANDLE call, AXISCHANDLE attachment, 
	const char * pName, AXISCHANDLE attributes, int nAttributes);

/**
	 * Creates an IAttribute that can be used on an attachment reference on Call::addAttachmentParameter.
	 * If this IAttribute is subsequently passed to Call::addAttachmentParameter, Axis C++ will delete the storage 
	 * associated with the IAttribute during ~Call.
     * You must ensure the prefix has a valid namespace declared, otherwise an invalid SOAP message will be produced.
     * 
     * @param pLocalname The local name of the Attribute.
     * @param pPrefix The prefix of the Attribute.
     * @param pValue The value of the Attribute.
     */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateAttributeCall(AXISCHANDLE call, const AxiscChar * pLocalname, 
	const AxiscChar * pPrefix, const AxiscChar * pValue);

/* Method that set the remote method name */
AXISC_STORAGE_CLASS_INFO void axiscSetOperation(AXISCHANDLE call, const char * pchOperation, 
	const char * pchNamespace);
AXISC_STORAGE_CLASS_INFO int axiscSetEndpointURI(AXISCHANDLE call, const char * pchEndpointURI);
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateHeaderBlock(AXISCHANDLE call, AxiscChar * pachLocalName, 
	AxiscChar * pachUri, AxiscChar * pachPrefix);

/* Methods used by stubs to get a deserialized value of XML element
     * as basic types
     */
AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetElementAsIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetElementAsBooleanCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetElementAsUnsignedIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetElementAsShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetElementAsUnsignedShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetElementAsByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetElementAsUnsignedByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetElementAsLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetElementAsIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetElementAsUnsignedLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetElementAsFloatCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetElementAsDoubleCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetElementAsDecimalCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetElementAsStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetElementAsAnyURICall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetElementAsQNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetElementAsHexBinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetElementAsBase64BinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetElementAsDateTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetElementAsDateCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetElementAsTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetElementAsDurationCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gYearMonth * axiscGetElementAsGYearMonthCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gYear * axiscGetElementAsGYearCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gMonthDay * axiscGetElementAsGMonthDayCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gDay * axiscGetElementAsGDayCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gMonth * axiscGetElementAsGMonthCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__nonPositiveInteger * axiscGetElementAsNonPositiveIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__negativeInteger * axiscGetElementAsNegativeIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__nonNegativeInteger * axiscGetElementAsNonNegativeIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__positiveInteger * axiscGetElementAsPositiveIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__normalizedString axiscGetElementAsNormalizedStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__token axiscGetElementAsTokenCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__language axiscGetElementAsLanguageCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__Name axiscGetElementAsNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NCName axiscGetElementAsNCNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ID axiscGetElementAsIDCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__IDREF axiscGetElementAsIDREFCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__IDREFS axiscGetElementAsIDREFSCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ENTITY axiscGetElementAsENTITYCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ENTITIES axiscGetElementAsENTITIESCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NMTOKEN axiscGetElementAsNMTOKENCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NMTOKENS axiscGetElementAsNMTOKENSCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NOTATION axiscGetElementAsNOTATIONCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Methods used by stubs to get a deserialized value of a XML attribute
     * as basic types
     */
AXISC_STORAGE_CLASS_INFO xsdc__int * axiscGetAttributeAsIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__boolean * axiscGetAttributeAsBooleanCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedInt * axiscGetAttributeAsUnsignedIntCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__short * axiscGetAttributeAsShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedShort * axiscGetAttributeAsUnsignedShortCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__byte * axiscGetAttributeAsByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedByte * axiscGetAttributeAsUnsignedByteCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__long * axiscGetAttributeAsLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__integer * axiscGetAttributeAsIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__unsignedLong * axiscGetAttributeAsUnsignedLongCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__float * axiscGetAttributeAsFloatCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__double * axiscGetAttributeAsDoubleCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__decimal * axiscGetAttributeAsDecimalCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__string axiscGetAttributeAsStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__anyURI axiscGetAttributeAsAnyURICall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__QName axiscGetAttributeAsQNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__hexBinary * axiscGetAttributeAsHexBinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__base64Binary * axiscGetAttributeAsBase64BinaryCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__dateTime * axiscGetAttributeAsDateTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__date * axiscGetAttributeAsDateCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__time * axiscGetAttributeAsTimeCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__duration * axiscGetAttributeAsDurationCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gYearMonth * axiscGetAttributeAsGYearMonthCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gYear * axiscGetAttributeAsGYearCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gMonthDay * axiscGetAttributeAsGMonthDayCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gDay * axiscGetAttributeAsGDayCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__gMonth * axiscGetAttributeAsGMonthCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NOTATION axiscGetAttributeAsNOTATIONCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__normalizedString axiscGetAttributeAsNormalizedStringCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__token axiscGetAttributeAsTokenCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__language axiscGetAttributeAsLanguageCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__Name axiscGetAttributeAsNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NCName axiscGetAttributeAsNCNameCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ID axiscGetAttributeAsIDCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__IDREF axiscGetAttributeAsIDREFCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__IDREFS axiscGetAttributeAsIDREFSCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ENTITY axiscGetAttributeAsENTITYCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__ENTITIES axiscGetAttributeAsENTITIESCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NMTOKEN axiscGetAttributeAsNMTOKENCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__NMTOKENS axiscGetAttributeAsNMTOKENSCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__nonPositiveInteger * axiscGetAttributeAsNonPositiveIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__negativeInteger * axiscGetAttributeAsNegativeIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__nonNegativeInteger * axiscGetAttributeAsNonNegativeIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO xsdc__positiveInteger * axiscGetAttributeAsPositiveIntegerCall(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Method used by stubs to get a deserialized value of complex types */
AXISC_STORAGE_CLASS_INFO void * axiscGetCmplxObjectCall(AXISCHANDLE call, void * pDZFunct, 
	void * pCreFunct, void * pDelFunct, const AxiscChar * pName, 
	const AxiscChar * pNamespace);

/* Method used by stubs to get a deserialized Array of complex types */
AXISC_STORAGE_CLASS_INFO Axisc_Array * axiscGetCmplxArrayCall(AXISCHANDLE call, Axisc_Array * pArray, 
	void * pDZFunct, void * pCreFunct, void * pDelFunct, 
	void * pSizeFunct, const AxiscChar * pName, const AxiscChar * pNamespace);

/* Method used by stubs to get a deserialized Array of basic types */
AXISC_STORAGE_CLASS_INFO Axisc_Array * axiscGetBasicArrayCall(AXISCHANDLE call, AXISC_XSDTYPE nType, 
	const AxiscChar * pName, const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscCheckMessage(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO void * axiscCheckFault(AXISCHANDLE call, const AxiscChar * pName, 
	const AxiscChar * pNamespace);
AXISC_STORAGE_CLASS_INFO int axiscGetStatusCall(AXISCHANDLE call);

/**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
AXISC_STORAGE_CLASS_INFO void axiscSetProxyCall(AXISCHANDLE call, const char * pcProxyHost, 
	unsigned int uiProxyPort);
AXISC_STORAGE_CLASS_INFO AxiscAnyType * axiscGetAnyObjectCall(AXISCHANDLE call);
AXISC_STORAGE_CLASS_INFO int axiscAddAnyObject(AXISCHANDLE call, AxiscAnyType * pAnyObject);

/**
	 * Returns the prefix for a previously defined namespace. If the 
	 * namespace has not previously been associated with a prefix, it
	 * creates a new prefix, which is unique and returns that. It will
	 * only return prefixes for user-defined namespaces, so passing a 
	 * standard namespace will cause a new prefix to be created.
	 * 
	 * @param pNamespace the namespace to look for
	 * @return the prefix for this namespace
	 */
AXISC_STORAGE_CLASS_INFO const AxiscChar * axiscGetNamespacePrefixCall(AXISCHANDLE call, const AxiscChar * pNamespace);

/**
	 * Returns a complex fault as an XML string 
	 */
AXISC_STORAGE_CLASS_INFO const xsdc__string axiscGetFaultAsXMLString(AXISCHANDLE call);

/**
	 * Adds an attachment to the MIME message. This attachment will not be referenced from the SOAP body. The storage
	 * associated with the ISoapAttachment will be deleted during ~Call.
	 * 
	 * @param objAttach the attachment to add to the message.
	 */
AXISC_STORAGE_CLASS_INFO void axiscAddAttachmentCall(AXISCHANDLE call, AXISCHANDLE objAttach);

/**
	 * Creates an ISoapAttachment which represents an attachment. The ISoapAttachment can be passed to addAttachment
	 * or addAttachmentParameter. The attachment will not be added to the message unless it is subsequently passed to
	 * addAttachment or addAttachmentParameter. The storage associated with the ISoapAttachment will not be 
	 * automatically deleted by Axis C++ unless it is passed to addAttachment or addAttachmentParamater.
	 */
AXISC_STORAGE_CLASS_INFO AXISCHANDLE axiscCreateSoapAttachmentCall(AXISCHANDLE call);

// clean memeory in case of exceptions and destructor etc.


/*
       Following are pointers to relevant objects of the ClientAxisEngine
       instance. So they do not belong to this object and are not created
       or deleted
     */
/*
       Transport object
     */
/* Minimal error check */
/**
    * Proxy server name.
    */
/**
    * Proxy server port.
    */
/**
    * Use Proxy or not?
    */
/**
    * To track if the initialize was called/matched with an uninitialize
    */
// Samisa m_pchSessionID was misssing and there was a compile error due to this


#ifdef __cplusplus
 }
#endif

#endif /* CALL_INCLUDED */