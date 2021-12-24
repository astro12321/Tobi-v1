#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "transport.hpp"
#include "hex.hpp"


Transport::Transport(hex &hex)
{
    this->h = hex;
}


int Transport::getTransportProto() { return this->transportProto; }

int Transport::getType() { return -1; }
int Transport::getCode() { return -1; }