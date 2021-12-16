#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "ipv4.hpp"

//using namespace std;


Network::Network(std::string hex)
{
    this->hex = hex;

    //Attributing the transport header to the good protocol
    this->ipv4 = Ipv4(hex);
}