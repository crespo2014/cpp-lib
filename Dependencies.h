/*
 * Dependencies.h
 *
 *  Created on: 4 Jun 2014
 *      Author: lester
 */

#ifndef DEPENDENCIES_H_
#define DEPENDENCIES_H_

/*
 * Considerations:
 * A element could be connected twice to the same element
 * do not remove connection if it is still connected
 */
#include <stdint.h>
#include <vector>
#include <iostream>

template<class T>
class Dependencies
{
	class _node
	{
		friend class Dependencies<T> ;
		T* n;
		uint16_t level;
		std::vector<bool> depends;
	public:
		_node(T* t) :
				n(t), level(0)
		{

		}
	};
	std::vector<_node> nodes;
public:
	Dependencies()
	{

	}
	~Dependencies()
	{

	}
	/*
	 * Add a new element
	 */
	void add(T* v)
	{
		nodes.emplace_back(v);
		for (auto &n : nodes)
		{
			n.depends.resize(nodes.size(), false);
		}
	}
	/*
	 * it is not allowed to remove a node if another depends on its
	 */
	void del(T* n)
	{
		// get out node level must be
		uint16_t idx = 0;

		//  convert node to index
		for (; idx < nodes.size(); ++idx)
		{
			if (nodes[idx].n == n)
				break;
		}
		// remove if node was founded
		if (idx < nodes.size())
		{
			// find first node that depends on n
			uint16_t i = 0;
			while (i < nodes.size() && !nodes[i].depends[idx])
			{
				++i;
			}
			// remove if there is not dependencies
			if (i == nodes.size())
			{
				nodes.erase(nodes.begin() + idx);
				for (auto &n : nodes)
				{
					n.depends.erase(n.depends.begin() + idx);
				}
			}

		}
	}
	/*
	 * Make in_node depends on out_node
	 */
	bool link(T* in_node,T* out_node)
	{
		// get out node level must be
		uint16_t out_idx = 0, in_idx = 0;

		//  convert node to index
		for (uint16_t idx = 0; idx < nodes.size(); ++idx)
		{
			if (nodes[idx].n == out_node)
				out_idx = idx;
			else if (nodes[idx].n == in_node)
				in_idx = idx;
		}

		// if out node has high level and depends on i node the operation is invalid
		if ((nodes[out_idx].level > nodes[in_idx].level) && isDepend(out_idx, in_idx))
		{
			return false;
		}

		// move input node one level up over out node
		if (nodes[out_idx].level >= nodes[in_idx].level)
			ShiftUp(in_idx, nodes[out_idx].level + 1 - nodes[in_idx].level);

		// mark output node as dependency for input
		nodes[in_idx].depends[out_idx] = true;
		return true;
	}
	/*
	 * Remove nodes link or dependency
	 */
	bool unlink(T* in_node,T* out_node)
	{
		// get out node level must be
		uint16_t out_idx = 0, in_idx = 0;

		//  convert node to index
		for (uint16_t idx = 0; idx < nodes.size(); ++idx)
		{
			if (nodes[idx].n == out_node)
				out_idx = idx;
			else if (nodes[idx].n == in_node)
				in_idx = idx;
		}
		nodes[in_idx].depends[out_idx] = false;
		ShiftDown(in_idx);
		return false;
	}
	/*
	 * Shift down the specific node if it is possible
	 */
	void ShiftDown(uint16_t node_idx)
	{
		// find the high level dependency
		uint16_t lvl = 0;
		for (uint16_t idx = 0; idx < nodes.size(); ++idx)
		{
			if (nodes[node_idx].depends[idx] && (nodes[idx].level >= lvl))
				lvl = nodes[idx].level + 1;
		}
		// get new level and propagate
		if (lvl != nodes[node_idx].level)
		{
			nodes[node_idx].level = lvl;
			for (uint16_t idx = 0; idx < nodes.size(); ++idx)
			{
				if (nodes[idx].depends[node_idx])
				{
					ShiftDown(idx);
				}
			}
		}
	}
	/*
	 * For the specific node idx shift up all dependencies
	 */
	void ShiftUp(uint16_t node_idx, uint16_t count)
	{
		nodes[node_idx].level += count;
		for (uint16_t idx = 0; idx < nodes.size(); ++idx)
		{
			if (nodes[idx].depends[node_idx])
			{
				nodes[idx].level += count;
				ShiftUp(idx, count);
			}
		}
	}
	/*
	 * check dependencies between two nodes
	 * return true if out node depends on in node
	 */
	bool isDepend(uint16_t out_idx, uint16_t in_idx)
	{
		// check direct dependency
		if (nodes[out_idx].depends[in_idx])
			return true;
		// check second level of dependencies
		for (uint16_t i = 0; i < nodes[out_idx].depends.size(); ++i)
		{
			if (nodes[out_idx].depends[i] && isDepend(i, in_idx))
				return true;
		}
		return false;
	}
	/*
	 * output processing base in levels
	 * when a level without nodes is found it is the last one.
	 */
	void output()
	{
		bool b = true;
		for (uint16_t idx = 0; idx < nodes.size() && b; ++idx)
		{
			b = false;	// no nodes for this level
			for (auto &it : nodes)
			{
				if ((it).level == idx)
				{
					b = true;
					std::cout << *(it.n) << " ";
				}
			}
			std::cout << std::endl;
		}

	}
}
;


#endif /* DEPENDENCIES_H_ */
