#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;


Ipv4::Ipv4(::hex hex)
{
    this->hex = ipv4::Hex(hex);

    this->source = getIp(this->hex.source);
    this->dest = getIp(this->hex.dest);
    this->ttl = this->hex.ttl.to_dec();
    this->transportProt = getTransportProt(this->hex.transportProt.to_dec());
}


std::string Ipv4::getIp(::hex hex) { return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }


std::string Ipv4::getTransportProt(int prot)
{
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
    Hex::Hex(::hex hex)
    {
        this->hex = hex;
        this->source = hex.substr(12, 4);
        this->dest = hex.substr(16, 4);
        this->ttl = hex[8];
        this->transportProt = hex[9];
    }

}