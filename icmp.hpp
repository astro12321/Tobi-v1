#ifndef ICMP_HPP
#define ICMP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "transport.hpp"


namespace icmp //Namespace because this Hex class will have fields that are unique to ipv4
{
    class Frame: public hex
    {
        public:
            byte type;
            byte code;
            hex checksum;
            hex data;

            Frame() = default;
            Frame(hex &he);
    };
}


class ICMP : public Transport
{
    private:
        int type;
        int code;

    public:
        icmp::Frame frame;

        ICMP() = default;
        ICMP(hex &hex);

        int getType();
        int getCode();
};


#endif