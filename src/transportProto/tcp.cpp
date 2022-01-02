#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <transport.hpp>
#include <tcp.hpp>


namespace tcp
{
    Frame::Frame(hex &aHex): hex(aHex)
    {
        this->source = aHex.substr(0, 2);
        this->dest = aHex.substr(2, 2);
        this->seqNumber = aHex.substr(4, 4);
        this->ackNumber = aHex.substr(8, 4);
        this->hdrLen = aHex[12].first();
        this->flags = aHex[12].last().to_string() + aHex[13].to_string();
        this->window = aHex.substr(14, 2);
        this->csum = aHex.substr(16, 2);
    }

    const hex &Frame::getSource() const { return this->source; }
    const hex &Frame::getDest() const { return this->dest; }
    const hex &Frame::getSeqNumber() const { return this->seqNumber; }
    const hex &Frame::getAckNumber() const { return this->ackNumber; }
    const byte &Frame::getHdrLen() const { return this->hdrLen; }
    const hex &Frame::getFlags() const { return this->flags; }
    const hex &Frame::getWindow() const { return this->window; }
    const hex &Frame::getCsum() const { return this->csum; }
}


TCP::TCP(hex &hex): Transport(hex, 6) //6 for TCP
{
    this->frame = tcp::Frame(hex);

    this->source = frame.getSource().to_dec();
    this->dest = frame.getDest().to_dec();
    this->seqNumber = frame.getSeqNumber().to_fstring();
    this->ackNumber = frame.getAckNumber().to_fstring();
    this->hdrLen = frame.getHdrLen().to_dec();
    this->flags = frame.getFlags().to_fstring();
    this->window = frame.getWindow().to_dec();
    this->csum = frame.getCsum().to_fstring();

    //Setting parents variables
    setSource(source);
    setDest(dest);
    setCsum(csum);
}


std::string TCP::getSeqNumber() const { return this->seqNumber; }
std::string TCP::getAckNumber() const { return this->ackNumber; }
int TCP::getHdrLen() const { return this->hdrLen; }
std::string TCP::getFlags() const { return this->flags; }
int TCP::getWindow() const { return this->window; }