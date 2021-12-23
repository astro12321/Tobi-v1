#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "network.hpp"
#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;

#include <memory>///////////////

Layer::Layer(hex &pktHex)
{
    //Giving each layers their bytes of the packet

    //Network layer
    this->network = findNetworkProt(pktHex);


    /*//Transport layer
    std::string transportProt = network.transportProt;
    std::string transportPacket = packetHex.substr(networkHex.length(), packetHex.length());
    std::string transportHex = findTransportHex(transportPacket, transportProt);
    this->transport = Transport(transportHex, transportProt);*/
}


//Gotta use pointers because polymorphism requires it (smart pointers)
std::shared_ptr<Network> Layer::findNetworkProt(hex &pktHex)
{
    int ipVersion = pktHex[0].first().to_dec();
    
    if (ipVersion == 4)
    {
        hex hex = pktHex.substr(0, 20);
        return std::shared_ptr<Ipv4>(new Ipv4(hex));
    }
    
    throw std::invalid_argument("Not an ipv4 packet"); //This has to change
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