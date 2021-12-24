#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <memory>

#include "layer.hpp"
#include "network.hpp"
//#include "transport.hpp"
#include "ipv4.hpp"
#include "hex.hpp"
#include "icmp.hpp"


Layer::Layer(hex &pktHex)
{
    this->network = findNetworkProto(pktHex);

    if (this->network != nullptr)
    {
        this->networkValid = true;

        this->transport = findTransportProto(pktHex, getNetwork().getHex().numberOfBytes(), getNetwork().getTransportProto());

        if (this->transport != nullptr)
        {
            this->transportValid = true;
        }
        else { this->transportValid = false; }
    }
    else { this->networkValid = false; } //If the packet is invalid (a protocol that we don't parse)
}


//Pretty evil because it's returning an object on the heap (which should be manually deleted), but acceptable here as this object is a smart pointer which will delete itself
Network &Layer::getNetwork() { return *(this->network); }
Transport &Layer::getTransport() { return *(this->transport); }

bool Layer::networkIsValid() { return this->networkValid; }
bool Layer::transportIsValid() { return this->transportValid; }

//int Layer::getStatus() { return this->status; }


//Gotta use pointers because polymorphism requires it (smart pointers)
std::unique_ptr<Network> Layer::findNetworkProto(hex &pktHex)
{
    int ipVersion = pktHex[0].first().to_dec();
    
    if (ipVersion == 4)
    {
        hex hex = pktHex.substr(0, 20);
        return std::make_unique<Ipv4>(hex); //make_unique avoid using "new"
    }
    
    return std::unique_ptr<Network>(nullptr);
}


std::unique_ptr<Transport> Layer::findTransportProto(hex &pktHex, int networkLength, int proto)
{
    switch (proto)
    {
        case 1: //ICMP
        {
            hex transportHex = pktHex.substr(networkLength, pktHex.numberOfBytes() - networkLength);

            return std::make_unique<ICMP>(transportHex);
        }

        /*case 6: //TCP
            int tcpHeaderLen = pktHex[12].first().to_dec();
            pktHex.substr(0, tcpHeaderLen * 4);

            return "TCP";

        case 17: //UDP
            pktHex.substr(0, 8);

            return "UDP";*/

        default:
            return std::unique_ptr<Transport>(nullptr);
    }



    /*
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
    }*/
}