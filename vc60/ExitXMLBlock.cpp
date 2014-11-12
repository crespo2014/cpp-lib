/*=========================================================================+

   Name:
      ExitXMLBlock.cpp

   Abstract:
      This class provides sample methods to manipulate the Exit argument and
	  results blocks which are encoded in XML.  You may need to extend this
	  class with additional methods depending on what data you need to pass
	  in arguments or results from your program exits.

      The methods here call upon functions of Xerces-C++
	  to manipuate the XML data.

   Created:
      08/12/03

   Notes:

+=========================================================================*/

#pragma warning(disable:4786)

#include <stdlib.h>
#include <stdio.h>

// Xerces-C++
#define XERCES_TMPLSINC
#include <xercesc/util/TransService.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>
#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif
XERCES_CPP_NAMESPACE_USE

// EtaXmlDefines defines the XML tags used in the XML argument/results blocks
#include "etrustSDK\Admin\include\EtaXmlDefines.h"

// ExitXMLBlock is a helper class that is used to hide most XML knowledge
#include "ExitXMLBlock.h"

// EtaClass defines attribute names and object class names from the COS namespace
#include "etrustSDK\Admin\include\etaclass.h"


/*-------------------------------------------------------------------------+
	Forward declaration of local functions
+-------------------------------------------------------------------------*/
bool IsInVector(const string sName, vectorOfStrings& vsVector);

/*-------------------------------------------------------------------------+
	Static
+-------------------------------------------------------------------------*/
XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* ExitXMLBlock::g_pImplementation = NULL;


/*-------------------------------------------------------------------------+
   Constructor / Destructor
+-------------------------------------------------------------------------*/

ExitXMLBlock::ExitXMLBlock(
		string		sInputXML
	)
{
	int iRc;

	// xerces-c
	m_pXmlDocument				= NULL;
	m_pXmlTranscoder			= NULL;

	// Initialize member variables.
	m_sInputXML					= sInputXML;
	m_sExitType					= "";
	m_sObjectDn					= "";
	m_sObjectName				= "";
	m_sObjectClass				= "";
	m_sAuthenticationType		= AUTHTYPE_NONE;
	m_sAuthenticationUser		= "";
	m_sAuthenticationPassword	= "";

	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char* pszMessage = XMLString::transcode(toCatch.getMessage());
		cerr << "Error during initialization! :\n" << pszMessage << "\n";
		XMLString::release(&pszMessage);
	}

	// Create UTF-16/UTF-8 conversion transcoder
	Initialize_Transcoder();

	// Get Implementation
	if (ExitXMLBlock::g_pImplementation == NULL) {
		XMLCh* pzcValue = UTF8toUTF16("LS");
		ExitXMLBlock::g_pImplementation = DOMImplementationRegistry::getDOMImplementation(pzcValue);
		delete pzcValue;
	}

	// Initialize XML Parser
	m_pXmlWriter = ExitXMLBlock::g_pImplementation ->createDOMWriter();
	m_pXmlBuilder = ExitXMLBlock::g_pImplementation->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	m_pXmlWriter->setFeature(XMLUni::fgDOMXMLDeclaration, false);
	m_pXmlBuilder->resetDocumentPool();
	m_pXmlDocument = NULL;

	// Parse the input.
	iRc = Parse_ETA_Input_XML();
	if (iRc == 0) {
	}
}

ExitXMLBlock::~ExitXMLBlock()
{
	XMLPlatformUtils::Terminate();
	
	// This was allocated in this object, and there is no corresponding
	// free
	delete m_pXmlBuilder;
}


/*-------------------------------------------------------------------------+
	Public Methods
+-------------------------------------------------------------------------*/

/*=========================================================================+
	Add_Function_Return_Value:
		For custom rule functions, the eTExitCustom tag of the output XML
		block contains the function result(s).  For each value to return,
		the Add_Function_Return_Value() method should be called.

+=========================================================================*/
void
ExitXMLBlock::Add_Function_Return_Value(
		string		sValue
	)
{
	// Append the return value to the return string array
	if (!sValue.empty()) {
		m_vsReturnValues.insert(m_vsReturnValues.end(), sValue);
	}
}


