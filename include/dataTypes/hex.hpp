//Custom data types
#ifndef HEX_HPP
#define HEX_HPP

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
        byte(std::string byte);
        int to_dec() const;
        std::string to_string() const;
        std::string to_fstring() const;
        byte first() const;
        byte last() const;
};


class hex
{
    private:
        std::string h;
        unsigned char *b;
        int len;
    
    public:
        hex();
        hex(std::string hex);
        hex(unsigned char *bytes, int len);

        int length() const;
        int numberOfBytes() const;
        int to_dec() const;
        std::string to_string() const;
        std::string to_fstring() const;
        const unsigned char &getBytes() const;

        hex substr (int start, int len) const;

        byte operator [] (size_t ind) const;
};


#endif