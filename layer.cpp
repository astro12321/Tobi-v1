#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "network.hpp"
#include "hex.hpp"

//using namespace std;


Layer::Layer(hex h)
{
    //Giving each layers their bytes of the packet

    //Network layer
    hex networkHex = findNetworkHex(h);
    this->network = Network(networkHex.to_string());

    /*//Transport layer
    std::string transportProt = network.transportProt;
    std::string transportPacket = packetHex.substr(networkHex.length(), packetHex.length());
    std::string transportHex = findTransportHex(transportPacket, transportProt);
    this->transport = Transport(transportHex, transportProt);*/
}


hex Layer::findNetworkHex(hex hex)
{
    int ipVersion = hex[0].first().to_dec();
    
    if (ipVersion == 4) return hex.substr(0, 20);

    throw std::invalid_argument("Not an ipv4 packet");
}


hex Layer::findTransportHex(hex hex, std::string protocol)
{
    if (protocol == "TCP")
    {
        int tcpHeaderLen = hex[12].first().to_dec();

        return hex.substr(0, tcpHeaderLen * 4);
    }

    else if (protocol == "UDP")
    {
        return hex.substr(0, 8);
    }

    else if (protocol == "ICMP")
    {
        return hex.substr(0, hex.numberOfBytes());
    }

    throw std::invalid_argument("What protocol is this ?");
}