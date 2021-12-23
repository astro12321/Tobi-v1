#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"
#include "network.hpp"


//namespace ipv4
//{
Frame::Frame(hex &he): hex(he)
{
    this->source = he.substr(12, 4);
    this->dest = he.substr(16, 4);
    this->ttl = he[8];
    this->transportProto = he[9];
}

//}


Ipv4::Ipv4(hex &hex): Network(hex)
{
    this->setNetworkProto(4);
    this->frame = Frame(hex); //ipv4::Frame(hex);
    this->ttl = this->frame.ttl.to_dec();
    
    //Setting parent variable
    this->setSource(getIp(this->frame.source));
    this->setDest(getIp(this->frame.dest));
    this->setTransportProto(this->frame.transportProto.to_dec());
}


std::string Ipv4::getIp(hex &hex) { return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }

/*
std::string Ipv4::getTransportProt(int prot)
{
    switch(prot)
    {
        case 1: return "ICMP";
        case 6: return "TCP";
        case 17: return "UDP";
        default: return "unknown";
    }
}*/


int Ipv4::getTTL() { return this->ttl; }