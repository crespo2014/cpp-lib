#pragma once

/*=========================================================================+

   Name:
      ExitXMLBlock.h

   Abstract:
      This class provides sample methods to manipulate the Exit argument and
	  results blocks which are encoded in XML.  You may need to extend this
	  class with additional methods depending on what data you need to pass
	  in arguments or results from your program exits.

      The methods here call upon functions of the MSXML toolkit
	  to manipuate the XML data.

	  See comments in ExitXMLBlock.cpp for method invocation usage.

   Created:
      08/12/03

   Notes:

+=========================================================================*/

#ifndef __EXITXMLBLOCK_H__
#define __EXITXMLBLOCK_H__

#include <string>
#include <vector>
#include <list>
#include "eTrustSDK\Opt\src\ecs\include\eCSutf8.h"

using namespace std;
using std::string;

typedef vector<string>	vectorOfStrings;

// Xerces-C++
#include "xercesc\util\PlatformUtils.hpp"
#include "xercesc\dom\DOM.hpp"


#define MAX_MSG_LEN					4096

// From ldap.h
#define LDAP_SUCCESS				0x00
#define LDAP_OPERATIONS_ERROR		0x01

typedef enum {
	E_SUCCESS,
	E_WARNING,
	E_FAILURE
} STATUS_T;

typedef enum {
	AUTHTYPE_NONE,
	AUTHTYPE_GLOBAL_USER,
	AUTHTYPE_PROXY_USER,
	AUTHTYPE_PROXY_OTHER
} AUTHTYPE_T;




class ExitXMLBlock
{
public:
	ExitXMLBlock(
			string		sInputXML
		);

	~ExitXMLBlock();

	virtual void Add_Function_Return_Value(
			string		sValue
		);

	virtual void Build_Return_XML(
			STATUS_T	tStatus,
			bool		bContinueEtaExecution,
			string		sLogMessage,
			string &	sReturnXML,						// OUT
			int			iMaxReturnLength,
			bool		bObscureValue = false
		);

	/*
	|| Get methods
	*/
	string Get_Attribute_Name(
			int			iIndex = 0
		) const;

	string Get_Attribute_Value(
			string		sAttribute,
			int			iValueIndex	= 0
		) const;

	string Get_Authentication_Password() const;

	AUTHTYPE_T Get_Authentication_Type() const;

	string Get_Authentication_User() const;

	string Get_Exit_Type() const;

	string Get_Function_Parameter(
			int			iParamNumber,
			int			iParamIndex		= 0
		) const;

	string Get_Object_DN() const;

	string Get_Object_Name() const;

	string Get_Object_Class() const;

protected:
	static int Convert_To_LDAP_Status(
			STATUS_T		tStatus
		);

	static string Convert_Status_To_Category_String(
			STATUS_T		tStatus
		);

	static AUTHTYPE_T Convert_Authentication_Type_String_to_Enum(
			string			sType
		);

	/*
	|| XML parsing methods
	*/
	virtual int Parse_ETA_Input_XML();

	virtual void Parse_Object_Block(
			string		sBlockName
		);

	virtual void Parse_Authentication_Block(
			string		sBlockName
		);

public:
	/*
	|| Alternate XML Block parsing methods
	*/
	virtual int Parse_Block(
			string		sBlockName
		);

	string Get_Block_Attribute_Name(
			int			iIndex = 0
		) const;

	string Get_Block_Attribute_Value(
			string		sAttribute,
			int			iValueIndex	= 0
		) const;

protected:
	/*
	|| XML base methods
	*/
	virtual int Add_Element(
			XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*	pDocument,
			XERCES_CPP_NAMESPACE_QUALIFIER DOMElement*	pParentElement,
			string			sTag,
			string			sValue,
			string			sTagAttribute			= "",
			string			sTagAttributeValue		= ""
		);

	virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMNodeList* Find_Node(
			XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*	pDocument,
			string			sTag,
			bool			bFindMultipleNodes	= true
		);

	int Initialize_Transcoder();

	string UTF16toUTF8(
			const XMLCh*	pxcUtf16String
		);

	XMLCh* UTF8toUTF16(
			string			suUtf8String
		);

private:
	static XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* g_pImplementation;

protected:
	/* XML Parsing */
	XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument*		m_pXmlDocument;
	XERCES_CPP_NAMESPACE_QUALIFIER XMLTranscoder*	m_pXmlTranscoder;
	/* XML Writing */
	XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder*		m_pXmlBuilder;
	XERCES_CPP_NAMESPACE_QUALIFIER DOMWriter*		m_pXmlWriter;

	/* Class variables */
	string				m_sInputXML;
	string				m_sExitType;
	/* Object Block data */
	string				m_sObjectClass;
	string				m_sObjectDn;
	string				m_sObjectName;
	vectorOfStrings		m_vsObjectAttributes;
	vectorOfStrings		m_vsObjectValues;
	/* Authentication Block data */
	AUTHTYPE_T			m_sAuthenticationType;
	string				m_sAuthenticationUser;
	string				m_sAuthenticationPassword;
	/* Return XML Payload data */
	vectorOfStrings		m_vsReturnValues;
	/* Parsed block data */
	vectorOfStrings		m_vsBlockAttributeList;		// list of attributes
	vectorOfStrings		m_vsBlockAttributes;
	vectorOfStrings		m_vsBlockValues;
};

#endif // __EXITXMLBLOCK_H__
