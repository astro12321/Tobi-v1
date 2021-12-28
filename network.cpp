#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "hex.hpp"


Network::Network(hex &hex) {  this->h = hex; }


//virtual
int Network::getTTL() { return -1; }

hex& Network::getHex() { return this->h; }

std::string Network::getSource() { return this->source; };
std::string Network::getDest() { return this->dest; };
int Network::getStatus() { return this->status; }
int Network::getTransportProto() { return this->transportProto; }
int Network::getNetworkProto() { return this->networkProto; }


void Network::setTransportProto(int transportProto) { this->transportProto = transportProto; }
void Network::setNetworkProto(int networkProto) { this->networkProto = networkProto; }
void Network::setSource(std::string source) { this->source = source; }
void Network::setDest(std::string dest) { this->dest = dest; }
void Network::setStatus(int status) { this->status = status; }