/*=========================================================================+
	Build_Return_XML:
		Build the XML block that eTrust Admin expects the program exit
		to return.

		<eTExitReturn>
			<eTExitReturnCategory></eTExitReturnCategory>
			<eTExitReturnNative></eTExitReturnNative>
			<eTExitContinue></eTExitContinue>
			<eTExitLogMsg></eTExitLogMsg>
			<eTExitCustom></eTExitCustom>
		</eTExitReturn>

	    The return XML buffer provided by eTrust Admin is over 4000 bytes
		long.  There will be no problem fitting the entire output XML
		document into this buffer unless sLogMessage or the custom_msg built
		from the return values array is very long.  Thus, this code attempts
		first to build an XML buffer with all of the provided information
		and if it is too long does the following:
			case 1:  custom_msg is provided
				--> generate a failure exit return block with no custom_msg

			case 2:  sLogMessage is provided, but no custom_msg
				--> replace the very long sLogMessage with a short one.

+=========================================================================*/
void
ExitXMLBlock::Build_Return_XML(
		STATUS_T	tStatus,
		bool		bContinueEtaExecution,
		string		sLogMessage,
		string &	sReturnXML,						// OUT
		int			iMaxReturnLength,
		bool		bObscureValue  // = false
	)
{
	int iRc;
	string	suValue;
	UTF8	pszuValue[32];
	XMLCh*	pxcValue;

	pxcValue = UTF8toUTF16(UTFEXIT_EXITRETURN);
	DOMDocument* pDocument = ExitXMLBlock::g_pImplementation->createDocument(0, pxcValue, 0);
	delete pxcValue;
	DOMElement* pRootElement = pDocument->getDocumentElement();

	// ...eTrust Admin Category.
	suValue = Convert_Status_To_Category_String(tStatus);
	iRc = Add_Element(pDocument, pRootElement, UTFEXIT_EXITRETURNCATEGORY, suValue);

	// ...Program exit return code.
	sprintf(pszuValue, "%d", tStatus);
	iRc = Add_Element(pDocument, pRootElement, UTFEXIT_EXITRETURNNATIVE, pszuValue);

	// ...Should eTrust Admin continue execution?
	suValue = (bContinueEtaExecution ? UTFEXIT_TRUE : UTFEXIT_FALSE);
	iRc = Add_Element(pDocument, pRootElement, UTFEXIT_EXITCONTINUE, suValue);

	// ...Log message.
	if (!sLogMessage.empty()) {
		iRc = Add_Element(pDocument, pRootElement, UTFEXIT_EXITLOGMSG, sLogMessage);
	}

	// ...Custom message (used for return values today; and perhaps for
	// other exit-type specific purposes in the future).
	if (m_vsReturnValues.size() > 0) {
		pxcValue = UTF8toUTF16(UTFEXIT_EXITCUSTOM);
        DOMElement* pElement = pDocument->createElement(pxcValue);
		delete pxcValue;
        pRootElement->appendChild(pElement);

		// Add each return value as <eTFuncReturn>...</eTFuncReturn>
		for (unsigned int iIndex = 0; iIndex <  m_vsReturnValues.size(); iIndex++) {
			if (bObscureValue) {	// add the obscured attribute for passwords
				Add_Element(
					pDocument,
					pElement,
					UTFEXIT_CF_FUNCRETURN,
					m_vsReturnValues[iIndex],
					"obscured",
					"yes");
			} else {
				Add_Element(
					pDocument,
					pElement,
					UTFEXIT_CF_FUNCRETURN,
					m_vsReturnValues[iIndex]);
			}
		}
	}

	// Generate the return XML string
	DOMBuilder* pBuilder;	// Parser
	DOMWriter*	pWriter;	// Serializer

	pWriter = ExitXMLBlock::g_pImplementation->createDOMWriter();
	pBuilder = ExitXMLBlock::g_pImplementation->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	pWriter->setFeature(XMLUni::fgDOMXMLDeclaration, false);
	pBuilder->resetDocumentPool();

	const XMLCh* pxcReturnXML = pWriter->writeToString(*pRootElement);
	sReturnXML = UTF16toUTF8(pxcReturnXML);

	if (pBuilder) {
		delete pBuilder;
	}
	if (pWriter) {
		delete pWriter;
	}
	
	if (pDocument) {
		delete pDocument;
		pDocument = NULL;
	}

	// Check to make sure it isn't too long for the return buffer
	int iLength = sReturnXML.length();
	if (iLength >= iMaxReturnLength) {
		sReturnXML = "";
		sLogMessage = "ERROR: Return XML buffer too long";

		// If too long, and a custom message was provided, fail the
		// call (and consequently do not report an output value).
		if (m_vsReturnValues.size() > 0) {
			m_vsReturnValues.clear();
			tStatus = E_FAILURE;
			bContinueEtaExecution = false;
		}
	}
}

/*=========================================================================+
	Get_Attribute_Name:
		Return the name of the next attribute.  Returns "" when there
		are no more attributes.

		Repeated call with with iIndex = 0, 1, 2, ...
		until returned string is empty.
+=========================================================================*/
string
ExitXMLBlock::Get_Attribute_Name(
		int			iIndex	/* = 0 */
	) const
{
	string	sValue		= "";
	int		iAttrCount	= m_vsObjectAttributes.size();

	if (iAttrCount > 0 && iIndex >= 0 && iIndex < iAttrCount) {
		sValue = m_vsObjectAttributes[iIndex];
	}
	return sValue;
}

