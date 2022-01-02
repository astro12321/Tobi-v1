#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <network.hpp>
#include <hex.hpp>
#include <ip.hpp>
#include <defaults.hpp>


Network::Network(hex &hex, int proto) 
{  
    this->h = hex; 
    this->networkProto = proto;

    this->transportProto = -1;
    this->status = -1;
    this->source = IP(UNDEF);
    this->dest = IP(UNDEF);
}


//virtual IPv4
int Network::getTTL() const { return -1; }

const hex& Network::getHex() const { return this->h; }

IP Network::getSource() const { return this->source; };
IP Network::getDest() const { return this->dest; };
int Network::getStatus() const { return this->status; }
int Network::getTransportProto() const { return this->transportProto; }
int Network::getNetworkProto() const { return this->networkProto; }


void Network::setTransportProto(int transportProto) { this->transportProto = transportProto; }
void Network::setSource(IP source) { this->source = source; }
void Network::setDest(IP dest) { this->dest = dest; }
void Network::setStatus(int status) { this->status = status; }