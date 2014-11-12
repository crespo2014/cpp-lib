/*
 * JsonParse.cpp
 *
 *  Created on: 24 Aug 2013
 *      Author: lester
 */

#include "JsonParse.h"
#include "string.h"
#include "log.h"

#include "exception_base.h"

namespace uexception
{
class json_parser: public uexception::error_base
{
public:
	json_parser(const _error_info& i, uint16_t line, uint16_t pos, const char* desc) :
			error_base(i), desc(desc), line(line), pos(pos)
	{
	}
	virtual ~json_parser() throw ()
	{
	}
	virtual const char* what() const throw () override
	{
		return desc;
	}
	/*
	 * Use to log all error info from a exception
	 */
	virtual unsigned print(char* str, uint32_t size) const override
	{
		if (size == 0)
			return 0;
		*str = 0;
		int ir = snprintf(str, size, "at %d.%d %s",line,pos,desc);
		return (ir > 0 && (unsigned) ir > size) ? size : ir;
	}
private:
	const char* const desc;
	uint16_t line = 0;
	uint16_t pos = 0;
};
}

#define DEFINE_JSON_EXCEPTION(type,desc) \
namespace uexception { \
class type: public json_parser { \
public: \
	type(const _error_info& i, uint16_t line, uint16_t pos) : json_parser(i, line, pos,desc) {}  \
	virtual ~type() throw () {} \
};}

// Exception are define to get an easy description from type
DEFINE_JSON_EXCEPTION(json_unexpected_close,"json object close unexpected")
DEFINE_JSON_EXCEPTION(json_unmatch_close,"json object close does not match")
DEFINE_JSON_EXCEPTION(json_root_node_open,"Close node is missing for root node")
DEFINE_JSON_EXCEPTION(json_invalid_char,"character is invalid or out of range")


JsonParse::JsonParse(MemPage *mem)
{
	this->mem = mem;
	this->strList = strList;
	pos = 0;
	last_tk = 0;
	json = 0;
	first_tk = 0;
}

JsonParse::~JsonParse()
{

}

/**
 * Parse JSON string and fill tokens.
 */
void JsonParse::Parse(char* json, unsigned short size)
{
	// FIX use a token stack to avoid parent attribute. max deep to 30 nodes
	StrList strList(mem);
	pos = 0;
	last_tk = 0;
	this->json = json;
	first_tk = 0;

	jsntok *token;
	if (!json)
		throw error_api(ERROR_INFO(), api_error::get_wrong_param());
	//if (!size) size = strlen(json);

	for (; json[pos] && (!size || (pos < size)); pos++)
	{
		char c;
		unsigned char type;

		c = json[pos];
		switch (c)
		{
		case '{':
		case '[':
			// create token and push on stack
			// new object or array found
			newToken(token, (c == '{') ? JSN_OBJECT : JSN_ARRAY, strList);
			break;
		case '}':
		case ']':
			// an object close, go to parent
			type = (c == '}' ? JSN_OBJECT : JSN_ARRAY);
			// closing object unexpected
			if (!last_tk)
			{
				throw json_unexpected_close(ERROR_INFO(),line,pos);
			}
			// if current object is not an object go to parent
			if (!(last_tk->type & JSN_OBJECT))
			{
				// goto to parent and mark as waiting for child then it will be close
				if (!(last_tk = last_tk->parent))
				{
					throw json_unexpected_close(ERROR_INFO(),line,pos);
				}
				next_tok_rel = JSON_CHILD;
			}
			// object waiting for sibling it is like a close object
			// go to parent
			if ((last_tk->type & JSN_OBJECT) && (next_tok_rel == JSON_SIBLING))
			{
				if (!(last_tk = last_tk->parent))
				{
					throw json_unexpected_close(ERROR_INFO(),line,pos);
				}
				next_tok_rel = JSON_CHILD;
			}
			// closing object must match type
			if ((last_tk->type & (~JSN_VALUE)) != type)
			{
				throw json_unmatch_close(ERROR_INFO(),line,pos);
			}
			// closing object
			// for value object, the next will a sibling of her parent
			// for key object the next will be sibling

			// setting sibling is like close an object
			next_tok_rel = JSON_SIBLING;
			if (last_tk->type & JSN_VALUE)
			{
				if (!(last_tk = last_tk->parent))
				{
					throw json_unexpected_close(ERROR_INFO(),line,pos);
				}
			}
			break;
		case '\"':
			// it is a key if parent is a object, if parent is primitive then it is a value
			newToken(token, JSN_STRING, strList);
			break;
		case ':':
			next_tok_rel = JSON_CHILD_VALUE;
			break;
		case ',':
			next_tok_rel = JSON_SIBLING;
			break;
		case '\t':
		case '\r':
		case '\n':
		case ' ':
			break;
#ifdef JSMN_STRICT
			/* In strict mode primitives are: numbers and booleans */
			case '-': case '0': case '1' : case '2': case '3' : case '4':
			case '5': case '6': case '7' : case '8': case '9':
			case 't': case 'f': case 'n' :
#else
			/* In non-strict mode every unquoted value is a primitive */
		default:
#endif
			newToken(token, JSN_PRIMITIVE, strList);

			break;

#ifdef JSMN_STRICT
			/* Unexpected char in strict mode */
			default:
			log_e("Unexpected char in strict mode")
			return ERROR_INVALID_VAL;
#endif

		}
	}
	// check that current node is the first
	if (last_tk != first_tk)
	{
		throw json_root_node_open(ERROR_INFO(),line,pos);
	}
#ifdef PARSE_DEBUG
	strList.Print();
#endif
}