/*=========================================================================+
	Get_Attribute_Value:
		Return the value for the specified attribute.

		For multi-valued attributes, call repeated with 
		iValueIndex = 0, 1, 2, ...
		until returned string is empty.
+=========================================================================*/
string
ExitXMLBlock::Get_Attribute_Value(
		string		sAttribute,
		int			iValueIndex			// = 0
	) const
{
	string	sValue		= "";

	for (unsigned int iIndex = 0; iIndex < m_vsObjectAttributes.size(); iIndex++) {
		if (m_vsObjectAttributes[iIndex] == sAttribute) {
			if (iValueIndex-- <= 0) {
				// Found a matching attribute; return the corresponding value.
				sValue = m_vsObjectValues[iIndex];
				break;
			}
		}
	}
	return sValue;
}

/*=========================================================================+
	Get_Authentication_Password/Type/User:
		Returns the data items from the authentication block of the
		input XML block. The authentication block provides credentials
		that the program exit can use to log in to a system or application.
		Depending on the authentication type, the user and password
		values may take on various meanings. See Parse_Authentication
		method below for more details.
+=========================================================================*/
string
ExitXMLBlock::Get_Authentication_Password() const
{
	return m_sAuthenticationPassword;
}

AUTHTYPE_T
ExitXMLBlock::Get_Authentication_Type() const
{
	return m_sAuthenticationType;
}

string
ExitXMLBlock::Get_Authentication_User() const
{
	return m_sAuthenticationUser;
}

/*=========================================================================+
	Get_Exit_Type:
		Returns the exit type from the input XML block.  The exit type
		determine the kind of event is being processed.  If you install the
		same program exit subroutine for multiple different types of exits,
		then you may need to check within your program exit subroutine
		as to which type of exit this is.  However, if your exit is only
		called for one type of exit, or your exit's behavior is independent
		of exit type, you wouldn't need to check this value.
+=========================================================================*/
string
ExitXMLBlock::Get_Exit_Type() const
{
	return m_sExitType;
}

/*=========================================================================+
	Get_Function_Parameter:
		Return the value for the specified custom function parameter.

		For multi-valued parameters, call repeated with val_no = 0, 1, 2, ...
		until returned string is empty.

		Function parameters are encoded as attributes eTFuncParam1
		through eTFuncParam10.  If any of the parameters are multi-valued,
		the parameter is repeated for each value.
+=========================================================================*/
string
ExitXMLBlock::Get_Function_Parameter(
		int			iParamNumber,
		int			iParamIndex			// = 0
	) const
{
	string			sValue				= "";
	UTF8			pszuParamName[20];

	sprintf(pszuParamName, UTFEXIT_CF_FUNCPARAM "%d", iParamNumber);

	sValue = Get_Attribute_Value(pszuParamName, iParamIndex);

	return sValue;
}

/*=========================================================================+
	Get_Object_DN:
		Returns the full LDAP distinguished name (DN) of the object being
		operated on.  This might be the DN of a global user or account or
		other object, depending on the exit type.
+=========================================================================*/
string
ExitXMLBlock::Get_Object_DN() const
{
	return m_sObjectDn;
}

/*=========================================================================+
	Get_Object_Name:
		Returns the common name of the object being operated on.  In
		other words, if the object DN is "eTGlobalUserName=xxx,....",
		then the object name is simply "xxx".
+=========================================================================*/
string
ExitXMLBlock::Get_Object_Name() const
{
	return m_sObjectName;
}

/*=========================================================================+
	Get_Object_Class:
		Returns the object class of the object being operated on.  In
		other words, if the object is a global user, then the object
		class would be "eTGlobalUser".
+=========================================================================*/
string
ExitXMLBlock::Get_Object_Class() const
{
	return m_sObjectClass;
}


/*-------------------------------------------------------------------------+
	Protected Methods
+-------------------------------------------------------------------------*/

/*=========================================================================+
   Convert_To_LDAP_Status:

      Convert the program exit status to an LDAP status suitable to return
	  from a program exit.

      This sample only convert the status to LDAP_SUCCESS or
      LDAP_OPERATIONS_ERROR.  Your program exit might want to
      support more LDAP status values.

+=========================================================================*/
int
ExitXMLBlock::Convert_To_LDAP_Status(
		STATUS_T		tStatus
	)
{
	int rc;

	switch (tStatus) {
	case E_SUCCESS:
		rc = LDAP_SUCCESS;
		break;

	default:
		rc = LDAP_OPERATIONS_ERROR;
	}

	return rc;
}

