#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "operations.hpp"

//using namespace std;


Ipv4::Ipv4(std::string hexStr)
{
    this->hex = ipv4::Hex(hexStr);

    this->source = getIp(hex.source);
    this->dest = getIp(hex.dest);
    this->ttl = operations::hexToDec(hex.ttl);
    this->protocol = getProtocol(hex.protocol);
}


std::string Ipv4::getIp(std::string hex)
{
    int ipByte1 = operations::hexToDec(hex.substr(0, 2));
    int ipByte2 = operations::hexToDec(hex.substr(2, 2));
    int ipByte3 = operations::hexToDec(hex.substr(4, 2));
    int ipByte4 = operations::hexToDec(hex.substr(6, 2));
    
    std::string ip = std::to_string(ipByte1) + "." + std::to_string(ipByte2) + "." + std::to_string(ipByte3) + "." + std::to_string(ipByte4);

    return ip;
}


std::string Ipv4::getProtocol(std::string hex)
{
    int prot = operations::hexToDec(hex);

    switch(prot)
    {
        case 1: return "ICMP";
        case 6: return "TCP";
        case 17: return "UDP";
        default: return "unknown";
    }
}


namespace ipv4
{
    Hex::Hex(std::string hex)
    {
        this->hex = hex;
        this->source = hex.substr(12 * 2, 8);
        this->dest = hex.substr(16 * 2, 8);
        this->ttl = hex.substr(8 * 2, 2);
        this->protocol = hex.substr(9 * 2, 2);
    }

}