/*
 Parse primitive, by creating a child node for the current node
 */
unsigned int JsonParse::ParsePrimitive(jsntok_t *token, StrList &strList)
{
	int start = pos;
	// look for end of primitive
	for (; json[pos] != '\0'; pos++)
	{
		// check char range: must be >=32 <=127
		if (json[pos] < 32 || json[pos] >= 127)
		{
			throw json_invalid_char(ERROR_INFO(),line,pos);
		}
		switch (json[pos])
		{
#ifndef JSMN_STRICT
		/* In strict mode primitive must be followed by "," or "}" or "]" */
		case ':':
#endif
		case '\t':
		case '\r':
		case '\n':
		case ' ':
		case ',':
		case ']':
		case '}':
			break;
		default:
			continue;
		}
		break;
	}

#ifdef JSMN_STRICT
	/* In strict mode primitive must be followed by a comma/object/array */
	if (!json[pos]) return ERROR_PART;
#endif
	if (start + sizeof(token->c) + sizeof(token->d) > pos)
	{
		token->type |= JSN_SHORT_VALUE;
		*token->c = 0;
		strncat(token->c, &json[start], pos - start);
	}
	else
		strList.push(&json[start], pos - start, token->val);

	pos--;	// stay before end mark, may be necessary to close some parent in case of ]}
}

/*
 get json string, it can be a key or value
 Get token after parse, if something wrong whole process go down
 */