/*=========================================================================+
   Convert_Status_To_Category_String:

      Convert status into an eTrust Admin status category string.

      Upon return from a program exit, the eTrust Admin server will log
	  the program exit's execution using its status category value.

      This sample code has only three status values so they map nicely to
      the eTrust Admin status category values.  If your program exit has more
	  status codes, then you must map each of your status code into one of
      the three category values.

+=========================================================================*/
string
ExitXMLBlock::Convert_Status_To_Category_String(
		STATUS_T		tStatus
	)
{
	string sCategory = UTFEXIT_FAILURE;

	switch (tStatus) {
	case E_SUCCESS:		sCategory = UTFEXIT_SUCCESS; break;
	case E_WARNING:		sCategory = UTFEXIT_WARNING; break;
	case E_FAILURE:		sCategory = UTFEXIT_FAILURE; break;
	default:			sCategory = UTFEXIT_FAILURE; break;
	}

	return sCategory;
}

/*=========================================================================+
   Convert_Authentication_Type_String_to_Enum:

      Convert a type string into the type enum value.

      The eTrust Admin server will pass to each program exit invocation
	  an optional authentication block providing the identity under
	  which the program exit should execute.  This will allow the
	  program exit to log in to various systems to carry out the work
	  of the program exit.

      The authentication types are

		NONE        - no authentication information provided

		GLOBAL_USER - authenticate as the logged in global user who
			initiated the operation that spawned this program exit invocation

        PROXY_USER  - authenticate as a fixed global user configured when
			the program exit was registered within eTrust Admin

		PROXY_OTHER - authenticate as a fixed name and password whose
			meaning is known by the program exit.  E.g., as an Windows
			account and password.

+=========================================================================*/
AUTHTYPE_T
ExitXMLBlock::Convert_Authentication_Type_String_to_Enum(
		string		sType
	)
{
	AUTHTYPE_T	tAuthType		= AUTHTYPE_NONE;

	/*
	|| If no authentication is needed, eTrust Admin won't send an
	|| Authentication block.  Thus the type_string can be NULL,
	|| in which case the type is NONE.
	*/
	if (sType.empty()) {
		tAuthType = AUTHTYPE_NONE;
	}
	else if (sType == UTFEXIT_AUTHTYPE_NONE) {
		tAuthType = AUTHTYPE_NONE;
	}
	else if (sType == UTFEXIT_AUTHTYPE_GLOBAL_USER) {
		tAuthType = AUTHTYPE_GLOBAL_USER;
	}
	else if (sType == UTFEXIT_AUTHTYPE_PROXY_USER) {
		tAuthType = AUTHTYPE_PROXY_USER;
	}
	else if (sType == UTFEXIT_AUTHTYPE_PROXY_OTHER) {
		tAuthType = AUTHTYPE_PROXY_OTHER;
	}
	else {
		tAuthType = AUTHTYPE_NONE;
	}

	return tAuthType;
}


