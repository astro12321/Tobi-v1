//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <ip.hpp>
#include <hex.hpp>


IP::IP(const hex &hex)
{
    this->h = hex;

    std::string b1 = std::to_string(hex[0].to_dec());
    std::string b2 = std::to_string(hex[1].to_dec());
    std::string b3 = std::to_string(hex[2].to_dec());
    std::string b4 = std::to_string(hex[3].to_dec());

    this->ip = b1 + "." + b2 + "." + b3 + "." + b4;
}

IP::IP(std::string ip) { this->ip = ip; }

std::string IP::to_string() const { return this->ip; }
const hex &IP::to_hex() const { return this->h; }