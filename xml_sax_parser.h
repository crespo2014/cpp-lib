/*
 * xml_sax_parser.h
 *
 *  Created on: 30 Apr 2014
 *      Author: lester
 */

#ifndef XML_SAX_PARSER_H_
#define XML_SAX_PARSER_H_

#include <limits.h>
#include "stdint.h"
#include "Buffer.h"
#include "log.h"
#include <vector>
#include "os.h"
#include "fstring.h"
#include "utf8_it.h"

//DEFINE_BASE_EXCEPTION(xml_base);

class xml_base: public error_base
{
public:
	unsigned line, pos;
	xml_base(const char* desc,const _error_info& i) :
			error_base(desc, i), line(0), pos(0)
	{
	}
};

DEFINE_DERIVED_EXCEPTION(xml_unexpected_character, xml_base, "Invalid character");
DEFINE_DERIVED_EXCEPTION(xml_invalid_name, xml_base, "Invalid character use for named a  tag name or attribute ");
DEFINE_DERIVED_EXCEPTION(xml_opentag_missing, xml_base, "symbol < is missing");
DEFINE_DERIVED_EXCEPTION(xml_invalid_character, xml_base, "A not valid symbol was read");
DEFINE_DERIVED_EXCEPTION(xml_closing_tag, xml_base, "A unmatched close tag found");
DEFINE_DERIVED_EXCEPTION(xml_no_root_tag, xml_base, "More than one root tag found");
DEFINE_DERIVED_EXCEPTION(xml_name_to_long, xml_base, "The buffer is not long enough to hold key,value string");

using namespace std;
using namespace io;

/*
 * Parse status
 *  tag_name tag_attr tag_data tag_close
 *  root element is tag data
 *  read char one by one
 *   ¦-------------------------------------------------------------------------------------------
 *   ¦                                                                                          ^
 *  (1)[<](starting)----[/](closing)------[a-z](name)-----------------[>](closed)---|           ¦
 *               ¦                                              ^                   |           ¦
 *               ¦                                              ¦  _________________|           ¦
 *               ¦                                              ¦  |                            ¦
 *               ¦                                              ¦  |                            ¦
 *   			 -- [a-z](name)----(2)(open)-----[/](finishing)--  |     ---------------------->¦
 *                               ^          ¦                      |     ^                      ¦
 *                               ¦          ¦                      |     ¦                      ¦
 *     --------------------------           ¦----[>](childs)-------------------[a-z](data)----->¦
 *     ¦                                    ¦
 *     ¦            -------------------------
 *     ¦            ¦
 *     ¦          [a-z](attribute-name)-----[=]["]----[a-z](attribute value)-----["]----¦
 *     ¦                                                                                ¦
 *     ¦--------------------------------------------------------------------------------¦
 *
 *
 *
 */

/*
 * An implementation of sax handler could be usefull for testing
 * also can be derived from this and only implement necessary events
 */
class SaxHandler
{
	char c = ' ';
public:
	void OnTagOpen(const char* name)
	{
		cout << c << endl << "<" << name;
		c = '>';
	}
	void OnAttribute(const char* key, const char* val)
	{
		cout << " " << key << " = " << val << " ";
	}
	void OnData(const char* val)
	{
		cout << ">" << val;
		c= ' ';
	}
	void OnTagClose(const char* name)
	{
		cout << c;
		if (name)
			cout << "</" << name << ">";
		else
			cout << "/>";
		cout << endl;
		c = ' ';
	}
	void OnError(unsigned line, unsigned pos)
	{
		cout << " invalid character at " << line << "." << pos << endl;
	}
};

/*
 * Standard ascii decode iterator
 */
class ascii_decode_it
{
public:
	// Paremeters are current value and next function
	template<class F>
	static uint32_t read(uint8_t v, F f/* std::function<uint8_t()> readChar*/)
	{
		return v;
	}
};

/*
 * Decode V2
 */
