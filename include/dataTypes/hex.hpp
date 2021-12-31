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
        int to_dec();
        std::string to_string();
        std::string to_fstring();
        byte first();
        byte last();
};


class hex
{
    private:
        std::string h;
        unsigned char *b;
        int len;
    
    public:
        hex();
        hex(const hex &hex);
        //hex(const char *hex);
        hex(std::string hex);
        hex(unsigned char *bytes, int len);

        int length();
        int numberOfBytes();
        int to_dec();
        std::string to_string();
        std::string to_fstring();
        unsigned char &getBytes();
        hex substr(int start, int len);

        friend std::ostream &operator<<(std::ostream& os, const hex& hex);
        hex &operator=(char *hex);
        byte operator[](size_t ind);
};


#endif