#ifndef IPV4_HPP
#define IPV4_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

//using namespace std;


namespace ipv4 //Namespace because this Hex class will have fields that are unique to ipv4
{
    class Hex
    {       
        public:
            std::string hex;
            std::string source;
            std::string dest;
            std::string ttl;
            std::string transportProt;

            Hex() = default;
            Hex(std::string hex);
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
        Ipv4(std::string hexStr);
    
    private:
        std::string getIp(std::string hex);
        std::string getTransportProt(std::string hex);
};


#endif