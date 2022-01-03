//Custom data types
#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>

#include <byte.hpp>


class hex
{
    private:
        std::string h;
        std::vector<unsigned char> b;

        std::vector<unsigned char> stringToHex(std::string str) const;
        std::string hexToString(std::vector<unsigned char> vecHex) const;
    
    public:
        hex();
        hex(std::string hex);
        hex(unsigned char *bytes, int len);

        int numberOfBytes() const;
        int to_dec() const;
        std::string to_string() const;
        std::string to_fstring() const;
        std::string convert_to_string(int delimiter = 31, std::string replacement = ".") const;

        const std::vector<unsigned char> &getBytes() const;

        hex substr (int start, int len) const;

        const byte operator [] (size_t ind) const;
};


#endif