/*=========================================================================+
	Parse_ETA_Input_XML:

		Parse the input XML block.

		eTrust Admin sends an XML block containing data of the
		object being processed.  The XML block also contains
		optional authentication data.

	The format of the input XML block is:
		<eTExitInvoke eTExitType={type of exit}>
			< {objectclass} >
				<eTDN> {dn of object being processed} </eTDN>
				<eTName> {name of object being processed} </eTName>
				< {attribute} > {value} </ {attribute} >
			< {objectclass} >

			<Authentication>
				<Type> {type of authentication} </Type>
				<User> {user to authenticate as} </User>
				<Password> {password (in the clear)} </Password>
			</Authentication>
		</eTExitInvoke>


		The {attribute} and {value} are specific to the object
		being processed.  E.g., if the object has attribute "City"
		and value "Renton", the XML block will contains the tag:
			<City>Renton</City>

		If the attribute is multi-valued, each value will have a
		separate tag:
			<City>Renton</City>
			<City>Kirkland</City>

+=========================================================================*/
int
ExitXMLBlock::Parse_ETA_Input_XML()
{
	int				iRc			= -1;		// failure
	DOMElement*		pElement	= NULL;
	DOMNodeList*	pNodeList	= NULL;
	XMLCh*			pxcTag		= NULL;
	const XMLCh*	pxcValue	= NULL;
	UTF8*			pszuValue	= NULL;
	string			sTagName;
	string			sTagValue;
	string			sErrMsg;
	int				iTagCount;

	// Load the XML document.
	try {
		m_pXmlBuilder->resetDocumentPool();
		MemBufInputSource oSource(
							(const XMLByte*)m_sInputXML.c_str(),
							m_sInputXML.length(),
							"InputBuffer",
							false);
		Wrapper4InputSource oWrapper(&oSource, false);
		m_pXmlDocument = m_pXmlBuilder->parse(oWrapper);
	}
	catch (const XMLException& toCatch) {
		sErrMsg = XMLString::transcode(toCatch.getMessage());
        cerr << "\nError during parsing\nException message is: \n" << sErrMsg << "\n";
		goto exit;
	}
	catch (const DOMException& toCatch) {
        const unsigned int iMaxChars = 2047;
        XMLCh pzcErrMsg[iMaxChars + 1];
		sErrMsg = XMLString::transcode(toCatch.msg);
		cerr << "\nDOM Error during parsing\nException message is: \n" << sErrMsg << "\n";
        if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, pzcErrMsg, iMaxChars))
                cerr << "Message is: " << XMLString::transcode(pzcErrMsg) << endl;
		goto exit;
	}
	catch (...) {
        cerr << "\nUnexpected exception during parsing\n";
		goto exit;
	}

	// Get the exit type from the top level node's tag attribute.
	pElement = m_pXmlDocument->getDocumentElement();

	pxcTag = UTF8toUTF16(UTFEXIT_EXITTYPE);
	pxcValue = pElement->getAttribute(pxcTag);
	delete pxcTag;
	if (pxcValue) {
		this->m_sExitType = UTF16toUTF8(pxcValue);
	}

	// Find all the child nodes.
	pNodeList = pElement->getChildNodes();
	if (!pNodeList) {
		goto exit;
	}

	/*
	|| Get the number of tags found under the top level node.
	|| If the node_list is empty initialize the tag count to 0.
	*/
	iTagCount = pNodeList->getLength();
	// cout << "Tag Count:" << iTagCount << endl;

	// Get the tag and value under the top level node and parse each tag.
	for (int iIndex = 0; iIndex < iTagCount; iIndex++) {
		DOMNode* pNode = pNodeList->item(iIndex);
		if (!pNode) {
			// Error!
			continue;
		}

		short siTagType = pNode->getNodeType();
		if (siTagType != 1 /* DOMNode::NodeType::ELEMENT_NODE */) {
			continue;
		}

		/*
		|| Get the tag name.  If failed to get the tag name,
		|| skip the current tag.
		*/
		pxcValue = pNode->getNodeName();
		if (pxcValue) {
			sTagName = UTF16toUTF8(pxcValue);
		}

		pxcValue = pNode->getNodeValue();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}

#if 0
		cout << "Node Name: '" << sTagName << "'" << endl;
		cout << "Node Type: " << siTagType << endl;
		cout << "Node Value: '" << (sTagValue.empty() ? "<empty>" : sTagValue) << "'" << endl;
		const XMLCh* pxcValue = pNode->getTextContent();
		string sTagText = UTF16toUTF8(pxcValue);
		cout << "Node Text: '" << (sTagText.empty() ? "<empty>" : sTagText) << "'" << endl;
		cout << endl;
#endif

		if (sTagName == UTFEXIT_AUTHENTICATION) {
			Parse_Authentication_Block(sTagName);

		} else {
			this->m_sObjectClass = sTagName;
			Parse_Object_Block(this->m_sObjectClass);
		}
	}
	iRc = 0;	// success!

exit:
	return iRc;
}

/*=========================================================================+
	Parse_Object_Block:

		Parse an object block from the XML input.  The object block is
		an XML string of the form:

			< {objectclass} >
				<eTDN> {dn of object being processed} </eTDN>
				<eTName> {name of object being processed} </eTName>
				< {attribute} > {value} </ {attribute} >
			< {objectclass} >

+=========================================================================*/
void
ExitXMLBlock::Parse_Object_Block(
		string		sBlockName
	)
{
	DOMNodeList*	pTopNodeList	= NULL;
	DOMNode*		pTopNode		= NULL;
	DOMNodeList*	pNodeList		= NULL;
	const XMLCh*	pxcValue		= NULL;
	string			sTagName;
	string			sTagValue;
	short			iTagType;
	int				iTagCount;

	// Find the XML block.
	pTopNodeList = Find_Node(m_pXmlDocument, sBlockName);
	if (!pTopNodeList) {
		goto exit;
	}
	pTopNode = pTopNodeList->item(0);	// Should only be one!

	// Find all the child nodes.
	pNodeList = pTopNode->getChildNodes();

	/*
	|| Get the number of tags found under the top level node.
	|| If the pNodeList is empty, initialize the tag count to 0.
	*/
	iTagCount = pNodeList->getLength();

	// Get the tag and value under the top level node and parse each tag.
	for (int iIndex = 0; iIndex < iTagCount; iIndex++) {
		DOMNode* pNode = pNodeList->item(iIndex);
		if (!pNode) {
			// Error!
			continue;
		}

		iTagType = pNode->getNodeType();
		if (iTagType != 1 /* DOMNode::NodeType::ELEMENT_NODE */) {
			continue;
		}

		/*
		|| Get the tag name.  If failed to get the tag name,
		|| skip the current tag.
		*/
		pxcValue = pNode->getNodeName();
		if (pxcValue) {
			sTagName = UTF16toUTF8(pxcValue);
		}

		/*
		pxcValue = pNode->getNodeValue();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}
		*/

		pxcValue = pNode->getTextContent();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}

#if 0
		cout << "OBJ Node Name: '" << sTagName << "'" << endl;
		cout << "OBJ Node Type: " << iTagType << endl;
		cout << "OBJ Node Value: '" << (sTagValue.empty() ? "<empty>" : sTagValue) << "'" << endl;
		cout << endl;
#endif

		if (sTagName == UTFEXIT_DN) {
			m_sObjectDn = sTagValue;
		}
		else if (sTagName == UTFNAME) {
			m_sObjectName = sTagValue;
		}
		else {
			/*
			|| Any other tag is an attribute name.
			|| Insert the attribute name and value into the end of the
			|| respective attribute and value arrays.
			|| Attribute with multiple values will have multple elements
			|| in both arrays.
			*/
			m_vsObjectAttributes.insert(m_vsObjectAttributes.end(), sTagName);
			m_vsObjectValues.insert(m_vsObjectValues.end(), sTagValue);
		}
	}
