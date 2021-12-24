#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"
#include "network.hpp"
#include "defaults.hpp"

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
    this->frame = Frame(hex); //ipv4::Frame(hex);
    this->ttl = this->frame.ttl.to_dec();
    
    //Setting parent variable
    this->setNetworkProto(4);
    this->setSource(hexToIP(this->frame.source));
    this->setDest(hexToIP(this->frame.dest));
    this->setStatus(findPktStatus());
    this->setTransportProto(this->frame.transportProto.to_dec());
}


std::string Ipv4::hexToIP(hex &hex) { return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }

int Ipv4::getTTL() { return this->ttl; }

int Ipv4::findPktStatus()
{
    if (this->getSource() == INTIP) return 1;
    return 0;
}