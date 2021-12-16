#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"

//using namespace std;


Ipv4::Ipv4(std::string hex)
{
    this->hex = ipv4::Hex(hex);
}

namespace ipv4
{
    Hex::Hex(std::string hex)
    {
        this->hex = hex;
    }   

}