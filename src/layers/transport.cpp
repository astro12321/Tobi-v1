#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <transport.hpp>
#include <hex.hpp>
#include <byte.hpp>
#include <defaults.hpp>


Transport::Transport(hex &hex, int proto) 
{
    this->h = hex; 
    this->proto = proto;

    this->source = -1;
    this->dest = -1;
    this->csum = UNDEF;
}


//virtual ICMP
int Transport::getType() const { return -1; }
int Transport::getCode() const { return -1; }
std::string Transport::getData() const { return UNDEF; }

//virtual TCP
std::string Transport::getSeqNumber() const { return UNDEF; }
std::string Transport::getAckNumber() const { return UNDEF; }
int Transport::getHdrLen() const { return -1; }
std::string Transport::getFlags() const { return UNDEF; }
int Transport::getWindow() const { return -1; }



const hex &Transport::getHex() const { return this->h; }
int Transport::getProto() const { return this->proto; }
int Transport::getSource() const { return this->source; }
int Transport::getDest() const { return this->dest; }
std::string Transport::getCsum() const { return this->csum; }


void Transport::setSource(int source) { this->source = source; }
void Transport::setDest(int dest) { this->dest = dest; }
void Transport::setCsum(std::string csum) { this->csum = csum; }