class decode_ascii
{
	char c;
public:
	/*
	 * Push byte to decode while false
	 * true means that a new bytes is ready to take using get
	 */
	bool push(uint8_t v)
	{
		c = v;
		return true;
	}
	/*
	 * Get char from decode and clear status machine
	 */
	uint32_t get() const
	{
		return c;
	}
};

namespace sax_parser
{
enum _tag_status
{
	// for status is tag_close
	tag_root,		// waiting root tag
	tag_root_tag,    // waiting the root tag ?
	tag_open,    	// tag is open, reading name or attributes
	tag_content, 	// reading content for this tag
	tag_child, 		// content has been read, no more content or data expected reading child
	tag_closing, 	// tag is near to be closed after read /
};
}

/*
 * Using the default handle means that a object must implement all methods in SaxHandler
 */
template<class H = SaxHandler, class D = decode_ascii>
class SaxParser
{

public:
	SaxParser(H& handler, InBuffer &b) :
			handler(handler), buff(b), it_decode(b.begin()), it(b.begin()), it_key(it), it_val(it), stack(0), c(' '), tag_status(
					sax_parser::tag_root), line(1), pos(0)
	{

	}
	// declare a friend using any template I do not how to use partial specialization as <H,C>
	template<class T, class C>
	friend class SaxParser;
	/*
	 * Create a copy of parser using a different character decoder
	 */
	template<class C>
	SaxParser(const SaxParser<H, C> s) :
			handler(s.handler), buff(s.buff), it_decode(s.it_decode), it(s.it), it_key(s.it_key), it_val(s.it_val), stack(s.stack), c(s.c), tag_status(
					s.tag_status), line(s.line), pos(s.pos)
	{

	}
	/*
	 * Try reading root node to get xml information
	 * continue reading nodes
	 */
	void start()
	{
		bool utf8b = false;
		// reading root node is not allowed to failed
		try
		{
			popToken();		// get start tag or data
			if (c != '<')
			{
				return_exception(xml_invalid_character);
			}
			read_pop();
			// if root node is not present then parse from this object
			if (c != '?')
			{
				onTagOpen();
			}
			else
			{
				utf8b = onRootNode();
				// if encode is ascii the call read nodes
			}
		} catch (xml_base& e)
		{
			setData(e);
			throw;
		}
		// root node was found, switch to a new one parser if encode is not ascii
		if (utf8b)
		{
			// check character encoder and call new parser
			SaxParser<H, decode_utf8> p(*this);
			p.read_nodes();
		}
		else
		{
			read_nodes();
		}
	}
	/*
	 * Read nodes, root node is not allowed here
	 */
	void read_nodes()
	{
		try
		{
			for (;;)
			{
				popToken();		// get start tag or data
				if (c != '<')
				{
					if (tag_status != sax_parser::tag_content)
						return_exception(xml_invalid_character);
					onContent();
					tag_status = sax_parser::tag_child;
					// Content will stop on character <
				}
				// we are in the symbol <
				read_pop();
				if (c == '/')
				{
					read_pop();
					onTagClose();
					continue;
				}
				onTagOpen();
			}
		} catch (const error_eof& e)
		{
			if (stack || (tag_status != sax_parser::tag_child))
				throw;
			// eof expected
		} catch (xml_base& e)
		{
			setData(e);
			throw;
		}
	}
private:
	D decode;
	H& handler;
	InBuffer &buff;
	// data iterator
	Buffer::iterator it_decode;	// iterator used by decoder
	Buffer::iterator it;		// main iterator,
	Buffer::iterator it_key;    // can be tag name , attribute name , or value
	Buffer::iterator it_val;    // attribute value
	unsigned stack;		// what is the deep of current node
	uint32_t c;		// current char
	sax_parser::_tag_status tag_status;

	// file line and pos
	unsigned line;
	unsigned pos;

	// Update exception with data from parser status
	void setData(xml_base &b)
	{
		b.line = line;
		b.pos = pos;
	}

