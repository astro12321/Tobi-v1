//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <byte.hpp>


hex::hex() { this->h = ""; }


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


int hex::length() const { return this->len; } //Number of bytes read (aka bytesRead)
int hex::numberOfBytes() const { return this->h.length() / 2; }

int hex::to_dec() const { return std::stoul(this->h, nullptr, 16); }
std::string hex::to_string() const { return this->h; }
std::string hex::to_fstring() const { return "0x" + this->h; }

const unsigned char &hex::getBytes() const { return *this->b; }

hex hex::substr(int start, int len) const { return hex(this->h.substr(start * 2, len * 2)); }

//return hex values by bytes (so by pairs)
byte hex::operator [] (size_t ind) const
{
    if (ind * 2 + 1 > h.length()) throw std::out_of_range("hex array index out of range");
    return byte(std::string() + h[ind * 2] + h[ind * 2 + 1]);
}