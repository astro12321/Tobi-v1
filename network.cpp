#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "ipv4.hpp"
#include "hex.hpp"

//using namespace std;


Network::Network(hex h)
{
    this->h = h;

    //Attributing the transport header to the good protocol
    int ipVersion = h[0].first().to_dec();

    if (ipVersion == 4) {
        this->ipv4 = Ipv4(h);
        this->transportProt = ipv4.transportProt;
    }

}