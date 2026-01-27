#ifndef __BIPIO_H__
#define __BIPIO_H__
#include "../Base/base.hpp"
#include <fstream>
using CppOutStream = std::ofstream;
using CppInStream = std::ifstream;

inline std::ostream& operator << ( std::ostream& os, const CppOutStream& rhs ) {
    os << (rhs.is_open() ? "an instanciated file stream" : "no_file file_stream");
    return os;
}

void print(intarray & arr);

void emptyFile(std::string filename);
CppOutStream openOutStream(std::string filename);
void printInStream(CppOutStream& outputstream, std::string txt);
void printInStream(CppOutStream& outputstream, int n);
void printInStream(CppOutStream& outputstream, double x);
void closeStream(CppOutStream& outputstream);


inline std::ostream& operator << ( std::ostream& os, const CppInStream& rhs ) {
    os << (rhs.is_open() ? "an instanciated file stream" : "no_file file_stream");
    return os;
}

CppInStream openInStream(std::string filename);
void jump_n_lines(CppInStream& inputstream, int& n);
void readInStream(CppInStream& inputstream, std::string& txt);
void readInStream(CppInStream& inputstream, int& n);
void readInStream(CppInStream& inputstream, double& x);
void closeStream(CppInStream& inputstream);

#endif // __BIPIO_H__