exit:
	;
}

/*=========================================================================+
	Parse_Authentication:
		Parse the authentication block from the input XML block.  This
		is called during the constructor of this object.

		The Authentication block is an XML block such as
			<Authentication>
				<Type> {type of authentication} </Type>
				<User> {user to authenticate as} </User>
				<Password> {password} </Password>
			</Authentication>

+=========================================================================*/
void
ExitXMLBlock::Parse_Authentication_Block(
		string		sBlockName
	)
{
	DOMNodeList*	pTopNodeList	= NULL;
	DOMNode*		pTopNode		= NULL;
	DOMNodeList*	pNodeList		= NULL;
	const XMLCh*	pxcValue		= NULL;
	string			sTagName;
	string			sTagValue;
	short			iTagType;
	int				iTagCount;
	
	// Find the XML block.
	pTopNodeList = Find_Node(m_pXmlDocument, sBlockName);
	if (!pTopNodeList) {
		goto exit;
	}
	pTopNode = pTopNodeList->item(0);	// Should only be one!

	// Find all the child nodes.
	pNodeList = pTopNode->getChildNodes();

	/*
	|| Get the number of tags found under the top level node.
	|| If the pNodeList is empty, initialize the tag count to 0.
	*/
	iTagCount = pNodeList->getLength();

	// Get the tag and value under the top level node and parse each tag.
	for (int iIndex = 0; iIndex < iTagCount; iIndex++) {
		DOMNode* pNode = pNodeList->item(iIndex);
		if (!pNode) {
			// Error!
			continue;
		}

		iTagType = pNode->getNodeType();
		if (iTagType != 1 /* DOMNode::NodeType::ELEMENT_NODE */) {
			continue;
		}

		/*
		|| Get the tag name.  If failed to get the tag name,
		|| skip the current tag.
		*/
		pxcValue = pNode->getNodeName();
		if (pxcValue) {
			sTagName = UTF16toUTF8(pxcValue);
		}

		/*
		pxcValue = pNode->getNodeValue();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}
		*/

		pxcValue = pNode->getTextContent();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}

#if 0
		cout << "AUTH Node Name: '" << sTagName << "'" << endl;
		cout << "AUTH Node Type: " << iTagType << endl;
		cout << "AUTH Node Value: '" << (sTagValue.empty() ? "<empty>" : sTagValue) << "'" << endl;
		cout << endl;
#endif

		if (sTagName == UTFEXIT_AUTHTYPE) {
			m_sAuthenticationType = Convert_Authentication_Type_String_to_Enum(sTagValue);
		}
		else if (sTagName == UTFEXIT_AUTHUSER) {
			m_sAuthenticationUser = sTagValue;
		}
		else if (sTagName == UTFEXIT_AUTHPASSWORD) {
			m_sAuthenticationPassword = sTagValue;
		}
	}
exit:
	;
}

