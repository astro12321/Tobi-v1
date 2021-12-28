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
        Transport(hex &hex, int proto);
        virtual ~Transport() = default;

        hex &getHex();
        int getTransportProto();

        //ICMP
        virtual int getType();
        virtual int getCode();
        virtual std::string getChecksum();
        virtual std::string getData();

        //TCP


        //UDP


};


#endif