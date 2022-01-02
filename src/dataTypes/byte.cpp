//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <byte.hpp>


byte::byte() { this->b = "00"; }

byte::byte(std::string b)
{
    if (b.length() != 2)
        throw std::invalid_argument("a byte must be composed of 2 hex character");

    this->b = b;
}

int byte::to_dec() const { return std::stoul(b, nullptr, 16); }

std::string byte::to_string() const { return b; }
std::string byte::to_fstring() const { return "0x" + this->b; }

byte byte::first() const { return byte(std::string("0") + b[0]); }
byte byte::last() const { return byte(std::string("0") + b[1]); }