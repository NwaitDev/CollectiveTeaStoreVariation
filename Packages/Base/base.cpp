#include "base.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>



intarray zeros(const int dim1){
    intarray out = std::vector<int>(dim1);
    for(size_t i = 0; i<dim1; ++i){
        out[i] = 0;
    }
    return out;
}

intarray range(const int upto){
    intarray out = std::vector<int>(upto);
    for(size_t i = 0; i<upto; ++i){
        out[i] = i;
    }
    return out;
}


double randomdouble(){
	return (double)rand() / RAND_MAX;
}