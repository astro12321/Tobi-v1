#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

//using namespace std;


namespace operations
{
    std::string bytesToHex(unsigned char *bytes, int len);
    int hexToDec(std::string hex);
    int hexToDec(char hex);
}


#endif