	unsigned getLine() const
	{
		return line;
	}
	unsigned getPos() const
	{
		return pos;
	}
	void updatePosition()
	{
		if (c == '\n')
		{
			line++;
			pos = 1;
		}
		else if (c != 'r')
		{
			pos++;
		}
	}
	/*
	 * Different way to do.
	 * Read current char and go next discard any previous data
	 */
	void read_pop()
	{
		it = it_decode;
		do
		{
			if (it_decode == buff.end())
			{
				buff.setOrigin(it);
				buff.adjust(it_decode);
				buff.readData();
				it = buff.begin();
			}
		} while (!decode.push(*(it_decode++)));
		c = decode.get();
		updatePosition();
	}
	/*
	 * Read current char, go next, and adjust if it is necessary
	 */
	void read_next()
	{
		uint8_t v;
		it = it_decode;
		do
		{
			if (it_decode == buff.end())
			{
				buff.setOrigin(it_key);
				buff.adjust(it_val);
				buff.adjust(it_decode);
				buff.adjust(it);
				buff.readData();
				it_key = buff.begin();
			}
			v = *it_decode;
			++it_decode;
		} while (!decode.push(v));
		c = decode.get();
		updatePosition();
	}

	// extract next character discarding any previous content or iterator
	//
	void pop_read()
	{
		it = it_decode;
		do
		{
			++it_decode;
			if (it_decode == buff.end())
			{
				buff.setOrigin(it);
				buff.adjust(it_decode);
				buff.readData();
				it_decode = buff.begin();
			}
		} while (!decode.push(*it_decode));
		c = decode.get();
		updatePosition();
	}
	// extract next character adjust iterator if new data is read
	void next_read()
	{
		it = it_decode;
		do
		{
			++it_decode;
			if (it_decode == buff.end())
			{
				buff.setOrigin(it_key);
				buff.adjust(it_val);
				buff.adjust(it_decode);
				buff.adjust(it);
				buff.readData();
				it_key = buff.begin();
			}
		} while (!decode.push(*it_decode));
		c = decode.get();
		updatePosition();
	}

	// Extract character last is the stop
	void next(uint32_t stop_c)
	{
		do
		{
			read_next();
		} while (c != stop_c);
	}
	/*
	 * Extract characters stop on token
	 */
	void nextToken()
	{
		do
		{
			read_next();
		} while (isWhiteSpace());
	}
	/*
	 * Extract characters until get a valid token
	 */
	void popToken()
	{
		do
		{
			read_pop();
		} while (isWhiteSpace());
	}

	// read data stop with ending char
	void readDataUntil(char c)
	{
		it_val = it_decode;
		next(c);
		*it = 0;
	}
	void popComment()
	{
		do
		{
			read_pop();
		} while (isCommentChar());
	}

	/*
	 * Read a key or name
	 * name must be start with a letter can contain letters numbers and underscore _
	 */
	void readName()
	{
		if (!isNameStartChar())
			return_exception(xml_invalid_name);
		it_key = it;
		do
		{
			read_next();
		} while (isNameChar());
	}
	/*
	 * Read a name and validate ending character
	 * iterator will point to ending char
	 *
	 * name must be start with a letter can contain letters numbers and underscore _
	 */
	void readName(uint32_t stop_c)
	{
		readName();
		if (c != stop_c)
			return_exception(xml_invalid_character);		// tag name must finish with space
		*it = 0;
	}

	// Root node <? has been discovery it is on char ?
	bool onRootNode()
	{
		if (stack || (tag_status != sax_parser::tag_root))
		{
			return_exception(xml_no_root_tag);
		}
		read_pop();				// discard ?
		readName();			// check against xml
		if (c != ' ')
			return_exception(xml_invalid_character);
		while (readAttribute())
		{
			handler.OnAttribute(it_key, it_val);
		}
		if (c != '?')
			return_exception(xml_invalid_character);
		read_pop();
		if (c != '>')
			return_exception(xml_invalid_character);
		tag_status = sax_parser::tag_root_tag;
		return true;
	}

