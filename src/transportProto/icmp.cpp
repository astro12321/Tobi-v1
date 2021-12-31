#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <transport.hpp>
#include <icmp.hpp>
#include <defaults.hpp>


namespace icmp
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->type = aHex[0];
        this->code = aHex[1];
        this->csum = aHex.substr(2, 2);
        this->data = aHex.substr(16, aHex.numberOfBytes() - 16);
    }

    byte &Frame::getType() { return this->type; }
    byte &Frame::getCode() { return this->code; }
    hex &Frame::getCsum() { return this->csum; }
    hex &Frame::getData() { return this->data; }
}


ICMP::ICMP(hex &hex): Transport(hex, 1) //1 for ICMP
{
    this->frame = icmp::Frame(hex);

    this->type = frame.getType().to_dec();
    this->code = frame.getCode().to_dec();
    this->csum = frame.getCsum().to_fstring();
    this->data = frame.getData().to_fstring();

    //Setting parents variables
    setCsum(csum);
}


int ICMP::getType() { return this->type; }
int ICMP::getCode() { return this->code; }
std::string ICMP::getData() { return this->data; }