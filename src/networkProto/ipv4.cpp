#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <ipv4.hpp>
#include <address.hpp>
#include <hex.hpp>
#include <byte.hpp>
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

    this->source = Address(frame.getSource());
    this->dest = Address(frame.getDest());
    this->ttl = frame.getTtl().to_dec();
    this->transportProto = frame.getTransportProto().to_dec();
    
    //Setting parents variables
    this->setSource(source);
    this->setDest(dest);
    this->setStatus(findPktStatus());
    this->setTransportProto(transportProto);
}


int Ipv4::getTTL() const { return this->ttl; }

int Ipv4::findPktStatus() const {
    if (this->getSource().to_string() == INTIP.to_string()) return 1;
    return 0;
}