/*
 * jparse.h
 *
 *  Created on: 9 Nov 2013
 *      Author: lester
 */

#ifndef JPARSE_H_
#define JPARSE_H_


#include "jnode.h"

/*
 * Application getting data from json must use this structure
 * to get more than one data at the time
 */
template<class N = JsonNode<OneRelease> >
struct _json_desc
{
	const char* key;		// key value
	N *node;		// child node or value node
	struct _json_desc *child;	// get data from child objects
};

/*
 * Get data from json object using a class as descriptor
 */

template<class N = JsonNode<OneRelease> >
class JsonNodeDesc
{
public:
	JsonNodeDesc(const char *key)
	{
		this->key = key;
		node = 0;
		child = 0;
	}
	JsonNodeDesc(const char *key, JsonNodeDesc** childs)
	{
		this->key = key;
		node = 0;
		child = childs;
	}
	JsonNodeDesc *getNext()
	{
		return &this[1];
	}
	JsonNodeDesc **getChild()
	{
		return child;
	}
	const char* getKey()
	{
		return key;
	}
	void setNode(N *node)
	{
		this->node = node;
	}
private:
	const char* key;		// key value
	N *node;			// child node or value node
	JsonNodeDesc **child;	// get data from child objects
};





/*
 * Json parser with different parse options
 * TODO:
 * parse a const char* and create node with const char* as values
 */
