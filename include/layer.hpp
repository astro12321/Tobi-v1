#ifndef LAYER_HPP
#define LAYER_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <memory>

#include <transport.hpp>

class Network;
class Transport;
class Application;


class Layer
{
    private:
        bool networkValid;
        bool transportValid;
        bool applicationValid;

        std::unique_ptr<Network> network;
        std::unique_ptr<Transport> transport;
        std::unique_ptr<Application> application;

        std::unique_ptr<Network> findNetworkProto(hex &hex);
        std::unique_ptr<Transport> findTransportProto(hex &pktHex, int networkLength, int proto);
        std::unique_ptr<Application> findApplicationProto(hex &pktHex, int headersLen);

        bool isDNS();
    
    public:
        Layer() = default;
        Layer(hex &pktHex);

        Network &getNetwork();
        Transport &getTransport();
        Application &getApplication();

        bool networkIsValid();
        bool transportIsValid();
        bool applicationIsValid();
};


#endif