/*=========================================================================+
	Parse_Block:

		Parse the specified block from the XML input.  The block is 
		expected to be an XML string of the following form:

			< {sBlockName} >
				<name1> {value1_1} </name1>
				<name2> {value2_1} </name2>
				...
			< {sBlockName} >

		This method is to be used when the Exit XML has been extended,
		and the Parse_ETA_Input_XML() method might decode the wrong
		"object" block.

		This method return -1 if it failed to find the named block or
		zero on success.  The data parsed can be retrieved using
		the Get_Block_Attribute_Name() and Get_Block_Attribute_Value().

+=========================================================================*/
int
ExitXMLBlock::Parse_Block(
		string		sBlockName
	)
{
	int				iRc				= -1;	// failure
	DOMNodeList*	pTopNodeList	= NULL;
	DOMNode*		pTopNode		= NULL;
	DOMNodeList*	pNodeList		= NULL;
	const XMLCh*	pxcValue		= NULL;
	string			sTagName;
	string			sTagValue;
	short			iTagType;
	int				iTagCount;
	
	// Clear previous data, if any
	m_vsBlockAttributeList.clear();
	m_vsBlockAttributes.clear();
	m_vsBlockValues.clear();

	// Find the XML block.
	pTopNodeList = Find_Node(m_pXmlDocument, sBlockName);
	if (!pTopNodeList) {
		goto exit;
	}
	pTopNode = pTopNodeList->item(0);	// Should only be one!
	if (!pTopNode) {
		goto exit;
	}

	// Find all the child nodes.
	pNodeList = pTopNode->getChildNodes();

	/*
	|| Get the number of tags found under the top level node.
	|| If the pNodeList is empty, initialize the tag count to 0.
	*/
	iTagCount = pNodeList->getLength();

	// Get the tag and value under the top level node and parse each tag.
	for (int iIndex = 0; iIndex < iTagCount; iIndex++) {
		DOMNode* pNode = pNodeList->item(iIndex);
		if (!pNode) {
			// Error!
			continue;
		}

		iTagType = pNode->getNodeType();
		if (iTagType != 1 /* DOMNode::NodeType::ELEMENT_NODE */) {
			continue;
		}

		/*
		|| Get the tag name.  If failed to get the tag name,
		|| skip the current tag.
		*/
		pxcValue = pNode->getNodeName();
		if (pxcValue) {
			sTagName = UTF16toUTF8(pxcValue);
		}

		/*
		pxcValue = pNode->getNodeValue();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}
		*/

		pxcValue = pNode->getTextContent();
		if (pxcValue) {
			sTagValue = UTF16toUTF8(pxcValue);
		}

#if 0
		cout << "BLK Node Name: '" << sTagName << "'" << endl;
		cout << "BLK Node Type: " << iTagType << endl;
		cout << "BLK Node Value: '" << (sTagValue.empty() ? "<empty>" : sTagValue) << "'" << endl;
		cout << endl;
#endif

		/*
		|| Insert the attribute name and value into the end of the
		|| respective attribute and value arrays.
		|| Attribute with multiple values will have multiple elements
		|| in both arrays.
		*/
		if (!IsInVector(sTagName, m_vsBlockAttributeList)) {
			m_vsBlockAttributeList.insert(m_vsBlockAttributeList.end(), sTagName);
		}
		m_vsBlockAttributes.insert(m_vsBlockAttributes.end(), sTagName);
		m_vsBlockValues.insert(m_vsBlockValues.end(), sTagValue);
	}
	iRc = 0;

exit:
	return iRc;
}

/*=========================================================================+
	Get_Block_Attribute_Name:
		Return the name of the next attribute.  Returns "" when there
		are no more attributes.

		Repeated call with with iIndex = 0, 1, 2, ...
		until returned string is empty.
+=========================================================================*/
string
ExitXMLBlock::Get_Block_Attribute_Name(
		int			iIndex	/* = 0 */
	) const
{
	string	sValue		= "";
	int		iAttrCount	= m_vsBlockAttributeList.size();

	if (iAttrCount > 0 && iIndex >= 0 && iIndex < iAttrCount) {
		sValue = m_vsBlockAttributeList[iIndex];
	}
	return sValue;
}

/*=========================================================================+
	Get_Block_Attribute_Value:
		Return the value for the specified attribute.

		For multi-valued attributes, call repeated with 
		iValueIndex = 0, 1, 2, ...
		until returned string is empty.
+=========================================================================*/
string
ExitXMLBlock::Get_Block_Attribute_Value(
		string		sAttribute,
		int			iValueIndex			// = 0
	) const
{
	string	sValue		= "";

	for (unsigned int iIndex = 0; iIndex < m_vsBlockAttributes.size(); iIndex++) {
		if (m_vsBlockAttributes[iIndex] == sAttribute) {
			if (iValueIndex-- <= 0) {
				// Found a matching attribute; return the corresponding value.
				sValue = m_vsBlockValues[iIndex];
				break;
			}
		}
	}
	return sValue;
}


