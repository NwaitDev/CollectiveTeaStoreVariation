#ifndef __BASE_H__
#define __BASE_H__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

using intarray = std::vector<int>;

enum collective_optional{
    REGULAR,
    STOP
};

using c_int = std::pair<int, collective_optional>;
using c_float = std::pair<double, collective_optional>;
using c_bool = std::pair<bool, collective_optional>;
using c_intarray = std::pair<intarray, collective_optional>;


intarray zeros(const int dim1);
intarray range(const int upto);


inline std::ostream& operator << ( std::ostream& os, const intarray& rhs ) {
    os << "[int_array("<<rhs.size()<<") :";
    for( size_t i = 0; i<rhs.size(); ++i){
        os << rhs.at(i) <<" ";
    }
    os <<"]";
    return os;
}

double randomdouble();

inline int asint(float f){return (int)f;}
inline double asfloat(int i){return (double)i;}


#endif // __BASE_H__
