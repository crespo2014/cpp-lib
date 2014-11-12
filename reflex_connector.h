/*
 * reflex_connector.h
 *
 *  Created on: 1 May 2014
 *      Author: lester
 */

#ifndef REFLEX_CONNECTOR_H_
#define REFLEX_CONNECTOR_H_

#include "reflex.h"

#include "xerces-util.h"
/*
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/AttributeList.hpp>

XERCES_CPP_NAMESPACE_USE;
//
 *
 */
/*
 * autorelease xerces strings
 */
class xmlString
{
	char *s;
public:
	operator char*()
	{
		return s;
	}
	xmlString(const XMLCh* const c) :
			s(XMLString::transcode(c))
	{
	}
	~xmlString()
	{
		XMLString::release(&s);
	}
};

namespace reflex {

/*
 * Connector for custom Sax parser
 */

class SaxConnector: private ReflexStack//, public SaxHandler
{
public:
	SaxConnector(const char* name, Reflex& r) :
			ReflexStack(name, r)
	{

	}
	void OnTagOpen(const char* name)
	{
		return OnItem(name);
	}
	void OnTagClose(const char* name)
	{
		return OnCloseItem(name);
	}
	void OnData(const char* val)
	{
		return OnValue(val);
	}
	void OnAttribute(const char* name, const char* value)
	{
		//return ReflexStack::OnAttribute(name,value);
	}
	~SaxConnector()
	{
	}

};

class XercesConnector: private ReflexStack, public HandlerBase
{
public:
	XercesConnector(const char* name, Reflex& r) :
			ReflexStack(name, r)
	{

	}

	void startElement(const XMLCh* const c, AttributeList& a) override
	{
		xmlString n(c);
		OnItem(n);
		for (unsigned i = 0; i < a.getLength(); ++i)
		{
			xmlString n(a.getName(i));
			xmlString v(a.getValue(i));
			//ReflexStack::OnAttribute(n, v);
		}
	}
	void endElement(const XMLCh* const name)
	{
		xmlString n(name);
		OnCloseItem(n);
	}
	void characters(const XMLCh * const chars, const XMLSize_t length)
	{
		xmlString v(chars);
		OnValue(v);
	}

};

}

#endif /* REFLEX_CONNECTOR_H_ */
