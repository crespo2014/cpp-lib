/*
 * DataSource.h
 *
 *  Created on: 15 Apr 2014
 *      Author: lester
 */

#ifndef DATASOURCE_H_
#define DATASOURCE_H_

#include "configurable.h"
#include <list>


class A : public Configurable
{
	virtual const struct _configurable_descriptor_list& getDescriptor() const
	{
		static struct _configurable_descriptor_list l {0,nullptr};
		return l;
	}
};


class DataSource: public Configurable
{

public:
	DataSource();
	virtual ~DataSource();


	virtual const struct _configurable_descriptor_list& getDescriptor();
	virtual int setValue(unsigned id, double d);
	virtual Configurable* getNewObject(int type);

private:
	std::list<A> list;

};

#endif /* DATASOURCE_H_ */
