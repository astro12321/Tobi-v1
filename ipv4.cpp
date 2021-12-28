#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "ipv4.hpp"
#include "hex.hpp"
#include "network.hpp"
#include "defaults.hpp"


namespace ipv4
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->source = aHex.substr(12, 4);
        this->dest = aHex.substr(16, 4);
        this->ttl = aHex[8];
        this->transportProto = aHex[9];
    }

    hex &Frame::getSource() { return this->source; }   
    hex &Frame::getDest() { return this->dest; }
    byte &Frame::getTtl() { return this->ttl; }
    byte &Frame::getTransportProto() { return this->transportProto; }
}


Ipv4::Ipv4(hex &hex): Network(hex)
{
    this->frame = ipv4::Frame(hex); //ipv4::Frame(hex);

    this->source = hexToIP(frame.getSource());
    this->dest = hexToIP(frame.getDest());
    this->ttl = frame.getTtl().to_dec();
    this->transportProto = frame.getTransportProto().to_dec();
    
    //Setting parents variables
    this->setNetworkProto(4);
    this->setSource(source);
    this->setDest(dest);
    this->setStatus(findPktStatus());
    this->setTransportProto(transportProto);
}


std::string Ipv4::hexToIP(hex &hex) { return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }


int Ipv4::getTTL() { return this->ttl; }

int Ipv4::findPktStatus() {
    if (this->getSource() == INTIP) return 1;
    return 0;
}