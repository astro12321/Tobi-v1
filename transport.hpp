#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"

//using namespace std;


class Transport 
{       
    public:
        std::string hex;
        Ipv4 ipv4;

        Transport() = default;
        Transport(std::string hex);
};


#endif