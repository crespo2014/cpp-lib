/*
 * ostreamstring.h
 *
 *  Created on: 7 Mar 2015
 *      Author: lester
 */

#ifndef OSTREAMSTRING_H_
#define OSTREAMSTRING_H_

#include <sstream>

class SS
{
    std::ostringstream stream;
public:
    template<class T>
    SS& operator <<(const T& t)
    {
        stream << t;
        return *this;
    }
    operator const std::string() const
    {
        return stream.str();
    }
};


#endif /* OSTREAMSTRING_H_ */
