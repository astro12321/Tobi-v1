#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <memory>

#include "layer.hpp"
#include "network.hpp"
#include "ipv4.hpp"
#include "hex.hpp"


Layer::Layer(hex &pktHex)
{
    this->network = findNetworkProt(pktHex);

    if (this->network != nullptr)
    {
        this->valid = true;

        /*//Transport layer
        std::string transportProt = network.transportProt;
        std::string transportPacket = packetHex.substr(networkHex.length(), packetHex.length());
        std::string transportHex = findTransportHex(transportPacket, transportProt);
        this->transport = Transport(transportHex, transportProt);*/
    }
    else { this->valid = false; } //If the packet is invalid (a protocol that we don't parse)
}


//Pretty evil because it's returning an object on the heap (which should be manually deleted), but acceptable here as this object is a smart pointer which will delete itself
Network &Layer::getNetwork() { return *(this->network); }

bool Layer::isValid() { return this->valid; }

//int Layer::getStatus() { return this->status; }


//Gotta use pointers because polymorphism requires it (smart pointers)
std::unique_ptr<Network> Layer::findNetworkProt(hex &pktHex)
{
    int ipVersion = pktHex[0].first().to_dec();
    
    if (ipVersion == 4)
    {
        hex hex = pktHex.substr(0, 20);
        return std::make_unique<Ipv4>(hex); //make_unique avoid using "new"
    }
    
    return std::unique_ptr<Network>(nullptr);
}


hex Layer::findTransportHex(hex &pktHex, std::string protocol)
{
    if (protocol == "TCP")
    {
        int tcpHeaderLen = pktHex[12].first().to_dec();

        return pktHex.substr(0, tcpHeaderLen * 4);
    }

    else if (protocol == "UDP")
    {
        return pktHex.substr(0, 8);
    }

    else if (protocol == "ICMP")
    {
        return pktHex.substr(0, pktHex.numberOfBytes());
    }

    throw std::invalid_argument("What protocol is this ?");
}