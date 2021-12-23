#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "network.hpp"
#include "hex.hpp"

//using namespace std;


Layer::Layer(hex &pktHex)
{
    //Giving each layers their bytes of the packet

    //Network layer
    hex networkHex = findNetworkHex(pktHex);
    this->network = Network(networkHex);

    /*//Transport layer
    std::string transportProt = network.transportProt;
    std::string transportPacket = packetHex.substr(networkHex.length(), packetHex.length());
    std::string transportHex = findTransportHex(transportPacket, transportProt);
    this->transport = Transport(transportHex, transportProt);*/
}


hex Layer::findNetworkHex(hex &pktHex)
{
    int ipVersion = pktHex[0].first().to_dec();
    
    if (ipVersion == 4) return pktHex.substr(0, 20);

    throw std::invalid_argument("Not an ipv4 packet");
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