#include "bipio.hpp"
#include <string>

void printIntArray(IntArray& arr){
    std::cout<<"[";
    for (int i : arr) {
        std::cout<<i<<" ";
    }
    std::cout<<"]"<<std::endl;
}

void emptyFile(std::string filename){
    std::ofstream myfile;
    myfile.open (filename);
    myfile.close();
}

CppOutStream openOutStream(std::string filename){
    std::ofstream myfile;
    myfile.open (filename,std::ios_base::app);
    return myfile;
}

void printInStream(CppOutStream& outputstream, std::string txt){
    outputstream << txt;
}

void printInStream(CppOutStream& outputstream, int n){
    outputstream <<" "<< n;
}
void printInStream(CppOutStream& outputstream, double x){
    outputstream <<" "<< x;
}

void closeStream(CppOutStream& outputstream){
    outputstream.close();
}



CppInStream openInStream(std::string filename){
    std::ifstream myfile;
    myfile.open (filename,std::ios_base::app);
    return myfile;
}

void jump_n_lines(CppInStream& inputstream, int& n){
    std::string line;
    for (int i = 0; i<n; ++i) {
        std::getline(inputstream,line);
    }
}

void readInStream(CppInStream& inputstream, std::string& txt){
    inputstream >> txt;
}
void readInStream(CppInStream& inputstream, int& n){
    inputstream >> n;
}
void readInStream(CppInStream& inputstream, double& x){
    inputstream >> x;
}
void closeStream(CppInStream& inputstream){
    inputstream.close();
}