#include "base.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>



c_int cpy(c_int& toBeAssigned){
    return c_int{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

c_bool cpy(c_bool& toBeAssigned){
    return c_bool{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}
c_float cpy(c_float& toBeAssigned){
    return c_float{std::get<0>(toBeAssigned),std::get<1>(toBeAssigned)};
}

c_IntArray cpy(c_IntArray& toBeAssigned){
    c_IntArray ret;
    std::get<1>(ret) = std::get<1>(toBeAssigned);
    std::get<0>(toBeAssigned) = std::vector<int>(std::get<0>(toBeAssigned));
    return ret;
}

IntArray zeros(const int dim1){
    IntArray out = std::vector<int>(dim1);
    for(size_t i = 0; i<(size_t)dim1; ++i){
        out[i] = 0;
    }
    return out;
}

IntArray range(const int upto){
    IntArray out = std::vector<int>(upto);
    for(size_t i = 0; i<(size_t)upto; ++i){
        out[i] = i;
    }
    return out;
}

bool are_copies(IntArray& a, IntArray& b){
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


bool are_copies(c_IntArray& a, c_IntArray& b){
    if(std::get<1>(a)!=std::get<1>(b)){
        return false;
    }
    return are_copies(std::get<0>(a),std::get<0>(b));
}
bool are_copies(IntArray& a, c_IntArray& b){
    if(STOP == std::get<1>(b)){
        return false;
    }
    return are_copies(a,std::get<0>(b));
}

bool are_copies(c_IntArray& a, IntArray& b){
    if(STOP == std::get<1>(a)){
        return false;
    }
    return are_copies(b,std::get<0>(a));
}


double randomdouble(){
	return (double)rand() / RAND_MAX;
}