#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <transport.hpp>
#include <udp.hpp>


namespace udp
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->source = aHex.substr(0, 2);
        this->dest = aHex.substr(2, 2);
        this->csum = aHex.substr(6, 2);
    }

    const hex &Frame::getSource() const { return this->source; }
    const hex &Frame::getDest() const { return this->dest; }
    const hex &Frame::getCsum() const { return this->csum; }
}


UDP::UDP(hex &hex): Transport(hex, 17)
{
    this->frame = udp::Frame(hex);

    this->source = frame.getSource().to_dec();
    this->dest = frame.getDest().to_dec();
    this->csum = frame.getCsum().to_fstring();

    //Setting parents variables
    setSource(source);
    setDest(dest);
    setCsum(csum);
}