#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "network.hpp"
#include "operations.hpp"
#include "hex.hpp"

//using namespace std;


Layer::Layer(hex hex)
{
    //Giving each layers their bytes of the packet

    //Network layer
    std::string networkHex = findNetworkHex(hex.to_string());
    this->network = Network(networkHex);

    //Transport layer
    /*std::string transportProt = network.transportProt;
    std::string transportPacket = packetHex.substr(networkHex.length(), packetHex.length());
    std::string transportHex = findTransportHex(transportPacket, transportProt);
    this->transport = Transport(transportHex, transportProt);*/
}


std::string Layer::findNetworkHex(hex hex)
{
    //int ipVersion = operations::hexToDec(packetHex[0]);
    int ipVersion = hex[0].first().to_dec();

    if (ipVersion == 4) {
        return hex.substr(0, 20).to_string();
    }

    return "Not an ipv4 packet...";
}


std::string Layer::findTransportHex(hex hex, std::string protocol)
{
    if (protocol == "TCP")
    {
        int tcpHeaderLen = hex.substr(12, 1).first().to_dec();

        return hex.substr(0, tcpHeaderLen * 4).to_string();
    }

    else if (protocol == "UDP")
    {
        return hex.substr(0, 8).to_string();
    }

    else if (protocol == "ICMP")
    {
        return hex.substr(0, hex.numberOfBytes()).to_string();
    }

    return "wtf";

}