	/*
	 * A tag has been open , pointer expected past the first character
	 */
	void onTagOpen()
	{
		// first tag, but we are waiting for a child
		if (!stack && (tag_status != sax_parser::tag_root_tag))
		{
			return_exception(xml_no_root_tag);
		}
		/*
		 * Reading head of tag
		 */
		readName();
		if (c == ' ')
		{
			tag_status = sax_parser::tag_open;
		}
		else if (c == '/')
		{
			tag_status = sax_parser::tag_closing;
		}
		else if (c == '>')
		{
			tag_status = sax_parser::tag_content;
		}
		else if (c < ' ')
			return_exception(xml_invalid_character);
		fstring(it_key, it);
		*it = 0;
		handler.OnTagOpen(it_key);
		/*
		 Reading  attributes
		 */
		if (tag_status == sax_parser::tag_open)
		{
			while (readAttribute())
			{
				handler.OnAttribute(it_key, it_val);
			}
			if (c == '/')
			{
				tag_status = sax_parser::tag_closing;
			}
			else if (c == '>')
			{
				tag_status = sax_parser::tag_content;
			}
			else
				return_exception(xml_invalid_character);
		}
		/*
		 * Reading end of the tag
		 */
		if (tag_status == sax_parser::tag_closing)
		{
			if (c != '>')
				return_exception(xml_invalid_character);
			handler.OnTagClose(nullptr);
			tag_status = sax_parser::tag_child;
			read_pop();
		}
		if (tag_status == sax_parser::tag_content)
		{
			stack++;
		}
	}
	/*
	 * try to read an attribute return false
	 */
	bool readAttribute()
	{
		popToken();
		if (!isNameStartChar())
			return false;
		readName('=');
		read_next();
		if (c != '\"')
			return_exception(xml_invalid_character);
		readDataUntil('\"');
		return true;
	}
	/*
	 * A close tag received, read name an validate , expected pointer past the first character
	 */
	void onTagClose()
	{
		readName('>');
		handler.OnTagClose(it_key);
		tag_status = sax_parser::tag_child;
		if (!stack)
		{
			return_exception(xml_closing_tag);
		}
		stack--;
		tag_status = sax_parser::tag_child;
	}

	/*
	 * read content for current tag
	 */
	void onContent()
	{
		it_key = it;
		next('<');
		*it = 0;
		handler.OnData(it_key);
	}

	/*
	 * Check a start char for a name
	 *  NameStartChar = ":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6]
	 *
	 *  | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] | [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]
	 */
	bool isNameStartChar()
	{
		return ((c <= 'Z') && (c >= 'A')) || ((c <= 'z') && (c >= 'a')) || ((c >= 0xC0) && (c <= 0xD6)) || (c == ':') || (c == '_');
	}
	/*
	 * Check a name char
	 * NameChar = NameStartChar | "-" | "." | [0-9] | #xB7
	 */
	bool isNameChar()
	{
		return isNameStartChar() || ((c >= '0') && (c <= '9')) || (c == '-') || (c == '.');
	}
	bool isCommentChar()
	{
		return (c != '-');
	}
	bool isWhiteSpace()
	{
		return (c == 0x20) || (c == 0x9) || (c == 0xD) || (c == 0xA);
	}
	bool isChar()
	{
		return false;
	}
	bool isDataChar()
	{
		return (c >= ' ') && (c != '<') && (c != '>');
		// && (c != '%') && (c != '&')
	}
	/*
	 * Comment node is open
	 * iterator on  <!
	 */
	void onComment()
	{
		read_pop();
		if (c != '-')
			return_exception(xml_invalid_character);
		read_pop();
		if (c != '-')
			return_exception(xml_invalid_character);
		while (isCommentChar())
		{
			read_pop();
		}
		if (c != '-')
			return_exception(xml_invalid_character);
		read_pop();
		if (c != '-')
			return_exception(xml_invalid_character);
		read_pop();
		if (c != '>')
			return_exception(xml_invalid_character);
		read_pop();    // expected eof here
	}

};

#endif /* XML_SAX_PARSER_H_ */
