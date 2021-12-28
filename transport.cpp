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
}


//virtual
int Transport::getType() { return -1; }
int Transport::getCode() { return -1; }
std::string Transport::getChecksum() { return UNDEF; }
std::string Transport::getData() { return UNDEF; }

hex &Transport::getHex() { return this->h; }

int Transport::getTransportProto() { return this->transportProto; }