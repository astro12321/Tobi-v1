#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"


class Transport 
{       
    private:
        hex h;
        int transportProto;

    public:
        Transport() = default;
        Transport(hex &hex);
        virtual ~Transport() = default;

        int getTransportProto();

        virtual int getType();
        virtual int getCode();
};


#endif