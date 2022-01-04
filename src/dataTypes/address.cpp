//Custom data types
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include <address.hpp>
#include <hex.hpp>


Address::Address(const hex &aHex, int type)
{
    this->h = aHex;

    switch (type)
    {
        case 6: //IPv6 specified
        {
            std::string addr = "";

            for (size_t i = 0; i < (size_t)aHex.numberOfBytes(); i++)
            {
                addr += aHex[i].to_string();

                if (i % 2 != 0 && i > 0 && i < (size_t)aHex.numberOfBytes() - 1) addr += ":";
            }

            this->addr = addr;

            break;         
        }

        default: //Automatic conversion (IPv4 or CNAME)
        {
            if (aHex.numberOfBytes() == 4) //IP address
            {
                std::string b1 = std::to_string(aHex[0].to_dec());
                std::string b2 = std::to_string(aHex[1].to_dec());
                std::string b3 = std::to_string(aHex[2].to_dec());
                std::string b4 = std::to_string(aHex[3].to_dec());

                this->addr = b1 + "." + b2 + "." + b3 + "." + b4;
            }
            
            else this->addr = aHex.convert_to_string(); //Converts CNAME

            break;
        }
      
    }

}

Address::Address(std::string addr) { 
    this->addr = addr;
    //this->h = hex("");
}

std::string Address::to_string() const { return this->addr; }
const hex &Address::to_hex() const { return this->h; }

void Address::convertToIPv6()
{
    
}