#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "operations.hpp"

//using namespace std;


namespace operations
{
    std::string bytesToHex(unsigned char *bytes, int len)
    {
        std::stringstream ss;
        ss << std::hex;

        for (int i = 0; i < len; ++i)
            ss << std::setw(2) << std::setfill('0') << (int)bytes[i];

        return ss.str();
    }


    int hexToDec(std::string hex)
    {
        return std::stoul(hex, nullptr, 16);
    }


    int hexToDec(char hex)
    {
        return std::stoul(std::string(1, hex), nullptr, 16);
    }

}