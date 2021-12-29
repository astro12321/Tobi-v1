#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "transport.hpp"
#include "hex.hpp"
#include "defaults.hpp"


Transport::Transport(hex &hex, int proto) 
{
    this->h = hex; 
    this->transportProto = proto;

    this->source = -1;
    this->dest = -1;
    this->csum = UNDEF;
}


//virtual ICMP
int Transport::getType() { return -1; }
int Transport::getCode() { return -1; }
std::string Transport::getData() { return UNDEF; }

//virtual TCP
std::string Transport::getSeqNumber() { return UNDEF; }
std::string Transport::getAckNumber() { return UNDEF; }
int Transport::getHdrLen() { return -1; }
std::string Transport::getFlags() { return UNDEF; }
int Transport::getWindow() { return -1; }

//virtual UDP



hex &Transport::getHex() { return this->h; }

int Transport::getTransportProto() { return this->transportProto; }
int Transport::getSource() { return this->source; }
int Transport::getDest() { return this->dest; }
std::string Transport::getCsum() { return this->csum; }


void Transport::setSource(int source) { this->source = source; }
void Transport::setDest(int dest) { this->dest = dest; }
void Transport::setCsum(std::string csum) { this->csum = csum; }