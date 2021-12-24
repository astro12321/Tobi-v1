#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"
#include "network.hpp"


namespace ipv4 //Namespace because this Hex class will have fields that are unique to ipv4
{
    class Frame: public hex
    {
        public:
            hex source;
            hex dest;
            byte ttl;
            byte transportProto;

            Frame() = default;
            Frame(hex &he);
    };
}


class Ipv4 : public Network
{
    private:
        std::string hexToIP(hex &hex);
        int findPktStatus();
    
    public:
        ipv4::Frame frame;
        int ttl;

        Ipv4() = default;
        Ipv4(hex &hex);
        
        int getTTL();
};


#endif