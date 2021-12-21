//Custom data type
#ifndef HEX_HPP
#define HEX_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

//using namespace std;


class hex 
{
    public:
        hex() = default;
        hex(const char *hex);
        hex(std::string hex);
        hex(char hex);
        hex(unsigned char *bytes, int len);

        int length();
        int numberOfBytes();
        int to_dec();
        std::string to_string();
        hex first();
        hex last();
        unsigned char *bytes();
        hex substr(int start, int len);

        friend std::ostream &operator<<(std::ostream& os, const hex& hex);
        hex &operator=(char *hex);
        hex operator[](int index);
        
    private:
        std::string h;

        //evitate to recalculate each time a packet comes in
        unsigned char *b;
        int len;

};


#endif