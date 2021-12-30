//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "hex.hpp"


//Constructors
hex::hex() { this->h = ""; }


hex::hex(const hex &hex)
{
    this->h = hex.h;
    this->b = hex.b;
    this->len = hex.len;
}


hex::hex(std::string hex)
{
    if (hex.length() % 2 != 0)
        throw std::invalid_argument("the hex string must have an even number length");
    
    this->h = hex;
}


hex::hex(unsigned char *bytes, int len)
{
    this->len = len;
    memcpy(&b, &bytes, sizeof(bytes));

    std::stringstream ss;
    ss << std::hex;

    for (int i = 0; i < len; ++i)
        ss << std::setw(2) << std::setfill('0') << (int)bytes[i];

    this->h = ss.str();
}


//Functions
int hex::length() { return this->len; } //Number of bytes read (aka bytesRead)

int hex::numberOfBytes() { return this->h.length() / 2; }

int hex::to_dec() { return std::stoul(this->h, nullptr, 16); }

std::string hex::to_string() { return this->h; }
std::string hex::to_fstring() { return "0x" + this->h; }

unsigned char &hex::getBytes() { return *this->b; }

hex hex::substr(int start, int len) { return hex(this->h.substr(start * 2, len * 2)); }


//Operator overload
hex &hex::operator=(char *hex) { return *this; }

std::ostream &operator<<(std::ostream& os, const hex& hex) { return os << hex.h; }

//return hex values by bytes (so by pairs)
byte hex::operator[](int ind) 
{
    if (ind * 2 + 1 > h.length()) throw std::out_of_range("hex array index out of range");
    return byte(std::string() + h[ind * 2] + h[ind * 2 + 1]);
}


////////////////////////////////////////////////////////////////////////


byte::byte() { this->b = "00"; }

byte::byte(std::string byte)
{
    if (byte.length() != 2)
        throw std::invalid_argument("a byte must be composed of 2 hex character");

    this->b = byte;
}

int byte::to_dec() { return std::stoul(b, nullptr, 16); }

std::string byte::to_string() { return b; }
std::string byte::to_fstring() { return "0x" + this->b; }

byte byte::first() { return byte(std::string("0") + b[0]); }
byte byte::last() { return byte(std::string("0") + b[1]); }