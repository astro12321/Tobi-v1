//Custom data types
#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>


class Address
{
    private:
        hex h;
        std::string addr;
    
    public:
        Address() = default;
        Address(std::string addr);
        Address(const hex &aHex, int type = 0);

        std::string to_string() const;
        const hex &to_hex() const;
        void convertToIPv6();
};


#endif