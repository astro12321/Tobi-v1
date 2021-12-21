#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "layer.hpp"
#include "hex.hpp"

#define BUFFERSIZE 4096

//using namespace std;


class Packet 
{       
    public:
        int index;
        Layer layer;
        class::hex hex;

        Packet(int ind, class::hex hex);
};


#endif