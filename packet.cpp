#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "packet.hpp"
#include "network.hpp"
#include "hex.hpp"
#include "defaults.hpp"


Packet::Packet(int ind, hex &hex)
{
    this->index = ind;
    this->h = hex;
    this->layer = Layer(hex);

    this->status = setStatus(this->layer.getStatus());
    this->transportProto = setTransportProto(this->layer.getNetwork().getTransportProto()); //Could change to take the protocol directly in transport layer
    this->networkProto = setNetworkProto(this->layer.getNetwork().getNetworkProto());
}


hex &Packet::getHex() { return this->h; }
Layer &Packet::getLayer() { return this->layer; }
std::string Packet::getStatus() { return this->status; }
int Packet::getIndex() { return this->index; }
std::string Packet::getTransportProto() { return this->transportProto; }
std::string Packet::getNetworkProto() { return this->networkProto; }


std::string Packet::setStatus(int status)
{
    if (status == 1) return "SENT";
    else if ((status == 0)) return "RECV";
    return undef;
}


std::string Packet::setNetworkProto(int proto)
{
    switch(proto)
    {
        case 4: return "IPv4";
        default: return undef;
    }
}


std::string Packet::setTransportProto(int proto)
{
    switch(proto)
    {
        case 1: return "ICMP";
        case 6: return "TCP";
        case 17: return "UDP";
        default: return undef;
    }
}