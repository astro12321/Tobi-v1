#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "transport.hpp"
#include "hex.hpp"

//using namespace std;


class Layer 
{       
    public:
        Network network;
        Transport transport;

        Layer() = default;
        Layer(hex &pktHex);

    private:
        hex findNetworkHex(hex &hex);
        hex findTransportHex(hex &hex, std::string protocol);
};


#endif