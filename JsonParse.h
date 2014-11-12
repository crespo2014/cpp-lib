/*
 * JsonParse.h
 *
 *  Created on: 24 Aug 2013
 *      Author: lester
 */

#ifndef JSONPARSE_H_
#define JSONPARSE_H_

#include "MemPage.h"
#include "StrList.h"
#include "os.h"
#include "exception_base.h"

// bit 0 ( 1 for json objects 0 = json value or primitive
// bit 1 ( 1 - json value)
#define JSN_OBJECT		1	// bit mask for object
#define JSN_VALUE		2	// bit mask for token to indicate that is a value
#define JSN_SHORT_VALUE	4	// bit for char value < sizeof(void*)
#define JSN_ARRAY		(8+JSN_OBJECT)	// Object and array
#define JSN_STRING		16				// string value
#define JSN_PRIMITIVE 	24				// primitive value

#define JSN_TYPE_MASK	0xF9	// this mask will remove control bits from json type
/*
 Basic json structure with minimal data
 Use for objects
 */
typedef struct type_
{
	char object :1;
	char value :1;
	char cvalue :1;
	char type :4;
} _json_type;

/*
 Head use for all json object type
 */
struct _json_head
{
	struct jsntok* parent;

	struct type_
	{
		char object :1;
		char value :1;
		char cvalue :1;
		char type :4;
	};
};

struct _json_obj_token: public _json_head
{
	struct jsntok* next;
	struct jsntok* child;
};

struct _json_val_token: public _json_head
{
	union
	{
		char* val;
		char c[1];
	};
};

// json token struct
// c and d will use to store short char string
// c cover alignment to char* and d cover char*

typedef struct jsntok
{
	struct jsntok* parent;
	struct jsntok* next;
	struct jsntok* child;
	unsigned char type;
	char c[sizeof(void*) - sizeof(unsigned char)];	// alignment
	union
	{
		char d[sizeof(char*)];	// for short string use this
		char* val;
	};
} jsntok_t;

// define next token relationship
enum
{
	JSON_CHILD = 0, // child or value token
	JSON_CHILD_VALUE,
	JSON_SIBLING
};

/*!
 Structure to get data from json object
 data will be returned as char* or token *
 json array will be ignore for child detection
 */
struct _jsn_desc
{
	const char* key;			// key to look for
	const char* val;			// value or
	struct jsntok *token;		// token if value is not a char* it is a object
	struct _jsn_desc *child;	// child descriptor

//	struct _jsn_desc *parent;	// use by function to avoid recursive
};

//   parent : val[key : value, next: value, next:value]

// a next object must be  key always.
// child can be anything

class JsonParse
{
public:
	JsonParse(MemPage *mem);
	void Parse(char* json, unsigned short size);
	static void getValues(jsntok_t * token, struct _jsn_desc *desc);
	static bool isEqual(jsntok_t * token, const char* val);
	void Print()
	{
		return Print(first_tk);
	}
	static inline jsntok_t *getNext(jsntok_t* token)
	{
		return (token) ? token->next : 0;
	}
	static inline jsntok_t *getChild(jsntok_t* token)
	{
		return (token) ? token->child : 0;
	}
	static inline char *getVal(jsntok_t* token)
	{
		return (token) ? ((token->type & JSN_SHORT_VALUE) ? (token->c) : (token->val)) : 0;
	}
	static inline unsigned char getType(jsntok_t* token)
	{
		return (token) ? (token->type & JSN_TYPE_MASK) : 0;
	}
	inline jsntok_t *getFirst()
	{
		return first_tk;
	}

	virtual ~JsonParse();
private:
	MemPage *mem;
	StrList *strList;
	jsntok_t *last_tk;	// last token in use, will be parent for child or it will contain value
	jsntok_t *first_tk;
	unsigned char next_tok_rel;	// next token relation
	unsigned short pos;
	char* json;
	uint32_t line =0;
	uint32_t line_pos = 0;
	unsigned int ParsePrimitive(jsntok_t *token, StrList &strList);
	void ParseString(jsntok_t *token, StrList &strList);
	void newToken(jsntok_t * &token, unsigned char type, StrList &strList);
	static void Print(jsntok_t *token);
};

#endif /* JSONPARSE_H_ */
