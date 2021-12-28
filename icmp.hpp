#ifndef ICMP_HPP
#define ICMP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "transport.hpp"


namespace icmp
{
    class Frame: public hex
    {
        private:
            byte type;
            byte code;
            hex checksum;
            hex data;

        public: //Could add checksum status support
            Frame() = default;
            Frame(hex &aHex);

            byte &getType();
            byte &getCode();
            hex &getChecksum();
            hex &getData();
    };
}


class ICMP : public Transport
{
    private:
        icmp::Frame frame;
        int type;
        int code;
        std::string checksum;
        std::string data;

    public:
        ICMP() = default;
        ICMP(hex &hex);

        int getType();
        int getCode();
        std::string getChecksum();
        std::string getData();
};


#endif