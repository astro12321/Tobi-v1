//Custom data types
#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

//using namespace std;


class byte
{
    private:
        std::string b;

    public:
        byte();
        byte(std::string byte);
        int to_dec();
        std::string to_string();
        byte first();
        byte last();
};


class hex 
{
    private:
        std::string h;

        //evitate to recalculate each time a packet comes in
        unsigned char *b;
        int len;

    public:
        hex();
        hex(const char *hex);
        hex(std::string hex);
        hex(unsigned char *bytes, int len);

        int length();
        int numberOfBytes();
        int to_dec();
        std::string to_string();
        unsigned char *bytes();
        hex substr(int start, int len);

        friend std::ostream &operator<<(std::ostream& os, const hex& hex);
        hex &operator=(char *hex);
        byte operator[](int index);
};


#endif