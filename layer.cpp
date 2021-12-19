#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "network.hpp"
#include "operations.hpp"

//using namespace std;


Layer::Layer(std::string packetHex)
{
    //Giving each layers their bytes of the packet

    //Network layer
    this->network = Network(findNetworkHex(packetHex));

    //Transport layer
}


std::string Layer::findNetworkHex(std::string packetHex)
{
    int ipVersion = operations::hexToDec(packetHex[0]);

    if (ipVersion == 4) {
        return packetHex.substr(0, 20 * 2);
    }

    return "Not an ipv4 packet...";
}