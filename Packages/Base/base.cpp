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

c_intarray cpy(c_intarray& toBeAssigned){
    c_intarray ret;
    std::get<1>(ret) = std::get<1>(toBeAssigned);
    std::get<0>(toBeAssigned) = std::vector<int>(std::get<0>(toBeAssigned));
    return ret;
}

intarray zeros(const int dim1){
    intarray out = std::vector<int>(dim1);
    for(size_t i = 0; i<(size_t)dim1; ++i){
        out[i] = 0;
    }
    return out;
}

intarray range(const int upto){
    intarray out = std::vector<int>(upto);
    for(size_t i = 0; i<(size_t)upto; ++i){
        out[i] = i;
    }
    return out;
}

bool are_copies(intarray& a, intarray& b){
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



double randomdouble(){
	return (double)rand() / RAND_MAX;
}