#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "transport.hpp"

//using namespace std;


class Layer 
{       
    public:
        std::string packetHex;
        Transport transport;

        Layer() = default;
        Layer(std::string packetHex);
};


#endif