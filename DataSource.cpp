/*
 * DataSource.cpp
 *
 *  Created on: 15 Apr 2014
 *      Author: lester
 */

#include "DataSource.h"

enum
{
	FIELD_TYPE, //
	FIELD_CONNECTION_TYPE,
	FIELD_DESCRIPTION,
	FIELD_NODES,
	ELEMENT_A
};

static struct _configurable_descriptor desc[] =
{
{ "type", FIELD_TYPE, TYPE_STRING },
{ "pci", ELEMENT_A, TYPE_OBJECT } };

struct _configurable_descriptor_list desc_list
{ sizeof(desc) / sizeof(*desc), desc };

DataSource::DataSource()
{
	// TODO Auto-generated constructor stub

}

DataSource::~DataSource()
{
	// TODO Auto-generated destructor stub
}

const struct _configurable_descriptor_list& DataSource::getDescriptor()
{
	return desc_list;
}

int DataSource::setValue(unsigned id, double d)
{
	if (id == FIELD_DESCRIPTION)
	{
		// check value
	}
	else
	{
		return -1;	// unknown value or invalid type
	}
	return 0;
}

Configurable* DataSource::getNewObject(int type)
{
	if (type == ELEMENT_A)
	{
		list.push_back(A());
		return &(*list.rbegin());
	}
	return nullptr;
}
