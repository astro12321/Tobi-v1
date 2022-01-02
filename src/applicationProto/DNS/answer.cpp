#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <answer.hpp>
#include <ip.hpp>


namespace dns
{
    namespace answer
    {
        Frame::Frame(hex &aHex): hex(aHex)
        {
            int nameLen = aHex.numberOfBytes() - 4;

            this->name = aHex.substr(0, nameLen);
            this->type = aHex.substr(nameLen, 2);
            this->_class = aHex.substr(nameLen + 2, 2);
        }


        const hex &Frame::getName() const { return this->name; }
        const hex &Frame::getType() const { return this->type; }
        const hex &Frame::getClass() const { return this->_class; }
        const hex &Frame::getTtl() const { return this->ttl; }
        const hex &Frame::getAddress() const { return this->address; }



        Answer::Answer(hex &hex)
        {
            this->frame = Frame(hex);

            this->name = frame.getName().to_fstring();
            this->type = frame.getType().to_dec();
            this->_class = frame.getClass().to_fstring();
        }

    }

}