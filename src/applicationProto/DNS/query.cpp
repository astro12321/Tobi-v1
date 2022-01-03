#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <hex.hpp>
#include <query.hpp>
#include <address.hpp>


namespace dns
{
    namespace query
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



        Query::Query(hex &hex)
        {
            this->frame = Frame(hex);

            this->name = Address(frame.getName());
            this->type = frame.getType().to_dec();
            this->_class = frame.getClass().to_fstring();
        }


        const Address &Query::getName() const { return this->name; }
        int Query::getType() const { return this->type; }
        std::string Query::getClass() const { return this->_class; }
    }

}