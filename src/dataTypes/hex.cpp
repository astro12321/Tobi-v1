//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include <bitset>

#include <hex.hpp>
#include <byte.hpp>


hex::hex() 
{ 
    this->h = "00";
    //this->b = stringToHex(""); //Resource intensive
}


hex::hex(std::string hex)
{
    if (hex.length() % 2 != 0)
        throw std::invalid_argument("the hex string must have an even number length");
    
    this->h = hex;
    //this->b = stringToHex(hex); //Resource intensive
}


hex::hex(unsigned char *bytes, int len)
{
    this->b = std::vector<unsigned char>(bytes, bytes + len);
    this->h = hexToString(b);
}


//int hex::length() const { return this->len; } //Number of bytes read (aka bytesRead)
int hex::numberOfBytes() const { return this->h.length() / 2; }

int hex::to_dec() const { return std::stoul(this->h, nullptr, 16); }
std::string hex::to_string() const { return this->h; }
std::string hex::to_fstring() const { return "0x" + this->h; }

std::string hex::convert_to_string(int delimiter, std::string replacement) const
{
    std::string fin = "";
    size_t len = h.length() / 2;

    for (size_t i = 0; i < len; i++)
    {
        std::string tmp = std::string() + h[i * 2] + h[i * 2 + 1];
        int letterCode = std::stoul(tmp, nullptr, 16);

        if (letterCode > delimiter) fin += (char)letterCode; //If the letter is above the delimiter (refer to the ASCII table to understand the delimiter)
        else if (i != 0 && i != len - 1) fin += replacement; //If it's not, replace the letter by the replacement var (of course not the first or last letter)
    }

    return fin;
}

const std::vector<unsigned char> &hex::getBytes() const { return this->b; }

hex hex::substr(int start, int len) const { return hex(this->h.substr(start * 2, len * 2)); }

//return hex values by bytes (so by pairs)
const byte hex::operator [] (size_t ind) const {
    if (ind * 2 + 1 > h.length()) throw std::out_of_range("hex array index out of range");
    return byte(std::string() + h[ind * 2] + h[ind * 2 + 1]);
}

//Construct a char vector from a hex string
std::vector<unsigned char> hex::stringToHex(std::string str) const
{
    std::stringstream ss;
    std::vector<unsigned char> hexVec;
    int buffer;
    size_t offset = 0;

    while (offset < str.length()) 
    {
        ss.clear();
        ss << std::hex << str.substr(offset, 2);
        ss >> buffer;

        hexVec.push_back(static_cast<unsigned char>(buffer));

        offset += 2;
    }

    return hexVec;
}

std::string hex::hexToString(std::vector<unsigned char> vecHex) const
{
    std::stringstream ss;
    ss << std::hex;

    for (size_t i = 0; i < vecHex.size(); ++i)
        ss << std::setw(2) << std::setfill('0') << (int)vecHex[i];

    return ss.str();
}