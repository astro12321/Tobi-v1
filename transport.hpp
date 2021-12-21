#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

//using namespace std;


class Transport 
{       
    public:
        std::string protocol;
        std::string hex;

        Transport() = default;
        Transport(std::string hex, std::string protocol);
};


#endif