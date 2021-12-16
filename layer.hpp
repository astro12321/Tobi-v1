#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "network.hpp"

//using namespace std;


class Layer 
{       
    public:
        std::string packetHex;
        Network network;

        Layer() = default;
        Layer(std::string packetHex);
};


#endif