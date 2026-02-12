#include "base.hpp"
#include <cassert>
#include <cstdlib>
#include <tuple>
#include <vector>



c_int cpy(const c_int& toBeAssigned){
    return c_int{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

c_bool cpy(const c_bool& toBeAssigned){
    return c_bool{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}
c_float cpy(const c_float& toBeAssigned){
    return c_float{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

c_IntArray cpy(const c_IntArray& toBeAssigned){
    c_IntArray ret;
    std::get<1>(ret) = std::get<1>(toBeAssigned);
    std::get<0>(ret) = std::vector<int>(std::get<0>(toBeAssigned));
    return ret;
}

IntArray zeros(const int& dim1){
    IntArray out = std::vector<int>(dim1);
    for(size_t i = 0; i<(size_t)dim1; ++i){
        out[i] = 0;
    }
    return out;
}

IntArray range(const int& upto){
    IntArray out = std::vector<int>(upto);
    for(size_t i = 0; i<(size_t)upto; ++i){
        out[i] = i;
    }
    return out;
}

bool are_copies(const IntArray& a, const IntArray& b){
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i=0; i<a.size(); ++i) {
        if(a[i]!=b[i]){
            return false;
        }
    }
    return true;
}


bool are_copies(const c_IntArray& a, const c_IntArray& b){
    if(std::get<1>(a)!=std::get<1>(b)){
        return false;
    }
    return are_copies(std::get<0>(a),std::get<0>(b));
}
bool are_copies(const IntArray& a, const c_IntArray& b){
    if(STOP == std::get<1>(b)){
        return false;
    }
    return are_copies(a,std::get<0>(b));
}

bool are_copies(const c_IntArray& a, const IntArray& b){
    if(STOP == std::get<1>(a)){
        return false;
    }
    return are_copies(b,std::get<0>(a));
}


c_int make(const int& value){
    return std::make_tuple(value, REGULAR);
}
c_float make(const double& value){
    return std::make_tuple(value, REGULAR);
}
c_bool make(const bool& value){
    return std::make_tuple(value, REGULAR);
}
c_IntArray make(const IntArray& value){
    return std::make_tuple(value, REGULAR);
}

bool are_copies(const c_int& a, const c_int& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}
bool are_copies(const c_int& a, const int& b){
    return ((std::get<1>(a) == REGULAR) && (std::get<0>(a) == b));
}
bool are_copies(const int& a, const c_int& b){
    return are_copies(b,a);
}

bool are_copies(const c_float& a, const c_float& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}
bool are_copies(const c_bool& a, const c_bool& b){
    return ((STOP == std::get<1>(b)) && (std::get<1>(a) == STOP)) 
            || ((std::get<1>(a) == REGULAR) && (std::get<1>(b) == REGULAR) && (std::get<0>(a) == std::get<1>(b)));
}


double randomdouble(){
	return (double)rand() / RAND_MAX;
}