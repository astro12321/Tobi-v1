#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"

//using namespace std;


class Layer 
{       
    public:
        Network network;

        Layer() = default;
        Layer(std::string packetHex);

    private:
        std::string findNetworkHex(std::string packetHex);
};


#endif