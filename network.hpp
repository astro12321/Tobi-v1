#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"

//using namespace std;


class Network 
{       
    public:
        std::string hex;
        Ipv4 ipv4;
        std::string transportProt;

        Network() = default;
        Network(std::string hex);
};


#endif