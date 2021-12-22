#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"

//using namespace std;


namespace ipv4 //Namespace because this Hex class will have fields that are unique to ipv4
{
    class Hex
    {       
        public:
            ::hex hex;
            ::hex source;
            ::hex dest;
            byte ttl;
            byte transportProt;

            Hex() = default;
            Hex(::hex hex);
    };

}


class Ipv4 
{       
    public:
        ipv4::Hex hex;
        std::string source;
        std::string dest;
        int ttl;
        std::string transportProt;

        Ipv4() = default;
        Ipv4(::hex hex);
    
    private:
        std::string getIp(::hex hex);
        std::string getTransportProt(int prot);
};


#endif