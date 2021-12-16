#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "transport.hpp"
#include "ipv4.hpp"

//using namespace std;


Transport::Transport(std::string hex)
{
    this->hex = hex;

    //Attributing the transport header to the good protocol
    this->ipv4 = Ipv4(hex);
}