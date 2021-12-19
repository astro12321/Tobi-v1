#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "ipv4.hpp"
#include "operations.hpp"

//using namespace std;


Network::Network(std::string hex)
{
    this->hex = hex;

    //Attributing the transport header to the good protocol
    int ipVersion = operations::hexToDec(hex[0]);

    if (ipVersion == 4) {
        this->ipv4 = Ipv4(hex);
    }

}