#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;


class Network 
{       
    public:
        hex h;
        Ipv4 ipv4;
        std::string transportProt;

        Network() = default;
        Network(hex h);
};


#endif