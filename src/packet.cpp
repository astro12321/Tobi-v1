#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <packet.hpp>
#include <network.hpp>
#include <hex.hpp>
#include <defaults.hpp>
#include <dns.hpp>
#include <layer.hpp>


Packet::Packet(int ind, hex &hex)
{
    this->index = ind;
    this->h = hex;
    this->layer = Layer(hex);

    if (layer.networkIsValid())
    {
        this->status = setStatus(layer.getNetwork().getStatus());

        this->networkProto = setNetworkProto(layer.getNetwork().getNetworkProto());
        this->transportProto = setTransportProto(layer.getNetwork().getTransportProto());

        if (layer.applicationIsValid()) this->applicationProto = layer.getApplication().getProto();
        else this->applicationProto = UNDEF;
    }
}


const hex &Packet::getHex() const { return this->h; }
const Layer &Packet::getLayer() const { return this->layer; }
std::string Packet::getStatus() const { return this->status; }
int Packet::getIndex() const { return this->index; }
std::string Packet::getTransportProto() const { return this->transportProto; }
std::string Packet::getNetworkProto() const { return this->networkProto; }
std::string Packet::getApplicationProto() const { return this->applicationProto; }


std::string Packet::setStatus(int status) const
{
    if (status == 1) return "SENT";
    return "RECV";
}


std::string Packet::setNetworkProto(int proto) const
{
    switch(proto) {
        case 4: return "IPv4";
        default: return UNDEF; //Should never return (the isValid bool would be false in this case)
    }
}


std::string Packet::setTransportProto(int proto) const
{
    switch(proto) {
        case 1: return "ICMP";
        case 6: return "TCP";
        case 17: return "UDP";
        default: return UNDEF;
    }
}