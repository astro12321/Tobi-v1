#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <network.hpp>

class IP;
class hex;
class byte;


namespace ipv4 //Namespace because this Hex class will have fields that are unique to ipv4
{
    class Frame: public hex
    {
        private:
            hex source;
            hex dest;
            byte ttl;
            byte transportProto;

        public:
            Frame() = default;
            Frame(hex &aHex);

            const hex &getSource() const;
            const hex &getDest() const;
            const byte &getTtl() const;
            const byte &getTransportProto() const;
    };
}


class Ipv4 : public Network
{
    private:
        ipv4::Frame frame;
        Address source;
        Address dest;
        int ttl;
        int transportProto;

        int findPktStatus() const;
    
    public:
        Ipv4() = default;
        Ipv4(hex &hex);

        int getTTL() const;
};


#endif