template<class N = JsonNode<OneRelease>, class A = OneRelease>
class Json
{
public:
	Json()
	{
		root = 0;
	}
	~Json()
	{

	}
	static unsigned short parse(const char* json, unsigned short size,N &root, A &alloc)
	{
		return 0;
	}
	unsigned short parse(const char* json, unsigned short size, A &alloc)
	{
		// define next token relationship
		enum
		{
			NODE_KEY,		// key node after { , set as current
			NODE_CHILD, 	// child after [ , set as current
			NODE_VALUE,		// value node after : it can not be current
			NODE_SIBLING	// after , or after object close
		};

		N* nodeStack[30];
		unsigned short nodeStackPos = 0;
		N* cnode;	// current node
		unsigned char node_rel = NODE_VALUE;	// new node relationship
		unsigned char c;

		unsigned short pos = 0;	// parsing pos
		//unsigned short npos;
		if (size == 0)
			size = 0xFFFF;

		// look at root node start
		for (; json[pos] && pos < size; pos++)
		{
			c = json[pos];
			if (c <= ' ')
				continue;
			CHECK_RET_CODE(c == '{', ERR_PROTOCOL);
			root = N::createObject(alloc);
			node_rel = NODE_KEY;
			cnode = root;
			nodeStack[nodeStackPos] = cnode;
			nodeStackPos++;
			pos++;
			break;
		}
		CHECK_RET_CODE(root != 0, ERR_PROTOCOL);

		for (; json[pos] && (pos < size); pos++)
		{
			c = json[pos];
			if ((c == '\t') || (c == '\r') || (c == '\n') || (c == ' '))
				continue;
			/*
			 * Array or object start
			 */
			if ((c == '{') || (c == '['))
			{
				// object is not allowed for key nodes
				CHECK_RET_CODE(node_rel != NODE_KEY, ERR_PROTOCOL);
				N* nnode;
				if (c == '{')
					nnode = N::createObject(alloc);
				else
					nnode = N::createArray(alloc);
				CHECK_RET_CODE(nnode != 0, ERR_MEMORY);
				/*
				 * if a object is a value then the parent node must be push on stack
				 * when object is close parent node will be pop from stack
				 */
				if (node_rel == NODE_VALUE)
				{
					nnode->setValueFlag();
					CHECK_RET_CODE(nodeStackPos < sizeof(nodeStack) / sizeof(*nodeStack), ERR_PROTOCOL);
					nodeStack[nodeStackPos] = cnode;
					nodeStackPos++;
				}
				if (node_rel == NODE_SIBLING)
					cnode->setNext(nnode);
				else
					cnode->setChild(nnode);
				// any node after object must be a child
				if (c == '{')
					node_rel = NODE_KEY;
				else
					node_rel = NODE_CHILD;
				cnode = nnode;
				/*
				 * Push object on stack and wait for close mark to pop
				 */
				CHECK_RET_CODE(nodeStackPos < sizeof(nodeStack) / sizeof(*nodeStack), ERR_PROTOCOL);
				nodeStack[nodeStackPos] = cnode;
				nodeStackPos++;
			} else if ((c == '}') || (c == ']'))
			{
				/*
				 * A object can not be close if a value is required
				 */
				CHECK_RET_CODE(node_rel != NODE_VALUE, ERR_PROTOCOL);
				/*
				 *  pop object from stack and check type
				 */
				CHECK_RET_CODE(nodeStackPos > 0, ERR_PROTOCOL);
				nodeStackPos--;
				cnode = nodeStack[nodeStackPos];
				if (c == '}')
					CHECK_RET_CODE(cnode->isObject(), ERR_PROTOCOL);
				else
					CHECK_RET_CODE(cnode->isArray(), ERR_PROTOCOL);
				/*
				 * if closed object is a value then pop parent from stack
				 */
				if (cnode->isValue())
				{
					CHECK_RET_CODE(nodeStackPos > 0, ERR_PROTOCOL);
					nodeStackPos--;
					cnode = nodeStack[nodeStackPos];
				}
				node_rel = NODE_SIBLING;
			} else if (c == '\"')
			{
				pos++;
				unsigned short npos = pos;
				CHECK_RET_CODE(parseString(json, pos, size) == NO_ERR, ERR_PROTOCOL);
				N *nnode = N::createString(&json[npos], pos - npos, alloc);
				CHECK_RET_CODE(nnode != 0, ERR_MEMORY);
				if (node_rel == NODE_VALUE)
					nnode->setValueFlag();
				/*
				 *  node can be sibling, child key or child value
				 */
				if (node_rel == NODE_SIBLING)
				{
					cnode->setNext(nnode);
					cnode = nnode;
				} else
				{
					cnode->setChild(nnode);
					if (node_rel == NODE_KEY)
						cnode = nnode;
				}
				node_rel = NODE_SIBLING;
				/*
				 * end of string is the character ", it will be jump at for loop
				 */
			} else if (c == ':')
			{
				node_rel = NODE_VALUE;
			} else if (c == ',')
			{
				node_rel = NODE_SIBLING;
			} else
			{
				/*
				 * Start of primitive node
				 */
				//CHECK_RET_CODE(node_rel == NODE_VALUE, ERR_PROTOCOL); // primitives on array
				unsigned short npos = pos;
				CHECK_RET_CODE(parsePrimitive(json, pos, size) == NO_ERR, ERR_PROTOCOL);
				N *nnode = N::createPrimitive(&json[npos], pos - npos, alloc);
				CHECK_RET_CODE(nnode != 0, ERR_MEMORY);

				// node can be sibling or child key or child value
				if (node_rel == NODE_SIBLING)
				{
					cnode->setNext(nnode);
					cnode = nnode;
				} else
				{
					cnode->setChild(nnode);
					if (node_rel != NODE_VALUE)
						cnode = nnode;
				}
				node_rel = NODE_SIBLING;
				// end of primitive must be checked
				pos--;
			}
		}
		// check that current node is the first
		CHECK_RET_CODE(nodeStackPos == 0, ERR_PROTOCOL);
		return NO_ERR;
	}
	void release(A &alloc)
	{
		if (root)
		{
			root->release(alloc);
			root = 0;
		}
	}
	static unsigned short calcStringSize(N *node)
	{
		unsigned short size = 0;
		while (node)
		{
			if (node->isValue())
				size += 1;
			if (node->isArray())
			{
				size += 1; 	//printf("[");
			} else if (node->isObject())
			{
				size += 1;	//printf("{ ");
			} else if (node->isString())
			{
				size += (2 + strlen(node->getValue()));		//printf("\"%s\"", node->getValue());
			} else if (node->isPrimitive())
			{
				size += (strlen(node->getValue())); 		//printf("%s", node->getValue());
			}

			if (node->getChild())
			{
				size +=calcStringSize(node->getChild()); //Print(node->getChild());
			}

			if (node->isArray())
			{
				size += 1;	//printf("]");
			} else if (node->isObject())
			{
				size += 1;	//printf("}\n");
			}
			if (node->getNext())
			{
				size += 1;	//printf(",");
			}
			node = node->getNext();
		}
		return size;

	}
	static void Print(N *node)
	{
		while (node)
		{
			if (node->isValue())
				printf(":");
			if (node->isArray())
			{
				printf("[");
			} else if (node->isObject())
			{
				printf("{ ");
			} else if (node->isString())
			{
				printf("\"%s\"", node->getValue());
			} else if (node->isPrimitive())
			{
				printf("%s", node->getValue());
			}

			if (node->getChild())
				Print(node->getChild());

			if (node->isArray())
			{
				printf("]");
			} else if (node->isObject())
			{
				printf("}\n");
			}
			if (node->getNext())
				printf(",");
			node = node->getNext();
		}
	}
	/*
	 * extract values from node using a descriptor
	 * json node must be a parent object node
	 */
	static void getValues(N *n, struct _json_desc<N>* desc)
	{
		struct _json_desc<N> *cdesc = desc;	//current descriptor
		unsigned int j;

		if ((!n) || (!n->isObject()))
			return;

		// go to first child and then use sibling
		n = n->getChild();
		/*
		 * look at from descriptors
		 */
		for (j = 0; cdesc[j].key; j++)
		{
			for (; n; n = n->getNext())
			{
				if (n->isEqual(cdesc[j].key))
				{
					cdesc[j].node = n->getChild();
					if ((cdesc[j].node != 0) && (cdesc[j].child != 0))
						getValues(n->getChild(), cdesc[j].child);
					break;
				}
			}
		}
	}
	static void getValues(N *n, JsonNodeDesc<N>** desc)
	{
		CHECK_RET_VOID((n != 0) && n->isObject());

		// go to first child and then use sibling
		n = n->getChild();
		/*
		 * look at from descriptors
		 */
		for (JsonNodeDesc<N>* d = *desc; d && d->getKey(); d = d->getNext())
		{
			for (; n; n = n->getNext())
			{
				if (n->isEqual(d->getKey()))
				{
					d->setNode(n->getChild());
					if (d->getChild())
						getValues(n->getChild(), d->getChild());
					break;
				}
			}
		}
	}
	/*
	 * Look for node value
	 */
	static N* getNode(const char* key, N *node)
	{
		CHECK_RET_CODE(node && node->isObject(), 0);
		// go to first child and then use sibling
		node = node->getChild();
		while (node)
		{
			if (node->isEqual(key))
				return node->getChild();
			node = node->getNext();
		}
		return 0;
	}
	inline N *getRoot()
	{
		return root;
	}
private:
	/*
	 * Extract string node from json message
	 */
	unsigned short parseString(const char* json, unsigned short &pos, unsigned short size)
	{
		for (; pos < size; pos++)
		{
			unsigned char c = json[pos];
			CHECK_RET_CODE(c >= 32 && c < 127, ERR_PROTOCOL);
			if (c == '\"')
				return NO_ERR;
			if (c == '\\')
			{
				pos++;
				c = json[pos];
				switch (c)
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
					CHECK_RET_CODE(false, ERR_PROTOCOL);
				}
			}

		}
		return ERR_PROTOCOL;
	}
	unsigned short parsePrimitive(const char* json, unsigned short &pos, unsigned short size)
	{
		for (; pos < size; pos++)
		{
			unsigned char c = json[pos];

			if ((c == ':') || (c == '\t') || (c == '\r') || (c == '\n') || (c == ' ') || (c == ',') || (c == ']') || (c == '}'))
			{
				return NO_ERR;
			}
			CHECK_RET_CODE(c >= 32 && c < 127, ERR_PROTOCOL);
		}
		return ERR_PROTOCOL;
	}
	N *root;
};
#endif /* JPARSE_H_ */
