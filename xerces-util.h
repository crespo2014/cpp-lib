/*
 * xerces-util.h
 *
 *  Created on: 30 Apr 2014
 *      Author: lester
 */

#ifndef XERCES_UTIL_H_
#define XERCES_UTIL_H_

#include <string>
#include <memory>

#include <xercesc/dom/DOM.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/parsers/SAXParser.hpp>

#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE;

/*
 * Some usefull functions to hanlde xml documents with xerces
 */

class utils
{
public:
	/*
	 * Compare node name
	 */
	static bool isName(DOMNode* node, const char* tagName)
	{
		if ((!node) || (node->getNodeType() != DOMNode::ELEMENT_NODE)) return false;

		const XMLCh *name = node->getNodeName();
		if (!name) return false;
		char* v = XMLString::transcode(name);
		bool b = (strcmp(v, tagName) == 0);
		XMLString::release(&v);
		return b;
	}
	/*
	 * Get node by name
	 */
	static DOMNode* getChildByName(DOMNode* node, const char* tagName)
	{
		if (!node) return nullptr;
		DOMNode *n = node->getFirstChild();
		for (; n; n = n->getNextSibling())
		{
			if (n->getNodeType() != DOMNode::ELEMENT_NODE) continue;
			const XMLCh *name = n->getNodeName();
			if (!name) continue;
			char* v = XMLString::transcode(name);
			bool b = (strcmp(v, tagName) == 0);
			XMLString::release(&v);
			if (b) break;
		}
		return n;
	}

	/*
	 * Find a child node by name and assign to string
	 * */
	static void getChild(DOMNode* node, const char* tagName, std::string &s)
	{
		DOMNode *n = getChildByName(node, tagName);
		if (!n) return;
		DOMNode* child = n->getFirstChild();
		if (child->getNodeType() == DOMNode::TEXT_NODE)
		{
			const XMLCh *c = child->getNodeValue();
			char* v = XMLString::transcode(c);
			s = v;
			XMLString::release(&v);
		} else
			s.clear();
	}

	static void getChild(DOMNode* node, const char* tagName, unsigned &u)
	{
		DOMNode *n = getChildByName(node, tagName);
		if (!n) return;
		DOMNode* child = n->getFirstChild();
		if (child->getNodeType() == DOMNode::TEXT_NODE)
		{
			const XMLCh *c = child->getNodeValue();
			char* v = XMLString::transcode(c);
			sscanf(v, "%d", &u);
			XMLString::release(&v);
		}
	}

	static void getChild(DOMNode* node, const char* tagName, float &u)
	{

		DOMNode *n = getChildByName(node, tagName);
		if (!n) return;
		DOMNode* child = n->getFirstChild();
		if (child->getNodeType() == DOMNode::TEXT_NODE)
		{
			const XMLCh *c = child->getNodeValue();
			char* v = XMLString::transcode(c);
			sscanf(v, "%f", &u);
			XMLString::release(&v);
		}
	}

	/*
	 * Find a child node by name and assign to string
	 * */
	static void getChild(DOMNode* node, const char* tagName, bool &b)
	{
		DOMNode *n = getChildByName(node, tagName);
		if (!n) return;
		DOMNode* child = n->getFirstChild();
		if (child->getNodeType() == DOMNode::TEXT_NODE)
		{
			const XMLCh *c = child->getNodeValue();
			char* v = XMLString::transcode(c);
			if (*v == '0')
				b = false;
			else
				b = true;
			XMLString::release(&v);
		}
	}

	/*
	 * Get child elements from from parent and fill a container
	 */
	template<typename C>
	static void getList(DOMNode* node, const char* childname, C & container)
	{
		if (!node) return;
		DOMNode *n = node->getFirstChild();
		for (; n; n = n->getNextSibling())
		{
			if (isName(n, childname)) container.list.push_back(typename C::value_type(n));
		}
	}
	/*
	 * Extract object name from container.
	 * add a s character to the name and get a node with this new name
	 * find all childrens
	 */
	template<typename C>
	static void getList(DOMNode* node, C & container)
	{
		std::string s { container.getObjName() };
		s.push_back('s');
		DOMNode *n = getChildByName(node, s.c_str());
		if (!n) return;
		n = n->getFirstChild();
		for (; n; n = n->getNextSibling())
		{
			if (isName(n, container.getObjName())) container.list.push_back(typename C::value_type(n));
		}
	}

	/*
	 * print information
	 */
	template<typename C>
	static void print(const char* name, const C& d)
	{
		std::cout << "<" << name << ">" << d << "</" << name << ">" << std::endl;
	}

	template<typename C>
	static void printList(const char* name, const C& d)
	{
		std::string s { name };
		s.resize(s.size() - 1);

		std::cout << "<" << name << ">" << std::endl;
		for (auto it = d.begin(); it != d.end(); ++it)
		{
			printObject(s.c_str(), *it);
		}
		std::cout << "</" << name << ">" << std::endl;
	}

	template<typename C>
	static void printList(const C& container)
	{
		std::string s { container.getObjName() };
		s.push_back('s');

		std::cout << "<" << s << ">" << std::endl;
		for (auto it = container.list.begin(); it != container.list.end(); ++it)
		{
			printObject(container.getObjName(), *it);
		}
		std::cout << "</" << s << ">" << std::endl;
	}

	template<typename C>
	static void printObject(const char* name, const C& o)
	{
		std::cout << "<" << name << ">" << std::endl;
		o.print();
		std::cout << "</" << name << ">" << std::endl;
	}
	template<typename C>
	static void printObject(const C& o)
	{
		std::cout << "<" << o.objType() << ">" << std::endl;
		o.print();
		std::cout << "</" << o.objType() << ">" << std::endl;
	}
};

#endif /* XERCES_UTIL_H_ */
