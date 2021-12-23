#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
//#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;


Network::Network(hex &hex)
{
    this->h = hex;

    //Attributing the network header to the good protocol
    int ipVersion = hex[0].first().to_dec();

    /*if (ipVersion == 4) {
        this->ipv4 = Ipv4(hex);
        this->transportProt = ipv4.transportProt;
    }*/

}


int Network::getTTL() { return -1; }