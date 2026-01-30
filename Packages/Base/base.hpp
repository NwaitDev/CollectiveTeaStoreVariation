#ifndef __BASE_H__
#define __BASE_H__

#include <cstddef>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>
#include <cstdlib>
#include <ctime>



using IntArray = std::vector<int>;

enum collective_optional{
    REGULAR,
    STOP
};


using c_int = std::tuple<int, collective_optional>;
using c_float = std::tuple<double, collective_optional>;
using c_bool = std::tuple<bool, collective_optional>;
using c_IntArray = std::tuple<IntArray, collective_optional>;



IntArray zeros(const int dim1);
IntArray range(const int upto);
bool are_copies(IntArray&, IntArray&);


c_int cpy(c_int&);
c_bool cpy(c_bool&);
c_float cpy(c_float&);
c_IntArray cpy(c_IntArray&);

inline std::ostream& operator << ( std::ostream& os, const IntArray& rhs ) {
    os << "[int_array("<<rhs.size()<<") :";
    for( size_t i = 0; i<rhs.size(); ++i){
        os << rhs.at(i) <<" ";
    }
    os <<"]";
    return os;
}

double randomdouble();

inline int asint(double f){return (int)f;}
inline double asfloat(int i){return (double)i;}
inline double floatIdentity(double f){return f;}
inline double intIdentity(int i){return i;}

#endif // __BASE_H__
