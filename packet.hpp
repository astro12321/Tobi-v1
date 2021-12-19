#ifndef PACKET_HPP
#define PACKET_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "network.hpp"
#include "layer.hpp"

#define BUFFERSIZE 4096

//using namespace std;


class Packet 
{       
    public:
        unsigned char bytes[BUFFERSIZE];
        int index;
        int length;
        std::string hex; //Could maybe do a Hex class for the packet (in it's own namespace)
        Layer layer;

        Packet(int ind, unsigned char *buf, int br);
};


#endif