//Custom data types
#ifndef IP_HPP
#define IP_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>


class IP
{
    private:
        hex h;
        std::string ip;
    
    public:
        IP() = default;
        IP(std::string ip);
        IP(const hex &hex);

        std::string to_string() const;
        const hex &to_hex() const;
};


#endif