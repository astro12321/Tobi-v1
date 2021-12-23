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

//using namespace std;


class Layer
{
    public:
        std::shared_ptr<Network> network;
        //Transport transport;

        Layer() = default;
        Layer(hex &pktHex);

    private:
        std::shared_ptr<Network> findNetworkProt(hex &hex);
        Network findNetworkProtWORKING(hex &hex);
        hex findTransportHex(hex &hex, std::string protocol);
};


#endif