#ifndef ICMP_HPP
#define ICMP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class hex;
class Transport;


namespace icmp
{
    class Frame: public hex
    {
        private:
            byte type;
            byte code;
            hex csum;
            hex data;

        public: //Could add checksum status support
            Frame() = default;
            Frame(hex &aHex);

            byte &getType();
            byte &getCode();
            hex &getCsum();
            hex &getData();
    };
}


class ICMP : public Transport
{
    private:
        icmp::Frame frame;
        int type;
        int code;
        std::string csum;
        std::string data;

    public:
        ICMP() = default;
        ICMP(hex &hex);

        int getType();
        int getCode();
        std::string getData();
};


#endif