#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <icmp.hpp>
#include <hex.hpp>
#include <byte.hpp>
#include <transport.hpp>
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

    const byte &Frame::getType() const { return this->type; }
    const byte &Frame::getCode() const { return this->code; }
    const hex &Frame::getCsum() const { return this->csum; }
    const hex &Frame::getData() const { return this->data; }
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


int ICMP::getType() const { return this->type; }
int ICMP::getCode() const { return this->code; }
std::string ICMP::getData() const { return this->data; }