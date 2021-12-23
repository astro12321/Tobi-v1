#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "hex.hpp"

#include "network.hpp"

//using namespace std;


//namespace ipv4 //Namespace because this Hex class will have fields that are unique to ipv4
//{
class Frame: public hex
{
    public:
        hex source;
        hex dest;
        byte ttl;
        byte transportProt;

        Frame() = default;
        Frame(hex &he);
};

//}


class Ipv4 : public Network
{       
    public:
        /*ipv4::*/Frame frame;
        int ttl;

        Ipv4() = default;
        Ipv4(hex &hex);
        
        int getTTL();
    
    private:
        std::string getIp(hex &hex);
        std::string getTransportProt(int prot);
};


#endif