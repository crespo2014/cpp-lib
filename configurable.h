/*
 * configurable.h
 *
 *  Created on: 15 Apr 2014
 *      Author: lester
 */

#ifndef CONFIGURABLE_H_
#define CONFIGURABLE_H_

#include <string>
/*
 * Abstract class that must be implement by every object
 * capable of be setup from configuration file
 */

enum	// type of elements
{
	TYPE_DOUBLE = 0,	//
	TYPE_STRING,
	TYPE_UNSIGNED,
	TYPE_SIGNED,
	TYPE_OBJECT
};
#define TYPE_OBJECT_MASK	16		// this mask must be bigger than the more type

struct _configurable_descriptor
{
	const char* field_name;			// case sensitive flag is need
	const unsigned type;
	const unsigned id;

};

struct _configurable_descriptor_list
{
	unsigned count;
	struct _configurable_descriptor *desc;
};

// do not use virtual destructor,
class Configurable
{
	virtual const struct _configurable_descriptor_list& getDescriptor() const = 0;

	virtual int setValue(unsigned id, double d)
	{
		return -1;// this function is not implemented by derived class, derived does not need to implement all set functions
	}
	virtual int setValue(unsigned id, const std::string& str)
	{
		return -1;
	}
	virtual int setValue(unsigned id, int d)
	{
		return -1;
	}
	virtual int setValue(unsigned id, unsigned d)
	{
		return -1;
	}
	// check for mandatory data missing
	virtual bool isValid()
	{
		return false;
	}
	// for value of type object we need enter in a recursive call
	virtual Configurable* getNewObject(int type)
	{
		return nullptr;
	}
};

#endif /* CONFIGURABLE_H_ */
