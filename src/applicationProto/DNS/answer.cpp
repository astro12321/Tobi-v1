#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <answer.hpp>
#include <address.hpp>


namespace dns
{
    namespace answer
    {
        Frame::Frame(hex &aHex): hex(aHex)
        {
            this->name = aHex.substr(0, 2);
            this->type = aHex.substr(2, 2);
            this->_class = aHex.substr(4, 2);
            this->ttl = aHex.substr(6, 4);
            this->address = aHex.substr(12, aHex.numberOfBytes() - 12);
        }


        const hex &Frame::getName() const { return this->name; }
        const hex &Frame::getType() const { return this->type; }
        const hex &Frame::getClass() const { return this->_class; }
        const hex &Frame::getTtl() const { return this->ttl; }
        const hex &Frame::getAddress() const { return this->address; }



        Answer::Answer(hex &aHex)
        {
            this->frame = Frame(aHex);

            this->name = frame.getName().to_fstring(); //Pointer to address in packet
            this->type = frame.getType().to_dec();
            this->_class = frame.getClass().to_fstring();
            this->ttl = frame.getTtl().to_dec();

            if (type == 28) this->address = Address(frame.getAddress(), 6); //If it's IPv6 we need to specify it to the address class
            else this->address = Address(frame.getAddress());
        }


        const std::string &Answer::getName() const { return this->name; }
        int Answer::getType() const { return this->type; }
        std::string Answer::getClass() const { return this->_class; }
        const int &Answer::getTtl() const { return this->ttl; }
        const Address &Answer::getAddress() const { return this->address; }
    }

}