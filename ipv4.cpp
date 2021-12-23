#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;

#include "network.hpp"


//namespace ipv4
//{
Frame::Frame(hex &he): hex(he)
{
    this->source = he.substr(12, 4);
    this->dest = he.substr(16, 4);
    this->ttl = he[8];
    this->transportProt = he[9];
}

//}


Ipv4::Ipv4(hex &hex): Network(hex)
{
    this->frame = Frame(hex); //ipv4::Frame(hex);
    ///////////

    this->source = getIp(this->frame.source);
    this->dest = getIp(this->frame.dest);
    this->ttl = this->frame.ttl.to_dec();
    this->transportProt = getTransportProt(this->frame.transportProt.to_dec());
}


std::string Ipv4::getIp(hex &hex) { return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }


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


int Ipv4::getTTL()
{
    return this->ttl;
}