/*=========================================================================+
	Add_Element:
		Add a "<tag> value </tag>" element to an XML block.  If the
		optional tag attribute and value are provided, then the element
		will look like "<tag attribute=value> value </tag>" instead.

+=========================================================================*/
int
ExitXMLBlock::Add_Element(
			DOMDocument*	pDocument,
			DOMElement*		pParentElement,
			string			sTag,
			string			sValue,
			string			sTagAttribute,		//		= "",
			string			sTagAttributeValue	//		= ""
	)
{
	DOMElement*			pElement	= NULL;
	STATUS_T			tStatus		= E_SUCCESS;
	XMLCh*				pxcValue	= NULL;
	int					iRc			= -1;		// FailureS
	
	// Create element.
	if (pDocument && pParentElement && !sTag.empty() && !sValue.empty()) {
		pxcValue = UTF8toUTF16(sTag);
		DOMElement* pChild = pDocument->createElement(pxcValue);
		delete pxcValue;

		pxcValue = UTF8toUTF16(sValue);
		DOMText* pText = pDocument->createTextNode(pxcValue);
		delete pxcValue;

		pChild->appendChild(pText);

		// Add the tag attribute if specified.
		if (!sTagAttribute.empty() && !sTagAttributeValue.empty()) {
			XMLCh* pxcAttr	= UTF8toUTF16(sTagAttribute);
			XMLCh* pxcValue	= UTF8toUTF16(sTagAttributeValue);
			pChild->setAttribute(pxcAttr, pxcValue);
			delete pxcAttr;
			delete pxcValue;
		}

		pParentElement->appendChild(pChild);
		iRc = 0;
	} 
	return iRc;
}

/*=========================================================================+
	Find_Node:
		Locate the node with the indicated tag.

+=========================================================================*/
DOMNodeList*
ExitXMLBlock::Find_Node(
		DOMDocument*			pDocument,
		string					sTag,
		bool					bFindMultipleNodes		// = true
	)
{
	DOMNodeList*	pNodeList	= NULL;
	XMLCh*			pxcTag		= NULL;

	pxcTag = UTF8toUTF16(sTag);
	pNodeList = pDocument->getElementsByTagName(pxcTag);
	delete pxcTag;

	return pNodeList;
}

/*=========================================================================+
	Initialize_Transcoder:
		Intialize s UTF-16 to UTF-8 transcoder

+=========================================================================*/
int
ExitXMLBlock::Initialize_Transcoder()
{
	int						iRc			= 0;		// success
	XMLCh*					pxcEncoding	= NULL;
	XMLTransService::Codes	tFailReason;

	pxcEncoding = XMLString::transcode("UTF-8");
	m_pXmlTranscoder = XMLPlatformUtils::fgTransService->makeNewTranscoderFor(pxcEncoding, tFailReason, 1024);
	if (!m_pXmlTranscoder) {
		// ERROR: XML::Xerces: INIT: Could not create UTF-8	transcoder
		iRc = -1;
	}
	return iRc;
}

/*=========================================================================+
	UTF16toUTF8:
		Convert a UTF-16 string into UTF-8 std::string

+=========================================================================*/
string
ExitXMLBlock::UTF16toUTF8(
		const XMLCh* pxcString
	)
{
	string			sString;
	unsigned int	iCharsEaten = 0;
	int				iLength		= XMLString::stringLen(pxcString);
	XMLByte*		pxbBuffer	= NULL;
	unsigned int	iTotalChars;

	pxbBuffer = new XMLByte[iLength * 4];          // output string
	iTotalChars = m_pXmlTranscoder->transcodeTo(
										(const XMLCh*)pxcString,
										(unsigned int)iLength,
										(XMLByte*)pxbBuffer,
										(unsigned int)iLength * 4,
										iCharsEaten,
										XMLTranscoder::UnRep_Throw);
	pxbBuffer[iTotalChars] = '\0';
	sString = (UTF8*)pxbBuffer;
	delete pxbBuffer;
	return sString;
}

/*=========================================================================+
	UTF8toUTF16:
		Convert a UTF-8 std::string into an UTF-16 string

		Note: The caller must release the returned string by
		calling 'delete'

+=========================================================================*/
XMLCh* 
ExitXMLBlock::UTF8toUTF16(
		string			sString
	)
{
	unsigned int	iCharsEaten		= 0;
	int				iLength			= sString.size();
	XMLCh*			pxcBuffer		= NULL;
	unsigned char*	pszCharSizes	= NULL;
	unsigned int	iTotalChars;
		
	pxcBuffer = new XMLCh[iLength * 4];
	pszCharSizes = new unsigned char[iLength * 4];
	iTotalChars = m_pXmlTranscoder->transcodeFrom(
										(XMLByte*)sString.c_str(),
										(unsigned int)iLength,
										(XMLCh* const)pxcBuffer,
										(unsigned int)iLength * 4,
										iCharsEaten,
										pszCharSizes);
	pxcBuffer[iTotalChars] = '\0';
	delete pszCharSizes;
	return pxcBuffer;
}

/*
|| Local functions
*/
// Is the name in the vector?
bool
IsInVector(const string sName, vectorOfStrings& vsVector)
{
	if (vsVector.size() == 0) {
		return false;
	}

	for (unsigned int iIndex = 0; iIndex < vsVector.size(); iIndex++) {
		if (sName == vsVector[iIndex]) {
			return true;
		}
	}
	return false;
}

