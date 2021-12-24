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
#include "transport.hpp"
#include "hex.hpp"


class Layer
{
    private:
        bool networkValid;
        bool transportValid;

        std::unique_ptr<Network> network;
        std::unique_ptr<Transport> transport;

        std::unique_ptr<Network> findNetworkProto(hex &hex);
        std::unique_ptr<Transport> findTransportProto(hex &pktHex, int networkLength, int proto);
    
    public:
        Layer() = default;
        Layer(hex &pktHex);

        Network &getNetwork();
        Transport &getTransport();

        bool networkIsValid();
        bool transportIsValid();
};


#endif