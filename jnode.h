/*
 * jnode.h
 *
 *  Created on: 9 Nov 2013
 *      Author: lester
 */

#ifndef JNODE_H_
#define JNODE_H_

/*
 * TODO
 * A json node parser must use recursive function
 * json node has next node and value of type object, string, primitive
 * object and array are values
 *
 *
 */

/*
 * define node type
 */
enum
{
	JV2_OBJECT = 0,	// object node getFirstKey, lookkey
	JV2_ARRAY,	    // array getFirstValue
	JV2_PRIMITIVE,	// getcontent
	JV2_STRING,		// getcontent
};

// extra flags
#define JV2_DATA_PTR 	1 	// node content is a pointer to string
#define JV2_KEY_NODE	2	// it is a key string node
#define JV2_F_OBJECT	4	// it is a object the size is reduce

template<class J>
class jnodev2
{
public:
	/*
	 * Creation routines
	 */
	// Create a pointer node
	static J*	create(const char * s);
	// create a inside content node
	static J*	create(char* s,unsigned short size);
	// create a inside content
	static J* create(char* s);
	// create a node for object
	static J* create();

	void setArrayType();
	void setObjectType();
	void setPrimitiveType();
	void setStringType();
	void setKeyFlag();
	/*
	 * only on string and primitive
	 */
	const char* getchar()
	{
		if (!this)
			return "";
		if ((type != JV2_PRIMITIVE) && (type != JV2_STRING))
			return "";
		if (flag & JV2_DATA_PTR)
			return pval;
		return val;
	}
	/*
	 * get value node
	 */
	J* getValue()
	{
		if (this && (flag & JV2_KEY_NODE))
			return valnode;
		return 0;
	}
	// Only for objects
	J* getFirstKey()
	{
		if (this && (type == JV2_OBJECT))
			return valnode;
		return 0;
	}
	// Only for arrays
	J* getFirstValue()
	{
		if (this && (type == JV2_ARRAY))
			return valnode;
		return 0;
	}
	// for everything
	J* getNext()
	{
		if (this)
			return next;
		return 0;
	}

private:
	void init()
	{
		type = 0;
		flag = 0;
		next = 0;
		valnode = 0;
		pval = 0;
	}
	unsigned char type;
	unsigned char flag;
	J* next;
	J* valnode;	// use by objects, array, keystring
	union
	{
		// use by primitive or string nodes
		char* pval;
		char val[0];
	};
};


#include "OneRelease.h"

#define JNODE_VALUE		1	// bit mask for token to indicate that is a value, a object can be a value
#define JNODE_KEY			2	// bit mask for key node
#define JNODE_ARRAY		8	// Array object
#define JNODE_OBJECT		32	// Object
#define JNODE_STRING		16				// string value
#define JNODE_PRIMITIVE 	24				// primitive value
#define JNODE_TYPE_MASK 	(255-3)			// mask for extract type

/*
 * There is non-release allocator and release allocator
 * a node using non-release would not implement release function
 * a node using release allocator will implement release function
 * a node can not have virtual functions
 * the parser will received a node class type
 */

/*
 * Json Node base class using a JsonNode template and a allocator template
 */
template<class J, class A>
class JNodeBase
{
public:
	/*
	 * object or array nodes can be values at the time
	 */
	inline void setValueFlag()
	{
		type |= JNODE_VALUE;
	}
	/*
	 * check if node is a object node
	 */
	bool isObject()
	{
		return ((type & JNODE_TYPE_MASK) == JNODE_OBJECT);
	}
	inline bool isArray()
	{
		return ((type & JNODE_TYPE_MASK) == JNODE_ARRAY);
	}
	/*
	 * Check if node is a value node
	 */
	inline bool isValue()
	{
		return (type & JNODE_VALUE);
	}
	inline bool isString()
	{
		return (type & JNODE_STRING);
	}
	inline bool isPrimitive()
	{
		return (type & JNODE_PRIMITIVE);
	}
	/*
	 * Check value
	 */
	bool isEqual(const char* v)
	{
		if ((this == 0) || (*value == 0) || (v == 0))
			return false;
		return (strcmp(v, value) == 0);
	}
	/*
	 * insert sibling node at the beginning
	 * it is only allowed for key element
	 */
	void insertNext(J* node)
	{
		if (node == 0)
			throw error_api(ERROR_INFO(),api_error::get_wrong_param);
		node->setNext(this->getNext());
		this->setNext(node);
	}
	/*
	 * insert child at the beginning of list.
	 */
	void addChild(J* node)
	{
		if ((node == 0) || (this == 0))
			return;
		if (this->child)
		{
			this->child->insertNext(node);
		} else
			this->setChild(node);
	}

// getter and setter
	J* getNext()
	{
		return (this) ? sibling : 0;
	}
	J* getChild()
	{
		return (this) ? child : 0;
	}
	unsigned char getType()
	{
		return (this) ? type : 0;
	}
	void setNext(J* node)
	{
		if (this)
			sibling = node;
	}
	void setChild(J* node)
	{
		if (this)
			child = node;
	}
	const char *getValue()
	{
		return (this) ? value : "";
	}

