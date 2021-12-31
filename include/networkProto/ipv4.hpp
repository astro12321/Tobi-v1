#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <network.hpp>

class hex;


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

            hex &getSource();
            hex &getDest();
            byte &getTtl();
            byte &getTransportProto();
    };
}


class Ipv4 : public Network
{
    private:
        ipv4::Frame frame;
        std::string source;
        std::string dest;
        int ttl;
        int transportProto;

        std::string hexToIP(hex &hex);
        int findPktStatus();
    
    public:
        Ipv4() = default;
        Ipv4(hex &hex);

        int getTTL();
};


#endif