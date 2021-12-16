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

            Hex() = default;
            Hex(std::string hex);
    };

}


class Ipv4 
{       
    public:
        ipv4::Hex hex;

        Ipv4() = default;
        Ipv4(std::string hex);
};


#endif