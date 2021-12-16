#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "layer.hpp"
#include "transport.hpp"

//using namespace std;


Layer::Layer(std::string packetHex)
{
    this->packetHex = packetHex;

    //Giving each layers their bytes of the packet
    this->transport = Transport(packetHex);
}