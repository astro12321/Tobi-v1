#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "transport.hpp"
#include "icmp.hpp"
#include "defaults.hpp"


namespace icmp
{
    Frame::Frame(hex &he): hex(he)
    {
        this->type = he[0];
        this->code = he[1];
        this->checksum = he.substr(2, 2);
        this->data = he.substr(4, he.numberOfBytes() - 4);
    }
}


ICMP::ICMP(hex &hex): Transport(hex)
{
    this->frame = icmp::Frame(hex);
}


int ICMP::getType() { return this->frame.type.to_dec(); }
int ICMP::getCode() { return this->frame.code.to_dec(); }