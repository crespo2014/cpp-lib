/*
 * config_stack.h
 *
 *  Created on: 1 May 2014
 *      Author: lester
 */

#ifndef CONFIG_STACK_H_
#define CONFIG_STACK_H_

#include "utils.h"
#include "os.h"
#include <string>
#include "log.h"
#include "fstring.h"

DEFINE_BASE_EXCEPTION(error_reflex);
DEFINE_DERIVED_EXCEPTION(error_too_many_root, error_reflex, "There are more than one root element");
DEFINE_DERIVED_EXCEPTION(error_root_missmatch, error_reflex, "Root element name does not match");
DEFINE_DERIVED_EXCEPTION(error_not_child, error_reflex, "This attribute does not support children ");
DEFINE_DERIVED_EXCEPTION(error_not_value, error_reflex, "An object does not support set a value");
DEFINE_DERIVED_EXCEPTION(error_missmatch_closed, error_reflex, "A closed name does not match open one");
DEFINE_DERIVED_EXCEPTION(error_not_attribute, error_reflex, "The attribute is not in the list");
DEFINE_DERIVED_EXCEPTION(error_not_reflex, error_reflex, "Failed to factory a new reflex object");

/*
 * This a reflexion object for reading configuration from files.
 *
 * a xml sax handler connector is is also implemented to supply this object with data
 */

namespace reflex
{
// Data coming from configuration files will be validate again this types
enum attr_type
{
	t_object,    //
	t_string,    //
	t_float,	//
	t_double,
	t_unsigned,    //
	t_signed,    //
};

struct obj_descriptor;

// Object will describe its internal data using this structure
struct attr_descriptor
{
	//const char* const name;
	fstring name;
	const attr_type type;
	const unsigned id;			// use internally by the class
	const struct obj_descriptor* desc;
};

struct obj_descriptor
{
	const unsigned attr_count;
	const struct attr_descriptor * const attr;
};

// call back function for

/*
 * each object must implement a function called type() to get a name for this type
 */
class Reflex
{
public:

	// use this for iteration over objects inside configuration interfaces (Serialization)
	class CallBack
	{
	public:
		virtual void operator()(Reflex* c) = 0;
	};
	virtual const struct obj_descriptor* getDescriptor() const = 0;

	virtual bool setValue(unsigned id, const char* val) = 0;

	virtual bool getValue(unsigned id, std::string & val) const = 0;

	virtual Reflex* createInstance(int id) = 0;

	// validate object status
	virtual bool validate()
	{
		return true;
	}
	// execute a function for each object of type
	virtual bool for_each(unsigned id, CallBack& cb)
	{
		return false;
	}
protected:
	Reflex()
	{
	}
	/*
	 Reflex(const Reflex&) = delete;
	 Reflex(const Reflex&&) = delete;
	 Reflex & operator =(const Reflex&) = delete;
	 Reflex & operator =(const Reflex&&) = delete;
	 */
	~Reflex()
	{

	}
	// Usefull functions to read different to convert from string
	static void get(const char* v, unsigned &u)
	{
		sscanf(v, "%d", &u);
	}
	static void get(const char* v, char &u)
	{
		u = *v;
	}
	static void get(const char* v, float &f)
	{
		sscanf(v, "%f", &f);
	}
	static void get(const char* v, std::string &s)
	{
		s = v;
	}
	static void get(const char* v, bool &b)
	{
		_status_base<char> st
		{ 'e' };
		// status machine
		if (*v == '0')
			b = false;
		else
			b = true;
	}
	template<typename T>
	static void set(std::string &out, T &in)
	{
		out = std::to_string(in);
	}

};

/*
 * A handler for reflexion. a reflex stack must implement it
 */
class Handler
{
public:
	/*
	 * A new item is open, data or subitems will came soon
	 */
	void OnItem(const char* name);
	/*
	 * A value for the current item is read
	 */
	void OnValue(const char* val);
	/*
	 nulptr also means that the item has been close without data inside
	 also it means that is not necessary make validation of name
	 *
	 */
	void OnCloseItem(const char *name = nullptr);
	/*
	 * A item attribute ha been found it is usefull on xml
	 */
	/*
	 void OnAttribute(const char* name, const char* val)
	 {

	 }
	 */
protected:
	~Handler()
	{

	}
};

/*
 * Object to received notification of incoming data
 */
class ReflexStack: public Handler
{
	/*
	 * Each item or attribute is a stack element
	 */
	class _stack
	{
		friend class ReflexStack;
		Reflex* const r;							// parent object for simple type, or current object for type object
		const struct obj_descriptor* const desc;	// descriptor cache
		const struct attr_descriptor* const attr;    // current open attribute

