#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <ipv4.hpp>
#include <hex.hpp>
#include <network.hpp>
#include <defaults.hpp>


namespace ipv4
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->source = aHex.substr(12, 4);
        this->dest = aHex.substr(16, 4);
        this->ttl = aHex[8];
        this->transportProto = aHex[9];
    }

    const hex &Frame::getSource() const { return this->source; }   
    const hex &Frame::getDest() const { return this->dest; }
    const byte &Frame::getTtl() const { return this->ttl; }
    const byte &Frame::getTransportProto() const { return this->transportProto; }
}


Ipv4::Ipv4(hex &hex): Network(hex, 4)
{
    this->frame = ipv4::Frame(hex); //ipv4::Frame(hex);

    this->source = hexToIP(frame.getSource());
    this->dest = hexToIP(frame.getDest());
    this->ttl = frame.getTtl().to_dec();
    this->transportProto = frame.getTransportProto().to_dec();
    
    //Setting parents variables
    this->setSource(source);
    this->setDest(dest);
    this->setStatus(findPktStatus());
    this->setTransportProto(transportProto);
}


std::string Ipv4::hexToIP(const hex &hex) const {  return std::to_string(hex[0].to_dec()) + "." + std::to_string(hex[1].to_dec()) + "." + std::to_string(hex[2].to_dec()) + "." + std::to_string(hex[3].to_dec()); }


int Ipv4::getTTL() const { return this->ttl; }

int Ipv4::findPktStatus() const {
    if (this->getSource() == INTIP) return 1;
    return 0;
}