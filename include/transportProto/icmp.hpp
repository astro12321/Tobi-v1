#ifndef ICMP_HPP
#define ICMP_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <transport.hpp>

class hex;
class byte;


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

            const byte &getType() const;
            const byte &getCode() const;
            const hex &getCsum() const;
            const hex &getData() const;
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

        int getType() const;
        int getCode() const;
        std::string getData() const;
};


#endif