	inline void release(A &alloc)
	{
		if (A::canFree() && this)
		{
			this->getChild()->release(alloc);
			this->getNext()->release(alloc);
			alloc.free(this);
		}
	}
	/*
	 * get key node with this name
	 */
	J* getKeyNode(const char *name)
	{
		CHECK_RET_CODE(this != 0, 0);
		// go to first child and then use sibling
		J* node = this->getChild();
		while (node)
		{
			if (node->isEqual(name))
				return node;
			node = node->getNext();
		}
		return 0;
	}
	/*
	 * get value node with this name
	 */
	J* getValueNode(const char *name)
	{
		CHECK_RET_CODE(this != 0, 0);
		// go to first child and then use sibling
		J* node = this->getChild();
		while (node)
		{
			if (node->isEqual(name))
				return node->getChild();
			node = node->getNext();
		}
		return 0;
	}
	/*
	 * Print json to object that support push
	 */
	template<class P>
	void print(P &p)
	{
		JNodeBase<J, A>* n = this;
		while (n)
		{
			if (n->isValue())
				p.push(":");
			if (n->isArray())
			{
				p.push("[");
			} else if (n->isObject())
			{
				p.push("{");
			} else if (n->isString())
			{
				p.push("\"");
				p.push(n->getValue());
				p.push("\"");
			} else if (n->isPrimitive())
			{
				p.push(n->getValue());
			}
			if (n->getChild())
				n->getChild()->print(p);

			if (n->isArray())
			{
				p.push("]");
			} else if (n->isObject())
			{
				p.push("}");
			}
			if (n->getNext())
				p.push(",");
			n = n->getNext();
		}
	}
	/*
	 * Remove child node with value
	 */
	void removeKey(const char* key, A &mem)
	{
		J* n = this->getChild();
		if (n->isEqual(key))
		{
			setChild(n->getNext());
			n->setNext(0);
			n->release(mem);
			return;
		}
		while (n)
		{
			if (n->sibling && n->sibling->isEqual(key))
			{
				J* old = n->getNext();
				n->setNext(old->getNext());
				old->setNext(0);
				old->release(mem);
				continue;	// all nodes with same name will be remove
			}
			n = n->getNext();
		}
	}

protected:
	void init()
	{
		sibling = 0;
		child = 0;
		type = 0;
		value[0] = 0;
	}

	J *sibling;
	J *child;
	unsigned char type;
	char value[1];
};

/*
 * this object can not be instanced, it most be allocate using some memory allocator
 * there is a specialization for one release memory allocator to avoid call release on every node
 * Actually it is a memory block with some functionality to manage internal data
 * it can not be instated
 */

template<class A = OneRelease>
class JsonNode: public JNodeBase<JsonNode<A>, A>
{
	/*
	 * avoid compiler creating defaults constructors
	 */
private:
	JsonNode();
	~JsonNode();
	JsonNode(const JsonNode&);
	JsonNode& operator =(const JsonNode&);

public:
	/*
	 * Create a pair node value from string
	 */
	inline static JsonNode *createPair(const char* key, const char* value, A &alloc)
	{
		JsonNode *n = createString(key, strlen(key), alloc);
		CHECK_RET_CODE(n != 0, 0);
		n->setChild(createString(value, strlen(value), alloc));
		CHECK_RET_CODE(n->getChild() != 0, n);
		n->getChild()->setValueFlag();
		return n;
	}
	/*
	 * Create a node of type object
	 */
	inline static JsonNode *createObject(A &alloc)
	{
		return create(JNODE_OBJECT, alloc);
	}
	/*
	 * Create a node of type array
	 */
	inline static JsonNode *createArray(A &alloc)
	{
		return create(JNODE_ARRAY, alloc);
	}
	/*
	 * Create a primitive node
	 */
	inline static JsonNode *createPrimitive(const char* str, unsigned short size, A &alloc)
	{
		return create(JNODE_PRIMITIVE | JNODE_VALUE, str, size, alloc);
	}
	static JsonNode *createPrimitive(const char* str, A &alloc)
	{
		return create(JNODE_PRIMITIVE | JNODE_VALUE, str, strlen(str), alloc);
	}
	/*
	 * Create a String node
	 */
	inline static JsonNode *createString(const char* str, unsigned short size, A &alloc)
	{
		return create(JNODE_STRING, str, size, alloc);
	}

	static JsonNode *createString(const char* str, A &alloc)
	{
		return create(JNODE_STRING, str, strlen(str), alloc);
	}

private:

	static JsonNode *create(unsigned char type, A &alloc)
	{
		JsonNode* p = (JsonNode*) alloc.alloc(sizeof(JsonNode));
		CHECK_RET_CODE(p != 0, 0);
		p->init();
		p->type = type;
		return p;
	}

	static JsonNode *create(unsigned char type, const char* str, unsigned short size, A &alloc)
	{
		JsonNode* p = (JsonNode*) alloc.alloc(sizeof(JsonNode) + size);
		CHECK_RET_CODE(p != 0, 0);
		p->init();
		p->type = type;
		memcpy(p->value, str, size);
		p->value[size] = 0;
		return p;
	}
};

#endif /* JNODE_H_ */
