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



IntArray zeros(const int& dim1);
IntArray range(const int& upto);
bool are_copies(const IntArray&, const IntArray&);
bool are_copies(const c_IntArray&, const c_IntArray&);
bool are_copies(const IntArray&, const c_IntArray&);
bool are_copies(const c_IntArray&, const IntArray&);


c_int cpy(const c_int&);
c_bool cpy(const c_bool&);
c_float cpy(const c_float&);
c_IntArray cpy(const c_IntArray&);

c_int make(const int&);
c_float make(const double&);
c_bool make(const bool&);
c_IntArray make(const IntArray&);
bool are_copies(const c_int&, const c_int&);
bool are_copies(const c_int&, const int&);
bool are_copies(const int&, const c_int&);
bool are_copies(const c_float&, const c_float&);
bool are_copies(const c_bool&, const c_bool&);

inline std::ostream& operator << ( std::ostream& os, const IntArray& rhs ) {
    os << "[int_array("<<rhs.size()<<") :";
    for( size_t i = 0; i<rhs.size(); ++i){
        os << rhs.at(i) <<" ";
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const c_int& rhs ) {
    os << "[collective int: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const c_bool& rhs ) {
    os << "[collective bool: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const c_float& rhs ) {
    os << "[collective float: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        os<<std::get<0>(rhs);
    }
    os <<"]";
    return os;
}

inline std::ostream& operator << ( std::ostream& os, const c_IntArray& rhs ) {
    os << "[collective int_array: ";
    if(std::get<1>(rhs) == STOP){
        os << "STOP ";
    }else{
        for( size_t i = 0; i<std::get<0>(rhs).size(); ++i){
            os << std::get<0>(rhs).at(i) <<" ";
        }
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