void JsonParse::ParseString(jsntok_t *token, StrList &strList)
{
	// jump " char
	pos++;
	int start = pos;
	/* Skip starting quote */
	for (; json[pos] != '\0'; pos++)
	{
		char c = json[pos];

		/* Quote: end of string */
		if (c == '\"')
		{
			if (start + sizeof(token->c) + sizeof(token->d) > pos)
			{
				token->type |= JSN_SHORT_VALUE;
				*token->c = 0;
				strncat(token->c, &json[start], pos - start);
			}
			else
				strList.push(&json[start], pos - start, token->val);
			return;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\')
		{
			pos++;
			switch (json[pos])
			{
			/* Allowed escaped symbols */
			case '\"':
			case '/':
			case '\\':
			case 'b':
			case 'f':
			case 'r':
			case 'n':
			case 't':
				break;
				/* Allows escaped symbol \uXXXX */
			case 'u':
				/* FIX */
				break;
				/* Unexpected symbol */
			default:
				throw json_invalid_char(ERROR_INFO(),line,pos);
			}
		}
	}
}

void JsonParse::newToken(jsntok_t * &token, unsigned char type, StrList &strList)
{
	mem->Get(sizeof(*token), (void**) &token);
	token->next = 0;
	token->child = 0;
	token->type = type;
	if (type & JSN_OBJECT)
	{
#ifdef PARSE_DEBUG
		log_d("object : ")
#endif
	}
	if (next_tok_rel == JSON_CHILD_VALUE)
	{
		token->type |= JSN_VALUE;
	}
	// it is a first token it has not parent
	if (!first_tk)
	{
		first_tk = token;
		token->parent = 0;
		next_tok_rel = JSON_CHILD;
		last_tk = token;
	}
	else
	{
		// it is the first sibling
		if ((next_tok_rel == JSON_CHILD) || (next_tok_rel == JSON_CHILD_VALUE))
		{
#ifdef PARSE_DEBUG
			log_d("child : ")
#endif
			token->parent = last_tk;
			last_tk->child = token;
		}
		// it get parent from her sibling
		else if (next_tok_rel == JSON_SIBLING)
		{
#ifdef PARSE_DEBUG
			log_d("sibling : ")
#endif
			token->parent = last_tk->parent;
			last_tk->next = token;
		}
	}
	// primitive or string node can't be use like last node if it is a value
	// primitive with a primitive parent  is a value
	// only object or primitive with parent of type object can be use like last node
	if ((type & JSN_OBJECT) || !(token->type & JSN_VALUE))
	{
		// an object or not a value
#ifdef PARSE_DEBUG
		log_d("switched : ")
#endif
		last_tk = token;
		next_tok_rel = JSON_CHILD;
	}
	else
	{
		// if a node can have child then her parent must have a sibling
		next_tok_rel = JSON_SIBLING;
	}
	if (type == JSN_STRING)
	{
		ParseString(token, strList);
	}
	else if (type == JSN_PRIMITIVE)
	{
		ParsePrimitive(token, strList);
	}
#ifdef PARSE_DEBUG
	if ((uir == NO_ERR) && !(token->type & JSN_OBJECT))
	{
		log_d("=%s",getVal(token))
	}
#endif
}

void JsonParse::Print(jsntok_t *token)
{
	while (token)
	{
		if (token->type & JSN_VALUE)
			printf(":");
		if ((token->type & JSN_TYPE_MASK) == JSN_ARRAY)
		{
			printf("[");
		}
		else if ((token->type & JSN_TYPE_MASK) == JSN_OBJECT)
		{
			printf("{ ");
		}
		else if (((token->type & JSN_TYPE_MASK) == JSN_STRING) || ((token->type & JSN_TYPE_MASK) == JSN_PRIMITIVE))
		{
			printf("\"%s\"", getVal(token));
		}

		if (token->child)
			Print(token->child);

		if ((token->type & JSN_TYPE_MASK) == JSN_ARRAY)
		{
			printf("]");
		}
		else if ((token->type & JSN_TYPE_MASK) == JSN_OBJECT)
		{
			printf("}\n");
		}
		if (token->next)
			printf(",");
		token = token->next;
	}
}

// compare
bool JsonParse::isEqual(jsntok_t * token, const char* val)
{
	if (token->type & JSN_OBJECT)
		return false;
	return (strcmp(val, getVal(token)) == 0);
}
/*
 Extract all usefully data from json object using descriptors
 token must be a json object
 Start token must be a json object
 object will be returned as token pointer.
 */
void JsonParse::getValues(jsntok_t * token, struct _jsn_desc *desc)
{
	struct _jsn_desc *cdesc = desc;	//current descriptor
	unsigned int j;

	// clear current values
	for (j = 0; cdesc[j].key; j++)
	{
		cdesc[j].val = 0;
		cdesc[j].token = 0;
	}
	if (!token)
		return;

	// check start token
	if (!(token->type & JSN_OBJECT))
		return;

	// go to first child and then use sibling
	token = token->child;
	while (token)
	{
		// look for descriptor of this token
		for (j = 0; cdesc[j].key; j++)
		{
			if (!isEqual(token, cdesc[j].key))
				continue;
			// goto value token
			if (token->child)
			{
				if (token->child->type & JSN_OBJECT)
				{
					if (cdesc[j].child)
					{
						getValues(token->child, cdesc[j].child);
						break;
					}
					else
						cdesc[j].token = token->child;
				}
				else
					cdesc[j].val = getVal(token->child);
			}
			break;
		}
		token = token->next;
	}
}
