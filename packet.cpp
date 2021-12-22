#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "packet.hpp"
#include "network.hpp"
#include "hex.hpp"

#define BUFFERSIZE 4096

//using namespace std;


Packet::Packet(int ind, class::hex hex)
{
    this->index = ind;
    this->hex = hex;

    this->layer = Layer(hex.to_string());
}