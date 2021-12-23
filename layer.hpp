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
        int status;

        std::unique_ptr<Network> network;

        std::unique_ptr<Network> findNetworkProt(hex &hex);
        hex findTransportHex(hex &hex, std::string protocol);
        int setStatus();
    
    public:
        Layer() = default;
        Layer(hex &pktHex);

        int getStatus();
        Network &getNetwork();
};


#endif