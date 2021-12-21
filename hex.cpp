//Custom data type
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "hex.hpp"

//using namespace std;


hex::hex(const char *hex) 
{ 
    this->h = std::string(hex); 
}

hex::hex(std::string hex) 
{
    this->h = hex; 
}

hex::hex(char hex) 
{ 
    this->h = std::string(1, hex); 
}

hex::hex(unsigned char *bytes, int len)
{
    this->b = bytes;
    this->len = len;

    std::stringstream ss;
    ss << std::hex;

    for (int i = 0; i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)bytes[i];

    this->h = ss.str();
}

int hex::length() { return len; } //Number of bytes read

int hex::numberOfBytes() { return h.length() / 2; }

int hex::to_dec() { return std::stoul(h, nullptr, 16); }

std::string hex::to_string() { return h; }

unsigned char *hex::bytes() { return b; }

//return the first/last part of the byte (so the first/last 4 bits)
//! Doesn't check for hex total length (would be more logic to only apply it on bytes) !
hex hex::first() { return hex(h[0]); }
hex hex::last() { return hex(h[1]); }

hex hex::substr(int start, int len) { return hex(h.substr(start * 2, len * 2)); }


hex &hex::operator=(char *hex) { return *this; }

std::ostream &operator<<(std::ostream& os, const hex& hex) { return os << hex.h; }

//return hex values by bytes (so by pairs)
hex hex::operator[](int ind)
{
    if (ind + 1 > h.length()) throw std::out_of_range("hex array index out of range");
    if (ind % 2 != 0) ind++; 

    return hex(std::string() + h[ind] + h[ind + 1]);
}