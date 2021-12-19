#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iomanip>

#include "packet.hpp"
#include "network.hpp"
#include "operations.hpp"

#define BUFFERSIZE 4096

//using namespace std;


Packet::Packet(int ind, unsigned char *buffer, int bytesRead)
{
    memcpy(bytes, buffer, BUFFERSIZE);
    index = ind;
    length = bytesRead;

    this->hex = operations::bytesToHex(bytes, length);
    
    this->layer = Layer(hex);
}