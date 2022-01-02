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

        std::unique_ptr<Network> findNetworkProto(hex &hex) const;
        std::unique_ptr<Transport> findTransportProto(hex &pktHex, int networkLength, int proto) const;
        std::unique_ptr<Application> findApplicationProto(hex &pktHex, int headersLen) const;

        bool isDNS() const;
    
    public:
        Layer() = default;
        Layer(hex &pktHex);

        const Network &getNetwork() const;
        const Transport &getTransport() const;
        const Application &getApplication() const;

        bool networkIsValid() const;
        bool transportIsValid() const;
        bool applicationIsValid() const;
};


#endif