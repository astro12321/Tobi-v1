#ifndef BYTE_HPP
#define BYTE_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>


class byte
{
    private:
        std::string b;

    public:
        byte();
        byte(std::string b);

        int to_dec() const;
        std::string to_string() const;
        std::string to_fstring() const;
        std::string to_bits() const;
        byte first() const;
        byte last() const;
};


#endif