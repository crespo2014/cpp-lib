/*
 * utils.h
 *
 *  Created on: 2 May 2014
 *      Author: lester
 */

#ifndef UTILS_H_
#define UTILS_H_

/*
 * Status machine using nodes
 *
 * each node contain a value and a list of destinations. last destination is null
 *
 * last node does not contain next
 * a map for last node agains final values is need
 */

template<class T>
class _basic_node
{
	T val;
	_basic_node* next;
public:
	_basic_node(const T& v, _basic_node* next) :
			val(v), next(next)
	{

	}
	T& operator *()
	{
		return *val;
	}
};

template<class T, int N = 0>
class _status_base: public _basic_node<T>
{
	_basic_node<T>* const next[N + 1];
public:
	_status_base(const T& v) :
			_basic_node<T>(v, next)
	{
	}
};

template<class T>
class _status_base<T,0>: public _basic_node<T>
{

public:
	_status_base(const T& v) :
			_basic_node<T>(v, nullptr)
	{
	}
};

//template<class T
#endif /* UTILS_H_ */
