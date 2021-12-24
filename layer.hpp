#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <memory>

#include "network.hpp"
#include "ipv4.hpp"
//#include "transport.hpp"//////////////////////////
#include "hex.hpp"


class Layer
{
    private:
        bool valid;

        std::unique_ptr<Network> network;

        std::unique_ptr<Network> findNetworkProt(hex &hex);
        hex findTransportHex(hex &hex, std::string protocol);
    
    public:
        Layer() = default;
        Layer(hex &pktHex);

        Network &getNetwork();
        bool isValid();
};


#endif