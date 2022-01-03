#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <network.hpp>
#include <hex.hpp>
#include <address.hpp>
#include <defaults.hpp>


Network::Network(hex &hex, int proto) 
{  
    this->h = hex; 
    this->networkProto = proto;

    this->transportProto = -1;
    this->status = -1;
    this->source = Address(UNDEF);
    this->dest = Address(UNDEF);
}


//virtual IPv4
int Network::getTTL() const { return -1; }

const hex& Network::getHex() const { return this->h; }

Address Network::getSource() const { return this->source; };
Address Network::getDest() const { return this->dest; };
int Network::getStatus() const { return this->status; }
int Network::getTransportProto() const { return this->transportProto; }
int Network::getNetworkProto() const { return this->networkProto; }


void Network::setTransportProto(int transportProto) { this->transportProto = transportProto; }
void Network::setSource(Address source) { this->source = source; }
void Network::setDest(Address dest) { this->dest = dest; }
void Network::setStatus(int status) { this->status = status; }