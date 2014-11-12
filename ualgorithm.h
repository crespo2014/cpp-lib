/*
 * ualgorithm.h
 *
 *  Created on: 25 Jun 2014
 *      Author: lester.crespo
 */

#ifndef UALGORITHM_H_
#define UALGORITHM_H_

//user algorithm

// find e value in  ordered list with using middle list compare, jump to middle of the list
// return last element when failed to found

template<typename C, typename D>
C find(C start, C end, D d)
{
	C lower = start;
	C higher = end;
	unsigned step = end - start;
	while (step > 0)
	{
		step /= 2;
		if (lower[step] < d)
			lower += step;
		else if (lower[step] > d)
			higher -= step;
		else
			break;
	}
	if (!(*lower == d))
		return end;
	return lower;
}

#endif /* UALGORITHM_H_ */