		_stack(Reflex* r, const struct obj_descriptor* d, const struct attr_descriptor* a) :
				r(r), desc(d), attr(a)
		{
		}
	};

	struct attr_descriptor attr;
	_stack root;
	_stack* current;
	std::vector<_stack> stack;
	unsigned ignoredCount = 0;		// how many nodes are ignore
public:
	// construct using first object in stack
	ReflexStack(const char* name, Reflex& r) :
			attr
			{ name, t_object, 0 }, root(&r, r.getDescriptor(), &attr), current(&root)
	{
		stack.reserve(20);
	}
	// Incoming data functions
	void OnItem(const char* name)
	//void OnItem(const fstring& name)
	{
		// check for item currently ignoring
		if (ignoredCount)
		{
			log_e("the item %s is ignored", name);
			ignoredCount++;
			return;
		}
		if (!current)
			return_exception(error_too_many_root);
		// root element is compare again name.
		if (current == &root)
		{
			//if (attr.name = name)
			//if (strcmp(name, attr.name) != 0)
			if (attr.name != name)
			{
				log_e("root item name does not match name %s", name);
				return_exception(error_root_missmatch);
			}
			stack.push_back(root);
			current = &(*stack.rbegin());
		}
		else
		{
			// a child item in only valid for attribute of type object
			if (current->attr->type != t_object)
			{
				ignoredCount++;
				return_exception(error_not_child);
			}

			// find item on list
			unsigned char i = 0;
			//while (i < current->desc->attr_count && name !=  current->desc->attr[i].name)
			while (i < current->desc->attr_count && current->desc->attr[i].name != name /*strcmp(name, current->desc->attr[i].name) != 0*/)
			{
				++i;
			}
			if (i == current->desc->attr_count)
			{
				log_e("item %s is not on %s", name, current->attr->name.c_str());
				ignoredCount++;
			}
			else
			{
				// attributes
				Reflex* re = (current->desc->attr[i].type == t_object) ? current->r->createInstance(current->desc->attr[i].id) : current->r;
				if (re == nullptr)
				{
					log_e("not object for item %s in %s", name, current->attr->name.c_str());
					return_exception(error_not_reflex);
					ignoredCount++;
				}
				else
				{
					stack.push_back(_stack(re, re->getDescriptor(), &current->desc->attr[i]));
					current = &(*stack.rbegin());
				}
			}
		}
	}
	/*
	 *
	 */
	void OnValue(const char* val)
	{
		if (ignoredCount)
			return;
		if (!current)
		{
			//log_e("there is not active attribute");
			return_exception(error_not_value);
		}
		if (current->attr->type == t_object)
		{
			log_e("object %s does not support value %s", current->attr->name.c_str(), val);
			return_exception(error_not_value);
		}
		else
			current->r->setValue(current->attr->id, val);
	}
	/*
	 *
	 */
	void OnCloseItem(const char *name)
	//void OnCloseItem(const fstring& name)
	{
		if (ignoredCount)
		{
			ignoredCount--;
			return;
		}
		//if (!current || !stack.size() || ((name.size()) && (name !=  current->attr->name))) //&& strcmp(name, current->attr->name) != 0))
		if (!current || !stack.size() || ( name && current->attr->name != name /*strcmp(name, current->attr->name) != 0*/))
		{
			log_e("closed item %s does not match open item %s", name, current->attr->name.c_str());
			return_exception(error_missmatch_closed);
		}
		stack.pop_back();
		if (!stack.size())
			current = nullptr;    // root element finish
		else
			current = &(*stack.rbegin());
	}
};

}

#endif /* CONFIG_STACK_H_ */
